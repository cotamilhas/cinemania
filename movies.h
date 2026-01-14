#pragma once

#define MAX_MOVIES 2000
#define MAX_STR 100
#define MAX_DESC 500

typedef struct {
    int code;
    char title[MAX_STR];
    char genres[MAX_STR];
    char description[MAX_DESC];
    char director[MAX_STR];
    char actors[MAX_STR];
    int year;
    int duration;
    float rating;
    int favorite;
    float revenue;
} Movie;

typedef struct {
    Movie movies[MAX_MOVIES];
    int count;
} MovieList;

void listMovies(MovieList *list);
void searchMovies(MovieList *list);
void showMovieInfo(MovieList *list);
void addMovie(MovieList *list);

void updateMovie(MovieList *list);
void removeMovie(MovieList *list);
void clearMovies(MovieList *list);
void importMovies(MovieList *list);
void exportMovies(MovieList *list);