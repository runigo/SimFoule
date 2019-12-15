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


#include "donnees.h"


int donneesOptionsImplicite(optionsT * options)
	{
		// Préréglage des valeurs optionnelles, 
		// 	réglage des valeurs implicites

	(*options).mode = 1;	// -1 : Pause, 1 : Simulation
	(*options).duree = DUREE;	// nombre d'incrémentation de la foule par affichage
	(*options).boucle = 1;	// répétition des simulations

	(*options).initial = 1;	// 1 : Initialisation fichier construction.

	(*options).nom = "a";	// Nom du fichier d'initialisation.

	(*options).nombre = 0;	// Nombre de mobiles

	(*options).taille = CELLULE;	// Taille moyenne des mobiles
	(*options).masse = MASSE_MAX;	// Masse moyenne des mobiles

	(*options).nervosite = NERVOSITE_MAX;	// Nervosité moyenne des mobiles
	(*options).celerite = CELERITE_MAX;	//	célérité moyenne des mobiles

	(*options).dt = DT_MAX;	// discrétisation du temps

			//	Dessin des graphes 0 ou 1
	(*options).dessineAngle=0;
	(*options).dessineMur=1;
	(*options).dessineMobile=1;

			//	Dimension du batiment
	(*options).batimentX = BATIMENT_X_IMP;
	(*options).batimentY = BATIMENT_Y_IMP;
	(*options).batimentZ = BATIMENT_Z_IMP;
	return 0;
	}



int donneesInitialisationSysteme(systemeT * systeme, optionsT * options)
	{

		fprintf(stderr, "  Initialisation du système\n");
	systemeInitialisation(systeme, (*options).dt);

		fprintf(stderr, "  Initialisation du batiment : %s\n", (*options).nom);
	donneesInitialisationBatiment(&(*systeme).batiment, options);

		fprintf(stderr, "  Création et initialisation de la foule\n");
	donneesCreationFoule(&(*systeme).foule, options);
	donneesInitialisationFoule(&(*systeme).foule, &(*systeme).batiment);

	return 0;
	}



int donneesInitialisationBatiment(batimentT * batiment, optionsT * options)
	{

	batimentInitialiseVide(batiment);
/*
	if((*options).initial < 0)
		{
		(*options).nombre = batimentInitialiseImplicite(batiment, -(*options).initial);
		}
	else
		{
		if((*options).initial < 26)
			{
			(*options).nombre = fichierLecture(batiment, (*options).initial);
			}
		else
			{
			(*options).nombre = batimentInitialiseImplicite(batiment, (*options).initial);
			}
		}
*/

	if(fichierLecture(batiment, options, (*options).nom) < 0) // Erreur de lecture
		{
		printf("	Initialisation implicite du batiment\n");
		batimentInitialiseImplicite(batiment, -(*options).initial);
		}

	(*options).nombre = batimentNombreMobile(batiment);

	(*options).batimentX = (*batiment).etage[0].etageX;
	(*options).batimentY = (*batiment).etage[0].etageY;
	(*options).batimentZ = (*batiment).batimentZ;

	return 0;
	}

int donneesSauvegardeConstruction(constructionT * construction, optionsT * options, char * nom)
	{

	batimentProjection(&(*construction).batiment, &(*construction).normal);

	batimentNormalise(&(*construction).normal, 1);

	(*construction).normal.batimentZ = 1;

	fichierEcriture(&(*construction).normal, options, nom);

	return 0;
	}
/*
int donneesSauvegardeBatiment(batimentT * batiment, optionsT * options)
	{
	(void)options;

	batimentNormalise(batiment, 1);

	fichierEcriture(batiment, options);

	return 0;
	}
*/
int donneesCreationFoule(fouleT * foule, optionsT * options)
	{
		// Initialisation de la foule

	(*foule).dt = (*options).dt;		// Discrétisation du temps
	(*foule).horloge = 0.0;			// Horloge

	(*foule).nombre = (*options).nombre;	// Nombre de mobile
	(*foule).restant = (*options).nombre;	// Nombre de mobile restant à sortir

	(*foule).taille = (*options).taille;		// Taille moyenne des mobiles
	(*foule).masse = (*options).masse;			// Masse moyenne des mobiles

	(*foule).nervosite = (*options).nervosite;	// Nervosité moyenne des mobiles
	(*foule).celerite = (*options).celerite;	//	Nervosité moyenne des mobiles

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

		// Position des mobiles
	for(k=0;k<(*batiment).batimentZ;k++)
		{
		for(i=0;i<(*batiment).etage[k].etageX;i++)
			{
			for(j=0;j<(*batiment).etage[k].etageY;j++)
				{
				if((*batiment).etage[k].cellule[i][j].statut == 9)
					{
					mobileInitialisePosition(&iter->mobile, i*CELLULE+centrage, j*CELLULE+centrage, k);
					iter=iter->suivant;
					compteur ++;
					}
				}
			}
		}
	fprintf(stderr, "    donneesInitialisationFoule : position de %d mobiles initialisée.\n", compteur);

	return 0;
	}

int donneesInitialisationInterface(interfaceT * interface, optionsT * options)
	{
	(void)options;
		fprintf(stderr, "    donneesInitialisationInterface\n");
	interfaceInitialisationSDL();
	interfaceCreation(interface);
	return 0;
	}


int donneesInitialisationGraphique(graphiqueT * graphique, interfaceT * interface, optionsT * options)
	{
		fprintf(stderr, "    donneesInitialisationGraphique\n");
	graphiqueInitialisation(graphique, interface, (*options).taille);
	//	fprintf(stderr, "    donneesInitialisationGraphique : sortie\n");

	return 0;
	}

int donneesCreationGraphe(grapheT * graphe, optionsT * options)
	{

	grapheInitialisation(graphe, (*options).batimentX, (*options).batimentY, (*options).batimentZ);

	return grapheCreation(graphe, (*options).nombre);
	}

//////////////////////////////////////////////////////////////////////////

