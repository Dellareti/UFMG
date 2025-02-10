#include "venda.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

//Auxiliares 

void trocaCelular(Celular *x,Celular* y){
    Celular temp = *x;
    *x = *y;
    *y = temp;
}

Celular celularIndex(std::list<Celular> _list, int _idx) {
    
    std::list<Celular>::iterator i = _list.begin();
    for (int j = 0; j < _idx; j++){
    ++i;
}
  return *i;
}

int listaParticao(std::list<Celular> celularArranjo, int low, int high) {
  Celular pivo = celularIndex(celularArranjo, high);    
  int i = (low - 1); 

  for (int j = low; j <= high - 1; j++)  {
    
    Celular celularAtual = celularIndex(celularArranjo, j);
    if (!(pivo.operator<(celularAtual))) {
      i++;   
      
      Celular smallerElement = celularIndex(celularArranjo, i);
      trocaCelular(&smallerElement, &celularAtual);
    }
  }
  
  Celular trocaPivoCelular = celularIndex(celularArranjo, i + 1);
  trocaCelular(&trocaPivoCelular, &pivo);
  return (i + 1);
}

void quickSort(std::list<Celular> celularArranjo, int low, int high) {
  if (low < high) {
    int pi = listaParticao(celularArranjo, low, high);

    quickSort(celularArranjo, low, pi -1);
    quickSort(celularArranjo, pi +1, high);
  }
}

bool comparaItens(Celular primeiro, Celular segundo) {
    
  std::string selectPrimeiroFabricante = primeiro.fabricante.substr(1, primeiro.fabricante.length());
  std::string selectSegundoFabricante = segundo.fabricante.substr(1, segundo.fabricante.length());

  std::string selectPrimeirotModelo = primeiro.modelo.substr(1, primeiro.modelo.length());
  std::string selectSegundoModelo = segundo.modelo.substr(1, segundo.modelo.length());

  if(primeiro.fabricante != segundo.fabricante){
    return primeiro.fabricante < segundo.fabricante;
  }
  else if(primeiro.modelo != segundo.modelo){
    return primeiro.modelo < segundo.modelo;
  }
}


//Fim

void Venda::adicionaCelular(const Celular& celular) {
  // TODO: Implemente este metodo
    this->m_celulares.push_front(celular);
  
}

void Venda::ordena() {
  // TODO: Implemente este metodo
  // Preste atencao no exemplo que a descricao utilizada na ordenacao considera
  // a fabricante antes do modelo do celular
  
    this->m_celulares.sort(comparaItens);
}

void Venda::recarregaEstoque(int cod, int qtd) {
  // TODO: Implemente este metodo
  
    std::list<Celular>::iterator i;
    
    for (i = this->m_celulares.begin(); i != this->m_celulares.end(); ++i) {
      if(i->celularId() == cod) {
         i->qtd += qtd;
      return;
    }
  }
}

void Venda::efetuaVenda(int cod, int qtd) {
  // TODO: Implemente este metodo
  /**
   * Observe na descricao do enunciado que nao e permita a venda de um modelo
   * cuja quantidade seja maior que a quantidade atual em estoque.
   * Ex: Se existirem apenas 5 celulares Motorola Moto G50 em estoque, vendas a
   * partir de 6 unidades devem ser ignoradas.
   */
   
    std::list<Celular>::iterator i;
    
    for (i = this->m_celulares.begin(); i != this->m_celulares.end(); ++i) {
      if(i->celularId() == cod) {
        if(i->qtd >= qtd)
          i->qtd -= qtd;
          
      if(i->qtd == 0)
        Venda::removeModelo(cod);
      return;
    }
  }
}

void Venda::aplicaDesconto(const std::string& fabricante, float desconto) {
  // TODO: Implemente este metodo
  
    std::list<Celular>::iterator i;
    
    for (i = this->m_celulares.begin(); i != this->m_celulares.end(); ++i) {
      if(i->fabricante == fabricante){
      i->valor -= i->valor*(desconto/100);
   }
 }
}

void Venda::removeModelo(int cod) {
  // TODO: Implemente este metodo
  
    std::list<Celular>::iterator i;

    for (i = this->m_celulares.begin(); i != this->m_celulares.end(); ++i) {
      if(i->celularId() == cod) {
        this->m_celulares.erase(i);
        return;
     } 
   } 
 }

void Venda::imprimeEstoque() const {
  // TODO: Implemente este metodo.
  /**
   * Aqui voce tera que imprimir a lista de celulares em estoque com as
   * restricoes descritas no enunciado do problema. Notem no exemplo que a
   * primeira letra da cor do celular fica maiuscula. Outra coisa, se houver
   * apenas um item em estoque de determinado modelo de celular, voce tera que
   * imprimir '1 restante' e nao '1 restantes'. Por ultimo, apenas modelos de
   * celulares com pelo menos um item em estoque deverao ser exibidos.
   */
   
   for(const auto& celular : this->m_celulares) {
       
    std::cout << celular.fabricante; 
    std::cout << " ";

    std::cout << celular.modelo; 
    std::cout << ", ";

    std::cout << celular.armazenamento; 
    std::cout << "GB, ";

    std::cout << celular.memoria; 
    std::cout << "GB RAM, ";

    std::cout << (int)(celular.peso*1000); 
    std::cout << " gramas, ";

    std::string print = "";
    print += std::toupper(celular.cor[0]);
    print += celular.cor.substr(1, celular.cor.size());

    std::cout << print;
    std::cout << ", ";

    std::cout << celular.qtd; 
    if(celular.qtd == 1)
      std::cout << " restante, ";
    else
      std::cout << " restantes, ";

    std::cout << "R$ ";
    std::cout << std::fixed << std::setprecision(2) << celular.valor;

    std::cout << std::endl;
  }
   
}