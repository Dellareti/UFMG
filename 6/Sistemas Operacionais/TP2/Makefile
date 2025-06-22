CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = simulador
SRCS = simulador.c page_table.c replacement.c utils.c
OBJS = $(SRCS:.c=.o)
HEADERS = simulador.h

# =============================================================================
# TARGETS PRINCIPAIS
# =============================================================================

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf resultados/ tabelas/ resultados_detalhados/ resultados_test/
	rm -f temp_result.txt
	rm -f sequential.log random.log locality.log loop.log

# =============================================================================
# TESTES BÁSICOS
# =============================================================================

test: $(TARGET)
	@echo "=== TESTANDO ALGORITMOS COM TODOS OS WORKLOADS ==="
	@echo "--- Compilador ---"
	./$(TARGET) lru compilador.log 4 128
	./$(TARGET) random compilador.log 4 128
	./$(TARGET) lfu compilador.log 4 128
	./$(TARGET) clock compilador.log 4 128
	
	@echo "--- Matriz ---"
	./$(TARGET) lru matriz.log 4 128
	./$(TARGET) random matriz.log 4 128
	./$(TARGET) lfu matriz.log 4 128
	./$(TARGET) clock matriz.log 4 128
	
	@echo "--- Compressor ---"
	./$(TARGET) lru compressor.log 4 128
	./$(TARGET) random compressor.log 4 128
	./$(TARGET) lfu compressor.log 4 128
	./$(TARGET) clock compressor.log 4 128
	
	@echo "--- Simulador ---"
	./$(TARGET) lru simulador.log 4 128
	./$(TARGET) random simulador.log 4 128
	./$(TARGET) lfu simulador.log 4 128
	./$(TARGET) clock simulador.log 4 128
	

test_result: $(TARGET)
	@echo "=== SALVANDO RESULTADOS DETALHADOS POR ALGORITMO E WORKLOAD ==="
	@mkdir -p resultados_detalhados
	
	@echo "Salvando resultados do compilador.log..."
	./$(TARGET) lru compilador.log 4 128 > resultados_detalhados/compilador_lru.txt
	./$(TARGET) random compilador.log 4 128 > resultados_detalhados/compilador_random.txt
	./$(TARGET) lfu compilador.log 4 128 > resultados_detalhados/compilador_lfu.txt
	./$(TARGET) clock compilador.log 4 128 > resultados_detalhados/compilador_clock.txt
	
	@echo "Salvando resultados do matriz.log..."
	./$(TARGET) lru matriz.log 4 128 > resultados_detalhados/matriz_lru.txt
	./$(TARGET) random matriz.log 4 128 > resultados_detalhados/matriz_random.txt
	./$(TARGET) lfu matriz.log 4 128 > resultados_detalhados/matriz_lfu.txt
	./$(TARGET) clock matriz.log 4 128 > resultados_detalhados/matriz_clock.txt
	
	@echo "Salvando resultados do compressor.log..."
	./$(TARGET) lru compressor.log 4 128 > resultados_detalhados/compressor_lru.txt
	./$(TARGET) random compressor.log 4 128 > resultados_detalhados/compressor_random.txt
	./$(TARGET) lfu compressor.log 4 128 > resultados_detalhados/compressor_lfu.txt
	./$(TARGET) clock compressor.log 4 128 > resultados_detalhados/compressor_clock.txt
	
	@echo "Salvando resultados do simulador.log..."
	./$(TARGET) lru simulador.log 4 128 > resultados_detalhados/simulador_lru.txt
	./$(TARGET) random simulador.log 4 128 > resultados_detalhados/simulador_random.txt
	./$(TARGET) lfu simulador.log 4 128 > resultados_detalhados/simulador_lfu.txt
	./$(TARGET) clock simulador.log 4 128 > resultados_detalhados/simulador_clock.txt
	
	@echo "Resultados detalhados salvos em 'resultados_detalhados/'"
	@echo "Arquivos criados:"
	@ls -la resultados_detalhados/


