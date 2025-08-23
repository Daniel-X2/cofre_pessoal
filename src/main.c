#include <gtk/gtk.h>
#include <stdio.h>

void config_init(GtkWidget *window);
int botao();
int main(int argc, char *argv[]) {
    
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *buttom; 

    gtk_init(&argc, &argv);
 //config_init(window);
    builder = gtk_builder_new_from_file("");//depois mudar o arquivo .glade pra xml
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    
    //int **ponteiro=window;
    //config_init(window);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //printf("ola mundo");
    gtk_widget_show_all(window);
    gtk_main();
    
   

    return 0;
}
void config_init(GtkWidget *window)
{   
    gtk_window_set_default_size(GTK_WINDOW(window),400,400);
}
int botao()
{

    return 1;

}













