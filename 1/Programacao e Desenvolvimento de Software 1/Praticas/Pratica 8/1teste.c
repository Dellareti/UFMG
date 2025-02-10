#include<stdio.h>
#include<stdlib.h>
#include"1.h"

#define TAM_MAX 100

int main(void){
    
    int k,m,n;
    int matriz[TAM_MAX][TAM_MAX];

    do{
        
    printf("Digite a quantidade de linhas da matriz \n");
    scanf("%d",&m);

    printf("Digite a quantidade de colunas da matriz \n");
    scanf("%d",&n);

    if (m < 0 || m > TAM_MAX || n < 0 || n > TAM_MAX){
        printf("Digite um valor de tamanho correto");
    }
} while (m < 0 || m > TAM_MAX || n < 0 || n > TAM_MAX);
    
    do{

    printf("Digite o valor limite para preencher a matriz (De 1 a k)\n");
    scanf("%d",&k);
    printf("\n");
    
    if (k<2){
        printf("Digite um valor inteiro maior que 1\n");
    }
} while (k<2);

    geraMatrizRandom(k,m,n);
    zeraConsecutivos(matriz,m,n);
    sobeZeros(matriz,m,n);

    return 0;
}