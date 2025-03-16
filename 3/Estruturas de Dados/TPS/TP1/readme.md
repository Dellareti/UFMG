# Poker Face

Um sistema para simulação de jogos de Poker virtual desenvolvido em C++.

## Visão Geral

Este projeto implementa um sistema de jogo de Poker que automatiza as decisões de jogabilidade. Os jogadores podem fazer suas jogadas físicas (incluindo blefes e apostas) enquanto o sistema gerencia:

- A validação das mãos dos jogadores
- A determinação dos vencedores de cada rodada
- O controle do dinheiro virtual de cada jogador
- A distribuição do pote entre os vencedores

O programa foi desenvolvido como trabalho prático para a disciplina de Algoritmos e Estruturas de Dados II da UFMG.

## Funcionalidades

- **Classificação de mãos**: Identifica as combinações de cartas (Royal Flush, Straight Flush, Four of a Kind, etc.)
- **Sistema de apostas**: Gerencia as apostas e distribui o pote conforme as regras
- **Gerenciamento de jogadores**: Controla o saldo de cada jogador
- **Critérios de desempate**: Implementa todas as regras de desempate do Poker tradicional
- **Testes de sanidade**: Valida rodadas e apostas para garantir a consistência do jogo

## Detalhes Técnicos

### Implementação

O programa foi estruturado em módulos separados para facilitar a manutenção e compreensão:

- **Banco**: Responsável pelo gerenciamento financeiro dos jogadores
- **Jogo**: Controla o fluxo do jogo, rodadas e decisão de vencedores
- **Mão**: Implementa as classificações e comparações de mãos de Poker
- **Jogador**: Representa o jogador com seus atributos e mãos
- **IO**: Gerencia entrada e saída de dados

### Modularização

O sistema está dividido nos seguintes componentes:
- `banco.h/.cpp`: Gerenciamento financeiro dos jogadores
- `jogo.h/.cpp`: Controle do fluxo de jogo e rodadas
- `mao.h/.cpp`: Classificação e comparação de mãos
- `jogador.h/.cpp`: Gerenciamento de jogadores
- `io.h/.cpp`: Entrada e saída de dados
- `sort.h`: Algoritmo de ordenação para organizar as cartas e resultados

### Análise de Complexidade

A maior parte das operações tem complexidade constante O(1), pois:
- Número máximo de jogadores é limitado (máximo de 10)
- Cada mão contém exatamente 5 cartas
- Comparações entre mãos são realizadas em tempo constante

A execução completa do jogo é O(n) onde n é o número de rodadas.

## Formato de Entrada e Saída

### Entrada

O programa lê os dados de um arquivo chamado `entrada.txt`:

```
3 1000            // Número de rodadas e dinheiro inicial
5 50              // Número de jogadores e valor do pingo
Giovanni 100 6O 3P 10E 11O 1O  // Nome, aposta e cartas
John 200 3P 4E 3E 13C 13O
...
```

### Saída

A saída é escrita no arquivo `saida.txt`:

```
1 1000 S          // Número de vencedores, valor ganho, tipo da mão
Gisele            // Nome do vencedor
...
####             // Separador
Gisele 2050      // Resultado final: nome e saldo
...
```

## Requisitos

- Compilador C++ (testado com G++ da GNU Compiler Collection)
- Sistema operacional Linux (testado no Ubuntu 20.04 LTS)
- GNU Make

## Compilação e Execução

```bash
make all        # Compila o projeto
make distclean  # Remove objetos
make clean      # Remove objetos e executável
```

O arquivo `entrada.txt` deve estar no diretório raiz do projeto. Após a execução, o resultado estará em `saida.txt`.

Para executar:
```bash
cd bin
./tp1
```

## Exemplos de Uso

O projeto inclui casos de teste para demonstrar o funcionamento, incluindo:
- Caso básico com diferentes tipos de mãos
- Caso de desempate de Full House
- Verificação de robustez com apostas inválidas

## Autoria

Desenvolvido por Ítalo Dell'Areti como trabalho prático para a disciplina de Algoritmos e Estruturas de Dados II da UFMG.
