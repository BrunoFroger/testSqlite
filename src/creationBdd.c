//----------------------------------------------
//
//      creationBdd.c
//
//----------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include "../inc/variables.h"
#include "../inc/execRequete.h"

typedef struct {
    char nom[50];
    char key[50];
    char type[50];
    char notnull[50];
} structFields;

structFields fields[20];

//----------------------------------------------
//
//      suppEspaces
//
//----------------------------------------------
void suppEspaces(char *texte){
    int j = 0;
    for (int i = 0 ; i < strlen(texte) ; i++){
        if (texte[i] != ' '){
            texte[j++]=texte[i];
        }
    }
    texte[j] = '\0';
}

//----------------------------------------------
//
//      getLigne
//
//----------------------------------------------
void getLigne(char *ligne, FILE *fic){
    strcpy(ligne, "");
    fgets(ligne, 100, fic);
    ligne[strlen(ligne) - 1]='\0';  // suppression du RC
    if (strlen(ligne) == 0) strcpy(ligne, "");
    if (ligne[0] == '#') strcpy(ligne, "");
    suppEspaces(ligne);
}

//----------------------------------------------
//
//      initField
//
//----------------------------------------------
void initField(int index){
    strcpy(fields[index].nom, "");
    strcpy(fields[index].key, "");
    strcpy(fields[index].type, "");
    strcpy(fields[index].notnull, "");
}

//----------------------------------------------
//
//      setVar
//
//----------------------------------------------
void setVar(char *var,int index){
    //printf("traitement de %s\n", var);
    if (strncmp(var, "KEY", 3) == 0) {
        strcpy(fields[index].key, " PRIMARY KEY");
    } else if (strncmp(var, "TEXT", 4) == 0){
        strcpy(fields[index].type, " TEXT");
    } else if (strncmp(var, "CHAR(", 5) == 0) {
        strcpy(fields[index].type, " ");
        strcat(fields[index].type, var);
    } else if (strncmp(var, "INT", 3) == 0) {
        strcpy(fields[index].type, " INT");
    } else if (strncmp(var, "REAL", 4) == 0) {
        strcpy(fields[index].type, " REAL");
    } else if (strncmp(var, "NOTNULL", 4) == 0) {
        strcpy(fields[index].notnull, " NOT NULL");
    } else {
        strcpy(fields[index].nom,var);
    }
}

//----------------------------------------------
//
//      setField
//
//----------------------------------------------
void setField(int index, char *champs){
    char var[20];
    int j = 0;
    initField(index);
    for (int i = 0 ; i < strlen(champs) ; i++){
        if (champs[i] != ','){
            var[j++] = champs[i];
            var[j] = '\0';
        } else {
            j=0;
            setVar(var, index);
        }
    }
    setVar(var, index);

}

//----------------------------------------------
//
//      creationBdd
//
//----------------------------------------------
void creationBdd(char *nomBase){
    FILE *fic;
    char ligne[200];
    char *tmp;
    int rc;
    char requete[500];
    char nomTable[100];
    int numField = 0;
    char message[100];
    char fichierDefinition[150];
    int constructionTableEnCours=0;

    sprintf(fichierDefinition, "struct_bdd_%s.txt", nomBase);
    fic = fopen(fichierDefinition, "r");
    if (fic == NULL){
        printf("Impossible d'ouvrir le fichier %s \n", fichierDefinition);
        exit(-1);
    }
    printf("Lecture du fichier de definition des données\n");
    while (!feof(fic)){
        getLigne(ligne, fic);
        if (strlen(ligne) == 0) continue;
        //printf("ligne lue (%d) :  %s\n", (int)strlen(ligne), ligne);

        if (strncmp(ligne, "BASE", 4) == 0){
            tmp = &ligne[5];
            strcpy(fichierBDD, tmp);
            printf("definition du nom de la base de donnee : <%s>\n", fichierBDD);
            rc = sqlite3_open(fichierBDD, &db);

            if( rc ) {
                fprintf(stderr, (char *) "Can't open database: %s\n", sqlite3_errmsg(db));
                exit(0);
            } else {
                fprintf(stderr, (char *) "Opened database successfully\n");
            }
        } else if (strncmp(ligne, "TABLE", 5) == 0){
            char champ[100];
            strcpy(nomTable, &ligne[6]);
            constructionTableEnCours = 1;
            //printf("creation de la table %s\n", nomTable);
            getLigne(ligne, fic);
            numField = 0;
            while (strncmp(ligne, "FIELD", 5) == 0){
                if (!feof(fic)){
                    strcpy(champ, &ligne[6]);
                    //printf("ajout du champ %d : %s\n", numField, champ);
                    setField(numField, champ);
                    getLigne(ligne, fic);
                    numField++;
                } else break;
            }
            // constructipn de la commande de creation de la table
            sprintf(requete, "CREATE TABLE IF NOT EXISTS %s (", nomTable);
            for (int i = 0 ; i < numField ; i++){
                strcat(requete, fields[i].nom);
                strcat(requete, fields[i].type);
                strcat(requete, fields[i].key);
                strcat(requete, fields[i].notnull);
                if (i != (numField - 1)) strcat (requete, ", ");
            }
            strcat(requete, ");");
            printf("requete de creation de la table : %s\n", requete);
            sprintf(message, "creation de la table %s\n", nomTable);
            execRequete(requete, db, message);                
        }
        strcpy(ligne, "");

    }
    strcpy(prompt, fichierBDD);

}