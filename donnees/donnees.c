/*
Copyright janvier 2018, Stephan Runigo
runigo@free.fr
SimFoule 1.2  simulateur de foule
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


#include "donnees.h"


int donneesOptionsImplicite(optionsT * options)
	{
		// Préréglage des valeurs optionnelles, 
		// 	réglage des valeurs implicites


	(*options).fond=240;	// couleur du fond de l'affichage
	(*options).mode = 1;	// -1 : Wait, 1 : Poll
	(*options).pause=25;	// temps de pause SDL en ms
	(*options).duree = 90;	// nombre d'incrémentation de la foule par affichage

	(*options).initial=-1;	// Numéro du fichier d'initialisation.

	(*options).nombre=33;	// Nombre d'humain
	(*options).nervosite=7.7;	// Nervosité des humains
	(*options).masse=77.77;	// Masse des humains
	(*options).dt=0.00666;	// discrétisation du temps

			//	Dessin des graphes 0 ou 1
	(*options).dessineAngle=0;
	(*options).dessineMur=1;
	(*options).dessineHumain=1;
	return 0;
	}

int donneesInitialisationBatiment(batimentT * batiment, optionsT * options)
	{
		printf("    donneesInitialisationBatiment : batimentInitialise %d\n", (*options).initial);
	(*options).nombre = batimentInitialise(batiment, -1);
		fprintf(stderr, "    donneesInitialisationBatiment : nombre d'humain = %d\n", (*options).nombre);

	if( (*options).initial > -1 && (*options).initial < 99)
		{
		printf("donneesInitialisationBatiment : fichierLecture\n");
		(*options).nombre = fichierLecture(batiment, (*options).initial);
		}

	return 0;
	}

//int donneesSystemeSauvegarde(controleurT * controleur, int numero);
int donneesSauvegardeBatiment(batimentT * batiment, optionsT * options)
	{
		if( (*options).initial > -1 && (*options).initial < 99)
			{
			fichierEcriture(batiment, (*options).initial);
			}
		else
			{
			printf("donneesSauvegardeBatiment : Erreur lors de la sauvegarde\n");
			}
	
	return 0;
	}

int donneesCreationFoule(fouleT * foule, optionsT * options)
	{
		// Initialisation de la foule

	(*foule).dt = (*options).dt;		// Discrétisation du temps
	(*foule).horloge = 0.0;			// Horloge

	(*foule).nombre = (*options).nombre;	// Nombre d'humain
	(*foule).restant = (*options).nombre;	// Nombre d'humain restant à sortir

	(*foule).masse = (*options).masse;		// Masse des humains
	(*foule).nervosite = (*options).nervosite;	// Nervosité des humains

		// Création de la chaîne
	fouleCreation(foule);

	return 0;
	}

int donneesInitialisationFoule(fouleT * foule, batimentT * batiment)
	{
	chaineT *iter=(*foule).premier;
	float centrage = ((float)(CELLULE))/2.0;
	int i, j, k;
	int compteur = 0;

		// Position des humains
	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				if((*batiment).etage[k].cellule[i][j].statut == 9)
					{
					humainInitialisePosition(&iter->humain, i*CELLULE+centrage, j*CELLULE+centrage, k);
					//fprintf(stderr, "Initialisation position humain : %d, %d\n", i, j);
					//fprintf(stderr, "  coordonnées : x= %f, y= %f, z= %d\n", iter->humain.nouveau.x, iter->humain.nouveau.y, iter->humain.nouveau.z);
					iter=iter->suivant;
					compteur ++;
					}
				}
			}
		}
	fprintf(stderr, "    donneesInitialisationFoule : position de %d humains initialisée.\n", compteur);

	return 0;
	}

int donneesInitialisationInterface(interfaceT * interface, optionsT * options)
	{
		fprintf(stderr, "    donneesInitialisationInterface : Initialisation de la SDL2, fond = %d\n", (*options).fond);
	interfaceInitialisation(interface, (*options).fond);
	return 0;
	}

int donneesCreationGraphe(grapheT * graphe, optionsT * options)
	{
		fprintf(stderr, "    donneesCreationGraphe : Création du graphe, nombre = %d\n", (*options).nombre);
	grapheCreation(graphe, (*options).nombre);
	return 0;
	}

int donneesInitialisationGraphe(grapheT * graphe, interfaceT * interface)
	{
		fprintf(stderr, "    donneesInitialisationGraphe : Initialisation du graphe\n");
	grapheInitialisation((*interface).rendu, graphe);
	return 0;
	}

//////////////////////////////////////////////////////////////////////////

/*
Copyright novembre 2017, Stephan Runigo
runigo@free.fr
SiCF 1.2  simulateur de corde vibrante et spectre
Ce logiciel est un programme informatique servant à simuler l'équation
d'une corde vibrante, à calculer sa transformée de fourier, et à donner
une représentation graphique de ces fonctions. 
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

