/*****************************************************************//**
* \file fonctions.h
* \brief Header of principals data structures and functions.
* \author Power Rangers
* \date November 2020
 *********************************************************************/
#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

/**
 * \typedef struct Maillon
 * \brief A Maillon is composed by a character, an integer, and a pointer to the next Maillon.
 */
typedef struct Maillon{
    char caractere;
    int occurrences;
    struct Maillon *next;
}Maillon;

 /**
 * \typedef struct Arbre
 * \brief Arbre owns 3 pointers : Maillon, and 2 other Arbre.
 */
typedef struct Arbre{
    struct Maillon *noeud;
    struct Arbre *sad, *sag;
}Arbre;

// PARTIE 1
/**
 * \brief Function that translate a character into binary sequence, and write it in a text file.
 * \param The character we have to write in binary.
 */
void write_binary (char caractere);

/**
 * \brief Function that treat text files.
 */
void read_txt ();

/**
 * \brief Function that count the number of characters in a file.
 * \param The file we have to process.
 * \return An integer representing the number of characters in the file.
 */
int count_char(FILE *fichier);

/**
 * \brief Function that count the number of character's occurrences of a simply linked list.
 * \param The list we have to process.
 * \return An integer representing the number of occurrences.
 */
int count_node(Maillon *liste);

// PARTIE 2
/**
 * \brief Function that create a list of nodes representing characters in a text and their occurrences.
 * \return A list of nodes.
 */
Maillon* occurrences();

/**
 * \brief Function that finds the minimum of a nodes list.
 * \param The list we have to process.
 * \return A node.
 */
Maillon* minimum_of_a_list(Maillon *liste_occ);

/** \brief Function that delete a node of a simply chained list.
 * \param The list we have to process.
 * \param The character of the node we have to delete.
 */
void delete_node(Maillon **liste_occ, char caractere);

/**
 * \brief Function that create a Huffman Tree.
 * \param A list of nodes containing characters an their occurrences.
 * \param An integer : character's number in the file.
 * \return A tree's node, the first of the queue.
 */
Arbre* create_huffman_tree(Maillon *liste_occ, int nbr);

/**
 * \brief Function that create a dictionary by attributing a new short binary sequence to each character.
 * \param The Huffman tree.
 * \param The text file we have to write on.
 * \param A list of nodes containing binary suites.
 */
void write_dictionary (Arbre *arbre_huffman, FILE *dictionary, Maillon *liste_dic);


void encodage(char *fichierinput, char *fichieroutput, char *dictionnaire[256]);

/**
 * \brief Function that free up a linked list memory space.
 * \param The linked list.
 */
void liberation_liste(Maillon* liste);

/**
 * \brief Function that free up a tree's memory space
 * \param The Huffman tree.
 */
void liberation_arbre(Arbre *arbre);

#endif // FONCTIONS_H_INCLUDED
