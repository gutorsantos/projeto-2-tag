#define FILE_PATH "./entradaProj2TAG.txt"

FILE* readFile() {
    FILE *fptr;                     // Criado ponteiro para arquivo

    fptr = fopen(FILE_PATH, "r");   // Abre o arquivo no modo leitura

    // Verifica se o arquivo foi aberto com sucesso
    if(fptr == NULL) {
        printf("Error! Opening file failed!");
        return NULL;
    }

    return fptr;
}

void closeFile(FILE* fptr) {
    fclose(fptr);
}