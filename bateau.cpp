#include "proprietes.cpp"
#include "bateau.h"
#include "coordonnees.h"
#include "plateau.h"
#include "cli.h"
#include "unittest.h"
#include <stdlib.h>

int getTaille(Bateau* b) {
	return b->taille;
}
void setTaille(Bateau* b, int x) {
	b->taille = x;
}
int getTouches(Bateau* b) {
	return b->compteTouche;
}
void setTouches(Bateau* b, int x) {
	b->compteTouche = x;
}
void incTouches(Bateau* b) {
	setTouches(b, getTouches(b) + 1);
}
Bateau* getSuivant(Bateau* b) {
	return b->suivant;
}
Bateau* getPrecedent(Bateau* b) {
	return b->precedent;
}
void setSuivant(Bateau* b, Bateau* d) {
	b->suivant = d;
}
void setPrecedent(Bateau* b, Bateau* d) {
	b->precedent = d;
}
Coordonnee* getCoordonnee(Bateau* b, int i) {
	return &b->liste[i];
}
void setCoordonnee(Bateau* b, int i, Coordonnee* x) {
	b->liste[i] = *x;
}
Bateau* getPremier(ListeBateau* m) {
	return m->premier;
}
Bateau* getDernier(ListeBateau* m) {
	return m->dernier;
}
void setPremier(ListeBateau* m, Bateau* b) {
	m->premier = b;
}
void setDernier(ListeBateau* m, Bateau* b) {
	m->dernier = b;
}
int getCompteur(ListeBateau* m, int i) {
	return m->compteurs[i];
}
void setCompteur(ListeBateau* m, int i, int x) {
	m->compteurs[i] = x;
}
void incCompteur(ListeBateau* m, int i) {
	setCompteur(m, i, getCompteur(m, i) + 1);
}

// #####################################

int totalBateauxAutorises() {
	int i, x = 0;
	for(i = 0; i < TAILLES_MAX; i++)
		x += TAILLES[i];
	return x;
}

bool bateauAutorise(ListeBateau* m, int taille) {
	return bateauxRestantsAutorises(m, taille) > 0;
}

int bateauxRestantsAutorises(ListeBateau* m, int taille) {
	return TAILLES[taille - 1] - getCompteur(m, taille - 1);
}

void afficherBateauxRestantsAutorises(ListeBateau* m) {
	int i, x;
	afficher("Vous pouvez placer :\n");
	for(i = 0; i < TAILLES_MAX; i++)
		if((x = bateauxRestantsAutorises(m, i)) > 0) {
			// printf("%d bateaux de : %d cases \n", TAILLES[i], i + 1);
			afficher(" - ", x);
			afficher(" bateaux de : ", i, " cases.\n");
		}
}

void allouerListe(ListeBateau* m){
	int i;
	for(i = 0; i < TAILLES_MAX; i++)
		setCompteur(m, i, 0);
	setPremier(m, NULL);
	setDernier(m, NULL);
}

void detruireListe(ListeBateau* m){
	Bateau *b, *suivant = getPremier(m);
	while((b = suivant) != NULL) {
		suivant = getSuivant(b);
		detruireBateau(b);
	}
	setPremier(m, NULL);
	setDernier(m, NULL);
}

static void detruireBateau(Bateau* b){
	setPrecedent(b, NULL);
	setSuivant(b, NULL);
	free(b);
}

static Bateau* creerBateau(Coordonnee liste[], int taille) {
	int i;
	Bateau* b;
	b = (Bateau*) malloc(sizeof(Bateau));
	for(i = 0; i < taille; i++) {
		initCoordonnee(getCoordonnee(b, i), getY(&liste[i]), getX(&liste[i]));
	}
	setTaille(b, taille);
	setPrecedent(b, NULL);
	setSuivant(b, NULL);
	setTouches(b, 0);
	return b;
}

Bateau* trouverBateau(ListeBateau* m, Coordonnee* x){
	Bateau *b, *suivant = getPremier(m);
	while((b = suivant) != NULL) {
		suivant = getSuivant(b);
		if(bateauContient(b, x))
			return b;
	}
	return NULL;
}

static bool bateauContient(Bateau* b, Coordonnee* x) {
	int i;
	for(i = 0; i < getTaille(b); i++)
		if(egal(getCoordonnee(b, i), x))
			return true;
	return false;
}

bool toucherBateau(Bateau* b) {
	incTouches(b);
	return (getTouches(b) == getTaille(b));
}

