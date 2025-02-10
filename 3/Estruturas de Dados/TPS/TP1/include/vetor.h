#pragma once

#include "../include/vetor.h"
#include "../include/memlog.h"

template <class T>
class Vetor{
private:
    int tam;
    int id;
    T *dados;

public:
    Vetor(int tam, int id) : tam(tam), id(id), dados(new T[tam]){
        defineFaseMemLog(0);
    }

    Vetor(const Vetor<T> &v) : tam(v.tam), id(v.id), dados(new T[tam]){
        defineFaseMemLog(0);
        for (int i = 0; i < v.tam; i++){
            leMemLog((long int)v.dados + i * sizeof(T), sizeof(T), id);
            escreveMemLog((long int)dados + i * sizeof(T), sizeof(T), id);
            dados[i] = v.dados[i];
        }
    }

    ~Vetor(){
        defineFaseMemLog(2);
        for (int i = 0; i < tam; i++){
            leMemLog((long int)dados + i * sizeof(T), sizeof(T), id);
            dados[i].~T();
        }
    }

    T operator[](int i) const{
        defineFaseMemLog(1);
        leMemLog((long int)dados + i * sizeof(T), sizeof(T), id);
        return dados[i];
    }

    T &operator[](int i){
        defineFaseMemLog(1);
        escreveMemLog((long int)dados + i * sizeof(T), sizeof(T), id);
        return dados[i];
    }

    void sort(){
        insertion_sort(dados, tam);
    }
};