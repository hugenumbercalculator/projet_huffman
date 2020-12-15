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

int count_char(FILE *fichier)
{
    int nbr = 0;
    if (!fichier) return nbr;
    else{
        while (fgetc(fichier) != EOF)
            nbr += 1;
        return nbr;
    }
}

int count_node(Maillon *liste)
{
    int nbr = 0;
    while (liste != NULL){
        nbr ++;
        liste = liste->next;
    }
    return nbr;
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

Maillon* minimum_of_a_list(Maillon *liste_occ)
{
    Maillon *minimum;
    minimum = (Maillon*)malloc(sizeof(Maillon));
    minimum->caractere = liste_occ->caractere;
    minimum->occurrences = liste_occ->occurrences;
    liste_occ = liste_occ->next;

    while (liste_occ){
        if (liste_occ->occurrences < minimum->occurrences){
            minimum->occurrences = liste_occ->occurrences;
            minimum->caractere = liste_occ->caractere;
        }
        liste_occ = liste_occ->next;
    }
    return minimum;
}

void delete_node(Maillon **liste, char caractere)
{
    Maillon *temporaire;
    temporaire = (Maillon*)malloc(sizeof(Maillon));

    if (*liste != NULL){
        delete_node(&(*liste)->next, caractere);
        if ((*liste)->caractere == caractere){
            temporaire = *liste;
            *liste = (*liste)->next;
            free(temporaire);
        }
    }
}

Arbre* create_huffman_tree(Maillon *liste_occ, int nbr)
{
    Arbre *arbre_huffman;
    arbre_huffman = (Arbre*)malloc(sizeof(Arbre));
    File *file;
    file = (File*)malloc(sizeof(File));
    file->first = NULL;

    for (int i=0; i<nbr; i++){
        arbre_huffman->noeud = minimum_of_a_list(liste_occ);
        delete_node(&liste_occ, arbre_huffman->noeud->caractere);
        enfiler(file,arbre_huffman);
    }
    while (file){
        Arbre *new_node;
        new_node = (Arbre*)malloc(sizeof(Arbre));
        new_node->sag = defiler(file);
        new_node->sad = defiler(file);
        new_node->noeud->occurrences = new_node->sad->noeud->occurrences + new_node->sag->noeud->occurrences;
        printf("%d",new_node->noeud->occurrences);
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

void encodage(char* fichierinput,char* fichieroutput,char *dictionnaire[256])
{
    char chaine[500]; //Element_d *temp = liste;
    FILE* texte = fopen("input.txt", "r");
    FILE* texteout = fopen("binary.txt", "w");
    while (fgets(chaine,500,texte)){
        for (int j=0;chaine[j]!='0';j++)
            fprintf(texteout,"%s",dictionnaire[chaine[j]]);
    }
    fclose(texte);
    fclose(texteout);
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