static void ajouterBateau(ListeBateau* m, Bateau* b) {
	if(getPremier(m) == NULL) {
		setPremier(m, b);
		setDernier(m, b);
	} else {
		Bateau* queue = getDernier(m);
		setSuivant(queue, b);
		setPrecedent(b, queue);
		setDernier(m, b);
	}
}

void enregistrerBateau(ListeBateau* m, Coordonnee liste[], int taille) {
	ajouterBateau(m, creerBateau(liste, taille));
	incCompteur(m, taille - 1);
}

bool enregistrerTir(ListeBateau* m, Coordonnee* tir) {
	Bateau* b;
	if((b = trouverBateau(m, tir)) != NULL)
		return toucherBateau(b);
	return false;
}

void testsBateaux() {

	Coordonnee liste[10];
	initSuiteCoordonnees(liste, 2, "B0 B4");

	Bateau *b = creerBateau(liste, 3);
	Bateau *b2 = creerBateau(liste, 5);

	afficher("\n###############################");
	afficher("\n### *** FICHIER BATEAU *** ###\n");

	afficher("\n # FONCTION getTaille()\n");
	assertEquals(getTaille(b), 3, "Bateau de taille 3 ");
	assertEquals(getTaille(b2), 5, "Bateau de taille 5 ");

	afficher("\n # FONCTION setTaille()\n");
	setTaille(b, 3);
	assertEquals(getTaille(b), 3, "taille = 3");
	setTaille(b, 5);
	assertEquals(getTaille(b), 5, "taille = 5");

	afficher("\n # FONCTION getTouches()\n");
	ListeBateau MonListeBateau;
	ListeBateau *mgr = &MonListeBateau;
	Bateau *MonBateau = creerBateau(liste, 4);
	allouerListe(mgr);
	ajouterBateau(mgr, MonBateau);
	Coordonnee t;
	Coordonnee *tir = &t;
	initCoordonnee(tir,"B0");
	enregistrerTir(mgr, tir);
	assertEquals(getTouches(MonBateau), 1,"MonBateau touche a la case 'B0' ");



	afficher("\n # FONCTION setTouches()\n");
	setTouches(MonBateau, 2);
	assertEquals(getTouches(MonBateau), 2, "Bateau a ete touche 2 fois");

	afficher("\n # FONCTION incTouches()\n");
	incTouches(MonBateau);
	assertEquals(getTouches(MonBateau), 3, "il a ete toucher 3 fois");

	afficher("\n # FONCTION setSuivant()\n");
    Bateau *BateauSuivant = creerBateau(liste, 3);
	setSuivant(MonBateau, BateauSuivant);
	assertEquals(getSuivant(MonBateau), BateauSuivant, "le bateau suivant est BateauSuivant");

	afficher("\n # FONCTION setPrecedent()\n");
	Bateau *BateauPrecedent = creerBateau(liste, 5);
	setSuivant(MonBateau, BateauPrecedent);
	assertEquals(getSuivant(MonBateau), BateauPrecedent, "le bateau precedent est BateauPrecedent");


	afficher("\n # FONCTION getCoordonnee()\n");
	initSuiteCoordonnees(liste, 2, "A0 A3");
	Bateau *NouveauBateau = creerBateau(liste,4);
	Coordonnee c;
	Coordonnee *coordonnee = &c;
	initCoordonnee(coordonnee,"A2");
	assertTrue(egal(getCoordonnee(NouveauBateau, 2), coordonnee), "a la case 2 on a la coordonnee A2");

    afficher("\n # FONCTION setCoordonnee()\n");
    setCoordonnee(NouveauBateau, 2, coordonnee);
    assertTrue(egal(getCoordonnee(NouveauBateau, 2),coordonnee), "la coordonnee de mon NouveauBateau est A2");

    afficher("\n # FONCTION setPremier()\n");
	setPremier(mgr,NouveauBateau);
	assertEquals(getPremier(mgr), NouveauBateau, "le premier bateau est NouveauBateau");

    afficher("\n # FONCTION setDernier()\n");
    setDernier(mgr, NouveauBateau);
    assertEquals(getDernier(mgr), NouveauBateau, "le dernier bateau est NouveauBateau");

    afficher("\n # FONCTION getPremier()\n");
    assertEquals(getPremier(mgr), NouveauBateau, "il y a un premier bateau");

    afficher("\n # FONCTION getDernier()\n");
    assertEquals(getPremier(mgr), NouveauBateau, "il y a un dernier bateau");

    afficher("\n # FONCTION totalBateauxAutorises()\n");
    assertEquals(totalBateauxAutorises(), 5, "on a le droit a 5 bateaux MAXI");

    afficher("\n # FONCTION bateauAutorise(ListeBateau* m, int taille)\n");
    assertTrue(bateauAutorise(mgr, 3), "bateaux de taille 3 autorise");
    assertTrue(bateauAutorise(mgr, 5), "bateaux de taille 5 autorise");


    afficher("\n # FONCTION bateauxRestantsAutorises(ListeBateau* m, int taille)\n");
    assertEquals(bateauxRestantsAutorises(mgr, 3), 2, "il reste 2 bateaux de taille 3 a placer");
    assertEquals(bateauxRestantsAutorises(mgr, 5), 1, "il reste 1 bateaux de taille 5 a placer");


    afficher("\n # FONCTION afficherBateauxRestantsAutorises(ListeBateau* m)\n");
    afficherBateauxRestantsAutorises(mgr);

    afficher("\n # FONCTION allouerListe(ListeBateau* m)\n");
    setPremier(mgr, NouveauBateau);
    setDernier(mgr, NouveauBateau);
    assertEquals(getPremier(mgr), NouveauBateau, "allocation d'un bateau en premiere position dans le manager");
    assertEquals(getDernier(mgr), NouveauBateau, "allocation d'un bateau en derniere position dans le manager");


    afficher("\n # FONCTION detruireListe(ListeBateau* m)\n");
    setPremier(mgr, NouveauBateau);
	setDernier(mgr, NouveauBateau);
	detruireBateau(NouveauBateau);
	assertEquals(getPremier(mgr), NouveauBateau, "il existe plus de bateau dans le mgr");
	assertEquals(getDernier(mgr), NouveauBateau, "il existe plus de bateau dans le mgr");

	afficher("\n # FONCTION detruireBateau(Bateau* b)\n");
	setSuivant(MonBateau, NouveauBateau);
    detruireBateau(NouveauBateau);
	assertEquals(getSuivant(MonBateau), NouveauBateau, "il existe plus de bateau NouveauBateau");



	afficher("\n # FONCTION creerBateau(Coordonnee liste[], int taille)\n");
	assertEquals(creerBateau(liste, 4), NouveauBateau, "un bateau de taille 4 a ete creer");

	afficher("\n # FONCTION trouverBateau(ListeBateau* m, Coordonnee* x)\n");
	assertEquals(trouverBateau(mgr, coordonnee), NouveauBateau, "on a trouver un bateau NouveauBateau");

	afficher("\n # FONCTION bateauContient(Bateau* b, Coordonnee* x)\n");
	assertTrue(bateauContient(NouveauBateau, coordonnee), "coordonee A2 dans NouveauBateau");


	afficher("\n # FONCTION toucherBateau(Bateau* b)\n");
	incTouches(MonBateau);
	assertEquals(getTouches(MonBateau), 4,"MonBateau touche a la case 'B0' 'B1' 'B2' 'B3' ");
	assertEquals(getTaille(MonBateau), 4, "MonBateau fait une taille 4");


    afficher("\n # FONCTION enregistrerTir(ListeBateau* m, Coordonnee* tir)\n");
    Coordonnee t2;
	Coordonnee *tir2 = &t2;
	initCoordonnee(tir2,"A1");
	enregistrerTir(mgr, tir2);
	assertEquals(getTouches(NouveauBateau), 1,"NouveauBateau touche a la case 'A1' ");
	
	afficher("\n # FONCTION ajouterBateau(ListeBateau* , Bateau* b)\n");
	// reset manager
	Coordonnee pa, *pointA = &pa;
	Coordonnee plan_mistral[TAILLES_MAX];
	detruireListe(mgr);
	allouerListe(mgr);
	initSuiteCoordonnees(plan_mistral, 4, "A0 A1 A2 A3");
	Bateau* mistral = creerBateau(plan_mistral, 4);
	ajouterBateau(mgr, mistral);
	initCoordonnee(pointA, "A1");
	assertEquals(trouverBateau(mgr, pointA), mistral, "Bateau mistral ajoute et trouve ");
	
	afficher("\n # FONCTION enregistrerBateau(ListeBateau* m, Coordonnee liste[], int taille)\n");
	Coordonnee pb, *pointB = &pb;
	Coordonnee tst, *test = &tst;
	Coordonnee plan_kennedy[TAILLES_MAX];
	initSuiteCoordonnees(plan_kennedy, 5, "B0 B1 B2 B3 B4");
	enregistrerBateau(mgr, plan_kennedy, 5);
	initCoordonnee(pointB, "B1");
	initCoordonnee(test, "B0");
	assertTrue(egal(getCoordonnee(trouverBateau(mgr, pointB), 0), test), "Bateau kennedy ajoute et trouve ");
	
}
