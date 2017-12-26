#ifndef _ETAGE_
#define _ETAGE_

#include "../modele/cellule.h"

struct EtageT {
	celluleT cellule[BATIMENT][BATIMENT];	//	Un étage est un tableau de cellules
};
typedef struct EtageT etageT;

int etageInitialise(etageT * etage);
int etageCreationMur(etageT * etage, int X, int Y);
int etageCreationSortie(etageT * etage, int X, int Y);

int etageCalculeDistance(etageT * etage);
int etageCalculeSens(etageT * etage);

int etageAffiche(etageT * etage);
#endif
