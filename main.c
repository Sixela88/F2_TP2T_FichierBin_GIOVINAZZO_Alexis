#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 1000
//BUT : Realiser un programme pour ecrire dans un fichier binaire puis le lire.

//Type Date de naissance
typedef struct Date{
    int j;
    int m;
    int a;
}Date;

//Type Carte identité
typedef struct Cid{
    int NumCarte;
    char Nom[32];
    char Prenom[32];
    char Sexe;
    Date DateNaiss;
    char Ville[32];
}Cid;

//Prototypes :
void AffichMenu(int *choix);
void AjouterCID();
void ConsulterCID();


int main()
{
    int choix=0;


    do{
        //Menu du programme
        AffichMenu(&choix);
        switch (choix){
            case 1 :
                AjouterCID();
                break;
            case 2 :
                ConsulterCID();
                break;
            case 3 :
                printf("Vous quittez le programme\n");
                break;
            default :
                printf("Erreur, veuillez recommencer votre saisie de choix\n");
                break;
        }
        system("pause");
        system("cls");
    }while (choix==1 || choix==2);
    return 0;
}

void AffichMenu(int *choix){
    //BUT : Afficher le menu du programme
    //ENTREES : Choix de l'utilisateur
    //SORTIES //
    printf("Enregistrement de carte d'identite dans un fichier\n");
    printf("Menu :\n");
    printf("        1) Ajouter une CI\n");
    printf("        2) Consulter CI\n");
    printf("        3) Quitter\n");
    scanf("%d",choix);
}

void AjouterCID(){
    //BUT : Ecrire dans un fichier
    //ENTREES : Donnees de l'utilisateur (type CID)
    //SORTIES : Donnees ecrites dans le fichier
    FILE* fichierCI = NULL; //descripteur de fichier
    Cid Carteid,*pCarteid=NULL;//

    pCarteid = (Cid*) malloc(sizeof(Cid));
    printf("Munissez vous de vos informations\n");
    printf("Saisissez votre numero de carte d'identite\n");
    scanf("%d",&Carteid.NumCarte);
    pCarteid->NumCarte = Carteid.NumCarte;
    fflush(stdin);

    printf("Saisissez votre nom\n");
    scanf("%s",Carteid.Nom);
    strcpy(pCarteid->Nom,Carteid.Nom);
    fflush(stdin);

    printf("Saisissez votre prenom\n");
    scanf("%s",Carteid.Prenom);
    strcpy(pCarteid->Prenom,Carteid.Prenom);
    fflush(stdin);

    printf("Saisissez votre sexe (M/F)\n");
    scanf("%c",&Carteid.Sexe);
    pCarteid->Sexe = Carteid.Sexe;
    fflush(stdin);

    printf("Saisissez votre date de naissance (JJ MM AAAA) \n");
    scanf("%d%d%d",&Carteid.DateNaiss.j,&Carteid.DateNaiss.m,&Carteid.DateNaiss.a);
    pCarteid->DateNaiss.j = Carteid.DateNaiss.j;
    pCarteid->DateNaiss.m = Carteid.DateNaiss.m;
    pCarteid->DateNaiss.a = Carteid.DateNaiss.a;
    fflush(stdin);

    printf("Saisissez votre ville\n");
    scanf("%s",Carteid.Ville);
    strcpy(pCarteid->Ville,Carteid.Ville);
    fflush(stdin);
    //Ecriture dans le fichier
    fichierCI = fopen("fichiertestCI.bin","ab"); // Ouverte d'un fichier.bin
    if (fichierCI != NULL){
        fwrite( pCarteid , sizeof(Cid) , sizeof(pCarteid) , fichierCI );
        fclose(fichierCI);
        free (pCarteid);
    }
    else
    {
        // Sinon on affiche un message d'erreur
        printf("Impossible d'ouvrir le fichiertestCI.bin");
    }
}

void ConsulterCID(){
    //BUT : Consulter les cartes d'identite stockees dans le fichier
    //ENTREES : Taille du fichier et donnes du fichier
    //SORTIES : Affiche le contenu du fichier
    FILE* fichierCI = NULL;
    Cid *AffichCid=NULL;
    long lSize;

    printf("Consultation\n");
    fichierCI = fopen("fichiertestCI.bin","rb"); //Ouverture du fichier en mode lecture
    if (fichierCI != NULL){
        fseek (fichierCI , 0 , SEEK_END);
        lSize = ftell (fichierCI); //Taille du fichier
        rewind (fichierCI); //Pointeur se replace au debut du fichier

        // allocate memory to contain the whole file:
        AffichCid = (Cid*) malloc (sizeof(Cid)*lSize); //Allocation de memoire du pointeur

        if (AffichCid == NULL) {
            printf("Memory error");
        }
        do // On lit le fichier jusqu'a la fin
        {
            fread(AffichCid,sizeof(Cid),sizeof(AffichCid),fichierCI); //Affecte a AffichCid les donnes du fichier
            printf("Num : %d\nNom : %s\nPrenom : %s\nSexe : %c\nDate de naissance : %d/%d/%d\nVille : %s\n",AffichCid->NumCarte,AffichCid->Nom,
            AffichCid->Prenom,AffichCid->Sexe,AffichCid->DateNaiss.j,AffichCid->DateNaiss.m,AffichCid->DateNaiss.a,AffichCid->Ville); //Affiche
        }while (EOF==1);
        free (AffichCid); //Libere
    }
    else
    {
        // Sinon on affiche un message d'erreur
        printf("Impossible d'ouvrir le fichiertestCI.bin");
    }
    fclose(fichierCI); //Ferme le fichier
}
