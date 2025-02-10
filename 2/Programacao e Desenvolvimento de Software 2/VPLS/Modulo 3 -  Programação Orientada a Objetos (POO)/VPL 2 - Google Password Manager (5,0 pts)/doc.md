VPL 2 - Google Password Manager (5,0 pts)
 Data de entrega: sábado, 18 Dez 2021, 23:59
 Arquivos requeridos: google_password.hpp, google_password.cpp, usuario.cpp, usuario.hpp ( Baixar)
Tipo de trabalho:  Trabalho individual
Descrição

O Google Passwords Manager é um gerenciador de senhas do Chrome. O serviço armazena as credenciais coletadas (com o consentimento do usuário) todas as vezes em que o usuário realizada um login ou cria um cadastro em algum site.

Neste problema, você terá que simular o gerenciamento de logins e senhas.

Para fazer essa simulação, você terá que implementar duas classes: GooglePassword e Usuario. OBS: O arquivo google_password.hpp não deve ser modificado. Já o arquivo usuario.hpp deve ser modificado apenas para declaração das variáveis necessárias.

A classe Usuario deverá armazenar as seguintes informações:

Usuario
---------------------------------
- login: string
- password: string

OBS: Essas informações, como são sigilosas, devem ser de acesso restrito da classe Usuario. Logo, só podem ser manipuladas por outras classes, através de métodos.

A classe GooglePassword deverá manter a lista de senha salvas, associado ao site que foi utilizado. Além disso, ela deverá possuir os seguintes métodos:

GooglePassword
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- passwords: std::map<string, Usuario>
+ insert(string url, string login, string password): void
+ update(string url, string login, string old_password, string new_password): void
+ remove(string url): void
+ printPasswords(): void
- checkPassword(string password): bool

Breve descrição:
insert(string url, string login, string password); // insere uma nova senha associado a um determinado site
update(string url, string login, string old_password, string new_password); //atualiza as credenciais utilizadas em um site
remove(string url); //remove as informações associadas a um site
printPasswords(); //imprime as informações salvas em ordem alfabética, utilizando os sites como critério de ordem
checkPassword(string password); // verifica se o password passa em todas as restricoes
OBS: O gerenciador não deverá aceitar senhas que contenham a sequência "123456", caracteres em branco, possuam menos do que 6 ou mais do que 50 caracteres.

Help

https://www.cplusplus.com/doc/tutorial/classes/
https://www.cplusplus.com/reference/map/map/
https://www.cplusplus.com/reference/string/string/

Formato de entrada

Cada método da classe GooglePassword é associado a um comando. Esses comandos são executados de forma aleatória. Os parâmetros de entrada de cada comando seguem a mesma ordem de declação dos métodos e são separados por vírgula. Por exemplo, para o comando insert a ordem os parâmetros são: url, login e password.

Formato de saída

O método printPasswords() da classe GooglePassword é executado após o processamento de todos os comandos. Deverão ser exibidos a quantidade de credenciais armazenadas e os detalhes das informações de cada site.

Exemplo de entrada

insert
sistemas.ufmg.br,aluno,esta_senha_e_forte
insert
www.linkedin.com,usuario_trabalhador,ninguem_conhece_essa_senha_porque_ela_e_muito_forte
insert
www.facebook.com,usuario_divertido,123456
insert
www.youtube.com,criador_de_conteudo,ninguem_descobre_esta_senha

Exemplo de Saída

2
sistemas.ufmg.br: aluno and esta_senha_e_forte
www.youtube.com: criador_de_conteudo and ninguem_descobre_esta_senha

Depurando localmente
Caso você queira testar seu VPL localmente, você pode baixar os arquivos necessários aqui, e usá-los com diferentes arquivos de entrada, assim:

g++ *.cpp -o main
./main < input.txt
