# Trabalho Prático #2 - Organização de Computadores I

Este repositório contém a implementação do Trabalho Prático #2 da disciplina DCC006: Organização de Computadores I, ministrada pelos Professores Omar Paranaíba Vilela Neto e Daniel Fernandes Macedo.

## Descrição do Trabalho

O objetivo deste trabalho é implementar modificações em um caminho de dados RISC-V de 5 estágios em Verilog, incluindo novas operações e módulos. As implementações incluem:

### Problema 1: XORI - XOR Immediate (5.0 pontos)
Implementação da instrução de XOR com valores imediatos, que realiza uma operação lógica bit a bit entre o conteúdo de um registrador e um valor imediato.

### Problema 2: AND - AND logic (2.5 pontos)
Implementação da instrução de AND lógica que realiza uma operação AND bit a bit entre os conteúdos de dois registradores.

### Problema 3: J - Jump (5.0 pontos)
Implementação da instrução de salto incondicional, que permite o desvio do fluxo de execução para um endereço específico.

### Problema 4: BLTU - Branch Less Than Unsigned (2.5 pontos)
Implementação da instrução de desvio condicional que compara dois registradores como valores sem sinal e desvia se o primeiro for menor que o segundo.

## Estrutura do Repositório

- `processor.ipynb`: Notebook Jupyter contendo a implementação do caminho de dados RISC-V modificado com todas as instruções adicionais implementadas
- `report.pdf`: Relatório técnico explicando as decisões de projeto tomadas para cada implementação
- `test/`: Diretório contendo os códigos de teste em assembly para validar as implementações

## Tecnologias Utilizadas

- Linguagem de Descrição de Hardware Verilog
- Google Colab para execução e simulação do código
- RISC-V ISA (Conjunto de Instruções do RISC-V)

## Como Executar

Para executar o caminho de dados e os testes:

1. Abra o arquivo `processor.ipynb` no Google Colab
2. Execute todas as células do notebook para carregar a implementação Verilog
3. Os testes de cada instrução implementada estão nas células apropriadas do notebook
4. As formas de onda resultantes da simulação podem ser visualizadas no notebook

## Detalhes de Implementação

### XORI - XOR Immediate
- Modificou-se a ALU para incluir a operação de XOR
- Adicionou-se o reconhecimento do opcode e funct3 correspondentes na unidade de controle
- Implementou-se o correto tratamento do valor imediato

### AND - AND Logic
- Extendeu-se a ALU para suportar a operação AND entre dois registradores
- Configurou-se o controle para reconhecer o formato R e a operação específica

### J - Jump
- Implementou-se a lógica de desvio incondicional
- Adicionou-se o cálculo do endereço de destino baseado no formato da instrução
- Realizou-se as adaptações necessárias no controle de fluxo do pipeline

### BLTU - Branch Less Than Unsigned
- Estendeu-se a unidade de comparação para suportar comparações sem sinal
- Adicionou-se o reconhecimento da instrução específica na unidade de controle
- Implementou-se a lógica de desvio condicional baseada na comparação

## Decisões de Projeto

Detalhes sobre as decisões de projeto, desafios encontrados e soluções implementadas podem ser encontrados no arquivo `report.pdf`.

