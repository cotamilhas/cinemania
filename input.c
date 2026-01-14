#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
// aaaaaaaaaaaaaaaaa
// limpa o buffer de entrada ate encontrar '\n' ou EOF
void cleanInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// le uma string com proteção ao tamanho e remove o '\n'
void readString(char *buffer, int size, char *msg) {
    printf("%s", msg); // mostra a mensagem
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; // remove o '\n'
        } else {
            cleanInputBuffer(); // limpa o resto
        }
    }
}

// le um inteiro dentro de um intervalo
int readInteger(int min, int max, char *msg) {
    int value;
    char input[50];
    while (1) {
        printf("%s", msg); // mostra a mensagem
        fgets(input, 50, stdin); // le como string
        
        if (sscanf(input, "%d", &value) == 1) { // tenta converter para int
            if (value >= min && value <= max) { // valida intervalo
                return value;
            }
        }
        printf("ERRO: Insira um valor inteiro entre %d e %d.\n", min, max);
    }
}

// le um float dentro de um intervalo
float readFloat(float min, float max, char *msg) {
    float value;
    char input[50];

    while (1) {
        printf("%s", msg); // mostra a mensagem
        fgets(input, 50, stdin); // le como string
        
        if (sscanf(input, "%f", &value) == 1) { // tenta converter para float
            if (value >= min && value <= max) { // valida intervalo
                return value;
            }
        }
        printf("ERRO: Insira um valor entre %.1f e %.1f.\n", min, max);
    }
}