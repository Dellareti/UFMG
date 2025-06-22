#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

/* Níveis de debug */
#define DEBUG_NONE 0
#define DEBUG_BASIC 1
#define DEBUG_DETAILED 2
#define DEBUG_VERBOSE 3

/* Tipos de tabela de páginas */
#define PAGE_TABLE_DENSE 0
#define PAGE_TABLE_HIERARCHY_2LEVEL 1
#define PAGE_TABLE_HIERARCHY_3LEVEL 2
#define PAGE_TABLE_INVERTED 3

/* Algoritmos de substituição de páginas */
#define REPLACEMENT_RANDOM 0
#define REPLACEMENT_LRU 1
#define REPLACEMENT_LFU 2
#define REPLACEMENT_CLOCK 3  // Nosso quarto algoritmo escolhido

/**
 * Estrutura Frame: Representa um frame físico na memória
 */
typedef struct {
    unsigned page_number;    // Número da página virtual armazenada neste frame
    unsigned long last_used; // Momento quando este frame foi acessado pela última vez (para LRU)
    unsigned access_count;   // Quantas vezes este frame foi acessado (para LFU)
    bool valid;              // Se este frame contém uma página válida
    bool dirty;              // Se esta página foi modificada (para write-back)
    bool referenced;         // Para algoritmo Clock
} Frame;

/**
 * Tabela de Páginas Densa
 * Um array simples mapeando cada página virtual para um frame físico
 */
typedef struct {
    int *entries;           // Array de números de frames (-1 se não estiver na memória)
    unsigned size;          // Número de entradas na tabela
} DensePageTable;

/**
 * Tabela de Páginas Hierárquica de Dois Níveis
 * Primeiro nível é o diretório de páginas, segundo nível contém os mapeamentos reais
 */
typedef struct {
    int **directory;        // Array de ponteiros para tabelas de páginas
    unsigned dir_size;      // Tamanho do diretório
    unsigned table_size;    // Tamanho de cada tabela de páginas
} TwoLevelPageTable;

/**
 * Tabela de Páginas Hierárquica de Três Níveis
 */
typedef struct {
    int ***directory;       // Array de ponteiros para diretórios de nível médio
    unsigned dir_size;      // Tamanho do diretório de nível superior
    unsigned mid_size;      // Tamanho de cada diretório de nível médio
    unsigned table_size;    // Tamanho de cada tabela de páginas
} ThreeLevelPageTable;

/**
 * Tabela de Páginas Invertida
 * Mapeia frames físicos para páginas virtuais (mapeamento reverso)
 */
typedef struct {
    unsigned *virtual_pages; // Número da página virtual para cada frame
    unsigned size;           // Número de entradas (igual ao número de frames)
    bool *valid;             // Se cada entrada é válida
} InvertedPageTable;

/* Funções principais */
void initialize(unsigned alg_type, unsigned page_size, unsigned memory_size, int page_table_type);
void cleanup(void);
void handle_memory_access(unsigned address, char access_type);
void print_statistics(const char *algorithm_name, const char *input_file);
unsigned get_page_number(unsigned address);

/* Inicialização de tabelas de páginas */
void initialize_page_table(int page_table_type);
void initialize_dense_page_table(unsigned address_bits);
void initialize_two_level_page_table(unsigned address_bits);
void initialize_three_level_page_table(unsigned address_bits);
void initialize_inverted_page_table(void);

/* Limpeza de tabelas de páginas */
void cleanup_dense_page_table(void);
void cleanup_two_level_page_table(void);
void cleanup_three_level_page_table(void);
void cleanup_inverted_page_table(void);

/* Algoritmos de substituição de páginas */
int random_replacement(void);
int lru_replacement(void);
int lfu_replacement(void);
int clock_replacement(void);

/* Funções de busca em tabelas de páginas */
int lookup_dense(unsigned page_number);
int lookup_two_level(unsigned page_number);
int lookup_three_level(unsigned page_number);
int lookup_inverted(unsigned page_number);

/* Funções de atualização em tabelas de páginas */
void update_dense(unsigned page_number, int frame_number);
void update_two_level(unsigned page_number, int frame_number);
void update_three_level(unsigned page_number, int frame_number);
void update_inverted(unsigned page_number, int frame_number);

/* Funções utilitárias */
int get_algorithm_type(const char *name);

/* Funções de extensão */
void benchmark_page_tables(const char *input_file_name);
void create_test_files(void);

#endif