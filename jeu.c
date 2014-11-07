/*  *** JEU.C ***

Ce fichier contient toute la logique du jeu implementee jusqu'a maintenant.
Les fonctions relatives a la ligen de commande, c'est a dire (recuperation
	d'informations et affichage, entrees & sorties), sont regroupees dans CLI.C
Les proprietes & constantes globales de jeu dont plusieurs fichiers auront
	besoin sont regroupees dans PROPRIETES.C

*/

// Directives de preprocesseur
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jeu.h"

int jouerPartie() {
	int bateaux1[TAILLE][TAILLE];
	int bateaux2[TAILLE][TAILLE];
	int tirs1[TAILLE][TAILLE];
	int tirs2[TAILLE][TAILLE];

	char joueur1[50];
	char joueur2[50];
	char* gagnant;
	demanderNomsJoueurs(joueur1, joueur2, 50);

	initialiserTableau(bateaux1);
	initialiserTableau(tirs1);
	initialiserTableau(bateaux2);
	initialiserTableau(tirs2);

	demanderBateaux(bateaux1, joueur1);
	demanderBateaux(bateaux2, joueur2);
	
	while(1) {
		demanderTir(tirs1, bateaux2, joueur1);
		if(partieTerminee(tirs1, bateaux2)) { 
			gagnant = joueur1;
			break; }
		demanderTir(tirs2, bateaux1, joueur2);
		if(partieTerminee(tirs2, bateaux1)) { 
			gagnant = joueur2;
			break; }
	}
	
	nettoyerAffichage();
	printf("\n $$$  %s, VOUS AVEZ GAGNE! :D $$$  \n", gagnant);
	pause();

	return 0;
}

void demanderNomsJoueurs(char* j1, char* j2, int taille) {
	nettoyerAffichage();
	demander("Veuillez entrer le nom du premier joueur : ", j1, taille);
	demander("Veuillez entrer le nom du deuxieme joueur : ", j2, taille);
	nettoyerAffichage();
}

void demanderTir(int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE], char* nom) {

	// Declaration et initalisation variables requises
	int valide, quitter, tir;
	Coordonnee entree;
	quitter = tir = valide = 1;

	nettoyerAffichage();
	printf("\n ---  %s, c'est a vous. ---  \n", nom);
	pause();

	// Boucle qui se relançera tant que les coordonnees entrees
	// ne sont pas valide ou pas possible (ex: deja tire la)
	do{
	
		// Affichage infos requise, message d'erreurs
		nettoyerAffichage();
		afficherTableau(tirs);
		if(valide != 1) printf("Coordonnees invalides. Veuillez reessayer.\n");
		if(tir != 1) printf("Tir deja effectue. Veuillez reessayer.\n");
		valide = tir = 1;
		printf("%s, ", nom);

		// Demandes coordonees de tirs, formatage
		initCoordonnee(0, 0, &entree);
		valide = demanderCoordonnee("veuillez entrer les coordonnees de tir. \n ( exemple: A1 ou: i8 ) : ", &entree);
		
		// Verifications validite, possibilite, et sauvegarde si verfication reussies.
		if(valide == 1) tir = placerTir(&entree, tirs, bateaux);

	} while(valide == 0 || tir == 0);
	
	nettoyerAffichage();
	afficherTableau(tirs);
	if(tir == TOUCHE)
		printf("TOUCHE! :D \n");
	else
		printf("Plouf... :/ \n");
	pause();

}


/*  PLACER TIR
Cette fonction prends des coordonees valides, verfies s'il n'y a pas de tir deja
	present a cet endroit, et si oui sauvegarde le tir, en verifiant si c'est
	touche ou plouf. Renvoie 0 si le tir n'a pas ete effectue, sinon renvoie TOUCHE ou PLOUF. */
int placerTir(Coordonnee *c, int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]) {
	
	// Si il y a deja eu un tir, renvoyer 0.
	if(tirs[c->y][c->x] != VIDE) return 0;

	// Sinon, si il y a un beateau, enregistrer TOUCHE, sinon PLOUF.
	if(verifierPresenceBateau(c, bateaux))
		return tirs[c->y][c->x] = TOUCHE;
	else
		return tirs[c->y][c->x] = PLOUF;
}

