#include "graphe.h"

	// Création et initialisation

int grapheCreation(grapheT * graphe, int nombre)
	{
		//	Création du graphe de la foule

	pointsT *iter;
	(*graphe).premier=NULL;
	(*graphe).premier=pointCreationGraphe(nombre);

	if((*graphe).premier!=NULL)
		{
		fprintf(stderr, "Graphe créé\n");
		}
	else
		{
		fprintf(stderr, "Echec de pointCreationGraphe\n");
		}

	iter=(*graphe).premier;
	do
		{
		iter->xm=LARGEUR/2;
		iter->ym=HAUTEUR/2;
		}
	while(iter!=(*graphe).premier);

	return 0;
	}

void grapheSuppression(grapheT * graphe)
	{
	pointSupprime(&(*graphe).premier);
	printf("Graphe supprimé\n");
	}

int grapheInitialisation(SDL_Renderer *rendu, grapheT * graphe)
{
	//SDL_Texture *texture = 0;
	//(*graphe).texture = 0;
	//SDL_Surface *image = 0;
	//(*graphe).image = 0;
	(*graphe).image = SDL_LoadBMP("mur.bmp");
	if (!(*graphe).image)
		{
		fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
		return 0;
		}
 
	(*graphe).texture = SDL_CreateTextureFromSurface(rendu, (*graphe).image);
	SDL_FreeSurface((*graphe).image);
	if ((*graphe).texture == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	return 0;
}

	// Dessin 
void grapheMur(SDL_Renderer *rendu, grapheT * graphe)
	{
	int i;
	SDL_Rect coordonnee = {0, 0, 12, 12};
	for(i=0;i<300;i+=12)
		{
		coordonnee.x = LARGEUR/8 + i;
		coordonnee.y = HAUTEUR/4 + i;
		SDL_RenderCopy(rendu, (*graphe).texture, NULL, &coordonnee);
		}

	return;
	}
void grapheHumain(SDL_Renderer *rendu, grapheT * graphe)
	{
	int i;
	SDL_Rect coordonnee = {0, 0, 12, 12};
	for(i=0;i<300;i+=12)
		{
		coordonnee.x = LARGEUR/8 + i;
		coordonnee.y = HAUTEUR/4 + i;
		SDL_RenderCopy(rendu, (*graphe).texture, NULL, &coordonnee);
		}

	return;
	}
/*
void grapheHumain(SDL_Renderer *rendu, graphe_t p) {    
	int x1 = p.coord1.x;
	int y1 = p.coord1.y;

	int x2 = p.coord2.x;
	int y2 = p.coord2.y;

	SDLS_affiche_image("humain.bmp",rendu,x1-4,y1-4);

	SDLS_affiche_image("humain.bmp",rendu,x2-4,y2-4);

	SDLS_affiche_image("humain.bmp",rendu,LARGEUR/2,HAUTEUR/2);

	return;
	}
	// Dessin 
void grapheTrait(SDL_Renderer *rendu, graphe_t p) {    
	int x1 = p.coord1.x;
	int y1 = p.coord1.y;

	int x2 = p.coord2.x;
	int y2 = p.coord2.y;

	int xoffset = 1;

	SDL_Point graphe1[3] = {
		{LARGEUR/2, HAUTEUR/2},
		{x1,    y1},
		{x2,    y2}
	};

	SDL_Point graphe2[3] = {
		{LARGEUR/2 + xoffset, HAUTEUR/2},
		{x1 + xoffset,    y1},
		{x2 + xoffset,    y2}
	};

	SDL_RenderDrawLines(rendu, graphe1, 3);
	SDL_RenderDrawLines(rendu, graphe2, 3);

	return;
	}
*/

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

int SDLS_affiche_image(char * fname,SDL_Renderer * rendu, int x, int y) 
{
	SDL_Texture * texture = 0;
	SDL_Rect coordonnee;

	texture = SDLS_loadTexture(fname,rendu);
	if (texture == 0) return 3;

	// Récupération de la taille de la texture 
	SDL_QueryTexture(texture, NULL, NULL, &coordonnee.w, &coordonnee.h);

	// Centrage
	coordonnee.x = x; //(WIDTH - dst.w)/2;
	coordonnee.y = y; //(HEIGHT- dst.h)/2;

	// Affichage
	SDL_RenderCopy(rendu, texture, NULL, &coordonnee);
	//SDL_RenderPresent(ren);
	return 0;
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
