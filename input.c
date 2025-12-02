#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

void cleanInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void readString(char *buffer, int size, char *msg) {
    printf("%s", msg);
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}

int readInteger(int min, int max, char *msg) {
    int value;
    char input[50];
    while (1) {
        printf("%s", msg);
        fgets(input, 50, stdin);
        if (sscanf(input, "%d", &value) == 1) {
            if (value >= min && value <= max) {
                return value;
            }
        }
        printf("ERRO: Insira um valor inteiro entre %d e %d.\n", min, max);
    }
}

float readFloat(float min, float max, char *msg) {
    float value;
    char input[50];
    while (1) {
        printf("%s", msg);
        fgets(input, 50, stdin);
        if (sscanf(input, "%f", &value) == 1) {
            if (value >= min && value <= max) {
                return value;
            }
        }
        printf("ERRO: Insira um valor entre %.1f e %.1f.\n", min, max);
    }
}