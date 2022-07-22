//----------------------------------------------
//
//      menu.c
//
//----------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "../inc/variables.h"
#include "../inc/sendRequete.h"
#include "../inc/selectBdd.h"
#include "../inc/tools.h"

void menu(void){
    int car = ' ';

    sprintf(prompt, "%s", fichierBDD);
    while (1){
        if (car != 10){
            printf("\n\ntests sqlite3\n");
            printf("b => creation/ouverture d'une base\n");
            printf("r => envoi d'une requete\n");
            printf("d => mode debug on/off : ");
            if (modeDebug == 1) printf("on\n"); else printf("off\n");
            printf("h => aide\n");
            printf("q => quitte le programme\n");
            printf("%s > ", prompt);
            car = getc(stdin);
            fflush(stdin);
            switch(car){
                case 'b' : 
                    selectBdd();
                    break;
                case 'r' : 
                    sendRequete();
                    break;
                case 'd' : 
                    if (modeDebug == 0)
                        modeDebug=1;
                    else
                        modeDebug=0;
                    break;
                case 'h' : 
                    aide();
                    break;
                case 'q' : 
                    exit(0);
                    break;
                case 10 : break;
                default :
                    printf("commande %d inconnue\n", car);
            }
        } else car = ' ';
    }
}