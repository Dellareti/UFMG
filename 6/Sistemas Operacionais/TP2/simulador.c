#include "simulador.h"

unsigned page_size_kb;       
unsigned memory_size_kb;     
unsigned total_frames;       
unsigned s_bits;           
unsigned access_time;       
int debug_level = DEBUG_NONE; 

unsigned long total_accesses = 0;
unsigned long page_reads = 0;
unsigned long page_writes = 0;

Frame *physical_memory;

int current_page_table_type;
void *page_table;
int (*replacement_algorithm)(void);
int (*lookup_function)(unsigned);
void (*update_function)(unsigned, int);

/**
 * Calcula o número da página a partir de um endereço de memória
 */
unsigned get_page_number(unsigned address) {
    return address >> s_bits;
}

/**
 * Inicializa o simulador com base nos parâmetros da linha de comando
 */
void initialize(unsigned alg_type, unsigned page_size, unsigned memory_size, int page_table_type) {
    // Armazena os parâmetros
    page_size_kb = page_size;
    memory_size_kb = memory_size;
    
    // Calcula valores derivados
    total_frames = memory_size_kb / page_size_kb;
    
    // Calcula o valor de s (bits de offset da página)
    unsigned tmp = page_size_kb * 1024;
    s_bits = 0;
    while (tmp > 1) {
        tmp = tmp >> 1;
        s_bits++;
    }
    
    // Inicializa contador de tempo de acesso
    access_time = 0;
    
    // Aloca memória física
    physical_memory = (Frame *)malloc(total_frames * sizeof(Frame));
    if (!physical_memory) {
        perror("Failed to allocate physical memory");
        exit(EXIT_FAILURE);
    }
    
    // Inicializa frames da memória física
    for (unsigned i = 0; i < total_frames; i++) {
        physical_memory[i].valid = false;
        physical_memory[i].dirty = false;
        physical_memory[i].last_used = 0;
        physical_memory[i].access_count = 0;
        physical_memory[i].referenced = false;
    }
    
    // Define algoritmo de substituição de páginas
    switch (alg_type) {
        case REPLACEMENT_RANDOM:
            replacement_algorithm = random_replacement;
            break;
        case REPLACEMENT_LRU:
            replacement_algorithm = lru_replacement;
            break;
        case REPLACEMENT_LFU:
            replacement_algorithm = lfu_replacement;
            break;
        case REPLACEMENT_CLOCK:
            replacement_algorithm = clock_replacement;
            break;
        default:
            fprintf(stderr, "Invalid replacement algorithm\n");
            exit(EXIT_FAILURE);
    }
    
    current_page_table_type = page_table_type;
    
    // Inicializa o tipo de tabela de páginas selecionado
    switch (page_table_type) {
        case PAGE_TABLE_DENSE:
            lookup_function = lookup_dense;
            update_function = update_dense;
            break;
        case PAGE_TABLE_HIERARCHY_2LEVEL:
            lookup_function = lookup_two_level;
            update_function = update_two_level;
            break;
        case PAGE_TABLE_HIERARCHY_3LEVEL:
            lookup_function = lookup_three_level;
            update_function = update_three_level;
            break;
        case PAGE_TABLE_INVERTED:
            lookup_function = lookup_inverted;
            update_function = update_inverted;
            break;
        default:
            fprintf(stderr, "Invalid page table type\n");
            exit(EXIT_FAILURE);
    }
    
    srandom(time(NULL));
}

/**
 * Processa um acesso à memória - núcleo da simulação
 */
