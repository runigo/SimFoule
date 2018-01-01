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

/*

	Un vecteurT contient les coordonnées cartésienne
	et éventuellement les coordonées polaires

	Dans SimFoule, la coordonée z est un entier et représente l'étage.
		Si z est négatif, il représente l'escalier.

*/

#ifndef _VECTEUR_
#define _VECTEUR_

#include "../donnees/constantes.h"

typedef struct VecteurT vecteurT;
	struct VecteurT
		{
		float x;
		float y;
		int z;
		float r;
		float psi;
		float phi;
		};

void vecteurCartesien(vecteurT * v, float x, float y, int z);
void vecteurCartesienEgale(vecteurT * v1, vecteurT * v2); // v2 = v1
void vecteurInitialisePolaire(vecteurT * v, float r, float psi, float phi);
float vecteurScalaireCartesien(vecteurT * v1, vecteurT * v2);
void vecteurSommeCartesien(vecteurT * v1, vecteurT * v2, vecteurT * v3); // v3 = v1 + v2
void vecteurDifferenceCartesien(vecteurT * v1, vecteurT * v2, vecteurT * v3); // v3 = v1 - v2

float vecteurNormaliseCartesien(vecteurT * v); // normalise, renvoie la norme initiale

int vecteurInitialiseVecteurPhi(vecteurT * pointDeVue, vecteurT * vecteurPhi, float hauteur);
int vecteurInitialiseVecteurPsi(vecteurT * pointDeVue, vecteurT * vecteurPsi, float largeur);

#endif
////////////////////////////////////////////////////////////

/*
Copyright juillet 2017, Stephan Runigo
runigo@free.fr
SiCP 1.3  simulateur de chaîne de pendules
Ce logiciel est un programme informatique servant à simuler l'équation
d'une chaîne de pendules et à en donner une représentation graphique.
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

