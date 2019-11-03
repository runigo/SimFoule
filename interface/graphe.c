/*
Copyright octobre 2019, Stephan Runigo
runigo@free.fr
SimFoule 2.0  simulateur de foule
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


#include "graphe.h"

	// Création et initialisation

int grapheInitialisation(grapheT * graphe, int batimentX, int batimentY, int batimentZ)
	{
	int i, j, k;

	for(k=0;k<BATIMENT_Z_MAX;k++)
		{
		for(i=0;i<BATIMENT_X_MAX;i++)
			{
			for(j=0;j<BATIMENT_Y_MAX;j++)
				{
				(*graphe).plan[i][j][k] = 0;
				(*graphe).angle[i][j][k] = 0;
				}
			}
		}

	(*graphe).batimentX=batimentX;
	(*graphe).batimentY=batimentY;
	(*graphe).batimentZ=batimentZ;

	return 0;
	}


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
/////////////////////////////////////////////////////////////////////////
