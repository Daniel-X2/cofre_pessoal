#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/diretorio.h"
#include "../include/init.h"
#include <string.h>
#include "../include/teste.h"


//#include "../include/banco_de_dados.h"
//#include "../include/crypto.h"
char *SENHA="senha do maluco";
GtkWidget * confirmar;
GtkWidget * cancelar;
GtkBuilder * builder;
GtkWidget * window;
GtkWidget * senhas;
GtkWidget * input_nome;
GtkWidget * input_nome_item;
GtkWidget * input_senha;
GtkWidget * janela_note;
void laco();

void entry_janela1();

void botao_senhas(const char *nome_item,int id);
void conectar_botoes();
void confirmar_entrada();
void botao_lixeira();
void botao_notas();
void cancelar_entrada();
void get_object_gtk();
void separar( char *dados);
int main(int argc, char *argv[]) {
    
    
    
    gtk_init(&argc, &argv);
    iniciar_banco();
  

    
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
void botao_senhas(const char *nome_item,int id)
{
    //gtk_notebook_set_current_page(GTK_NOTEBOOK(janela_note),0);
    GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder, "container"));
    // Criar um botão novo
    const gchar *teste=nome_item;
    printf("%s",nome_item);
    GtkWidget *btn = gtk_button_new_with_label(teste);
    char *id_button;

    //sprintf(id_button,"%s",id);/////////////


    gtk_widget_set_name(btn,"id_button");


    // Adicionar no box
    gtk_box_pack_start(GTK_BOX(box), btn, FALSE, FALSE, 1);
    gtk_widget_show_all(box);
}
void entry_janela1()
{
    const gchar *nome_item=gtk_entry_get_text(GTK_ENTRY(input_nome_item));
    const gchar *senha=gtk_entry_get_text(GTK_ENTRY(input_senha));
    const gchar *nome=gtk_entry_get_text(GTK_ENTRY(input_nome));
    
    
    char dados[100];
    sprintf(dados,"%s|||%s|||%s",nome_item,senha,nome);
    
    //init_cripto(SENHA,dados);
    
}
void get_object_gtk()
{
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

    janela_note=GTK_WIDGET(gtk_builder_get_object(builder,"gtknotebook"));
    
    confirmar=GTK_WIDGET(gtk_builder_get_object(builder,"confirmar"));
    cancelar=GTK_WIDGET(gtk_builder_get_object(builder,"cancelar"));
    
    senhas=GTK_WIDGET(gtk_builder_get_object(builder,"botao_senha"));
    
    input_nome=GTK_WIDGET(gtk_builder_get_object(builder,"input_usuario"));
    input_nome_item=GTK_WIDGET(gtk_builder_get_object(builder,"input_item"));
    input_senha=GTK_WIDGET(gtk_builder_get_object(builder,"input_senha"));

}   
void conectar_botoes()
{
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(senhas,"clicked",G_CALLBACK(laco),NULL);
    g_signal_connect(confirmar,"clicked",G_CALLBACK(confirmar_entrada),NULL);
    g_signal_connect(cancelar,"clicked",G_CALLBACK(cancelar_entrada),NULL);
}
void separar( char *dados)
{
    
    char *nome_item= strtok(dados,"|||");
    char *senha=strtok(NULL,"|||");
    char *nome=strtok(NULL,"|||");

    printf("ola mano %s %s %s\n",nome,senha,nome_item);
    
    
}
void laco()
{
    unsigned int quantidade_de_linhas=verificar_quantidade();
    
    for (int c =1;c<=quantidade_de_linhas;c++)
    {
        
        const char *n3=descriptografar(SENHA,c);
        char n2[1000];
        sprintf(n2,"%s",n3);
        
        botao_senhas(n2,c);
    }
}
void cancelar_entrada()
{
    gtk_entry_set_text(GTK_ENTRY(input_nome),"");
    gtk_entry_set_text(GTK_ENTRY(input_nome_item),"");
    gtk_entry_set_text(GTK_ENTRY(input_senha),"");
}
void confirmar_entrada()
{
    const char *nome=gtk_entry_get_text(GTK_ENTRY(input_nome));
    const char *nome_item=gtk_entry_get_text(GTK_ENTRY(input_nome_item));
    const char *senha=gtk_entry_get_text(GTK_ENTRY(input_senha));
    char juntar_dados[strlen(nome)+strlen(nome_item)+strlen(senha)+10];

    sprintf(juntar_dados,"%s|||%s|||%s",nome_item,nome,senha);
    init_cripto(SENHA,juntar_dados,0,0);
    
}