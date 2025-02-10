#include <log.h>
#include <sort.h>

static void insertion_sort(palavra_t* arr, int esq, int dir, Alfabeto* alfa) {
    for (int i = esq + 1; i <= dir; i++) {
        auto key = leitura(arr, i, 1);
        int j;
        for (j = i - 1; j >= esq && alfa->cmp(key.palavra, leitura(arr, j, 1).palavra) < 0; j--) {
            escrita(arr, j + 1, 1) = leitura(arr, j, 1);
        }
        escrita(arr, j + 1, 1) = key;
    }
}
static int escolhe_pivot(palavra_t* arr, int esq, int dir, int tam_mediana, Alfabeto* alfa) {
    int diff = dir - esq;
    if (diff < tam_mediana) {
        return esq;
    }
    palavra_t candidatos[tam_mediana];
    for (int i = 0; i < tam_mediana; i++) {
        escrita(candidatos, i, 2) = leitura(arr, esq + i, 1);
    }
    insertion_sort(candidatos, 0, tam_mediana - 1, alfa);
    for (int i = 0; i < tam_mediana; i++) {
        if (leitura(arr, esq + i, 1).palavra == leitura(candidatos, tam_mediana / 2, 2).palavra) {
            return esq + i;
        }
    }
    return esq;
}

static int partition(palavra_t* arr, int esq, int dir, Alfabeto* alfa, int tam_mediana) {
    int pivot = escolhe_pivot(arr, esq, dir, tam_mediana, alfa);
    int i = esq;
    int j = dir;
    while (i <= j) {
        if (alfa->cmp(leitura(arr, i, 1).palavra, leitura(arr, pivot, 1).palavra) <= 0) {
            i++;
        } else if (alfa->cmp(leitura(arr, j, 1).palavra, leitura(arr, pivot, 1).palavra) > 0) {
            j--;
        } else {
            leitura(arr, i, 1);
            leitura(arr, j, 1);
            escrita(arr, i, 1);
            escrita(arr, j, 1);
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    leitura(arr, pivot, 1);
    leitura(arr, j, 1);
    escrita(arr, pivot, 1);
    escrita(arr, j, 1);
    swap(arr[pivot], arr[j]);
    return j;
}

void quicksort(palavra_t* arr, int esq, int dir, Alfabeto* alfa, int tam_particao, int tam_mediana) {
    if (esq < dir) {
        int diff = dir - esq;
        if (diff <= tam_particao) {
            insertion_sort(arr, esq, dir, alfa);
            return;
        }
        int pivot = partition(arr, esq, dir, alfa, tam_mediana);
        quicksort(arr, esq, pivot - 1, alfa, tam_particao, tam_mediana);
        quicksort(arr, pivot + 1, dir, alfa, tam_particao, tam_mediana);
    }
}