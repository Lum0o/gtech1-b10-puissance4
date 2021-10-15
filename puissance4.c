#include <stdio.h>
#include <stdbool.h>

int NBL = 6;
int NBC = 7;
bool player = 0;

int inittab(char tab[NBL][NBC]) {
    int l, c;
    for (l = 0; l<NBL ; l++) {
        for (c = 0; c<NBC ; c++) {
            tab[l][c] = '.';
        }
    }
    return tab;
}

int initNextLine(int nbLine){
  int l;
  int tab[7];
  
  for (l=0; l<nbLine ; l++){
    tab[l] = 0;
    printf("%d", tab[l]);
  }
  printf("\n");
}

int readtab(char tab[NBL][NBC]) {
    int l, c;
    for(l=0 ; l<NBL ; l++) {
        printf("\n---------------\n");
            for(c=0 ; c<NBC ; c++) {
                printf("|%c", tab[l][c]);
            }
	    printf("|");
    }
    printf("\n---------------\n");
    printf(" 1 2 3 4 5 6 7\n");
}

int playerInput(int NBC, char tab[], int next[]){
   if(player==0) tab[NBC, next[NBC-1]] = '0';
   else tab[NBC, next[NBC-1]] = 'x';
}

int initGame(){
  int nextLine[NBC];
  char tab = inittab;
  readtab(tab);
  bool player = 0;
  initNextLine(NBC);
  
  return player;
}

int changePlayer(){
  !player;
  if (player == false)
  printf("C'est au tour du joueur 1");
  else printf("C'est au tour du joueur 2");
}
    
int main(void) {
  initGame();
  printf("Joueur 1, à toi de jouer !\n");
  int nb = scanf("Entrer un numéro de colonne [1:7] : ");
  playerInput(nb, tab);
  
    
}

