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

#include "affichage.h"

int affichageChangeCouleur(affichageT * affichage, SDL_Color couleur);

int affichageDestruction(affichageT * affichage)
	{
	SDL_DestroyRenderer((*affichage).rendu);
	return 0;
	}


int affichageInitialisation(affichageT * affichage, interfaceT * interface)
	{
		// Création du rendu
	(*affichage).rendu = SDL_CreateRenderer((*interface).fenetre, -1 , 
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(NULL == (*affichage).rendu)
		{
		(*affichage).rendu = SDL_CreateRenderer((*interface).fenetre, -1 , 
						SDL_RENDERER_SOFTWARE);
		if(NULL == (*affichage).rendu)
			{
			fprintf(stderr, "ERREUR affichageInitialisation : Erreur SDL_CreateRenderer : %s \n", SDL_GetError());
			return EXIT_FAILURE;
			}
		}

	int fond = 245;
	//SDL_Color orange = {255, 127, 40, 255};
	(*affichage).fond.r = 255;
	(*affichage).fond.g = 250;
	(*affichage).fond.g = 200;
	(*affichage).fond.g = 255;
	(*affichage).contraste.r = 255-fond;
	(*affichage).contraste.g = 255-fond;
	(*affichage).contraste.b = 255-fond;
	(*affichage).contraste.a = 255;
	(*affichage).orange.r = 255;
	(*affichage).orange.g = 127;
	(*affichage).orange.b = 40;
	(*affichage).orange.a = 255;
	(*affichage).jaune.r = 255;
	(*affichage).jaune.g = 255;
	(*affichage).jaune.b = 0;
	(*affichage).jaune.a = 255;
	(*affichage).gris.r = 127;
	(*affichage).gris.g = 127;
	(*affichage).gris.b = 127;
	(*affichage).gris.a = 255;
	(*affichage).cyan.r = 127;
	(*affichage).cyan.g = 40;
	(*affichage).cyan.b = 255;
	(*affichage).cyan.a = 255;
	(*affichage).vert.r = 173;
	(*affichage).vert.g = 255;
	(*affichage).vert.b = 47;
	(*affichage).vert.a = 255;

	return 0;
}

int affichageNettoyage(affichageT * affichage)
	{
	SDL_SetRenderDrawColor((*affichage).rendu, (*affichage).fond.r,  (*affichage).fond.g, (*affichage).fond.g, (*affichage).fond.g);
	SDL_RenderClear((*affichage).rendu);
	return 0;
	}

//////////////////////////////////////////////////////////////////////////////

