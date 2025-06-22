#include "simulador.h"

extern unsigned page_size_kb;
extern unsigned memory_size_kb;
extern unsigned total_frames;
extern unsigned s_bits;
extern int debug_level;
extern void *page_table;

extern int (*lookup_function)(unsigned);
extern void (*update_function)(unsigned, int);

/**
 * Função de benchmark para medir o desempenho de diferentes estruturas de tabela de páginas
 */
void benchmark_page_tables(const char *input_file_name) {
    unsigned bench_page_size_kb = 4;
    unsigned bench_memory_size_kb = 128;
    unsigned bench_total_frames = bench_memory_size_kb / bench_page_size_kb;
    
    // Calcula s_bits para este benchmark
    unsigned bench_s_bits = 0;
    unsigned tmp = bench_page_size_kb * 1024;
    while (tmp > 1) {
        tmp = tmp >> 1;
        bench_s_bits++;
    }
    
    FILE *input_file = fopen(input_file_name, "r");
    if (!input_file) {
        perror("Failed to open input file for benchmarking");
        return;
    }
    
    unsigned total_accesses = 0;
    unsigned addr;
    char rw;
    while (fscanf(input_file, "%x %c", &addr, &rw) == 2) {
        total_accesses++;
    }
    rewind(input_file);
    
    printf("==========================================================\n");
    printf("BENCHMARK DAS ESTRUTURAS DE TABELA DE PÁGINAS\n");
    printf("==========================================================\n");
    printf("Configuração do benchmark:\n");
    printf("- Páginas: %u KB\n", bench_page_size_kb);
    printf("- Memória: %u KB (%u frames)\n", bench_memory_size_kb, bench_total_frames);
    printf("- Acessos: %u\n", total_accesses);
    printf("- Arquivo: %s\n\n", input_file_name);
    
    double lookup_times[4] = {0};
    double update_times[4] = {0};
    size_t memory_usage[4] = {0};
    
    const char *table_names[] = {"Dense", "Two-Level", "Three-Level", "Inverted"};
    
    // Testa cada tipo de tabela de páginas
    for (int type = 0; type < 4; type++) {
        printf("Testando tabela %s...\n", table_names[type]);
        
        // Cria tabela de páginas temporária para este teste
        void *test_page_table = NULL;
        int (*test_lookup_function)(unsigned) = NULL;
        void (*test_update_function)(unsigned, int) = NULL;
        
        // Inicializa o tipo específico de tabela de páginas
        switch (type) {
            case PAGE_TABLE_DENSE: {
                // Inicializa tabela de páginas densa
                unsigned table_size = 1 << (32 - bench_s_bits);
                DensePageTable *table = (DensePageTable *)malloc(sizeof(DensePageTable));
                table->entries = (int *)malloc(table_size * sizeof(int));
                for (unsigned i = 0; i < table_size; i++) {
                    table->entries[i] = -1;
                }
                table->size = table_size;
                test_page_table = table;
                test_lookup_function = lookup_dense;
                test_update_function = update_dense;
                memory_usage[type] = sizeof(DensePageTable) + table_size * sizeof(int);
                break;
            }
            case PAGE_TABLE_HIERARCHY_2LEVEL: {
                // Inicializa tabela de páginas de dois níveis
                unsigned total_page_bits = 32 - bench_s_bits;
                unsigned dir_bits = total_page_bits / 2;
                unsigned table_bits = total_page_bits - dir_bits;
                unsigned dir_size = 1 << dir_bits;
                unsigned table_size = 1 << table_bits;
                
                TwoLevelPageTable *table = (TwoLevelPageTable *)malloc(sizeof(TwoLevelPageTable));
                table->directory = (int **)malloc(dir_size * sizeof(int *));
                for (unsigned i = 0; i < dir_size; i++) {
                    table->directory[i] = NULL;
                }
                table->dir_size = dir_size;
                table->table_size = table_size;
                test_page_table = table;
                test_lookup_function = lookup_two_level;
                test_update_function = update_two_level;
                memory_usage[type] = sizeof(TwoLevelPageTable) + dir_size * sizeof(int *);
                break;
            }
            case PAGE_TABLE_HIERARCHY_3LEVEL: {
                // Inicializa tabela de páginas de três níveis
                unsigned total_page_bits = 32 - bench_s_bits;
                unsigned dir_bits = total_page_bits / 3;
                unsigned mid_bits = dir_bits;
                unsigned table_bits = total_page_bits - dir_bits - mid_bits;
                unsigned dir_size = 1 << dir_bits;
                unsigned mid_size = 1 << mid_bits;
                unsigned table_size = 1 << table_bits;
                
                ThreeLevelPageTable *table = (ThreeLevelPageTable *)malloc(sizeof(ThreeLevelPageTable));
                table->directory = (int ***)malloc(dir_size * sizeof(int **));
                for (unsigned i = 0; i < dir_size; i++) {
                    table->directory[i] = NULL;
                }
                table->dir_size = dir_size;
                table->mid_size = mid_size;
                table->table_size = table_size;
                test_page_table = table;
                test_lookup_function = lookup_three_level;
                test_update_function = update_three_level;
                memory_usage[type] = sizeof(ThreeLevelPageTable) + dir_size * sizeof(int **);
                break;
            }
            case PAGE_TABLE_INVERTED: {
                // Inicializa tabela de páginas invertida
                InvertedPageTable *table = (InvertedPageTable *)malloc(sizeof(InvertedPageTable));
                table->virtual_pages = (unsigned *)malloc(bench_total_frames * sizeof(unsigned));
                table->valid = (bool *)malloc(bench_total_frames * sizeof(bool));
                for (unsigned i = 0; i < bench_total_frames; i++) {
                    table->valid[i] = false;
                }
                table->size = bench_total_frames;
                test_page_table = table;
                test_lookup_function = lookup_inverted;
                test_update_function = update_inverted;
                memory_usage[type] = sizeof(InvertedPageTable) + 
                                    bench_total_frames * sizeof(unsigned) + 
                                    bench_total_frames * sizeof(bool);
                break;
            }
        }
        
        // Define variáveis globais temporariamente para as funções lookup/update
        void *original_page_table = page_table;
        page_table = test_page_table;
        
        // Mede performance de lookup
        rewind(input_file);
        clock_t start = clock();
        while (fscanf(input_file, "%x %c", &addr, &rw) == 2) {
            unsigned page = addr >> bench_s_bits;  // Calcula número da página
            int frame = test_lookup_function(page);
            (void)frame; 
        }
        clock_t end = clock();
        lookup_times[type] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Mede performance de update
        rewind(input_file);
        start = clock();
        int frame_num = 0;
        while (fscanf(input_file, "%x %c", &addr, &rw) == 2) {
            unsigned page = addr >> bench_s_bits;  // Calcula número da página
            test_update_function(page, frame_num % bench_total_frames);
            frame_num++;
        }
        end = clock();
        update_times[type] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Limpa esta tabela de páginas
        page_table = original_page_table;
        
        switch (type) {
            case PAGE_TABLE_DENSE: {
                DensePageTable *table = (DensePageTable *)test_page_table;
                free(table->entries);
                free(table);
                break;
            }
            case PAGE_TABLE_HIERARCHY_2LEVEL: {
                TwoLevelPageTable *table = (TwoLevelPageTable *)test_page_table;
                for (unsigned i = 0; i < table->dir_size; i++) {
                    if (table->directory[i] != NULL) {
                        free(table->directory[i]);
                    }
                }
                free(table->directory);
                free(table);
                break;
            }
            case PAGE_TABLE_HIERARCHY_3LEVEL: {
                ThreeLevelPageTable *table = (ThreeLevelPageTable *)test_page_table;
                for (unsigned i = 0; i < table->dir_size; i++) {
                    if (table->directory[i] != NULL) {
                        for (unsigned j = 0; j < table->mid_size; j++) {
                            if (table->directory[i][j] != NULL) {
                                free(table->directory[i][j]);
                            }
                        }
                        free(table->directory[i]);
                    }
                }
                free(table->directory);
                free(table);
                break;
            }
            case PAGE_TABLE_INVERTED: {
                InvertedPageTable *table = (InvertedPageTable *)test_page_table;
                free(table->virtual_pages);
                free(table->valid);
                free(table);
                break;
            }
        }
        
        printf("  Concluído (Lookup: %.6fs, Update: %.6fs)\n", 
               lookup_times[type], update_times[type]);
    }
    
    // Imprime resultados
    printf("\n==========================================================\n");
    printf("RESULTADOS DO BENCHMARK\n");
    printf("==========================================================\n");
    printf("%-15s | %-11s | %-11s | %-12s\n", 
           "Estrutura", "Lookup (s)", "Update (s)", "Memória (KB)");
    printf("----------------|-------------|-------------|-------------\n");
    
    for (int i = 0; i < 4; i++) {
        printf("%-15s | %11.6f | %11.6f | %12.2f\n", 
               table_names[i], 
               lookup_times[i], 
               update_times[i], 
               memory_usage[i] / 1024.0);
    }
    
    printf("\n");
    fclose(input_file);
}

