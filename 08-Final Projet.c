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
    //Allocation de mémoire
    struct client* nouveau_client = (struct client*)malloc(sizeof(struct client));
    if (nouveau_client != NULL) {
        strcpy(nouveau_client->codecl, codecl); //allocation pour le code du client
        strcpy(nouveau_client->prenom, prenom); //allocation pour le prenom du client
        strcpy(nouveau_client->nom, nom); //allocation pour le nom du client
        nouveau_client->tel = tel; //allocation pour le tel du client
        strcpy(nouveau_client->ville, ville); //allocation pour laa ville du client
        nouveau_client->suivant = NULL;
    }
    return nouveau_client;
}

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
    struct client* p = tete_client;
    while (p != NULL) {
        fprintf(fichier, "codecl: %s, Prenom: %s, Nom: %s, tel: %d, Ville: %s\n", p->codecl, p->prenom, p->nom, p->tel, p->ville);
        p = p->suivant;
    }
    fclose(fichier);
    printf("Les clients ont été copiés dans le fichier %s\n", nomFichier);
}

// Fonction pour copier les comptes dans le fichier comptes.txt
void copiecompte(struct compte* tete_compte, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "a+");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    struct compte* p = tete_compte;
    while (p != NULL) {
        fprintf(fichier, "numero: %d, date ouverture: %02d/%02d/%d, agence: %s, solde: %.2f, codecl: %s\n", p->numero, p->dateouverture.jour, p->dateouverture.mois, p->dateouverture.annee, p->agence, p->solde, p->codecl);
        p = p->suivant;
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

    //Début du programme
    do{
        printf("\n\t * * * Bienvenu à vous * * *\n");
        printf("Veuillez tapez:\n");
        printf("1 pour ajouter un client\n");
        printf("2 pour ajouter un compte\n");
        printf("3 pour effectuer une operation\n");
        printf("4 pour afficher les clients\n");
        printf("5 pour afficher les comptes\n");
        printf("6 pour sauvegarder les modifications\n");
        printf("7 pour quitter\n");
        printf("Que choisissez-vous ? ");
        scanf("%d",&choix);

        // 1 Ajout d'un client
        if (choix == 1){

            printf("\n\t* * * * Ajout d'un client * * * *\n");
            printf("Saisir le code: ");
            scanf("%s",codecl);
            printf("Saisir le prenom: ");
            scanf("%s",prenom);
            printf("Saisir le nom: ");
            scanf("%s",nom);
            printf("Saisir le numero: ");
            scanf("%d",&tel);
            printf("Saisir la ville: ");
            scanf("%s",ville);

            //copie des clients en tete de liste
            tete_client = ajouterclient(tete_client, codecl, prenom, nom, tel, ville);
        }

        //2 Ajout d'un compte
        else if (choix == 2){

            // Ajout des comptes au début de la liste
            printf("\n\t* * * * Ajout d'un compte * * * *\n");
            printf("Saisir le numero du compte: ");
            scanf("%d", &numero);
            printf("Saisir la date d'ouverture du compte (jour mois annee): ");
            scanf("%d %d %d", &dateouverture.jour, &dateouverture.mois, &dateouverture.annee);
            printf("Saisir l'agence: ");
            scanf("%s", agence);
            printf("Saisir le solde: ");
            scanf("%f", &solde);
            printf("Saisir le codecl: ");
            scanf("%s", codecl);

            //copie des comptes en tete de liste
            tete_compte = ajoutercompte(tete_compte, numero, dateouverture, agence, solde, codecl);
        }

        //3 Operation sur un compte
        else if (choix == 3){

            printf("\n\t* * * * Operation sur un compte * * * *\n");
            printf("Tapez 1 pour effectuer un depot\n");
            printf("Tapez 2 pour effectuer un retrait\n");
            printf("choisissez un nombre: ");
            scanf("%d", &choixoperation);

            //Depot sur le compte
            if (choixoperation == 1) {

                printf("\n\t* * * dépôt sur un compte * * *\n");
                printf("Saisir le numero du compte: ");
                scanf("%d", &numero);
                printf("Saisir le code de l'opération: ");
                scanf("%s", codeop);
                printf("Saisir le montant à déposer: ");
                scanf("%f", &montant);
                printf("Saisir la date de l'opération (jour mois annee): ");
                scanf("%d %d %d", &dateop.jour, &dateop.mois, &dateop.annee);
                
                //Ajout des infos dans la fonction deposer
                int resultat = deposer(tete_compte, numero, montant, codeop, dateop);

                if (resultat == 1) {
                    printf("Dépôt effectué avec succès.\n");
                }
                else {
                    printf("Échec du dépôt. Compte non trouvé.\n");
                }
            }

            //Retrait sur le compte
            else if (choixoperation == 2) {

                printf("\n\t* * * retrait sur un compte * * *\n");
                printf("Saisir le numero du compte: ");
                scanf("%d", &numero);
                printf("Saisir le code de l'opération: ");
                scanf("%s", codeop);
                printf("Saisir le montant à retirer: ");
                scanf("%f", &montant);
                printf("Saisir la date de l'opération (jour mois annee): ");
                scanf("%d %d %d", &dateop.jour, &dateop.mois, &dateop.annee);

                //Ajout des infos dans la fonction retirer
                int resultat = retirer(tete_compte, numero, montant, codeop, dateop);

                if (resultat == 1) {
                    printf("Retrait effectué avec succès.\n");
                }
                else if (resultat == -1) {
                    printf("Échec du retrait. Solde insuffisant.\n");
                }
                else {
                    printf("Échec du retrait. Compte non trouvé.\n");
                }
            }
        }

        //4 Affichage de la liste des clients
        else if(choix == 4){
            printf("\n\t* * * Liste des clients saisis * * *\n");
            struct client* p_client = tete_client;
            while (p_client != NULL) {
                printf("codecl: %s, Prenom: %s, Nom: %s, tel: %d, Ville: %s\n", p_client->codecl, p_client->prenom, p_client->nom, p_client->tel, p_client->ville); p_client = p_client->suivant;
            }   
        }

        //5 Affichage de la liste des comptes
        else if (choix == 5){
            printf("\n\t* * * Liste les comptes saisis * * *\n");
            struct compte* p_compte = tete_compte;
            while (p_compte != NULL) {
            printf("numero: %d, date ouverture: %02d/%02d/%d, agence: %s, solde: %.2f, codecl: %s\n", p_compte->numero, p_compte->dateouverture.jour, p_compte->dateouverture.mois, p_compte->dateouverture.annee, p_compte->agence, p_compte->solde, p_compte->codecl);
            p_compte = p_compte->suivant;
            }
        }

        //6 Sauvegarde des données
        else if (choix == 6){

            // Copier les clients dans le fichier clients.txt
            copieclient(tete_client, "clients.txt");

            // Copier les comptes dans le fichier comptes.txt
            copiecompte(tete_compte, "comptes.txt");
        }

    } while(choix != 7);


    printf("Bien la Bonne Journée à vous !");
    
    return 0;
}