benchmark: $(TARGET)
	@echo "=== EXECUTANDO BENCHMARK DE DESEMPENHO ==="
	@echo "Testando LRU com variação de memória e páginas..."
	./$(TARGET) lru compilador.log 4 128 1
	./$(TARGET) lru compilador.log 4 256 1
	./$(TARGET) lru compilador.log 4 512 1
	./$(TARGET) lru compilador.log 4 1024 1
	./$(TARGET) lru compilador.log 2 512 1
	./$(TARGET) lru compilador.log 4 512 1
	./$(TARGET) lru compilador.log 8 512 1
	./$(TARGET) lru compilador.log 16 512 1
	./$(TARGET) lru compilador.log 32 512 1
	./$(TARGET) lru compilador.log 64 512 1

# =============================================================================
# TESTES DAS ESTRUTURAS DE TABELA DE PÁGINAS
# =============================================================================

test_tables: $(TARGET)
	@echo "=== TESTANDO ESTRUTURAS DE TABELA DE PÁGINAS ==="
	@mkdir -p tabelas
	
	@echo "Estrutura,Páginas_Lidas,Páginas_Escritas,Taxa_Page_Faults" > tabelas/comparacao_tabelas.csv
	
	@echo "Testando Tabela Densa (0)..."
	@echo -n "Densa," >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 0 0 | grep "Páginas lidas:" | awk '{printf $$3 ","}' >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 0 0 | grep "Páginas escritas:" | awk '{printf $$3 ","}' >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 0 0 | grep "Taxa de page faults:" | awk '{print $$5}' >> tabelas/comparacao_tabelas.csv
	
	@echo "Testando Tabela Hierárquica 2 Níveis (1)..."
	@echo -n "Hierárquica_2_Níveis," >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 1 0 | grep "Páginas lidas:" | awk '{printf $$3 ","}' >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 1 0 | grep "Páginas escritas:" | awk '{printf $$3 ","}' >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 1 0 | grep "Taxa de page faults:" | awk '{print $$5}' >> tabelas/comparacao_tabelas.csv
	
	@echo "Testando Tabela Hierárquica 3 Níveis (2)..."
	@echo -n "Hierárquica_3_Níveis," >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 2 0 | grep "Páginas lidas:" | awk '{printf $$3 ","}' >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 2 0 | grep "Páginas escritas:" | awk '{printf $$3 ","}' >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 2 0 | grep "Taxa de page faults:" | awk '{print $$5}' >> tabelas/comparacao_tabelas.csv
	
	@echo "Testando Tabela Invertida (3)..."
	@echo -n "Invertida," >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 3 0 | grep "Páginas lidas:" | awk '{printf $$3 ","}' >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 3 0 | grep "Páginas escritas:" | awk '{printf $$3 ","}' >> tabelas/comparacao_tabelas.csv
	@./$(TARGET) lru compilador.log 4 128 3 0 | grep "Taxa de page faults:" | awk '{print $$5}' >> tabelas/comparacao_tabelas.csv
	
	@echo "\n=== EXECUTANDO BENCHMARK DE DESEMPENHO ==="
	@./$(TARGET) lru compilador.log 4 128 0 8 > tabelas/benchmark_performance.txt
	
	@echo "\n=== RESULTADOS ==="
	@echo "Dados salvos em tabelas/comparacao_tabelas.csv"
	@echo "Benchmark salvo em tabelas/benchmark_performance.txt"
	@echo "\nResumo:"
	@cat tabelas/comparacao_tabelas.csv

# =============================================================================
# GERAÇÃO DE PADRÕES DE TESTE
# =============================================================================

generate_patterns: $(TARGET)
	@echo "=== GERANDO PADRÕES DE TESTE ==="
	./$(TARGET) random dummy.log 4 128 9
	@echo "\nArquivos gerados:"
	@ls -l sequential.log random.log locality.log loop.log 2>/dev/null || echo "Erro: Arquivos não foram gerados"

