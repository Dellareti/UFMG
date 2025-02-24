#ifndef QUADROALOCACAO_HPP
#define QUADROALOCACAO_HPP

#include "Disciplina.hpp"

#include <map>
#include <vector>

struct QuadroAlocacao{
    std::map<std::string, Disciplina> quadro;
    QuadroAlocacao() = default;
    void inserir_alocacao(std::string codigo, std::string nome, std::string dia, std::string horario, std::string sala);
    void remover_alocacao_disciplina(std::string codigo, std::string horario);
    std::vector<Disciplina> recuperar_disciplinas_mais_ofertadas();
    void imprimir_alocacao_completa();
};

#endif