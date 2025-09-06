#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/diretorio.h"
#include "../include/banco_de_dados.h"
#include "../include/criptografar.h"

GtkBuilder * builder;
GtkWidget * window;
GtkWidget * botao_nota;
GtkWidget * lixeira;
GtkWidget * senhas;
GtkWidget * input_nome;
GtkWidget * input_nome_item;
GtkWidget * input_nome_item2;
GtkWidget * input_senha;
GtkWidget * input_anotacao;
GtkWidget * janela_note;
GtkWidget * cancelar;
GtkWidget * salvar;
GtkWidget * botao_confirmar;
GtkTextIter start,end;
GtkTextBuffer * buffer;

void entry_janela1();
void entry_janela2();
void botao_senhas();
void conectar_botoes();
void botoes();
void botao_lixeira();
void botao_notas();
void cancelar_entry();
void get_object_gtk();
int main(int argc, char *argv[]) {
    
    
    
    gtk_init(&argc, &argv);
    init_sql();
  


    char *caminho=encontrar_diretorio("./layout/interface.glade");
    if (!caminho)
    {
        fprintf(stderr, "Arquivo não encontrado!\n");
        return 0;
    }
    builder = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
    //free(caminho);
    get_object_gtk();
    init_criptografia("iae","8787");
    conectar_botoes();
    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),0);
    
    //printf("ola mundo");
    gtk_widget_show_all(window);
    gtk_main();
    
    fechar_banco();

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
    
    printf("%s %s %s\n",nome,nome_item,senha);

    
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
    //note=GTK_WIDGET(gtk_builder_get_object(builder,"ola"));
    botao_nota=GTK_WIDGET(gtk_builder_get_object(builder,"notas"));
    //janela_notas=GTK_WIDGET(gtk_builder_get_object(builder,"janela_anotacoes"));
    //gtk_notebook_set_current_page(GTK_NOTEBOOK(botao_notas),2);
    lixeira=GTK_WIDGET(gtk_builder_get_object(builder,"botao_lixeira"));
    
    senhas=GTK_WIDGET(gtk_builder_get_object(builder,"botao_senha"));
    
    botao_confirmar=GTK_WIDGET(gtk_builder_get_object(builder,"botao_confirmar"));

    salvar=GTK_WIDGET(gtk_builder_get_object(builder,"salvar"));

    cancelar=GTK_WIDGET(gtk_builder_get_object(builder,"cancelar"));
    
    input_nome_item=GTK_WIDGET(gtk_builder_get_object(builder,"input_item2"));
    
    input_anotacao=GTK_WIDGET(gtk_builder_get_object(builder,"input_anotacao"));

    input_nome=GTK_WIDGET(gtk_builder_get_object(builder,"input_usuario"));
    input_nome_item2=GTK_WIDGET(gtk_builder_get_object(builder,"input_item"));
    input_senha=GTK_WIDGET(gtk_builder_get_object(builder,"input_senha"));

    
    
   
    
}   

void conectar_botoes()
{
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(cancelar,"clicked",G_CALLBACK(cancelar_entry),NULL);

    g_signal_connect(salvar,"clicked",G_CALLBACK(entry_janela2),NULL);

    g_signal_connect(botao_confirmar,"clicked",G_CALLBACK(entry_janela1),NULL);
    
    g_signal_connect(lixeira,"clicked",G_CALLBACK(botao_lixeira),NULL);
    
    g_signal_connect(senhas,"clicked",G_CALLBACK(botao_senhas),NULL);
    
    g_signal_connect(botao_nota,"clicked",G_CALLBACK(botao_notas),NULL);


}

