#include <stdio.h>
#include <stdlib.h>

// Arvore TAD
struct arvore{
    int valor;
    struct arvore *esq;
    struct arvore *dir;
}typedef Arvore;

//Lista dupla circular TAD
struct lista{ 
    int valor;
    struct lista *prox;
    struct lista *ant;
}typedef Lista;

// Fila dupla circular TAD
struct fila{ 
    int valor;
    struct fila *prox;
    struct fila *ant;
} typedef Fila;

// Parte da lista

Lista *adiciona_no_final_lista(int valor,Lista *ini){ 

    Lista *aux = (Lista *)malloc(sizeof(Lista));

    aux->valor = valor;
    aux->prox = aux;
    aux->ant = aux;

    if(ini==NULL){
        ini = aux;
    }
    else{
        aux->prox = ini;
        aux->ant = ini->ant;
        ini->ant->prox = aux;
        ini->ant = aux;
    }

    return ini;
}

void mostra_lista(Lista *ini){

   Lista *aux = ini;

   if(aux!=NULL){
       while(aux->prox!=ini){

          printf("%d ",aux->valor);
          aux = aux->prox;
       }

       printf("%d",aux->valor);
   }
}

// Fila 
Fila *adiciona_no_final_fila(int valor,Fila *ini){ 

    Fila *aux = (Fila *)malloc(sizeof(Fila));

    aux->valor = valor;
    aux->prox = aux;
    aux->ant = aux;

    if(ini==NULL){

        ini = aux;
    }
    else{
        
        aux->prox = ini;
        aux->ant = ini->ant;
        ini->ant->prox = aux;
        ini->ant = aux;
    }

    return ini;
}

void mostra_fila(Fila *ini){

   Fila *aux = ini;
   if(aux!=NULL){

       while(aux->prox!=ini){

            printf("%d -> ",aux->valor);
            aux = aux->prox;
       }

       printf("%d -> ",aux->valor);
   }
}

//So deleta o da frente
Fila *deleta_da_fila(Fila *ini){ 

    Fila *aux = ini;

    if(aux!=NULL && aux->prox!=ini && aux->ant!=ini){
        ini->ant->prox = aux->prox;
        ini->prox->ant = aux->ant;
        ini = ini->prox;
        free(aux);

    }
    else if(aux!=NULL && aux->prox==ini && aux->ant==ini){
        ini = NULL;
        free(aux);
    }
    return ini;
}

/// Parte da arvore

Arvore *treeInsert(Arvore *raiz,int chave){

    Arvore *raizAux = (Arvore *)malloc(sizeof(Arvore));

    raizAux->valor = chave;
    raizAux->dir = NULL;
    raizAux->esq = NULL;

    Arvore *y = NULL;
    Arvore *x = raiz;

    while(x!=NULL){
        y = x;

        if(raizAux->valor < x->valor){
            x = x->esq;
        }
        else{
            x = x->dir;
        }
    }
    // So entra neste if se a arvore a raiz da estiver nula 
    if(y == NULL){ 

        raiz = raizAux;
    }
    else{
        if(raizAux->valor < y->valor){
            y->esq = raizAux;
        }else{
            y->dir = raizAux;
        }
    }

    return raiz;
}

void inOrdem(Arvore *raiz){

    if(raiz!=NULL){
        inOrdem(raiz->esq);
        printf("%d  ",raiz->valor);
        inOrdem(raiz->dir);
    }
}

// Busca a por chave
struct arvore *treeSearch(Arvore *raiz,int chaveQueBusco){

    while(raiz!=NULL && chaveQueBusco!=raiz->valor){

        if(chaveQueBusco < raiz->valor){

            raiz = raiz->esq;
        }else{

            raiz = raiz->dir;
        }
    }

    return raiz;
}

// Parte da Busca em Largura

Fila *busca_em_largura(Fila *inicio_fila,Arvore *raiz,Lista *inicio_lista){

     // Busca na arvore o valor da frente da fila 
    Arvore *r = treeSearch(raiz,inicio_fila->valor);
    if(r!= NULL && r->esq != NULL){
        inicio_fila = adiciona_no_final_fila(r->esq->valor,inicio_fila);
    }

    if(r!= NULL && r->dir != NULL){
        inicio_fila = adiciona_no_final_fila(r->dir->valor,inicio_fila);
    }

    inicio_fila = deleta_da_fila(inicio_fila);
    return inicio_fila;
}

    int main(){

    int testes,qtdTestes=1;
    scanf("%d",&testes);

    while(testes--){

        Lista *inicio_lista = NULL;
        Fila * inicio_fila = NULL;
        Arvore *raiz_arvore = NULL;

        int qtd_nodos_arvore,i,no;
        scanf("%d",&qtd_nodos_arvore);

        // Aloca na arvore

        for(i=0;i<qtd_nodos_arvore;i++){ 
            scanf("%d",&no);
            raiz_arvore = treeInsert(raiz_arvore,no);
        }

        // adiciona a raiz da arvore na fila

        inicio_fila = adiciona_no_final_fila(raiz_arvore->valor,inicio_fila); 

        while(inicio_fila!=NULL){

            inicio_lista = adiciona_no_final_lista(inicio_fila->valor,inicio_lista);
            inicio_fila = busca_em_largura(inicio_fila,raiz_arvore,inicio_lista);
        }

        printf("Case %d:\n",qtdTestes);
        mostra_lista(inicio_lista);
        printf("\n\n");

        qtdTestes++;
    }

    return 0;
}
