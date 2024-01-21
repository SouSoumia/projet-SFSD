#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100
//*************************************************cr�ation de fichier*************************************************************
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
    int NB_enreg_inser;             // nombre d'enregistrement ins�ri�
    int NB_enreg_suppr;            // nombre d'enregistrement supprim�
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
        if (mode == 'n')                         //cr�er un nouveau fichier ou ouvrir en mode cr�ation
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
    fwrite(&(f->entetef), sizeof(struct entete), 1, f->fichier);  // �crit l'ent�te du fichier (entety) dans le fichier
    fclose(f->fichier);
    free(f);                                               // Lib�re la m�moire allou�e dynamiquement pour la structure sfsdtovc
}

// lire un bloc sp�cifique � partir d'un fichier  et le stocker dans le buffer (buf est un pointeur vers le buffer)
void lire(sfsdtovc *f, int num_block, buffer *buf)
{
    if (num_block <= (f->entetef).No_dern_bloc)
    {
        fseek(f->fichier, sizeof(entete) + (num_block - 1) * sizeof(struct block), SEEK_SET); //(SEEK_SET) qui d�finit le d�but du fichier comme r�f�rence.
        fread(buf, sizeof(struct block), 1, f->fichier);
    }
}
// �crire le contenu d'un tampon (buffer) dans un bloc sp�cifique

void ecrire(sfsdtovc *f, int num_block, buffer *buf)
{
    if (num_block <= (f->entetef).No_dern_bloc)
    {
        fseek(f->fichier, sizeof(entete) + (num_block - 1) * sizeof(struct block), SEEK_SET);
        fwrite(buf, sizeof(struct block), 1, f->fichier);
    }
}

// La fonction est con�ue pour retourner diff�rentes valeurs de l'ent�te du fichier en fonction de la valeur de i

int entete_f(sfsdtovc *f, int i)
{
    if (i == 1)
        return f->entetef.No_dern_bloc;
    if (i == 2)
        return f->entetef.NB_enreg_inser;
    if (i == 3)
        return f->entetef.NB_enreg_suppr;

  //cette proc�dure permet de modifier diff�rentes valeurs de l'ent�te fonction de la valeur de i
void aff_entete(sfsdtovc *f, int i, int val)
{
    if (i == 1)
        f->entetef.No_dern_bloc = val;
    if (i == 2)
        f->entetef.NB_enreg_inser = val;
    if (i == 3)
        f->entetef.NB_enreg_suppr = val; // Si i est �gal � 4 la proc�dure met � jour la valeur de NB_enreg_suppr dans la structure entetef de la structure tovc avec la valeur fournie (val).
}
// llouer un nouveau bloc dans le fichier on va l'utiliser apr�s
int alloc_block(sfsdtovc *f)
{
    aff_entete(f, 1, entete_f(f, 1) + 1);
    aff_entete(f, 2, 0);
    return entete_f(f, 1);


// parcourir tous les blocs du fichier et les afficher et lit le contenu de chaque bloc du fichier dans un buffer et ex�cute potentiellement des op�rations sur les donn�es du buffer

void afficher(sfsdtovc *f)
{
    int i = 1, j;                                      //i � 1 pour repr�senter le num�ro du bloc en cours d'examen
    buffer buf;
    while (i <= (entete_f(f, 1)))
    {
        j = 0;
        lire(f, i, &buf);     //pour lire le contenu du bloc num�ro i du fichier dans le buffer (buf).
        while (j < max)
        {
        }
        i++;   //Incr�mente le num�ro du bloc (i) pour passer au bloc suivant lors de la prochaine it�ration de la boucle principale.
    }





}
void suppression_logique(sfsdtovc *f,  char nom[50], char prenom[50],int matricule){ // on commence par donner le nom prenom et matricule a supprimer
 int i,j,trouve;
 buffer buf;
 // on cherche l'etudiant a supprimer
 recherche(f,nom,prenom,matricule,&trouve,&i,&j);
 if (trouve){
    lire(f,i,&buf);
 buf.tab[j]='V';
 ecrire(f,i,&buf);

 }
 }






int main()
 { 
int mat,i,j;
char nom[50];
char prenom[50];
val ind[20];
int choice,choice1
printf("\n MENU PRINCIPAL");
Printf("1-START \n");
Printf("2-QUITTER \n");
Printf("\n\n VOTRE CHOIX :");
Scanf("%d", &choice);
switch (choice){
    case 0: // fin programme ;
    {
        goto end;
    }
    case 1: // nouveau fichier
    {
 system("cls");

        printf("\n\n 1 : Creation;\n");
        printf(" 2 : Recherche;\n");
        printf("3 : Supression logique;\n");

         printf("\n\n Votre choix : ");
        scanf("%d", &choice1);







 }
  return 0;
}



