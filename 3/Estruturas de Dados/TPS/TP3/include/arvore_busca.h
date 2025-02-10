#pragma once

#include <string>

#include <mensagem.h>

struct no_bst {
    mensagem dado;
    struct no_bst* esq;
    struct no_bst* dir;
    ~no_bst() {}
};

class bst {
  private:
    no_bst* raiz;
    no_bst* min(no_bst* no);

  public:
    bst();
    ~bst();
    bool insere(mensagem dado);
    bool remove(int id);
    mensagem* encontra(int id);
};