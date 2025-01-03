//Test compte 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure date
struct date {
    int jour;
    int mois;
    int annee;
};

// Définition de la structure compte
struct compte {
    int numero;
    struct date dateouverture;
    char agence[15];
    float solde;
    char codecl[15];
    struct compte* suivant;
};

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

// Fonction pour ajouter un compte au début de la liste
struct compte* ajoutercompte(struct compte* tete_compte, int numero, struct date dateouverture, const char* agence, float solde, const char* codecl) {
    
    // Allocation de la mémoire et copie des informations pour le nouveau compte
    struct compte* nouveau_compte = allouercompte(numero, dateouverture, agence, solde, codecl);
    if (nouveau_compte != NULL) {
        nouveau_compte->suivant = tete_compte;
        tete_compte = nouveau_compte;
    }
    return tete_compte;
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

int main() {
    struct compte* tete_compte = NULL;

    struct date date1 = {22, 12, 2012};
    struct date date2 = {10, 5, 2020};
    struct date date3 = {1, 1, 2023};

    tete_compte = ajoutercompte(tete_compte, 1, date1, "woyofal", 25000, "cl001");
    tete_compte = ajoutercompte(tete_compte, 2, date2, "dakar", 15000, "cl002");
    tete_compte = ajoutercompte(tete_compte, 3, date3, "touba", 30000, "cl003");

    // Affichage des comptes
    struct compte* p_compte = tete_compte;
    while (p_compte != NULL) {
        printf("numero: %d, date ouverture: %02d/%02d/%d, agence: %s, solde: %.2f, codecl: %s\n", p_compte->numero, p_compte->dateouverture.jour, p_compte->dateouverture.mois, p_compte->dateouverture.annee, p_compte->agence, p_compte->solde, p_compte->codecl);
        p_compte = p_compte->suivant;
    }

    // Copier les comptes dans le fichier
    copiecompte(tete_compte, "comptes.txt");

    return 0;
}