/*  *** CLI.H ***

Ce fichier contient toute les fonctions relatives à la ligen de commande,
c'est à dire (récupération d'informations et affichage, entrées & sorties).

*/

#ifndef CLI
#define CLI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coordonnees.h"
#include "proprietes.c"

// Les prorotypes publics
void afficherTableau(int tableau[TAILLE][TAILLE]);
void demander(char* s, char* t, int n);
void nettoyerAffichage();
char lettreDeChiffre(int x);
int demanderCoordonnee(char* s, Coordonnee* cible);
int demanderCoordonnees(char* s, Coordonnee cible[], int tailleMax);

#endif