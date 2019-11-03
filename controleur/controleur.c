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

#include "controleur.h"

int controleurEvolution(controleurT * controleur);

	int controleurProjection(controleurT * controleur);
	int controleurEvolutionSysteme(controleurT * controleur);
	int controleurConstructionGraphique(controleurT * controleur);

	int controleurBoucle(controleurT * controleur);

	void controleurChangeMode(controleurT * controleur);
	void controleurChangeVitesse(controleurT * controleur, float facteur);
	void controleurChangeDessin(int * dessine);


int controleurTraiteEvenement(controleurT * controleur);

	int controleurClavier(controleurT * controleur);
	int controleurClavierMaj(controleurT * controleur);
	int controleurClavierCtrl(controleurT * controleur);
	int controleurClavierCtrlMaj(controleurT * controleur);


int controleurCommandes(controleurT * controleur, int zone);
int controleurInitialiseParametres(controleurT * controleur, int forme);
int controleurInitialiseFluxons(controleurT * controleur);
int controleurInitialiseNulle(controleurT * controleur);

int controleurSouris(controleurT * controleur);
int controleurDefile(controleurT * controleur);
int controleurDefilePointDeVue(controleurT * controleur);
int controleurDefileCommandes(controleurT * controleur, int zone);
void controleurBoutonSouris(controleurT * controleur, int appui);
void controleurAfficheSouris(controleurT * controleur);

int controleurAfficheForces(controleurT * controleur);

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

	batimentDirections(&(*controleur).systeme.batiment);
	return 0;
	}

int controleurInitialisation(controleurT * controleur)
	{
		// Initialisation du controleur

	(*controleur).options.sortie = 0;	// Sortie de SimFoule si > 0
	(*controleur).modePause = (*controleur).options.mode;		// Evolution système ou pause

	systemeInitialisation(&(*controleur).systeme, (*controleur).options.dt);

		fprintf(stderr, "  Initialisation de la projection\n");
	projectionInitialiseLongueurs(&(*controleur).projection, BATIMENT_X_IMP, BATIMENT_Y_IMP);

		fprintf(stderr, "  Initialisation du batiment\n");
	donneesInitialisationBatiment(&(*controleur).systeme.batiment, &(*controleur).options);

		fprintf(stderr, "  Initialisation de la foule\n");
	donneesCreationFoule(&(*controleur).systeme.foule, &(*controleur).options);
	donneesInitialisationFoule(&(*controleur).systeme.foule, &(*controleur).systeme.batiment);

		fprintf(stderr, "  Initialisation de l'interface graphique\n");
	donneesCreationGraphe(&(*controleur).graphe, &(*controleur).options);
	donneesInitialisationInterface(&(*controleur).interface, &(*controleur).options);
	donneesInitialisationGraphique(&(*controleur).graphique, &(*controleur).interface, &(*controleur).options);

		fprintf(stderr, " Initialisation horloge SDL\n");
	horlogeCreation(&(*controleur).horloge);

	return 0;
	}

int controleurReinitialisation(controleurT * controleur, int initial)
	{

	(*controleur).options.initial = initial;

		fprintf(stderr, "Réinitialisation du système %d\n", (*controleur).options.initial);

	grapheSuppression(&(*controleur).graphe);
	fouleSuppression(&(*controleur).systeme.foule);

		// Réinitialisation du système
	systemeInitialisation(&(*controleur).systeme, (*controleur).options.dt);

		//fprintf(stderr, "  Réinitialisation du batiment\n");
	donneesInitialisationBatiment(&(*controleur).systeme.batiment, &(*controleur).options);

		//fprintf(stderr, "  Réinitialisation de la foule\n");
	donneesCreationFoule(&(*controleur).systeme.foule, &(*controleur).options);
	donneesInitialisationFoule(&(*controleur).systeme.foule, &(*controleur).systeme.batiment);

		//fprintf(stderr, "  Réinitialisation du graphe\n");
	donneesCreationGraphe(&(*controleur).graphe, &(*controleur).options);

		//fprintf(stderr, "Calcul des directions\n");
	assert(controleurDirections(controleur)==0);

	return 0;
	}

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

	horlogeChrono(&(*controleur).horloge, 0);

	controleurProjection(controleur);

	horlogeChrono(&(*controleur).horloge, 1);

	if((*controleur).modePause > 0)
		{
		if(controleurEvolutionSysteme(controleur)!=0)
			{
			controleurBoucle(controleur);
			}
		}

	horlogeChrono(&(*controleur).horloge, 2);

	controleurConstructionGraphique(controleur);

	horlogeChrono(&(*controleur).horloge, 3);

	return (*controleur).sortie;
	}

