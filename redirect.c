#include "shell.h"

#define FILE_MODE (S_IRUSR | S_IWUSR)

// Fecha fdold, duplica fd para fdold, fecha fd e remove operador + nome de ficheiro dos argumentos
int dupandclose(int fd, int fdold, int numargs, char *args[])
{
    if (fd < 0)
    {
        perror("erro ao abrir ficheiro");
        exit(1);
    }
    dup2(fd, fdold);
    close(fd);
    args[numargs - 2] = NULL;
    return numargs - 2;
}

int redirects(int numargs, char *args[])
{
    if (numargs < 3)
        return numargs;

    // Redirecionamento de stderr (2>)
    if (strcmp(args[numargs - 2], "2>") == 0)
    {
        int fd = creat(args[numargs - 1], FILE_MODE);
        numargs = dupandclose(fd, STDERR_FILENO, numargs, args);
    }

    // Redirecionamento de stdout: >> (append) ou > (overwrite)
    if (numargs >= 3)
    {
        if (strcmp(args[numargs - 2], ">>") == 0)
        {
            int fd = open(args[numargs - 1], O_CREAT | O_WRONLY | O_APPEND, FILE_MODE);
            numargs = dupandclose(fd, STDOUT_FILENO, numargs, args);
        }
        else if (strcmp(args[numargs - 2], ">") == 0)
        {
            int fd = creat(args[numargs - 1], FILE_MODE);
            numargs = dupandclose(fd, STDOUT_FILENO, numargs, args);
        }
    }

    // Redirecionamento de stdin (<)
    if (numargs >= 3 && strcmp(args[numargs - 2], "<") == 0)
    {
        int fd = open(args[numargs - 1], O_RDONLY);
        numargs = dupandclose(fd, STDIN_FILENO, numargs, args);
    }

    return numargs;
}


