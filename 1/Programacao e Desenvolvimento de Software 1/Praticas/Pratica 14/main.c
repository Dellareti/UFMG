#include<stdio.h>
#include<stdlib.h>

int main(){

    int a[2] = {5,6}

    printf("\nSoma de cubos %d\n",somaCubos(3));
    printf("Imprimir numeros naturais : %d\n", imprimeNaturais(3));
    printf("Imprime naturais em ordem decrescente : %d\n", imprimeNaturaisDecrescente(3));
    printf("Somar elementos de um vetor %d\n",somaElementosVetor(a,2));
    printf("Media elementos  %d\n",mediaElementosVetor(a,0,2));
    printf("x elevado a y %d\n", potencia(2,3));
    printf("String invertida ");
    stringInvertida("Hello World\n");

    int resultado = 0;
    printf("Numero invertido %d\n",inverteNumeroInteiro(123),&resultado);
    printf("Decimal para binario : ");
    decimalParaBinario(5);
    printf("\n");
    printf("Menor elemento de a: %d\n",menorElementoVetor(a,2));

    return 0;
}