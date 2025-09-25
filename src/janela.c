
#include "../include/janela.h"
#include <stdlib.h>
    GtkWidget * window2;
    GtkBuilder * builder_janela;
    int id;
int window_dados(GtkWidget *widget, gpointer user_data) {
   
    const gchar* name=gtk_widget_get_name(widget);
   id = atoi(name);

    char *caminho=encontrar_diretorio("./layout/atualizar_dados.glade");
    if (!caminho)
    {   
        free(caminho);
        char *caminho=encontrar_diretorio("../layout/atualizar_dados.glade");
        
        if (!caminho)
        {
            fprintf(stderr, "[ERRO] Arquivo de interface não encontrado!\n");
            fprintf(stderr, "       Tentativas: ./layout/atualizar_dados.glade e ../layout/atualizar_dados.glade\n");
            fprintf(stderr, "       Solução: Verifique se a pasta 'layout' existe no diretório correto.\n");                
            free(caminho);
            
            return 1;
            
        }
        else
        {
            builder_janela = gtk_builder_new_from_file(caminho);
            free(caminho);
        }
    }
    else
    {
        builder_janela = gtk_builder_new_from_file(caminho);
        free(caminho);
    }
    
    
    //free(caminho);
    
    window2 = GTK_WIDGET(gtk_builder_get_object(builder_janela, "window2"));
    g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);
     
    GtkWidget *   input_item=GTK_WIDGET(gtk_builder_get_object(builder_janela,"atualizar_item"));
    GtkWidget *  input_senha=GTK_WIDGET(gtk_builder_get_object(builder_janela,"atualizar_usuario"));
    GtkWidget * input_nome=GTK_WIDGET(gtk_builder_get_object(builder_janela,"atualizar_senha"));
   GtkWidget * botao_deletar=GTK_WIDGET(gtk_builder_get_object(builder_janela,"delete"));

    
    char *SENHA =senha_janela();
    
    char *dados=descriptografar(SENHA,id,0);
    const gchar *nome_item= strtok(dados,"|||");
    const gchar *senha=strtok(NULL,"|||");
   const  gchar *nome=strtok(NULL,"|||");
   //
    gtk_entry_set_text(GTK_ENTRY(input_item),nome_item);
    gtk_entry_set_text(GTK_ENTRY(input_nome),nome);
    gtk_entry_set_text(GTK_ENTRY(input_senha),senha);

    GtkWidget * botao_alterar=GTK_WIDGET(gtk_builder_get_object(builder_janela,"alterar"));
    g_signal_connect(botao_alterar,"clicked",G_CALLBACK(alterar),NULL);
    g_signal_connect(botao_deletar,"clicked",G_CALLBACK(deletar),NULL);

    gtk_widget_show_all(window2);
    gtk_main();
    
    //GtkWidget * teste1=GTK_WIDGET(gtk_builder_get_object(builder_janela,teste));

    //gpointer data = g_object_get_data(G_OBJECT(teste1),"id");
    //id=(int)data;
    
    destruir(dados);
    //free(user_data);///verificar depois
     g_object_unref(builder_janela);
    builder_janela = NULL;
    return 0;
}
void alterar()
{
    
    GtkWidget * input_item=GTK_WIDGET(gtk_builder_get_object(builder_janela,"atualizar_item"));
    GtkWidget * input_senha=GTK_WIDGET(gtk_builder_get_object(builder_janela,"atualizar_usuario"));
    GtkWidget * input_nome=GTK_WIDGET(gtk_builder_get_object(builder_janela,"atualizar_senha"));
    const char *nome=gtk_entry_get_text(GTK_ENTRY(input_nome));
    const char *nome_item=gtk_entry_get_text(GTK_ENTRY(input_item));
    const char *senha=gtk_entry_get_text(GTK_ENTRY(input_senha));
    if(strlen(nome)==0 |strlen(nome_item)==0| strlen(senha)==0)
    {
        if(strlen(nome)==0)
        {
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_nome),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
            gtk_entry_set_icon_tooltip_text(GTK_ENTRY(input_nome),GTK_ENTRY_ICON_PRIMARY,"Aviso: Nome  em branco");
        }
        else
        {
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_nome),GTK_ENTRY_ICON_PRIMARY,NULL);
        }
        if(strlen(nome_item)==0)
        {
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_item),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
            gtk_entry_set_icon_tooltip_text(GTK_ENTRY(input_item),GTK_ENTRY_ICON_PRIMARY,"Aviso: Nome do item em branco");
        }
        else
        {
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_item),GTK_ENTRY_ICON_PRIMARY,NULL);
        }
        if(strlen(senha)==0)
        {
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_senha),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
            gtk_entry_set_icon_tooltip_text(GTK_ENTRY(input_nome),GTK_ENTRY_ICON_PRIMARY,"Aviso: Senha em branco");
        }
        else{
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_senha),GTK_ENTRY_ICON_PRIMARY,NULL);
        }
        
    }
    else{
        char juntar_dados[strlen(nome)+strlen(nome_item)+strlen(senha)+10];
        char *SENHA=senha_janela();
        sprintf(juntar_dados,"%s|||%s|||%s",nome_item,senha,nome);
        init_cripto(SENHA,juntar_dados,1,id);
        
    }
   
    
}
int deletar()
{
    
    
    delete_init(id);
    gtk_widget_destroy(window2);
    controle_de_fluxo();
    
    return 0;
}