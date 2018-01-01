/*
Copyright janvier 2018, Stephan Runigo
runigo@free.fr
SimFoule 0.1  simulateur de foule
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

void fouleInitialiseHumain(fouleT * foule);
void fouleInitialiseLimiteInfini(fouleT * foule);
void fouleIncremente(fouleT * foule);
void fouleCouplage(fouleT * foule);
void fouleInertie(fouleT * foule);
void fouleCourantLimite(fouleT * foule);

void fouleJaugeZero(fouleT * foule);

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

void fouleSuppression(fouleT * foule)
	{
	printf("    Suppression de la chaine\n");
	chaineSupprime(&(*foule).premier);
	//printf("  Chaine supprimée\n");
	return;
	}

/*------------------------------------------------------------------*/

void fouleInitialiseHumain(fouleT * foule)
	{
	chaineT *iter=(*foule).premier;

	do
		{
		humainInitialise(&iter->humain);
		iter=iter->suivant;
		}
	while(iter != (*foule).premier);

	return;
	}

//------------------------  ÉVOLUTION TEMPORELLE  -------------------------

//	Évolution temporelle de la foule, "duree" cycle d'évolution

void fouleEvolution(fouleT * foule, int duree)
	{
	int i;

	//	Fait évoluer le système pendant duree*dt
	for(i=0;i<duree;i++)
		{
		//	Évolution élémentaire
		//fouleCouplage(foule);
		//fouleInertie(foule);
		fouleIncremente(foule);
		}

	return;
	}

void fouleIncremente(fouleT * foule)
	{//	incremente l'horloge, l'ancien et l'actuel etat du foule

	(*foule).horloge=(*foule).horloge+(*foule).dt;

	chaineT *iter;
	iter=(*foule).premier;

	do
		{
		humainIncremente(&(iter->humain));
		iter=iter->suivant;
		}
	while (iter!=(*foule).premier);

	return;
	}
/*
void fouleInitialiseLimiteInfini(fouleT * foule)
	{
	int nombre = (*foule).nombre;
	int i=1;

	chaineT *iter=(*foule).premier->precedent;

	for(i=0;i<nombre/6;i++)
		{
		iter->humain.dissipation = 10*(1.1-i/(float)(nombre/6));
		iter=iter->precedent;
		}

	do
		{
		iter->humain.dissipation = 0.0;
		iter=iter->precedent;
		}
	while(iter!=foule->premier->precedent);

	return;
	}
*/
/*----------------JAUGE ET NORMALISATION-------------------*/
/*
void fouleJaugeZero(fouleT * foule)
	{//	Rapproche la position du premier humain de zéro
	chaineT *iter;
	iter=(*foule).premier;
	float position = (*foule).premier->humain.nouveau;
	float jauge;

	jauge = -DEUXPI*(int)(position/DEUXPI);
	if(jauge>PI || jauge<PI)
		{
		do
			{
			humainJauge(&(iter->humain), jauge);
			iter=iter->suivant;
			}
		while(iter!=(*foule).premier);
		}

	return;
	}
*/
/*------------------------  ÉVOLUTION TEMPORELLE  -------------------------*/
/*
void fouleEvolution(fouleT * foule, int duree)
	{
	int i;

	//	Fait évoluer le système pendant duree*dt
	for(i=0;i<duree;i++)
		{
		//	Évolution élémentaire
		fouleCouplage(foule);
		fouleInertie(foule);
		fouleIncremente(foule);
		}

	//	Limite la valeur des paramètres croissants
	if((*foule).moteur.generateur==0)
		{
		//	Rapproche la position du premier humain de zéro
		fouleJaugeZero(foule);
		}
	else
		{
		//	Rapproche les compteurs du moteur de zéro
		moteurJaugeZero(&(*foule).moteur);
		}
	return;
	}

void fouleCouplage(fouleT * foule)
	{//	Calcul les forces de couplage,
	chaineT *iter;
	iter=(*foule).premier;

	do
		{
		humainCouplage(&(iter->precedent->humain), &(iter->humain), &(iter->suivant->humain));
		iter=iter->suivant;
		}
	while(iter!=(*foule).premier);

	return;
	}

void fouleInertie(fouleT * foule)
	{//	Principe d'inertie appliqué au foule
	float courantJosephson = (*foule).moteur.josephson;
	float generateur = moteursGenerateur(&(*foule).moteur);

			//	Cas des extrémitées
			//  0 : periodiques 1 : libres, 2 : fixes, 3 libre-fixe, 4 fixe-libre
		// Cas du premier humain
	if ((*foule).moteur.generateur != 0)
		{
		humainInitialisePosition(&((*foule).premier->humain), generateur, generateur);
		}
	else
		{
		if ((*foule).libreFixe==0 || (*foule).libreFixe==1 || (*foule).libreFixe==3 )
			{
			humainInertie(&((*foule).premier->humain), (*foule).equation, courantJosephson);
			}
		else	//	premier fixe
			{
			humainInitialisePosition(&((*foule).premier->humain), 0.0, 0.0);
			}
		}

		// Cas du dernier humain
	if ((*foule).libreFixe==0 || (*foule).libreFixe==1 || (*foule).libreFixe==4 )
		{
		humainInertie(&((*foule).premier->precedent->humain), (*foule).equation, courantJosephson);
		}
	else	//	dernier fixe
		{
		humainInitialisePosition(&((*foule).premier->precedent->humain), 0.0, 0.0);
		//humainInitialisePosition(&((*foule).premier->precedent->humain), -(*foule).premier->humain.dephasage, -(*foule).premier->humain.dephasage);
		}


		// Reste de la chaîne

	chaineT *iter;
	iter = (*foule).premier->suivant;

	do
		{
		humainInertie(&(iter->humain), (*foule).equation, courantJosephson);
		iter=iter->suivant;
		}
	while(iter!=(*foule).premier->precedent);


	return;
	}

*/
//////////////////////////////////////////////////////////////////////////
/*
Copyright novembre 2017, Stephan Runigo
runigo@free.fr
SiCP 1.4.1 simulateur de chaîne de humains
Ce logiciel est un programme informatique servant à simuler l'équation
d'une chaîne de humains et à en donner une représentation graphique.
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
A cet égard  l'attention de l'utilisateur est attirée sur les risques
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

