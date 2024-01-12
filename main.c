#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100
//*************************************************création de fichier*************************************************************
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
{
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
        fread(&(f->entetef), sizeof(struct entete), 1, f->fichier);
    }
    else
    {
        if (mode == 'n')                         //créer un nouveau fichier ou ouvrir en mode création
        {
            f->fichier = fopen(nom, "wb+");
            f->entetef.No_dern_bloc = 1;
            f->entetef.NB_enreg_inser = 0;
            f->entetef.NB_enreg_suppr = 0;
        }
    }
    return f;
}
    void fermer(sfsdtovc *f)
{
    rewind(f->fichier);                                           // positionner le curseur au debut du fichier
    fwrite(&(f->entetef), sizeof(struct entete), 1, f->fichier);  // Écrit l'entête du fichier (entety) dans le fichier
    fclose(f->fichier);
    free(f);                                               // Libère la mémoire allouée dynamiquement pour la structure sfsdtovc
}

// lire un bloc spécifique à partir d'un fichier  et le stocker dans le buffer (buf est un pointeur vers le buffer)
void lire(sfsdtovc *f, int num_block, buffer *buf)
{
    if (num_block <= (f->entetef).No_dern_bloc)
    {
        fseek(f->fichier, sizeof(entete) + (num_block - 1) * sizeof(struct block), SEEK_SET); //(SEEK_SET) qui définit le début du fichier comme référence.
        fread(buf, sizeof(struct block), 1, f->fichier);
    }
}
// écrire le contenu d'un tampon (buffer) dans un bloc spécifique

void ecrire(sfsdtovc *f, int num_block, buffer *buf)
{
    if (num_block <= (f->entetef).No_dern_bloc)
    {
        fseek(f->fichier, sizeof(entete) + (num_block - 1) * sizeof(struct block), SEEK_SET);
        fwrite(buf, sizeof(struct block), 1, f->fichier);
    }
}

// La fonction est conçue pour retourner différentes valeurs de l'entête du fichier en fonction de la valeur de i

int entete_f(sfsdtovc *f, int i)
{
    if (i == 1)
        return f->entetef.No_dern_bloc;
    if (i == 2)
        return f->entetef.NB_enreg_inser;
    if (i == 3)
        return f->entetef.NB_enreg_suppr;







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



