// vente.h
#ifndef VENTE_H
#define VENTE_H

#define MAX_VENTES 100

typedef struct {
    char numero_vente[15]; // Format AAAAMMDDHHmmSS
    char login[6]; // Login du pharmacien
    char produit_code[6]; // Code du produit vendu
    int quantite; // Quantité vendue
    float prix_total; // Prix total de la vente
} Vente;

extern Vente ventes[];
extern int nbVentes;

void enregistrerVente(char *login);
void afficherVentes();

#endif // VENTE_H

