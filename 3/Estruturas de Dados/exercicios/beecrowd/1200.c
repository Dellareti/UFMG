#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct noArv {
    char letra;
    struct noArv *esq;
    struct noArv *dir;
};
typedef struct noArv TNo;
typedef struct {
	TNo *raiz;
} descArv;

TNo *buscaPai(TNo *, char);
int FLAG;

int pesquisa(TNo *r, char letra) {
	if(r == NULL){
		return 0;
	} else {
		if(r->letra == letra) {
			return 1;
        }
		else {
			return pesquisa(r->esq, letra) + pesquisa(r->dir, letra);	
        }
    }	
}

void inicializaNo(descArv *d) {
	d->raiz = NULL;
	FLAG=0;
}

void insereNo(descArv *d, char letra) {
	TNo *aux, *pai;
	
	aux = (TNo *) malloc(sizeof(TNo));
	aux->dir = NULL;
	aux->esq = NULL;	
	aux->letra = letra;	
	pai = buscaPai(d->raiz, letra);

	if(pai == NULL) {
		d->raiz = aux;
    } else {
		if(letra <= pai->letra) {
			pai->esq = aux;
        } else {
			pai->dir = aux;
        }
    }
}

TNo *buscaPai(TNo *r, char n) { 
	if(r == NULL) {
		return NULL;
    } else {
		if(n <= r->letra) {
			if(r->esq == NULL) {
				return r;
            } else {
				return buscaPai(r->esq, n);
            }
        } else {
			if(r->dir == NULL) {
				return r;
            } else {
				return buscaPai(r->dir, n);
            }
        }
    }
}

void prefixa(TNo *r) {
	if(r != NULL){
		if(FLAG)
			printf(" %c", r->letra);
		else {
			printf("%c", r->letra);
			FLAG++;
		}
		prefixa(r->esq);		
		prefixa(r->dir);		
	}
}

void posfixa(TNo *r){
	if(r != NULL) {
		posfixa(r->esq);		
		posfixa(r->dir);
		if(FLAG)
			printf(" %c", r->letra);
		else {
			printf("%c", r->letra);
			FLAG++;
		}
	}
}

void infixa(TNo *r){
	if(r != NULL){
		infixa(r->esq);
		if(FLAG)
			printf(" %c", r->letra);
		else {
			printf("%c", r->letra);
			FLAG++;
		}
		infixa(r->dir);
	}
}

int main(){ 	
    descArv d;
	char entrada[100], v;
	inicializaNo(&d);
	
	while(scanf(" %s ", entrada) != EOF) {
		if(strcmp(entrada,"I") == 0) {		
			scanf(" %c ", &v);
			insereNo(&d, v);
		} else {
			if(strcmp(entrada, "P") == 0) {
				scanf(" %c ", &v);
				if(pesquisa(d.raiz, v))
					printf("%c existe\n", v);
				else
					printf("%c nao existe\n", v); 
			} else {
				if(!strcmp(entrada, "INFIXA"))
					infixa(d.raiz);
				else
					if(!strcmp(entrada, "PREFIXA"))
						prefixa(d.raiz);
					else
						posfixa(d.raiz);
				printf("\n");	
				FLAG = 0;
			}	
		}
	}		
	
	return 0;
}
