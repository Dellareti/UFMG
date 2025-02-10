#include <arvore_busca.h>
#include <log.h>
#include <memlog.h>

bst::bst() { this->raiz = nullptr; }

bst::~bst() {
    defineFaseMemLog(2);
    while (leitura(this->raiz, 1) != nullptr) {
        this->remove(this->raiz->dado.id);
    }
}

bool bst::insere(mensagem dado) {
    defineFaseMemLog(0);
    if (leitura(this->raiz, 1) == nullptr) {
        escrita(this->raiz, 1) = new no_bst{dado, nullptr, nullptr};
        defineFaseMemLog(1);
        return true;
    } else {
        no_bst* atual = this->raiz;
        while (true) {
            if (dado.id < atual->dado.id) {
                if (leitura(atual->esq, 1) == nullptr) {
                    escrita(atual->esq, 1) = new no_bst{dado, nullptr, nullptr};
                    defineFaseMemLog(1);
                    return true;
                } else
                    atual = atual->esq;
            } else if (dado.id > atual->dado.id) {
                if (leitura(atual->dir, 1) == nullptr) {
                    escrita(atual->dir, 1) = new no_bst{dado, nullptr, nullptr};
                    defineFaseMemLog(1);
                    return true;
                } else
                    atual = atual->dir;
            } else {
                defineFaseMemLog(1);
                return false;
            }
        }
    }
}

bool bst::remove(int id) {
    if (this->raiz == nullptr)
        return false;
    else {
        no_bst* atual = this->raiz;
        no_bst* pai = nullptr;
        while (atual != nullptr) {
            if (id < leitura(atual, 1)->dado.id) {
                pai = atual;
                atual = atual->esq;
            } else if (id > leitura(atual, 1)->dado.id) {
                pai = atual;
                atual = atual->dir;
            } else {
                if (leitura(atual, 1)->esq == nullptr && leitura(atual, 1)->dir == nullptr) {
                    if (pai == nullptr)
                        escrita(this->raiz, 1) = nullptr;
                    else if (pai->esq == atual)
                        escrita(pai->esq, 1) = nullptr;
                    else
                        escrita(pai->dir, 1) = nullptr;
                    delete atual;
                    return true;
                } else if (leitura(atual->esq, 1) == nullptr) {
                    if (pai == nullptr)
                        escrita(this->raiz, 1) = atual->dir;
                    else if (pai->esq == atual)
                        escrita(pai->esq, 1) = atual->dir;
                    else
                        escrita(pai->dir, 1) = atual->dir;
                    delete atual;
                    return true;
                } else if (leitura(atual->dir, 1) == nullptr) {
                    if (pai == nullptr)
                        escrita(this->raiz, 1) = atual->esq;
                    else if (pai->esq == atual)
                        escrita(pai->esq, 1) = atual->esq;
                    else
                        escrita(pai->dir, 1) = atual->esq;
                    delete atual;
                    return true;
                } else {
                    no_bst* sucessor = this->min(atual->dir);
                    if (pai == nullptr)
                        escrita(this->raiz, 1) = sucessor;
                    else if (pai->esq == atual)
                        escrita(pai->esq, 1) = sucessor;
                    else
                        escrita(pai->dir, 1) = sucessor;
                    escrita(sucessor->esq, 1) = atual->esq;
                    escrita(sucessor->dir, 1) = atual->dir;
                    delete atual;
                    return true;
                }
            }
        }
        return false;
    }
}

no_bst* bst::min(no_bst* no) {
    if (leitura(no->esq, 1) == nullptr)
        return no;
    else
        return min(no->esq);
}

mensagem* bst::encontra(int id) {
    if (leitura(this->raiz, 1) == nullptr)
        return nullptr;
    else {
        no_bst* atual = this->raiz;
        while (leitura(atual, 1)->dado.id != id) {
            if (id < leitura(atual, 1)->dado.id)
                atual = atual->esq;
            else
                atual = atual->dir;
            if (leitura(atual, 1) == nullptr)
                return nullptr;
        }
        return &atual->dado;
    }
}