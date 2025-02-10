#ifndef ESTADO_H
#define ESTADO_H

#include <vector>
#include <string>
#include <map>
#include <stack>
#include <set>
#include <queue>

// Definição da classe Estado
class Estado {
    private:
        // Atributos relacionados ao grafo (número de vértices, mapas de cidade-índice, listas de adjacência, etc.)
        int numero_de_vertices;
        std::map<std::string, int> cidade_para_indice;
        std::vector<std::vector<int>> lista_adjacencia;
        std::vector<bool> visitados;
        std::vector<bool> visitados_transposto;
        std::vector<std::vector<int>> lista_adjacencia_transposta;
        std::vector<int> componentes;
        std::stack<int> pilha;
        int quantidade_componentes;
        
        // Funções auxiliares para realizar operações no grafo, como encontrar caminho do carteiro chinês, verificar ciclo euleriano, etc.
        std::vector<int> encontrar_caminho_carteiro_chines(int inicio);
        void inverter_caminho(std::vector<int>& caminho);
        bool tem_ciclo_euleriano(const std::vector<std::vector<int>>& adj); 
        void dfs_ciclo(int atual, std::vector<std::vector<int>>& adj_local, std::vector<int>& caminho); 
        void dfs_componente(int v, std::vector<std::vector<int>>& subgrafo, std::vector<bool>& visitado);
        // Métodos relacionados a ciclos eulerianos
        bool e_alcancavel(const std::vector<std::vector<int>>& g, int origem, int destino);
        bool verifica_graus_euler(const std::vector<std::vector<int>>& g);
        void encontrar_ciclo_euler(int v, std::vector<std::vector<int>>& g, std::vector<int>& ciclo);
        std::vector<int> obter_ciclo_euler(int inicio, std::vector<std::vector<int>> g);
        void dfs_componente_local(int v, std::vector<std::vector<int>>& subgrafo,
                                std::vector<bool>& visitado,
                                std::vector<bool>& no_subgrafo,
                                int origem);

    public:
        // Construtor que inicializa o número de vértices
        Estado(int v);
        std::map<int, std::string> indice_para_cidade;

        // Métodos para adicionar cidades e estradas
        void adiciona_cidade(const std::string& cidade, int indice);
        void adiciona_estrada(const std::string& origem, const std::string& destino);

        // Métodos  principais
        std::vector<int> busca_em_largura(int inicio) const;
        std::string calcula_capital() const;    
        void transpor_grafo();
        void dfs1(int v);
        void dfs2(int v);
        void insert_ordenado_por_distancia(std::vector<std::pair<std::string, int>>& vec,
                                        const std::string& cidade, int distancia);
        std::pair<int, std::vector<std::string>> calcula_batalhao();
        std::pair<int, std::vector<std::vector<int>>> calcula_patrulhamento();
};

#endif // ESTADO_H