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

#include "../modele/batiment.h"

	//		INITIALISATION

int batimentInitialiseEtageVide(batimentT * batiment);
int batimentInitialiseFacade(batimentT * batiment);
int batimentInitialiseMur(batimentT * batiment, int numero);
int batimentInitialiseMobile(batimentT * batiment, int numero);
int batimentInitialiseMurImplicite(batimentT * batiment);
int batimentInitialiseMobileImplicite(batimentT * batiment);

	//		ÉVOLUTION

	//		INFORMATION


	//		---------  INITIALISATION  ---------  //

int batimentProjection(batimentT * construction, batimentT * normal)
	{ // Projette la construction sur normal
	int k;

	for(k=0;k<BATIMENT_Z_MAX;k++)
		{
		etageProjection(&(*construction).etage[k], &(*normal).etage[k]);
		}

	return 0;
	}


int batimentNormalise(batimentT * batiment, int etageXYZ)
	{ // Supprime les marges
	int k;

	for(k=0;k<BATIMENT_Z_MAX;k++)
		{
		etageNormalise(&(*batiment).etage[k], etageXYZ);
		}

	return 0;
	}

int batimentInitialiseVide(batimentT * batiment)
	{ // Initialise le batiment vide
	int k;
	
	(*batiment).batimentZ = BATIMENT_Z_MAX; // Nombre d'étage

	for(k=0;k<BATIMENT_Z_MAX;k++)
		{							// Surface des étages
		etageInitialise(&(*batiment).etage[k], BATIMENT_X_MAX, BATIMENT_Y_MAX, k);
		}

	return 0;
	}

int batimentInitialise9(batimentT * batiment)
	{ // Initialise le batiment plein de mobiles
	
	batimentInitialiseVide(batiment);

	etageInitialise9(&(*batiment).etage[0], BATIMENT_X_MAX, BATIMENT_Y_MAX, 0);
	etageInitialise9(&(*batiment).etage[1], BATIMENT_X_MAX, BATIMENT_Y_MAX, 1);

	return 0;
	}

int batimentInitialiseImplicite(batimentT * batiment, int niveau)
	{ // Renvoie le nombre de mobiles présent

	batimentInitialiseVide(batiment);

	(*batiment).batimentZ = BATIMENT_Z_IMP; // Nombre d'étage

	if((niveau > 0) && (niveau <= BATIMENT_Z_MAX))
		{
		(*batiment).batimentZ = niveau;
		}

	int k;
	for(k=0;k<(*batiment).batimentZ;k++)
		{									 // Surface des étages
		etageInitialise(&(*batiment).etage[k], BATIMENT_X_IMP, BATIMENT_Y_IMP, k);
		}

		// Plan du batiment
	batimentInitialiseFacade(batiment);
	batimentInitialiseMur(batiment, 0);

		// Position des mobiles
	return batimentInitialiseMobileImplicite(batiment);
	}

int batimentInitialiseFacade(batimentT * batiment)
	{ // Initialise les facades du batiment et des sorties.
	int i, j, k;

		// Plan du batiment
	for(k=0;k<(*batiment).batimentZ;k++)
		{
		for(i=0;i<(*batiment).etage[k].etageX;i++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[i][0]);
			celluleCreationMur(&(*batiment).etage[k].cellule[i][(*batiment).etage[k].etageY-1]);
			}
		for(j=0;j<(*batiment).etage[k].etageY;j++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[0][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX-1][j]);
			}
		}

		// Sorties
	for(k=0;k<(*batiment).batimentZ;k++)
		{
		if((k/2)==((k+1)/2))
			{
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2+1][0]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2-1][0]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2][0]);
			}
		else
			{
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2+1][(*batiment).etage[k].etageY-1]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2-1][(*batiment).etage[k].etageY-1]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2][(*batiment).etage[k].etageY-1]);
			}
		}

	return 0;
	}