int controleurBoucle(controleurT * controleur)
	{
	controleurReinitialisation(controleur, (*controleur).options.initial);
	if((*controleur).options.initial<25)
		{
		(*controleur).options.initial++;
		}
	else
		{
		(*controleur).options.initial=0;
		}
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

		// Réinitialisation des commandes de la souris
	SDL_PumpEvents();
	SDL_GetMouseState(&x,&y);
	commandesInitialiseSouris(&(*controleur).commandes, x, y);

		//	Projection des fonctions sur les graphes

	projectionBatimentPlan(&(*controleur).systeme.batiment, &(*controleur).projection, &(*controleur).graphe);

	projectionBatimentSens(&(*controleur).systeme.batiment, &(*controleur).projection, &(*controleur).graphe);

	projectionFoulePoints(&(*controleur).systeme.foule, &(*controleur).projection, &(*controleur).graphe);

	projectionSystemeCommandes(&(*controleur).systeme, &(*controleur).projection, &(*controleur).commandes, (*controleur).options.duree, (*controleur).modePause);

	return (*controleur).sortie;
	}

int controleurEvolutionSysteme(controleurT * controleur)
	{

	if((*controleur).systeme.foule.restant>0)
		{
		//fprintf(stderr, "Evolution temporelle de la foule\n");
		systemeEvolution(&(*controleur).systeme, (*controleur).options.duree);
		}
	if((*controleur).systeme.foule.restant==0)
		{
		//fprintf(stderr, "Fin de la simulation\n");
		controleurAfficheForces(controleur);
		(*controleur).systeme.foule.restant = -1;
		return 1;
		}
	return 0;
	}

int controleurConstructionGraphique(controleurT * controleur)
	{

		//fprintf(stderr, "Nettoyage de l'affichage\n");
	//graphiqueNettoyage(&(*controleur).graphique);

		//fprintf(stderr, "Dessin du fond\n");
	graphiqueFond(&(*controleur).graphique);

		//fprintf(stderr, "Dessin des Commandes\n");
	//graphiqueCommandes(&(*controleur).graphique, &(*controleur).commandes);

		//fprintf(stderr, "Dessin des graphes\n");
	if((*controleur).options.dessineAngle==1)
		graphiqueDessineAngle(&(*controleur).graphique, &(*controleur).graphe);
	if((*controleur).options.dessineMur==1)
		graphiqueDessineMur(&(*controleur).graphique, &(*controleur).graphe);
	if((*controleur).options.dessineMobile==1)
		graphiqueDessineMobile(&(*controleur).graphique, &(*controleur).graphe, (*controleur).options.taille);

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	graphiqueMiseAJour(&(*controleur).graphique);

	return (*controleur).sortie;
	}

