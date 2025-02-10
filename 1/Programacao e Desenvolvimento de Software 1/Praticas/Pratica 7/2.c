#include<stdio.h>

#define TAM_MAX 1000

int main(void){

// Ex2 

  int i,n;
  unsigned long int f[TAM_MAX];
  f[0] = 1;
  f[1] = 1;

  printf("Digite o numero de termos da sequencia:\n");
  scanf("%d", &n);

  while (n <= 0 || n >= TAM_MAX) {
    printf("Digite novamente:\n");
    scanf("%d", &n);
  }

    if (n>=0 && n< TAM_MAX){
        for ( i = 2; i <=; i++){
            f[i]=f[i-1] + f[i-2];
            printf("fibonacci %d = %4.3e\n",n,f[n]);
        }
        
}

  printf("\n");
 return 0;
}
