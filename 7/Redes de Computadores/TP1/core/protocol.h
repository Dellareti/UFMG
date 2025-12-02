#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MSG_SIZE 256
#define INITIAL_HP 100
#define DAMAGE 20

typedef enum {
    MSG_INIT,           // Boas vindas
    MSG_ACTION_REQ,     // Solicitação de ação
    MSG_ACTION_RES,     // Cliente responde com ação escolhida
    MSG_BATTLE_RESULT,  // Resultado do turno
    MSG_INVENTORY,      // Atualização de inventário
    MSG_GAME_OVER,      // Fim de jogo
    MSG_ESCAPE          // Jogador fugiu
} MessageType;


typedef enum {
    ACTION_LASER = 0,      // Laser Attack
    ACTION_TORPEDO = 1,    // Photon Torpedo
    ACTION_SHIELDS = 2,    // Shields Up
    ACTION_CLOAKING = 3,   // Cloaking
    ACTION_HYPER_JUMP = 4  // Hyper Jump
} ActionType;

// Estrutura da mensagem
typedef struct {
    int type;               // Tipo da mensagem (MessageType)
    int client_action;      // Ação escolhida pelo cliente
    int server_action;      // Ação escolhida pelo servidor
    int client_hp;          // HP do cliente
    int server_hp;          // HP do servidor
    int client_torpedoes;   // Número de torpedos usados pelo cliente
    int client_shields;     // Número de escudos usados pelo cliente
    char message[MSG_SIZE]; // Mensagem textual
} BattleMessage;

const char* get_action_name(int action);
const char* get_action_verb(int action);
int is_valid_action(int action);

#endif
