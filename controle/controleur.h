#ifndef _CONTROLEUR_
#define _CONTROLEUR_

#include "../graphisme/graphe.h"

typedef struct ControleurT controleurT;
struct ControleurT {
	interfaceT interface;
	interfaceT reglage;
	grapheT graphe;
};


int controleurInitialisation(controleurT * controleur);

int controleurSimulation(controleurT * controleur);

int controleurDestruction(controleurT * controleur);

#endif
