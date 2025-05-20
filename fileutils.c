#include "shell.h"

void maior(const char *ficheiro1, const char *ficheiro2) {
    struct stat stat1, stat2;

    // Informações do primeiro ficheiro
    //
    if (stat(ficheiro1, &stat1) != 0) {
        perror("Erro ao aceder ao ficheiro 1");
        return;
    }

    // Informações do segundo ficheiro
    //
    if (stat(ficheiro2, &stat2) != 0) {
        perror("Erro ao aceder ao ficheiro 2");
        return;
    }

    if (stat1.st_size > stat2.st_size) {
        printf("Ficheiro maior: %s\n", ficheiro1);
        printf("Tamanho: %.2f KB\n", stat1.st_size / 1024.0);
    } else if (stat2.st_size > stat1.st_size) {
        printf("Ficheiro maior: %s\n", ficheiro2);
        printf("Tamanho: %.2f KB\n", stat2.st_size / 1024.0);
    } else {
        printf("Os ficheiros têm o mesmo tamanho: %.2f KB\n", stat1.st_size / 1024.0);
    }
}

void setx(const char *ficheiro) {
    struct stat info;

    // Permissões atuais
    //
    if (stat(ficheiro, &info) != 0) {
        perror("Erro ao aceder ao ficheiro");
        return;
    }

    // chmod +x 
    //
    mode_t novas_permissoes = info.st_mode | S_IXUSR;

    if (chmod(ficheiro, novas_permissoes) != 0) {
        perror("Erro ao alterar permissões");
        return;
    }

    printf("Permissão de execução atribuída ao ficheiro '%s'.\n", ficheiro);
}

void removerl(const char *ficheiro) {
    struct stat info;

    // Permissões atuais
    //
    if (stat(ficheiro, &info) != 0) {
        perror("Erro ao aceder ao ficheiro");
        return;
    }

    mode_t novas_permissoes = info.st_mode;
    novas_permissoes &= ~S_IRGRP; // remove leitura do grupo
    novas_permissoes &= ~S_IROTH; // remove leitura dos outros

    if (chmod(ficheiro, novas_permissoes) != 0) {
        perror("Erro ao alterar permissões");
        return;
    }

    printf("Permisões de leitura removidas no ficheiro '%s'.\n", ficheiro);
}

void listar(char *pasta) {
    if (pasta == NULL) {
        pasta = ".";
    }

    DIR *dir = opendir(pasta);
    if (dir == NULL) {
        perror("Erro ao abrir diretório");
        return;
    }

    struct dirent *entrada;
    struct stat info;
    char caminho[1024];

    while ((entrada = readdir(dir)) != NULL) {

        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0)
            continue;

        snprintf(caminho, sizeof(caminho), "%s/%s", pasta, entrada->d_name);

        if (stat(caminho, &info) == 0) {
            printf("Nome: %-20s | Inode: %-10lu | Tamanho: %-8ld bytes | Modificado: %s",
                   entrada->d_name,
                   (unsigned long) info.st_ino,
                   info.st_size,
                   ctime(&info.st_mtime));  
        } else {
            perror("Erro ao obter info do ficheiro");
        }
    }

    closedir(dir);
}
