//Test compte 2 (Sans initialisation des comptes)
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
    int numero;
    struct date dateouverture;
    char agence[15];
    float solde;
    char codecl[15];

    // Variable pour le choix de l'utilisateur
    int choix;
    do {
        printf("Tapez 1 pour ajouter un compte 2 pour quitter: ");
        scanf("%d", &choix);

        if (choix == 1) {
            // Ajout des comptes au début de la liste
            printf("Saisir le numero du compte: ");
            scanf("%d", &numero);
            printf("Saisir la date d'ouverture du compte (jour mois annee): ");
            scanf("%d %d %d", &dateouverture.jour, &dateouverture.mois, &dateouverture.annee);
            printf("Saisir l'agence du compte: ");
            scanf("%s", agence);
            printf("Saisir le solde du compte: ");
            scanf("%f", &solde);
            printf("Saisir le codecl du compte: ");
            scanf("%s", codecl);

            tete_compte = ajoutercompte(tete_compte, numero, dateouverture, agence, solde, codecl);
        }

        // Affichage des comptes
        struct compte* p_compte = tete_compte;
        while (p_compte != NULL) {
            printf("numero: %d, date ouverture: %02d/%02d/%d, agence: %s, solde: %.2f, codecl: %s\n", p_compte->numero, p_compte->dateouverture.jour, p_compte->dateouverture.mois, p_compte->dateouverture.annee, p_compte->agence, p_compte->solde, p_compte->codecl);
            p_compte = p_compte->suivant;
        }


    } while (choix != 2);

    // Copier les comptes dans le fichier
    copiecompte(tete_compte, "comptes.txt");

    return 0;
}