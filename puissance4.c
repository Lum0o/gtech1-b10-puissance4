#include <stdio.h>
#include <stdbool.h>
#include "bonus.c"

#define NBL 6
#define NBC 7

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
}playerInfo;

playerInfo players[2];

char *p1name;
char p1color;
char *p2name;
char p2color;

char tokens[] = "ox"; // Tableau des jetons lié à player (changement automatique à chaque tour du jeton)
char tab[NBL][NBC]; // Tableau pour le jeu
int nextLine[NBC]; // Tableau des index pour déterminer où le jeton DOIT tomber
int LastMove[2]; // Tableau contenant les coordonnées du dernier coup joué

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
        printf("\n -----------------------------\n");
	
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
    printf("\n -----------------------------\n");
    printf("   1   2   3   4   5   6   7  \n\n");
}

void initGame(){
  player, wantToRestart = true;
  maxTokens = NBL*NBC;
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
  printf("\n\n\nROUND %d", matchCount);
  printf("\n--------");
}

void resetGame(){
  initTab();
  initNextLine(NBC);
  tokenCount = 0;
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
    printf("\n\n------------------------------------\n");
  }
  else {
    if (player){
      printf("\n------------------------------------\n\n");
      printColoredText(players[1].color, players[1].name);
      printf(" a gagné la partie !!");
      printf("\n\n------------------------------------\n");
    }
    else {
      printf("\n------------------------------------\n\n");
      printColoredText(players[0].color, players[0].name);
      printf(" a gagné la partie !!");
      printf("\n\n------------------------------------\n");
    }
  }
}

bool askRestart(){
  char tmp;
  printf("Voulez-vous rejouer ?\nTapez 'Y' pour OUI ou une autre touche pour fermer le jeu : ");
  scanf("%s", &tmp);
  if (tmp == 'y') return true;
  else return false;
}

void main(void){
  initGame();
  
  do{
    resetGame();
    int nb;
    do {
      printTab();
      changePlayer();
      nb = inputNbr();
      tokenInput(nb-1, nextLine[nb-1]); // n-1 (liste commence par 0)
      isThereAWinner = TestVictory(LastMove,tab,NBL,NBC);
  
    }while (!isThereAWinner && tokenCount != maxTokens); // Tant que pas de victoire/nulle
    matchCount++;
    printResult();
    wantToRestart = askRestart();
    
  }while (wantToRestart); // Recommence la partie en gardant les noms et couleurs
}

