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

#include "commandes.h"

int commandesInitialiseBoutons(commandesT * commandes, int largeur, int hauteur)
	{

	//	PANNEAU DROIT

		 // Zone des boutons rotatifs
	(*commandes).rotatifs=(int)(0.830797*largeur);
		// BOUTONS ROTATIFS SUIVANT X
	(*commandes).rotatifX=(int)(0.017*largeur);	//		Rayon suivant X 0.896150
	(*commandes).rotatifsCentre=(int)(0.879141*largeur); // Position
		// BOUTONS ROTATIFS SUIVANT Y
	(*commandes).rotatifY=(int)(0.025*hauteur);	//		Rayon suivant Y 0.094067
	(*commandes).rotatifCentre[0]=(int)(0.118669*hauteur); // Masse
	(*commandes).rotatifCentre[1]=(int)(0.259045*hauteur); // Ecart
	(*commandes).rotatifCentre[2]=(int)(0.441389*hauteur); // Nervosité
	(*commandes).rotatifCentre[3]=(int)(0.575977*hauteur); // Ecart
	(*commandes).rotatifCentre[4]=(int)(0.759768*hauteur); // Simulation
	(*commandes).rotatifCentre[5]=(int)(0.875976*hauteur); // 

		 // Zone des petits boutons
	(*commandes).boutons=(int)(0.931065*largeur);
		// PETITS BOUTONS SUIVANT X
	(*commandes).boutonX=(int)(0.007*largeur);			//		Rayon suivant X
	(*commandes).boutonsCentre=(int)(0.950761*largeur);	//	Positon X
		// PETITS BOUTONS SUIVANT Y
	(*commandes).boutonY=(int)(0.010*largeur); //		Rayon suivant Y
	(*commandes).boutonCentre[0]=(int)(0.230101*hauteur); // Uniforme
	(*commandes).boutonCentre[1]=(int)(0.287988*hauteur); //		Aléatoire
	(*commandes).boutonCentre[2]=(int)(0.542692*hauteur); // 		Uniforme
	(*commandes).boutonCentre[3]=(int)(0.599132*hauteur); //	Aléatoire
	(*commandes).boutonCentre[4]=(int)(0.745297*hauteur); //Pause
	(*commandes).boutonCentre[5]=(int)(0.803184*hauteur); // Max
	(*commandes).boutonCentre[6]=(int)(0.862518*hauteur); // Implicite


	//	PANNEAU BAS

		 // Zone du panneau
	(*commandes).bas=(int)(0.816208*hauteur); //	Suivant Y

		// BOUTONS LINEAIRES SUIVANT Y
	(*commandes).lineaireY=(int)(0.0392156862745*hauteur); // 693-636/2 =  / 714 // Rayon suivant Y
	(*commandes).lineairesCentre=(int)(0.958181818182*hauteur); // 693+636/2 =  / 714 // Position Y des boutons linéaires
		// BOUTONS LINEAIRES SUIVANT X
	(*commandes).lineaireX=(int)(0.0306563039724*largeur); // 332-261/2 / 1158	Rayon suivant X
	(*commandes).lineaireCentre[0]=(int)(0.20067264574*largeur); // 261	Hauteur
	(*commandes).lineaireCentre[1]=(int)(0.20067264574*largeur); // 332	Distance
	(*commandes).lineaireCentre[2]=(int)(0.257847533632*largeur); // 414+596/2	Simulation < temps réèl
	(*commandes).lineaireCentre[3]=(int)(0.406950672646*largeur); // 414+596/2	Simulation > temps réèl	

		// BOUTONS TRIANGULAIRES SUIVANT Y
	(*commandes).triangleY=(int)(0.030*hauteur); // Rayon suivant Y 0.925000
	(*commandes).trianglesCentre=(int)(0.957500*hauteur); // Position Y des petits triangles
	(*commandes).trianglesLumiere=(int)(0.957500*hauteur); // Position Y des lumières
		// BOUTONS TRIANGULAIRES SUIVANT X
	(*commandes).triangleX=(int)(0.016*largeur); // Rayon suivant X 0.007500
	(*commandes).triangleCentre[0]=(int)(0.023750*largeur); // 	vide
	(*commandes).triangleCentre[1]=(int)(0.065000*largeur); // 	mur
	(*commandes).triangleCentre[2]=(int)(0.105000*largeur); //  sortie
	(*commandes).triangleCentre[3]=(int)(0.805000*largeur); // 	entree
	(*commandes).triangleCentre[4]=(int)(0.143750*largeur); // 	mobile

	(*commandes).triangleCentre[5]=(int)(0.197500*largeur); // 	point
	(*commandes).triangleCentre[6]=(int)(0.237500*largeur); // 	trait
	(*commandes).triangleCentre[7]=(int)(0.277500*largeur); // 	rectangle

	(*commandes).triangleCentre[8]=(int)(0.685765*largeur); // 	3
	(*commandes).triangleCentre[9]=(int)(0.714414*largeur); // 	4

		//	Vitesse de la simulation

	(*commandes).a=(0.277*largeur-0.23*largeur)/(DUREE-2);
	//(*commandes).a=(((*commandes).triangleCentre[6]-(*commandes).triangleCentre[5])/(DUREE-2)));
	(*commandes).b=0.23*largeur-(*commandes).a;	//	Droite duree < DUREE
	//(*commandes).b=((*commandes).triangleCentre[5]-(*commandes).a);	//	Droite duree < DUREE
	(*commandes).A=(0.42*largeur-0.38*largeur)/(DUREE_MAX-DUREE-1);
	//(*commandes).A=(((*commandes).triangleCentre[10]-(*commandes).triangleCentre[9])/(DUREE_MAX-DUREE-1));
	(*commandes).B=0.38*largeur-(*commandes).A*(DUREE+1);	//	Droite duree > DUREE
	//(*commandes).B=((*commandes).triangleCentre[9]-(*commandes).A*(DUREE+1));	//	Droite duree > DUREE

	return 0;
	}

