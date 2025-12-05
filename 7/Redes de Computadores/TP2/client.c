#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include "common.h"
#include "rede.h"

 // Variáveis globais
cidade_t cidades[MAX_CIDADES];
int num_cidades = 0;

int sock_global = -1;
struct sockaddr_storage servidor_addr;
socklen_t servidor_len;

// Sincronização entre threads 
pthread_mutex_t mutex_dados = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_missao = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_missao = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_conclusao = PTHREAD_COND_INITIALIZER;

// Sincronização de ACKs (Thread 3 -> Thread 2) 
pthread_mutex_t mutex_ack = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_ack = PTHREAD_COND_INITIALIZER;
int ack_recebido = 0;
int tipo_ack_recebido = -1;

typedef struct {
    int ativa;
    int id_cidade;
    int id_equipe;
    int thread4_terminou;
} missao_t;

missao_t missao_atual = {0, 0, 0, 0};

volatile int programa_ativo = 1;

// Sleep que verifica flag a cada segundo
void sleep_interruptivel(int segundos) {
    for (int i = 0; i < segundos && programa_ativo; i++) {
        sleep(1);
    }
}

int parsear_vertice(char *buffer, int *id, char *nome, int *tipo) {
    buffer[strcspn(buffer, "\r\n")] = 0;

    if (strlen(buffer) == 0) {
        return -1;
    }

    char *token = strtok(buffer, " ");
    if (!token) return -1;
    *id = atoi(token);

    char temp_nome[MAX_NOME_CIDADE] = "";
    char *last_token = NULL;

    while ((token = strtok(NULL, " ")) != NULL) {
        if (last_token) {
            if (strlen(temp_nome) > 0) strcat(temp_nome, " ");
            strcat(temp_nome, last_token);
        }
        last_token = token;
    }

    if (!last_token) return -1;

    *tipo = atoi(last_token);
    strncpy(nome, temp_nome, MAX_NOME_CIDADE - 1);
    nome[MAX_NOME_CIDADE - 1] = '\0';
    return 0;
}

void carregar_cidades(const char* caminho_arquivo) {
    FILE* arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo do grafo");
        exit(1);
    }

    int num_vertices, num_arestas;
    int resultado_leitura = fscanf(arquivo, "%d %d", &num_vertices, &num_arestas);
    if (resultado_leitura != 2) {
        fprintf(stderr, "Erro ao ler dimensões do grafo\n");
        fclose(arquivo);
        exit(1);
    }

    fgetc(arquivo);
    num_cidades = num_vertices;

    int vertices_lidos = 0;
    while (vertices_lidos < num_vertices) {
        char buffer[TAMANHO_BUFFER_LINHA];
        char* leitura_ok = fgets(buffer, sizeof(buffer), arquivo);

        if (leitura_ok == NULL) {
            fprintf(stderr, "Erro ao ler vértice\n");
            fclose(arquivo);
            exit(1);
        }

        int id, tipo;
        char nome[MAX_NOME_CIDADE];

        int parse_ok = parsear_vertice(buffer, &id, nome, &tipo);
        if (parse_ok >= 0) {
            cidades[id].id = id;
            cidades[id].tipo = tipo;
            cidades[id].status = STATUS_OK;
            strcpy(cidades[id].nome, nome);
            vertices_lidos++;
        }
    }

    fclose(arquivo);
}

// Thread 2 aguarda notificação da Thread 3 sobre ACK recebido
int aguardar_ack(int tipo_ack_esperado, int timeout_ms) {
    struct timespec ts;
    struct timeval agora;

    gettimeofday(&agora, NULL);

    // Converte timeout para timespec
    int segundos_extra = timeout_ms / 1000;
    int milissegundos_resto = timeout_ms % 1000;
    long nanossegundos_extras = milissegundos_resto * 1000000;

    ts.tv_sec = agora.tv_sec + segundos_extra;
    ts.tv_nsec = (agora.tv_usec * 1000) + nanossegundos_extras;

    long um_bilhao = 1000000000;
    if (ts.tv_nsec >= um_bilhao) {
        ts.tv_nsec -= um_bilhao;
        ts.tv_sec++;
    }

    pthread_mutex_lock(&mutex_ack);

    int continuar_aguardando = 1;
    while (continuar_aguardando) {
        if (ack_recebido || !programa_ativo) {
            break;
        }

        int resultado_espera = pthread_cond_timedwait(&cond_ack, &mutex_ack, &ts);

        if (resultado_espera == ETIMEDOUT) {
            pthread_mutex_unlock(&mutex_ack);
            return 0;
        }

        if (resultado_espera != 0) {
            pthread_mutex_unlock(&mutex_ack);
            return 0;
        }
    }

    int tipos_iguais = (tipo_ack_recebido == tipo_ack_esperado);
    int sucesso = (ack_recebido && tipos_iguais) ? 1 : 0;

    ack_recebido = 0;
    tipo_ack_recebido = -1;

    pthread_mutex_unlock(&mutex_ack);

    return sucesso;
}

