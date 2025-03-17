# Trabalho Prático #2 - Organização de Computadores I

Este repositório contém a implementação do Trabalho Prático #2 da disciplina DCC006: Organização de Computadores I, ministrada pelos Professores Omar Paranaíba Vilela Neto e Daniel Fernandes Macedo.

## Descrição do Trabalho

O objetivo deste trabalho foi implementar modificações em um caminho de dados RISC-V de 5 estágios utilizando a Linguagem de Descrição de Hardware Verilog. Foram implementadas quatro instruções através de alterações e acréscimos ao código fornecido em um arquivo Jupyter Notebook (.ipynb), executável no Google Colab.

### Instruções Implementadas

1. **Instrução MUL (mul Rd, Rs1, Rs2)** (Problema 1)
   - Implementação da operação de multiplicação que toma valores de dois registradores e armazena o resultado em um registrador destino
   - Formato da instrução: `00000 01 rs2 rs1 000 rd 0110011`

2. **Instrução DIV (div Rd, Rs1, Rs2)** (Problema 2)
   - Implementação da operação de divisão que toma valores de dois registradores e armazena a parte inteira do resultado em um registrador destino
   - Formato da instrução: `00000 01 rs2 rs1 100 rd 0110011`

3. **Instrução ANDI (andi Rd, Rs1, imm)** (Problema 3)
   - Implementação da operação AND imediata que compara bit-a-bit um registrador com um valor imediato
   - Formato da instrução: `imm[11:0] rs1 111 rd 0010011`

4. **Instrução BEQ (beq Rs1, Rs2, label)** (Problema 4)
   - Implementação da instrução de branch condicional que desvia o fluxo de execução se dois registradores tiverem valores iguais
   - Formato da instrução: `offset[12|10:5] rs2 rs1 000 offset[4:1|11] 1100011`

## Estrutura do Repositório

- `processador.ipynb`: Notebook Jupyter contendo a implementação completa do caminho de dados RISC-V com todas as instruções adicionais
- `relatorio.pdf`: Relatório técnico explicando as decisões de projeto, os testes realizados e os resultados obtidos

## Tecnologias Utilizadas

- Linguagem de Descrição de Hardware Verilog
- Google Colab para execução e simulação
- Jupyter Notebook para organização da implementação

## Como Executar

1. Abra o arquivo `processador.ipynb` no Google Colab
2. Execute as células sequencialmente para configurar o ambiente Verilog
3. Para cada instrução, os testes específicos estão em células dedicadas

## Detalhes de Implementação

### Instrução MUL
- Adicionamos um fio para realizar a operação MUL que suporta até 64 bits para evitar overflow/underflow
- Diferenciais entre MUL, ADD e DIV foram feitos com base nos campos funct3 e funct7 da instrução
- Modificação da ALU para incluir a nova operação

### Instrução DIV
- Similar à MUL, adicionamos um fio para realizar a operação DIV
- Diferenciais foram baseados no campo funct3, já que DIV e MUL possuem o mesmo opcode e funct7
- Implementação contempla casos de divisão exata e divisão com resultado não inteiro (truncando para a parte inteira)

### Instrução ANDI
- Aproveitamento da estrutura de instruções imediatas já existentes (como o ADDI)
- Diferenciação através do campo funct3
- Adaptação da ALU para realizar a operação AND com valor imediato

### Instrução BEQ
- Criação de um novo case para o opcode específico do BEQ
- Utilização da estrutura de branch já existente no processador base
- Implementação de testes para verificar tanto branches tomados quanto não tomados

## Autores

- Raquel Gonçalves Rosa
- Italo Dell'Areti

## Considerações Finais

- Todos os testes foram realizados para garantir o funcionamento correto das instruções implementadas
- Foram enfrentados desafios na geração de waveforms devido à falta de documentação clara
- Nas instruções de branch, identificamos limitações na instrução JUMP no código base, optando por não utilizá-la nos testes
