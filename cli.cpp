/*  *** CLI.C ***

Ce fichier contient toute les fonctions relatives a la ligen de commande,
c'est a dire (recuperation d'informations et affichage, entrees & sorties).

*/

// Directives de preprocesseur
#include "cli.h"
#include "plateau.h"

// Les prorotypes prives
static void glup(char* t, int n);
static void vidange();
static void tokky(char* s, char** cible, int length);
static int compterEspaces(char* s);
static void split(char* s, char** cible, int taille);



int demanderCoordonnee(char* s, Coordonnee* cible) {
	char texte[100];
	demander(s, texte, 100);
	return initCoordonnee(cible, texte);
}

int demanderCoordonnees(char* s, Coordonnee cible[], int tailleMax) {
	int i, n, x;
	char entree[100];

	demander(s, entree, 100);
	n = compterEspaces(entree) + 1;
	n = (n > tailleMax) ? tailleMax : n;

	char **splitte;
	splitte = (char**) malloc(sizeof(char*) * n);
	for(i = 0; i < n; i++)
		splitte[i] = (char*) malloc(sizeof(char) * 100);

	split(entree, splitte, n);

	x = initSuiteCoordonnees(cible, n, splitte);
	
	for(i = 0; i < n; i++)
		free(splitte[i]);
	free(splitte);

	return x;
}

// DEMANDER 
// equivalent de scanf, mais passe par fgets pour plus de securite.
void demander(char* s, char* t) {
	demander(s, t, TAILLE_ENTREE);
}
void demander(char* s, char* t, int n) {
	printf("%s", s);
	glup(t, n);
}

void afficher(char* s) {
	printf("%s", s);
}

void debug(char* s) {
	printf("DEBUG : %s \n", s);
}

// NETTOYER AFFICHAGE
// equivalent de CLS sur windows et clear sur linux, vide
// l'affichage de la console
void nettoyerAffichage() {
	#ifdef _WIN32	// If we are compiling on windows
	system("CLS");
	#else			// If we are compiling for linux/unix
	system("clear");
	#endif
	printf("              #### SUPER BATAILLE NAVALE :D #### \n\n");
}

// AFFICHER TABLEAU
// Affiche un tableau a deux dimensions de taille TAILLExTAILLE
// a la console.
void afficherTableau(int tableau[TAILLE][TAILLE]) {
	int i, j;

	printf("    ");
	for(i = 0; i < TAILLE; i++)
		printf(" %d ", i);
	printf("\n    ");
	for(i = 0; i < TAILLE; i++)
		printf("   ");
	printf("\n");
	for(i = 0; i < TAILLE; i++) {
		printf(" %c  ", lettreDeChiffre(i));
		for(j = 0; j < TAILLE; j++)
			printf(" %c ", tableau[i][j]);
		printf("\n\n");
	}

	printf("\n");
}

void afficherPlateau(Plateau* p) {
	int i, j, taille = p->taille;

	printf("    ");
	for(i = 0; i < taille; i++)
		printf(" %d ", i);
	printf("\n    ");
	for(i = 0; i < taille; i++)
		printf("   ");
	printf("\n");
	for(i = 0; i < taille; i++) {
		printf(" %c  ", lettreDeChiffre(i));
		for(j = 0; j < taille; j++)
			printf(" %c ", getCase(p, i, j));
		printf("\n\n");
	}

	printf("\n");
}

// Conversion entre 'A' et son equivalent selon l'encodage
char lettreDeChiffre(int x) {
	return ('A' + x);
}
int chiffreDeLettre(char x) {
	return (x - 'A');
}

void intToString(char* s, int x) {
	sprintf(s, "%d", x);
}


// PRIVe ** GLUP
// fgets sans le charactere entree a la fin.
static void glup(char* t, int n) {
	fgets(t, n, stdin);
	(t)[strlen(t) - 1] = '\0';
}

// PRIVe ** VIDANGE
// Vide la flux stdin, peut causer une demande a l'utilisateur attendant entree.
static void vidange() {
	char c;
	while((c = getchar()) != '\0' && c != EOF && c != '\n');
}

// PROBLEMS TO FIX HERE : STD FUNCTION FAILS,
// MY FUNCTION BETTER BUT TO SIMPLIFY
static void split(char* s, char** cible, int taille) {
	int i, length;
	tokky(s, cible, taille);
}

// PRIVe ** compterEspaces
// Compte le nombre d'espaces trouves dans un string
static int compterEspaces(char* s) {
	int i, n, size = strlen(s);
	for(i = n = 0; i < size; i++)
		if(s[i] == ' ') n++;
	return n;
}

// new version of EUStringToStringTable, replaced to tokky
static void tokky(char* s, char** cible, int length) {
	int i, j, k, l, m, n, N;
	
	i = j = k = l = m = n = 0;

	N = strlen(s);
	n = length;

	for(i = 0; i <= N; i++) {
		j++;
		if((s[i] == ' ' || s[i] == '\0') && i != 0) {
			k = j - 1;
			for(l = 0; l < k; l++)
				cible[m][l] =  s[(i - k) + l];
			cible[m][k] = '\0';
			j = 0;
			m++;
		}
	}

}

void couleur(int x) {
	#ifdef _WIN32
	if(x == 1)
		system("COLOR 0A");
	else if(x == 2)
		system("COLOR 0B");
	else if(x == 3)
		system("COLOR 0A");
	else
		system("COLOR 3F");
	#endif
}

void afficherAccueil() {
	printf("                                                       .         \n");
	printf("         .                         .                  /|         \n");
	printf("        /|                  .     /|\\                /_|         \n");
	printf("       /_|                 /|    /_|_\\             ____|___      \n");
	printf("~~~  ____|___  ~~~~~~~~~~ / |   /__|__\\ ~~~~~~~~~~ \\______/ ~~~~~\n");
	printf("~~~~ \\______/ ~~~~~~~~~~ /__|  /___|___\\ ~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~ ____|______|_____ ~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \\_o_ _ _o_ _ _o_/ ~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ . ~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~ . ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   /|   ~~~~~~~~~\n");
	printf("~~~~~~~~   /|  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   /_|   ~~~~~~~~~\n");
	printf("~~~~~~~   /_|   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  ____|___  ~~~~~~~\n");
	printf("~~~~~~  ____|___  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \\______/   ~~~~~~\n");
	printf("~~~~~~  \\______/   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n\n\n");
	printf("Bonjour.\n");
	printf("Pour tester, tapez 'test' \n");
	printf("Pour jouer, tapez 'jeu'\n");
	printf("Pour quitter, tapez 'quitter' \n");
}


void afficherBateauxDisponibles() {
	int i;
	printf("Vous pouvez placer :\n");
	for(i = 0; i < TAILLES_MAX; i++)
		if(TAILLES[i] > 0)
			printf("%d bateaux de : %d cases \n", TAILLES[i], i + 1);
	
}

void pause() {
	char entree[50];
	demander("\n Appuyez sur Entrer pour continuer... ", entree, 50);
}