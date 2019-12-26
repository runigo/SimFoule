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

#include "textureMenu.h"

int textureMenuInitialisation(textureMenuT * textureMenu, affichageT * affichage)
	{
	int retour = 0;
/*
	SDL_Surface *panneau = 0;

	panneau = SDL_LoadBMP("./image/SimFouleUniforme.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, ./image/SimFouleUniforme.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).simfoule = SDL_CreateTextureFromSurface((*affichage).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*textureMenu).simfoule == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}
*/

	SDL_Surface *lumiereVerte = 0;

	lumiereVerte = SDL_LoadBMP("./image/lumiereVerte.bmp");
	if (!lumiereVerte)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereVerte.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).lumiereVerte = SDL_CreateTextureFromSurface((*affichage).rendu, lumiereVerte);
	SDL_FreeSurface(lumiereVerte);
	if ((*textureMenu).lumiereVerte == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	SDL_Surface *lumiereRouge = 0;

	lumiereRouge = SDL_LoadBMP("./image/lumiereRouge.bmp");
	if (!lumiereRouge)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereRouge.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).lumiereRouge = SDL_CreateTextureFromSurface((*affichage).rendu, lumiereRouge);
	SDL_FreeSurface(lumiereRouge);
	if ((*textureMenu).lumiereRouge == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	SDL_Surface *lumiereJaune = 0;

	lumiereJaune = SDL_LoadBMP("./image/lumiereJaune.bmp");
	if (!lumiereJaune)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereJaune.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).lumiereJaune = SDL_CreateTextureFromSurface((*affichage).rendu, lumiereJaune);
	SDL_FreeSurface(lumiereJaune);
	if ((*textureMenu).lumiereJaune == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	SDL_Surface *lumiereOrange = 0;

	lumiereOrange = SDL_LoadBMP("./image/lumiereOrange.bmp");
	if (!lumiereOrange)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereOrange.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).lumiereOrange = SDL_CreateTextureFromSurface((*affichage).rendu, lumiereOrange);
	SDL_FreeSurface(lumiereOrange);
	if ((*textureMenu).lumiereOrange == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

		fprintf(stderr,"textureMenuInitialisation \n");



	SDL_Surface *image = 0;

			//	Menu construction

	image = SDL_LoadBMP("./image/SimFouleConstruction.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleConstruction.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).construction = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureMenu).construction == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}


		//	 Boutons

	image = SDL_LoadBMP("./image/SimFouleBoutonVide.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonVide.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).boutonVide = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureMenu).boutonVide == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}


	image = SDL_LoadBMP("./image/SimFouleBoutonMur.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonMur.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).boutonMur = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureMenu).boutonMur == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}


	image = SDL_LoadBMP("./image/SimFouleBoutonSortie.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonSortie.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).boutonSortie = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureMenu).boutonSortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

/*
	image = SDL_LoadBMP("./image/SimFouleBoutonEntree.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonEntree.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).boutonEntree = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureMenu).boutonEntree == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}
*/

	image = SDL_LoadBMP("./image/SimFouleBoutonMobile.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonMobile.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).boutonMobile = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureMenu).boutonMobile == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}


	image = SDL_LoadBMP("./image/SimFouleBoutonPoint.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonPoint.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).boutonPoint = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureMenu).boutonPoint == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}


	image = SDL_LoadBMP("./image/SimFouleBoutonTrait.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleBoutonTrait.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).boutonTrait = SDL_CreateTextureFromSurface((*affichage).rendu, image);
	SDL_FreeSurface(image);
	if ((*textureMenu).boutonTrait == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}


	SDL_Surface *menu = 0;
	menu = SDL_LoadBMP("./image/SimFouleConstruction01.bmp");
	if (!menu)
		{
		fprintf(stderr,"Erreur chargement image, SimFouleConstruction01.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*textureMenu).boutonRectangle = SDL_CreateTextureFromSurface((*affichage).rendu, menu);
	SDL_FreeSurface(menu);
	if ((*textureMenu).boutonRectangle == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}




	return retour;
}

//////////////////////////////////////////////////////////////////////////////

