/**
 * @file main.c
 * @brief Arquivo principal do cofre pessoal. Responsável por inicializar a interface gráfica, conectar sinais e manipular widgets usando GTK.
 */

#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/diretorio.h"
#include "../include/init.h"
#include <string.h>
#include "../include/janela.h"
#include <stdlib.h>
#include "../include/funcoes_main.h"
#include "../include/login.h"

/**
 * @var SENHA
 * @brief Senha mestra utilizada para criptografia e descriptografia dos dados.
 */


// Variáveis globais para widgets e objetos GTK
int n5=0;
char*SENHA=NULL;
GtkWidget * confirmar;        ///< Botão de confirmação
GtkWidget * cancelar;         ///< Botão de cancelamento
GtkBuilder * builder;         ///< Builder para carregar o layout Glade
GtkWidget * window;           ///< Janela principal
GtkWidget * botao_senhas;     ///< Botão para acessar senhas
GtkWidget * input_nome;       ///< Campo de entrada para nome do usuário
GtkWidget * input_nome_item;  ///< Campo de entrada para nome do item
GtkWidget * input_senha;      ///< Campo de entrada para senha
GtkWidget * janela_note;      ///< Notebook (abas)
GtkWidget * container;        ///< Container para os widgets de itens
GtkWidget * botao_atualizar;  ///< Botão para atualizar lista
GtkWidget * box;              ///< Box para empacotar widgets
GtkWidget * botao_lista;
/**
 * @brief Função principal. Inicializa GTK, carrega interface, conecta sinais e exibe a janela.
 */
int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);
    iniciar_banco();

    char *caminho=encontrar_diretorio("./layout/interface.glade");
    int total;
    //int id=

    //int linha=retornar_quantidade_init();
    
    if (!caminho)
        {
            fprintf(stderr, "segunda tentativa!\n");
            free(caminho);
            char *caminho=encontrar_diretorio("../layout/interface.glade");
            if(!caminho)
            {
                free(caminho);
                fprintf(stderr, "arquivo nao encontrado!\n");
                fprintf(stderr, "tente mudar a localizaçao da pasta layout!\n");
                return 1;
            }
            else
                {
                    builder = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
                    free(caminho);
                    fechar_banco_init();
                }
        }
    else
        {
            builder = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
            free(caminho);
        }
    //builder = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
    int total_linha=retornar_quantidade_init();
    get_object_gtk();
    
    
    if(TRUE)
    {
        SENHA=login_main(0);
        int linha=retornar_quantidade_init();
        unsigned int* id=verificar_id();
        //printf("ola mano %s \n",SENHA);
        
        
        if(SENHA==NULL )
        { 
            gtk_widget_destroy(window);
            //free(id);
        }
        else if(total_linha==0 )//| 
        {
            
            //free(id);
            controle_de_fluxo();
            free(caminho);
            box = GTK_WIDGET(gtk_builder_get_object(builder, "container"));
            get_object_gtk();
    
            //int *n1=verificar_quantidade();
    
            conectar_botoes();
            gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),0);
    
            ///adicionar_widget();

            gtk_widget_show_all(window);
            gtk_main();
            
            
            return 1;
        }
        else if(descriptografar(SENHA,id[0])!=NULL)
        {
            char * verificar_senha=descriptografar(SENHA,id[0]);
            //free(id);
            controle_de_fluxo();
            free(caminho);
            box = GTK_WIDGET(gtk_builder_get_object(builder, "container"));
            get_object_gtk();
    
            //int *n1=verificar_quantidade();
    
            conectar_botoes();
            gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),0);
            
            ///adicionar_widget();
            
            gtk_widget_show_all(window);
            gtk_main();
            //free(id);

            return 1;
        }
        //destruir(verificar_senha);
    }
    fechar_banco_init();
    free(SENHA);
   
    
}

void acao_senha()
{
    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),0);
}
 
void atualizar_lista(char *nome_item,int id)
{
    
    char *nome =separar(nome_item);
    
    const gchar *titulo=nome;
    GtkWidget *btn = gtk_button_new_with_label(titulo);
    
    char id_button[200];
    sprintf(id_button,"%i",id);
    int *pid = malloc(sizeof(int));
    *pid = id;
    g_signal_connect(btn,"clicked",G_CALLBACK(window_dados),pid);
    gtk_widget_set_name(btn,id_button);
    gtk_box_pack_start(GTK_BOX(box), btn, FALSE, FALSE, 1);
    //free(pid);
    
    
}

void get_object_gtk()
{
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    janela_note=GTK_WIDGET(gtk_builder_get_object(builder,"gtknotebook"));
    confirmar=GTK_WIDGET(gtk_builder_get_object(builder,"confirmar"));
    cancelar=GTK_WIDGET(gtk_builder_get_object(builder,"cancelar"));
    botao_atualizar=GTK_WIDGET(gtk_builder_get_object(builder,"botao_atualizar"));
    botao_senhas=GTK_WIDGET(gtk_builder_get_object(builder,"botao_senha"));
    input_nome=GTK_WIDGET(gtk_builder_get_object(builder,"input_usuario"));
    input_nome_item=GTK_WIDGET(gtk_builder_get_object(builder,"input_item"));
    input_senha=GTK_WIDGET(gtk_builder_get_object(builder,"input_senha"));
    botao_lista=GTK_WIDGET(gtk_builder_get_object(builder,"lista"));
    container=GTK_WIDGET(gtk_builder_get_object(builder,"container"));
}   

