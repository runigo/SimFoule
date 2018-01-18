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
		fprintf(stderr, "    Graphe créé\n");
		}
	else
		{
		fprintf(stderr, "Echec de pointCreationGraphe\n");
		}

	iter=(*graphe).premier;
	do
		{
		iter->xm=FENETRE_X/2;
		iter->ym=FENETRE_Y/2;
		iter->zm=0;
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
	image = SDL_LoadBMP("./image/mur.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, mur.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).mur = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).mur == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("./image/humain.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, humain.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).humain = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).humain == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

		// Activation de la transparence
	//SDL_BLENDMODE_NONE || SDL_BLENDMODE_BLEND || SDL_BLENDMODE_ADD || SDL_BLENDMODE_MOD
	if(SDL_SetTextureBlendMode((*graphe).humain, SDL_BLENDMODE_MOD) < 0)
		fprintf(stderr, "grapheInitialisation : Erreur SDL_SetRenderDrawBlendMode : %s.", SDL_GetError());

	image = SDL_LoadBMP("./image/sortie.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, sortie.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).sortie = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("./image/entree.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, entree.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).entree = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

		// DIRECTIONS

	image = SDL_LoadBMP("./image/direction0.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction0.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction0 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("./image/direction1.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction1.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction1 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("./image/direction2.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction2.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction2 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("./image/direction3.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction3.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction3 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("./image/direction4.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction4.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction4 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("./image/direction5.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction5.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction5 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("./image/direction6.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction6.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction6 = SDL_CreateTextureFromSurface(rendu, image);
	SDL_FreeSurface(image);
	if ((*graphe).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		return 0;
		}

	image = SDL_LoadBMP("./image/direction7.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction7.bmp : %s\n",SDL_GetError());
		return 0;
		}
	(*graphe).direction7 = SDL_CreateTextureFromSurface(rendu, image);
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
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
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
				/*case 3:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).entree, NULL, &coordonnee);
				break;*/
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
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			switch((*graphe).angle[i][j][0])
				{
				case 0:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction0, NULL, &coordonnee);
				break;
				case 1:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction1, NULL, &coordonnee);
				break;
				case 2:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction2, NULL, &coordonnee);
				break;
				case 3:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction3, NULL, &coordonnee);
				break;
				case 4:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction4, NULL, &coordonnee);
				break;
				case 5:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction5, NULL, &coordonnee);
				break;
				case 6:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction6, NULL, &coordonnee);
				break;
				case 7:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy(rendu, (*graphe).direction7, NULL, &coordonnee);
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
	SDL_Rect coordonnee = {0, 0, HUMAIN, HUMAIN};

	pointsT *iterGraph=(*graphe).premier;

	int centrage = (HUMAIN)/2;

	do
		{
		coordonnee.x = iterGraph->xm-centrage;
		coordonnee.y = iterGraph->ym-centrage;
		// int plan[BATIMENT_X][BATIMENT_Y][BATIMENT_Z]; // Plan du batiment		À UTILISER ICI ?
				// 0 : libre, 1 : mur, 2 : sortie		if(iterGraph->zm=(*graphe).plan[][][])

		if(iterGraph->zm!=-1) // dessine les humains de l'étage
			SDL_RenderCopy(rendu, (*graphe).humain, NULL, &coordonnee);

		iterGraph = iterGraph->suivant;
		}
	while(iterGraph!=(*graphe).premier);

	return;
	}
/*
void grapheDessineHumain(SDL_Renderer *rendu, grapheT * graphe)
	{
	int i, j;
	SDL_Rect coordonnee = {0, 0, HUMAIN, HUMAIN};
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
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
*/
/////////////////////////////////////////////////////////////////////////
