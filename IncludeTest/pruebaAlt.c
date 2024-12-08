#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Estructura de jugador
typedef struct {
    int number;
    char name[30];
    int hand[7]; // Mano del jugador (5 personales + 2 comunitarias)
    int handValue; // Valor de la mano evaluada
    int money; // Dinero del jugador
    bool fold; // true si el jugador se retiró
} player;

// Prototipos
void clearBuffer();
int deal_reset(int check);
void distributeCards(player players[], int numPlayers);
void evaluateHand(player *p);
void showPlayerHand(player *p);
void bettingRound(player players[], int numPlayers, int *pot);
void showWinner(player players[], int numPlayers, int pot);
void menu(player players[], int numPlayers);

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

// Ronda de apuestas
void bettingRound(player players[], int numPlayers, int *pot) {
    int highestBet = 0;
    bool betting = true;

    printf("\n--- Inicia la ronda de apuestas ---\n");
    while (betting) {
        betting = false;

        for (int i = 0; i < numPlayers; i++) {
            if (players[i].fold) continue;

            printf("\n%s tiene $%d. Apuesta actual: $%d\n", players[i].name, players[i].money, highestBet);
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
                    if (scanf("%d", &raise) != 1 || raise <= 0 || raise > players[i].money) {
                        printf("Cantidad inválida. Intenta de nuevo.\n");
                        clearBuffer();
                        i--;
                        
                        continue;
                    }
                    clearBuffer();
                    highestBet += raise;
                    players[i].money -= highestBet;
                    *pot += highestBet;
                    betting = true;
                    break;
                }
                case 2:
                    if (players[i].money >= highestBet) {
                        players[i].money -= highestBet;
                        *pot += highestBet;
                    } else {
                        printf("No tienes suficiente dinero. Te retiras automáticamente.\n");
                        players[i].fold = true;
                    }
                    break;
                case 3:
                    players[i].fold = true;
                    printf("%s se ha retirado.\n", players[i].name);
                    break;
                default:
                    printf("Opción inválida. Intenta de nuevo.\n");
                    i--;
            }
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

// Función principal
int main() {
    int numPlayers;

    do {
        printf("Introduce el número de jugadores (1-4): ");
        if (scanf("%d", &numPlayers) != 1 || numPlayers < 1 || numPlayers > 4) {
            printf("Entrada inválida. Intenta de nuevo.\n");
            clearBuffer();
        }
    } while (numPlayers < 1 || numPlayers > 4);

    player players[4] = {
        {1, "Jugador 1", {0}, 0, 1000, false},
        {2, "Jugador 2", {0}, 0, 1000, false},
        {3, "Jugador 3", {0}, 0, 1000, false},
        {4, "Jugador 4", {0}, 0, 1000, false}
    };

    menu(players, numPlayers);
    return 0;
}