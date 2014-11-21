#include "plateau.h"
#include "bateau.h"
#include "coordonnees.h"
#include "unittest.h"
#include "proprietes.cpp"

// Les prototypes privés
static int radar_NON_C(Plateau* p, int y, int x, int rayon, char c);
static bool case_NON_C(Plateau* p, int y, int x, char c);
static bool caseNonVide(Plateau* p, int y, int x);
static void coulerBateau(Bateau* b, Plateau* tirs);

void allouerPlateau(Plateau* p) {
	allouerPlateau(p, TAILLE);
}
void allouerPlateau(Plateau* p, int taille) {
	int i;

	p->board = (char**) malloc(sizeof(char*) * taille);
	for(i = 0; i < taille; i++)
		p->board[i] = (char*) malloc(sizeof(char) * taille);
	setTaille(p, taille);

	allouerManager(getManager(p));
}

void detruirePlateau(Plateau* p) {
	int i;

	for(i = 0; i < p->taille; i++)
		free(p->board[i]);
	free(p->board);
	setTaille(p, 0);

	detruireManager(getManager(p));
}


void initPlateau(Plateau* p) {
	initPlateau(p, VIDE);
}
void initPlateau(Plateau* p, char x) {
	int j, i;
	for(i = 0; i < p->taille; i++)
		for(j = 0; j < p->taille; j++)
			setCase(p, i, j, x);
}

int getTaille(Plateau* p) {
	return p->taille;
}
void setTaille(Plateau* p, int x) {
	p->taille = x;
}

char getCase(Plateau* p, Coordonnee* x) {
	return getCase(p, getY(x), getX(x));
}
char getCase(Plateau* p, int y, int x) {
	return p->board[y][x];
}
void setCase(Plateau* p, Coordonnee* x, char c) {
	setCase(p, getY(x), getX(x), c);
}
void setCase(Plateau* p, int y, int x, char c) {
	p->board[y][x] = c;
}

BateauManager* getManager(Plateau* p) {
	return &p->manager;
}

bool caseNonVide(Plateau* p, Coordonnee* x) {
	return case_NON_C(p, getY(x), getX(x), VIDE);
}
static bool caseNonVide(Plateau* p, int y, int x) {
	return case_NON_C(p, y, x, VIDE);
}
static bool case_NON_C(Plateau* p, int y, int x, char c) {
	return (getCase(p, y, x) != c);
}

bool autoriserBateau(Plateau* p, int taille) {
	return bateauAutorise(getManager(p), taille);
}

bool placerTir(Plateau* bateaux, Plateau* tirs, Coordonnee* x) {
	if(caseNonVide(tirs, x)) return false;
	if(caseNonVide(bateaux, x)) {
		setCase(tirs, x, TOUCHE);
		if(enregistrerTir(getManager(bateaux), x))
			coulerBateau(trouverBateau(getManager(bateaux), x), tirs);
	} else
		setCase(tirs, x, PLOUF);
	return true;
}

bool placerBateau(Plateau* bateaux, Coordonnee liste[], int taille) {
	int i;

	for(i = 0; i < taille; i++)
		if(caseNonVide(bateaux, &(liste[i]))) return false;

	for(i = 0; i < taille; i++)
		setCase(bateaux, &(liste[i]), taille + '0');

	enregistrerBateau(getManager(bateaux), liste, taille);

	return true;
}

bool tousBateauxTouches(Plateau* bateaux, Plateau* tirs) {
	int i, j, t = getTaille(bateaux);
	for(i = 0; i < t; i++)
		for(j = 0; j < t; j++) 
			if(caseNonVide(bateaux, i, j) && !caseNonVide(tirs, i, j))
				return false;
	return true;
}

static void coulerBateau(Bateau* b, Plateau* tirs) {
	int i, n = getTaille(b);
	for(i = 0; i < n; i++)
		setCase(tirs, getCoordonnee(b, i), COULE);
}


int radar(Plateau* p, Coordonnee* tir) {
	return radar_NON_C(p, getY(tir), getX(tir), RAYON_RADAR, VIDE);
}
static int radar_NON_C(Plateau* p, int y, int x, int rayon, char c) {
	int i, j, k, d, dx, dy, proche = 0;
	for(i = y - rayon; i < y + rayon; i++)
		for(j = x - rayon; j < x + rayon ; j++)
			if(i < getTaille(p) && i >= 0 && j < getTaille(p) && j >= 0)
				if(case_NON_C(p, i, j, c) && (!(i == y && j == x))) {
					dy = y - i;
					dx = x - j;
					dy = (dy < 0) ? -dy : dy;
					dx = (dx < 0) ? -dx : dx;
					d = (dy > dx) ? dy : dx;
					for(k = rayon; k > 0 ; k--)
						if(d == k && (proche == 0 || (proche != 0 && (k < proche))))
							proche = k;
				}
	return proche;
}






void testsPlateau() {
	printf("\n###############################");
	printf("\n### *** FICHIER PLATEAU *** ###\n");

	printf("\n # FONCTION initPlateau()\n");
	Plateau p;
	allouerPlateau(&p);
	initPlateau(&p);
	assertEquals(getCase(&p, 0, 0), VIDE, "Test plateau[0][0] = VIDE");
	assertEquals(getCase(&p, 9, 9), VIDE, "Test plateau[9][9] = VIDE");

	printf("\n # FONCTION setCase()\n");
	setCase(&p, 9, 9, BATEAU);
	assertEquals(getCase(&p, 9, 9), BATEAU, "Test plateau[9][9] = BATEAU");


	detruirePlateau(&p);
}