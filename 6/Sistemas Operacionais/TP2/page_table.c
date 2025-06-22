#include "simulador.h"

extern unsigned total_frames;
extern int debug_level;
extern void *page_table;
extern unsigned s_bits;

/*** Funções de Inicialização das Tabelas de Páginas ***/

/**
 * Inicializa a tabela de páginas densa
 */
void initialize_dense_page_table(unsigned address_bits) {
    // Para endereços de 32 bits com s_bits de offset, precisamos de 2^(32-s_bits) entradas
    unsigned table_size = 1 << (address_bits - s_bits);
    
    DensePageTable *table = (DensePageTable *)malloc(sizeof(DensePageTable));
    if (!table) {
        perror("Failed to allocate dense page table");
        exit(EXIT_FAILURE);
    }
    
    table->entries = (int *)malloc(table_size * sizeof(int));
    if (!table->entries) {
        perror("Failed to allocate dense page table entries");
        exit(EXIT_FAILURE);
    }
    
    // Inicializa todas as entradas como -1 (não está na memória)
    for (unsigned i = 0; i < table_size; i++) {
        table->entries[i] = -1;
    }
    
    table->size = table_size;
    page_table = table;
    
    if (debug_level >= DEBUG_BASIC) {
        printf("Initialized dense page table with %u entries\n", table_size);
    }
}

/**
 * Inicializa a tabela de páginas hierárquica de dois níveis
 */
void initialize_two_level_page_table(unsigned address_bits) {
    // Divide os bits de endereço (excluindo offset) entre diretório e tabela
    unsigned total_page_bits = address_bits - s_bits;
    unsigned dir_bits = total_page_bits / 2;
    unsigned table_bits = total_page_bits - dir_bits;
    
    unsigned dir_size = 1 << dir_bits;
    unsigned table_size = 1 << table_bits;
    
    TwoLevelPageTable *table = (TwoLevelPageTable *)malloc(sizeof(TwoLevelPageTable));
    if (!table) {
        perror("Failed to allocate two-level page table");
        exit(EXIT_FAILURE);
    }
    
    table->directory = (int **)malloc(dir_size * sizeof(int *));
    if (!table->directory) {
        perror("Failed to allocate two-level page table directory");
        exit(EXIT_FAILURE);
    }
    
    // Inicializa todas as entradas do diretório como NULL (nenhuma tabela alocada ainda)
    for (unsigned i = 0; i < dir_size; i++) {
        table->directory[i] = NULL;
    }
    
    table->dir_size = dir_size;
    table->table_size = table_size;
    page_table = table;
    
    if (debug_level >= DEBUG_BASIC) {
        printf("Initialized two-level page table with %u directory entries, each pointing to tables of %u entries\n",
               dir_size, table_size);
    }
}

/**
 * Inicializa a tabela de páginas hierárquica de três níveis
 */
void initialize_three_level_page_table(unsigned address_bits) {
    // Divide os bits de endereço (excluindo offset) entre os níveis
    unsigned total_page_bits = address_bits - s_bits;
    unsigned dir_bits = total_page_bits / 3;
    unsigned mid_bits = dir_bits;
    unsigned table_bits = total_page_bits - dir_bits - mid_bits;
    
    unsigned dir_size = 1 << dir_bits;
    unsigned mid_size = 1 << mid_bits;
    unsigned table_size = 1 << table_bits;
    
    ThreeLevelPageTable *table = (ThreeLevelPageTable *)malloc(sizeof(ThreeLevelPageTable));
    if (!table) {
        perror("Failed to allocate three-level page table");
        exit(EXIT_FAILURE);
    }
    
    table->directory = (int ***)malloc(dir_size * sizeof(int **));
    if (!table->directory) {
        perror("Failed to allocate three-level page table directory");
        exit(EXIT_FAILURE);
    }
    
    // Inicializa todas as entradas do diretório como NULL
    for (unsigned i = 0; i < dir_size; i++) {
        table->directory[i] = NULL;
    }
    
    table->dir_size = dir_size;
    table->mid_size = mid_size;
    table->table_size = table_size;
    page_table = table;
    
    if (debug_level >= DEBUG_BASIC) {
        printf("Initialized three-level page table with %u top entries, %u mid entries, %u bottom entries\n",
               dir_size, mid_size, table_size);
    }
}

/**
 * Inicializa a tabela de páginas invertida
 */
void initialize_inverted_page_table() {
    InvertedPageTable *table = (InvertedPageTable *)malloc(sizeof(InvertedPageTable));
    if (!table) {
        perror("Failed to allocate inverted page table");
        exit(EXIT_FAILURE);
    }
    
    table->virtual_pages = (unsigned *)malloc(total_frames * sizeof(unsigned));
    if (!table->virtual_pages) {
        perror("Failed to allocate inverted page table entries");
        exit(EXIT_FAILURE);
    }
    
    table->valid = (bool *)malloc(total_frames * sizeof(bool));
    if (!table->valid) {
        perror("Failed to allocate inverted page table valid flags");
        exit(EXIT_FAILURE);
    }
    
    // Inicializa todas as entradas como inválidas
    for (unsigned i = 0; i < total_frames; i++) {
        table->valid[i] = false;
    }
    
    table->size = total_frames;
    page_table = table;
    
    if (debug_level >= DEBUG_BASIC) {
        printf("Initialized inverted page table with %u entries\n", total_frames);
    }
}

