#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Answers can be either in Portuguese or in English.
Respostas podem sem tanto em português como em inglês.
*/

/*
1. Term of commitment

The group members declare that all code developed for this project is their own.
The group members declare that they have not copied material from the Internet
  nor obtained code from third parties.

2. Group members and allocation of effort

Fill in the lines below with the name and email of the group members.
Replace XX with the contribution of each group member in the development of the work.

Ítalo Dell’Areti <italodellareti@ufmg.br> 50%
Raquel Gonçalves Rosa <raquelgr@ufmg.br> 50%

3. Solutions

Briefly describe the solutions implemented for this project and justify their choices.

Para implementar, foram utilizadas diversas chamadas de sistema do Linux:

1. Para a função fork1(), implementamos um wrapper para a chamada de sistema fork()
   que cria um novo processo. A implementação verifica o valor de retorno da chamada fork()
   para identificar possíveis falhas na criação do processo filho. Essa abordagem é
   importante porque caso o fork falhe (por exemplo, devido à falta de recursos do sistema),
   podemos encerrar o programa com uma mensagem de erro apropriada ao invés de continuar a 
   execução de forma inconsistente.


2. Na implementação de comandos simples (handle_simple_cmd()), utilizamos execvp() da família
   exec, que possui duas vantagens principais: (1) busca automaticamente o executável no 
   path do sistema, tornando desnecessário especificar o caminho completo do binário; e 
   (2) aceita argumentos no formato de um array de strings, compatível com a estrutura de 
   dados execcmd já disponível no código. Esta escolha simplifica a implementação e mantém a
   compatibilidade com a maioria dos comandos de shell padrão.


3. Para o redirecionamento de entrada/saída (handle_redirection()), adotamos uma técnica baseada 
   na manipulação direta de descritores de arquivo. Primeiro, fechamos o descritor padrão
   (0 para stdin ou 1 para stdout) e em seguida abrimos o arquivo especificado. O sistema operacional,
   por design, atribui o menor descritor disponível ao novo arquivo aberto, que será exatamente o
   que acabamos de fechar. Isso efetivamente substitui a entrada/saída padrão pelo arquivo 
   especificado sem necessidade de chamadas adicionais como dup2().


4. A implementação de pipes (handle_pipe()) seguiu o modelo de comunicação entre processos:
   criamos o pipe usando a chamada pipe(), depois dois processos filhos usando fork1() 
   - um para executar o comando à esquerda e outro para o comando à direita do pipe. No primeiro 
   processo filho, redirecionamos stdout para a extremidade de escrita do pipe, enquanto no segundo 
   redirecionamos stdin para a extremidade de leitura. É essencial fechar os descritores não utilizados
   em cada processo para evitar bloqueios e vazamentos de recursos. O processo pai espera pela 
   conclusão de ambos os processos filhos para garantir que todas as operações se completem 
   corretamente.


5. Na correção da mensagem de erro para o comando cd, identificamos que o problema estava relacionado
   à semântica da mensagem. Como a função chdir() falha quando o diretório especificado não existe 
   ou não pode ser acessado (e não porque um processo não existe), modificamos a mensagem para
  "directory does not exist", que reflete com mais precisão a natureza do erro.


** Observações importantes sobre execução: 

Se durante a execução do comando "make" ocorrerem erros de permissão como:

1. "make: ./grade.sh: Permission denied" - isso acontece quando o script principal não tem permissão de execução.

2. Erros como "./grade.sh: line XX: tests/testN.sh: Permission denied" seguidos de "FAIL" em todos os testes - isso
   indica que os scripts de teste individuais também não possuem permissão de execução.

   Para resolver esses problemas de permissão, execute os seguintes comandos:

   chmod +x grade.sh              # Dá permissão de execução ao script principal
   chmod +x tests/test*.sh        # Dá permissão de execução a todos os scripts de teste

   Esses comandos são essenciais para que o ambiente de testes funcione corretamente. 


4. Bibliographic references

- Linux man pages (man 2 fork, man 3 exec, man 2 pipe, man 2 dup)
- Advanced Programming in the UNIX Environment, W. Richard Stevens
*/

/****************************************************************
 * Simplified xv6 Shell
 *
 * This code was adapted from the UNIX xv6 code and material from
 * the MIT Operating Systems course (6.828).
 ***************************************************************/

#define MAXARGS 10

/* Every command has a type. After identifying the command's type,
    the code converts a *cmd into the specific command type. */
struct cmd {
    int type; /* ' ' (exec)
                 '|' (pipe)
                 '<' or '>' (redirection) */
};

struct execcmd {
    int type;             // ' ' (exec)
    char *argv[MAXARGS];  // Arguments for the command to be executed
};

struct redircmd {
    int type;         // < or > (redirection)
    struct cmd *cmd;  // The command to execute (e.g., an execcmd)
    char *file;       // The input or output file
    int mode;         // The mode in which the file should be opened
    int fd;           // The file descriptor number to be used
};

