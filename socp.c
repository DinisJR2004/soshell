#include "shell.h"

#define BUFFSIZE 128  // Tamanho do buffer para leitura/escrita

void ioCopy(int IN, int OUT) {
    int n;
    char buf[1024];
    
    while ((n = read(IN, buf, sizeof(buf))) > 0) {
        if (write(OUT, buf, n) != n) {
            perror("Erro na escrita");
            return; // Sai da função mas não retorna valor
        }
    }
    
    if (n < 0) {
        perror("Erro na leitura");
    }
}

void socp(char *fonte, char *destino) {
    int fd_origem = open(fonte, O_RDONLY);
    if (fd_origem < 0) {
        perror("Erro ao abrir arquivo de origem");
        return;
    }

    int fd_destino = open(destino, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_destino < 0) {
        perror("Erro ao criar/abrir arquivo de destino");
        close(fd_origem);
        return;
    }

    ioCopy(fd_origem, fd_destino);
    
    close(fd_origem);
    close(fd_destino);
}