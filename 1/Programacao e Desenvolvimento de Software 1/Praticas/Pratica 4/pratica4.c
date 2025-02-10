#include <stdio.h>
#include <math.h>
#include "pratica4.h"

float paraMetrosPorSegundo(float v){
    float aux;
    aux = v/3.6;
    printf("A velocidade em m/s e : %2.f ",aux);
}

float areaCirculo(float raio){
    float aux;
    float pi=3.141592;

    aux = pi * raio * raio;
    printf("A area do circulo e : %f",aux);

}

int maior3(int n1,int n2,int n3){
    int maior;

    if(n1 > n2){
    maior = n1;
}
      else{
      maior = n2;
}
     if(maior < n3){
     maior = n3;
 }
    printf("O maior numero e : %d",maior);
}

int ePar(int n ){
    if(n%2==0){
        printf("1");
    }
    else{
     printf("0");
    }
}

int ehDivisivelPor3ou5(int n){
    if (n%3==0 && n%5==0){
        printf("0");
    }
    else if(n%3==0 || n%5==0){
        printf("1");
    }
    else{
        printf("0");
    }
}

float pesoIdeal(float h,char sexo){
    
    if(sexo=='m' || sexo=='M'){
        float pi;
        pi=(72.7*h)-58;
        //printf("Seu peso ideal e : %f \n",pi);
        return pi;
 }

    else if(sexo=='f' || sexo=='F'){
        float pi2;
        pi2=(62.1*h)-44.7; 
       // printf("Seu peso ideal e : %f \n",pi2);
       return pi2;
    }
    else{
        //printf("Digite a letra correspondente ao sexo ");
        return 0;
    }
}

int somaImpares(int n){

int soma;
for (i = 0; i < n; i++){
    if (n%2 !=0){
    soma=soma+i;
    }
    return soma; 
  }
}

double fatorial(int n){
   int i;
   for(n = 1; i > 1; i--){
         n = n*i;
   }
  
return n;
} 

int somaNumerosDiv3ou5(int n){
    int soma;
    for (int i = 0; i < n; i++){
        if (ehDivisivelPor3ou5(n)){
            soma=soma+1;
        }
        
    }
    return soma;
}

float calculaMedia(int x,int y,int z,int operacao){
    switch (operacao){
   case -1:{
       printf("\n Digite uma opcao valida \n");
        break;
    }
    case 1:{
        float geometrica;
        geometrica = cbrt(x*y*z);
        printf("\n Media geometria e : %f \n",geometrica);    
        break;
    }

    case 2:{
        float ponderada;
        ponderada = ((x+2)*(y+3)*z)/6;
        printf("\n Media ponderada e : %f \n",ponderada);
        break; 
    }
 case 3:{
        float harmonica;
        harmonica = 3/((1/x+1)/((y+1)/z));
        break; 
    }
 case 4:{
        float aritimetica;
        aritimetica = (x+y+z)/3;
        printf(" \n Media aritimetica e : %f",aritimetica);
        break; 
    }
    default:
        break;
    }

}

int numerosDivisores(int n){
    for (int i = 1; i <= n; ++i) {
        if (n%i==0) {
            printf(" %d , ", i);
        }
    } 
return 0;


}

int enesimoFibonacci(int n){ 

   int i,seq;
   int  primeiroN = 0;
   int  segundoN  = 1;
 
   if(n>2) {
 
    printf("\n\n\n1:\n\n");
      for(i=0;i<n;i++){
 
    seq = primeiroN + segundoN;
    segundoN = primeiroN;
    primeiroN = seq;
    printf("\n\n%d\n\n",seq);

}

int mdc(unsigned int x,unsigned int y){
    int resto;

    do {
        resto = x % y;

        x = y;
        y = resto;

    } while (resto != 0);

    return num1;
 }
}

int mmc(unsigned int x,unsigned int y){
    
    int mmc, aux, i;

    for (i = 2; i <= y; i++) {
        aux = x * i;
        if ((aux % y) == 0) {
            mmc = aux;
            i = y + 1;
        }
    }
    return mmc;
}

int mdcEmmc(unsigned int x,unsigned int y){

    int a, b, temp, mdc, mmc; 
 
	a = x; 
	b = y; 
	
    while (x < 0 && y < 0 ){
    while (b != 0) { 
	temp = x; 
	x = y; 
	y = temp%y; 
} 
	mdc = a; 
	mmc = (x * y)/a; 
	
	printf("\n\n O MDC de %d e %d e : %d \n\n", x, y, mdc); 
	printf("\n\n O MMC de %d e %d e : %d\n\n", x, y, mmc); 
 }
    	

return 0;
}