#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <string.h>

// affichage de menu

void affichermenu(){

    printf("******************************\n");
    printf("Nos services :\n \n");
    printf("*1* Ajouter un nouveau compte. \n");
    printf("*2* Ajouter un bus a la base de donnee. \n");
    printf("*3* Creer une nouvelle resevetion. \n");
    printf("*4* Afficher les details des bus. \n");
    printf("*5* afficher les details d'une reservation. \n");
    printf("*6* Modifier les details d'une reservation. \n");
    printf("*0* Sortir de l'application \n \n");
    printf("******************************\n");

}
// partie d'ajout d'un voyageur

typedef struct date{

    int j,m,a;

}date;

typedef struct heure{

    int h,m;

}heure;

typedef struct voyageur{

    int numvoy;
    char nom[20],prenom[20],adresse[20];
    int cin;

}voyageur;


struct voyageur creevoyajeur(){

    struct voyageur v;

    printf("Vous devez saisir les données suivant : \n \n");
    printf("Saisir le numéro du voyageur :");
    scanf("%d",&v.numvoy);
    printf("Saisir le nom du voyageur :");
    scanf("%s",v.nom);
    printf("Saisir le prenom du voyageur :");
    scanf("%s",v.prenom);
    printf("Saisir l'adresse actuelle du voyageur :");
    scanf("%s",v.adresse);
    printf("Saisir le numero de CIN : ");
    scanf("%d",&v.cin);

    return v;
}
void ajoutvoyageur(char *filename,struct voyageur v){

    FILE *f=fopen(filename,"a");
    fwrite(&v, sizeof(struct voyageur), 1, f);
    fputc('\n', f);
    fclose(f);
    printf("L'ajout d'un voyageur a ete effectué avec succès.\nvotre identifiant est '%d' \nVous devez le conserver pour l'utiliser ulterirement !!! \n \n",v.numvoy);
}

// ajout un bus a la base de donnee


typedef struct bus{

    int numbus;
    char serie[2];
    char nature[6];
    int capacite;

}bus;

struct bus creebus(){

    struct bus b;
    printf("Donner le numéro du nouveau bus : ");
    scanf("%d",&b.numbus);
     printf("Donner la serie (Un caractère majuscule) et la nature (privé ou public) separees par une espace : ");
    scanf("%s %s",b.serie,b.nature);
    printf("Saisir son capacité : ");
    scanf("%d",&b.capacite);

    return b;
}

void ajoutbus(struct bus b){

    FILE *f=fopen("bus.txt","a");
    fwrite(&b, sizeof(struct bus), 1, f);
    fputc('\n', f);
    fclose(f);
    printf("L'ajout d'un bus a ete effectué avec succès \n \n");
}

// creation d'une reservation

typedef struct reservation{

    int numres,idvoy;
    char nomvoy[20],prenomvoy[20];
    int numbus;
    struct date datevoy;
    struct date dateretour;
    char destination[100];

}reservaion;

atomic_int identifiant = 0;

struct reservation creereservation(){

    struct reservation r;
    r.numres=__sync_fetch_and_add(&identifiant, 1);
    
    printf("Pour creer une nouvelle reservation vous devez remplir ce formulaire :\n \n");
    printf("Saisir votre identifiant : ");
    scanf("%d",&r.idvoy);
    printf("Saisir vote Nom : ");
    scanf("%s",r.nomvoy);
    printf("Saisir votre prenom : ");
    scanf("%s",r.prenomvoy);
    printf("Saisir le numero du bus : ");
    scanf("%d",&r.numbus);
    printf("Saisir la date de voyage (date de depart) sous la forme jj//mm//aaaa : ");
    scanf("%d/%d/%d",&r.datevoy.j,&r.datevoy.m,&r.datevoy.a);
    printf("Saisir la date de retour sous la forme jj//mm//aaaa : ");
    scanf("%d/%d/%d",&r.dateretour.j,&r.dateretour.m,&r.dateretour.a);
    printf("Saisir votre distinations :");
    scanf("%s",r.destination);

