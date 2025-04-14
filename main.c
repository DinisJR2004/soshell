#include "shell.h"

char prompt[100];
char prev_dir[1024] = "";

int main()
{
  int len;
  char linha[1024]; /* um comando */
  char *args[64];   /* com um maximo de 64 argumentos */

  strcpy(prompt, "SOSHELL:");
  while (1)
  {
    printf("%s", prompt);
    if (fgets(linha, 1023, stdin) == NULL)
    {
      printf("\n");
      exit(0);
    }
    len = strlen(linha);
    if (1 == len)
      continue; /* linha é apenas \n */
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';
    parse(linha, args); /* particiona a string em argumentos */

    if (!builtin(args))
      execute(args); /* executa o comando */
  }
  return 0;
}

int builtin(char **args)
{
  if (args[0] == NULL)
    return 0;

  // Contar argumentos
  int numargs = 0;
  while (args[numargs] != NULL)
    numargs++;

  // Guardar descritores originais
  int saved_stdin = dup(STDIN_FILENO);
  int saved_stdout = dup(STDOUT_FILENO);
  int saved_stderr = dup(STDERR_FILENO);


  /////////////////////////////
  int pipe_index = containsPipe(numargs, args);
  if (pipe_index != -1) {
    return executar_com_pipe(args);  // Chama a função para lidar com o pipe
  }
  /////////////////////////////////

  // Tratar redirecionamentos
  numargs = redirects(numargs, args);

  // Comandos embutidos
  if (strcmp(args[0], "sair") == 0)
  {
    // Restaurar antes de sair
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    dup2(saved_stderr, STDERR_FILENO);
    close(saved_stdin);
    close(saved_stdout);
    close(saved_stderr);
    exit(0);
  }

  if (strncmp(args[0], "42", 2) == 0)
  {
    printf("42 is the answer to life the universe and everything\n");
    printf("https://pt.wikipedia.org/wiki/The_Hitchhiker's_Guide_to_the_Galaxy\n");
    goto fim;
  }

  if (strcmp(args[0], "obterinfo") == 0)
  {
    printf("SO Shell 2025 versão 1.0\n");
    goto fim;
  }

  if (strlen(args[0]) > 4 && strncmp(args[0], "PS1=", 4) == 0)
  {
    strcpy(prompt, args[0] + 4);
    goto fim;
  }

  if (strcmp(args[0], "quemsoueu") == 0)
  {
    system("id");
    goto fim;
  }

  if (strcmp(args[0], "cd") == 0)
  {
    int err;
    char current_dir[1024];

    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
      perror("getcwd");
      goto fim;
    }

    if (args[1] == NULL || strcmp(args[1], "~") == 0 || strcmp(args[1], "$HOME") == 0)
      err = chdir(getenv("HOME"));
    else if (strcmp(args[1], "-") == 0)
    {
      if (strlen(prev_dir) == 0)
      {
        fprintf(stderr, "cd: diretório anterior não definido\n");
        goto fim;
      }
      err = chdir(prev_dir);
      printf("%s\n", prev_dir);
    }
    else
      err = chdir(args[1]);

    if (err < 0)
      perror(args[1]);
    else
      strcpy(prev_dir, current_dir);

    goto fim;
  }

  if (strcmp(args[0], "socp") == 0)
  {
    if (args[1] != NULL && args[2] != NULL)
      socp(args[1], args[2]);
    else
      fprintf(stderr, "Uso: socp <fonte> <destino>\n");
    goto fim;
  }

  if (strcmp(args[0], "calc") == 0)
  {
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL)
      fprintf(stderr, "Uso: calc <valor1> <operador> <valor2>\n");
    else
      calc(args[1], args[2], args[3]);
    goto fim;
  }

  if (strcmp(args[0], "bits") == 0)
  {
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL)
      fprintf(stderr, "Uso: bits <valor1> <operador> <valor2>\n");
    else
      bits(args[1], args[2], args[3]);
    goto fim;
  }

  if (strcmp(args[0], "isjpg") == 0)
  {
    if (args[1] == NULL)
    {
      fprintf(stderr, "Uso: isjpg <ficheiro>\n");
      goto fim;
    }

    int fd = open(args[1], O_RDONLY);
    if (fd == -1)
    {
      perror("Erro ao abrir ficheiro");
      goto fim;
    }

    if (isjpg(fd))
      printf("O ficheiro %s é um JPG válido.\n", args[1]);
    else
      printf("O ficheiro %s NÃO é um JPG válido.\n", args[1]);

    close(fd);
    goto fim;
  }

  // Comando não é embutido
  dup2(saved_stdin, STDIN_FILENO);
  dup2(saved_stdout, STDOUT_FILENO);
  dup2(saved_stderr, STDERR_FILENO);
  close(saved_stdin);
  close(saved_stdout);
  close(saved_stderr);
  return 0;

  // Usa goto fim; para garantir que o restauro dos stdio acontece sempre antes de retornar.
fim:
  // Restaurar stdio antes de sair
  dup2(saved_stdin, STDIN_FILENO);
  dup2(saved_stdout, STDOUT_FILENO);
  dup2(saved_stderr, STDERR_FILENO);
  close(saved_stdin);
  close(saved_stdout);
  close(saved_stderr);
  return 1;
}
