#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/diretorio.h"
#include "../include/init.h"
#include <string.h>
//#include "../include/banco_de_dados.h"
//#include "../include/crypto.h"
char *SENHA="senha do maluco";
GtkBuilder * builder;
GtkWidget * window;
GtkWidget * senhas;
GtkWidget * input_nome;
GtkWidget * input_nome_item;
GtkWidget * input_senha;
GtkWidget * janela_note;


void entry_janela1();
void entry_janela2();
void botao_senhas();
void conectar_botoes();
void botoes();
void botao_lixeira();
void botao_notas();
void cancelar_entry();
void get_object_gtk();
void separar( char *dados);
int main(int argc, char *argv[]) {
    
    
    
    gtk_init(&argc, &argv);
    //init_sql();
  


    char *caminho=encontrar_diretorio("./layout/interface.glade");
    if (!caminho)
    {
        fprintf(stderr, "Arquivo não encontrado!\n");
        return 0;
    }
    builder = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
    //free(caminho);
    get_object_gtk();
    //init_criptografia("iae","8787");
    conectar_botoes();
    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),0);
    
    
   
    
    //printf("ola mundo");
    gtk_widget_show_all(window);
    gtk_main();
    
    //fechar_banco();

    return 1;
}

void botao_notas()
{
    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),1);
}
void botao_lixeira()
{
    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),2);
}
void botao_senhas()
{
    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),0);
}


void entry_janela1()
{
    const gchar *nome_item=gtk_entry_get_text(GTK_ENTRY(input_nome_item));
    const gchar *senha=gtk_entry_get_text(GTK_ENTRY(input_senha));
    const gchar *nome=gtk_entry_get_text(GTK_ENTRY(input_nome));
    
    
    char dados[100];
    sprintf(dados,"%s|||%s|||%s",nome_item,senha,nome);
    
    init_cripto(SENHA,dados);
    
}

void entry_janela2()
{
    buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(input_anotacao));

    gtk_text_buffer_get_start_iter(buffer,&start);
    gtk_text_buffer_get_end_iter(buffer,&end);

    const gchar *anotacao= gtk_text_buffer_get_text(buffer,&start,&end,FALSE);

    const gchar *nome_item=gtk_entry_get_text(GTK_ENTRY(input_nome_item));
    
    
    
    
    

}
void cancelar_entry()
{
    buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(input_anotacao));
    gtk_entry_set_text(GTK_ENTRY(input_nome_item),"");
    gtk_text_buffer_set_text(buffer,"",1);
    
}
 
void get_object_gtk()
{
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

    janela_note=GTK_WIDGET(gtk_builder_get_object(builder,"gtknotebook"));
    

    
    senhas=GTK_WIDGET(gtk_builder_get_object(builder,"botao_senha"));
    
    input_nome=GTK_WIDGET(gtk_builder_get_object(builder,"input_usuario"));
    input_nome_item=GTK_WIDGET(gtk_builder_get_object(builder,"input_item"));
    input_senha=GTK_WIDGET(gtk_builder_get_object(builder,"input_senha"));

}   

void conectar_botoes()
{
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(senhas,"clicked",G_CALLBACK(botao_senhas),NULL);

}
void separar( char *dados)
{
    
    char *nome_item= strtok(dados,"|||");
    char *senha=strtok(NULL,"|||");
    char *nome=strtok(NULL,"|||");

    printf("ola mano %s %s %s\n",nome,senha,nome_item);
    
    
}
