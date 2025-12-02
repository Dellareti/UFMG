#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "core/protocol.h"


static int attempt_connection(struct addrinfo* info) {
    int socket_fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (socket_fd < 0) return -1;

    if (connect(socket_fd, info->ai_addr, info->ai_addrlen) < 0) {
        close(socket_fd);
        return -1;
    }

    return socket_fd;
}

// TCP com servidor
int connect_to_server(const char* host, int port) {
    struct addrinfo hints, *results, *ptr;
    char service[8];
    int socket_fd = -1;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    snprintf(service, sizeof(service), "%d", port);

    if (getaddrinfo(host, service, &hints, &results) != 0) {
        fprintf(stderr, "Erro ao resolver endereço.\n");
        return -1;
    }

    for (ptr = results; ptr && socket_fd < 0; ptr = ptr->ai_next) {
        socket_fd = attempt_connection(ptr);
    }

    freeaddrinfo(results);

    if (socket_fd < 0) {
        fprintf(stderr, "Não foi possível estabelecer conexão.\n");
    }

    return socket_fd;
}

int send_message(int socket_fd, BattleMessage* data) {
    size_t total = sizeof(BattleMessage);
    ssize_t sent = send(socket_fd, data, total, 0);
    return (sent == (ssize_t)total) ? 0 : -1;
}

int receive_message(int socket_fd, BattleMessage* buffer) {
    size_t expected = sizeof(BattleMessage);
    ssize_t received = recv(socket_fd, buffer, expected, 0);

    if (received == 0) {
        printf("Conexão finalizada pelo servidor.\n");
        return -1;
    }

    if (received != (ssize_t)expected) {
        perror("Falha na recepção");
        return -1;
    }

    return 0;
}

// remove caracteres restantes no buffer de entrada
static void flush_stdin_buffer() {
    int character;
    while ((character = getchar()) != '\n' && character != EOF);
}

static int read_integer_from_stdin() {
    int num = -1;
    if (scanf("%d", &num) != 1) {
        flush_stdin_buffer();
        return -1;
    }
    return num;
}

int read_action() {
    return read_integer_from_stdin();
}

static int display_welcome_screen(int socket_fd) {
    BattleMessage initial;

    if (receive_message(socket_fd, &initial) < 0) return -1;

    if (initial.type == MSG_INIT) {
        printf("%s\n", initial.message);
    }

    return 0;
}


static int prompt_for_action(const BattleMessage* menu) {
    int selection;

    printf("%s\n", menu->message);

    while (1) {
        printf("> ");
        fflush(stdout);

        selection = read_action();

        if (is_valid_action(selection)) {
            return selection;
        }

        printf("Entrada inválida! Use valores 0-4.\n");
    }
}

// envia escolha do jogador para servidor
static int transmit_player_choice(int socket_fd, int action) {
    BattleMessage response;
    memset(&response, 0, sizeof(BattleMessage));
    response.type = MSG_ACTION_RES;
    response.client_action = action;
    return send_message(socket_fd, &response);
}

// envia ação do jogador para servidor
static int send_player_action(int socket_fd, const BattleMessage* prompt) {
    int selected = prompt_for_action(prompt);
    return transmit_player_choice(socket_fd, selected);
}


static int process_game_turn(int socket_fd, BattleMessage* packet) {
    if (send_player_action(socket_fd, packet) < 0) {
        return -1;
    }

    if (receive_message(socket_fd, packet) < 0) {
        return -1;
    }

    printf("%s\n", packet->message);


    return (packet->type == MSG_GAME_OVER) ? 1 : 0;
}

void play_game(int socket_fd) {
    BattleMessage packet;
    int running = 1;

    if (display_welcome_screen(socket_fd) < 0) {
        return;
    }

    // Loop dos turnos
    while (running) {

        if (receive_message(socket_fd, &packet) < 0) {
            break;
        }

        if (packet.type == MSG_INVENTORY) {
            printf("%s\n", packet.message);
            continue;
        }

        if (packet.type == MSG_ESCAPE) {
            printf("%s\n", packet.message);
            break;
        }

        // fim de jogo normal
        if (packet.type == MSG_GAME_OVER) {
            printf("%s\n", packet.message);
            break;
        }

        if (packet.type == MSG_ACTION_REQ) {
            int result = process_game_turn(socket_fd, &packet);
            if (result != 0) {
                running = 0;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <host> <porta>\n", argv[0]);
        fprintf(stderr, "Exemplo IPv4: %s 127.0.0.1 5001\n", argv[0]);
        fprintf(stderr, "Exemplo IPv6: %s ::1 5001\n", argv[0]);
        return 1;
    }

    const char* target_host = argv[1];
    int target_port = atoi(argv[2]);

    if (target_port < 1 || target_port > 65535) {
        fprintf(stderr, "Número de porta inválido (1-65535).\n");
        return 1;
    }

    printf("Iniciando conexão com %s:%d...\n", target_host, target_port);

    int network_fd = connect_to_server(target_host, target_port);
    
    if (network_fd < 0) {
        return 1;
    }

    printf("Conectado com sucesso!\n\n");

    play_game(network_fd);
    close(network_fd);
    
    return 0;
}
