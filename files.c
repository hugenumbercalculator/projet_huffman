#include <stdio.h>
#include <stdlib.h>
#include "files.h"

void enfiler(File *file, char caractere)
{
    Element *nouveau = malloc(sizeof(Element));
    nouveau->info = caractere;
    nouveau->next = NULL;

    if (file->first != NULL)
    {
        Element *elementActuel = file->first;
        while (elementActuel->next != NULL){
            elementActuel = elementActuel->next;
        }
        elementActuel->next = nouveau;
    }
    else file->first = nouveau;
}

char defiler(File *file)
{
    char caractere;

    if(file->first){
        Element *elementdefile = file->first;
        caractere = elementdefile->info;
        file->first = elementdefile->next;
        free(elementdefile);
    }
    return caractere;
}
