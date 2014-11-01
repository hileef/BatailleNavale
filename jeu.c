/*  *** JEU.C ***

Ce fichier contient toute la logique du jeu implémentée jusqu'a maintenant.
Les fonctions relatives à la ligen de commande, c'est à dire (récupération
	d'informations et affichage, entrées & sorties), sont regroupées dans CLI.C
Les proprietes & constantes globales de jeu dont plusieurs fichiers auront
	besoin sont regroupées dans PROPRIETES.C

*/

// Directives de préprocesseur
#include <stdio.h>
#include <string.h>
#include "cli.c"
#include "proprietes.c"

// Les prorotypes
void initialiserTableau(int t[TAILLE][TAILLE]);
void demanderBateaux(int bateauxJoueur1[TAILLE][TAILLE]);
int placerBateau(char** coordonnees, int nombre, int bateaux[TAILLE][TAILLE]);
int validercoordonnees(char** coord, int nombre);
void demanderTir(int tirsJoueur2[TAILLE][TAILLE], int bateauxJoueur1[TAILLE][TAILLE]);
int placerTir(char** coordonnees, int nombre, int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]);
int verifierPresenceBateau(int y, int x, int bateaux[TAILLE][TAILLE]);


// MAIN - Fonction de démarrage
int main() {

	int bateauxJoueur1[TAILLE][TAILLE];
	int tirsJoueur2[TAILLE][TAILLE];

	initialiserTableau(bateauxJoueur1);
	initialiserTableau(tirsJoueur2);

	demanderBateaux(bateauxJoueur1);
	demanderTir(tirsJoueur2, bateauxJoueur1);

}

/*	DEMANDER TIR
Cette fonction affiche le tableau de tirs du joueur, et lui demande de rentrer
	les coordonnees de son tir. La validité des coordonnees de tir ainsi que la 
	possibilité du tir sont évalués, le cas échouant les coordonees de tir
	sont re-demandées.
	Si aucun problème n'est rencontré, le tir est géré par PLACER TIR.

ATTENTION: POUR LE MOMENT LA BOUCLE QUI DEMANDE LES TIRS EST INFINIE, POUR RAISONS DE TESTS. */
void demanderTir(int tirsJoueur2[TAILLE][TAILLE], int bateauxJoueur1[TAILLE][TAILLE]) {

	// Déclaration et initalisation variables requises
	int valide, nombre, tir, quitter;
	char** coordonnees;
	quitter = tir = valide = 1;

	// BOUCLE INFINIE
	while(quitter)
	{
		// Boucle qui se relançera tant que les coordonnees entrees
		// ne sont pas valide ou pas possible (ex: déja tiré là)
		do{

			// Affichage infos requise, message d'erreurs
			nettoyerAffichage();
			printf("### SUPER BATAILLE NAVALE :D ###\n\n");
			afficherTableau(tirsJoueur2);
			if(valide != 1) printf("Vous avez ecris de la merde. Veuillez réessayer.\n");
			if(tir != 1) printf("Tir déja effectué. Veuillez réessayer.\n");

			// Demandes coordonees de tirs, formatage
			coordonnees = demanderTableau("Veuillez entrer les coordonnees de tir. (exemple: 'A1') : ", &nombre);
			
			// Verifications validité, possibilité, et sauvegarde si vérfication réussies.
			valide = tir = 0;
			valide = validercoordonnees(coordonnees, nombre);
			if(valide) tir = placerTir(coordonnees, nombre, tirsJoueur2, bateauxJoueur1);

		} while(valide != 1 || tir != 1);

	}

}


/*  PLACER TIR
Cette fonction prends des coordonees valides, vérfies s'il n'y a pas de tir déja
	présent à cet endroit, et si oui sauvegarde le tir, en vérifiant si c'est
	touché ou plouf. Renvoie 0 si le tir n'a pas été effectué, 1 si sauvegardé. */
int placerTir(char** coordonnees, int nombre, int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]) {
	
	// Si il n'ya qu'une seule coordonée continuer, sinon renvoyer 0.
	if(nombre == 1) {
		// Déclaration et initialisation variables
		int x, y;
		y = coordonnees[0][0] - 'A';
		x = coordonnees[0][1] - '0';

		// Si il y a déja eu un tir, renvoyer 0.
		if(tirs[y][x] != VIDE) return 0;

		// Sinon, si il y a un beateau, enregistrer TOUCHE, sinon PLOUF.
		if(verifierPresenceBateau(y, x, bateaux)) tirs[y][x] = TOUCHE;
		else{ tirs[y][x] = PLOUF; }
		return 1; 

	} else return 0;

}


/*	DEMANDER PLACER BATEAUX
Cette fonction affiche le tableau de bateaux du joueur, et lui demande de rentrer
	les coordonnees de ses bateaux. La validité des coordonnees de bateaux ainsi que la 
	possibilité de placement du bateau sont évalués, le cas échouant les coordonees de bateau
	sont re-demandées.
	Si aucun problème n'est rencontré, le placement de bateau est géré par PLACER BATEAU. */
