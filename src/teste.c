#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/diretorio.h"
#include "../include/init.h"
#include <string.h>
#include "../include/teste.h"
    GtkWidget * window_janela;
    GtkBuilder * builder_janela;
    GtkWidget * input_item_janela;
    GtkWidget * input_nome_janela;
    GtkWidget * input_senha_janela;
    GtkWidget * botao_alterar;
int id;



int teste(GtkWidget *widget, gpointer user_data) {
    id = *((int*)user_data);

    
    //gtk_init(&argc, &argv);
    //init_sql();
    char *caminho=encontrar_diretorio("./layout/atualizar_dados.glade");
    //printf("ola mundoooo %s",caminho);
    if (!caminho)
    {
        fprintf(stderr, "Arquivo não encontrado!\n");
        return 0;
    }
    
    builder_janela = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
    //free(caminho);
    
    window_janela = GTK_WIDGET(gtk_builder_get_object(builder_janela, "window2"));
    g_signal_connect(window_janela, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    input_item_janela=GTK_WIDGET(gtk_builder_get_object(builder_janela,"input_item"));
    input_senha_janela=GTK_WIDGET(gtk_builder_get_object(builder_janela,"input_usuario"));
    input_nome_janela=GTK_WIDGET(gtk_builder_get_object(builder_janela,"input_senha"));
   
    

    char *dados=descriptografar("senha do maluco",id);
    const gchar *nome_item= strtok(dados,"|||");
    const gchar *senha=strtok(NULL,"|||");
   const  gchar *nome=strtok(NULL,"|||");
    gtk_entry_set_text(GTK_ENTRY(input_item_janela),nome_item);
    gtk_entry_set_text(GTK_ENTRY(input_nome_janela),nome);
    gtk_entry_set_text(GTK_ENTRY(input_senha_janela),senha);

    
    botao_alterar=GTK_WIDGET(gtk_builder_get_object(builder_janela,"alterar"));
    g_signal_connect(botao_alterar,"clicked",G_CALLBACK(alterar),NULL);
    
    //init_criptografia("iae","8787");
    
    
    
    
   
    
    //printf("ola mundo");
    gtk_widget_show_all(window_janela);
    gtk_main();
    //free(id);
    //fechar_banco();

    return 1;
}
void alterar()
{
    printf("cheguei\n");
    const char *nome=gtk_entry_get_text(GTK_ENTRY(input_nome_janela));
    const char *nome_item=gtk_entry_get_text(GTK_ENTRY(input_item_janela));
    const char *senha=gtk_entry_get_text(GTK_ENTRY(input_senha_janela));
    char juntar_dados[strlen(nome)+strlen(nome_item)+strlen(senha)+10];

    sprintf(juntar_dados,"%s|||%s|||%s",nome_item,senha,nome);
    init_cripto("senha do maluco",juntar_dados,1,id);
    //free(id);
}