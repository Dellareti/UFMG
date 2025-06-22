#include "simulador.h"

extern Frame *physical_memory;
extern unsigned total_frames;
extern int debug_level;

/**
 * Algoritmo de substituição de páginas aleatório
 * Retorna o número do frame a ser substituído
 */
int random_replacement() {
    int victim_frame = random() % total_frames;
    
    if (debug_level >= DEBUG_DETAILED) {
        printf("  Random replacement selected frame %d\n", victim_frame);
    }
    
    return victim_frame;
}

/**
 * Algoritmo de substituição LRU (Least Recently Used)
 * Retorna o número do frame menos recentemente usado
 */
int lru_replacement() {
    unsigned long min_time = ULONG_MAX;
    int victim_frame = -1;
    
    // Encontra o frame que foi usado há mais tempo
    for (unsigned i = 0; i < total_frames; i++) {
        if (physical_memory[i].valid && physical_memory[i].last_used < min_time) {
            min_time = physical_memory[i].last_used;
            victim_frame = i;
        }
    }
    
    if (victim_frame == -1) {
        // Não deveria acontecer se a memória estiver cheia, mas por precaução
        victim_frame = 0;
        
        if (debug_level >= DEBUG_BASIC) {
            printf("  Warning: LRU could not find a valid frame, using frame 0\n");
        }
    } else if (debug_level >= DEBUG_DETAILED) {
        printf("  LRU selected frame %d (last used at time %lu)\n", 
               victim_frame, physical_memory[victim_frame].last_used);
    }
    
    return victim_frame;
}

/**
 * Algoritmo de substituição LFU (Least Frequently Used)
 * Retorna o número do frame menos frequentemente usado
 */
int lfu_replacement() {
    unsigned min_count = UINT_MAX;
    int victim_frame = -1;
    
    // Encontra o frame que foi acessado menos vezes
    for (unsigned i = 0; i < total_frames; i++) {
        if (physical_memory[i].valid && physical_memory[i].access_count < min_count) {
            min_count = physical_memory[i].access_count;
            victim_frame = i;
        }
    }
    
    if (victim_frame == -1) {
        // Não deveria acontecer se a memória estiver cheia, mas por precaução
        victim_frame = 0;
        
        if (debug_level >= DEBUG_BASIC) {
            printf("  Warning: LFU could not find a valid frame, using frame 0\n");
        }
    } else if (debug_level >= DEBUG_DETAILED) {
        printf("  LFU selected frame %d (access count %u)\n", 
               victim_frame, physical_memory[victim_frame].access_count);
    }
    
    return victim_frame;
}

/**
 * Algoritmo de substituição Clock (algoritmo de segunda chance)
 * Retorna o número do frame a ser substituído usando ponteiro circular
 */
int clock_replacement() {
    // Variável estática para manter a posição do ponteiro
    static unsigned hand = 0;
    
    // Posição inicial do ponteiro para esta iteração
    unsigned initial_hand = hand;
    
    // Continua avançando o ponteiro até encontrar um frame com bit de referência = false
    do {
        // Se o bit de referência é false, encontramos nossa vítima
        if (physical_memory[hand].valid && !physical_memory[hand].referenced) {
            int victim = hand;
            // Avança o ponteiro para a próxima vez
            hand = (hand + 1) % total_frames;
            
            if (debug_level >= DEBUG_DETAILED) {
                printf("  Clock selected frame %d (not referenced)\n", victim);
            }
            
            return victim;
        }
        
        // Caso contrário, dá uma segunda chance e limpa o bit de referência
        physical_memory[hand].referenced = false;
        
        if (debug_level >= DEBUG_VERBOSE) {
            printf("  Clock giving second chance to frame %d\n", hand);
        }
        
        // Avança o ponteiro
        hand = (hand + 1) % total_frames;
    } while (hand != initial_hand);
    
    // Se deu uma volta completa e todos os frames foram referenciados,
    // pega a posição atual do ponteiro (que agora tem seu bit de referência limpo)
    int victim = hand;
    // Avança o ponteiro para a próxima vez
    hand = (hand + 1) % total_frames;
    
    if (debug_level >= DEBUG_DETAILED) {
        printf("  Clock selected frame %d (all frames were referenced)\n", victim);
    }
    
    return victim;
}