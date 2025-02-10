#include <regex>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>

#include "LineProcessor.hpp"

void LinePrinter::processaLinha(const std::string &str){
  std::cout << str << std::endl;
}

bool ContadorPopRural::linhaValida(const std::string &str) const{
  // Neste exemplo usaremos expressoes regulares para verificar se uma linha
  // eh valida ou nao.
  //
  // Esta expressao regular eh formada por cinco partes. Cada uma dessas
  // partes eh um dos tres tipos de padrao regular abaixo:
  //
  // \\w+ eh qualquer palavra com um ou mais digitos, letras e sublinhas (_)
  // \\s* eh qualquer sequencia de zero ou mais espacos (inclui tab)
  // \\d+ eh qualquer sequencia de um ou mais digitos
  std::regex regularExpr("\\w+\\s*\\d+\\s*\\d+");

  // A funcao regex_match vai retornar verdadeiro se a string str casa-se com
  // a expressao regular que acabamos de criar:
  return std::regex_match(str, regularExpr);
}

void ContadorPopRural::processaLinha(const std::string &str){
  //
  // Em geral eh mais facil ler dados de uma string se a string eh transformada
  // em um objeto do tipo stringstream:
  std::stringstream ss(str);
  //
  // Iremos ler os dados da string nestas tres variaveis abaixo:
  std::string nomePais;
  unsigned populacao, percUrbana;
  //
  // Como sabemos que a linha contem string int int, podemos fazer a leitura
  // facilmente usando o operador de streaming:
  ss >> nomePais >> populacao >> percUrbana;
  //
  // Note que precisamos arredondar o valor que serah impresso. O arredondamento
  // serah feito via a funcao floor. Ou seja, decimais serao sempre
  // arredondados para baixo:
  unsigned popRural = floor(populacao - (populacao * (percUrbana / 100.0)));
  //
  // Uma vez encontrados os valores que precisam ser impressos, seguimos o
  // modelo do enunciado do exercicio:
  std::cout << popRural << " pessoas vivem no campo no " << nomePais << std::endl;
}

bool ContadorNumNaturais::linhaValida(const std::string &str) const{
  std::regex regularExpr("[\\s\\d]+");
  return std::regex_match(str, regularExpr);
}

void ContadorNumNaturais::processaLinha(const std::string &str){
  std::stringstream ss(str);
  unsigned soma = 0, valor;
  while (ss >> valor){
    soma += valor;
  }
  std::cout << soma << std::endl;
}

bool LeitorDeFutebol::linhaValida(const std::string &str) const{
  std::regex regularExpr("\\s*\\w+\\s+\\d+\\s+\\w+\\s+\\d+\\s*");
  return std::regex_match(str, regularExpr);
}

void LeitorDeFutebol::processaLinha(const std::string &str){
  std::stringstream ss(str);
  std::string time1, time2;
  unsigned gols1, gols2;
  ss >> time1 >> gols1 >> time2 >> gols2;
  if (gols1 == gols2){
    std::cout << "Empate" << std::endl;
  }
  else{
    std::cout << "Vencedor: " << (gols1 > gols2 ? time1 : time2) << std::endl;
  }
}

void ContadorDePalavras::processaLinha(const std::string &str){
  unsigned numPalavras = 0;
  std::stringstream ss(str);
  std::string palavra;
  while (ss >> palavra){
    numPalavras++;
  }
  std::cout << numPalavras << std::endl;
}

bool InversorDeFrases::linhaValida(const std::string &str) const{
  std::regex regularExpr("[a-zA-Z\\s]+");
  return std::regex_match(str, regularExpr);
}

void InversorDeFrases::processaLinha(const std::string &str){
  std::stringstream ss(str);
  std::vector<std::string> palavras;
  std::string palavra;
  while (ss >> palavra){
    palavras.push_back(palavra);
  }
  std::reverse(palavras.begin(), palavras.end());
  for (auto &palavra : palavras){
    std::cout << palavra << " ";
  }
}

bool EscritorDeDatas::linhaValida(const std::string &str) const{
  std::string dateFormat = "\\s*\\d\\d?/\\d\\d?/\\d{4}";
  // Note que você pode usar uma expressao regular como:
  // "\\s*\\d\\d?/\\d\\d?/\\d{4}" para saber se a linha eh valida:
  return std::regex_match(str, std::regex(dateFormat));
}

void EscritorDeDatas::processaLinha(const std::string &str){
  std::stringstream ss(str);
  std::string mes;
  std::getline(ss, mes, '/');
  std::getline(ss, mes, '/');
  // Lembre-se que as iniciais dos meses sao:
  // "Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out",
  // "Nov", e "Dez".
  std::string meses[12] = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez"};
  std::cout << meses[std::stoi(mes) - 1] << std::endl;
}