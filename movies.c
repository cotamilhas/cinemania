#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "movies.h"
#include "input.h"

int compareCodeAsc(const void *a, const void *b) {
    return ((Movie*)a)->code - ((Movie*)b)->code;
}

int compareRatingDesc(const void *a, const void *b) {
    float diff = ((Movie*)b)->rating - ((Movie*)a)->rating;
    return (diff > 0) - (diff < 0);
}

int compareTitleAsc(const void *a, const void *b) {
    return strcmp(((Movie*)a)->title, ((Movie*)b)->title);
}

void toLowerCase(char *str, char *dest) {
    for (int i = 0; str[i]; i++) {
        dest[i] = tolower(str[i]);
    }
    dest[strlen(str)] = '\0';
}

void addMovie(MovieList *list) {
    if (list->count >= MAX_MOVIES) {
        printf("ERRO: Limite de filmes atingido (%d).\n", MAX_MOVIES);
        return;
    }

    Movie *m = &list->movies[list->count];
    
    m->code = (list->count == 0) ? 1 : list->movies[list->count - 1].code + 1;

    printf("\n--- Novo Filme (Codigo: %d) ---\n", m->code);
    
    readString(m->title, MAX_STR, "Titulo: ");
    readString(m->genres, MAX_STR, "Generos: ");
    readString(m->description, MAX_DESC, "Descricao: ");
    readString(m->director, MAX_STR, "Realizador: ");
    readString(m->actors, MAX_STR, "Atores: ");
    
    m->year = readInteger(1888, 2030, "Ano: ");
    m->duration = readInteger(1, 1000, "Duracao (min): ");
    m->rating = readFloat(0.0, 10.0, "Nota (0-10): ");
    m->favorite = readInteger(0, 10000000, "Favoritos (qtd): ");
    m->revenue = readFloat(0.0, 5000.0, "Receita (Milhoes): ");

    list->count++;
    printf("SUCESSO: Filme adicionado!\n");
}

void printHeader() {
    printf("\n%-5s | %-25s | %-15s | %-4s | %-4s | %-15s\n", "CODE", "TITULO", "REALIZADOR", "ANO", "NOTA", "GENEROS");
    printf("--------------------------------------------------------------------------------\n");
}

void printRow(Movie m) {
    char shortTitle[26], shortDir[16], shortGen[16];
    strncpy(shortTitle, m.title, 25); shortTitle[25] = '\0';
    strncpy(shortDir, m.director, 15); shortDir[15] = '\0';
    strncpy(shortGen, m.genres, 15); shortGen[15] = '\0';
    
    printf("%-5d | %-25s | %-15s | %-4d | %-4.1f | %-15s\n", 
           m.code, shortTitle, shortDir, m.year, m.rating, shortGen);
}

void listMovies(MovieList *list) {
    if (list->count == 0) {
        printf("Sem filmes registados.\n");
        return;
    }

    printf("\n--- Listar Filmes ---\n");
    printf("1. Ordem crescente do code\n");
    printf("2. Ordem decrescente do rating\n");
    printf("3. Ordem alfabetica do title\n");
    int op = readInteger(1, 3, "Opcao: ");

    switch (op) {
        case 1: qsort(list->movies, list->count, sizeof(Movie), compareCodeAsc); break;
        case 2: qsort(list->movies, list->count, sizeof(Movie), compareRatingDesc); break;
        case 3: qsort(list->movies, list->count, sizeof(Movie), compareTitleAsc); break;
    }

    printHeader();
    for (int i = 0; i < list->count; i++) {
        printRow(list->movies[i]);
    }
}

void searchMovies(MovieList *list) {
    if (list->count == 0) { printf("Sem filmes.\n"); return; }

    printf("\n--- Pesquisar ---\n");
    printf("1. Titulo (contem string)\n");
    printf("2. Genero\n");
    printf("3. Realizador\n");
    printf("4. Ator\n");
    int op = readInteger(1, 4, "Opcao: ");

    char term[MAX_STR];
    readString(term, MAX_STR, "Termo de pesquisa: ");
    
    char termLower[MAX_STR]; 
    toLowerCase(term, termLower);

    printHeader();
    int found = 0;
    for (int i = 0; i < list->count; i++) {
        char fieldLower[MAX_STR];
        int match = 0;

        switch(op) {
            case 1: // Titulo
                toLowerCase(list->movies[i].title, fieldLower);
                if (strstr(fieldLower, termLower)) match = 1;
                break;
            case 2: // Genero
                toLowerCase(list->movies[i].genres, fieldLower);
                if (strstr(fieldLower, termLower)) match = 1;
                break;
            case 3: // Realizador
                toLowerCase(list->movies[i].director, fieldLower);
                if (strstr(fieldLower, termLower)) match = 1;
                break;
            case 4: // Ator
                toLowerCase(list->movies[i].actors, fieldLower);
                if (strstr(fieldLower, termLower)) match = 1;
                break;
        }

        if (match) {
            printRow(list->movies[i]);
            found++;
        }
    }
    if (!found) printf("Nenhum resultado encontrado.\n");
}

void showMovieInfo(MovieList *list) {
    int code = readInteger(1, 99999, "Introduza o Code do filme: ");
    
    for (int i = 0; i < list->count; i++) {
        if (list->movies[i].code == code) {
            Movie m = list->movies[i];
            printf("\n--- Detalhes do Filme ---\n");
            printf("Code: %d\n", m.code);
            printf("Titulo: %s\n", m.title);
            printf("Generos: %s\n", m.genres);
            printf("Realizador: %s\n", m.director);
            printf("Atores: %s\n", m.actors);
            printf("Ano: %d\n", m.year);
            printf("Duracao: %d min\n", m.duration);
            printf("Rating: %.1f\n", m.rating);
            printf("Favoritos: %d\n", m.favorite);
            printf("Receita: %.2fM\n", m.revenue);
            printf("Descricao: %s\n", m.description);
            return;
        }
    }
    printf("Filme com codigo %d nao encontrado.\n", code);
}