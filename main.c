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
    liste_occ = (Maillon*)malloc(10*sizeof(Maillon));
    liste_dic = (Maillon*)malloc(sizeof(Maillon));

    //OUVERTURE DES FICHIERS .TXT
    FILE *input, *binary, *dictionary;
    input = fopen("input.txt","r");
    binary = fopen("binary.txt","r");
    dictionary = fopen("dictionary.txt","w");

    //CORPS
    read_txt();
    printf("%d characters in input.txt\n",nbr_char(input));
    printf("%d characters in binary.txt\n",nbr_char(binary));
    liste_occ = occurrences();
    while(liste_occ != NULL)
    {
        printf("%c:%d\n",liste_occ->caractere,liste_occ->occurrences);
        liste_occ = liste_occ->next;
    }
    //arbre_huffman = create_huffman_tree(liste_occ, nbr_char(input));
    //printf("%c",arbre_huffman->noeud->caractere);
    //write_dictionary(&arbre_huffman, &dictionary, &liste_dic);

    //FERMETURE DES FICHIERS .TXT
    fclose(input);
    fclose(binary);
    fclose(dictionary);

    //LIBERATION MEMOIRE
    liberation_liste(liste_occ);
   /* liberation_liste(liste_dic);
    liberation_arbre(arbre_huffman); */

}