test_patterns: $(TARGET) generate_patterns
	@echo "=== TESTANDO PADRÕES DE ACESSO PERSONALIZADOS ==="
	
	@echo "\n--- Padrão Sequencial ---"
	./$(TARGET) lru sequential.log 4 128 1
	./$(TARGET) random sequential.log 4 128 1
	./$(TARGET) lfu sequential.log 4 128 1
	./$(TARGET) clock sequential.log 4 128 1
	
	@echo "\n--- Padrão Aleatório ---"
	./$(TARGET) lru random.log 4 128 1
	./$(TARGET) random random.log 4 128 1
	./$(TARGET) lfu random.log 4 128 1
	./$(TARGET) clock random.log 4 128 1
	
	@echo "\n--- Padrão de Localidade (80/20) ---"
	./$(TARGET) lru locality.log 4 128 1
	./$(TARGET) random locality.log 4 128 1
	./$(TARGET) lfu locality.log 4 128 1
	./$(TARGET) clock locality.log 4 128 1
	
	@echo "\n--- Padrão de Loop ---"
	./$(TARGET) lru loop.log 4 128 1
	./$(TARGET) random loop.log 4 128 1
	./$(TARGET) lfu loop.log 4 128 1
	./$(TARGET) clock loop.log 4 128 1

# =============================================================================
# ANÁLISE COMPLETA E GRÁFICOS
# =============================================================================

