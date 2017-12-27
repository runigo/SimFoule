#include "controleur.h"

float reelAleatoire(float min, float max) {
    return min + (((float)rand() / (float)(RAND_MAX / (max - min))));
}


int controleurDestruction(controleurT * controleur)
	{
	interfaceDestruction(&(*controleur).interface);
	return 0;
	}

int controleurInitialisation(controleurT * controleur)
	{
	interfaceInitialisation(&(*controleur).interface);
	grapheInitialisation((*controleur).interface.rendu, &(*controleur).graphe);
	return 0;
	}

int controleurSimulation(controleurT * controleur)
{
    
	while((*controleur).interface.continu) {
		while(SDL_PollEvent(&(*controleur).interface.evenement))
			{
			if((*controleur).interface.evenement.type == SDL_QUIT)
				{
				(*controleur).interface.continu = false;
				}

			switch((*controleur).interface.evenement.type)
				{
				case SDL_QUIT:
					(*controleur).interface.continu = false;
					break;
				case SDL_KEYDOWN:
					switch((*controleur).interface.evenement.key.keysym.sym)
					{
					case SDLK_i:
					break;
					}
				break;
			}
		}
		// Évolution temporelle
	//penduleEvolution(&p1, &p2);        

		// Projection angle > entier
	//projectionPendules(&p1, &p2, &p);

	interfaceNettoyage(&(*controleur).interface);

	grapheMur((*controleur).interface.rendu, &(*controleur).graphe);
	//pointsMur((*controleur).interface.rendu, p);
	//pointsHumain((*controleur).interface.rendu, p);

	interfaceMiseAJour(&(*controleur).interface);

	SDL_Delay(5);
    }
    return 0;
}
