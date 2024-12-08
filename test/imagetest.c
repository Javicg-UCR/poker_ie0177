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

#include "include.h"

#define GLADE_FILE "./test/ImageTesting.glade"

// Declaración de la ventana principal

// Declaración del toplevel y containers -------------------------------------------

// Game window
GtkWidget *gameWindow;
GtkWidget *gameFixed;

// Start window
GtkWidget *startWindow;
GtkWidget *startFixed;

// Bet window
GtkWidget *betWindow;
GtkWidget *betFixed;

// Declaración de imágenes de cartas ---------------------------------

// Table
GtkImage *cardTable1;
GtkImage *cardTable2;
GtkImage *cardTable3;
GtkImage *cardTable4;
GtkImage *cardTable5;

// Hand
GtkImage *cardHand1;
GtkImage *cardHand2;

// Declaración de labels -------------------------------------------

// Game window
GtkWidget *labelPlayerID;
GtkWidget *labelMoney;
GtkWidget *labelBet;
GtkWidget *labelPot;
GtkWidget *labelHand;

// Start window
GtkWidget *labelTitle;

// Declaración de controladores ----------------------------------------------

// Game window
GtkWidget *buttonFold;
GtkWidget *buttonRaise;
GtkWidget *buttonCall;

// Bet Window
GtkWidget *buttonBet;
GtkWidget *entryBet;

// Declaración del builder ----------------------------------------------------

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

player players[4] = {
    {1, "Jugador 1", {1,0,0,0,0,0,0}, 0, 1000, false, 0},
    {2, "Jugador 2", {2,0,0,0,0,0,0}, 0, 1000, false, 1},
    {3, "Jugador 3", {3,0,0,0,0,0,0}, 0, 1000, false, 2},
    {4, "Jugador 4", {4,0,0,0,0,0,0}, 0, 1000, false, 3}
};

// static int global_i = 0;
static int current_player = 1;

// --------------------------------------------------------------------------------------------------------------------

// Funciones básicas

// --------------------------------------------------------------------------------------------------------------------

// Función para cambiar la imágen de una carta a base de un identificador numérico. 0 es la carta volteada.

void change_image(GtkImage * image, int id) 
{
    gtk_image_set_from_file(image, imageFilename[id]);
}

// Función para cambiar el texto de un label. Recibe el label por editar y un pointer al texto por poner

void change_label(GtkWidget * label, char *string)
{
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) string);
}

// Función para cambio de ventanas. Recibe la ventana vieja y la nueva

void change_window(GtkWidget * oldWindow,GtkWidget * newWindow)
{
    gtk_widget_hide(oldWindow);
    gtk_widget_show_all(newWindow);
}

// Función para hacer el setup de la mesa. Toma el ID numérico del jugador y coloca la mesa según la mano del jugador.

void change_board(int id)
{
    id --; // Las listas empiezan en 0

    // Update de la mesa
    change_image(cardHand1,players[id].hand[0]);
    change_image(cardHand2,players[id].hand[1]);
    change_image(cardTable1,players[id].hand[2]);
    change_image(cardTable2,players[id].hand[3]);
    change_image(cardTable3,players[id].hand[4]);
    change_image(cardTable4,players[id].hand[5]);
    change_image(cardTable5,players[id].hand[6]);

    // Update de los labels
    //change_label()
    //change_label()
    //change_label()
}


// -----------------------------------------------------------------------------

// Funciones de los botones

// -----------------------------------------------------------------------------

void on_buttonCall_clicked (GtkButton *b) // Call

{
    static int counter = 2;
    change_image(cardTable5,counter);
    counter++;
}

void on_buttonRaise_clicked (GtkButton *b) // Raise

{
    change_window(gameWindow,betWindow);
}

void on_buttonFold_clicked (GtkButton *b) // Fold

{
    static int dumb = 1;
    change_board(dumb);
    if (dumb < 4)
    {
        dumb++;
    }
    else
    {
        dumb = 1;
    }
}

void on_buttonStart_clicked(GtkButton *b) // Start
{
    change_window(startWindow,gameWindow);
    change_board(current_player);
}

