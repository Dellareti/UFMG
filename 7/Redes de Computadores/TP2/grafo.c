#include "grafo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

void inicializar_grafo(estrutura_grafo_t* g, int num_vertices) {
    if (num_vertices > MAX_CIDADES) {
        fprintf(stderr, "Erro: grafo excede limite de cidades\n");
        exit(1);
    }

    g->num_vertices = num_vertices;
    g->num_arestas = 0;

    int i = 0;
    while (i < MAX_CIDADES) {
        g->adjacencias[i] = NULL;
        i++;
    }
}

static no_adjacencia_t* alocar_no_adjacencia(int destino, int peso) {
    no_adjacencia_t* no = malloc(sizeof(no_adjacencia_t));
    if (!no) {
        perror("Erro ao alocar nó de adjacência");
        exit(1);
    }
    no->destino = destino;
    no->peso = peso;
    no->prox = NULL;
    return no;
}

void inserir_aresta_bidirecional(estrutura_grafo_t* g, int origem, int destino, int peso) {
    if (origem < 0 || origem >= MAX_CIDADES || destino < 0 || destino >= MAX_CIDADES) {
        fprintf(stderr, "Erro: índices inválidos (%d, %d)\n", origem, destino);
        return;
    }

    no_adjacencia_t* no_ida = alocar_no_adjacencia(destino, peso);
    no_ida->prox = g->adjacencias[origem];
    g->adjacencias[origem] = no_ida;

    no_adjacencia_t* no_volta = alocar_no_adjacencia(origem, peso);
    no_volta->prox = g->adjacencias[destino];
    g->adjacencias[destino] = no_volta;

    g->num_arestas++;
}

void liberar_grafo(estrutura_grafo_t* g) {
    int i = 0;
    while (i < MAX_CIDADES) {
        no_adjacencia_t* atual = g->adjacencias[i];
        while (atual != NULL) {
            no_adjacencia_t* proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
        g->adjacencias[i] = NULL;
        i++;
    }
}

static int parsear_linha_vertice(char* linha, int* id, char* nome, int* tipo) {
    linha[strcspn(linha, "\r\n")] = 0;

    if (strlen(linha) == 0) {
        return -1;
    }

    char* token = strtok(linha, " ");
    if (!token) return -1;
    *id = atoi(token);

    char buffer_nome[MAX_NOME_CIDADE] = "";
    char* ultimo_token = NULL;
    size_t buffer_len = 0;

    while ((token = strtok(NULL, " ")) != NULL) {
        if (ultimo_token) {
            size_t token_len = strlen(ultimo_token);
            size_t espaco_necessario = buffer_len + token_len + (buffer_len > 0 ? 2 : 1);

            if (espaco_necessario < MAX_NOME_CIDADE) {
                if (buffer_len > 0) {
                    buffer_nome[buffer_len++] = ' ';
                }
                strncpy(buffer_nome + buffer_len, ultimo_token, MAX_NOME_CIDADE - buffer_len - 1);
                buffer_len += token_len;
                buffer_nome[buffer_len] = '\0';
            }
        }
        ultimo_token = token;
    }

    if (!ultimo_token) return -1;

    *tipo = atoi(ultimo_token);
    strncpy(nome, buffer_nome, MAX_NOME_CIDADE - 1);
    nome[MAX_NOME_CIDADE - 1] = '\0';
    return 0;
}

int carregar_grafo_de_arquivo(estrutura_grafo_t* g, const char* caminho) {
    FILE* arquivo = fopen(caminho, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo do grafo");
        return -1;
    }

    int num_vertices, num_arestas;
    int lidos = fscanf(arquivo, "%d %d", &num_vertices, &num_arestas);
    if (lidos != 2) {
        fclose(arquivo);
        return -1;
    }
    fgetc(arquivo);

    inicializar_grafo(g, num_vertices);

    int vertices_carregados = 0;
    while (vertices_carregados < num_vertices) {
        char linha[TAMANHO_BUFFER_LINHA];
        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            fclose(arquivo);
            return -1;
        }

        int id, tipo;
        char nome[MAX_NOME_CIDADE];

        if (parsear_linha_vertice(linha, &id, nome, &tipo) < 0) {
            continue;
        }

        // Validação de limites do ID
        if (id < 0 || id >= MAX_CIDADES) {
            fprintf(stderr, "Erro: ID de vértice inválido %d (max=%d)\n", id, MAX_CIDADES - 1);
            continue;
        }

        g->vertices[id].id = id;
        g->vertices[id].tipo = tipo;
        strcpy(g->vertices[id].nome, nome);
        g->vertices[id].status = STATUS_OK;

        vertices_carregados++;
    }

    int arestas_carregadas = 0;
    while (arestas_carregadas < num_arestas) {
        char linha[TAMANHO_BUFFER_LINHA];
        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            break;
        }

        linha[strcspn(linha, "\r\n")] = 0;
        if (strlen(linha) == 0) {
            continue;
        }

        int u, v, peso;
        if (sscanf(linha, "%d %d %d", &u, &v, &peso) == 3) {
            inserir_aresta_bidirecional(g, u, v, peso);
            arestas_carregadas++;
        }
    }

    fclose(arquivo);
    return 0;
}

