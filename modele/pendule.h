#ifndef _PENDULE_
#define _PENDULE_

#include "../donnees/constantes.h"

struct Pendule_t {
    double masse;
    double longueur;
    
    double theta_actuel;
    double theta_intermed;
};
typedef struct Pendule_t pendule_t;

pendule_t penduleCreation(double masse, double longueur, double theta_actuel, double theta_intermed);
double penduleThetaPremier(pendule_t p1, pendule_t p2);
double penduleThetaSecond(pendule_t p1, pendule_t p2);
void penduleEvolution(pendule_t *p1, pendule_t *p2);
void penduleAffiche(pendule_t p, int i);
#endif
