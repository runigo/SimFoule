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

#include "../donnees/batiment.h"

int batimentInitialiseVide(batimentT * batiment);

int batimentInitialiseVide(batimentT * batiment)
	{
	int k;
	fprintf(stderr, "batimentInitialiseVide : Entrée dans la fonction\n");
	for(k=0;k<BATIMENT_Z;k++)
		{
		etageInitialise(&(*batiment).etage[k]);
		}
	fprintf(stderr, "batimentInitialiseVide : Sortie de la fonction\n");
	return 0;
	}

int batimentInitialise(batimentT * batiment, int numero)
	{ // Renvoie le nombre d'humain présent
	(void)numero;
	int i, j, k;
	int nombre = 0;

	fprintf(stderr, "batimentInitialise : Entrée dans la fonction\n");
	batimentInitialiseVide(batiment);

		// Plan du batiment
	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[i][0]);
			celluleCreationMur(&(*batiment).etage[k].cellule[i][BATIMENT_Y-1]);
			}
		for(j=0;j<BATIMENT_Y;j++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[0][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X-1][j]);
			}
		for(j=1;j<BATIMENT_Y/2-1;j++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X/2][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X/2][BATIMENT_Y-j-1]);
			}
		celluleCreationSortie(&(*batiment).etage[k].cellule[0][1]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[0][2]);
		celluleCreationEntree(&(*batiment).etage[k].cellule[BATIMENT_X-1][BATIMENT_Y-3]);
		celluleCreationEntree(&(*batiment).etage[k].cellule[BATIMENT_X-1][BATIMENT_Y-2]);
		}

		// Position des humains
	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=BATIMENT_X/2+1;i<BATIMENT_X-1;i++)
			{
			for(j=1;j<BATIMENT_Y-1;j++)
				{
				celluleCreationHumain(&(*batiment).etage[k].cellule[i][j]);
				nombre++;
				}
			}
		}
	fprintf(stderr, "batimentInitialise : Sortie de la fonction\n");
	return nombre;
	}

int batimentDirections(batimentT * batiment)
	{
	int k;
	fprintf(stderr, "batimentDirection : Entrée dans la fonction\n");
	for(k=0;k<BATIMENT_Z;k++)
		{
		etageCalculDistanceEtSens(&(*batiment).etage[k]);
		}
	fprintf(stderr, "batimentDirection : Sortie de la fonction\n");
	return 0;
	}

int batimentAffiche(batimentT * batiment)
	{
	(void)batiment;
	printf("batimentAffiche");
	return 0;
	}

///////////////////////////////////////////////////////////////////
