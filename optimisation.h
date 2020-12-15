/*****************************************************************//**
* \file optimisation.h
* \brief Header of optimization's functions and structure.
* \author Power Rangers
* \date December 2020
 *********************************************************************/
#ifndef OPTIMISATION_H_INCLUDED
#define OPTIMISATION_H_INCLUDED

/**
 * \typedef struct Doubly Linked List
 * \brief A LDC is composed by a character, an integer, a pointer to the next Maillon, another to the previous one.
 */
typedef struct LDC{
    char caractere;
    int occurrences;
    struct LDC *next, *prec;
}LDC;

/**
 * \brief
 * \param
 * \return
 */
int taille_LDC(LDC *liste);

/**
 * \brief Recursive function of dichotomous search.
 * \param A doubly linked list.
 * \param The character we have to find or class in the list.
 * \param The list's length.
 * \return
 */
LDC* dichotomie(LDC *liste, char T, int taille);


#endif // OPTIMISATION_H_INCLUDED
