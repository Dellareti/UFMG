#include <stdlib.h>
#include <math.h>

// 1
float parteInteira(float x){
    int inteiro;
    inteiro = (int)x;
    return inteiro;    
}

float parteFracionaria(float x){
    float fracionario;
    fracionario = x -(int)x;
    return fracionario;
}

float divInts(int x,int y){
    float div;
    div = (float)x / (float)y;
    return div;
}
// 2
void soma1(int *x){
    (*x)++;
}

// 4
void troca(float *end_valor1,float *end_valor2){
    float a = *end_valor1;
    *end_valor1 = *end_valor2;
    *end_valor2 = a;
}

// 5
unsigned long long fast_pow_2 (int expoente){
        int unsigned long long a = 1;
        return a<<expoente;
}

// 6 
int ddd(unsigned int number){
    return number / pow(10,8);

}

unsigned int soma1SePar(unsigned int number){
    return number | (unsigned int )1;
}

unsigned int parOuImpar (unsigned int number){
    return !(number & (unsigned int )1);

}