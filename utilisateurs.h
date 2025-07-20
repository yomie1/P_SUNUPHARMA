#ifndef UTILISATEURS_H
#define UTILISATEURS_H

typedef struct {
    char login[6];
    char motDePasse[20];
    char nom[30];
    char prenom[30];
    char telephone[15];
    int bloque;
    int Admin;
} Utilisateur;

void initialiserFichierUsers();
void creerUtilisateur();
int loginUtilisateur(Utilisateur *userConnecte);
void afficherUtilisateurs();
void bloquerUtilisateur();
void changerMotDePasse(Utilisateur *user);

#endif
