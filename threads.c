#include "shell.h"

char copy_log[MAX_LOG_ENTRIES][LOG_ENTRY_SIZE];
int log_index = 0;

void aviso (char *mesg, int tempo)
{
    while (tempo > 0) {

        sleep (1);
        tempo--;

    }

    fprintf (stderr, "Aviso : %s\n", mesg );
}

void * avisowrapperMAU(void *args) {

    char ** argsin = (char **)args;
    aviso(argsin[1], atoi(argsin[2]));
    return NULL;

}

void * avisowrapper(void *args) {
    aviso_t * ptr = (aviso_t *)args;
    aviso(ptr->msg, ptr->tempo);
    free(ptr);
    return NULL;
}

void socpthread(char *fonte, char *destino) {
    // Validação básica dos argumentos
    if (fonte == NULL || destino == NULL) {
        fprintf(stderr, "Uso: socpthread <fonte> <destino>\n");
        return;
    }

    // Aloca e preenche a estrutura de dados
    copiar_t *dados = malloc(sizeof(copiar_t));
    if (dados == NULL) {
        perror("malloc");
        return;
    }

    strncpy(dados->fonte, fonte, 255);
    dados->fonte[255] = '\0';
    strncpy(dados->destino, destino, 255);
    dados->destino[255] = '\0';

    // Cria a thread detached
    pthread_t thread;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    if (pthread_create(&thread, &attr, socp_wrapper, (void *)dados) != 0) {
        perror("pthread_create");
        free(dados);
    }
    
    pthread_attr_destroy(&attr);
}

void log_copy_result(const char *filename, int success) {
    time_t current_time;
    time(&current_time);
    char *time_str = ctime(&current_time);
    
    time_str[strlen(time_str)-1] = '\0';
    snprintf(copy_log[log_index % MAX_LOG_ENTRIES], LOG_ENTRY_SIZE,
             "%s %s - %s", time_str, filename, success ? "SUCCESS" : "FAILED");
    log_index++;
}

void *socp_wrapper(void *args) {
    copiar_t *dados = (copiar_t *)args;
    int success = 0;
    
    if (dados && dados->fonte[0] && dados->destino[0]) {
        if (access(dados->fonte, F_OK) == 0) {
            socp(dados->fonte, dados->destino);
            success = (access(dados->destino, F_OK) == 0);  // CORREÇÃO: parênteses fechado
        }
    }
    
    log_copy_result(dados->fonte, success);
    free(dados);
    return NULL;
}

void InfoCopias() { 
    int start = (log_index > MAX_LOG_ENTRIES) ? (log_index % MAX_LOG_ENTRIES) : 0;
    int count = (log_index > MAX_LOG_ENTRIES) ? MAX_LOG_ENTRIES : log_index;
    
    for (int i = 0; i < count; i++) {
        printf("%s\n", copy_log[(start + i) % MAX_LOG_ENTRIES]);
    }
}