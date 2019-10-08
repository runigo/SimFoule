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


#include "../modele/etage.h"

int etageCalculeInteret(etageT * etage, int i, int j); // Calcul l'intérêt à rejoindre les voisines

int etageVoisinVisite(etageT * etage, int i, int j); // Retourne le nombre de voisines visitées

int etageCalculeDistance(etageT * etage); // Ajoute la distance la plus grande à toutes les cellules
int etageDiffuseInteret(etageT * etage); // Diffuse l'intérêt à rejoindre les voisines
int etageRectifieInteret(etageT * etage); // Rectifie l'intérêt à rejoindre les murs
int etageCalculSens(etageT * etage);
int etageCalculSensCellule(etageT * etage, int X, int Y);

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
	{	// Calcul du chemin le plus court vers les sorties
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

		fprintf(stderr, "    Calcul intérêt\n");
	do
		{
		if(compteur>2)sortie=true;

		for(i=0;i<BATIMENT_X;i++)		// Visite des cellules du front
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				if(celluleDonneStatut(&(*etage).cellule[i][j])!=1 // Cellule non mur
						&& celluleDonneVisite(&(*etage).cellule[i][j])==0 // Cellule non visité
						&& etageVoisinVisite(etage, i, j)>0) // Voisins visités
					{
					etageCalculeInteret(etage, i, j);
					celluleChangeVisite(&(*etage).cellule[i][j], -1); // Appartient au front
					sortie = false;
					}
				}
			}

		for(i=0;i<BATIMENT_X;i++)	// Marquage des cellules qui viennent d'être visitées
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				if(celluleDonneVisite(&(*etage).cellule[i][j])<0) // Appartient au front
					{
					celluleChangeVisite(&(*etage).cellule[i][j], 1); // À été visité
					}
				}
			}

		for(i=0;i<BATIMENT_X;i++)	// Incrémentation des cellules visitées
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

		//fprintf(stderr, "    Jauge des distances\n");
	etageCalculeDistance(etage);

		//fprintf(stderr, "    Diffusion des intérêts\n");
	etageDiffuseInteret(etage);

		//fprintf(stderr, "    Rectification des intérêts\n");
	etageRectifieInteret(etage);

	//etageAffiche(etage);


	return 0;
	}


int etageVoisinVisite(etageT * etage, int i, int j)
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
	{ // Donne de l'intérêt à aller vers des cellules plus proches de la sortie
	int nombre = 0;

	if(i<BATIMENT_X-1)
		{
		if(celluleDonneVisite(&(*etage).cellule[i+1][j])==1) // vers angle 0
			{
			(*etage).cellule[i][j].interet[0]=3*UNITE_NOTE;
			nombre++;
			}
		}
	if(i>0)
		{
		if(celluleDonneVisite(&(*etage).cellule[i-1][j])==1) // vers angle 4
			{
			(*etage).cellule[i][j].interet[4]=3*UNITE_NOTE;
			nombre++;
			}
		}
	if(j<BATIMENT_Y-1)
		{
		if(celluleDonneVisite(&(*etage).cellule[i][j+1])==1) // vers angle 2
			{
			(*etage).cellule[i][j].interet[2]=3*UNITE_NOTE;
			nombre++;
			}
		}
	if(j>0)
		{
		if(celluleDonneVisite(&(*etage).cellule[i][j-1])==1) // vers angle 6
			{
			(*etage).cellule[i][j].interet[6]=3*UNITE_NOTE;
			nombre++;
			}
		}

	(*etage).cellule[i][j].issue = nombre;

	return nombre;
	}

