//---------------------------------------------------------------------
// Arquivo	: mat.c
// Conteudo	: implementacao do TAD MAT 
// Autor	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico	: 2021-10-18 - arquivo criado
//		: 2021-10-21 - estrutura de diretorios
//              : 2021-11-14 - adequacao para versao 1.1 memlog
//---------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"


// limite superior da inicializacao aleatoria
#define INITRANDOMRANGE 10
// Macro que realiza swap sem variavel auxiliar
#define ELEMSWAP(x, y) (x += y, y = x - y, x -= y)

mat_tipo *criar_matriz_arquivo(char *txt_nome){

// Leitura dos arquivos TXT

  FILE *Arquivo = fopen(txt_nome, "r");
  erroAssert(Arquivo != NULL, "Arquivo nao encontrado!\n");

  mat_tipo *matriz = malloc(sizeof(mat_tipo));

  fscanf(Arquivo, "%d", &matriz->tamx);
  fscanf(Arquivo, "%d", &matriz->tamy);

  cria_matriz(matriz, matriz->tamx, matriz->tamy,matriz->id);

  // Confere e alerta se a matriz esta vazia
  int resultado_leitura_matriz = 0;

  for (int i = 0; i < matriz->tamx; i++){
    for (int j = 0; j < matriz->tamy; j++){

      resultado_leitura_matriz = fscanf(Arquivo, "%lf", &matriz->m[i][j]);
      erroAssert(resultado_leitura_matriz != -1,"A matriz informada esta vazia!\n");
      // Escreve + performace
      escreveMemLog((long int)(&(matriz->m[i][j])), sizeof(double),matriz->id);
    }
  }

  fclose(Arquivo);

  return matriz;
};

// Descrição função - cria_matriz : 
// Cria a matriz com as dimensões tamanho_x e tamanho_y e aloca dinamincamente essas dimensões 
// Entrada: mat, tx, ty, id
// Saida: mat
void cria_matriz(mat_tipo *mat, int tx, int ty,int id){
  // Converir se as dimensoes da matriz são validas
  erroAssert(tx > 0, "Dimensao nula");
  erroAssert(ty > 0, "Dimensao nula");

  //Atribui os valores das dimensões
  mat->tamx = tx;
  mat->tamy = ty;
  // inicializa o identificador da matriz, para rastreamento
  mat->id = id;
  // Chama a função para alocar dinamicamente os valores das dimensões da matriz
  aloca_matriz_dinamicamente(mat);
}


// Descrição função - aloca_matriz_dinamicamente : 
// Aloca os vetores para receber as linhas da matriz
// Entrada: *matriz
// Saida: *matriz
void aloca_matriz_dinamicamente(mat_tipo *matriz){
  // Alocação
  matriz->m = malloc(matriz->tamx * sizeof(double *));
  // Atribuindo 
  for (int i = 0; i < matriz->tamx; i++){
    matriz->m[i] = malloc(matriz->tamy * sizeof(double));
  }
}

// Descrição função - criar_matriz_de_arquivo : 
// Cria o arquivo do resultado das operações 
// Entrada: *mat e txt_nome
// Saida: txt_nome
void criar_matriz_de_arquivo(mat_tipo *mat, char *txt_nome){
  // Para escrever no arquivo
  FILE *arquivo = fopen(txt_nome, "w");
  // Escrevendo a quantidade se linhas e colunas no txt
  fprintf(arquivo, "%d %d", mat->tamx, mat->tamy);

  // Escrevendo as linhas no txt
  for (int i = 0; i < mat->tamx; i++){

  // Pulando linha para escrever na proxima
    fprintf(arquivo, "\n");

    for (int j = 0; j < mat->tamy; j++){
      
      fprintf(arquivo, "%.2f ", mat->m[i][j]);
      // Performace de leitura + Alocação
      leMemLog((long int)(&(mat->m[i][j])), sizeof(double),mat->id);
    }
  }

  fclose(arquivo);
}

