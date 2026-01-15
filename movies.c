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
    char shortTitle[51], shortDir[31], shortGen[51];
    strncpy(shortTitle, m.title, 50); shortTitle[50] = '\0';
    strncpy(shortDir, m.director, 30); shortDir[30] = '\0';
    strncpy(shortGen, m.genres, 50); shortGen[50] = '\0';
    
    printf("%-5d | %-50s | %-30s | %-4d | %-4.1f | %-50s\n", 
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
            case 1:
                toLowerCase(list->movies[i].title, fieldLower);
                if (strstr(fieldLower, termLower)) match = 1;
                break;
            case 2:
                toLowerCase(list->movies[i].genres, fieldLower);
                if (strstr(fieldLower, termLower)) match = 1;
                break;
            case 3:
                toLowerCase(list->movies[i].director, fieldLower);
                if (strstr(fieldLower, termLower)) match = 1;
                break;
            case 4:
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
    int code = readInteger(1, MAX_MOVIES, "Introduza o Code do filme: ");
    
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

void updateMovie(MovieList *list) {
    printf("\n--- Alterar Filme ---\n");
    int code = readInteger(1, MAX_MOVIES, "Codigo do filme a alterar: ");
    
    int index = -1;
    for (int i = 0; i < list->count; i++) {
        if (list->movies[i].code == code) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("ERRO: Filme nao encontrado.\n");
        return;
    }

    Movie *m = &list->movies[index];
    printf("A editar: %s (Deixa vazio/0 para manter o atual)\n", m->title);
    
    printf("Novo Titulo (Atual: %s): \n", m->title);
    char temp[MAX_STR];
    readString(temp, MAX_STR, "> ");
    if (strlen(temp) > 0) strcpy(m->title, temp);

    printf("Novos Generos (Atual: %s): \n", m->genres);
    readString(temp, MAX_STR, "> ");
    if (strlen(temp) > 0) strcpy(m->genres, temp);

    int newYear;
    do {
        newYear = readInteger(0, 2030, "Novo Ano (0 mantem): ");
        if (newYear == 0 || (newYear >= 1888 && newYear <= 2030)) break;
        printf("ERRO: Insira 0 ou um valor entre 1888 e 2030.\n");
    } while (-1);

    if (newYear != 0) m->year = newYear;

    int newDur = readInteger(0, 1000, "Nova Duracao (0 mantem): ");
    if (newDur != 0) m->duration = newDur;

    float newRating;
    do {
        newRating = readFloat(-1.0, 10.0, "Novo Rating (-1 mantem): ");
        if (newRating == -1 || (newRating >= 0 && newRating <= 10)) break;
        printf("ERRO: Insira -1 ou um valor entre 0.0 e 10.0.\n");
    } while (1);

    if (newRating != -1) m->rating = newRating;

    printf("SUCESSO: Filme atualizado!\n");
}

void removeMovie(MovieList *list) {
    printf("\n--- Eliminar Filme ---\n");
    int code = readInteger(1, MAX_MOVIES, "Codigo do filme a eliminar: ");

    int index = -1;
    for (int i = 0; i < list->count; i++) {
        if (list->movies[i].code == code) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("ERRO: Filme nao encontrado.\n");
        return;
    }

    printf("Tem a certeza que quer apagar '%s'? (1-Sim, 0-Nao): ", list->movies[index].title);
    int confirm = readInteger(0, 1, "");
    
    if (confirm == 1) {
        // arrastar todos os filmes seguintes uma posição para trás
        for (int i = index; i < list->count - 1; i++) {
            list->movies[i] = list->movies[i+1];
        }
        list->count--;
        printf("SUCESSO: Filme eliminado.\n");
    } else {
        printf("Operacao cancelada.\n");
    }
}

void clearMovies(MovieList *list) {
    printf("\n--- Limpar Memoria ---\n");
    printf("ATENCAO: Isto apaga tudo o que nao foi guardado!\n");
    int confirm = readInteger(0, 1, "Tem a certeza? (1-Sim, 0-Nao): ");

    if (confirm == 1) {
        list->count = 0;
        printf("Memoria limpa. Comecamos do zero.\n");
    }
}

void parseLineAndAdd(char *line, MovieList *list) {
    if (list->count >= MAX_MOVIES) return;

    Movie m;
    memset(&m, 0, sizeof(Movie));

    char *ptr = line;
    int col = 0;
    char buffer[MAX_DESC + 100]; 
    int bufIdx = 0;

    while (*ptr != '\0' && *ptr != '\n' && *ptr != '\r') {
        
        if (*ptr == ';') {
            buffer[bufIdx] = '\0';

            switch(col) {
                case 0: m.code = atoi(buffer); break;
                case 1: strncpy(m.title, buffer, MAX_STR-1); break;
                case 2: strncpy(m.genres, buffer, MAX_STR-1); break;
                case 3: strncpy(m.description, buffer, MAX_DESC-1); break;
                case 4: strncpy(m.director, buffer, MAX_STR-1); break;
                case 5: strncpy(m.actors, buffer, MAX_STR-1); break;
                case 6: m.year = atoi(buffer); break;
                case 7: m.duration = atoi(buffer); break;
                case 8: m.rating = atof(buffer); break;
                case 9: m.favorite = atoi(buffer); break;
                case 10: m.revenue = atof(buffer); break;
            }
            
            col++;
            bufIdx = 0;
        } 
        else {
            if (bufIdx < MAX_DESC) {
                buffer[bufIdx++] = *ptr;
            }
        }
        ptr++;
    }
    
    buffer[bufIdx] = '\0';
    if (col == 10) { 
         m.revenue = atof(buffer);
    }
    
    int exists = 0;
    for(int i=0; i<list->count; i++) {
        if(list->movies[i].code == m.code) { exists = 1; break; }
    }

    if (!exists && m.code > 0) {
        list->movies[list->count] = m;
        list->count++;
    }
}

void importMovies(MovieList *list) {
    char filename[MAX_STR];
    readString(filename, MAX_STR, "Nome do ficheiro: ");

    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("ERRO: Nao foi possivel abrir o ficheiro.\n");
        return;
    }

    char buffer[4096]; 
    
    int initialCount = list->count;

    fgets(buffer, 4096, f); 

    while (fgets(buffer, 4096, f)) {
        parseLineAndAdd(buffer, list);
    }

    fclose(f);
    
    printf("SUCESSO: Total de filmes: %d (Novos adicionados: %d).\n", 
           list->count, list->count - initialCount);
}

