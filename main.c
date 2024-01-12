#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*************************************************création de fichier*************************************************************
  // enregistrement physique
  typedef struct etudiant
{
    char nom[50];
    char prenom[50];
    int matricule;
    char fineng;
    char finchamps;
};

 typedef struct block
{
    char tab[max];

} block;

typedef block buffer;

typedef struct entete
{   int nbrblock;                      //le nombre de blocks
    int nbreng;                       //le nombre d'enregistrements
    int No_dern_bloc;                // indice de dernier bloc
    int NB_enreg_inser;             // nombre d'enregistrement insérié
    int NB_enreg_suppr;            // nombre d'enregistrement supprimé
} entete;

 typedef struct sfsdtovc
{
    FILE *fichier;
    entete entetef;
} sfsdtovc;

  sfsdtovc *ouvrir(char nom[50], char mode)
{
    sfsdtovc *f = malloc(sizeof(sfsdtovc));       // pour allocation d'un enrg qui contient un fichier et une entet du fichier
    if (mode == 'a')                             // ajouter ou ouvrir en mode ajout
    {
        f->fichier = fopen(nom, "rb+");
        fread(&(f->entety), sizeof(struct entete), 1, f->fichier);
    }
    else
    {
        if (mode == 'n')                         //créer un nouveau fichier ou ouvrir en mode création
        {
            f->fichier = fopen(nom, "wb+");
            f->entety.No_dern_bloc = 1;
            f->entety.ind_pos_libre = 0;
            f->entety.NB_enreg_inser = 0;
            f->entety.NB_enreg_suppr = 0;
        }
    }
    return f;
}














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


      fwrite(&entete, sizeof(enteteF),1,projetsfsd);

































        return 0;
 }



