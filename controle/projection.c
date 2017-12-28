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

#include "projection.h"

int projectionEtagePlan(etageT * etage, projectionT * projection, grapheT * graphe)
	{	//	Projette les murs sur le plan du graphe
	int i, j;
	(void)projection;

	for(i=0;i<BATIMENT;i++)
		{
		for(j=0;j<BATIMENT;j++)
			{
			(*graphe).plan[i][j][0]=(*etage).cellule[i][j].statut;
			}
		}
	return 0;
	}


int projectionFoulePoints(fouleT * foule, projectionT * projection, grapheT * graphe)
	{	//	Projette les coordonnées des humains sur les points du graphe

	chaineT *iterFoule=(*foule).premier;
	pointsT *iterGraph=(*graphe).premier;
	(void)projection;

	do
		{
		iterGraph->xm = (int)(iterFoule->humain.nouveau.x);
		iterGraph->ym = (int)(iterFoule->humain.nouveau.y);

		iterGraph = iterGraph->suivant;
		iterFoule = iterFoule->suivant;
		}
	while(iterGraph!=(*graphe).premier);
	return 0;
	}

int projectionInitialiseCouleurs(projectionT * projection, int r, int v, int b, int fond)
	{		// Initialise la couleur du graphe
	(*projection).rouge = r;
	(*projection).vert = v;
	(*projection).bleu = b;
	(*projection).fond = fond;
	return 0;
	}

int projectionInitialiseLongueurs(projectionT * projection, int hauteur, int largeur)
	{		// Fixe la taille de la chaîne et l'effet de perspective
	(*projection).hauteur = hauteur;
	(*projection).largeur = largeur;
	return 0;
	}

int projectionAffiche(projectionT * projection)
	{		// Affiche les valeurs de psi et phi
	float r, v, b, f;

	r = (*projection).rouge;
	v = (*projection).vert;
	b = (*projection).bleu;
	f = (*projection).fond;

	printf("(*projection).pointDeVue.r = %f\n", r);
	printf("(*projection).pointDeVue.v = %f\n", v);
	printf("(*projection).pointDeVue.b = %f\n", b);
	printf("(*projection).pointDeVue.fond = %f\n", f);

	return 0;
	}

////////////////////////////////////////////////////////////////////////////////
/*
Copyright juillet 2017, Stephan Runigo
runigo@free.fr
SiCP 1.3.5  simulateur de chaîne de pendules
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

