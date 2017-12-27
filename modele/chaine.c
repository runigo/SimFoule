/*
Copyright décembre 2017, Stephan Runigo
runigo@free.fr
SimFoule 0.0  simulateur de foule
Ce logiciel est un programme informatique servant à simuler une foule 
d'humains et à en donner une représentation graphique.
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

#include "chaine.h"

chaineT* chaineCreationPremier(void);
void chaineCreationHumain(chaineT* premier);
void chaineSupprimeHumain(chaineT* premier);

chaineT* chaineCreation(int nombre)
	{
	int i;
	chaineT* premier=chaineCreationPremier();
	for(i=1;i<nombre;i++)
		chaineCreationHumain(premier);
	return premier;
	}

void chaineSupprime(chaineT** premier)
	{
	chaineSupprimeHumain(*premier);
	free(*premier);
	*premier=NULL;
	}

chaineT* chaineCreationPremier(void)
	{ // creation du premier chaineT
	//chaineT * premier;
	//premier = (chaineT*) malloc(sizeof(chaineT));
	chaineT* premier = malloc(sizeof *premier);
	if (premier!=NULL)
		{
		premier->suivant=premier;
		premier->precedent=premier;
		}
	else
		{
		fprintf(stderr, "erreur de malloc dans chaineCreationPremier");
		}
	//affichePendul(&(premier->pendule));
	return premier;
	}

void chaineSupprimeHumain(chaineT* premier)
	{
	chaineT *iter, *suivant;
	for(iter=premier->suivant; iter !=premier; iter=suivant)
		{
		suivant=iter->suivant;
		free(iter);
		}
	}

void chaineCreationHumain(chaineT* premier)
	{// ajoute un pendule à la chaine
	chaineT * nouveau = (chaineT*) malloc(sizeof(chaineT));
	if (nouveau!=NULL)
		{
		nouveau->precedent=premier;
		nouveau->suivant=premier->suivant;
		premier->suivant->precedent=nouveau;
		premier->suivant=nouveau;
		}
	else
		{
		fprintf(stderr, "erreur de malloc dans chaineCreationHumain");
		}
	//affichePendul(&(nouveau->pendule));
	}

//////////////////////////////////////////////////////////////////////////
/*
Copyright septembre 2017, Stephan Runigo
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

