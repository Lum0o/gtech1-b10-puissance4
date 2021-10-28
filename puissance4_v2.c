#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "bonus.h"

#define NBL_DEFAULT 6
#define NBC_DEFAULT 7
#define NBP_DEFAULT 2

int NBL = NBL_DEFAULT;
int NBC = NBC_DEFAULT;
int NBP = NBP_DEFAULT;

int player;            //switch d'un joueur à un autre

bool isThereAWinner;   // Notre variable pour arrêter le jeu en cas de victoire
bool wantToRestart;

int tokenCount;
int maxTokens;
int matchCount;

typedef struct{        //Info des joueurs
  char *name;
  char color;
  char token;
  int score;
}playerInfo;

char *tokens = NULL;        // Tableau des jetons appartenant aux joueurs
char **tab = NULL ;         // Tableau de jeu
int *nextLine = NULL ;      // Tableau pour déterminer sur quelle ligne le jeton va tomber dans la colonne
playerInfo *players = NULL; // Tableau contenant les données de tout les joueurs

char colors[] = "rvbjpc";   // Couleurs disponibles pour les joueurs
int LastMove[2];            // Tableau contenant les coordonnées du dernier coup joué utilisé pour le test de victoire

char **tab_malloc() {
  char **tab_ = (char**)malloc(NBL * sizeof(char*)); // "Les lignes"
  for(int l=0; l<NBL; l++)
    tab_[l] = (char*)malloc(NBC * sizeof(char));     // Les colonnes sont "attachées" à =tab[l]=
  return tab_;
}

int *nextLine_malloc() {
  int *nextLine_ = (int*)malloc( NBC * sizeof(int));
  return nextLine_;
}

playerInfo *players_malloc(){
  playerInfo *players_ = (playerInfo*)malloc(NBP * sizeof(playerInfo));
  return players_;
}

char *tokens_malloc(){
  char *tokens_ = (char*)malloc(NBP * sizeof(char));
  return tokens_;
}

void flushstdin() {//vidage du buffer
  int c;
  while((c = getchar()) != '\n' && c != EOF){}
}

void printColoredText(char color, char text[]){
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
    case 'p':
      printf("\033[0;35m");
      break;
    case 'c':
      printf("\033[0;36m");
      break;
    default:
      break;
    }
  printf("%s", &text);
  printf("\033[0m");
  }

void printColoredChar(char color, char token){
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
    case 'p':
      printf("\033[0;35m");
      break;
    case 'c':
      printf("\033[0;36m");
      break;
    case 'w':
      printf("\033[1;37m");
      break;
    default:
      break;
    }
  printf("%c", token);
  printf("\033[0m");
  }


void initTab(){
  tab = tab_malloc();
    for (int l=0; l<NBL; l++) {
        for (int c=0; c<NBC; c++) {
	  tab[l][c] = '.'; 
        }
    }
}

void initNextLine(int nbLine){ // nextLine[i] = la ligne où doit tomber le jeton   
  for (int l=0; l<nbLine ; l++){
    nextLine[l] = 0;
  }
  printf("\n");
}

char checkColorInput(char input){ // Vérification si la couleur en entrée existe
  while (true){
    for(int i=0; i<strlen(colors); i++){
      if(input==colors[i]) return input;
    }
    printf("\033[0;31mVous avez choisi une couleur inexistante, veuillez réessayer : \033[0m"); 
    scanf("%s", &input);
    flushstdin();
  }
}

void initPlayersInfo(){
  players = players_malloc();
  tokens = tokens_malloc();
  
  for (int i=0; i<NBP; i++){
    char *name;
    char color;
    char token;
    
    printf("\nJoueur %d, entrez votre nom : ", i+1);
    scanf("%s", &name);
    players[i].name = name;
    flushstdin();
    
    printf("Sélectionnez une couleur parmis ");
    for(int i=0; i<strlen(colors); i++){
      printColoredChar(colors[i], colors[i]);
      printf(" ");
    }
    printf(": ");
    scanf("%s", &color);
    players[i].color = checkColorInput(color);

    printf("Choisissez un caractère pour votre jeton : ");
    scanf("%s", &token);
    players[i].token = token;
    flushstdin();
  }
}


void printTab(){ // Affiche le tableau de jeu avec les couleurs des jetons 
  for (int l=0; l<NBL; l++){
        printf("\n ");
        for(int l = 0; l<NBC; l++)
	  printf("----");
	printf("-\n");
	
	for(int c=0; c<NBC; c++) {
          printf(" | ");
	  if(tab[l][c] == '.')
	    printColoredChar('w', tab[l][c]);	  
	  else{
	    for(int i=0; i<NBP; i++)
              if(tab[l][c] == players[i].token){
	        printColoredChar(players[i].color, tab[l][c]);
	        break;
	      }
	  }
	}
	 printf(" |");
  }
  printf("\n ");
  for(int l = 0; l<NBC; l++)
    printf("----");
  printf("-\n  ");

  for(int l = 0; l<NBC; l++)
    printf(" %d  ",( l+1 ));
  printf("\n\n");
}

