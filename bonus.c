
#include <stdio.h>
#include <stdbool.h>

bool TestVictory(int LastMove[],char Tab[][], char NBL, char MBC){
  int victory = 1;
  char token = Tab[LastMove[0]][LastMove[1]];

  for ( int i = 1; i<4 ; i++ ) {
    if ( LastMove[0] > -i && LastMove[1] > -i ){
      if ( Tab[LastMove[0]-i][LastMove[1]-i] == token ){
        victory = victory + 1
      }
      else {
      break }
    }
  }
  if (victory == 4) { return True }

  for ( int i = 1; i<4 ; i++ ) {
    if ( LastMove[0] < (NBL-i) && LastMove[1] < (NBC-i) ){
      if ( Tab[LastMove[0]-i][LastMove[1]-i] == token ){
        victory = victory + 1
    }
    else {
      break }                                                                                                            }                                                                                                                
  }
}
