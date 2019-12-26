/*
Copyright décembre 2019, Stephan Runigo
runigo@free.fr
SimFoule 2.2  simulateur de foule
Ce logiciel est un programme informatique servant à simuler l'évacuation
d'une foule dans un batiment et à en donner une représentation graphique.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée. Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard l'attention de l'utilisateur est attirée sur les risques
associés au chargement, à l'utilisation, à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant des connaissances informatiques approfondies. Les
utilisateurs sont donc invités à charger et tester l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "textureSysteme.h"

int textureSystemeInitialisation(textureSystemeT * textureSysteme, affichageT * affichage)
	{
	int retour = 0;

	SDL_Surface *image = 0;

	image = SDL_LoadBMP("./image/mur.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, mur.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).mur = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).mur == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/mobile.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, mobile.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).mobile = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).mobile == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}
		// Activation de la transparence
	//SDL_BLENDMODE_NONE || SDL_BLENDMODE_BLEND || SDL_BLENDMODE_ADD || SDL_BLENDMODE_MOD
	if(SDL_SetTextureBlendMode((*textureSysteme).mobile, SDL_BLENDMODE_MOD) < 0)
		fprintf(stderr, "grapheInitialisation : Erreur SDL_SetRenderDrawBlendMode : %s.", SDL_GetError());

	image = SDL_LoadBMP("./image/sortie.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, sortie.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).sortie = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/entree.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, entree.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).entree = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

		// DIRECTIONS

	image = SDL_LoadBMP("./image/direction0.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction0.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).direction0 = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction1.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction1.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).direction1 = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction2.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction2.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).direction2 = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction3.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction3.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).direction3 = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction4.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction4.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).direction4 = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction5.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction5.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).direction5 = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction6.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction6.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).direction6 = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction7.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction7.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).direction7 = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}


	image = SDL_LoadBMP("./image/SimFouleConstruction01.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleConstruction01.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureSysteme).construct = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureSysteme).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	return retour;
}

//////////////////////////////////////////////////////////////////////////////