void enviar_ack(int tipo_ack) {
    header_t header;
    header.tipo = MSG_ACK;
    header.tamanho = sizeof(payload_ack_t);

    payload_ack_t payload;
    payload.status = tipo_ack;

    char buffer[BUFFER_SIZE];
    memcpy(buffer, &header, sizeof(header_t));
    memcpy(buffer + sizeof(header_t), &payload, sizeof(payload_ack_t));

    sendto(sock_global, buffer, sizeof(header_t) + sizeof(payload_ack_t), 0,(struct sockaddr*)&servidor_addr, servidor_len);

    printf("-> ACK enviado ao servidor\n");
}

void* thread_monitoramento(void* arg) {
    (void)arg;

    int continuar = 1;
    while (continuar) {
        if (!programa_ativo) {
            continuar = 0;
            break;
        }

        pthread_mutex_lock(&mutex_dados);

        int cidade_idx = 0;
        while (cidade_idx < num_cidades) {
            int sorteio = rand();
            int chance = sorteio % 100;
            int alerta = (chance < PROBABILIDADE_ALERTA) ? 1 : 0;
            cidades[cidade_idx].status = alerta ? STATUS_ALERTA : STATUS_OK;
            cidade_idx++;
        }

        pthread_mutex_unlock(&mutex_dados);
        sleep_interruptivel(INTERVALO_TELEMETRIA);
    }

    return NULL;
}

void preparar_payload_telemetria(payload_telemetria_t *payload) {
    payload->total = num_cidades;

    pthread_mutex_lock(&mutex_dados);
    for (int i = 0; i < num_cidades; i++) {
        payload->dados[i].id_cidade = cidades[i].id;
        payload->dados[i].status = cidades[i].status;
    }
    pthread_mutex_unlock(&mutex_dados);
}

void exibir_telemetria(payload_telemetria_t *payload) {
    printf("\n[ENVIANDO TELEMETRIA]\n");
    printf("Total de cidades: %d\n", num_cidades);

    for (int i = 0; i < num_cidades; i++) {
        if (payload->dados[i].status == STATUS_ALERTA) {
            printf("ALERTA: %s (ID=%d)\n",
                   cidades[payload->dados[i].id_cidade].nome,
                   payload->dados[i].id_cidade);
        }
    }
}

int enviar_com_retry(void *mensagem, size_t tamanho, int tipo_ack_esperado) {
    for (int tentativa = 1; tentativa <= MAX_RETRIES; tentativa++) {
        printf("-> Telemetria enviada (tentativa %d/%d)\n", tentativa, MAX_RETRIES);

        sendto(sock_global, mensagem, tamanho, 0,
               (struct sockaddr*)&servidor_addr, servidor_len);

        if (aguardar_ack(tipo_ack_esperado, TIMEOUT_ACK_MS)) {
            printf(". ACK recebido do servidor\n");
            return 1;
        } else if (tentativa < MAX_RETRIES) {
            printf(". Timeout, reenviando...\n");
        }
    }

    printf(". Falha após %d tentativas, aguardando próximo ciclo\n", MAX_RETRIES);
    return 0;
}

