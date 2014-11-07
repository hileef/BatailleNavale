#include "cli.h"
#include "proprietes.c"
#include "coordonnees.h"


// Les prototypes
void initialiserTableau(int t[TAILLE][TAILLE]);
void demanderBateaux(int bateauxJoueur1[TAILLE][TAILLE], char* nom);
int placerBateau(Coordonnee entrees[], int taille, int bateaux[TAILLE][TAILLE]);
int validercoordonnees(char** coord, int nombre);
void demanderTir(int tirsJoueur2[TAILLE][TAILLE], int bateauxJoueur1[TAILLE][TAILLE], char* nom);
int placerTir(Coordonnee *c, int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]);
int verifierPresenceBateau(Coordonnee *c, int bateaux[TAILLE][TAILLE]);
int partieTerminee(int tirs[TAILLE][TAILLE], int bateaux[TAILLE][TAILLE]);
void demanderNomsJoueurs(char* j1, char* j2, int taille);
int jouerPartie();

