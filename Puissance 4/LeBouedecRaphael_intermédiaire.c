#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>


const char PION_A = 'X';
const char PION_B = 'O';
const char VIDE = ' ';
const char INCONNU = ' ';
const int NBLIG = 6;
const int NBCOL = 7;
const int COLONNE_DEBUT = NBCOL/2;

typedef char grille[5][6];

void initGrille(grille g);
void afficher(grille g, char pion, int colonne);
bool grillePleine(grille g);


/* 
il faut avoir les procédures:
- initGrille
- afficher
- jouer
- finDePartie

les fonctions:
- choisirColonne
- grillePleine
- trouverLigne
- estVainqueur
*/



int main() {
    char vainqueur;
    int ligne, colonne;
    grille g;
    
    initGrille(g);
    vainqueur = INCONNU;
    afficher(g, PION_A, COLONNE_DEBUT);
    
    while((vainqueur == INCONNU) &&  (!grillePleine(g))){
        jouer(g, PION_A, &ligne, &colonne);
        afficher(g, PION_B, COLONNE_DEBUT);
        if(estVainqueur(g, ligne, colonne)){
            vainqueur = PION_A;
        }
        else if(!grillePleine(g)){
            jouer(g, PION_B, &ligne, &colonne);
            afficher(g, PION_A, COLONNE_DEBUT);
            if(estVainqueur(g, ligne, colonne)){
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);
    
    return EXIT_SUCCESS;
}



void initGrille(grille g){
    for (int i = 0; i < NBLIG; i++){
        for (int y = 0; y < NBCOL; y++){
            g[i][y] = VIDE;
        }
    }
}




void afficher(grille g, char pion, int colonne){
    
    printf("_______________\n");
    printf(" 1 2 3 4 5 6 7 \n");
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
    
    for (int i = 0; i < (colonne*2) -1; i++){
        printf(" ");
    }
    printf("%c\n", pion);
    
    for (int lig = 0; lig < 6; lig++){
        printf("|");
        
        for (int col = 0; col < 7; col++){
            printf("%c", g[lig][col]);
            printf("|");
        }
        printf("\n");
    }
}



bool grillePleine(grille g){
    bool statut;
    int cpt = 0;
    statut = false;
    
    for (int x = 0; x < 7; x++){
        if ((g[x][0] == PION_A) || (g[x][0] == PION_B)){
            cpt = cpt + 1;
        }
    }
    if (cpt == 7){
        statut = true;
    }
    else{
        cpt = 0;
    }
    
    return statut;
}