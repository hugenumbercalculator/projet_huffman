#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "fonctions.h"

void enfiler(File *file, Arbre *a)
{
    Arbre *new_tree = malloc(sizeof(Arbre));
    new_tree->noeud->caractere = a->noeud->caractere;
    new_tree->noeud->occurrences = a->noeud->occurrences;

    if (file->first)
    {
        Arbre *actual_tree = file->first;
        while (actual_tree->noeud->next){
            actual_tree = actual_tree->noeud->next;
        }
        actual_tree->noeud->next = new_tree;
    }
    else file->first = new_tree;
}

Arbre* defiler(File *file)
{
    Arbre *tree;
    if(file->first){
        Arbre *actual_tree = file->first;
        tree = actual_tree;
        file->first = actual_tree->noeud->next;
        free(actual_tree);
    }
    return tree;
}
