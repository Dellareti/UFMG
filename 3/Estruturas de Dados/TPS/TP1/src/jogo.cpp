#include "jogo.h"
#include "io.h"
#include "jogador.h"
#include "sort.h"
#include "mao.h"
#include "vetor.h"

#include <iostream>
#include <fstream>

Jogo::Jogo(std::ifstream &entrada, std::ofstream &saida) : entrada(entrada), saida(saida){
    std::string linha;
    std::getline(entrada, linha);
    get_info_jogo(linha, n_rounds, dinheiro_inicial);
}

Jogo::~Jogo(){
    delete banco;
}

void Jogo::comeca(){
    primeira_rodada();
    
    for (int i = 1; i < n_rounds; i++){
        std::string linha;
        std::getline(entrada, linha);
        int n_jogadores_round, pingo;
        get_info_rodada(linha, n_jogadores_round, pingo);

        Vetor<Jogador> jogadores = Vetor<Jogador>(n_jogadores_round, 2);

        int pote = pingo * n_jogadores;
        banco->modifica_todos_saldos(-pingo);
        bool valid = true;

        for (int j = 0; j < n_jogadores_round; j++){
            std::getline(entrada, linha);
            jogadores[j] = parse_jogada(linha);
            pote += jogadores[j].get_aposta();

            if (valid && !banco->modifica_saldo(static_cast<const Vetor<Jogador>>(jogadores)[j].get_nome(), -jogadores[j].get_aposta()) || jogadores[j].get_aposta() % 50 != 0){
                valid = false;
                // devolve o saldo que já foi descontado
                for (int k = 0; k < j; k++) {
                    banco->modifica_saldo(static_cast<const Vetor<Jogador>>(jogadores)[k].get_nome(), jogadores[k].get_aposta());
                }
            }
        }
        if (valid){
            jogadores.sort();
            const int vencedores = n_vencedores(jogadores, n_jogadores_round);
            saida << vencedores << " " << pote << " " << jogadores[0].get_mao().get_nome() << std::endl;
            nomes_jogadores(jogadores, vencedores);
            distribui_pote(jogadores, vencedores, pote);
        }
    }
}

void Jogo::resultado(){
    saida << "####" << std::endl;
    banco->mostra_saldo(saida);
}

void Jogo::primeira_rodada(){
    std::string linha;
    std::getline(entrada, linha);
    int pingo;

    get_info_rodada(linha, n_jogadores, pingo);
    Vetor<Jogador> jogadores = Vetor<Jogador>(n_jogadores, 2);

    int pote = pingo * n_jogadores;
    for (int i = 0; i < n_jogadores; i++){

        std::getline(entrada, linha);
        jogadores[i] = parse_jogada(linha);
        pote += jogadores[i].get_aposta();
    }

    this->banco = new Banco(n_jogadores, jogadores, dinheiro_inicial);

    for (int i = 0; i < n_jogadores; i++){
        if (!banco->modifica_saldo(static_cast<const Vetor<Jogador>>(jogadores)[i].get_nome(), -(jogadores[i].get_aposta() + pingo)) || jogadores[i].get_aposta() % 50 != 0){
            // devolve o saldo que já foi descontado
            for (int j = 0; j < i; j++) {
                banco->modifica_saldo(static_cast<const Vetor<Jogador>>(jogadores)[j].get_nome(), jogadores[j].get_aposta() + pingo);
            }
            return;
        }
    }
    jogadores.sort();
    const int vencedores = n_vencedores(jogadores, n_jogadores);

    saida << vencedores << " " << pote << " " << jogadores[0].get_mao().get_nome() << std::endl;

    nomes_jogadores(jogadores, vencedores);
    distribui_pote(jogadores, vencedores, pote);
}

int Jogo::n_vencedores(const Vetor<Jogador> jogadores, const int n){
    int vencedores = 1; // o primeiro na lista vai ter a mão com maior ranque, então qualquer empate será entre ele e os proximos jogadores na lista com o mesmo ranque da mão
    
    for (int i = 1; i < n; i++){
        if (jogadores[i].get_mao() == jogadores[0].get_mao()){
            vencedores++;
        }
        else{
            return vencedores;
        }
    }
    return vencedores;
}

void Jogo::nomes_jogadores(const Vetor<Jogador> jogadores, const int n){
    Vetor<std::string> nomes(n, 2);

    for (int i = 0; i < n; i++){
        nomes[i] = jogadores[i].get_nome();
    }
    nomes.sort();

    inverte(nomes, n);
    for (int i = 0; i < n - 1; i++){
        saida << nomes[i] << " ";
    }
    saida << nomes[n - 1] << std::endl;
}

void Jogo::distribui_pote(const Vetor<Jogador> jogadores, int n, int pote){
	const int pote_por_vencedor = pote / n;
    
    for (int i = 0; i < n; i++){
        banco->modifica_saldo(jogadores[i].get_nome(), pote_por_vencedor);
    }
}