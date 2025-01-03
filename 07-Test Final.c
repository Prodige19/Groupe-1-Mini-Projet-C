//Test Final Projet (Avec initialisation des clients, des comptes et operation sur les comptes)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Déclaration des structures
struct client {
    char codecl[15];
    char prenom[15];
    char nom[15];
    int tel;
    char ville[15];
    struct client* suivant;
};

struct date { //Structure date pour le compte
    int jour;
    int mois;
    int annee;
};

struct compte {
    int numero;
    struct date dateouverture;
    char agence[15];
    float solde;
    char codecl[15];
    struct compte* suivant;
};

struct date2 { //Structure date pour les operations
    int jour;
    int mois;
    int annee;
};

struct operation {
    char codeop[15];
    int numero;
    int type;
    float montant;
    struct date2 dateop;
};

// Fonction pour allouer un nouveau client
struct client* allouerclient(const char* codecl, const char* prenom, const char* nom, int tel, const char* ville) {
    //Allocation de mémoire pour le nouveau client
    struct client* nouveau_client = (struct client*)malloc(sizeof(struct client));

    //Copie des informations pour le client
    if (nouveau_client != NULL) {
        strcpy(nouveau_client->codecl, codecl);
        strcpy(nouveau_client->prenom, prenom);
        strcpy(nouveau_client->nom, nom);
        nouveau_client->tel = tel;
        strcpy(nouveau_client->ville, ville); 
        nouveau_client->suivant = NULL;
    }
    return nouveau_client;
}

// Fonction pour allouer un nouveau compte
struct compte* allouercompte(int numero, struct date dateouverture, const char* agence, float solde, const char* codecl) {
    
    // Allocation de mémoire
    struct compte* nouveau_compte = (struct compte*)malloc(sizeof(struct compte));

    if (nouveau_compte != NULL) {
        //Copie des informations
        nouveau_compte->numero = numero;
        nouveau_compte->dateouverture = dateouverture;
        strcpy(nouveau_compte->agence, agence);
        nouveau_compte->solde = solde;
        strcpy(nouveau_compte->codecl, codecl);
        nouveau_compte->suivant = NULL;
    }
    return nouveau_compte;
}

// Fonction pour ajouter un client au début de la liste
struct client* ajouterclient(struct client* tete_client, const char* codecl, const char* prenom, const char* nom, int tel, const char* ville) {
    //Allocation de la mémoire pour le client
    struct client* nouveau_client = allouerclient(codecl, prenom, nom, tel, ville);
    if (nouveau_client != NULL) {
        nouveau_client->suivant = tete_client;
        tete_client = nouveau_client;
    }
    return tete_client;
}

// Fonction pour ajouter un compte au début de la liste
struct compte* ajoutercompte(struct compte* tete_compte, int numero, struct date dateouverture, const char* agence, float solde, const char* codecl) {
    // Allocation de la mémoire pour le nouveau compte
    struct compte* nouveau_compte = allouercompte(numero, dateouverture, agence, solde, codecl);
    if (nouveau_compte != NULL) {
        nouveau_compte->suivant = tete_compte;
        tete_compte = nouveau_compte;
    }
    return tete_compte;
}

// Fonction pour copier les clients dans le fichier clients.txt
void copieclient(struct client* tete_client, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "a+");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    struct client* p_client = tete_client;
    while (p_client != NULL) {
        fprintf(fichier, "codecl: %s, Prenom: %s, Nom: %s, tel: %d, Ville: %s\n", p_client->codecl, p_client->prenom, p_client->nom, p_client->tel, p_client->ville);
        p_client = p_client->suivant;
    }
    fclose(fichier);
    printf("Les clients ont été copiés dans le fichier %s\n", nomFichier);
}

// Fonction pour copier les comptes dans le fichier comptes.txt
void copiecompte(struct compte* tete_compte, const char* nomFichier) {

    //Ouverture du fichier en mode ajout
    FILE* fichier = fopen(nomFichier, "a+");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    struct compte* p_compte = tete_compte;
    
    //Ecriture dans le fichier txt
    while (p_compte != NULL) {
        fprintf(fichier, "numero: %d, date ouverture: %02d/%02d/%d, agence: %s, solde: %.2f, codecl: %s\n", p_compte->numero, p_compte->dateouverture.jour, p_compte->dateouverture.mois, p_compte->dateouverture.annee,p_compte->agence, p_compte->solde, p_compte->codecl);
        p_compte = p_compte->suivant;
    }
    fclose(fichier);
    printf("Les comptes ont été copiés dans le fichier %s\n", nomFichier);
}

