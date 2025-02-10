#include<stdio.h>

#define TAM_MAX 1000

int main(void){

int x[TAM_MAX],y[TAM_MAX];
int n;

    do{
     
    printf("Digite o tamanho do vetor ate 100 \n");
    scanf("%d",&n);

        if (n <0 || n > TAM_MAX){
            printf("Tamanho invalido\n");
        }

    } while (n <0 || n > TAM_MAX);

    printf("Digite os elementos do vetor\n");
    for (int i = 0; i < n; i++){
        scanf("%d",&x[i]);
    }
    
    for (int i = 0; i < n; i++){
        y[i]= x[n-1-i];
    }

    // printf
    for (int i = 0; i < n; i++){
      printf("y[%d] = %d\n",i,y[i]);
    }

    return 0;
}