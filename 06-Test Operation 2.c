//Test operation 2 (sans initialisation des comptes et des opérations)
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

// Fonction pour enregistrer l'opération dans le fichier operations.txt
void enregistrer_operation(const char* codeop, int numero, const char* type, float montant, struct date2 dateop) {
    FILE* fichier = fopen("operations.txt", "a");
    if (fichier != NULL) {
        fprintf(fichier, "codeop: %s, numero: %d, type: %s, montant: %.2f, date: %02d/%02d/%d\n",
                codeop, numero, type, montant, dateop.jour, dateop.mois, dateop.annee);
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

int main() {
    // Initialisation de la tête du client
    struct client* tete_client = NULL;
    char codecl[15];
    char prenom[15];
    char nom[15];
    int tel;
    char ville[15];

    // Initialisation de la tête du compte
    struct compte* tete_compte = NULL;
    int numero;
    struct date dateouverture;
    char agence[15];
    float solde;

    // Variable pour le choix de l'utilisateur
    int choix, choixoperation;
    float montant;
    char codeop[15];
    struct date2 dateop;

    do {
        printf("Tapez 1 pour ajouter un compte, 2 pour effectuer une operation: ");
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

            //copie des comptes en tete de liste
            tete_compte = ajoutercompte(tete_compte, numero, dateouverture, agence, solde, codecl);
        } else if (choix == 2) {
            do {
                printf("Saisir 1 pour effectuer un depot sur un compte et 2 pour effectuer un retrait sur un compte: ");
                scanf("%d", &choixoperation);

                if (choixoperation == 1) {

                    //Depot sur le compte
                    printf("Saisir le numero du compte: ");
                    scanf("%d", &numero);
                    printf("Saisir le codeop: ");
                    scanf("%s", codeop);
                    printf("Saisir le montant à déposer: ");
                    scanf("%f", &montant);
                    printf("Saisir la date de l'opération (jour mois annee): ");
                    scanf("%d %d %d", &dateop.jour, &dateop.mois, &dateop.annee);
                    int resultat = deposer(tete_compte, numero, montant, codeop, dateop);
                    if (resultat == 1) {
                        printf("Dépôt effectué avec succès.\n");
                    } else {
                        printf("Échec du dépôt. Compte non trouvé.\n");
                    }
                }

                else if (choixoperation == 2) {

                    //Retrait sur le compte
                    printf("Saisir le numero du compte: ");
                    scanf("%d", &numero);
                    printf("Saisir le codeop: ");
                    scanf("%s", codeop);
                    printf("Saisir le montant à retirer: ");
                    scanf("%f", &montant);
                    printf("Saisir la date de l'opération (jour mois annee): ");
                    scanf("%d %d %d", &dateop.jour, &dateop.mois, &dateop.annee);
                    int resultat = retirer(tete_compte, numero, montant, codeop, dateop);
                    if (resultat == 1) {
                        printf("Retrait effectué avec succès.\n");
                    } else if (resultat == -1) {
                        printf("Échec du retrait. Solde insuffisant.\n");
                    } else {
                        printf("Échec du retrait. Compte non trouvé.\n");
                    }
                }

                printf("Voulez-vous effectuer une autre operation ? 1: oui 2:non ");
                scanf("%d", &choixoperation);
            } while (choixoperation == 1);
        }
        else {
            printf("Choix invalide.\n");
        }
        printf("Tapez 1 pour continuer ou 2 pour vous arreter: \n");
        scanf("%d", &choix);

    } while (choix == 1);

    // Affichage des comptes
    struct compte* p_compte = tete_compte;
    while (p_compte != NULL) {
        printf("numero: %d, date ouverture: %02d/%02d/%d, agence: %s, solde: %.2f, codecl: %s\n", p_compte->numero, p_compte->dateouverture.jour, p_compte->dateouverture.mois, p_compte->dateouverture.annee, p_compte->agence, p_compte->solde, p_compte->codecl);
        p_compte = p_compte->suivant;
    }

    return 0;
}