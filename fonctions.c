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
            temp = malloc(sizeof(Maillon));
            temp->caractere = caractere;
            temp->occurrences = 1;
            temp->next = NULL;
        }
        caractere = fgetc(fichier);
    }
    fclose(fichier);
    //return liste_occ;
}

Maillon minimum(Maillon *liste_occ)
{
    Maillon *temp;
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

Arbre huffman(Maillon *liste_occ, int nbr)
{
    Arbre *arbre;
    arbre = (Arbre*)malloc(sizeof(Arbre));
    File *file;

    for (int i=0; i<nbr; i++){
        arbre->noeud->occurences = minimum(&liste_occ)->occurrences;
        arbre->noeud->caractere = minimum(&liste_occ)->caractere;
        enfiler(file,&arbre);
    }

    while (file){
        arbre->sag = defiler(file);
        arbre->sad = defiler(file);
        arbre->noeud->occurrences = arbre->sad->noeud->occurrences + arbre->sag->noeud->occurrences;
    }
    return arbre;
}


void write_dictionnary(Arbre *arbre, FILE *dictionnaire, Maillon *liste_dic)
{
    Maillon *temp;
    temp = liste_dic;

    if (!arbre) return;

    if (arbre->sag){ //REMPLISSAGE DU DICTIONNAIRE
        temp->caractere = '0';
        temp = temp->next;
        write_dictionnary(&arbre->sag, dictionnaire);
    }
    if (arbre->noeud->caractere){ //ECRITURE DANS LE DICTIONNAIRE
        fprintf(dictionnaire,"%c : ",arbre->noeud->caractere);
        temp = liste;
        while (temp != NULL){
            fputc(temp->caractere,dictionnaire);
            temp = temp->next;
        }
        fputc("\n",dictionnaire);
        return;
    }

    if (arbre->sad){  //REMPLISSAGE DU DICTIONNAIRE
        temp->caractere = '1';
        temp = temp->next;
        write_dictionnary(&arbre->sad, dictionnaire);
    }
    if (arbre->md){ //ECRITURE DANS LE DICTIONNAIRE
        fprintf(dictionnaire,"%c : ",arbre->noeud->caractere);
        temp = liste;
        while (temp != NULL){
            fputc(temp->caractere,dictionnaire);
            temp = temp->next;
        }
        fputc("\n",dictionnaire);
        return;
    }
}
