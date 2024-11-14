//Archivo preliminar para explorar Glade


// Includes necesarios para desarollar en C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk3.4/gtk.h>
#include <gtk3.4/gtkx.h>
#include <math.h>
#include <ctype.h>

// Se declaran pointers globales

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *button1;
GtkWidget *label1;
GtkWidget *builder;

int main (int argc, char *argv[])
{
    gtk_init(&argc,&argv); // Procesamiento de los argumentos de línea de comandos en GTK

    builder = gtk_builder_new_from_file("part1.glade");
    
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));

    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
}