/*	DEMANDER PLACER BATEAUX
Cette fonction affiche le tableau de bateaux du joueur, et lui demande de rentrer
	les coordonnees de ses bateaux. La validite des coordonnees de bateaux ainsi que la 
	possibilite de placement du bateau sont evalues, le cas echouant les coordonees de bateau
	sont re-demandees.
	Si aucun probleme n'est rencontre, le placement de bateau est gere par PLACER BATEAU. */
void demanderBateaux(int bateaux[TAILLE][TAILLE], char* nom){
	// Declaration et initlisation variables
	int i, n, nombre, valide, placement;
	placement = valide = 1;
	nombre = n = 20;
	Coordonnee entrees[n];
	
	nettoyerAffichage();
	printf("\n ---  %s, c'est a vous. ---  \n", nom);
	pause();

	// Cette boucle demandera chaque entree de bateau pour le nombre de bateau a placer.
	for(i = 0; i < NOMBRE_BATEAUX; i++) {
	// Boucle qui se relançera tant que les coordonnees entrees ne sont pas valide ou
	// pas possible (ex: collision avec bateau deja place)
	do{
		// Affichage infos requise
		nettoyerAffichage();
		afficherTableau(bateaux);
		printf("%s, il vous reste %d bateau(x) de %d cases a placer.\n", nom, NOMBRE_BATEAUX - i, TAILLE_BATEAU);
		

		// Gestion messages d'erreurs
		if(valide == 0) printf("Attention : Coordonnees invalides. Veuillez reessayer.\n");
		if(placement == 0) printf("Attention : Placement de bateau impossible. Veuillez reessayer.\n");
		valide = placement = 1;
		
		// Demandes coordonees de bateaux, formatage
		initCoordonnees(entrees, n);

		valide = nombre = demanderCoordonnees("Veuillez entrer les coordonnees de votre bateau. \n ( exemple: A2 D2 ou: h9 h8 h7 h6 ) : ", entrees, n);
		
		// getchar();
		
		// Verifications validite, possibilite, et sauvegarde si verfication reussies.
		if(valide > 0) placement = placerBateau(entrees, nombre, bateaux);
		
	} while(valide == 0 || placement == 0);

	}

	nettoyerAffichage();
	afficherTableau(bateaux);
	printf("\n\n%s, vos bateaux sont maintenants places.\n", nom);
	pause();

}


/*  PLACER TIR
Cette fonction prends des coordonees valides, verfies s'il n'y a pas de bateau deja
	present a cet endroit, et si oui sauvegarde le tir, en verifiant si c'est
	touche ou plouf. Renvoie 0 si le tir n'a pas ete effectue, 1 si sauvegarde.

POUR L'INSTANT LA TAILLE DES BATEAU EST FIXeE ET PRISE EN COMPTE COMME TEL. */
int placerBateau(Coordonnee entrees[], int taille, int bateaux[TAILLE][TAILLE]){

	// Declaration et initialisation variables
	int i, j, x, y;

	// Si les coordonnes nes coincident pas avec la taille de bateau renovyer 0
	if(taille == TAILLE_BATEAU){

		// S'il y a deja un bateau, renvoyer 0.
		for(i = 0; i < taille; i++)
			if(verifierPresenceBateau(&entrees[i], bateaux)) return 0;

		// Sinon, placer le bateau aux coordonnees indiquees.
		for(i = 0; i < taille; i++)
			bateaux[entrees[i].y][entrees[i].x] = BATEAU;
			
		return 1;
	} else return 0;

}


/* VERIFIER PRESENCE BATEAU
Renvoie 1 si un bateau est present aux coordoonees donnes, 0 sinon. */
int verifierPresenceBateau(Coordonnee *c, int bateaux[TAILLE][TAILLE]) {
	return (bateaux[c->y][c->x] != VIDE) ? 1: 0;
}

/* INITALISER TABLEAU
Initialise un tableau a deux dimension de taille TAILLExTAILLE.
Le tableau sera rempli avec la propriete VIDE. */
void initialiserTableau(int t[TAILLE][TAILLE]){
	int i, j;
	for(i = 0; i < TAILLE; i++)
		for(j = 0; j < TAILLE; j++)
			t[i][j] = VIDE;

}

int partieTerminee(int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]) {
	int i, j;
	for(i = 0; i < TAILLE; i++)
		for(j = 0; j < TAILLE; j++) 
			if(bateaux[i][j] == (BATEAU) && tirs[i][j] == VIDE)
				return 0;
	return 1;
}

