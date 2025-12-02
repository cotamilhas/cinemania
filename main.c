#include <stdio.h>
#include <stdlib.h>
#include "movies.h"
#include "input.h"

int main() {
    MovieList myList;
    myList.count = 0;

    int option;

    do {
        printf("\n=== CINE MANIA ===\n");
        printf("1. Listar todos os filmes\n");
        printf("2. Pesquisar filmes\n");
        printf("3. Consultar informacao de um filme\n");
        printf("4. Adicionar filme\n");
        printf("0. Sair\n");
        
        option = readInteger(0, 4, "Escolha uma opcao: ");

        switch (option) {
            case 1:
                listMovies(&myList);
                break;
            case 2:
                searchMovies(&myList);
                break;
            case 3:
                showMovieInfo(&myList);
                break;
            case 4:
                addMovie(&myList);
                break;
            case 0:
                printf("A sair do CineMania...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (option != 0);

    return 0;
}