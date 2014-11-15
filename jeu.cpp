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


// MAIN - Fonction de demarrage

int accueil() {
	nettoyerAffichage();
	afficherAccueil();
	char entree[100];
	printf("Bonjour.\n");
	printf("Pour tester, tapez 'test' \n");
	printf("Pour jouer, tapez 'jeu'\n");
	printf("Pour quitter, tapez 'quitter'");
	demander(" : ", entree, 100);
	if(entree[0] == 't' || entree[0] == 'T') return 2;
	else if(entree[0] == 'q' || entree[0] == 'Q') return 0;
	else return 1;
	
}

int jouerPartie() {
	int bateaux1[TAILLE][TAILLE];
	int bateaux2[TAILLE][TAILLE];
	int tirs1[TAILLE][TAILLE];
	int tirs2[TAILLE][TAILLE];
	
	char rejouer[50];
	char joueur1[50];
	char joueur2[50];

	initialiserTableau(bateaux1);
	initialiserTableau(tirs1);
	initialiserTableau(bateaux2);
	initialiserTableau(tirs2);

	nettoyerAffichage();
	
	couleur(1);
	demander("Veuillez entrer le nom du joueur 1 : ", joueur1, 50);
	couleur(2);
	demander("Veuillez entrer le nom du joueur 2 : ", joueur2, 50);
	
	couleur(1);
	demanderBateaux(bateaux1, joueur1);
	couleur(2);
	demanderBateaux(bateaux2, joueur2);
	
	while(1) {
		couleur(1);
		demanderTir(tirs1, bateaux2, joueur1);
		if(partieTerminee(tirs1, bateaux2) == 1) break;
		couleur(2);
		demanderTir(tirs2, bateaux1, joueur2);
		if(partieTerminee(tirs2, bateaux1) == 1) break;
	}
	
	
	nettoyerAffichage();
	printf("\n\n BRAVO !\n\n YOU'RE THE WINNER!! \n\n");
	pause();
	
	couleur(0);
	
}


void demanderTir(int tirsJoueur2[TAILLE][TAILLE], int bateauxJoueur1[TAILLE][TAILLE], char* nom) {

	// Declaration et initalisation variables requises
	int valide, quitter, tir, radar;
	Coordonnee entree;
	quitter = tir = valide = 1;

	// Boucle qui se relançera tant que les coordonnees entrees
	// ne sont pas valide ou pas possible (ex: deja tire la)
	do{
	
		// Affichage infos requise, message d'erreurs
		nettoyerAffichage();
		afficherTableau(tirsJoueur2);
		printf("%s, c'est ton tour !\n", nom);
		if(valide != 1) printf("Coordonnees invalides. Recommence.\n");
		if(tir != 1) printf("Tir fait auparavant. Recommence.\n");
		valide = tir = 1;

		// Demandes coordonees de tirs, formatage
		initCoordonnee(0, 0, &entree);
		valide = demanderCoordonnee("Veuillez entrer les coordonnees de tir. \n ( exemple: A1 ou: i8 ) : ", &entree);
		
		// Verifications validite, possibilite, et sauvegarde si verfication reussies.
		if(valide == 1) tir = placerTir(&entree, tirsJoueur2, bateauxJoueur1);

	} while(valide != 1 || tir != 1);
	
	nettoyerAffichage();
	afficherTableau(tirsJoueur2);
	radar = superRadar(&entree, bateauxJoueur1);
	//printf("RADAR = %d\n", radar);
	if(radar > 0 && verifierPlouf(&entree, bateauxJoueur1))
		printf("\nLe radar a detecte un bateau dans un rayon de %d cases.\n", radar);
	pause();

}


/*  PLACER TIR
Cette fonction prends des coordonees valides, verfies s'il n'y a pas de tir deja
	present a cet endroit, et si oui sauvegarde le tir, en verifiant si c'est
	touche ou plouf. Renvoie 0 si le tir n'a pas ete effectue, 1 si sauvegarde. */
