#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
      int nbrblock;           //le nombre de blocks
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



     FILE *projetsfsd= fopen(projetsfsd,"wb");
      if (projetsfsd == NULL) {
        perror("erreur d'ouverture de fichier");
        return 1;
      }


      //l'initialisation de l'entete
      enteteF entete;
      entete.nbrblock=3;
      entete.nbreng=5;




































        return 0;
 }



