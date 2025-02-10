#ifndef NAVE_H
#define NAVE_H

#include "Ponto2D.hpp"

struct Nave
{

private:
    Ponto2D _posicao;
    double _forca, _energia = 100;
    void receber_dano(double dano);

public:
    Nave(Ponto2D posicao, double forca);
    void mover(double dx, double dy);
    double calcular_distancia(Nave *nave);
    Nave *determinar_nave_mais_proxima(Nave **naves, int n);
    void atacar(Nave **naves, int n);
    void imprimir_status();
};

#endif