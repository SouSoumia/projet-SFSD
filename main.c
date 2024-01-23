#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100
//*************************************************crï¿½ation de fichier*************************************************************
  // enregistrement physique
  typedef struct etudiant
{
    char nom[50];
    char prenom[50];
    int matricule;
    char fineng;
    char finchamps;
    int taille;

}etudiant;






 typedef struct block
{
    char tab[max];

} block;






typedef block buffer;







typedef struct entete
{
    int No_dern_bloc;                // indice de dernier bloc
<<<<<<< HEAD
    int NB_enreg_inser;             // nombre d'enregistrement insï¿½riï¿½
    int NB_enreg_suppr;            // nombre d'enregistrement supprimï¿½
=======
    int NB_enreg_inser;             // nombre d'enregistrement insérié
    int NB_enreg_suppr;            // nombre d'enregistrement supprimé
    int ind_pos_libre;            // indice de position libre
>>>>>>> 30d88f35e027f7073d9b279933fc2392060ac3f2
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
        if (mode == 'n')                         //crï¿½er un nouveau fichier ou ouvrir en mode crï¿½ation
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
    fwrite(&(f->entetef), sizeof(struct entete), 1, f->fichier);  // ï¿½crit l'entï¿½te du fichier (entety) dans le fichier
    fclose(f->fichier);
    free(f);                                               // Libï¿½re la mï¿½moire allouï¿½e dynamiquement pour la structure sfsdtovc
}

<<<<<<< HEAD
// lire un bloc spï¿½cifique ï¿½ partir d'un fichier  et le stocker dans le buffer (buf est un pointeur vers le buffer)
=======









// lire un bloc spécifique à partir d'un fichier  et le stocker dans le buffer (buf est un pointeur vers le buffer)
>>>>>>> 30d88f35e027f7073d9b279933fc2392060ac3f2
void lire(sfsdtovc *f, int num_block, buffer *buf)
{
    if (num_block <= (f->entetef).No_dern_bloc)
    {
        fseek(f->fichier, sizeof(entete) + (num_block - 1) * sizeof(struct block), SEEK_SET); //(SEEK_SET) qui dï¿½finit le dï¿½but du fichier comme rï¿½fï¿½rence.
        fread(buf, sizeof(struct block), 1, f->fichier);
    }
}
<<<<<<< HEAD
// ï¿½crire le contenu d'un tampon (buffer) dans un bloc spï¿½cifique
=======












// écrire le contenu d'un tampon (buffer) dans un bloc spécifique
>>>>>>> 30d88f35e027f7073d9b279933fc2392060ac3f2

void ecrire(sfsdtovc *f, int num_block, buffer *buf)
{
    if (num_block <= (f->entetef).No_dern_bloc)
    {
        fseek(f->fichier, sizeof(entete) + (num_block - 1) * sizeof(struct block), SEEK_SET);
        fwrite(buf, sizeof(struct block), 1, f->fichier);
    }
}

<<<<<<< HEAD
// La fonction est conï¿½ue pour retourner diffï¿½rentes valeurs de l'entï¿½te du fichier en fonction de la valeur de i
=======











// La fonction est conçue pour retourner différentes valeurs de l'entête du fichier en fonction de la valeur de i
>>>>>>> 30d88f35e027f7073d9b279933fc2392060ac3f2

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
<<<<<<< HEAD
}
  //cette procï¿½dure permet de modifier diffï¿½rentes valeurs de l'entï¿½te fonction de la valeur de i
=======


}
















  //cette procédure permet de modifier différentes valeurs de l'entête fonction de la valeur de i
>>>>>>> 30d88f35e027f7073d9b279933fc2392060ac3f2
void aff_entete(sfsdtovc *f, int i, int val)
{
    if (i == 1)
        f->entetef.No_dern_bloc = val;
    if (i == 2)
        f->entetef.ind_pos_libre = val;
    if (i == 3)
<<<<<<< HEAD
        f->entetef.NB_enreg_suppr = val; // Si i est ï¿½gal ï¿½ 4 la procï¿½dure met ï¿½ jour la valeur de NB_enreg_suppr dans la structure entetef de la structure tovc avec la valeur fournie (val).
}
// llouer un nouveau bloc dans le fichier on va l'utiliser aprï¿½s
=======
        f->entetef.NB_enreg_inser = val;
    if (i == 4)
        f->entetef.NB_enreg_suppr = val; // Si i est égal à 4 la procédure met à jour la valeur de NB_enreg_suppr dans la structure entetef de la structure tovc avec la valeur fournie (val).
}














// llouer un nouveau bloc dans le fichier on va l'utiliser aprés
>>>>>>> 30d88f35e027f7073d9b279933fc2392060ac3f2
int alloc_block(sfsdtovc *f)
{
    aff_entete(f, 1, entete_f(f, 1) + 1);
    aff_entete(f, 2, 0);
    return entete_f(f, 1);
}






}
// parcourir tous les blocs du fichier et les afficher et lit le contenu de chaque bloc du fichier dans un buffer et exï¿½cute potentiellement des opï¿½rations sur les donnï¿½es du buffer

