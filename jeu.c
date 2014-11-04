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
#include <stdlib.h>
#include "cli.h"
#include "proprietes.c"
#include "coordonnees.h"

// Les prototypes
void initialiserTableau(int t[TAILLE][TAILLE]);
void demanderBateaux(int bateauxJoueur1[TAILLE][TAILLE]);
int placerBateau(Coordonnee entrees[], int taille, int bateaux[TAILLE][TAILLE]);
int validercoordonnees(char** coord, int nombre);
void demanderTir(int tirsJoueur2[TAILLE][TAILLE], int bateauxJoueur1[TAILLE][TAILLE]);
int placerTir(Coordonnee *c, int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]);
int verifierPresenceBateau(Coordonnee *c, int bateaux[TAILLE][TAILLE]);

static void split2(char* s, char** cible, int taille);

// MAIN - Fonction de démarrage
int main() {

	int bateauxJoueur1[TAILLE][TAILLE];
	int tirsJoueur2[TAILLE][TAILLE];

	initialiserTableau(bateauxJoueur1);
	initialiserTableau(tirsJoueur2);

	demanderBateaux(bateauxJoueur1);
	demanderTir(tirsJoueur2, bateauxJoueur1);

}

void demanderTir(int tirsJoueur2[TAILLE][TAILLE], int bateauxJoueur1[TAILLE][TAILLE]) {

	// Déclaration et initalisation variables requises
	int valide, quitter, tir;
	Coordonnee entree;
	quitter = tir = valide = 1;

	// BOUCLE INFINIE
	while(quitter)
	{
		// Boucle qui se relançera tant que les coordonnees entrees
		// ne sont pas valide ou pas possible (ex: déja tiré là)
		do{
		
			// Affichage infos requise, message d'erreurs
			nettoyerAffichage();
			afficherTableau(tirsJoueur2);
			if(valide != 1) printf("Coordonnees invalides. Veuillez réessayer.\n");
			if(tir != 1) printf("Tir déja effectué. Veuillez réessayer.\n");
			valide = tir = 1;

			// Demandes coordonees de tirs, formatage
			initCoordonnee(0, 0, &entree);
			valide = demanderCoordonnee("Veuillez entrer les coordonnees de tir. \n ( exemple: A1 ou: i8 ) : ", &entree);
			
			// Verifications validité, possibilité, et sauvegarde si vérfication réussies.
			if(valide == 1) tir = placerTir(&entree, tirsJoueur2, bateauxJoueur1);

		} while(valide != 1 || tir != 1);

	}

}


/*  PLACER TIR
Cette fonction prends des coordonees valides, vérfies s'il n'y a pas de tir déja
	présent à cet endroit, et si oui sauvegarde le tir, en vérifiant si c'est
	touché ou plouf. Renvoie 0 si le tir n'a pas été effectué, 1 si sauvegardé. */
int placerTir(Coordonnee *c, int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]) {
	
	// Si il y a déja eu un tir, renvoyer 0.
	if(tirs[c->y][c->x] != VIDE) return 0;

	// Sinon, si il y a un beateau, enregistrer TOUCHE, sinon PLOUF.
	if(verifierPresenceBateau(c, bateaux))
		tirs[c->y][c->x] = TOUCHE;
	else
		tirs[c->y][c->x] = PLOUF;
	return 1; 

}

/*	DEMANDER PLACER BATEAUX
Cette fonction affiche le tableau de bateaux du joueur, et lui demande de rentrer
	les coordonnees de ses bateaux. La validité des coordonnees de bateaux ainsi que la 
	possibilité de placement du bateau sont évalués, le cas échouant les coordonees de bateau
	sont re-demandées.
	Si aucun problème n'est rencontré, le placement de bateau est géré par PLACER BATEAU. */
void demanderBateaux(int bateauxJoueur1[TAILLE][TAILLE]){
	// Déclaration et initlisation variables
	int i, n, nombre, valide, placement;
	placement = valide = 1;
	nombre = n = 20;
	Coordonnee entrees[n];
	

	// Cette boucle demandera chaque entree de bateau pour le nombre de bateau à placer.
	for(i = 0; i < NOMBRE_BATEAUX; i++) {
	// Boucle qui se relançera tant que les coordonnees entrees ne sont pas valide ou
	// pas possible (ex: collision avec bateau déja placé)
	do{
		// Affichage infos requise
		nettoyerAffichage();
		afficherTableau(bateauxJoueur1);
		printf("Il vous reste %d bateau(x) de votre flotte à placer.\n", NOMBRE_BATEAUX - i);

		// Gestion messages d'erreurs
		if(valide == 0) printf("Attention : Coordonnees invalides. Veuillez réessayer.\n");
		if(placement == 0) printf("Attention : Placement de bateau impossible. Veuillez réessayer.\n");
		valide = placement = 1;
		
		// Demandes coordonees de bateaux, formatage
		initCoordonnees(entrees, n);

		valide = nombre = demanderCoordonnees("Veuillez entrer les coordonnees de votre bateau. \n ( exemple: A2 D2 ou: h9 h8 h7 h6 ) : ", entrees, n);
		
		// getchar();
		
		// Verifications validité, possibilité, et sauvegarde si vérfication réussies.
		if(valide > 0) placement = placerBateau(entrees, nombre, bateauxJoueur1);
		
	} while(valide == 0 || placement == 0);

	}

}


/*  PLACER TIR
Cette fonction prends des coordonees valides, vérfies s'il n'y a pas de bateau déja
	présent à cet endroit, et si oui sauvegarde le tir, en vérifiant si c'est
	touché ou plouf. Renvoie 0 si le tir n'a pas été effectué, 1 si sauvegardé.

POUR L'INSTANT LA TAILLE DES BATEAU EST FIXÉE ET PRISE EN COMPTE COMME TEL. */
int placerBateau(Coordonnee entrees[], int taille, int bateaux[TAILLE][TAILLE]){

	// Déclaration et initialisation variables
	int i, j, x, y;

	// Si les coordonnes nes coincident pas avec la taille de bateau renovyer 0
	if(taille == TAILLE_BATEAU){

		// S'il y a déja un bateau, renvoyer 0.
		for(i = 0; i < taille; i++)
			if(verifierPresenceBateau(&entrees[i], bateaux)) return 0;

		// Sinon, placer le bateau aux coordonnees indiquees.
		for(i = 0; i < taille; i++)
			bateaux[entrees[i].y][entrees[i].x] = '0' + taille;
			
		return 1;
	} else return 0;

}


/* VERIFIER PRESENCE BATEAU
Renvoie 1 si un bateau est présent aux coordoonees donnes, 0 sinon. */
int verifierPresenceBateau(Coordonnee *c, int bateaux[TAILLE][TAILLE]) {
	return (bateaux[c->y][c->x] != VIDE) ? 1: 0;
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

