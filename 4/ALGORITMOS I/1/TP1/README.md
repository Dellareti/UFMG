# Trabalho Prático 1 - O Plano de Campanha

## Descrição
Este trabalho prático foi desenvolvido para a disciplina de Algoritmos 1 da Universidade Federal de Minas Gerais (UFMG). O objetivo foi solucionar o problema computacional conhecido como "O Plano de Campanha" utilizando estruturas de dados e algoritmos de grafos.

## Problema
O problema consiste em determinar se é possível criar um plano de campanha que satisfaça todos os eleitores do deputado simultaneamente. Cada seguidor do deputado faz 4 escolhas:
- Duas propostas que devem continuar no plano de campanha
- Duas propostas que devem ser retiradas do plano de campanha

Para agradar um seguidor, ao menos uma das propostas votadas a favor deve permanecer no plano e ao menos uma das propostas com voto contrário deve ser retirada.

## Modelagem
O problema foi modelado utilizando a lógica proposicional e o problema 2-SAT (2-Satisfatibilidade), que determina se uma fórmula booleana na forma normal conjuntiva com no máximo duas variáveis por cláusula é satisfatível.

A implementação utiliza um grafo direcionado onde:
- Cada nó representa uma proposta
- As arestas representam as implicações lógicas entre as propostas

O algoritmo de Kosaraju é utilizado para encontrar os componentes fortemente conectados do grafo, o que permite determinar se existe uma solução válida para o problema.

## Estrutura do Projeto
- `main.cpp`: Ponto de entrada do programa
- `campanha.cpp`: Implementação da estrutura e algoritmos
- `campanha.hpp`: Declaração das estruturas e funções
- `Makefile`: Configuração para compilação do projeto

## Estruturas de Dados
- Grafos implementados com listas de adjacência
- Pilha para o algoritmo DFS do Kosaraju
- Vetores alocados dinamicamente na heap para suportar grandes entradas

## Algoritmos Implementados
- `aloca_e_inicializa_estruturas()`: Aloca os vetores no heap e inicializa as estruturas
- `adicionar_grafos()`: Adiciona arestas ao grafo direcionado
- `dfs1()` e `dfs2()`: Implementação do algoritmo de Kosaraju para identificação de componentes fortemente conectados
- `satisfaz()`: Verifica a satisfatibilidade do problema

## Compilação e Execução
Para compilar o programa:
```
make
```

Para executar o programa com um arquivo de entrada:
```
./tp1 < arquivo_de_entrada.txt
```

Para salvar a saída em um arquivo:
```
./tp1 < arquivo_de_entrada.txt > arquivo_de_saida.txt
```

Para limpar os arquivos de compilação:
```
make clean
```

## Formato de Entrada
- Primeira linha: Dois inteiros S e P (número de seguidores e número de propostas)
- Próximas S linhas: Quatro inteiros X1, X2, Y1, Y2 representando as preferências de cada seguidor
  - X1 e X2: Propostas que o seguidor deseja manter
  - Y1 e Y2: Propostas que o seguidor deseja retirar
  - Um valor 0 indica que o seguidor não está fazendo uso daquele voto
- A entrada termina quando S = P = 0

## Formato de Saída
Para cada caso de teste, o programa imprime uma linha contendo:
- `sim`: Se é possível satisfazer a todos os seguidores
- `nao`: Se não é possível satisfazer a todos

## Autor
Ítalo Dell'Areti - Universidade Federal de Minas Gerais (UFMG)

## Ambiente de Desenvolvimento
O programa foi desenvolvido e testado em um ambiente Linux distribuição Ubuntu 20.04 LTS utilizando Visual Studio Code e compilado com G++ da GNU Compiler Collection.
