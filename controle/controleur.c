/*
Copyright janvier 2018, Stephan Runigo
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


#include "controleur.h"

int controleurProjection(controleurT * control);
int controleurEvolutionSysteme(controleurT * control);
int controleurConstructionGraphique(controleurT * control);
int controleurActionClavier(controleurT * control);

int controleurTraiteEvenement(controleurT * control);

int controleurClavier(controleurT * control);
int controleurClavierMaj(controleurT * controleur);
int controleurClavierCtrl(controleurT * controleur);
int controleurSouris(controleurT * control);
void controleurBoutonSouris(controleurT * control, int appui);

void controleurChangeMode(controleurT * control);
void controleurChangeVitesse(controleurT * control, float facteur);

int controleurDirections(controleurT * controleur)
	{
		// Calcul des directions
		fprintf(stderr, "  Calcul des directions\n");
	batimentDirections(&(*controleur).systeme.batiment);
	return 0;
	}

int controleurInitialisation(controleurT * controleur)
	{
		// Initialisation du controleur

	(*controleur).options.sortie = 0;	// Sortie de SiCP si > 0

		//fprintf(stderr, "  Initialisation de la projection\n");
	//projectionInitialiseCouleurs(&(*controleur).projection, 50, 50, 50, (*controleur).options.fond);
	//projectionInitialiseLongueurs(&(*controleur).projection, BATIMENT_X, BATIMENT_Y);

		fprintf(stderr, "  Initialisation du batiment\n");
	donneesInitialisationBatiment(&(*controleur).systeme.batiment, &(*controleur).options);

		fprintf(stderr, "  Initialisation de la foule\n");
	donneesCreationFoule(&(*controleur).systeme.foule, &(*controleur).options);
	donneesInitialisationFoule(&(*controleur).systeme.foule, &(*controleur).systeme.batiment);

		fprintf(stderr, "  Initialisation de l'interface graphique\n");
	donneesCreationGraphe(&(*controleur).graphe, &(*controleur).options);
	donneesInitialisationInterface(&(*controleur).interface, &(*controleur).options);
	donneesInitialisationGraphe(&(*controleur).graphe, &(*controleur).interface);

	return 0;
	}

int controleurSuppression(controleurT * controleurT)
	{
	fprintf(stderr, "  Suppression de l'interface\n");
	interfaceDestruction(&(*controleurT).interface);
	fprintf(stderr, "  Suppression du graphe\n");
	grapheSuppression(&(*controleurT).graphe);
	fprintf(stderr, "  Suppression de la foule\n");
	fouleSuppression(&(*controleurT).systeme.foule);
	return 0;
	}

int controleurSimulationGraphique(controleurT * controleur)
	{

	//batimentCalculDistanceEtSens(&(*controleur).batiment);
			//fprintf(stderr, "Entrée dans la boucle SDL\n");
	do	{
			//fprintf(stderr, "Projection du systeme sur la représentation graphique\n");
		controleurProjection(controleur);

			//fprintf(stderr, "Évolution du systeme\n");
		// controleurEvolutionSysteme(controleur);

			//fprintf(stderr, "Mise à jour de la fenêtre graphique et pause\n");
		controleurConstructionGraphique(controleur);

			//fprintf(stderr, "Prise en compte des actions clavier\n");
		controleurActionClavier(controleur);

		}
	while((*controleur).interface.evenement.type != SDL_QUIT);
			//fprintf(stderr, "Sortiee de la boucle SDL\n");
	return 0;
	}

int controleurProjection(controleurT * controleur)
	{
		//	Projection des fonctions sur les graphes

	projectionBatimentPlan(&(*controleur).systeme.batiment, &(*controleur).projection, &(*controleur).graphe);

	//projectionBatimentSens(&(*controleur).systeme.batiment, &(*controleur).projection, &(*controleur).graphe);

	projectionFoulePoints(&(*controleur).systeme.foule, &(*controleur).projection, &(*controleur).graphe);

	return (*controleur).options.sortie;
	}

int controleurEvolutionSysteme(controleurT * controleur)
	{
		//fprintf(stderr, "Evolution temporelle de la foule\n");
	systemeEvolution(&(*controleur).systeme, (*controleur).options.duree);

	return 0;
	}

int controleurConstructionGraphique(controleurT * controleur)
	{
		//fprintf(stderr, "Nettoyage de l'affichage\n");
	interfaceNettoyage(&(*controleur).interface);

	//	Dessin des graphes;
	//grapheDessineAngle((*controleur).interface.rendu, &(*controleur).graphe);
	grapheDessineMur((*controleur).interface.rendu, &(*controleur).graphe);
	grapheDessineHumain((*controleur).interface.rendu, &(*controleur).graphe);

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	interfaceMiseAJour(&(*controleur).interface);

		// Pause
	SDL_Delay((*controleur).options.pause);

	return (*controleur).options.sortie;
	}

int controleurActionClavier(controleurT * controleur)
	{
	int sortie = 0;
		//fprintf(stderr, "Traitement des évenements, mode %d\n", (*controleur).mode);
	if((*controleur).options.mode<0)
		{
				// Attente d'un évenement SDL
		if(SDL_WaitEvent(&(*controleur).interface.evenement))
			{
			sortie += controleurTraiteEvenement(controleur);
			}
		}
	else
		{
			// Sans attente
		if( SDL_PollEvent(&(*controleur).interface.evenement) )
			{
			sortie += controleurTraiteEvenement(controleur);
			}
		}

	if((*controleur).interface.evenement.type == SDL_QUIT) sortie += 1;

	(*controleur).options.sortie += sortie;

	return (*controleur).options.sortie;
	}

int controleurTraiteEvenement(controleurT * controleur)
	{
	int sortie = 0;

	switch((*controleur).interface.evenement.type)
		{
		case SDL_QUIT:
			sortie = 1;break;
		case SDL_MOUSEMOTION:
			sortie = controleurSouris(controleur);break;
		case SDL_MOUSEBUTTONDOWN:
			controleurBoutonSouris(controleur, 1);break;
		case SDL_MOUSEBUTTONUP:
			controleurBoutonSouris(controleur, 0);break;
		case SDL_KEYDOWN:
			if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
			|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT))
				{
				sortie = controleurClavierMaj(controleur);break;
				}
			else
				{
				if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LCTRL)
				|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RCTRL))
					{
					sortie = controleurClavierCtrl(controleur);break;
					}
				else
					{
					sortie = controleurClavier(controleur);break;
					}
				}
			/*if (((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
				{sortie = controleurClavierMaj(controleur);break;}
			else
				{
				if (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT)
					{sortie = controleurClavierMaj(controleur);break;}
				else {sortie = controleurClavier(controleur);break;}
				}*/
		//case SDL_KEYDOWN:
			//sortie = controleurClavier(controleur);break;
		}

	if(sortie != 0)
		{
		fprintf(stderr, "sortie <> 0\n");
		(*controleur).options.sortie = 1;
		}
	return sortie;
	}

