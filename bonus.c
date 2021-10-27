
#include <stdio.h>
#include <stdbool.h>
extern char** tab;

bool TestVictory(int LastMove[2], char NBL, char NBC){
  int victory = 1;
  char token = tab[LastMove[0]][LastMove[1]];

// Vérification de sortie de tableau -> Vérification des jetons en haut à gauche
  for ( int i = 1; i<4 ; i++ ) {
    if ( LastMove[0] > (i-1) && LastMove[1] > (i-1) ){
      if ( tab[LastMove[0]-i][LastMove[1]-i] == token ){
        victory = victory + 1;
      }
      else {
        break; }
    }
    else {
      break; }
  }
  if (victory >= 4) { return true; } // >= dans le cas d'un puissance 5

  /* ici victory n'est pas remis à 1 car on vérifie ensuite les valeurs en bas à droite
     qui sont dans la même diagonale ( permet donc de détecter les puissances 4 dans le
     cas où le dernier jeton est mis au milieu des 3 autres*/

  for ( int i = 1; i<4 ; i++ ) {
    if ( LastMove[0] < (NBL-i) && LastMove[1] < (NBC-i) ){
      if ( tab[LastMove[0]+i][LastMove[1]+i] == token ){
        victory = victory + 1;
      }
      else {
        break; }
    }
    else {
      break; }
  }
  if (victory >= 4) { return true; }
  victory = 1; // fin de la diagonale haut gauche / bas droite --> remise de victory à 1
  // début des vérifications pour la diagonale haut droite / bas gauche

  for ( int i = 1;  i<4 ; i++ ) {
    if ( LastMove[0] < (NBL-i) && LastMove[1] > (i-1) ){
      if ( tab[LastMove[0]+i][LastMove[1]-i] == token ){
        victory = victory + 1;
      }
      else {
        break; }
    }
    else {
      break; }
  }
  if (victory >= 4) { return true; }

  for ( int i = 1; i<4 ; i++) {
    if ( LastMove[0] > (i-1) && LastMove[1] < (NBC-i) ){
      if ( tab[LastMove[0]-i][LastMove[1]+i] == token ){
        victory = victory + 1;
      }
      else {
        break; }
    }
    else {
      break; }
  }
  if (victory >= 4) { return true; }
  victory = 1; // fin de la diagonale haut droite / bas gauche --> remise de victory à 1
  // début des vérifications pour les valeurs horizontales

  for ( int i = 1; i<4 ; i++ ) {
    if ( LastMove[1] > (i-1) ) {
      if ( tab[LastMove[0]][LastMove[1]-i] == token ){
        victory = victory + 1;
      }
      else {
        break; }
    }
    else {
      break; }
  }
  if (victory >= 4) { return true; }

  for ( int i = 1; i<4 ; i++ ) {
    if ( LastMove[1] < (NBC-i) ){
      if ( tab[LastMove[0]][LastMove[1]+i] == token ){
        victory = victory + 1;
      }
      else {
        break; }
    }
    else {
      break; }
  }
  if (victory >= 4) { return true; }
  victory = 1; // fin des vérifications pour les valeurs horizontales --> remise< de victory à 1
  /* début des vérifications pour les valeurs verticales (uniquement sous
     le dernier jeton car il ne peut y en avoir au dessus */

  for ( int i= 1; i<4 ; i++ ) {
    if ( LastMove[0] < (NBL-i) ){
      if ( tab[LastMove[0]+i][LastMove[1]] == token ){
        victory = victory + 1;
      }
      else {
        break; }
    }
    else {
      break; }
  }
  if (victory >= 4) { return true; }
  else { return false; }
}
