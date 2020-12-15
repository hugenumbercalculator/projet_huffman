/*****************************************************************//**
* \file test.h
* \brief Header of unit test functions.
* \author Power Rangers
* \date December 2020
 *********************************************************************/
#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
#include "fonctions.h"

/**
 * \brief Function that print a simply chained list.
 * \param The list we have to process.
 */
void print_liste_occ(Maillon *liste_occ);

/**
 * \brief Recursive function that print a Tree.
 * \param The structure we have to process.
 */
void print_arbre(Arbre *a);

/**
 * \brief Function that print a queue.
 * \param The queue we have to print.
 */
void print_file(File *f);

#endif // TEST_H_INCLUDED