void controleurChangeMode(controleurT * controleur)
	{
	(*controleur).options.mode=-(*controleur).options.mode;

	return;
	}

void controleurChangeVitesse(controleurT * controleur, float facteur)
	{
	if( (*controleur).options.duree > 999 && facteur > 1 )
		{
		fprintf(stderr, "duree maximale atteinte");
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
					fprintf(stderr, "duree minimale atteinte");
					}
				}
			}
		}
	fprintf(stderr, "duree = %d\n", (*controleur).options.duree);
	return;
	}

int controleurClavier(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Sortie
		case SDLK_ESCAPE:
			(*controleur).options.sortie = 1;break;

	// Mode : attente d'un evenement / pas d'attente
		case SDLK_RETURN:
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

	// Conditions aux limites
/*
		case SDLK_y:
			changeDephasage(&(*controleur).foule, 2*PI);break;
		case SDLK_h:
			changeDephasage(&(*controleur).foule, -2*PI);break;
		case SDLK_w:
			changeConditionsLimites(&(*controleur).foule, 0); // periodiques
			break;
		case SDLK_x:
			changeConditionsLimites(&(*controleur).foule, 1); // libres
			break;
		case SDLK_c:
			changeConditionsLimites(&(*controleur).foule, 2); // fixes
			break;
		case SDLK_b:
			changeConditionsLimites(&(*controleur).foule, 3); // libre fixe
			break;
		case SDLK_n:
			changeConditionsLimites(&(*controleur).foule, 4); // fixe libre
			break;

	// Dissipation
		case SDLK_d:
			changeDissipation(&(*controleur).foule, 1.3);break;
		case SDLK_e:
			changeDissipation(&(*controleur).foule, 0.7);break;
		case SDLK_r:
			changeFormeDissipation(&(*controleur).foule, 0);break;
		case SDLK_f:
			changeFormeDissipation(&(*controleur).foule, 1);break;
		case SDLK_v:
			changeFormeDissipation(&(*controleur).foule, 2);break;

	// Couplage
		case SDLK_a:
			changeCouplage(&(*controleur).foule, 1.1);break;
		case SDLK_q:
			changeCouplage(&(*controleur).foule, 0.9);break;

	// Masse
		case SDLK_z:
			changeMasse(&(*controleur).foule, 1.1);break;
		case SDLK_s:
			changeMasse(&(*controleur).foule, 0.91);break;

	// Gravitation
		case SDLK_t:
			changeGravitation(&(*controleur).foule, 1.1);break;
		case SDLK_g:
			changeGravitation(&(*controleur).foule, 0.91);break;

	// Moteur jonction Josephson
		case SDLK_UP:
			moteursChangeJosephson(&(*controleur).foule.moteur,1.1);break;
		case SDLK_DOWN:
			moteursChangeJosephson(&(*controleur).foule.moteur,0.91);break;
		case SDLK_LEFT:
			moteursChangeJosephson(&(*controleur).foule.moteur,-1.0);break;
		case SDLK_RIGHT:
			moteursChangeJosephson(&(*controleur).foule.moteur,0.0);break;

	// Moteur générateur de signaux

		case SDLK_p:
			moteursChangeFrequence(&(*controleur).foule.moteur,1.1);break;
		case SDLK_m:
			moteursChangeFrequence(&(*controleur).foule.moteur,0.91);break;
		case SDLK_u:
			moteursChangeAmplitude(&(*controleur).foule.moteur,1.1);break;
		case SDLK_j:
			moteursChangeAmplitude(&(*controleur).foule.moteur,0.91);break;
		case SDLK_o:
			moteursChangeGenerateur(&(*controleur).foule.moteur, -1);break;
		case SDLK_i:
			moteursChangeGenerateur(&(*controleur).foule.moteur, 3);break;
		case SDLK_l:
			moteursChangeGenerateur(&(*controleur).foule.moteur, 2);break;


	// Choix de l'equation

		case SDLK_F1: // Pendules
			changeEquation(&(*controleur).foule, 1);break;
		case SDLK_F2: // Harmoniques
			changeEquation(&(*controleur).foule, 2);break;
		case SDLK_F3: // Corde
			changeEquation(&(*controleur).foule, 3);break;
		case SDLK_F4: // Corde asymétrique
			changeEquation(&(*controleur).foule, 4);break;


	// Choix de l'equation

		case SDLK_F5: // Pendules
			observablesAfficheEnergie(&(*controleur).foule);break;

		case SDLK_F6: // Pendules
			systemeAffiche(&(*controleur).foule);break;

*/
		default:
			;
		}
	return (*controleur).options.sortie;
	}

