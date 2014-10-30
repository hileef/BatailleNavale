#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficherTableau(int** tableau, int taille);
void demander(char* s, char* t, int n);
void nettoyerAffichage();
char indiceLettre(int x);

static void glup(char* t, int n);
static void vidange();

// LES FONCTIONS CI-DESSOUS SONT DISPONIBLES POUR L'UTILISATEUR

void demander(char* s, char* t, int n) {
	printf("%s", s);
	glup(t, n);
}

void nettoyerAffichage() {
	#ifdef _WIN32	// If we are compiling on windows
	system("CLS");
	#else			// If we are compiling for linux/unix
	system("clear");
	#endif
}

void afficherTableau(int** tableau, int taille) {
	int i, j;

	printf("    ");
	for(i = 0; i < taille; i++)
		printf(" %d ", i);
	
	for(i = 0; i < taille; i++) {
		printf(" %c |", indiceLettre(i));
		for(j = 0; j < taille; j++)
			printf(" %d ", tableau[i][j]);
		printf("| %c \n", indiceLettre(i));
	}
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