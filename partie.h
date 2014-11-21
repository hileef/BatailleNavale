#ifndef PARTIE
#define PARTIE

#include "plateau.h"

typedef struct Partie Partie;
struct Partie {
	Plateau bateaux1;
	Plateau bateaux2;
	Plateau tirs1;
	Plateau tirs2;
	char joueur1[TAILLE_ENTREE];
	char joueur2[TAILLE_ENTREE];
};

void jouerPartie(Partie* p);

#endif