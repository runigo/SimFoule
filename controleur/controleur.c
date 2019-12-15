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

#include "controleur.h"
#include "controleurClavier.h"
#include "controleurSouris.h"

	//	INITIALISATION - SUPRESSION

int controleurCorrigeDuree(controleurT * controleur);

	//	ÉVOLUTION

int controleurEvolution(controleurT * controleur);
int controleurEvolutionModeEco(controleurT * controleur);

	int controleurProjection(controleurT * controleur);
	int controleurEvolutionSysteme(controleurT * controleur);
	int controleurEvolutionDessin(controleurT * controleur);
	int controleurConstructionGraphique(controleurT * controleur);

	int controleurBoucle(controleurT * controleur);

int controleurKEYDOWN(controleurT * controleur);
int controleurTraiteEvenement(controleurT * controleur);

int controleurMemoireOptions(controleurT * controleur);

	//	CHANGEMENT DES PARAMETRES

	//		INFORMATIONS


	//	-------  INITIALISATION - SUPRESSION  -------  //

int controleurSuppression(controleurT * controleur)
	{

	fprintf(stderr, "  Suppression de la foule\n");
	fouleSuppression(&(*controleur).systeme.foule);

	fprintf(stderr, "Suppression du graphe\n");
	grapheSuppression(&(*controleur).graphe);

	fprintf(stderr, "Suppression de l'horloge\n");
	horlogeSuppression(&(*controleur).horloge);

	fprintf(stderr, "Suppression du rendu\n");
	graphiqueDestruction(&(*controleur).graphique);

	fprintf(stderr, "Suppression de la fenêtre\n");
	interfaceDestruction(&(*controleur).interface);

	fprintf(stderr, "Sortie de la SDL\n");
	interfaceQuitteSDL();

	return 0;
	}

int controleurDirections(controleurT * controleur)
	{
		// Calcul des directions

		fprintf(stderr, "Calcul des directions\n");
	batimentDirections(&(*controleur).systeme.batiment);
	return 0;
	}

int controleurInitialisation(controleurT * controleur)
	{
		// Initialisation du controleur

	int retour = 0;

	(*controleur).sortie = 0;	// Sortie de SimFoule si > 0
	(*controleur).modePause = (*controleur).options.mode;		// Evolution système ou pause
	(*controleur).modeDessin = 1;		// 1 : simulation, -1 : construction
	(*controleur).modeEco = 1;		// 0 : système-graphique, 1 : (1)système-(1)graphique, n : (n)système-(1)graphique
	(*controleur).etapeEco = 1;		// -1 : graphique, 0 : système-graphique, > 0 : système (= étape)

		//fprintf(stderr, "  Initialisation de la projection\n");
	retour += projectionInitialiseLongueurs(&(*controleur).projection, BATIMENT_X_IMP, BATIMENT_Y_IMP);

		//fprintf(stderr, "  Initialisation des commandes\n");
	retour += commandesInitialiseBoutons(&(*controleur).commandes, FENETRE_X, FENETRE_Y);

		//fprintf(stderr, "  Initialisation du système\n");
	retour += donneesInitialisationSysteme(&(*controleur).systeme, &(*controleur).options);

		//fprintf(stderr, "  Initialisation de construction\n");
	retour += constructionInitialisation(&(*controleur).construction);

		//fprintf(stderr, "Calcul des directions\n");
	retour += controleurDirections(controleur);

		//fprintf(stderr, "  Initialisation du graphe\n");
	retour += donneesCreationGraphe(&(*controleur).graphe, &(*controleur).options);

		//fprintf(stderr, "  Initialisation de l'interface graphique\n");
	retour += donneesInitialisationInterface(&(*controleur).interface, &(*controleur).options);
	retour += donneesInitialisationGraphique(&(*controleur).graphique, &(*controleur).interface, &(*controleur).options);

		//fprintf(stderr, " Initialisation horloge SDL\n");
	retour += horlogeCreation(&(*controleur).horloge);

		controleurProjection(controleur);	//	Projections

		controleurCorrigeDuree(controleur);

	return retour;
	}

