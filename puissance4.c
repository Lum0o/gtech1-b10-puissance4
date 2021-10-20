/*
TODO : Vérification si gagnant (ligne, colonne et diagonale) *à discuter comment faire*
       Améliorer l'affichage du tableau (ajouter des couleurs)
       Se mettre au point tous les deux sur le fonctionnement du code pour qu'on soit parfait <3
       Le code est pas mal opti je pense (peut-être trop de fonctions ? mais je pense que c'est cool comme ça)
 */

#include <stdio.h>
#include <stdbool.h>
#include "bonus.c"

#define NBL 6
#define NBC 7

bool player; // false = joueur 1, true = joueur 2
char *p1name;
char p1color;
char *p2name;
char p2color;
char pInfo[2][33]; // 32 caractères + '\0'

bool isGameFinished; // Notre variable pour arrêter le jeu

char tokens[] = "ox"; // Tableau des jetons lié à player (changement automatique à chaque tour du jeton)
char tab[NBL][NBC]; // Tableau pour le jeu
int nextLine[NBC]; // Tableau des index pour déterminer où le jeton DOIT tomber
int LastMove[2]; // tableau contenant les coordonnées du dernier coup joué

void setColor(char color, char text[]){
  switch (color)
    {
    case 'r':
      printf("\033[0;31m");
      break;
    case 'y':
      printf("\033[1;33m");
      break;
    case 'b':
      printf("\033[0;34m");
      break;
    case 'g':
      printf("\033[0;32m");
      break;
    default:
      break;
    }
  printf("%s", &text);
  printf("\033[0m");
  }

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
  LastMove[0] = 5-next;
  LastMove[1] = playerInput; // attribution des coordonnées du dernier coup
  nextLine[playerInput]++; // le prochain jeton sera au-dessus
}

void initPlayersInfo(){
  for (int i=0; i<2; i++){
    printf("\nJoueur %d, entrez votre nom : ", i+1);
    scanf("%s", &pInfo[i][0]);
    printf("\nChoisissez une couleur (r=rouge, v=vert, b=bleu, j=jaune) : ");
    scanf("%c", &pInfo[i][1]);
  }
}

void initGame(){
  player = false;
  initTab();
  printTab();
  initNextLine(NBC);
  initPlayersInfo();
}

void changePlayer(void){// à améliorer (message et structure)
  player = !player; // ou player ^= 1;
  printf("C'est au tour de ");
  if (!player){  
    setColor(p1color, p1name);//Changer 'r' en couleur du joueur 
  }
  else{
    setColor(p2color, p2name);
  }
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
  isGameFinished = TestVictory(LastMove,tab,NBL,NBC);

  } while(!isGameFinished);
  
}

