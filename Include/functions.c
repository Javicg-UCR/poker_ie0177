// Include de funciones necesarias para el juego de poker

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int deal_reset(int check)
{
    // Check == 1 -> Reset
    // Check != 1 -> Deal

    // Declaración del array para las cartas utilizadas
    // Asegura que no se repitan
    static int dealt[52];
    
    // Random seed
    srand(time(NULL));

    int card; // Inicializar card

    // ---------------------------------------------------
    
    if (check == 1) // Ressetear el deck a 0s
    {
        for (int i = 0; i == 51; i++)
        {
            dealt[i] = 0;
        }
        return 0;
    }
    check = 0; // Resettear check, se va a utilizar luego

    // -------------------------------------------------------

    if (dealt[52] != 0) // Todas las cartas han salido
    {
        return -1;
    }
    
    while (check == 0) 
    {
        card = (rand() % 52 ) + 1; // Generar una carta

        check = 1; // Variable se cambiará si se encuentra la carta
        
        for (int i = 0; i < 52; i++) // Revisar si está en las cartas previamente dadas
        {
            if (dealt[i] == card)
            {
                check == 0; // Se encontró la carta (otro loop)
            }
        }
    }

    for (int i = 0; i < 52; i++) // Añadir la carta al array final del array y devolverla
    {
        if (dealt[i] == 0)
        {
            dealt[i] = card;
            return card;
        }
    }
    
    return -1; // Error: No se añadió la carta
}