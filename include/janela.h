#ifndef JANELA
#define JANELA_H
#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/diretorio.h"
#include "../include/init.h"
#include <string.h>
#include "../include/funcoes_main.h"

int janela_confirmar();
void alterar();
int window_dados(GtkWidget *widget, gpointer user_data);
int deletar();
#endif