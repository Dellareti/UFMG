import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
import numpy as np
import warnings

# Suprimir warnings desnecessários
warnings.filterwarnings('ignore')

# Configuração do estilo dos gráficos
plt.style.use('default')
sns.set_palette("husl")

# Criar diretório para salvar os gráficos
os.makedirs('resultados/graficos/imagens', exist_ok=True)

def carregar_dados():
    # Carrega os dados dos arquivos CSV
    try:
        memoria_df = pd.read_csv('resultados/graficos/dados/memoria_variavel.csv')
        pagina_df = pd.read_csv('resultados/graficos/dados/pagina_variavel.csv')
        workload_df = pd.read_csv('resultados/graficos/dados/workloads.csv')
        
        # Limpar dados inválidos
        memoria_df = memoria_df.dropna()
        pagina_df = pagina_df.dropna()
        workload_df = workload_df.dropna()
        
        return memoria_df, pagina_df, workload_df
    except FileNotFoundError as e:
        print(f"Erro: Arquivo não encontrado - {e}")
        print("Execute 'make generate_data_for_graphs' primeiro!")
        return None, None, None

def grafico_memoria_variavel(df):
    # Gera gráficos variando o tamanho da memória
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 10))
    fig.suptitle('Análise dos Algoritmos - Variação do Tamanho da Memória\n(Páginas fixas em 4KB)', fontsize=16)
    
    # Gráfico 1: Taxa de Page Faults
    for algo in df['Algoritmo'].unique():
        algo_data = df[df['Algoritmo'] == algo]
        if not algo_data.empty:
            ax1.plot(algo_data['Memoria_KB'], algo_data['Taxa_Page_Faults'], 
                    marker='o', linewidth=2, label=algo.upper())
    ax1.set_xlabel('Tamanho da Memória (KB)')
    ax1.set_ylabel('Taxa de Page Faults (%)')
    ax1.set_title('Taxa de Page Faults vs Tamanho da Memória')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    # Gráfico 2: Páginas Lidas
    for algo in df['Algoritmo'].unique():
        algo_data = df[df['Algoritmo'] == algo]
        if not algo_data.empty:
            ax2.plot(algo_data['Memoria_KB'], algo_data['Paginas_Lidas'], 
                    marker='s', linewidth=2, label=algo.upper())
    ax2.set_xlabel('Tamanho da Memória (KB)')
    ax2.set_ylabel('Páginas Lidas')
    ax2.set_title('Páginas Lidas vs Tamanho da Memória')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    # Gráfico 3: Páginas Escritas
    for algo in df['Algoritmo'].unique():
        algo_data = df[df['Algoritmo'] == algo]
        if not algo_data.empty:
            ax3.plot(algo_data['Memoria_KB'], algo_data['Paginas_Escritas'], 
                    marker='^', linewidth=2, label=algo.upper())
    ax3.set_xlabel('Tamanho da Memória (KB)')
    ax3.set_ylabel('Páginas Escritas')
    ax3.set_title('Páginas Escritas vs Tamanho da Memória')
    ax3.legend()
    ax3.grid(True, alpha=0.3)
    
    # Gráfico 4: Comparação combinada
    try:
        pivot_data = df.pivot(index='Memoria_KB', columns='Algoritmo', values='Taxa_Page_Faults')
        pivot_data.plot(kind='bar', ax=ax4, width=0.8)
        ax4.set_xlabel('Tamanho da Memória (KB)')
        ax4.set_ylabel('Taxa de Page Faults (%)')
        ax4.set_title('Comparação das Taxas de Page Faults')
        ax4.legend(title='Algoritmo')
        ax4.set_xticklabels(ax4.get_xticklabels(), rotation=45)
    except Exception as e:
        ax4.text(0.5, 0.5, f'Erro ao gerar gráfico:\n{str(e)}', 
                transform=ax4.transAxes, ha='center', va='center')
    
    plt.tight_layout()
    plt.savefig('resultados/graficos/imagens/memoria_variavel.png', dpi=300, bbox_inches='tight')
    plt.close()
    print("✓ Gráfico 'memoria_variavel.png' gerado")

