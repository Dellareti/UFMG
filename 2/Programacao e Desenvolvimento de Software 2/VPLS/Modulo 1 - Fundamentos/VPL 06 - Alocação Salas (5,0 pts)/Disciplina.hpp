#ifndef DISCIPLINA_HPP
#define DISCIPLINA_HPP

#include "Alocacao.hpp"

#include <string>
#include <list>

struct Disciplina{
    std::string codigo, nome;
    std::list<Alocacao> alocacao;
    Disciplina(std::string codigo, std::string nome);
    Disciplina(Disciplina const &d);
    Disciplina() = default;
    void inserir_alocacao(std::string dia, std::string horario, std::string sala);
    void remover_alocacao(std::string horario);
    void imprimir_alocacao();
};

#endif