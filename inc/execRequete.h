//----------------------------------------------
//
//      execRequete.h
//
//----------------------------------------------

#ifndef EXEC_REQUETE
#define EXEC_REQUETE

#include <sqlite3.h>

extern void execRequete(char *sql, sqlite3 *db, char *message);

#endif