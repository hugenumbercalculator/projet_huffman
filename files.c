#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "fonctions.h"

void enfiler(File *file, Arbre *a)
{
    Arbre *new_node;
    new_node = (Arbre*)malloc(sizeof(Arbre));
    new_node->noeud = (Maillon*)malloc(sizeof(Maillon));
    new_node->noeud->caractere = a->noeud->caractere;
    new_node->noeud->occurrences = a->noeud->occurrences;

    if (file->first != NULL){ //on se positionne à la fin pour enfiler en queue
        Arbre *actual_tree = file->first;
        while (actual_tree->noeud->next != NULL){
            actual_tree = actual_tree->noeud->next;
        }
        actual_tree->noeud->next = new_node;
    }
    else file->first = new_node; //on enfile en tête de file dans le cas où elle est vide
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
