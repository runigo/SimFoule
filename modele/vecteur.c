/*
Copyright novembre 2019, Stephan Runigo
runigo@free.fr
SimFoule 2.1  simulateur de foule
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

#include "vecteur.h"

void vecteurCartesien(vecteurT * v, float x, float y, int z)
	{
	(*v).x=x;
	(*v).y=y;
	(*v).z=z;
	return;
	}

void vecteurAffiche(vecteurT * v)
	{
	fprintf(stdout, "  x = %f ", (*v).x);
	fprintf(stdout, "  y = %f ", (*v).y);
	fprintf(stdout, "  z = %d ", (*v).z);
	return;
	}

void vecteurEgaleCartesien(vecteurT * v1, vecteurT * v2) // v2 = v1
	{
	(*v2).x=(*v1).x;
	(*v2).y=(*v1).y;
	(*v2).z=(*v1).z;
	return;
	}

float vecteurScalaireCartesien(vecteurT * v1, vecteurT * v2)
	{
	return ((*v1).x*(*v2).x + (*v1).y*(*v2).y + (*v1).z*(*v2).z);
	}

float vecteurScalaireCartesien2D(vecteurT * v1, vecteurT * v2)
	{
	return ((*v1).x*(*v2).x + (*v1).y*(*v2).y);
	}

void vecteurSommeCartesien(vecteurT * v1, vecteurT * v2, vecteurT * v3)
	{ // v3 = v1 + v2
	(*v3).x=(*v1).x+(*v2).x;
	(*v3).y=(*v1).y+(*v2).y;
	(*v3).z=(*v1).z+(*v2).z;
	return;
	}

void vecteurSommeCartesien2D(vecteurT * v1, vecteurT * v2, vecteurT * v3)
	{ // v3 = v1 + v2
	(*v3).x=(*v1).x+(*v2).x;
	(*v3).y=(*v1).y+(*v2).y;
	return;
	}

void vecteurDifferenceCartesien(vecteurT * v1, vecteurT * v2, vecteurT * v3)
	{ // v3 = v1 - v2
	(*v3).x=(*v1).x-(*v2).x;
	(*v3).y=(*v1).y-(*v2).y;
	(*v3).z=(*v1).z-(*v2).z;
	return;
	}

void vecteurDifferenceCartesien2D(vecteurT * v1, vecteurT * v2, vecteurT * v3)
	{ // v3 = v1 - v2
	(*v3).x=(*v1).x-(*v2).x;
	(*v3).y=(*v1).y-(*v2).y;
	return;
	}

int vecteurProduitCartesien(vecteurT * v1, float lambda, vecteurT * v2)
	{ // v2 = lambda v1
	(*v2).x=lambda*(*v1).x;
	(*v2).y=lambda*(*v1).y;
	(*v2).z=lambda*(*v1).z;
	return 0;
	}

int vecteurProduitCartesien2D(vecteurT * v1, float lambda, vecteurT * v2)
	{ // v2 = lambda v1
	(*v2).x=lambda*(*v1).x;
	(*v2).y=lambda*(*v1).y;
	return 0;
	}

float vecteurNormeCartesien(vecteurT * v)
	{ // Renvoie la norme
	return sqrt((*v).x*(*v).x+(*v).y*(*v).y+(*v).z*(*v).z);
	}

float vecteurNormaliseCartesien(vecteurT * v)
	{ // normalise, renvoie la norme initiale, -1 si nulle
	float norme = sqrt((*v).x*(*v).x+(*v).y*(*v).y+(*v).z*(*v).z);
	if(norme>0.0)
		{
		(*v).x=(*v).x/norme;
		(*v).y=(*v).y/norme;
		(*v).z=(*v).z/norme;
		}
	else norme = -1.0;
	return norme;
	}

float vecteurNormeCartesien2D(vecteurT * v)
	{ // Renvoie la norme
	return sqrt((*v).x*(*v).x+(*v).y*(*v).y);
	}

float vecteurNormaliseCartesien2D(vecteurT * v)
	{ // normalise, renvoie la norme initiale, -1 si nulle
	float norme = sqrt((*v).x*(*v).x+(*v).y*(*v).y);
	if(norme>0.0)
		{
		(*v).x=(*v).x/norme;
		(*v).y=(*v).y/norme;
		}
	else norme = -1.0;
	return norme;
	}

//////////////////////////////////////////////////////////////////////
