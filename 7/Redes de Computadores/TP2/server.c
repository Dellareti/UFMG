#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include "common.h"
#include "grafo.h"
#include "rede.h"

// Variáveis globais
estrutura_grafo_t grafo;
int modo_ipv6 = 0;
int equipes_livres[MAX_CIDADES];  // 1=livre, 0=ocupada
int sock_global = -1;
volatile int servidor_ativo = 1;

// Handler para shutdown
void signal_handler(int sig) {
    (void)sig;
    printf("\n\nEncerrando servidor...\n");
    servidor_ativo = 0;

    if (sock_global >= 0) {
        shutdown(sock_global, SHUT_RDWR);
        close(sock_global);
    }

    liberar_grafo(&grafo);
    exit(0);
}

void enviar_ack(int sock, struct sockaddr *cliente_addr, socklen_t cliente_len, int tipo_ack) {
    header_t header;
    header.tipo = MSG_ACK;
    header.tamanho = sizeof(payload_ack_t);

    payload_ack_t payload;
    payload.status = tipo_ack;

    char buffer[BUFFER_SIZE];
    memcpy(buffer, &header, sizeof(header_t));
    memcpy(buffer + sizeof(header_t), &payload, sizeof(payload_ack_t));

    sendto(sock, buffer, sizeof(header_t) + sizeof(payload_ack_t), 0,cliente_addr, cliente_len);
    printf("-> ACK enviado (tipo=%d)\n", tipo_ack);
}

void enviar_ordem_drone(int sock, struct sockaddr *cliente_addr, socklen_t cliente_len,int id_cidade, int id_equipe) {
    header_t header;
    header.tipo = MSG_EQUIPE_DRONE;
    header.tamanho = sizeof(payload_equipe_drone_t);

    payload_equipe_drone_t payload;
    payload.id_cidade = id_cidade;
    payload.id_equipe = id_equipe;

    char buffer[BUFFER_SIZE];
    memcpy(buffer, &header, sizeof(header_t));
    memcpy(buffer + sizeof(header_t), &payload, sizeof(payload_equipe_drone_t));

    sendto(sock, buffer, sizeof(header_t) + sizeof(payload_equipe_drone_t), 0,cliente_addr, cliente_len);

    printf("-> Ordem enviada: Equipe %s (ID=%d) -> Cidade %s (ID=%d)\n",
           grafo.vertices[id_equipe].nome, id_equipe,
           grafo.vertices[id_cidade].nome, id_cidade);
}

int identificar_alertas(payload_telemetria_t *payload, int *cidades_alerta) {
    int num_alertas = 0;

    for (int i = 0; i < payload->total; i++) {
        if (payload->dados[i].status == STATUS_ALERTA) {
            int id = payload->dados[i].id_cidade;
            printf("ALERTA: %s (ID=%d)\n", grafo.vertices[id].nome, id);
            cidades_alerta[num_alertas++] = id;
        }
    }

    return num_alertas;
}

void despachar_drone_para_alerta(int sock, struct sockaddr *cliente_addr,
                                  socklen_t cliente_len, int id_cidade) {
    printf("\n[DESPACHANDO DRONES]\n");
    printf("Cidade em alerta: %s (ID=%d)\n",
           grafo.vertices[id_cidade].nome, id_cidade);

    int distancia;
    int id_equipe = buscar_capital_livre(&grafo, equipes_livres, id_cidade, &distancia);

    if (id_equipe == -1) {
        printf("-> Nenhuma equipe disponível no momento\n");
        return;
    }

    printf("-> Dijkstra: capital %s (ID=%d) selecionada, distância=%d km\n",grafo.vertices[id_equipe].nome, id_equipe, distancia);

    equipes_livres[id_equipe] = 0;
    enviar_ordem_drone(sock, cliente_addr, cliente_len, id_cidade, id_equipe);
}

void processar_telemetria(int sock, struct sockaddr *cliente_addr, socklen_t cliente_len,payload_telemetria_t *payload) {
    printf("\n[TELEMETRIA RECEBIDA]\n");
    printf("Total de cidades monitoradas: %d\n", payload->total);

    int cidades_alerta[MAX_CIDADES];
    int num_alertas = identificar_alertas(payload, cidades_alerta);

    enviar_ack(sock, cliente_addr, cliente_len, ACK_TELEMETRIA);

    for (int i = 0; i < num_alertas; i++) {
        despachar_drone_para_alerta(sock, cliente_addr, cliente_len, cidades_alerta[i]);
    }
}