int controleurReinitialisation(controleurT * controleur, char *nom)
	{
	int retour = 0;

	(*controleur).options.nom = nom;

		//fprintf(stderr, "Enregistrement des options\n");
	retour += controleurMemoireOptions(controleur);

		fprintf(stderr, "Réinitialisation du système %s\n", nom);

	retour += grapheSuppression(&(*controleur).graphe);
	retour += fouleSuppression(&(*controleur).systeme.foule);

		// Réinitialisation du système
	retour += donneesInitialisationSysteme(&(*controleur).systeme, &(*controleur).options);

		//fprintf(stderr, "Calcul des directions\n");
	retour += controleurDirections(controleur);

		//fprintf(stderr, "  Réinitialisation du graphe\n");
	retour += donneesCreationGraphe(&(*controleur).graphe, &(*controleur).options);

		controleurProjection(controleur);	//	Projections

		controleurCorrigeDuree(controleur);

	return retour;
	}

int controleurCorrigeDuree(controleurT * controleur)
	{

	(*controleur).options.duree = 60 - batimentNombreMobile(&(*controleur).systeme.batiment)/2;

	if((*controleur).options.duree < 1)
		{
		(*controleur).options.duree = 1;
		}

	return (*controleur).options.duree;
	}

int controleurMemoireOptions(controleurT * controleur)
	{
		// Mise en mémoire des paramètres

	(*controleur).options.taille = (*controleur).systeme.foule.taille;	// Taille moyenne des mobiles
	(*controleur).options.masse = (*controleur).systeme.foule.masse;	// Masse moyenne des mobiles

	(*controleur).options.nervosite = (*controleur).systeme.foule.nervosite;	// Nervosité moyenne des mobiles
	(*controleur).options.celerite = (*controleur).systeme.foule.celerite;	//	célérité moyenne des mobiles

	(*controleur).options.dt = (*controleur).systeme.foule.dt;	// discrétisation du temps

	return 0;
	}


	//	-------  ÉVOLUTION  -------  //

int controleurSimulationGraphique(controleurT * controleur)
	{
	do	{
		if (SDL_WaitEvent(&(*controleur).interface.evenement))
			{
			controleurTraiteEvenement(controleur);
			}
		}
	while((*controleur).sortie == 0);

	return 0;
	}

int controleurEvolution(controleurT * controleur)
	{
	//horlogeChrono(&(*controleur).horloge, 0);

		if((*controleur).modeDessin > 0) // Évolution du système
			{
			if((*controleur).modePause > 0)
				{
				if((*controleur).etapeEco>=0 || (*controleur).modeEco==0)
					{
					if(controleurEvolutionSysteme(controleur)!=0)
						{
						controleurBoucle(controleur);
						}
					}
				}
			}
		else	//	Évolution de la construction
			{
			controleurEvolutionDessin(controleur);
			}

	//horlogeChrono(&(*controleur).horloge, 1);

	if((*controleur).etapeEco<0 || (*controleur).modeDessin<0)
		{
		controleurProjection(controleur);	//	Projections
		controleurConstructionGraphique(controleur); // Affichage
		}

	//horlogeChrono(&(*controleur).horloge, 2);

	controleurEvolutionModeEco(controleur);

	return (*controleur).sortie;
	}

int controleurEvolutionModeEco(controleurT * controleur)
	{
			//	Évolution de l'étape du mode économie de CPU
	//(*controleur).modeEco = 1;		// 0 : système-graphique, 1 : (1)système-(1)graphique, n : (n)système-(1)graphique
	//(*controleur).etapeEco = 1;		// -1 : graphique, 0 : système-graphique, > 0 : système (= étape)

	if((*controleur).modeEco == 0)
		{
		(*controleur).etapeEco = -1;
		}
	else	//	(*controleur).modeEco > 0
		{
		switch((*controleur).etapeEco)
			{
			case -1:
				(*controleur).etapeEco = (*controleur).modeEco;break;
			case 1:
				(*controleur).etapeEco = -1;break;
			default:
				(*controleur).etapeEco --;
			}
		}

	return 0;
	}

