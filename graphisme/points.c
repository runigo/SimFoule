#include "points.h"

	// Création et initialisation
points_t pointsCreation(void)
{
    points_t p;

    p.coord1.x = 0;
    p.coord1.y = 0;
    p.coord2.x = 0;
    p.coord2.y = 0;
    
    return p;
}

	// Dessin 
void pointsMur(SDL_Renderer *rendu, points_t p) {    
	int x1 = p.coord1.x;
	int y1 = p.coord1.y;

	int x2 = p.coord2.x;
	int y2 = p.coord2.y;

	int xoffset = 1;

	// SDL_SetRenderDrawColor(rendu, 0, 0, 0, SDL_ALPHA_OPAQUE);


	// Rectangle SDL
	SDL_Rect rectangle;

	//texture = SDLS_loadTexture("particule.bmp",rendu);
	//SDL_Texture* SDLS_loadTexture(char * filename, SDL_Renderer *ren){
	SDL_Texture *texture = 0;
	SDL_Surface *image = 0;
	image = SDL_LoadBMP("particule.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if (texture == 0)
		{
		fprintf(stderr,"Erreur creation texture : %s\n",SDL_GetError());
		return;
		}
	//return texture;
  
	// Récupération de la taille de la texture 
	//SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);

	// Centrage
	rectangle.x = x2-2; //(WIDTH - dst.w)/2;
	rectangle.y = y2-2; //(HEIGHT- dst.h)/2;
	SDLS_affiche_image("particule.bmp",rendu,x2-2,y2-2);

	// Affichage
	//SDL_RenderCopy(rendu, texture, NULL, &rectangle);

	// Centrage
	rectangle.x = x1-2; //(WIDTH - dst.w)/2;
	rectangle.y = y1-2; //(HEIGHT- dst.h)/2;
	SDLS_affiche_image("particule.bmp",rendu,x1-2,y1-2);

	// Affichage
	//SDL_RenderCopy(rendu, texture, NULL, &rectangle);

	SDL_Point points1[3] = {
		{LARGEUR/2, HAUTEUR/2},
		{x1,    y1},
		{x2,    y2}
	};

	SDL_Point points2[3] = {
		{LARGEUR/2 + xoffset, HAUTEUR/2},
		{x1 + xoffset,    y1},
		{x2 + xoffset,    y2}
	};

	SDL_RenderDrawLines(rendu, points1, 3);
	SDL_RenderDrawLines(rendu, points2, 3);

	// Affichage
	SDL_RenderCopy(rendu, texture, NULL, &rectangle);
	//SDL_RenderPresent(ren);

	return;
	}

	// Dessin 
void pointsPendules(SDL_Renderer *rendu, points_t p) {    
	int x1 = p.coord1.x;
	int y1 = p.coord1.y;

	int x2 = p.coord2.x;
	int y2 = p.coord2.y;

	int xoffset = 1;

	// SDL_SetRenderDrawColor(rendu, 0, 0, 0, SDL_ALPHA_OPAQUE);


	// Rectangle SDL
	SDL_Rect rectangle;

	//texture = SDLS_loadTexture("particule.bmp",rendu);
	//SDL_Texture* SDLS_loadTexture(char * filename, SDL_Renderer *ren){
	SDL_Texture *texture = 0;
	SDL_Surface *image = 0;
	image = SDL_LoadBMP("particule.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if (texture == 0)
		{
		fprintf(stderr,"Erreur creation texture : %s\n",SDL_GetError());
		return;
		}
	//return texture;
  
	// Récupération de la taille de la texture 
	//SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);

	// Centrage
	rectangle.x = x2-2; //(WIDTH - dst.w)/2;
	rectangle.y = y2-2; //(HEIGHT- dst.h)/2;
	SDLS_affiche_image("particule.bmp",rendu,x2-2,y2-2);

	// Affichage
	//SDL_RenderCopy(rendu, texture, NULL, &rectangle);

	// Centrage
	rectangle.x = x1-2; //(WIDTH - dst.w)/2;
	rectangle.y = y1-2; //(HEIGHT- dst.h)/2;
	SDLS_affiche_image("particule.bmp",rendu,x1-2,y1-2);

	// Affichage
	//SDL_RenderCopy(rendu, texture, NULL, &rectangle);

	SDL_Point points1[3] = {
		{LARGEUR/2, HAUTEUR/2},
		{x1,    y1},
		{x2,    y2}
	};

	SDL_Point points2[3] = {
		{LARGEUR/2 + xoffset, HAUTEUR/2},
		{x1 + xoffset,    y1},
		{x2 + xoffset,    y2}
	};

	SDL_RenderDrawLines(rendu, points1, 3);
	SDL_RenderDrawLines(rendu, points2, 3);

	// Affichage
	SDL_RenderCopy(rendu, texture, NULL, &rectangle);
	//SDL_RenderPresent(ren);

	return;
	}

void pointsChemin(SDL_Renderer *rendu, points_t p) {
	static SDL_Point point[2048] = {{0}};
	static int       i = 0;

	point[i].x = p.coord2.x;
	point[i].y = p.coord2.y;

	if(++i > 2048)
		i = 0;

	SDL_SetRenderDrawColor(rendu, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(rendu, point, 2046);
	}

//////////////////////////////////////////////////////////////////////////

//https://deptinfo-ensip.univ-poitiers.fr/ENS/doku/doku.php/stu:progc:sdls

// Version 1.1

SDL_Texture* SDLS_loadTexture(char * filename, SDL_Renderer *ren){
        SDL_Texture *texture = 0;
        SDL_Surface *image = 0;
        image = SDL_LoadBMP(filename);
        if (!image)
          {
          fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
          return 0;
          }
 
        texture = SDL_CreateTextureFromSurface(ren, image);
        SDL_FreeSurface(image);
        if (texture == 0)
          {
          fprintf(stderr,"Erreur creation texture : %s\n",SDL_GetError());
          return 0;
          }
        return texture;
}

Uint32 SDLS_couleur(int r, int g, int b)
	{
	return (((r<<8)+ g)<<8 )+ b;
	}

int SDLS_getpixels(SDL_Renderer * ren, Uint32* pixels, int w, int h)
	{
	int res;
	int width=w;
	(void)h;//, height=h;
	//SDL_RenderGetLogicalSize(ren,&width,&height);
	//printf("%d %d\n",width,height);
	res = SDL_RenderReadPixels(ren,NULL,SDL_PIXELFORMAT_ARGB8888,pixels,width*sizeof(Uint32));
	if (res<0) 
		{
		fprintf(stderr,"Erreur getpixels : %s\n",SDL_GetError());
		return -1;
		}
	return 0;
	}
int  SDLS_putpixels(SDL_Renderer * ren, Uint32* pixels, int w, int h) 
	{
	SDL_Texture * tex;
	int width=w, height=h;
	//SDL_RenderGetLogicalSize(ren,&width,&height);
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING, width, height);
	SDL_UpdateTexture(tex, NULL, pixels, width * sizeof (Uint32));
	SDL_RenderCopy(ren,tex, NULL, NULL);
	SDL_RenderPresent(ren);
	SDL_DestroyTexture(tex);
	return 0;
	}

void SDLS_affiche_image(char * fname,SDL_Renderer * ren, int x, int y) 
{
	SDL_Texture * tex = 0;
	SDL_Rect dst;

	tex = SDLS_loadTexture(fname,ren);
	if (tex == 0) return;

	// Récupération de la taille de la texture 
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

	// Centrage
	dst.x = x; //(WIDTH - dst.w)/2;
	dst.y = y; //(HEIGHT- dst.h)/2;

	// Affichage
	SDL_RenderCopy(ren, tex, NULL, &dst);
	//SDL_RenderPresent(ren);
}

int SDLS_init(int w, int h, SDL_Window **win, SDL_Renderer **ren)
	{
	/* Initialisation de la SDL. Si ça se passe mal, on quitte */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr,"Erreur initialisation\n");
		return -1;
	}
	/* Création de la fenêtre et du renderer */
	SDL_CreateWindowAndRenderer(w,h, 0, win, ren); // SDL_WINDOW_SHOWN|SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,&win,&ren);
	if (!*win || !*ren) 
		{
		fprintf(stderr,"Erreur à la création des fenêtres\n");
		SDL_Quit();
	return -1;
	}
	/* Affichage du fond noir */
	SDL_SetRenderDrawColor(*ren, 0, 0, 0, 255);
	SDL_RenderClear(*ren);

	SDL_RenderPresent(*ren);

	return 0;
}
