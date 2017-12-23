#ifndef _INTERFACE_
#define _INTERFACE_

#include "../donnees/constantes.h"

#include <SDL2/SDL.h>

typedef struct InterfaceT interfaceT;
struct InterfaceT {
	SDL_Window *fenetre;
	SDL_Renderer *rendu;
	SDL_Event evenement;
    bool continu;
	int fond;
};

int interfaceInitialisation(interfaceT * interface);
int interfaceNettoyage(interfaceT * interface);
int interfaceMiseAJour(interfaceT * interface);
int interfaceDestruction(interfaceT * interface);
#endif
