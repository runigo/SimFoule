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


#include "systeme.h"


int systemeSortieMobile(systemeT * systeme, mobileT * mobile); // Le mobile a ateint une sortie.
int systemeAbandonMobile(systemeT * systeme, mobileT * mobile); // Diminue la vitalité et supprimme.

int systemeCorrigeMur(systemeT * systeme);	// Correction des nouvelles positions

float systemeForceBatiment(systemeT * systeme); // Calcul de la force de couplage avec le batiment
float systemeForceMurs(systemeT * systeme); // Calcul de la force de couplage avec les mur

float systemeVitessesSouhaitees(systemeT * systeme); // Calcul des vitesses souhaitées
float systemeVitesseSouhaiteeMobile(etageT * etage, int X, int Y, mobileT * mobile); // Calcul de la vitesse souhaitée
int systemeCalculDensite(systemeT * systeme); // Initialisation du nombre de mobile par cellule
int systemeMiseAJourNoteCellule(etageT * etage, int X, int Y);

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
	float forceBatiment = 0;
	float forceMobiles = 0;
	float forceMurs = 0;
	float forceSomme = 0;

	//	Fait évoluer le système pendant duree*dt
	for(i=0;i<duree;i++)
		{
			// Déplacement inertiel
		fouleInertie(&(*systeme).foule);

			// Correction des nouvelles positions
		systemeCorrigeMur(systeme);

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

	do	// Remise à zéro
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
		for(etage=0;etage<(*systeme).batiment.batimentZ;etage++)
			{
			if(Z==etage)
				{
				if(X>0)
					{
					if((*systeme).batiment.etage[Z].cellule[X-1][Y].statut==1)
						force = mobileAjouteForceMur(&iter->mobile, -1, 0, &(*systeme).batiment.etage[etage].angle[0]);
					if(Y>0)
						if((*systeme).batiment.etage[Z].cellule[X-1][Y-1].statut==1)
							force = mobileAjouteForceMur(&iter->mobile, -1, -1, &(*systeme).batiment.etage[etage].angle[1]);
					if(Y<(*systeme).batiment.etage[etage].etageY-1)
						if((*systeme).batiment.etage[Z].cellule[X-1][Y+1].statut==1)
						force = mobileAjouteForceMur(&iter->mobile, -1, 1, &(*systeme).batiment.etage[etage].angle[7]);
					}
				if(Y>0)
					if((*systeme).batiment.etage[Z].cellule[X][Y-1].statut==1)
						force = mobileAjouteForceMur(&iter->mobile, 0, -1, &(*systeme).batiment.etage[etage].angle[2]);
				if(X<(*systeme).batiment.etage[etage].etageX-1)
					{
					if((*systeme).batiment.etage[Z].cellule[X+1][Y].statut==1)
						force = mobileAjouteForceMur(&iter->mobile, 1, 0, &(*systeme).batiment.etage[etage].angle[4]);
					if(Y>0)
						if((*systeme).batiment.etage[Z].cellule[X+1][Y-1].statut==1)
							force = mobileAjouteForceMur(&iter->mobile, 1, -1, &(*systeme).batiment.etage[etage].angle[3]);
					if(Y<(*systeme).batiment.etage[etage].etageY-1)
						if((*systeme).batiment.etage[Z].cellule[X+1][Y+1].statut==1)
							force = mobileAjouteForceMur(&iter->mobile, 1, 1, &(*systeme).batiment.etage[etage].angle[5]);
					}
				if(Y<(*systeme).batiment.etage[etage].etageY-1)
					if((*systeme).batiment.etage[Z].cellule[X][Y+1].statut==1)
						force = mobileAjouteForceMur(&iter->mobile, 0, 1, &(*systeme).batiment.etage[etage].angle[6]);
				}
			}
		if(force>forceMax)
			forceMax = force;
		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	return forceMax;
	}