void* thread_telemetria(void* arg) {
    (void)arg;
    sleep_interruptivel(2);

    while (programa_ativo) {
        header_t header;
        header.tipo = MSG_TELEMETRIA;
        header.tamanho = sizeof(payload_telemetria_t);

        payload_telemetria_t payload;
        preparar_payload_telemetria(&payload);
        exibir_telemetria(&payload);

        char buffer[BUFFER_SIZE];
        memcpy(buffer, &header, sizeof(header_t));
        memcpy(buffer + sizeof(header_t), &payload, sizeof(payload_telemetria_t));

        enviar_com_retry(buffer, sizeof(header_t) + sizeof(payload_telemetria_t), ACK_TELEMETRIA);

        fflush(stdout);
        sleep_interruptivel(INTERVALO_TELEMETRIA);
    }

    return NULL;
}

// Thread 3: Notifica Thread 2 que ACK foi recebido
void processar_ack_recebido(payload_ack_t* ack) {
    pthread_mutex_lock(&mutex_ack);
    ack_recebido = 1;
    tipo_ack_recebido = ack->status;
    pthread_cond_signal(&cond_ack);  // Acorda Thread 2
    pthread_mutex_unlock(&mutex_ack);
}

void enviar_conclusao_missao(int id_cidade, int id_equipe) {
    header_t header;
    header.tipo = MSG_CONCLUSAO;
    header.tamanho = sizeof(payload_conclusao_t);

    payload_conclusao_t payload;
    payload.id_cidade = id_cidade;
    payload.id_equipe = id_equipe;

    char buffer[BUFFER_SIZE];
    memcpy(buffer, &header, sizeof(header_t));
    memcpy(buffer + sizeof(header_t), &payload, sizeof(payload_conclusao_t));

    sendto(sock_global, buffer, sizeof(header_t) + sizeof(payload_conclusao_t), 0,(struct sockaddr*)&servidor_addr, servidor_len);

    printf("-> Conclusao enviada ao servidor\n");
    fflush(stdout);

    aguardar_ack(ACK_CONCLUSAO, TIMEOUT_ACK_MS);
}

void processar_ordem_drone(payload_equipe_drone_t* payload) {
    printf("\n[ORDEM DE DRONE RECEBIDA]\n");
    printf("Cidade: %s (ID=%d)\n",cidades[payload->id_cidade].nome, payload->id_cidade);
    printf("Equipe: %s (ID=%d)\n",cidades[payload->id_equipe].nome, payload->id_equipe);
    fflush(stdout);

    enviar_ack(ACK_EQUIPE_DRONE);

    pthread_mutex_lock(&mutex_missao);

    if (missao_atual.ativa) {
        printf("Ja existe missao ativa, ordem ignorada\n");
        fflush(stdout);
        pthread_mutex_unlock(&mutex_missao);
        return;
    }

    missao_atual.ativa = 1;
    missao_atual.id_cidade = payload->id_cidade;
    missao_atual.id_equipe = payload->id_equipe;
    missao_atual.thread4_terminou = 0;

    printf("-> Missao registrada para execucao\n");
    fflush(stdout);

    pthread_cond_signal(&cond_missao);

    while (!missao_atual.thread4_terminou) {
        pthread_cond_wait(&cond_conclusao, &mutex_missao);
    }

    pthread_mutex_unlock(&mutex_missao);

    enviar_conclusao_missao(payload->id_cidade, payload->id_equipe);

    pthread_mutex_lock(&mutex_missao);
    missao_atual.ativa = 0;
    pthread_mutex_unlock(&mutex_missao);
}

// Thread 3: Multiplexador - recebe TODAS as mensagens do servidor 
void* thread_recepcao_drones(void* arg) {
    (void)arg;
    char buffer[BUFFER_SIZE];

    while (programa_ativo) {
        // Select com timeout para verificar programa_ativo
        fd_set readfds;
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        FD_ZERO(&readfds);
        FD_SET(sock_global, &readfds);

        int ret = select(sock_global + 1, &readfds, NULL, NULL, &tv);

        if (ret <= 0) {
            continue;
        }

        struct sockaddr_storage from_addr;
        socklen_t from_len = sizeof(from_addr);

        int n = recvfrom(sock_global, buffer, BUFFER_SIZE, 0,(struct sockaddr*)&from_addr, &from_len);

        if (n < 0) {
            break;
        }
        if (n < (int)sizeof(header_t)) {
            continue;
        }

        header_t* header = (header_t*)buffer;
        void* payload_ptr = buffer + sizeof(header_t);

        if (header->tipo == MSG_ACK) {
            processar_ack_recebido((payload_ack_t*)payload_ptr);
        } else if (header->tipo == MSG_EQUIPE_DRONE) {
            processar_ordem_drone((payload_equipe_drone_t*)payload_ptr);
        }
    }

    return NULL;
}

