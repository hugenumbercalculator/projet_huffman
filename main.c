#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"
#include "files.h"

int main()
{
    Noeud *arbre;
    FILE *input, *binary, *dictionnaire;
    input = fopen("input.txt","r");
    binary = fopen("binary.txt","r");
    dictionnaire = fopen("dictionnaire.txt","w");

    read_txt();
    printf("%d characters in input.txt\n",nbr_char(input));
    printf("%d characters in binary.txt\n",nbr_char(binary));

    //write_dictionnary(&arbre, dictionnaire);

    fclose(input);
    fclose(binary);
    fclose(dictionnaire);
}
