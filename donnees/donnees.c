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


#include "donnees.h"

	//		Initialisation et création du batiment et de la foule

	//		Initialisation et création du graphe

	//		Initialisation de la SDL


int donneesEtage(etageT * etage, optionsT * options);
int donneesFoule(fouleT * foule, optionsT * options);
int donneesCreationGraphique(controleurT * controleur);

int donneesCreationControleur(controleurT * controleur)
	{

	(*controleur).options.sortie = 0;	// Sortie de SiCP si > 0

	projectionInitialiseCouleurs(&(*controleur).projection, 50, 50, 50, (*controleur).options.fond);
	projectionInitialiseLongueurs(&(*controleur).projection, HAUTEUR, LARGEUR);
		fprintf(stderr, "  Initialisation de l'étage\n");
	donneesEtage(&(*controleur).etage, &(*controleur).options);
		fprintf(stderr, "  Initialisation de la foule\n");
	donneesFoule(&(*controleur).foule, &(*controleur).options);

		fprintf(stderr, "  Initialisation de l'interface graphique\n");
	donneesCreationGraphique(controleur);

	return 0;
	}

int donneesOptions(optionsT * options)
	{
		// Préréglage des valeurs optionnelles

	(*options).initialise=0;	// couleur du fond de l'affichage

	(*options).fond=240;	// couleur du fond de l'affichage
	(*options).mode = 1;	// -1 : Wait, 1 : Poll
	(*options).pause=25;	// temps de pause SDL en ms

	(*options).duree = 10;	// 100 : temps réèl. Voir options.c

	(*options).nombre=30;	// Nombre d'humain

	(*options).nervosite=0.9;	// Nervosité des humains
	(*options).dt=0.006;	// discrétisation du temps
							// 25 images par seconde, SDL_Delay(30);
							// dt*duree = 0.004
	return 0;
	}

int donneesEtage(etageT * etage, optionsT * options)
	{
	fichierLecture(etage, (*options).initialise);
	return 0;
	}

int donneesFoule(fouleT * foule, optionsT * options)
	{

		// Initialisation de la foule

	(*foule).nombre = (*options).nombre;	// Nombre d'humain
	(*foule).dt = (*options).dt;		// Discrétisation du temps
	(*foule).masse = (*options).masse;			// Masse des humains
	(*foule).horloge = 0.0;			// Horloge
	// Nervosité des humains maximale Nervosite nervosite
	(*foule).nervosite = (*options).nervosite;	// dissipation

	fouleCreation(foule);

	return 0;
	}

int donneesCreationGraphique(controleurT * controleur)
	{
		fprintf(stderr, " Initialisation de la SDL2\n");
	interfaceInitialisation(&(*controleur).interface, (*controleur).options.fond);
		fprintf(stderr, " Création du graphe\n");
	grapheCreation(&(*controleur).graphe, (*controleur).options.nombre);
		fprintf(stderr, " Initialisation du graphe\n");
	grapheInitialisation((*controleur).interface.rendu, &(*controleur).graphe);
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

