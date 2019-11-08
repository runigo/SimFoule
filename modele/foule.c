/*
Copyright novembre 2019, Stephan Runigo
runigo@free.fr
SimFoule 2.1  simulateur de foule
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


#include "foule.h"

	//		CRÉATION  ET  INITIALISATION

	//		ÉVOLUTION  TEMPORELLE

	//		CHANGEMENT  DES  PARAMÈTRES

int fouleInitialiseMobile(fouleT * foule);
void fouleInitialiseLimiteInfini(fouleT * foule);
void fouleCouplage(fouleT * foule);
void fouleCourantLimite(fouleT * foule);

//void fouleJaugeZero(fouleT * foule);

/*--------------------------------------------------------------*/

	//		CRÉATION  ET  INITIALISATION

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

	fouleInitialiseMobile(foule);

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

int fouleInitialiseMobile(fouleT * foule)
	{
	chaineT *iter=(*foule).premier;

	do
		{
		mobileInitialise(&iter->mobile, (*foule).taille, (*foule).masse, (*foule).nervosite, (*foule).dt);
		iter=iter->suivant;
		}
	while(iter != (*foule).premier);

	return 0;
	}


	//		ÉVOLUTION  TEMPORELLE

int fouleIncremente(fouleT * foule)
	{//	incremente l'horloge, l'ancien et l'actuel état de la foule

	(*foule).horloge=(*foule).horloge+(*foule).dt;

	chaineT *iter;
	iter=(*foule).premier;

	do
		{
		mobileIncremente(&(iter->mobile));
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
		if((iter->mobile).nouveau.z!=-1)
			mobileInertie(&(iter->mobile));
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
		{	// force Batiment + force Murs + force Mobiles
		vecteurEgaleCartesien(&iter->mobile.forceBatiment, &iter->mobile.sommeForces); // v2 = v1
		vecteurSommeCartesien(&iter->mobile.sommeForces, &iter->mobile.forceMurs, &iter->mobile.sommeForces); // v3 = v1 + v2
		vecteurSommeCartesien(&iter->mobile.sommeForces, &iter->mobile.forceMobiles, &iter->mobile.sommeForces); // v3 = v1 + v2
		iter=iter->suivant;
		}
	while(iter!=(*foule).premier);
	return 0.0;
	}

float fouleForceMobiles(fouleT * foule)
	{ // Calcul des forces de contact entre les mobiles
	chaineT *iter1;
	chaineT *iter2;
	iter1 = (*foule).premier;

		// Remise à zéro
	do
		{
		vecteurCartesien(&iter1->mobile.forceMobiles, 0.0, 0.0, 0.0);
		iter1=iter1->suivant;
		}
	while(iter1!=(*foule).premier);

		// Calcul des interactions de contact entre mobiles
	do
		{	// Calcul des interactions sur iter 1
		iter2 = iter1->suivant;
		do
			{
			if(mobileProximite(&iter1->mobile, &iter2->mobile)>0)
				{
				mobileAjouteForceMobile(&iter1->mobile, &iter2->mobile);
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
		force = vecteurNormeCartesien2D(&iter1->mobile.forceMobiles);
		if(force > forceMax) forceMax = force;
		iter1=iter1->suivant;
		}
	while(iter1!=(*foule).premier);

	return force;
	}



	//		CHANGEMENT  DES  PARAMÈTRES

int fouleChangeMasseMoyenne(fouleT * foule, float facteur)
	{
	chaineT *iter=(*foule).premier;

	do
		{
		mobileChangeMasse(&iter->mobile, facteur);
		iter=iter->suivant;
		}
	while(iter != (*foule).premier);

	return 0;
	}


int fouleChangeEcartMasse(fouleT * foule, float facteur)
	{
	chaineT *iter=(*foule).premier;

	do
		{
		mobileChangeMasse(&iter->mobile, facteur);
		iter=iter->suivant;
		}
	while(iter != (*foule).premier);

	return 0;
	}

int fouleChangeNervositeMoyenne(fouleT * foule, float facteur)
	{
	chaineT *iter=(*foule).premier;

	do
		{
		mobileChangeNervosite(&iter->mobile, facteur);
		iter=iter->suivant;
		}
	while(iter != (*foule).premier);

	return 0;
	}

int fouleChangeEcartNervosite(fouleT * foule, float facteur)
	{
	chaineT *iter=(*foule).premier;

	do
		{
		mobileChangeMasse(&iter->mobile, facteur);
		iter=iter->suivant;
		}
	while(iter != (*foule).premier);

	return 0;
	}


/////////////////////////////////////////////////////////////////////////////////////