int controleurClavierMaj(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{

	// Sortie

		case SDLK_ESCAPE:
			(*controleur).options.sortie = 1;break;

    // Mode : attente d'un evenement / pas d'attente

		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;


	// Réinitialisation du système
		// Lecture des fichier
/*		case SDLK_a:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 0);break;
		case SDLK_z:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 1);break;
		case SDLK_e:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 2);break;
		case SDLK_r:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 3);break;
		case SDLK_t:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 4);break;
		case SDLK_y:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 5);break;
		case SDLK_u:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 6);break;
		case SDLK_i:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 7);break;
		case SDLK_o:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 8);break;
		case SDLK_p:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 9);break;
		case SDLK_q:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 10);break;
		case SDLK_s:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 11);break;
		case SDLK_d:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 12);break;
		case SDLK_f:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 13);break;
		case SDLK_g:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 14);break;
		case SDLK_h:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 15);break;
		case SDLK_j:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 16);break;
		case SDLK_k:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 17);break;
		case SDLK_l:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 18);break;
		case SDLK_m:
			fprintf(stderr, "Réinitialisation du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, 19);break;


		// Ecriture des fichiers
		// Ecriture des fichiers
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 10);break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 11);break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 12);break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 13);break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 14);break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 15);break;
*/		/*case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, );break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, );break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeInitialise(&(*controleur).batiment, );break;*/

		default:
			;
		}
	return (*controleur).options.sortie;
	}

int controleurClavierCtrl(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Sortie
		case SDLK_ESCAPE:
			(*controleur).options.sortie = 1;break;
	// Mode : attente d'un evenement / pas d'attente
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;

	// Enregistrement
		// Sauvegarde du système
/*		case SDLK_a:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 0);break;
		case SDLK_z:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 1);break;
		case SDLK_e:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 2);break;
		case SDLK_r:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 3);break;
		case SDLK_t:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 4);break;
		case SDLK_y:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 5);break;
		case SDLK_u:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 6);break;
		case SDLK_i:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 7);break;
		case SDLK_o:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 8);break;
		case SDLK_p:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 9);break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 10);break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 11);break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 12);break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 13);break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 14);break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 15);break;


		// Ecriture des fichiers
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 10);break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 11);break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 12);break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 13);break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 14);break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, 15);break;
*/		/*case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, );break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, );break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, );break;
		case SDLK_:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSystemeSauvegarde(&(*controleur).batiment, );break;*/

		default:
			;
		}
	return (*controleur).options.sortie;
	}

int controleurSouris(controleurT * controleur)
	{
	float x, y;
	if((*controleur).appui==1)
		{
		x=-0.01*(float)((*controleur).interface.evenement.motion.xrel);
		y=0.1*FENETRE_Y*(float)((*controleur).interface.evenement.motion.yrel);
		//fprintf(stderr, "controleurSouris yrel = %d , x = %f\n", (*controleur).interface.evenement.motion.yrel, x);
		//fprintf(stderr, "controleurSouris xrel = %d , y = %f\n", (*controleur).interface.evenement.motion.xrel, y);
		(void)x;(void)y;
		}
	return (*controleur).options.sortie;
	}

void controleurBoutonSouris(controleurT * controleur, int appui)
	{
	(*controleur).appui=appui;
	return;
	}
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
