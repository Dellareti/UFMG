#include "estado.h"
#include <iostream>

int main() {
    // Lê a primeira linha
    int vertices, arestas;
    std::cin >> vertices >> arestas;
    
    Estado estado(vertices);
    
    // Lê as cidades e cria o mapeamento
    std::string cidade_A, cidade_B;
    std::map<std::string, bool> conjunto_das_cidades;
    std::vector<std::pair<std::string, std::string>> estradas;

    for (int i = 0; i < arestas; i++) {
        std::cin >> cidade_A >> cidade_B;
        conjunto_das_cidades[cidade_A] = true;
        conjunto_das_cidades[cidade_B] = true;
        estradas.push_back({cidade_A, cidade_B});
    }
    // Verifica se o número de cidades corresponde ao número de vértices
      if (conjunto_das_cidades.size() != static_cast<size_t>(vertices)) {
            std::cerr << "Número de cidades diferentes (" << conjunto_das_cidades.size() 
                     << ") não corresponde ao número de vértices informado (" << vertices << ")" << std::endl;
            return 1;
        }
    
    // Cria o mapeamento de cidades para índices
    int indice = 0;
    for (const auto& par : conjunto_das_cidades) {
        estado.adiciona_cidade(par.first, indice++);
    }
    
    // Adiciona as estradas
    for (const auto& estrada : estradas) {
        estado.adiciona_estrada(estrada.first, estrada.second);
    }
   
    // Encontra a Capital - PT I
    std::string capital = estado.calcula_capital();
    std::cout << capital << std::endl;

    // Encontra Batalhoes - PT II
    auto [num_cfcs, nomes_cfcs] = estado.calcula_batalhao();

    // Número de CFCs (exceto capital)
    std::cout << num_cfcs << std::endl;
    
    for (const auto& cidade : nomes_cfcs) {
        std::cout << cidade << std::endl;
    }

    // Encontra Patrulhamento - PT III
   
    auto [num_patrulhas, caminhos] = estado.calcula_patrulhamento();
    std::cout << num_patrulhas << std::endl;

    if (num_patrulhas > 0) {
        for (const auto& caminho : caminhos) {
            for (size_t i = 0; i < caminho.size(); i++) {
                std::cout << estado.indice_para_cidade[caminho[i]];
                if (i < caminho.size() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    return 0;
}