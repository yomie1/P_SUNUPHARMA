#include <stdio.h>
#include "Produit.h"

int main() {
    int choix;

    do {
        printf("\n====== MENU PRODUIT ======\n");
        printf("1. Ajouter produit\n");
        printf("2. Afficher produits\n");
        printf("3. Modifier produit\n");
        printf("4. Supprimer produit\n");
        printf("5. Verifier peremption d’un produit\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterProduit(); break;
            case 2: afficherProduits(); break;
            case 3: modifierProduit(); break;
            case 4: supprimerProduit(); break;
            case 5: verifUnProduit(); break;
            case 0: printf("Au revoir.\n"); break;
            default: printf("Choix invalide.\n"); break;
        }
    } while (choix != 0);

    return 0;
}
