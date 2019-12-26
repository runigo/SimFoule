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


#ifndef _MOBILE_
#define _MOBILE_

#include "../modele/vecteur.h"

struct MobileT {
	vecteurT nouveau;
	vecteurT actuel;
	vecteurT ancien;

	vecteurT vitesse;

	vecteurT vitesseSouhaitee;

	vecteurT forceBatiment;
	vecteurT forceMobiles;
	vecteurT forceMurs;
	vecteurT sommeForces;


	int taille;

	float rayon;
	float masse;

	float nervosite;
	float celerite;

	int vivacite;	//	"points de vie"

	float dtsurtau;
	float dt2surM;
	float dt;
};
typedef struct MobileT mobileT;

	//		INITIALISATION

int mobileInitialise(mobileT * mobile, float dt);

int mobileInitialiseTaille(mobileT * mobile, int taille);
int mobileInitialiseMasse(mobileT * mobile, float masse);
int mobileInitialiseNervosite(mobileT * mobile, float nervosite);
int mobileInitialiseCelerite(mobileT * mobile, float celerite);

int mobileInitialiseVivacite(mobileT * mobile, float vivacite);

	//		Initialisation sans test de valeur
void mobileInitialiseMasseEco(mobileT * mobile, float masse, float dt2surM);
void mobileInitialiseNervositeEco(mobileT * mobile, float nervosite, float dtsurtau);
void mobileInitialiseCeleriteEco(mobileT * mobile, float celerite);

int mobileInitialisePosition(mobileT * mobile, float x, float y, int z); // z=-1 : sortie

	//		ÉVOLUTION

int mobileInertie(mobileT * mobile);
int mobileIncremente(mobileT * mobile);

int mobileProximite(mobileT * mobile1, mobileT * mobile2); // retourne 1 si les mobiles sont proche, 0 sinon

float mobileCouplage(mobileT * mobile, vecteurT * vitesseSouhaite);
float mobileAjouteForceMobile(mobileT * mobile1, mobileT * mobile2);
float mobileAjouteForceMur(mobileT * mobile1, int DX, int DY, vecteurT * angle);

	//		CHANGEMENT  DES  PARAMÈTRES

int mobileChangeMasse(mobileT * mobile, float facteur);
int mobileChangeNervosite(mobileT * mobile, float facteur);
int mobileChangeCelerite(mobileT * mobile, float facteur);

int mobileChangeVivacite(mobileT * mobile, int impact);
int mobileImpactVivacite(mobileT * mobile);

	//		AFFICHAGE

int mobileAffiche(mobileT * mobile);
#endif
////////////////////////////////////////////////////////////////////
