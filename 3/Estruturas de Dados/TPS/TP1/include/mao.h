#pragma once

#include "carta.h"
#include "sort.h"
#include "vetor.h"

#include <string>
#include <fstream>

class Mao{
private:
    Vetor<carta_t>cartas = Vetor<carta_t>(5, 0); ///< Vetor de cartas
    int forca; ///< Força da mão
    int ranque; ///< Ranque da mão
    enum ranques ///< Classificações das mãos
    {
        HIGH_CARD,
        ONE_PAIR,
        TWO_PAIR,
        THREE_OF_A_KIND,
        STRAIGHT,
        FLUSH,
        FULL_HOUSE,
        FOUR_OF_A_KIND,
        STRAIGHT_FLUSH,
        ROYAL_FLUSH
    };
    std::string nomes_ranques[10] = { ///< Nomes das classificações para exibir na saída
        "HC",
        "OP",
        "TP",
        "TK",
        "S",
        "F",
        "FH",
        "FK",
        "SF",
        "RSF"};
    /**
     *  Função que verifica se a mão é um royal flush.
     *        Custo: O(1).
     *  
     *  true Se a mão for um royal flush.
     */
    bool eh_royal_flush();

    /**
     *  Função que verifica se a mão é um straight flush.
     *        Custo: O(1).
     *  true Se a mão for um straight flush.
     */ 
    bool eh_straight_flush();

    /**
     *  Função que verifica se mão é uma quadra.
     *        Custo: O(1).
     * 
     *  true Se a mão for uma quadra.
     */
    bool eh_four_of_a_kind();

    /**
     *  Função que verifica se a mão é um full house.
     *        Custo: O(1).
     *  true Se a mão for um full house.
     */
    bool eh_full_house();

    /**
     *  Função que verifica se a mão é um flush.
     *        Custo: O(1).
     *  true Se a mão for um flush.
     */
    bool eh_flush();

    /**
     *  Função que verifica se a mão é um straight.
     *        Custo: O(1).
     *  true Se a mão for um straight.
     */
    bool eh_straight();

    /**
     *  Função que verifica se a mão é uma trinca.
     *        Custo: O(1).
     *  true Se a mão for uma trinca.
     */
    bool eh_three_of_a_kind();

    /**
     *  Função que verifica se a mão é dois pares.    
     *        Custo: O(1).
     *  true Se a mão for dois pares.
     */
    bool eh_two_pair();
    
    /**
     *  Função que verifica se a mão é um par.
     *        Custo: O(1).
     *  true Se a mão for um par.
     */
    bool eh_one_pair();

    /**
     *  Função que pega a carta alta de uma mão (desconsiderando o que já faz parte de uma combinação).
     *        Custo: O(n). Onde n é o número de cartas na mão, que é sempre 5. Então é O(1).
     * 
     *  int o valor da carta alta.
     */
    int high_card();

    /**
     *  Função que pega o valor do primeiro par que encontrar na mão (apenas um par mesmo, ignora trincas ou quadras).
     *        Custo: O(n). Onde n é o número de cartas na mão, que é sempre 5. Então é O(1).
     * 
     *  int o valor das cartas no par.
     */
    int get_valor_par();

    /**
     *  Função que pega o valor do menor par na mão (para as combinações de dois pares).
     *        Custo: O(n). Onde n é o número de cartas na mão, que é sempre 5. Então é O(1).
     *  
     *  int o valor do menor par.
     */
    int par_menor();

    /**
     *  Função que pega o valor do maior par na mão (para as combinações de dois pares).
     *        Custo: O(n). Onde n é o número de cartas na mão, que é sempre 5. Então é O(1).
     * 
     *  int o valor do maior par.
     */
    int par_maior();

    /**
     *  Função que pega o valor da trinca na mão.
     *        Custo: O(n). Onde n é o número de cartas na mão, que é sempre 5. Então é O(1).
     * 
     *  int o valor da trinca.
     */
    int get_tripla();

    /**
     *  Função que determina a força da mão que o jogador possui. Com valores para o desempate de combinações "iguais".
     *        Também determina qual é a combinação da mão.
     *        Custo: O(1).
     * 
     *  int a força da mão.
     */
    int determina_forca();

public:  
    Mao(/* args */);
    /**
     *  Construtor da classe Mao.
     *        Custo: O(1).
     * 
     *  cartas string com as cartas para a mão.
     */
    explicit Mao(std::string cartas[5]);

    /**
     *  Lê da string as cartas para a mão.
     *        Custo: O(n). Onde n é o número de cartas na mão, que é sempre 5. Então é O(1).
     * 
     *  cartas string com as cartas para a mão.
     */
    void parse_cartas(std::string cartas[5]);

    /**
     *  Getter para o nome da combinação da mão.
     * 
     *  std::string com o nome da combinação.
     */
    std::string get_nome();

    ~Mao() = default;
    bool operator<(const Mao &other) const;
    bool operator>(const Mao &other) const;
    bool operator==(const Mao &other) const;
};
