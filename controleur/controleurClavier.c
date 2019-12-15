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

		//	AZE QSD : Paramètres foule

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

		//	UIO PM JKL : Paramètres construction

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
/*
		case SDLK_j:
			//donneesSauvegardeBatiment(&(*controleur).construction.batiment, &(*controleur).options);break;
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, &("jj"));break; */
		case SDLK_k:
			batimentInitialise9(&(*controleur).construction.batiment);break;
		case SDLK_l:
			batimentInitialiseVide(&(*controleur).construction.batiment);break;

		//	WXCVBN : Options boucle et initial

		case SDLK_w:
			printf("Option boucle = 0\n");
			(*controleur).options.boucle = 0;break;
		case SDLK_x:
			printf("Option boucle = 1\n");
			(*controleur).options.boucle = 1;break;
		case SDLK_c:
			printf("Option boucle = 2\n");
			(*controleur).options.boucle = 2;break;
		case SDLK_v:
			printf("Option initial = 0\n");
			(*controleur).options.initial = 0;break;
		case SDLK_b:
			printf("Option initial = 1\n");
			(*controleur).options.initial = 1;break;
		case SDLK_n:
			printf("Option initial = 2\n");
			(*controleur).options.initial = 2;break;

		//	RTY FGH : Economie de CPU, controleurChangeModeEco(controleurT * controleur, int mode)

		case SDLK_r:
			controleurChangeModeEco(controleur, 0);break;
		case SDLK_t:
			controleurChangeModeEco(controleur, 1);break;
		case SDLK_y:
			controleurChangeModeEco(controleur, 2);break;
		case SDLK_f:
			controleurChangeModeEco(controleur, 13);break;
		case SDLK_g:
			controleurChangeModeEco(controleur, 49);break;
		case SDLK_h:
			controleurChangeModeEco(controleur, 99);break;

		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierMaj(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// 1 : simulation, -1 : construction
		case SDLK_ESCAPE:
			controleurChangeModeDessin(controleur);break;

    // Mode : évolution du système en pause

		case SDLK_RETURN:
			controleurChangeModePause(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeModePause(controleur);break;


	// Réinitialisation du système
		// Lecture des fichier
		case SDLK_a:
			controleurReinitialisation(controleur, "a");break;
		case SDLK_z:
			controleurReinitialisation(controleur, "z");break;
		case SDLK_e:
			controleurReinitialisation(controleur, "e");break;
		case SDLK_r:
			controleurReinitialisation(controleur, "r");break;
		case SDLK_t:
			controleurReinitialisation(controleur, "t");break;
		case SDLK_y:
			controleurReinitialisation(controleur, "y");break;
		case SDLK_u:
			controleurReinitialisation(controleur, "u");break;
		case SDLK_i:
			controleurReinitialisation(controleur, "i");break;
		case SDLK_o:
			controleurReinitialisation(controleur, "o");break;
		case SDLK_p:
			controleurReinitialisation(controleur, "p");break;
		case SDLK_q:
			controleurReinitialisation(controleur, "q");break;
		case SDLK_s:
			controleurReinitialisation(controleur, "s");break;
		case SDLK_d:
			controleurReinitialisation(controleur, "d");break;
		case SDLK_f:
			controleurReinitialisation(controleur, "f");break;
		case SDLK_g:
			controleurReinitialisation(controleur, "g");break;
		case SDLK_h:
			controleurReinitialisation(controleur, "h");break;
		case SDLK_j:
			controleurReinitialisation(controleur, "j");break;
		case SDLK_k:
			controleurReinitialisation(controleur, "k");break;
		case SDLK_l:
			controleurReinitialisation(controleur, "l");break;
		case SDLK_m:
			controleurReinitialisation(controleur, "m");break;
		case SDLK_w:
			controleurReinitialisation(controleur, "w");break;
		case SDLK_x:
			controleurReinitialisation(controleur, "x");break;
		case SDLK_c:
			controleurReinitialisation(controleur, "c");break;
		case SDLK_v:
			controleurReinitialisation(controleur, "v");break;
		case SDLK_b:
			controleurReinitialisation(controleur, "b");break;
		case SDLK_n:
			controleurReinitialisation(controleur, "n");break;

		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierCtrl(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// 1 : simulation, -1 : construction
		case SDLK_ESCAPE:
			controleurChangeModeDessin(controleur);break;
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
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "aa");break;
	/*	case SDLK_z:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "z");break;
		case SDLK_e:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "e");break;
		case SDLK_r:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "r");break;
		case SDLK_t:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "t");break;
		case SDLK_y:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "y");break;
		case SDLK_u:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "u");break;
		case SDLK_i:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "i");break;
		case SDLK_o:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "o");break;
		case SDLK_p:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "p");break;
*/
	// Réinitialisation du système
/*		case SDLK_a:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "a");break;
		case SDLK_z:
			fprintf(stderr, "Réinitialisation du système\n");
			systemeInitialisePosition(&(*controleur).systeme, "z");break;
		case SDLK_e:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "e");break;
		case SDLK_r:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "r");break;
		case SDLK_t:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "t");break;
		case SDLK_y:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "y");break;
		case SDLK_u:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "u");break;
		case SDLK_i:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "i");break;
		case SDLK_o:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "o");break;
		case SDLK_p:
			fprintf(stderr, "Réinitialisation du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "p");break;
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
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "g");break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "h");break;
		case SDLK_j:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "j");break;
		case SDLK_k:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "k");break;
		case SDLK_l:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "l");break;
		case SDLK_m:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "m");break;
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "w");break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "x");break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "c");break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "v");break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "b");break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierFonction(&(*controleur).systeme, &(*controleur).graphe, "n");break;*/
		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierCtrlMaj(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// 1 : simulation, -1 : construction
		case SDLK_ESCAPE:
			controleurChangeModeDessin(controleur);break;
	// Mode : évolution du système en pause
		case SDLK_RETURN:
			controleurChangeModePause(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeModePause(controleur);break;

	// Sauvegarde du système
		case SDLK_a:
			fprintf(stderr, "Sauvegarde de la construction\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "aa");break;
		case SDLK_z:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "z");break;
		case SDLK_e:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "e");break;
		case SDLK_r:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "r");break;
		case SDLK_t:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "t");break;
		case SDLK_y:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "y");break;
		case SDLK_u:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "u");break;
		case SDLK_i:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "i");break;
		case SDLK_o:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "o");break;
		case SDLK_p:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "p");break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "q");break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "s");break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "d");break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "f");break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "g");break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "h");break;
		case SDLK_j:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "j");break;
		case SDLK_k:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "k");break;
		case SDLK_l:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "l");break;
		case SDLK_m:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "m");break;
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "w");break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "x");break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "c");break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "v");break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "b");break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			donneesSauvegardeConstruction(&(*controleur).construction, &(*controleur).options, "n");break;
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