int controleurTraiteEvenement(controleurT * controleur)
	{
	int sortie = 0;
	switch((*controleur).interface.evenement.type)
		{
		case SDL_QUIT:
			(*controleur).sortie = 1;break;
		case SDL_MOUSEWHEEL:
			controleurDefile(controleur);break;
		case SDL_MOUSEMOTION:
			controleurSouris(controleur);break;
		case SDL_MOUSEBUTTONDOWN:
			controleurBoutonSouris(controleur, 1);break;
		case SDL_MOUSEBUTTONUP:
			controleurBoutonSouris(controleur, 0);break;
		case SDL_USEREVENT:
			controleurEvolution(controleur);break;
		case SDL_KEYDOWN:
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
				sortie = controleurClavier(controleur);break;
				}
			else
				{
				if(Maj == 1 && ctrl == 1)
					{
					sortie = controleurClavierCtrlMaj(controleur);break;
					}
				else
					{
					if(Maj == 1 )
						{
						sortie = controleurClavierMaj(controleur);break;
						}
					else
						{
						sortie = controleurClavierCtrl(controleur);break;
						}
					}
				}
			}
		default:
			;
		}
	if(sortie!=0) (*controleur).sortie = 1;
	return (*controleur).sortie;
	}

void controleurChangeMode(controleurT * controleur)
	{
	(*controleur).modePause=-(*controleur).modePause;

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

void controleurChangeDessin(int * dessine)
	{
	if((*dessine)==0)
		(*dessine)=1;
	else
		(*dessine)=0;

	return;
	}

int controleurClavier(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Mode : évolution du système en pause
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;

	// Vitesse de la simulation
		case SDLK_KP_PLUS:
			controleurChangeVitesse(controleur, 1.1);break;
		case SDLK_KP_MINUS:
			controleurChangeVitesse(controleur, 0.91);break;
		case SDLK_F9:
			controleurChangeVitesse(controleur, 0.32);break;
		case SDLK_F10:
			controleurChangeVitesse(controleur, 0.91);break;
		case SDLK_F11:
			controleurChangeVitesse(controleur, 1.1);break;
		case SDLK_F12:
			controleurChangeVitesse(controleur, 3.1);break;

	// Affichage des informations
		case SDLK_F1:
			etageAffiche(&(*controleur).systeme.batiment.etage[0]);break;
	/*	case SDLK_F2:
			controleurAfficheVitesse(&(*controleur).options.dessineAngle);break;
		case SDLK_F3:
			controleurAfficheOptions(&(*controleur).options.dessineMur);break;
		case SDLK_F4:
			controleurAfficheMobile(&(*controleur).options.dessineMobile);break;
*/
		case SDLK_F5:
			controleurAfficheForces(controleur);break;
		case SDLK_F6:
			controleurChangeDessin(&(*controleur).options.dessineAngle);break;
		case SDLK_F7:
			controleurChangeDessin(&(*controleur).options.dessineMur);break;
		case SDLK_F8:
			controleurChangeDessin(&(*controleur).options.dessineMobile);break;


		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierMaj(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{

	// Sortie

		case SDLK_ESCAPE:
			(*controleur).sortie = 1;break;

    // Mode : évolution du système en pause

		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;


	// Réinitialisation du système
		// Lecture des fichier
		case SDLK_a:
			controleurReinitialisation(controleur, 0);break;
		case SDLK_z:
			controleurReinitialisation(controleur, 1);break;
		case SDLK_e:
			controleurReinitialisation(controleur, 2);break;
		case SDLK_r:
			controleurReinitialisation(controleur, 3);break;
		case SDLK_t:
			controleurReinitialisation(controleur, 4);break;
		case SDLK_y:
			controleurReinitialisation(controleur, 5);break;
		case SDLK_u:
			controleurReinitialisation(controleur, 6);break;
		case SDLK_i:
			controleurReinitialisation(controleur, 7);break;
		case SDLK_o:
			controleurReinitialisation(controleur, 8);break;
		case SDLK_p:
			controleurReinitialisation(controleur, 9);break;
		case SDLK_q:
			controleurReinitialisation(controleur, 10);break;
		case SDLK_s:
			controleurReinitialisation(controleur, 11);break;
		case SDLK_d:
			controleurReinitialisation(controleur, 12);break;
		case SDLK_f:
			controleurReinitialisation(controleur, 13);break;
		case SDLK_g:
			controleurReinitialisation(controleur, 14);break;
		case SDLK_h:
			controleurReinitialisation(controleur, 15);break;
		case SDLK_j:
			controleurReinitialisation(controleur, 16);break;
		case SDLK_k:
			controleurReinitialisation(controleur, 17);break;
		case SDLK_l:
			controleurReinitialisation(controleur, 18);break;
		case SDLK_m:
			controleurReinitialisation(controleur, 19);break;
		case SDLK_w:
			controleurReinitialisation(controleur, 20);break;
		case SDLK_x:
			controleurReinitialisation(controleur, 21);break;
		case SDLK_c:
			controleurReinitialisation(controleur, 22);break;
		case SDLK_v:
			controleurReinitialisation(controleur, 23);break;
		case SDLK_b:
			controleurReinitialisation(controleur, 24);break;
		case SDLK_n:
			controleurReinitialisation(controleur, 25);break;

		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierCtrl(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Sortie
		case SDLK_ESCAPE:
			(*controleur).sortie = 1;break;
	// Mode : évolution du système en pause
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;

	// Réinitialisation du système
	/*	case SDLK_a:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 0);break;
		case SDLK_z:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 1);break;
		case SDLK_e:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 2);break;
		case SDLK_r:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 3);break;
		case SDLK_t:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 4);break;
		case SDLK_y:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 5);break;
		case SDLK_u:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 6);break;
		case SDLK_i:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 7);break;
		case SDLK_o:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 8);break;
		case SDLK_p:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 9);break;
*/
	// Réinitialisation du système
/*		case SDLK_a:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 0);break;
		case SDLK_z:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, 1);break;
		case SDLK_e:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 2);break;
		case SDLK_r:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 3);break;
		case SDLK_t:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 4);break;
		case SDLK_y:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 5);break;
		case SDLK_u:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 6);break;
		case SDLK_i:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 7);break;
		case SDLK_o:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 8);break;
		case SDLK_p:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 9);break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 10);break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 11);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 12);break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 13);break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 14);break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 15);break;
		case SDLK_j:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 16);break;
		case SDLK_k:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 17);break;
		case SDLK_l:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 18);break;
		case SDLK_m:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 19);break;
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 20);break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 21);break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 22);break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 23);break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 24);break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, 25);break;*/
		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierCtrlMaj(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Sortie
		case SDLK_ESCAPE:
			(*controleur).sortie = 1;break;
	// Mode : évolution du système en pause
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;
/*
		// Ecriture des fichiers
		case SDLK_a:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 0);break;
		case SDLK_z:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 1);break;
		case SDLK_e:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 2);break;
		case SDLK_r:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 3);break;
		case SDLK_t:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 4);break;
		case SDLK_y:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 5);break;
		case SDLK_u:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 6);break;
		case SDLK_i:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 7);break;
		case SDLK_o:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 8);break;
		case SDLK_p:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 9);break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 10);break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 11);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 12);break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 13);break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 14);break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 15);break;
		case SDLK_j:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 16);break;
		case SDLK_k:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 17);break;
		case SDLK_l:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 18);break;
		case SDLK_m:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 19);break;
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 20);break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 21);break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 22);break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 23);break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 24);break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphe, 25);break;*/
		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurSouris(controleurT * controleur)
	{
	(void)controleur;
/*
				// Action des mouvements de la souris
	float x, y;
	if((*controleur).appui==1)
		{
		if( (*controleur).commandes.sourisX < (*controleur).commandes.rotatifs && (*controleur).commandes.sourisY < (*controleur).commandes.bas )
			{
			//fprintf(stderr, "controleurSouris xrel = %d\n", (*controleur).interface.evenement.motion.xrel);
			x=-0.0031*(float)((*controleur).interface.evenement.motion.xrel);
			y=0.0031*(float)((*controleur).interface.evenement.motion.yrel);
				//fprintf(stderr, "controleurSouris yrel = %d\n", (*controleur).interface.evenement.motion.yrel);
				//fprintf(stderr, "controleurSouris yrel = %d\n", (*controleur).interface.evenement.motion.yrel);
			projectionChangePsi(&(*controleur).projection, x);
			projectionChangePhi(&(*controleur).projection, y);
			}
		}
*/
	return (*controleur).sortie;
	}

int controleurDefile(controleurT * controleur)
	{
	(void)controleur;
/*
				// Action des mouvements de la mollette

	if((*controleur).commandes.sourisX>(*controleur).commandes.rotatifs)
		{
		controleurDefileCommandes(controleur, 1);
		}
	else
		{
		if((*controleur).commandes.sourisY>(*controleur).commandes.bas)
			{
			controleurDefileCommandes(controleur, 3);
			}
		else
			{
			controleurDefilePointDeVue(controleur);
			}
		}
*/
	return 0;
	}

int controleurDefilePointDeVue(controleurT * controleur)
	{
	(void)controleur;
/*
				// Action des mouvements de la mollette dans la zone 1

	if((*controleur).interface.evenement.wheel.y > 0) // scroll up
		{
		//projectionChangeDistance(&(*controleur).projection, 1.1);
		projectionChangeTaille(&(*controleur).projection, 1.03);
		//fprintf(stderr, "evenement.wheel.y = %d\n", (*controleur).interface.evenement.wheel.y);
		//fprintf(stderr, "Distance = %f\n", (*controleur).projection.pointDeVue.r);
		}
	else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
		{
		//projectionChangeDistance(&(*controleur).projection, 0.9);
		projectionChangeTaille(&(*controleur).projection, 0.97);
		//fprintf(stderr, "evenement.wheel.y = %d\n", (*controleur).interface.evenement.wheel.y);
		//fprintf(stderr, "Distance = %f\n", (*controleur).projection.pointDeVue.r);
		}

	//if(event.wheel.x > 0) // scroll right{}
	//else if(event.wheel.x < 0) // scroll left{}
*/
	return 0;
	}

void controleurBoutonSouris(controleurT * controleur, int appui)
	{
	(void)controleur;
	(void)appui;
/*
				// Action du bouton gauche de la souris

	(*controleur).appui=appui;
	
	if(appui==1)
		{
		if((*controleur).commandes.sourisX>(*controleur).commandes.rotatifs)
			{
			if((*controleur).commandes.sourisX>(*controleur).commandes.boutons)
				{
				controleurCommandes(controleur, 2);
				}
			else
				{
				controleurCommandes(controleur, 1);
				}
			}
		else
			{
			if((*controleur).commandes.sourisY>(*controleur).commandes.bas)
				{
				controleurCommandes(controleur, 3);
				}
			else
				{
				controleurCommandes(controleur, 0);
				}
			}
		}
*/
	return;
	}

int controleurCommandes(controleurT * controleur, int zone)
	{
				// Action du bouton gauche de la souris
				// dans les zones 2 et 3

	int commande;
	if(zone==2)
		{
		commande = commandeBoutons(&(*controleur).commandes);
		switch(commande)	//	
			{
		/*	case 0: // Périodique
				changeConditionsLimites(&(*controleur).systeme, 0);break;
			case 1: // Libre
				changeConditionsLimites(&(*controleur).systeme, 1);break;
			case 2: // Fixe
				changeConditionsLimites(&(*controleur).systeme, 2);break;
			case 3: // Mixte
				changeConditionsLimites(&(*controleur).systeme, 4);break;
			case 4: // Uniforme
				changeFormeDissipation(&(*controleur).systeme, 1);break;
			case 5: // Nulle
				changeFormeDissipation(&(*controleur).systeme, 0);break;
			case 6: // Extrémité
				changeFormeDissipation(&(*controleur).systeme, 2);break;
			case 7: // Marche
				moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs,1);break;
			case 8: // Arrêt
				moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs,0);break;
			case 9: // Droite
				moteursSensJosephson(&(*controleur).systeme.moteurs,1);break;
			case 10: // Gauche
				moteursSensJosephson(&(*controleur).systeme.moteurs,-1);break;
			case 11: // Arrêt
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 0);break;
			case 12: // Sinus
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 1);break;
			case 13: // Carré
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 2);break;
			case 14: // Impulsion
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 3);break;
			case 15: // Fluxon
				changeDephasage(&(*controleur).systeme, 1);break;
			case 16: // Anti F.
				changeDephasage(&(*controleur).systeme, -1);break; */
			default:
				;
			}
		}
	if(zone==3)
		{
		commande = commandeTriangles(&(*controleur).commandes);
		switch(commande)	//	
			{
		/*	case 0:
				(*controleur).projection.rotation=3;break;
			case 1:
				(*controleur).projection.rotation=1;break;
			case 2:
				(*controleur).projection.rotation=0;break;
			case 3:
				(*controleur).projection.rotation=-1;break;
			case 4:
				(*controleur).projection.rotation=-3;break;
			case 5:
				controleurChangeVitesse(controleur, 0.32);break;
			case 6:
				controleurChangeVitesse(controleur, 0.91);break;
			case 7:
				controleurChangeMode(controleur);break;
			case 8:
				controleurChangeVitesse(controleur, -1.0);break;
			case 9:
				controleurChangeVitesse(controleur, 1.1);break;
			case 10:
				controleurChangeVitesse(controleur, 3.1);break;
			case 11:
				systemeInitialisePosition(&(*controleur).systeme, 1);break;
			case 12:
				systemeInitialisePosition(&(*controleur).systeme, 2);break;
			case 13:
				systemeInitialisePosition(&(*controleur).systeme, 3);break;
			case 14:
				systemeInitialisePosition(&(*controleur).systeme, 4);break;
			case 15:
				systemeInitialisePosition(&(*controleur).systeme, 5);break;
			case 16:
				systemeInitialisePosition(&(*controleur).systeme, 6);break;
			case 17:
				controleurInitialiseParametres(controleur, 1);break;
			case 18:
				controleurInitialiseParametres(controleur, 2);break;
			case 19:
				controleurInitialiseParametres(controleur, 3);break;
			case 20:
				controleurInitialiseParametres(controleur, 4);break;*/
			default:
				;
			}
		}
	return 0;
	}

int controleurInitialiseParametres(controleurT * controleur, int forme)
	{
	(void)controleur;
	(void)forme;
/*
	switch(forme)
		{
		case 0:
			controleurInitialiseNulle(controleur);break;
		case 1:
			controleurInitialiseNulle(controleur);break;
		case 2:
			controleurInitialiseNulle(controleur);
			moteursChangeGenerateur(&(*controleur).systeme.moteurs, 1);
			changeFormeDissipation(&(*controleur).systeme, 2);break;
		case 3:
			controleurInitialiseFluxons(controleur);
			changeDissipation(&(*controleur).systeme, 0.33);break;
		case 4:
			controleurInitialiseFluxons(controleur);
			changeFormeDissipation(&(*controleur).systeme, 2);	// Extrémitée absorbante
			break;
		default:
			controleurInitialiseNulle(controleur);break;
		}
*/
	return 0;
	}

int controleurInitialiseNulle(controleurT * controleur)
	{
	(void)controleur;
/*
	moteursChangeGenerateur(&(*controleur).systeme.moteurs, 0);
	(*controleur).systeme.premier->pendule.dephasage = 0; // Supprime les fluxons

		// Condition au limites libres
	changeConditionsLimites(&(*controleur).systeme, 1);

		// Réglage du couplage
	changeCouplageMoyenne(&(*controleur).systeme);

		// Réglage de la dissipation
	changeDissipationMoyenne(&(*controleur).systeme);
	changeFormeDissipation(&(*controleur).systeme, 0);

		// Réglage du moteur josephson
	moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs, 0);
	moteursChangeJosephsonMoyenne(&(*controleur).systeme.moteurs);

		// Réglage du moteur périodique
	moteursChangeGenerateur(&(*controleur).systeme.moteurs, 0);
*/
	return 0;
	}

int controleurInitialiseFluxons(controleurT * controleur)
	{
	(void)controleur;
/*
			controleurInitialiseNulle(controleur);

	changeDephasage(&(*controleur).systeme, -6*PI); // Ajoute 3 fluxons

		// Condition au limites périodique
	changeConditionsLimites(&(*controleur).systeme, 0);

		// Réglage du couplage
	changeCouplageMoyenne(&(*controleur).systeme);

		// Réglage de la dissipation
	changeDissipationMoyenne(&(*controleur).systeme);
	changeFormeDissipation(&(*controleur).systeme, 1);

		// Réglage du moteur josephson
	moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs, 1);
	moteursChangeJosephsonMoyenne(&(*controleur).systeme.moteurs);
*/
	return 0;
	}

int controleurDefileCommandes(controleurT * controleur, int zone)
	{
	(void)controleur;
	(void)zone;
/*
	int commande = -1;
	if(zone==1)
		{
		commande = commandeRotatifs(&(*controleur).commandes);
		if((*controleur).interface.evenement.wheel.y > 0) // scroll up
			{
			switch(commande)
				{
				case 0:
					changeCouplage(&(*controleur).systeme, 1.1);break;
				case 1:
					changeDissipation(&(*controleur).systeme, 1.1);break;
				case 2:
					moteursChangeJosephson(&(*controleur).systeme.moteurs, 1.1);break;
				case 3:
					moteursChangeAmplitude(&(*controleur).systeme.moteurs, 1.1);break;
				case 4:
					moteursChangeFrequence(&(*controleur).systeme.moteurs, 1.1);break;
				default:
					;
				}
			}
		else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
			{
			switch(commande)	
				{
				case 0:
					changeCouplage(&(*controleur).systeme, 0.91);break;
				case 1:
					changeDissipation(&(*controleur).systeme, 0.91);break;
				case 2:
					moteursChangeJosephson(&(*controleur).systeme.moteurs, 0.91);break;
				case 3:
					moteursChangeAmplitude(&(*controleur).systeme.moteurs, 0.91);break;
				case 4:
					moteursChangeFrequence(&(*controleur).systeme.moteurs, 0.91);break;
				default:
					;
				}
			}
		}

	if(zone==3)
		{
		commande = commandeLineaires(&(*controleur).commandes);
		if((*controleur).interface.evenement.wheel.y > 0) // scroll up
			{
			switch(commande)
				{
				case 0:
					controleurDefilePointDeVue(controleur);break;
				case 1:
					controleurDefilePointDeVue(controleur);break;
				case 2:
					controleurChangeVitesse(controleur, 1.1);break;
				case 3:
					controleurChangeVitesse(controleur, 1.1);break;
				default:
					;
				}
			}
		else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
			{
			switch(commande)	
				{
				case 0:
					controleurDefilePointDeVue(controleur);break;
				case 1:
					controleurDefilePointDeVue(controleur);break;
				case 2:
					controleurChangeVitesse(controleur, 0.91);break;
				case 3:
					controleurChangeVitesse(controleur, 0.91);break;
				default:
					;
				}
			}
		}
*/
	return 0;
	}

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
void controleurAfficheSouris(controleurT * controleur)
	{
	fprintf(stderr, "(*controleur).graphique.fenetreY = %d\n", (*controleur).graphique.fenetreY);
	fprintf(stderr, "(*controleur).commandes.sourisY = %d\n", (*controleur).commandes.sourisY);
	fprintf(stderr, "(*controleur).graphique.fenetreX = %d\n", (*controleur).graphique.fenetreX);
	fprintf(stderr, "(*controleur).commandes.sourisX = %d\n", (*controleur).commandes.sourisX);

	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////
