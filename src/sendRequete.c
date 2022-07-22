//----------------------------------------------
//
//      sendRequete.c
//
//----------------------------------------------


#include <stdio.h>

#include "../inc/variables.h"
#include "../inc/execRequete.h"

//----------------------------------------------
//
//      sendRequete
//
//----------------------------------------------
void sendRequete(void){
    char requete[200];

    printf("Saisissez votre requete > ");
    fflush (stdin);
    fgets(requete, 200, stdin);
    fflush(stdin);
    execRequete(requete, db,  "requete saisie manuellement");
}