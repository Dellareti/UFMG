#include "Disciplina.hpp"

#include <iostream>

Disciplina::Disciplina(std::string codigo, std::string nome) : codigo(codigo), nome(nome) {}

Disciplina::Disciplina(Disciplina const &d) : codigo(d.codigo), nome(d.nome), alocacao(d.alocacao) {}

void Disciplina::inserir_alocacao(std::string dia, std::string horario, std::string sala){
    alocacao.emplace_back(dia, horario, sala);
}

void Disciplina::remover_alocacao(std::string horario){
    alocacao.remove_if([&horario](Alocacao &alocacao)
                       { return alocacao.horario == horario; });
}

void Disciplina::imprimir_alocacao(){
    alocacao.sort([](Alocacao &a1, Alocacao &a2)
                  { return a1.horario < a2.horario; });
    for (auto &a : alocacao){
        std::cout << codigo << " " << nome << " ";
        a.imprimir_dados();
    }
}