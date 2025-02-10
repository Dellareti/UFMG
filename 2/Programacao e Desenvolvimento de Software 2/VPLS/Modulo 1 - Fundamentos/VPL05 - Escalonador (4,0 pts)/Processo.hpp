#ifndef PROCESSO_HPP
#define PROCESSO_HPP

#include <string>

struct Processo{
    int _id;
    std::string _nome;
    int _prioridade;

    Processo(int id, std::string nome, int prioridade);
    void imprimir_dados();
};

#endif