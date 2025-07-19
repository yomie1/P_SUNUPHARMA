#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Produit.h"

Produit p;

void verifier(FILE *f) {
    if (f == NULL) {
        puts("Le fichier ne peut pas etre ouvert !");
        exit(1);
    }
}

void ajouterProduit() {
    FILE *f = fopen("Produits.dat", "ab");
    verifier(f);

    printf("Code (5 caracteres) : ");
    scanf("%s", p.code);
    printf("Designation : ");
    scanf("%s", p.designation);
    printf("Categorie : ");
    scanf("%s", p.categorie);
    printf("Prix : ");
    scanf("%f", &p.prix);
    printf("Quantite : ");
    scanf("%d", &p.quantite);
    printf("Date de peremption :\n");
    printf("  Annee : ");
    scanf("%d", &p.annee);
    printf("  Mois  : ");
    scanf("%d", &p.mois);
    printf("  Jour  : ");
    scanf("%d", &p.jours);

    fwrite(&p, sizeof(Produit), 1, f);
    fclose(f);
    printf("Produit ajoute avec succes.\n");
}

void afficherProduits() {
    FILE *f = fopen("Produits.dat", "rb");
    verifier(f);

    printf("\nListe des produits :\n");
    printf("%-10s %-15s %-15s %-10s %-10s %-15s\n",
           "Code", "Designation", "Categorie", "Prix", "Quantite", "Date peremption");

    while (fread(&p, sizeof(Produit), 1, f)) {
        printf("%-10s %-15s %-15s %-10.2f %-10d %04d-%02d-%02d\n",
               p.code, p.designation, p.categorie, p.prix,
               p.quantite, p.annee, p.mois, p.jours);
    }

    fclose(f);
}

void modifierProduit() {
    char code[6];
    int ver = 0;

    printf("Donner le code du produit : ");
    scanf("%s", code);

    FILE *f = fopen("Produits.dat", "rb");
    FILE *tp = fopen("tmp.dat", "wb");
    verifier(f);
    verifier(tp);

    while (fread(&p, sizeof(Produit), 1, f)) {
        if (strcmp(code, p.code) == 0) {
            ver = 1;
            printf("Modification du produit [%s]\n", p.code);
            printf("Nouvelle designation : ");
            scanf("%s", p.designation);
            printf("Nouvelle categorie : ");
            scanf("%s", p.categorie);
            printf("Nouveau prix : ");
            scanf("%f", &p.prix);
            printf("Nouvelle quantite : ");
            scanf("%d", &p.quantite);
            printf("Nouvelle date de peremption :\n");
            printf("  Annee : ");
            scanf("%d", &p.annee);
            printf("  Mois  : ");
            scanf("%d", &p.mois);
            printf("  Jour  : ");
            scanf("%d", &p.jours);
        }
        fwrite(&p, sizeof(Produit), 1, tp);
    }

    fclose(f);
    fclose(tp);
    remove("Produits.dat");
    rename("tmp.dat", "Produits.dat");

    (ver) ? printf("Produit modifie avec succes.\n") : printf("Produit non trouve.\n");
}

void supprimerProduit() {
    char code[6];
    int t = 0;

    printf("Donner le code du produit : ");
    scanf("%s", code);

    FILE *f = fopen("Produits.dat", "rb");
    FILE *tp = fopen("tmp.dat", "wb");
    verifier(f);
    verifier(tp);

    while (fread(&p, sizeof(Produit), 1, f)) {
        if (strcmp(code, p.code) == 0) {
            t = 1;
            continue;
        }
        fwrite(&p, sizeof(Produit), 1, tp);
    }

    fclose(f);
    fclose(tp);
    remove("Produits.dat");
    rename("tmp.dat", "Produits.dat");

    (t) ? printf("Produit supprime avec succes.\n") : printf("Produit non trouve.\n");
}

int verExpire(Produit p){
    int a, m, j;
    printf("Entre le date de aujourdhui");
    scanf("%d %d %d", &a, &m, &j);
    if (p.annee<a) return 1;
    if (p.annee==a && p.mois<m) return 1;
    if (p.annee == a && p.mois == m && p.jours < j) return 1;

    printf("Le produit est valid");
    return 0;

}

