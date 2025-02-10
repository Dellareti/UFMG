#pragma once

#include <stack>
#include <vector>

struct Campanha {
    const int seguidores;
    const int propostas;

    std::vector<int>* grafo;
    std::vector<int>* grafo_transposto;
    std::stack<int> pilha;
    bool* visitados;
    bool* visitados_transposto;
    int* componentes;
    int quantidade_componentes = 1;

    Campanha(int seguidores, int propostas);
    ~Campanha();
    void aloca_e_inicializa_estruturas();
    void adicionar_grafos(int origem, int destino);
    void dfs1(int origem);
    void dfs2(int origem);
    bool satisfaz(int const* a, int const* b);
};