void* thread_simulacao_drones(void* arg) {
    (void)arg;
    while (programa_ativo) {
        pthread_mutex_lock(&mutex_missao);

        while (!missao_atual.ativa || missao_atual.thread4_terminou) {
            pthread_cond_wait(&cond_missao, &mutex_missao);
            if (!programa_ativo) {
                pthread_mutex_unlock(&mutex_missao);
                return NULL;
            }
        }

        int id_cidade = missao_atual.id_cidade;
        int id_equipe = missao_atual.id_equipe;

        pthread_mutex_unlock(&mutex_missao);

        int tempo_missao = (rand() % TEMPO_MAX_MISSAO) + 1;

        printf("\n[MISSAO EM ANDAMENTO]\n");
        printf("Equipe %s atuando em %s\n",cidades[id_equipe].nome, cidades[id_cidade].nome);
        printf(". Tempo estimado: %d segundos\n", tempo_missao);
        fflush(stdout);

        sleep_interruptivel(tempo_missao);

        printf(". Missao concluida!\n");
        fflush(stdout);

        pthread_mutex_lock(&mutex_missao);
        missao_atual.thread4_terminou = 1;
        pthread_cond_signal(&cond_conclusao);
        pthread_mutex_unlock(&mutex_missao);
    }

    return NULL;
}

void signal_handler(int sig) {
    (void)sig;
    programa_ativo = 0;

    pthread_cond_broadcast(&cond_missao);
    pthread_cond_broadcast(&cond_conclusao);
    pthread_cond_broadcast(&cond_ack);

    if (sock_global >= 0) {
        shutdown(sock_global, SHUT_RDWR);
        close(sock_global);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <v4|v6>\n", argv[0]);
        return 1;
    }

    signal(SIGINT, signal_handler);
    srand(time(NULL));
    carregar_cidades("grafo_amazonia_legal.txt");

    if (strcmp(argv[1], "v4") == 0) {
        sock_global = criar_socket_cliente_ipv4("127.0.0.1", PORTA_SERVIDOR,&servidor_addr, &servidor_len);
        printf("Conectado ao servidor 127.0.0.1:%d\n\n", PORTA_SERVIDOR);
        fflush(stdout);
    } else if (strcmp(argv[1], "v6") == 0) {
        sock_global = criar_socket_cliente_ipv6("::1", PORTA_SERVIDOR,&servidor_addr, &servidor_len);
        printf("Conectado ao servidor ::1:%d\n\n", PORTA_SERVIDOR);
        fflush(stdout);
    } else {
        fprintf(stderr, "Protocolo inválido. Use 'v4' ou 'v6'.\n");
        return 1;
    }

    if (sock_global < 0) {
        fprintf(stderr, "Falha ao criar socket\n");
        return 1;
    }

    pthread_t tid_monitoramento, tid_telemetria, tid_recepcao, tid_simulacao;

    printf("Iniciando threads...\n\n");
    fflush(stdout);

    pthread_create(&tid_monitoramento, NULL, thread_monitoramento, NULL);
    pthread_create(&tid_simulacao, NULL, thread_simulacao_drones, NULL);
    pthread_create(&tid_telemetria, NULL, thread_telemetria, NULL);
    pthread_create(&tid_recepcao, NULL, thread_recepcao_drones, NULL);

    printf("[Thread Monitoramento] Iniciada\n");
    printf("[Thread Simulacao Drones] Iniciada\n");
    printf("[Thread Telemetria] Iniciada\n");
    printf("[Thread Recepcao Drones] Iniciada\n");
    printf(". Todas as threads iniciadas com sucesso\n");
    printf("Pressione Ctrl+C para encerrar...\n\n");
    fflush(stdout);

    pthread_join(tid_monitoramento, NULL);
    pthread_join(tid_telemetria, NULL);
    pthread_join(tid_recepcao, NULL);
    pthread_join(tid_simulacao, NULL);

    if (sock_global >= 0) {
        close(sock_global);
    }

    return 0;
}
