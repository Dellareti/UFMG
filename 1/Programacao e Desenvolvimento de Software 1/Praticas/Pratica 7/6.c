#include<stdio.h>
#include<stdlib.h>

#define TAM_VETOR 60

int main(void){

    int x[TAM_VETOR],y[TAM_VETOR],u[2*TAM_VETOR];
    int tam_atual=0;
    int certo,numero;

    for (int i = 0; i < TAM_VETOR; i++){
        do{
            x[i]=rand();
        } while (x[i] < 0 || x[i] > 365);
        do{
           y[i]=rand();
        } while (y[i] < 0 || y[i] > 365);
    }
    
    for (int i = 0; i < TAM_VETOR; i++){
       numero = x[i];
       certo =0;
       for (int j = 0; j < tam_atual; j++){
           if (numero = u[j]){
               certo =1;
               break;
           }
       }
       
            if (!certo){
            u[tam_atual] = numero;
            tam_atual++;
         }       
       }
    
    printf("\n Vetor unitario \n");
    for ( int i = 0; i < tam_atual; i++){
        printf("u[%d] = %d\n",i,u[i]);
    }
    
    return 0;
}