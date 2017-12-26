#ifndef _CELLULE_
#define _CELLULE_

#include "../modele/vecteur.h"

struct CelluleT {
    bool mur;
    bool sortie;
    vecteurT sens;
    int distance;
};
typedef struct CelluleT celluleT;

double celluleInitialise(celluleT * cellule);
int celluleCreationMur(celluleT * cellule, int X, int Y);
int celluleCreationSortie(celluleT * cellule, int X, int Y);
bool celluleMur(celluleT * cellule, int X, int Y);
bool celluleSortie(celluleT * cellule, int X, int Y);
#endif
