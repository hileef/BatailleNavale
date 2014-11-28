#include "coordonnees.h"
#include "proprietes.cpp"
#include "systeme.h"
#include "partie.h"
#include "cli.h"


int amorce() {
	couleur(0);
	char choix;
	while(true){
		choix = accueil();
		switch(choix) {
			case 't':
				tests(); break;
			case 'q':
				return 0;
			default:
				Partie p;
				jouerPartie(&p);
		}
	}
}

static void tests() {
	couleur(3);
	nettoyerAffichage();
	testsCoordonnees();
	testsPlateau();
	testsBateaux();
	testsPartie();
	pause();
	couleur(0);

}

static char accueil() {
	char entree[TAILLE_ENTREE];
	nettoyerAffichage();
	afficherAccueil();
	demander("votre choix : ", entree, TAILLE_ENTREE);
	if(entree[0] >= 'A' && entree[0] <= 'Z') return (entree[0] - 'A' + 'a');
	return entree[0];
}