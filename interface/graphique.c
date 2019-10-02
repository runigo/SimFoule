/*
Copyright octobre 2019, Stephan Runigo
runigo@free.fr
SimFoule 2.0  simulateur de foule
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

#include "graphique.h"

int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur);
void graphiqueLigne(graphiqueT * graphique, int X, int Y, int x, int y);
void graphiqueTige(graphiqueT * graphique, int X, int Y, int x, int y, float sinT, float cosT);
//void graphiqueMasse(graphiqueT * graphique, int abs, int ord);

void graphiqueTriangleGris(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By);
void graphiqueTriangle(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By);
void graphiqueRectangle(graphiqueT * graphique, int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy);

void graphiqueMobile(graphiqueT * graphique, grapheT * graphe);

int graphiqueDestruction(graphiqueT * graphique)
	{
	SDL_DestroyRenderer((*graphique).rendu);
	return 0;
	}


int graphiqueInitialisation(graphiqueT * graphique, interfaceT * interface, int taille)
	{
	int retour = 0;
	int fenetreX;
	int fenetreY;

	(*graphique).taille = taille;

	SDL_GetWindowSize((*interface).fenetre, &fenetreX, &fenetreY);

	(*graphique).fenetreX=fenetreX;
	(*graphique).fenetreY=fenetreY;

		// Création du rendu
	(*graphique).rendu = SDL_CreateRenderer((*interface).fenetre, -1 , 
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(NULL == (*graphique).rendu)
		{
		(*graphique).rendu = SDL_CreateRenderer((*interface).fenetre, -1 , 
						SDL_RENDERER_SOFTWARE);
		if(NULL == (*graphique).rendu)
			{
			fprintf(stderr, "ERREUR interfaceInitialisation : Erreur SDL_CreateRenderer : %s \n", SDL_GetError());
			return EXIT_FAILURE;
			}
		}

	int fond = 245;
	//SDL_Color orange = {255, 127, 40, 255};
	(*graphique).fond.r = fond;
	(*graphique).fond.g = fond;
	(*graphique).fond.b = fond;
	(*graphique).fond.a = 255;
	(*graphique).contraste.r = 255-fond;
	(*graphique).contraste.g = 255-fond;
	(*graphique).contraste.b = 255-fond;
	(*graphique).contraste.a = 255;
	(*graphique).orange.r = 255;
	(*graphique).orange.g = 127;
	(*graphique).orange.b = 40;
	(*graphique).orange.a = 255;
	(*graphique).jaune.r = 255;
	(*graphique).jaune.g = 255;
	(*graphique).jaune.b = 0;
	(*graphique).jaune.a = 255;
	(*graphique).gris.r = 127;
	(*graphique).gris.g = 127;
	(*graphique).gris.b = 127;
	(*graphique).gris.a = 255;
	(*graphique).cyan.r = 127;
	(*graphique).cyan.g = 40;
	(*graphique).cyan.b = 255;
	(*graphique).cyan.a = 255;
	(*graphique).vert.r = 173;
	(*graphique).vert.g = 255;
	(*graphique).vert.b = 47;
	(*graphique).vert.a = 255;

	//SDL_Texture *masse;

	SDL_Surface *panneau = 0;

	panneau = SDL_LoadBMP("./image/SimFoule.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, ./image/SimFoule.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).simfoule = SDL_CreateTextureFromSurface((*graphique).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*graphique).simfoule == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	SDL_Surface *lumiereVerte = 0;

	lumiereVerte = SDL_LoadBMP("./image/lumiereVerte.bmp");
	if (!lumiereVerte)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereVerte.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).lumiereVerte = SDL_CreateTextureFromSurface((*graphique).rendu, lumiereVerte);
	SDL_FreeSurface(lumiereVerte);
	if ((*graphique).lumiereVerte == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	SDL_Surface *lumiereRouge = 0;

	lumiereRouge = SDL_LoadBMP("./image/lumiereRouge.bmp");
	if (!lumiereRouge)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereRouge.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).lumiereRouge = SDL_CreateTextureFromSurface((*graphique).rendu, lumiereRouge);
	SDL_FreeSurface(lumiereRouge);
	if ((*graphique).lumiereRouge == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	SDL_Surface *lumiereJaune = 0;

	lumiereJaune = SDL_LoadBMP("./image/lumiereJaune.bmp");
	if (!lumiereJaune)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereJaune.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).lumiereJaune = SDL_CreateTextureFromSurface((*graphique).rendu, lumiereJaune);
	SDL_FreeSurface(lumiereJaune);
	if ((*graphique).lumiereJaune == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	SDL_Surface *lumiereOrange = 0;

	lumiereOrange = SDL_LoadBMP("./image/lumiereOrange.bmp");
	if (!lumiereOrange)
		{
		fprintf(stderr,"ERREUR chargement image, lumiereOrange.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).lumiereOrange = SDL_CreateTextureFromSurface((*graphique).rendu, lumiereOrange);
	SDL_FreeSurface(lumiereOrange);
	if ((*graphique).lumiereOrange == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

		fprintf(stderr,"graphiqueInitialisation \n");


	SDL_Surface *image = 0;

	image = SDL_LoadBMP("./image/mur.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, mur.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).mur = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).mur == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/mobile.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, mobile.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).mobile = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).mobile == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}
		// Activation de la transparence
	//SDL_BLENDMODE_NONE || SDL_BLENDMODE_BLEND || SDL_BLENDMODE_ADD || SDL_BLENDMODE_MOD
	if(SDL_SetTextureBlendMode((*graphique).mobile, SDL_BLENDMODE_MOD) < 0)
		fprintf(stderr, "grapheInitialisation : Erreur SDL_SetRenderDrawBlendMode : %s.", SDL_GetError());

	image = SDL_LoadBMP("./image/sortie.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, sortie.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).sortie = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/entree.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, entree.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).entree = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

		// DIRECTIONS

	image = SDL_LoadBMP("./image/direction0.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction0.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).direction0 = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction1.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction1.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).direction1 = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction2.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction2.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).direction2 = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction3.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction3.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).direction3 = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction4.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction4.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).direction4 = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction5.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction5.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).direction5 = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction6.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction6.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).direction6 = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}

	image = SDL_LoadBMP("./image/direction7.bmp");
	if (!image)
		{
		fprintf(stderr,"Erreur chargement image, direction7.bmp : %s\n",SDL_GetError());
		retour++;
		}
	(*graphique).direction7 = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).sortie == 0)
		{
		fprintf(stderr,"grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour++;
		}
	return retour;
}

int graphiqueNettoyage(graphiqueT * graphique)
	{
	SDL_RenderClear((*graphique).rendu);
	return 0;
	}

int graphiqueFond(graphiqueT * graphique)
	{
		// Dessine le fond 
	SDL_Rect coordonnee = {0, 0, (*graphique).fenetreX, (*graphique).fenetreY};
	SDL_RenderCopy((*graphique).rendu, (*graphique).simfoule, NULL, &coordonnee);
	
	return 0;
	}

int graphiqueCommandes(graphiqueT * graphique, commandesT * commandes)
	{
		// Dessine les commandes sélectionées
	
	SDL_Rect coordonnee = {0, 0, (*graphique).fenetreX, (*graphique).fenetreY};
	int centrage = 5;
	coordonnee.w=10;
	coordonnee.h=10;
	coordonnee.x = (*commandes).boutonsCentre - centrage;	// Positon X de la zone des petits boutons
	int i;
	int X, Y, x, y;
			
	for(i=0;i<BOUTON_COMMANDES;i++)
		{
		if((*commandes).boutonEtat[i]==1)
			{
			coordonnee.y = (*commandes).boutonCentre[i] - centrage; // Positon Y des petits boutons
			//	Dessin des petits boutons
			SDL_RenderCopy((*graphique).rendu, (*graphique).mobile, NULL, &coordonnee);
			}
		}

	graphiqueChangeCouleur(graphique, (*graphique).orange);
	X=(*commandes).rotatifsCentre;
	for(i=0;i<ROTATIF_COMMANDES;i++)
		{
		Y=(*commandes).rotatifCentre[i];
		x=X+(*commandes).rotatifPositionX[i];
		y=Y+(*commandes).rotatifPositionY[i];
		SDL_RenderDrawLine((*graphique).rendu, X-1, Y, x-1, y);
		SDL_RenderDrawLine((*graphique).rendu, X, Y-1, x, y-1);
		SDL_RenderDrawLine((*graphique).rendu, X+1, Y, x+1, y);
		SDL_RenderDrawLine((*graphique).rendu, X, Y+1, x, y+1);
		}

	centrage = 6;
	coordonnee.w=12;
	coordonnee.h=12;
	coordonnee.y = (*commandes).trianglesLumiere - centrage;	// Positon Y de la zone du bas
	for(i=0;i<TRIANGLE_COMMANDES;i++)
		{
		if((*commandes).triangleEtat[i]==1)
			{
			coordonnee.x = (*commandes).triangleCentre[i] - centrage; // Positon X des boutons triangulaire
			SDL_RenderCopy((*graphique).rendu, (*graphique).lumiereVerte, NULL, &coordonnee);
			}
		else
			{
				if((*commandes).triangleEtat[i]==2)
				{
				coordonnee.x = (*commandes).triangleCentre[i] - centrage; // Positon X des boutons triangulaire
				SDL_RenderCopy((*graphique).rendu, (*graphique).lumiereRouge, NULL, &coordonnee);
				}
				else
					{
					coordonnee.x=(*commandes).lineairePositionX;	//	Droite duree < DUREE
					if((*commandes).triangleEtat[5]==-1 || (*commandes).triangleEtat[10]==-1)
						{
						SDL_RenderCopy((*graphique).rendu, (*graphique).lumiereOrange, NULL, &coordonnee);
						}
					if((*commandes).triangleEtat[6]==-1 || (*commandes).triangleEtat[9]==-1)
						{
						SDL_RenderCopy((*graphique).rendu, (*graphique).lumiereJaune, NULL, &coordonnee);
						}
					}
			}
		}

	return 0;
	}

int graphiqueMiseAJour(graphiqueT * graphique)
	{
	SDL_RenderPresent((*graphique).rendu);
	return 0;
	}

int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur)
	{
	if(SDL_SetRenderDrawColor((*graphique).rendu, couleur.r, couleur.g, couleur.b, couleur.a) < 0)
	return -1;
	//if(SDL_RenderClear(renderer) < 0)
		//return -1;
	return 0;  
	}



		// DESSIN DU GRAPHE

void graphiqueDessineMur(graphiqueT * graphique, grapheT * graphe)
	{
	int i, j;
	SDL_Rect coordonnee = {0, 0, CELLULE, CELLULE};
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			switch((*graphe).plan[i][j][0])
				{
				case 1:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).mur, NULL, &coordonnee);
				break;
				case 2:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).sortie, NULL, &coordonnee);
				break;
				/*case 3:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).entree, NULL, &coordonnee);
				break;*/
				default:
					;
				}
			}
		}
	return;
	}