void exportMovies(MovieList *list) {
    char filename[MAX_STR];
    readString(filename, MAX_STR, "Nome do ficheiro para exportar (ex: backup.csv): ");

    FILE *test = fopen(filename, "r");
    if (test) {
        printf("ERRO: O ficheiro ja existe!\n");
        fclose(test);
        return;
    }

    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("ERRO: Nao foi possivel criar o ficheiro.\n");
        return;
    }

    fprintf(f, "code;title;genres;description;director;actors;year;duration;rating;favorite;revenue\n");

    for (int i = 0; i < list->count; i++) {
        Movie m = list->movies[i];

        char ratingStr[16], revenueStr[32];

        snprintf(ratingStr, sizeof(ratingStr), "%.1f", m.rating);
        snprintf(revenueStr, sizeof(revenueStr), "%.2f", m.revenue);

        for (int j = 0; ratingStr[j]; j++) if (ratingStr[j] == '.') ratingStr[j] = ',';
        for (int j = 0; revenueStr[j]; j++) if (revenueStr[j] == '.') revenueStr[j] = ',';

        fprintf(f, "%d;%s;%s;%s;%s;%s;%d;%d;%s;%d;%s\n",
            m.code, m.title, m.genres, m.description, m.director, m.actors,
            m.year, m.duration, ratingStr, m.favorite, revenueStr
        );
    }

    fclose(f);
    printf("SUCESSO: Dados exportados!\n");
}
