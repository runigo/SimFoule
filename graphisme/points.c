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

#include "points.h"

pointsT* pointsCreationPremierGraphe(void);
void pointsCreationPointGraphe(pointsT* premier);
void pointsSupprimeGraphe(pointsT* premier);

pointsT* pointsCreationGraphe(int nombre)
	{
	int i;
	pointsT* premier=pointsCreationPremierGraphe();
	for(i=1;i<nombre;i++)
		pointsCreationPointGraphe(premier);
	return premier;
	}

void pointsSupprime(pointsT** premier)
	{
	pointsSupprimeGraphe(*premier);
	free(*premier);
	*premier=NULL;
	}

pointsT* pointsCreationPremierGraphe(void)
	{
	//pointsT * premier;
	//premier = (pointsT*) malloc(sizeof(pointsT));
	pointsT* premier = malloc(sizeof *premier);
	if (premier!=NULL)
		{
		premier->suivant=premier;
		}
	else fprintf(stderr, "Echec de malloc dans creationPremierGraphe()");
	//affichePendul(&(premier->pendul));
	return premier;
	}

void pointsSupprimeGraphe(pointsT* premier)
	{
	pointsT *iter, *suivant;
	for(iter=premier->suivant; iter !=premier; iter=suivant)
		{
		suivant=iter->suivant;
		free(iter);
		}
	}

void pointsCreationPointGraphe(pointsT* premier)
	{// ajoute un pendule à la chaine
	pointsT * nouveau = (pointsT*) malloc(sizeof(pointsT));
	if (nouveau!=NULL)
		{
		nouveau->suivant=premier->suivant;
		premier->suivant=nouveau;
		}
	//affichePendul(&(nouveau->pendul));
	}
//////////////////////////////////////////////////////////////////////
/*
Copyright avril 2016, Stephan Runigo
runigo@free.fr
SiCP 1.1  simulateur de chaîne de pendules
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

