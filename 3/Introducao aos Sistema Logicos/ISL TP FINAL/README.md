# 🔐 Circuito Sequencial - Cofre de Pão de Queijo

Este repositório contém a implementação de um circuito sequencial em Verilog para controlar um mecanismo de destravamento de um cofre com senha. O projeto foi desenvolvido como parte da disciplina de Introdução aos Sistemas Lógicos.

## 📋 Visão Geral do Projeto

O projeto implementa um circuito sequencial que controla o destravamento da porta de um cofre quando a senha correta (CBBAA) é inserida. O circuito foi modelado utilizando máquina de estados finitos, mapas de Karnaugh e implementado em Verilog.

## 🔍 Funcionalidades

- O circuito aceita uma sequência de entradas correspondentes às letras A, B e C
- Quando a senha correta (CBBAA) é inserida, a porta do cofre é aberta
- Após a senha ser inserida corretamente, a porta permanece aberta até que o circuito seja resetado
- Entradas incorretas não comprometem a segurança do cofre

## 📊 Implementação

A implementação do projeto seguiu os seguintes passos:

1. **Diagrama de Estados**: Definição dos estados necessários para representar a sequência da senha
2. **Tabela de Próximo Estado**: Criação da tabela que define as transições entre estados
3. **Mapas de Karnaugh**: Simplificação das funções lógicas para os próximos estados
4. **Circuito Lógico**: Implementação do circuito baseado nas funções simplificadas
5. **Código Verilog**: Desenvolvimento do código para simulação e teste

## 💾 Estrutura do Projeto

- `design.sv`: Implementação principal do circuito em Verilog
- `testbench.sv`: Testbench básico para validação da funcionalidade
- `testbench2.sv`: Testa a permanência no estado final após a abertura do cofre
- `testbench3.sv`: Testa a resistência do circuito a sequências de entrada incorretas

## ⚙️ Componentes do Circuito

O circuito utiliza os seguintes componentes:
- 3 Flip-flops tipo D para armazenar o estado atual (Q2, Q1, Q0)
- Portas lógicas para implementar as funções de próximo estado
- Entradas para X1 e X0 (representando A, B e C)
- Saída LED que acende quando o cofre é destravado
- Reset para reinicializar o circuito

## 📊 Máquina de Estados

A máquina de estados do cofre é representada por 6 estados:
- A0 (000): Estado inicial
- A1 (001): Após receber C
- A2 (010): Após receber C e B
- A3 (011): Após receber C, B e B
- A4 (100): Após receber C, B, B e A
- A5 (101): Estado final (cofre aberto) após receber C, B, B, A e A

## 🧪 Testes Realizados

Foram implementados três testbenches diferentes:
1. **Teste Básico**: Verifica se o circuito reconhece a senha correta e abre o cofre
2. **Teste de Permanência**: Confirma que após aberto, o cofre continua aberto independente das entradas subsequentes
3. **Teste de Segurança**: Verifica que sequências incorretas não abrem o cofre

## 🛠️ Ferramentas Utilizadas

- **CircuitVerse**: Para o design e simulação do circuito lógico
- **EDA Playground**: Para a implementação e teste do código Verilog

## 📝 Como Executar

1. Acesse o [EDA Playground](https://www.edaplayground.com/)
2. Copie o conteúdo dos arquivos design.sv e testbench.sv (ou outro testbench)
3. Execute a simulação e verifique os resultados

## 🔗 Links

- [Circuito no CircuitVerse](https://circuitverse.org/users/137724/projects/tp-isl-ed724e72-84bd-4997-943f-a2f51bd9b4cf)
- [Projeto no EDA Playground](https://www.edaplayground.com/x/CTGB)

---

Desenvolvido por Ítalo Dell'Areti - Universidade Federal de Minas Gerais (UFMG)
