#pragma once

#include <palavra.h>
#include <string>

class Alfabeto {

  private:
    int alfabeto[26];

  public:
    Alfabeto(const std::string& linha);
    ~Alfabeto() = default;
    int indice(char letra);
    int cmp(const palavra_t& a, const palavra_t& b);
};