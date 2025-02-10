#include "venda.hpp"

#include <iomanip>

Venda::~Venda() {
  /**
   * Aqui voce deve deletar os ponteiros contidos na lista m_pedidos
   */
  for (auto p : m_pedidos){
    delete p;
  }
}

void Venda::adicionaPedido(Pedido* p) {
  m_pedidos.push_back(p);
}

void Venda::imprimeRelatorio() const {
  /**
   * Aqui voce tem que percorrer a lista de todos os pedidos e imprimir o resumo
   * de cada um. Por ultimo, devera ser exibido o total de venda e a quantidade
   * de pedidos processados.
   */
  auto total = 0.0;
  auto i = 1;
  for (auto pedido : m_pedidos){
    std::cout << "Pedido " << i++ << std::endl;
    std::cout << pedido->resumo() << std::endl;
    total += pedido->calculaTotal();
  }
  std::cout << "Relatorio de Vendas" << std::endl;
  std::cout << "Total de vendas: R$ " << std::fixed << std::setprecision(2) << total << std::endl;
  std::cout << "Total de pedidos: " << m_pedidos.size() << std::endl;
}