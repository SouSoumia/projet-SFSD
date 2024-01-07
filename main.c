#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
      int nbrblock;      //le nombre de blocks
      int nbreng;             //le nombre d'enregistrements
}enteteF;


 // enregistrement physique avec chevauchement
typedef struct{
      int sizeofnom;
      char nom[50];
      int sizeofprenom;
      char prenom[50];
      int sizeofmatricule;
      int matricule;
      char fineng;
      char finchamps;
}etudiant;




void ecrireng(FILE *projetsfsd, etudiant *etu)  // procédure qui écrit un enregistrement physique dans le fichier
 {
      fwrite(etu, sizeof(etudiant),1,projetsfsd);
 }



int main()
 {   char fineng='#';             // mark fin d'enregistrement
     char finchamps='$';          // mark fin de champs



     FILE *projetsfsd= fopen(projetsfsd,"w");



      //l'initialisation de l'entete
      enteteF entete;
      nbrblock=3;
      nbreng=5;

      fwrite(&entete, sizeof(enteteF),1,projetsfsf);
































        return 0;
 }