void graphiqueDessineAngle(graphiqueT * graphique, grapheT * graphe)
	{
	int i, j;
	SDL_Rect coordonnee = {0, 0, CELLULE, CELLULE};
	for(i=0;i<BATIMENT_X;i++)
		{
		for(j=0;j<BATIMENT_Y;j++)
			{
			switch((*graphe).angle[i][j][0])
				{
				case 0:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).direction0, NULL, &coordonnee);
				break;
				case 1:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).direction1, NULL, &coordonnee);
				break;
				case 2:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).direction2, NULL, &coordonnee);
				break;
				case 3:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).direction3, NULL, &coordonnee);
				break;
				case 4:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).direction4, NULL, &coordonnee);
				break;
				case 5:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).direction5, NULL, &coordonnee);
				break;
				case 6:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).direction6, NULL, &coordonnee);
				break;
				case 7:
					coordonnee.x = i*CELLULE;
					coordonnee.y = j*CELLULE;
					SDL_RenderCopy((*graphique).rendu, (*graphique).direction7, NULL, &coordonnee);
				break;
				default:
					;
				}
			}
		}
	return;
	}

void graphiqueDessineMobile(graphiqueT * graphique, grapheT * graphe, int taille)
	{
	SDL_Rect coordonnee = {0, 0, taille, taille};

	pointsT *iterGraph=(*graphe).premier;

	int centrage = (taille)/2;

	do
		{
		coordonnee.x = iterGraph->xm-centrage;
		coordonnee.y = iterGraph->ym-centrage;
		// int plan[BATIMENT_X][BATIMENT_Y][BATIMENT_Z]; // Plan du batiment		À UTILISER ICI ?
				// 0 : libre, 1 : mur, 2 : sortie		if(iterGraph->zm=(*graphe).plan[][][])

		if(iterGraph->zm!=-1) // dessine les mobiles de l'étage
			SDL_RenderCopy((*graphique).rendu, (*graphique).mobile, NULL, &coordonnee);

		iterGraph = iterGraph->suivant;
		}
	while(iterGraph!=(*graphe).premier);

	return;
	}


		//	FONCTIONS DE DESSINS GÉOMÉTRIQUES

