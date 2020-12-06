/*****************************************************************//**
* \file files.h
* \brief Header of queues' functions and structure.
* \author Power Rangers
* \date November 2020
 *********************************************************************/
#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

 /**
 * \typedef struct File
 * \brief pointer on the first queue's element.
 */
typedef struct File{
    struct Arbre *first;
}File;

/**
 * \brief Function that enqueue a queue.
 * \param The queue we have to process.
 * \param The tree's node we have to enqueue.
 */
void enfiler(File *file, Arbre *a);

/**
 * \brief Function that dequeue a queue.
 * \param The queue we have to process.
 * \return A tree's node, the first of the queue.
 */
Arbre defiler(File *file);

#endif // FILES_H_INCLUDED
