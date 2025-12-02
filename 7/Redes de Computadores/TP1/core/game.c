#include <string.h>
#include <stdio.h>
#include "game.h"


// Tabela para resultados de combate
// Valores especiais usados apenas internamente na tabela (apenas servidor):
// -1 = wildcard (casa com qualquer ação 0-3 exceto Hyper Jump 4)
// -2 = sentinela (marca fim da tabela)
typedef struct {
    int client_action;    // Ação do cliente 
    int server_action;    // Ação do servidor: 1,2,3,4 ou -1,-2
    int client_damage;    // HP que o cliente perde neste turno
    int server_damage;    // HP que o servidor perde neste turno
    int game_ends;        // 1 = partida termina, 0 = continua jogando
    int client_escapes;   // 1 = cliente fugiu, 0 = permanece em combate
    int server_escapes;   // 1 = servidor fugiu, 0 = permanece em combate
    const char* message;  // Texto do resultado
} CombatRule;

// Todos os resultados possíveis
static const CombatRule COMBAT_TABLE[] = {
    // Fugas 
    {4, 4, 0, 0, 1, 1, 1, "Ambos fugiram para o hiperespaço!"},           
    {4, -1, 0, 0, 1, 1, 0, "Você escapou para o hiperespaço."},           
    {-1, 4, 0, 0, 1, 0, 1, "O inimigo fugiu para o hiperespaço!"},

    // Escudos bloqueando lasers
    {2, 0, 0, 0, 0, 0, 0, "Ataque inimigo bloqueado!"},
    {0, 2, 0, 0, 0, 0, 0, "Seu ataque foi bloqueado pelos escudos inimigos!"},

    // Escudos bloqueando torpedos
    {2, 1, 0, 0, 0, 0, 0, "Ataque inimigo bloqueado!"},
    {1, 2, 0, 0, 0, 0, 0, "Seu ataque foi bloqueado pelos escudos inimigos!"},

    // Camuflagem desvia torpedos
    {3, 1, 0, 0, 0, 0, 0, "Ataque inimigo falhou!"},
    {1, 3, 0, 0, 0, 0, 0, "Seu torpedo falhou contra o sistema de camuflagem!"},

    // Laser penetra camuflagem
    {3, 0, 20, 0, 0, 0, 0, "Você recebeu 20 de dano."},
    {0, 3, 0, 20, 0, 0, 0, "Seu laser penetrou a camuflagem! Inimigo perdeu 20 HP."},

    // Torpedo > Laser
    {1, 0, 0, 20, 0, 0, 0, "Seu torpedo destruiu o laser inimigo! Inimigo perdeu 20 HP."},
    {0, 1, 20, 0, 0, 0, 0, "Você recebeu 20 de dano."},

    // Ataques mútuos
    {0, 0, 20, 20, 0, 0, 0, "Ambos receberam 20 de dano."},
    {1, 1, 20, 20, 0, 0, 0, "Ambos receberam 20 de dano."},

    // Defesas mútuas
    {2, 2, 0, 0, 0, 0, 0, "Ambos se defenderam."},
    {3, 3, 0, 0, 0, 0, 0, "Ambos se camuflaram."},
    {2, 3, 0, 0, 0, 0, 0, "Nenhum dano causado."},
    {3, 2, 0, 0, 0, 0, 0, "Nenhum dano causado."},

    // Sentinela final
    {-2, -2, 0, 0, 0, 0, 0, "Nenhum efeito."}
};

static inline int is_retreat(int move) {
    return (move == ACTION_HYPER_JUMP);
}

// Busca exata do resultado na tabela
static const CombatRule* lookup_outcome(int a, int b) {

    for (int i = 0; COMBAT_TABLE[i].client_action != -2; i++) {
        if ((COMBAT_TABLE[i].client_action == a && COMBAT_TABLE[i].server_action == b) ||
            (COMBAT_TABLE[i].client_action == -1 && COMBAT_TABLE[i].server_action == b && !is_retreat(a)) ||
            (COMBAT_TABLE[i].client_action == a && COMBAT_TABLE[i].server_action == -1 && !is_retreat(b))) {
            return &COMBAT_TABLE[i];
        }
    }

    for (int i = 0; COMBAT_TABLE[i].client_action != -2; i++) {
        if (COMBAT_TABLE[i].client_action == -2) return &COMBAT_TABLE[i];
    }

    return &COMBAT_TABLE[0];
}


TurnResult resolve_combat(int client_action, int server_action) {
    TurnResult outcome;
    memset(&outcome, 0, sizeof(TurnResult));

    const CombatRule* rule = lookup_outcome(client_action, server_action);

    outcome.client_damage = rule->client_damage;
    outcome.server_damage = rule->server_damage;
    outcome.game_over = rule->game_ends;
    outcome.client_escaped = rule->client_escapes;
    outcome.server_escaped = rule->server_escapes;
    strncpy(outcome.result_message, rule->message, MSG_SIZE - 1);

    return outcome;
}
