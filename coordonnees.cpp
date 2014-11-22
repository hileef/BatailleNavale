#include "coordonnees.h"

#include <stdio.h>
#include <string.h>
#include "unittest.h"
#include "proprietes.cpp"
#include "cli.h"

// Les prototypes privés
static bool validerCoordonnee(char y, char x, Coordonnee *c);
static int sontAlignees(Coordonnee cible[], int nombre);
static int sontALaSuite(Coordonnee cible[], int nombre, int orientation);
static int validerSuiteCoordonnees(Coordonnee cible[], int nombre);

static int etendueSuiteCoordonnees(char** entree, int nombre);
static int etendueSuiteCoordonnees(Coordonnee* a, Coordonnee* b);
static void etendreSuiteCoordonnees(Coordonnee cible[], int etendue);


// GET & SET de COORDONNEE
int getY(Coordonnee* c) { return c->y; }
int getX(Coordonnee* c) { return c->x; }
void setY(Coordonnee* c, int y) { c->y = y; }
void setX(Coordonnee* c, int x) { c->x = x; }


bool egal(Coordonnee* a, Coordonnee* b) {
	return ((getY(a) == getY(b)) && (getX(a) == getX(b)));
}

// INIT COORDONNEE
void initCoordonnee(Coordonnee* c) {
	initCoordonnee(c, 0, 0); }
void initCoordonnee(Coordonnee* c, int i, int j) {
	setY(c, i);
	setX(c, j);
}
bool initCoordonnee(Coordonnee* c, const char* texte) {
	if(texte[0] != '\0' &&  texte[1] != '\0' && texte[2] == '\0')
		return validerCoordonnee(texte[0], texte[1], c);
	else return false;
}


// INIT SUITE COORDONNEES
int initSuiteCoordonnees(Coordonnee cible[], int n) {
	return initSuiteCoordonnees(cible, n, 0, 0); }
int initSuiteCoordonnees(Coordonnee cible[], int n, int i, int j) {
	int k;
	for(k = 0; k < n; k++)
		initCoordonnee(&cible[k], i, j);
	return n;
}
int initSuiteCoordonnees(Coordonnee cible[], int n, char** textes) {
	int i, etendue = etendueSuiteCoordonnees(textes, n);

	for(i = 0; i < n; i++) {
		if(!initCoordonnee(&cible[i], textes[i])) return false;
	}

	if(n == 2 && etendue > 2)
		etendreSuiteCoordonnees(cible, etendue);

	if(etendue > 2)
		return validerSuiteCoordonnees(cible, etendue);
	else return validerSuiteCoordonnees(cible, n);
}

static int validerSuiteCoordonnees(Coordonnee cible[], int nombre) {
	int orientation = sontAlignees(cible, nombre);
	if(orientation == 0) return 0;
	if(sontALaSuite(cible, nombre, orientation) == 0) return 0;
	return nombre;
}

//	Verifie si les coordonees donnes sont bien une lettre et un chiffre,
// 		et qu'ils font bien parti des limites du tableau, auquel cas
//		sauvegarder dans c et renvoyer 1 sinon renvoyer 0.
static bool validerCoordonnee(char y, char x, Coordonnee *c) {
	bool maj = true;

	if(x < '0' || x >= '0' + TAILLE) return false;
	if(y < 'A' || y >= 'A' + TAILLE) maj = false;
	if(!maj && (y < 'a' || y >= 'a' + TAILLE)) return false;

	setY(c, (maj) ? y - 'A' : y - 'a');
	setX(c, x - '0');
	return true;
}

//	Verifie si les coordonnees sont bien alignees (ex A0 A1 :OK ; A0 B1 :NON)
// 		Renvoie 0 si non, 1 si Vertical, 2 si horizontal
static int sontAlignees(Coordonnee cible[], int nombre) {
	int i, t, horizontal, vertical;
	horizontal = vertical = 1;

	t = getY(&cible[0]);
	for(i = 1; i < nombre; i++){
		if(t != getY(&cible[i])) horizontal = 0; 
	}

	t = getX(&cible[0]);
	for(i = 1; i < nombre; i++){
		if(t != getX(&cible[i])) vertical = 0;
	}

	if(!vertical && !horizontal) return 0;
	else if(vertical) return 1;
	else return 2;
}

