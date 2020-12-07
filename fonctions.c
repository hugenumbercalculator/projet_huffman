#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"
#include "files.h"

void write_binary (char caractere)
{
    char tab[8] = "00000000";
    int x =128, entier = caractere;
    FILE *binary;
    binary = fopen("binary.txt","a");

    for (int i=0; i<8; i++){ //boucle de remplissage du tableau de caractères
        if (entier-x>=0){
            tab[i] = '1';
            entier -= x;
        }
        x = x/2;
    }
    for (int i=0; i<8; i++) fputc(tab[i],binary);
    fclose(binary);
}

void read_txt ()
{
    char caractere;
    FILE *input, *binary;
    input = fopen ("input.txt","r");
    binary = fopen ("binary.txt","w");

    if (input != NULL){
        caractere = fgetc(input);
        while(caractere!=EOF){
            write_binary(caractere); //ecriture binaire dans le fichier binary.txt
            caractere = fgetc(input); //lecture du caractère suivant dans le fichier input.txt
        }
    }
    fclose(input);
    fclose(binary);
}

int nbr_char(FILE *fichier)
{
    int nbr = 0;
    if (!fichier) return nbr;
    else{
        while (fgetc(fichier) != EOF)
            nbr += 1;
        return nbr;
    }
}

Maillon* occurrences()
{
    Maillon *liste_occ, *temp;
    liste_occ = (Maillon*)malloc(sizeof(Maillon));
    temp = (Maillon*)malloc(sizeof(Maillon));
    FILE *fichier;
    fichier = fopen("input.txt","r");
    char caractere = fgetc(fichier);
    bool run;
    printf("declaration OK\n");

    while(caractere != EOF){
        temp = liste_occ;
        run = true;
        while (run && temp){
            printf(" 2e while OK\n");
            if (temp->caractere == caractere){
                printf("entre dans la condition\n");
                temp->occurrences += 1;
                run = false;
            }
            temp = temp->next;
        }
        if (run){
            temp = (Maillon*)malloc(sizeof(Maillon));
            temp->caractere = caractere;
            temp->occurrences = 1;
            temp->next = NULL;
            printf("premier OK\n");
        }
        caractere = fgetc(fichier);
    }
    fclose(fichier);
    return liste_occ;
}

Maillon* minimum(Maillon *liste_occ)
{
    Maillon *temp;
    temp = (Maillon*)malloc(sizeof(Maillon));
    temp->caractere = liste_occ->caractere;
    temp->occurrences = liste_occ->occurrences;
    liste_occ = liste_occ->next;

    while (liste_occ){
        if (liste_occ->occurrences < temp->occurrences){
            temp->occurrences = liste_occ->occurrences;
            temp->caractere = liste_occ->caractere;
        }
        liste_occ = liste_occ->next;
    }
    return temp;
}

Arbre* create_huffman_tree(Maillon **liste_occ, int nbr)
{
    Arbre *arbre_huffman;
    File *file;
    arbre_huffman = (Arbre*)malloc(sizeof(Arbre));
    file = (File*)malloc(sizeof(File));

    for (int i=0; i<nbr; i++){
        arbre_huffman->noeud->occurrences = minimum(&liste_occ)->occurrences;
        arbre_huffman->noeud->caractere = minimum(&liste_occ)->caractere;
        enfiler(file,arbre_huffman);
    }

    while (file){
        arbre_huffman->sag = defiler(file);
        arbre_huffman->sad = defiler(file);
        arbre_huffman->noeud->occurrences = arbre_huffman->sad->noeud->occurrences + arbre_huffman->sag->noeud->occurrences;
    }
    return arbre_huffman;
}


void write_dictionnary(Arbre *arbre_huffman, FILE *dictionnary, Maillon *liste_dic)
{
    Maillon *temp;
    temp = liste_dic;

    if (!arbre_huffman) return;

    if (arbre_huffman->sag){ //REMPLISSAGE DU DICTIONNAIRE
        temp->caractere = '0';
        temp = temp->next;
        write_dictionnary(arbre_huffman->sag, dictionnary, liste_dic);
    }
    if (arbre_huffman->noeud->caractere){ //ECRITURE DANS LE DICTIONNAIRE
        fprintf(dictionnary,"%c : ",arbre_huffman->noeud->caractere);
        temp = liste_dic;
        while (temp != NULL){
            fputc(temp->caractere,dictionnary);
            temp = temp->next;
        }
        fputc("\n",dictionnary);
        return;
    }

    if (arbre_huffman->sad){  //REMPLISSAGE DU DICTIONNAIRE
        temp->caractere = '1';
        temp = temp->next;
        write_dictionnary(arbre_huffman->sad, dictionnary, liste_dic);
    }
    if (arbre_huffman->noeud->caractere){ //ECRITURE DANS LE DICTIONNAIRE
        fprintf(dictionnary,"%c : ",arbre_huffman->noeud->caractere);
        temp = liste_dic;
        while (temp != NULL){
            fputc(temp->caractere,dictionnary);
            temp = temp->next;
        }
        fputc("\n",dictionnary);
        return;
    }
}
