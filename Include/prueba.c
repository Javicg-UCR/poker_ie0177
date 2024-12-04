#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Estructura de jugador
typedef struct {
    int number;
    char name[30];
    int hand[7]; // 5 cartas del jugador + 2 cartas comunitarias
    int handValue;
    int money;
    int fold; // 0 para no retirado, 1 para retirado
} player;

// Prototipos de funciones
int deal_reset(int check);
int determineCardValue(int x);
int determineCardType(int x);
bool isSameSuit(int suits[], int n);
bool isConsecutive(int values[], int n);
bool isRoyalFlush(int values[], int suits[], int n);
bool isStraightFlush(int values[], int suits[], int n);
bool isFourOfAKind(int values[], int n);
bool isFullHouse(int values[], int n);
bool isFlush(int suits[], int n);
bool isStraight(int values[], int n);
bool isThreeOfAKind(int values[], int n);
bool isTwoPair(int values[], int n);
bool isOnePair(int values[], int n);
int getHighCard(int values[], int n);
void evaluateHand(player *p);
void showPlayerHand(player *p);
void distributeCards(player players[], int numPlayers);
void menu(player players[], int numPlayers);
void clearBuffer();

// Función para limpiar el buffer de entrada
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función para reiniciar o repartir cartas
int deal_reset(int check) {
    static int dealt[52] = {0};
    static int cardsDealt = 0;

    if (check == 1) {
        memset(dealt, 0, sizeof(dealt));
        cardsDealt = 0;
        return 0;
    }

    if (cardsDealt >= 52) {
        return -1;
    }

    int card;
    do {
        card = (rand() % 52) + 1;
    } while (dealt[card - 1] == 1);

    dealt[card - 1] = 1;
    cardsDealt++;
    return card;
}

// Determinar valor de la carta
int determineCardValue(int x) {
    return ((x - 1) / 4) + 2;
}

// Determinar palo de la carta
int determineCardType(int x) {
    return ((x - 1) % 4) + 1;
}

// Verificar si todas las cartas son del mismo palo
bool isSameSuit(int suits[], int n) {
    for (int i = 1; i < n; i++) {
        if (suits[i] != suits[0]) {
            return false;
        }
    }
    return true;
}

// Verificar si las cartas son consecutivas
bool isConsecutive(int values[], int n) {
    for (int i = 1; i < n; i++) {
        if (values[i] != values[i - 1] + 1) {
            return false;
        }
    }
    return true;
}

// Evaluar si el jugador tiene Escalera Real
bool isRoyalFlush(int values[], int suits[], int n) {
    return isStraightFlush(values, suits, n) && values[0] == 10;
}

// Evaluar si el jugador tiene Escalera de Color
bool isStraightFlush(int values[], int suits[], int n) {
    return isSameSuit(suits, n) && isConsecutive(values, n);
}

// Evaluar si el jugador tiene Poker
bool isFourOfAKind(int values[], int n) {
    int count[15] = {0};
    for (int i = 0; i < n; i++) {
        count[values[i]]++;
    }
    for (int i = 2; i <= 14; i++) {
        if (count[i] == 4) {
            return true;
        }
    }
    return false;
}

// Evaluar si el jugador tiene Full
bool isFullHouse(int values[], int n) {
    int count[15] = {0};
    for (int i = 0; i < n; i++) {
        count[values[i]]++;
    }
    bool hasThree = false, hasTwo = false;
    for (int i = 2; i <= 14; i++) {
        if (count[i] == 3) {
            hasThree = true;
        }
        if (count[i] == 2) {
            hasTwo = true;
        }
    }
    return hasThree && hasTwo;
}

// Evaluar si el jugador tiene Color
bool isFlush(int suits[], int n) {
    return isSameSuit(suits, n);
}

// Evaluar si el jugador tiene Escalera
bool isStraight(int values[], int n) {
    return isConsecutive(values, n);
}

// Evaluar si el jugador tiene Trío
bool isThreeOfAKind(int values[], int n) {
    int count[15] = {0};
    for (int i = 0; i < n; i++) {
        count[values[i]]++;
    }
    for (int i = 2; i <= 14; i++) {
        if (count[i] == 3) {
            return true;
        }
    }
    return false;
}

// Evaluar si el jugador tiene Doble Pareja
bool isTwoPair(int values[], int n) {
    int count[15] = {0};
    for (int i = 0; i < n; i++) {
        count[values[i]]++;
    }
    int pairCount = 0;
    for (int i = 2; i <= 14; i++) {
        if (count[i] == 2) {
            pairCount++;
        }
    }
    return pairCount == 2;
}