void conectar_botoes()
{

    //faz as conexoes entre os botoes e funçoes
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(botao_atualizar,"clicked",G_CALLBACK(controle_de_fluxo),NULL);
    g_signal_connect(confirmar,"clicked",G_CALLBACK(confirmar_entrada),NULL);
    g_signal_connect(cancelar,"clicked",G_CALLBACK(cancelar_entrada),NULL);
    g_signal_connect(botao_lista,"clicked",G_CALLBACK(acao_nota),NULL);
    g_signal_connect(botao_senhas,"clicked",G_CALLBACK(acao_senha),NULL);
}//acao_senha
 char* separar( char *dados)
{
    //faz retorna o nome do item pra ser colocado como titulo no widget
    char *nome_item= strtok(dados,"|||");
    char *senha=strtok(NULL,"|||");
    char *nome=strtok(NULL,"|||");

    return nome_item;
    
    
}
void destruir_filhos(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(widget);
}

void cancelar_entrada()
{
    //quando o usuario chama a funçao limpa a entrada
    gtk_entry_set_text(GTK_ENTRY(input_nome),"");
    gtk_entry_set_text(GTK_ENTRY(input_nome_item),"");
    gtk_entry_set_text(GTK_ENTRY(input_senha),"");
}
int confirmar_entrada()
{
    //quando chama a funçao as variaveis pegam os valores do entry 
    //faz uma junçao e criptografa
    const char *nome=gtk_entry_get_text(GTK_ENTRY(input_nome));
    const char *nome_item=gtk_entry_get_text(GTK_ENTRY(input_nome_item));
    const char *senha=gtk_entry_get_text(GTK_ENTRY(input_senha));
    unsigned int *lista_de_id=verificar_id();
    if(strlen(senha)==0 | strlen(nome)==0 | strlen(nome_item)==0)
    {
        if(strlen(nome)==0)
    {
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_nome),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
        gtk_entry_set_icon_tooltip_text(GTK_ENTRY(input_nome),GTK_ENTRY_ICON_PRIMARY,"Aviso: Nome em branco");
    }
    else{
         gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_nome),GTK_ENTRY_ICON_PRIMARY,NULL);
    }
    if (strlen(nome_item)==0)
    {
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_nome_item),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
        gtk_entry_set_icon_tooltip_text(GTK_ENTRY(input_nome_item),GTK_ENTRY_ICON_PRIMARY,"Aviso: Nome do Item em branco");
    }
    else{
         gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_nome_item),GTK_ENTRY_ICON_PRIMARY,NULL);
    }
    
    if(strlen(senha)==0)
    {
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_senha),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
        gtk_entry_set_icon_tooltip_text(GTK_ENTRY(input_senha),GTK_ENTRY_ICON_PRIMARY,"Aviso: Senha em branco");
    }
    
    else{
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_senha),GTK_ENTRY_ICON_PRIMARY,NULL);
    }
   
    return 1;
}
    else{
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_senha),GTK_ENTRY_ICON_PRIMARY,NULL);
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_nome_item),GTK_ENTRY_ICON_PRIMARY,NULL);
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(input_nome),GTK_ENTRY_ICON_PRIMARY,NULL);
    }
    
    
    
    char juntar_dados[strlen(nome)+strlen(nome_item)+strlen(senha)+10];

    sprintf(juntar_dados,"%s|||%s|||%s",nome_item,nome,senha);
   
    
    init_cripto(SENHA,juntar_dados,0,1);
    
    
   
    free(lista_de_id);
    cancelar_entrada();
    //destruir(dados);
    adicionar_na_lista();
  

     
}

gboolean adicionar_widget(gpointer verificador)
{
    /* o gtk_container_foreach ele sai destruindo todos os widgets do container
    depois e pego a quantidade de linhas e feito um for pra descriptografar 
    e adicionar no container com tudo atualizado e depois exibe tudo
    */

    unsigned int *lista_de_id=verificar_id();
    int total_linha=retornar_quantidade_init();
    if (total_linha==0 )
    {
        return FALSE;
    }
    else if(n5>=total_linha)
    {
        return FALSE;
    }
   
    char *dados=descriptografar(SENHA,lista_de_id[n5]);
   

    char n2[strlen(dados)+10];
    sprintf(n2,"%s",dados);
    
    atualizar_lista(n2,lista_de_id[n5]);
    printf("aqui no adicionar widget %i\n",lista_de_id[n5]);
    n5++;
    destruir(dados);
    
    free(lista_de_id);
    gtk_widget_show_all(box);
    return TRUE;
}
void controle_de_fluxo()
{
    n5=0;
    gtk_container_foreach(GTK_CONTAINER(container), destruir_filhos, NULL);
    g_timeout_add(500,adicionar_widget,NULL);
}
void acao_nota()
{
    gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),2);
}
char* senha_janela()
{
    return SENHA;
}
void adicionar_na_lista()
{
    unsigned int *id=verificar_id();
    //int total_linha=retornar_quantidade_init();
    char *dados=descriptografar(SENHA,id[n5]);

    char n2[strlen(dados)+10];
    sprintf(n2,"%s",dados);
    atualizar_lista(n2,id[n5]);
    //printf("aqui no adicionar widget %i\n",id[n5]);
    n5++;
    //destruir(dados);

    gtk_widget_show_all(box);
    
}   