// Verifie si les coordonnes sont bien a la suite (ex A1 A2 A3 :OK ; ex A1 A4 A5 :NON)
//	Revoie 0 si non, 1 si ordre croissant, 2 si ordre decroissant
static int sontALaSuite(Coordonnee cible[], int nombre, int orientation) {
	int i, t, croissant, decroissant;
	croissant = decroissant = 1;

	if(orientation == 2) {
		t = getX(&cible[0]);
		for(i = 1; i < nombre; i++) {
			if(getX(&cible[i]) != t + i) croissant = 0;
			if(getX(&cible[i]) != t - i) decroissant = 0;
		}
	} else if(orientation == 1) {
		t = getY(&cible[0]);
		for(i = 1; i < nombre; i++) {
			if(getY(&cible[i]) != t + i) croissant = 0;
			if(getY(&cible[i]) != t - i) decroissant = 0;
		}
	} else return 0;

	if(!croissant && !decroissant) return 0;
	else if(croissant) return 1;
	else return 2;
}


// 	Verifie si une entree peuvent êtres reformatees exemple: 'A0 A3' -> 'A0 A1 A2 A3'
//		renvoie 0 si impossible, sinon renvoie le nombre total apres etendue
static int etendueSuiteCoordonnees(char** entree, int nombre) {
	Coordonnee a, b;
	if(nombre == 2) {
		if(initCoordonnee(&a, entree[0]) == 0) return 0;
		if(initCoordonnee(&b, entree[1]) == 0) return 0;
		return etendueSuiteCoordonnees(&a, &b);
	} else return 0;
}

// 	Verifie si deux coordonnees peuvent êtres reformatees (ex A1,A3 -> A1,A2,A3 ) 
//		renvoie 0 si impossible, sinon renvoie le nombre d'elements apres etendue
static int etendueSuiteCoordonnees(Coordonnee* a, Coordonnee* b) {
	Coordonnee t[2];
	t[0] = *a;
	t[1] = *b;
	int orientation = sontAlignees(t, 2);
	if(orientation == 0) return 0;
	if(sontALaSuite(t, 2, orientation) != 0) return 0;
	else if(orientation == 1) 
		return (getY(a) > getY(b)) ? (getY(a) - getY(b)) + 1 : (getY(b) - getY(a)) + 1;
	else
		return (getX(a) > getX(b)) ? (getX(a) - getX(b)) + 1 : (getX(b) - getX(a)) + 1;

}

// Transforme le tableau de coordonnes cible comme tel : [A0,A3,_,_] -> [A0,A1,A2,A3]
static void etendreSuiteCoordonnees(Coordonnee cible[], int etendue) {
	bool croissant;
	int i, orientation = sontAlignees(cible, 2);
	cible[etendue - 1] = cible[1];

	if(orientation == 1)
		croissant = (getY(&cible[0]) < getY(&cible[1]));
	else
		croissant = (getX(&cible[0]) < getX(&cible[1])); 

	for(i = 1; i < etendue - 1; i++) {
		if(croissant) {
			if(orientation == 1)
				initCoordonnee(&cible[i], getY(&cible[0]) + i, getX(&cible[0]));
			else if(orientation == 2) 
				initCoordonnee(&cible[i], getY(&cible[0]), getX(&cible[0]) + i);
		} else {
			if(orientation == 1)
				initCoordonnee(&cible[i], getY(&cible[0]) - i, getX(&cible[0]));
			else if(orientation == 2) 
				initCoordonnee(&cible[i], getY(&cible[0]), getX(&cible[0]) - i);
		}
	}

}



