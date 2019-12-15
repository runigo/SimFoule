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


#ifndef _CONSTANTES_
#define _CONSTANTES_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265359


	//	---------------------	PARAMÈTRES GRAPHIQUES	------------//

	//		FENÊTRE

//#define FENETRE_X 1117 // Largeur de la fenêtre
//#define FENETRE_Y 691 // Hauteur de la fenêtre
#define FENETRE_X 800 // Largeur de la fenêtre
#define FENETRE_Y 400 // Hauteur de la fenêtre

	//		COMMANDES

#define BOUTON_COMMANDES 7 // Nombres de petits boutons
#define ROTATIF_COMMANDES 6 // Nombre de boutons rotatifs

#define LINEAIRE_COMMANDES 4 // Nombres de commandes linéaires
#define TRIANGLE_COMMANDES 10 // Nombres de commandes triangulaires

	//		CAPTEURS

#define DUREE_CAPTEURS 128 // Nombre de points en mémoire

	//		TEMPORELLE

#define TEMPS_AFFICHAGE 110 // Durée entre les affichages en ms

#define MEMOIRE_CHRONO 10 // Nombre de points en mémoire des durées chronométrées


	//	---------------------	PARAMÈTRES SYSTÈME	------------//

	//		SPATIALES

#define BATIMENT_X_IMP 50	// Longueur implicite suivant x du batiment (en nombre de cellule)
#define BATIMENT_Y_IMP 25	// Longueur implicite suivant y du batiment (en nombre de cellule)
#define BATIMENT_Z_IMP 1	// Nombre implicite d'étage

#define BATIMENT_X_MAX 60	// Longueur maximale suivant x du batiment (en nombre de cellule)
#define BATIMENT_Y_MAX 30	// Longueur maximale suivant y du batiment (en nombre de cellule)
#define BATIMENT_Z_MAX 3	// Nombre d'étage maximale

#define CELLULE 16		// Longueur du coté d'une cellule (en pixel)
#define CELLULESUR2 CELLULE/2	// Demi longueur du coté d'une cellule (en pixel)

#define NOMBRE_MAX 1000	// Nombre maximale de mobiles

	//		TEMPORELLES

#define DT_MAX 0.06	// dt maximale
#define DT_IMPLICITE 0.019	// dt implicite
#define DT_MIN 0.00007	// dt minimale

#define DUREE 100 // Nombre implicite d'incrémentation du système entre deux affichages.
#define DUREE_MAX 777	// Nombre maximale d'incrémentation entre les affichages

	//		MOBILES

#define MOBILE_MIN 1 // Taille minimale d'un mobile
#define MOBILE_IMP CELLULE // Taille implicite d'un mobile
#define MOBILE_MAX CELLULE*2 // Taille maximale d'un mobile

#define MASSE_MIN 25.5	// Masse minimale d'un mobile
#define MASSE_IMP 77.77	// Masse implicite d'un mobile
#define MASSE_MAX 155.5	// Masse maximale d'un mobile

#define NERVOSITE_MAX 7.7	// Nervosité maximale
#define NERVOSITE_IMP 1.7	// Nervosité implicite
#define NERVOSITE_MIN 1.1	// Nervosité minimale

#define CELERITE_MAX 3.7	// Célérité maximale
#define CELERITE_IMP 1.77	// Célérité implicite
#define CELERITE_MIN 0.377	// Célérité minimale

#define VIVACITE_MAX 11	// Vivacité maximale
#define VIVACITE_IMP 10	// Vivacité implicite
#define VIVACITE_MIN 0	// Vivacité minimale

	//		INTERACTIONS

#define UNITE_NOTE 0.55		// Unité de note pour la direction souhaitable

#define FORCE_CONTACT_MOBILE 141	// constante de force de répulsion de contact entre mobile
#define FORCE_CONTACT_MUR 1171		// constante de force de répulsion de contact avec les murs

	//		INITIALISATION

#define INITIAL_MIN -99	// Fichiers d'initialisation
#define INITIAL_MAX 99	// Fichiers d'initialisation

#endif
//////////////////////////////////////////////////////////////////////
