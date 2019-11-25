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


#include "../modele/construction.h"


	//	-------  INITIALISATION  -------  //

int constructionInitialisation(constructionT * construction)
	{

	batimentInitialiseVide(&(*construction).batiment);

	(*construction).statut = 1;		// 0:libre, 1:mur, 2:sortie, 3:entrée, 9:mobileé

	(*construction).Xdebut = 1;
	(*construction).Ydebut = 1;
	(*construction).Xfin = 1;
	(*construction).Yfin = 1;

	return 0;
	}


	//	-------  ÉVOLUTION  -------  //

int constructionProjection(constructionT * construction)	// Projette le niveau 1 sur le niveau 0
	{
	int i, j;
		//fprintf(stderr, "    constructionProjection\n");
	for(i=0;i<(*construction).batiment.etage[0].etageX;i++)
		{
		for(j=0;j<(*construction).batiment.etage[0].etageY;j++)
			{
			(*construction).batiment.etage[0].cellule[i][j].statut = (*construction).batiment.etage[1].cellule[i][j].statut;
			}
		}
	return 0;
	}

int constructionPositionInitiale(constructionT * construction, int X, int Y) // Enregistre la position de la souris au moment de l'appui
	{

	//fprintf(stderr, "    constructionPositionInitial : %d, %d\n", X, Y);

	(*construction).Xdebut = X;
	(*construction).Ydebut = Y;

	return 0;
	}

int constructionPositionFinale(constructionT * construction, int X, int Y) // Enregistre la position de la souris actuelle
	{

	//fprintf(stderr, "    constructionPositionFinal : %d, %d\n", X, Y);

	(*construction).Xfin = X;
	(*construction).Yfin = Y;

	return 0;
	}

int constructionAjouteTrace(constructionT * construction, int niveau)	// Ajoute le tracé au niveau
	{
	int i;
	int X, Y;
	int X0 = (*construction).Xdebut;
	int Y0 = (*construction).Ydebut;
	int X1 = (*construction).Xfin;
	int Y1 = (*construction).Yfin;

	float x = (X1-X0);
	float y = (Y1-Y0);
	float max = 0;

	if(x<0) {x = -x;}
	if(y<0) {y = -y;}
	if(x<y) {max = y;} else {max = x;}

	if(max>0)
		{
		x = (X1-X0)/max;
		y = (Y1-Y0)/max;
		for(i=0;i<max;i++)
			{
			X = X0 + (int)(i*x);
			Y = Y0 + (int)(i*y);
			if(X>=0 && Y>=0 && X<BATIMENT_X_MAX && y<BATIMENT_Y_MAX)
				{
				celluleInitialiseStatut(&(*construction).batiment.etage[niveau].cellule[X][Y], (*construction).statut);
				}
			else
				{
				fprintf(stderr, "ERREUR constructionTrace\n");
				}
			}
		}
	else
		{
		celluleInitialiseStatut(&(*construction).batiment.etage[niveau].cellule[X0][Y0], (*construction).statut);
		}

	//fprintf(stderr, "    constructionTrace : %d\n", (*construction).statut);

	return 0;
	}


	//	-------  CHANGEMENT DES PARAMÈTRES  -------  //

int constructionChangeMotif(constructionT * construction, int statut)
	{	// Change le motif du tracé

	(*construction).statut = statut; // 0:libre, 1:mur, 2:sortie, 3:entrée, 9:mobile

	fprintf(stderr, "    constructionChangeStatut : %d\n", (*construction).statut);

	return 0;
	}


////////////////////////////////////////////////////////////////////////

