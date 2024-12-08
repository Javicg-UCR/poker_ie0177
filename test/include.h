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
    int cycle; // Sirve para hacer el ciclo
} player;

// Funciones
void clearBuffer();
int deal_reset(int check);
void distributeCards(player players[], int numPlayers);
void evaluateHand(player *p);
void showPlayerHand(player *p);
void bettingRound(player players[], int numPlayers, int *pot);
void showWinner(player players[], int numPlayers, int pot);
void menu(player players[], int numPlayers);
int cycle(player players[], int numPlayers, int cycle_by);