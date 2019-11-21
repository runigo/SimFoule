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

#include "controleurSouris.h"

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
				// Action de la rotation de la mollette

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
		/*	case 0: // Uniforme
				changeConditionsLimites(&(*controleur).systeme, 0);break;
			case 1: // Aléatoire
				changeConditionsLimites(&(*controleur).systeme, 1);break;
			case 2: // Uniforme
				changeConditionsLimites(&(*controleur).systeme, 2);break;
			case 3: // Aléatoire
				changeConditionsLimites(&(*controleur).systeme, 4);break;
			case 4: // Pause
				changeFormeDissipation(&(*controleur).systeme, 1);break;
			case 5: // Max
				changeFormeDissipation(&(*controleur).systeme, 0);break;
			case 6: // Implicite
				changeFormeDissipation(&(*controleur).systeme, 2);break;*/
			default:
				;
			}
		}
	if(zone==3)
		{
		commande = commandeTriangles(&(*controleur).commandes);
		switch(commande)	//	
			{
			case 0:
				controleurReinitialisation(controleur, 20);break;
			case 1:
				controleurReinitialisation(controleur, 21);break;
			case 2:
				controleurReinitialisation(controleur, 22);break;
			case 3:
				controleurReinitialisation(controleur, 23);break;
			case 4:
				controleurReinitialisation(controleur, 24);break;
			case 5:
				controleurReinitialisation(controleur, 25);break;
			case 6:
				controleurReinitialisation(controleur, -1);break;
			case 7:
				controleurReinitialisation(controleur, -2);break;
			case 8:
				controleurReinitialisation(controleur, -3);break;
			case 9:
				controleurReinitialisation(controleur, -4);break;
			default:
				;
			}
		}
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
					changeMasseMoyenne(&(*controleur).systeme, 1.1);break;
				case 1:
					changeEcartMasse(&(*controleur).systeme, 1.1);break;
				case 2:
					changeNervositeMoyenne(&(*controleur).systeme, 1.1);break;
				case 3:
					changeEcartNervosite(&(*controleur).systeme, 1.1);break;
				case 4:
					controleurChangeVitesse(&(*controleur).systeme.moteurs, 1.1);break;
				default:
					;
				}
			}
		else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
			{
			switch(commande)	
				{
				case 0:
					changeMasseMoyenne(&(*controleur).systeme, 0.91);break;
				case 1:
					changeEcartMasse(&(*controleur).systeme, 0.91);break;
				case 2:
					changeNervositeMoyenne(&(*controleur).systeme, 0.91);break;
				case 3:
					changeEcartNervosite(&(*controleur).systeme, 0.91);break;
				case 4:
					controleurChangeVitesse(controleur, 0.91);break;
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

void controleurAfficheSouris(controleurT * controleur)
	{
	float ratioX = (*controleur).commandes.sourisX/(float)(*controleur).graphique.fenetreX;
	float ratioY = (*controleur).commandes.sourisY/(float)(*controleur).graphique.fenetreY;
/*
	fprintf(stderr, "(*controleur).graphique.fenetreY = %d\n", (*controleur).graphique.fenetreY);
	fprintf(stderr, "(*controleur).commandes.sourisY = %d\n", (*controleur).commandes.sourisY);
	fprintf(stderr, "(*controleur).graphique.fenetreX = %d\n", (*controleur).graphique.fenetreX);
	fprintf(stderr, "(*controleur).commandes.sourisX = %d\n", (*controleur).commandes.sourisX);
*/

	fprintf(stderr, "	Rapport suivant X = %f\n", ratioX);
	fprintf(stderr, "	Rapport suivant Y = %f\n", ratioY);

	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////