// Evaluar si el jugador tiene Pareja
bool isOnePair(int values[], int n) {
    int count[15] = {0};
    for (int i = 0; i < n; i++) {
        count[values[i]]++;
    }
    for (int i = 2; i <= 14; i++) {
        if (count[i] == 2) {
            return true;
        }
    }
    return false;
}

// Obtener la carta más alta
int getHighCard(int values[], int n) {
    int max = values[0];
    for (int i = 1; i < n; i++) {
        if (values[i] > max) {
            max = values[i];
        }
    }
    return max;
}

// Evaluar la mano de un jugador
void evaluateHand(player *p) {
    int values[7], suits[7];
    for (int i = 0; i < 7; i++) {
        values[i] = determineCardValue(p->hand[i]);
        suits[i] = determineCardType(p->hand[i]);
    }

    // Ordenar valores
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 7; j++) {
            if (values[i] > values[j]) {
                int temp = values[i];
                values[i] = values[j];
                values[j] = temp;

                int tempSuit = suits[i];
                suits[i] = suits[j];
                suits[j] = tempSuit;
            }
        }
    }

    // Determinar la mejor combinación
    if (isRoyalFlush(values, suits, 7)) {
        printf("%s tiene Escalera Real de Color\n", p->name);
    } else if (isStraightFlush(values, suits, 7)) {
        printf("%s tiene Escalera de Color\n", p->name);
    } else if (isFourOfAKind(values, 7)) {
        printf("%s tiene Poker\n", p->name);
    } else if (isFullHouse(values, 7)) {
        printf("%s tiene Full\n", p->name);
    } else if (isFlush(suits, 7)) {
        printf("%s tiene Color\n", p->name);
    } else if (isStraight(values, 7)) {
        printf("%s tiene Escalera\n", p->name);
    } else if (isThreeOfAKind(values, 7)) {
        printf("%s tiene Trío\n", p->name);
    } else if (isTwoPair(values, 7)) {
        printf("%s tiene Doble Pareja\n", p->name);
    } else if (isOnePair(values, 7)) {
        printf("%s tiene Pareja\n", p->name);
    } else {
        printf("%s tiene Carta más Alta: %d\n", p->name, getHighCard(values, 7));
    }
}

// Mostrar las manos de los jugadores
void showPlayerHand(player *p) {
    printf("\n%s tiene las siguientes cartas:\n", p->name);
    for (int i = 0; i < 7; i++) {
        int value = determineCardValue(p->hand[i]);
        int suit = determineCardType(p->hand[i]);
        printf("Carta %d: Valor %d, Palo %d\n", i + 1, value, suit);
    }
}

// Repartir cartas a los jugadores
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

// Menú interactivo
void menu(player players[], int numPlayers) {
    int option;
    do {
        printf("\n=== Menú ===\n");
        printf("1. Repartir cartas a los jugadores\n");
        printf("2. Mostrar las manos de los jugadores\n");
        printf("3. Evaluar manos\n");
        printf("4. Salir\n");
        printf("Elige una opción: ");
        if (scanf("%d", &option) != 1) {
            printf("Entrada inválida. Intenta de nuevo.\n");
            clearBuffer(); // Limpiar el buffer si la entrada es inválida
            continue;
        }
        clearBuffer(); // Limpiar el buffer tras una entrada válida

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
            case 3:
                for (int i = 0; i < numPlayers; i++) {
                    evaluateHand(&players[i]);
                }
                break;
            case 4:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida. Intenta de nuevo.\n");
        }
    } while (option != 4);
}

// Función principal
int main() {
    int numPlayers;

    // Configurar número de jugadores
    do {
        printf("Introduce el número de jugadores (máximo 4): ");
        if (scanf("%d", &numPlayers) != 1) {
            printf("Entrada inválida. Intenta de nuevo.\n");
            clearBuffer(); // Limpiar el buffer si la entrada es inválida
            continue;
        }
        clearBuffer(); // Limpiar el buffer tras una entrada válida
        if (numPlayers < 1 || numPlayers > 4) {
            printf("Número inválido. Deben ser entre 1 y 4 jugadores.\n");
        }
    } while (numPlayers < 1 || numPlayers > 4);

    // Inicializar jugadores
    player players[4] = {
        {1, "Jugador 1", {0}, 0, 1000, 0},
        {2, "Jugador 2", {0}, 0, 1000, 0},
        {3, "Jugador 3", {0}, 0, 1000, 0},
        {4, "Jugador 4", {0}, 0, 1000, 0}
    };

    // Llamar al menú
    menu(players, numPlayers);

    return 0;
}

