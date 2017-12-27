#ifndef _GRAPHE_
#define _GRAPHE_

#include "interface.h"
#include "../modele/etage.h"
#include "../graphisme/points.h"

struct GrapheT {
	SDL_Texture *texture;
	SDL_Surface *image;

	pointsT * premier;

	etageT * etage;
};
typedef struct GrapheT grapheT;

int grapheCreation(grapheT * graphe, int nombre);
int grapheInitialisation(SDL_Renderer *rendu, grapheT * graphe);
void grapheSuppression(grapheT * graphe);
void grapheMur(SDL_Renderer *rendu, grapheT * graphe);
void grapheHumain(SDL_Renderer *rendu, grapheT * graphe);

//https://deptinfo-ensip.univ-poitiers.fr/ENS/doku/doku.php/stu:progc:sdls

// Version 1.1
SDL_Texture* SDLS_loadTexture(char * filename, SDL_Renderer *ren);
int SDLS_affiche_image(char * fname,SDL_Renderer * ren, int x, int y);
int SDLS_init(int w, int h, SDL_Window **win, SDL_Renderer **ren);
int SDLS_putpixels(SDL_Renderer * ren, Uint32* pixels,int w, int h);
int SDLS_getpixels(SDL_Renderer * ren, Uint32* pixels,int w, int h);

#endif
