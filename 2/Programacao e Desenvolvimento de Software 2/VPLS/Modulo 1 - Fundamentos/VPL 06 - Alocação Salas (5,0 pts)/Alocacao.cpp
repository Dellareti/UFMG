#include "Alocacao.hpp"

#include <iostream>

Alocacao::Alocacao(std::string dia, std::string horario, std::string sala) : dia(dia), horario(horario), sala(sala) {}

void Alocacao::imprimir_dados(){
    std::cout << dia << " " << horario << " " << sala << std::endl;
}