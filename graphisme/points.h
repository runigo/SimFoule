#ifndef _POINTS_
#define _POINTS_

#include "interface.h"

struct Points_t {
    SDL_Point coord1;
    SDL_Point coord2;
};
typedef struct Points_t points_t;

points_t pointsCreation(void);
void pointsPendules(SDL_Renderer *rendu, points_t p);
void pointsChemin(SDL_Renderer *rendu, points_t p);

//https://deptinfo-ensip.univ-poitiers.fr/ENS/doku/doku.php/stu:progc:sdls

// Version 1.1
SDL_Texture* SDLS_loadTexture(char * filename, SDL_Renderer *ren);
void SDLS_affiche_image(char * fname,SDL_Renderer * ren, int x, int y);
int SDLS_init(int w, int h, SDL_Window **win, SDL_Renderer **ren);
int SDLS_putpixels(SDL_Renderer * ren, Uint32* pixels,int w, int h);
int SDLS_getpixels(SDL_Renderer * ren, Uint32* pixels,int w, int h);

#endif
