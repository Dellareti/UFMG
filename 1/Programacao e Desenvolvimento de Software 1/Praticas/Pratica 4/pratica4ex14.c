#include <stdio.h>
#include <math.h>
#include "pratica4.h"

int main(){
   int x,y;

	printf("\n\n Digite os dois  numeros: \n\n"); 
	scanf("%d %d", &x, &y);

    mdc(x,y);
     
    return 0;
}