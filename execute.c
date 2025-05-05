/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"

void execute(char **args) {
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
      // Processo filho
      if (execvp(args[0], args) == -1) {
          perror("execvp");
      }
      exit(EXIT_FAILURE);
  } else if (pid < 0) {
      // Erro no fork
      perror("fork");
  } else {
      // Processo pai
      do {
          waitpid(pid, &status, WUNTRACED);
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
}
