//Test client (Avec nitialisation des clients)
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
    struct client* p_compte = tete_client;
    while (p_compte != NULL) {
        fprintf(fichier, "codecl: %s, Prenom: %s, Nom: %s, tel: %d, Ville: %s\n", p_compte->codecl, p_compte->prenom, p_compte->nom, p_compte->tel, p_compte->ville);
        p_compte = p_compte->suivant;
    }
    fclose(fichier);
    printf("Les clients ont été copiés dans le fichier %s\n", nomFichier);
}

int main() {
    struct client* tete_client = NULL;

    tete_client = ajouterclient(tete_client, "cl001", "Prodige", "OKO", 781649057, "Dakar");
    tete_client = ajouterclient(tete_client, "cl002", "Maeva", "Fatima", 781649057, "Dakar");
    tete_client = ajouterclient(tete_client, "cl003", "Sobour", "YO", 781649057, "Dakar");
        
    // Affichage des clients
    struct client* p_compte = tete_client;
    while (p_compte != NULL) {
        printf("codecl: %s, Prenom: %s, Nom: %s, tel: %d, Ville: %s\n", p_compte->codecl, p_compte->prenom, p_compte->nom, p_compte->tel, p_compte->ville);
        p_compte = p_compte->suivant;
    }

    // Copier les clients dans le fichier
    copieclient(tete_client, "clients.txt");

    return 0;
}