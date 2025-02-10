#include <stdio.h>
#include <stdlib.h>

float leFilial(char buffer[], int filial){
    float filiais[5] = {0.0};
    sscanf(buffer, "%f %f %f %f %f",
    &filiais[0], &filiais[1], &filiais[2], &filiais[3], &filiais[4]);
    return filiais[filial - 1];
}

// 1
float somaSaldo(char nome_arquivo[], int filial, int ini, int fim) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        return 0.0;
    }
    if(filial < 1 || filial > 5){ 
        return 0.0;
    }
    if(fim < ini){
        return 0.0;
    }
    float saldo = 0.0;
    char buffer[128]; // tamanho arbitrário pra uma linha
    ini = ini < 1 ? 1 : ini;
    
    for (int i = 1; i < ini; i++){
        if(fgets(buffer, 128, arquivo) == NULL) {
            return 0.0;
        } 
    }
    for(int i = ini; i <= fim; i++){
        if(fgets(buffer, 128, arquivo) == NULL){
            return saldo;
        }
        
        saldo += leFilial(buffer, filial);
    }
    fclose(arquivo);
    return saldo;
}

float* leGastos(FILE* arquivo, int num_colunas){
    
    float* gastos = (float*)malloc((num_colunas + 1) * sizeof(float));
    gastos[num_colunas] = 0.0;
    
    for (int i = 0; i < num_colunas; i++){
        fscanf(arquivo, " %f", &gastos[i]);
    }
    return gastos;
}

// 2

float** carregaLista(const char nome_arquivo[]){
    FILE* arquivo = fopen(nome_arquivo, "r");
    
    if (arquivo == NULL){
        return NULL;
    }
    int num_linhas;
    fscanf(arquivo, "%d\n", &num_linhas);
    
    float** lista = (float**)malloc((num_linhas + 1) * sizeof(float*));
    lista[num_linhas] = NULL;
    for (int i = 0; i < num_linhas; i++){
        char mes[32];
        int ano, num_colunas;
        fscanf(arquivo, "%s %d %d", mes, &ano, &num_colunas);
        lista[i] = leGastos(arquivo, num_colunas);
    }
    fclose(arquivo);
    return lista;
}



float somaGastos(float *mes){
    if (*mes == 0.0){
        return 0.0;
    }
    return somaGastos(mes + 1) + *mes;
}

float max(float a, float b){
    return a > b ? a : b;
}

// 3
float maiorGasto(float **gastos) {
    if (*gastos == NULL){
        return 0.0;
    }
    return max(somaGastos(*gastos), maiorGasto(gastos + 1));
}


// 4
//não altere este struct!
typedef struct Empresa {
  float juros;
  float taxa;
}Empresa;


float valorTotalEmprestimo(float valor, int m, Empresa empresa) {
    if (m == 0){
        return valor + empresa.taxa;
    }
    return valorTotalEmprestimo(valor * (1 + empresa.juros), m - 1, (Empresa){empresa.juros, empresa.taxa * (1 + empresa.juros)});
}


// 5
int diferencaChaves(char *programa) {
    
   if(*programa == '\0'){
        return 0;
    }
    if(*programa == '{'){
        return diferencaChaves(programa + 1) + 1;
    }
    if(*programa == '}') {
        return diferencaChaves(programa + 1) - 1;
    }
    return diferencaChaves(programa + 1);
}


// Para testes
int minha_main()
{
    return -1;
}