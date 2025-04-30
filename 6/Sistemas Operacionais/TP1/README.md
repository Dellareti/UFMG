# Trabalho Prático #1 - Shell Básico

Este repositório contém a implementação de um shell básico desenvolvido como parte do Trabalho Prático #1 da disciplina de Sistemas Operacionais (2025/1) da UFMG.

## Integrantes

- Ítalo Dell'Areti - italodellareti@ufmg.br (50%)
- Raquel Gonçalves Rosa - raquelgr@ufmg.br (50%)

## Descrição do Trabalho

O objetivo deste trabalho foi implementar um shell simplificado capaz de executar comandos básicos do sistema operacional. O shell suporta:

1. Comandos simples (ex: `ls`, `cat`)
2. Redirecionamento de entrada e saída (ex: `cat < arquivo.txt`, `echo "texto" > arquivo.txt`)
3. Pipes para sequenciamento de comandos (ex: `ls | grep .c | wc`)

## Soluções Implementadas

### 1. Fork de Processos (fork1)

Implementamos um wrapper para a chamada de sistema `fork()` que verifica o valor de retorno para identificar possíveis falhas na criação do processo filho. Em caso de falha, o programa é encerrado com uma mensagem de erro apropriada.

### 2. Execução de Comandos Simples (handle_simple_cmd)

Utilizamos `execvp()` da família exec para execução de comandos simples. Esta função busca automaticamente o executável no path do sistema e aceita argumentos no formato de um array de strings, compatível com a estrutura de dados `execcmd` disponível no código.

### 3. Redirecionamento de Entrada/Saída (handle_redirection)

Para redirecionamento de I/O, manipulamos diretamente os descritores de arquivo. Fechamos o descritor padrão (0 para stdin ou 1 para stdout) e abrimos o arquivo especificado, permitindo que o sistema operacional atribua o menor descritor disponível ao novo arquivo.

### 4. Implementação de Pipes (handle_pipe)

Para a comunicação entre processos através de pipes, criamos o pipe usando a chamada `pipe()` e dois processos filhos usando `fork1()`. No primeiro processo filho, redirecionamos stdout para a extremidade de escrita do pipe, enquanto no segundo redirecionamos stdin para a extremidade de leitura.

### 5. Correção de Mensagem de Erro

Corrigimos a mensagem de erro para o comando `cd`, substituindo "process does not exist" por "directory does not exist", já que a chamada `chdir()` falha quando o diretório especificado não existe ou não pode ser acessado.

## Testes

O shell foi testado usando o script `grade.sh` fornecido na especificação, que executa uma série de testes para verificar a corretude da implementação:

1. Comando simples (`ls`)
2. Sequência de comandos simples
3. Redirecionamento de saída
4. Redirecionamento de entrada
5. Redirecionamento de entrada/saída
6. Comando com pipe
7. Sequência de comandos com pipe
8. Sequência de comandos com pipe e redirecionamento

## Instruções de Uso

Para compilar e executar o shell:

```bash
# Compilação
gcc sh.c -o myshell.out

# Execução
./myshell.out
```

Ou, alternativamente, use o comando `make` para compilar e testar automaticamente:

```bash
make
```

## Observações Importantes

Se durante a execução do comando "make" ocorrerem erros de permissão como:

1. "make: ./grade.sh: Permission denied" - isso acontece quando o script principal não tem permissão de execução.

2. Erros como "./grade.sh: line XX: tests/testN.sh: Permission denied" seguidos de "FAIL" em todos os testes - isso indica que os scripts de teste individuais também não possuem permissão de execução.

Para resolver esses problemas de permissão, execute os seguintes comandos:

```bash
chmod +x grade.sh              # Dá permissão de execução ao script principal
chmod +x tests/test*.sh        # Dá permissão de execução a todos os scripts de teste
```

## Referências Bibliográficas

- Linux man pages (man 2 fork, man 3 exec, man 2 pipe, man 2 dup)
- Advanced Programming in the UNIX Environment, W. Richard Stevens