/**
 * Cria arquivos de teste com padrões específicos de acesso à memória
 */
void create_test_files() {
    // Padrão de acesso sequencial - simula travessia linear de array
    FILE *sequential = fopen("sequential.log", "w");
    if (sequential) {
        for (unsigned i = 0; i < 1000; i++) {
            // Páginas são alinhadas em limites de 4KB para clareza
            fprintf(sequential, "%08x %c\n", i * 4096, (i % 2 == 0) ? 'R' : 'W');
        }
        fclose(sequential);
        printf("Created sequential.log with 1000 sequential accesses\n");
    } else {
        perror("Failed to create sequential.log");
    }
    
    // Padrão de acesso aleatório - simula acessos imprevisíveis à memória
    FILE *random_file = fopen("random.log", "w");
    if (random_file) {
        srandom(time(NULL));
        for (unsigned i = 0; i < 1000; i++) {
            // Gera endereço aleatório, alinhado à página
            unsigned addr = random() & 0xFFFFF000;  
            fprintf(random_file, "%08x %c\n", addr, (random() % 2 == 0) ? 'R' : 'W');
        }
        fclose(random_file);
        printf("Created random.log with 1000 random accesses\n");
    } else {
        perror("Failed to create random.log");
    }
    
    // Padrão de localidade (regra 80/20) - 80% dos acessos para 20% das páginas
    FILE *locality = fopen("locality.log", "w");
    if (locality) {
        srandom(time(NULL) + 1);
        
        unsigned hot_pages[20];
        for (unsigned i = 0; i < 20; i++) {
            hot_pages[i] = random() & 0xFFFFF000;  
        }
        
        for (unsigned i = 0; i < 1000; i++) {
            unsigned addr;
            if (random() % 100 < 80) {
                // 80% de chance de acessar uma página quente
                addr = hot_pages[random() % 20];
            } else {
                // 20% de chance de acessar qualquer outra página
                addr = random() & 0xFFFFF000;
            }
            fprintf(locality, "%08x %c\n", addr, (random() % 2 == 0) ? 'R' : 'W');
        }
        fclose(locality);
        printf("Created locality.log with 1000 accesses (80%% to 20%% of pages)\n");
    } else {
        perror("Failed to create locality.log");
    }
    
    // Padrão de loop - acessa repetidamente o mesmo conjunto de páginas em sequência
    // Simula loops de programas ou operações repetitivas
    FILE *loop = fopen("loop.log", "w");
    if (loop) {
        for (unsigned iter = 0; iter < 10; iter++) {
            for (unsigned i = 0; i < 100; i++) {
                fprintf(loop, "%08x %c\n", i * 4096, (i % 3 == 0) ? 'W' : 'R');
            }
        }
        fclose(loop);
        printf("Created loop.log with 1000 accesses in a repetitive pattern\n");
    } else {
        perror("Failed to create loop.log");
    }
}