# Servidor de Emails Otimizado

Este projeto implementa um simulador de servidor de emails otimizado, desenvolvido como parte do Trabalho Prático 3 da disciplina de Estrutura de Dados (DCC205) na Universidade Federal de Minas Gerais (UFMG).

## Descrição

O simulador implementa um servidor de emails com foco em gerenciamento adequado de memória e otimização da pesquisa por usuários e mensagens. O sistema utiliza uma estrutura de dados híbrida composta por tabela hash e árvores binárias de busca para armazenar e gerenciar eficientemente as mensagens de email.

### Principais Funcionalidades

- **Entrega de Emails**: Recebe um novo email destinado a um usuário específico e o armazena na estrutura adequada.
- **Consulta de Emails**: Busca e recupera emails específicos armazenados para determinado usuário.
- **Exclusão de Emails**: Remove emails específicos da caixa de entrada de um usuário.

## Estrutura do Projeto

A implementação foi realizada utilizando as seguintes estruturas:

- **Tabela Hash**: Armazena as caixas de mensagens dos usuários.
- **Árvore Binária de Busca**: Cada entrada da tabela hash aponta para uma árvore que armazena os emails.
- **Mensagem**: Estrutura que representa um email individual.

### Organização de Arquivos

```
TP
├── bin/         # Diretório para o executável
├── include/     # Arquivos de cabeçalho (.h)
│   ├── arvore_busca.h
│   ├── mensagem.h
│   └── tabela_hash.h
├── obj/         # Objetos gerados na compilação
├── src/         # Código-fonte (.cpp)
│   ├── arvore_busca.cpp
│   ├── tabela_hash.cpp
│   └── main.cpp
├── Makefile     # Instruções de compilação
└── log_mem.txt  # Arquivo de log para análise de desempenho
```

## Análise de Complexidade

### Tempo
- **Árvore Binária (bst)**
  - Criação: O(1)
  - Inserção: O(n)
  - Remoção: O(n)
  - Busca do menor elemento: O(n)
  - Busca geral: O(n)

- **Tabela Hash**
  - Criação: O(n)
  - Inserção: O(1)
  - Remoção: O(1)
  - Busca: O(1)
  - Função hash: O(1)

### Espaço
- No pior caso, a complexidade de espaço nas árvores binárias de busca e na tabela hash é O(n).

## Como Compilar e Executar

### Compilação
```bash
# Compilar todo o projeto
make all

# Limpar arquivos objeto
make distclean

# Limpar objetos e executável
make clean
```

### Execução
```bash
./bin/tp3 -i entrada.txt -o saida.txt
```

Onde:
- `-i entrada.txt`: Especifica o arquivo de entrada a ser processado
- `-o saida.txt`: Especifica o arquivo de saída para os resultados

## Formato do Arquivo de Entrada

O arquivo de entrada deve seguir o seguinte formato:
- Primeira linha: Um inteiro M representando o tamanho da tabela hash
- Linhas seguintes: Operações do servidor no formato:
  - `ENTREGA U E N MSG`: Entrega uma mensagem para o usuário U
  - `CONSULTA U E`: Consulta a mensagem E do usuário U
  - `APAGA U E`: Remove a mensagem E do usuário U

Exemplo:
```
23
ENTREGA 5 103 6 Bom dia, meu amigo! Tudo bom?
CONSULTA 5 103
APAGA 5 103
```

## Implementação

O projeto foi desenvolvido em C++ e compilado com o G++ da GNU Compiler Collection. A implementação seguiu princípios de modularização, com separação clara de responsabilidades entre os componentes do sistema.

## Autor

Ítalo Dell'Areti - Universidade Federal de Minas Gerais (UFMG)
