// NÃO ALTERE ESSA LINHA
#include "avaliacao_basica_escalonador.hpp"

#include <iostream>
#include "ListaProcessos.hpp"

int main(){
    ListaProcessos lista_processos;
    int id, prioridade;
    char ch;
    std::string nome;
    while (cin >> ch){
        switch (ch){
        case 'a':
            cin >> id;
            cin >> nome;
            cin >> prioridade;
            lista_processos.adicionar_processo(new Processo(id, nome, prioridade));
            break;
        case 'm':
            lista_processos.remover_processo_maior_prioridade();
            break;
        case 'n':
            lista_processos.remover_processo_menor_prioridade();
            break;
        case 'r':
            cin >> id;
            lista_processos.remover_processo_por_id(id);
            break;
        case 'p':
            lista_processos.imprimir_lista();
            break;
        case 'b':
            avaliacao_basica();
        }
    }
    return 0;
}