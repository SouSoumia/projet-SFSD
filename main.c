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
}
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

}
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
void creation_fichier(char nomfich[256], char fichnoms[256], char fichprenoms[256], int *n)
{
    buffer buf;
    char chaine[256], matricule[5], nomE[256];
    int k, i = 1, j = 0;
    char prenom[256], nom[256];
    int trouve;
    srand(time(NULL));

    // nombre d'insertions
    printf("Combien d'eleve initialement ?");
    scanf("%d", n);

    for (int k = 0; k < *n; k++)
    {
        gen_enrg(fichnoms, fichprenoms, chaine);
        if (k == 0)
        {
            insertion(nomfich, chaine, 1);
        }
        else
        {
            insertion(nomfich, chaine, 2);
        }
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
int matricule,i,j,n;
char nom[50];
char prenom[50];
int trouve;
int choix,choix1;
menuprincipal:
   printf("______________________________________________________________________________\n");
    printf("\n  LE MENU PRINCIPAL");
    printf("\n ______________________________________________________________________________\n\n\n");
    printf(" [1] : start;\n");
    printf(" [0] : quitter;\n");
Scanf("%d", &choix);
switch (choix){
    case 0: // fin programme ;
    {
        goto end;
    }
    case 1: // nouveau fichier
    {
 
 manipulation_fichier:
        system("cls");

        printf("\n\n [1] : Creation;\n");
        printf(" [2] : Recherche;\n");
        printf(" [3] : Affichage;\n");
        printf(" [4] : Supression logique;\n");
          printf("\n\n Votre choix : ");
        scanf("%d", &choix1);


  switch (choix1)
        {
        case 0: // retour au menu principal
        {
            goto menuprincipal;
        }
        case 1: // insertion
        {
            printf("\n\n\n ________________________________\n");
            printf("\n  CREATION DU FICHIER INITIALE :");
            printf("\n ________________________________\n\n\n");
            creation_fichier("ficherIn", "noms.txt", "prenoms.txt" , &n);
            printf("creation avec succes!\n");
            printf("tap to continue...");
            getch();
            goto manipulation_fichier;
        }
        case 2: // recherche
        {

            printf("\n\n\n ________________________________\n");
            printf("\n  LA RECHERCHE :");
            printf("\n ________________________________\n\n\n");

            affichage("ficherIn");

            printf("~REMARQUE~\n");
            printf("notre enregistrement contient:\n");
            printf("champ_eff(1 car)+matricule(4car)+nom,prenom.\n\n");

            sfsdtovc *f = ouvrir("ficherIn", 'a');
            printf("\nEntrer nom: ");
            scanf("%s", nom);
            printf("Entrer prenom: ");
            scanf("%s", prenom);
            getchar();
            printf("entrer matricule:");
            scanf("%d", matricule);

            Recherche(f,nom,prenom,matricule,&trouve,&i,&j);
    if (trouve)
            {
                printf("\nElement trouve! dans le bloc %d en position %d\n", i, j);
            }
            else
            {
                printf("\nElement non trouve dans le fichier!");
            }
            fermer(f);
            printf("\ntap to continue...");

            getch();
            goto manipulation_fichier;
        }
 
            case 3:
        {
            printf("\n\n\n ______________________________________________________________________________\n");
            printf("\n  SUPRESSION LOGIQUE:");
            printf("\n ______________________________________________________________________________\n\n\n");

            affichage("ficherIn");
            printf("\n");
            printf("~REMARQUE~\n");
            printf("notre enregistrement contient:\n");
            printf("champ_eff(1 car)+matricule(4car)+nom,prenom.\n\n");

            sfsdtovc *f = ouvrir("ficherIn", 'a');
            printf("\n Eleve a supprimer :\n");
            printf("\nEntrer nom: ");
            scanf("%s", nom);
            printf("Entrer prenom: ");
            scanf("%s", prenom);
            getchar();
            printf("entrer matricule:");
            scanf("%d", matricule);

              suppression_log(f, nom, prenom, matricule);
            fermer(f);
            printf("\ntap to continue...");

            getch();
            goto manipulation_fichier;
        }



 }
    }
}   
end:
  return 0;
}



