#include "rede_eletrica.hpp"
#include <queue>

// Valor máximo para capacidade infinita para o Ford-Fulkerson
const int INFINITO = 0x3f3f3f3f;

// Inicializa estruturas da rede
RedeEletrica::RedeEletrica(int vertices) : numero_vertices(vertices) {
    capacidade.resize(vertices + 2, std::vector<int>(vertices + 2, 0));
    fluxo.resize(vertices + 2, std::vector<int>(vertices + 2, 0));
    demandas.resize(vertices, 0);
    eh_gerador.resize(vertices, false);
}

// Adiciona conexão entre vértices
void RedeEletrica::adicionar_conexao(int origem, int destino, int cap) {
    capacidade[origem-1][destino-1] = cap;
}

// Define tipo do nó (gerador ou consumidor)
void RedeEletrica::definir_tipo_no(int no, int tipo) {
    no--;
    if (tipo == 0) {
        eh_gerador[no] = true;
    } else {
        demandas[no] = tipo;
    }
}

int RedeEletrica::valor_minimo(int a, int b) {
    return (a < b) ? a : b;
}

// BFS para encontrar caminhos aumentantes
bool RedeEletrica::busca_em_largura(std::vector<std::vector<int>>& grafo_residual, int fonte, int sumidouro, std::vector<int>& pai) {

    std::vector<bool> visitado(numero_vertices + 2, false);
    std::queue<int> fila;
    
    fila.push(fonte);
    visitado[fonte] = true;
    pai[fonte] = -1;

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        // Verifica todos os vértices para caminhos possíveis
        for (int proximo = 0; proximo < numero_vertices + 2; proximo++) {
            // Se há capacidade residual e não foi visitado
            if (!visitado[proximo] && grafo_residual[atual][proximo] > 0) {
                pai[proximo] = atual;
                visitado[proximo] = true;
                fila.push(proximo);

                if (proximo == sumidouro) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Implementação do Ford-Fulkerson
int RedeEletrica::ford_fulkerson(std::vector<std::vector<int>>& capacidade_atual, int fonte, int sumidouro) {

    std::vector<std::vector<int>> grafo_residual = capacidade_atual;
    std::vector<int> pai(numero_vertices + 2);
    int fluxo_maximo = 0;

    // Zera a matriz de fluxo
    for (int i = 0; i < numero_vertices + 2; i++) {
        for (int j = 0; j < numero_vertices + 2; j++) {
            fluxo[i][j] = 0;
        }
    }

    // Enquanto existir caminho aumentante
    while (busca_em_largura(grafo_residual, fonte, sumidouro, pai)) {
        // Encontra a capacidade mínima no caminho
        int fluxo_caminho = INFINITO;
        for (int v = sumidouro; v != fonte; v = pai[v]) {
            int u = pai[v];
            fluxo_caminho = valor_minimo(fluxo_caminho, grafo_residual[u][v]);
        }

        // Atualiza fluxos e grafo residual
        for (int v = sumidouro; v != fonte; v = pai[v]) {
            int u = pai[v];
            grafo_residual[u][v] -= fluxo_caminho;
            grafo_residual[v][u] += fluxo_caminho;

            // Atualiza matriz de fluxo somente para vértices originais
            if (u < numero_vertices && v < numero_vertices) {
                fluxo[u][v] += fluxo_caminho;
                // Atualiza também fluxo reverso
                if (capacidade_atual[v][u] > 0) {
                    fluxo[v][u] -= fluxo_caminho;
                }
            }
        }
        fluxo_maximo += fluxo_caminho;
    }

    return fluxo_maximo;
}

// Parte 2.1
// Calcula energia total possível na rede
int RedeEletrica::calcular_energia_total() {
    auto capacidade_backup = capacidade;
    int super_fonte = numero_vertices;
    int super_sumidouro = numero_vertices + 1;
    
    capacidade.resize(numero_vertices + 2, std::vector<int>(numero_vertices + 2, 0));
    
    // Restaura conexões originais
    for (int i = 0; i < numero_vertices; i++) {
        for (int j = 0; j < numero_vertices; j++) {
            capacidade[i][j] = capacidade_backup[i][j];
        }
    }

    // Liga super fonte aos geradores
    for (int i = 0; i < numero_vertices; i++) {
        if (eh_gerador[i]) {
            capacidade[super_fonte][i] = INFINITO;
        }
    }

    // Liga consumidores ao super sumidouro com capacidades máximas
    for (int i = 0; i < numero_vertices; i++) {
        if (!eh_gerador[i]) {
            int capacidade_maxima = 0;
            for (int j = 0; j < numero_vertices; j++) {
                if (eh_gerador[j]) {
                    capacidade_maxima += capacidade[j][i];
                }
            }
            capacidade[i][super_sumidouro] = demandas[i];
        }
    }

    int energia_total = ford_fulkerson(capacidade, super_fonte, super_sumidouro);
    capacidade = capacidade_backup;
    
    return energia_total;
}

// Parte 2.2
// Calcula energia não atendida aos consumidores
int RedeEletrica::calcular_energia_nao_atendida() {
    auto capacidade_backup = capacidade;
    int super_fonte = numero_vertices;
    int super_sumidouro = numero_vertices + 1;
    
    capacidade.resize(numero_vertices + 2, std::vector<int>(numero_vertices + 2, 0));
    
    // Restaura conexões e configura rede
    for (int i = 0; i < numero_vertices; i++) {
        for (int j = 0; j < numero_vertices; j++) {
            capacidade[i][j] = capacidade_backup[i][j];
        }
        if (eh_gerador[i]) {
            capacidade[super_fonte][i] = INFINITO;
        }
        if (!eh_gerador[i]) {
            capacidade[i][super_sumidouro] = demandas[i];
        }
    }

    // Calcula demanda total e energia máxima
    int demanda_total = 0;
    for (int i = 0; i < numero_vertices; i++) {
        if (!eh_gerador[i]) {
            demanda_total += demandas[i];
        }
    }

    int energia_maxima = ford_fulkerson(capacidade, super_fonte, super_sumidouro);
    capacidade = capacidade_backup;

    return demanda_total - energia_maxima;
}

// Parte 2.3
// Calcula energia perdida na transmissão
int RedeEletrica::calcular_energia_perdida() {
    auto capacidade_backup = capacidade;
    int super_fonte = numero_vertices;
    int super_sumidouro = numero_vertices + 1;
    
    capacidade.resize(numero_vertices + 2, std::vector<int>(numero_vertices + 2, 0));
    
    // Restaura conexões
    for (int i = 0; i < numero_vertices; i++) {
        for (int j = 0; j < numero_vertices; j++) {
            capacidade[i][j] = capacidade_backup[i][j];
        }
    }

    // Calcula energia total que os geradores podem gerar inicialmente
    int energia_gerada = 0;
    for (int i = 0; i < numero_vertices; i++) {
        if (eh_gerador[i]) {
            for (int j = 0; j < numero_vertices; j++) {
                if (!eh_gerador[j] && capacidade_backup[i][j] > 0) {
                    energia_gerada += capacidade_backup[i][j];
                }
            }
        }
    }

    // Configura rede para calcular fluxo máximo
    for (int i = 0; i < numero_vertices; i++) {
        if (eh_gerador[i]) {
            capacidade[super_fonte][i] = INFINITO;
        }
        if (!eh_gerador[i]) {
            capacidade[i][super_sumidouro] = demandas[i];
        }
    }

    // Calcula fluxo máximo que efetivamente chega
    int fluxo_maximo = ford_fulkerson(capacidade, super_fonte, super_sumidouro);

    capacidade = capacidade_backup;
    
    // Energia perdida é a diferença entre o gerado e o que chega
    return energia_gerada - fluxo_maximo;
}

// Parte 2.4
// Encontra conexões operando em capacidade máxima
std::vector<std::tuple<int, int, int>> RedeEletrica::encontrar_conexoes_criticas() {
    auto capacidade_backup = capacidade;
    std::vector<std::tuple<int, int, int>> criticas;
    std::vector<std::tuple<int, int, int>> temp;
    int super_fonte = numero_vertices;
    int super_sumidouro = numero_vertices + 1;
    
    capacidade.resize(numero_vertices + 2, std::vector<int>(numero_vertices + 2, 0));
    
    // Configura rede e encontra conexões críticas 
    for (int i = 0; i < numero_vertices; i++) {
        for (int j = 0; j < numero_vertices; j++) {
            capacidade[i][j] = capacidade_backup[i][j];
        }
        if (eh_gerador[i]) {
            capacidade[super_fonte][i] = INFINITO;
        }
        if (!eh_gerador[i]) {
            capacidade[i][super_sumidouro] = demandas[i];
        }
    }

    ford_fulkerson(capacidade, super_fonte, super_sumidouro);

    for (int i = 0; i < numero_vertices; i++) {
        for (int j = 0; j < numero_vertices; j++) {
            if (capacidade_backup[i][j] > 0 && fluxo[i][j] == capacidade_backup[i][j]) {
                criticas.push_back({i+1, j+1, capacidade_backup[i][j]});
            }
        }
    }

   // Ordenação simples para poucas conexões críticas
std::size_t n = criticas.size();
for (std::size_t i = 0; i < n; i++) {
    for (std::size_t j = i + 1; j < n; j++) {
        // Compara capacidades primeiro
        if (std::get<2>(criticas[i]) < std::get<2>(criticas[j])) {
            auto temp = criticas[i];
            criticas[i] = criticas[j];
            criticas[j] = temp;
        }
        // Se capacidades são iguais, compara vértices
        else if (std::get<2>(criticas[i]) == std::get<2>(criticas[j])) {
            // Se origem é diferente, ordena por origem
            if (std::get<0>(criticas[i]) != std::get<0>(criticas[j])) {
                if (std::get<0>(criticas[i]) > std::get<0>(criticas[j])) {
                    auto temp = criticas[i];
                    criticas[i] = criticas[j];
                    criticas[j] = temp;
                }
            }
            // Se origem é igual, ordena por destino
            else if (std::get<1>(criticas[i]) > std::get<1>(criticas[j])) {
                auto temp = criticas[i];
                criticas[i] = criticas[j];
                criticas[j] = temp;
            }
        }
    }
}

    capacidade = capacidade_backup;
    return criticas;
}