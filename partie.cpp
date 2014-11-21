#include "partie.h"
#include "cli.h"

// Les prototypes privés
static void demanderBateauxAuJoueur(Partie* p, int joueur);
static void demanderTirAuJoueur(Partie* p, int joueur);
static void resultatsTirsJoueur(Partie* p, Coordonnee* tir, int joueur);
static bool tourJoueur(Partie* p, int joueur);
static int jouerTours(Partie* p);
static void gagnerPartie(Partie* p, int gagnant);
static void fermerPartie(Partie* p);
static void preparerPartie(Partie* p);
static void fermerPlateaux(Partie* p);
static void preparerPlateaux(Partie* p);

// Protypes privés : acces proprietes
static Plateau* getBateaux(Partie* p, int joueur);
static Plateau* getTirs(Partie* p, int joueur);
static char* getJoueur(Partie* p, int joueur);

// Protypes privés : traduction fonction externes
static bool tousBateauxTouches(Partie* p, int joueur);
static bool placerTir(Partie* p, int joueur, Coordonnee* tir);

// #####################################

static Plateau* getBateaux(Partie* p, int joueur) {
	return (joueur == 1) ? &p->bateaux1: &p->bateaux2;
}
static Plateau* getTirs(Partie* p, int joueur) {
	return (joueur == 1) ? &p->tirs1: &p->tirs2;
}
static char* getJoueur(Partie* p, int joueur) {
	return (joueur == 1) ? p->joueur1: p->joueur2;
}

static bool tousBateauxTouches(Partie* p, int joueur) {
	int autreJoueur = (joueur == 1) ? 2: 1;
	return tousBateauxTouches(getBateaux(p, autreJoueur), getTirs(p, joueur));
}

static bool placerTir(Partie* p, int joueur, Coordonnee* tir) {
	int autreJoueur = (joueur == 1) ? 2: 1;
	return placerTir(getBateaux(p, autreJoueur), getTirs(p, joueur), tir);
}

void jouerPartie(Partie* p) {
	preparerPartie(p);

	demanderBateauxAuJoueur(p, 1);
	demanderBateauxAuJoueur(p, 2);

	gagnerPartie(p, jouerTours(p));
	
	couleur(0);
	fermerPartie(p);
}



static void preparerPlateaux(Partie* p) {
	allouerPlateau(getBateaux(p,1));
	allouerPlateau(getBateaux(p,2));
	allouerPlateau(getTirs(p,1));
	allouerPlateau(getTirs(p,2));
	initPlateau(getBateaux(p,1));
	initPlateau(getBateaux(p,2));
	initPlateau(getTirs(p,1));
	initPlateau(getTirs(p,2));
}

static void fermerPlateaux(Partie* p) {
	detruirePlateau(getBateaux(p,1));
	detruirePlateau(getBateaux(p,2));
	detruirePlateau(getTirs(p,1));
	detruirePlateau(getTirs(p,2));
}

static void preparerPartie(Partie* p) {
	nettoyerAffichage();
	couleur(1);
	demander("Veuillez entrer le nom du joueur 1 : ", getJoueur(p, 1));
	couleur(2);
	demander("Veuillez entrer le nom du joueur 2 : ", getJoueur(p, 2));
	preparerPlateaux(p);
}

static void fermerPartie(Partie* p) {
	fermerPlateaux(p);
}

static void gagnerPartie(Partie* p, int gagnant) {
	nettoyerAffichage();
	afficher("\n\n BRAVO, ");
	afficher(getJoueur(p, gagnant));
	afficher("\n\n YOU'RE THE WINNER!! \n\n");
	pause();
}

static int jouerTours(Partie* p) {
	while(true) {
		if(tourJoueur(p, 1)) return 1;
		if(tourJoueur(p, 2)) return 2;
	}
}

static bool tourJoueur(Partie* p, int joueur){
	couleur(joueur);
	demanderTirAuJoueur(p, joueur);
	return tousBateauxTouches(p, joueur);
}

static void demanderTirAuJoueur(Partie* p, int joueur) {
	Coordonnee tir;
	bool tirValide, tirPlace;
	tirValide = tirPlace = true;

	do {

		nettoyerAffichage();
		afficherPlateau(getTirs(p, joueur));
		afficher("Amiral ");
		afficher(getJoueur(p, joueur));
		afficher(", c'est votre tour! \n");
		if(!tirValide) afficher("Coordonnees invalides. Recommence. \n");
		if(!tirPlace) afficher("Tir fait auparavant. Recommence. \n");
		afficher("Veuillez entrer les coordonnees de tir. \n ( exemple: A1 ou i8 )");
		tirValide = tirPlace = true;

		tirValide = (demanderCoordonnee(" : ", &tir) == 1);
		if(tirValide) tirPlace = placerTir(p, joueur, &tir);
	} while(!tirValide || !tirPlace);

	resultatsTirsJoueur(p, &tir, joueur);

}

static void resultatsTirsJoueur(Partie* p, Coordonnee* tir, int joueur) {
	char conv[2];
	int autreJoueur = (joueur == 1) ? 2: 1;
	nettoyerAffichage();
	afficherPlateau(getTirs(p,joueur));
	if(RADAR_ACTIVE && getCase(getTirs(p,joueur), tir) == PLOUF) {
		int r = radar(getBateaux(p, autreJoueur), tir);
		if(r > 0) {
			afficher("Le radar a detecte un bateau dans un rayon de ");
			intToString(conv, r);
			afficher(conv);
			afficher(" cases. (attention: detecte aussi les epaves)\n");
		}
	}

	pause();
}

static void demanderBateauxAuJoueur(Partie* p, int joueur) {
	int i, taille, nombreBateauxTotal = totalBateauxAutorises();
	bool bateauValide, bateauAutorise, bateauPlace;
	bateauValide = bateauAutorise = bateauPlace = true;
	Coordonnee liste[TAILLE_ENTREE];

	for(i = 0; i < nombreBateauxTotal; i++) { do {

		nettoyerAffichage();
		afficherPlateau(getBateaux(p, joueur));
		afficher("Amiral ");
		afficher(getJoueur(p, joueur));
		afficher(", c'est votre tour! \n");
		afficherBateauxDisponibles();
		if(!bateauValide) afficher("Coordonnees invalides. Recommence. \n");
		if(!bateauAutorise) afficher("Bateau non disponible. Recommence. \n");
		if(!bateauPlace) afficher("Placement impossible. Recommence. \n");
		afficher("Veuillez entrer les coordonnees de votre bateau. \n ( exemple: A2 D2 ou: h9 h8 h7 h6 )");
		bateauValide = bateauAutorise = bateauPlace = true;

		if((bateauValide = (taille = demanderCoordonnees(" : ", liste, TAILLE_ENTREE)) > 0)) {
			if((bateauAutorise = autoriserBateau(getBateaux(p, joueur), taille)))
				bateauPlace = placerBateau(getBateaux(p, joueur), liste, taille);
		}

	} while(!(bateauValide && bateauAutorise && bateauPlace)); }

	nettoyerAffichage();
	afficherPlateau(getBateaux(p, joueur));
	printf("Vos bateux sont maintenant mis en place.\n");
	pause();

}


