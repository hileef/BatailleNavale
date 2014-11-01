/*  *** CLI.C ***

Ce fichier contient toute les fonctions relatives à la ligen de commande,
c'est à dire (récupération d'informations et affichage, entrées & sorties).

*/

// Directives de préprocesseur
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proprietes.c"

// Les prorotypes publics
void afficherTableau(int tableau[TAILLE][TAILLE]);
void demander(char* s, char* t, int n);
void nettoyerAffichage();
char lettreDeChiffre(int x);

// Les prorotypes privés
static void glup(char* t, int n);
static void vidange();
static char** EUStringToStringTable(char* s, char sep, int* length);
static int EUcountSeparators(char* s, int size, char separator);

// DEMANDER 
// equivalent de scanf, mais passe par fgets pour plus de sécurité.
void demander(char* s, char* t, int n) {
	printf("%s", s);
	glup(t, n);
}

// DEMANDER TABLEAU
// equivalent de scanf suivi de l'equivalent de la
// fonction split de Javascript utilisée avec ' '
// ATTENTION : CETTE VERSION UTILISE EUStringToStringTable. >> sera bientôt remplacé.
char** demanderTableau(char* s, int* n) {
	printf("%s", s);
	char target[100];
	glup(target, 100);
	return EUStringToStringTable(target ,' ', n);
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
		printf(" - ");
	printf("\n");
	for(i = 0; i < TAILLE; i++) {
		printf(" %c -", lettreDeChiffre(i));
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

// PRIVÉ ** EUStringToStringTable
// Parses String to String table using separator sep
// WARNING: THIS USES MALLOC. ALLOCATED RESOURCES MUST BE FREED.
static char** EUStringToStringTable(char* s, char sep, int* length) {
	int i, j, k, l, m, n, N;
	char** table;
	char* word;
	
	i = j = k = l = m = n = 0;

	N = strlen(s);
	n = EUcountSeparators(s, N, sep) + 1;
	table = (char**) malloc(sizeof(char*) * n);
	word = (char*) malloc(sizeof(char) * (k+1));

	for(i = 0; i <= N; i++) {
		j++;
		if((s[i] == sep || s[i] == '\0') && i != 0) {
			k = j - 1;
			word = (char*) malloc(sizeof(char) * (k));
			for(l = 0; l < k; l++)
				word[l] =  s[(i - k) + l];
			word[k] = '\0';
			table[m] = word;
			j = 0;
			m++;
		}
	}

	*length = n;
	return table;

}

// PRIVÉ ** EUcountSeparators
// Counts occurences of character separator in string
static int EUcountSeparators(char* s, int size, char separator) {
	int i, n;
	for(i = n = 0; i < size; i++)
		if(s[i] == separator) n++;
	return n;
}