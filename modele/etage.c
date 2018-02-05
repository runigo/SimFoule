/*
Copyright février 2018, Stephan Runigo
runigo@free.fr
SimFoule 1.4  simulateur de foule
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

int etageCalculeInteret(etageT * etage, int i, int j); // Calcul l'intérêt à rejoindre les voisines
int etageVoisinVisite(etageT * etage, int i, int j); // Retourne le nombre de voisines visitées
int etageCalculeDistance(etageT * etage); // Ajoute la distance la plus grande à toutes les cellules

int etageInitialise(etageT * etage, int niveau)
	{
	int i, j;
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			celluleInitialise(&(*etage).cellule[i][j]);
			}
		}

		// 8 vecteurs de direction, normés
	vecteurCartesien(&(*etage).angle[0], 1.0, 0.0, 0);
	vecteurCartesien(&(*etage).angle[1], 0.7071, 0.7071, 0);
	vecteurCartesien(&(*etage).angle[2], 0.0, 1.0, 0);
	vecteurCartesien(&(*etage).angle[3], -0.7071, 0.7071, 0);
	vecteurCartesien(&(*etage).angle[4], -1.0, 0.0, 0);
	vecteurCartesien(&(*etage).angle[5], -0.7071, -0.7071, 0);
	vecteurCartesien(&(*etage).angle[6], 0.0, -1.0, 0);
	vecteurCartesien(&(*etage).angle[7], 0.7071, -0.7071, 0);

		// Numéro de l'étage
	(*etage).etage=niveau;

		// Vecteur nul
	vecteurCartesien(&(*etage).vecteurNul, 0.0, 0.0, 0);

	return 0;
	}

int etageCreationCelluleMur(etageT * etage, int i, int j)
	{
	celluleCreationMur(&(*etage).cellule[i][j]);
	return 0;
	}

int etageCreationCelluleSortie(etageT * etage, int i, int j)
	{
	celluleCreationSortie(&(*etage).cellule[i][j]);
	return 0;
	}

int etageInitialiseStatutCellule(etageT * etage, int i, int j, int statut)
	{// 0:libre, 1:mur, 2:sortie, 3:entrée, 9:mobile lors de l'initialisation
	celluleInitialiseStatut(&(*etage).cellule[i][j], statut);	
	return 0;
	}

int etageDonneStatutCellule(etageT * etage, int i, int j)
	{// 0:libre, 1:mur, 2:sortie, 3:entrée, 9:mobile lors de l'initialisation
	return celluleDonneStatut(&(*etage).cellule[i][j]);
	}

int etageCalculDistanceEtSens(etageT * etage)
	{
	int i, j;
	bool sortie=false;
	int compteur = 0;

		fprintf(stderr, "    Initialisation des sorties\n");
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			if(celluleDonneStatut(&(*etage).cellule[i][j]) == 2)
				{
				celluleChangeVisite(&(*etage).cellule[i][j], 1);
				fprintf(stderr, "      Sortie : %d, %d\n", i, j);
				}
			}
		}

	//etageAffiche(etage);
	fprintf(stderr, "    Calcul intérêt\n");
	do
		{
		if(compteur>2)sortie=true;

			// Visite des cellules du front
		for(i=0;i<BATIMENT_X;i++)
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				if(celluleDonneStatut(&(*etage).cellule[i][j])!=1 // Cellule non mur
						&& celluleDonneVisite(&(*etage).cellule[i][j])==0 // Cellule non visité
						&& etageVoisinVisite(etage, i, j)>0) // Voisins visité
					{
					etageCalculeInteret(etage, i, j);
					celluleChangeVisite(&(*etage).cellule[i][j], -1); // Appartient au front
					sortie = false;
					}
				}
			}

			// Marquage des cellules qui viennent d'être visitées
		for(i=0;i<BATIMENT_X;i++)
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				if(celluleDonneVisite(&(*etage).cellule[i][j])<0) // Appartient au front
					{
					celluleChangeVisite(&(*etage).cellule[i][j], 1); // À été visité
					}
				}
			}

			// Incrémentation des cellules visitées
		for(i=0;i<BATIMENT_X;i++)
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				if(celluleDonneVisite(&(*etage).cellule[i][j])!=0) // À été visité
					{ // Ajoute -1 à la distance des cellules visitées
					celluleChangeDistance(&(*etage).cellule[i][j], -1);
					}
				}
			}
		compteur++;
		if(compteur>CELLULE_ETAGE)
			{
			fprintf(stderr, "    ERREUR : etageCalculDistanceEtSens : Il y aurait des cellules inaccessibles ?\n");
			sortie=true;
			}
		}
	while(sortie==false);

	//etageAffiche(etage);
		//fprintf(stderr, "    Jauge des distances\n");
	etageCalculeDistance(etage);

	return 0;
	}


int etageVoisinVisite(etageT * etage, int i, int j) // Retourne le nombre de voisin visité
	{ // Retourne le nombre de voisin visité
	int nombre = 0;
	if(i<BATIMENT_X-1)
	if(celluleDonneVisite(&(*etage).cellule[i+1][j])>0)
		nombre++;
	if(j<BATIMENT_Y-1)
	if(celluleDonneVisite(&(*etage).cellule[i][j+1])>0)
		nombre++;
	if(i>0)
	if(celluleDonneVisite(&(*etage).cellule[i-1][j])>0)
		nombre++;
	if(j>0)
	if(celluleDonneVisite(&(*etage).cellule[i][j-1])>0)
		nombre++;
	return nombre;
	}

int etageCalculeInteret(etageT * etage, int i, int j)
	{ // Calcul le sens et la direction de la cellule en fonction des voisins visité
	int nombre = 0;

	if(i<BATIMENT_X-1)
		{
		if(celluleDonneVisite(&(*etage).cellule[i+1][j])==1) // vers angle 0
			{
			(*etage).cellule[i][j].angle[0]=3*UNITE_NOTE;
			nombre++;
			}
		}
	if(i>0)
		{
		if(celluleDonneVisite(&(*etage).cellule[i-1][j])==1) // vers angle 4
			{
			(*etage).cellule[i][j].angle[4]=3*UNITE_NOTE;
			nombre++;
			}
		}
	if(j<BATIMENT_Y-1)
		{
		if(celluleDonneVisite(&(*etage).cellule[i][j+1])==1) // vers angle 2
			{
			(*etage).cellule[i][j].angle[2]=3*UNITE_NOTE;
			nombre++;
			}
		}
	if(j>0)
		{
		if(celluleDonneVisite(&(*etage).cellule[i][j-1])==1) // vers angle 6
			{
			(*etage).cellule[i][j].angle[6]=3*UNITE_NOTE;
			nombre++;
			}
		}

	return nombre;
	}

int etageCalculeDistance(etageT * etage)
	{ // Ajoute la distance la plus grande à toutes les cellules
	int i, j;
	int max = 0;
	//fprintf(stderr, "  etageCalculeDistance, entrée\n");
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
	fprintf(stderr, "      etageCalculeDistance, max = %d\n", max);
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			celluleChangeDistance(&(*etage).cellule[i][j], -max);
			}
		}
	//fprintf(stderr, "  etageCalculeDistance, sortie\n");
	return 0;
	}

int etageAffiche(etageT * etage)
	{
	int i, j;
/*
	printf("etageAffiche Norme\n");
	for(j=0;j<BATIMENT_Y;j++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			fprintf(stderr, " %3.1f", (*etage).cellule[i][j].norme);
			}
		fprintf(stderr, " \n");
		}
*/
	printf("etageAffiche distance\n");
	for(j=0;j<BATIMENT_Y;j++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			fprintf(stderr, " %2d", celluleDonneDistance(&(*etage).cellule[i][j]));
			}
		fprintf(stderr, " \n");
		}
/*
	printf("etageAffiche angle\n");
	for(j=0;j<BATIMENT_Y;j++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			fprintf(stderr, " %d", (*etage).cellule[i][j].angle);
			}
		fprintf(stderr, " \n");
		}
	//fprintf(stderr, "  etageCalculeDistance, max = %d\n", max);
*/
	return 0;
	}

/*
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
*/

///////////////////////////////////////////////////////////////////
