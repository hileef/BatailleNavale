#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE 5

void afficherTableau(int tableau[TAILLE][TAILLE], int taille);
void demander(char* s, char* t, int n);
void nettoyerAffichage();
char indiceLettre(int x);

static void glup(char* t, int n);
static void vidange();

static char** EUStringToStringTable(char* s, char sep, int* length);
static int EUcountSeparators(char* s, int size, char separator);

// LES FONCTIONS CI-DESSOUS SONT DISPONIBLES POUR L'UTILISATEUR

void demander(char* s, char* t, int n) {
	printf("%s", s);
	glup(t, n);
}

char** demanderTableau(char* s, int* n) {
	printf("%s", s);
	char target[100];
	glup(target, 100);
	return EUStringToStringTable(target ,' ', n);
}

void nettoyerAffichage() {
	#ifdef _WIN32	// If we are compiling on windows
	system("CLS");
	#else			// If we are compiling for linux/unix
	system("clear");
	#endif
}

void afficherTableau(int tableau[TAILLE][TAILLE], int taille) {
	int i, j;

	printf("    ");
	for(i = 0; i < taille; i++)
		printf(" %d ", i);
	printf("\n    ");
	for(i = 0; i < taille; i++)
		printf(" - ");
	printf("\n");
	for(i = 0; i < taille; i++) {
		printf(" %c -", indiceLettre(i));
		for(j = 0; j < taille; j++)
			printf(" %c ", tableau[i][j]);
		printf("\n");
	}

	printf("\n");
}

char indiceLettre(int x) {
	return ('A' + x);
}


// FONCTIONS PRIVEES, NON DISPONIBLES POUR L'UTILISATEUR

static void glup(char* t, int n) {
	fgets(t, n, stdin);
	(t)[strlen(t) - 1] = '\0';
}
static void vidange() {
	char c;
	while((c = getchar()) != '\0' && c != EOF && c != '\n');
}

// Parses String to String table using separator sep
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

// Counts occurence of character separator in string
static int EUcountSeparators(char* s, int size, char separator) {
	int i, n;
	for(i = n = 0; i < size; i++)
		if(s[i] == separator) n++;
	return n;
}