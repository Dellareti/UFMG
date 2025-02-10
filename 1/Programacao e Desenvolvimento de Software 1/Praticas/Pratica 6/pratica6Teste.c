#include <stdio.h>
#include <string.h> 
#include <conio.h>
#include <stdlib.h>
#include "pratica6.h"

int main (void){
    
    // Ex 1
    int n;
    printf("Digite o termo do numero de euler");
    scanf("%d",&n);
    exercicio(n);

    // Ex 2 
    int nota;
    printf("Digite sua nota : ");
    scanf("%d",&nota);
    exercicio2(nota);

    // Ex 3
    int n;
    printf("Digite o numero de linhas do triangulo de floyd\n\n");
    scanf("%d",&n);
    exercicio3(n);

    // Ex 4
    char string[128];
    printf("Digite seu texto : ");
    fgets(string,128,stdin);
    exercicio4(string);

    // Ex 5
    char string1[128];
    printf("Digite seu texto : ");
    fgets(string1,128,stdin);
    exercicio5(string1);

    // Ex 6
    char string2[128];
    printf("Digite um texto: \n");
    gets(string2);
    exercicio6(string2);

    // Ex 7
    char string3[128];
    printf("Digite um texto: \n");
    gets(string3);
    exercicio7(string3);

    // Ex 8
    char string4[128];
    printf(" Nome terminado em ponto final \n");
    gets(string4);
    exercicio8(string4);

    return 0;
}