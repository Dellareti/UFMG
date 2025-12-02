#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "core/protocol.h"
#include "core/game.h"

#define BACKLOG 1  // 1 cliente por vez

// opções de socket
static inline int setup_socket_options(int sockfd) {
    int reuse = 1;
    return setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
}


static int init_ipv6_socket(int port) {
    struct sockaddr_in6 addr;
    int sockfd = socket(AF_INET6, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("Erro ao criar socket IPv6");
        return -1;
    }

    if (setup_socket_options(sockfd) < 0) {
        perror("Erro no setsockopt");
        close(sockfd);
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    addr.sin6_addr = in6addr_any;
    addr.sin6_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Erro no bind IPv6");
        close(sockfd);
        return -1;
    }

    return sockfd;
}


static int init_ipv4_socket(int port) {
    struct sockaddr_in addr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("Erro ao criar socket IPv4");
        return -1;
    }

    if (setup_socket_options(sockfd) < 0) {
        perror("Erro no setsockopt");
        close(sockfd);
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Erro no bind IPv4");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int create_server_socket(const char* protocol, int port) {
    int sockfd;

    if (strcmp(protocol, "v6") == 0) {
        sockfd = init_ipv6_socket(port);
    } else if (strcmp(protocol, "v4") == 0) {
        sockfd = init_ipv4_socket(port);
    } else {
        fprintf(stderr, "Protocolo inválido. Use 'v4' ou 'v6'.\n");
        exit(1);
    }

    if (sockfd < 0) {
        exit(1);
    }

    // Socket em modo de escuta
    if (listen(sockfd, BACKLOG) < 0) {
        perror("Erro no listen");
        close(sockfd);
        exit(1);
    }

    return sockfd;
}

int send_message(int client_socket, BattleMessage* msg) {
    ssize_t result = send(client_socket, msg, sizeof(BattleMessage), 0);
    return (result < 0) ? -1 : 0;
}

int receive_message(int client_socket, BattleMessage* msg) {
    ssize_t bytes = recv(client_socket, msg, sizeof(BattleMessage), 0);

    if (bytes == 0) {
        printf("Cliente desconectou.\n");
        return -1;
    }

    if (bytes < 0) {
        perror("Erro ao receber mensagem");
        return -1;
    }

    return 0;
}

// Ação aleatória do servidor
static inline int get_random_action() {
    return rand() % 5;  // 0 a 4
}

int generate_server_action() {
    return get_random_action();
}

// Estado da partida
typedef struct {
    int client_health;
    int server_health;
    int client_torpedo_count;
    int client_shield_count;
    int round_num;
    int client_fled;
    int server_fled;
} BattleSession;

static void reset_battle_session(BattleSession* s) {
    s->client_health = INITIAL_HP;
    s->server_health = INITIAL_HP;
    s->client_torpedo_count = 0;
    s->client_shield_count = 0;
    s->round_num = 0;
    s->client_fled = 0;
    s->server_fled = 0;
}


static void transmit_welcome(int client_socket, BattleSession* session) {
    BattleMessage greeting;
    memset(&greeting, 0, sizeof(BattleMessage));
    greeting.type = MSG_INIT;
    greeting.client_hp = session->client_health;
    greeting.server_hp = session->server_health;
    strcpy(greeting.message, "Conectado ao servidor.\nSua nave: SS-42 Voyager (HP: 100)");
    send_message(client_socket, &greeting);
}


static void build_action_menu(BattleMessage* packet, BattleSession* s) {
    memset(packet, 0, sizeof(BattleMessage));
    packet->type = MSG_ACTION_REQ;
    packet->client_hp = s->client_health;
    packet->server_hp = s->server_health;

    strcpy(packet->message,
           "\nEscolha sua ação:\n"
           "0 - Laser Attack\n"
           "1 - Photon Torpedo\n"
           "2 - Shields Up\n"
           "3 - Cloaking\n"
           "4 - Hyper Jump");
}

static void update_action_counters(BattleSession* s, int action) {
    if (action == ACTION_TORPEDO) s->client_torpedo_count++;
    if (action == ACTION_SHIELDS) s->client_shield_count++;
}

static void apply_combat_damage(BattleSession* s, const TurnResult* outcome) {
    s->client_health -= outcome->client_damage;
    s->server_health -= outcome->server_damage;

    if (s->client_health < 0) s->client_health = 0;
    if (s->server_health < 0) s->server_health = 0;

    if (outcome->client_escaped) s->client_fled = 1;
    if (outcome->server_escaped) s->server_fled = 1;
}

