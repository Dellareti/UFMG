#include "estado.h"
#include <iostream>
#include <set>
#include <map>
#include <queue>

// Inicializa o Estado
Estado::Estado(int v) : numero_de_vertices(v) {
    lista_adjacencia.resize(v);
}

void Estado::adiciona_cidade(const std::string &cidade, int indice) {
    cidade_para_indice[cidade] = indice;
    indice_para_cidade[indice] = cidade;
}

void Estado::adiciona_estrada(const std::string &origem, const std::string &destino) {
    int origem_id = cidade_para_indice[origem];
    int destino_id = cidade_para_indice[destino];
    lista_adjacencia[origem_id].push_back(destino_id);
}

// BFS para encontrar as distâncias mínimas de um vértice (inicio) para todos os outros
std::vector<int> Estado::busca_em_largura(int inicio) const {
    std::vector<int> distancias(numero_de_vertices, -1);
    std::vector<int> fila;

    distancias[inicio] = 0;
    fila.push_back(inicio);
    size_t atual = 0;

    while (atual < fila.size()) {
        int v = fila[atual++];
        for (int u: lista_adjacencia[v]) {
            if (distancias[u] == -1) {
                distancias[u] = distancias[v] + 1;
                fila.push_back(u);
            }
        }
    }

    return distancias;
}

//  Determina qual cidade tem a menor distância até todas as outras cidades
std::string Estado::calcula_capital() const {
    int melhor_capital = -1;
    int menor_distancia_maxima = numero_de_vertices + 1;

    for (int inicio = 0; inicio < numero_de_vertices; inicio++) {
        std::vector<int> distancias = busca_em_largura(inicio);

        // Verifica se todos vértices são alcançáveis
        bool todas_cidades_alcancaveis = true;
        int distancia_maxima_atual = 0;

        for (int i = 0; i < numero_de_vertices; i++) {
            if (i != inicio && distancias[i] == -1) {
                todas_cidades_alcancaveis = false;
                break;
            }
            if (distancias[i] > distancia_maxima_atual) {
                distancia_maxima_atual = distancias[i];
            }
        }

        if (todas_cidades_alcancaveis && distancia_maxima_atual < menor_distancia_maxima) {
            menor_distancia_maxima = distancia_maxima_atual;
            melhor_capital = inicio;
        }
    }

    return indice_para_cidade.at(melhor_capital);
}

// PARTE 2

void Estado::transpor_grafo() {
    lista_adjacencia_transposta.resize(numero_de_vertices);
    for (int i = 0; i < numero_de_vertices; i++) {
        for (int j: lista_adjacencia[i]) {
            lista_adjacencia_transposta[j].push_back(i);
        }
    }
}

void Estado::dfs1(int v) {
    //KOSARAJU PT1
    visitados[v] = true;
    for (int u: lista_adjacencia[v]) {
        if (!visitados[u]) {
            dfs1(u);
        }
    }
    pilha.push(v);
}

void Estado::dfs2(int v) {
    //KOSARAJU PT2
    visitados_transposto[v] = true;
    componentes[v] = quantidade_componentes;
    for (int u: lista_adjacencia_transposta[v]) {
        if (!visitados_transposto[u]) {
            dfs2(u);
        }
    }
}

void Estado::insert_ordenado_por_distancia(std::vector<std::pair<std::string, int> > &vec,
                                           const std::string &cidade,
                                           int distancia) {
    size_t pos = 0;
    // Encontra a posição correta baseada primeiro na distância e depois alfabetica
    while (pos < vec.size() &&
           (vec[pos].second < distancia ||
            (vec[pos].second == distancia && vec[pos].first < cidade))) {
        pos++;
    }
    vec.insert(vec.begin() + pos, {cidade, distancia});
}

