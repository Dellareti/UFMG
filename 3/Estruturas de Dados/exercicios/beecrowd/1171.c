#include <stdio.h>
#include <stdlib.h>

void insercao(int num[], int n) {
    int i, elem, j;
    i = 0;
    j = 0;

    for(i = 1; i < n; i++) {
        elem = num[i];
        j = i - 1;

        while(j >= 0 && elem < num[j]) {
            num[j + 1] = num[j];
            j--;
        } 

        num[j + 1] = elem;
    }
}

int main(){
    int n, i, comp, cont;
    scanf("%d", &n);
    int num[n];
    
    for(i = 0; i < n; i++){
        scanf("%d", &num[i]);
    }
    
    insercao(num, n);
    comp = num[0];
    i = 1;
    cont = 1;

    while(1){
        if(i == n+1) {
            break;
        } 

        if(num[i] == comp) {
            cont++;
            i++;
        } else {
            printf("%d aparece %d vez(es)\n", comp, cont);
            comp = num[i];
            cont = 0;
        }
    }

    return 0;
}
