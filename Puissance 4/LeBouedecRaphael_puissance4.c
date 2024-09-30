// Programme qui permer de jouer au Puissance 4

//-----------------------------definition---------------------

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

typedef char grille[6][7];

void initGrille(grille g);
void afficher(grille g, char pion, int colonne);
bool grillePleine(grille g);
void jouer(grille g, char pion, int *ligne, int *colonne);
int choisirColonne(grille g, char pion, int colonne);
int trouverLigne(grille g, int colonne);
bool estVainqueur(grille g, int ligne, int colonne);
void finDePartie(char pion);
char tirage();

// ------------------------------programme-----------------------------

int main() {
    char vainqueur;
    int ligne, colonne;
    grille gri;
    
    initGrille(gri);
    vainqueur = INCONNU;
    
    
    if(tirage() == PION_A){
        afficher(gri, PION_A, COLONNE_DEBUT);
        while((vainqueur == INCONNU) &&  !grillePleine(gri)){
            jouer(gri, PION_A, &ligne, &colonne);
            afficher(gri, PION_B, COLONNE_DEBUT);
            
            if(estVainqueur(gri, ligne, colonne)){
                vainqueur = PION_A;
            }
            
            else if(!grillePleine(gri)){
                jouer(gri, PION_B, &ligne, &colonne);
                afficher(gri, PION_A, COLONNE_DEBUT);
                if(estVainqueur(gri, ligne, colonne)){
                    vainqueur = PION_B;
                }
            }
            
        }
    }else{
        afficher(gri, PION_B, COLONNE_DEBUT);
        while((vainqueur == INCONNU) &&  !grillePleine(gri)){
            jouer(gri, PION_B, &ligne, &colonne);
            afficher(gri, PION_A, COLONNE_DEBUT);
            
            if(estVainqueur(gri, ligne, colonne)){
                vainqueur = PION_B;
            }
            
            else if(!grillePleine(gri)){
                jouer(gri, PION_A, &ligne, &colonne);
                afficher(gri, PION_B, COLONNE_DEBUT);
                if(estVainqueur(gri, ligne, colonne)){
                    vainqueur = PION_A;
                }
            }
            
        }
    }
    
    finDePartie(vainqueur);

    return EXIT_SUCCESS;
}

//----------------------------------fonction et procedure-----------------------------


//Initialise la grille en affectant la constante VIDE à chacun de ses éléments.
void initGrille(grille g){
    for (int ligne = 0; ligne < NBLIG; ligne++){
        for (int colonne = 0; colonne < NBCOL; colonne++){
            g[ligne][colonne] = VIDE;
        }
    }
}



/*Réalise l’affichage à l’écran du contenu de la grille avec les pions déjà joués. Cette procédure
affiche aussi, au-dessus de la grille, le prochain pion à tomber : il sera affiché au-dessus de la
colonne dont le numéro est donné en paramètre. Cette procédure commencera par effacer l’écran.*/
void afficher(grille g, char pion, int colonne){
    
    system("clear");
    
    printf("_______________\n");
    printf(" 1 2 3 4 5 6 7 \n");
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
    
    for (int c = 0; c < (colonne * 2) + 1; c++){
        printf(" ");
    }
    printf("%c\n", pion);
    
    
    for (int lig = 0; lig < NBLIG; lig++){
        printf("|");
        
        for (int col = 0; col < NBCOL; col++){
            printf("%c", g[lig][col]);
            printf("|");
        }
        printf("\n");
    }
}


