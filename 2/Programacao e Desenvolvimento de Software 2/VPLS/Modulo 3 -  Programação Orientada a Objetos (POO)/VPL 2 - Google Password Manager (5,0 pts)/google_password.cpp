#include "google_password.hpp"

#include <iostream>

void GooglePassword::insert(const std::string &url,
                            const std::string &login,
                            const std::string &password){
  /**
   * Lembre-se que as credenciais so podem ser inseridas com as seguintes
   * condicoes:
   * Condicao 1: A senha nao pode ter a seguencia '123456'.
   * Condicao 2: A senha nao pode ter mais do que 50 caracteres (no maximo 50).
   * Condicao 3: A senha nao pode ter menos do que 6 caracteres (no minimo 6).
   * Condicao 4: A senha nao pode ter caracteres em branco ' '.
   *
   * Exemplos de senhas invalidas:
   * 123456
   * test_123456
   * 123456_test
   * test_123456_test
   * senha test
   */
  if (checkPassword(password) && m_passwords.find(url) == m_passwords.end()){
    m_passwords[url] = Usuario(login, password);
  }
}

void GooglePassword::remove(const std::string &url){
  m_passwords.erase(url);
}

void GooglePassword::update(const std::string &url,
                            const std::string &login,
                            const std::string &old_password,
                            const std::string &new_password){
  // TODO: Implemente este metodo
  /**
   * Caso a url nao seja encontrada, o metodo update deve ser ignorado, ou seja,
   * este metodo nao pode inserir novas credenciais. Alem disso, as informacoes
   * do usuario so podem ser atualizadas se a senha antiga for igual a senha
   * atual. Nao esqueca de verificar se o novo password tambem e valido.
   */
  if (m_passwords.find(url) != m_passwords.end()){
    if (m_passwords[url].getPassword() == old_password){
      if (checkPassword(new_password)){
        m_passwords[url].setLogin(login);
        m_passwords[url].setPassword(new_password);
      }
    }
  }
}

void GooglePassword::printPasswords()
{
  /**
   * Exemplo de saida:
   * www.site.com: login and password
   *
   */
  std::cout << m_passwords.size() << std::endl;
  for (auto &pass : m_passwords){
    std::cout << pass.first << ": " << pass.second.getLogin() << " and "
              << pass.second.getPassword() << std::endl;
  }
}

bool GooglePassword::checkPassword(const std::string &password) const{
  return password.find("123456") == std::string::npos &&
         password.size() <= 50 &&
         password.size() >= 6 &&
         password.find(" ") == std::string::npos;
}