/*
Copyright janvier 2018, Stephan Runigo
runigo@free.fr
SimFoule 1.2.1  simulateur de foule
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


#include "foule.h"

int fouleInitialiseHumain(fouleT * foule);
void fouleInitialiseLimiteInfini(fouleT * foule);
void fouleCouplage(fouleT * foule);
void fouleCourantLimite(fouleT * foule);

//void fouleJaugeZero(fouleT * foule);

/*--------------------------------------------------------------*/

int fouleCreation(fouleT * foule)
	{
	(*foule).premier = chaineCreation((*foule).nombre);

	if((*foule).premier!=NULL)
		{
		fprintf(stderr, "    Chaîne créée\n");
		}
	else
		{
		fprintf(stderr, "\n\nfouleCreation : Echec de chaineCreation\n\n");
		}

	fouleInitialiseHumain(foule);

	return 0;
	}

int fouleSuppression(fouleT * foule)
	{
	printf("    Suppression de la chaine\n");
	chaineSupprime(&(*foule).premier);
	//printf("  Chaine supprimée\n");
	return 0;
	}

/*------------------------------------------------------------------*/

int fouleInitialiseHumain(fouleT * foule)
	{
	chaineT *iter=(*foule).premier;

	do
		{
		humainInitialise(&iter->humain, (*foule).masse, (*foule).nervosite, (*foule).dt);
		iter=iter->suivant;
		}
	while(iter != (*foule).premier);

	return 0;
	}

//------------------------  ÉVOLUTION TEMPORELLE  -------------------------

int fouleIncremente(fouleT * foule)
	{//	incremente l'horloge, l'ancien et l'actuel etat de la foule

	(*foule).horloge=(*foule).horloge+(*foule).dt;

	chaineT *iter;
	iter=(*foule).premier;

	do
		{
		humainIncremente(&(iter->humain));
		iter=iter->suivant;
		}
	while (iter!=(*foule).premier);

	return 0;
	}

int fouleInertie(fouleT * foule)
	{//	Principe d'inertie appliqué à la foule

	chaineT *iter;
	iter = (*foule).premier;

	do
		{
		if((iter->humain).nouveau.z!=-1)
			humainInertie(&(iter->humain));
		iter=iter->suivant;
		}
	while(iter!=(*foule).premier);


	return 0;
	}

float fouleSommeForces(fouleT * foule)
	{ // Calcul de la somme des forces extérieures
	chaineT *iter;
	iter = (*foule).premier;

	do
		{	// force Batiment + force Murs + force Humains
		vecteurEgaleCartesien(&iter->humain.forceBatiment, &iter->humain.sommeForces); // v2 = v1
		vecteurSommeCartesien(&iter->humain.sommeForces, &iter->humain.forceMurs, &iter->humain.sommeForces); // v3 = v1 + v2
		vecteurSommeCartesien(&iter->humain.sommeForces, &iter->humain.forceHumains, &iter->humain.sommeForces); // v3 = v1 + v2
		iter=iter->suivant;
		}
	while(iter!=(*foule).premier);
	return 0.0;
	}

float fouleForceHumains(fouleT * foule)
	{ // Calcul des forces de contact entre les humains
	chaineT *iter1;
	chaineT *iter2;
	iter1 = (*foule).premier;

		// Remise à zéro
	do
		{
		vecteurCartesien(&iter1->humain.forceHumains, 0.0, 0.0, 0.0);
		iter1=iter1->suivant;
		}
	while(iter1!=(*foule).premier);

		// Calcul des interactions de contact entre humains
	do
		{	// Calcul des interactions sur iter 1
		iter2 = iter1->suivant;
		do
			{
			if(humainProximite(&iter1->humain, &iter2->humain)>0)
				{
				humainAjouteForceHumain(&iter1->humain, &iter2->humain);
				}
			iter2=iter2->suivant;
			}
		while(iter2!=(*foule).premier);
		iter1=iter1->suivant;
		}
	while(iter1!=(*foule).premier);

		// Force maximale
	float force = 0;
	float forceMax = 0;
	do
		{
		force = vecteurNormeCartesien2D(&iter1->humain.forceHumains);
		if(force > forceMax) forceMax = force;
		iter1=iter1->suivant;
		}
	while(iter1!=(*foule).premier);

	return force;
	}
/////////////////////////////////////////////////////////////////////////////////////
