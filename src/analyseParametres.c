//----------------------------------------------
//
//      analyseParametres.c
//
//----------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "../inc/variables.h"
#include "../inc/tools.h"

/* debug message output */
void analyseParametres(int argc, char **argv){
    char param[50];
    char option;
    for (int i = 1 ; i < argc ; i++){
        strcpy(param, argv[i]);
        debug("analyse du paramètre %d = %s\n", i, param);
        if (param[0] == '-'){
            option = param[1];
            switch (option){
                case 'b' : // force utilisation d'une base precise
                    i++;
                    if (i >= argc) {
                        printf("manque nom de la base \n");
                        exit(0);
                    }
                    strcpy(fichierBDD, argv[i]);
                    break;
                case 'd' : // activation du mode debug
                    modeDebug=1;
                    printf("activation du mode debug\n");
                    break;
                default :
                    printf("option %s inconnue\n", param);
                    aide();
                    exit(0);
            }
        } else {
            printf("une option doit commencer par '-'\n");
            aide();
            exit(0);
        }
    }
}