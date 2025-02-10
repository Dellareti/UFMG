#include <alfabeto.h>
#include <log.h>

#include <iostream>
#include <sstream>

Alfabeto::Alfabeto(const std::string& linha) {
    std::stringstream ss(linha);
    for (int posicao = 0; posicao < 26; posicao++) {
        char ch;
        ss >> ch;
        int letra = toupper(ch) - 'A';
        if (letra < 0 || letra >= 26) {
            throw std::invalid_argument("Alfabeto inválido");
        }
        escrita(alfabeto, letra, 0) = posicao;
    }
}

int Alfabeto::indice(const char letra) {
    char maiuscula = toupper(letra);
    if (maiuscula < 'A' || maiuscula > 'Z') {
        return static_cast<int>(maiuscula) - 'A';
    }
    return leitura(alfabeto, maiuscula - 'A', 0);
}

int Alfabeto::cmp(const palavra_t& a, const palavra_t& b) {
    int i = 0;
    while (i < a.palavra.size() && i < b.palavra.size()) {
        int indice_a = indice(a.palavra[i]);
        int indice_b = indice(b.palavra[i]);
        if (indice_a != indice_b) {
            return indice_a - indice_b;
        }
        i++;
    }
    return a.palavra.size() - b.palavra.size();
}