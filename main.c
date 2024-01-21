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
    int ind_pos_libre;            // indice de position libre
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
            f->entetef.ind_pos_libre = 0;
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
        return f->entetef.ind_pos_libre;
    if (i == 3)
        return f->entetef.NB_enreg_inser;
    if (i == 4)
        return f->entetef.NB_enreg_suppr;

  //cette procédure permet de modifier différentes valeurs de l'entête fonction de la valeur de i
void aff_entete(sfsdtovc *f, int i, int val)
{
    if (i == 1)
        f->entetef.No_dern_bloc = val;
    if (i == 2)
        f->entety.ind_pos_libre = val;
    if (i == 3)
        f->entetef.NB_enreg_inser = val;
    if (i == 4)
        f->entetef.NB_enreg_suppr = val; // Si i est égal à 4 la procédure met à jour la valeur de NB_enreg_suppr dans la structure entetef de la structure tovc avec la valeur fournie (val).
}
// llouer un nouveau bloc dans le fichier on va l'utiliser aprés
int alloc_block(sfsdtovc *f)
{
    aff_entete(f, 1, entete_f(f, 1) + 1);
    aff_entete(f, 2, 0);
    return entete_f(f, 1);


// parcourir tous les blocs du fichier et les afficher et lit le contenu de chaque bloc du fichier dans un buffer et exécute potentiellement des opérations sur les données du buffer

void afficher(sfsdtovc *f)
{
    int i = 1, j;                                      //i à 1 pour représenter le numéro du bloc en cours d'examen
    buffer buf;
    while (i <= (entete_f(f, 1)))
    {
        j = 0;
        lire(f, i, &buf);     //pour lire le contenu du bloc numéro i du fichier dans le buffer (buf).
        while (j < max)
        {
        }
        i++;   //Incrementer le numéro du bloc (i) pour passer au bloc suivant lors de la prochaine itération de la boucle principale.
    }



}

 //************************************insertion d'element saisie par l'utilisateur***********************************************

 void inserer_element(sfsdtovc *f) {
    etudiant etud;


     printf("Saisir le nom : ");
     scanf("%s", etud.nom);


    printf("Saisir le prénom : ");
    scanf("%s", etud.prenom);


    printf("Saisir le matricule : ");
    scanf("%d", &etud.matricule);


     buffer buf;
     int num_bloc;



     // Demander à l'utilisateur le numéro du bloc où insérer l'étudiant


       printf("Saisir le numéro du bloc pour l'insertion : ");
       scanf("%d", &num_bloc);



        if (num_bloc > f->entetef.No_dern_bloc) {
        printf("Le bloc spécifié n'existe pas. L'insertion a échoué.\n");
        return;
    }

    // lecture et écriture d'aprés le buffer
      lire(f, num_bloc, &buf);
      ecrire(f, num_bloc, &buf);

      // Mettre à jour les informations dans l'entête

       aff_entete(f, 2, f->entetef.ind_pos_libre + 1);
       aff_entete(f, 3, f->entetef.NB_enreg_inser + 1);

       printf("Insertion réussie.\n");


      /*Cette partie du code que je vais écrit effectue le traitement des derniers caractères restants dans le tableau
      Tab du dernier bloc. Elle parcourt circulairement Tab à partir de l'indice ind jusqu'à l'indice indc.
      Ensuite, elle écrit le bloc dans le fichier et met à jour les informations dans l'entête (AFF_Entete).
      Enfin, elle ferme le fichier (Fermer(f)). */


      ind == indc;

      indc--; // Si (indc < 0) indc := e.Taille

    while (ind != indc) {

              buf.Tab[j] = Tab[ind];
              ind = (ind + 1) % e.taille;
              j++;
}
     // Si j = b, écrire le bloc dans le fichier

    if (j == b) {
    EcrireDir(f, i, buf);
    j = 0;
    i++;
}

      // Fin de la boucle de traitement
     // On termine la copie des caractères restants de Tab dans le dernier bloc

       buf.Tab[j] = Tab[ind];
       j++;



     // Ecrire le dernier bloc dans le fichier
    EcrireDir(f, i, buf);

    // Mettre à jour les informations dans l'entête
       AFF_Entete(f, 1, i);
       AFF_Entete(f, 2, j);

       Fermer(f);













}




























int main()
 {




        return 0;
 }



