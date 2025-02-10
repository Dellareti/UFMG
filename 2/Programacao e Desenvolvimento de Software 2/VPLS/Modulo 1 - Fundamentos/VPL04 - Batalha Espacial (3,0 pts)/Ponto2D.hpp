#ifndef Ponto2D_H
#define Ponto2D_H

#include <iostream>
#include <cmath>

using namespace std;

struct Ponto2D
{
    double _x, _y;

    Ponto2D(double x = 0, double y = 0);
    double calcular_distancia(Ponto2D *p2);
};

#endif