std::pair<int, std::vector<std::string> > Estado::calcula_batalhao() {
    // Inicialização
    visitados.assign(numero_de_vertices, false);
    visitados_transposto.assign(numero_de_vertices, false);
    componentes.assign(numero_de_vertices, -1);
    while (!pilha.empty()) pilha.pop();
    quantidade_componentes = 0;

    // Primeira DFS
    for (int i = 0; i < numero_de_vertices; i++) {
        if (!visitados[i]) {
            dfs1(i);
        }
    }

    // Transpõe o grafo
    transpor_grafo();

    // Segunda DFS
    while (!pilha.empty()) {
        int v = pilha.top();
        pilha.pop();
        if (!visitados_transposto[v]) {
            dfs2(v);
            quantidade_componentes++;
        }
    }

    // Encontra a capital e calcula as distâncias a partir dela
    std::string capital = calcula_capital();
    int capital_id = cidade_para_indice[capital];
    int componente_capital = componentes[capital_id];
    std::vector<int> distancias = busca_em_largura(capital_id);

    // Para cada componente, vamos guardar todas as suas cidades
    std::map<int, std::vector<int> > cidades_por_componente;
    for (int i = 0; i < numero_de_vertices; i++) {
        if (componentes[i] != componente_capital) {
            cidades_por_componente[componentes[i]].push_back(i);
        }
    }

    // Estrutura para armazenar as cidades com suas distâncias
    std::vector<std::pair<std::string, int>> cidades_com_distancias;
    std::set<int> cfcs_processados;

    // Para cada componente, escolhe a cidade mais próxima da capital
    for (const auto &[componente, cidades]: cidades_por_componente) {
        if (cfcs_processados.find(componente) == cfcs_processados.end()) {
            cfcs_processados.insert(componente);

            // Encontra a cidade do componente mais próxima da capital
            int cidade_mais_proxima = cidades[0];
            int menor_distancia = distancias[cidade_mais_proxima];

            for (int cidade: cidades) {
                if (distancias[cidade] != -1 && distancias[cidade] < menor_distancia) {
                    menor_distancia = distancias[cidade];
                    cidade_mais_proxima = cidade;
                }
            }

            // Insere a cidade na posição correta baseada na distância
            insert_ordenado_por_distancia(cidades_com_distancias,
                                          indice_para_cidade[cidade_mais_proxima],
                                          menor_distancia);
        }
    }

    // Extrai apenas os nomes das cidades que já estão na ordem correta
    std::vector<std::string> cfcs_nomes;
    for (const auto &[cidade, distancia]: cidades_com_distancias) {
        cfcs_nomes.push_back(cidade);
    }

    return {quantidade_componentes - 1, cfcs_nomes};
}

// PARTE 3

bool Estado::e_alcancavel(const std::vector<std::vector<int>>& g, int origem, int destino) {
    std::vector<bool> visitado(numero_de_vertices, false);
    std::queue<int> fila;
    
    fila.push(origem);
    visitado[origem] = true;
    
    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        
        if (atual == destino) return true;
        
        for (int proximo : g[atual]) {
            if (!visitado[proximo]) {
                visitado[proximo] = true;
                fila.push(proximo);
            }
        }
    }
    
    return false;
}

bool Estado::verifica_graus_euler(const std::vector<std::vector<int>>& g) {
    std::vector<int> grau_entrada(numero_de_vertices, 0);
    std::vector<int> grau_saida(numero_de_vertices, 0);
    int vertices_ativos = 0;
    
    // Calcula graus e conta vértices ativos
    for (int i = 0; i < numero_de_vertices; i++) {
        grau_saida[i] = static_cast<int>(g[i].size());
        if (grau_saida[i] > 0) {
            vertices_ativos++;
        }
        for (int v : g[i]) {
            grau_entrada[v]++;
        }
    }
    
    // Verifica se os vértices ativos formam um ciclo válido
    int vertices_ciclo = 0;
    for (int i = 0; i < numero_de_vertices; i++) {
        if (grau_entrada[i] > 0 || grau_saida[i] > 0) {
            if (grau_entrada[i] == grau_saida[i]) {
                vertices_ciclo++;
            }
        }
    }
    
    return vertices_ciclo == vertices_ativos && vertices_ativos > 0;
}

