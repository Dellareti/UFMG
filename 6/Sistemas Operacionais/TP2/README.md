# Simulador de Memória Virtual - TP2 Sistemas Operacionais

Este projeto implementa um simulador de memória virtual desenvolvido como trabalho prático da disciplina de Sistemas Operacionais da UFMG.

## Descrição

O simulador implementa diferentes algoritmos de substituição de páginas e estruturas de tabelas de páginas para análise de desempenho em diversos cenários de uso.

### Algoritmos de Substituição Implementados

- **Random**: Substituição aleatória de páginas
- **LRU** (Least Recently Used): Substitui a página menos recentemente usada
- **LFU** (Least Frequently Used): Substitui a página menos frequentemente usada
- **Clock**: Algoritmo Clock (segunda chance)

### Estruturas de Tabela de Páginas

- **Densa**: Tabela simples com mapeamento direto
- **Hierárquica 2 Níveis**: Estrutura hierárquica com dois níveis
- **Hierárquica 3 Níveis**: Estrutura hierárquica com três níveis
- **Invertida**: Tabela de páginas invertida

## Compilação

```bash
make
```

## Uso

```bash
./simulador <algoritmo> <arquivo_log> <tamanho_pagina_KB> <tamanho_memoria_KB> [tipo_tabela] [debug_level]
```

### Parâmetros

- **algoritmo**: `random`, `lru`, `lfu`, ou `clock`
- **arquivo_log**: Arquivo de trace com acessos à memória
- **tamanho_pagina_KB**: Tamanho da página em KB (ex: 4)
- **tamanho_memoria_KB**: Tamanho da memória física em KB (ex: 128)
- **tipo_tabela** (opcional): Tipo de tabela de páginas (0-3, padrão: 1)
- **debug_level** (opcional): Nível de debug (0-3, padrão: 0)

### Exemplo de Uso

```bash
./simulador lru compilador.log 4 128
```

## Testes Disponíveis

### Testes Básicos
```bash
make test          # Testa todos algoritmos com todos workloads
make benchmark     # Executa benchmark de desempenho
make test_result   # Salva resultados detalhados em arquivos
```

### Testes de Estruturas
```bash
make test_tables   # Compara estruturas de tabela de páginas
```

### Testes de Padrões
```bash
make test_patterns # Testa padrões de acesso personalizados
```

### Análise Completa
```bash
make generate_graphs  # Gera análise completa com gráficos
make test_all        # Executa todos os testes
```

## Workloads Incluídos

- `compilador.log` - Trace de compilação
- `matriz.log` - Operações com matrizes
- `compressor.log` - Algoritmo de compressão
- `simulador.log` - Trace do próprio simulador

## Estrutura do Projeto

- `simulador.c` - Código principal do simulador
- `simulador.h` - Definições e estruturas
- `page_table.c` - Implementação das tabelas de páginas
- `replacement.c` - Algoritmos de substituição
- `utils.c` - Funções utilitárias
- `gerar_graficos.py` - Script para geração de gráficos
- `Makefile` - Automação de compilação e testes

## Dependências para Gráficos

Para gerar gráficos de análise:

```bash
make install_deps
```

Ou manualmente:
```bash
pip3 install pandas matplotlib seaborn numpy
```

## Resultados

Os resultados são salvos em:
- `resultados_detalhados/` - Resultados por algoritmo e workload
- `tabelas/` - Comparação de estruturas de tabelas
- `resultados/graficos/` - Gráficos e análises visuais

## Limpeza

```bash
make clean  # Remove arquivos compilados e resultados
```

## Ajuda

```bash
make help   # Lista todos os comandos disponíveis
```