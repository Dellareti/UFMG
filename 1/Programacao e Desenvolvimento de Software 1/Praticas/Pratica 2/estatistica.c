#include "estatistica.h"
#include <stdio.h>
#include <math.h>

float cauchy (float x){
    
    float pi = 3.141592;
    double resultado;
    resultado = 1 / (pi * (1 + pow(x, 2)));
    printf("O cauchy de %2.f e : %1f \n",x,resultado);
}

float gumbel (float x,float y,float b){
    float z;
    double resultado;
    z = (x-y)/b;
    resultado = 1 / b * exp(-(z+exp(-z)));
    printf("O Gumbel de x =%2.f,y =%2.f e b =%2.f e : %1f \n",x,y,b,resultado);

}

float laplace (float x,float y,float b){
    double resultado;
    resultado =1 / (2*b) * exp(-(fabs(x-y)/ b) ) ;
    printf("O calculo de Laplace de x =%2.f, y =%2.f e b =%2.f e : %1f \n",x,y,b,resultado);
}