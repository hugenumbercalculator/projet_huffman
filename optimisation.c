#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "optimisation.h"
#include "fonctions.h"
#include "files.h"
#include "test.h"

int taille_LDC(LDC *liste)
{
    int taille = 0;
    LDC *temporaire;
    temporaire = liste;

    if (liste == NULL) return 0;
    while (temporaire != NULL){
        taille ++;
        temporaire = temporaire->next;
    }
    return taille;
}

LDC* dichotomie(LDC *liste, char caractere, int taille)
{
    LDC *temporaire;
    temporaire = liste;

    for (int i=0; i<(taille/2); i++){
        temporaire = temporaire->next;
    }
    if (temporaire->occurrences > liste->caractere){
        dichotomie(liste, caractere, taille/2);
    }
    else{
        dichotomie(liste, caractere, taille/2);
    }
}
