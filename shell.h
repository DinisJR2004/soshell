#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h> 
#include <math.h>

void parse(char *buf, char **args);

void execute(char **args);

int builtin (char **args);

void socp(char *fonte, char *destino);

void ioCopy(int IN, int OUT);

void calc (char *value1, char *op, char *value2);

void bits(char *op1, char *op, char *op2);

int isjpg(int fileDescriptor);

int dupandclose(int fd, int fdold, int numargs, char *args[]);

int redirects(int numargs, char *args[]);

int executar_com_pipe(char **args);

int containsPipe (int numArgs, char **arg);

/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1
