//Test client 1 (Sans initialisation des clients)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure Client
struct client {
    char codecl[15];
    char prenom[15];
    char nom[15];
    int tel;
    char ville[15];
    struct client* suivant;
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

int main() {
    struct client* tete_client = NULL;
    char codecl[15];
    char prenom[15];
    char nom[15];
    int tel;
    char ville[15];

    //Variable pour le choix de l'utilisateur
    int choix;
    do{
        printf("Tapez 1 pour ajouter un client et 2 pour quitter: ");
        scanf("%d",&choix);

        if (choix == 1){
            // Ajout des clients au début de la liste
            printf("Saisir le code du client: ");
            scanf("%s",codecl);
            printf("Saisir le prenom du client: ");
            scanf("%s",prenom);
            printf("Saisir le nom du client: ");
            scanf("%s",nom);
            printf("Saisir le numero du client: ");
            scanf("%d",&tel);
            printf("Saisir la ville du client: ");
            scanf("%s",ville);

            tete_client = ajouterclient(tete_client, codecl, prenom, nom, tel, ville);
        }

        // Affichage des clients
        struct client* p_client = tete_client;
        while (p_client != NULL) {
            printf("codecl: %s, Prenom: %s, Nom: %s, tel: %d, Ville: %s\n", p_client->codecl, p_client->prenom, p_client->nom, p_client->tel, p_client->ville);
            p_client = p_client->suivant;
        }
        printf("\n");
    }while(choix != 2);

    // Copier les clients dans le fichier
    copieclient(tete_client, "clients.txt");

    return 0;
}