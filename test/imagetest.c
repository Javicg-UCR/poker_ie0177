//Archivo preliminar para explorar imágenes

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

#define GLADE_FILE "./test/ImageTesting.glade"

// Se declaran pointers globales

GtkWidget *window;
GtkWidget *fixed1;

// Card image declarations
GtkImage *cardTable1;
GtkImage *cardTable2;
GtkImage *cardTable3;
GtkImage *cardTable4;
GtkImage *cardTable5;

GtkImage *cardHand1;
GtkImage *cardHand2;

// Declaración del builder

GtkBuilder *builder;

// Lista para obtener filenames por índice

char imageFilename[53][30] = {"./Assets/cardBack_red5.png",
"./Assets/cardClubs2.png","./Assets/cardSpades2.png","./Assets/cardHearts2.png","./Assets/cardDiamonds2.png",
"./Assets/cardClubs3.png","./Assets/cardSpades3.png","./Assets/cardHearts3.png","./Assets/cardDiamonds3.png",
"./Assets/cardClubs4.png","./Assets/cardSpades4.png","./Assets/cardHearts4.png","./Assets/cardDiamonds4.png",
"./Assets/cardClubs5.png","./Assets/cardSpades5.png","./Assets/cardHearts5.png","./Assets/cardDiamonds5.png",
"./Assets/cardClubs6.png","./Assets/cardSpades6.png","./Assets/cardHearts6.png","./Assets/cardDiamonds6.png",
"./Assets/cardClubs7.png","./Assets/cardSpades7.png","./Assets/cardHearts7.png","./Assets/cardDiamonds7.png",
"./Assets/cardClubs8.png","./Assets/cardSpades8.png","./Assets/cardHearts8.png","./Assets/cardDiamonds8.png",
"./Assets/cardClubs9.png","./Assets/cardSpades9.png","./Assets/cardHearts9.png","./Assets/cardDiamonds9.png",
"./Assets/cardClubs10.png","./Assets/cardSpades10.png","./Assets/cardHearts10.png","./Assets/cardDiamonds10.png",
"./Assets/cardClubsJ.png","./Assets/cardSpadesJ.png","./Assets/cardHeartsJ.png","./Assets/cardDiamondsJ.png",
"./Assets/cardClubsQ.png","./Assets/cardSpadesQ.png","./Assets/cardHeartsQ.png","./Assets/cardDiamondsQ.png",
"./Assets/cardClubsK.png","./Assets/cardSpadesK.png","./Assets/cardHeartsK.png","./Assets/cardDiamondsK.png",
"./Assets/cardClubsA.png","./Assets/cardSpadesA.png","./Assets/cardHeartsA.png","./Assets/cardDiamondsA.png",
};

int change_image(GtkImage * image,int id) // Función para cambiar una carta a base de un índice. 0 es la carta vuelta.
{
    gtk_image_set_from_file(image, imageFilename[id]);
    return 0;
}

int main (int argc, char *argv[])
{
    gtk_init(&argc,&argv); // Procesamiento de los argumentos de línea de comandos en GTK

    builder = gtk_builder_new_from_file(GLADE_FILE); // Cargar el archivo glade 
    
    // Window -------------------------------------------------------------------------------------

    window = GTK_WIDGET(gtk_builder_get_object(builder,"window")); // Crear la ventana y conectarla

    

    // Tamaño correcto de ventana
    //gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
    //gtk_window_set_resizable (GTK_WINDOW(window)), FALSE );

    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL); // Conexión a la ventana con destroy

    //--------------------------------------------------------

    gtk_builder_connect_signals(builder,NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder,"fixed1"));

    // Posicionamiento de cartas

    // Table
    cardTable1 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable1"));
    cardTable2 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable2"));
    cardTable3 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable3"));
    cardTable4 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable4"));
    cardTable5 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable5"));

    // Hand

    cardHand1 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable1"));
    cardHand2 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable2"));


    // Cambio de imágenes
    change_image(cardTable1,52);


    // Visibility
    gtk_widget_show_all(window);

    gtk_main();

    return EXIT_SUCCESS;
}