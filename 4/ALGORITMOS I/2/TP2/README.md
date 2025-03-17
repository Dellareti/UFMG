# Sistema de Diagnóstico para Rede Elétrica - Metalmax

## Descrição
Este trabalho prático foi desenvolvido para a disciplina de Algoritmos 1 da Universidade Federal de Minas Gerais (UFMG). O objetivo é analisar a rede elétrica da Metalmax, uma grande siderúrgica especializada na produção de aço, e fornecer diagnósticos precisos sobre seu funcionamento.

## Problema
A Metalmax utiliza uma rede elétrica interna complexa composta por geradores, consumidores e conexões entre eles. A rede apresenta as seguintes características:

- **Geradores**: Pontos de fornecimento de energia sem restrições de capacidade
- **Consumidores**: Pontos com demandas específicas que precisam ser atendidas
- **Conexões**: Caminhos unidirecionais com capacidade máxima limitada

O sistema desenvolvido fornece quatro diagnósticos essenciais:
1. **Energia Total**: Capacidade máxima que a rede pode operar
2. **Energia Não-atendida**: Quantidade de energia que falta para atender todas as demandas
3. **Energia Perdida**: Quantidade de energia desperdiçada na transmissão
4. **Conexões Críticas**: Conexões operando em capacidade máxima

## Modelagem
O problema foi modelado utilizando teoria dos grafos com fluxo:
- Vértices (V): Representam os geradores e consumidores
- Arestas direcionadas (E): Representam as conexões com suas capacidades
- Grafo G(V,E): Representa a rede elétrica completa

O algoritmo principal utilizado é o **Ford-Fulkerson** para cálculo de fluxo máximo, com **Busca em Largura (BFS)** para encontrar caminhos aumentantes. Estruturalmente, utilizamos:
- Matriz de adjacência para representar o grafo
- Super fonte e super sumidouro para adaptar o problema ao cenário de fluxo máximo

## Estrutura do Projeto
- `main.cpp`: Lê a entrada, instancia a classe RedeEletrica e imprime os resultados
- `rede_eletrica.hpp`: Define a interface da classe RedeEletrica
- `rede_eletrica.cpp`: Implementa os algoritmos para análise da rede elétrica

## Algoritmos Implementados
- `calcular_energia_total()`: Determina a capacidade máxima da rede
- `calcular_energia_nao_atendida()`: Calcula a diferença entre a demanda total e o fluxo máximo
- `calcular_energia_perdida()`: Identifica a energia gerada que não chega aos consumidores
- `encontrar_conexoes_criticas()`: Encontra conexões operando em capacidade máxima
- `ford_fulkerson()`: Implementação do algoritmo de fluxo máximo
- `busca_em_largura()`: Implementação do BFS para encontrar caminhos aumentantes

## Compilação e Execução
Para compilar o programa:
```bash
make
```

Para executar o programa com um arquivo de entrada:
```bash
./tp2 < arquivo_de_entrada.txt
```

Para salvar a saída em um arquivo:
```bash
./tp2 < arquivo_de_entrada.txt > arquivo_de_saida.txt
```

## Formato de Entrada
A entrada segue o seguinte formato:
1. Primeira linha: `V E` (número de pontos na rede e número de conexões)
2. Próximas V linhas: `Vi T` (identificador do ponto e tipo - 0 para gerador, >0 para consumidor com demanda)
3. Próximas E linhas: `Vi Vj C` (conexão de Vi para Vj com capacidade C)

## Formato de Saída
A saída consiste em:
1. Primeira linha: Energia total que a rede comporta
2. Segunda linha: Energia não-atendida
3. Terceira linha: Energia perdida ao longo da rede
4. Quarta linha: Número de conexões críticas
5. Para cada conexão crítica: `Vi Vj Eij` (origem, destino e capacidade da conexão)

## Exemplo

### Entrada:
```
6 7
1 0
2 20
3 30
4 40
5 50
6 50
1 2 50
1 3 60
1 4 70
1 5 80
1 6 30
2 4 10
5 6 15
```

### Saída:
```
185
5
105
2
1 6 30
5 6 15
```

## Complexidade
- **Tempo**: O(|V|E²) dominado pelo algoritmo Ford-Fulkerson
- **Espaço**: O(|V|²) dominado pelas matrizes de capacidade e fluxo

## Autor
Ítalo Dell'Areti - Universidade Federal de Minas Gerais (UFMG)

## Vídeo da Implementação
O vídeo demonstrando a implementação e o teste com Valgrind está disponível em:
https://drive.google.com/file/d/1PDd1vNfJdK9kL43P3KGgS9IuYK2iPz0L/view?usp=sharing

## Referências
- Geeks for Geeks: Breadth First Search or BFS for a Graph
- Geeks for Geeks: Ford Fulkerson Algorithm for Maximum Flow Problem
- CORMEN, T. H. et al. Introduction to Algorithms. 3rd ed. MIT Press, 2009.
- KLEINBERG, J.; TARDOS, E. Algorithm Design. Pearson, 2005.
