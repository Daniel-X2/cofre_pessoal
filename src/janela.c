/**
 * @file janela.c
 * @brief Funções relacionadas à interface gráfica de atualização de dados do usuário utilizando GTK.
 */

#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/diretorio.h"
#include "../include/init.h"
#include <string.h>
#include "../include/janela.h"
#include "../include/funcoes_main.h"
// Variáveis globais para os widgets da janela de atualização
GtkWidget *window2;                ///< Janela de atualização de dados
GtkBuilder *builder_window2;       ///< Builder para carregar o layout Glade
GtkWidget *input_item_window2;     ///< Campo de entrada para o nome do item
GtkWidget *input_nome_window2;     ///< Campo de entrada para o nome do usuário
GtkWidget *input_senha_window2;    ///< Campo de entrada para a senha
GtkWidget *botao_alterar;          ///< Botão para confirmar alteração
int id;                            ///< ID do usuário selecionado

/**
 * @brief Abre a janela de atualização de dados, preenchendo os campos com os dados descriptografados do usuário.
 * 
 * Carrega o layout da janela, busca os dados do usuário pelo ID, descriptografa e preenche os campos.
 * Conecta o botão de alteração à função de atualização.
 * 
 * @param widget Widget que disparou o evento (não utilizado).
 * @param user_data Ponteiro para o ID do usuário (int*).
 * @return 1 em caso de sucesso, 0 em caso de erro.
 */
int window_dados(GtkWidget *widget, gpointer user_data);

/**
 * @brief Função de callback chamada ao clicar no botão de alterar.
 * 
 * Lê os dados dos campos de entrada, concatena e chama a função de atualização criptografada.
 */


    GtkWidget * window2;
    GtkBuilder * builder_window2;
    GtkWidget * input_item_window2;
    GtkWidget * input_nome_window2;
    GtkWidget * input_senha_window2;
    GtkWidget * botao_alterar;
    GtkWidget * botao_deletar;
int id;



int window_dados(GtkWidget *widget, gpointer user_data) {
    id = *((int*)user_data);

    char *caminho=encontrar_diretorio("./layout/atualizar_dados.glade");
    if (!caminho)
    {   
        free(caminho);
        char *caminho=encontrar_diretorio("../layout/atualizar_dados.glade");
        fprintf(stderr, "Segunda tentativa!\n");
        if (!caminho)
        {
            fprintf(stderr, "diretorio nao foi encontrado!\n");
            free(caminho);
            free(id);
            return 1;
            
        }
        else
        {
            builder_window2 = gtk_builder_new_from_file(caminho);
            free(caminho);
        }
    }
    else
    {
        builder_window2 = gtk_builder_new_from_file(caminho);
        free(caminho);
    }
    
    
    //free(caminho);
    
    window2 = GTK_WIDGET(gtk_builder_get_object(builder_window2, "window2"));
    g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    input_item_window2=GTK_WIDGET(gtk_builder_get_object(builder_window2,"input_item"));
    input_senha_window2=GTK_WIDGET(gtk_builder_get_object(builder_window2,"input_usuario"));
    input_nome_window2=GTK_WIDGET(gtk_builder_get_object(builder_window2,"input_senha"));
   botao_deletar=GTK_WIDGET(gtk_builder_get_object(builder_window2,"delete"));

    
    char *SENHA =senha_janela();
    printf("deu erro aqui%s\n",SENHA);
    char *dados=descriptografar(SENHA,id);
    const gchar *nome_item= strtok(dados,"|||");
    const gchar *senha=strtok(NULL,"|||");
   const  gchar *nome=strtok(NULL,"|||");
   //
    gtk_entry_set_text(GTK_ENTRY(input_item_window2),nome_item);
    gtk_entry_set_text(GTK_ENTRY(input_nome_window2),nome);
    gtk_entry_set_text(GTK_ENTRY(input_senha_window2),senha);

    
    botao_alterar=GTK_WIDGET(gtk_builder_get_object(builder_window2,"alterar"));
    g_signal_connect(botao_alterar,"clicked",G_CALLBACK(alterar),NULL);
    g_signal_connect(botao_deletar,"clicked",G_CALLBACK(deletar),NULL);

    gtk_widget_show_all(window2);
    gtk_main();
    //free(id);
    destruir(dados);

    
    return 0;
}
void alterar()
{
    //printf("cheguei\n");
    const char *nome=gtk_entry_get_text(GTK_ENTRY(input_nome_window2));
    const char *nome_item=gtk_entry_get_text(GTK_ENTRY(input_item_window2));
    const char *senha=gtk_entry_get_text(GTK_ENTRY(input_senha_window2));
    if(strlen(nome)==0 |strlen(nome_item)==0| strlen(senha)==0)
    {
        if(strlen(nome)==0)
        {
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_nome_window2),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
             gtk_entry_set_icon_tooltip_text(GTK_ENTRY(input_nome_window2),GTK_ENTRY_ICON_PRIMARY,"Aviso: Nome  em branco");
        }
        else
        {
             gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_nome_window2),GTK_ENTRY_ICON_PRIMARY,NULL);
        }
        if(strlen(nome_item)==0)
        {
                        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_item_window2),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
             gtk_entry_set_icon_tooltip_text(GTK_ENTRY(input_item_window2),GTK_ENTRY_ICON_PRIMARY,"Aviso: Nome do item em branco");
        }
        else
        {
                         gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_item_window2),GTK_ENTRY_ICON_PRIMARY,NULL);
        }
        if(strlen(senha)==0)
        {
                        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_senha_window2),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
             gtk_entry_set_icon_tooltip_text(GTK_ENTRY(input_nome_window2),GTK_ENTRY_ICON_PRIMARY,"Aviso: Senha em branco");
        }
        else{
                         gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_senha_window2),GTK_ENTRY_ICON_PRIMARY,NULL);
        }
        
    }
    else{
         char juntar_dados[strlen(nome)+strlen(nome_item)+strlen(senha)+10];
        char *SENHA=senha_janela();
        sprintf(juntar_dados,"%s|||%s|||%s",nome_item,senha,nome);
        init_cripto(SENHA,juntar_dados,1,id);
    }
   
    //free(id);
}
int deletar()
{
    delete_init(id);
    gtk_widget_destroy(window2);
    controle_de_fluxo();
    
    return 0;
}