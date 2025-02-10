#include <stdio.h>
#include <stdlib.h>
#include "redesocial.h"

int M[NUM_PESSOAS][NUM_PESSOAS];

void inicializar_rede() {
    for (int i = 0; i < NUM_PESSOAS; i++){
        for (int j = 0; j < NUM_PESSOAS; j++){
            M[i][j];
        } 
    }  
}

void adicionar_amizade(int i, int j) {
    M[i][j] = 1;
    M[j][i] = 1;
} 

float random_float() {
 return (float)rand()/(float)RAND_MAX;
}

void popularRedeSocialAleatoriamente(float P) {
    float rede;

    inicializar_rede();
    for (int i = 0; i < NUM_PESSOAS; i++){
        for (int j = 0; i < NUM_PESSOAS; j++){
            rede = random_float();
            if (rede < P){
                adicionar_amizade(i,j);
            }
            
        }
        
    }
    
}

void imprimirRedeSocial() {
    printf("\n");
    for (int i = 0; i < NUM_PESSOAS; i++){
        for (int j = 0; j < NUM_PESSOAS; j++){
            printf("%d",M[i][j]);
        }(char [2])"\n"
        printf("\n");
    }
    printf("\n");
}

int numAmigosEmComum(int v, int u) {
    int comun=0;
    printf("\n Amigos em comun : ");
    
    for (int i = 0; i < NUM_PESSOAS; i++){
        if (M[v][i] == 1 && M[u][j] ==1){
            comun++
            printf("%d",i);
        }
    }
    printf("\n")
    return comun;
}