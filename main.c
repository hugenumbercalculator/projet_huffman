#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"
#include "files.h"

int main()
{
    // ALLOCATIONS DYNAMIQUES
    Arbre *arbre_huffman;
    arbre_huffman = (Arbre*)malloc(sizeof(Arbre));
    Maillon *liste_occ, *liste_dic;
    liste_occ = (Maillon*)malloc(sizeof(Maillon));
    liste_dic = (Maillon*)malloc(sizeof(Maillon));

    //OUVERTURE DES FICHIERS .TXT
    FILE *input, *binary, *dictionnary;
    input = fopen("input.txt","r");
    binary = fopen("binary.txt","r");
    dictionnary = fopen("dictionnary.txt","w");

    //CORPS
    read_txt();
    printf("%d characters in input.txt\n",nbr_char(input));
    printf("%d characters in binary.txt\n",nbr_char(binary));
    liste_occ = occurrences();
    printf("occurences OK\n");
    while(liste_occ)
    {
        printf("%d ",liste_occ->occurrences);
        liste_occ = liste_occ->next;
    }
    //arbre_huffman = create_huffman_tree(&liste_occ, nbr_char(input));
    //write_dictionnary(&arbre_huffman, &dictionnary, &liste_dic);

    //FERMETURE DES FICHIERS .TXT
    fclose(input);
    fclose(binary);
    fclose(dictionnary);

    //LIBERATION MEMOIRE
    free(arbre_huffman);
    free(liste_occ);
    free(liste_dic);
}