void handle_memory_access(unsigned address, char access_type) {
    access_time++;
    total_accesses++;
    
    // Calcula o número da página a partir do endereço
    unsigned page_number = get_page_number(address);
    
    if (debug_level >= DEBUG_BASIC) {
        printf("Access #%u: Address 0x%08x, Page %u, Type %c\n", access_time, address, page_number, access_type);
    }
    
    int frame_number = lookup_function(page_number);
    
    // Verifica se a página já está na memória
    if (frame_number != -1) {
        if (debug_level >= DEBUG_DETAILED) {
            printf("  Page hit: page %u found in frame %d\n", page_number, frame_number);
        }
        
        // Atualiza metadados do frame para este acesso
        physical_memory[frame_number].last_used = access_time;
        physical_memory[frame_number].access_count++;
        physical_memory[frame_number].referenced = true;
        
        // Se for uma escrita, marca a página como suja
        if (access_type == 'W') {
            physical_memory[frame_number].dirty = true;
            
            if (debug_level >= DEBUG_DETAILED) {
                printf("  Marked frame %d as dirty\n", frame_number);
            }
        }
    } else {
        if (debug_level >= DEBUG_BASIC) {
            printf("  Page fault: page %u not in memory\n", page_number);
        }
        
        page_reads++;
        
        bool memory_full = true;
        for (unsigned i = 0; i < total_frames; i++) {
            if (!physical_memory[i].valid) {
                frame_number = i;
                memory_full = false;
                break;
            }
        }
        
        // Se a memória estiver cheia, precisa substituir uma página
        if (memory_full) {
            frame_number = replacement_algorithm();
            
            if (debug_level >= DEBUG_DETAILED) {
                printf("  Memory full, replacing frame %d (page %u)\n", frame_number, physical_memory[frame_number].page_number);
            }
            
            // Se a página a ser substituída estiver suja, precisa escrevê-la de volta
            if (physical_memory[frame_number].dirty) {
                page_writes++;
                
                if (debug_level >= DEBUG_DETAILED) {
                    printf("  Writing dirty page %u back to disk\n", physical_memory[frame_number].page_number);
                }
            }
            
            // Remove o mapeamento da página antiga
            update_function(physical_memory[frame_number].page_number, -1);
        } else {
            if (debug_level >= DEBUG_DETAILED) {
                printf("  Using empty frame %d\n", frame_number);
            }
        }
        
        // Carrega a nova página no frame
        physical_memory[frame_number].page_number = page_number;
        physical_memory[frame_number].valid = true;
        physical_memory[frame_number].dirty = (access_type == 'W');
        physical_memory[frame_number].last_used = access_time;
        physical_memory[frame_number].access_count = 1;
        physical_memory[frame_number].referenced = true;
        
        update_function(page_number, frame_number);
        
        if (debug_level >= DEBUG_DETAILED) {
            printf("  Loaded page %u into frame %d\n", page_number, frame_number);
        }
    }
}

/**
 * Imprime as estatísticas finais
 */
void print_statistics(const char *algorithm_name, const char *input_file) {
    printf("Executando o simulador...\n");
    printf("Arquivo de entrada: %s\n", input_file);
    printf("Tamanho da memória: %u KB\n", memory_size_kb);
    printf("Tamanho das páginas: %u KB\n", page_size_kb);
    printf("Técnica de reposição: %s\n", algorithm_name);
    
    // Imprime informações do tipo de tabela de páginas
    const char *table_names[] = {"Densa", "Hierárquica 2 níveis", "Hierárquica 3 níveis", "Invertida"};
    printf("Tipo de tabela de páginas: %s\n", table_names[current_page_table_type]);
    
    printf("Páginas lidas: %lu\n", page_reads);
    printf("Páginas escritas: %lu\n", page_writes);    
    printf("Taxa de page faults: %.2f%%\n", (page_reads * 100.0) / total_accesses);
    
    // Estatísticas adicionais se em modo debug
    if (debug_level >= DEBUG_BASIC) {
        printf("\nEstatísticas adicionais:\n");
        printf("Total de acessos à memória: %lu\n", total_accesses);
    }
}

/**
 * Inicializa a estrutura de tabela de páginas apropriada
 */
void initialize_page_table(int page_table_type) {
    unsigned address_bits = 32;
    
    switch (page_table_type) {
        case PAGE_TABLE_DENSE:
            initialize_dense_page_table(address_bits);
            break;
        case PAGE_TABLE_HIERARCHY_2LEVEL:
            initialize_two_level_page_table(address_bits);
            break;
        case PAGE_TABLE_HIERARCHY_3LEVEL:
            initialize_three_level_page_table(address_bits);
            break;
        case PAGE_TABLE_INVERTED:
            initialize_inverted_page_table();
            break;
    }
}

/**
 * Mapeia nome do algoritmo para tipo do algoritmo
 */
int get_algorithm_type(const char *name) {
    if (strcmp(name, "random") == 0) {
        return REPLACEMENT_RANDOM;
    } else if (strcmp(name, "lru") == 0) {
        return REPLACEMENT_LRU;
    } else if (strcmp(name, "lfu") == 0) {
        return REPLACEMENT_LFU;
    } else if (strcmp(name, "clock") == 0) {
        return REPLACEMENT_CLOCK;
    } else {
        fprintf(stderr, "Unknown algorithm: %s\n", name);
        exit(EXIT_FAILURE);
    }
}

/**
 * Limpa os recursos alocados
 */