// Descrição função - soma_matrizes : 
// Soma duas matrizes quando possuem as caracteristicas necesárias para as operações 
// Entrada: a, b
// Saida: c
void soma_matrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c){
  // Verifica se as dimensões das matrizes são compatíveis para fazer a soma
  erroAssert(a->tamx == b->tamx, "Ordem diferente! As matrizes precisam ter a mesma ordem");
  erroAssert(a->tamy == b->tamy, "Ordem diferente! As matrizes precisam ter a mesma ordem");

  // Inicia a matriz c com a ordem correta
  cria_matriz(c, a->tamx, a->tamy,c->id);

  // Somatório de elementos + performace 
  for (int i = 0; i < a->tamx; i++){
    for (int j = 0; j < a->tamy; j++){

      c->m[i][j] = a->m[i][j] + b->m[i][j];
      // Leitura + performace 
      leMemLog((long int)(&(a->m[i][j])), sizeof(double),a->id);
      leMemLog((long int)(&(b->m[i][j])), sizeof(double),b->id);
      // Escrita + performace 
      escreveMemLog((long int)(&(c->m[i][j])), sizeof(double),c->id);
    }
  }
}

// Descrição função - multiplica_matrizes : 
// Multiplica duas matrizes e armazena em uma outra matriz -> A * B = C 
// Entrada: a, b
// Saida: c
void multiplica_matrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c){

  // Verifica se as dimensões das matrizes são compatíveis para fazer a multiplicação
  erroAssert(a->tamy == b->tamx, "É necessário que o número de colunas da primeira matriz seja igual ao número de linhas da segunda matriz");

  // Inicia a matriz c com a ordem correta
  cria_matriz(c, a->tamx, b->tamy,c->id);

  // Multiplica as matrizes + performace 
  for (int i = 0; i < c->tamx; i++){
    for (int j = 0; j < c->tamy; j++){
      for (int k = 0; k < a->tamy; k++){

        c->m[i][j] += a->m[i][k] * b->m[k][j];
        // Leitura + performace 
        leMemLog((long int)(&(a->m[i][k])), sizeof(double),a->id);
        leMemLog((long int)(&(b->m[k][j])), sizeof(double),b->id);
        // Escrita + performace 
        escreveMemLog((long int)(&(c->m[i][j])), sizeof(double),c->id);
      }
    }
  }
}

// Descrição função - transpoe_matriz : 
// transpoe a matriz de entrada
// Entrada: a
// Saida: a
void transpoe_matriz(mat_tipo *a){

  // Alocação
  mat_tipo transposta_de_a;
  transposta_de_a.tamx = a->tamy;
  transposta_de_a.tamy = a->tamy;

  aloca_matriz_dinamicamente(&transposta_de_a);

  // Transpoe a matriz 
  for (int i = 0; i < a->tamx; i++){
    for (int j = 0; j < a->tamy; j++){

      transposta_de_a.m[j][i] = a->m[i][j];
      // Escrita + performace 
      escreveMemLog((long int)(&(a->m[i][j])), sizeof(double),a->id);
      escreveMemLog((long int)(&(transposta_de_a.m[j][i])), sizeof(double),a->id);
    }
  }

  // Desalocar e trocar pela transposta
  desalocar_matriz(a->m, a->tamx);
  a->m = transposta_de_a.m;

  // Novas dimensoes
  ELEMSWAP(a->tamx, a->tamy);
}

// Descrição função - destroi_matriz: 
// Destroi a matriz que for o input
// Entrada: a
// Saida: a
void destroi_matriz(mat_tipo *a){
  //um erro é lançado se a matriz for destruida mais de uma vez
  erroAssert(a != NULL, "A Matriz ja foi destruida");
  desalocar_matriz(a->m, a->tamx);

  // Libera a matriz 
  free(a);
  a = NULL;
}

// Descrição função - destroi_matrizes: 
// Destroi varias matrizes
// Entrada: Matrizes e némero de matrizes a serem destruidas
// Saida: NULL
void destroi_matrizes(mat_tipo **matrizes, int numero_de_matrizes){

  for (int i = 0; i < numero_de_matrizes; i++){
    destroi_matriz(matrizes[i]);
  }
}

void desalocar_matriz(double **matriz, int tamx){

  // Desalocando as linhas
  for (int i = 0; i < tamx; i++){
    free(matriz[i]);
  }
  // Desalocando vetor das linhas
  free(matriz);
}
