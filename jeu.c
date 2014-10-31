#include <stdio.h>
#include "cli.c"

#define TAILLE 10
#define TAILLE_BATEAU 4
#define NOMBRE_BATEAUX 3

void initialiserTableau(int t[TAILLE][TAILLE]);
void demanderPlacerBateaux(int bateauxJoueur1[TAILLE][TAILLE]);
int placerBateau(char** coordonnees, int nombre, int bateaux[TAILLE][TAILLE]);
int validercoordonnees(char** coord, int nombre);
void demanderTir(int tirsJoueur2[TAILLE][TAILLE], int bateauxJoueur1[TAILLE][TAILLE]);
int placerTir(char** coordonnees, int nombre, int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]);
int verifierPresenceBateau(int y, int x, int bateaux[TAILLE][TAILLE]);


// Fonction de démarrage.
int main() {

	int bateauxJoueur1[TAILLE][TAILLE];
	int tirsJoueur2[TAILLE][TAILLE];

	initialiserTableau(bateauxJoueur1);
	initialiserTableau(tirsJoueur2);

	demanderPlacerBateaux(bateauxJoueur1);
	demanderTir(tirsJoueur2, bateauxJoueur1);

}

void demanderTir(int tirsJoueur2[TAILLE][TAILLE], int bateauxJoueur1[TAILLE][TAILLE]) {
	int valide, nombre, tir, quitter;
	char** coordonnees;
	quitter = tir = valide = 1;

	while(quitter)
	{
		do{
			nettoyerAffichage();
			printf("### SUPER BATAILLE NAVALE :D ###\n\n");
			afficherTableau(tirsJoueur2, TAILLE);

			if(valide != 1) printf("Vous avez ecris de la merde. Veuillez réessayer.\n");
			if(tir != 1) printf("Tir déja effectué. Veuillez réessayer.\n");

			coordonnees = demanderTableau("Veuillez entrer les coordonnees de tir. (exemple: 'A1') : ", &nombre);
			
			valide = validercoordonnees(coordonnees, nombre);
			if(valide) tir = placerTir(coordonnees, nombre, tirsJoueur2, bateauxJoueur1);
		} while(valide != 1 || tir != 1);
	}

	afficherTableau(tirsJoueur2, TAILLE);
}

int placerTir(char** coordonnees, int nombre, int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]) {
	if(nombre == 1) {
		int x, y;
		y = coordonnees[0][0] - 'A';
		x = coordonnees[0][1] - '0';
		if(tirs[y][x] != '.') return 0;
		else {
			if(verifierPresenceBateau(y, x, bateaux)) tirs[y][x] = '*';
			else{ tirs[y][x] = 'O'; }
			return 1; 
		}
	} else return 0;
}

void demanderPlacerBateaux(int bateauxJoueur1[TAILLE][TAILLE]){
	int i, nombre, valide, placement;
	placement = valide = 1;
	char entree[100];
	char** coordonnees;

	for(i = 0; i < NOMBRE_BATEAUX; i++)
	do{
		nettoyerAffichage();
		printf("### SUPER BATAILLE NAVALE :D ###\n\n");
		afficherTableau(bateauxJoueur1, TAILLE);

		if(valide != 1) printf("Vous avez ecris de la merde. Veuillez réessayer.\n");
		if(placement != 1) printf("Placement de bateau impossible. Veuillez réessayer\n");

		coordonnees = demanderTableau("Veuillez entrer les coordonnees de votre bateau en majuscules, séparé par des espaces. (Toutes les cases qu'il prend)(exemple: 'A1 A2 A3') : ", &nombre);
		

		valide = validercoordonnees(coordonnees, nombre);
		if(valide) placement = placerBateau(coordonnees, nombre, bateauxJoueur1);
	} while(valide != 1 || placement != 1);

}

int placerBateau(char** coordonnees, int nombre, int bateaux[TAILLE][TAILLE]){
	int i, j, x, y;
	if(nombre == TAILLE_BATEAU){
		// Verification
		for(i = 0; i < nombre; i++)
			if(verifierPresenceBateau(coordonnees[i][0] - 'A', coordonnees[i][1] - '0', bateaux)) return 0;

		// Placement
		for(i = 0; i < nombre; i++) {
			y = coordonnees[i][0] - 'A';
			x = coordonnees[i][1] - '0';
			bateaux[y][x] = 'B';
		}
		return 1;
	} else return 0;
}

int verifierPresenceBateau(int y, int x, int bateaux[TAILLE][TAILLE]) {
	return (bateaux[y][x] == 'B') ? 1: 0;
}

int validercoordonnees(char** coord, int nombre) {
	// Verfier 1 letter 1 chifffre
	// Verifier alignés && à la suite
	// A l'interieur du tableau

	char t;
	int i;
	int orientationHorizontale, orientationVerticale, croissant, decroissant;
	orientationHorizontale = orientationVerticale = croissant = decroissant = 1;

	for(i = 0; i < nombre; i++){
		char c3 = coord[i][2];
		if(c3 != '\0') return 0;
	}

	for(i = 0; i < nombre; i++){
		char c1 = coord[i][0];
		char c2 = coord[i][1];
		if(c1 < 'A' || c1 >= 'A' + TAILLE) return 0;
		if(c2 < '0' || c2 >= '0' + TAILLE) return 0;
	}

	t = coord[0][0];
	for(i = 1; i < nombre; i++){
		if(t != coord[i][0]) orientationHorizontale = 0; 
	}

	t = coord[0][1];
	for(i = 1; i < nombre; i++){
		if(t != coord[i][1]) orientationVerticale = 0;
	}

	if(!orientationVerticale && !orientationHorizontale)
		return 0;

	if(orientationHorizontale) {
		char u = coord[0][1];
		for(i = 1; i < nombre; i++) {
			if(coord[i][1] != u + i) croissant = 0;
			if(coord[i][1] != u - i) decroissant = 0;
		}
	}

	if(orientationVerticale) {
		char u = coord[0][0];
		for(i = 1; i < nombre; i++) {
			if(coord[i][0] != u + i) croissant = 0;
			if(coord[i][0] != u - i) decroissant = 0;
		}
	}

	if(!croissant && !decroissant) return 0;

	return 1;

}

void initialiserTableau(int t[TAILLE][TAILLE]){
	int i, j;
	for(i = 0; i < TAILLE; i++)
		for(j = 0; j < TAILLE; j++)
			t[i][j] = '.';
}