int commandesInitialiseSouris(commandesT * commandes, int sourisX, int sourisY)
	{
		 // Rayon des petits boutons
	int rayonX=(*commandes).boutonX;
	int rayonY=(*commandes).boutonY;

		// POSITION DE LA SOURIS
	(*commandes).sourisX = sourisX; // position X de la souris
	(*commandes).sourisY = sourisY; // position Y de la souris

	if(sourisX>(*commandes).rotatifs)
		{
		if(sourisX<(*commandes).boutons)// Zone des boutons rotatifs
			{
			rayonX=(*commandes).rotatifX;
			rayonY=(*commandes).rotatifY;
			}
		}
	else 
		{
		if(sourisY>(*commandes).bas) // Zone du bas
			{
			rayonX=(*commandes).triangleX;
			rayonY=(*commandes).triangleY;
			}
		}

	(*commandes).sourisGauche = sourisX-rayonX; // position X de la souris - RayonBoutonX
	(*commandes).sourisDroite = sourisX+rayonX; // position X de la souris + RayonBoutonX
	(*commandes).sourisHaut = sourisY-rayonY; // position Y de la souris - RayonBoutonY
	(*commandes).sourisBas = sourisY+rayonY; // position Y de la souris + RayonBoutonY

	return 0;
	}

int commandeBoutons(commandesT * commandes)
	{
	int i;
	if((*commandes).boutonsCentre>(*commandes).sourisGauche && (*commandes).boutonsCentre<(*commandes).sourisDroite)
		{
		for(i=0;i<BOUTON_COMMANDES;i++)
			{
			if((*commandes).boutonCentre[i]>(*commandes).sourisHaut && (*commandes).boutonCentre[i]<(*commandes).sourisBas)
				{
				return i;
				}
			}
		}
	return -1;
	}

int commandeRotatifs(commandesT * commandes)
	{
	int i;
	if((*commandes).rotatifsCentre>(*commandes).sourisGauche && (*commandes).rotatifsCentre<(*commandes).sourisDroite)
		{
		for(i=0;i<ROTATIF_COMMANDES;i++)
			{
			if((*commandes).rotatifCentre[i]>(*commandes).sourisHaut && (*commandes).rotatifCentre[i]<(*commandes).sourisBas)
				{
				return i;
				}
			}
		}
	return -1;
	}

int commandeTriangles(commandesT * commandes)
	{
	int i;
	if((*commandes).trianglesCentre>(*commandes).sourisHaut && (*commandes).trianglesCentre<(*commandes).sourisBas)
		{
		for(i=0;i<TRIANGLE_COMMANDES;i++)
			{
			if((*commandes).triangleCentre[i]>(*commandes).sourisGauche && (*commandes).triangleCentre[i]<(*commandes).sourisDroite)
				{
				return i;
				}
			}
		}
	return -1;
	}

int commandeLineaires(commandesT * commandes)
	{
	int i;
	if((*commandes).lineairesCentre>(*commandes).sourisHaut && (*commandes).lineairesCentre<(*commandes).sourisBas)
		{
		for(i=0;i<LINEAIRE_COMMANDES;i++)
			{
			if((*commandes).lineaireCentre[i]>(*commandes).sourisGauche && (*commandes).lineaireCentre[i]<(*commandes).sourisDroite)
				{
				return i;
				}
			}
		}
	return -1;
	}

//////////////////////////////////////////////////////////////////