// Fonction pour enregistrer l'opération dans le fichier operations.txt
void enregistrer_operation(const char* codeop, int numero, const char* type, float montant, struct date2 dateop) {
    FILE* fichier = fopen("operations.txt", "a");
    if (fichier != NULL) {
        fprintf(fichier, "codeop: %s, numero: %d, type: %s, montant: %.2f, date: %02d/%02d/%d\n", codeop, numero, type, montant, dateop.jour, dateop.mois, dateop.annee);
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

// Fonction pour effectuer un dépôt
int deposer(struct compte* tete_compte, int numero, float montant, const char* codeop, struct date2 dateop) {
    struct compte* p_depot = tete_compte;
    while (p_depot != NULL) {
        if (p_depot->numero == numero) {
            p_depot->solde += montant;
            // Enregistrer l'opération
            enregistrer_operation(codeop, numero, "depot", montant, dateop);
            return 1; // Succès
        }
        p_depot = p_depot->suivant;
    }
    return 0; // Échec, compte non trouvé
}

// Fonction pour effectuer un retrait
int retirer(struct compte* tete_compte, int numero, float montant, const char* codeop, struct date2 dateop) {
    struct compte* p_retrait = tete_compte;
    while (p_retrait != NULL) {
        if (p_retrait->numero == numero) {
            if (p_retrait->solde >= montant) {
                p_retrait->solde -= montant;
                // Enregistrer l'opération
                enregistrer_operation(codeop, numero, "retrait", montant, dateop);
                return 1; // Succès
            } else {
                return -1; // Échec, solde insuffisant
            }
        }
        p_retrait = p_retrait->suivant;
    }
    return 0; // Échec, compte non trouvé
}

int main(){

    // Initialisation des tete de structures
    struct client* tete_client = NULL;
    struct compte* tete_compte = NULL;

    // 1 Ajout des client
    printf("\t* * * Ajout des Clients * * *\n");
    tete_client = ajouterclient(tete_client, "cl001", "Prodige", "OKO", 781649057, "Dakar");
    tete_client = ajouterclient(tete_client, "cl002", "Maeva", "Fatima", 781649057, "Dakar");
    tete_client = ajouterclient(tete_client, "cl003", "Sobour", "YO", 781649057, "Dakar");

    //2 Affichage des clients
    struct client* p_client = tete_client;
    while (p_client != NULL) {
        printf("codecl: %s, Prenom: %s, Nom: %s, tel: %d, Ville: %s\n", p_client->codecl, p_client->prenom, p_client->nom, p_client->tel, p_client->ville);
        p_client = p_client->suivant;
    }

    //3 Ajout des comptes
    printf("\n\t* * * Ajout des Comptes * * *\n");
    struct date date1 = {22, 12, 2012};
    struct date date2 = {10, 5, 2020};
    struct date date3 = {1, 1, 2023};

    tete_compte = ajoutercompte(tete_compte, 1, date1, "woyofal", 25000, "cl001");
    tete_compte = ajoutercompte(tete_compte, 2, date2, "senelec", 15000, "cl002");
    tete_compte = ajoutercompte(tete_compte, 3, date3, "woyofal", 30000, "cl003");

    //4 Affichage des comptes
    struct compte* p_compte = tete_compte;
    while (p_compte != NULL) {
        printf("numero: %d, date ouverture: %02d/%02d/%d, agence: %s, solde: %.2f, codecl: %s\n", p_compte->numero, p_compte->dateouverture.jour, p_compte->dateouverture.mois, p_compte->dateouverture.annee, p_compte->agence, p_compte->solde, p_compte->codecl);
        p_compte = p_compte->suivant;
    }

    //5 Operation sur les comptes

        // Définition des variables pour les opérations
        struct date2 dateop1 = {1, 1, 2025};
        struct date2 dateop2 = {2, 6, 2012};
        struct date2 dateop3 = {3, 10, 2024};

        //Depôt
        //Ajout des infos dans la fonction deposer
        deposer(tete_compte, 1, 5000.0, "op001", dateop1); // Dépôt de 5000 dans le compte 1
   
        //Retrait
        //Ajout des infos dans la fonction retirer
        retirer(tete_compte, 2, 2000.0,"op002",dateop2); // Retrait de 2000 du compte 2

        //Pas d'ajout dans la fonction retirer car le solde est insuffisant
        retirer(tete_compte, 3, 35000.0,"op003",dateop3); // retrait de 35000 du compte 3 (échec, solde insuffisant)

        printf("\n");
    //6 Sauvegarde des données

        // Copier les clients dans le fichier clients.tx
        copieclient(tete_client, "clients.txt");

        // Copier les comptes dans le fichier comptes.txt
        copiecompte(tete_compte, "comptes.txt");
    
    return 0;
}