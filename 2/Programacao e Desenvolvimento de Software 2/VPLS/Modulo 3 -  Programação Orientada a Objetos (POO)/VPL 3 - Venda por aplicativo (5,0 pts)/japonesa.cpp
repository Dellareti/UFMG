#include "japonesa.hpp"

std::string Japonesa::descricao() const {
  // TODO: Implemente este metodo.
  /*
   * Note que aqui voce deve retornar uma descricao detalhada da comida
   * japonesa.
   *
   * Exemplos:
   * 1X Comida japonesa - Combo 1, 4 sushis, 5 temakis e 6 hots.
   * 1X Comida japonesa - Combo 2, 5 sushis, 6 temakis e 8 hots.
   */
   
  return std::to_string(getQtd()) + "X Comida japonesa - " + combinado + ", " + std::to_string(sushi)
         + " sushis, " + std::to_string(temaki) + " temakis e " + std::to_string(hots) + " hots.";
}

Japonesa::Japonesa(const std::string& combinado,
                   int sushi,
                   int temaki,
                   int hots,
                   int qtd,
                   float valor_unitario) : combinado(combinado), sushi(sushi), temaki(temaki), hots(hots) {
  m_qtd = qtd;
  m_valor_unitario = valor_unitario; 
}