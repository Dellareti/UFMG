# Sistema de Segurança para o Império de Archadia

**Autor:** Ítalo Dell'Areti  
**Instituição:** Universidade Federal de Minas Gerais (UFMG)

## 📝 Descrição do Projeto

Este projeto implementa um sistema de segurança militar para o império fictício de Archadia, que precisa organizar suas defesas em diferentes estados. Cada estado é representado por uma estrutura que contém:

- Uma capital
- Centros urbanos
- Estradas de mão única conectando os centros urbanos

O sistema resolve três problemas principais:

1. **Determinação da Capital**: Identificar o centro urbano ideal que permitirá ao exército alcançar todos os outros centros pelo menor caminho possível.
2. **Posicionamento de Batalhões**: Determinar a quantidade e localização de batalhões secundários necessários para garantir que as tropas possam retornar e se reagrupar.
3. **Rotas de Patrulhamento**: Estabelecer rotas de patrulhamento que permitem cobrir todas as estradas possíveis e retornar ao ponto de origem.

## 🛠️ Tecnologias Utilizadas

- Linguagem: C/C++
- Estruturas de dados: Grafos (representados por listas de adjacência)
- Algoritmos principais:
  - Busca em Largura (BFS)
  - Algoritmo de Kosaraju
  - Algoritmo para encontrar ciclos Eulerianos (Hierholzer)

## 📊 Modelagem do Problema

O problema foi modelado usando grafos direcionados, onde:

- **Vértices (V)**: Representam os centros urbanos
- **Arestas direcionadas (E)**: Representam as estradas de mão única
- **Grafo G(V,E)**: Representa um estado completo

## 🚀 Como Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/Dellareti/Meta-Back-End-Developer.git
   cd caminho/para/o/projeto
   ```

2. Compile o programa usando o Makefile:
   ```bash
   make
   ```

3. Execute o programa, fornecendo um arquivo de entrada:
   ```bash
   ./tp1 < testCase01.txt
   ```

## 📥 Formato de Entrada

A entrada segue o formato:
```
NC NE
C1 C2
...
```
Onde:
- `NC`: Número de centros urbanos
- `NE`: Número de estradas
- Cada linha seguinte representa uma estrada de `C1` para `C2`

Exemplo:
```
6 8
Rhedrise Vandrad
Vandrad Benith
Khudealine Thonet
Thonet Khudealine
Rhedrise Khudealine
Benith Vandrad
Vandrad Muafland
Muafland Vandrad
```

## 📤 Formato de Saída

A saída segue o formato:
```
Capital
NB
Batalhao1
Batalhao2
...
P
Rota1
Rota2
...
```
Onde:
- `Capital`: Nome do centro urbano escolhido como capital
- `NB`: Número de batalhões secundários necessários
- Cada linha seguinte representa a localização de um batalhão
- `P`: Número de patrulhamentos possíveis
- Cada linha seguinte representa uma rota válida de patrulhamento

Exemplo:
```
Rhedrise
2
Khudealine
Vandrad
2
Khudealine Thonet
Vandrad Muafland Vandrad Benith
```

## 📈 Análise de Complexidade

### Estruturas de Dados
- Lista de adjacência: O(|V| + |E|) de espaço

### Funções Principais
- **calcula_capital**: O(|V| * (|V| + |E|)) tempo, O(|V|) espaço
- **calcula_batalhao**: O(|V| + |E|) + O(|V| * log|V|) tempo, O(|V| + |E|) espaço
- **calcula_patrulhamento**: O(|V| * (|V| + |E|)) tempo, O(|V| + |E|) espaço

## 📝 Informações Adicionais

Este trabalho foi desenvolvido como parte da disciplina de Algoritmos I e aborda conceitos importantes como:

- Grafos e seus componentes
- Algoritmos de busca
- Componentes fortemente conectados
- Ciclos eulerianos

Para mais detalhes sobre a implementação, consulte a documentação e o código fonte fornecidos.

## 🔗 Referências

- Geeks for Geeks: Depth First Search or DFS for a Graph
- Geeks for Geeks: Breadth First Search or BFS for a Graph
- USP IME: Algoritmo de Kosaraju-Sharir para componentes fortes
- Geeks for Geeks: Strongly Connected Components
- Geeks for Geeks: Euler Circuit in a Directed Graph
- Geeks for Geeks: Hierholzer's Algorithm for directed graph
- CORMEN, T. H. et al. Introduction to Algorithms. 3rd ed. MIT Press, 2009.
- KLEINBERG, J.; TARDOS, E. Algorithm Design. Pearson, 2005.
