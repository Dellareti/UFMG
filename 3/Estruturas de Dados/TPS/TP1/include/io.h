#pragma once

#include "jogador.h"

#include <string>

/**
 *  Inverte o vetor (inplace).
 *        Custo: O(n).
 * 
 * s string a ser invertida
 */
template <typename T>
void inverte(T &s, int n){
    for (std::size_t i = 0; i < n / 2; i++){
	    const auto j = n - i - 1;
        troca(s[i], s[j]);
    }
}

/**
 *  Lê uma jogada a partir de uma linha.
 *        Custo: O(n). Onde n é o número de cartas na mão, que é sempre 5. Então é O(1).
 * 
 * linha linha com a jogada.
 *  Jogador um objeto Jogador construído com a jogada.
 */
Jogador parse_jogada(std::string &linha);

/**
 *  Lê as informações do jogo a partir de uma linha.
 *        Custo: O(1).
 * 
 * linha linha com as informações.
 * n_rounds variável que recebe o número de rounds. (referência)
 * dinheiro_inicial variável que recebe o dinheiro inicial. (referência)
 */
void get_info_jogo(std::string &linha, int &n_rounds, int &dinheiro_inicial);

/**
 *  Lê as informações da rodada a partir de uma linha.
 *        Custo: O(1).
 * 
 * line linha com as informações.
 * n_jogadores variável que recebe o número de jogadordres. (referência)
 * pingo variável que recebe o pingo da rodada. (referência)
 */
void get_info_rodada(std::string &line, int &n_jogadores, int &pingo);
