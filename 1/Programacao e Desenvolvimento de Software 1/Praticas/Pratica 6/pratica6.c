#include <stdio.h>
#include <string.h> 
#include <conio.h>
#include <stdlib.h>
#include "pratica6.h"

int exercicio(int n){
double i,j; 
double fat;
double e = 1.0;

for (i = 0; i<=n; i++){
    fat =1.0;
    for (j=2; j <= i; j++){
        fat = fat*j;
    }
    e = e + (1.0/fat);
}
    printf("E = %.5lf\n",e);  
    return 0;
}

int exercicio2(int nota){

 switch (nota){
   case 1:
   case 2:
   case 3:
   case 4:{
       printf("\n Conceito : F \n");
        break;
    }
    case 5:{ 
        printf("\n Conceito : D  \n");    
        break;
    }

    case 6:{
        printf("\n Conceito : D  \n");
        break; 
    }
    case 7:{ 
        printf("\n Conceito : C  \n");
        break; 
    }
    case 8:{
        printf(" \n Conceito : B \n");
        break; 
    }
    case 9: 
    case 10:{
        printf(" \n Conceito : A \n");
        break; 
    }
    default:{
        printf("\nDigite uma opcao valida\n");
    }  
  }
  return 0;
}

int exercicio3(int n){
 int i,j;
    int n_linhas = 0;

    for (i = 1; i <= n; i++){
        for (j = 1; j <= i; j++){
        n_linhas++;
        printf("%d ",n_linhas);
       }
        printf("\n");
    }
    return 0;
}

void exercicio4(char string[]){

    int numeroCaracteres = 0;
    while (string[numeroCaracteres] != '\0'){
        numeroCaracteres++;
    }
    printf("Numero de letras e espacos eh : %d\n",numeroCaracteres-1);
    printf("Numero de caracteres eh : %d\n",numeroCaracteres);
}

void exercicio5(char string[]){
    printf("Convertendo para maiusculas : %s\n",strupr(string));
}

void exercicio6(char string[]){

    char inverso[128];
    int i;
    int f =0;
   
  for (i=strlen(string)-1; i >=0; i--){
      inverso[f] = string[i];
      f++;
  }     
 
    inverso[f] = '\0';
   
  if(strcmp(string,inverso)==0){
    printf("Eh palindromo\n");
  }
   
  else{
    printf("Nao eh palindromo\n");
  }
}

void exercicio7(char string[]){

char inverso[128];
    int i;
    int f =0;
   
  for (i=strlen(string)-1; i >=0; i--){
      inverso[f] = string[i];
      f++;
  }     
 
    inverso[f] = '\0';
    printf("O inverso e : %s \n",inverso);
}

void exercicio8(char caractere[]){
   printf(" Nome terminado em ponto final \n");
    do{
       caractere = getc(stdin);
       if (caractere >= 65 && caractere <= 90){
           printf("%c.",caractere);
       }
    } while (caractere != '.');
    printf("\n");
}
