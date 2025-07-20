#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilisateurs.h"

Utilisateur u;

void verifierFichierUser(FILE *f) {
    if (f == NULL) {
        printf("Erreur fichier USERS.dat\n");
        exit(1);
    }
}

void creerUtilisateur() {
    FILE *f = fopen("USERS.dat", "ab");
    verifierFichierUser(f);

    printf("Login (5 lettres MAJ) : ");
    scanf("%s", u.login);


    if (strlen(u.login) != 5) {
        printf("Erreur : Le login doit faire exactement 5 lettres majuscules.\n");
        fclose(f);
        return;
    }

    strcpy(u.motDePasse, "pharma123"); // mot de passe par défaut
    printf("Nom : ");
    scanf("%s", u.nom);
    printf("Prenom : ");
    scanf("%s", u.prenom);
    printf("Telephone : ");
    scanf("%s", u.telephone);
    printf("Role (1 = Admin, 0 = Pharmacien) : ");
    scanf("%d", &u.Admin);
    u.bloque = 0;

    fwrite(&u, sizeof(Utilisateur), 1, f);
    fclose(f);
    printf("Utilisateur cree avec mot de passe : pharma123\n");
}

int loginUtilisateur(Utilisateur *userConnecte) {
    char login[6], mdp[20];
    FILE *f = fopen("USERS.dat", "rb");
    verifierFichierUser(f);

    printf("Login : ");
    scanf("%s", login);
    printf("Mot de passe : ");
    scanf("%s", mdp);

    while (fread(&u, sizeof(Utilisateur), 1, f)) {
        if (strcmp(u.login, login) == 0 && strcmp(u.motDePasse, mdp) == 0) {
            if (u.bloque) {
                printf("Ce compte est bloque.\n");
                fclose(f);
                return 0;
            }
            *userConnecte = u;
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    printf("Identifiants invalides.\n");
    return 0;
}

void changerMotDePasse(Utilisateur *user) {
    char nouveauMdp[20];
    FILE *f = fopen("USERS.dat", "rb");
    FILE *tmp = fopen("temp.dat", "wb");
    verifierFichierUser(f);
    verifierFichierUser(tmp);

    printf("Nouveau mot de passe : ");
    scanf("%s", nouveauMdp);
    strcpy(user->motDePasse, nouveauMdp);

    while (fread(&u, sizeof(Utilisateur), 1, f)) {
        if (strcmp(u.login, user->login) == 0)
            fwrite(user, sizeof(Utilisateur), 1, tmp);
        else
            fwrite(&u, sizeof(Utilisateur), 1, tmp);
    }

    fclose(f);
    fclose(tmp);
    remove("USERS.dat");
    rename("temp.dat", "USERS.dat");

    printf("Mot de passe modifie avec succes.\n");
}

void afficherUtilisateurs() {
    FILE *f = fopen("USERS.dat", "rb");
    verifierFichierUser(f);

    printf("Liste des utilisateurs :\n");
    printf("%-6s %-10s %-10s %-12s %-8s %-6s\n", "Login", "Nom", "Prenom", "Telephone", "Role", "Bloque");

    while (fread(&u, sizeof(Utilisateur), 1, f)) {
        printf("%-6s %-10s %-10s %-12s %-8s %-6s\n",
               u.login, u.nom, u.prenom, u.telephone,
               u.Admin ? "Admin" : "Pharmacien",
               u.bloque ? "Oui" : "Non");
    }

    fclose(f);
}

void bloquerUtilisateur() {
    char login[6];
    int bloquer;
    FILE *f = fopen("USERS.dat", "rb");
    FILE *tmp = fopen("temp.dat", "wb");
    verifierFichierUser(f);
    verifierFichierUser(tmp);

    printf("Login a bloquer/debloquer : ");
    scanf("%s", login);
    printf("0 = actif, 1 = bloquer : ");
    scanf("%d", &bloquer);

    while (fread(&u, sizeof(Utilisateur), 1, f)) {
        if (strcmp(u.login, login) == 0)
            u.bloque = bloquer;
        fwrite(&u, sizeof(Utilisateur), 1, tmp);
    }

    fclose(f);
    fclose(tmp);
    remove("USERS.dat");
    rename("temp.dat", "USERS.dat");
    printf("Statut mis a jour.\n");
}
