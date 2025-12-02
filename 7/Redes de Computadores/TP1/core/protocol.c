#include "protocol.h"
#include <string.h>
#include <stdio.h>

#define FALLBACK_LABEL "Unknown"
#define FALLBACK_DESC "fez algo desconhecido"

typedef struct {
    const char* label;
    const char* description;
    int code;
} CommandMetadata;

// Comandos disponíveis
static const CommandMetadata COMMAND_REGISTRY[] = {
    {"Laser Attack", "disparou um Laser", 0},
    {"Photon Torpedo", "disparou um Photon Torpedo", 1},
    {"Shields Up", "ativou os Escudos", 2},
    {"Cloaking", "ativou Cloaking", 3},
    {"Hyper Jump", "acionou o Hyper Jump", 4}
};

#define REGISTRY_SIZE (sizeof(COMMAND_REGISTRY) / sizeof(CommandMetadata))


static inline int check_bounds(int code) {
    return (code >= 0 && code < (int)REGISTRY_SIZE);
}

// Recupera metadados baseado no código
static inline const CommandMetadata* fetch_metadata(int code) {
    return check_bounds(code) ? &COMMAND_REGISTRY[code] : NULL;
}

const char* get_action_name(int action) {
    const CommandMetadata* meta = fetch_metadata(action);
    return meta ? meta->label : FALLBACK_LABEL;
}

// Pega descrição do comando
const char* get_action_verb(int action) {
    const CommandMetadata* meta = fetch_metadata(action);
    return meta ? meta->description : FALLBACK_DESC;
}

int is_valid_action(int action) {
    return check_bounds(action);
}