void controleurChangeModeEco(controleurT * controleur, int mode)
	{
			//	Évolution de l'étape du mode économie de CPU
	//(*controleur).modeEco = 1;		// 0 : système-graphique, 1 : (1)système-(1)graphique, n : (n)système-(1)graphique
	//(*controleur).etapeEco = 1;		// -1 : graphique, 0 : système-graphique, > 0 : système (= étape)

	if(mode == 0)
		{
		(*controleur).modeEco = 0;		// 0 : système-graphique, 1 : (1)système-(1)graphique, n : (n)système-(1)graphique
		(*controleur).etapeEco = 0;		// -1 : graphique, 0 : système-graphique, > 0 : système (= étape)
		}
	else	//	(*controleur).modeEco > 0
		{
		(*controleur).modeEco = mode;		// 0 : système-graphique, 1 : (1)système-(1)graphique, n : (n)système-(1)graphique
		(*controleur).etapeEco = mode;		// -1 : graphique, 0 : système-graphique, > 0 : système (= étape)
		}

		printf("controleurChangeModeEco (*controleur).modeEco = %d\n", (*controleur).modeEco);

	return;
	}


int controleurBoucle(controleurT * controleur)
	{
/*
	switch((*controleur).options.boucle)
		{
		case 0:
			if((*controleur).options.initial<25)
				{
				(*controleur).options.initial++;
				}
			else
				{
				(*controleur).options.initial=0;
				}
				break;
		case 2:
			(*controleur).options.initial=-1;break;

		default:
			;
		}
*/
	controleurReinitialisation(controleur, (*controleur).options.nom);

	return 0;
	}


int controleurProjection(controleurT * controleur)
	{
	int x, y; //  fenêtre, puis souris

		// Récupération de la taille de la fenêtre
	SDL_GetWindowSize((*controleur).interface.fenetre, &x, &y);

		// Réinitialisation des commandes si la fenêtre change de taille
	if((*controleur).graphique.fenetreX!=x || (*controleur).graphique.fenetreY!=y)
		{
		(*controleur).graphique.fenetreX=x;
		(*controleur).graphique.fenetreY=y;
		projectionChangeFenetre(&(*controleur).projection, x, y);
		commandesInitialiseBoutons(&(*controleur).commandes, x, y);
		}

		// Réinitialisation de la position de la souris
	SDL_PumpEvents();
	SDL_GetMouseState(&x,&y);
	commandesInitialiseSouris(&(*controleur).commandes, x, y);

		//	Projection des fonctions sur les graphes
	if((*controleur).modeDessin > 0)
		{
	projectionBatimentPlan(&(*controleur).systeme.batiment, &(*controleur).projection, &(*controleur).graphe);
	projectionBatimentSens(&(*controleur).systeme.batiment, &(*controleur).projection, &(*controleur).graphe);
	projectionFoulePoints(&(*controleur).systeme.foule, &(*controleur).projection, &(*controleur).graphe);
		}
	else	//	Projection de la construction
		{
	projectionBatimentPlan(&(*controleur).construction.batiment, &(*controleur).projection, &(*controleur).graphe);
		}

		//	Projection du système sur les commandes
	projectionSystemeCommandes(&(*controleur).systeme, &(*controleur).projection, &(*controleur).commandes, (*controleur).options.duree, (*controleur).modePause);

	return (*controleur).sortie;
	}

int controleurEvolutionSysteme(controleurT * controleur)
	{

	if((*controleur).systeme.foule.restant>0)
		{
		systemeEvolution(&(*controleur).systeme, (*controleur).options.duree);
		}
	if((*controleur).systeme.foule.restant==0)
		{
		controleurAfficheForces(controleur);
		(*controleur).systeme.foule.restant = -1;
		return 1;
		}
	return 0;
	}