void demanderBateaux(int bateauxJoueur1[TAILLE][TAILLE]){
	// Déclaration et initlisation variables
	int i, nombre, valide, placement;
	placement = valide = 1;
	char entree[100];
	char** coordonnees;

	// Cette boucle demandera chaque entree de bateau pour le nombre de bateau à placer.
	for(i = 0; i < NOMBRE_BATEAUX; i++)
	// Boucle qui se relançera tant que les coordonnees entrees ne sont pas valide ou
	// pas possible (ex: collision avec bateau déja placé)
	do{

		// Affichage infos requise, message d'erreurs, puis reset des erreurs.
		nettoyerAffichage();
		printf("### SUPER BATAILLE NAVALE :D ###\n\n");
		afficherTableau(bateauxJoueur1);
		if(valide != 1) printf("Coordonnees invalides. Veuillez réessayer.\n");
		if(placement != 1) printf("Placement de bateau impossible. Veuillez réessayer.\n");

		// Demandes coordonees de bateaux, formatage
		coordonnees = demanderTableau("Veuillez entrer les coordonnees de votre bateau en majuscules, séparé par des espaces.(Toutes les cases qu'il prend)(exemple: 'A1 A2 A3') : ", &nombre);
		
		// Verifications validité, possibilité, et sauvegarde si vérfication réussies.
		valide = placement = 0;
		valide = validercoordonnees(coordonnees, nombre);
		if(valide) placement = placerBateau(coordonnees, nombre, bateauxJoueur1);

	} while(valide != 1 || placement != 1);

}


/*  PLACER TIR
Cette fonction prends des coordonees valides, vérfies s'il n'y a pas de bateau déja
	présent à cet endroit, et si oui sauvegarde le tir, en vérifiant si c'est
	touché ou plouf. Renvoie 0 si le tir n'a pas été effectué, 1 si sauvegardé.

POUR L'INSTANT LA TAILLE DES BATEAU EST FIXÉE ET PRISE EN COMPTE COMME TEL. */
int placerBateau(char** coordonnees, int taille, int bateaux[TAILLE][TAILLE]){

	// Déclaration et initialisation variables
	int i, j, x, y;

	// Si les coordonnes nes coincident pas avec la taille de bateau renovyer 0
	if(taille == TAILLE_BATEAU){

		// S'il y a déja un bateau, renvoyer 0.
		for(i = 0; i < taille; i++)
			if(verifierPresenceBateau(coordonnees[i][0] - 'A', coordonnees[i][1] - '0', bateaux)) return 0;

		// Sinon, placer le bateau aux coordonnees indiquees.
		for(i = 0; i < taille; i++) {
			y = coordonnees[i][0] - 'A';
			x = coordonnees[i][1] - '0';
			bateaux[y][x] = '0' + taille;
		}
		return 1;
	} else return 0;

}


/* VERIFIER PRESENCE BATEAU
Renvoie 1 si un bateau est présent aux coordoonees donnes, 0 sinon. */
int verifierPresenceBateau(int y, int x, int bateaux[TAILLE][TAILLE]) {
	return (bateaux[y][x] != VIDE) ? 1: 0;
}

/* VALIDER COORDONNEES
Renvoir 1 si les coordonees donnes sont considérées valides, 0 sinon.
Facteurs: Coordonees doivent être composée d'une lettre et d'un chiffre,
	doivent être linéaire dans leur orientation (horiz ou verti), et doivent
	se suivre sans trous.
*/
int validercoordonnees(char** coord, int nombre) {

	// Définition et initialisation variables
	char t, c1, c2;
	int i, horizontal, vertical, croissant, decroissant;
	horizontal = vertical = croissant = decroissant = 1;

	// Vérficiation : il y a bien 2 charactères par coordonees
	for(i = 0; i < nombre; i++)
		if(coord[i][2] != '\0')
			return 0;

	// Vérficiation : les 2 charactères sont une lettre et un chiffre
	// et ils ne sont pas hors de la portée du tableau
	for(i = 0; i < nombre; i++){
		c1 = coord[i][0];
		c2 = coord[i][1];
		if(c1 < 'A' || c1 >= 'A' + TAILLE) return 0;
		if(c2 < '0' || c2 >= '0' + TAILLE) return 0;
	}

	// Vérification : orientation horizontale
	t = coord[0][0];
	for(i = 1; i < nombre; i++){
		if(t != coord[i][0]) horizontal = 0; 
	}

	// Vérification : orientation verticale
	t = coord[0][1];
	for(i = 1; i < nombre; i++){
		if(t != coord[i][1]) vertical = 0;
	}

	// Vérification : l'orientation est linéaire
	if(!vertical && !horizontal)
		return 0;

	// Vérification : à la suite (en horizontal) 
	if(horizontal) {
		t = coord[0][1];
		for(i = 1; i < nombre; i++) {
			if(coord[i][1] != t + i) croissant = 0;
			if(coord[i][1] != t - i) decroissant = 0;
		}
	}

	// Vérification : à la suite (en vertical)
	if(vertical) {
		t = coord[0][0];
		for(i = 1; i < nombre; i++) {
			if(coord[i][0] != t + i) croissant = 0;
			if(coord[i][0] != t - i) decroissant = 0;
		}
	}

	// Vérification : à la suite
	// (en croissant ou décroissant) dans une des deux dimensions
	if(!croissant && !decroissant) return 0;

	// Verifications terminées.
	return 1;

}


/* INITALISER TABLEAU
Initialise un tableau à deux dimension de taille TAILLExTAILLE.
Le tableau sera rempli avec la propriete VIDE. */
void initialiserTableau(int t[TAILLE][TAILLE]){
	int i, j;
	for(i = 0; i < TAILLE; i++)
		for(j = 0; j < TAILLE; j++)
			t[i][j] = VIDE;

}