def grafico_pagina_variavel(df):
    # Gera gráficos variando o tamanho da página
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 10))
    fig.suptitle('Análise dos Algoritmos - Variação do Tamanho da Página\n(Memória fixa em 512KB)', fontsize=16)
    
    # Gráfico 1: Taxa de Page Faults
    for algo in df['Algoritmo'].unique():
        algo_data = df[df['Algoritmo'] == algo]
        if not algo_data.empty:
            ax1.plot(algo_data['Pagina_KB'], algo_data['Taxa_Page_Faults'], 
                    marker='o', linewidth=2, label=algo.upper())
    ax1.set_xlabel('Tamanho da Página (KB)')
    ax1.set_ylabel('Taxa de Page Faults (%)')
    ax1.set_title('Taxa de Page Faults vs Tamanho da Página')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    ax1.set_xscale('log', base=2)
    
    # Gráfico 2: Páginas Lidas
    for algo in df['Algoritmo'].unique():
        algo_data = df[df['Algoritmo'] == algo]
        if not algo_data.empty:
            ax2.plot(algo_data['Pagina_KB'], algo_data['Paginas_Lidas'], 
                    marker='s', linewidth=2, label=algo.upper())
    ax2.set_xlabel('Tamanho da Página (KB)')
    ax2.set_ylabel('Páginas Lidas')
    ax2.set_title('Páginas Lidas vs Tamanho da Página')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    ax2.set_xscale('log', base=2)
    
    # Gráfico 3: Páginas Escritas
    for algo in df['Algoritmo'].unique():
        algo_data = df[df['Algoritmo'] == algo]
        if not algo_data.empty:
            ax3.plot(algo_data['Pagina_KB'], algo_data['Paginas_Escritas'], 
                    marker='^', linewidth=2, label=algo.upper())
    ax3.set_xlabel('Tamanho da Página (KB)')
    ax3.set_ylabel('Páginas Escritas')
    ax3.set_title('Páginas Escritas vs Tamanho da Página')
    ax3.legend()
    ax3.grid(True, alpha=0.3)
    ax3.set_xscale('log', base=2)
    
    # Gráfico 4: Heatmap das taxas de page faults
    try:
        pivot_data = df.pivot(index='Algoritmo', columns='Pagina_KB', values='Taxa_Page_Faults')
        if not pivot_data.empty and not pivot_data.isnull().all().all():
            sns.heatmap(pivot_data, annot=True, fmt='.1f', cmap='YlOrRd', ax=ax4)
            ax4.set_title('Heatmap: Taxa de Page Faults por Algoritmo e Tamanho da Página')
            ax4.set_xlabel('Tamanho da Página (KB)')
            ax4.set_ylabel('Algoritmo')
        else:
            ax4.text(0.5, 0.5, 'Dados insuficientes\npara heatmap', 
                    transform=ax4.transAxes, ha='center', va='center')
    except Exception as e:
        ax4.text(0.5, 0.5, f'Erro ao gerar heatmap:\n{str(e)}', 
                transform=ax4.transAxes, ha='center', va='center')
    
    plt.tight_layout()
    plt.savefig('resultados/graficos/imagens/pagina_variavel.png', dpi=300, bbox_inches='tight')
    plt.close()
    print("✓ Gráfico 'pagina_variavel.png' gerado")

