import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Configurações básicas de estilo
plt.style.use('default')

# Lê os dados
fb = pd.read_csv('metricas/ForcaBruta.csv')
pd_data = pd.read_csv('metricas/ProgDinamica.csv')
guloso = pd.read_csv('metricas/Guloso.csv')

# Configuração dos ticks do eixo x
min_cidades = min(min(fb['num_cidades']), min(pd_data['num_cidades']), min(guloso['num_cidades']))
max_cidades = max(max(fb['num_cidades']), max(pd_data['num_cidades']), max(guloso['num_cidades']))
xticks = range(min_cidades, max_cidades + 1)

# Gráfico 1: Tempo x Número de Cidades
plt.figure(figsize=(12, 6))
plt.semilogy(fb['num_cidades'], fb['tempo_ms'], 'ro-', label='Força Bruta', linewidth=2, markersize=8)
plt.semilogy(pd_data['num_cidades'], pd_data['tempo_ms'], 'bs-', label='Programação Dinâmica', linewidth=2, markersize=8)
plt.semilogy(guloso['num_cidades'], guloso['tempo_ms'], 'g^-', label='Guloso', linewidth=2, markersize=8)
plt.grid(True)
plt.xticks(xticks)
plt.xlabel('Número de Cidades')
plt.ylabel('Tempo (ms) - Escala Log')
plt.title('Comparação de Tempo de Execução')
plt.legend()
plt.savefig('grafico_tempo.png', dpi=300, bbox_inches='tight')
plt.close()

# Gráfico 2: Memória x Número de Cidades
plt.figure(figsize=(12, 6))
# Plotando PD primeiro porque tem valores maiores
plt.plot(pd_data['num_cidades'], pd_data['memoria_kb'], 'bs-', label='Programação Dinâmica', linewidth=2, markersize=8)
# Depois plotamos Força Bruta e Guloso com marcadores maiores e cores diferentes
plt.plot(guloso['num_cidades'], guloso['memoria_kb'], 'g^-', label='Guloso', linewidth=2, markersize=10, alpha=0.7)
plt.plot(fb['num_cidades'], fb['memoria_kb'], 'rD-', label='Força Bruta', linewidth=2, markersize=10, alpha=0.7)
plt.grid(True)
plt.xticks(xticks)
plt.xlabel('Número de Cidades')
plt.ylabel('Memória (KB)')
plt.title('Comparação de Uso de Memória')
plt.legend()
plt.savefig('grafico_memoria.png', dpi=300, bbox_inches='tight')
plt.close()

# Gráfico 3: Qualidade da Solução
plt.figure(figsize=(12, 6))
plt.plot(pd_data['num_cidades'], pd_data['custo'], 'bs-', label='Solução Ótima (Programação Dinâmica)', linewidth=2, alpha=0.7, markersize=8)
plt.plot(guloso['num_cidades'], guloso['custo'], 'g^-', label='Solução Gulosa', linewidth=2, alpha=0.7, markersize=8)
plt.grid(True)
plt.xticks(xticks)
plt.xlabel('Número de Cidades')
plt.ylabel('Custo da Solução')
plt.title('Comparação da Qualidade das Soluções')
plt.legend()
plt.savefig('grafico_qualidade.png', dpi=300, bbox_inches='tight')
plt.close()

# Cálculo e impressão de estatísticas
print("\nEstatísticas:")
print("\nForça Bruta:")
print(f"Máximo número de cidades: {fb['num_cidades'].max()}")
print(f"Tempo máximo: {fb['tempo_ms'].max()/1000:.2f} segundos")

print("\nProgramação Dinâmica:")
print(f"Máximo número de cidades: {pd_data['num_cidades'].max()}")
print(f"Tempo máximo: {pd_data['tempo_ms'].max()/1000:.2f} segundos")
print(f"Memória máxima: {pd_data['memoria_kb'].max()/1024:.2f} MB")

print("\nGuloso vs Ótimo:")
merged = pd.merge(pd_data, guloso, on='num_cidades', suffixes=('_pd', '_guloso'))
merged['diferenca_percentual'] = ((merged['custo_guloso'] - merged['custo_pd']) / merged['custo_pd'] * 100)
print(f"Média de desvio do ótimo: {merged['diferenca_percentual'].mean():.2f}%")
print(f"Máximo desvio do ótimo: {merged['diferenca_percentual'].max():.2f}%")