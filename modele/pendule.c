#include "../modele/pendule.h"

pendule_t penduleCreation(double masse, double longueur, double theta_actuel, double theta_intermed)
{
    pendule_t p;
    
    p.masse             = masse;
    p.longueur          = longueur;
    p.theta_actuel      = theta_actuel;
    p.theta_intermed    = theta_intermed;
    
    return p;
}

double penduleThetaPremier(pendule_t p1, pendule_t p2) {
    double m = p1.masse + p2.masse;
    
    double a = p2.masse * p1.longueur * p1.theta_intermed * p1.theta_intermed * sin(p2.theta_actuel - p1.theta_actuel) * cos(p2.theta_actuel - p1.theta_actuel);
    double b = p2.masse * G * sin(p2.theta_actuel) * cos(p2.theta_actuel - p1.theta_actuel);
    double c = p2.masse * p2.longueur * p2.theta_intermed * p2.theta_intermed * sin(p2.theta_actuel - p1.theta_actuel);
    double d = -m * G * sin(p1.theta_actuel);
    
    double e = (m * p1.longueur) - p2.masse * p1.longueur * cos(p2.theta_actuel - p1.theta_actuel) * cos(p2.theta_actuel - p1.theta_actuel);
    
    return (a + b + c + d) / e;

}

double penduleThetaSecond(pendule_t p1, pendule_t p2) {
    double m = p1.masse + p2.masse;
    
    double a = -p2.masse * p2.longueur * p2.theta_intermed * p2.theta_intermed * sin(p2.theta_actuel - p1.theta_actuel) * cos(p2.theta_actuel - p1.theta_actuel);
    double b = m * (G * sin(p1.theta_actuel) * cos(p2.theta_actuel - p1.theta_actuel) - p1.longueur * p1.theta_intermed * p1.theta_intermed * sin(p2.theta_actuel - p1.theta_actuel) - G * sin(p2.theta_actuel));
    double c = (m * p2.longueur) - p2.masse * p2.longueur * cos(p2.theta_actuel - p1.theta_actuel) * cos(p2.theta_actuel - p1.theta_actuel);
    
    return (a + b) / c;
}

void penduleEvolution(pendule_t *p1, pendule_t *p2) {
    float dt = 0.05;
    
    p1->theta_intermed += penduleThetaPremier(*p1, *p2) * dt;
    p2->theta_intermed += penduleThetaSecond(*p1, *p2) * dt;
    
    p1->theta_actuel += p1->theta_intermed * dt;
    p2->theta_actuel += p2->theta_intermed * dt;
}

void penduleAffiche(pendule_t p, int i) {
    printf("Pendulum %d:", i);
    
    printf("\n\t- Lenght: %.3lf\n", p.longueur);
    printf("\t- Mass: %.3lf\n\n", p.masse);
}

