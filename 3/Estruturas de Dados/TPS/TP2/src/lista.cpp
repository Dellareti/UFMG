#include <lista.h>
#include <log.h>

Lista::Lista(/* args */) : primeiro(nullptr), ultimo(nullptr), tamanho(0) {}

Lista::Lista(const std::string& linha) : primeiro(nullptr), ultimo(nullptr), tamanho(0) {}

Lista::~Lista() {
    no* atual = primeiro;
    while (atual != nullptr) {
        no* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}

void Lista::insere(const std::string& palavra) {
    no* novo = new no;
    novo->palavra = new palavra_t(palavra);
    novo->proximo = nullptr;
    if (primeiro == nullptr) {
        primeiro = novo;
        ultimo = novo;
    } else {
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void Lista::atualiza(const std::string& palavra) {
    palavra_t chave(palavra);
    if (!encontra(chave)) {
        insere(palavra);
    }
}

bool Lista::encontra(const palavra_t& palavra) {
    no* atual = primeiro;
    while (atual != nullptr) {
        if (atual->palavra->palavra == palavra.palavra) {
            atual->palavra->ocorrencias++;
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

palavra_t* Lista::to_array() {
    palavra_t* array = new palavra_t[tamanho];
    no* atual = primeiro;
    int i = 0;
    while (atual != nullptr) {
        escrita(array, i, 1) = *atual->palavra;
        i++;
        atual = atual->proximo;
    }
    return array;
}

int Lista::get_tamanho() { return tamanho; }