

#include "float_str.h"

// Converte valores em ponto flutuante para string
// Parte inteira (até 3 dígitos)
// Parte decimal (dois dígitos sempre)
void float_str(float valor, char *str) {
    int inteiro;
    int negativo = 0;

    if (valor < 0) {
        negativo = 1;
        valor = -valor;
    }

    // Multiplica por 100 e arredonda
    int num = (int)(valor * 100 + 0.5);

    inteiro = num / 100;
    int decimal = num % 100;

    // Constrói a string manualmente
    int pos = 0;

    if (negativo) {
        str[pos++] = '-';
    }
    else {
        str[pos++] = ' ';
    }

    // Parte inteira (até 3 dígitos)
    if (inteiro >= 100) {
        str[pos++] = (char)(inteiro / 100) + '0';
        str[pos++] = (char)((inteiro / 10) % 10) + '0';
        str[pos++] = (char)(inteiro % 10) + '0';
    } else if (inteiro >= 10) {
        str[pos++] = (char)(inteiro / 10) + '0';
        str[pos++] = (char)(inteiro % 10) + '0';
    } else {
        str[pos++] = (char)inteiro + '0';
    }

    str[pos++] = ',';

    // Parte decimal (dois dígitos sempre)
    str[pos++] = (char)(decimal / 10) + '0';
    str[pos++] = (char)(decimal % 10) + '0';

    str[pos] = '\0'; // final da string
}
