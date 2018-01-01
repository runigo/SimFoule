/*
Copyright janvier 2018, Stephan Runigo
runigo@free.fr
SimFoule 1.0  simulateur de foule
Ce logiciel est un programme informatique servant à simuler l'évacuation
d'une foule dans un batiment et à en donner une représentation graphique.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies. Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/


#ifndef _GRAPHE_
#define _GRAPHE_

#include "interface.h"
#include "../graphisme/points.h"

struct GrapheT {
	SDL_Texture *mur;
	SDL_Texture *sortie;
	SDL_Texture *entree;

	int plan[BATIMENT_X][BATIMENT_Y][BATIMENT_Z]; // Plan du batiment
				// 0 : libre, 1 : mur, 2 : sortie

	SDL_Texture *direction0;
	SDL_Texture *direction1;
	SDL_Texture *direction2;
	SDL_Texture *direction3;
	SDL_Texture *direction4;
	SDL_Texture *direction5;
	SDL_Texture *direction6;
	SDL_Texture *direction7;

	int angle[BATIMENT_X][BATIMENT_Y][BATIMENT_Z]; // Direction vers la sortie
				// 0 : droite, 2 : bas, 4 : gauche, 6 : haut
				//  				    6
				//	Angles 			 5     7
				//	 possibles :		4       0
				//				 3     1
				//				    2
				

	SDL_Texture *humain;

	pointsT * premier; // Positions des humains
};
typedef struct GrapheT grapheT;

int grapheCreation(grapheT * graphe, int nombre);
void grapheSuppression(grapheT * graphe);

int grapheInitialisation(SDL_Renderer *rendu, grapheT * graphe);

void grapheDessineMur(SDL_Renderer *rendu, grapheT * graphe);
void grapheDessineAngle(SDL_Renderer *rendu, grapheT * graphe);
void grapheDessineHumain(SDL_Renderer *rendu, grapheT * graphe);

#endif
