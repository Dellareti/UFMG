VPL 06 - Alocação Salas (5,0 pts)
 Disponível a partir de: quinta, 14 Out 2021, 00:00
 Data de entrega: terça, 23 Nov 2021, 23:59
 Arquivos requeridos: main.cpp, Alocacao.hpp, Alocacao.cpp, Disciplina.hpp, Disciplina.cpp, QuadroAlocacao.hpp, QuadroAlocacao.cpp ( Baixar)
Tipo de trabalho:  Trabalho individual
O objetivo desse exercício é praticar o uso de diferentes estruturas da STL.

Para ajudar os alunos a encontrarem onde ocorrerão suas aulas, você deverá desenvolver um programa que será responsável por manipular um quadro de alocação de salas. Esse quadro demandará a implementação de três TADs: Alocacao, Disciplina e QuadroAlocacao. Cada TAD deve seguir as especificações abaixo:

Alocacao:
Atributos: dia, horario, sala (todos do tipo string).

Alocacao(string dia, string horario, string sala): Método construtor para a inicialização dos atributos.

void imprimir_dados(): faz a impressão dos atributos no seguinte formato: "dia horario sala", com uma quebra de linha ao final.

Disciplina:
Atributos: codigo e nome (ambos do tipo string), e alocacao (que guarda uma coleção de elementos do tipo Alocacao, você deve escolher a estrutura que julgar mais adequada para usar).

Disciplina(string codigo, string nome): método construtor para a inicialização dos atributos.

void inserir_alocacao(string dia, string horario, string sala): cria uma nova alocação para a disciplina a partir dos dados informados e insere na coleção.

void remover_alocacao(string horario): remove uma alocação da coleção. Para facilitar, vamos assumir que existe apenas uma única alocação em cada horário.

void imprimir_alocacao(): imprime todas as alocações para a disciplina. Cada alocação deve ser impressa em uma linha separada e seguindo o formato "codigo nome dia horario sala". Além disso, a alocação deve ser impressa ordenada de acordo com o horário.

QuadroAlocacao:
Atributos: crie um atributo para guardar as alocações de todas as disciplinas. Você deve escolher a estrutura que julgar mais adequada para usar (dica: um map é bem útil!).

void inserir_alocacao(string codigo, string nome, string dia, string horario, string sala): cria uma nova alocação para uma determinada disciplina de acordo com os parâmetros informados. Todas as disciplinas possuem códigos diferentes, ou seja, únicos.

remover_alocacao_disciplina(string codigo, string horario): remove a alocação em um determinado horário para a disciplina com o código informado. Lembrando que os horários de alocação são únicos em cada disciplina.

vector<Disciplina> recuperar_disciplinas_mais_ofertadas(): recupera todas as disciplinas que possuem o maior número de alocações.

imprimir_alocacao_completa(): imprime todo o quadro de alocação. As disciplinas devem estar ordenadas pelo código, e as alocações pelo horário da oferta.

Você é livre para adicionar nos TADs quaisquer outros atributos ou métodos auxiliares que julgar necessário.

Por fim, no arquivo main.cpp você deve implementar toda a parte de entrada/saída que será responsável por manipular os seguintes comandos:
'a codigo nome dia horario sala': comando para adicionar uma nova alocacao no quadro de acordo com os parâmetros passados. Você pode assumir que as informações *não* possuem espaço, ou seja, são palavras únicas.

'm': comando para recuperar as disciplinas mais ofertas. Sempre que esse comando for chamado além de recuperar as disciplinas, a alocação de cada uma também deve ser impressa.

'r codigo horario': remove uma alocação do quadro de acordo com o código da disciplina e horário informados.

'p': comando para imprimir a alocação completa.

'b': deve chamar a função 'avaliacao_basica()' implementada no arquivo "avaliacao_basica_alocacao.hpp" (já incluído no main.cpp). Essa função faz uma avaliação do código (não apenas dos resultados).

Para ilustrar, abaixo é apresentado um exemplo de entrada/saída:

input=
a MAT333 CAL1 Seg-Qua 19:00-20:40 2003
a MAT111 GAAL Ter-Qui 07:30-09:10 3015
a MAT111 GAAL Ter-Qui 14:55-16:35 3015
a DCC123 PDS2  Ter-Qui 14:55-16:35 3040
p
m

output =
DCC123 PDS2 Ter-Qui 14:55-16:35 3040
MAT111 GAAL Ter-Qui 07:30-09:10 3015
MAT111 GAAL Ter-Qui 14:55-16:35 3015
MAT333 CAL1 Seg-Qua 19:00-20:40 2003
MAT111 GAAL Ter-Qui 07:30-09:10 3015
MAT111 GAAL Ter-Qui 14:55-16:35 3015

Nesse exemplo, as quatro primeiras linhas da saída representam a chamada de 'imprimir_alocacao_completa()' (comando 'p') e as duas últimas linhas a disciplina mais ofertada e suas alocações (comando 'm').


Atenção: Lembre-se de fazer a correta modularização utilizando os arquivos .hpp e .cpp.

Dica 1:
O código da avaliação básica pode ser copiado aqui, caso você queira depurar algo localmente.

Dica 2:
Você pode usar os códigos dos exercícios anteriores e o da avaliação básica para lhe ajudar a fazer toda a parte de entrada/saída.

Referências:
https://www.cplusplus.com/doc/tutorial/structures/
https://www.cplusplus.com/reference/stl/
