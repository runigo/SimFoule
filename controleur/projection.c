/*
Copyright février 2018, Stephan Runigo
runigo@free.fr
SimFoule 1.4  simulateur de foule
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

#include "projection.h"

int projectionInitialiseCouleurs(projectionT * projection, int r, int v, int b, int fond)
	{
	(*projection).rouge=r;
	(*projection).vert=v;
	(*projection).bleu=b;
	(*projection).fond=fond;
	return 0;
	}

int projectionInitialiseLongueurs(projectionT * projection, int hauteur, int largeur)
	{
	(*projection).hauteur=hauteur;
	(*projection).largeur=largeur;
	return 0;
	}

int projectionChangeFenetre(projectionT * projection, int x, int y)
	{
	(*projection).hauteur=hauteur;
	(*projection).largeur=largeur;
	return 0;
	}

int projectionSystemeCommandes(systemeT * systeme, projectionT * projection, commandesT * commandes, int duree, int mode)
	{		// Projette le système sur les commandes

	(void)systeme;
	(void)projection;
	(void)commandes;
	(void)duree;
	(void)mode;

	float theta;
	float ratioRotatif = 0.9;
	float courantJosephson = projectionAbsolue((*systeme).moteurs.courantJosephson);

				//	Projection sur les boutons rotatifs
/*	 //	Couplage
	theta = DEUXPI * (*projection).logCouplage * log( (*systeme).couplage / (COUPLAGE_MIN * (*systeme).nombre) );
	(*commandes).rotatifPositionX[0]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[0]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));
*/
		//int rotatifPositionX[ROTATIF_COMMANDES]; // Position du bouton rotatif
		//int rotatifPositionY[ROTATIF_COMMANDES];


				//	Projection sur les petits boutons de droite
/*	int i;
	for(i=0;i<BOUTON_COMMANDES;i++) (*commandes).boutonEtat[i]=0;

		//int libreFixe;		//	0 : périodiques 1 : libres, 2 : fixes, 
							//		3 libre-fixe, 4 fixe-libre
	switch((*systeme).libreFixe)	//	
		{
		case 0:
			(*commandes).boutonEtat[0]=1;break;
		default:
			;
		}

	//	int modeDissipation;	//	0 : nulle 1 : uniforme, 2 : extrémité absorbante.
	switch((*systeme).modeDissipation)	//	
		{
		case 0:
			(*commandes).boutonEtat[5]=1;break;
		default:
			;
		}
*/
				//	Projection sur les petits boutons du bas
		//	Vitesse de la simulation
	if(duree<DUREE)
		{
			if(duree==1) (*commandes).triangleEtat[5]=-1; else (*commandes).triangleEtat[6]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).a * duree + (*commandes).b);
		}
	else
		{
		if(duree>DUREE)
			{
			if(duree==DUREE_MAX) (*commandes).triangleEtat[10]=-1; else (*commandes).triangleEtat[9]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).A * duree + (*commandes).B);
			}
		else
			{
			(*commandes).triangleEtat[8]=1;
			}
		}

	if(mode<0)
		{
		(*commandes).triangleEtat[7]=2;
		}
	return 0;
	}

int projectionBatimentPlan(batimentT * batiment, projectionT * projection, grapheT * graphe)
	{
			//	Projette la position des murs sur le graphe
	int i, j, k;
	(void)projection;

	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				(*graphe).plan[i][j][k]=(*batiment).etage[k].cellule[i][j].statut;
				}
			}
		}
	return 0;
	}

int projectionBatimentSens(batimentT * batiment, projectionT * projection, grapheT * graphe)
	{
			//	Projette la direction de la sortie sur le graphe
	int i, j, k;
	(void)projection;

	for(k=0;k<BATIMENT_Z;k++)
		{
		for(i=0;i<BATIMENT_X;i++)
			{
			for(j=0;j<BATIMENT_Y;j++)
				{
				(*graphe).angle[i][j][k]=(*batiment).etage[k].cellule[i][j].sens;
				}
			}
		}
	return 0;
	}


int projectionFoulePoints(fouleT * foule, projectionT * projection, grapheT * graphe)
	{
		//	Projette la position des mobiles sur le graphe

	chaineT *iterFoule=(*foule).premier;
	pointsT *iterGraph=(*graphe).premier;
	(void)projection;

	do
		{
		iterGraph->xm = (int)(iterFoule->mobile.nouveau.x);
		iterGraph->ym = (int)(iterFoule->mobile.nouveau.y);
		iterGraph->zm = (int)(iterFoule->mobile.nouveau.z);

		iterGraph = iterGraph->suivant;
		iterFoule = iterFoule->suivant;
		}
	while(iterGraph!=(*graphe).premier);

	return 0;
	}

///////////////////////////////////////////////////////////////////////

