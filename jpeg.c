#include "shell.h"

// Um ficheiro JPG começa com 0xFF 0xD8 0xFF, seguido de um byte de tipo (0xE0, 0xE1, 0xE2, 0xE8).
//
// Output: 1 -> É JPEG | 0 -> Não é JPEG
//
int isjpg(int fileDescriptor) {

    // armazenar os primeiros 4 bytes
    unsigned char b[4];
    int n = read(fileDescriptor, b, 4); 

    if (n < 4) {  
        return 0;
    }

    lseek(fileDescriptor, 0, SEEK_SET);

    // Verificar os magic bytes (0xFF, 0xD8, 0xFF) + um dos tipos conhecidos
    if (b[0] == 0xFF && b[1] == 0xD8 && b[2] == 0xFF && (b[3] == 0xE0 || b[3] == 0xE1 || b[3] == 0xE2 || b[3] == 0xE8)) {
        return 1;
    }

    return 0;
}
