#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NBLIGNE 10
#define NBCOLONNE 10
typedef char laby[NBLIGNE][NBCOLONNE];

typedef struct {
    char caractere;
    int numeroLigne;
    int numeroColonne;
} caseLabyrinthe;

void lireLaby(laby L, char nomFichier[30]) {
    FILE* fic;
    caseLabyrinthe case;
    fic = fopen(nomFichier, "r");

    while(!foef(fic)) {
        fread(&case, sizeof(caseLabyrinthe), 1, fic);
        strcpy(L[case.numeroLigne][case.numeroColonne], case.caractere);
    }

    L[1][0] = 'O';

    fclose(fic);
}

void afficherLaby(laby L) {
    for (int i = 0; i < NBLIGNE; i++) {
        for (int j = 0; j < NBCOLONNE; j++) {
            printf("%c ", L[i][j]);
        }
        printf("\n");
    }
}

void chercherPion(laby L, int * ligne, int * colonne) {
    for (int i = 0; i < NBLIGNE; i++) {
        for(int j = 0; j < NBCOLONNE; j++) {
            if (strcmp(&L[i][j], 'O')==0) {
                *ligne = i;
                *colonne = j;
            }
        }
    }
}

bool impasse(laby L, int ligne, int colonne) {
    int nbmur = 0;

    if (strcmp(L[ligne-1][colonne], 'X')==0) {
        nbmur++;
    }
    if (strcmp(L[ligne+1][colonne], 'X')==0) {
        nbmur++;
    }
    if (strcmp(L[ligne][colonne-1], 'X')==0) {
        nbmur++;
    }
    if (strcmp(L[ligne][colonne+1], 'X')==0) {
        nbmur++;
    }

    if (nbmur==3) {
        return true;
    } else {
        return false;
    }
}

deplacement(laby L, int * ligne, int * colonne) {
    char dep[1];

    printf("Saisir l'action : ");
    scanf("%c", &dep);

    switch (dep){
    case 'G':
        *colonne = *colonne -1;
        break;
    case 'D':
        *colonne = *colonne +1;
        break;
    case 'H':
        *ligne = *ligne -1;
        break;
    case 'B':
        *ligne = *ligne +1;
        break;
    
    default:
        break;
    }
}

int main() {
    int lignePion = 0, colonnePion = 0;
    laby labyrinthe = {
        {'X','X','X','X','X','X','X','X','X','X'},
        {'O',' ',' ','X','X',' ',' ',' ','X','X'},
        {'X','X',' ',' ',' ',' ','X',' ','X','X'},
        {'X','X',' ','X','X','X','X',' ',' ','X'},
        {'X',' ',' ','X','X','X','X','X','X','X'},
        {'X',' ','X','X',' ',' ',' ',' ',' ','X'},
        {'X',' ',' ',' ',' ','X',' ','X',' ','X'},
        {'X',' ','X','X','X','X',' ','X',' ','X'},
        {'X',' ',' ',' ',' ','X',' ','X',' ',' '},
        {'X','X','X','X','X','X','X','X','X','X'},
    };
    char nomFic[30] = "LABYRINTHE.DATA";

    /*lireLaby(labyrinthe, &nomFic[30]);*/
    afficherLaby(labyrinthe);
    chercherPion(labyrinthe, &lignePion, &colonnePion);

    printf("Pion en %d %d", lignePion, colonnePion);

    if (impasse(labyrinthe, lignePion, colonnePion)) {
        printf("Le pion est dans une impasse");
    }


    return EXIT_SUCCESS;
}