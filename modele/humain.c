/*
Copyright janvier 2018, Stephan Runigo
runigo@free.fr
SimFoule 1.2  simulateur de foule
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


#include "../modele/humain.h"

int humainMemeEtage(humainT * humain1, humainT * humain2);
	// = 0 si etage différent, 1 si même étage, -1 si sortie
int humainDistanceArithmetique(humainT * humain1, humainT * humain2);
	// En pixel, retourne la distance arithmétique (dx+dy)

int humainInitialise(humainT * humain, float masse, float nervosite, float dt)
	{
	int retour = 0;

	vecteurCartesien(&(*humain).vitesse, 0, 0, 0);
	vecteurCartesien(&(*humain).vitesseSouhaite, 0, 0, 0);
	vecteurCartesien(&(*humain).forceBatiment, 0, 0, 0);
	vecteurCartesien(&(*humain).forceHumains, 0, 0, 0);
	vecteurCartesien(&(*humain).forceMurs, 0, 0, 0);
	vecteurCartesien(&(*humain).sommeForces, 0, 0, 0);

	retour += humainInitialisePosition(humain, 0, 0, 0);
	retour += humainInitialiseCaractere(humain, masse, nervosite, dt);

	return retour;
	}

int humainInitialisePosition(humainT * humain, float x, float y, int z)
	{
	vecteurCartesien(&(*humain).nouveau, x, y, z);
	vecteurCartesien(&(*humain).actuel, x, y, z);
	vecteurCartesien(&(*humain).ancien, x, y, z);

	return 0;
	}

int humainInitialiseCaractere(humainT * humain, float masse, float nervosite, float dt)
	{
	int retour = 0;

	(*humain).masse = 66.999;
	(*humain).nervosite = 0.999;
	(*humain).dt = 0.000333;

	if( masse > MASSE_MIN && masse < MASSE_MAX )
		(*humain).masse = masse;
	else retour ++;

	if( nervosite > NERVOSITE_MIN && nervosite < NERVOSITE_MAX )
		(*humain).nervosite = nervosite;
	else retour ++;

	if( dt > DT_MIN && dt < DT_MAX )
		(*humain).dt = dt;
	else retour ++;

	(*humain).dtsurtau = dt*nervosite;
	(*humain).dt2surM = dt*dt/(*humain).masse;

	return retour;
	}

float humainCalculVitesse(humainT * humain)
	{	// vitesse = nouveau - ancien = vitesse en unité de dt
	vecteurDifferenceCartesien2D(&(*humain).nouveau, &(*humain).actuel, &(*humain).vitesse); // v3 = v1 - v2
	return sqrt(vecteurScalaireCartesien2D(&(*humain).vitesse, &(*humain).vitesse));
	}

int humainIncremente(humainT * humain)
	{
	vecteurCartesienEgale(&(*humain).actuel, &(*humain).ancien); // v2 = v1
	vecteurCartesienEgale(&(*humain).nouveau, &(*humain).actuel); // v2 = v1
	return 0;
	}

int humainInertie(humainT * humain)
	{// nouveau = 2 actuel - ancien + somme des forces

		// nouveau = 2 actuel - ancien
	vecteurSommeCartesien2D(&(*humain).actuel, &(*humain).actuel, &(*humain).nouveau); // v3 = v1 + v2
	vecteurDifferenceCartesien2D(&(*humain).nouveau, &(*humain).ancien, &(*humain).nouveau); // v3 = v1 - v2


		// nouveau += somme des forces
	vecteurSommeCartesien2D(&(*humain).sommeForces, &(*humain).nouveau, &(*humain).nouveau); // v3 = v1 + v2
	
	return 0;
	}

int humainCouplage(humainT * humain, vecteurT * vitesseSouhaite)
	{
		// vitesse = nouveau - actuel
	vecteurDifferenceCartesien2D(&(*humain).nouveau, &(*humain).actuel, &(*humain).vitesse); // v3 = v1 - v2

		// vitesseSouhaite = dt vitesseSouhaite
	vecteurProduitCartesien2D(vitesseSouhaite, (*humain).dt, &(*humain).vitesseSouhaite); // v2 = lambda v1

		// force = vitesse souhaite - vitesse (le tout fois dt)
	vecteurDifferenceCartesien2D(&(*humain).vitesseSouhaite, &(*humain).vitesse, &(*humain).forceBatiment); // v3 = v1 - v2

		//  force = dtsurtau * FORCE_COUPLAGE * force
	vecteurProduitCartesien2D(&(*humain).forceBatiment, (*humain).dtsurtau, &(*humain).forceBatiment); // v2 = lambda v1
	return 0;
	}

int humainMemeEtage(humainT * humain1, humainT * humain2)
	{	// = 0 si étage différent, 1 si même étage, -1 si sortie
	int meme = 0;
	if((*humain1).nouveau.z == -1 || (*humain2).nouveau.z == -1)
		meme = -1;
	else
		if((*humain1).nouveau.z == (*humain2).nouveau.z)
			meme = 1;

	return meme;
	}

int humainDistanceArithmetique(humainT * humain1, humainT * humain2)
	{	// En pixel, retourne la distance arithmétique (dx+dy)
	int X = (*humain1).nouveau.x == (*humain2).nouveau.x;
	int Y = (*humain1).nouveau.y == (*humain2).nouveau.y;
	if(X<0)
		X=-X;
	if(Y<0)
		Y=-Y;
	return X+Y;
	}

int humainProximite(humainT * humain1, humainT * humain2)
	{
	int proche = 0;
	if(humainMemeEtage(humain1, humain2)==1)
		if(humainDistanceArithmetique(humain1, humain2) < INTERACTION_HUMAIN)
			proche = 1;
	return proche;
	}

float humainAjouteForceHumain(humainT * humain1, humainT * humain2)
	{
	float force = 0;
	vecteurT vecteur; // r = actuel1 - actuel2  puis normalisation
	vecteurCartesien(&vecteur, 0, 0, 0);

		// Vecteur = nouveau1 - nouveau2
	vecteurDifferenceCartesien2D(&(*humain1).nouveau, &(*humain2).nouveau, &vecteur); // v3 = v1 - v2

		// Vecteur = unitaire (nouveau1 - nouveau2)
	float distance = vecteurNormaliseCartesien2D(&vecteur); // normalise, renvoie la norme initiale

	if(distance<HUMAINetDEMI)
		{
		force = FORCE_CONTACT_HUMAIN*(*humain1).dt2surM * (HUMAINetDEMI - distance); // norme de la force

			// Vecteur = force * unitaire
		vecteurProduitCartesien2D(&vecteur, force, &vecteur); // v2 = lambda v1

			// Ajoute la force sur 1
		vecteurSommeCartesien2D(&(*humain1).forceHumains, &vecteur, &(*humain1).forceHumains); // v3 = v1 + v2

			// Vecteur = - vecteur
		vecteurProduitCartesien2D(&vecteur, force, &vecteur); // v2 = lambda v1

			// Ajoute la force sur 2
		vecteurSommeCartesien2D(&(*humain2).forceHumains, &vecteur, &(*humain2).forceHumains); // v3 = v1 + v2
		}

	return force;
	}

float humainAjouteForceMur(humainT * humain, int DX, int DY, vecteurT * angle)
	{
	float force = 0;
		// Position de l'humain
	float x = (*humain).nouveau.x;
	float y = (*humain).nouveau.y;
		// Position de la cellule
	int X = (int)(x/CELLULE);
	int Y = (int)(y/CELLULE);
		// vecteur temporaire
	vecteurT vecteur; // r = actuel1 - actuel2  puis normalisation

		// vecteur = position du mur
	if(DX==0)
		vecteurCartesien(&vecteur, x, Y*CELLULE + CELLULESUR2 + DY*CELLULESUR2, 0);
	if(DY==0)
		vecteurCartesien(&vecteur, X*CELLULE + CELLULESUR2 + DX*CELLULESUR2, y, 0);
	if(DX!=0 && DY!=0)
		vecteurCartesien(&vecteur, X*CELLULE + CELLULESUR2 + DX*CELLULESUR2, Y*CELLULE + CELLULESUR2 + DY*CELLULESUR2, 0);

		// Vecteur = nouveau - mur
	vecteurDifferenceCartesien2D(&(*humain).nouveau, &vecteur, &vecteur); // v3 = v1 - v2
		// Vecteur = unitaire (nouveau - mur)
	float distance = vecteurNormaliseCartesien2D(&vecteur); // normalise, renvoie la norme initiale

	if(distance<HUMAIN) // SUR2
		{
		force = FORCE_CONTACT_MUR*(*humain).dt2surM*(HUMAIN - distance); // norme de la forceSUR2

			// Vecteur = force * unitaire
		vecteurProduitCartesien2D(angle, force, &vecteur); // v2 = lambda v1

			// Ajoute la force sur 1
		vecteurSommeCartesien2D(&(*humain).forceMurs, &vecteur, &(*humain).forceMurs); // v3 = v1 + v2
		}

	return force;
	}

int humainAffiche(humainT * humain)
	{
	fprintf(stderr, "\nAffiche humain\n");
	fprintf(stderr, "  nouveau x : %f , actuel x : %f, ancien x : %f\n", (*humain).nouveau.x, (*humain).actuel.x, (*humain).nouveau.x);
	fprintf(stderr, "  nouveau y : %f , actuel y : %f, ancien y : %f\n", (*humain).nouveau.y, (*humain).actuel.y, (*humain).nouveau.y);

	fprintf(stderr, "  vitesse x : %f , vitesse y : %f\n", (*humain).vitesse.x, (*humain).vitesse.y);
	fprintf(stderr, "  vitesseSouhaite x : %f , vitesseSouhaite y : %f\n", (*humain).vitesseSouhaite.x, (*humain).vitesseSouhaite.y);
	fprintf(stderr, "  forceExterieur x : %f , forceExterieur y : %f\n\n", (*humain).forceBatiment.x, (*humain).forceBatiment.y);
	return 0;
	}

/*

void vecteurCartesien(vecteurT * v, float x, float y, int z);
void vecteurCartesienEgale(vecteurT * v1, vecteurT * v2); // v2 = v1
float vecteurScalaireCartesien(vecteurT * v1, vecteurT * v2);
void vecteurProduitCartesien(vecteurT * v1, vecteurT * v2);
void vecteurSommeCartesien(vecteurT * v1, vecteurT * v2, vecteurT * v3); // v3 = v1 + v2
void vecteurDifferenceCartesien(vecteurT * v1, vecteurT * v2, vecteurT * v3); // v3 = v1 - v2
	vecteurT nouveau;
	vecteurT actuel;
	vecteurT ancien;

	vecteurT vitesse;
	vecteurT vitesseSouhaite;
	vecteurT forceExterieur;

	float masse;
	float nervosite;
*/

///////////////////////////////////////////////////////////////////////////
