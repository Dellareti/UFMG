#pragma once

/**
 *  Troca o valor de duas variáveis.
 * 
 * T 
 *  a 
 *  b 
 */
template <class T>
void troca(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

/**
 *  Insertion sort padrão com ordenação decrescente.
 *        Custo: O(n^2).
 * 
 *  T 
 *  arr o vetor a ser ordenado.
 *  n o número de elementos no vetor.
 */
template <class T>
void insertion_sort(T arr[], const int n){
    for (int i = 1; i < n; i++){
        int j = i;
        while (j > 0 && arr[j - 1] < arr[j]){
            troca(arr[j - 1], arr[j]);
            j--;
        }
    }
}
