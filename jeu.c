#include <stdio.h>
#include "cli.c"

#define TAILLE 5
#define TAILLE_BATEAU 3

void initialiserTableau(int t[TAILLE][TAILLE]);
void demanderPlacerBateaux(int bateauxJoueur1[TAILLE][TAILLE]);
int validerCoordonees(char** coord, int nombre);


// Fonction de démarrage.
int main() {

	int bateauxJoueur1[TAILLE][TAILLE];
	int tirsJoueur2[TAILLE][TAILLE];

	initialiserTableau(bateauxJoueur1);
	initialiserTableau(tirsJoueur2);

	demanderPlacerBateaux(bateauxJoueur1);
}

void demanderPlacerBateaux(int bateauxJoueur1[TAILLE][TAILLE]){
	int i;
	int nombre;
	char entree[100];
	char** coordonees;

	afficherTableau(bateauxJoueur1, TAILLE);
	coordonees = demanderTableau("Veuillez entrer les coordonees de votre bateau en majuscules, séparé par des espaces. (Toutes les cases qu'il prend)(exemple: 'A1 A2 A3') : ", &nombre);
	
	if(validerCoordonees(coordonees, nombre))
		printf("Valide.\n");
	else
		printf("PAS Valide.\n");

/*
	for(i = 0; i < nombre; i++)
		printf("%s\n", coordonees[i]);
*/

}

int validerCoordonees(char** coord, int nombre) {
	// Verfier 1 letter 1 chifffre
	// Verifier alignés && à la suite
	// A l'interieur du tableau

	char t;
	int i;
	int orientationHorizontale, orientationVerticale, croissant, decroissant;
	orientationHorizontale = orientationVerticale = croissant = decroissant = 1;

	printf("Verification: Lettre et Chiffre dans tableau\n");
	for(i = 0; i < nombre; i++){
		char c1 = coord[i][0];
		char c2 = coord[i][1];
		if(c1 < 'A' && c1 >= 'A' + TAILLE) return 0;
		if(c2 < '0' && c2 > '9') return 0;
	}

	t = coord[0][0];
	for(i = 1; i < nombre; i++){
		if(t != coord[i][0]) orientationHorizontale = 0; 
	}

	t = coord[0][1];
	for(i = 1; i < nombre; i++){
		if(t != coord[i][1]) orientationVerticale = 0;
	}

	printf("Verification: Orientation stable\n");
	if(!orientationVerticale && !orientationHorizontale)
		return 0;

	if(orientationHorizontale) {
		char u = coord[0][1];
		for(t = 1; i < nombre; i++) {
			if(coord[i][1] != u + i) croissant = 0;
			if(coord[i][1] != u - i) decroissant = 0;
		}
	}
	printf("Verification: Croissant:%d, Decroissant:%d \n", croissant, decroissant);

	if(orientationVerticale) {
		char u = coord[0][0];
		for(t = 1; i < nombre; i++) {
			if(coord[i][0] != u + i) croissant = 0;
			if(coord[i][0] != u - i) decroissant = 0;
		}
	}

	printf("Verification: Coordonees a la suite\n");
	if(!croissant && !decroissant) return 0;

	return 1;

}

void initialiserTableau(int t[TAILLE][TAILLE]){
	int i, j;
	for(i = 0; i < TAILLE; i++)
		for(j = 0; j < TAILLE; j++)
			t[i][j] = 0;
}