struct pipecmd {
    int type;           // | (pipe)
    struct cmd *left;   // Left side of the pipe
    struct cmd *right;  // Right side of the pipe
};

int fork1(void);                                        // Fork but exit if an error occurs
struct cmd *parsecmd(char *);                           // Process the command line
void handle_simple_cmd(struct execcmd *ecmd);           // Handle simple commands
void handle_redirection(struct redircmd *rcmd);         // Handle redirection
void handle_pipe(struct pipecmd *pcmd, int *p, int r);  // Handle pipes

/* Execute the command cmd. It never returns. */
void runcmd(struct cmd *cmd) {
    int p[2], r;
    struct execcmd *ecmd;
    struct pipecmd *pcmd;
    struct redircmd *rcmd;

    if (cmd == 0)
        exit(0);

    switch (cmd->type) {
        default:
            fprintf(stderr, "Unknown command type\n");
            exit(-1);

        case ' ':
            ecmd = (struct execcmd *)cmd;
            if (ecmd->argv[0] == 0)
                exit(0);
            handle_simple_cmd(ecmd);
            break;

        case '>':
        case '<':
            rcmd = (struct redircmd *)cmd;
            handle_redirection(rcmd);
            runcmd(rcmd->cmd);
            break;

        case '|':
            pcmd = (struct pipecmd *)cmd;
            handle_pipe(pcmd, p, r);
            break;
    }
    exit(0);
}

int fork1(void) {
    /* Task 1: Implement the fork1 function.
    The function is supposed to create a new process using the `fork()` system call.
    It should print a message if the fork fails, otherwise return the process ID of the child process (or -1 if the fork fails).
    */
    int pid = fork();
    if (pid == -1) {
        fprintf(stderr, "fork failed\n");
        exit(-1);
    }
    return pid;
    /* END OF TASK 1 */
}

void handle_simple_cmd(struct execcmd *ecmd) {
    /* Task 2: Implement the code below to execute simple commands. */
    execvp(ecmd->argv[0], ecmd->argv);
    fprintf(stderr, "exec %s failed\n", ecmd->argv[0]);
    exit(-1);
    /* END OF TASK 2 */
}

void handle_redirection(struct redircmd *rcmd) {
    /* Task 3: Implement the code below to handle input/output redirection. */
    close(rcmd->fd);

    /* O valor 0666 especifica as permissões para um novo arquivo criado:
     * - Leitura/escrita (6) para o proprietário
     * - Leitura/escrita (6) para o grupo
     * - Leitura/escrita (6) para outros usuários
     * Estas permissões facilitam testes e serão reduzidas pela máscara de modo (umask) do sistema.
     * Este parâmetro só tem efeito para redirecionamento de saída (>) quando o arquivo não existe e precisa ser criado.
     */
    if (open(rcmd->file, rcmd->mode, 0666) < 0) {
        fprintf(stderr, "open %s failed\n", rcmd->file);
        exit(-1);
    }
    /* END OF TASK 3 */
}

void handle_pipe(struct pipecmd *pcmd, int *p, int r) {
    /* Task 4: Implement the code below to handle pipes. */
    if (pipe(p) < 0) {
        fprintf(stderr, "pipe creation failed\n");
        exit(-1);
    }

    // Processo filho para o lado esquerdo do pipe
    if (fork1() == 0) {
        close(1);        // Fecha stdout
        dup(p[1]);       // Duplica a extremidade de escrita do pipe para stdout
        close(p[0]);     // Fecha a extremidade de leitura
        close(p[1]);     // Fecha o descritor original de escrita
        runcmd(pcmd->left);
    }

    // Processo filho para o lado direito do pipe
    if (fork1() == 0) {
        close(0);        // Fecha stdin
        dup(p[0]);       // Duplica a extremidade de leitura do pipe para stdin
        close(p[0]);     // Fecha o descritor original de leitura
        close(p[1]);     // Fecha a extremidade de escrita
        runcmd(pcmd->right);
    }

    // Processo pai fecha ambas as extremidades do pipe
    close(p[0]);
    close(p[1]);
    
    // Espera pelos processos filhos terminarem
    wait(NULL);
    wait(NULL);
    /* END OF TASK 4 */
}

int getcmd(char *buf, int nbuf) {
    if (isatty(fileno(stdin)))
        fprintf(stdout, "$ ");
    memset(buf, 0, nbuf);
    fgets(buf, nbuf, stdin);
    if (buf[0] == 0)  // EOF
        return -1;
    return 0;
}

