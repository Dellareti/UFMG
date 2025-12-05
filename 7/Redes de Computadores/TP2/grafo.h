#ifndef GRAFO_H
#define GRAFO_H

#include "common.h"

typedef struct {
    int num_vertices;
    int num_arestas;
    cidade_t vertices[MAX_CIDADES];
    no_adjacencia_t* adjacencias[MAX_CIDADES];
} estrutura_grafo_t;

void inicializar_grafo(estrutura_grafo_t* g, int num_vertices);
void inserir_aresta_bidirecional(estrutura_grafo_t* g, int origem, int destino, int peso);
void liberar_grafo(estrutura_grafo_t* g);
int carregar_grafo_de_arquivo(estrutura_grafo_t* g, const char* caminho);

void calcular_dijkstra(estrutura_grafo_t* g, int origem, int* distancias, int* visitados);

int buscar_capital_livre(estrutura_grafo_t* g, int* equipes_disponiveis,int cidade_alerta, int* distancia_resultado);

#endif
