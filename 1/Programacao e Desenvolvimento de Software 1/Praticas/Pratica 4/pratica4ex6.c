#include <stdio.h>
#include <math.h>
#include "pratica4.h"

int main(){
    
float h;
char sexo;

    printf("Digite sua altura :\n");
    scanf("%f",&h);
    getchar();

    printf("Digite seu sexo (m ou M para masculino e f ou F para feminino)\n");
    scanf("%c",&sexo);
    getchar();

    pesoIdeal(h,sexo);
    
    return 0;
}