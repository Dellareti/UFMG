#include "resolvedor_caixeiro.hpp"

std::pair<int, std::vector<int>> ResolvedorGuloso::resolver() {
    int melhor_custo = std::numeric_limits<int>::max();
    std::vector<int> melhor_caminho;
    
    // Tenta começar de cada cidade
    for(int cidade_inicio = 0; cidade_inicio < num_cidades; cidade_inicio++) {
        std::vector<bool> visitado(num_cidades, false);
        std::vector<int> caminho_atual;
        int custo_atual = 0;
        
        // Marca a cidade inicial como visitada
        int cidade_atual = cidade_inicio;
        visitado[cidade_atual] = true;
        
        // Se não estamos começando da cidade 0, a adicionamos ao caminho
        if(cidade_atual != 0) {
            caminho_atual.push_back(cidade_atual);
        }
        
        // Constrói o caminho a partir desta cidade inicial
        for(int i = 0; i < num_cidades - 1; i++) {
            int proxima_cidade = -1;
            int menor_distancia = std::numeric_limits<int>::max();
            
            // Encontra a cidade não visitada mais próxima
            for(int j = 0; j < num_cidades; j++) {
                if(!visitado[j] && distancias[cidade_atual][j] < menor_distancia) {
                    menor_distancia = distancias[cidade_atual][j];
                    proxima_cidade = j;
                }
            }
            
            if(proxima_cidade != -1) {
                // Adiciona a próxima cidade ao caminho (exceto se for 0 e não for a última)
                if(proxima_cidade != 0 || i == num_cidades - 2) {
                    caminho_atual.push_back(proxima_cidade);
                }
                visitado[proxima_cidade] = true;
                custo_atual += menor_distancia;
                cidade_atual = proxima_cidade;
            }
        }
        
        // Adiciona o custo de voltar à cidade inicial
        custo_atual += distancias[cidade_atual][cidade_inicio];
        
        // Se este caminho é melhor que o anterior, atualiza
        if(custo_atual < melhor_custo) {
            melhor_custo = custo_atual;
            melhor_caminho = caminho_atual;
            
            // Se não começamos da cidade 0, reorganiza o caminho
            if(cidade_inicio != 0) {
                std::vector<int> novo_caminho;
                bool found_zero = false;
                
                // Primeiro procura a partir do 0 até o fim
                for(size_t i = 0; i < caminho_atual.size(); i++) {
                    if(found_zero) {
                        novo_caminho.push_back(caminho_atual[i]);
                    } else if(caminho_atual[i] == 0) {
                        found_zero = true;
                    }
                }
                
                // Depois do início até antes do 0
                for(size_t i = 0; i < caminho_atual.size(); i++) {
                    if(caminho_atual[i] == 0) {
                        break;
                    }
                    novo_caminho.push_back(caminho_atual[i]);
                }
                
                melhor_caminho = novo_caminho;
            }
        }
    }
    
    return {melhor_custo, melhor_caminho};
}