# Trabalho Prático 3 - Exposição de Tecidos

## Descrição
Este trabalho prático foi desenvolvido para a disciplina de Algoritmos 1 da Universidade Federal de Minas Gerais (UFMG). O objetivo foi solucionar o problema computacional conhecido como "Exposição de Tecidos" utilizando algoritmos de programação dinâmica.

## Problema
O problema consiste em determinar a maior quantidade de rolos de tecido que o vendedor Jorginho consegue expor na prateleira da loja FP Tecidinhos, seguindo algumas restrições:
- Jorginho só pode manipular os rolos na ordem em que eles chegaram
- Para posicionar cada rolo, ele tem três opções:
  1. Colocá-lo na prateleira pelo lado direito e empurrá-lo até encostar nos rolos já existentes
  2. Colocá-lo na prateleira pelo lado esquerdo e empurrá-lo até encostar nos rolos já existentes
  3. Simplesmente não colocá-lo na prateleira
- Os rolos precisam estar em ordem decrescente de preço na prateleira
- Jorginho nunca encomenda produtos de valores iguais

## Modelagem
O problema foi modelado utilizando programação dinâmica. A solução utiliza uma tabela hash para armazenar e consultar os estados já calculados, otimizando o desempenho do algoritmo.

A abordagem utiliza uma função hash personalizada para pares de inteiros, permitindo rastrear eficientemente as extremidades de cada sequência de tapetes, mantendo a restrição de ordem decrescente de preços.

## Estrutura do Projeto
- `main.cpp`: Ponto de entrada do programa, responsável pela leitura dos dados de entrada e saída dos resultados
- `loja.cpp`: Implementação do algoritmo de programação dinâmica
- `loja.hpp`: Declaração da função principal utilizada para resolver o problema

## Algoritmo Implementado
O algoritmo principal `maior_sequencia_tapetes()` tem as seguintes características:
- Utiliza um mapa não-ordenado (`unordered_map`) para implementar a programação dinâmica
- Armazena pares de extremidades (maior e menor valor) nas sequências para controlar a ordem decrescente
- Para cada novo tapete, verifica se é possível adicioná-lo em alguma das extremidades das sequências existentes
- Mantém o controle da maior sequência encontrada

A função `pair_hash` foi implementada para criar hashes eficientes para os pares de valores que representam as extremidades de cada sequência.

## Compilação e Execução
Para compilar o programa:
```
make
```

Para executar o programa com um arquivo de entrada:
```
./tp03 < arquivo_de_entrada.txt
```

Para salvar a saída em um arquivo:
```
./tp03 < arquivo_de_entrada.txt > arquivo_de_saida.txt
```

## Formato de Entrada
- A primeira linha contém um inteiro N (1 ≤ N ≤ 10), que representa o número de casos de teste
- Para cada caso de teste:
  - A próxima linha contém um inteiro R (1 ≤ R ≤ 20000), que representa a quantidade de rolos
  - Cada uma das próximas R linhas contém um inteiro Pi (1 ≤ Pi ≤ 1000000), que é o valor do i-ésimo rolo de tecido

## Formato de Saída
- Para cada caso de teste, o programa imprime uma linha contendo um número inteiro que representa a quantidade de rolos que serão expostos

## Exemplo de Uso
Arquivo de entrada `teste.txt`:
```
3
4
6
7
3
5
9
9
1
3
8
4
5
10
7
6
10
3
13
1
4
9
8
12
6
14
5
```

Execução:
```
./tp03 < teste.txt
```

Saída esperada:
```
3
5
6
```

## Autor
Ítalo Dell'Areti - Universidade Federal de Minas Gerais (UFMG)

## Ambiente de Desenvolvimento
O programa foi desenvolvido em C++ e testado em um ambiente Linux, utilizando o compilador G++ da GNU Compiler Collection.

## Complexidade
O algoritmo implementado tem complexidade de tempo O(n²) no pior caso, onde n é o número de rolos de tecido, atendendo aos requisitos do problema.
