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
#include <dirent.h> 
#include <pwd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <limits.h>

#define MAX_LOG_ENTRIES 100
#define LOG_ENTRY_SIZE 130

extern char copy_log[MAX_LOG_ENTRIES][LOG_ENTRY_SIZE];
extern int log_index;

typedef struct {
    char msg[256];
    int tempo;
} aviso_t;

typedef struct {
    char fonte[256];      
    char destino[256];          
} copiar_t;

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

void aviso (char *mesg, int tempo);

void * avisowrapperMAU(void *args);

void * avisowrapper(void *args);

void socpthread(char *fonte, char *destino);

void *socp_wrapper(void *args);

void log_copy_result(const char *filename, int success);

void InfoCopias();

void maior(const char *ficheiro1, const char *ficheiro2);

void setx(const char *ficheiro);

void removerl(const char *ficheiro);

void listar(char *pasta);

void neofetch();

/* constantes que podem tornar uteis*/
#define BG 0
#define FG 1