int placerTir(Coordonnee *c, int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]) {
	
	// Si il y a deja eu un tir, renvoyer 0.
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
	les coordonnees de ses bateaux. La validite des coordonnees de bateaux ainsi que la 
	possibilite de placement du bateau sont evalues, le cas echouant les coordonees de bateau
	sont re-demandees.
	Si aucun probleme n'est rencontre, le placement de bateau est gere par PLACER BATEAU. */
void demanderBateaux(int bateauxJoueur1[TAILLE][TAILLE], char* nom){
	// Declaration et initlisation variables
	int i, n, nombre, valide, placement;
	placement = valide = 1;
	nombre = n = 20;
	Coordonnee entrees[n];
	

	// Cette boucle demandera chaque entree de bateau pour le nombre de bateau a placer.
	for(i = 0; i < NOMBRE_BATEAUX; i++) {
	// Boucle qui se relançera tant que les coordonnees entrees ne sont pas valide ou
	// pas possible (ex: collision avec bateau deja place)
	do{
		// Affichage infos requise
		nettoyerAffichage();
		afficherTableau(bateauxJoueur1);
		printf("%s, c'est ton tour!\n", nom);
		printf("Il vous reste %d bateau(x) de %d cases de votre flotte a placer.\n", NOMBRE_BATEAUX - i,  TAILLE_BATEAU);
		

		// Gestion messages d'erreurs
		if(valide == 0) printf("Attention : Coordonnees invalides. Recommence.\n");
		if(placement == 0) printf("Attention : Placement de bateau impossible. Recommence.\n");
		valide = placement = 1;
		
		// Demandes coordonees de bateaux, formatage
		initCoordonnees(entrees, n);

		valide = nombre = demanderCoordonnees("Veuillez entrer les coordonnees de votre bateau. \n ( exemple: A2 D2 ou: h9 h8 h7 h6 ) : ", entrees, n);
		
		// getchar();
		
		// Verifications validite, possibilite, et sauvegarde si verfication reussies.
		if(valide > 0) placement = placerBateau(entrees, nombre, bateauxJoueur1);
		
	} while(valide == 0 || placement == 0);

	}
	
	nettoyerAffichage();
	afficherTableau(bateauxJoueur1);
	printf("Vos bateux sont maintenant mis en place.\n");
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

int verifierPlouf(Coordonnee *c, int bateaux[TAILLE][TAILLE]) {
	return (bateaux[c->y][c->x] != PLOUF) ? 1: 0;
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

int radar(Coordonnee* tir, int bateaux[TAILLE][TAILLE]) {
	int i, j, k, dy, dx, proche = RAYON_RADAR;
	for(i = tir->y - RAYON_RADAR; i < tir->y + RAYON_RADAR; i++) {
		for(j = tir->x - RAYON_RADAR; j < tir->x + RAYON_RADAR; j++) {
			if(!(i == tir->y && j == tir->x)) {
				if(bateaux[i][j] == BATEAU) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int superRadar(Coordonnee* tir, int bateaux[TAILLE][TAILLE]) {
	int i, j, k, d, dx, dy, proche = 0;
	for(i = tir->y - RAYON_RADAR; i < tir->y + RAYON_RADAR; i++) {
		for(j = tir->x - RAYON_RADAR; j < tir->x + RAYON_RADAR; j++) {
			if((bateaux[i][j] == BATEAU) && (!(i == tir->y && j == tir->x))) {
				dy = tir->y - i;
				dx = tir->x - j;
				d = (dy > dx) ? dy : dx;
				for(k = RAYON_RADAR; k > 0 ; k--)
					if(d == k || d == -k || d == k || d == -k) proche = k;
			}
		}
	}
	return proche;
	
}





void testsJeu() {
	printf("\n###########################");
	printf("\n### *** FICHIER JEU *** ###\n");

	int bateaux[TAILLE][TAILLE];
	
	printf("\n # FONCTION initialiserTableau()\n");
	initialiserTableau(bateaux);
	assertEquals(bateaux[0][0], (int) VIDE, "Test bateaux[0][0] == VIDE");
	assertEquals(bateaux[1][1], (int) VIDE, "Test bateaux[1][1] == VIDE");
	assertEquals(bateaux[1][0], (int) VIDE, "Test bateaux[1][0] == VIDE");
	assertEquals(bateaux[0][1], (int) VIDE, "Test bateaux[0][1] == VIDE");
	
	Coordonnee liste[4];
	char* destroyer[2];
	destroyer[0] = "A0";
	destroyer[1] = "A3";
	
	
	printf("\n # FONCTION placerBateau()\n");
	printf("Test : qu'un bateau est bien place.\n");
	entrerCoordonneesEtReformatter(destroyer, liste, 2, 4);
	placerBateau(liste, 4, bateaux);
	assertEquals(bateaux[0][0], (int) BATEAU, "Test pour Destroyer(A0,A3) bateaux[0][0] == BATEAU");
	assertEquals(bateaux[0][1], (int) BATEAU, "Test pour Destroyer(A0,A3) bateaux[0][1] == BATEAU");
	assertEquals(bateaux[0][2], (int) BATEAU, "Test pour Destroyer(A0,A3) bateaux[0][2] == BATEAU");
	assertEquals(bateaux[0][3], (int) BATEAU, "Test pour Destroyer(A0,A3) bateaux[0][3] == BATEAU");
	
	destroyer[0] = "A0";
	destroyer[1] = "D0";
	printf("Test : qu'un bateau ne peut pas etre place sur un bateau existant\n");
	entrerCoordonneesEtReformatter(destroyer, liste, 2, 4);
	placerBateau(liste, 4, bateaux);
	assertEquals(placerBateau(liste, 4, bateaux), 0, "Test placerBateau sur case occupee(A0,D0) == 0");
	
	printf("\n # FONCTION placerTir()\n");
	int tirs[TAILLE][TAILLE];
	initialiserTableau(tirs);
	Coordonnee c;
	initCoordonnee(0, 0, &c);
	assertEquals(placerTir(&c, tirs, bateaux), 1, "Test placerTir sur case non tiree A0 == 1");
	initCoordonnee(0, 0, &c);
	assertEquals(placerTir(&c, tirs, bateaux), 0, "Test placerTir sur case deja tiree A0 == 0");
	
	printf("\n # FONCTION verifierPresenceBateau()\n");
	assertEquals(verifierPresenceBateau(&c, bateaux), 1, "Test presence bateau case pleine A0 == 1");
	initCoordonnee(9, 9, &c);
	assertEquals(verifierPresenceBateau(&c, bateaux), 0, "Test presence bateau case vide J9 == 0");
	
	printf("\n # FONCTION partieTerminee()\n");
	assertEquals(partieTerminee(tirs, bateaux), 0, "Test tous bateaux on ete touche (faux).");
	tirs[0][0] = (int) TOUCHE;
	tirs[0][1] = (int) TOUCHE;
	tirs[0][2] = (int) TOUCHE;
	tirs[0][3] = (int) TOUCHE;
	assertEquals(partieTerminee(tirs, bateaux), 1, "Test tous bateaux on ete touche (vrai)");
	
	printf("\n # FONCTION radar()\n");
	initialiserTableau(bateaux);
	initialiserTableau(tirs);
	
	Coordonnee liste2[4];
	char* destroyer2[2];
	destroyer2[0] = "A0";
	destroyer2[1] = "A3";
	entrerCoordonneesEtReformatter(destroyer2, liste2, 2, 4);
	placerBateau(liste2, 4, bateaux);
	
	Coordonnee d, e, f, g, h;
	initCoordonnee(2, 2, &d);
	initCoordonnee(1, 2, &e);
	initCoordonnee(9, 9, &f);
	initCoordonnee(3, 2, &g);
	initCoordonnee(0, 6, &h);
	
	assertEquals(superRadar(&d, bateaux), 2, "Test radar proche.");
	assertEquals(superRadar(&e, bateaux), 1, "Test radar proche.");
	assertEquals(superRadar(&f, bateaux), 0, "Test radar loin.");
	assertEquals(superRadar(&g, bateaux), 3, "Test radar proche.");
	assertEquals(superRadar(&h, bateaux), 3, "Test radar proche.");
	
}