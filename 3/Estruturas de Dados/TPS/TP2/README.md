# O Analisador

Um sistema para análise de ocorrências de palavras em textos usando ordem lexicográfica customizada, implementado em C++.

## Visão Geral

Este projeto implementa um analisador de texto que conta a frequência de ocorrência de palavras em um arquivo, ordenando-as de acordo com uma ordem lexicográfica personalizada. O sistema processa arquivos de texto, faz a contagem de ocorrências de cada palavra e gera um relatório ordenado segundo a ordem lexicográfica definida pelo usuário.

O programa foi desenvolvido como trabalho prático para a disciplina de Estruturas de Dados II da UFMG.

## Funcionalidades

- **Ordem Lexicográfica Customizada**: Permite definir uma ordenação personalizada das letras do alfabeto
- **Contagem de Palavras**: Identifica e contabiliza a ocorrência de cada palavra no texto
- **Tratamento de Case-Insensitive**: Palavras com variações de caixa alta/baixa são contabilizadas como sendo a mesma palavra
- **Quicksort Otimizado**: Implementação do algoritmo Quicksort com otimizações de pivô e particionamento
- **Análise de Desempenho**: Avaliação experimental do comportamento do algoritmo com diferentes parâmetros

### Funcionalidades Extra (Ponto Opcional)

- **Correção de Texto**: Tratamento de caracteres acentuados, união de palavras separadas por hífen
- **Remoção de Pontuação**: Limpeza automática de pontuação no meio e início das palavras

## Detalhes Técnicos

### Implementação

O programa está estruturado em módulos distintos:

- **Alfabeto**: Gerencia a ordem lexicográfica customizada
- **Lista**: Estrutura de dados para armazenamento inicial das palavras
- **Sort**: Implementação do Quicksort com as otimizações requeridas
- **IO**: Leitura dos arquivos e manipulação da entrada/saída

### Otimizações do Quicksort

O sistema implementa duas otimizações principais no algoritmo Quicksort:

1. **Mediana de M elementos**: Escolhe o pivô como sendo a mediana de M elementos do array
2. **Uso de algoritmo simples para partições pequenas**: Utiliza o algoritmo de Insertion Sort para partições menores que um limiar S

### Análise de Complexidade

- Quicksort Padrão: O(n log n) no caso médio
- Com as otimizações implementadas, o algoritmo mantém a complexidade assintótica de O(n log n) no caso médio, mas apresenta melhor desempenho prático em muitos casos

## Como Usar

### Requisitos

- Compilador C++ (testado com G++ da GNU Compiler Collection)
- Sistema operacional Linux (testado no Ubuntu 20.04 LTS)
- GNU Make

### Compilação

```bash
make all       # Compila o projeto
make distclean # Remove objetos
make clean     # Remove objetos e executável
```

### Execução

```bash
./bin/tp2 -i entrada.txt -o saida.txt -m 5 -s 10
```

Parâmetros:
- `-i <arquivo>`: Arquivo de entrada com ordem lexicográfica e texto a ser analisado
- `-o <arquivo>`: Arquivo de saída para os resultados
- `-m <valor>`: Tamanho da mediana para escolha do pivô (opcional)
- `-s <valor>`: Tamanho da partição para usar algoritmo simples (opcional)

### Formato de Entrada

O arquivo de entrada deve conter dois blocos principais:

```
#ORDEM
Q A Z W S X E D C R F V T G B Y H N M J U I K O L P

#TEXTO
Este é um exemplo de texto para análise.
As ocorrências de cada palavra serão contadas.
```

### Formato de Saída

O arquivo de saída contém as palavras ordenadas segundo a nova ordem lexicográfica, junto com sua frequência:

```
exemplo 1
análise 1
cada 1
contadas 1
de 2
é 1
este 1
...
#FIM
```

## Avaliação Experimental

O programa inclui uma análise experimental comparando o desempenho do algoritmo com diferentes configurações:

- Variação do tamanho do vetor a ser ordenado
- Diferentes valores para o parâmetro M (mediana)
- Diferentes valores para o parâmetro S (tamanho da partição)

Os resultados demonstram o impacto dessas otimizações no tempo de execução e padrão de acesso à memória do algoritmo.

## Autoria

Desenvolvido por Ítalo Dell'Areti como trabalho prático para a disciplina de Estruturas de Dados II da UFMG.
