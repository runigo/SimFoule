/*
Copyright décembre 2017, Stephan Runigo
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


#include "graphe.h"

	// Création et initialisation

int grapheCreation(grapheT * graphe, int nombre)
	{
		//	Création du graphe de la foule

	pointsT *iter;
	(*graphe).premier=NULL;
	(*graphe).premier=pointsCreationGraphe(nombre);

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
	pointsSupprime(&(*graphe).premier);
	//printf("Graphe supprimé\n");
	}

int grapheInitialisation(SDL_Renderer *rendu, grapheT * graphe)
{
	SDL_Surface *image = 0;

	//image = SDL_LoadBMP("direction0.bmp");
	image = SDL_LoadBMP("mur.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).mur = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).mur == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("humain.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).humain = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).humain == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("sortie.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).sortie = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

		// DIRECTION

	image = SDL_LoadBMP("direction0.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction0 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("direction2.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction2 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("direction4.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction4 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("direction6.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction6 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}


	return 0;
}

	// Dessin 
void grapheDessineMur(SDL_Renderer *rendu, grapheT * graphe)
	{
	int i, j;
	SDL_Rect coordonnee = {0, 0, CELLULE, CELLULE};
	for(i=0;i<BATIMENT;i++)
		{
		for(j=0;j<BATIMENT;j++)
			{
			switch((*graphe).plan[i][j][0])
				{
				case 1:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).mur, NULL, &coordonnee);
				break;
				case 2:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).sortie, NULL, &coordonnee);
				break;
				default:
					;
				}
			}
		}
	return;
	}

void grapheDessineAngle(SDL_Renderer *rendu, grapheT * graphe)
	{
	int i, j;
	SDL_Rect coordonnee = {0, 0, CELLULE, CELLULE};
	for(i=0;i<BATIMENT;i++)
		{
		for(j=0;j<BATIMENT;j++)
			{
			switch((*graphe).angle[i][j][0])
				{
				case 0:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction0, NULL, &coordonnee);
				break;
				case 2:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction2, NULL, &coordonnee);
				break;
				case 4:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction4, NULL, &coordonnee);
				break;
				case 6:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction6, NULL, &coordonnee);
				break;
				default:
					;
				}
			}
		}
	return;
	}

void grapheDessineHumain(SDL_Renderer *rendu, grapheT * graphe)
	{
	int i, j;
	SDL_Rect coordonnee = {0, 0, HUMAIN, HUMAIN};
	for(i=0;i<BATIMENT;i++)
		{
		for(j=0;j<BATIMENT;j++)
			{
			switch((*graphe).plan[i][j][0])
				{
				case 9:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).humain, NULL, &coordonnee);
				break;
				default:
					;
				}
			}
		}
	return;
	}

/////////////////////////////////////////////////////////////////////////
