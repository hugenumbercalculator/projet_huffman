#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <stdbool.h>

typedef struct Maillon{
    char caractere;
    int occurrences;
    struct Maillon *next;
}Maillon;

typedef struct Noeud{
    int poids;
    struct Noeud *nd, *ng;
    struct Maillon *md, *mg;
}Noeud;

// PARTIE 1
void write_bin (char caractere);
void read_txt ();
int nbr_char(FILE *fichier);

// PARTIE 2
Maillon occurrences();
char minimum(Maillon *liste_occ);
Noeud huffman(Maillon *liste_occ, int nbr);

#endif // FONCTIONS_H_INCLUDED
