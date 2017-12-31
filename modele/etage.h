/*
Copyright décembre 2017, Stephan Runigo
runigo@free.fr
SimFoule 1.0  simulateur de foule
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


#ifndef _ETAGE_
#define _ETAGE_

#include "../modele/cellule.h"

struct EtageT {
	celluleT cellule[BATIMENT_X][BATIMENT_Y];	//	Un étage est un tableau de cellules

	int etage; // Numero de l'étage

	vecteurT angle[8];	// Vecteurs directions 			    6
				//	possibles			 5     7
				//	pour les			4       0
				//	cellules.			 3     1
				//					    2
				
	vecteurT vecteurNul;	// Vecteur nul
};
typedef struct EtageT etageT;

//int etageInitialise(etageT * etage);

int etageCreationCelluleMur(etageT * etage, int X, int Y);
int etageCreationCelluleSortie(etageT * etage, int X, int Y);
int etageInitialiseStatutCellule(etageT * etage, int i, int j,int statut);
int etageDonneStatutCellule(etageT * etage, int i, int j);

int etageCalculDistanceEtSens(etageT * etage);

int etageAffiche(etageT * etage);
#endif
