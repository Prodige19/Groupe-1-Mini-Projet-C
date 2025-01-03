//Test Operation 1 (Avec initialisation des comptes et des opérations)
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

struct date2 {
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

// Fonction pour allouer un nouveau compte
struct compte* allouercompte(int numero, struct date dateouverture, const char* agence, float solde, const char* codecl) {
    // Allocation de mémoire
    struct compte* nouveau_compte = (struct compte*)malloc(sizeof(struct compte));

    if (nouveau_compte != NULL) {
        nouveau_compte->numero = numero; // allocation pour le numéro du compte
        nouveau_compte->dateouverture = dateouverture; // allocation pour la date d'ouverture du compte
        strcpy(nouveau_compte->agence, agence); // allocation pour l'agence du compte
        nouveau_compte->solde = solde; // allocation pour le solde du compte
        strcpy(nouveau_compte->codecl, codecl); // allocation pour le codecl du compte
        nouveau_compte->suivant = NULL;
    }
    return nouveau_compte;
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

// Fonction pour effectuer un dépôt
int deposer(struct compte* tete_compte, int numero, float montant) {
    struct compte* p_depot = tete_compte;
    while (p_depot != NULL) {
        if (p_depot->numero == numero) {
            p_depot->solde += montant;
            return 1; // Succès
        }
        p_depot = p_depot->suivant;
    }
    return 0; // Échec, compte non trouvé
}

// Fonction pour effectuer un retrait
int retirer(struct compte* tete_compte, int numero, float montant) {
    struct compte* p_retrait = tete_compte;
    while (p_retrait != NULL) {
        if (p_retrait->numero == numero) {
            if (p_retrait->solde >= montant) {
                p_retrait->solde -= montant;
                return 1; // Succès
            } else {
                return -1; // Échec, solde insuffisant
            }
        }
        p_retrait = p_retrait->suivant;
    }
    return 0; // Échec, compte non trouvé
}

int main() {
    struct compte* tete_compte = NULL;
    // Initialisation de plusieurs comptes directement dans le code
    struct date date1 = {22, 12, 2012};
    struct date date2 = {10, 5, 2020};
    struct date date3 = {1, 1, 2023};

    tete_compte = ajoutercompte(tete_compte, 1, date1, "woyofal", 25000.0, "cl001");
    tete_compte = ajoutercompte(tete_compte, 2, date2, "dakar", 15000.0, "cl002");
    tete_compte = ajoutercompte(tete_compte, 3, date3, "touba", 30000.0, "cl003");

    // Effectuer quelques opérations
    deposer(tete_compte, 1, 5000.0); // Déposer 5000 dans le compte 1
    retirer(tete_compte, 2, 2000.0); // Retirer 2000 du compte 2
    retirer(tete_compte, 3, 35000.0); // Essayer de retirer 35000 du compte 3 (échec, solde insuffisant)

    // Affichage des comptes
    struct compte* p_compte = tete_compte;
    while (p_compte != NULL) {
        printf("numero: %d, date ouverture: %02d/%02d/%d, agence: %s, solde: %.2f, codecl: %s\n", p_compte->numero, p_compte->dateouverture.jour, p_compte->dateouverture.mois, p_compte->dateouverture.annee, p_compte->agence, p_compte->solde, p_compte->codecl);
        p_compte = p_compte->suivant;
    }

    return 0;
}