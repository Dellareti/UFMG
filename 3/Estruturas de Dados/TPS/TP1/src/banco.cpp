#include "banco.h"
#include "jogador.h"
#include "sort.h"
#include "vetor.h"

Banco::Banco(const int n_contas, Vetor<Jogador> jogadores, const int dinheiro_inicial){
    this->n_contas = n_contas;
    for (int i = 0; i < n_contas; i++){
        contas[i].nome = jogadores[i].get_nome();
        contas[i].saldo = dinheiro_inicial;
    }
}

int Banco::modifica_saldo(const std::string &nome, const int quantia){
    
    for (int i = 0; i < n_contas; i++){
        if (contas[i].nome == nome){
            if (contas[i].saldo + quantia > 0){
                contas[i].saldo += quantia;
                return 1;
            }
            return 0;
        }
    }
    return -1;
}

void Banco::mostra_saldo(std::ofstream &saida){
    contas.sort();

    for (int i = 0; i < n_contas; i++){
        saida << contas[i].nome << " " << contas[i].saldo << std::endl;
    }
}

void Banco::modifica_todos_saldos(const int quantia){
    
    for (int i = 0; i < n_contas; i++){
        if (contas[i].saldo + quantia > 0){
            contas[i].saldo += quantia;
        }
        else{
            for (int j = 0; j < i; j++){
                contas[j].saldo -= quantia;
            }
            return;
        }
    }
}