void processar_conclusao(int sock, struct sockaddr *cliente_addr, socklen_t cliente_len,payload_conclusao_t *payload) {
    printf("\n[MISSAO CONCLUIDA]\n");
    printf("Cidade atendida: %s (ID=%d)\n",grafo.vertices[payload->id_cidade].nome, payload->id_cidade);
    printf("Equipe: %s (ID=%d)\n",grafo.vertices[payload->id_equipe].nome, payload->id_equipe);

    equipes_livres[payload->id_equipe] = 1;
    printf("-> Equipe %s liberada para novas missões\n",grafo.vertices[payload->id_equipe].nome);

    enviar_ack(sock, cliente_addr, cliente_len, ACK_CONCLUSAO);
}

int criar_e_configurar_socket(int familia, void *addr, size_t addr_len) {
    int sock = socket(familia, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Erro ao criar socket");
        return -1;
    }

    if (bind(sock, (struct sockaddr *)addr, addr_len) < 0) {
        perror("Erro ao fazer bind");
        close(sock);
        return -1;
    }

    return sock;
}


int main(int argc, char *argv[]) {
    if (argc != 2 || (strcmp(argv[1], "v4") != 0 && strcmp(argv[1], "v6") != 0)) {
        fprintf(stderr, "Uso: %s <v4|v6>\n", argv[0]);
        return 1;
    }

    modo_ipv6 = (strcmp(argv[1], "v6") == 0);

    // Registrar signal handler para shutdown
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("Carregando grafo da Amazônia Legal...\n");
    fflush(stdout);
    if (carregar_grafo_de_arquivo(&grafo, "grafo_amazonia_legal.txt") < 0) {
        fprintf(stderr, "Erro ao carregar grafo\n");
        return 1;
    }

    // Inicializar equipes livres
    int idx = 0;
    while (idx < grafo.num_vertices) {
        equipes_livres[idx] = 1;
        idx++;
    }

    printf("Grafo carregado: %d vértices, %d arestas\n",grafo.num_vertices, grafo.num_arestas);
    fflush(stdout);

    sock_global = modo_ipv6 ? criar_socket_servidor_ipv6(PORTA_SERVIDOR): criar_socket_servidor_ipv4(PORTA_SERVIDOR);
    if (sock_global < 0) {
        liberar_grafo(&grafo);
        return 1;
    }

    printf("Servidor escutando na porta %d...\n\n", PORTA_SERVIDOR);
    fflush(stdout);

    char buffer[BUFFER_SIZE];
    struct sockaddr_storage cliente_addr;
    socklen_t cliente_len;

    while (servidor_ativo) {
        cliente_len = sizeof(cliente_addr);
        ssize_t recv_len = recvfrom(sock_global, buffer, BUFFER_SIZE, 0,(struct sockaddr *)&cliente_addr, &cliente_len);

        if (recv_len < (ssize_t)sizeof(header_t)) {
            continue;
        }

        header_t *header = (header_t *)buffer;
        void *payload = buffer + sizeof(header_t);

        // Validar tamanho total da mensagem
        size_t tamanho_esperado = sizeof(header_t) + header->tamanho;
        if ((size_t)recv_len < tamanho_esperado) {
            fprintf(stderr, "Mensagem incompleta: recebido %zd bytes, esperado %zu\n",recv_len, tamanho_esperado);
            continue;
        }

        // Validar tamanho do payload de acordo com o tipo de mensagem
        switch (header->tipo) {
            case MSG_TELEMETRIA:
                if (header->tamanho != sizeof(payload_telemetria_t)) {
                    fprintf(stderr, "Payload MSG_TELEMETRIA inválido: %u bytes (esperado %zu)\n",header->tamanho, sizeof(payload_telemetria_t));
                    continue;
                }
                processar_telemetria(sock_global, (struct sockaddr *)&cliente_addr,cliente_len, (payload_telemetria_t *)payload);
                break;

            case MSG_ACK:
                if (header->tamanho != sizeof(payload_ack_t)) {
                    fprintf(stderr, "Payload MSG_ACK inválido: %u bytes (esperado %zu)\n",
                            header->tamanho, sizeof(payload_ack_t));
                    continue;
                }
                {
                    payload_ack_t *ack = (payload_ack_t *)payload;
                    if (ack->status == ACK_EQUIPE_DRONE) {
                        printf("\n[ACK RECEBIDO]\n");
                        printf("Cliente confirmou recebimento de ordem de drone\n");
                    }
                }
                break;

            case MSG_CONCLUSAO:
                if (header->tamanho != sizeof(payload_conclusao_t)) {
                    fprintf(stderr, "Payload MSG_CONCLUSAO inválido: %u bytes (esperado %zu)\n",header->tamanho, sizeof(payload_conclusao_t));
                    continue;
                }
                processar_conclusao(sock_global, (struct sockaddr *)&cliente_addr,cliente_len, (payload_conclusao_t *)payload);
                break;

            default:
                fprintf(stderr, "Tipo de mensagem desconhecido: %u\n", header->tipo);
                break;
        }
    }

    // Cleanup ao sair do loop
    close(sock_global);
    liberar_grafo(&grafo);
    return 0;
}