void afficher(sfsdtovc *f)
{
    int i = 1, j;                                      //i ï¿½ 1 pour reprï¿½senter le numï¿½ro du bloc en cours d'examen
    buffer buf;
    while (i <= (entete_f(f, 1)))
    {
        j = 0;
        lire(f, i, &buf);     //pour lire le contenu du bloc numï¿½ro i du fichier dans le buffer (buf).
        while (j < max)
        {
            printf("%c", buf.tab[j]);

            j++;
        }
        i++;   //Incrementer le numéro du bloc (i) pour passer au bloc suivant lors de la prochaine itération de la boucle principale.
    }
    printf("\n");

}












 //************************************insertion d'element saisie par l'utilisateur***********************************************








   void lire(sfsdtovc *f, int num_block, buffer *buf);
    void EcrireDir(sfsdtovc *f, int i, struct block *buf);





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











        // lecture et écriture d'après le buffer
         lire(f, num_bloc, &buf);

    // Mettre à jour les informations dans l'entête
    aff_entete(f, 2, f->entetef.ind_pos_libre + 1);
    aff_entete(f, 3, f->entetef.NB_enreg_inser + 1);








    // Partie du code traitant les derniers caractères restants dans le tableau Tab du dernier bloc





    int ind = 0;
    int indc;
    int j = 0;
    char Tab[max];
    int b = max;
    int i = num_bloc; // Mettre à jour i avec le numéro de bloc actuel

    indc = b - 1;





    while (ind != indc)
    {
        buf.tab[j] = Tab[ind];
        ind = (ind + 1) % b;
        j++;

        // Si j = b, écrire le bloc dans le fichier
        if (j == b)
        {
            EcrireDir(f, i, &buf);
            j = 0;
            i++;
        }
<<<<<<< HEAD
        i++;   //Incrï¿½mente le numï¿½ro du bloc (i) pour passer au bloc suivant lors de la prochaine itï¿½ration de la boucle principale.
=======
>>>>>>> 30d88f35e027f7073d9b279933fc2392060ac3f2
    }
}
void mat_aleat(char chaine[3])
{
    int min = 0; //dÃ©finissent les bornes pour la gÃ©nÃ©ration de nombres alÃ©atoires entre 0 et 9 inclus.
    int maxi = 9; 
    char c; //est utilisÃ© pour stocker chaque caractÃ¨re gÃ©nÃ©rÃ©.
    int x; // est la valeur gÃ©nÃ©rÃ©e alÃ©atoirement entre min et maxi.
    FILE *fichier = fopen("ids.txt", "r+");
    int vrai = 0;
    ;
    char nom[256];
    while (vrai == 0)
    {

        vrai = 1;
        for (int i = 0; i < 4; i++)
        {
            x = rand() % (maxi + 1 - min) + min;
            c = x + '0';
            chaine[i] = c;
        }
        chaine[4] = '\0';

        while (!feof(fichier))
        {
            fgets(nom, 256, fichier);
            if (strcpy(nom, chaine) == 0)
            {
                vrai = 0;
            }
        }
    }
    fputs("\n", fichier);
    fputs(chaine, fichier);
    fclose(fichier);
}
void alea_nom_prenom(char chaine[256], char nomfich1[256], char nomfich2[256])
{
    int min = 1;
    int maxi = 5;
    // srand(time(NULL));
    int i = rand() % (maxi + 1 - min) + min;
    int j = rand() % (maxi + 1 - min) + min;
    strcpy(chaine, "\0");

    // reccupere le nom et le prenom
    char nom[256];

    FILE *fichier = fopen(nomfich1, "r");
    while (i > 0)
    {
        fgets(nom, 256, fichier);
        i--;
    }
    fclose(fichier);
    char prenom[256];
    FILE *fichier2 = fopen(nomfich2, "r");

    while (j > 0)
    {
        fgets(prenom, 256, fichier2);
        j--;
    }
    fclose(fichier2);
    // pour suprimmer le dernier saut de ligne
    int k = 0;
    int z = 0;
    while (prenom[k] != '\0')
    {
        if (prenom[k] != '\n')
        {
            prenom[z] = prenom[k];
            z++;
        }
        k++;
    }
    prenom[z] = '\0';

    k = 0;
    z = 0;
    while (nom[k] != '\0')
    {
        if (nom[k] != '\n')
        {
            nom[z] = nom[k];
            z++;
        }
        k++;
    }
    nom[z] = '\0';

    strcat(nom, ",");
    strcat(nom, prenom);
    int x = strlen(nom);
    char s[256];
    sprintf(s, "%d", x);
    strcat(chaine, s);
    strcat(chaine, nom);
}

void gen_enrg(char fnom[256], char fprenom[256], char chaine[256])
{
    char matricule[5], nomE[256];
    strcpy(chaine, "F"); // eff <- faux donc enregistrement existant logiquement
    mat_aleat(matricule);
    alea_nom_prenom(nomE, fnom, fprenom);
    strcat(chaine, matricule);
    strcat(chaine, nomE);




    // Fin de la boucle de traitement
    // On termine la copie des caractères restants de Tab dans le dernier bloc






    buf.tab[j] = Tab[ind];
    j++;





    // Ecrire le dernier bloc dans le fichier
        EcrireDir(f, i, &buf);





    // Mettre à jour les informations dans l'entête
    aff_entete(f, 1, i);
    aff_entete(f, 2, j);





    Fermer(f);
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

            afficher("ficherIn");

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

            afficher("ficherIn");
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

              suppression_logique(f, nom, prenom, matricule);
            fermer(f);
            printf("\ntap to continue...");

            getch();
            goto manipulation_fichier;
        }

   // Ouvrir le fichier en mode création

    sfsdtovc *fichier = ouvrir("votre_fichier.dat", 'n');

    inserer_element(fichier);

    afficher(fichier);

    fermer(fichier);

 }
    }
}   
end:
  return 0;
}



