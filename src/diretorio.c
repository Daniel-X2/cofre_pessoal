#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../include/diretorio.h"

char* encontrar_diretorio (char diretorio[]) {
    /*
    char diretorio= "../layout/interface.glade"
    se eu quero que o diretorio volte sera necessario . ou .. pra voltar a diretorios anteriores 
    e resolver o caminho absoluto

    sera necessario usar o free depois
    */
    char* caminho = realpath(diretorio, NULL);//
    caminho="/home/daniel/Área de trabalho/cofre_pessoal/layout/interface.glade";
    if (caminho != NULL) {
        printf("Absoluto: %s\n", caminho);
        //free(caminho);
        return caminho;
    } else {
        perror("Erro ao resolver caminho"); // mostra o motivo
        printf("foi nao man\n");
        free(caminho);
    }
}
