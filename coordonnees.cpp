#include "coordonnees.h"

static int validerCoordonnees(Coordonnee cible[], int nombre);
static int validerCoordonnee(char y, char x, Coordonnee* c);
static int sontAlignees(Coordonnee cible[], int nombre);
static int sontALaSuite(Coordonnee cible[], int nombre, int orientation);
static int peutReformatter(Coordonnee a, Coordonnee b);
static void reformatter(Coordonnee cible[], int reformattage);

void initCoordonnee(int i, int j, Coordonnee* c) {
	c->y = i;
	c->x = j;
}

void initCoordonnees(Coordonnee x[], int n) {
	int i;
	for(i = 0; i < n; i++)
		initCoordonnee(0, 0, &x[i]);
}

int entrerCoordonnees(char** entree, Coordonnee cible[], int nombre) {
	return entrerCoordonneesEtReformatter(entree, cible, nombre, 0);
}

int entrerCoordonneesEtReformatter(char** entree, Coordonnee cible[], int nombre, int reformattage) {
	int i;

	for(i = 0; i < nombre; i++) {
		if(entrerCoordonnee(entree[i], &cible[i]) == 0) return 0;
	}

	if(nombre == 2 && reformattage > 2)
		reformatter(cible, reformattage);

	if(reformattage > 2) return validerCoordonnees(cible, reformattage);
	else return validerCoordonnees(cible, nombre);
	

}

// 	Verifie si une entree peuvent êtres reformatees exemple: 'A0 A3' -> 'A0 A1 A2 A3'
//		renvoie 0 si impossible, sinon renvoie le nombre total apres reformattage
int peutReformatterEntree(char** entree, int nombre) {
	Coordonnee a, b;
	if(nombre == 2) {
		if(entrerCoordonnee(entree[0], &a) == 0) return 0;
		if(entrerCoordonnee(entree[1], &b) == 0) return 0;
		return peutReformatter(a, b);
	} else return 0;
}

//	Verifie si cette entree correspond bien a une coordonne valide,
//		si oui sauvegarder dans c et renvoyer 1 sinon renvoyer 0
int entrerCoordonnee(char* entree, Coordonnee* c) {
	// Si il y a bien exactement 2 characteres dans l'entree
	if(entree[0] != '\0' &&  entree[1] != '\0' && entree[2] == '\0') {
		return validerCoordonnee(entree[0], entree[1], c);
	} else return 0;
}

static int validerCoordonnees(Coordonnee cible[], int nombre) {
	int orientation = sontAlignees(cible, nombre);
	if(orientation == 0) return 0;
	if(sontALaSuite(cible, nombre, orientation) == 0) return 0;
	return nombre;
}

//	Verifie si les coordonees donnes sont bien une lettre et un chiffre,
// 		et qu'ils font bien parti des limites du tableau, auquel cas
//		sauvegarder dans c et renvoyer 1 sinon renvoyer 0.
static int validerCoordonnee(char y, char x, Coordonnee *c) {
	int maj  = 1;

	if(x < '0' || x >= '0' + TAILLE) return 0;
	if(y < 'A' || y >= 'A' + TAILLE) maj = 0;
	if(maj == 0 && (y < 'a' || y >= 'a' + TAILLE)) return 0;

	c->y = (maj) ? y - 'A' : y - 'a';
	c->x = x - '0';
	return 1;
}

//	Verifie si les coordonnees sont bien alignees (ex A0 A1 :OK ; A0 B1 :NON)
// 		Renvoie 0 si non, 1 si Vertical, 2 si horizontal
static int sontAlignees(Coordonnee cible[], int nombre) {
	int i, t, horizontal, vertical;
	horizontal = vertical = 1;

	t = cible[0].y;
	for(i = 1; i < nombre; i++){
		if(t != cible[i].y) horizontal = 0; 
	}

	t = cible[0].x;
	for(i = 1; i < nombre; i++){
		if(t != cible[i].x) vertical = 0;
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
		t = cible[0].x;
		for(i = 1; i < nombre; i++) {
			if(cible[i].x != t + i) croissant = 0;
			if(cible[i].x != t - i) decroissant = 0;
		}
	} else if(orientation == 1) {
		t = cible[0].y;
		for(i = 1; i < nombre; i++) {
			if(cible[i].y != t + i) croissant = 0;
			if(cible[i].y != t - i) decroissant = 0;
		}
	} else return 0;

	if(!croissant && !decroissant) return 0;
	else if(croissant) return 1;
	else return 2;
}



// 	Verifie si deux coordonnees peuvent êtres reformatees (ex A1,A3 -> A1,A2,A3 ) 
//		renvoie 0 si impossible, sinon renvoie le nombre d'elements apres reformattage
static int peutReformatter(Coordonnee a, Coordonnee b) {
	Coordonnee t[2];
	t[0] = a;
	t[1] = b;
	int orientation = sontAlignees(t, 2);
	if(orientation == 0) return 0;
	if(sontALaSuite(t, 2, orientation) != 0) return 0;
	else if(orientation == 1) 
		return (a.y > b.y) ? (a.y - b.y) + 1 : (b.y - a.y) + 1;
	else
		return (a.x > b.x) ? (a.x - b.x) + 1 : (b.x - a.x) + 1;

}

