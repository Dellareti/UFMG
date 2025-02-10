#pragma once

#include <alfabeto.h>

void quicksort(palavra_t* arr, int left, int right, Alfabeto* alfa, int tam_particao, int tam_mediana);

template <typename T> void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
