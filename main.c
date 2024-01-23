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
        if (mode == 'n')                         //cr�er un nouveau fichier ou ouvrir en mode cr�ation
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
        return f->entetef.ind_pos_libre;
    if (i == 3)
        return f->entetef.NB_enreg_inser;
    if (i == 4)
        return f->entetef.NB_enreg_suppr;

  //cette proc�dure permet de modifier diff�rentes valeurs de l'ent�te fonction de la valeur de i
void aff_entete(sfsdtovc *f, int i, int val)
{
    if (i == 1)
        f->entetef.No_dern_bloc = val;
    if (i == 2)
        f->entety.ind_pos_libre = val;
    if (i == 3)
        f->entetef.NB_enreg_inser = val;
    if (i == 4)
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
        i++;   //Incrementer le num�ro du bloc (i) pour passer au bloc suivant lors de la prochaine it�ration de la boucle principale.
    }



}

 //************************************insertion d'element saisie par l'utilisateur***********************************************

 void inserer_element(sfsdtovc *f) {
    etudiant etud;


     printf("Saisir le nom : ");
     scanf("%s", etud.nom);


    printf("Saisir le pr�nom : ");
    scanf("%s", etud.prenom);


    printf("Saisir le matricule : ");
    scanf("%d", &etud.matricule);


     buffer buf;
     int num_bloc;



     // Demander � l'utilisateur le num�ro du bloc o� ins�rer l'�tudiant


       printf("Saisir le num�ro du bloc pour l'insertion : ");
       scanf("%d", &num_bloc);



        if (num_bloc > f->entetef.No_dern_bloc) {
        printf("Le bloc sp�cifi� n'existe pas. L'insertion a �chou�.\n");
        return;
    }

    // lecture et �criture d'apr�s le buffer
      lire(f, num_bloc, &buf);
      ecrire(f, num_bloc, &buf);

      // Mettre � jour les informations dans l'ent�te

       aff_entete(f, 2, f->entetef.ind_pos_libre + 1);
       aff_entete(f, 3, f->entetef.NB_enreg_inser + 1);

       printf("Insertion r�ussie.\n");
}


// Binary search for the info by the matricule, the returned value is the index of the block where the info is found, the index of the block where the info is found, and a var trouve to indicate if the info is found or not

void Binary_Search(sfsdtovc *f, int matricule, int *num_bloc , int *num_eng , int *trouve)
{
    buffer buf;
    int i = 1, j = 0;
    int bi = 1, bs = entete_f(f, 1);
    *trouve = 0; // 0 = false
    *num_bloc = 0;
    *num_eng = 0;

    while(bi <= bs && *trouve == 0)
    {
        i = (bi + bs) / 2;
        lire(f, i, &buf);
        while (j < max && *trouve == 0)
        {
            if (buf.tab[j] == matricule)
            {
                *trouve = 1;
                *num_bloc = i;
                *num_eng = j;
            }
            j++;
        }
        if (buf.tab[j] > matricule)
            bs = i - 1;
        else
            bi = i + 1;
    }
    
    
}

























int main()
 {




        return 0;
 }



