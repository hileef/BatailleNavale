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

struct ListeBateau {
	Bateau* premier;
	Bateau* dernier;
	int compteurs[TAILLES_MAX];
};
typedef struct ListeBateau ListeBateau;

Bateau* getPremier(ListeBateau* m);
void 	setPremier(ListeBateau* m, Bateau* b);

Bateau* getDernier(ListeBateau* m);
void 	setDernier(ListeBateau* m, Bateau* b);

int 	getCompteur(ListeBateau m, int i);
void 	setCompteur(ListeBateau m, int i, int x);
void 	incCompteur(ListeBateau m, int i);

void 	allouerListe(ListeBateau* m);
void 	detruireListe(ListeBateau* b);

void 	enregistrerBateau(ListeBateau* m, Coordonnee liste[], int taille);
Bateau* trouverBateau(ListeBateau* m, Coordonnee* x);
bool 	bateauAutorise(ListeBateau* m, int taille);
int 	bateauxRestantsAutorises(ListeBateau* m, int taille);
void 	afficherBateauxRestantsAutorises(ListeBateau* m);
int 	totalBateauxAutorises();

bool 	enregistrerTir(ListeBateau* m, Coordonnee* tir);

// Les prototypes privés
static void 	detruireBateau(Bateau* b);
static Bateau* 	creerBateau(Coordonnee liste[], int taille);
static bool 	bateauContient(Bateau* b, Coordonnee* x);
static bool 	toucherBateau(Bateau* b);
static void 	ajouterBateau(ListeBateau* m, Bateau* b);

// Les tests
void 	testsBateaux();

#endif
