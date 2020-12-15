#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"
#include "files.h"

void print_liste_occ( Maillon *liste_occ)
{
    while(liste_occ != NULL)
    {
        printf("%c:%d\n",liste_occ->caractere,liste_occ->occurrences);
        liste_occ = liste_occ->next;
    }
}


void print_arbre(Arbre *a)
{
    if (!a) return;
    printf("%d ",a->noeud->occurrences);
    print_arbre(a->sag);
    print_arbre(a->sad);
}

void print_file(File *f)
{
    while (f->first->noeud->next != NULL){
        printf("%c:%d\n", f->first->noeud->caractere, f->first->noeud->occurrences);
        f->first->noeud = f->first->noeud->next;
    }
}
