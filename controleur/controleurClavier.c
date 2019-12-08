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

#include "controleurClavier.h"
#include "controleurSouris.h"

int controleurClavier(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// 1 : simulation, -1 : construction
		case SDLK_ESCAPE:
			controleurChangeModeDessin(controleur);break;

	// Mode : évolution du système ou pause
		case SDLK_RETURN:
			controleurChangeModePause(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeModePause(controleur);break;

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
		case SDLK_F2:
			mobileAffiche(&(*controleur).systeme.foule.premier->mobile);break;
		case SDLK_F3:
			controleurAffiche(controleur);break;
		case SDLK_F4:
			etageAffiche(&(*controleur).systeme.batiment.etage[0]);break;

		case SDLK_F5:
			controleurAfficheForces(controleur);break;
		case SDLK_F6:
			controleurChangeDessin(&(*controleur).options.dessineAngle);break;
		case SDLK_F7:
			controleurChangeDessin(&(*controleur).options.dessineMur);break;
		case SDLK_F8:
			controleurChangeDessin(&(*controleur).options.dessineMobile);break;


		case SDLK_a:
			fouleChangeMasse(&(*controleur).systeme.foule, 1.1);break;
		case SDLK_q:
			fouleChangeMasse(&(*controleur).systeme.foule, 0.91);break;
		case SDLK_z:
			fouleChangeNervosite(&(*controleur).systeme.foule, 1.1);break;
		case SDLK_s:
			fouleChangeNervosite(&(*controleur).systeme.foule, 0.91);break;
		case SDLK_e:
			fouleChangeCelerite(&(*controleur).systeme.foule, 1.1);break;
		case SDLK_d:
			fouleChangeCelerite(&(*controleur).systeme.foule, 0.91);break;

		case SDLK_u:
			constructionChangeMotif(&(*controleur).construction, 3);break;
		case SDLK_i:
			constructionChangeMotif(&(*controleur).construction, 2);break;
		case SDLK_o:
			constructionChangeMotif(&(*controleur).construction, 0);break;
		case SDLK_p:
			constructionChangeMotif(&(*controleur).construction, 9);break;
		case SDLK_m:
			constructionChangeMotif(&(*controleur).construction, 1);break;

		case SDLK_j:
			//donneesSauvegardeBatiment(&(*controleur).construction.batiment, &(*controleur).options);break;
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options);break;
		case SDLK_k:
			constructionChangeMotif(&(*controleur).construction, 9);break;
		case SDLK_l:
			batimentInitialiseVide(&(*controleur).construction.batiment);break;

		case SDLK_w:
			(*controleur).options.boucle = 0;break;
		case SDLK_x:
			(*controleur).options.boucle = 1;break;
		case SDLK_c:
			(*controleur).options.boucle = 2;break;
		case SDLK_n:
			fprintf(stderr,"controleurClavier");break;

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
			controleurChangeModePause(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeModePause(controleur);break;


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
		//case SDLK_n:
		//	controleurReinitialisation(controleur, 25);break;
		case SDLK_n:
			fprintf(stderr,"controleurClavierMaj");break;

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
			controleurChangeModePause(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeModePause(controleur);break;
		case SDLK_n:
			fprintf(stderr,"controleurClavierCtrl");break;

	// Sauvegarde du système
		case SDLK_a:
			fprintf(stderr, "Sauvegarde de la construction\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options);break;
	/*	case SDLK_z:
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
			controleurChangeModePause(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeModePause(controleur);break;
		case SDLK_n:
			fprintf(stderr,"controleurClavierCtrlMaj");break;
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

void controleurAfficheClavier(controleurT * controleur)
	{
	(void)controleur;
/*
	fprintf(stderr, "(*controleur).graphique.fenetreY = %d\n", (*controleur).graphique.fenetreY);
	fprintf(stderr, "(*controleur).commandes.sourisY = %d\n", (*controleur).commandes.sourisY);
	fprintf(stderr, "(*controleur).graphique.fenetreX = %d\n", (*controleur).graphique.fenetreX);
	fprintf(stderr, "(*controleur).commandes.sourisX = %d\n", (*controleur).commandes.sourisX);

	fprintf(stderr, "	Rapport suivant X = %f\n", ratioX);
	fprintf(stderr, "	Rapport suivant Y = %f\n", ratioY);
*/

	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////














