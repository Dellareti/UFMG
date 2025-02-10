#include<stdio.h>

#define TAM_MAX 100

int main(void){

// Ex1 

double u[TAM_MAX], v[TAM_MAX];
double produto;

unsigned int n;

do{
    printf("Digite o tamanho dos vetores ate 100\n");
    scanf("%d",&n);

    if (n > TAM_MAX){
        printf("Tamanho invalido\n");
    }
} while (n > TAM_MAX);

    printf("Digite o tamanho do vetor u\n");
    for (int i = 0; i < n; i++){
        scanf("%lf",&u[i]);
    }
    
    printf("Digite o tamanho do vetor v\n");
    for (int i = 0; i < n; i++){
        scanf("%lf",&v[i]);
    }

    for (int i = 0; i < n; i++){
        produto+=(u[i]*v[i]);
    }
    
    printf("O produto escalar eh : %.2lf",produto);

 return 0;
}