void initGame(){
  player = 0;
  maxTokens = NBL*NBC;
  nextLine = nextLine_malloc() ; 
  matchCount = 1;
  initTab();
  printf("\n _____   _   _   _   _____   _____       ___   __   _   _____   _____        _   _ \n");
  printf("|  _  | | | | | | | /  ___/ /  ___/     /   | |  | | | /  ___| | ____|      | | | |\n");
  printf("| |_| | | | | | | | | |___  | |___     / /| | |   || | | |     | |__        | |_| |\n");
  printf("|  ___/ | | | | | | |___  | |___  |   / / | | | ||   | | |     |  __|       |___  |\n");
  printf("| |     | |_| | | |  ___| |  ___| |  / /  | | | | |  | | |___  | |___           | |\n");
  printf("|_|     |_____/ |_| /_____/ /_____/ /_/   |_| |_|  |_| |_____| |_____|          |_|\n\n");
  printf("Pour gagner c'est simple, il vous faudra aligner 4 mêmes jetons à l'horizontale, à la verticale ou en diagonale !\n\n");
  printf("TABLEAU : %d * %d\n", NBL, NBC);
  printf("JOUEURS : %d\n", NBP);
  printTab();
  initPlayersInfo();
}

void resetGame(){
  initTab();
  initNextLine(NBC);
  isThereAWinner = false;
  tokenCount = 0;
  printf("\n\n\nROUND %d", matchCount);
  printf("\n--------");
}

void tokenInput(int nbc, int nbl){               // Insère le jeton du joueur grâce à l'index de nextLine
  
  tab[(NBL-1)-nbl][nbc] = players[player].token; // le tableau des lignes se lit à l'envers pour le jeu
  LastMove[0] = (NBL-1)-nbl;
  LastMove[1] = nbc;                             // attribution des coordonnées du dernier coup
  nextLine[nbc]++;                               // le prochain jeton de cette colonne sera au-dessus
  tokenCount++;
}

void changePlayer(){
  player++;
  if(player == NBP) player = 0;
  printf("C'est à vous, ");
  printColoredText(players[player].color, players[player].name);
  printf("\n");
}

int inputCLN(){
  int nb;
  printf("Choisissez une colonne : ");
  int success = scanf("%d", &nb);

  while(true){
    if (success > 0){ //si le scanf a bien été exécuté = pas de lettre en entrée
    
      if (nb >= 1 && nb <= NBC  && nextLine[nb-1] < NBL) return nb; //tant que le nombre n'est pas une bonne colonne
      else if (nextLine[nb-1] >= NBL){
        printf("\033[0;31mLa colonne est déjà pleine, choisissez-en une autre : \033[0m");
      }
      else if (nb < 1 || nb > NBC){
        printf("\033[0;31mVous avez choisi une colonne inexistante ! Réessayez : \033[0m");
      }
    }
    else printf("\033[0;31mAttention ! Vous avez entré une lettre ! Réessayez : \033[0m");   

    flushstdin();
    success = scanf("%d", &nb);
  }
}

void printResult(){
  printTab();
  if (tokenCount == maxTokens && !isThereAWinner){
    printf("\n------------------------------------\n\n");
    printf("Vous êtes à égalité !");
  }
  else {
    players[player].score++;
    printf("\n------------------------------------\n\n");
    printColoredText(players[player].color, players[player].name);
    printf(" a gagné la partie !!");
  }
  printf("\n\nSCORE :");

  for(int i=0; i<NBP; i++){
    printf("\n-> ");
    printColoredText(players[i].color, players[i].name);
    printf(" avec %d victoire(s)", players[i].score);
  }
  printf("\n\n------------------------------------\n");
}

bool askRestart(){
  char input;
  printf("Voulez-vous rejouer ?\nTapez 'Y' pour OUI ou une autre touche pour fermer le jeu : ");

  int success = scanf("%s", &input);
  if (success > 0 && input == 'y') return true;
  else return false;
}

void main(int argc, char* argv[]){
  if (argc >= 2){
    NBL = atoi(argv[1]);
    NBC = atoi(argv[2]);
  }
  if (argc >= 3) NBP = atoi(argv[3]);
 
  initGame();
  do{ // boucle de rejouabilité
    resetGame();
    int nbc;
    
    do {//boucle de jeu
      printTab();
      changePlayer();
      nbc = inputCLN(); //input joueur (colonne)
      tokenInput(nbc-1, nextLine[nbc-1]); // n-1 (liste commence par 0)
      
      if(tokenCount > 6) //Impossible de gagner avant
        isThereAWinner = TestVictory(LastMove,NBL,NBC);
    
    }while (!isThereAWinner && tokenCount != maxTokens);
    matchCount++;
    printResult();
    wantToRestart = askRestart();
    
  }while (wantToRestart); // Recommence la partie en gardant les noms et couleurs
  printf("\n***FIN DU JEU***\n\n");
}


