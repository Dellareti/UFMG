#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


typedef struct Xis {
    int linha, coluna, tam;
} Xis;


typedef struct Ponto {
    float x, y;
} Ponto;


typedef struct Circulo {
    Ponto centro;
    float raio;
} Circulo;

typedef struct Triangulo {
    Ponto sup, base_esq, base_dir;
} Triangulo;


#define MAX_TAM 100

//1)

void matrizIdentidade(int M[][MAX_TAM], int n) {
    
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j){
                M[i][j]=1;    
            }
            else{
                M[i][j]=0;
            }
        }
    }
}


//2)

int insereXis(int M[][MAX_TAM], int n, Xis x) {
    
    int i,j,k;
    float tam;
    
   if(n<=0 || n>MAX_TAM){
      return 0; 
   }
   
    tam = x.tam;

    k = (tam-1)/2;
    
    for(i=x.linha; i<x.linha + x.tam; i++){
        for(j=x.coluna; j<x.coluna + x.tam; j++){
            if(i-x.linha==j-x.coluna ||(i-x.linha)+(j-x.coluna)==x.tam-1){
                M[i-k][j-k]=1;    
            }
          else{
                M[i-k][j-k]=0;
            }
        }
    }
    
    
    return 1; 
}

//3)

Xis maiorXis(int M[][MAX_TAM], int n, int i, int j) {
    
    Xis x;
    int a,b,c=0,e=0,tamMin=30,tam[4]={0};
    
    if(M[i][j]>0){
        for( a = -1; a<=1; a++){
           for( b = -1 ; b<=1;b++){
            if(M[i+a][j+b]>0){
                
               for(c=0;c<(n-i);c++){

                if(M[i+a*(1+c)][j+b*(1+c)]>0){
                    tam[e]=tam[e]+1;
                    
                    if(tam[e]<tamMin){
                      tamMin=tam[e];
                        
                    }
                 
                }    
            }
                c=0;
                e++;
                      
        }
           
            
    }
           
}
       if(e==5){
            x.linha = i;
              x.coluna = j;
              x.tam = 2*tamMin+1;
            }
        else{
            x.linha = i;
            x.coluna = j;
            x.tam = 1;
            
        }
    
     }
     else{
        x.linha = 0;
        x.coluna = 0;
        x.tam = 0;
         
     }  
    
    return x;
}

//4)

int lerXis(Xis *x, int n) {
    
    Xis y;
    *x = y;
    int aux =0;
    int c = 1;
    
    do{
     
    scanf("%d",&y.linha); 
    scanf("%d",&y.coluna);
    scanf("%d",&y.tam);
    
    if(y.linha < 0 || y.coluna < 0 || y.linha +y.tam > n || y.coluna +y.tam >n){
        c++;
    }
    else{
        aux=1;
    }
    
    }while(aux==0);
    
    *x = y;
    
    //printf("%d",c);
    
    return c;
}

//5) 

int numCharsRepetidos(char str[]) {
    
    int cont[256];
    int i;
    
    for(i=0;i<256;i++){
        cont[i]=0;
    }
    i=0;
    
    while(str[i] != '\0'){
        if(toupper(str[i])>=65 && toupper(str[i])<=90){
            cont[toupper(str[i])]++;
          }
          i++;
    }

    int n;
    for(i=0;i<=126;i++){
        
           n+= (cont[i] >1);
               
         }
        
    return n;
}

// 6

int estaContidoCirculoTriangulo(Circulo cir, Triangulo tri) {
   
    float a,b,c;

   a = sqrt(pow(cir.centro.x - tri.base_dir.x,2)+pow(cir.centro.y - tri.base_dir.y,2));
   b = sqrt(pow(cir.centro.x - tri.base_esq.x,2)+pow(cir.centro.y - tri.base_esq.y,2));
   c = sqrt(pow(cir.centro.x - tri.sup.x,2)+pow(cir.centro.y - tri.sup.y,2));



   if(a>=cir.raio || b>=cir.raio || c >=cir.raio){   
        return 0;
    }
    else{ 
        return 1;
    }
 }

// 0

void minha_main() {
    //Voce pode simular uma funcao main nesta funcao. Use-a para testar o que quiser. 
    //Para isso, execute a sua prova e entre com o exercicio 0.
    //Isso fara com que esta funcao (minha_main) seja chamada pelo VPL.
    //Importante: esta funcao NAO sera avaliada!!! No entanto, erros de compilacao nesta funcao invalidam (nota 0!) TODA a prova!
    
    printf("\nPor enquanto nao estou fazendo nada :(");
    
}





