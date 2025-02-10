#ifndef NAVE_C
#define NAVE_C

#include <iostream>
#include <cmath>
#include "Nave.hpp"

using namespace std;

Nave::Nave(Ponto2D posicao, double forca = 1.0) : _posicao(posicao), _forca(forca) {}

void Nave::mover(double dx, double dy){
    _posicao._x += dx;
    _posicao._y += dy;
}

double Nave::calcular_distancia(Nave *nave){
    return _posicao.calcular_distancia(&nave->_posicao);
}

Nave *Nave::determinar_nave_mais_proxima(Nave **naves, int n){
    Nave *nave_mais_proxima = nullptr;
    double menor_distancia = INFINITY;
    for (int i = 0; i < n; i++){
        double distancia = calcular_distancia(naves[i]);
        if (distancia > 0 && distancia < menor_distancia){
            menor_distancia = distancia;
            nave_mais_proxima = naves[i];
        }
    }
    return nave_mais_proxima;
}

void Nave::atacar(Nave **naves, int n){
    Nave *nave_mais_proxima = determinar_nave_mais_proxima(naves, n);
    if (nave_mais_proxima == nullptr){
        return;
    }
    double distancia = calcular_distancia(nave_mais_proxima);
    double dano = _forca * (100.0 / distancia);
    dano = dano > 30 ? 30 : dano;
    nave_mais_proxima->receber_dano(dano);
}

void Nave::receber_dano(double dano){
    _energia -= dano;
    if (_energia <= 50){
        cout << "Energia baixa!" << endl;
    }
}

void Nave::imprimir_status(){
    cout << _posicao._x << " " << _posicao._y << " " << _energia << endl;
}

#endif