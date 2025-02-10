// NÃO ALTERE ESSA LINHA
#include "avaliacao_basica_alocacao.hpp"

#include "QuadroAlocacao.hpp"

int main()
{

    //
    // Adicione seu código aqui e faça as demais alterações necessárias
    //
    QuadroAlocacao quadro;
    std::string codigo, nome, dia, horario, sala;
    std::vector<Disciplina> disciplinas;
    char ch;
    while (cin >> ch){
        switch (ch){
        case 'a':
            cin >> codigo;
            cin >> nome;
            cin >> dia;
            cin >> horario;
            cin >> sala;
            quadro.inserir_alocacao(codigo, nome, dia, horario, sala);
            break;
        case 'm':
            disciplinas = quadro.recuperar_disciplinas_mais_ofertadas();
            for (Disciplina &disciplina : disciplinas)
                disciplina.imprimir_alocacao();   
            break;
        case 'r':
            cin >> codigo;
            cin >> horario;
            quadro.remover_alocacao_disciplina(codigo, horario);
            break;
        case 'p':
            quadro.imprimir_alocacao_completa();
            break;
        case 'b':
            avaliacao_basica();
        }
    }
    return 0;
}