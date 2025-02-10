#include "rede_eletrica.hpp"
#include <iostream>

int main() {
    int num_vertices, num_arestas;
    std::cin >> num_vertices >> num_arestas;

    RedeEletrica rede(num_vertices);

    // Lê informações dos nós
    for (int i = 0; i < num_vertices; i++) {
        int no, tipo;
        std::cin >> no >> tipo;
        rede.definir_tipo_no(no, tipo);
    }

    // Lê conexões
    for (int i = 0; i < num_arestas; i++) {
        int origem, destino, capacidade;
        std::cin >> origem >> destino >> capacidade;
        rede.adicionar_conexao(origem, destino, capacidade);
    }

    // Calcula e imprime resultados
    std::cout << rede.calcular_energia_total() << std::endl;
    std::cout << rede.calcular_energia_nao_atendida() << std::endl;
    std::cout << rede.calcular_energia_perdida() << std::endl;

    auto conexoes_criticas = rede.encontrar_conexoes_criticas();
    std::cout << conexoes_criticas.size() << std::endl;

    for (const auto& conexao : conexoes_criticas) {
    // Imprime origem da conexão
    std::cout << std::get<0>(conexao) << " " 
              // Imprime destino da conexão
              << std::get<1>(conexao) << " " 
              // Imprime capacidade da conexão
              << std::get<2>(conexao) << std::endl;
    }

    return 0;
}