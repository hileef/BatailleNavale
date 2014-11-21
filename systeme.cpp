#include "proprietes.cpp"
#include "systeme.h"
#include "partie.h"
#include "cli.h"

static void tests();
static void options();
static char accueil();

int amorce() {
	char choix;
	while(true){
		choix = accueil();
		switch(choix) {
			case 'o':
				options();
				break;
			case 't':
				tests();
				break;
			case 'q':
				return 0;
			default:
				Partie p;
				jouerPartie(&p);
		}
	}
}

static void tests() {
	;
}

static void options() {
	;
}

static char accueil() {
	char entree[TAILLE_ENTREE];
	nettoyerAffichage();
	afficherAccueil_v2();
	demander("votre choix : ", entree, 100);
	if(entree[0] >= 'A' && entree[0] <= 'Z') return (entree[0] - 'A' + 'a');
	return entree[0];
}