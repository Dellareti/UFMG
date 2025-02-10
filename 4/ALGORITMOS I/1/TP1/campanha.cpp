#include <algorithm>
#include <campanha.h>

Campanha::Campanha(const int seguidores, const int propostas) : seguidores(seguidores), propostas(propostas) {
    aloca_e_inicializa_estruturas();
}

Campanha::~Campanha() {
    delete[] grafo;
    delete[] grafo_transposto;
    delete[] visitados;
    delete[] visitados_transposto;
    delete[] componentes;
}

void Campanha::aloca_e_inicializa_estruturas() {
    const int tam = 2 * propostas + 1;
    grafo = new std::vector<int>[tam];
    grafo_transposto = new std::vector<int>[tam];
    visitados = new bool[tam];
    std::fill(visitados, visitados + tam, false);
    visitados_transposto = new bool[tam];
    std::fill(visitados_transposto, visitados_transposto + tam, false);
    componentes = new int[tam];
    std::fill(componentes, componentes + tam, 0);
}

void Campanha::adicionar_grafos(const int origem, const int destino) {
    grafo[origem].push_back(destino);
    grafo_transposto[destino].push_back(origem); // invertendo a origem e destino do grafo transposto
}

void Campanha::dfs1(const int origem) { //kosaraju parte 1
    if (visitados[origem])
        return;
    visitados[origem] = true;
    for (auto const& vertice : grafo[origem]) {
        dfs1(vertice);
    }
    pilha.push(origem);
}

void Campanha::dfs2(const int origem) {// kosaraju parte 2
    if (visitados_transposto[origem])
        return;
    visitados_transposto[origem] = true;
    for (auto const& vertice : grafo_transposto[origem]) {
        dfs2(vertice);
    }
    componentes[origem] = quantidade_componentes;
}

bool Campanha::satisfaz(int const* a, int const* b) {
    const int n = propostas;
    const int m = seguidores * 2; // pois cada seguidor tem duas condições, uma contra e uma a favor
    // >0 = a favor, <0 = contra
    // 0 = não se importa, mas não estarão presentes em nenhum array, pois as variáveis foram duplicadas quando algum
    // seguidor se absteve

    for (int i = 0; i < m; i++) {
        if (a[i] > 0 && b[i] > 0) { // a favor de ambas
            adicionar_grafos(a[i] + n, b[i]);
            adicionar_grafos(b[i] + n, a[i]);
        } else if (a[i] > 0 && b[i] < 0) { // a favor apenas de a
            adicionar_grafos(a[i] + n, n - b[i]);
            adicionar_grafos(-b[i], a[i]);
        } else if (a[i] < 0 && b[i] > 0) { // a favor apenas de b
            adicionar_grafos(-a[i], b[i]);
            adicionar_grafos(b[i] + n, n - a[i]);
        } else { // contra ambas
            adicionar_grafos(-a[i], n - b[i]);
            adicionar_grafos(-b[i], n - a[i]);
        }
    }

    for (int i = 1; i <= n * 2; i++) {
        if (!visitados[i]) {
            dfs1(i);
        }
    }

    while (!pilha.empty()) {
        const int v = pilha.top();
        pilha.pop();
        if (!visitados_transposto[v]) {
            dfs2(v);
            quantidade_componentes++;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (componentes[i] == componentes[i + n]) {
            return false;
        }
    }
    return true;
}