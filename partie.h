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

// Les prototypes privés
static void demanderBateauxAuJoueur(Partie* p, int joueur);
static void demanderTirAuJoueur(Partie* p, int joueur);
static void resultatsTirsJoueur(Partie* p, Coordonnee* tir, int joueur);

static bool tourJoueur(Partie* p, int joueur);
static int  jouerTours(Partie* p);

static void gagnerPartie(Partie* p, int gagnant);

static void preparerPartie(Partie* p);
static void fermerPartie(Partie* p);

static void preparerPlateaux(Partie* p);
static void fermerPlateaux(Partie* p);

static Plateau* getBateaux(Partie* p, int joueur);
static Plateau* getTirs(Partie* p, int joueur);
static char* 	getJoueur(Partie* p, int joueur);

static bool tousBateauxTouches(Partie* p, int joueur);
static bool placerTir(Partie* p, int joueur, Coordonnee* tir);

// Les tests
void testsPartie();

#endif