def grafico_workloads(df):
    # Gera gráficos comparando diferentes workloads
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 10))
    fig.suptitle('Análise dos Algoritmos - Diferentes Workloads\n(4KB páginas, 128KB memória)', fontsize=16)
    
    # Gráfico 1: Taxa de Page Faults por workload
    try:
        pivot_data = df.pivot(index='Workload', columns='Algoritmo', values='Taxa_Page_Faults')
        if not pivot_data.empty:
            pivot_data.plot(kind='bar', ax=ax1, width=0.8)
            ax1.set_xlabel('Workload')
            ax1.set_ylabel('Taxa de Page Faults (%)')
            ax1.set_title('Taxa de Page Faults por Workload')
            ax1.legend(title='Algoritmo')
            ax1.set_xticklabels(ax1.get_xticklabels(), rotation=45)
    except Exception as e:
        ax1.text(0.5, 0.5, f'Erro no gráfico 1:\n{str(e)}', 
                transform=ax1.transAxes, ha='center', va='center')
    
    # Gráfico 2: Páginas Lidas por workload
    try:
        pivot_data = df.pivot(index='Workload', columns='Algoritmo', values='Paginas_Lidas')
        if not pivot_data.empty:
            pivot_data.plot(kind='bar', ax=ax2, width=0.8)
            ax2.set_xlabel('Workload')
            ax2.set_ylabel('Páginas Lidas')
            ax2.set_title('Páginas Lidas por Workload')
            ax2.legend(title='Algoritmo')
            ax2.set_xticklabels(ax2.get_xticklabels(), rotation=45)
    except Exception as e:
        ax2.text(0.5, 0.5, f'Erro no gráfico 2:\n{str(e)}', 
                transform=ax2.transAxes, ha='center', va='center')
    
    # Gráfico 3: Páginas Escritas por workload
    try:
        pivot_data = df.pivot(index='Workload', columns='Algoritmo', values='Paginas_Escritas')
        if not pivot_data.empty:
            pivot_data.plot(kind='bar', ax=ax3, width=0.8)
            ax3.set_xlabel('Workload')
            ax3.set_ylabel('Páginas Escritas')
            ax3.set_title('Páginas Escritas por Workload')
            ax3.legend(title='Algoritmo')
            ax3.set_xticklabels(ax3.get_xticklabels(), rotation=45)
    except Exception as e:
        ax3.text(0.5, 0.5, f'Erro no gráfico 3:\n{str(e)}', 
                transform=ax3.transAxes, ha='center', va='center')
    
    # Gráfico 4: Heatmap comparativo
    try:
        pivot_data = df.pivot(index='Algoritmo', columns='Workload', values='Taxa_Page_Faults')
        if not pivot_data.empty and not pivot_data.isnull().all().all():
            sns.heatmap(pivot_data, annot=True, fmt='.1f', cmap='RdYlBu_r', ax=ax4)
            ax4.set_title('Heatmap: Taxa de Page Faults por Algoritmo e Workload')
            ax4.set_xlabel('Workload')
            ax4.set_ylabel('Algoritmo')
        else:
            ax4.text(0.5, 0.5, 'Dados insuficientes\npara heatmap', 
                    transform=ax4.transAxes, ha='center', va='center')
    except Exception as e:
        ax4.text(0.5, 0.5, f'Erro no heatmap:\n{str(e)}', 
                transform=ax4.transAxes, ha='center', va='center')
    
    plt.tight_layout()
    plt.savefig('resultados/graficos/imagens/workloads.png', dpi=300, bbox_inches='tight')
    plt.close()
    print("✓ Gráfico 'workloads.png' gerado")

