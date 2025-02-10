#pragma once

#include <memlog.h>

template <typename T> T leitura(T* x, size_t indice, int id) {
    leMemLog((long int)&x[indice], sizeof(T), id);
    return x[indice];
}

template <typename T> T& escrita(T* x, size_t indice, int id) {
    escreveMemLog((long int)&x[indice], sizeof(T), id);
    return x[indice];
}
