#include <log.h>
#include <tabela_hash.h>

hash_table::hash_table(int tam) {
    this->tam = tam;
    this->tabela = new bst*[tam];
    for (int i = 0; i < tam; i++)
        escrita(this->tabela, i, 0) = new bst;
}

hash_table::~hash_table() { delete[] this->tabela; }

bool hash_table::insere(int chave, mensagem dado) {
    int indice = this->hash(chave);
    return leitura(this->tabela, indice, 0)->insere(dado);
}

bool hash_table::remove(int chave, int id) {
    int indice = this->hash(chave);
    return leitura(this->tabela, indice, 0)->remove(id);
}

mensagem* hash_table::encontra(int chave, int id) {
    int indice = this->hash(chave);
    return leitura(this->tabela, indice, 0)->encontra(id);
}

int hash_table::hash(int chave) { return chave % this->tam; }