def grafico_comparativo_geral(memoria_df, pagina_df, workload_df):
    # Gera um gráfico comparativo geral dos algoritmos
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(16, 12))
    fig.suptitle('Análise Comparativa Geral dos Algoritmos de Substituição', fontsize=16)
    
    # Gráfico 1: Desempenho médio por algoritmo
    algoritmos = ['random', 'lru', 'lfu', 'clock']
    cores = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4']
    
    # Calcular médias
    medias_pf = []
    medias_pl = []
    medias_pe = []
    
    for algo in algoritmos:
        # Média das taxas de page faults em diferentes cenários
        try:
            pf_memoria = memoria_df[memoria_df['Algoritmo'] == algo]['Taxa_Page_Faults'].mean()
            pf_pagina = pagina_df[pagina_df['Algoritmo'] == algo]['Taxa_Page_Faults'].mean()
            pf_workload = workload_df[workload_df['Algoritmo'] == algo]['Taxa_Page_Faults'].mean()
            
            # Verificar se os valores são válidos
            valid_values = [x for x in [pf_memoria, pf_pagina, pf_workload] if not pd.isna(x)]
            if valid_values:
                medias_pf.append(sum(valid_values) / len(valid_values))
            else:
                medias_pf.append(0)
            
            # Páginas lidas (normalizadas)
            pl_memoria = memoria_df[memoria_df['Algoritmo'] == algo]['Paginas_Lidas'].mean()
            medias_pl.append(pl_memoria if not pd.isna(pl_memoria) else 0)
            
            # Páginas escritas (normalizadas)
            pe_memoria = memoria_df[memoria_df['Algoritmo'] == algo]['Paginas_Escritas'].mean()
            medias_pe.append(pe_memoria if not pd.isna(pe_memoria) else 0)
        except Exception as e:
            print(f"Erro ao calcular médias para {algo}: {e}")
            medias_pf.append(0)
            medias_pl.append(0)
            medias_pe.append(0)
    
    # Barras para taxa de page faults
    bars1 = ax1.bar(algoritmos, medias_pf, color=cores, alpha=0.8)
    ax1.set_xlabel('Algoritmo')
    ax1.set_ylabel('Taxa Média de Page Faults (%)')
    ax1.set_title('Taxa Média de Page Faults por Algoritmo')
    ax1.grid(True, alpha=0.3)
    
    # Adicionar valores nas barras
    for bar, valor in zip(bars1, medias_pf):
        if valor > 0:
            ax1.text(bar.get_x() + bar.get_width()/2, bar.get_height() + max(medias_pf)*0.01,
                    f'{valor:.1f}%', ha='center', va='bottom')
    
    # Gráfico 2: Eficiência relativa (menor é melhor)
    if max(medias_pf) > 0:
        eficiencia = [pf / min([x for x in medias_pf if x > 0]) if pf > 0 else 1 for pf in medias_pf]
    else:
        eficiencia = [1] * len(medias_pf)
    
    bars2 = ax2.bar(algoritmos, eficiencia, color=cores, alpha=0.8)
    ax2.set_xlabel('Algoritmo')
    ax2.set_ylabel('Eficiência Relativa')
    ax2.set_title('Eficiência Relativa dos Algoritmos\n(1.0 = melhor desempenho)')
    ax2.grid(True, alpha=0.3)
    ax2.axhline(y=1.0, color='red', linestyle='--', alpha=0.5)
    
    for bar, valor in zip(bars2, eficiencia):
        ax2.text(bar.get_x() + bar.get_width()/2, bar.get_height() + max(eficiencia)*0.01,
                f'{valor:.2f}', ha='center', va='bottom')
    
    # Gráfico 3: Comparação simples (sem radar)
    x_pos = np.arange(len(algoritmos))
    width = 0.25
    
    # Normalizar as métricas para comparação
    if max(medias_pf) > 0:
        pf_norm = [100 - pf for pf in medias_pf]  # Inverter (maior é melhor)
    else:
        pf_norm = [100] * len(medias_pf)
    
    if max(medias_pl) > min(medias_pl):
        pl_norm = [100 - ((pl - min(medias_pl)) / (max(medias_pl) - min(medias_pl))) * 100 for pl in medias_pl]
    else:
        pl_norm = [100] * len(medias_pl)
    
    if max(medias_pe) > min(medias_pe):
        pe_norm = [100 - ((pe - min(medias_pe)) / (max(medias_pe) - min(medias_pe))) * 100 for pe in medias_pe]
    else:
        pe_norm = [100] * len(medias_pe)
    
    ax3.bar(x_pos - width, pf_norm, width, label='Page Faults (inv)', alpha=0.8)
    ax3.bar(x_pos, pl_norm, width, label='Páginas Lidas (inv)', alpha=0.8)
    ax3.bar(x_pos + width, pe_norm, width, label='Páginas Escritas (inv)', alpha=0.8)
    
    ax3.set_xlabel('Algoritmo')
    ax3.set_ylabel('Score Normalizado (maior = melhor)')
    ax3.set_title('Comparação Multidimensional Normalizada')
    ax3.set_xticks(x_pos)
    ax3.set_xticklabels([algo.upper() for algo in algoritmos])
    ax3.legend()
    ax3.grid(True, alpha=0.3)
    
    # Gráfico 4: Ranking dos algoritmos
    if any(pf > 0 for pf in medias_pf):
        ranking_data = pd.DataFrame({
            'Algoritmo': [algo.upper() for algo in algoritmos],
            'Taxa_PF': medias_pf,
            'Páginas_Lidas': medias_pl,
            'Páginas_Escritas': medias_pe,
            'Eficiência': eficiencia
        })
        
        # Criar ranking baseado na taxa de page faults
        ranking_data = ranking_data[ranking_data['Taxa_PF'] > 0]  # Remover valores zero
        if not ranking_data.empty:
            ranking_data = ranking_data.sort_values('Taxa_PF')
            
            bars4 = ax4.barh(ranking_data['Algoritmo'], ranking_data['Taxa_PF'], color=cores[:len(ranking_data)])
            ax4.set_xlabel('Taxa de Page Faults (%)')
            ax4.set_ylabel('Algoritmo')
            ax4.set_title('Ranking dos Algoritmos\n(baseado na taxa de page faults)')
            ax4.grid(True, alpha=0.3)
            
            for i, (algo, valor) in enumerate(zip(ranking_data['Algoritmo'], ranking_data['Taxa_PF'])):
                ax4.text(valor + max(ranking_data['Taxa_PF'])*0.01, i, f'{valor:.1f}%', va='center')
        else:
            ax4.text(0.5, 0.5, 'Dados insuficientes\npara ranking', 
                    transform=ax4.transAxes, ha='center', va='center')
    else:
        ax4.text(0.5, 0.5, 'Dados insuficientes\npara ranking', 
                transform=ax4.transAxes, ha='center', va='center')
    
    plt.tight_layout()
    plt.savefig('resultados/graficos/imagens/comparativo_geral.png', dpi=300, bbox_inches='tight')
    plt.close()
    print("✓ Gráfico 'comparativo_geral.png' gerado")

