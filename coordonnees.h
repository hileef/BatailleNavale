#ifndef COORDONNEES
#define COORDONNEES

struct Coordonnee {
	int y;
	int x;
};
typedef struct Coordonnee Coordonnee;

enum Orientation {VERTICAL = 1, HORIZONTAL = 2};
enum Variation {CROISSANT = 1, DECROISSANT = 2};

void	setY(Coordonnee* c, int y);
void	setX(Coordonnee* c, int x);
int 	getY(Coordonnee* c);
int 	getX(Coordonnee* c);

bool 	egal(Coordonnee* a, Coordonnee* b);

void 	initCoordonnee(Coordonnee* c);
void 	initCoordonnee(Coordonnee* c, int i, int j);
bool 	initCoordonnee(Coordonnee* c, const char* texte);

int 	initSuiteCoordonnees(Coordonnee tableau_coordonnees[], int n);
int 	initSuiteCoordonnees(Coordonnee tableau_coordonnees[], int n, int i, int j);
int 	initSuiteCoordonnees(Coordonnee tableau_coordonnees[], int n, char** textes);
int 	initSuiteCoordonnees(Coordonnee tableau_coordonnees[], int n, const char* texte);

// Les prototypes privés
static bool validerCoordonnee(char y, char x, Coordonnee *c);
static int  orientationAlignement(Coordonnee tableau_coordonnees[], int nombre_coordonnees);
static int  variationEtOrdre(Coordonnee tableau_coordonnees[], int nombre_coordonnees, int orientation);
static int  validerSuiteCoordonnees(Coordonnee tableau_coordonnees[], int nombre_coordonnees);

static int  etendueSuiteCoordonnees(char** entree, int nombre_coordonnees);
static int  etendueSuiteCoordonnees(Coordonnee* a, Coordonnee* b);
static void etendreSuiteCoordonnees(Coordonnee tableau_coordonnees[], int etendue);

// Les tests
void 	testsCoordonnees();

#endif