// Transforme le tableau de coordonnes cible comme tel : [A0,A3,_,_] -> [A0,A1,A2,A3]
static void reformatter(Coordonnee cible[], int taille) {
	int i, sens, orientation = sontAlignees(cible, 2);
	cible[taille - 1] = cible[1];

	if(orientation == 1)
		sens = (cible[0].y > cible[1].y) ? 0: 1;
	else
		sens = (cible[0].x > cible[1].x) ? 0: 1; 

	for(i = 1; i < taille - 1; i++) {
		if(sens) {
			if(orientation == 1)
				initCoordonnee(cible[0].y + i, cible[0].x, &cible[i]);
			else if(orientation == 2) 
				initCoordonnee(cible[0].y, cible[0].x + i, &cible[i]);
		} else {
			if(orientation == 1)
				initCoordonnee(cible[0].y - i, cible[0].x, &cible[i]);
			else if(orientation == 2) 
				initCoordonnee(cible[0].y, cible[0].x - i, &cible[i]);
		}
	}

}



void testsCoordonnees() {
	printf("\n###################################");
	printf("\n### *** FICHIER COORDONNEES *** ###\n");

	char* entrees[3];
	entrees[0] = "B9";
	entrees[1] = "A3";
	entrees[2] = "C5";
	
	char* entrees2[2];
	entrees2[0] = "A0";
	entrees2[1] = "A3";

	printf("\n # FONCTION initCoordonnee()\n");
	Coordonnee c;
	initCoordonnee(5,9, &c);
	assertEquals(c.y, 5, "Test Coordonnee c.y = 5");
	assertEquals(c.x, 9, "Test Coordonnee c.x = 9");
	
	printf("\n # FONCTION initCoordonnees()\n");
	Coordonnee liste[4];
	initCoordonnees(liste, 3);
	assertEquals(liste[0].y, 0, "Test Coordonnee liste[0].y = 0");
	assertEquals(liste[0].x, 0, "Test Coordonnee liste[0].x = 0");
	assertEquals(liste[1].y, 0, "Test Coordonnee liste[1].y = 0");
	assertEquals(liste[1].x, 0, "Test Coordonnee liste[1].x = 0");
	assertEquals(liste[2].y, 0, "Test Coordonnee liste[2].y = 0");
	assertEquals(liste[2].x, 0, "Test Coordonnee liste[2].x = 0");
	
	printf("\n # FONCTION entrerCoordonnee()\n");
	entrerCoordonnee("B9", &c);
	assertEquals(c.y, 1, "Test Coordonnee c.y = 1 ('B')");
	assertEquals(c.x, 9, "Test Coordonnee c.x = 9");
	
	printf("\n # FONCTION entrerCoordonnees()\n");
	entrerCoordonnees(entrees, liste, 3);
	assertEquals(liste[0].y, 1, "Test Coordonnee liste[0].y = 1 ('B')");
	assertEquals(liste[0].x, 9, "Test Coordonnee liste[0].x = 9");
	assertEquals(liste[1].y, 0, "Test Coordonnee liste[1].y = 0 ('A')");
	assertEquals(liste[1].x, 3, "Test Coordonnee liste[1].x = 3");
	assertEquals(liste[2].y, 2, "Test Coordonnee liste[2].y = 2 ('C')");
	assertEquals(liste[2].x, 5, "Test Coordonnee liste[2].x = 5");
	
	printf("\n # FONCTION entrerCoordonneesEtReformatter()\n");
	entrerCoordonneesEtReformatter(entrees2, liste, 2, 4);
	assertEquals(liste[0].y, 0, "Test Coordonnee liste[0].y = 0 ('A')");
	assertEquals(liste[0].x, 0, "Test Coordonnee liste[0].x = 0");
	assertEquals(liste[1].y, 0, "Test Coordonnee liste[1].y = 1 ('A')");
	assertEquals(liste[1].x, 1, "Test Coordonnee liste[1].x = 0");
	assertEquals(liste[2].y, 0, "Test Coordonnee liste[2].y = 2 ('A')");
	assertEquals(liste[2].x, 2, "Test Coordonnee liste[2].x = 0");
	assertEquals(liste[3].y, 0, "Test Coordonnee liste[2].y = 2 ('A')");
	assertEquals(liste[3].x, 3, "Test Coordonnee liste[2].x = 3");
	
	printf("\n # FONCTION peutReformatterEntree()\n");
	assertEquals(peutReformatterEntree(entrees2, 2), 4, "Test peutReformatterEntree(A0 A3) -> 4");
	entrees2[1] = "C3";
	assertEquals(peutReformatterEntree(entrees2, 2), 0, "Test peutReformatterEntree(A0 C3) -> 0");
}