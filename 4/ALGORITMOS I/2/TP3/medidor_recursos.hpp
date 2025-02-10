#ifndef MEDIDOR_RECURSOS_HPP
#define MEDIDOR_RECURSOS_HPP

#include <chrono>
#include <sys/resource.h>

class MedidorRecursos {
private:
    std::chrono::high_resolution_clock::time_point inicio;
    std::chrono::high_resolution_clock::time_point fim;
    rusage uso_recursos_inicio;
    rusage uso_recursos_fim;

public:
    void iniciar() {
        inicio = std::chrono::high_resolution_clock::now();
        getrusage(RUSAGE_SELF, &uso_recursos_inicio);
    }

    void parar() {
        fim = std::chrono::high_resolution_clock::now();
        getrusage(RUSAGE_SELF, &uso_recursos_fim);
    }

    // Retorna o tempo em milissegundos
    long obter_tempo() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count();
    }

    // Retorna o uso de memória em kilobytes
    long obter_memoria() {
        return uso_recursos_fim.ru_maxrss - uso_recursos_inicio.ru_maxrss;
    }
};

#endif