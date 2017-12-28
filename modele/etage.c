/*
Copyright décembre 2017, Stephan Runigo
runigo@free.fr
SimFoule 0.0  simulateur de foule
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


#include "../modele/etage.h"

int etageEvolutionDistance(etageT * etage);
int etageEvolutionSens(etageT * etage);

int etageInitialise(etageT * etage)
	{
	int i, j;
	for(i=0;i<BATIMENT;i++)
		{
		for(j=0;j<BATIMENT;j++)
			{
			celluleInitialise(&(*etage).cellule[i][j]);
			}
		}
	return 0;
	}

int etageCreationMur(etageT * etage, int i, int j)
	{
	celluleCreationMur(&(*etage).cellule[i][j]);
	return 0;
	}

int etageCreationSortie(etageT * etage, int i, int j)
	{
	celluleCreationSortie(&(*etage).cellule[i][j]);
	return 0;
	}
int etageInitialiseStatutCellule(etageT * etage, int i, int j, int statut)
	{
	(*etage).cellule[i][j].statut = statut;
	return 0;
	}

int etageDonneStatutCellule(etageT * etage, int i, int j)
	{
	return celluleDonneStatut(&(*etage).cellule[i][j]);	// 0:libre, 1:mur, 2:sortie
	}

int etageCalculeDistance(etageT * etage)
	{
	(void)etage;
	return 0;
	}

int etageCalculeSens(etageT * etage)
	{
	(void)etage;
	return 0;
	}

int etageEvolutionDistance(etageT * etage)
	{
	(void)etage;
	return 0;
	}

int etageEvolutionSens(etageT * etage)
	{
	(void)etage;
	return 0;
	}


int etageAffiche(etageT * etage)
	{
	(void)etage;
	printf("etageAffiche");
	return 0;
	}

///////////////////////////////////////////////////////////////////
