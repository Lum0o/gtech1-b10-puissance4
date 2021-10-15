#include <stdio.h>

int NBL = 6;
int NBC = 7;

int inittab(char tab[NBL][NBC]) {
    int l , c;
    for (l = 0; l<NBL ; l++) {
        for (c = 0; c<NBC ; c++) {
            tab[l][c] = ".";
        }
    }
}

int readtab(char tab[NBL][NBC]) {
    int l, c;
    for(l=0 ; l<NBL ; l++) {
        printf("\n---------------------\n");
            for(c=0 ; c<NBC ; c++) {
                printf("|%c|", tab[l][c]);
            }
    }
    printf("\n---------------------\n");
}

int main(void) {
    char tab[NBL][NBC];
    inittab(tab);
    readtab(tab);
}

