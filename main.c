#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"
#include "files.h"

int main()
{
    // ALLOCATIONS DYNAMIQUES
    Arbre *arbre;
    arbre = (Arbre*)malloc(sizeof(Arbre));
    Maillon *liste_occ, *liste_dic;
    liste_occ = (Maillon*)malloc(sizeof(Maillon));
    liste_dic = (Maillon*)malloc(sizeof(Maillon));

    //OUVERTURE DES FICHIERS .TXT
    FILE *input, *binary, *dictionnaire;
    input = fopen("input.txt","r");
    binary = fopen("binary.txt","r");
    dictionnaire = fopen("dictionnaire.txt","w");

    read_txt();
    printf("%d characters in input.txt\n",nbr_char(input));
    printf("%d characters in binary.txt\n",nbr_char(binary));
    liste_occ = occurrences();
    arbre = huffman(&liste_occ, nbr_char(input));
    write_dictionnary(&arbre, dictionnaire, &liste_dic);

    //FERMETURE DES FICHIERS .TXT
    fclose(input);
    fclose(binary);
    fclose(dictionnaire);

    //LIBERATION MEMOIRE
    free(arbre);
    free(liste_occ);
    free(liste_dic);
}
