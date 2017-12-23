#include "../projection/projection.h"

int projectionPremierX(pendule_t p1) {
    return (int)(LARGEUR / 2 - sin(p1.theta_actuel) * p1.longueur);
}

int projectionPremierY(pendule_t p1) {
    return (int)(HAUTEUR / 2 + cos(p1.theta_actuel) * p1.longueur);
}

int projectionSecondX(pendule_t p1, pendule_t p2) {
    return (int)(projectionPremierX(p1) - sin(p2.theta_actuel) * p2.longueur);
}

int projectionSecondY(pendule_t p1, pendule_t p2) {
    return (int)(projectionPremierY(p1) + cos(p2.theta_actuel) * p2.longueur);
}

void projectionPendules(pendule_t *p1, pendule_t *p2, points_t *p)
{
    p->coord1.x = (int)projectionPremierX(*p1);
    p->coord1.y = (int)projectionPremierY(*p1);
    
    p->coord2.x = (int)projectionSecondX(*p1, *p2);
    p->coord2.y = (int)projectionSecondY(*p1, *p2);
}

