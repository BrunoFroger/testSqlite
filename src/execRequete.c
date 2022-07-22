

#include <stdio.h>
#include <sqlite3.h>

//----------------------------------------------
//
//      callback
//
//----------------------------------------------
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

//----------------------------------------------
//
//      execRequete
//
//----------------------------------------------
void execRequete(char *sql, sqlite3 *db, char *message ){

    char *zErrMsg = 0;
    int rc;
    /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "%s", message);
   }
}