int controleurEvolutionDessin(controleurT * controleur)
	{


	if((*controleur).appui == 1)
		{
		//fprintf(stderr, "controleurEvolutionDessin ((*controleur).appui == 1)\n");
		int X = (*controleur).commandes.sourisX / CELLULE ;
		int Y = (*controleur).commandes.sourisY / CELLULE ;
		constructionProjection(&(*controleur).construction);	// Projette le niveau 1 sur l'étage 0
		constructionPositionFinale(&(*controleur).construction, X, Y); // Enregistre la position actuelle de la souris
		constructionAjouteTrace(&(*controleur).construction, 0);	// Ajoute le tracé sur l'étage 0
		}
	//else		{		;		}

	return 0;
	}

int controleurConstructionGraphique(controleurT * controleur)
	{

		//fprintf(stderr, "Nettoyage de l'affichage\n");
	graphiqueNettoyage(&(*controleur).graphique);

		//fprintf(stderr, "Dessin du fond\n");
	//graphiqueFond(&(*controleur).graphique);

		//fprintf(stderr, "Dessin des Commandes\n");
	//graphiqueCommandes(&(*controleur).graphique, &(*controleur).commandes);

		//fprintf(stderr, "Dessin des graphes\n");
	if((*controleur).modeDessin > 0)
		{
		if((*controleur).options.dessineAngle==1)
			{
			graphiqueDessineAngle(&(*controleur).graphique, &(*controleur).graphe);
			}
		if((*controleur).options.dessineMur==1)
			{
			graphiqueDessineMur(&(*controleur).graphique, &(*controleur).graphe);
			}
		if((*controleur).options.dessineMobile==1)
			{
			graphiqueDessineMobile(&(*controleur).graphique, &(*controleur).graphe, (*controleur).options.taille);
			}
		}
	else	//	Dessin de la construction
		{
		graphiqueDessineStatut(&(*controleur).graphique, &(*controleur).graphe);
		}

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	graphiqueMiseAJour(&(*controleur).graphique);

	return (*controleur).sortie;
	}

int controleurTraiteEvenement(controleurT * controleur)
	{
	switch((*controleur).interface.evenement.type)
		{
		case SDL_QUIT:
			(*controleur).sortie = 1;break;
		case SDL_MOUSEWHEEL:
			controleurSourisDefile(controleur);break;
		case SDL_MOUSEMOTION:
			controleurSourisMouvement(controleur);break;
		case SDL_MOUSEBUTTONDOWN:
			controleurSourisBouton(controleur, 1);break;
		case SDL_MOUSEBUTTONUP:
			controleurSourisBouton(controleur, 0);break;
		case SDL_USEREVENT:
			controleurEvolution(controleur);break;
		case SDL_KEYDOWN:
			controleurKEYDOWN(controleur);break;
		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurKEYDOWN(controleurT * controleur)
	{
	int Maj = 0;
	int ctrl = 0;

	if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
	|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT))
		{
		Maj = 1;
		}
	if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL)
	|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RCTRL) == KMOD_RCTRL))
		{
		ctrl = 1;
		}
	if(Maj == 0 && ctrl == 0)
		{
		return controleurClavier(controleur);
		}
	else
		{
		if(Maj == 1 && ctrl == 1)
			{
			return controleurClavierCtrlMaj(controleur);
			}
		else
			{
			if(Maj == 1 )
				{
				return controleurClavierMaj(controleur);
				}
			else
				{
				return controleurClavierCtrl(controleur);
				}
			}
		}

	return -1;
	}


	//	-------  CHANGEMENT DES PARAMETRES  -------  //


