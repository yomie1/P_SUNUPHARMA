#include "vente.h"
#include "produit.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

Vente ventes[MAX_VENTES];
int nbVentes = 0;

void enregistrerVente(char *login) {
    char code[6];
    printf("Entrez le code du produit à vendre : ");
    scanf("%s", code);

    Produit *produit = rechercherProduit(code);
    if (produit != NULL) {
        if (produit->quantite > 0) {
            produit->quantite--;

            // Génération du numéro de vente
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            char numero_vente[15];
            sprintf(numero_vente, "%04d%02d%02d%02d%02d%02d",
                    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                    tm.tm_hour, tm.tm_min, tm.tm_sec);

            // Calcul du prix total
            float prix_total = produit->prix;

            // Création du fichier de facture
            char nom_facture[50];
            sprintf(nom_facture, "BILLS/RECU_%s_%s_%d.txt", numero_vente, login, produit->categorie_id); // Utilisation de l'ID de la catégorie

            // Création du dossier /BILLS/ si nécessaire
            struct stat st = {0};
            if (stat("BILLS", &st) == -1) {
                mkdir("BILLS", 0700);
            }

            // Écriture dans le fichier de facture
            FILE *f = fopen(nom_facture, "w");
            if (f != NULL) {
                fprintf(f, "Facture de Vente\n");
                fprintf(f, "Numéro de vente : %s\n", numero_vente);
                fprintf(f, "Pharmacien : %s\n", login);
                fprintf(f, "Produit : %s\n", produit->designation);
                fprintf(f, "Quantité : %d\n", 1); // On vend une unité
                fprintf(f, "Prix total : %.2f\n", prix_total);
                fclose(f);
                printf("Vente enregistrée avec succès. Facture créée : %s\n", nom_facture);
            } else {
                printf("Erreur lors de la création de la facture.\n");
            }

            // Enregistrement de la vente
            strcpy(ventes[nbVentes].numero_vente, numero_vente);
            strcpy(ventes[nbVentes].login, login);
            strcpy(ventes[nbVentes].produit_code, produit->code);
            ventes[nbVentes].quantite = 1; // On vend une unité
            ventes[nbVentes].prix_total = prix_total;
            nbVentes++;
        } else {
            printf("Stock insuffisant pour le produit %s.\n", produit->designation);
        }
    } else {
        printf("Produit non trouvé.\n");
    }
}

void afficherVentes() {
    printf("Liste des ventes :\n");
    for (int i = 0; i < nbVentes; i++) {
        printf("Numéro de vente: %s, Pharmacien: %s, Produit: %s, Quantité: %d, Prix total: %.2f\n",
               ventes[i].numero_vente, ventes[i].login, ventes[i].produit_code,
               ventes[i].quantite, ventes[i].prix_total);
    }
}
