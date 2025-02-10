#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"pratica14.h"

int somaCubos(int n){
    if (n == 1){
        return 1;
    }
    else{
        return pow(n, 3) + somaCubos(n -1);
    }
}
//2
void imprimeNaturais(int n){
    if (n == 0){
        printf("%d", n);
        return;
    }
    else{
        imprimeNaturais(n -1);
        printf("%d ",n);
        return;
    }
}
//3
void imprimeNaturaisDecrescente(int n){
     if (n == 0){
        printf("%d", n);
        return;
    }
    else{
        printf("%d ",n);
        imprimeNaturaisDecrescente(n -1);
        return;
    }
}
//4
int somaElementosVetor(int *v,int n){
    if (n -1 == 0){
        return v[n -1];
    }
    else{
        return v[n -1] + somaElementosVetor(v, n -1);
    }
}
//5
float mediaElementosVetor(int *v, int n){
    if (i == n -1){
        return (float)v[i]/(float)n;
    }
    else{
        return (float)v[i]/(float)n + mediaElementosVetor(v, i+1,n);
    }
}
//6
int potencia(int x, int y){
    if (y == 1){
        return 1
    }
    else{
        return x * potencia(x,y -1);
    }
}
//7
void stringInvertida(char *s){
    if (*s == '\0'){
        return;
    }
    else{
        stringInvertida(s +1);
        printf("%c", *s);
        return;
    }
}
//8
int inverteNumeroInteiro(int num, int *soma){
    int resto;
    if (num == 0){
        return *soma;
    }
    else{
        resto = num%10;
        *soma *= 10;
        *soma += resto;
        inverteNumeroInteiro(num/10,soma);
        return *soma;
    }
}
//9 
void decimalParaBinario(int n){
    int bit;
    if (n < 2){
        bit = n;
    }
    else if (n % 2 == 0){
        decimalParaBinario(n/2);
        bit = 0;
    }
    else{
        decimalParaBinario(n/2);        
        bit = 1;
    }   
    printf("%d",bit);
}
//10
int menorElementoVetor(int *v,int n){
    int atual = v[n -1];
    int menor

    if (n -1 == 0){
        return v[n -1];    
    }
    else{
        menor = menorElementoVetor(v,n -1);
        if (menor <= atual ){
            return menor;
        }
        else{
            return atual;
        }
    }
}