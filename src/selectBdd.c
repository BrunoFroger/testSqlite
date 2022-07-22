//----------------------------------------------
//
//      selectBdd.c
//
//----------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "../inc/variables.h"
#include "../inc/creationBdd.h"

void selectBdd(void){
    char nomBase[50];
    system("ls *.bd");
    fflush(stdin);
    printf("selectionner la base a utiliser > ");
    scanf("%s", nomBase);
    fflush(stdin);
    sprintf(fichierBDD, "struct_bdd_%s", nomBase);
    sqlite3_close(db);
    creationBdd(nomBase);
}