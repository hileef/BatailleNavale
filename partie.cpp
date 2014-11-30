#include "partie.h"
#include "cli.h"

// --------------------------------------------------------
// Récupérer le joueur-------------------------------------


static Plateau* getBateaux(Partie* p, int joueur) {
		if (joueur == 1)
			return &p->bateaux1;
		else return &p->bateaux2;
}

static Plateau* getTirs(Partie* p, int joueur) {
		if (joueur == 1)
			return &p->tirs1;
		else return &p->tirs2;
}

static char* getJoueur(Partie* p, int joueur) {
		if (joueur == 1)
			return p->joueur1;
		else return p->joueur2;
}

// --------------------------------------------------------
// Traductions fonctions externes -------------------------


static bool tousBateauxTouches(Partie* p, int joueur) {
		int autreJoueur;
		if (joueur == 1)
			autreJoueur = 2;
		else autreJoueur = 1;
		return tousBateauxTouches(getBateaux(p,autreJoueur),getTirs(p,joueur)); 

}

static bool placerTir(Partie* p, int joueur, Coordonnee* tir){
		int autreJoueur;
		if (joueur == 1)
			autreJoueur = 2;
		else autreJoueur = 1;
		return placerTir(getBateaux(p,autreJoueur),getTirs(p,joueur),tir); 
}


// --------------------------------------------------------
// Déroulement du jeu--------------------------------------


void jouerPartie(Partie *p) {
		preparerPartie(p);

		demanderBateauxAuJoueur(p,1);
		demanderBateauxAuJoueur(p,2);

		gagnerPartie(p,jouerTours(p));

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


static void preparerPartie(Partie* p) {
	nettoyerAffichage();

	couleur(1);
	demander("Veuillez entrer le nom du joueur 1 : ", getJoueur(p, 1));

	couleur(2);
	demander("Veuillez entrer le nom du joueur 2 : ", getJoueur(p, 2));

	preparerPlateaux(p);
}

static void fermerPartie(Partie* p) {
	detruirePlateau(getBateaux(p,1));
	detruirePlateau(getBateaux(p,2));
	detruirePlateau(getTirs(p,1));
	detruirePlateau(getTirs(p,2));
}

static void gagnerPartie(Partie* p, int gagnant) {
	nettoyerAffichage();

	afficher("\n\n * * * * confettis * * * * \n\n");
	afficher("\n\n BRAVO ! \n\n");
	afficher(" \n\n C'est une victoire pour vous Amiral ");
	afficher(getJoueur(p, gagnant));
	afficher(" ! \n\n");

	pause();
}


// --------------------------------------------------------
// Différents tours----------------------------------------------


static int jouerTours(Partie* p) {
	while(true) {
		if(tourJoueur(p, 1))
			return 1;
		if(tourJoueur(p, 2))
			return 2;
	}
}

static bool tourJoueur(Partie* p, int joueur){
		couleur(joueur);

		demanderTirAuJoueur(p, joueur);

		return tousBateauxTouches(p, joueur);
}

static void demanderTirAuJoueur(Partie* p, int joueur) {
	Coordonnee tir;
	bool tirValide = true;
	bool tirPlace = true;

	couleur(joueur);

	do {
		
		nettoyerAffichage();
		afficherPlateau(getTirs(p,joueur));
		afficher("Amiral ");
		afficher(getJoueur(p,joueur));
		afficher(", c'est votre tour !\n");
		
		if(!tirValide)
			afficher("Les coordonnees ne sont pas valides. Veuillez recommencer.\n");
		if(!tirPlace)
			afficher("Le tir deja effectue. Veuillez recommencer.\n");

		tirValide = true;
		tirPlace = true;
		
		afficher("Veuillez entrez des coordonnees de tirs. \n\t(exemple: 'A1' ou: 'i8')");

		tirValide = demanderCoordonnee(" : ",&tir) == 1;
        if(tirValide) tirPlace = placerTir(p, joueur, &tir);

	} while(!tirValide || !tirPlace);

	resultatsTirsJoueur(p,&tir,joueur);
}

static void resultatsTirsJoueur(Partie* p, Coordonnee* tir, int joueur){
	int autreJoueur;
	if(joueur == 1)
		autreJoueur = 2;
	else
		autreJoueur = 1;
	
	nettoyerAffichage();
	afficherPlateau(getTirs(p,joueur));
	
	if(RADAR_ACTIVE && getCase(getTirs(p,joueur), tir) == PLOUF) {
		int r = radar(getBateaux(p, autreJoueur), tir);
		if(r > 0) {
			afficher("Un bateau ennemi se trouve dans un rayon de ", r);
			afficher(" case(s).\n Faites attention, les epaves restent des bateaux.");
		}
	}
	
	pause();
}


static void demanderBateauxAuJoueur(Partie* p, int joueur) {
	int i, taille, nombreBateauxTotal = totalBateauxAutorises();
    bool bateauValide, bateauAutorise, bateauPlace;
    bateauValide = true;
    bateauAutorise = true;
    bateauPlace = true;
    Coordonnee liste[TAILLE_ENTREE];

    couleur(joueur);

	for(i = 0 ; i < nombreBateauxTotal ; ++i){
		do {
			nettoyerAffichage();
			afficherPlateau(getBateaux(p,joueur));
			afficher("Amiral ");
			afficher(getJoueur(p,joueur));
			afficher(", C'est votre tour ! ");
			afficherBateauxDisponibles(getBateaux(p,joueur));

			if(!bateauValide)
				afficher("Ce bateau n'est pas valide. Veuillez Recommencer.\n");
			if(!bateauAutorise)
				afficher("Ce bateau n'est pas disponible. Veuillez recommencer.\n");
			if(!bateauPlace)
				afficher("Il n'y a pas la place pour un bateau. Veuillez recommencer.\n");
			
			bateauValide = true;
			bateauAutorise = true;
			bateauPlace = true;

			afficher("Veuillez entrer les coordonnees de votre bateau. \n ( exemple: 'A2 D2' ou: 'h9 h8 h7 h6' )");

			if((bateauValide = (taille = demanderCoordonnees(" : ", liste, TAILLE_ENTREE)) > 0)) {
				if((bateauAutorise = autoriserBateau(getBateaux(p, joueur), taille)))
					bateauPlace = placerBateau(getBateaux(p, joueur), liste, taille);
			}


		} while(!(bateauValide && bateauAutorise && bateauPlace)); 
	}

	nettoyerAffichage();
	afficherPlateau(getBateaux(p,joueur));
	afficher("Tous les bateaux sont en place.\n");
	pause();
	}




