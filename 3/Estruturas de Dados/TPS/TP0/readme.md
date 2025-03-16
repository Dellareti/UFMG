# Operações com Matrizes Dinamicamente Alocadas

Este projeto implementa operações básicas de matrizes usando alocação dinâmica de memória em C, com foco em desempenho e eficiência de memória.

## Visão Geral

Esta implementação converte uma implementação estática de matriz em uma dinâmica, suportando as seguintes operações:
- Soma de matrizes
- Multiplicação de matrizes
- Transposição de matriz

O projeto enfatiza:
- Alocação/desalocação dinâmica de memória
- Análise de desempenho
- Padrões de acesso à memória
- Análise de complexidade computacional

## Funcionalidades

- **Gerenciamento Dinâmico de Memória**: Matrizes são alocadas dinamicamente com base nas dimensões de entrada
- **Operações de Matriz**: 
  - Soma (requer matrizes de dimensões iguais)
  - Multiplicação (requer que a contagem de colunas da primeira matriz = contagem de linhas da segunda matriz)
  - Transposição (funciona em qualquer matriz)
- **Análise de Desempenho**: Inclui ferramentas de registro para medir o tempo de execução e padrões de acesso à memória
- **Tratamento de Erros**: Verificação robusta de erros para dimensões de matriz e E/S de arquivos

## Detalhes Técnicos

### Implementação

O programa utiliza os seguintes componentes:
- `mat.c`: Implementação principal das operações de matriz e E/S de arquivos
- `matop.c`: Controla o fluxo do programa
- `memlog.c`: Registra acesso à memória e tempo de execução para análise de desempenho

### Estrutura de Dados

A implementação usa uma estrutura chamada `mat` que contém:
- `tamx` e `tamy`: Dimensões da matriz
- `id`: Identificador para rastreamento de desempenho
- Array 2D alocado dinamicamente (`double **`) para armazenar elementos da matriz

### Análise de Complexidade

- Soma de Matrizes: O(m×n)
- Transposição de Matriz: O(m×n)
- Multiplicação de Matrizes: O(m²×n)

Onde m é o número de linhas e n é o número de colunas.

## Uso

### Compilação

```bash
make all        # Compila tudo
make mem        # Gera arquivos de registro de acesso à memória
make prof       # Mede tempos de desempenho
make gprof      # Ilustra o uso do gprof para depuração
make clean      # Remove objetos e executável
```

### Executando o Programa

O programa aceita os seguintes parâmetros de linha de comando:

```
./bin/program
    -s          # Operação de soma
    -m          # Operação de multiplicação
    -t          # Operação de transposição (apenas para matriz 1)
    -1 m1.txt   # Arquivo de entrada da primeira matriz
    -2 m2.txt   # Arquivo de entrada da segunda matriz
    -o res.txt  # Arquivo de matriz de saída
    -p log.out  # Arquivo de registro de desempenho
    -l          # Registrar padrões de acesso à memória
```

### Formato de Entrada

As matrizes de entrada devem ser fornecidas como arquivos de texto onde:
- A primeira linha contém dois inteiros definindo as dimensões (linhas e colunas)
- As linhas seguintes contêm os elementos da matriz como números de ponto flutuante

### Arquivos de Saída

As operações produzem arquivos de resultado no diretório raiz do projeto:
- `res-soma`: Resultado da soma de matrizes
- `res-mult`: Resultado da multiplicação de matrizes
- `res-transp`: Resultado da transposição de matriz

## Desempenho

A implementação é otimizada para:
- Eficiência no uso de memória
- Tempo de execução
- Padrões de acesso à memória e localidade


## Requisitos

- Compilador C/C++ (G++ recomendado)
- Ambiente Linux (testado no Ubuntu 20.04 LTS)
- GNU Make

## Licença

Este projeto é um exercício acadêmico para a disciplina de Estruturas de Dados da UFMG (Universidade Federal de Minas Gerais).
