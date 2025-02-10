#pragma once

#include "banco.h"
#include "vetor.h"

#include <fstream>

class Jogo{
private:
    int n_rounds; ///< numero de rounds
    int n_jogadores; ///< numero de jogadores
    int dinheiro_inicial; ///< dinheiro inicial
    Banco *banco; ///< banco do jogo
    std::ifstream &entrada; ///< arquivo de entrada
    std::ofstream &saida; ///< arquivo de saida
public:
    Jogo() = default;
    /**
     *  Construtor da classe Jogo.
     * 
     * entrada arquivo de entrada (já aberto).
     * saida arquivo de saída (já aberto).
     */
    Jogo(std::ifstream &entrada, std::ofstream &saida);
    /**
     *  Destrói o objeto Jogo.
     *        Libera o banco.
     */
    ~Jogo();

    /**
     *  Inicia o jogo.
     * 
     */
    void comeca();

    /**
     *  Primeira rodada do jogo. É especial pois nela descobriremos os jogadores e começaremos o banco.
     * 
     */
    void primeira_rodada();

    /**
     *  Conta o número de jogadores que venceram a rodada.
     * 
     * jogadores jogadores da rodada.
     * n número de jogadores na rodada.
     *  int número de vencedores.
     */
    int n_vencedores(Vetor<Jogador> jogadores, int n);

    /**
     *  Escreve no arquivo de saída os n primeiros jogadores.
     * 
     * jogadores jogadores da rodada.
     * n número de jogadores a escrever os nomes.
     */
    void nomes_jogadores(Vetor<Jogador> jogadores, int n);

    /**
     *  Distribui o pote entre os vencedores da rodada.
     * 
     * jogadores jogadores da rodada.
     * n número de jogadores que venceram.
     * pote quantidade total do pote.
     */
    void distribui_pote(Vetor<Jogador> jogadores, int n, int pote);

    /**
     *  Imprime o resultado do jogo (nomes dos jogadores com o saldo, ordenados pelo saldo).
     * 
     */
    void resultado();
};
