#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"
#include "files.h"
#include "test.h"
#include "optimisation.h"

int main()
{
    // ALLOCATIONS DYNAMIQUES
    Arbre *arbre_huffman;
    arbre_huffman = (Arbre*)malloc(sizeof(Arbre));
    Maillon *liste_occ, *liste_dic;
    liste_occ = (Maillon*)malloc(sizeof(Maillon));
    liste_dic = (Maillon*)malloc(sizeof(Maillon));

    //OUVERTURE DES FICHIERS .TXT
    FILE *input, *binary, *dictionary;
    input = fopen("input.txt","r");
    binary = fopen("binary.txt","r");
    dictionary = fopen("dictionary.txt","w");
    int nbr_occ, nbr_input = count_char(input), nbr_binary = count_char(binary);

    //CORPS
    read_txt();
    printf("%d characters in input.txt\n",nbr_input);
    printf("%d characters in binary.txt\n",nbr_binary);
    liste_occ = occurrences();
    nbr_occ = count_node(liste_occ);
   // print_liste_occ(liste_occ);
    /*arbre_huffman = create_huffman_tree(liste_occ, nbr_occ);
    print_arbre(arbre_huffman);
    write_dictionary(&arbre_huffman, &dictionary, &liste_dic);*/

    //FERMETURE DES FICHIERS .TXT
    fclose(input);
    fclose(binary);
    fclose(dictionary);

    //LIBERATION MEMOIRE
    liberation_liste(liste_occ);
    /*liberation_liste(liste_dic);
    liberation_arbre(arbre_huffman);*/
}
