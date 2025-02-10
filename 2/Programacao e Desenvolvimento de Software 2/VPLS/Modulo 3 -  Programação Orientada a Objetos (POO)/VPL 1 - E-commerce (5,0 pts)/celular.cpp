#include "celular.hpp"

// TODO: Inicialize aqui sua variavel estatica. Caso tenha optado por essa
// solucao.

int Celular::id = 0;

Celular::Celular(std::string modelo, std::string fabricante, int armazenamento, int memoria, double peso, std::string cor, int qtd, float valor) {
  // TODO: Implemente este metodo
    this->modelo = modelo;
    this->fabricante = fabricante;
    this->armazenamento = armazenamento;
    this->memoria = memoria;
    this->peso = peso;
    this->cor = cor;
    this->qtd = qtd;
    this->valor = valor;
    this->id += 1;
    this->cod = this->id;
}

bool Celular::operator<(const Celular& other) {
  // TODO: Implemente este metodo. 
  // Preste atencao no exemplo que a descricao utilizada na ordenacao considera
  // a fabricante antes do modelo do celular
  
    std::string selectFabricante = this->fabricante.substr(1, this->fabricante.length());
    std::string outroFabricante = other.fabricante.substr(1, other.fabricante.length());

    if(selectFabricante < outroFabricante){
      return true;
    }
    std::string selectModelo = this->modelo.substr(1, this->modelo.length());
    std::string otroModelo = other.modelo.substr(1, other.modelo.length());

    if(selectModelo < otroModelo && (selectFabricante == outroFabricante)){
      return true;
    }
  
  return false;
}
  
int Celular::celularId() {
    return this->cod;
 }
