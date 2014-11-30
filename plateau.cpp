#include <stdlib.h>
#include "plateau.h"

#include "bateau.h"
#include "coordonnees.h"
#include "unittest.h"
#include "proprietes.cpp"
#include "cli.h"

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
	int i, j;
	for(i = 0; i < p->taille; ++i)
		for (j = 0; j < p->taille; ++j)
			setCase(p, i, j, x);
}

int getTaille(Plateau* p) {
	return p->taille;
}
void setTaille(Plateau* p, int x) {
	p->taille = x;
}

char getCase(Plateau* p, Coordonnee* coor) {
	int y, x;
	y = getY(coor);
	x = getX(coor);
	return getCase(p, y, x);
}
char getCase(Plateau* p, int y, int x) {
	return p->board[y][x];
}
void setCase(Plateau* p, Coordonnee* coor, char c) {
	int y, x;
	y = getY(coor);
	x = getX(coor);
	setCase(p, y, x, c);
}
void setCase(Plateau* p, int y, int x, char c) {
	p->board[y][x] = c;
}

BateauMGR* getManager(Plateau* p) {
	return &p->manager;
}

bool caseNonVide(Plateau* p, Coordonnee* coor) {
	int y, x, c;
	y = getY(coor);
	x = getX(coor);
	c = VIDE;
	return case_NON_C(p, y, x, c);
}
static bool caseNonVide(Plateau* p, int y, int x) {
	return case_NON_C(p, y, x, VIDE);
}
static bool case_NON_C(Plateau* p, int y, int x, char c) {
	if (getCase(p, y, x) != c)
		return true;
	else return false;
}

bool autoriserBateau(Plateau* p, int taille) {
	return bateauAutorise(getManager(p), taille);	
}

bool placerTir(Plateau* bateaux, Plateau* tirs, Coordonnee* coor) {
	if (caseNonVide(tirs, coor))
		return false;

	if (caseNonVide(bateaux, coor)) {
		setCase(tirs, coor, TOUCHE);
		if(enregistrerTir(getManager(bateaux), coor))
			coulerBateau(trouverBateau(getManager(bateaux), coor), tirs);
	} else
		setCase(tirs, coor, PLOUF);	
	
	return true; 
}

bool placerBateau(Plateau* bateaux, Coordonnee liste[], int taille) {
	int i;

	for (i = 0; i < taille; ++i)
		if (caseNonVide(bateaux, &liste[i]))
			return false;

	for (i = 0; i < taille; ++i)
		setCase(bateaux, &liste[i], taille + '0');
		
	enregistrerBateau(getManager(bateaux), liste, taille);
	
	return true;
}

bool tousBateauxTouches(Plateau* bateaux, Plateau* tirs) {
	int i, j, t;
	t = getTaille(bateaux);
	for (i = 0; i < t; ++i)
		for (j = 0; j < t; ++j)
			if (caseNonVide(bateaux, i, j) && !caseNonVide(tirs, i, j))
				return false;
	return true;
}

static void coulerBateau(Bateau* b, Plateau* tirs) {
	int i, c;
	c = getTaille(b);
	for (i = 0; i < c; ++i)
		setCase(tirs, getCoordonnee(b, i), COULE);
}