void play_game(int client_socket) {
    BattleMessage packet;
    BattleSession session;

    reset_battle_session(&session);
    transmit_welcome(client_socket, &session);

    // Loop de rodadas
    while (session.client_health > 0 && session.server_health > 0) {
        session.round_num++;

        build_action_menu(&packet, &session);
        send_message(client_socket, &packet);

        // Escolha do jogador
        if (receive_message(client_socket, &packet) < 0) break;

        int player_action = packet.client_action;

        if (player_action < 0 || player_action > 4) {
            BattleMessage error;
            memset(&error, 0, sizeof(BattleMessage));
            error.type = MSG_ACTION_REQ;
            error.client_hp = session.client_health;
            error.server_hp = session.server_health;
            strcpy(error.message, "Erro: escolha inválida!\nPor favor selecione um valor entre 0 e 4.");
            send_message(client_socket, &error);
            session.round_num--;
            continue;
        }

        update_action_counters(&session, player_action);
        int server_action = generate_server_action();

        TurnResult result = resolve_combat(player_action, server_action);
        apply_combat_damage(&session, &result);

        char battle_report[MSG_SIZE * 2];
        snprintf(battle_report, sizeof(battle_report),
                 "Você %s!\nServidor %s!\nResultado: %s\nPlacar: Você %d x %d Inimigo",
                 get_action_verb(player_action),
                 get_action_verb(server_action),
                 result.result_message,
                 session.client_health,
                 session.server_health);
        battle_report[MSG_SIZE - 1] = '\0';

        // Envia resultado
        BattleMessage response;
        memset(&response, 0, sizeof(BattleMessage));
        response.type = MSG_BATTLE_RESULT;
        response.client_action = player_action;
        response.server_action = server_action;
        response.client_hp = session.client_health;
        response.server_hp = session.server_health;
        response.client_torpedoes = session.client_torpedo_count;
        response.client_shields = session.client_shield_count;
        strcpy(response.message, battle_report);
        send_message(client_socket, &response);

    
        if (result.game_over || session.client_health <= 0 || session.server_health <= 0) {
            break;
        }
    }

    // Envia inventário final
    BattleMessage inventory;
    memset(&inventory, 0, sizeof(BattleMessage));
    inventory.type = MSG_INVENTORY;
    inventory.client_hp = session.client_health;
    inventory.server_hp = session.server_health;
    inventory.client_torpedoes = session.client_torpedo_count;
    inventory.client_shields = session.client_shield_count;

    snprintf(inventory.message, MSG_SIZE,
             "\nFim de jogo!\nInventário final:\n"
             "- HP restante: %d\n"
             "- Torpedos usados: %d\n"
             "- Escudos usados: %d\n"
             "- Turnos jogados: %d",
             session.client_health,
             session.client_torpedo_count,
             session.client_shield_count,
             session.round_num);

    send_message(client_socket, &inventory);

    // Determina tipo e mensagem de término
    BattleMessage finale;
    memset(&finale, 0, sizeof(BattleMessage));
    finale.client_hp = session.client_health;
    finale.server_hp = session.server_health;
    finale.client_torpedoes = session.client_torpedo_count;
    finale.client_shields = session.client_shield_count;

    // Verifica fuga 
    if (session.client_fled || session.server_fled) {
        finale.type = MSG_ESCAPE;

        if (session.client_fled && session.server_fled) {
            strcpy(finale.message, "\nFuga mútua.\nObrigado por jogar!");
        } else if (session.client_fled) {
            strcpy(finale.message, "\nVocê escapou para o hiperespaço.\nObrigado por jogar!");
        } else {
            strcpy(finale.message, "\nO inimigo fugiu para o hiperespaço!\nVocê derrotou a frota inimiga!");
        }
    } else {
        // Fim de jogo normal
        finale.type = MSG_GAME_OVER;

        if (session.client_health <= 0) {
            strcpy(finale.message, "\nSua nave foi destruída!");
        } else if (session.server_health <= 0) {
            strcpy(finale.message, "\nVocê derrotou a frota inimiga!");
        } else {
            strcpy(finale.message, "\nFim de jogo!\nObrigado por jogar!");
        }
    }

    send_message(client_socket, &finale);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <v4|v6> <porta>\n", argv[0]);
        fprintf(stderr, "Exemplo: %s v4 5001\n", argv[0]);
        return 1;
    }

    const char* ip_version = argv[1];
    int listen_port = atoi(argv[2]);

    if (listen_port <= 0 || listen_port > 65535) {
        fprintf(stderr, "Porta inválida. Use um valor entre 1 e 65535.\n");
        return 1;
    }

    // Seed para gerador random
    srand(time(NULL));

    printf("Servidor StarFleet Protocol iniciado.\n");
    printf("Protocolo: %s\n", ip_version);
    printf("Porta: %d\n", listen_port);
    printf("Aguardando conexões...\n\n");

    int listening_socket = create_server_socket(ip_version, listen_port);

    // Loop aceita cliente
    for (;;) {
        struct sockaddr_storage client_address;
        socklen_t address_length = sizeof(client_address);

        int client_socket = accept(listening_socket, (struct sockaddr*)&client_address, &address_length);
        if (client_socket < 0) {
            perror("Erro no accept");
            continue;
        }

        printf("Cliente conectado!\n");

        play_game(client_socket);

        printf("Partida encerrada. Aguardando próximo cliente...\n\n");
        close(client_socket);
    }

    close(listening_socket);
    return 0;
}
