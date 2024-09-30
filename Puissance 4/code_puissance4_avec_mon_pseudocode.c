#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef int tab[6][7];

void tirage(int *tour);  // fait le tirage pour savoir qui commence
void affiche_tableau(tab);    // affiche le tableau en fonction de l'avancé de la partie
void demande_action(int *tour , tab, bool *end);  // demande au joueur quelle action il veut faire
void gagne_ligne(tab, int ligne, bool *end);      // regarde si le joueur à gagné sur une ligne
void gagne_colonne(tab, int colonne, bool *end);  // regarde si le joueur à gagné sur une colonne
void gagneDescendDiagonal(tab tableau, bool *end);// regarde si le joueur à gagné sur une diagonale qui monte
void gagneMonteDiagonal(tab tableau, bool *end);  // regarde si le joueur à gagné sur une diagonal qui descent

int main(){
    int tour;
    bool end;
    
    end = false;
    tab grille = {0};
    
    printf("Le joueur n°1 a les carrés et le second a les triangles\n");
    
    tirage(&tour);
    affiche_tableau(grille);
    
    if (tour == 0){
        while(end != true){
            demande_action(&tour, grille, &end);
            affiche_tableau(grille);
            tour += 1;
            if (tour > 41){
                end = true;
                printf("Egalité");
            }
        }
    }
    else {
        while(end != true){
            demande_action(&tour, grille, &end);
            affiche_tableau(grille);
            tour += 1;
            if (tour > 42){
                end = true;
                printf("Egalité");
            }
        }
    }
    return EXIT_SUCCESS;
}


void tirage(int *tour){
    srand(time(NULL));
    int r = rand() % 2;
    if (r == 1){
        *tour = 0;
    }
    else{
        *tour = 1;
    }
}

void affiche_tableau(tab tableau){
    int ligne;
    int colonne;
    
    printf("_______________\n");
    printf(" 0 1 2 3 4 5 6 \n");
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
    
    for (ligne = 0; ligne < 6; ligne++){
        printf("|");
        
        for (colonne = 0; colonne < 7; colonne++){
            switch (tableau[ligne][colonne]){
                case 1 : printf("□");
                break;
                
                case 2 : printf("Δ");
                break;
                
                default : printf(" ");
                break;
            }
            printf("|");
        }
        printf("\n");
    }
}

void demande_action(int *tour, tab tableau, bool *end){
    int ligne = 5;
    int colonne, joueur;
    bool place = false;
    
    if (*tour %2 == 0){
        joueur = 1;
    }
    else{
        joueur = 2;
    }
        
    do{
        printf("Joueur %d, où voulez-vous mettre votre pion? : ", joueur);
        scanf("%d", &colonne);
        if (colonne < 0 || colonne > 6){
            printf("Choisir une colonne entre 0 et 6\n");
        } 
    }while (colonne < 0 || colonne > 6);
    
    
    
    while (place != true){
        
        if (tableau[ligne][colonne] == 0){
            if (*tour % 2 == 0){
                tableau[ligne][colonne] = 1;
                place = true;
            }
            else{
                tableau[ligne][colonne] = 2;
                place = true;

            }
        }
        else{
            ligne--;
            if (ligne < 0){
                printf("La colonne est remplie, où voulez-vous placer votre pion? : ");
                scanf("%d", &colonne);
                ligne = 5;
            }
        }
    }
    gagne_ligne(tableau, ligne, end);
    if (*end != true){
        gagne_colonne(tableau, colonne, end);
    }
    if (*end != true){
        gagneDescendDiagonal(tableau, end);
    }
    if (*end != true){
        gagneMonteDiagonal(tableau, end);
    }
}

void gagne_ligne(tab tableau, int ligne, bool *end){
    int i;
    int nb4_j1, nb4_j2;
    nb4_j1 = 0;
    nb4_j2 = 0;
    *end = false;
    
    for (i = 0; i < 7; i++){
        if (tableau[ligne][i] == 1){
            nb4_j1 = nb4_j1 + 1;
            nb4_j2 = 0;
            if (nb4_j1 >= 4){
                printf("Joueur 1 vous avez gagné !!!\n");
                i = i + 7;
                *end = true;
            }
        }
        else if (tableau[ligne][i] == 2){
            nb4_j2 = nb4_j2 + 1;
            nb4_j1 = 0;
            if (nb4_j2 >= 4){
                printf("Joueur 2 vous avez gagné !!!\n");
                i = i + 7;
                *end = true;
            }
        }
        else{
            nb4_j1 = 0;
            nb4_j2 = 0;
        }
    }
}

void gagne_colonne(tab tableau, int colonne, bool *end){
    int i;
    int nb4_j1, nb4_j2;
    
    nb4_j1 = 0;
    nb4_j2 = 0;
    *end = false;
    
    for (i = 0; i < 6; i++){
        if (tableau[i][colonne] == 1){
            nb4_j1 = nb4_j1 + 1;
            nb4_j2 = 0;
            if (nb4_j1 >= 4){
                printf("Joueur 1 vous avez gagné !!!\n");
                i = i + 7;
                *end = true;
            }
        }
        else if (tableau[i][colonne] == 2){
            nb4_j2 = nb4_j2 + 1;
            nb4_j1 = 0;
            if (nb4_j2 >= 4){
                printf("Joueur 2 vous avez gagné !!!\n");
                i = i + 7;
                *end = true;
            }
        }
        else{
            nb4_j1 = 0;
            nb4_j2 = 0;
        }
    }
}

void gagneDescendDiagonal(tab tableau, bool *end){
    int ligne, colonne;
    for(ligne = 0; ligne < 3; ligne++){
        for(colonne = 0; colonne < 4; colonne++){
            if(tableau[ligne][colonne] == 1 && tableau[ligne+1][colonne+1] == 1 && tableau[ligne+2][colonne+2] == 1 && tableau[ligne+3][colonne+3] == 1){
                printf("Joueur 1 vous avez gagné !!!\n");
                *end = true;
            }
            if(tableau[ligne][colonne] == 2 && tableau[ligne+1][colonne+1] == 2 && tableau[ligne+2][colonne+2] == 2 && tableau[ligne+3][colonne+3] == 2){
                printf("Joueur 2 vous avez gagné !!!\n");
                *end = true;
            }
        }
    }
}

void gagneMonteDiagonal(tab tableau, bool *end){
    int ligne, colonne;
    for(ligne = 3; ligne < 6; ligne++){
        for(colonne = 0; colonne < 4; colonne++){
            if(tableau[ligne][colonne] == 1 && tableau[ligne-1][colonne+1] == 1 && tableau[ligne-2][colonne+2] == 1 && tableau[ligne-3][colonne+3] == 1){
                printf("Joueur 1 vous avez gagné !!!\n");
                *end = true;
            }
            if(tableau[ligne][colonne] == 2 && tableau[ligne-1][colonne+1] == 2 && tableau[ligne-2][colonne+2] == 2 && tableau[ligne-3][colonne+3] == 2){
                printf("Joueur 2 vous avez gagné !!!\n");
                *end = true;
            }
        }
    }
}