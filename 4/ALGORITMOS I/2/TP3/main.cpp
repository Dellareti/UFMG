#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>  // para sprintf
#include <cstdlib> // para system
#include "resolvedor_caixeiro.hpp"
#include "medidor_recursos.hpp"

ResolvedorCaixeiro* criar_resolvedor(char estrategia, const std::vector<Aresta>& arestas, int n) {
    switch (estrategia) {
        case 'b':
            return new ResolvedorForcaBruta(arestas, n);
        case 'd':
            return new ResolvedorDinamico(arestas, n);
        case 'g':
            return new ResolvedorGuloso(arestas, n);
        default:
            return nullptr;
    }
}

// Arquivo para guardar as métricas
const char* ARQUIVO_METRICAS = "metricas.txt";

void salvar_metricas(char estrategia, int num_cidades, long tempo_ms, long memoria_kb, int custo) {
    const char* nome_estrategia = "";
    switch(estrategia) {
        case 'b': nome_estrategia = "ForcaBruta"; break;
        case 'd': nome_estrategia = "ProgDinamica"; break;
        case 'g': nome_estrategia = "Guloso"; break;
    }

    // Cria o diretório se não existir
    system("mkdir -p metricas");

    // Salva em arquivo separado para cada estratégia
    char nome_arquivo[100];
    sprintf(nome_arquivo, "metricas/%s.csv", nome_estrategia);

    // Cria arquivo se não existir ou abre para append
    bool arquivo_existe = (access(nome_arquivo, F_OK) != -1);
    FILE* arquivo = fopen(nome_arquivo, "a");

    if (arquivo) {
        // Escreve cabeçalho se arquivo for novo
        if (!arquivo_existe) {
            fprintf(arquivo, "num_cidades,tempo_ms,memoria_kb,custo\n");
        }
        fprintf(arquivo, "%d,%ld,%ld,%d\n", num_cidades, tempo_ms, memoria_kb, custo);
        fclose(arquivo);
    }
}

int main() {
    char estrategia;
    int V, E;
    
    // Lê a estratégia
    std::cin >> estrategia;
    
    // Lê o número de vértices e arestas
    std::cin >> V >> E;
    
    std::vector<Aresta> arestas;
    
    // Lê as arestas
    for (int i = 0; i < E; i++) {
        Aresta aresta;
        std::cin >> aresta.cidade1 >> aresta.cidade2 >> aresta.distancia;
        arestas.push_back(aresta);
    }
    
    // Cria o resolvedor apropriado
    ResolvedorCaixeiro* resolvedor = criar_resolvedor(estrategia, arestas, V);
    
    if (resolvedor != nullptr) {
        MedidorRecursos medidor;
        
        // Inicia medição
        medidor.iniciar();
        
        // Resolve o problema
        std::pair<int, std::vector<int>> resultado = resolvedor->resolver();
        int custo = resultado.first;
        std::vector<int> caminho = resultado.second;
        
        // Finaliza medição
        medidor.parar();
        
        // Salva métricas
        salvar_metricas(estrategia, V, medidor.obter_tempo(), 
                       medidor.obter_memoria(), custo);
        
        // Imprime a solução
        std::cout << custo << std::endl;
        
        // Imprime o caminho
        std::string resultado_final;
        resultado_final = resolvedor->obter_cidade_nome(0);  // Primeira cidade
        for (size_t i = 0; i < caminho.size(); i++) {
            resultado_final += " " + resolvedor->obter_cidade_nome(caminho[i]);
        }
        std::cout << resultado_final << std::endl;
        
        // Libera a memória
        delete resolvedor;
    }
    
    return 0;
}