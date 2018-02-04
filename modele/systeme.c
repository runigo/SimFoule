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


#include "systeme.h"


float systemeForceBatiment(systemeT * systeme); // Calcul de la force de couplage avec le batiment
float systemeForceMurs(systemeT * systeme); // Calcul de la force de couplage avec les mur
		
int systemeCalculDensite(systemeT * systeme); // Initialisation du nombre de mobile par cellule

int systemeInitialisation(systemeT * systeme, float dt)
	{
	(*systeme).dt = dt;		//	Discétisation du temps
	(*systeme).horloge = 0;		//	Horloge, chronomètre

		// Valeurs des forces les plus grandes
	(*systeme).forceBatimentMax = 0;
	(*systeme).forceMobilesMax = 0;
	(*systeme).forceMursMax = 0;
	(*systeme).forceSommeMax = 0;

	return 0;
	}


int systemeEvolution(systemeT * systeme, int duree)
	{ // Évolution temporelle de la foule, "duree" cycle d'évolution
	int i;
		// Vérification des valeurs les plus grandes
	float forceBatiment;
	float forceMobiles;
	float forceMurs;
	float forceSomme;

	//	Fait évoluer le système pendant duree*dt
	for(i=0;i<duree;i++)
		{
			// Déplacement inertiel
		fouleInertie(&(*systeme).foule);

			// Calcul des forces dans la  nouvelle situation
			//fprintf(stderr, "systemeForceBatiment\n");
		forceBatiment = systemeForceBatiment(systeme);
			//fprintf(stderr, "fouleForceMobiles\n");
		forceMobiles = fouleForceMobiles(&(*systeme).foule);
			//fprintf(stderr, "systemeForceMurs\n");
		forceMurs = systemeForceMurs(systeme);
			//fprintf(stderr, "fouleSommeForces\n");
		forceSomme = fouleSommeForces(&(*systeme).foule);

			// Enregistrement des valeurs les plus grandes
		if((*systeme).forceBatimentMax < forceBatiment) (*systeme).forceBatimentMax = forceBatiment;
		if((*systeme).forceMobilesMax < forceMobiles) (*systeme).forceMobilesMax = forceMobiles;
		if((*systeme).forceMursMax < forceMurs) (*systeme).forceMursMax = forceMurs;
		if((*systeme).forceSommeMax < forceSomme) (*systeme).forceSommeMax = forceSomme;
			// Incrémentation
		fouleIncremente(&(*systeme).foule);
		}

	//mobileAffiche(&(*systeme).foule.premier->mobile);

	return 0;
	}



