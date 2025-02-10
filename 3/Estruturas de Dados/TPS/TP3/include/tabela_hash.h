#pragma once

#include <arvore_busca.h>

class hash_table {
  public:
    hash_table(int tam);
    ~hash_table();
    bool insere(int chave, mensagem dado);
    bool remove(int chave, int id);
    mensagem* encontra(int chave, int id);
    int hash(int chave);

  private:
    int tam;
    bst** tabela;
};
