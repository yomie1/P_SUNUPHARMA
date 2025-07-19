#ifndef PRODUITS_H
#define PRODUITS_H

typedef struct
{
    char code[6], designation[50], categorie[30];
    float prix;
    int quantite,annee, mois, jours;
} Produit;

void ajouterProduit();
void afficherProduits();
void modifierProduit();
void supprimerProduit();
int verExpire(Produit p);

#endif


