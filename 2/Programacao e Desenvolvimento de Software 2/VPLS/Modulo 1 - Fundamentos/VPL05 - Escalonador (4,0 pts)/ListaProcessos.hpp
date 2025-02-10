#ifndef LISTA_PROCESSOS_HPP
#define LISTA_PROCESSOS_HPP

#include "Processo.hpp"

struct no{
    no(Processo *p) : processo(p) {}
    Processo *processo = nullptr;
    no *prox = nullptr;
};

struct ListaProcessos{
private:
    no *inicio = nullptr;

public:
    ListaProcessos() = default;
    void adicionar_processo(Processo *proc);
    Processo *remover_processo_maior_prioridade();
    Processo *remover_processo_menor_prioridade();
    Processo *remover_processo_por_id(int id);
    void imprimir_lista();
};

#endif