#pragma once

#include <palavra.h>

#include <string>

struct no {
    palavra_t* palavra = nullptr;
    no* proximo;
    ~no() { delete palavra; }
};

class Lista {
  private:
    no* primeiro;
    no* ultimo;
    int tamanho;

  public:
    Lista(/* args */);
    Lista(const std::string& linha);
    ~Lista();
    void insere(const std::string& palavra);
    void atualiza(const std::string& palavra);
    bool encontra(const palavra_t& palavra);
    palavra_t* to_array();
    int get_tamanho();
};
