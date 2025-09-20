#include <stdio.h>
#include "../include/diretorio.h"
#include <gtk/gtk.h>
#include "../include/init.h"
#include "../include/funcoes_main.h"
#include "../include/app_state.h"
#include "string.h"
#include <ctype.h>
#include "../include/login.h"
GtkWidget * window_login;
GtkBuilder * builder_login;
GtkWidget * confirmar_login;

char *senha2;
void confirmar_acao_login2()
{
    int quantidade_linha=retornar_quantidade_init();
    GtkWidget * usuario;
    GtkWidget * senha;
   
    usuario=GTK_WIDGET(gtk_builder_get_object(builder_login,"usuario"));
    senha=GTK_WIDGET(gtk_builder_get_object(builder_login,"senha"));
    const gchar* dados_senha=gtk_entry_get_text(GTK_ENTRY(senha));
    const gchar* dados_usuario= gtk_entry_get_text(GTK_ENTRY(usuario));
    

    if(strlen(dados_senha)==0 | strlen(dados_usuario)==0)
    {
        //char *SENHA;
        //snprintf(SENHA,500,"%s%s",dados_usuario,dados_senha);
         senha2=NULL;
        //printf("ola munGGGGGGdo %sdd\n",SENHA);
        //main_senha(NULL,0);

    }
    else
    {
        // Liberar memória anterior se existir
        if (senha2 != NULL) {
            free(senha2);
        }
        
        char senha1[strlen(dados_senha)+strlen(dados_usuario)+10];
       
        
        //printf("ola mundo %sdd",SENHA);
        
        if(quantidade_linha==0)
        {
            sprintf(senha1,"%s%s",dados_usuario,dados_senha);
            //AppState st;
            remover_espaco(senha1);
            senha2 = strdup(senha1); // Alocar e copiar a string
            
            //main_senha(&st);
            gtk_widget_destroy(window_login);
        }
        else
        {
            
            sprintf(senha1,"%s%s",dados_usuario,dados_senha);
            //AppState st;
            remover_espaco(senha1);
            senha2 = strdup(senha1); // Alocar e copiar a string
            //st.senha=senha;
            //SENHA=senha;
            //main_senha(&st);
            int *id=verificar_id();
            if(descriptografar(senha2,id[0])==NULL)
            {
                printf("ola nulo");
            }
            else
            {
                gtk_widget_destroy(window_login);
            }
            //descriptografar(SENHA,id[0]);
            
        }
        printf("agora quero ver %s",senha2);
    }
    
}
void confirmar_acao_login()
{
    int quantidade_linha=retornar_quantidade_init();
    GtkWidget * usuario;
    GtkWidget * senha;
   
    usuario=GTK_WIDGET(gtk_builder_get_object(builder_login,"usuario"));
    senha=GTK_WIDGET(gtk_builder_get_object(builder_login,"senha"));
    const gchar* dados_senha=gtk_entry_get_text(GTK_ENTRY(senha));
    const gchar* dados_usuario= gtk_entry_get_text(GTK_ENTRY(usuario));
    

    if(strlen(dados_senha)==0 | strlen(dados_usuario)==0)
    {
        //char *SENHA;
        //snprintf(SENHA,500,"%s%s",dados_usuario,dados_senha);
       
        //printf("ola munGGGGGGdo %sdd\n",SENHA);
        //main_senha(NULL,0);

    }
    else
    {
        char senha1[strlen(dados_senha)+strlen(dados_usuario)+10];
       
        
        printf("ola mundo dd");
        
        if(quantidade_linha==0)
        {
            
            sprintf(senha1,"%s%s",dados_usuario,dados_senha);
            //AppState st;
            
            senha2=senha1;
            
            //main_senha(&st);
            gtk_widget_destroy(window_login);
        }
        else
        {
            
            sprintf(senha1,"%s%s",dados_usuario,dados_senha);
            remover_espaco(senha1);
            //AppState st;
            senha2=senha1;
            printf("ola mundo %s",senha1);
            //st.senha=senha;
            //SENHA=senha;
            //main_senha(&st);
            int *id=verificar_id();
            //descriptografar(SENHA,id[0]);
            gtk_widget_destroy(window_login);
        }
        //printf("agora quero ver %s",senha2);
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
                //erro=1;
                //return erro;
            }
            else
                {
                    builder_login = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
                }
        }
    else
        {
            builder_login = gtk_builder_new_from_file(caminho);//depois mudar o arquivo .glade pra xml
        }
   free(caminho);
   
    
    window_login = GTK_WIDGET(gtk_builder_get_object(builder_login, "login"));
    g_signal_connect(window_login, "destroy", G_CALLBACK(gtk_main_quit), NULL);
 confirmar_login=GTK_WIDGET(gtk_builder_get_object(builder_login,"confirmar_login"));
 g_signal_connect(confirmar_login,"clicked",G_CALLBACK(confirmar_acao_login2),NULL);
        
    gtk_widget_show_all(window_login);
    gtk_main();
    printf("estou aqui em login %s",senha2); 
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