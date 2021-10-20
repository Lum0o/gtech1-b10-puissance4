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
bool isGameNull;

int count;
int maxCount;

char *p1name;
char p1color; // 32 caractères + '\0'
char *p2name;
char p2color;

bool isGameFinished; // Notre variable pour arrêter le jeu

char tokens[] = "ox"; // Tableau des jetons lié à player (changement automatique à chaque tour du jeton)
char tab[NBL][NBC]; // Tableau pour le jeu
int nextLine[NBC]; // Tableau des index pour déterminer où le jeton DOIT tomber
int LastMove[2]; // tableau contenant les coordonnées du dernier coup joué

void setNameColor(char color, char text[]){
  switch (color)
    {
    case 'r':
      printf("\033[0;31m");
      break;
    case 'j':
      printf("\033[1;33m");
      break;
    case 'b':
      printf("\033[0;34m");
      break;
    case 'v':
      printf("\033[0;32m");
      break;
    default:
      break;
    }
  printf("%s", &text);
  printf("\033[0m");
  }

void setTokenColor(char color, char token){
  switch (color)
    {
    case 'r':
      printf("\033[0;31m");
      break;
    case 'j':
      printf("\033[1;33m");
      break;
    case 'b':
      printf("\033[0;34m");
      break;
    case 'v':
      printf("\033[0;32m");
      break;
    case 'w':
      printf("\033[1;37m");
    default:
      break;
    }
  printf("%c", token);
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

void printTab(char playerColor){ /* à améliorer : - affichage trop étroit
		                      - ajouter couleur pour jeton  */
  for (int l=0; l<NBL; l++){ // parcours les lignes
        printf("\n -----------------------------\n");
	
	for(int c=0; c<NBC; c++) { // parcours les colonnes
          printf(" | ");
	  if(tab[l][c] == '.')
	    setTokenColor('w', tab[l][c]);
	  else if(tab[l][c] == tokens[0])
	    setTokenColor(p1color, tab[l][c]);
	  else if(tab[l][c] == tokens[1])
	    setTokenColor(p2color, tab[l][c]);
         }
	 printf(" |");
    }
    printf("\n -----------------------------\n");
    printf("   1   2   3   4   5   6   7  \n");
}

void playerInput(int playerInput, int next){ // Insère le jeton du joueur
  
  tab[5-next][playerInput] = tokens[player]; // le tableau se lit à l'envers donc 5-next pour inverser
  LastMove[0] = 5-next;
  LastMove[1] = playerInput; // attribution des coordonnées du dernier coup
  nextLine[playerInput]++; // le prochain jeton sera au-dessus
  count++;
}

void initPlayersInfo(){
    printf("\nJoueur 1, entrez votre nom : ");
    scanf("%s", &p1name);
    printf("\nChoisissez une couleur (r=rouge, v=vert, b=bleu, j=jaune) : ");
    scanf("%s", &p1color);
    while ( p1color != 'r' && p1color != 'b' && p1color != 'j' && p1color != 'v' ) {
      printf("vous avez rentré une couleur inexistante, veuillez réessayer");
      scanf("%s", &p1color);
      }
    printf("\nJoueur 2, entrez votre nom : ");
    scanf("%s", &p2name);
    printf("\nChoisissez une couleur (r=rouge, v=vert, b=bleu, j=jaune) : ");
    scanf("%s", &p2color);
    while ( p2color != 'r' && p2color != 'b' && p2color != 'j' && p2color != 'v' ) {
      printf("vous avez rentré une couleur inexistante, veuillez réessayer");
      scanf("%s", &p2color);
      }
    printf("\n");
}

void initGame(){
  player = true;
  count = 0;
  maxCount = NBL*NBC;
  initTab();
  printf("\n _____   _   _   _   _____   _____       ___   __   _   _____   _____        _   _ \n");
  printf("|  _  | | | | | | | /  ___/ /  ___/     /   | |  | | | /  ___| | ____|      | | | |\n");
  printf("| |_| | | | | | | | | |___  | |___     / /| | |   || | | |     | |__        | |_| |\n");
  printf("|  ___/ | | | | | | |___  | |___  |   / / | | | ||   | | |     |  __|       |___  |\n");
  printf("| |     | |_| | | |  ___| |  ___| |  / /  | | | | |  | | |___  | |___           | |\n");
  printf("|_|     |_____/ |_| /_____/ /_____/ /_/   |_| |_|  |_| |_____| |_____|          |_|\n\n");
  printTab('w');
  initNextLine(NBC);
  initPlayersInfo();
}

void changePlayer(void){// à améliorer (message et structure)
  player = !player; // ou player ^= 1;
  printf("C'est au tour de ");
  if (!player){
    setNameColor(p1color, p1name);//Changer 'r' en couleur du joueur
    printTab(p1color);
  }
  else{
    setNameColor(p2color, p2name);
    printTab(p2color);
  }
  printf("\n");
}

int inputNbr(){
  int nb;
  printf("Entre un nombre entre 1 et 7 : ");
  scanf("%d", &nb);
  while ( nb < 1 || nb > 7 ){
    printf("Votre chiffre n'est pas compris entre 1 et 7 réesayez :");
    scanf("%d", &nb);
    }
  return nb;
}

void printResult(){
  if (count == maxCount){
    printf("\n------------------------------------\n\n");
    printf("Les deux joueurs ont fait égalité !");
    printf("\n\n------------------------------------\n");
  }
  else {
    if (player){
      printf("\n------------------------------------\n\n");
      setNameColor(p2color , p2name);
      printf(" à gagné la partie !!");
      printf("\n\n------------------------------------\n");
    }
    else {
      printf("\n------------------------------------\n\n");
      setNameColor(p1color , p1name);
      printf(" à gagné la partie !!");
      printf("\n\n------------------------------------\n");
    }
  }
}


void main(void){
  initGame();
  int nb;
  
  do { // dans TOUS les cas on démarre la partie
  changePlayer();
  nb = inputNbr();
  playerInput(nb-1, nextLine[nb-1]); // n-1 (liste commence par 0)
  isGameFinished = TestVictory(LastMove,tab,NBL,NBC);
  
  } while(!isGameFinished && count != maxCount);
  printTab(p1color);
  printResult();
}

