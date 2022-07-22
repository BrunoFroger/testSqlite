//----------------------------------------------
//
//      main.c
//
//----------------------------------------------



#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

#include "../inc/creationBdd.h"
#include "../inc/variables.h"
#include "../inc/menu.h"
#include "../inc/analyseParametres.h"

//----------------------------------------------
//
//      main
//
//----------------------------------------------
int main(int argc, char **argv){
    char *sql;

    strcpy(fichierBDD, "livres");
    analyseParametres(argc, argv);

    creationBdd(fichierBDD);

    menu();

    return 0;

    printf("Tests sqlite3\n");   

    /* Create Table */
    sql = (char *) "CREATE TABLE IF NOT EXISTS COMPANY("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50)," \
        "SALARY         REAL );";
    //execRequete(sql, db, (char *) "Table created successfully\n");
    

    /* INSERT elements */
    sql = (char *) "INSERT OR IGNORE INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
        "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
        "INSERT OR IGNORE INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
        "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); " \
        "INSERT OR IGNORE INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
        "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
        "INSERT OR IGNORE INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
        "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
    //execRequete(sql, db, (char *) "Records created successfully\n");

    /* show elements */
    sql = (char *) "SELECT * FROM COMPANY;";
    //execRequete(sql, db, (char *) "Select executed successfully\n");

    sqlite3_close(db);
}