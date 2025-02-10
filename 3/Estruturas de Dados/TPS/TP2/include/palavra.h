#pragma once

#include <string>

struct palavra_t {
    std::string palavra;
    int ocorrencias;
    palavra_t(const std::string& palavra) {
        for (auto ch : palavra) {
            this->palavra += tolower(ch);
        }
        ocorrencias = 1;
    }
    palavra_t() = default;
};
