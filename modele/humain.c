/*
Copyright décembre 2017, Stephan Runigo
runigo@free.fr
SimFoule 0.0  simulateur de foule
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

int humainInitialise(humainT * humain, float masse, float nervosite, float dt)
	{
	int retour = 0;

	vecteurCartesien(&(*humain).vitesse, 0, 0, 0);
	vecteurCartesien(&(*humain).vitesseSouhaite, 0, 0, 0);
	vecteurCartesien(&(*humain).forceExterieur, 0, 0, 0);

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
	(*humain).dtsurtau = dt*nervosite;

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

	return retour;
	}

float humainCalculVitesse(humainT * humain)
	{	// vitesse = nouveau - ancien = vitesse en unité de dt
	vecteurDifferenceCartesien(&(*humain).nouveau, &(*humain).actuel, &(*humain).vitesse); // v3 = v1 - v2
	return sqrt(vecteurScalaireCartesien(&(*humain).vitesse, &(*humain).vitesse));
	}

int humainIncremente(humainT * humain)
	{
	vecteurCartesienEgale(&(*humain).actuel, &(*humain).ancien); // v2 = v1
	vecteurCartesienEgale(&(*humain).nouveau, &(*humain).actuel); // v2 = v1
	return 0;
	}

int humainInertie(humainT * humain)
	{
		// nouveau = 2 actuel - ancien + force
	vecteurSommeCartesien(&(*humain).actuel, &(*humain).actuel, &(*humain).nouveau); // v3 = v1 + v2
	vecteurDifferenceCartesien(&(*humain).nouveau, &(*humain).ancien, &(*humain).nouveau); // v3 = v1 - v2
	vecteurSommeCartesien(&(*humain).forceExterieur, &(*humain).nouveau, &(*humain).nouveau); // v3 = v1 + v2
	return 0;
	}

int humainCouplage(humainT * humain, vecteurT * vitesseSouhaite)
	{
		// vitesse = nouveau - actuel
	vecteurDifferenceCartesien(&(*humain).nouveau, &(*humain).actuel, &(*humain).vitesse); // v3 = v1 - v2

		// vitesseSouhaite = dt vitesseSouhaite
	vecteurProduitCartesien(vitesseSouhaite, (*humain).dt, &(*humain).vitesseSouhaite); // v2 = lambda v1

		// force = vitesse souhaite - vitesse (le tout fois dt)
	vecteurDifferenceCartesien(&(*humain).vitesseSouhaite, &(*humain).vitesse, &(*humain).forceExterieur); // v3 = v1 - v2

		//  force = dtsurtau force
	vecteurProduitCartesien(&(*humain).forceExterieur, (*humain).dtsurtau, &(*humain).forceExterieur); // v2 = lambda v1
	return 0;
	}

int humainAffiche(humainT * humain)
	{
	fprintf(stderr, "\nAffiche humain\n");
	fprintf(stderr, "  nouveau x : %f , actuel x : %f, ancien x : %f\n", (*humain).nouveau.x, (*humain).actuel.x, (*humain).nouveau.x);
	fprintf(stderr, "  nouveau y : %f , actuel y : %f, ancien y : %f\n", (*humain).nouveau.y, (*humain).actuel.y, (*humain).nouveau.y);

	fprintf(stderr, "  vitesse x : %f , vitesse y : %f\n", (*humain).vitesse.x, (*humain).vitesse.y);
	fprintf(stderr, "  vitesseSouhaite x : %f , vitesseSouhaite y : %f\n", (*humain).vitesseSouhaite.x, (*humain).vitesseSouhaite.y);
	fprintf(stderr, "  forceExterieur x : %f , forceExterieur y : %f\n\n", (*humain).forceExterieur.x, (*humain).forceExterieur.y);
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
