#include "shell.h"

// Está funcional, mas tenho que refazer no execute.c 
//

/* Detetar o simbolo do PIPE dentro do array of Strings. Devolve a indice ou -1 se não existe */
int containsPipe (int numArgs, char **args) {
    for (int index = 0; index < numArgs; index++){
        if ( '|' == args[index][0] ) {
            return index;
        }
    }
    return -1;
}

int executar_com_pipe(char **args) {

    char *comandos[10][64]; 
    int cmd_index = 0, arg_index = 0, inner_index = 0;

    // Dividir os comandos baseados no pipe
    while (args[arg_index] != NULL) {
        if (strcmp(args[arg_index], "|") == 0) {
            comandos[cmd_index][inner_index] = NULL;  
            cmd_index++;  
            inner_index = 0;
        } else {
            comandos[cmd_index][inner_index++] = args[arg_index]; 
        }
        arg_index++;
    }
    comandos[cmd_index][inner_index] = NULL;  

    int cmd_count = cmd_index + 1;  
    pid_t pid;
    int pipefd[2], prev_fd = -1;

    for (int i = 0; i < cmd_count; i++) {
        pipe(pipefd);  

        if ((pid = fork()) == 0) {
            // Se não é o primeiro comando, redireciona stdin
            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO);  // Redireciona stdin para o pipe anterior
                close(prev_fd);
            }

            // Se não é o último comando, redireciona stdout
            if (i < cmd_count - 1) {
                dup2(pipefd[1], STDOUT_FILENO);  // Redireciona o stdout para o próximo pipe
            }

            close(pipefd[0]);
            close(pipefd[1]);

            // Executa o comando
            if (!builtin(comandos[i])) {
                execute(comandos[i]);
            }
            exit(0);
        } else {
            wait(NULL);  // Espera o processo filho terminar
            close(pipefd[1]);
            if (prev_fd != -1) {
                close(prev_fd);
            }
            prev_fd = pipefd[0]; 
        }
    }

    return 1; 
}
