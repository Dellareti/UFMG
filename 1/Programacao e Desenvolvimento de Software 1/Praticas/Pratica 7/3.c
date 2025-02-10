#include<stdio.h>
#include<stdlib.h>

#define TAM_MAX 100

double mediaVetor(int vetor[],int n){
    double soma;
    int i;
    for ( i = 0; i < n; i++){
        soma+= vetor[i];
    }
    return soma/(double)n;    
}

void preecheVetor(int *vetor,int n ){
    for (int i = 0; i < n; i++){
    vetor[i]=rand();
    }
}

int main(void){

    int vetor[TAM_MAX];
    double media;
    int n;

    do{
    printf("Digite o tamanho do vetor ate 100 \n");
    scanf("%d",&n);

        if (n <0 || n > TAM_MAX){
            printf("Tamanho invalido\n");
        }

    } while (n <0 || n > TAM_MAX);

    preecheVetor(vetor,n);
    media=mediaVetor(vetor,n);

    // printf("%d\n",vetor[0]);
    // printf("%d\n",vetor[1]);
    // printf("%d\n",vetor[2]);
    // printf("%d\n",vetor[3]);

    printf("A media do vetor eh : %2.lf",media);

    return 0;
}