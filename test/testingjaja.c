#include <stdio.h>
#include <stdlib.h>
char buffer[10];

void int_to_str(int number, char *str) {
    int i = 0;

    // salvar una copia del número n
    int sign = number;

    // Agarrar dígitos, van a string
    while (number > 0) {
        // Poner el int en el string
        str[i++] = number % 10 + '0';
      	number /= 10;
    }

    // Null para acabar str
    str[i] = '\0';

    // Cambiar el orden
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

void main()
{
    intToStr(500,buffer);
    printf("srtin: %s, %d",buffer,6);
}