#ifndef RESOLVEDOR_CAIXEIRO_HPP
#define RESOLVEDOR_CAIXEIRO_HPP

#include <vector>
#include <string>
#include <limits>

// Estrutura que representa uma aresta do grafo que conecta duas cidades
struct Aresta {
   std::string cidade1;     
   std::string cidade2;     
   int distancia;          
};

// Classe base abstrata que implementa funcionalidades comuns para resolver o problema do caixeiro viajante
class ResolvedorCaixeiro {
   protected:
       std::vector<std::string> cidades;     
       std::vector<std::vector<int>> distancias;  
       int num_cidades;                          
       int obter_indice_cidade(const std::string& cidade);

   public:
       // Construtor que recebe lista de arestas e número de cidades
       ResolvedorCaixeiro(const std::vector<Aresta>& arestas, int n);
       virtual ~ResolvedorCaixeiro() = default;
       
       // Retorna string formatada com o caminho
       std::string obter_caminho_string(const std::vector<int>& caminho, bool incluir_primeiro = true);
       std::string obter_cidade_nome(int indice) const { return cidades[indice]; }
       
       virtual std::pair<int, std::vector<int>> resolver() = 0;
};

// Implementa estratégia de força bruta testando todas permutações possíveis
class ResolvedorForcaBruta : public ResolvedorCaixeiro {
   private:
       void trocar(std::vector<int>& vetor, int i, int j);
       bool prox_permutacao(std::vector<int>& vetor);

   public:
       using ResolvedorCaixeiro::ResolvedorCaixeiro;
       std::pair<int, std::vector<int>> resolver() override;
};

// Implementa estratégia de programação dinâmica usando memoização
class ResolvedorDinamico : public ResolvedorCaixeiro {
   private:
       int resolver_programacao_dinamica(int pos, int mascara, std::vector<std::vector<int>>& memo);
       
       std::vector<int> reconstruir_caminho(int pos, int mascara, std::vector<std::vector<int>>& memo);

   public:
       using ResolvedorCaixeiro::ResolvedorCaixeiro;
       std::pair<int, std::vector<int>> resolver() override;
};

// Implementa estratégia gulosa escolhendo sempre cidade mais próxima
class ResolvedorGuloso : public ResolvedorCaixeiro {
   public:
       using ResolvedorCaixeiro::ResolvedorCaixeiro;
       std::pair<int, std::vector<int>> resolver() override;
};

#endif