void graphiqueTige(graphiqueT * graphique, int X, int Y, int x, int y, float sinT, float cosT)
	{
	int decalageDroit = 0;
	int decalageDiag = 1;
	float sinCarre=sinT*sinT;
	int sinusC = (int)(125*sinCarre);
	(void)cosT;

		// Horizontales 		    R	  V	  B
	SDL_SetRenderDrawColor((*graphique).rendu, sinusC, 55+sinusC, 125+sinusC, 255-sinusC);
	//graphiqueChangeCouleur(graphique, (*graphique).cyan);
	SDL_RenderDrawLine((*graphique).rendu, X-decalageDroit, Y-decalageDiag, x-decalageDroit, y-decalageDiag);
	SDL_RenderDrawLine((*graphique).rendu, X+decalageDroit, Y+decalageDiag, x+decalageDroit, y+decalageDiag);

		// Verticale
	SDL_SetRenderDrawColor((*graphique).rendu, 250-sinusC, 250-sinusC, 25, 255);
	//graphiqueChangeCouleur(graphique, (*graphique).jaune);
	SDL_RenderDrawLine((*graphique).rendu, X+decalageDiag, Y+decalageDroit, x+decalageDiag, y+decalageDroit);
	SDL_RenderDrawLine((*graphique).rendu, X-decalageDiag, Y-decalageDroit, x-decalageDiag, y-decalageDroit);

	return;
	}

