/*
Copyright décembre 2019, Stephan Runigo
runigo@free.fr
SimFoule 2.2  simulateur de foule
Ce logiciel est un programme informatique servant à simuler l'évacuation
d'une foule dans un batiment et à en donner une représentation textureSysteme.
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

#ifndef _GRAPHIQUESYSTEME_
#define _GRAPHIQUESYSTEME_

#include "affichage.h"


struct TextureSystemeT {

	SDL_Texture *construct;			//	Textures du graphe
	SDL_Texture *mur;			//	Textures du graphe
	SDL_Texture *sortie;
	SDL_Texture *entree;
	SDL_Texture *mobile; int taille;	//	Taille des mobiles

	SDL_Texture *direction0;
	SDL_Texture *direction1;
	SDL_Texture *direction2;
	SDL_Texture *direction3;
	SDL_Texture *direction4;	// Flèches pour illustrer la direction
	SDL_Texture *direction5;
	SDL_Texture *direction6;
	SDL_Texture *direction7;

};
typedef struct TextureSystemeT textureSystemeT;

int textureSystemeInitialisation(textureSystemeT * textureSysteme, affichageT * affichage);

#endif
/////////////////////////////////////////////////////////////////
