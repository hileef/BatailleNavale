#include "jeu.h"
#include "cli.h"
#include "coordonnees.h"

void lancerTests();

int main() {

	int choix;
	couleur(0);
	while(choix = accueil()) {
		if(choix == 1)
			jouerPartie();
		else
			lancerTests();
	}
	return 0;

}

void lancerTests() {
	couleur(3);
	nettoyerAffichage();
	testsCoordonnees();
	testsJeu();
	pause();
	couleur(0);
}