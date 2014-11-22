#ifndef BATEAU
#define BATEAU

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

int 	getTaille(Bateau* b);
void 	setTaille(Bateau* b, int x);

int 	getTouches(Bateau* b);
void 	setTouches(Bateau* b, int x);
void 	incTouches(Bateau* b);

Coordonnee* getCoordonnee(Bateau* b, int i);
void 	setCoordonnee(Bateau* b, int i, Coordonnee* x);

Bateau* getSuivant(Bateau* b);
void 	setSuivant(Bateau* b, Bateau* d);

Bateau* getPrecedent(Bateau* b);
void 	setPrecedent(Bateau* b, Bateau* d);

struct BateauMGR {
	Bateau* premier;
	Bateau* dernier;
	int compteurs[TAILLES_MAX];
};
typedef struct BateauMGR BateauMGR;

Bateau* getPremier(BateauMGR* m);
void 	setPremier(BateauMGR* m, Bateau* b);

Bateau* getDernier(BateauMGR* m);
void 	setDernier(BateauMGR* m, Bateau* b);

int 	getCompteur(BateauMGR m, int i);
void 	setCompteur(BateauMGR m, int i, int x);
void 	incCompteur(BateauMGR m, int i);

void 	allouerManager(BateauMGR* m);
void 	detruireManager(BateauMGR* b);

void 	enregistrerBateau(BateauMGR* m, Coordonnee liste[], int taille);
Bateau* trouverBateau(BateauMGR* m, Coordonnee* x);
bool 	bateauAutorise(BateauMGR* m, int taille);
int 	bateauxRestantsAutorises(BateauMGR* m, int taille);
void 	afficherBateauxRestantsAutorises(BateauMGR* m);
int 	totalBateauxAutorises();

bool 	enregistrerTir(BateauMGR* m, Coordonnee* tir);



void 	testsBateaux();

#endif