float systemeForceMurs(systemeT * systeme)
	{ // Calcul des forces de contact avec les murs
	int X, Y, Z;
	int etage;
	chaineT *iter;
	iter = (*systeme).foule.premier;
	float force=0;
	float forceMax=0;

		// Remise à zéro
	do
		{
		vecteurCartesien(&iter->mobile.forceMurs, 0.0, 0.0, 0.0);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	do
		{
		X = (int)(iter->mobile.nouveau.x/CELLULE); // Position i de la cellule
		Y = (int)(iter->mobile.nouveau.y/CELLULE); // Position j de la cellule
		Z = iter->mobile.nouveau.z;
		for(etage=0;etage<BATIMENT_Z;etage++)
			{
			if(Z==etage)
				{
				if((*systeme).batiment.etage[Z].cellule[X-1][Y].statut==1)
					force = mobileAjouteForceMur(&iter->mobile, -1, 0, &(*systeme).batiment.etage[etage].angle[0]);
				if((*systeme).batiment.etage[Z].cellule[X-1][Y-1].statut==1)
					force = mobileAjouteForceMur(&iter->mobile, -1, -1, &(*systeme).batiment.etage[etage].angle[1]);
				if((*systeme).batiment.etage[Z].cellule[X][Y-1].statut==1)
					force = mobileAjouteForceMur(&iter->mobile, 0, -1, &(*systeme).batiment.etage[etage].angle[2]);
				if((*systeme).batiment.etage[Z].cellule[X+1][Y-1].statut==1)
					force = mobileAjouteForceMur(&iter->mobile, 1, -1, &(*systeme).batiment.etage[etage].angle[3]);
				if((*systeme).batiment.etage[Z].cellule[X+1][Y].statut==1)
					force = mobileAjouteForceMur(&iter->mobile, 1, 0, &(*systeme).batiment.etage[etage].angle[4]);
				if((*systeme).batiment.etage[Z].cellule[X+1][Y+1].statut==1)
					force = mobileAjouteForceMur(&iter->mobile, 1, 1, &(*systeme).batiment.etage[etage].angle[5]);
				if((*systeme).batiment.etage[Z].cellule[X][Y+1].statut==1)
					force = mobileAjouteForceMur(&iter->mobile, 0, 1, &(*systeme).batiment.etage[etage].angle[6]);
				if((*systeme).batiment.etage[Z].cellule[X-1][Y+1].statut==1)
					force = mobileAjouteForceMur(&iter->mobile, -1, 1, &(*systeme).batiment.etage[etage].angle[7]);
				}
			}
		if(force>forceMax) forceMax = force;
		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	return forceMax;
	}

float systemeForceBatiment(systemeT * systeme)
	{ // Calcul de la force liée à la vitesse souhaité
	int X, Y, Z;
	chaineT *iter;
	iter = (*systeme).foule.premier;
	float force = 0;
	float forceMax = 0;
	int angle;
	int dx, dy;
	int nombreX = 0; // nombre de mobile dans les cellules à ateindre
	int nombreY = 0; // nombre de mobile dans les cellules à ateindre
	int nombreXY = 0; // nombre de mobile dans les cellules à ateindre

		// Initialisation du nombre de mobile par cellule
	systemeCalculDensite(systeme);

	do	// Calcul de la vitesse souhaitée
		{
		X = (int)(iter->mobile.nouveau.x/CELLULE);
		Y = (int)(iter->mobile.nouveau.y/CELLULE);
		Z = iter->mobile.nouveau.z;
		if(Z>-1 && Z<BATIMENT_Z) // Le mobile est dans un étage
			{
			if( X<0 || X>BATIMENT_X || Y<0 || Y>BATIMENT_Y ) // Mobile hors batiment sans passer par une sortie
				{
				fprintf(stderr, "ERREUR : systemeCouplage : mobile hors batiment sans passer par une sortie.\n");
				iter->mobile.nouveau.z=-1; // Abandon du mobile.
				}
			else
				{
				if((*systeme).batiment.etage[Z].cellule[X][Y].statut==2) // le mobile a atteint une sortie
					{
					fprintf(stderr, "systemeCouplage : Sortie d'un mobile \n");
					iter->mobile.nouveau.z--;
					(*systeme).foule.restant--;
					fprintf(stderr, "systemeCouplage : Il en reste %d dans le batiment \n", (*systeme).foule.restant);
					fprintf(stderr, "systemeCouplage : chronomètre = %f \n", (*systeme).foule.horloge);
					}
				else
					{	// Calcul du couplage.
					angle = (*systeme).batiment.etage[Z].cellule[X][Y].angle;

						// Première initialisation de la vitesse souhaitée
					vecteurEgaleCartesien(&(*systeme).batiment.etage[Z].cellule[X][Y].sens, &(iter->mobile.vitesseSouhaite)); // v2 = v1

					if(angle%2==1)	// diagonale : 3 possibilité de vitesse souhaité
						{
						dx = (*systeme).batiment.etage[Z].cellule[X][Y].dx;
						dy = (*systeme).batiment.etage[Z].cellule[X][Y].dy;
							// Nombre de mobile dans les cellules à ateindre
							// (int)(2*souhaite.x)(int)(2*souhaite.y)
						nombreX = (*systeme).batiment.etage[Z].cellule[X+dx][Y].nombre;
						nombreY = (*systeme).batiment.etage[Z].cellule[X][Y+dy].nombre;
						nombreXY = (*systeme).batiment.etage[Z].cellule[X+dx][Y+dy].nombre;

							// Recherche de la cellule la moins dense
						if(nombreXY < nombreX && nombreXY < nombreY)
							{	// Vitesse souhaité = diagonale
							vecteurEgaleCartesien(&(*systeme).batiment.etage[Z].cellule[X][Y].sens, &(iter->mobile.vitesseSouhaite));
							}
						else	// vitesse souhaité = voisin direct X ou Y
							{
							if(nombreX<nombreY)
								{
								//vecteurEgaleCartesien(&(*systeme).batiment.etage[Z].cellule[X][Y].sens, &souhaite);
								vecteurEgaleCartesien(&(*systeme).batiment.etage[Z].cellule[X][Y].sens1, &(iter->mobile.vitesseSouhaite));
								}
							else
								{
								//vecteurEgaleCartesien(&(*systeme).batiment.etage[Z].cellule[X][Y].sens, &souhaite);
								vecteurEgaleCartesien(&(*systeme).batiment.etage[Z].cellule[X][Y].sens2, &(iter->mobile.vitesseSouhaite));
								}
							}
						}
					}
				}
			}
		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	do	// 
		{
		force = mobileCouplage(&(iter->mobile), &(iter->mobile.vitesseSouhaite));
		if(force>forceMax) forceMax = force;
		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	return forceMax;
	}

		
int systemeCalculDensite(systemeT * systeme)
	{	// Initialisation du nombre de mobile par cellule
	int X, Y, Z;
	chaineT *iter;
	iter = (*systeme).foule.premier;

		// Mise à zéro du nombre de mobile par cellule
	batimentMiseAZeroNombre(&(*systeme).batiment);

	do
		{
		X = (int)(iter->mobile.nouveau.x/CELLULE);
		Y = (int)(iter->mobile.nouveau.y/CELLULE);
		Z = iter->mobile.nouveau.z;

		if(Z>-1 && Z<BATIMENT_Z)
			(*systeme).batiment.etage[Z].cellule[X][Y].nombre++;

		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	return 0;
	}

