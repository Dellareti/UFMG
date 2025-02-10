#pragma once

#include "jogador.h"
#include "vetor.h"

#include <string>

struct conta{
    std::string nome; ///< nome do jogador
    int saldo; ///< saldo da conta
    conta() : nome(""), saldo(-1) {}
    bool operator<(const conta &other) const
    {
        return saldo < other.saldo;
    }
};

class Banco{
    private:
    int n_contas; ///< numero de contas
    Vetor<conta> contas = Vetor<conta>(10, 1); ///< não é possível mais de 10 players com um baralho só
    public:
    /**
     *  Construtor da classe Banco.
     *        Custo: O(n).
     *  n_contas Número de contas do banco
     *  jogadores Vetor de jogadores
     *  dinheiro_inicial Saldo inicial de cada conta
     */
    Banco(int n_contas, Vetor<Jogador> jogadores, int dinheiro_inicial);
    
    /**
     *  Modifica o saldo de apenas uma conta, indexada pelo nome.
     *        Custo: O(n) por conta da busca sequencial pela conta a partir do nome.
     *  nome Nome da conta.
     *  quantia Quantia a ser adicionada ou subtraída.
     */
    int modifica_saldo(const std::string& nome, int quantia);
    
    /**
     *  Imprime o saldo de todas as contas em saida.
     *        Custo: O(n).
     *  saida o arquivo de saída
     */
    void mostra_saldo(std::ofstream &saida);
    
    /**
     *  Modifica o saldo de todas as contas.
     *        Custo: O(n).
     *  quantia Quantia a ser adicionada ou subtraída.
     */
    void modifica_todos_saldos(int quantia);
};
