#ifndef COORDONNEES
#define COORDONNEES

#include <stdio.h>
#include <string.h>
#include "unittest.h"
#include "proprietes.cpp"

typedef struct Coordonnee Coordonnee;
struct Coordonnee {
	int y;
	int x;
};

void initCoordonnee(int i, int j, Coordonnee* c);
void initCoordonnees(Coordonnee x[], int n);
int entrerCoordonnee(char* entree, Coordonnee* c);
int entrerCoordonnees(char** entree, Coordonnee cible[], int nombre);
int entrerCoordonneesEtReformatter(char** entree, Coordonnee cible[], int nombre, int reformattage);
int peutReformatterEntree(char** entree, int nombre);

void testsCoordonnees();

#endif