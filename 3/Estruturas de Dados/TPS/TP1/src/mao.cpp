#include "mao.h"
#include "sort.h"
#include "vetor.h"

#include <string>
#include <iostream>


int Mao::high_card(){
    const auto cartas = this->cartas; // pq só vamos acessar
    if (ranque == HIGH_CARD){
        return cartas[0].valor;
    }
    if (ranque == ONE_PAIR){
	    const int valor_par = get_valor_par();
        
        for (int i = 0; i < 5; i++){
            if (cartas[i].valor != valor_par){
                return cartas[i].valor;
            }
        }
    }
    if (ranque == TWO_PAIR){
	    const int menor = par_menor();
	    const int maior = par_maior();
        
        for (int i = 0; i < 5; i++){
            if (cartas[i].valor != maior && cartas[i].valor != menor){
                return cartas[i].valor;
            }
        }
    }
    if (ranque == THREE_OF_A_KIND){
	    const int tripla = get_tripla();
        
        for (int i = 0; i < 5; i++){
            if (cartas[i].valor != tripla){
                return cartas[i].valor;
            }
        }
    }
    if (ranque == FLUSH){
        return cartas[0].valor;
    }
    return 0;
}

int Mao::get_valor_par(){
    const auto cartas = this->cartas;
    // par no começo
    if (cartas[0].valor == cartas[1].valor && cartas[0].valor != cartas[2].valor) {
        return cartas[0].valor;
    }
    // par no final
    if (cartas[4].valor == cartas[3].valor && cartas[4].valor != cartas[2].valor) {
        return cartas[4].valor;
    }
    // par no meio
    for (int i = 1; i < 4; i++){
        if (cartas[i].valor == cartas[i + 1].valor && cartas[i].valor != cartas[i + 2].valor && cartas[i].valor != cartas[i - 1].valor){
            return cartas[i].valor;
        }
    }
    return -1; // nunca vai cair aqui pq só vamos chamar isso quando tivermos certeza que é um par :D
}

int Mao::par_maior(){
    const auto cartas = this->cartas;
    int valor_par = -1;
    
    for (auto i = 0; i < 4; i++){
        if (cartas[i].valor == cartas[i + 1].valor){
            if (valor_par < cartas[i].valor){
                valor_par = cartas[i].valor;
            }
        }
    }
    return valor_par;
}

int Mao::par_menor(){
    const auto cartas = this->cartas;
    int valor_par = 999999;

    for (auto i = 0; i < 4; i++){
        if (cartas[i].valor == cartas[i + 1].valor){
            if (valor_par > cartas[i].valor){
                valor_par = cartas[i].valor;
            }
        }
    }
    return valor_par;
}

int Mao::get_tripla(){
    const auto cartas = this->cartas;

    for (auto i = 0; i < 3; i++){
        if (cartas[i].valor == cartas[i + 1].valor && cartas[i].valor == cartas[i + 2].valor){
            return cartas[i].valor;
        }
    }
    return -1; // só chamamos se tiver um par, então nunca vai cair aqui
}

int Mao::determina_forca(){
    const auto cartas = this->cartas;
    if (eh_royal_flush()){
        ranque = ROYAL_FLUSH;
        return 99999;
    }
    if (eh_straight_flush()){
        ranque = STRAIGHT_FLUSH;
        return STRAIGHT_FLUSH * 10000 + cartas[0].valor;
    }
    if (eh_four_of_a_kind()){
        ranque = FOUR_OF_A_KIND;
        return FOUR_OF_A_KIND * 10000 + cartas[2].valor * 10 + (cartas[0].valor != cartas[1].valor ? cartas[0].valor : cartas[4].valor);
    }
    if (eh_full_house()){
        ranque = FULL_HOUSE;
        return FULL_HOUSE * 10000 + get_tripla() * 10 + get_valor_par();
    }
    if (eh_flush()){
        ranque = FLUSH;
        return FLUSH * 10000 + high_card();
    }
    if (eh_straight()){
        ranque = STRAIGHT;
        return STRAIGHT * 10000 + cartas[4].valor;
    }
    if (eh_three_of_a_kind()){
        ranque = THREE_OF_A_KIND;
        return THREE_OF_A_KIND * 10000 + get_tripla() * 10 + high_card();
    }
    if (eh_two_pair()){
        ranque = TWO_PAIR;
        return TWO_PAIR * 10000 + par_maior() * 100 + par_menor() * 10 + high_card();
    }
    if (eh_one_pair()){
        ranque = ONE_PAIR;
        return ONE_PAIR * 10000 + get_valor_par() * 10 + high_card();
    }
    ranque = HIGH_CARD;
    return high_card();
}

