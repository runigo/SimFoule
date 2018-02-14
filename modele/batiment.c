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

#include "../modele/batiment.h"

int batimentInitialiseEtageVide(batimentT * batiment);
int batimentInitialiseFacade(batimentT * batiment);
int batimentInitialiseMur(batimentT * batiment, int numero);
int batimentInitialiseMobile(batimentT * batiment, int numero);

int batimentInitialise(batimentT * batiment, int numero)
	{ // Renvoie le nombre de mobiles présent
	int nombre = 0;

	//fprintf(stderr, "batimentInitialise : Entrée dans la fonction\n");
	batimentInitialiseEtageVide(batiment);

		// Plan du batiment
	batimentInitialiseFacade(batiment);
	batimentInitialiseMur(batiment, numero);

		// Position des mobiles
	nombre = batimentInitialiseMobile(batiment, numero);

	return nombre;
	}

int batimentInitialiseEtageVide(batimentT * batiment)
	{ // Initialise le batiment vide
	int k;
	for(k=0;k<BATIMENT_Z;k++)
		{
		etageInitialise(&(*batiment).etage[k], k);
		//celluleCreationMobile(&(*batiment).etage[k].cellule[BATIMENT_X/2][BATIMENT_Y/2]);
		}

	return 0;
	}

int batimentInitialiseFacade(batimentT * batiment)
	{ // Initialise les facades du batiment et des sorties.
	int i, j, k;

	//batimentInitialiseEtageVide(batiment);

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
		}

		// Sorties
	for(k=0;k<BATIMENT_Z;k++)
		{
		if((k/2)==((k+1)/2))
			{
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2+1][0]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2-1][0]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2][0]);
			}
		else
			{
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2+1][BATIMENT_Y-1]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2-1][BATIMENT_Y-1]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2][BATIMENT_Y-1]);
			}
		}

	return 0;
	}

int batimentInitialiseMur(batimentT * batiment, int numero)
	{ // Initialise les murs du batiment.
	int i, j, k;
	(void)numero;

		// Plan des murs
	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=0;i<BATIMENT_X/2-1;i++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[i][BATIMENT_Y/2+2]);
			celluleCreationMur(&(*batiment).etage[k].cellule[i][BATIMENT_Y/2-2]);
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X-1-i][BATIMENT_Y/2+2]);
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X-1-i][BATIMENT_Y/2-2]);
			}
		for(j=0;j<BATIMENT_Y/2-1;j++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X/2+2][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X/2-2][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X/2+2][BATIMENT_Y-1-j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X/2-2][BATIMENT_Y-1-j]);
			}
		for(j=0;j<BATIMENT_Y/2-1;j++)
			{
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X/4-1][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[3*BATIMENT_X/4+1][j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[BATIMENT_X/4-1][BATIMENT_Y-1-j]);
			celluleCreationMur(&(*batiment).etage[k].cellule[3*BATIMENT_X/4+1][BATIMENT_Y-1-j]);
			}

		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/4-2][BATIMENT_Y/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/4-3][BATIMENT_Y/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/4-2][BATIMENT_Y/2-2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/4-3][BATIMENT_Y/2-2]);
		
		celluleCreationVide(&(*batiment).etage[k].cellule[3*BATIMENT_X/4+2][BATIMENT_Y/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[3*BATIMENT_X/4+3][BATIMENT_Y/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[3*BATIMENT_X/4+2][BATIMENT_Y/2-2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[3*BATIMENT_X/4+3][BATIMENT_Y/2-2]);
		
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/2+3][BATIMENT_Y/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/2+4][BATIMENT_Y/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/2+3][BATIMENT_Y/2-2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/2+4][BATIMENT_Y/2-2]);
		
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/2-3][BATIMENT_Y/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/2-4][BATIMENT_Y/2+2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/2-3][BATIMENT_Y/2-2]);
		celluleCreationVide(&(*batiment).etage[k].cellule[BATIMENT_X/2-4][BATIMENT_Y/2-2]);
		
		}

		// Sorties
	for(k=0;k<BATIMENT_Z;k++)
		{
		if((k/2)==((k+1)/2))
			{
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2+1][0]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2-1][0]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2][0]);
			}
		else
			{
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2+1][BATIMENT_Y-1]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2-1][BATIMENT_Y-1]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X/2][BATIMENT_Y-1]);
			}
		}

	return 0;
	}

