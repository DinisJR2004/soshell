#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <limits.h>

void neofetch() {
    struct passwd *pw = getpwuid(getuid());
    char hostname[HOST_NAME_MAX];
    struct utsname uts;
    struct sysinfo sys;
    char cwd[PATH_MAX];

    // Nome do utilizador
    char *username = pw ? pw->pw_name : "Desconhecido";

    // Nome da máquina
    gethostname(hostname, sizeof(hostname));

    // Informações do sistema operativo e kernel
    uname(&uts);

    // Informações do sistema (CPU, memória, uptime)
    sysinfo(&sys);

    // Diretório atual
    getcwd(cwd, sizeof(cwd));

    // Conversão de memória total (em MB)
    unsigned long ram_mb = sys.totalram / 1024 / 1024;

    // Tempo desde boot (uptime)
    int dias = sys.uptime / 86400;
    int horas = (sys.uptime % 86400) / 3600;
    int minutos = (sys.uptime % 3600) / 60;

    // Impressão do "neofetch"

    printf(
        "       .--.\n"
        "      |o_o |\n"
        "      |:_/ |\n"
        "     //   \\ \\\n"
        "    (|     | )\n"
        "   /'\\_   _/`\\\n"
        "   \\___)=(___/\n"
        "\n"
    );

    printf("\n");
    printf("Usuário:      %s\n", username);
    printf("Host:         %s\n", hostname);
    printf("OS:           %s %s\n", uts.sysname, uts.release);
    printf("Kernel:       %s\n", uts.release);
    printf("Arquitetura:  %s\n", uts.machine);
    printf("CPU(s):       %d\n", get_nprocs());
    printf("RAM total:    %lu MB\n", ram_mb);
    printf("Diretório:    %s\n", cwd);
    printf("Uptime:       %dd %dh %dm\n", dias, horas, minutos);
    printf("\n");
}