void controleurChangeModePause(controleurT * controleur)
	{
	(*controleur).modePause=-(*controleur).modePause;

	if((*controleur).modePause > 0)
		{
		fprintf(stderr, "modePause : évolution\n");
		}
	else
		{
		fprintf(stderr, "modePause : pause\n");
		}

	return;
	}

void controleurChangeModeDessin(controleurT * controleur)
	{
	(*controleur).modeDessin = -(*controleur).modeDessin;

	if((*controleur).modeDessin > 0)
		{
		fprintf(stderr, "modeDessin : simulation\n");
		grapheInitialisation(&(*controleur).graphe, BATIMENT_X_MAX, BATIMENT_Y_MAX, BATIMENT_Z_IMP);
		}
	else
		{
		fprintf(stderr, "modeDessin : construction\n");
		grapheInitialisation(&(*controleur).graphe, BATIMENT_X_MAX, BATIMENT_Y_MAX, BATIMENT_Z_IMP);
		}

	return;
	}

void controleurChangeVitesse(controleurT * controleur, float facteur)
	{
	if(facteur < 0.0)
		{
		(*controleur).options.duree = DUREE;
		}
	else
		{
		if( (*controleur).options.duree > 11 )
			{
			(*controleur).options.duree = (*controleur).options.duree * facteur;
			}
		else
			{
			if( facteur > 1)
				{
				(*controleur).options.duree ++;
				}
			else
				{
				if( (*controleur).options.duree > 1 )
					{
					(*controleur).options.duree --;
					}
				else
					{
					fprintf(stderr, "duree minimale atteinte, ");
					}
				}
			}

		if( (*controleur).options.duree > DUREE_MAX)
			{
			fprintf(stderr, "duree maximale atteinte, ");
			(*controleur).options.duree = DUREE_MAX;
			}
		}
	fprintf(stderr, "duree = %d\n", (*controleur).options.duree);
	return;
	}

int controleurChangeDessin(int * construction)
	{ // dessine ou non les murs, les mobiles, les sens à suivre.
	if((*construction)==0)
		{
		(*construction)=1;
		}
	else
		{
		(*construction)=0;
		}

	return 0;
	}


	//	-------  INFORMATIONS  -------  //

int controleurAfficheForces(controleurT * controleur)
	{
	printf("\nForces maximales atteintes\n");
			// Vérification des valeurs les plus grandes
	printf("  force Batiment Max = %f\n", (*controleur).systeme.forceBatimentMax);
	printf("  force Mobiles Max = %f\n", (*controleur).systeme.forceMobilesMax);
	printf("  force Murs Max = %f\n", (*controleur).systeme.forceMursMax);
	printf("  force Somme Max = %f\n", (*controleur).systeme.forceSommeMax);
	
	return 0;
	}

int controleurAffiche(controleurT * controleur)
	{

	fprintf(stderr, "\n(*controleur).graphique.fenetreY = %d\n", (*controleur).graphique.fenetreY);
	fprintf(stderr, "(*controleur).commandes.sourisY = %d\n", (*controleur).commandes.sourisY);
	fprintf(stderr, "(*controleur).graphique.fenetreX = %d\n", (*controleur).graphique.fenetreX);
	fprintf(stderr, "(*controleur).commandes.sourisX = %d\n\n", (*controleur).commandes.sourisX);

	fprintf(stderr, "(*controleur).appui = %d\n", (*controleur).appui);
	fprintf(stderr, "(*controleur).curseurX = %d\n", (*controleur).curseurX);
	fprintf(stderr, "(*controleur).curseurY = %d\n\n", (*controleur).curseurY);

	fprintf(stderr, "(*controleur).modePause = %d\n", (*controleur).modePause);
	fprintf(stderr, "(*controleur).modeDessin = %d\n", (*controleur).modeDessin);
	fprintf(stderr, "(*controleur).sortie = %d\n\n", (*controleur).sortie);

	fprintf(stderr, "(*controleur).commandes.boutons = %d\n", (*controleur).commandes.boutons);


	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////
