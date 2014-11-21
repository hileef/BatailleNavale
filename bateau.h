#ifndef BATEAU_H
#define BATEAU_H

#include "proprietes.cpp"
#include "coordonnees.h"

struct Bateau {
	int taille;
	int compteTouche;
	Coordonnee liste[TAILLES_MAX];
	Bateau* suivant;
	Bateau* precedent;
};
typedef struct Bateau Bateau;

struct BateauManager {
	Bateau* premier;
	Bateau* dernier;
	int compteurs[TAILLES_MAX];
};
typedef struct BateauManager BateauManager;

void allouerManager(BateauManager* m);
void detruireManager(BateauManager* b);

Bateau* trouverBateau(BateauManager* m, Coordonnee* x);
void enregistrerBateau(BateauManager* m, Coordonnee liste[], int taille);
bool enregistrerTir(BateauManager* m, Coordonnee* tir);

int totalBateauxAutorises();
bool bateauAutorise(BateauManager* m, int taille);

// Protypes : acces proprietes
int getTaille(Bateau* b);
void setTaille(Bateau* b, int x);
int getTouches(Bateau* b);
void setTouches(Bateau* b, int x);
void incTouches(Bateau* b);
Coordonnee* getCoordonnee(Bateau* b, int i);
void setCoordonnee(Bateau* b, int i, Coordonnee* x);
Bateau* getSuivant(Bateau* b);
Bateau* getPrecedent(Bateau* b);
void setSuivant(Bateau* b, Bateau* d);
void setPrecedent(Bateau* b, Bateau* d);
Bateau* getPremier(BateauManager* m);
Bateau* getDernier(BateauManager* m);
void setPremier(BateauManager* m, Bateau* b);
void setDernier(BateauManager* m, Bateau* b);
int getCompteur(BateauManager m, int i);
void incCompteur(BateauManager m, int i);
void setCompteur(BateauManager m, int i, int x);

#endif