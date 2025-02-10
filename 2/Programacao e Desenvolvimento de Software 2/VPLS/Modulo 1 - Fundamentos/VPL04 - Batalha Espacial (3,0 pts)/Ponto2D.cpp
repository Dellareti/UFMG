#include <iostream>
#include <cmath>
#include "Ponto2D.hpp"

using namespace std;

Ponto2D::Ponto2D(double x, double y) : _x(x), _y(y) {}

double Ponto2D::calcular_distancia(Ponto2D *p2)
{
    double dx = p2->_x - _x;
    double dy = p2->_y - _y;
    return sqrt(dx * dx + dy * dy);
}