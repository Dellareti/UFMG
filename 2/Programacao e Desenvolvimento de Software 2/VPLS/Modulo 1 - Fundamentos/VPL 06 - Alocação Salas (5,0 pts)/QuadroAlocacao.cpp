#include "QuadroAlocacao.hpp"

#include <algorithm>
#include <string>
#include <utility>

void QuadroAlocacao::inserir_alocacao(std::string codigo, std::string nome, std::string dia, std::string horario, std::string sala){
    auto res = quadro.find(codigo);
    if (res == quadro.end()){
        quadro.insert(std::pair<std::string, Disciplina>(codigo, Disciplina(codigo, nome)));
    }
    quadro[codigo].inserir_alocacao(dia, horario, sala);
}

void QuadroAlocacao::remover_alocacao_disciplina(std::string codigo, std::string horario){
    quadro[codigo].remover_alocacao(horario);
}

std::vector<Disciplina> QuadroAlocacao::recuperar_disciplinas_mais_ofertadas(){
    size_t maior_oferta = quadro.begin()->second.alocacao.size();
    for(auto &d : quadro){
        if (d.second.alocacao.size() > maior_oferta){
            maior_oferta = d.second.alocacao.size();
        }
    }
    std::vector<Disciplina> disciplinas;
    for (auto &d : quadro){
        if(d.second.alocacao.size() == maior_oferta){
            disciplinas.push_back(d.second);
        }
    }
    return disciplinas;
}

void QuadroAlocacao::imprimir_alocacao_completa(){
    for (auto &d : quadro){
        d.second.imprimir_alocacao();
    }
}