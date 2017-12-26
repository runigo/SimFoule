
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

	fouleInitialiseHumain(foule);

	//fouleChangeLimite(foule);

	fouleInitialiseLimiteInfini(foule);

	return 0;
	}

void fouleSuppression(fouleT * foule)
	{
	chaineSupprime(&(*foule).premier);
	printf("Système supprimé\n");
	return;
	}

/*------------------------------------------------------------------*/

void fouleInitialiseHumain(fouleT * foule)
	{
	float m=(*foule).masse;
	float l=(*foule).longueur;
	float d=(*foule).dissipation;
	float c=(*foule).couplage;
	float g=(*foule).gravitation;
	float t=(*foule).moteur.dt;
	chaineT *iter=(*foule).premier;

	do
		{
		penduleInitialiseParametre(&iter->pendule, m, l, d);
		penduleInitialiseExterieur(&iter->pendule, c, g, t);
		penduleInitialisePosition(&iter->pendule, 0.0, 0.0);
		penduleInitialiseDephasage(&iter->pendule, 0.0);
		iter=iter->suivant;
		}
	while(iter != (*foule).premier);

	penduleInitialiseDephasage(&(*foule).premier->pendule, (*foule).dephasage);

	return;
	}

void fouleInitialiseLimiteInfini(fouleT * foule)
	{
	int nombre = (*foule).nombre;
	int i=1;

	chaineT *iter=(*foule).premier->precedent;

	for(i=0;i<nombre/6;i++)
		{
		iter->pendule.dissipation = 10*(1.1-i/(float)(nombre/6));
		iter=iter->precedent;
		}

	do
		{
		iter->pendule.dissipation = 0.0;
		iter=iter->precedent;
		}
	while(iter!=foule->premier->precedent);

	return;
	}

/*----------------JAUGE ET NORMALISATION-------------------*/

void fouleJaugeZero(fouleT * foule)
	{//	Rapproche la position du premier pendule de zéro
	chaineT *iter;
	iter=(*foule).premier;
	float position = (*foule).premier->pendule.nouveau;
	float jauge;

	jauge = -DEUXPI*(int)(position/DEUXPI);
	if(jauge>PI || jauge<PI)
		{
		do
			{
			penduleJauge(&(iter->pendule), jauge);
			iter=iter->suivant;
			}
		while(iter!=(*foule).premier);
		}

	return;
	}

/*------------------------  ÉVOLUTION TEMPORELLE  -------------------------*/

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
		//	Rapproche la position du premier pendule de zéro
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
		penduleCouplage(&(iter->precedent->pendule), &(iter->pendule), &(iter->suivant->pendule));
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
		// Cas du premier pendule
	if ((*foule).moteur.generateur != 0)
		{
		penduleInitialisePosition(&((*foule).premier->pendule), generateur, generateur);
		}
	else
		{
		if ((*foule).libreFixe==0 || (*foule).libreFixe==1 || (*foule).libreFixe==3 )
			{
			penduleInertie(&((*foule).premier->pendule), (*foule).equation, courantJosephson);
			}
		else	//	premier fixe
			{
			penduleInitialisePosition(&((*foule).premier->pendule), 0.0, 0.0);
			}
		}

		// Cas du dernier pendule
	if ((*foule).libreFixe==0 || (*foule).libreFixe==1 || (*foule).libreFixe==4 )
		{
		penduleInertie(&((*foule).premier->precedent->pendule), (*foule).equation, courantJosephson);
		}
	else	//	dernier fixe
		{
		penduleInitialisePosition(&((*foule).premier->precedent->pendule), 0.0, 0.0);
		//penduleInitialisePosition(&((*foule).premier->precedent->pendule), -(*foule).premier->pendule.dephasage, -(*foule).premier->pendule.dephasage);
		}


		// Reste de la chaîne

	chaineT *iter;
	iter = (*foule).premier->suivant;

	do
		{
		penduleInertie(&(iter->pendule), (*foule).equation, courantJosephson);
		iter=iter->suivant;
		}
	while(iter!=(*foule).premier->precedent);


	return;
	}

void fouleIncremente(fouleT * foule)
	{//	incremente l'horloge, l'ancien et l'actuel etat du foule

	//(*foule).moteur.horloge=(*foule).moteur.horloge+(*foule).moteur.dt;
	(*foule).moteur.chrono=(*foule).moteur.chrono+(*foule).moteur.dt;

	chaineT *iter;
	iter=(*foule).premier;

	do
		{
		penduleIncremente(&(iter->pendule));
		iter=iter->suivant;
		}
	while (iter!=(*foule).premier);

	return;
	}

//////////////////////////////////////////////////////////////////////////
/*
Copyright novembre 2017, Stephan Runigo
runigo@free.fr
SiCP 1.4.1 simulateur de chaîne de pendules
Ce logiciel est un programme informatique servant à simuler l'équation
d'une chaîne de pendules et à en donner une représentation graphique.
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

