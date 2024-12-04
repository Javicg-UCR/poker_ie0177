
#include <stdio.h>

// Determinar valor de la carta
void determineCardValue(int x) {

    x--;
    int cardVal = ((x - x % 4)/ 4)+ 2 ; // Fórmula para el valor de la carta

    if (cardVal >= 2 && cardVal <= 14) { // Corrección de la validación
        printf("Valor de la carta: %d\n", cardVal);
    } else {
        printf("Error: el valor calculado no es válido.\n");
    }
}

// Determinar palo de la carta: Asocia un numero del 1-4 de menor a mayor para trebol, pica, corazon y diamante
int determineCardType(int x) {
    int temp = (x % 4) + 1; // Fórmula para el palo
    return temp; // Devuelve el palo (1-4)
}

int main() {
    int x;

    // Solicitar número al usuario
    printf("Introduce un número entre 1 y 52: ");
    scanf("%d", &x);

    // Validar que el número esté en el rango
    if (x < 1 || x > 52) {
        printf("Error: el número debe estar entre 1 y 52.\n");
        return 1; // Salir con código de error
    }

    // Determinar valor y palo de la carta
    determineCardValue(x);

    int cardType = determineCardType(x);
    printf("Tipo de carta (palo): %d\n", cardType);

    return 0;
}