int radar(Plateau* p, Coordonnee* tir) {
	return radar_NON_C(p, getY(tir), getX(tir), RAYON_RADAR, VIDE);
}
static int radar_NON_C(Plateau* p, int y, int x, int rayon, char c) {
	int i, j, k, d, dx, dy, proche = 0;
	for(i = y - rayon; i <= y + rayon; i++)
		for(j = x - rayon; j <= x + rayon ; j++)
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

void afficherPlateau(Plateau* p) {
	int i, j, taille;
	taille = p->taille;
	char t[TAILLE_ENTREE];
	
	afficher("   ");
	for (i = 0; i < taille; ++i)
		afficher(" ", i, " ");
		
	afficher ("\n	");
	for (i = 0; i < taille; ++i)
		afficher(" ");
		
	afficher ("\n");
	for (i = 0; i < taille; ++i) {
		charToString(t, 'A' + i);
	afficher(" ", t, " ");
	
	for (j = 0; j < taille; ++j) {
		charToString(t, getCase(p, i, j));
		afficher(" ", t, " ");
			}
	afficher("\n\n");
		}
	afficher("\n");
}

void afficherBateauxDisponibles(Plateau* p) {
	afficherBateauxRestantsAutorises(getManager(p));
}


void testsPlateau() {
	Coordonnee tirv, tirv2, destroyer[10];
	Coordonnee *tir = &tirv, *tir2 = &tirv2;
	Plateau plateau, bateaux, tirs;
	Plateau *p, *b, *t;
	p = &plateau;
	b = &bateaux;
	t = &tirs;
	allouerPlateau(p);

	afficher("\n###############################");
	afficher("\n### *** FICHIER PLATEAU *** ###\n");

	afficher("\n # FONCTION initPlateau()\n");
	initPlateau(p);
	assertEquals(getCase(p, 0, 0), VIDE, "plateau[0][0] = VIDE");
	assertEquals(getCase(p, 0, 9), VIDE, "plateau[0][9] = VIDE");

	assertEquals(getCase(p, 9, 9), VIDE, "plateau[9][9] = VIDE");

	afficher("\n # FONCTION setCase(5, 5, '1')\n");
	setCase(p, 5, 5, '1');
	assertEquals(getCase(p, 5, 5), '1', "plateau[9][9] = '1'");
	assertEquals(getCase(p, 0, 0), VIDE, "plateau[0][0] = VIDE");

	afficher("\n # FONCTION setTaille(9)\n");
	setTaille(p, 9);
	assertEquals(getTaille(p), 9, "taille = 9");

	afficher("\n # FONCTION afficherPlateau()\n");
	afficherPlateau(p);

	allouerPlateau(b);
	initPlateau(b);
	allouerPlateau(t);
	initPlateau(t);
	initCoordonnee(tir, 5, 5);
	initCoordonnee(tir2, 5, 3);
	initSuiteCoordonnees(destroyer, 2, "F4 F5");

	afficher("\n # FONCTION placerBateau(['F4','F5'])\n");
	placerBateau(b, destroyer, 2);
	assertEquals(getCase(b, 5, 4), '2', "bateaux[5][4] = '2'");
	assertEquals(getCase(b, 5, 5), '2', "bateaux[5][5] = '2'");

	afficher("\n # FONCTION placerTir([F5]])\n");
	afficher(" # FONCTION placerTir([F3]])\n");
	placerTir(b, t, tir);
	placerTir(b, t, tir2);
	assertEquals(getCase(t, 5, 3), PLOUF, "tirs[5][4] = PLOUF");
	assertEquals(getCase(t, 5, 4), VIDE, "tirs[5][4] = VIDE");
	assertEquals(getCase(t, 5, 5), TOUCHE, "tirs[5][5] = TOUCHE");

	afficher("\n # FONCTION caseNonVide()\n");
	initCoordonnee(tir2, 5, 4);
	assertEquals(caseNonVide(t, tir2), false, "tirs[5][4] = false");
	assertEquals(caseNonVide(t, tir), true, "tirs[5][5] = true");

	afficher("\n # FONCTION tousBateauxTouches()\n");
	assertEquals(tousBateauxTouches(b, t), false, "bateaux ne sont pas tous touches ");
	placerTir(b, t, tir2);
	assertEquals(tousBateauxTouches(b, t), true, "bateaux sont tous touches        ");

	afficher("\n # FONCTION radar()\n");
	assertEquals(radar_NON_C(p, 5, 5, RAYON_RADAR, VIDE), 0, "radar sur position [5][5] = 0");
	assertEquals(radar_NON_C(p, 5, 6, RAYON_RADAR, VIDE), 1, "radar sur position [5][6] = 1");
	assertEquals(radar_NON_C(p, 4, 5, RAYON_RADAR, VIDE), 1, "radar sur position [4][5] = 1");
	assertEquals(radar_NON_C(p, 4, 6, RAYON_RADAR, VIDE), 1, "radar sur position [4][6] = 1");
	assertEquals(radar_NON_C(p, 3, 5, RAYON_RADAR, VIDE), 2, "radar sur position [3][5] = 2");
	assertEquals(radar_NON_C(p, 3, 6, RAYON_RADAR, VIDE), 2, "radar sur position [3][6] = 2");
	assertEquals(radar_NON_C(p, 3, 7, RAYON_RADAR, VIDE), 2, "radar sur position [3][7] = 2");
	assertEquals(radar_NON_C(p, 4, 7, RAYON_RADAR, VIDE), 2, "radar sur position [4][7] = 2");
	assertEquals(radar_NON_C(p, 5, 7, RAYON_RADAR, VIDE), 2, "radar sur position [5][7] = 2");
	assertEquals(radar_NON_C(p, 7, 7, RAYON_RADAR, VIDE), 2, "radar sur position [7][7] = 2");

	detruirePlateau(p);
	detruirePlateau(b);
	detruirePlateau(t);
}