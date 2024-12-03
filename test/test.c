//Archivo preliminar para explorar Glade


// Includes necesarios para desarollar en C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

// Se declaran pointers globales

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *button1;
GtkWidget *label1;
GtkBuilder *builder;

int main (int argc, char *argv[])
{
    gtk_init(&argc,&argv); // Procesamiento de los argumentos de línea de comandos en GTK

    builder = gtk_builder_new_from_file("GladeTest.glade");
    
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));

    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_builder_connect_signals(builder,NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder,"fixed1"));
    button1 = GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
    label1 = GTK_WIDGET(gtk_builder_get_object(builder,"label1"));

    gtk_widget_show(window);

    gtk_main();

    return EXIT_SUCCESS;
}

void on_button_clicked (GtkButton *b)

{
    gtk_label_set_text (GTK_LABEL(label1), (const gchar*) "Hello World");
}

