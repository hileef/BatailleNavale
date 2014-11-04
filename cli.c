/*  *** CLI.C ***

Ce fichier contient toute les fonctions relatives à la ligen de commande,
c'est à dire (récupération d'informations et affichage, entrées & sorties).

*/

// Directives de préprocesseur
#include "cli.h"

// Les prorotypes privés
static void glup(char* t, int n);
static void vidange();
static void tokky(char* s, char** cible, int length);
static int compterEspaces(char* s);
static void split(char* s, char** cible, int taille);



int demanderCoordonnee(char* s, Coordonnee* cible) {
	char target[100];
	demander(s, target, 100);
	return entrerCoordonnee(target, cible);
}

int demanderCoordonnees(char* s, Coordonnee cible[], int tailleMax) {
	int i, n, r, x;
	char entree[100];

	demander(s, entree, 100);
	n = compterEspaces(entree) + 1;
	n = (n > tailleMax) ? tailleMax : n;

	char **splitte;
	splitte = malloc(sizeof(char*) * n);
	for(i = 0; i < n; i++)
		splitte[i] = malloc(sizeof(char) * 100);

	split(entree, splitte, n);
	
	r = peutReformatterEntree(splitte, n);
	x = entrerCoordonneesEtReformatter(splitte, cible, n, r);
	
	for(i = 0; i < n; i++)
		free(splitte[i]);
	free(splitte);

	return x;
}

// DEMANDER 
// equivalent de scanf, mais passe par fgets pour plus de sécurité.
void demander(char* s, char* t, int n) {
	printf("%s", s);
	glup(t, n);
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
	printf(" #### SUPER BATAILLE NAVALE :D #### \n\n");
}

// AFFICHER TABLEAU
// Affiche un tableau à deux dimensions de taille TAILLExTAILLE
// à la console.
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
		printf("\n");
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


// PRIVÉ ** GLUP
// fgets sans le charactère entrée à la fin.
static void glup(char* t, int n) {
	fgets(t, n, stdin);
	(t)[strlen(t) - 1] = '\0';
}

// PRIVÉ ** VIDANGE
// Vide la flux stdin, peut causer une demande à l'utilisateur attendant entrée.
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

// PRIVÉ ** compterEspaces
// Compte le nombre d'espaces trouvés dans un string
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