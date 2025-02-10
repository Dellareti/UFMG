#include<stdio.h>

int main(void){
int x[10],y[10],z[20];
int contX =0,contY=0;

    printf("Digite os 10 valores do vetor x\n");
    for (int i = 0; i < 10; i++){
        scanf("%d",&x[i]);
    }

    printf("Digite os 10 valores do vetor y\n");
    for (int i = 0; i < 10; i++){
        scanf("%d",&y[i]);
    }
    
    for (int i = 0; i < 20; i++){
        if (i%2 ==0){
          z[i]=x[contX];
          contX++;
        }
        else{
          z[i]=y[contY];  
          contY++;
        }
    }
    
    for (int i = 0; i < 20; i++){
        printf("z[%d] = %d\n",i,z[i]);
    }
    


    return 0;
}