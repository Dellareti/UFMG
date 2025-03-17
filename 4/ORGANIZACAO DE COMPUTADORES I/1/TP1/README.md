# Trabalho Prático #1 - Organização de Computadores I

Este repositório contém as soluções para o Trabalho Prático #1 da disciplina DCC006: Organização de Computadores I, ministrada pelo Professor Daniel Fernandes Macedo.

## Descrição

O trabalho consiste em dois problemas de programação em assembly RISC-V, implementados para o simulador Venus:

### Problema 1: Inverter vetor recursivamente (5 pontos)
Implementação de um procedimento que inverte um vetor usando um algoritmo recursivo. O procedimento recebe duas posições de memória: a posição de início do vetor e a posição de fim do vetor.

### Problema 2: Verificador de CPF/CNPJ (5 pontos)
Implementação de três procedimentos:
1. `verificacpf`: Verifica a validade de um CPF
2. `verificacnpj`: Verifica a validade de um CNPJ
3. `verificadastro`: Procedimento que chama os dois anteriores dependendo do tipo de entrada

## Estrutura do Repositório

- `1.s`: Solução para o Problema 1 (Inversão de vetor recursiva)
- `2.s`: Solução para o Problema 2 (Verificador de CPF/CNPJ)

## Tecnologias Utilizadas

- Linguagem Assembly RISC-V
- [Venus Simulator](https://www.kvakil.me/venus/) - Simulador de ciclo único para execução e teste do código

## Como Executar

Para executar os códigos:

1. Acesse o [Venus Simulator](https://www.kvakil.me/venus/)
2. Copie o código do arquivo desejado (`1.s` ou `2.s`) para a aba "Editor"
3. Utilize a aba "Simulator" para executar o código passo a passo e visualizar os registradores

## Detalhes de Implementação

### Problema 1: Inversão de Vetor
- Implementa a recursão "de fora para dentro", onde a chamada recursiva mais interior inverte os elementos do meio do vetor
- Utiliza a pilha para salvar o endereço de retorno durante as chamadas recursivas
- Termina corretamente quando todos os elementos são invertidos

### Problema 2: Verificador de CPF/CNPJ
- Implementa os algoritmos de validação de CPF e CNPJ
- Utiliza a gestão de pilha para permitir que um procedimento chame outros procedimentos
- O procedimento `verificadastro` direciona para a função adequada com base no parâmetro de entrada

## Convenções Utilizadas

- Seguem-se as convenções da linguagem assembly RISC-V
- Utilizam-se instruções `jal` para chamada de procedimentos e `jalr` para retorno
- Implementa-se a gestão adequada de pilha para preservar registradores entre chamadas
