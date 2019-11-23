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

#ifndef _CONTROLEUR_
#define _CONTROLEUR_

#include "../donnees/donnees.h"				//	Conditions initiales
#include "../controleur/options.h"			//	Options de la ligne de commande
#include "../controleur/projection.h"		//	Projection du système sur le graphisme
#include "../modele/dessine.h"				//	Dessine la configuration
#include "../interface/graphique.h"			//	Librairie SDL et représentation graphique
#include "../interface/horloge.h"			//	Librairie SDL et représentation graphique
#include "../donnees/fichier.h"

typedef struct ControleurT controleurT;
	struct ControleurT
		{

		optionsT options;	//	Options de la ligne de commande

		systemeT systeme;	//	Modélisation du batiment et de la foule

		dessineT dessine;	//	Modélisation du batiment

		projectionT projection;	//	Paramètre de la projection

		grapheT graphe;		//	Graphe de la chaîne

		commandesT commandes;	//	Graphe des commandes

		interfaceT interface;	//	Fenêtre SDL

		graphiqueT graphique;	//	Rendu SDL et graphisme

		horlogeT horloge;		//	Horloge SDL

			int modePause;		// 1 : évolution système, -1 : pause
			int modeDessin;		// 1 : simulation, -1 : construction
			int sortie;	//	sortie de SiCP si > 0

			int appui;	//	1 si le bouton de la souris est appuyé, 0 sinon.
			int curseurX;	//	Position x de la souris.
			int curseurY;	//	Position y de la souris

		};

	//	INITIALISATION - SUPRESSION
int controleurInitialisation(controleurT * controleur);
int controleurSuppression(controleurT * controleur);

int controleurReinitialisation(controleurT * controleur, int initial);

	//	ÉVOLUTION
int controleurDirections(controleurT * controleur);
int controleurSimulationGraphique(controleurT * controleur);

int controleurChangeDessin(int * dessine); // dessin des murs, des mobiles, des sens à suivre.

	void controleurChangeModePause(controleurT * controleur);
	void controleurChangeModeDessin(controleurT * controleur);
	void controleurChangeVitesse(controleurT * controleur, float facteur);

int controleurAfficheForces(controleurT * controleur);

int controleurCommandes(controleurT * controleur, int zone);

#endif
