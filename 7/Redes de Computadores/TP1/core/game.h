#ifndef GAME_H
#define GAME_H

#include "protocol.h"

// Armazena o resultado do turno
typedef struct {
    int client_damage;      // Dano recebido pelo cliente
    int server_damage;      // Dano recebido pelo servidor
    char result_message[MSG_SIZE]; // Mensagem resultado
    int game_over;          // 1 se o jogo terminou, 0 contrário
    int client_escaped;     // 1 se o cliente fugiu
    int server_escaped;     // 1 se o servidor fugiu
} TurnResult;


TurnResult resolve_combat(int client_action, int server_action);

#endif
