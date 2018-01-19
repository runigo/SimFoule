/*
Copyright janvier 2018, Stephan Runigo
runigo@free.fr
Simfoule 1.2  simulateur de foule
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


#include "systeme.h"


int systemeForceBatiment(systemeT * systeme); // Calcul de la force de couplage avec le batiment
int systemeForceMurs(systemeT * systeme); // Calcul de la force de couplage avec les mur


int systemeEvolution(systemeT * systeme, int duree)
	{ // Évolution temporelle de la foule, "duree" cycle d'évolution
	int i;

	//	Fait évoluer le système pendant duree*dt
	for(i=0;i<duree;i++)
		{
			// Déplacement inertiel
		fouleInertie(&(*systeme).foule);

			// Calcul des forces dans la 
			// nouvelle situation
		systemeForceBatiment(systeme);
		//fouleForceHumains(&(*systeme).foule);
		//systemeForceMurs(systeme);
		fouleSommeForces(&(*systeme).foule);

			// Incrémentation
		fouleIncremente(&(*systeme).foule);
		}

	//humainAffiche(&(*systeme).foule.premier->humain);

	return 0;
	}



int systemeForceMurs(systemeT * systeme)
	{ // Calcul des forces de contact avec les murs
	int X, Y, Z;
	int etage;
	chaineT *iter;
	iter = (*systeme).foule.premier;
	float force;

		// Remise à zéro
	do
		{
		vecteurCartesien(&iter->humain.forceMurs, 0.0, 0.0, 0.0);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);


	do
		{
		X = (int)(iter->humain.nouveau.x/CELLULE);
		Y = (int)(iter->humain.nouveau.y/CELLULE);
		Z = iter->humain.nouveau.z;
		for(etage=0;etage<BATIMENT_Z;etage++)
			{
			if(Z==etage)
				{
				if((*systeme).batiment.etage[Z].cellule[X-1][Y].statut==1)
					force = humainAjouteForceMur(&iter->humain, -1, 0, &(*systeme).batiment.etage[etage].angle[0]);
				//if((*systeme).batiment.etage[Z].cellule[X-1][Y-1].statut==1)
				//	force = humainAjouteForceMur(&iter->humain, -1, -1, &(*systeme).batiment.etage[etage].angle[1]);
				if((*systeme).batiment.etage[Z].cellule[X][Y-1].statut==1)
					force = humainAjouteForceMur(&iter->humain, 0, -1, &(*systeme).batiment.etage[etage].angle[2]);
				//if((*systeme).batiment.etage[Z].cellule[X+1][Y-1].statut==1)
				//	force = humainAjouteForceMur(&iter->humain, 1, -1, &(*systeme).batiment.etage[etage].angle[3]);
				if((*systeme).batiment.etage[Z].cellule[X+1][Y].statut==1)
					force = humainAjouteForceMur(&iter->humain, 1, 0, &(*systeme).batiment.etage[etage].angle[4]);
				//if((*systeme).batiment.etage[Z].cellule[X+1][Y+1].statut==1)
				//	force = humainAjouteForceMur(&iter->humain, 1, 1, &(*systeme).batiment.etage[etage].angle[5]);
				if((*systeme).batiment.etage[Z].cellule[X][Y+1].statut==1)
					force = humainAjouteForceMur(&iter->humain, 0, 1, &(*systeme).batiment.etage[etage].angle[6]);
				//if((*systeme).batiment.etage[Z].cellule[X-1][Y+1].statut==1)
				//	force = humainAjouteForceMur(&iter->humain, -1, 1, &(*systeme).batiment.etage[etage].angle[7]);
				}
			}
		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	return (int)force;
	}

int systemeForceBatiment(systemeT * systeme)
	{ // Calcul des forces extérieures
	int X, Y, Z;	
	chaineT *iter;
	iter = (*systeme).foule.premier;

	do
		{
		X = (int)(iter->humain.nouveau.x/CELLULE);
		Y = (int)(iter->humain.nouveau.y/CELLULE);
		Z = iter->humain.nouveau.z;
		if(Z>-1 && Z<BATIMENT_Z)
			{
			if((*systeme).batiment.etage[Z].cellule[X][Y].statut==2)
				{
				fprintf(stderr, "systemeCouplage : Sortie d'un humain \n");
				iter->humain.nouveau.z--;
				(*systeme).foule.restant--;
				fprintf(stderr, "systemeCouplage : Il en reste %d dans le batiment \n", (*systeme).foule.restant);
				fprintf(stderr, "systemeCouplage : chronomètre = %f \n", (*systeme).foule.horloge);
				}
			if(X<0 || X>BATIMENT_X)
				{
				//fprintf(stderr, "systemeCouplage : humain hors batiment.\n");
				iter->humain.nouveau.z=-1;
				}
			else
				{
				if(Y<0 || Y>BATIMENT_Y)
					{
					//fprintf(stderr, "systemeCouplage : humain hors batiment.\n");
					iter->humain.nouveau.z=-1;
					}
				else	// Calcul du couplage si l'humain est à l'étage.
					{
					humainCouplage(&(iter->humain), &(*systeme).batiment.etage[Z].cellule[X][Y].sens);
					}
				}
			}
		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);
	return 0;
	}

