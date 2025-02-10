#include<stdio.h>
#include "selection.h"

int main(){

    int num_cartela = 1;
    int cartela_atual[6];
    int cartela_venc[6] = {6,9,22,23,48,52};
    int cartela_lost[6] = {4,8,15,16,23,42};
   
    FILE *arq, *arq_aux;
    arq = fopen("cartelas.txt","r");
    arq = fopen("auxiliar.txt","w");

    while (feof(arq) == 0){

     int cont;
       fprintf(arq_aux,"Ordenada: ");
       for (int i = 0; i < 6; i++){   
            fscanf(arq,"%d ",&cartela_atual[i]);
            ordenar_por_selecao(cartela_atual,6);
       }
         for (int i = 0; i < 6; i++){   
            fprintf(arq_aux,"%d",cartela_atual[i]);
            fprintf(arq_aux,"\n");
       }

       for (int cont = 0; cont < 6; cont++){
           if (cartela_atual[cont] != cartela_venc[cont]){
               break;
           }
           
       }
       if (cont ==6){
           printf("\n A cartela %d e vencedora.", num_cartela);
           num_cartela++;
       }   

    }
    

    fclose(arq);
    fclose(arq_aux);
    return 0;
}