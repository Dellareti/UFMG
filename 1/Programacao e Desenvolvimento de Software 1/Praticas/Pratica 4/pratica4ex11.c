#include <stdio.h>
#include <math.h>
#include "pratica4.h"

int main(){

int opcao;
int x,y,z;

    while (opcao!=-1 ){
    
    printf(" \n Digite sua opcao \n 1 - Geometrica \n 2 - Ponderada \n 3 - Harmonica \n 4 - Aritimetica \n -1 - Sair \n");
    scanf("%d",&opcao);

    if (opcao !=-1 ){
        printf("Digite o valor x \n");
        scanf("%d",&x);

        printf("Digite o valor y \n");
        scanf("%d",&y);

        printf("Digite o valor z \n");
        scanf("%d",&z);

        printf("%d",x);
        calculaMedia(x,y,z,opcao);

    } 
    
    if (opcao > 4 && opcao<1){
        printf("\n Digite uma opcao valida");
    }
    
}

    return 0;
}