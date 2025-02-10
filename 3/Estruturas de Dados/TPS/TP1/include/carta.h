#pragma once

struct carta_t {
    int valor; ///< Valor da carta. De 2 a 14, assumimos que o Às é a maior carta.
    char naipe; ///< Naipe da carta. 'C' para copas, 'P' para paus, 'E' para espadas, 'O' para ouros.
    bool operator <(const carta_t &other) const {
        return valor < other.valor;
    }
    bool operator >(const carta_t &other) const {
        return valor > other.valor;
    }
};
