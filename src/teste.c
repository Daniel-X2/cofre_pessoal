#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/diretorio.h"
#include "../include/init.h"
#include <string.h>





int teste() {
    GtkWidget * window;
    GtkBuilder * builder;
    
    
    //gtk_init(&argc, &argv);
    //init_sql();
  


    //char *caminho=encontrar_diretorio("../layout/atualizar_dado.glade");
    char caminho []="/home/daniel/Área de trabalho/cofre_pessoal/layout/atualizar_dados.glade";
    if (!caminho)
    {
        fprintf(stderr, "Arquivo não encontrado!\n");
        return 0;
    }
    
    builder = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
    //free(caminho);
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    
   
    //init_criptografia("iae","8787");
    
    
    
    
   
    
    //printf("ola mundo");
    gtk_widget_show_all(window);
    gtk_main();
    
    //fechar_banco();

    return 1;
}
