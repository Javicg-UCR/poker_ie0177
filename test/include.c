#include <stdio.h>
#include "include.h"

// Limpia el buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Reparte una carta única
int deal_reset(int check) {
    static int dealt[52] = {0};
    static int cardsDealt = 0;

    if (check == 1) { // Reiniciar mazo
        memset(dealt, 0, sizeof(dealt));
        cardsDealt = 0;
        return 0;
    }

    if (cardsDealt >= 52) {
        return -1; // No quedan cartas
    }

    int card;
    do {
        card = (rand() % 52) + 1;
    } while (dealt[card - 1] == 1);

    dealt[card - 1] = 1;
    cardsDealt++;
    return card;
}

// Repartir cartas a jugadores
void distributeCards(player players[], int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < 5; j++) {
            int card = deal_reset(0);
            if (card == -1) {
                printf("No hay más cartas disponibles.\n");
                exit(1);
            }
            players[i].hand[j] = card;
        }
    }
}

// Mostrar mano del jugador
void showPlayerHand(player *p) {
    printf("\n%s tiene las siguientes cartas:\n", p->name);
    for (int i = 0; i < 5; i++) { // Solo muestra las primeras 5 cartas
        printf("Carta %d: %d\n", i + 1, p->hand[i]);
    }
}

int cycle(player players[], int numPlayers, int cycle_by)
{
    for(int i = 0; i < numPlayers; i++)
    {
        players[i].cycle = ((numPlayers - cycle_by) + players[i].cycle) % numPlayers;
    }
    return 0;
}

int current_player(player players[], int i)
{
    for (int a = 0; a < 4; a++)
    {
        if (i == players[a].cycle)
        {
            return players[a].number - 1;
        }
    }
    return -1;
}

void bettingRound(player players[], int numPlayers, int *pot) {
    int highestBet = 0;
    int playerCounter = 0;

    printf("\n--- Inicia la ronda de apuestas ---\n");
    for (int i = 0; i < numPlayers; i++) {
        
        playerCounter = current_player(players,i);

        printf("\n i = %d, playerCounter = %d",i,playerCounter);

        if (players[playerCounter].fold) continue;

        printf("\n%s tiene $%d. Apuesta actual: $%d\n", players[playerCounter].name, players[playerCounter].money, highestBet);
        printf("1. Subir apuesta\n2. Igualar y pasar\n3. Retirarse\nOpción: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida. Intenta de nuevo.\n");
            clearBuffer();
            i--;
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: {
                int raise;
                printf("¿Cuánto quieres subir? ");
                if (scanf("%d", &raise) != 1 || raise <= 0 || raise > players[playerCounter].money) {
                    printf("Cantidad inválida. Intenta de nuevo.\n");
                    clearBuffer();
                    i--;
                    continue;
                }
                clearBuffer();
                highestBet += raise;
                players[playerCounter].money -= highestBet;
                *pot += highestBet;
                cycle(players,numPlayers,i);    
                i = 0;
                break;
            }
            case 2:
                if (players[playerCounter].money >= highestBet) {
                    players[playerCounter].money -= highestBet;
                    *pot += highestBet;
                } else {
                    printf("No tienes suficiente dinero. Te retiras automáticamente.\n");
                    players[playerCounter].fold = true;
                }
                break;
            case 3:
                players[playerCounter].fold = true;
                printf("%s se ha retirado.\n", players[playerCounter].name);
                break;
            default:
                printf("Opción inválida. Intenta de nuevo.\n");
                i--;
        }
    }
}

// Mostrar ganador
void showWinner(player players[], int numPlayers, int pot) {
    int bestValue = -1, winnerIndex = -1;

    for (int i = 0; i < numPlayers; i++) {
        if (!players[i].fold && players[i].handValue > bestValue) {
            bestValue = players[i].handValue;
            winnerIndex = i;
        }
    }

    if (winnerIndex != -1) {
        printf("\nEl ganador es %s con $%d adicionales. ¡Felicidades!\n", players[winnerIndex].name, pot);
        players[winnerIndex].money += pot;
    } else {
        printf("Todos los jugadores se retiraron. ¡No hay ganador!\n");
    }
}

// Menú interactivo
void menu(player players[], int numPlayers) {
    int option;
    int pot = 0;

    do {
        printf("\n=== Menú ===\n");
        printf("1. Repartir cartas\n2. Mostrar manos\n3. Evaluar manos\n4. Ronda de apuestas\n5. Mostrar ganador\n6. Salir\nOpción: ");
        if (scanf("%d", &option) != 1) {
            printf("Entrada inválida. Intenta de nuevo.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (option) {
            case 1:
                deal_reset(1); // Reiniciar el mazo
                distributeCards(players, numPlayers);
                printf("Cartas repartidas.\n");
                break;
            case 2:
                for (int i = 0; i < numPlayers; i++) {
                    showPlayerHand(&players[i]);
                }
                break;
            case 4:
                bettingRound(players, numPlayers, &pot);
                break;
            case 5:
                showWinner(players, numPlayers, pot);
                break;
            case 6:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida. Intenta de nuevo.\n");
        }
    } while (option != 6);
}