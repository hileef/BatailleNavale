#include "proprietes.cpp"

#if SYS_VERSION == 1

#include "jeu.h"
#include "cli.h"
#include "coordonnees.h"

void lancerTests();

int main() {

	int choix;
	couleur(0);
	while((choix = accueil())) {
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

#elif SYS_VERSION == 2

#include "systeme.h"

int main() {
	// Voir SYSTEME
	return amorce();
}

#endif



