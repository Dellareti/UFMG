#include "pizza.hpp"

std::string Pizza::descricao() const{
  // TODO: Implemente este metodo.
  /*
   * Note que aqui voce deve retornar uma descricao detalhada da pizza.
   *
   * Exemplos:
   * 2X Pizza Calabresa, 4 pedacos e borda recheada.
   * 2X Pizza Calabresa, 4 pedacos sem borda recheada.
   */

  return std::to_string(getQtd()) + "X Pizza " + sabor + ", " + std::to_string(pedacos)
         + " pedacos " + (borda_recheada ? "e borda recheada." : "e sem borda recheada.");
}

Pizza::Pizza(const std::string &sabor,
             int pedacos,
             bool borda_recheada,
             int qtd,
             float valor_unitario) : sabor(sabor), pedacos(pedacos), borda_recheada(borda_recheada){
  m_qtd = qtd;
  m_valor_unitario = valor_unitario;
}