    return r;
}

void ajoutreservation(struct reservation r){

    FILE *f=fopen("reservation.txt","a");
    fwrite(&r, sizeof(struct bus), 1, f);
    fputc('\n', f);
    fclose(f);
    // printf("num res %d ifvoy %d nom voy %s prenom voy %s numbus %d date voy %d/%d/%d date retour %d/%d/%d destination %s \n",r.numres,r.idvoy,r.nomvoy,r.prenomvoy,r.numbus,r.datevoy.j,r.datevoy.m,r.datevoy.a,r.dateretour.j,r.dateretour.m,r.dateretour.a,r.destination);
    printf("Reservation effectué avec succès \n \n");
}

// afficher les details d'un bus

void afficherbus(){

    FILE *f;
    f = fopen("bus.txt", "r");
    fseek(f,sizeof(struct bus),SEEK_SET);
    struct bus b;

    while (fread(&b, sizeof(struct bus), 1, f) == 1) {
        printf("Numero du bus  %d    ", b.numbus);
        printf("Serie  %s     ", b.serie);
        printf("Nature  %s     ", b.nature);
        printf("Capacite  %d\n", b.capacite);
   }

   fclose(f);

}
int existres(int n){

    FILE *f;
    f = fopen("reservation.txt", "r");
    fseek(f,sizeof(struct reservation),SEEK_SET);
    struct reservation r;
    int test=0;

    while (fread(&r, sizeof(struct reservation), 1, f) == 1) {
        if(n==r.numres ){
            test =1;
            break;
        }
    }
    fclose(f);

    return test;
}

void afficherres(int numreser,int id){

    int test;
    test=existres(numreser);
    if(test==0)
    printf("Aucune reservation de cette caracteristique vous devez verifier vos donner !!! \n \n");
    else{

        FILE *f;
        f = fopen("reservation.txt", "r");
        fseek(f,sizeof(struct reservation),SEEK_SET);
        struct reservation r;
        while (fread(&r, sizeof(struct reservation), 1, f) == 1) {

            if(numreser==r.numres && id==r.idvoy){
                printf("num res %d ifvoy %d nom voy %s prenom voy %s numbus %d date voy %d/%d/%d date retour %d/%d/%d destination %s \n",r.numres,r.idvoy,r.nomvoy,r.prenomvoy,r.numbus,r.datevoy.j,r.datevoy.m,r.datevoy.a,r.dateretour.j,r.dateretour.m,r.dateretour.a,r.destination);
                test =1;
                break;
            }
        }
        
        fclose(f);
    }
}

//recherche d'une reservation
 
struct reservation rechercherres(int n){

    struct reservation r;
    if(existres(n)){
        FILE *f;
        f = fopen("reservation.txt", "r");
        fseek(f,sizeof(struct reservation),SEEK_SET);
        struct reservation r;

        while (fread(&r, sizeof(struct reservation), 1, f) == 1) {
            if(n==r.numres ){
                break;
            }
        }
        fclose(f);
        
        return r;
    }
    
}

// Supprimer une reservation 

void supprimerres(struct reservation r1) {

    struct reservation r;
    FILE *f=fopen("reservation.txt","r");
    int l=0;
    while (fread(&r, sizeof(struct reservation), 1, f) == 1) {

        if(r.numres==r1.numres){

            break;
        }

        l++;
    }
    l++;
    
    FILE *reservation_copie = fopen("reservation_copie.txt", "w");

    struct reservation reservations[1000];

    while (fgets(reservations, sizeof(reservations), f)) {

        if (!(l == atoi(reservations))) {

        fprintf(reservation_copie, "%s", reservations);

        }
    }
    fclose(f);
    fclose(reservation_copie);
    remove("reservation.txt");
    rename("reservation_copie.txt", "reservation.txt");
    printf("La supprission a ete effectue avec succe !!!");
}


