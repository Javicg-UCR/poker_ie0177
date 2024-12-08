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
    int cycle;
} player;

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
            return players[a].number;
        }
    }
    return -1;
}

int main ()
{
    player players[4] = {
        {1, "Jugador 1", {0}, 0, 1000, false, 0},
        {2, "Jugador 2", {0}, 0, 1000, false, 1},
        {3, "Jugador 3", {0}, 0, 1000, false, 2},
        {4, "Jugador 4", {0}, 0, 1000, false, 3}
    };

    printf("\n1:%d, 2:%d, 3:%d, 4:%d\n",players[0].cycle,players[1].cycle,players[2].cycle,players[3].cycle);

    cycle(players,4,1);

    printf("\n1:%d, 2:%d, 3:%d, 4:%d\n",players[0].cycle,players[1].cycle,players[2].cycle,players[3].cycle);
}

