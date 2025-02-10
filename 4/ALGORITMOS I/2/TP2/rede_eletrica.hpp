#ifndef REDE_ELETRICA_H
#define REDE_ELETRICA_H

#include <vector>
#include <tuple>

class RedeEletrica {
private:
    // Atributos e Funções Auxiliares
    int numero_vertices;
    std::vector<std::vector<int>> capacidade;
    std::vector<std::vector<int>> fluxo;
    std::vector<int> demandas;
    std::vector<bool> eh_gerador;

    bool busca_em_largura(std::vector<std::vector<int>>& grafo_residual, int fonte, int sumidouro, std::vector<int>& pai);
    int ford_fulkerson(std::vector<std::vector<int>>& capacidade_atual, int fonte, int sumidouro);
    int valor_minimo(int a, int b);
    int energia_recebida_por_consumidor();

public:
    // Criação da Rede e Funções Principais
    explicit RedeEletrica(int vertices);
    void adicionar_conexao(int origem, int destino, int capacidade);
    void definir_tipo_no(int no, int tipo);
    int calcular_energia_total();
    int calcular_energia_nao_atendida();
    int calcular_energia_perdida();
    std::vector<std::tuple<int, int, int>> encontrar_conexoes_criticas();
};

#endif