# Trabalho Prático #1 - Organização de Computadores I

Este repositório contém a implementação do Trabalho Prático #1 da disciplina DCC006: Organização de Computadores I, ministrada pelo Professor Omar Paranaíba Vilela Neto.

## Descrição do Trabalho

O trabalho consiste em dois problemas de programação em Assembly RISC-V, implementados para o simulador Venus:

### Problema 1: Números Primos (5 pontos)
Implementação de um procedimento chamado `primos` que calcula os números primos dentro de uma faixa específica. O procedimento:
- Recebe o valor inicial (`a0`) e final (`a1`) do intervalo
- Recebe um ponteiro para área de memória onde os primos devem ser armazenados (`a2`)
- Retorna em `a0` a quantidade de números primos encontrados no intervalo

### Problema 2: Validador de Cartão de Crédito (5 pontos)
Implementação de dois procedimentos que implementam o algoritmo de Luhn para validação de cartões de crédito:
1. `verifica`: Recebe um ponteiro para os dígitos do cartão e retorna 1 se o cartão é válido, 0 caso contrário
2. `multvetores`: Recebe um ponteiro para os dígitos do cartão e calcula a multiplicação dos dígitos pelo vetor de base (1 e 2 alternados)

## Estrutura do Repositório

- `1.s`: Solução para o Problema 1 (Números Primos)
- `2.s`: Solução para o Problema 2 (Validador de Cartão de Crédito)

## Tecnologias Utilizadas

- Linguagem Assembly RISC-V
- [Venus Simulator](https://www.kvakil.me/venus/) - Simulador de ciclo único para execução e teste do código

## Como Executar

Para executar os códigos:

1. Acesse o [Venus Simulator](https://www.kvakil.me/venus/)
2. Copie o código do arquivo desejado (`1.s` ou `2.s`) para a aba "Editor"
3. Utilize a aba "Simulator" para executar o código passo a passo e visualizar os registradores

## Detalhes de Implementação

### Problema 1: Números Primos
- Implementa um algoritmo que verifica se cada número no intervalo é primo
- Um número é primo quando é maior que 1 e não é divisível por nenhum número além de 1 e ele mesmo
- O algoritmo utiliza otimização, verificando divisibilidade apenas até a raiz quadrada do número
- Os números primos encontrados são armazenados na área de memória fornecida
- Retorna a contagem total de números primos no intervalo especificado

### Problema 2: Validador de Cartão de Crédito
- Implementa o algoritmo de Luhn para validação de cartões de crédito
- Procedimento `multvetores` multiplica os dígitos do cartão por 1 e 2 alternadamente conforme especificado pelo algoritmo
- Quando a multiplicação resulta em um número de dois dígitos, soma-se esses dígitos (ou subtrai-se 9)
- Procedimento `verifica` calcula o dígito verificador e compara com o último dígito do cartão
- Utiliza gestão apropriada da pilha para permitir que um procedimento chame outro

## Convenções Utilizadas

- Seguem-se as convenções da linguagem assembly RISC-V
- Uso correto dos registradores, preservando valores conforme as convenções ABI
- Implementação de gestão adequada de pilha para chamadas de procedimento
- Uso das instruções `jal` para chamada de procedimentos e `jalr` para retorno

