/*
TODO : Vérification si gagnant (ligne, colonne et diagonale) *à discuter comment faire*
       Améliorer l'affichage du tableau (ajouter des couleurs)
       Se mettre au point tous les deux sur le fonctionnement du code pour qu'on soit parfait <3
       Le code est pas mal opti je pense (peut-être trop de fonctions ? mais je pense que c'est cool comme ça)
 */

#include <stdio.h>
#include <stdbool.h>

#define NBL 6
#define NBC 7

bool player; // false = joueur 1, true = joueur 2
bool isGameFinished = false; // Notre variable pour arrêter le jeu

char tokens[] = "ox"; // Tableau des jetons lié à player (changement automatique du jeton sans test)
char tab[NBL][NBC]; // Tableau pour le jeu
int nextLine[NBC]; // Tableau des index pour déterminer où le jeton DOIT tomber

void initTab(void){
    for (int l=0; l<NBL; l++) {
        for (int c=0; c<NBC; c++) {
	  tab[l][c] = '.'; 
        }
    }
}

void initNextLine(int nbLine){  
  for (int l=0; l<nbLine ; l++){
    nextLine[l] = 0; // pour faire tomber le jeton
  }
  printf("\n");
}

void printTab(void){ /* à améliorer : - affichage trop étroit
		                      - ajouter couleur pour jeton  */
  for (int l=0; l<NBL; l++){ // parcours les lignes
        printf("\n---------------\n");
	
	for(int c=0; c<NBC; c++) { // parcours les colonnes
                printf("|%c", tab[l][c]);
            }
	    printf("|");
    }
    printf("\n---------------\n");
    printf(" 1 2 3 4 5 6 7\n");
}

void playerInput(int playerInput, int next){ // Insère le jeton du joueur
  
  tab[5-next][playerInput] = tokens[player]; // le tableau se lit à l'envers donc 5-next pour inverser
  nextLine[playerInput]++; // le prochain jeton sera au-dessus
}

bool initGame(){
  initTab();
  printTab();
  initNextLine(NBC);
  player = 0;
}

void changePlayer(void){// à améliorer (message et structure)
  player = !player; // ou player ^= 1;
  if (player == false) printf("C'est au tour du joueur 1");
  else printf("C'est au tour du joueur 2");
  printf("\n");
}
    
void main(void){
  initGame();
  int nb;

  do { // dans TOUS les cas on démarre la partie
  printf("Entre un nombre entre 1 et 7 : ");
  scanf("%d", &nb);
  playerInput(nb-1, nextLine[nb-1]); // n-1 (liste commence par 0)
  printTab();
  changePlayer();
  
  } while(!isGameFinished);
}