void on_buttonBet_clicked(GtkButton *b) // Bet
{
    change_window(betWindow,gameWindow);
    current_player ++;
    change_board(current_player);
}

void on_entry_numeric_insert_text(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer user_data) {
    gchar *result = g_new(gchar, length + 1); // Temporary buffer for valid characters
    int j = 0;

    // Iterate through the input text
    for (int i = 0; i < length; i++) {
        if (isdigit(text[i])) { // Check if the character is a digit
            result[j++] = text[i];
        }
    }

    // Stop signal emission to prevent the original input
    g_signal_stop_emission_by_name(editable, "insert-text");

    // Insert only the valid numeric characters
    if (j > 0) {
        gtk_editable_insert_text(editable, result, j, position);
    }

    g_free(result); // Free temporary buffer
}

// -------------------------------------------------------------------------------

// Main

// --------------------------------------------------------------------------------

int main (int argc, char *argv[])
{
    gtk_init(&argc,&argv); // Procesamiento de los argumentos de línea de comandos en GTK

    builder = gtk_builder_new_from_file(GLADE_FILE); // Cargar el archivo glade 
    
    // Toplevels -------------------------------------------------------------------------------------

    // Creación del pointer de las ventanas
    gameWindow = GTK_WIDGET(gtk_builder_get_object(builder,"gameWindow"));
    startWindow = GTK_WIDGET(gtk_builder_get_object(builder,"startWindow"));
    betWindow = GTK_WIDGET(gtk_builder_get_object(builder,"betWindow"));

    // Tamaño correcto de gameWindow
    gtk_window_set_default_size(GTK_WINDOW(gameWindow), 1400, 700);
    gtk_window_set_resizable(GTK_WINDOW(gameWindow),FALSE);

    // Tamaño correcto de startWindow
    gtk_window_set_default_size(GTK_WINDOW(startWindow), 500, 250);
    gtk_window_set_resizable(GTK_WINDOW(startWindow),FALSE);

    // Conexión a las ventanas con destroy
    g_signal_connect(gameWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(startWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(startWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_builder_connect_signals(builder,NULL);

    // Containers --------------------------------------------------------------------------------------

    gameFixed = GTK_WIDGET(gtk_builder_get_object(builder,"gameFixed"));
    startFixed = GTK_WIDGET(gtk_builder_get_object(builder,"startFixed"));
    betFixed = GTK_WIDGET(gtk_builder_get_object(builder,"betFixed"));
    
    // Control & display (gameWindow) -------------------------------------------------------------------------------

    // Posicionamiento de labels

    labelPlayerID = GTK_WIDGET(gtk_builder_get_object(builder,"labelPlayerID"));
    labelMoney = GTK_WIDGET(gtk_builder_get_object(builder,"labelMoney"));
    labelPot = GTK_WIDGET(gtk_builder_get_object(builder,"labelPot"));
    labelBet = GTK_WIDGET(gtk_builder_get_object(builder,"labelBet"));
    labelHand = GTK_WIDGET(gtk_builder_get_object(builder,"labelHand"));
    labelTitle = GTK_WIDGET(gtk_builder_get_object(builder,"labelTitle"));

    // Posicionamiento de cartas

    // Table
    cardTable1 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable1"));
    cardTable2 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable2"));
    cardTable3 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable3"));
    cardTable4 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable4"));
    cardTable5 = GTK_IMAGE(gtk_builder_get_object(builder, "cardTable5"));

    // Hand
    cardHand1 = GTK_IMAGE(gtk_builder_get_object(builder, "cardHand1"));
    cardHand2 = GTK_IMAGE(gtk_builder_get_object(builder, "cardHand2"));

    // Control & display (betWindow) -------------------------------------------------------------------------------

    entryBet = GTK_WIDGET(gtk_builder_get_object(builder, "entryBet"));

    // Inicialización del programa ----------------------------------------------------

    gtk_widget_show_all(startWindow);

    gtk_main();

    return EXIT_SUCCESS;
}