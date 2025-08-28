#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/diretorio.h"
GtkBuilder * builder;
GtkWidget * window;
GtkWidget * botao_nota;
GtkWidget * lixeira;
GtkWidget * senhas;

void botao_senhas();

void config_init(GtkWidget *window);
void botao();
void botao_lixeira();
void botao_notas();
int main(int argc, char *argv[]) {
    
    
    
    gtk_init(&argc, &argv);

    char *caminho=encontrar_diretorio("../layout/interface.glade");
    if (!caminho)
    {
        fprintf(stderr, "Arquivo não encontrado!\n");
        return 0;
    }
    builder = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
    free(caminho);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    //note=GTK_WIDGET(gtk_builder_get_object(builder,"ola"));
    botao_nota=GTK_WIDGET(gtk_builder_get_object(builder,"notas"));
    //janela_notas=GTK_WIDGET(gtk_builder_get_object(builder,"janela_anotacoes"));
    //gtk_notebook_set_current_page(GTK_NOTEBOOK(botao_notas),2);
    lixeira=GTK_WIDGET(gtk_builder_get_object(builder,"botao_lixeira"));
    
    senhas=GTK_WIDGET(gtk_builder_get_object(builder,"botao_senhas"));
    
    g_signal_connect(lixeira,"clicked",G_CALLBACK(botao_lixeira),NULL);
    
    g_signal_connect(senhas,"clicked",G_CALLBACK(botao_senhas),NULL);
    
    g_signal_connect(botao_nota,"clicked",G_CALLBACK(botao_notas),NULL);
    
   

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //printf("ola mundo");
    gtk_widget_show_all(window);
    gtk_main();
    
   

    return 1;
}
void botao_notas()
{
    GtkWidget * janela_note1;


    janela_note1=GTK_WIDGET(gtk_builder_get_object(builder,"gtknotebook"));
    //janela_notas=GTK_WIDGET(gtk_builder_get_object(builder,"janela_anotacoes"));
    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note1),0);
}
void botao_lixeira()
{
    GtkWidget * janela_note3;
    janela_note3=GTK_WIDGET(gtk_builder_get_object(builder,"gtknotebook"));

    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note3),2);
    
}
void botao_senhas()
{
    GtkWidget * janela_note2;
    janela_note2=GTK_WIDGET(gtk_builder_get_object(builder,"gtknotebook"));

    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note2),1);
}