#ifndef PLATEAU
#define PLATEAU

#include "bateau.h"
#include "coordonnees.h"

struct Plateau {
	BateauMGR manager;
	char** board;
	int taille;
};
typedef struct Plateau Plateau;

void 	allouerPlateau(Plateau* p);
void 	allouerPlateau(Plateau* p, int taille);
void 	detruirePlateau(Plateau* p);

void 	initPlateau(Plateau* p);
void 	initPlateau(Plateau* p, char x);

int 	getTaille(Plateau* p);
void 	setTaille(Plateau* p, int x);

char 	getCase(Plateau* p, Coordonnee* x);
char 	getCase(Plateau* p, int y, int x);
void 	setCase(Plateau* p, Coordonnee* x, char c);
void 	setCase(Plateau* p, int y, int x, char c);

BateauMGR* getManager(Plateau* p);

void 	afficherPlateau(Plateau* p);
void 	afficherBateauxDisponibles(Plateau* p);

bool 	placerTir(Plateau* bateaux, Plateau* tirs, Coordonnee* x);
bool 	placerBateau(Plateau* bateaux, Coordonnee liste[], int taille);
bool 	autoriserBateau(Plateau* p, int taille);

bool 	caseNonVide(Plateau* p, Coordonnee* x);
int 	radar(Plateau* p, Coordonnee* tir);
bool 	tousBateauxTouches(Plateau* bateaux, Plateau* tirs);

// Les prototypes privés
static 	int  radar_NON_C(Plateau* p, int y, int x, int rayon, char c);
static 	bool case_NON_C(Plateau* p, int y, int x, char c);
static 	bool caseNonVide(Plateau* p, int y, int x);
static 	void coulerBateau(Bateau* b, Plateau* tirs);

// Les tests
void 	testsPlateau();

#endif