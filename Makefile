#A Simple Example Makefile for soshell
#
# Syntax:
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
# Variaveis: compiler, compiler flags, libraries to link, names of the object files for the executable.
#
CC=gcc
FLAGS=-c -Wall
LIBS=-lm
OBS=main.o execute.o parse.o socp.o calc.o jpeg.o redirect.o pipe.o

#Alvo por defeito é o primeiro
all :  soshell

main.o : shell.h main.c
	$(CC) $(FLAGS) main.c
execute.o : shell.h execute.c
	$(CC) $(FLAGS) execute.c
parse.o : shell.h parse.c
	$(CC) $(FLAGS) parse.c
socp.o : shell.h socp.c
	$(CC) $(FLAGS) socp.c 
calc.o : shell.h calc.c
	$(CC) $(FLAGS) calc.c 
jpeg.o : shell.h jpeg.c
	$(CC) $(FLAGS) jpeg.c 
redirect.o : shell.h redirect.c
	$(CC) $(FLAGS) redirect.c 
pipe.o : shell.h pipe.c
	$(CC) $(FLAGS) pipe.c 
soshell : $(OBS)
	$(CC)  -o soshell  $(OBS) $(LIBS)
clean limpar:
	rm -f soshell *.o
	rm -f *~
	echo "Remover: Ficheiros executáveis, objetos e temporários."
