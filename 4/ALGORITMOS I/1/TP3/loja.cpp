#include "loja.hpp"

#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        // multiply shift é melhor que apenas xor pra fazer o hash e evitar colisão
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second) << 16;
    }
};

size_t maior_sequencia_tapetes(const std::vector<int>& tapetes) {
    if (tapetes.empty()) {
        return {};
    }

    std::unordered_map<std::pair<int, int>, size_t, pair_hash> tabela;
    for (int tapete : tapetes) {
        auto copia = tabela; // já que vamos estar modificando a tabela, o iterador do loop pode mudar
        for (auto& [extremidades, tam] : copia) {
            auto [frente, tras] = extremidades;
            if (tapete > frente) {
                auto& entrada = tabela[{tapete, tras}];
                if (tam + 1 > entrada) {
                    entrada = tam + 1;
                }
            } else if (tras > tapete) {
                auto& entrada = tabela[{frente, tapete}];
                if (tam + 1 > entrada) {
                    entrada = tam + 1;
                }
            }
        }
        tabela[{tapete, tapete}] = 1;
    }

    return std::max_element(tabela.begin(), tabela.end(),
                            [](const auto& a, const auto& b) { return a.second < b.second; })
        ->second;
}