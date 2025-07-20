#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilisateurs.h"

int main() {
    Utilisateur user;
    int choix;

    printf("=== BIENVENUE DANS SUNUPHARMA ===\n");


    FILE *f = fopen("USERS.dat", "rb");
    if (f == NULL) {
        f = fopen("USERS.dat", "wb");
        if (f != NULL) {

            Utilisateur users[] = {
                {"ADMIN", "pharma123", "Admin", "System", "0000000000", 0, 1},
                {"PHARM", "pharma123", "Pharm", "Test", "0000000001", 0, 0}
            };


            fwrite(users, sizeof(Utilisateur), 2, f);
            fclose(f);
            printf("Utilisateurs cree s : ADMIN/pharma123 et PHARM/pharma123\n");
        }
    } else {
        fclose(f);
    }


    if (!loginUtilisateur(&user)) {
        return 0; // échec
    }

    printf("\n[✓] Connecte avec succes en tant que %s\n\n", user.Admin ? "ADMIN" : "PHARMACIEN");


    if (strcmp(user.motDePasse, "pharma123") == 0) {
        printf("Veuillez changer le mot de passe par defaut !\n");
        changerMotDePasse(&user);
    }

    do {
        printf("\n============== MENU ==============\n", user.Admin ? "ADMIN" : "PHARMACIEN");
        printf("1. Ajouter produit\n");
        printf("2. Afficher produits\n");
        printf("3. Modifier produit\n");
        printf("4. Supprimer produit\n");

        if (user.Admin) {
            printf("5. Ajouter categorie\n");
            printf("6. Afficher categories\n");
            printf("7. Supprimer categorie\n");
            printf("8. Creer utilisateur\n");
            printf("9. Afficher utilisateurs\n");
            printf("10. Bloquer/debloquer utilisateur\n");
            printf("11. Generer rapport journalier\n");
        } else {
            printf("5. Effectuer une vente\n");
            printf("6. Generer rapport journalier\n");
        }

        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Fonction ajouter produit - A implementer\n");
                break;
            case 2:
                printf("Fonction afficher produits - A implementer\n");
                break;
            case 3:
                printf("Fonction modifier produit - A implementer\n");
                break;
            case 4:
                printf("Fonction supprimer produit - A implementer\n");
                break;

            case 5:
                if (user.Admin) {
                    printf("Fonction ajouter categorie - A implementer\n");
                } else {
                    printf("Fonction effectuer vente - A implementer\n");
                }
                break;
            case 6:
                if (user.Admin) {
                    printf("Fonction afficher categories - A implementer\n");
                } else {
                    printf("Fonction generer rapport journalier - A implementer\n");
                }
                break;
            case 7:
                if (user.Admin) {
                    printf("Fonction supprimer categorie - A implementer\n");
                }
                break;
            case 8:
                if (user.Admin) {
                    creerUtilisateur();
                }
                break;
            case 9:
                if (user.Admin) {
                    afficherUtilisateurs();
                }
                break;
            case 10:
                if (user.Admin) {
                    bloquerUtilisateur();
                }
                break;
            case 11:
                if (user.Admin) {
                    printf("Fonction generer rapport journalier - A implementer\n");
                }
                break;

            case 0:
                printf("Déconnexion...\n");
                break;
            default:
                printf("Choix invalide !\n");
                break;
        }

        printf("\nAppuyez sur Entree pour continuer...");
        getchar(); getchar();

    } while (choix != 0);

    return 0;
}