int main(void) {
    static char buf[100];
    int r;

    // Read and execute commands.
    while (getcmd(buf, sizeof(buf)) >= 0) {
        /* Task 5: Explain the purpose of the if statement below and correct the error message.
        Why is the current error message incorrect? Justify the new message. */
        /* Answer:
           O propósito deste if é tratar especialmente o comando 'cd', já que mudar de diretório
           deve afetar o processo do shell atual, não um processo filho. A mensagem de erro
           "process does not exist" está incorreta porque a chamada chdir() falha quando o
           diretório especificado não existe ou não pode ser acessado, não quando um processo
           não existe. Uma mensagem mais adequada seria "directory does not exist".
         */
        if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ') {
            buf[strlen(buf) - 1] = 0;
            if (chdir(buf + 3) < 0)
                fprintf(stderr, "directory does not exist\n");
            continue;
        }
        /* END OF TASK 5 */

        if (fork1() == 0)
            runcmd(parsecmd(buf));
        wait(&r);
    }
    exit(0);
}

/****************************************************************
 * Helper functions for creating command structures
 ***************************************************************/

struct cmd *
execcmd(void) {
    struct execcmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = ' ';
    return (struct cmd *)cmd;
}

struct cmd *
redircmd(struct cmd *subcmd, char *file, int type) {
    struct redircmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = type;
    cmd->cmd = subcmd;
    cmd->file = file;
    cmd->mode = (type == '<') ? O_RDONLY : O_WRONLY | O_CREAT | O_TRUNC;
    cmd->fd = (type == '<') ? 0 : 1;
    return (struct cmd *)cmd;
}

struct cmd *
pipecmd(struct cmd *left, struct cmd *right) {
    struct pipecmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = '|';
    cmd->left = left;
    cmd->right = right;
    return (struct cmd *)cmd;
}

/****************************************************************
 * Command Line Processing
 ***************************************************************/

char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>";

int gettoken(char **ps, char *es, char **q, char **eq) {
    char *s;
    int ret;

    s = *ps;
    while (s < es && strchr(whitespace, *s))
        s++;
    if (q)
        *q = s;
    ret = *s;
    switch (*s) {
        case 0:
            break;
        case '|':
        case '<':
            s++;
            break;
        case '>':
            s++;
            break;
        default:
            ret = 'a';
            while (s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
                s++;
            break;
    }
    if (eq)
        *eq = s;

    while (s < es && strchr(whitespace, *s))
        s++;
    *ps = s;
    return ret;
}

int peek(char **ps, char *es, char *toks) {
    char *s = *ps;
    while (s < es && strchr(whitespace, *s)) s++;
    *ps = s;
    return *s && strchr(toks, *s);
}

struct cmd *parseline(char **, char *);
struct cmd *parsepipe(char **, char *);
struct cmd *parseexec(char **, char *);

/* Copy characters from the input buffer, starting from s to es.
 * Place a null terminator at the end to create a valid string. */
char *mkcopy(char *s, char *es) {
    int n = es - s;
    char *c = malloc(n + 1);
    assert(c);
    strncpy(c, s, n);
    c[n] = 0;
    return c;
}

struct cmd *
parsecmd(char *s) {
    char *es;
    struct cmd *cmd;

    es = s + strlen(s);
    cmd = parseline(&s, es);
    peek(&s, es, "");
    if (s != es) {
        fprintf(stderr, "leftovers: %s\n", s);
        exit(-1);
    }
    return cmd;
}

struct cmd *
parseline(char **ps, char *es) {
    struct cmd *cmd;
    cmd = parsepipe(ps, es);
    return cmd;
}

struct cmd *
parsepipe(char **ps, char *es) {
    struct cmd *cmd;

    cmd = parseexec(ps, es);
    if (peek(ps, es, "|")) {
        gettoken(ps, es, 0, 0);
        cmd = pipecmd(cmd, parsepipe(ps, es));
    }
    return cmd;
}

struct cmd *
parseredirs(struct cmd *cmd, char **ps, char *es) {
    int tok;
    char *q, *eq;

    while (peek(ps, es, "<>")) {
        tok = gettoken(ps, es, 0, 0);
        if (gettoken(ps, es, &q, &eq) != 'a') {
            fprintf(stderr, "missing file for redirection\n");
            exit(-1);
        }
        switch (tok) {
            case '<':
                cmd = redircmd(cmd, mkcopy(q, eq), '<');
                break;
            case '>':
                cmd = redircmd(cmd, mkcopy(q, eq), '>');
                break;
        }
    }
    return cmd;
}

struct cmd *
parseexec(char **ps, char *es) {
    char *q, *eq;
    int tok, argc;
    struct execcmd *cmd;
    struct cmd *ret;

    ret = execcmd();
    cmd = (struct execcmd *)ret;

    argc = 0;
    ret = parseredirs(ret, ps, es);
    while (!peek(ps, es, "|")) {
        if ((tok = gettoken(ps, es, &q, &eq)) == 0)
            break;
        if (tok != 'a') {
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
        cmd->argv[argc] = mkcopy(q, eq);
        argc++;
        if (argc >= MAXARGS) {
            fprintf(stderr, "too many args\n");
            exit(-1);
        }
        ret = parseredirs(ret, ps, es);
    }
    cmd->argv[argc] = 0;
    return ret;
}