#ifndef COORDONNEES
#define COORDONNEES

struct Coordonnee {
	int y;
	int x;
};
typedef struct Coordonnee Coordonnee;

void	setY(Coordonnee* c, int y);
void	setX(Coordonnee* c, int x);
int 	getY(Coordonnee* c);
int 	getX(Coordonnee* c);

bool 	egal(Coordonnee* a, Coordonnee* b);

void 	initCoordonnee(Coordonnee* c);
void 	initCoordonnee(Coordonnee* c, int i, int j);
bool 	initCoordonnee(Coordonnee* c, const char* texte);

int 	initSuiteCoordonnees(Coordonnee cible[], int n);
int 	initSuiteCoordonnees(Coordonnee cible[], int n, int i, int j);
int 	initSuiteCoordonnees(Coordonnee cible[], int n, char** textes);
int 	initSuiteCoordonnees(Coordonnee cible[], int n, const char* texte);

// Les prototypes privés
static bool validerCoordonnee(char y, char x, Coordonnee *c);
static int  sontAlignees(Coordonnee cible[], int nombre);
static int  sontALaSuite(Coordonnee cible[], int nombre, int orientation);
static int  validerSuiteCoordonnees(Coordonnee cible[], int nombre);

static int  etendueSuiteCoordonnees(char** entree, int nombre);
static int  etendueSuiteCoordonnees(Coordonnee* a, Coordonnee* b);
static void etendreSuiteCoordonnees(Coordonnee cible[], int etendue);

// Les tests
void 	testsCoordonnees();

#endif