generate_data: $(TARGET)
	@echo "=== GERANDO DADOS PARA ANÁLISE ==="
	@mkdir -p resultados/graficos/dados
	
	# Variação do tamanho da memória
	@echo "Algoritmo,Memoria_KB,Paginas_Lidas,Paginas_Escritas,Taxa_Page_Faults" > resultados/graficos/dados/memoria_variavel.csv
	@for algo in random lru lfu clock; do \
		for mem in 128 256 512 1024 2048; do \
			echo "Testando $$algo com $$mem KB de memória..."; \
			./$(TARGET) $$algo compilador.log 4 $$mem 0 0 > temp_result.txt 2>&1; \
			lidas=$$(grep "Páginas lidas:" temp_result.txt | awk '{print $$3}' | head -1); \
			escritas=$$(grep "Páginas escritas:" temp_result.txt | awk '{print $$3}' | head -1); \
			taxa=$$(grep "Taxa de page faults:" temp_result.txt | awk '{print $$5}' | sed 's/%//' | head -1); \
			if [ -n "$$lidas" ] && [ -n "$$escritas" ] && [ -n "$$taxa" ]; then \
				echo "$$algo,$$mem,$$lidas,$$escritas,$$taxa" >> resultados/graficos/dados/memoria_variavel.csv; \
			else \
				echo "$$algo,$$mem,0,0,0" >> resultados/graficos/dados/memoria_variavel.csv; \
			fi; \
			rm -f temp_result.txt; \
		done \
	done
	
	# Variação do tamanho da página
	@echo "Algoritmo,Pagina_KB,Paginas_Lidas,Paginas_Escritas,Taxa_Page_Faults" > resultados/graficos/dados/pagina_variavel.csv
	@for algo in random lru lfu clock; do \
		for pag in 2 4 8 16 32 64; do \
			echo "Testando $$algo com páginas de $$pag KB..."; \
			./$(TARGET) $$algo compilador.log $$pag 512 0 0 > temp_result.txt 2>&1; \
			lidas=$$(grep "Páginas lidas:" temp_result.txt | awk '{print $$3}' | head -1); \
			escritas=$$(grep "Páginas escritas:" temp_result.txt | awk '{print $$3}' | head -1); \
			taxa=$$(grep "Taxa de page faults:" temp_result.txt | awk '{print $$5}' | sed 's/%//' | head -1); \
			if [ -n "$$lidas" ] && [ -n "$$escritas" ] && [ -n "$$taxa" ]; then \
				echo "$$algo,$$pag,$$lidas,$$escritas,$$taxa" >> resultados/graficos/dados/pagina_variavel.csv; \
			else \
				echo "$$algo,$$pag,0,0,0" >> resultados/graficos/dados/pagina_variavel.csv; \
			fi; \
			rm -f temp_result.txt; \
		done \
	done
	
	# Diferentes workloads
	@echo "Algoritmo,Workload,Paginas_Lidas,Paginas_Escritas,Taxa_Page_Faults" > resultados/graficos/dados/workloads.csv
	@for algo in random lru lfu clock; do \
		for work in compilador matriz compressor simulador; do \
			if [ -f $$work.log ]; then \
				echo "Testando $$algo com $$work.log..."; \
				./$(TARGET) $$algo $$work.log 4 128 0 0 > temp_result.txt 2>&1; \
				lidas=$$(grep "Páginas lidas:" temp_result.txt | awk '{print $$3}' | head -1); \
				escritas=$$(grep "Páginas escritas:" temp_result.txt | awk '{print $$3}' | head -1); \
				taxa=$$(grep "Taxa de page faults:" temp_result.txt | awk '{print $$5}' | sed 's/%//' | head -1); \
				if [ -n "$$lidas" ] && [ -n "$$escritas" ] && [ -n "$$taxa" ]; then \
					echo "$$algo,$$work,$$lidas,$$escritas,$$taxa" >> resultados/graficos/dados/workloads.csv; \
				else \
					echo "$$algo,$$work,0,0,0" >> resultados/graficos/dados/workloads.csv; \
				fi; \
				rm -f temp_result.txt; \
			fi; \
		done \
	done
	
	@echo "Dados gerados em resultados/graficos/dados/"
	@wc -l resultados/graficos/dados/*.csv

generate_graphs: generate_data
	@echo "=== GERANDO GRÁFICOS COM PYTHON ==="
	@python3 -c "import pandas, matplotlib, seaborn, numpy" 2>/dev/null || (echo "Dependências Python não instaladas. Execute: make install_deps" && exit 1)
	@python3 gerar_graficos.py
	@echo "Análise completa finalizada!"
	@echo "Gráficos disponíveis em: resultados/graficos/imagens/"
	@echo "Relatório textual em: resultados/graficos/relatorio_analise.txt"

# =============================================================================
# TESTES COMPLETOS
# =============================================================================

test_all: $(TARGET)
	@echo "=== EXECUTANDO BATERIA COMPLETA DE TESTES ==="
	@make test
	@make test_tables
	@make test_patterns
	@make generate_graphs
	@echo "Todos os testes concluídos!"

# =============================================================================	
# UTILITÁRIOS
# =============================================================================

install_deps:
	@echo "Instalando dependências Python..."
	@pip3 install pandas matplotlib seaborn numpy
	@echo "Dependências instaladas!"

help:
	@echo "=== SIMULADOR DE MEMÓRIA VIRTUAL - HELP ==="
	@echo "Targets disponíveis:"
	@echo "  make              - Compila o simulador"
	@echo "  make test         - Testa todos algoritmos com todos workloads"
	@echo "  make benchmark    - Executa benchmark de desempenho com LRU"
	@echo "  make test_result - Salva resultados detalhados em arquivos separados"
	@echo "  make test_tables  - Testa estruturas de tabela de páginas"
	@echo "  make test_patterns- Testa padrões de acesso personalizados"
	@echo "  make generate_graphs - Gera análise completa com gráficos"
	@echo "  make test_all     - Executa todos os testes"
	@echo "  make clean        - Remove arquivos compilados e resultados"
	@echo "  make help         - Mostra esta ajuda"

.PHONY: all clean test benchmark test_result test_tables generate_patterns test_patterns generate_data generate_graphs test_all install_deps help