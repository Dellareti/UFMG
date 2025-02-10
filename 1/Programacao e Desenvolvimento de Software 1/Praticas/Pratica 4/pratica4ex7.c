#include <stdio.h>
#include <math.h>
#include "pratica4.h"

int main(){

float h;
char sexo;
float pesoAtual;

    printf("Digite sua altura em metros:\n");
    scanf("%f",&h);
    getchar();

    printf("Digite seu peso atual : ");
    scanf("%f",&pesoAtual);
    getchar();

    printf("Digite seu sexo (m ou M para masculino e f ou F para feminino)\n");
    scanf("%c",&sexo);
    getchar();

   float pesoBom = pesoIdeal(h,sexo);

    printf("Peso bom : %f \n",pesoBom);

    if(pesoBom > pesoAtual){
        float aux;
        aux = pesoBom - pesoAtual;
        printf("Voce precisa ganhar %f Kilos \n",aux);
    }

    else if(pesoAtual > pesoBom){
        float aux;
        aux = pesoAtual - pesoBom;
        printf("Voce precisa perder %f Kilos\n",aux);
    }
    
    else{
        printf("Voce esta no seu peso ideal\n");
    } 
    
    return 0;
}