void cleanup() {
    free(physical_memory);
    
    // Libera a estrutura de tabela de páginas apropriada
    switch (current_page_table_type) {
        case PAGE_TABLE_DENSE:
            cleanup_dense_page_table();
            break;
        case PAGE_TABLE_HIERARCHY_2LEVEL:
            cleanup_two_level_page_table();
            break;
        case PAGE_TABLE_HIERARCHY_3LEVEL:
            cleanup_three_level_page_table();
            break;
        case PAGE_TABLE_INVERTED:
            cleanup_inverted_page_table();
            break;
    }
}

/**
 * Função principal do simulador
 */
int main(int argc, char *argv[]) {
    // Verifica se o número correto de argumentos foi fornecido
    if (argc < 5 || argc > 7) {
        fprintf(stderr, "Uso: %s <algoritmo> <log_file> <page_size_kb> <memory_size_kb> [tabela_tipo/debug_level] [debug_level]\n", argv[0]);
        fprintf(stderr, "Algoritmos: random, lru, lfu, clock\n");
        fprintf(stderr, "Tipos de tabela: 0=Densa, 1=Hierárquica 2 níveis, 2=Hierárquica 3 níveis, 3=Invertida\n");
        fprintf(stderr, "Níveis de debug: 0=Nenhum, 1=Básico, 2=Detalhado, 3=Verboso, 8=Benchmark, 9=Gerar padrões\n");
        return EXIT_FAILURE;
    }
    
    const char *algorithm_name = argv[1];
    const char *input_file_name = argv[2];
    unsigned page_size = atoi(argv[3]);
    unsigned memory_size = atoi(argv[4]);
    
    int page_table_type = PAGE_TABLE_DENSE;  
    
    // Trata argumentos opcionais
    if (argc >= 6) {
        int arg5_value = atoi(argv[5]);
        
        if (argc == 6) {
            if (arg5_value <= 3) {
                // Assume que é tipo de tabela se estiver entre 0-3
                page_table_type = arg5_value;
            } else {
                // Assume que é nível de debug se for > 3
                debug_level = arg5_value;
            }
        } else if (argc == 7) {
            // Primeiro arg opcional é tipo de tabela, segundo é nível de debug
            page_table_type = arg5_value;
            debug_level = atoi(argv[6]);
        }
    }
    
    // Valida tipo de tabela
    if (page_table_type < 0 || page_table_type > 3) {
        fprintf(stderr, "Tipo de tabela inválido. Deve ser entre 0 e 3.\n");
        return EXIT_FAILURE;
    }
    
    // Verifica modos especiais de debug primeiro
    if (debug_level == 9) {
        printf("Gerando arquivos de padrões de teste...\n");
        create_test_files();
        printf("Arquivos de teste gerados com sucesso!\n");
        return EXIT_SUCCESS;
    }
    
    if (debug_level == 8) {
        printf("Executando benchmark das tabelas de páginas...\n");
        benchmark_page_tables(input_file_name);
        return EXIT_SUCCESS;
    }
    
    // Valida entradas
    if (page_size < 2 || page_size > 64) {
        fprintf(stderr, "Tamanho de página inválido. Deve estar entre 2 e 64 KB.\n");
        return EXIT_FAILURE;
    }
    
    if (memory_size < 128 || memory_size > 16384) {
        fprintf(stderr, "Tamanho da página deve ser uma potência de 2.\n");
        return EXIT_FAILURE;
    }
    
    unsigned tmp = page_size;
    bool is_power_of_two = (tmp != 0) && ((tmp & (tmp - 1)) == 0);

    if (!is_power_of_two) {
        fprintf(stderr, "Page size must be a power of 2.\n");
        return EXIT_FAILURE;
    }
    
    // Mapeia nome do algoritmo para tipo
    int algorithm_type = get_algorithm_type(algorithm_name);
    
    initialize(algorithm_type, page_size, memory_size, page_table_type);
    initialize_page_table(page_table_type);
    
    // Abre o arquivo de entrada
    FILE *input_file = fopen(input_file_name, "r");

    if (!input_file) {
        perror("Failed to open input file");
        cleanup();
        return EXIT_FAILURE;
    }
    
    // Processa cada acesso à memória
    unsigned addr;
    char rw;
    
    while (fscanf(input_file, "%x %c", &addr, &rw) == 2) {
        handle_memory_access(addr, rw);
    }
    
    print_statistics(algorithm_name, input_file_name);
    
    fclose(input_file);
    cleanup();
    
    return EXIT_SUCCESS;
}