void Estado::encontrar_ciclo_euler(int v, std::vector<std::vector<int>>& g,
                                 std::vector<int>& ciclo) {
    while (!g[v].empty()) {
        int u = g[v].back();
        g[v].pop_back();
        encontrar_ciclo_euler(u, g, ciclo);
    }
    ciclo.push_back(v);
}

std::vector<int> Estado::obter_ciclo_euler(int inicio, std::vector<std::vector<int>> g) {
    std::vector<int> ciclo;
    
    if (!verifica_graus_euler(g) || !e_alcancavel(g, inicio, inicio)) {
        return ciclo;
    }
    
    encontrar_ciclo_euler(inicio, g, ciclo);
    
    if (ciclo.size() <= 1) return std::vector<int>();
    
    // Inverte o ciclo e remove a última cidade
    std::vector<int> ciclo_correto;
    for (int i = static_cast<int>(ciclo.size()) - 1; i > 0; i--) {
        ciclo_correto.push_back(ciclo[i]);
    }
    
    return ciclo_correto;
}

void Estado::dfs_componente_local(int v, std::vector<std::vector<int>>& subgrafo,
                                std::vector<bool>& visitado,
                                std::vector<bool>& no_subgrafo,
                                int origem) {
    visitado[v] = true;
    no_subgrafo[v] = true;
    
    for (int u : lista_adjacencia[v]) {
        subgrafo[v].push_back(u);
        if (u == origem || !visitado[u]) {
            if (!visitado[u]) {
                dfs_componente_local(u, subgrafo, visitado, no_subgrafo, origem);
            }
        }
    }
}

std::pair<int, std::vector<std::vector<int>>> Estado::calcula_patrulhamento() {
    std::vector<std::vector<int>> patrulhas_possiveis;
    std::string capital = calcula_capital();
    int capital_id = cidade_para_indice[capital];
    
    auto [num_batalhoes, batalhoes] = calcula_batalhao();
    
    // Verifica ciclos para cada batalhão (incluindo a capital)
    std::vector<int> todos_batalhoes;
    todos_batalhoes.push_back(capital_id);
    for (const auto& cidade : batalhoes) {
        todos_batalhoes.push_back(cidade_para_indice[cidade]);
    }
    
    for (int batalhao_id : todos_batalhoes) {
        std::vector<std::vector<int>> subgrafo(numero_de_vertices);
        std::vector<bool> visitado(numero_de_vertices, false);
        std::vector<bool> no_subgrafo(numero_de_vertices, false);
        
        dfs_componente_local(batalhao_id, subgrafo, visitado, no_subgrafo, batalhao_id);
        
        // Adiciona arestas faltantes no subgrafo
        for (int i = 0; i < numero_de_vertices; i++) {
            if (no_subgrafo[i]) {
                for (int v : lista_adjacencia[i]) {
                    if (no_subgrafo[v]) {
                        bool aresta_existe = false;
                        for (int adj : subgrafo[i]) {
                            if (adj == v) {
                                aresta_existe = true;
                                break;
                            }
                        }
                        if (!aresta_existe) {
                            subgrafo[i].push_back(v);
                        }
                    }
                }
            }
        }
        
        if (batalhao_id == capital_id) {
            auto ciclo_completo = obter_ciclo_euler(capital_id, lista_adjacencia);
            if (!ciclo_completo.empty()) {
                patrulhas_possiveis.push_back(ciclo_completo);
                continue;
            }
        }
        
        auto ciclo = obter_ciclo_euler(batalhao_id, subgrafo);
        if (!ciclo.empty()) {
            patrulhas_possiveis.push_back(ciclo);
        }
    }
    
    return {static_cast<int>(patrulhas_possiveis.size()), patrulhas_possiveis};
}