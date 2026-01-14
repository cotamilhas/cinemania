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
        printf("1. Listar filmes\n");
        printf("2. Pesquisar filmes\n");
        printf("3. Consultar filme\n");
        printf("4. Adicionar filme\n");
        printf("5. Alterar filme\n");
        printf("6. Eliminar filme\n");
        printf("7. Limpar memoria\n");
        printf("8. Importar (CSV)\n");
        printf("9. Exportar (CSV)\n");
        printf("0. Sair\n");
        
        option = readInteger(0, 9, "Escolha uma opcao: ");

        switch (option) {
            case 1: listMovies(&myList); break;
            case 2: searchMovies(&myList); break;
            case 3: showMovieInfo(&myList); break;
            case 4: addMovie(&myList); break;
            case 5: updateMovie(&myList); break;
            case 6: removeMovie(&myList); break;
            case 7: clearMovies(&myList); break;
            case 8: importMovies(&myList); break;
            case 9: exportMovies(&myList); break;
            case 0: printf("A sair...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (option != 0);

    return 0;
}