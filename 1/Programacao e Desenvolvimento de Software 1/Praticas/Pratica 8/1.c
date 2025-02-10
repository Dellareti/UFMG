#include<stdio.h>
#include<stdlib.h>
#include"1.h"

#define TAM_MAX 100

int geraMatrizRandom(int limite,int linhas,int colunas){
    int matriz[TAM_MAX][TAM_MAX];

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            do{
                matriz[i][j]=rand();
            } while (matriz[i][j] < 1 || matriz[i][j] > limite);

        }
        
    }
    // imprime matriz

    for (int i = 0; i < colunas ; i++){
        for (int j = 0; j < linhas; j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

void sobeZeros(int matriz[][TAM_MAX],int linhas,int colunas){
    int aux;
    for (int i = 0; i < linhas; i++){
        for ( j = 0; j < colunas; j++){
            if (matriz[i][j] ==0){
                for (int x = i-1; x >= 0; x--){
                    aux = matriz[x][j];
                    if (aux ==0)
                    break;

                    else{
                        matriz[x][j] = matriz [x+1][j];
                        matriz[x+1][j] = aux;
                    }
                    
                }
                
            }
            
        }
        
    }
    // imprime matriz

    for (int i = 0; i < colunas ; i++){
        for (int j = 0; j < linhas; j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}





int zeraConsecutivos(int matriz [TAM_MAX][TAM_MAX],int linhas,int colunas){
    
    int apos,anterior;
    int contZeros = 0;
    int matrizLinha[TAM_MAX][TAM_MAX],matrizColuna[TAM_MAX][TAM_MAX];


// == Linha ===

    for (int i = 0; i < linhas; i++){
        apos=0;
        anterior=-1;
        for (int j = 0; j < colunas; j++){
            matrizLinha[i][j] = matriz[i][j];
            if (j != colunas-1){
                if (matrizLinha[i][j] != anterior){
                    if (apos >=3)
                    for ( int k =apos; k > 0; k--){
                        matrizLinha[i][j-k] = 0;
                    }
                   apos = 1; 
                }
              else{
                   apos++; 
            } 
        } 

        else{
            if (matrizLinha[i][j] != anterior){
                 if (apos >= 3){
                    for ( int k =apos; k > 0; k--){
                        matrizLinha[i][j-k] = 0;
                    }
                }
                else if(apos >=2 ){
                    for ( int k =apos; k >= 0; k--){
                        matrizLinha[i][j-k] = 0;
                    }
                }
            }
            
            anterior = matriz[i][j];
        }
    }      
       
 }

// ======= Coluna ======

   for (int j = 0; j < colunas; j++){
        apos=0;
        anterior=-1;
        for (int i = 0; i < linhas; i++){
            matrizColuna[i][j] = matriz[i][j];
            if (i != colunas-1){
                if (matrizColuna[i][j] != anterior){
                    if (apos >=3)
                    for ( int k =apos; k > 0; k--){
                        matrizColuna[i-k][j] = 0;
                    }
                   apos = 1; 
                }
              else{
                   apos++; 
            } 
        } 

        else{
            if (matrizColuna[i][j] != anterior){
                 if (apos >= 3){
                    for ( int k =apos; k > 0; k--){
                        matrizColuna[i-k][j] = 0;
                    }
                }
                else if(apos >=2 ){
                    for ( int k =apos; k >= 0; k--){
                        matrizColuna[i-k][j] = 0;
                    }
                }
            }
            
            anterior = matriz[i][j];
        }
    }      
       
 }

// Linhas e colunas fusão 

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            if (matrizLinha == 0 || matrizColuna ==0){

                matriz[i][j] = 0;
                contZeros++;
            }
        }
    }
    
// impressão   
    printf("\nMatriz com consecutivos zerados\n\n");

    for(int i = 0; i < colunas ; i++){
            for (int j = 0; j < linhas; j++){
                printf("%d ",matriz[i][j]);
            }
            printf("\n");
        }
        printf("\n");

    printf("%d\n",contZeros);
 
}