/*** Funções de Limpeza das Tabelas de Páginas ***/

void cleanup_dense_page_table() {
    DensePageTable *table = (DensePageTable *)page_table;
    free(table->entries);
    free(table);
}

void cleanup_two_level_page_table() {
    TwoLevelPageTable *table = (TwoLevelPageTable *)page_table;
    
    // Libera cada tabela de segundo nível que foi alocada
    for (unsigned i = 0; i < table->dir_size; i++) {
        if (table->directory[i] != NULL) {
            free(table->directory[i]);
        }
    }
    
    free(table->directory);
    free(table);
}

void cleanup_three_level_page_table() {
    ThreeLevelPageTable *table = (ThreeLevelPageTable *)page_table;
    
    // Libera todas as tabelas alocadas em todos os níveis
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
}

void cleanup_inverted_page_table() {
    InvertedPageTable *table = (InvertedPageTable *)page_table;
    free(table->virtual_pages);
    free(table->valid);
    free(table);
}

/*** Funções de Busca nas Tabelas de Páginas ***/

/**
 * Busca uma página na tabela de páginas densa
 */
int lookup_dense(unsigned page_number) {
    DensePageTable *table = (DensePageTable *)page_table;
    
    if (page_number >= table->size) {
        if (debug_level >= DEBUG_DETAILED) {
            printf("Page number %u is outside table bounds (size %u)\n", page_number, table->size);
        }
        return -1;
    }
    
    return table->entries[page_number];
}

/**
 * Busca uma página na tabela de páginas hierárquica de dois níveis
 */
int lookup_two_level(unsigned page_number) {
    TwoLevelPageTable *table = (TwoLevelPageTable *)page_table;
    
    // Extrai os índices do diretório e da tabela
    unsigned dir_index = page_number / table->table_size;
    unsigned table_index = page_number % table->table_size;
    
    if (dir_index >= table->dir_size) {
        if (debug_level >= DEBUG_DETAILED) {
            printf("Directory index %u is outside bounds (size %u)\n", dir_index, table->dir_size);
        }
        return -1;
    }
    
    // Verifica se a tabela de segundo nível existe
    if (table->directory[dir_index] == NULL) {
        if (debug_level >= DEBUG_DETAILED) {
            printf("No page table exists for directory entry %u\n", dir_index);
        }
        return -1;
    }
    
    return table->directory[dir_index][table_index];
}

/**
 * Busca uma página na tabela de páginas hierárquica de três níveis
 */
int lookup_three_level(unsigned page_number) {
    ThreeLevelPageTable *table = (ThreeLevelPageTable *)page_table;
    
    // Calcula os índices para cada nível
    unsigned total_table_entries = table->mid_size * table->table_size;
    unsigned dir_index = page_number / total_table_entries;
    unsigned remaining = page_number % total_table_entries;
    unsigned mid_index = remaining / table->table_size;
    unsigned table_index = remaining % table->table_size;
    
    if (dir_index >= table->dir_size) {
        if (debug_level >= DEBUG_DETAILED) {
            printf("Top-level directory index %u is outside bounds (size %u)\n", dir_index, table->dir_size);
        }
        return -1;
    }
    
    // Verifica se o diretório de nível médio existe
    if (table->directory[dir_index] == NULL) {
        if (debug_level >= DEBUG_DETAILED) {
            printf("No mid-level directory exists for top entry %u\n", dir_index);
        }
        return -1;
    }
    
    // Verifica se a tabela de páginas existe
    if (table->directory[dir_index][mid_index] == NULL) {
        if (debug_level >= DEBUG_DETAILED) {
            printf("No page table exists for mid-level entry %u,%u\n", dir_index, mid_index);
        }
        return -1;
    }
    
    return table->directory[dir_index][mid_index][table_index];
}

/**
 * Busca uma página na tabela de páginas invertida
 */
int lookup_inverted(unsigned page_number) {
    InvertedPageTable *table = (InvertedPageTable *)page_table;
    
    // Procura através da tabela pela página virtual
    for (unsigned i = 0; i < table->size; i++) {
        if (table->valid[i] && table->virtual_pages[i] == page_number) {
            return i;  // Retorna o número do frame
        }
    }
    
    // Página não encontrada na tabela
    return -1;
}

/*** Funções de Atualização das Tabelas de Páginas ***/

/**
 * Atualiza uma entrada na tabela de páginas densa
 */
void update_dense(unsigned page_number, int frame_number) {
    DensePageTable *table = (DensePageTable *)page_table;
    
    if (page_number < table->size) {
        table->entries[page_number] = frame_number;
    } else {
        if (debug_level >= DEBUG_BASIC) {
            printf("Warning: Attempt to update page %u outside table bounds (size %u)\n", 
                   page_number, table->size);
        }
    }
}

