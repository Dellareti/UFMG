#include "resolvedor_caixeiro.hpp"

ResolvedorCaixeiro::ResolvedorCaixeiro(const std::vector<Aresta>& arestas, int n) {
    num_cidades = n;
    distancias = std::vector<std::vector<int>>(n, std::vector<int>(n));
    cidades = std::vector<std::string>();

    // Coleta todas as cidades únicas
    for (const Aresta& aresta : arestas) {
        bool cidade1_existe = false;
        bool cidade2_existe = false;
        
        for (const std::string& cidade : cidades) {
            if (cidade == aresta.cidade1) cidade1_existe = true;
            if (cidade == aresta.cidade2) cidade2_existe = true;
        }
        
        if (!cidade1_existe) cidades.push_back(aresta.cidade1);
        if (!cidade2_existe) cidades.push_back(aresta.cidade2);
    }

    // Inicializa a matriz de distâncias
    for (const Aresta& aresta : arestas) {
        int i = obter_indice_cidade(aresta.cidade1);
        int j = obter_indice_cidade(aresta.cidade2);
        distancias[i][j] = aresta.distancia;
        distancias[j][i] = aresta.distancia; // Grafo não direcionado
    }
}

// Retorna o índice de uma cidade no vetor de cidades, -1 se não encontrar
int ResolvedorCaixeiro::obter_indice_cidade(const std::string& cidade) {
    for (int i = 0; i < num_cidades; i++) {
        if (cidades[i] == cidade) return i;
    }
    return -1;
}

// Formata o caminho como string, opcionalmente incluindo a cidade inicial
std::string ResolvedorCaixeiro::obter_caminho_string(const std::vector<int>& caminho, bool incluir_primeiro) {
    std::string resultado;
    // Adiciona cidade inicial se solicitado
    if (incluir_primeiro) {
        resultado = cidades[0];
    }
    // Adiciona as demais cidades do caminho
    for (int vertice : caminho) {
        resultado += " " + cidades[vertice];
    }
   // Adiciona cidade inicial no final se solicitado
    if (incluir_primeiro) {
        resultado += " " + cidades[0];
    }
    
    return resultado;
}