def gerar_relatorio_textual(memoria_df, pagina_df, workload_df):
    # Gera um relatório textual com as principais conclusões
    with open('resultados/graficos/relatorio_analise.txt', 'w', encoding='utf-8') as f:
        f.write("="*80 + "\n")
        f.write("RELATÓRIO DE ANÁLISE DOS ALGORITMOS DE SUBSTITUIÇÃO DE PÁGINAS\n")
        f.write("="*80 + "\n\n")
        
        # Verificar se há dados válidos
        if memoria_df.empty or pagina_df.empty or workload_df.empty:
            f.write("ERRO: Dados insuficientes para análise.\n")
            f.write("Verifique se os arquivos CSV foram gerados corretamente.\n")
            return
        
        # Análise por algoritmo
        f.write("1. DESEMPENHO MÉDIO POR ALGORITMO\n")
        f.write("-"*40 + "\n")
        
        algoritmos = ['random', 'lru', 'lfu', 'clock']
        ranking = []
        
        for algo in algoritmos:
            try:
                algo_memoria = memoria_df[memoria_df['Algoritmo'] == algo]
                if not algo_memoria.empty:
                    pf_media = algo_memoria['Taxa_Page_Faults'].mean()
                    pl_media = algo_memoria['Paginas_Lidas'].mean()
                    pe_media = algo_memoria['Paginas_Escritas'].mean()
                    
                    f.write(f"\n{algo.upper()}:\n")
                    f.write(f"  - Taxa média de page faults: {pf_media:.2f}%\n")
                    f.write(f"  - Páginas lidas (média): {pl_media:.0f}\n")
                    f.write(f"  - Páginas escritas (média): {pe_media:.0f}\n")
                    
                    ranking.append((algo, pf_media))
                else:
                    f.write(f"\n{algo.upper()}: Dados não disponíveis\n")
            except Exception as e:
                f.write(f"\n{algo.upper()}: Erro ao processar dados - {e}\n")
        
        # Ranking dos algoritmos
        if ranking:
            f.write("\n2. RANKING DOS ALGORITMOS\n")
            f.write("-"*40 + "\n")
            
            ranking.sort(key=lambda x: x[1])
            
            for i, (algo, pf) in enumerate(ranking, 1):
                f.write(f"{i}º lugar: {algo.upper()} - {pf:.2f}% de page faults\n")
        
        # Análise por workload
        f.write("\n3. ANÁLISE POR WORKLOAD\n")
        f.write("-"*40 + "\n")
        
        try:
            for workload in workload_df['Workload'].unique():
                f.write(f"\n{workload.upper()}:\n")
                workload_data = workload_df[workload_df['Workload'] == workload]
                if not workload_data.empty:
                    melhor_idx = workload_data['Taxa_Page_Faults'].idxmin()
                    melhor_algo = workload_data.loc[melhor_idx, 'Algoritmo']
                    melhor_taxa = workload_data['Taxa_Page_Faults'].min()
                    f.write(f"  - Melhor algoritmo: {melhor_algo.upper()} ({melhor_taxa:.2f}% page faults)\n")
                    
                    for _, row in workload_data.iterrows():
                        f.write(f"  - {row['Algoritmo'].upper()}: {row['Taxa_Page_Faults']:.2f}% page faults\n")
                else:
                    f.write(f"  - Dados não disponíveis para {workload}\n")
        except Exception as e:
            f.write(f"Erro ao analisar workloads: {e}\n")
        
        # Conclusões gerais
        if ranking:
            f.write("\n4. CONCLUSÕES GERAIS\n")
            f.write("-"*40 + "\n")
            f.write("• O algoritmo com melhor desempenho geral foi: " + ranking[0][0].upper() + "\n")
            f.write("• O algoritmo com pior desempenho geral foi: " + ranking[-1][0].upper() + "\n")
            f.write("• A diferença entre o melhor e pior algoritmo foi de " + 
                    f"{ranking[-1][1] - ranking[0][1]:.2f} pontos percentuais\n")
        
        # Observações específicas
        f.write("\n5. OBSERVAÇÕES ESPECÍFICAS\n")
        f.write("-"*40 + "\n")
        f.write("• LRU geralmente apresenta melhor desempenho em workloads com localidade temporal\n")
        f.write("• Random serve como baseline para comparação com outros algoritmos\n")
        f.write("• Clock oferece um bom compromisso entre desempenho e simplicidade\n")
        f.write("• LFU pode ser eficaz em workloads com padrões de acesso repetitivos\n")
    
    print("✓ Relatório textual 'relatorio_analise.txt' gerado")

