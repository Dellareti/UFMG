#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#               : 2021-11-15 - Versao 1.1 memlog
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera arquivos de registro de acesso
#               : make perf - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#		: make clean - remove objetos e executável
#------------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)

EXE = $(BIN)/matop

all: mem 
#perf 
#gprof

mem:$(EXE)
	$(EXE) -s -p somalog.out -1 m1.txt -2 m2.txt -o res-soma.txt
	$(EXE) -m -p multlog.out -1 m1.txt -2 m2.txt -o res-mult.txt
	$(EXE) -t -p transplog.out -1 m1.txt -o res-transp.txt

	
#perf: $(EXE)
#	$(EXE) -s -p /tmp/soma100.out -1 1m100.txt -2 2m100.txt
#	$(EXE) -m -p /tmp/mult100.out -1 1m100.txt -2 2m100.txt
#	$(EXE) -t -p /tmp/transp100.out -1 1m100.txt
#------------100
#	$(EXE) -s -p /tmp/soma100.out -1 1m100.txt -2 2m100.txt
#	$(EXE) -m -p /tmp/mult100.out -1 1m100.txt -2 2m100.txt
#	$(EXE) -t -p /tmp/transp100.out -1 1m100.txt
#------------200
#	$(EXE) -s -p /tmp/soma200.out -1 1m200.txt -2 2m200.txt
#	$(EXE) -m -p /tmp/mult200.out -1 1m200.txt -2 2m200.txt
#	$(EXE) -t -p /tmp/transp200.out -1 1m200.txt
#------------300
#	$(EXE) -s -p /tmp/soma300.out -1 1m300.txt -2 2m300.txt
#	$(EXE) -m -p /tmp/mult300.out -1 1m300.txt -2 2m300.txt
#	$(EXE) -t -p /tmp/transp300.out -1 1m300.txt


# gprof: $(BIN)/matop
# 	$(EXE) -s -1 m1.txt -2 m2.txt -p somalog.out
# 	gprof $(EXE) gmon.out > res-soma.txt

# 	$(EXE) -m -1 m1.txt -2 m2.txt -p multlog.out
# 	gprof $(EXE) gmon.out > res-mult.txt

# 	$(EXE) -t -1 m1.txt -p transplog.out
# 	gprof $(EXE) gmon.out > res-transp.txt

$(BIN)/matop: $(OBJS)
	$(CC) -pg -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c 

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm $(EXE) $(OBJS) gmon.out 