void Mao::parse_cartas(std::string cartas[5]){
    for (auto i = 0; i < 5; i++){
        Mao::cartas[i].naipe = cartas[i][cartas[i].size() - 1];
        const auto value = std::stoi(cartas[i].substr(0, cartas[i].size() - 1));
        Mao::cartas[i].valor = value == 1 ? 14 : value;
    }
}

bool Mao::eh_royal_flush(){
    const auto cartas = this->cartas;
    return eh_straight_flush() && cartas[0].valor == 14 && cartas[1].valor == 13;
}

bool Mao::eh_straight_flush(){
    const auto cartas = this->cartas;
    return eh_flush() && eh_straight();
}

bool Mao::eh_four_of_a_kind(){
    const auto cartas = this->cartas;
    if (cartas[0].valor == cartas[1].valor &&
        cartas[1].valor == cartas[2].valor &&
        cartas[2].valor == cartas[3].valor)
        return true;
    if (cartas[1].valor == cartas[2].valor &&
        cartas[2].valor == cartas[3].valor &&
        cartas[3].valor == cartas[4].valor)
        return true;
    return false;
}

bool Mao::eh_full_house(){
    const auto cartas = this->cartas;
    if (cartas[0].valor == cartas[1].valor &&
        cartas[2].valor == cartas[3].valor &&
        cartas[3].valor == cartas[4].valor)
        return true;
    if (cartas[0].valor == cartas[1].valor &&
        cartas[1].valor == cartas[2].valor &&
        cartas[3].valor == cartas[4].valor)
        return true;
    return false;
}

bool Mao::eh_flush(){
    const auto cartas = this->cartas;
    if (cartas[0].naipe == cartas[1].naipe &&
        cartas[1].naipe == cartas[2].naipe &&
        cartas[2].naipe == cartas[3].naipe &&
        cartas[3].naipe == cartas[4].naipe)
        return true;
    return false;
}

bool Mao::eh_straight(){
    const auto cartas = this->cartas;
    if (cartas[0].valor == cartas[1].valor + 1 &&
        cartas[1].valor == cartas[2].valor + 1 &&
        cartas[2].valor == cartas[3].valor + 1 &&
        cartas[3].valor == cartas[4].valor + 1)
        return true;
    if (cartas[0].valor == 14 &&
        cartas[1].valor == 5 &&
        cartas[2].valor == 4 &&
        cartas[3].valor == 3 &&
        cartas[4].valor == 2)
        return true;
    return false;
}

bool Mao::eh_three_of_a_kind(){
    const auto cartas = this->cartas;
    if (cartas[0].valor == cartas[1].valor &&
        cartas[1].valor == cartas[2].valor)
        return true;
    if (cartas[1].valor == cartas[2].valor &&
        cartas[2].valor == cartas[3].valor)
        return true;
    if (cartas[2].valor == cartas[3].valor &&
        cartas[3].valor == cartas[4].valor)
        return true;
    return false;
}

bool Mao::eh_two_pair(){
    const auto cartas = this->cartas;
    if (cartas[0].valor == cartas[1].valor &&
        cartas[2].valor == cartas[3].valor)
        return true;
    if (cartas[0].valor == cartas[1].valor &&
        cartas[3].valor == cartas[4].valor)
        return true;
    if (cartas[1].valor == cartas[2].valor &&
        cartas[3].valor == cartas[4].valor)
        return true;
    return false;
}

bool Mao::eh_one_pair(){
    const auto cartas = this->cartas;
    if (cartas[0].valor == cartas[1].valor)
        return true;
    if (cartas[1].valor == cartas[2].valor)
        return true;
    if (cartas[2].valor == cartas[3].valor)
        return true;
    if (cartas[3].valor == cartas[4].valor)
        return true;
    return false;
}

Mao::Mao(/* args */) : forca(0)
{
}

Mao::Mao(std::string cartas[5])
{
    parse_cartas(cartas);
    Mao::cartas.sort();
    forca = determina_forca();
}

bool Mao::operator<(const Mao &other) const{
    return forca < other.forca;
}

bool Mao::operator>(const Mao &other) const{
    return forca > other.forca;
}

bool Mao::operator==(const Mao &other) const{
    return forca == other.forca;
}

std::string Mao::get_nome(){
    return nomes_ranques[ranque];
}
