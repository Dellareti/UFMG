#include "ListaProcessos.hpp"

void ListaProcessos::adicionar_processo(Processo *proc){
    struct no *novo = new struct no(proc);
    if (inicio == nullptr || inicio->processo->_prioridade < novo->processo->_prioridade){
        novo->prox = inicio;
        inicio = novo;
    }
    else{
        struct no *aux = inicio;
        while (aux->prox != nullptr && aux->prox->processo->_prioridade >= novo->processo->_prioridade){
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
    }
}

Processo *ListaProcessos::remover_processo_maior_prioridade(){
    if (inicio == nullptr){
        return nullptr;
    }
    
    struct no *aux = inicio;
    inicio = inicio->prox;
    Processo *proc = aux->processo;
    delete aux;
    return proc;
}

Processo *ListaProcessos::remover_processo_menor_prioridade(){
    if (inicio == nullptr){
        return nullptr;
    }
    struct no *aux = inicio, *ant = nullptr;
    while (aux->prox != nullptr){
        ant = aux;
        aux = aux->prox;
    }
    ant->prox = nullptr;
    Processo *proc = aux->processo;
    delete aux;
    return proc;
}

Processo *ListaProcessos::remover_processo_por_id(int id){
    if (inicio == nullptr){
        return nullptr;
    }
    struct no *aux = inicio, *ant = nullptr;
    while (aux->prox != nullptr && aux->processo->_id != id){
        ant = aux;
        aux = aux->prox;
    }
    if (aux->processo->_id == id){
        if (ant == nullptr){
            inicio = aux->prox;
        }
        
        else{
            ant->prox = aux->prox;
        }
        
        Processo *proc = aux->processo;
        delete aux;
        return proc;
    }
    return nullptr;
}

void ListaProcessos::imprimir_lista(){
    struct no *aux = inicio;
    while (aux != nullptr){
        aux->processo->imprimir_dados();
        aux = aux->prox;
    }
}