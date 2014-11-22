/*  *** CLI.H ***

Ce fichier contient toute les fonctions relatives a la ligen de commande,
c'est a dire (recuperation d'informations et affichage, entrees & sorties).

*/

#ifndef CLI
#define CLI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coordonnees.h"
#include "proprietes.cpp"

// Les prorotypes publics



void 	pause();
void 	debug(const char* s);

void 	nettoyerAffichage();
void 	couleur(int x);

void 	afficher(const char* s);
void 	afficherAccueil();

void 	demander(const char* s, char* t, int n);
void 	demander(const char* s, char* t);

int 	demanderCoordonnee(const char* s, Coordonnee* cible);
int 	demanderCoordonnees(const char* s, Coordonnee cible[], int tailleMax);

void 	split(const char* s, char** cible, int taille);
void	allocSuperString(char*** t, int squared);
void	freeSuperString(char*** t, int squared);

void 	intToString(char* s, int x);
void 	charToString(char* s, char x);
char 	lettreDeChiffre(int x);

#endif