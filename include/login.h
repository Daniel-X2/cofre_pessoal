#ifndef LOGIN_H
#define LOGIN_H
#include <stdio.h>
#include "../include/diretorio.h"
#include <gtk/gtk.h>
#include "../include/init.h"
#include "../include/funcoes_main.h"
#include "string.h"
#include <ctype.h>
char* login_main(int verificar);
void conectar_botao_login();
void confirmar_acao_login2();
void remover_espaco(char * str);
gboolean interatividade(gpointer nulo);
#endif