/**
 * Atualiza uma entrada na tabela de páginas hierárquica de dois níveis
 */
void update_two_level(unsigned page_number, int frame_number) {
    TwoLevelPageTable *table = (TwoLevelPageTable *)page_table;
    
    unsigned dir_index = page_number / table->table_size;
    unsigned table_index = page_number % table->table_size;
    
    if (dir_index < table->dir_size) {
        // Aloca a tabela de segundo nível se ela não existir
        if (table->directory[dir_index] == NULL) {
            table->directory[dir_index] = (int *)malloc(table->table_size * sizeof(int));
            if (!table->directory[dir_index]) {
                perror("Failed to allocate second-level page table");
                exit(EXIT_FAILURE);
            }
            
            // Inicializa todas as entradas como -1 (não está na memória)
            for (unsigned i = 0; i < table->table_size; i++) {
                table->directory[dir_index][i] = -1;
            }
            
            if (debug_level >= DEBUG_DETAILED) {
                printf("Allocated new second-level page table for directory entry %u\n", dir_index);
            }
        }
        
        table->directory[dir_index][table_index] = frame_number;
    } else {
        if (debug_level >= DEBUG_BASIC) {
            printf("Warning: Attempt to update directory index %u outside bounds (size %u)\n", 
                   dir_index, table->dir_size);
        }
    }
}

/**
 * Atualiza uma entrada na tabela de páginas hierárquica de três níveis
 */
void update_three_level(unsigned page_number, int frame_number) {
    ThreeLevelPageTable *table = (ThreeLevelPageTable *)page_table;
    
    // Calcula os índices para cada nível
    unsigned total_table_entries = table->mid_size * table->table_size;
    unsigned dir_index = page_number / total_table_entries;
    unsigned remaining = page_number % total_table_entries;
    unsigned mid_index = remaining / table->table_size;
    unsigned table_index = remaining % table->table_size;
    
    if (dir_index < table->dir_size) {
        // Aloca o diretório de nível médio se ele não existir
        if (table->directory[dir_index] == NULL) {
            table->directory[dir_index] = (int **)malloc(table->mid_size * sizeof(int *));
            if (!table->directory[dir_index]) {
                perror("Failed to allocate mid-level directory");
                exit(EXIT_FAILURE);
            }
            
            // Inicializa todas as entradas como NULL
            for (unsigned i = 0; i < table->mid_size; i++) {
                table->directory[dir_index][i] = NULL;
            }
            
            if (debug_level >= DEBUG_DETAILED) {
                printf("Allocated new mid-level directory for top entry %u\n", dir_index);
            }
        }
        
        // Aloca a tabela de páginas se ela não existir
        if (table->directory[dir_index][mid_index] == NULL) {
            table->directory[dir_index][mid_index] = (int *)malloc(table->table_size * sizeof(int));
            if (!table->directory[dir_index][mid_index]) {
                perror("Failed to allocate bottom-level page table");
                exit(EXIT_FAILURE);
            }
            
            // Inicializa todas as entradas como -1 (não está na memória)
            for (unsigned i = 0; i < table->table_size; i++) {
                table->directory[dir_index][mid_index][i] = -1;
            }
            
            if (debug_level >= DEBUG_DETAILED) {
                printf("Allocated new page table for mid-level entry %u,%u\n", dir_index, mid_index);
            }
        }
        
        table->directory[dir_index][mid_index][table_index] = frame_number;
    } else {
        if (debug_level >= DEBUG_BASIC) {
            printf("Warning: Attempt to update top directory index %u outside bounds (size %u)\n", 
                   dir_index, table->dir_size);
        }
    }
}

/**
 * Atualiza uma entrada na tabela de páginas invertida
 */
void update_inverted(unsigned page_number, int frame_number) {
    InvertedPageTable *table = (InvertedPageTable *)page_table;
    
    // Se frame_number é -1, precisa encontrar e invalidar a entrada para esta página
    if (frame_number == -1) {
        for (unsigned i = 0; i < table->size; i++) {
            if (table->valid[i] && table->virtual_pages[i] == page_number) {
                table->valid[i] = false;
                if (debug_level >= DEBUG_DETAILED) {
                    printf("Invalidated entry for page %u in inverted page table\n", page_number);
                }
                break;
            }
        }
    } 
    // Caso contrário, atualiza ou adiciona a entrada para esta página
    else {
        if ((unsigned)frame_number < table->size) {
            table->virtual_pages[frame_number] = page_number;
            table->valid[frame_number] = true;
            
            if (debug_level >= DEBUG_DETAILED) {
                printf("Updated inverted page table entry: frame %d -> page %u\n", frame_number, page_number);
            }
        } else {
            if (debug_level >= DEBUG_BASIC) {
                printf("Warning: Attempt to update frame %d outside table bounds (size %u)\n", 
                      frame_number, table->size);
            }
        }
    }
}