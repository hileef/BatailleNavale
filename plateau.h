#ifndef PLATEAU
#define PLATEAU

#include "bateau.h"
#include "coordonnees.h"

struct Plateau {
	BateauManager manager;
	char** board;
	int taille;
};
typedef struct Plateau Plateau;

void allouerPlateau(Plateau* p);
void allouerPlateau(Plateau* p, int taille);
void detruirePlateau(Plateau* p);

void initPlateau(Plateau* p);
void initPlateau(Plateau* p, char x);

int getTaille(Plateau* p);
void setTaille(Plateau* p, int x);

BateauManager* getManager(Plateau* p);

char getCase(Plateau* p, Coordonnee* x);
char getCase(Plateau* p, int y, int x);
void setCase(Plateau* p, Coordonnee* x, char c);
void setCase(Plateau* p, int y, int x, char c);

bool caseNonVide(Plateau* p, Coordonnee* x);

bool autoriserBateau(Plateau* p, int taille);

bool placerTir(Plateau* bateaux, Plateau* tirs, Coordonnee* x);
bool placerBateau(Plateau* bateaux, Coordonnee liste[], int taille);
bool tousBateauxTouches(Plateau* bateaux, Plateau* tirs);
int radar(Plateau* p, Coordonnee* tir);



void testsPlateau();

#endif

/*
void coulerBateauSiPossible(Plateau* bateaux, Plateau* tirs) {
	int i, j, taille = bateaux->taille;
	
	// Horizontaux
	for(i = 0; i < taille; i++) {
		for(j = 0; j < taille; j++) {
			if(caseNonVide(bateaux, i, j) && caseNonVide(tirs, i, j)) {
				if(getCase(tirs, i, k) != COULE)
					couler_STEP(bateaux, tirs, i, j);
			}
		}
	}

}
bool couler_verif_h(Plateau* bateaux, Plateau* tirs, int i, int j){
	int k, l, x;
	x = getCase(bateaux, i, j);
	for(k = 0; k < x - '0'; k++) {
		if(caseNonVide(bateaux, i, j + k) && caseNonVide(tirs, i, j + k))
			if(getCase(bateaux, i, j + k) == x) {
				if(getCase(tirs, i, j + k) == COULE) return false;
			} else return false;
		} else return false;
	}
	bool haut, bas, gauche, droite;
	gauche = (j == 0) ? true: getCase(bateaux, i, j - 1) != x ;
	droite = (j >= taille - k) ? true: getCase(bateaux, i, j + k) != x ;
	if(i == 0) haut = true;
	else {
		for(l = 0; l < k; l++) {
			if(getCase(bateaux, i - 1, j + l) == x) haut = false;
		}
		haut = true;
	}
	if(i == bateaux->taille - 1) bas = true;
	else {
		for(l = 0; l < k; l++) {
			if(getCase(bateaux, i + 1, j + l) == x) bas = false;
		}
		bas = true;
	}
	if(haut && gauche && droite) ; // C'EST BON :D
	else if(haut && gauche && bas) ; // C'EST BON :D
	else return false;
}
void couler_appli_h(Plateau* bateaux, Plateau* tirs, int i, int j) {
	int k, x;
	x = getCase(bateaux, i, j);
	for(k = 0; k < x - '0'; k++)
		setCase(tirs, i, j + k, COULE);
}

*/