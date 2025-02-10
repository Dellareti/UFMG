#pragma once

#include <string>
#include <fstream>
#include "mao.h"


class Jogador{
private:
    std::string nome; ///< Nome do jogador
    Mao mao; ///< Mao do jogador
    int aposta; ///< Valor da aposta
public:
    Jogador() = default;

    /**
     *  Construtor da classe Jogador.
     *        Custo: O(1) (desconsiderando o custo do move()).
     * 
     * @param nome Nome do jogador.
     * @param mao Mão do jogador.
     * @param aposta Valor da aposta.
     */
    Jogador(std::string nome, const Mao& mao, int aposta);
    
    /**
     *  Getter da mão do jogador.
     *        Custo: O(1).
     * 
     *  Mao do jogador.
     */
    Mao get_mao();
    
    /**
     *  Getter da aposta do jogador.
     *        Custo: O(1).
     * 
     *  int com a aposta do jogador.
     */
    int get_aposta();
    
    /**
     *  Getter do nome do jogador.
     *        Custo: O(1).
     * 
     *  std::string com o nome do jogador.
     */
    std::string get_nome();

    bool operator<(const Jogador &other) const;
    bool operator>(const Jogador &other) const;
    bool operator==(const Jogador &other) const;
    ~Jogador() = default;
};
