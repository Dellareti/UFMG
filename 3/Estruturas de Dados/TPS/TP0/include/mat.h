//---------------------------------------------------------------------
// Arquivo	: mat.h
// Conteudo	: definicoes do TAD MAT 
// Autor	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico	: 2021-10-18 - arquivo criado
//		: 2021-10-21 - estrutura de diretorios
//----------------------------------------------------------------------

#ifndef MATH
#define MATH

#include <stdio.h>
#include "memlog.h"

typedef struct mat{

	double **m;
	int tamx, tamy;
	int id;
} mat_tipo;

mat_tipo * criar_matriz_arquivo(char *txt_nome);
// Funções já predefinidas pelo matop.c

void cria_matriz(mat_tipo *mat, int tx, int ty,int id);
void soma_matrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);
void multiplica_matrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);
void transpoe_matriz(mat_tipo *a);
void destroi_matriz(mat_tipo *a);
void criar_matriz_de_arquivo(mat_tipo *mat, char * txt_nome);

// Outras Funções 
void aloca_matriz_dinamicamente(mat_tipo *matriz);
void destroi_matrizes(mat_tipo ** matrizes, int numero_de_matrizes);
void desalocar_matriz(double **matriz, int tamy);

#endif
