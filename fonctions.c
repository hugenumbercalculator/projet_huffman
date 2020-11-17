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

Maillon occurrences()
{
    Maillon *liste_occ, *temp;
    liste_occ = (Maillon*)malloc(sizeof(Maillon));
    FILE *fichier;
    fichier = fopen("input.txt","r");
    char caractere = fgetc(fichier);
    bool run;

    while(caractere != EOF){
        temp = liste_occ;
        run = true;

        while (run && temp != NULL){
            if (temp->caractere == caractere){
                temp->occurrences += 1;
                run = false;
            }
            temp = temp->next;
        }
        if (run){
            temp->caractere = caractere;
            temp->occurrences = 1;
            temp->next = NULL;
        }
        caractere = fgetc(fichier);
    }
    fclose(fichier);
    //return liste_occ;
}

char minimum(Maillon *liste_occ)
{
    char caractere = liste_occ->caractere;
    int min = liste_occ->occurrences;
    liste_occ = liste_occ->next;

    while (liste_occ){
        if (liste_occ->occurrences < min){
            min = liste_occ->occurrences;
            caractere = liste_occ->caractere;
        }
        liste_occ = liste_occ->next;
    }
    return caractere;
}

Noeud huffman(Maillon *liste_occ, int nbr)
{
    Noeud *arbre;
    arbre = (Noeud*)malloc(sizeof(Noeud));
}


void write_dictionnary(Noeud *arbre, FILE *dictionnaire)
{
    File *file;
    file->first = NULL;

    if (!arbre) return;

    if (arbre->ng){
        enfiler(&file,'0');
        write_dictionnary(&arbre->ng, dictionnaire);
    }
    if (arbre->mg){
        fprintf(dictionnaire,"%c : ",arbre->mg->caractere);
        while (file->first) fputc(defiler(&file),dictionnaire);
        return;
    }


    if (arbre->nd){
        enfiler(&file,'1');
        write_dictionnary(&arbre->nd, dictionnaire);
    }
    if (arbre->md){
        fprintf(dictionnaire,"%c : ",arbre->md->caractere);
        while (file->first) fputc(defiler(&file),dictionnaire);
        return;
    }
}
