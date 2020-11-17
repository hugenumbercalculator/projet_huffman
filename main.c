#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"
int main()
{
    FILE *binary;
    binary = fopen("binary.txt","r");

    read_txt();
    printf("%d characters in binary.txt\n",nbr_char(binary));

    fclose(binary);
}
