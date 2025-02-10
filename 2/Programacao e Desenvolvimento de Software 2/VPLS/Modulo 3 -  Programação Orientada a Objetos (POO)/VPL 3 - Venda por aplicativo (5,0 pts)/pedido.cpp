#include "pedido.hpp"

Pedido::~Pedido(){
  /**
   * Aqui voce deve deletar os ponteiros contidos na lista m_produtos
   */
  for (auto p : m_produtos){
    delete p;
  }
}

void Pedido::setEndereco(const std::string &endereco){
  m_endereco = endereco;
}

float Pedido::calculaTotal() const{
  auto total = 0.0f;
  for (auto produto : m_produtos){
    total += produto->getValor() * produto->getQtd();
  }
  return total;
}

void Pedido::adicionaProduto(Produto *p){
  m_produtos.push_back(p);
}

std::string Pedido::resumo() const{
  /**
   * Aqui voce deve percorrer a lista de produtos para criar um resumo completo
   * do pedido. A cada iteracao, utilize o metodo descricao de cada produto para
   * montar o resumo do pedido. Por fim, adicione o endereco de entrega.
   *
   */
  std::string resumo;
  for (auto produto : m_produtos){
    resumo += produto->descricao() + '\n';
  }
  resumo += "Endereco: " + m_endereco;
  return resumo;
}