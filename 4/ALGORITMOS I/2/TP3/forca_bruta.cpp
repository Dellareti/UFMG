#include "resolvedor_caixeiro.hpp"

void ResolvedorForcaBruta::trocar(std::vector<int>& vetor, int i, int j) {
    int temp = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = temp;
}

bool ResolvedorForcaBruta::prox_permutacao(std::vector<int>& vetor) {
    // Usamos static_cast para evitar warnings de conversão
    int n = static_cast<int>(vetor.size());
    int i = n - 2;
    
    while (i >= 0 && vetor[i] >= vetor[i + 1]) i--;
    if (i < 0) return false;
    
    int j = n - 1;
    while (vetor[j] <= vetor[i]) j--;
    
    trocar(vetor, i, j);
    
    int esq = i + 1, dir = n - 1;
    while (esq < dir) {
        trocar(vetor, esq++, dir--);
    }
    
    return true;
}

std::pair<int, std::vector<int>> ResolvedorForcaBruta::resolver() {
    std::vector<int> vertices;
    for (int i = 1; i < num_cidades; i++) {
        vertices.push_back(i);
    }

    int custo_minimo = std::numeric_limits<int>::max();
    std::vector<int> melhor_caminho = vertices;
    
    do {
        int custo_atual = 0;
        int k = 0;
        
        custo_atual += distancias[0][vertices[0]];
        
        // Usamos static_cast para evitar warnings de conversão
        for (k = 0; k < static_cast<int>(vertices.size()) - 1; k++) {
            custo_atual += distancias[vertices[k]][vertices[k + 1]];
        }
        
        custo_atual += distancias[vertices[k]][0];
        
        if (custo_atual < custo_minimo) {
            custo_minimo = custo_atual;
            melhor_caminho = vertices;
        }
        
    } while (prox_permutacao(vertices));

    return {custo_minimo, melhor_caminho};
}