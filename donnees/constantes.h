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


#ifndef _CONSTANTES_
#define _CONSTANTES_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265359


	//	PARAMÈTRES GRAPHIQUES

#define FENETRE_X 892 // Largeur de la fenêtre
#define FENETRE_Y 550 // Hauteur de la fenêtre


#define BOUTON_COMMANDES 17 // Nombres de petits boutons
#define ROTATIF_COMMANDES 5 // Nombre de boutons rotatifs

#define LINEAIRE_COMMANDES 4 // Nombres de commandes linéaires
#define TRIANGLE_COMMANDES 21 // Nombres de commandes triangulaires

	//----------         DIMENSIONS  SPATIALES         -----------//

#define BATIMENT_X 25	// Longueur suivant x du batiment (en nombre de cellule)
#define BATIMENT_Y 25	// Longueur suivant y du batiment (en nombre de cellule)
#define BATIMENT_Z 1	// Nombre d'étage

#define CELLULE 16		// Longueur du coté d'une cellule (en pixel)
#define CELLULESUR2 CELLULE/2	// Demi longueur du coté d'une cellule (en pixel)

	//#define FENETRE_X BATIMENT_X*CELLULE // Taille de la fenêtre
	//#define FENETRE_Y BATIMENT_Y*CELLULE // Taille de la fenêtre

	#define CELLULE_ETAGE BATIMENT_X*BATIMENT_Y	// Nombre de cellule d'un étage
	#define CELLULE_BATIMENT CELLULE_ETAGE*BATIMENT_Z	// Nombre de cellule du batiment

	#define NOMBRE_MAX CELLULE_BATIMENT	// Nombre maximale d'mobiles


	//----------         PARAMETRES  TEMPORELLES         -----------//

#define TEMPS_AFFICHAGE 510 // Durée entre les affichages en ms

#define DT_MAX 0.06	// dt maximale
#define DT_MIN 0.00007	// dt minimale

#define DUREE 100 // Nombre implicite d'incrémentation du système entre deux affichages.
#define DUREE_MAX 777	// Nombre maximale d'incrémentation entre les affichages


	//----------         PARAMETRES  D'INITIALISATION         -----------//

#define INITIAL_MIN -99	// Fichiers d'initialisation
#define INITIAL_MAX 99	// Fichiers d'initialisation


	//----------         PARAMETRES  DES  MOBILES         -----------//

#define MOBILE_MIN 1 // Taille minimale d'un mobile
#define MOBILE_MAX CELLULE*2 // Taille maximale d'un mobile

#define MASSE_MIN 5	// Masse minimale d'un mobile
#define MASSE_MAX 199	// Masse maximale d'un mobile

#define NERVOSITE_MAX 19.1	// Nervosité maximale
#define NERVOSITE_MIN 0.55	// Nervosité minimale


	//----------        PARAMETRES  D'INTERACTIONS        -----------//
#define UNITE_NOTE 0.71		// Unité de note pour la direction souhaitable
#define FORCE_CONTACT_MOBILE 141	// constante de force de répulsion de contact entre mobile
#define FORCE_CONTACT_MUR 1171		// constante de force de répulsion de contact avec les murs
#endif
//////////////////////////////////////////////////////////////////////