//Teste si toutes les cases de la grille sont occupées ou non.
bool grillePleine(grille g){
    bool statut;
    int cpt = 0;
    statut = false;
    
    for (int col = 0; col < NBCOL; col++){
        if ((g[0][col] == PION_A) || (g[0][col] == PION_B)){
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

/*permet à un joueur de jouer son pion. La procédure fait appel à choisirColonne, afin que le
joueur indique la colonne dans laquelle il veut jouer ; puis fait appel à trouverLigne pour définir
la case où ajouter le pion.*/
void jouer(grille g, char pion, int *ligne, int *colonne){
    
    int col = COLONNE_DEBUT;

    do{
        *colonne = choisirColonne(g, pion, col);
        *ligne = trouverLigne(g, *colonne);
        
        
        if(*ligne == -1){
            printf("colonne pleine !!!\n");
        }
        
    }while(*ligne == -1);
    
    g[*ligne][*colonne] = pion;
    
}

/*Un joueur voit son pion au-dessus de la grille et cette fonction doit lui permettre de "déplacer"
son pion d’une colonne vers la gauche (par la touche ‘q’) ou d’une colonne vers la droite (par la
touche ‘d’). Après chaque déplacement, la grille est réaffichée. Le joueur peut finalement
choisir la colonne où il souhaite faire tomber son pion (par la touche ESPACE).
*/
int choisirColonne(grille g, char pion, int colonne){
    char choix, rc; //rc contient le retour chariot
    
    do{
        if (colonne == 6){
            do{
                printf("déplacer gauche : entrez 'q'\nplacer votre pion : espace\nvotre choix : ");
                scanf("%c%c", &choix, &rc);
                if(choix == 'd'){
                    printf("Colonne indisponible\n");
                }
                if((choix != 'q') && (choix != 'd') && (choix != ' ')){
                    printf("caractere eronné\n");
                }
                
            }while(choix == 'd' || ((choix != 'q') && (choix != ' ')));
        }else if(colonne == 0){
            do{
                printf("déplacer droite : entrez 'd'\nplacer votre pion : espace\nvotre choix : ");
                scanf("%c%c", &choix, &rc);
                if(choix == 'q'){
                    printf("Colonne indisponible\n");
                }
                if(choix != 'd' && (choix != 'q') && (choix != ' ')){
                    printf("caractere eronné\n");
                }
            }while(choix == 'q' || ((choix != 'd') && (choix != ' ')));
        }else{
            do{
                printf("déplacer gauche : entrez 'q'\ndéplacer droite : entrez 'd'\nplacer votre pion : espace\nvotre choix : ");
                scanf("%c%c", &choix, &rc);
                if(choix != 'd' && (choix != 'q') && (choix != ' ')){
                    printf("caractere eronné\n");
                }
            }while ((choix != 'q') && (choix != 'd') && (choix != ' '));
        }
        
        
        if (choix == 'd'){
            colonne += 1;
        } else if(choix == 'q'){
            colonne -= 1;
        }
        afficher(g, pion, colonne);
    }while(choix != ' ');
    
    return colonne;
}

/*Consiste à trouver la première case non occupée de la colonne. Si la colonne est pleine, la
fonction retourne -1.*/
int trouverLigne(grille g, int colonne){
    int indice = -1, ligne = NBLIG - 1;
    bool placer = false;
    
    while((placer != true) && (ligne >= 0)){
        if (g[ligne][colonne] == VIDE){
            indice = ligne;
            placer = true;
        }
        ligne -= 1;
    }
    
    return indice;
}

/*Regarde si un des deux joueurs à réussi à aligné au moins 4 pions et donc si un des deux joueurs à gagné*/
bool estVainqueur(grille g, int ligne, int colonne){
    bool gagner = false;
    
    for(int a = 0; a < 4; a++){
        if((g[ligne][a] == PION_A) && (g[ligne][a+1] == PION_A) && (g[ligne][a+2] == PION_A) && (g[ligne][a+3] == PION_A)){
            gagner = true;
        }
        if((g[ligne][a] == PION_B) && (g[ligne][a+1] == PION_B) && (g[ligne][a+2] == PION_B) && (g[ligne][a+3] == PION_B)){
            gagner = true;
        }
    }
        
    for(int b = 5; b > 2 ; b--){
        if((g[b][colonne] == PION_A) && (g[b-1][colonne] == PION_A) && (g[b-2][colonne] == PION_A) && (g[b-3][colonne] == PION_A)){
            gagner = true;
        }
        if((g[b][colonne] == PION_B) && (g[b-1][colonne] == PION_B) && (g[b-2][colonne] == PION_B) && (g[b-3][colonne] == PION_B)){
            gagner = true;
        }
    }
    
    
    
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 4; y++){
            if(g[x][y] == PION_A && g[x+1][y+1] == PION_A && g[x+2][y+2] == PION_A && g[x+3][y+3] == PION_A){
                gagner = true;
            }
            if(g[x][y] == PION_B && g[x+1][y+1] == PION_B && g[x+2][y+2] == PION_B && g[x+3][y+3] == PION_B){
                gagner = true;
            }
        }
    }
    
    
    for(int i = 3; i < 6; i++){
        for(int j = 0; j < 4; j++){
            if(g[i][j] == PION_A && g[i-1][j+1] == PION_A && g[i-2][j+2] == PION_A && g[i-3][j+3] == PION_A){
                gagner = true;
            }
            if(g[i][j] == PION_B && g[i-1][j+1] == PION_B && g[i-2][j+2] == PION_B && g[i-3][j+3] == PION_B){
                gagner = true;
            }
        }
    }
    
    return gagner;
}


//Affiche le résultat d’une partie lorsqu’elle est terminée.
void finDePartie(char pion){
    
    if (pion == PION_A){
        printf("Le joueur A à gagné");
    }else if (pion == PION_B){
        printf("Le joueur B à gagné");
    }else{
        printf("Egalité");
    }
    
}

//tire un des deux joueurs au hasard pour savoir qui commence
char tirage(){
    char joueur;
    srand(time(NULL));
    int r = rand() % 2;
    if (r == 1){
        joueur = PION_A;
    }
    else{
        joueur = PION_B;
    }
    return joueur;
}