void graphiqueTriangleGris(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By)
	{
	int x[3];
	int y[3];
	float a = 0.0;
	float b = 0.0;
	float c = 0.0;
	float d = 0.0;

	//Uint32 couleurG = SDL_MapRGB(affichage->format, 127, 127, 127);

	if(Y>Ay && Y>By){x[2]=X;y[2]=Y;
		if(Ay>By)
			{x[0]=Bx; y[0]=By; x[1]=Ax; y[1]=Ay;}
		else
			{x[0]=Ax; y[0]=Ay; x[1]=Bx; y[1]=By;}
		}
	else
		{
		if(Y<Ay && Y<By){x[0]=X;y[0]=Y;
			if(By>Ay)
				{x[1]=Ax; y[1]=Ay; x[2]=Bx; y[2]=By;}
			else
				{x[1]=Bx; y[1]=By; x[2]=Ax; y[2]=Ay;}
			}
		else{x[1]=X;y[1]=Y;
			if(By>Ay)
				{x[0]=Ax; y[0]=Ay; x[2]=Bx; y[2]=By;}
			else
				{x[0]=Bx; y[0]=By; x[2]=Ax; y[2]=Ay;}
			}
		}

	int i;

	if(y[0]!=y[1])
		{a=(float)(x[1]-x[0])/(y[1]-y[0]);}
	b=x[0]-a*y[0];

	if(y[0]!=y[2])
		{c=(float)(x[2]-x[0])/(y[2]-y[0]);}
	d=x[0]-c*y[0];

	graphiqueChangeCouleur(graphique, (*graphique).gris);

	for(i=y[0];i<=y[1];i++)
		{
		SDL_RenderDrawLine((*graphique).rendu, a*i+b, i, c*i+d, i);
		}

	if(y[1]!=y[2])
		{a=(float)(x[2]-x[1])/(y[2]-y[1]);}
	b=x[1]-a*y[1];

	for(i=y[1];i<=y[2];i++)
		{
		SDL_RenderDrawLine((*graphique).rendu, a*i+b, i, c*i+d, i);
		}

	return;
	}

void graphiqueTrianglePlein(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By)
	{
	graphiqueTriangleGris(graphique, X, Y, Ax, Ay, Bx, By);

	graphiqueChangeCouleur(graphique, (*graphique).contraste);

	SDL_RenderDrawLine((*graphique).rendu, X, Y, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, X, Y, Bx, By);
	SDL_RenderDrawLine((*graphique).rendu, Ax, Ay, Bx, By);

	return;
	}

void graphiqueRectanglePlein(graphiqueT * graphique, int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy)
	{

	graphiqueTriangleGris(graphique, Ax, Ay, Bx, By, Cx, Cy);
	graphiqueTriangleGris(graphique, Ax, Ay, Cx, Cy, Dx, Dy);

	graphiqueChangeCouleur(graphique, (*graphique).contraste);

	SDL_RenderDrawLine((*graphique).rendu, Bx, By, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, Dx, Dy, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, Cx, Cy, Bx, By);
	SDL_RenderDrawLine((*graphique).rendu, Cx, Cy, Dx, Dy);

	return;
	}

void graphiqueTriangle(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By)
	{

	SDL_RenderDrawLine((*graphique).rendu, X, Y, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, X, Y, Bx, By);
	SDL_RenderDrawLine((*graphique).rendu, Ax, Ay, Bx, By);

	return;
	}

void graphiqueRectangle(graphiqueT * graphique, int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy)
	{

	SDL_RenderDrawLine((*graphique).rendu, Bx, By, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, Dx, Dy, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, Cx, Cy, Bx, By);
	SDL_RenderDrawLine((*graphique).rendu, Cx, Cy, Dx, Dy);

	return;
	}

//////////////////////////////////////////////////////////////////////////////

