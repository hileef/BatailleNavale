/*  *** PROPRIETES.C ***

Ce fichier contient les directives de preprocesseur communes aux proprietes du jeu,
 de façon a ne pas avoir a les copier/coller dans chaque fichier du jeu, les modifier
 plusieurs fois au travers des fichiers, etc.

*/

// Verifie que ces directives n'ont pas deja etes lancees.
#ifndef PROPRIETES

// Sinon, les definir comme ayant ete lancees
#define PROPRIETES

// *** LES PROPRIETES ***
#define TAILLE 10
#define TAILLE_BATEAU 4
#define NOMBRE_BATEAUX 2

#define BATEAU 'B'
#define VIDE '.'
#define TOUCHE 'X'
#define COULE '#'
#define PLOUF 'O'
#define RAYON_RADAR 2
#define TAILLE_ENTREE 100

#define SYS_VERSION 2
// SYSTEME VERSION 2 -> DEPEDENCIES

const int TAILLES[] = {0, 1, 2, 1, 1, 0};
const int TAILLES_MAX = 6;

// Sortie de la condition que ces directives n'ont pas deja etes lancees.
#endif