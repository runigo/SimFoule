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


#ifndef _CELLULE_
#define _CELLULE_

#include "../modele/vecteur.h"

struct CelluleT {
		// Données d'initialisation
	int statut;		// 0:libre, 1:mur, 2:sortie, 3:entrée, 9:mobile lors de l'initialisation

		// Calcul de plus court chemin
	int visite;		// 1 si initialisé, -1 si visite en cours (appartient au front)
	int distance;		// Distance à la sortie
	int issue;		// Nombre de voisines "direct" à ateindre
	float interet[8];		// Intérêt à aller dans la direction
	float note[8];		// Intérêt - nombre
	int sens;		// Meilleur sens

		// Données dynamiques
	int nombre;	// nombre de mobile.
};
typedef struct CelluleT celluleT;

double celluleInitialise(celluleT * cellule);

int celluleCreationMur(celluleT * cellule);
int celluleCreationVide(celluleT * cellule);
int celluleCreationSortie(celluleT * cellule);
int celluleCreationEntree(celluleT * cellule);
int celluleCreationMobile(celluleT * cellule);

int celluleDonneStatut(celluleT * cellule);	// 0:libre, 1:mur, 2:sortie
int celluleInitialiseStatut(celluleT * cellule, int statut);	// 0:libre, 1:mur, 2:sortie, 3:entrée, 9:mobile

int celluleDonneVisite(celluleT * cellule);	// 1 si initialisé, -1 si visite en cours
int celluleChangeVisite(celluleT * cellule, int visite);	// change visite

int celluleDonneDistance(celluleT * cellule);	// Distance à la sortie
int celluleChangeDistance(celluleT * cellule, int pas);	// Ajoute le pas à la distance

int cellulePositionIssueInf(celluleT * cellule); // Retourne la position de l'issue
int cellulePositionIssueSup(celluleT * cellule); // Retourne la position de l'issue
int cellulePositionIssue(celluleT * cellule); // Retourne la position de l'issue
//int celluleAjouteNombre(celluleT * cellule);	// Ajoute 1 à nombre
#endif

/////////////////////////////////////////////////////////////////////
