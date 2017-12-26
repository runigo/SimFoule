#ifndef _HUMAIN_
#define _HUMAIN_

#include "../modele/vecteur.h"

struct HumainT {
    bool mur;
    bool sortie;
    vecteurT sens;
    int distance;
};
typedef struct HumainT humainT;

double humainInitialise(humainT * humain);
double humainThetaSecond(humainT * humain);
int humainCreationMur(humainT * humain, int X, int Y);
int humainCreationSortie(humainT * humain, int X, int Y);
bool humainMur(humainT * humain, int X, int Y);
bool humainSortie(humainT * humain, int X, int Y);
#endif