float systemeForceBatiment(systemeT * systeme)
	{ // Calcul de la force liée à la vitesse souhaité
	chaineT *iter;
	iter = (*systeme).foule.premier;
	float force = 0;
	float forceMax = 0;

			//fprintf(stderr, "   Calcul du nombre de mobile par cellule\n");
	systemeCalculDensite(systeme);

			//fprintf(stderr, "   Calcul de la vitesse souhaitée\n");
	systemeVitessesSouhaitees(systeme);

			//fprintf(stderr, "   Calcul de la force liée à la vitesse souhaité\n");
	do
		{
		force = mobileCouplage(&(iter->mobile), &(iter->mobile.vitesseSouhaitee));
		if(force>forceMax) forceMax = force;
		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	return forceMax;
	}

int systemeAbandonMobile(systemeT * systeme, mobileT * mobile)
	{ // Diminue la vitalité et supprimme.

	if(mobileChangeVivacite(mobile, 1) < 0) // le mobile est hors service
		{
		(*mobile).nouveau.z=-2; // Abandon du mobile.
		(*systeme).foule.restant--;
		}

	return 0;
	}

int systemeSortieMobile(systemeT * systeme, mobileT * mobile)
	{ // Le mobile a ateint une sortie.

	(*mobile).nouveau.z--;
	(*systeme).foule.restant--;

					//fprintf(stderr, "systemeSortieMobile : Sortie d'un mobile \n");
					//fprintf(stderr, "systemeSortieMobile : Il en reste %d dans le batiment \n", (*systeme).foule.restant);
					//fprintf(stderr, "systemeSortieMobile : chronomètre = %f \n", (*systeme).foule.horloge);
	return 0;
	}

float systemeVitessesSouhaitees(systemeT * systeme)
	{ // Calcul de la vitesse souhaité
	int X, Y, Z;
	chaineT *iter;
	iter = (*systeme).foule.premier;
	float vitesseSouhaite=0.0;

	do	// Calcul des vitesses souhaitées
		{
			// Coordonnée de la cellule
		X = (int)(iter->mobile.nouveau.x/CELLULE);
		Y = (int)(iter->mobile.nouveau.y/CELLULE);
		Z = iter->mobile.nouveau.z;

		if(Z>-1 && Z<(*systeme).batiment.batimentZ) // Le mobile est dans un étage
			{
			if( X<0 || X>(*systeme).batiment.etage[Z].etageX || Y<0 || Y>(*systeme).batiment.etage[Z].etageY ) // Mobile hors batiment sans passer par une sortie
				{
				fprintf(stderr, "ERREUR : systemeVitessesSouhaitees : mobile hors batiment sans passer par une sortie.\n");
				systemeAbandonMobile(systeme, &(iter->mobile));
				}
			else
				{
				if((*systeme).batiment.etage[Z].cellule[X][Y].statut==2) // le mobile a atteint une sortie
					{
					systemeSortieMobile(systeme, &(iter->mobile));
					}
				else
					{	// Initialisation de la vitesse souhaitée	// Calcul de la vitesse souhaitée
					systemeVitesseSouhaiteeMobile(&(*systeme).batiment.etage[Z], X, Y, &(iter->mobile));
					}
				}
			}
		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	return vitesseSouhaite;
	}

float systemeVitesseSouhaiteeMobile(etageT * etage, int X, int Y, mobileT * mobile)
	{ // Calcul de la vitesse souhaitée
	int i;
	int indexMax = 0;
	float max = 0.0;
	float vitesse = 1.0;

		// Recherche de la meilleur note
	for(i=0;i<8;i++)
		{
		if((*etage).cellule[X][Y].note[i]>max)
			{
			indexMax = i;
			max = (*etage).cellule[X][Y].note[i];
			}
		}

	vecteurEgaleCartesien(&(*etage).angle[indexMax], &(*mobile).vitesseSouhaitee); // v2 = v1

	vitesse = (*mobile).celerite*max;

	vecteurProduitCartesien(&(*mobile).vitesseSouhaitee, vitesse, &(*mobile).vitesseSouhaitee); // v2 = lambda v1


	(*etage).cellule[X][Y].sens = indexMax;

	return vitesse;
	}

int systemeCorrigeMur(systemeT * systeme)
	{	// Vérification et correction des nouvelles positions

	int X, Y, Z;
	chaineT *iter;
	iter = (*systeme).foule.premier;


	do
		{
		X = (int)(iter->mobile.nouveau.x/CELLULE);
		Y = (int)(iter->mobile.nouveau.y/CELLULE);
		Z = iter->mobile.nouveau.z;

		if(Z>-1 && Z<(*systeme).batiment.batimentZ)
			{
			if(X>-1 && X<(*systeme).batiment.etage[Z].etageX && Y>-1 && Y<(*systeme).batiment.etage[Z].etageY)
				{
				if((*systeme).batiment.etage[Z].cellule[X][Y].statut == 1)
					{
					iter->mobile.nouveau.x = iter->mobile.actuel.x;
					iter->mobile.nouveau.y = iter->mobile.actuel.y;
					if(mobileImpactVivacite(&(iter->mobile)) != 0) (*systeme).foule.restant--;
					}
				}
			else
				{
				fprintf(stderr, "ERREUR systemeCorrigeMur : XYZ = %d, %d, %d \n", X, Y, Z);
				systemeAbandonMobile(systeme, &(iter->mobile));
				}
			}

		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	//fprintf(stderr, "systemeCalculDensite, sortie\n");

	return 0;
	}

int systemeCalculDensite(systemeT * systeme)
	{	// Initialisation du nombre de mobile par cellule
		// et mise à jour de la note
	int X, Y, Z;
	chaineT *iter;
	iter = (*systeme).foule.premier;

	//fprintf(stderr, "systemeCalculDensite, entrée\n");

		// Mise à zéro du nombre de mobile par cellule
	batimentMiseAZeroNombre(&(*systeme).batiment);

	do
		{
		X = (int)(iter->mobile.nouveau.x/CELLULE);
		Y = (int)(iter->mobile.nouveau.y/CELLULE);
		Z = iter->mobile.nouveau.z;

		if(Z>-1 && Z<(*systeme).batiment.batimentZ)
			{
			if(X>-1 && X<(*systeme).batiment.etage[Z].etageX && Y>-1 && Y<(*systeme).batiment.etage[Z].etageY)
				{
				(*systeme).batiment.etage[Z].cellule[X][Y].nombre++;
				}
			else
				{
				fprintf(stderr, "ERREUR systemeCalculDensite, premier do-while, XYZ = %d, %d, %d \n", X, Y, Z);
				systemeAbandonMobile(systeme, &(iter->mobile));
				}
			}

		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	do
		{
		X = (int)(iter->mobile.nouveau.x/CELLULE);
		Y = (int)(iter->mobile.nouveau.y/CELLULE);
		Z = iter->mobile.nouveau.z;

		if(Z>-1 && Z<(*systeme).batiment.batimentZ)
			{
			if(X>-1 && X<(*systeme).batiment.etage[Z].etageX && Y>-1 && Y<(*systeme).batiment.etage[Z].etageY)
				{
				systemeMiseAJourNoteCellule(&(*systeme).batiment.etage[Z], X, Y);
				}
			else
				{
				fprintf(stderr, "ERREUR systemeCalculDensite, second do-while : XYZ = %d, %d, %d \n", X, Y, Z);
				systemeAbandonMobile(systeme, &(iter->mobile));
				}
			}

		iter=iter->suivant;
		}
	while(iter!=(*systeme).foule.premier);

	//fprintf(stderr, "systemeCalculDensite, sortie\n");

	return 0;
	}

int systemeMiseAJourNoteCellule(etageT * etage, int X, int Y)
	{	// Mise à jour de la note de la cellule X Y
	if(X<(*etage).etageX-1)
		{
		(*etage).cellule[X][Y].note[0] = (*etage).cellule[X][Y].interet[0] - (*etage).cellule[X+1][Y].nombre;
		if(Y<(*etage).etageY)
			{
			(*etage).cellule[X][Y].note[1] = (*etage).cellule[X][Y].interet[1] - (*etage).cellule[X+1][Y+1].nombre;
			}
		if(Y>0)
			{
			(*etage).cellule[X][Y].note[7] = (*etage).cellule[X][Y].interet[7] - (*etage).cellule[X+1][Y-1].nombre;
			}
		}
	if(X>0)
		{
		(*etage).cellule[X][Y].note[4] = (*etage).cellule[X][Y].interet[4] - (*etage).cellule[X-1][Y].nombre;
		if(Y<(*etage).etageY)
			{
			(*etage).cellule[X][Y].note[3] = (*etage).cellule[X][Y].interet[3] - (*etage).cellule[X-1][Y+1].nombre;
			}
		if(Y>0)
			{
			(*etage).cellule[X][Y].note[5] = (*etage).cellule[X][Y].interet[5] - (*etage).cellule[X-1][Y-1].nombre;
			}
		}
	if(Y<(*etage).etageY-1)
		{
		(*etage).cellule[X][Y].note[2] = (*etage).cellule[X][Y].interet[2] - (*etage).cellule[X][Y+1].nombre;
		}
	if(Y>0)
		{
		(*etage).cellule[X][Y].note[6] = (*etage).cellule[X][Y].interet[6] - (*etage).cellule[X][Y-1].nombre;
		}
	return 0;
	}

/////////////////////////////////////////////////////////////////////////////////:
