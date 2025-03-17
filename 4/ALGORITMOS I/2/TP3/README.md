# Problema do Caixeiro Viajante - Comparativo de Algoritmos

## Descrição
Este trabalho foi desenvolvido para a disciplina de Algoritmos 1 da Universidade Federal de Minas Gerais (UFMG) e implementa três abordagens distintas para resolver o Problema do Caixeiro Viajante (TSP). O objetivo é determinar a localização ideal de pontos de distribuição e as rotas de entrega para a empresa fictícia DelivExpress, encontrando o caminho mais curto que passa por todas as cidades exatamente uma vez e retorna à origem.

## Problema
A DelivExpress precisa estabelecer centros de distribuição em diferentes regiões e determinar:
1. Em qual cidade estabelecer o ponto de distribuição
2. Qual a melhor rota para passar por todas as cidades da região exatamente uma vez
3. Como retornar ao ponto inicial com o menor custo possível

Este é essencialmente o Problema do Caixeiro Viajante, um problema NP-difícil cuja complexidade cresce fatorialmente com o número de cidades.

## Estratégias Implementadas

### 1. Força Bruta
- **Abordagem**: Gera todas as permutações possíveis de cidades e seleciona a de menor custo
- **Garantia**: Encontra sempre a solução ótima
- **Complexidade de Tempo**: O(n!)
- **Viabilidade**: Prática apenas para regiões com até 13 cidades

### 2. Programação Dinâmica
- **Abordagem**: Algoritmo de Held-Karp, que resolve o problema de forma recursiva com memoização
- **Garantia**: Encontra sempre a solução ótima
- **Complexidade de Tempo**: O(n²2ⁿ)
- **Complexidade de Espaço**: O(n2ⁿ)
- **Viabilidade**: Prática para regiões médias (14-19 cidades)

### 3. Algoritmo Guloso
- **Abordagem**: Algoritmo do Vizinho Mais Próximo, que constrói a solução de forma incremental
- **Garantia**: Solução aproximada (não garante otimalidade)
- **Complexidade de Tempo**: O(n²)
- **Complexidade de Espaço**: O(n)
- **Viabilidade**: Altamente escalável, prático para qualquer tamanho de região

## Estrutura do Projeto
- `main.cpp`: Ponto de entrada do programa, processa entradas e coordena as chamadas aos algoritmos
- `resolvedor_caixeiro.hpp`: Interface base para todas as estratégias de resolução
- `forca_bruta.cpp`: Implementação da estratégia de força bruta
- `prog_dinamica.cpp`: Implementação da estratégia de programação dinâmica
- `guloso.cpp`: Implementação da estratégia gulosa
- `medidor_recursos.hpp`: Classe para medir tempo de execução e uso de memória

## Resultados Experimentais

### Tempo de Execução
![Comparação de Tempo de Execução](temp_execucao.png)

- **Força Bruta**: Viável até 13 cidades (62 segundos), crescimento fatorial
- **Programação Dinâmica**: Processou todos os casos até 23 cidades em 30 segundos
- **Guloso**: Tempo praticamente constante (0-1ms)

### Uso de Memória
![Comparação de Uso de Memória](uso_memoria.png)

- **Força Bruta**: Memória constante O(n)
- **Programação Dinâmica**: Crescimento exponencial, 23 cidades consumindo 783 MB
- **Guloso**: Memória constante O(n)

### Qualidade das Soluções
![Comparação da Qualidade das Soluções](qualidade_solucoes.png)

- **Soluções Ótimas** (Força Bruta e Programação Dinâmica): Garantia matemática de otimalidade
- **Soluções Gulosas**: Média de desvio de 13.37%, com máximo de 24.6% para 23 cidades

## Compilação e Execução
Para compilar o programa:
```bash
make
```

Para executar o programa com um arquivo de entrada:
```bash
./tp3 < entrada.txt
```

## Formato de Entrada
```
<estratégia>
<V> <E>
<cidade1> <cidade2> <distância>
...
```
Onde:
- `<estratégia>` é um caractere: 'b' para força bruta, 'd' para programação dinâmica ou 'g' para guloso
- `<V>` é o número de vértices (cidades) e `<E>` é o número de arestas (estradas)
- Cada linha seguinte descreve uma conexão entre duas cidades com sua respectiva distância

## Formato de Saída
```
<custo_total>
<cidade1> <cidade2> ... <cidadeN>
```
Onde:
- `<custo_total>` é o custo total da melhor rota encontrada
- A segunda linha contém a sequência de cidades da rota, começando pela cidade escolhida como ponto de distribuição

## Conclusões e Recomendações

Com base nos resultados experimentais, recomendamos:
- **Regiões pequenas (≤ 13 cidades)**: Usar força bruta para garantir a solução ótima
- **Regiões médias (14-19 cidades)**: Usar programação dinâmica para garantir a solução ótima
- **Regiões grandes (≥ 20 cidades)**: Usar o algoritmo guloso, aceitando uma solução aproximadamente 13% acima do ótimo em troca de eficiência

## Autor
Ítalo Dell'Areti - Universidade Federal de Minas Gerais (UFMG)

## Vídeo de Demonstração
[Link para o vídeo da implementação](https://drive.google.com/file/d/1mNFCoupKQRuWETCoDUduWK0qVSvr4EoF/view?usp=sharing)

## Referências
- Geeks For Geeks: The Traveling Salesman Problem
- CORMEN, T. H. et al. Introduction to Algorithms. 3rd ed. MIT Press, 2009
- KLEINBERG, J.; TARDOS, E. Algorithm Design. Pearson, 2005
- APPLEGATE, D. L. et al. The Traveling Salesman Problem: A Computational Study. Princeton University Press, 2006
