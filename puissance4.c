#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bonus.h"

#define NBL_DEFAULT 6
#define NBC_DEFAULT 7

int NBL = NBL_DEFAULT;
int NBC = NBC_DEFAULT;

bool player; // false = joueur 1, true = joueur 2
bool isThereAWinner; // Notre variable pour arrêter le jeu en cas de victoire
bool wantToRestart;

int tokenCount;
int maxTokens;
int matchCount;

//Info des joueurs
typedef struct{
  char *name;
  char color;
  int score;
}playerInfo;

playerInfo players[2];

char tokens[] = "ox"; // Tableau des jetons lié à player (changement automatique à chaque tour du jeton)
char **tab = NULL ;
int *nextLine = NULL ; // Tableau des index pour déterminer où le jeton DOIT tomber
int LastMove[2]; // Tableau contenant les coordonnées du dernier coup joué

char **tab_malloc() {
  char **tab_ = (char**)malloc(NBL * sizeof(char*)); // "Les lignes"
  for(int l=0; l<NBL; l++) // Pour chaque "ligne"
    tab_[l] = (char*)malloc(NBC * sizeof(char)); // Les colonnes sont "attachées" à =tab[l]=
  return tab_;
}

int *nextLine_malloc() {
  int *nextLine_ = (int*)malloc( NBC * sizeof(int));
  return nextLine_;
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
    case 'w':
      printf("\033[1;37m");
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

char checkColorInput(char input){ // Vérification si la couleur entrée existe
  while ( input != 'r' && input != 'b' && input != 'j' && input != 'v' ) {
      printf("Vous avez choisi une couleur inexistante, veuillez réessayer : ");
      scanf("%s", &input);
      }
  return input;
}

void initPlayersInfo(){

  for (int i=0; i<2; i++){
    char *name;
    char color;
    
    printf("\nJoueur %d, entrez votre nom : ", i+1);
    scanf("%s", &name);
    players[i].name = name;
    
    printf("Choisissez une couleur entre \033[0;31mr\033[0m, \033[0;32mv\033[0m, \033[0;34mb\033[0m, \033[1;33mj\033[0m) : ");
    scanf("%s", &color);
    players[i].color = checkColorInput(color);
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
	  else if(tab[l][c] == tokens[0])
	    printColoredChar(players[0].color, tab[l][c]);
	  else if(tab[l][c] == tokens[1]) 
	    printColoredChar(players[1].color, tab[l][c]);
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
  player, wantToRestart = true;
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
  printTab();
  initPlayersInfo();
}

void resetGame(){
  initTab();
  initNextLine(NBC);
  player = !player;
  tokenCount = 0;
  printf("\n\n\nROUND %d", matchCount);
  printf("\n--------");
}

void tokenInput(int playerInput, int next){ // Insère le jeton du joueur grâce à l'index de nextLine
  
  tab[5-next][playerInput] = tokens[player]; // le tableau se lit à l'envers donc 5-next pour inverser
  LastMove[0] = 5-next;
  LastMove[1] = playerInput; // attribution des coordonnées du dernier coup
  nextLine[playerInput]++; // le prochain jeton sera au-dessus
  tokenCount++;
}

void changePlayer(){
  player = !player; // ou player ^= 1;
  printf("C'est au tour de ");
  printColoredText(players[player].color, players[player].name);
  printf("\n");
}

int inputNbr(){
  int nb;
  printf("Choisissez une colonne : ");
  scanf("%d", &nb);
  
  //A TERMINER => voir intervenant
  while(true){ //Tant que l'utilisateur ne rentre pas une bonne colonne
    
    if (nb >= 1 && nb <= 7 && nextLine[nb-1] < 6) return nb;
    else if (nextLine[nb-1] >= 6){
      printf("La colonne est déjà pleine, choisissez-en une autre : ");
      scanf("%d", &nb);
    }
    else if (nb < 1 || nb > 7 && !(((nb = getchar()) != '\n') && nb != EOF)){
      printf("Vous avez choisi une colonne inexistante ! Réessayez : ");
      scanf("%d", &nb);
    }
    else{
      printf("Attention ! Vous avez entré une lettre ! Réessayez : ");
      while((nb = getchar()) != '\n'){
        scanf("%d", &nb);
      }
    }
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
  printf("\n\nSCORE : \n");
  printf("-> ");
  printColoredText(players[0].color, players[0].name);
  printf(" avec %d victoire.", players[0].score);
  printf("\n-> ");
  printColoredText(players[1].color, players[1].name);
  printf(" avec %d victoire.", players[1].score);
  printf("\n\n------------------------------------\n");
}

bool askRestart(){
  char tmp;
  printf("Voulez-vous rejouer ?\nTapez 'Y' pour OUI ou une autre touche pour fermer le jeu : ");
  scanf("%s", &tmp);
  if (tmp == 'y') return true;
  else return false;
}

void main(int argc, char* argv[]){
  if (argc > 2){
    NBL = atoi(argv[1]);
    NBC = atoi(argv[2]);
    printf("%d , %d", NBL, NBC);
  }
  initGame();
  do{
    resetGame();
    int nb;
    do {
      printTab();
      changePlayer();
      nb = inputNbr();
      tokenInput(nb-1, nextLine[nb-1]); // n-1 (liste commence par 0)
      isThereAWinner = TestVictory(LastMove,NBL,NBC);
  
    }while (!isThereAWinner && tokenCount != maxTokens); // Tant que pas de victoire/nulle
    matchCount++;
    printResult();
    wantToRestart = askRestart();
    
  }while (wantToRestart); // Recommence la partie en gardant les noms et couleurs
  printf("***FIN DU JEU***");
}