int batimentInitialiseMur(batimentT * batiment, int entier)
	{ // Initialise les murs du batiment.
	int i, j, k;
	(void)entier;

		// Plan des murs
	for(k=0;k<(*batiment).batimentZ;k++)
		{
		for(i=0;i<(*batiment).etage[k].etageX/2-1;i++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[i][(*batiment).etage[k].etageY/2+2]);
			celluleCreationMur(&(*batiment).etage[k].cellule[i][(*batiment).etage[k].etageY/2-2]);
			celluleCreationMur(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX-1-i][(*batiment).etage[k].etageY/2+2]);
			celluleCreationMur(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX-1-i][(*batiment).etage[k].etageY/2-2]);
			}
		for(j=0;j<(*batiment).etage[k].etageY/2-1;j++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2+2][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2-2][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2+2][(*batiment).etage[k].etageY-1-j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2-2][(*batiment).etage[k].etageY-1-j]);
			}
		for(j=0;j<(*batiment).etage[k].etageY/2-1;j++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/4-1][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[3*(*batiment).etage[k].etageX/4+1][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/4-1][(*batiment).etage[k].etageY-1-j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[3*(*batiment).etage[k].etageX/4+1][(*batiment).etage[k].etageY-1-j]);
			}

		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/4-2][(*batiment).etage[k].etageY/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/4-3][(*batiment).etage[k].etageY/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/4-2][(*batiment).etage[k].etageY/2-2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/4-3][(*batiment).etage[k].etageY/2-2]);
		
		celluleCreationVide(&(*batiment).etage[k].cellule[3*(*batiment).etage[k].etageX/4+2][(*batiment).etage[k].etageY/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[3*(*batiment).etage[k].etageX/4+3][(*batiment).etage[k].etageY/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[3*(*batiment).etage[k].etageX/4+2][(*batiment).etage[k].etageY/2-2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[3*(*batiment).etage[k].etageX/4+3][(*batiment).etage[k].etageY/2-2]);
		
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2+3][(*batiment).etage[k].etageY/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2+4][(*batiment).etage[k].etageY/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2+3][(*batiment).etage[k].etageY/2-2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2+4][(*batiment).etage[k].etageY/2-2]);
		
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2-3][(*batiment).etage[k].etageY/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2-4][(*batiment).etage[k].etageY/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2-3][(*batiment).etage[k].etageY/2-2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2-4][(*batiment).etage[k].etageY/2-2]);
		
		}

		// Sorties
	for(k=0;k<(*batiment).batimentZ;k++)
		{
		if((k/2)==((k+1)/2))
			{
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2+1][0]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2-1][0]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2][0]);
			}
		else
			{
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2+1][(*batiment).etage[k].etageY-1]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2-1][(*batiment).etage[k].etageY-1]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX/2][(*batiment).etage[k].etageY-1]);
			}
		}

	return 0;
	}

int batimentInitialiseMobileImplicite(batimentT * batiment)
	{ // Renvoie le nombre de mobiles présent
	int i, j, k;
	int nombre = 0;

		// Position des mobiles
	for(k=0;k<(*batiment).batimentZ;k++)
		{
		for(i=0;i<(*batiment).etage[k].etageX/2-2;i++)
			{
			for(j=0;j<(*batiment).etage[k].etageY/2-2;j++)
				{
				if((i+j)%3 == 0)
					{
					if(celluleDonneStatut(&(*batiment).etage[k].cellule[i][j]) == 0)
						{
						celluleCreationMobile(&(*batiment).etage[k].cellule[i][j]);
						nombre++;
						}
					if(celluleDonneStatut(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX-1-i][j]) == 0)
						{
						celluleCreationMobile(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX-1-i][j]);
						nombre++;
						}
					if(celluleDonneStatut(&(*batiment).etage[k].cellule[i][(*batiment).etage[k].etageY-1-j]) == 0)
						{
						celluleCreationMobile(&(*batiment).etage[k].cellule[i][(*batiment).etage[k].etageY-1-j]);
						nombre++;
						}
					if(celluleDonneStatut(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX-1-i][(*batiment).etage[k].etageY-1-j]) == 0)
						{
						celluleCreationMobile(&(*batiment).etage[k].cellule[(*batiment).etage[k].etageX-1-i][(*batiment).etage[k].etageY-1-j]);
						nombre++;
						}
					}
				}
			}
		}
	return nombre;
	}


	//		---------  ÉVOLUTION  ---------  //

int batimentDirections(batimentT * batiment)
	{ // Initialisation des directions suivant le chemin le plus court
	int k;

	for(k=0;k<(*batiment).batimentZ;k++)
		{
		fprintf(stderr, "  batimentDirection : etageCalculDistanceEtSens étage %d\n", k);
		etageCalculDistanceEtSens(&(*batiment).etage[k]);
		}

	return 0;
	}

int batimentMiseAZeroNombre(batimentT * batiment)
	{	// Mise à zéro du nombre de mobile par cellule
	int i, j, k;

	for(k=0;k<(*batiment).batimentZ;k++)
		{
		for(i=0;i<(*batiment).etage[k].etageX;i++)
			{
			for(j=0;j<(*batiment).etage[k].etageY;j++)
				{
				if((*batiment).etage[k].cellule[i][j].statut != 1)
					(*batiment).etage[k].cellule[i][j].nombre=0;
				}
			}
		}
	return 0;
	}


	//		---------  INFORMATION  ---------  //

int batimentNombreMobile(batimentT * batiment)
	{ // Retourne le nombre de mobiles
	int i, j, k;
	int nombre = 0;

	for(k=0;k<BATIMENT_Z_MAX;k++)
		{
		for(i=0;i<BATIMENT_X_MAX;i++)
			{
			for(j=0;j<BATIMENT_Y_MAX;j++)
				{
				if(celluleDonneStatut(&(*batiment).etage[k].cellule[i][j])==9)
					nombre++;
				}
			}
		}

	printf("	Le batiment contient %d mobiles\n", nombre);

	return nombre;
	}

int batimentAffiche(batimentT * batiment)
	{
	printf("batimentAffiche\n");
	int k;

	for(k=0;k<(*batiment).batimentZ;k++)
		{
		etageAffiche(&(*batiment).etage[k]);
		}
	return 0;
	}

///////////////////////////////////////////////////////////////////
