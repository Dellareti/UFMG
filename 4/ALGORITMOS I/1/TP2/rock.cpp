#include "rock.hpp"
#include <float.h>

#include <algorithm>

struct resultado {
    int ini;
    int fim;
    double soma;

    bool operator<(const resultado& r) const {
        if (soma < r.soma)
            return true;
        return false;
    }
};

resultado max_crossing_sum(double array[], const int ini, const int meio, const int fim) {
    double soma_esq = -DBL_MAX;   // limite de double
    double soma_dir = -DBL_MAX;
    double soma = 0.0;
    int lim_esq = meio;
    int lim_dir = meio;

    for (int i = meio; i >= ini; i--) {
        soma += array[i];
        if (soma > soma_esq) {
            soma_esq = soma;
            lim_esq = i;
        }
    }
    soma = 0.0;
    for (int i = meio + 1; i <= fim; i++) {
        soma += array[i];
        if (soma > soma_dir) {
            soma_dir = soma;
            lim_dir = i;
        }
    }
    return {lim_esq, lim_dir, soma_esq + soma_dir};
}

resultado max_sub_array_sum(double array[], const int ini, const int fim) {
    if (ini > fim) {
        return {0, 0, 0.0};
    }
    if (ini == fim) {
        return {ini, fim, array[ini]};
    }
    const int meio = (ini + fim) / 2;
    resultado esquerda = max_sub_array_sum(array, ini, meio), direita = max_sub_array_sum(array, meio + 1, fim),
              todo = max_crossing_sum(array, ini, meio, fim);
    return std::max(todo, std::max(esquerda, direita));
}

std::string escolhe_melhores_shows(double notas[], const int shows) {
    resultado melhor = max_sub_array_sum(notas, 0, shows - 1);
    return std::to_string(melhor.ini + 1) + " " + std::to_string(melhor.fim + 1);
}