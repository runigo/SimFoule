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


#ifndef _BATIMENT_
#define _BATIMENT_

#include "../modele/etage.h"

struct BatimentT {
	etageT etage[BATIMENT_Z_MAX];
	int batimentZ; // Nombre d'étage
};
typedef struct BatimentT batimentT;

	//		INITIALISATION

int batimentInitialiseVide(batimentT * batiment);
int batimentInitialiseImplicite(batimentT * batiment, int niveau);

int batimentProjection(batimentT * construction, batimentT * normal);
int batimentNormalise(batimentT * batiment, int etageXYZ);

	//		ÉVOLUTION

int batimentDirections(batimentT * batiment);
int batimentMiseAZeroNombre(batimentT * batiment);	// Mise à zéro du nombre de mobile par cellule

	//		INFORMATION

int batimentAffiche(batimentT * batiment);

#endif
