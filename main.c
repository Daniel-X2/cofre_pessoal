#include <gtk/gtk.h>
#include <stdio.h>

void config_init(int argc, char *argv[]);
int botao();
int main(int argc, char *argv[]) {
    
    config_init(argc,argv);

    //buttom=GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
    
   

    return 0;
}
void config_init(int argc, char *argv[])
{   
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *buttom; 
    
    gtk_init(&argc, &argv);
 //config_init(window);
    builder = gtk_builder_new_from_file("interface.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    
    gtk_window_set_default_size(GTK_WINDOW(window),200,200);
     g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //printf("ola mundo");
    gtk_widget_show_all(window);
    gtk_main();
}
int botao()
{
    
    return 1;

}

























