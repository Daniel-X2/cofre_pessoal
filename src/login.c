#include <stdio.h>
#include "../include/diretorio.h"
#include <gtk/gtk.h>
#include "../include/init.h"
#include "../include/funcoes_main.h"

#include "string.h"
#include <ctype.h>
#include "../include/login.h"
GtkWidget * window_login;
GtkBuilder * builder_login;
GtkWidget * confirmar_login;
GtkWidget * usuario;
GtkWidget * senha;
const gchar* dados_usuario;
const gchar* dados_senha;

char *senha2;
GtkWidget * confirm;
int janela_confirmar()
{
    gtk_widget_destroy(confirm);
    gtk_window_close(GTK_WINDOW(confirm));
    

    if(strlen(dados_senha)==0 | strlen(dados_usuario)==0)
    {
       
        senha2=NULL;
        
    }
    else
    {
        //gtk_entry_set_icon_from_icon_name(GTK_ENTRY(usuario),GTK_ENTRY_ICON_PRIMARY,NULL);
        //gtk_entry_set_icon_from_icon_name(GTK_ENTRY(senha),GTK_ENTRY_ICON_PRIMARY,NULL);
        // Liberar memória anterior se existir
        if (senha2 != NULL) {
            free(senha2);
        }
        
        char senha1[strlen(dados_senha)+strlen(dados_usuario)+10];
       
        

    sprintf(senha1,"%s%s",dados_usuario,dados_senha);
            //AppState st;
            remover_espaco(senha1);
            senha2 = strdup(senha1); // Alocar e copiar a string
            
            //main_senha(&st);
            gtk_widget_destroy(window_login);
                return 0;
            }
            //printf("ola mundo da senha %s\n",senha2);        
}
void confirmar_acao_login2()
{
    
   

    dados_senha=gtk_entry_get_text(GTK_ENTRY(senha));
    dados_usuario= gtk_entry_get_text(GTK_ENTRY(usuario));
    
    
    
        if(strlen(dados_senha)==0 | strlen(dados_usuario)==0)
    {
       
        senha2=NULL;
        
    }
    else
    {
        //gtk_entry_set_icon_from_icon_name(GTK_ENTRY(usuario),GTK_ENTRY_ICON_PRIMARY,NULL);
        //gtk_entry_set_icon_from_icon_name(GTK_ENTRY(senha),GTK_ENTRY_ICON_PRIMARY,NULL);
        // Liberar memória anterior se existir
        if (senha2 != NULL) {
            free(senha2);
        }
        
        char senha1[strlen(dados_senha)+strlen(dados_usuario)+10];
       
        
        //printf("ola mundo %sdd",SENHA);
        int quantidade_linha=retornar_quantidade_init();
        if(quantidade_linha==0)
        {
            confirm=GTK_WIDGET(gtk_builder_get_object(builder_login,"janela_confirmacao"));
            GtkWidget * botao_confirmar=GTK_WIDGET(gtk_builder_get_object(builder_login,"botao_confirmar"));
            g_signal_connect(botao_confirmar,"clicked",G_CALLBACK(janela_confirmar),NULL);
            gtk_widget_show_all(confirm);
            //gtk_main();

            //free(quantidade_linha);
             
           
            
        }
        else
        {
            
            sprintf(senha1,"%s%s",dados_usuario,dados_senha);
            //AppState st;
            remover_espaco(senha1);
            senha2 = strdup(senha1); // Alocar e copiar a string
        
            unsigned int *id=verificar_id();
            char * verificar=descriptografar(senha2,id[0]);
            //free(quantidade_linha);
            
            if(verificar==NULL)
            {
                
                gtk_entry_set_icon_from_icon_name(GTK_ENTRY(usuario),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-error");
                gtk_entry_set_icon_from_icon_name(GTK_ENTRY(senha),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-error");

                
            }
            else
            {
                gtk_widget_destroy(window_login);
            }
            free(id);
            destruir(verificar);
        }
    }
    
}

    
    
char* login_main(int verificar)
{
    
    char *caminho=encontrar_diretorio("./layout/tela_login.glade");
    
    if (!caminho)
        {
            fprintf(stderr, "segunda tentativa!\n");
            free(caminho);
            char *caminho=encontrar_diretorio("../layout/tela_login.glade");
            if(!caminho)
            {

                fprintf(stderr, "arquivo nao encontrado!\n");
                fprintf(stderr, "tente mudar a localizaçao da pasta layout!\n");
               free(caminho);
            }
            else
                {
                    builder_login = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
                    free(caminho);
                }
        }
    else
        {
            builder_login = gtk_builder_new_from_file(caminho);
            free(caminho);
            //depois mudar o arquivo .glade pra xml
        }
   
   usuario=GTK_WIDGET(gtk_builder_get_object(builder_login,"usuario"));
    senha=GTK_WIDGET(gtk_builder_get_object(builder_login,"senha"));
    g_timeout_add(500,interatividade,NULL);
   
    window_login = GTK_WIDGET(gtk_builder_get_object(builder_login, "login"));
    g_signal_connect(window_login, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    confirmar_login=GTK_WIDGET(gtk_builder_get_object(builder_login,"confirmar_login"));
    g_signal_connect(confirmar_login,"clicked",G_CALLBACK(confirmar_acao_login2),NULL);
        
    gtk_widget_show_all(window_login);
     
    gtk_main();
    
   return senha2;
    //return erro;
}

void remover_espaco(char * str)
{
    int i,j=0;
    for(i=0;str[i]!='\0';i++)
    {
        if(str[i]!=' ')
        {
            str[j++]=str[i];
        }
    }
    str[j]='\0';   
}
gboolean interatividade(gpointer nulo)
{
    dados_senha=gtk_entry_get_text(GTK_ENTRY(senha));
    dados_usuario= gtk_entry_get_text(GTK_ENTRY(usuario));
       
       
        if(strlen(dados_senha)==0)
        {
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(senha),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
            gtk_entry_set_icon_tooltip_text(GTK_ENTRY(senha),GTK_ENTRY_ICON_PRIMARY,"Aviso: Senha em branco");
            
        }
        else
        {
        
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(senha),GTK_ENTRY_ICON_PRIMARY,NULL);
        }
        if(strlen(dados_usuario)==0)
        {
             gtk_entry_set_icon_from_icon_name(GTK_ENTRY(usuario),GTK_ENTRY_ICON_PRIMARY,"gtk-dialog-warning");
             gtk_entry_set_icon_tooltip_text(GTK_ENTRY(usuario),GTK_ENTRY_ICON_PRIMARY,"Aviso: Usuario em branco");
            }      
        
        else
        {
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(usuario),GTK_ENTRY_ICON_PRIMARY,NULL);
        }
    
    
    
    return TRUE;
}
