#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
      int nbrblock;      //le nombre de blocks
      int nbreng;             //le nombre d'enregistrements
      int nbrchamps;     // le nombre des champs dans chaque enregistrement
}entete

typedef struct{
      char nom[50];
      char prenom[50];
      int matricule;
}etudiant
void ecrireng(FILE *projetsfsd, etudiant *etu)  // procédure qui écrit un enregistrement physique dans le fichier
 {
      fwrite(etu; sizeof(etudiant),1,projetsfsd);
 }



























int main()
{

    return 0;
}
