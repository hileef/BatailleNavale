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
#include "plateau.h"

// Les prorotypes publics
void pause();
void debug(char* s);
void afficher(char* s);
void afficherAccueil();
void afficherAccueil_v2();
void afficherTableau(int tableau[TAILLE][TAILLE]);
void afficherPlateau(Plateau* p);
void demander(char* s, char* t, int n);
void demander(char* s, char* t);
void nettoyerAffichage();
void couleur(int x);
char lettreDeChiffre(int x);
int demanderCoordonnee(char* s, Coordonnee* cible);
int demanderCoordonnees(char* s, Coordonnee cible[], int tailleMax);
void intToString(char* s, int x);
void afficherBateauxDisponibles();

#endif