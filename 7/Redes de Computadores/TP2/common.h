#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#define PORTA_SERVIDOR 8080
#define MAX_CIDADES 50
#define MAX_NOME_CIDADE 100
#define BUFFER_SIZE 4096
#define TAMANHO_BUFFER_LINHA 256
#define TIMEOUT_ACK_MS 5000
#define MAX_RETRIES 3
#define INTERVALO_TELEMETRIA 30
#define PROBABILIDADE_ALERTA 3
#define TEMPO_MAX_MISSAO 30

// Mensagens do protocolo UDP 
typedef enum {
    MSG_TELEMETRIA = 1,
    MSG_ACK = 2,
    MSG_EQUIPE_DRONE = 3,
    MSG_CONCLUSAO = 4
} tipo_mensagem_t;

typedef enum {
    ACK_TELEMETRIA = 0,
    ACK_EQUIPE_DRONE = 1,
    ACK_CONCLUSAO = 2
} tipo_ack_t;

typedef enum {
    STATUS_OK = 0,
    STATUS_ALERTA = 1
} status_cidade_t;

typedef enum {
    TIPO_REGIONAL = 0,
    TIPO_CAPITAL = 1
} tipo_cidade_t;

// Cabeçalho comum para compatibilidade de rede
typedef struct {
    uint16_t tipo;
    uint16_t tamanho;
} __attribute__((packed)) header_t;

typedef struct {
    int id_cidade;
    int status;
} __attribute__((packed)) telemetria_t;

typedef struct {
    int total;
    telemetria_t dados[MAX_CIDADES];
} __attribute__((packed)) payload_telemetria_t;

typedef struct {
    int status;
} __attribute__((packed)) payload_ack_t;

typedef struct {
    int id_cidade;
    int id_equipe;
} __attribute__((packed)) payload_equipe_drone_t;

typedef struct {
    int id_cidade;
    int id_equipe;
} __attribute__((packed)) payload_conclusao_t;

// Auxiliares para grafo 
typedef struct {
    int id;
    char nome[MAX_NOME_CIDADE];
    int tipo;
    int status;
} cidade_t;

// Nó da lista de adjacência 
typedef struct no_adj {
    int destino;
    int peso;
    struct no_adj* prox;
} no_adjacencia_t;

// Grafo da Amazônia Legal 
typedef struct {
    int num_vertices;
    int num_arestas;
    cidade_t cidades[MAX_CIDADES];
    no_adjacencia_t* adj[MAX_CIDADES];
} grafo_t;

#endif
