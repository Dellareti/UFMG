VPL05 - Escalonador (4,0 pts)
 Disponível a partir de: quinta, 14 Out 2021, 00:00
 Data de entrega: terça, 23 Nov 2021, 23:59
 Arquivos requeridos: main.cpp, Processo.hpp, Processo.cpp, ListaProcessos.hpp, ListaProcessos.cpp ( Baixar)
Tipo de trabalho:  Trabalho individual
Neste exercício estaremos simulando um escalonador de processos, ou seja, o subsistema de um SO que escolhe qual processo será executado pela CPU. Para isso, deve-se implementar uma Fila de Prioridades básica usando uma Lista Encadeada.

Você deverá implementar dois TADs: Processo e ListaProcessos. Cada TAD deve seguir as especificações abaixo:

Processo: 

Atributos: int _id, _prioridade; std::string _nome;

Processo(int id, std::string nome, int prioridade): Método construtor para a inicialização dos atributos.

void imprimir_dados(): Método que faz a impressão dos atributos no seguinte formato: "id nome prioridade", com uma quebra de linha ao final.


ListaProcessos:
void adicionar_processo(Processo* proc): Método que recebe um Processo (ponteiro) e o adiciona na lista de maneira ORDENADA considerando a prioridade informada. A ordenação da prioridade deve ser DECRESCENTE, ou seja, do maior para o menor. Logo, um processo de prioridade 5 deve aparecer antes na lista que um processo com prioridade 1. Em caso de prioridades iguais, a ordem de inserção deve ser respeitada.

Processo* remover_processo_maior_prioridade(): remove da lista o processos de maior prioridade, para facilitar, o primeiro da lista. Você deve retornar um ponteiro para o processo removido da lista (não é necessário desalocar a memória). 

Processo* remover_processo_menor_prioridade(): remove da lista o processo de menor prioridade, para facilitar, o último elemento da lista (não precisa respeitar a ordem de inserção). Você deve retornar um ponteiro para o processo removido da lista (não é necessário desalocar a memória). 

Processo* remover_processo_por_id(int id): remove da lista um processo de acordo com o id. Você deve retornar um ponteiro para o processo removido da lista (não é necessário desalocar a memória). Caso não exista na lista um processo com o id informado deve-se retornar nullptr.

void imprimir_lista(): imprime a situação atual da lista, ou seja, percorre toda a lista (do início para o final) e chama o método 'imprimir_dados()' de cada processo.

Você é livre para adicionar nos TADs quaisquer outros atributos ou métodos auxiliares que julgar necessário. Além disso, você também pode escolher entre utilizar uma Lista Simplesmente ou Duplamente Encadeada. 

Por fim, no arquivo main.cpp você deve implementar toda a parte de entrada/saída que será responsável por manipular os seguintes comandos:

'a id nome prioridade': comando para adicionar um novo processo na lista de acordo com os parâmetros passados. Você pode assumir que o nome sempre será uma única palavra.

'm': comando para remover o processo de MAIOR prioridade da lista.

'n': comando para remover o processo de MENOR prioridade da lista.

'r id': comando para remover um processo da lista de acordo com o ID informado.

'p': comando para imprimir a lista.

'b': deve chamar a função 'avaliacao_basica()' implementada no arquivo "avaliacao_basica_escalonador.hpp" (já incluído no main.cpp). Essa função faz uma avaliação do código (não apenas dos resultados).

Para ilustrar, abaixo é apresentado um exemplo de entrada/saída:

input=
a 1 Proc1 1
a 2 Proc2 1
a 3 Proc3 3
p

output =
3 Proc3 3
1 Proc1 1
2 Proc2 1

Atenção: Lembre-se de fazer a correta modularização utilizando os arquivos .hpp e .cpp.

Dica 1:
O código da avaliação básica pode ser copiado aqui, caso você queira depurar algo localmente.

Dica 2:
Você pode usar o código fornecido no exercício anterior e o da avaliação básica para lhe ajudar a fazer toda a parte de entrada/saída.

Referências:
https://www.cplusplus.com/doc/tutorial/pointers/
https://www.cplusplus.com/doc/tutorial/dynamic/
https://www.cplusplus.com/doc/tutorial/structures/
https://www.cplusplus.com/articles/LACRko23/
