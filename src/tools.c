//----------------------------------------------
//
//      tools.c
//
//----------------------------------------------

#include <stdio.h>
#include <stdarg.h>

#include "../inc/variables.h"

/* debug message output */
void debug( const char *fmt, ... ){
    va_list args;
    if ( modeDebug ) {
        va_start( args, fmt );
        fprintf(stderr, "DEBUG: ");
        vfprintf(stderr, fmt, args );
        va_end( args );
    }
}

void aide(void){
    printf("Programme testSqlite\n");
    printf("syntaxe : testSql [options]\n");
    printf("liste des options :\n");
    printf("    -b <nom de la base> : utilise la base passée en parametre (sans extention)\n");
    printf("    -d : mode ddebug\n");
    printf("    -h : affichage de cette aide\n");
}