#include <stdio.h>
#include "cli.c"

test

// Fonction de démarrage.
int main() {

	char entree[100];

	do {
		nettoyerAffichage();
		printf("Bonjour, bienvenue sur notre sublissime jeu.\n");
		demander("Voulez-vous quitter? Si oui, tapez '0' : ", entree, sizeof entree);
	} while(entree[0] != '0');
}