def main():
    print("Gerando gráficos de análise do simulador...")
    print("="*50)
    
    # Carregar dados
    memoria_df, pagina_df, workload_df = carregar_dados()
    
    if memoria_df is None:
        return
    
    # Verificar se há dados válidos
    print(f"Dados carregados:")
    print(f"- Memória variável: {len(memoria_df)} registros")
    print(f"- Página variável: {len(pagina_df)} registros")
    print(f"- Workloads: {len(workload_df)} registros")
    print()
    
    # Gerar gráficos
    try:
        grafico_memoria_variavel(memoria_df)
        grafico_pagina_variavel(pagina_df)
        grafico_workloads(workload_df)
        grafico_comparativo_geral(memoria_df, pagina_df, workload_df)
        
        # Gerar relatório textual
        gerar_relatorio_textual(memoria_df, pagina_df, workload_df)
        
        print("="*50)
        print("Todos os gráficos foram gerados com sucesso!")
        print("Arquivos salvos em: resultados/graficos/imagens/")
        print("Relatório textual: resultados/graficos/relatorio_analise.txt")
        print("\nGráficos gerados:")
        print("  • memoria_variavel.png - Análise variando tamanho da memória")
        print("  • pagina_variavel.png - Análise variando tamanho das páginas")
        print("  • workloads.png - Comparação entre diferentes workloads")
        print("  • comparativo_geral.png - Análise comparativa geral")
        
    except Exception as e:
        print(f"Erro durante a geração dos gráficos: {e}")
        print("Verifique se os dados foram gerados corretamente.")

if __name__ == "__main__":
    main()