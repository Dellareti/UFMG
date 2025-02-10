#include "io.h"
#include "jogador.h"
#include "sort.h"

#include <iostream>

auto get_token_inverso(std::string &linha){
	const auto pos = linha.find(' ');
    auto token = linha.substr(0, pos);
    inverte(token, token.size());
    linha.erase(0, pos + 1);
    return token;
}

// reverter a string
Jogador parse_jogada(std::string &linha){
    linha.erase(linha.find_last_not_of(" \n\r\t") + 1);
    inverte(linha, linha.size()); // pegando as cartas primeiro
    std::string cartas[5];
    
    for (int i = 0; i < 5; i++){
	    const auto token = get_token_inverso(linha);
        cartas[i] = token;
    }

    const auto token = get_token_inverso(linha);
    const int aposta = std::stoi(token);
    inverte(linha, linha.size()); // o que restou é o nome
    const std::string nome = linha;
    Jogador jogador(nome, Mao(cartas), aposta);
    return jogador;
}

auto get_token(std::string &linha){

	const auto pos = linha.find(' ');
    auto token = linha.substr(0, pos);
    linha.erase(0, pos + 1);
    return token;
}

void get_info_jogo(std::string &linha, int &n_rounds, int &dinheiro_inicial){
    auto token = get_token(linha);
    n_rounds = std::stoi(token);
    token = get_token(linha);
    dinheiro_inicial = std::stoi(token);
}

void get_info_rodada(std::string &linha, int &n_jogadores, int &pingo){
    auto token = get_token(linha);
    n_jogadores = std::stoi(token);
    token = get_token(linha);
    pingo = std::stoi(token);
}