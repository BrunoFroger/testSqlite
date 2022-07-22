//----------------------------------------------
//
//      variables.h
//
//----------------------------------------------


#ifndef VARIABLES
#define VARIABLES

#include <sqlite3.h>

extern char fichierBDD[200];
extern sqlite3 *db ;
extern char prompt[50];
extern int modeDebug;

#endif