int batimentInitialiseMobile(batimentT * batiment, int numero)
	{ // Renvoie le nombre de mobiles présent
	(void)numero;
	int i, j, k;
	int nombre = 0;

		// Position des mobiles
	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=0;i<BATIMENT_X/2-2;i++)
			{
			for(j=0;j<BATIMENT_Y/2-2;j++)
				{
				if((i+j)%3 == 0)
					{
					if(celluleDonneStatut(&(*batiment).etage[k].cellule[i][j]) == 0)
						{
						celluleCreationMobile(&(*batiment).etage[k].cellule[i][j]);
						nombre++;
						}
					if(celluleDonneStatut(&(*batiment).etage[k].cellule[BATIMENT_X-1-i][j]) == 0)
						{
						celluleCreationMobile(&(*batiment).etage[k].cellule[BATIMENT_X-1-i][j]);
						nombre++;
						}
					if(celluleDonneStatut(&(*batiment).etage[k].cellule[i][BATIMENT_Y-1-j]) == 0)
						{
						celluleCreationMobile(&(*batiment).etage[k].cellule[i][BATIMENT_Y-1-j]);
						nombre++;
						}
					if(celluleDonneStatut(&(*batiment).etage[k].cellule[BATIMENT_X-1-i][BATIMENT_Y-1-j]) == 0)
						{
						celluleCreationMobile(&(*batiment).etage[k].cellule[BATIMENT_X-1-i][BATIMENT_Y-1-j]);
						nombre++;
						}
					}
				}
			}
		}

	return nombre;
	}

int batimentInitialiseMobileTest(batimentT * batiment, int numero)
	{ // Renvoie le nombre de mobiles présent
	(void)numero;
	int i, j, k;
	int nombre = 0;
	int dim = 1;

	if(BATIMENT_X > 10)
		{
		if(BATIMENT_Y > 10) dim = 2;
		if(BATIMENT_Y > 30) dim = 3;
		if(BATIMENT_Y > 50) dim = 4;
		}
	else
		{
		if(BATIMENT_Y > 30) dim = 2;
		if(BATIMENT_Y > 50) dim = 3;
		}

	if(BATIMENT_Y > 10)
		{
		if(BATIMENT_X > 10) dim = 2;
		if(BATIMENT_X > 30) dim = 3;
		if(BATIMENT_X > 50) dim = 4;
		}
	else
		{
		if(BATIMENT_X > 30) dim = 2;
		if(BATIMENT_X > 50) dim = 3;
		}

		// Position des mobiles
	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				if((i+j)%dim == 0 && celluleDonneStatut(&(*batiment).etage[k].cellule[i][j]) == 0)
					{
					celluleCreationMobile(&(*batiment).etage[k].cellule[i][j]);
					nombre++;
					}
				}
			}
		}

	return nombre;
	}

int batimentInitialiseTest(batimentT * batiment, int numero)
	{ // Renvoie le nombre de mobiles présent
	(void)numero;
	int i, j, k;
	int nombre = 0;

	batimentInitialiseEtageVide(batiment);

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
		celluleCreationSortie(&(*batiment).etage[k].cellule[(int)BATIMENT_X/2][0]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[(int)BATIMENT_X/2][BATIMENT_Y-1]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[BATIMENT_X-1][(int)BATIMENT_Y/2]);
		celluleCreationSortie(&(*batiment).etage[k].cellule[0][(int)BATIMENT_Y/2]);
		}

		// Position des mobiles
	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=1;i<BATIMENT_X-1;i++)
			{
			for(j=1;j<BATIMENT_Y-1;j++)
				{
				if((i+j)/2 == (i+j+1)/2 )
					{
					celluleCreationMobile(&(*batiment).etage[k].cellule[i][j]);
					nombre++;
					}
				}
			}
		}
	//fprintf(stderr, "batimentInitialise : Sortie de la fonction\n");
	return nombre;
	}

int batimentDirections(batimentT * batiment)
	{ // Initialisation des directions suivant le chemin le plus court
	int k;
	for(k=0;k<BATIMENT_Z;k++)
		{
		fprintf(stderr, "  batimentDirection : etageCalculDistanceEtSens étage %d\n", k);
		etageCalculDistanceEtSens(&(*batiment).etage[k]);
		}
	//fprintf(stderr, "batimentDirection : Sortie de la fonction\n");
	return 0;
	}

int batimentMiseAZeroNombre(batimentT * batiment)
	{	// Mise à zéro du nombre de mobile par cellule
	int i, j, k;

	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				if((*batiment).etage[k].cellule[i][j].statut!=1)
					(*batiment).etage[k].cellule[i][j].nombre=0;
				}
			}
		}
	return 0;
	}

int batimentAffiche(batimentT * batiment)
	{
	printf("batimentAffiche");
	int k;

	for(k=0;k<BATIMENT_Z;k++)
		{
		etageAffiche(&(*batiment).etage[k]);
		}
	return 0;
	}

///////////////////////////////////////////////////////////////////
