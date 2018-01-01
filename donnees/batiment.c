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

int batimentCalculeDistance(batimentT * batiment); // Ajoute la distance la plus grande à toutes les cellules

//int batimentEvolutionDistance(batimentT * batiment);
//int batimentEvolutionSens(batimentT * batiment);

int batimentInitialise(batimentT * batiment)
	{
	int i = 0;
	int j = 0;
	int k = 0;
	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[i][0]);
			celluleCreationMur(&(*batiment).etage[k].cellule[i][BATIMENT_Y]);
			}
		for(j=0;j<BATIMENT_Y;j++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[0][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_Y][j]);
			}
		}
	for(k=0;k<BATIMENT_Z;k++)
		{
		for(j=1;j<BATIMENT_Y/2-1;j++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[0][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X/2][BATIMENT_Y-j]);
			}
		}
	celluleCreationSortie(&(*batiment).etage[k].cellule[0][1]);
	celluleCreationSortie(&(*batiment).etage[k].cellule[0][2]);
	return 0;
	}

/*
int batimentCreationCelluleMur(batimentT * batiment, int i, int j)
	{
	celluleCreationMur(&(*etage).cellule[i][j]);
	return 0;
	}

int batimentCreationCelluleSortie(batimentT * batiment, int i, int j)
	{
	celluleCreationSortie(&(*etage).cellule[i][j]);
	return 0;
	}

int batimentInitialiseStatutCellule(batimentT * batiment, int i, int j, int statut)
	{
	celluleInitialiseStatut(&(*etage).cellule[i][j], statut);	// 0:libre, 1:mur, 2:sortie
	return 0;
	}

int batimentDonneStatutCellule(batimentT * batiment, int i, int j)
	{
	return celluleDonneStatut(&(*etage).cellule[i][j]);	// 0:libre, 1:mur, 2:sortie
	}
int batimentCalculDistanceEtSens(batimentT * batiment)
	{
	int i, j;
	bool sortie;
	int compteur = 0;

		// Initialisation des sorties
		fprintf(stderr, "Initialisation des sorties\n");
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			if(celluleDonneStatut(&(*etage).cellule[i][j]) == 2)
				{
				celluleChangeVisite(&(*etage).cellule[i][j]);
				fprintf(stderr, "Sortie : %d, %d\n", i, j);
				}
			}
		}

		fprintf(stderr, "Calcul sens et distance\n");
	do
		{
		sortie=true;
		for(i=0;i<BATIMENT_X;i++)
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				if(!celluleDonneVisite(&(*etage).cellule[i][j]) && etageVoisinVisite(etage, i, j)>0)
					{
					etageCalculeSens(etage, i, j);
					celluleChangeVisite(&(*etage).cellule[i][j]);
					sortie = false;
					}
				}
			}
		for(i=0;i<BATIMENT_X;i++)
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				if(celluleDonneVisite(&(*etage).cellule[i][j]))
					{
					celluleChangeDistance(&(*etage).cellule[i][j], -1);
					}
				}
			}
		compteur++;
		if(compteur>CELLULE_ETAGE)
			{
			fprintf(stderr, "etageCalculDistanceEtSens : Il y aurait des cellules inaccessibles ?\n");
			sortie=true;
			}
		}
	while(sortie==false);

		fprintf(stderr, "Jauge des distances\n");
	etageCalculeDistance(etage);

	return 0;
	}


int batimentVoisinVisite(batimentT * batiment, int i, int j) // Retourne le nombre de voisin visité
	{ // Retourne le nombre de voisin visité
	int nombre = 0;
	if(celluleDonneVisite(&(*etage).cellule[i+1][j]))
		nombre++;
	if(celluleDonneVisite(&(*etage).cellule[i][j+1]))
		nombre++;
	if(celluleDonneVisite(&(*etage).cellule[i-1][j]))
		nombre++;
	if(celluleDonneVisite(&(*etage).cellule[i][j-1]))
		nombre++;
	return nombre;
	}

int batimentCalculeDistance(batimentT * batiment)
	{ // Ajoute la distance la plus grande à toutes les cellules
	int i, j;
	int max = 0;
	fprintf(stderr, "  batimentCalculeDistance, entrée\n");
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			if( celluleDonneDistance(&(*etage).cellule[i][j]) < max)
				{
				max = celluleDonneDistance(&(*etage).cellule[i][j]);
				}
			}
		}
	fprintf(stderr, "  etageCalculeDistance, max = %d\n", max);
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			celluleChangeDistance(&(*etage).cellule[i][j], max);
			}
		}
	fprintf(stderr, "  etageCalculeDistance, sortie\n");
	return 0;
	}

int batimentCalculeSens(batimentT * batiment, int i, int j)
	{ // Calcul le sens et la direction de la cellule
	//int angle = 0;
	int nombre = 0;

	if(celluleDonneVisite(&(*etage).cellule[i+1][j]))
		{
		vecteurSommeCartesien(&(*etage).angle[0], &(*etage).vecteurNul, &(*etage).cellule[i][j].sens);
		nombre++;
		}
	if(celluleDonneVisite(&(*etage).cellule[i][j+1]))
		{
		vecteurSommeCartesien(&(*etage).angle[2], &(*etage).cellule[i][j].sens, &(*etage).cellule[i][j].sens);
		nombre++;
		}
	if(celluleDonneVisite(&(*etage).cellule[i-1][j]))
		{
		vecteurSommeCartesien(&(*etage).angle[4], &(*etage).cellule[i][j].sens, &(*etage).cellule[i][j].sens);
		nombre++;
		}
	if(celluleDonneVisite(&(*etage).cellule[i][j-1]))
		{
		vecteurSommeCartesien(&(*etage).angle[6], &(*etage).cellule[i][j].sens, &(*etage).cellule[i][j].sens);
		nombre++;
		}

	(*etage).cellule[i][j].norme=vecteurNormaliseCartesien(&(*etage).cellule[i][j].sens);

	if((*etage).cellule[i][j].norme<0.0)
		//fprintf(stderr, "vecteurInitialisePolaire, r, psi, phi\n");
		fprintf(stderr, "etageCalculeSens : norme négative, cellule %d, %d\n", i, j);
	return 0;
	}

int batimentEvolutionDistance(batimentT * batiment)
	{
	(void)batiment;
	return 0;
	}

int batimentEvolutionSens(batimentT * batiment)
	{
	(void)batiment;
	return 0;
	}
*/
int batimentAffiche(batimentT * batiment)
	{
	(void)batiment;
	printf("batimentAffiche");
	return 0;
	}

///////////////////////////////////////////////////////////////////
