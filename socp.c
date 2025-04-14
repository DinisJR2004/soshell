#include "shell.h"

#define BUFFSIZE 128  // Tamanho do buffer para leitura/escrita

void ioCopy(int IN, int OUT) // Função de cópia
{
    int n;
    char buf[BUFFSIZE];
    while ((n = read(IN, buf, BUFFSIZE)) > 0)
    {
        if (write(OUT, buf, n) != n)
        {
            perror("Erro de escrita");
            close(IN);
            close(OUT);
            exit(1);
        }
    }
    if (n < 0)
        perror("Erro de leitura");
}

void socp(char *fonte, char *destino)
{
    int fd_origem, fd_destino;

    // Abrir arquivo de origem para leitura
    fd_origem = open(fonte, O_RDONLY);
    if (fd_origem < 0)
    {
        perror("Erro ao abrir arquivo de origem");
        return;
    }

    // Criar/abrir arquivo de destino para escrita (permissões: rw-r--r--)
    fd_destino = open(destino, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_destino < 0)
    {
        perror("Erro ao criar/abrir arquivo de destino");
        close(fd_origem);
        return;
    }

    // Copia os dados de fd_origem para fd_destino
    ioCopy(fd_origem, fd_destino);

    // Fecha os arquivos
    close(fd_origem);
    close(fd_destino);
}
