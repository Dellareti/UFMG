#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    struct no *prox;
    int valor;
 }noArv;

typedef struct {
    noArv *primeiro, *ultimo;
}descArv;

void criaArv(descArv *vetor, int n) {
	for(int i=0; i<n; i++) {
		vetor[i].primeiro = NULL;
		vetor[i].ultimo = NULL;
	}
}

void insereNo(descArv *vetor, int indice, int e) {
	noArv *aux = (noArv *)malloc(sizeof(noArv));
	aux->valor = e;
	aux->prox = NULL;

	if(vetor[indice].primeiro == NULL) {
		vetor[indice].primeiro = aux;
    } else {
		vetor[indice].ultimo->prox = aux;
    }
	vetor[indice].ultimo = aux;
}

int main() {
	descArv vetor[256];
    //Hash info
	int chave, num;
    // Comparadores
    int n, e;
	scanf("%d", &n);
	
    // Leitura e resul
	for(int j=0; j<n; j++){	
		scanf("%d %d", &chave, &num);
		criaArv(vetor, chave);
		
        // Dispersão
		for(int i=0; i<num; i++) {
			scanf("%d", &e);
			insereNo(vetor, e % chave, e);
		}
        // Imprime Hash
		for(int i=0; i<chave; i++) {
            noArv *aux = vetor[i].primeiro;
	        printf("%d -> ", i);

	        while(aux != NULL) {
		        printf("%d -> ", aux->valor);
		        aux = aux->prox;
	        }		
	        
			printf("\\");
	        printf("\n");
        }
        // Pula para o prox linha
		if(j + 1 < n) {
			printf("\n");
        }
	}
	
	return 0;
}
