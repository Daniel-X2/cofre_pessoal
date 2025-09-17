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
void alterar();

    GtkWidget * window2;
    GtkBuilder * builder_window2;
    GtkWidget * input_item_window2;
    GtkWidget * input_nome_window2;
    GtkWidget * input_senha_window2;
    GtkWidget * botao_alterar;
int id;



int window_dados(GtkWidget *widget, gpointer user_data) {
    id = *((int*)user_data);

    char *caminho=encontrar_diretorio("./layout/atualizar_dados.glade");
    if (!caminho)
    {
        fprintf(stderr, "Arquivo não encontrado!\n");
        return 0;
    }
    
    builder_window2 = gtk_builder_new_from_file(caminho);
    free(caminho);
    
    window2 = GTK_WIDGET(gtk_builder_get_object(builder_window2, "window2"));
    g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    input_item_window2=GTK_WIDGET(gtk_builder_get_object(builder_window2,"input_item"));
    input_senha_window2=GTK_WIDGET(gtk_builder_get_object(builder_window2,"input_usuario"));
    input_nome_window2=GTK_WIDGET(gtk_builder_get_object(builder_window2,"input_senha"));
   
    

    char *dados=descriptografar("senha do maluco",id);
    const gchar *nome_item= strtok(dados,"|||");
    const gchar *senha=strtok(NULL,"|||");
   const  gchar *nome=strtok(NULL,"|||");
   //
    gtk_entry_set_text(GTK_ENTRY(input_item_window2),nome_item);
    gtk_entry_set_text(GTK_ENTRY(input_nome_window2),nome);
    gtk_entry_set_text(GTK_ENTRY(input_senha_window2),senha);

    
    botao_alterar=GTK_WIDGET(gtk_builder_get_object(builder_window2,"alterar"));
    g_signal_connect(botao_alterar,"clicked",G_CALLBACK(alterar),NULL);
    
   
    
    
    
    
   
    
    
    gtk_widget_show_all(window2);
    gtk_main();
    //free(id);
    free(dados);

    return 1;
}
void alterar()
{
    printf("cheguei\n");
    const char *nome=gtk_entry_get_text(GTK_ENTRY(input_nome_window2));
    const char *nome_item=gtk_entry_get_text(GTK_ENTRY(input_item_window2));
    const char *senha=gtk_entry_get_text(GTK_ENTRY(input_senha_window2));
    char juntar_dados[strlen(nome)+strlen(nome_item)+strlen(senha)+10];

    sprintf(juntar_dados,"%s|||%s|||%s",nome_item,senha,nome);
    init_cripto("senha do maluco",juntar_dados,1,id);
    //free(id);
}