// Caminho mínimo
void calcular_dijkstra(estrutura_grafo_t* g, int origem, int* distancias, int* visitados) {
    int v = 0;
    while (v < g->num_vertices) {
        distancias[v] = INT_MAX;
        visitados[v] = 0;
        v++;
    }
    distancias[origem] = 0;

    int vertices_processados = 0;
    while (vertices_processados < g->num_vertices) {
        int vertice_escolhido = -1;
        int menor_dist = INT_MAX;

        int candidato = 0;
        while (candidato < g->num_vertices) {
            int nao_visitado = !visitados[candidato];
            int tem_menor_dist = (distancias[candidato] < menor_dist);

            if (nao_visitado && tem_menor_dist) {
                menor_dist = distancias[candidato];
                vertice_escolhido = candidato;
            }

            candidato++;
        }

        if (vertice_escolhido == -1) {
            break;
        }

        visitados[vertice_escolhido] = 1;

        no_adjacencia_t* vizinho = g->adjacencias[vertice_escolhido];
        while (vizinho != NULL) {
            int v_dest = vizinho->destino;
            int peso_aresta = vizinho->peso;

            int v_nao_visitado = !visitados[v_dest];
            int origem_alcancavel = (distancias[vertice_escolhido] != INT_MAX);

            if (v_nao_visitado && origem_alcancavel) {
                // Verificar overflow antes de somar
                if (distancias[vertice_escolhido] > INT_MAX - peso_aresta) {
                    // Overflow iminente, skip esta aresta
                    vizinho = vizinho->prox;
                    continue;
                }

                int dist_candidata = distancias[vertice_escolhido] + peso_aresta;
                int eh_melhor = (dist_candidata < distancias[v_dest]);

                if (eh_melhor) {
                    distancias[v_dest] = dist_candidata;
                }
            }

            vizinho = vizinho->prox;
        }

        vertices_processados++;
    }
}

// Busca capital disponível mais próxima usando Dijkstra
int buscar_capital_livre(estrutura_grafo_t* g, int* equipes_disponiveis,int cidade_alerta, int* distancia_resultado) {
    int distancias[g->num_vertices];
    int visitados[g->num_vertices];

    calcular_dijkstra(g, cidade_alerta, distancias, visitados);

    int capital_escolhida = -1;
    int melhor_distancia = INT_MAX;

    int candidato = 0;
    while (candidato < g->num_vertices) {
        cidade_t* cidade = &g->vertices[candidato];

        int eh_capital = (cidade->tipo == TIPO_CAPITAL);
        int esta_disponivel = equipes_disponiveis[candidato];
        int foi_alcancada = (distancias[candidato] != INT_MAX);
        int eh_mais_proxima = (distancias[candidato] < melhor_distancia);

        if (eh_capital && esta_disponivel && foi_alcancada && eh_mais_proxima) {
            melhor_distancia = distancias[candidato];
            capital_escolhida = candidato;
        }

        candidato++;
    }

    if (distancia_resultado && capital_escolhida >= 0) {
        *distancia_resultado = melhor_distancia;
    }

    return capital_escolhida;
}
