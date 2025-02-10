#include <stdio.h>
#include <math.h>
#include "pratica4.h"

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
}   

int main(){

int x,y;

	printf("\n\n Digite os dois  numeros: \n\n"); 
	scanf("%d %d", &x, &y);

    mdcEmmc(x,y);
    return 0;
}