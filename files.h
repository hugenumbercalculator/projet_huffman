#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

typedef struct Element{
    char info;
    struct Element *next;
}Element;

typedef struct FILE{
    struct Element *first;
}File;

void enfiler(File *file, char caractere);
char defiler(File *file);

#endif // FILES_H_INCLUDED
