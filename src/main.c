#include <gtk/gtk.h>


#include <stdio.h>
#include "../include/diretorio.h"
#include "../include/banco_de_dados.h"
GtkBuilder * builder;
GtkWidget * window;
GtkWidget * botao_nota;
GtkWidget * lixeira;
GtkWidget * senhas;
GtkWidget * input_nome;
GtkWidget * input_nome_item;
GtkWidget * input_senha;

GtkWidget * janela_note;
GtkWidget * teste;

GtkWidget * botao_confirmar;

void botao();
void botao_senhas();
void inputs();
void botoes();
void botao_lixeira();
void botao_notas();
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
    
    janela_note=GTK_WIDGET(gtk_builder_get_object(builder,"gtknotebook"));
    teste=GTK_WIDGET(gtk_builder_get_object(builder,"favorito"));
    g_signal_connect(teste,"clicked",G_CALLBACK(inputs),NULL);
    
    

    botoes();
    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),0);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //printf("ola mundo");
    gtk_widget_show_all(window);
    gtk_main();
    

    return 1;
}
void botoes()
{
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    //note=GTK_WIDGET(gtk_builder_get_object(builder,"ola"));
    botao_nota=GTK_WIDGET(gtk_builder_get_object(builder,"notas"));
    //janela_notas=GTK_WIDGET(gtk_builder_get_object(builder,"janela_anotacoes"));
    //gtk_notebook_set_current_page(GTK_NOTEBOOK(botao_notas),2);
    lixeira=GTK_WIDGET(gtk_builder_get_object(builder,"botao_lixeira"));
    
    senhas=GTK_WIDGET(gtk_builder_get_object(builder,"botao_senhas"));
    
    botao_confirmar=GTK_WIDGET(gtk_builder_get_object(builder,"botao_confirmar"));

    g_signal_connect(botao_confirmar,"clicked",G_CALLBACK(botao),NULL);
    
    g_signal_connect(lixeira,"clicked",G_CALLBACK(botao_lixeira),NULL);
    
    g_signal_connect(senhas,"clicked",G_CALLBACK(botao_senhas),NULL);
    
    g_signal_connect(botao_nota,"clicked",G_CALLBACK(botao_notas),NULL);
    
    
}
void botao_notas()
{
    


    janela_note=GTK_WIDGET(gtk_builder_get_object(builder,"gtknotebook"));
    //janela_notas=GTK_WIDGET(gtk_builder_get_object(builder,"janela_anotacoes"));
    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),0);
}
void botao_lixeira()
{
    
    janela_note=GTK_WIDGET(gtk_builder_get_object(builder,"gtknotebook"));

    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),2);
    
}
void botao_senhas()
{
    
    janela_note=GTK_WIDGET(gtk_builder_get_object(builder,"gtknotebook"));

    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),1);
}


void botao()
{
    
    input_nome=GTK_WIDGET(gtk_builder_get_object(builder,"input_usuario"));
    input_nome_item=GTK_WIDGET(gtk_builder_get_object(builder,"input_item"));
    input_senha=GTK_WIDGET(gtk_builder_get_object(builder,"input_senha"));

    const gchar *nome_item=gtk_entry_get_text(GTK_ENTRY(input_nome_item));
    const gchar *senha=gtk_entry_get_text(GTK_ENTRY(input_senha));
    const gchar *nome=gtk_entry_get_text(GTK_ENTRY(input_nome));
    
    printf("%s %s %s\n",nome,nome_item,senha);

    inserir_dados(nome_item,nome,senha);
}
void inputs()
{
    int n1=gtk_notebook_get_current_page(GTK_NOTEBOOK(janela_note));

    printf("iae %i\n",n1);
    switch (n1)
    {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;

    }
}