void testsCoordonnees() {
	Coordonnee c, k, l, m, n, liste[4];
	char **entreesZ1, **entreesZ2;
	int validite;

	allocSuperString(&entreesZ1, TAILLE_ENTREE);
	allocSuperString(&entreesZ2, TAILLE_ENTREE);

	afficher("\n###################################");
	afficher("\n### *** FICHIER COORDONNEES *** ###\n");

	afficher("\n # FONCTION initCoordonnee()\n");
	
	initCoordonnee(&c);
	assertEquals(getY(&c), 0, "Coordonnee c.y = 0 ('A') ");
	assertEquals(getX(&c), 0, "Coordonnee c.x = 0       ");

	afficher("\n # FONCTION initCoordonnee(5, 9)\n");
	initCoordonnee(&c, 5, 9);
	assertEquals(getY(&c), 5, "Coordonnee c.y = 5 ('F') ");
	assertEquals(getX(&c), 9, "Coordonnee c.x = 9       ");

	afficher("\n # FONCTION initCoordonnee('B9')\n");
	initCoordonnee(&c, "B9");
	assertEquals(getY(&c), 1, "Coordonnee c.y = 1 ('B') ");
	assertEquals(getX(&c), 9, "Coordonnee c.x = 9       ");
	
	afficher("\n # FONCTION initSuiteCoordonnees(2, 1)\n");

	initSuiteCoordonnees(liste, 3, 2, 1);
	assertEquals(getY(&liste[0]), 2, "Coordonnee liste[0].y = 2 ('C') ");
	assertEquals(getX(&liste[0]), 1, "Coordonnee liste[0].x = 1       ");
	assertEquals(getY(&liste[1]), 2, "Coordonnee liste[1].y = 2 ('C') ");
	assertEquals(getX(&liste[1]), 1, "Coordonnee liste[1].x = 1       ");
	assertEquals(getY(&liste[2]), 2, "Coordonnee liste[2].y = 2 ('C') ");
	assertEquals(getX(&liste[2]), 1, "Coordonnee liste[2].x = 1       ");
	


	split("B9 A3 C5", entreesZ1, 3);
	split("A0 A3", entreesZ2, 2);
	
	afficher("\n # FONCTION initSuiteCoordonnees(['B9', 'A3', 'C5'])\n");
	validite = initSuiteCoordonnees(liste, 3, entreesZ1);
	assertEquals(getY(&liste[0]), 1, "Coordonnee liste[0].y = 1 ('B') ");
	assertEquals(getX(&liste[0]), 9, "Coordonnee liste[0].x = 9       ");
	assertEquals(getY(&liste[1]), 0, "Coordonnee liste[1].y = 0 ('A') ");
	assertEquals(getX(&liste[1]), 3, "Coordonnee liste[1].x = 3       ");
	assertEquals(getY(&liste[2]), 2, "Coordonnee liste[2].y = 2 ('C') ");
	assertEquals(getX(&liste[2]), 5, "Coordonnee liste[2].x = 5       ");
	assertEquals(validite, 0, "Liste de coordonnees non valide.");
	
	afficher("\n # FONCTION etendreSuiteCoordonnees(['A0','A3','',''])\n");
	initCoordonnee(&k, 0, 0);
	initCoordonnee(&l, 0, 3);
	liste[0] = k;
	liste[1] = l;
	etendreSuiteCoordonnees(liste, 4);
	assertEquals(getY(&liste[0]), 0, "Coordonnee liste[0].y = 0 ('A') ");
	assertEquals(getX(&liste[0]), 0, "Coordonnee liste[0].x = 0       ");
	assertEquals(getY(&liste[1]), 0, "Coordonnee liste[1].y = 0 ('A') ");
	assertEquals(getX(&liste[1]), 1, "Coordonnee liste[1].x = 1       ");
	assertEquals(getY(&liste[2]), 0, "Coordonnee liste[2].y = 0 ('A') ");
	assertEquals(getX(&liste[2]), 2, "Coordonnee liste[2].x = 2       ");
	assertEquals(getY(&liste[3]), 0, "Coordonnee liste[2].y = 0 ('A') ");
	assertEquals(getX(&liste[3]), 3, "Coordonnee liste[2].x = 3       ");

	afficher("\n # FONCTION initSuiteCoordonnees(['A0','A3','',''])\n");
	validite = initSuiteCoordonnees(liste, 2, entreesZ2);
	assertEquals(getY(&liste[0]), 0, "Coordonnee liste[0].y = 0 ('A') ");
	assertEquals(getX(&liste[0]), 0, "Coordonnee liste[0].x = 0       ");
	assertEquals(getY(&liste[1]), 0, "Coordonnee liste[1].y = 0 ('A') ");
	assertEquals(getX(&liste[1]), 1, "Coordonnee liste[1].x = 1       ");
	assertEquals(getY(&liste[2]), 0, "Coordonnee liste[2].y = 0 ('A') ");
	assertEquals(getX(&liste[2]), 2, "Coordonnee liste[2].x = 2       ");
	assertEquals(getY(&liste[3]), 0, "Coordonnee liste[2].y = 0 ('A') ");
	assertEquals(getX(&liste[3]), 3, "Coordonnee liste[2].x = 3       ");
	assertEquals(validite, 4, "Liste de coordonnees valide.");
	

	freeSuperString(&entreesZ1, TAILLE_ENTREE);
	freeSuperString(&entreesZ2, TAILLE_ENTREE);
}