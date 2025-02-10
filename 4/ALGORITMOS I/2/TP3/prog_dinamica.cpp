#include "resolvedor_caixeiro.hpp"

int ResolvedorDinamico::resolver_programacao_dinamica(int pos, int mascara, std::vector<std::vector<int>>& memo) {
    // Se visitou todas as cidades, retorna à origem
    if (mascara == ((1 << num_cidades) - 1)) {
        return distancias[pos][0];
    }
    
    // Se já calculou este estado
    if (memo[pos][mascara] != -1) {
        return memo[pos][mascara];
    }
    
    int custo_minimo = std::numeric_limits<int>::max();
    
    // Como o grafo é completo, podemos tentar visitar qualquer cidade não visitada
    for (int prox = 0; prox < num_cidades; prox++) {
        if (!(mascara & (1 << prox))) {
            int novo_custo = distancias[pos][prox] + resolver_programacao_dinamica(prox, mascara | (1 << prox), memo);
            if (novo_custo < custo_minimo) {
                custo_minimo = novo_custo;
            }
        }
    }
    
    memo[pos][mascara] = custo_minimo;
    return custo_minimo;
}

// Reconstrói o caminho ótimo a partir dos estados memorizados
std::vector<int> ResolvedorDinamico::reconstruir_caminho(int pos, int mascara, std::vector<std::vector<int>>& memo) {
    std::vector<int> caminho;
    
    // Enquanto não visitou todas as cidades
    while (mascara != ((1 << num_cidades) - 1)) {
        int melhor_prox = -1;
        int melhor_custo = std::numeric_limits<int>::max();
               
        // Encontra próxima cidade do caminho ótimo
        for (int prox = 0; prox < num_cidades; prox++) {
            if (!(mascara & (1 << prox))) {
                int custo = distancias[pos][prox] + resolver_programacao_dinamica(prox, mascara | (1 << prox), memo);
                if (custo < melhor_custo) {
                    melhor_custo = custo;
                    melhor_prox = prox;
                }
            }
        }
        // Adiciona cidade ao caminho e atualiza estado
        caminho.push_back(melhor_prox);
        mascara |= (1 << melhor_prox);
        pos = melhor_prox;
    }
    
    return caminho;
}

// Resolve o problema do caixeiro viajante usando programação dinâmica
std::pair<int, std::vector<int>> ResolvedorDinamico::resolver() {
    
    // Inicializa matriz de memoização
    std::vector<std::vector<int>> memo(num_cidades, std::vector<int>(1 << num_cidades, -1));
    
    // Calcula custo mínimo e reconstrói caminho ótimo
    int custo_minimo = resolver_programacao_dinamica(0, 1, memo);
    std::vector<int> melhor_caminho = reconstruir_caminho(0, 1, memo);
    
    return {custo_minimo, melhor_caminho};
}