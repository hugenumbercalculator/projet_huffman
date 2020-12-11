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

    for (int i=0; i<8; i++){ //boucle de remplissage du tableau de caract�res
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
            caractere = fgetc(input); //lecture du caract�re suivant dans le fichier input.txt
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
    FILE *fichier;
    fichier = fopen("input.txt","r");
    Maillon *liste, *liste_ref;
    char caractere = fgetc(fichier);
    bool run;
    int i=0;

    while (caractere != EOF){
        run = true;
        if (i==0) // CAS VIDE
        {
            liste_ref = (Maillon*)malloc(sizeof(Maillon));
            liste_ref->caractere = caractere;
            liste_ref->occurrences = 0;
            liste_ref->next = NULL;
        }
        liste = liste_ref;
        while(liste){ //CAS CARACTERE DEJA PRESENT
            if(liste->caractere == caractere){
                liste->occurrences += 1;
                run = false;
            }
            liste = liste->next;
        }
        // PLACEMENT DANS LE DERNIER MAILLON
        liste = liste_ref;
        while(liste->next != NULL)
            liste = liste->next;
        if(run){ //INSERTION D'UN NOUVEAU MAILLON
            Maillon *nouveau_maillon;
            nouveau_maillon = (Maillon*)malloc(sizeof(Maillon));
            nouveau_maillon->caractere = caractere;
            nouveau_maillon->occurrences = 1;
            nouveau_maillon->next = NULL;
            liste->next = nouveau_maillon;
        }
        caractere = fgetc(fichier);
        i++;
    }
    fclose(fichier);
    return liste_ref;
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

Arbre* create_huffman_tree(Maillon *liste_occ, int nbr)
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


void write_dictionary(Arbre *arbre_huffman, FILE *dictionary, Maillon *liste_dic)
{
    Maillon *temp;
    temp = liste_dic;

    if (!arbre_huffman) return;

    if (arbre_huffman->sag){ //REMPLISSAGE DU DICTIONNAIRE
        temp->caractere = '0';
        temp = temp->next;
        write_dictionary(arbre_huffman->sag, dictionary, liste_dic);
    }
    if (arbre_huffman->noeud->caractere){ //ECRITURE DANS LE DICTIONNAIRE
        fprintf(dictionary,"%c : ",arbre_huffman->noeud->caractere);
        temp = liste_dic;
        while (temp != NULL){
            fputc(temp->caractere,dictionary);
            temp = temp->next;
        }
        fputc("\n",dictionary);
        return;
    }

    if (arbre_huffman->sad){  //REMPLISSAGE DU DICTIONNAIRE
        temp->caractere = '1';
        temp = temp->next;
        write_dictionary(arbre_huffman->sad, dictionary, liste_dic);
    }
    if (arbre_huffman->noeud->caractere){ //ECRITURE DANS LE DICTIONNAIRE
        fprintf(dictionary,"%c : ",arbre_huffman->noeud->caractere);
        temp = liste_dic;
        while (temp != NULL){
            fputc(temp->caractere,dictionary);
            temp = temp->next;
        }
        fputc("\n",dictionary);
        return;
    }
}

void encodage()
{
    FILE *new_file, *dictionnary;
    new_file = fopen("encoding.txt","w");
    dictionnary = fopen("dictionnary.txt","r");

    fclose(new_file);
}

void liberation_liste(Maillon *liste)
{
    if (liste==NULL) return;
    Maillon *actuel;
    actuel = (Maillon*)malloc(sizeof(Maillon));
    while(liste)
    {
        actuel = liste;
        liste = liste->next;
        free(actuel);
    }
}

void liberation_arbre(Arbre *arbre)
{
    if(!arbre) return;
    liberation_liste(arbre->noeud);
    liberation_arbre(arbre->sag);
    liberation_arbre(arbre->sad);
    free(arbre);
    arbre = NULL;
}