int etageDiffuseInteret(etageT * etage)
	{ // Diffuse l'intérêt à rejoindre les voisines des cellules plus proches de la sortie
	int i, j;
	int index;

	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			if((*etage).cellule[i][j].issue == 0 && (*etage).cellule[i][j].statut != 1)
				{
				//fprintf(stderr, "ERREUR : etageDiffuseInteret : cellule libre non visitée [%d][%d]\n", i, j);
				}
			if((*etage).cellule[i][j].issue == 1 && (*etage).cellule[i][j].statut != 1)
				{
				index = cellulePositionIssueSup(&(*etage).cellule[i][j]);
				(*etage).cellule[i][j].interet[(index+1)%8]=2*UNITE_NOTE;
				(*etage).cellule[i][j].interet[(index+7)%8]=2*UNITE_NOTE;
				(*etage).cellule[i][j].interet[(index+2)%8]=1*UNITE_NOTE;
				(*etage).cellule[i][j].interet[(index+6)%8]=1*UNITE_NOTE;
				}
			if((*etage).cellule[i][j].issue == 2 && (*etage).cellule[i][j].statut != 1)
				{
				index = cellulePositionIssueInf(&(*etage).cellule[i][j]);
				(*etage).cellule[i][j].interet[(index+1)%8]=2*UNITE_NOTE;
				(*etage).cellule[i][j].interet[(index+7)%8]=2*UNITE_NOTE;

				index = cellulePositionIssueSup(&(*etage).cellule[i][j]);
				(*etage).cellule[i][j].interet[(index+1)%8]=(*etage).cellule[i][j].interet[(index+1)%8] + 2*UNITE_NOTE;
				(*etage).cellule[i][j].interet[(index+7)%8]=(*etage).cellule[i][j].interet[(index+7)%8] + 2*UNITE_NOTE;
				}
			}
		}

	return 0;
	}

int etageRectifieInteret(etageT * etage)
	{ // Rectifie l'intérêt à rejoindre les murs
	int i, j;

	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			if((*etage).cellule[i][j].statut == 1)
				{
				if(i>0)
					{
					(*etage).cellule[i-1][j].interet[0]=-99;
					if(j>0)
						(*etage).cellule[i-1][j-1].interet[1]=-99;
					if(j<BATIMENT_Y-1)
						(*etage).cellule[i-1][j+1].interet[7]=-99;
					}
				if(i<BATIMENT_X-1)
					{
					(*etage).cellule[i+1][j].interet[4]=-99;
					if(j>0)
						(*etage).cellule[i+1][j-1].interet[3]=-99;
					if(j<BATIMENT_Y-1)
						(*etage).cellule[i+1][j+1].interet[5]=-99;
					}
				if(j<BATIMENT_Y-1)
					(*etage).cellule[i][j+1].interet[6]=-99;
				if(j>0)
					(*etage).cellule[i][j-1].interet[2]=-99;
				}
			}
		}

	return 0;
	}

int etageCalculSens(etageT * etage)
	{
	int i, j;

	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			etageCalculSensCellule(etage, i, j);
			}
		}

	return 0;
	}

int etageCalculSensCellule(etageT * etage, int X, int Y)
	{ // Calcul du sens le meilleur
	int i;
	int indexMax = 0;
	float max = 0.0;

		// Recherche de la meilleur note
	for(i=0;i<8;i++)
		{
		if((*etage).cellule[X][Y].note[i]>max)
			{
			indexMax = i;
			max = (*etage).cellule[X][Y].note[i];
			}
		}

	(*etage).cellule[X][Y].sens = indexMax;

	return 0;
	}

int etageCalculeDistance(etageT * etage)
	{ // Ajoute la distance la plus grande à toutes les cellules
	int i, j;
	int max = 0;

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

	return 0;
	}

int etageAffiche(etageT * etage)
	{
	int i, j, k;

	printf("etageAffiche distance\n");
	for(j=0;j<BATIMENT_Y;j++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			fprintf(stderr, " %2d", celluleDonneDistance(&(*etage).cellule[i][j]));
			}
		fprintf(stderr, " \n");
		}

	printf("etageAffiche interet\n");
	for(j=0;j<BATIMENT_Y;j++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			for(k=0;k<8;k++)
				{
				if((int)((*etage).cellule[i][j].interet[k])>-9)
					{
					fprintf(stderr, "%d", (int)((*etage).cellule[i][j].interet[k]));
					}
				else
					{
					fprintf(stderr, "m");
					}
				}
			fprintf(stderr, " ");
			}
		fprintf(stderr, " \n");
		}

	return 0;
	}

///////////////////////////////////////////////////////////////////

