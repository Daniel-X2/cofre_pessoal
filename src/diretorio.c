

#include "../include/diretorio.h"

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#endif


char* encontrar_diretorio(char diretorio[]) {
#ifdef _WIN32
    // Windows: usa _fullpath
    char* abs_pasta = (char*)malloc(_MAX_PATH);
    if (_fullpath(abs_pasta, diretorio, _MAX_PATH) != NULL) {
        return abs_pasta;
    } else {
        perror("Erro ao resolver caminho");
        free(abs_pasta);
        return NULL;
    }
#else
    // Unix: usa realpath
    char* caminho = realpath(diretorio, NULL);
    
    if (caminho != NULL) {
        return caminho;
    } else {
        perror("Erro ao resolver caminho");
        free(caminho);
        return NULL;
    }
#endif
}
