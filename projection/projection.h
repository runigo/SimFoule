#ifndef _PROJECTION_
#define _PROJECTION_

#include "../modele/pendule.h"
#include "../graphisme/points.h"

int projectionPremierX(pendule_t p1);
int projectionPremierY(pendule_t p1);
int projectionSecondX(pendule_t p1, pendule_t p2);
int projectionSecondY(pendule_t p1, pendule_t p2);
void projectionPendules(pendule_t *p1, pendule_t *p2, points_t *p);

#endif
