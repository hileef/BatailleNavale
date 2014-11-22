#ifndef PARTIE
#define PARTIE

#include "plateau.h"

struct Partie {
	Plateau bateaux1;
	Plateau bateaux2;
	Plateau tirs1;
	Plateau tirs2;
	char joueur1[TAILLE_ENTREE];
	char joueur2[TAILLE_ENTREE];
};
typedef struct Partie Partie;

void jouerPartie(Partie* p);
void testsPartie();

#endif