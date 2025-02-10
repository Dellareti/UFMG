#include "jogador.h"

#include <iostream>

Mao Jogador::get_mao(){
    return mao;
}

int Jogador::get_aposta(){
    return aposta;
}

std::string Jogador::get_nome(){
    return nome;
}

Jogador::Jogador(std::string nome, const Mao& mao, int aposta) : nome(std::move(nome)), mao(mao), aposta(aposta)
{
}

bool Jogador::operator<(const Jogador &other) const{
    return mao < other.mao;
}

bool Jogador::operator>(const Jogador &other) const{
    return mao > other.mao;
}

bool Jogador::operator==(const Jogador &other) const{
    return mao == other.mao;
}