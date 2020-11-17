#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

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
void write_binary (char caractere);
void read_txt ();
int nbr_char(FILE *fichier);

// PARTIE 2
Maillon occurrences();
char minimum(Maillon *liste_occ);
Noeud huffman(Maillon *liste_occ, int nbr);
void write_dictionnary (Noeud *arbre, FILE *dictionnaire);

#endif // FONCTIONS_H_INCLUDED