// programme principale


int main(){
    
    // choix du service
    char c;
    char des[100];
    int i,n,e,f,g,h,test=0;
    struct voyageur v;
    struct voyageur bus[1000];
    int numv = 0;
    struct bus b;
    struct reservation r;
    int x,y;

    printf("Bienvenu sur E-Bus \n \n");
    printf("*********** Menu ********* \n");
    printf("******************************************\n");
    printf("Nos services :\n \n");
    printf("*1* Ajouter un nouveau compte. \n");
    printf("*2* Ajouter un bus a la base de donnee. \n");
    printf("*3* Creer une nouvelle resevetion. \n");
    printf("*4* Afficher les details des bus. \n");
    printf("*5* afficher les details d'une reservation. \n");
    printf("*6* Modifier les details d'une reservation. \n");
    printf("*7* Annuler une reservation. \n");
    printf("*0* Sortir de l'application \n \n");
    printf("******************************************\n");


   
    while(!test){
 
    printf("Pour acceder a un service saisir son numero (Taper -1 pour accede au menu):\n");
    scanf("%d",&n);

    switch (n)
    {
    case -1:

        affichermenu();
        break;

    case 0:

        printf("Vous avez quite l'application !!! \n");
        test=1;
        break;

    case 1:

        v=creevoyajeur();
        ajoutvoyageur("voyageur.txt",v);
        break;

    case 2:

        b=creebus();
        ajoutbus(b);
        break;

    case 3:

        r=creereservation();
        ajoutreservation(r);
        break;

    case 4:

        afficherbus();
        break;

    case 5:

        printf("Saisir le numero de la reservation et votre numere (identifiant) :");
        scanf("%d %d",&x,&y);
        afficherres(x,y);
        break;

    case 6:

        printf("Saisir le numero de la reservation :");
        scanf("%d",h);
        test = 0;

        while(test==0){

            r=rechercherres(h);

            printf("Que voulez vous modifier \n");
            printf("********************************\n\n");
            printf("*1* Le numero du bus.\n");
            printf("*2* La date de voyage.\n");
            printf("*3* La date de retour.\n");
            printf("*4* Les distination.\n");
            printf("*0* Vous n'avez aucune modification.\n \n");
            printf("********************************\n");
            
            scanf("%d",i);
            switch (i){

            case 0:

                test=1;
                break;

            case 1:

                supprimerres(r);
                printf("Donner le nouveau numero du bus:");
                scanf("%d",&e);
                r.numbus=e;
                ajoutreservation(r);
                printf("Modification effectue avec secce !!");
                break;

            case 2:

                supprimerres(r);
                printf("Donner la nouvelle date de voyage sous la forme jj/mm/aaaa :");
                scanf("%d/%d/%d",&e,&f,&g);
                r.datevoy.j=e;
                r.datevoy.m=f;
                r.datevoy.a=g;
                ajoutreservation(r);
                printf("Modification effectue avec secce !!");
                break;

            case 3:

                supprimerres(r);
                printf("Donner la nouvelle date de retour sous la forme jj/mm/aaaa :");
                scanf("%d/%d/%d",&e,&f,&g);
                r.dateretour.j=e;
                r.dateretour.m=f;
                r.dateretour.a=g;
                ajoutreservation(r);
                printf("Modification effectue avec secce !!");
                break;

            case 4:

                supprimerres(r);
                printf("Donner les nouvelle destinations :");
                scanf("%s",des);
                strcpy(r.destination,des);
                ajoutreservation(r);
                printf("Modification effectue avec secce !!");
                break;

            }
            
        }
    case 7: 

        printf("Donner le numero de la reservation a annuler :");
        scanf("%d",&g);
        r=rechercherres(g);
        supprimerres(r);
        break;
        
    }
    

    }

}
