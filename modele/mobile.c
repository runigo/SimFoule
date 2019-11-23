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


#include "../modele/mobile.h"

	//	1	INITIALISATION
int mobileInitialiseDt(mobileT * mobile, float dt) ;

	//	2	ÉVOLUTION
int mobileMemeEtage(mobileT * mobile1, mobileT * mobile2);
int mobileDistanceArithmetique(mobileT * mobile1, mobileT * mobile2);

	//	3	CHANGEMENT  DES  PARAMÈTRES
	//	4	AFFICHAGE


				//				------------------
				//				  INITIALISATION
				//				------------------

int mobileInitialise(mobileT * mobile, float dt)
	{

	vecteurCartesien(&(*mobile).vitesse, 0, 0, 0);
	vecteurCartesien(&(*mobile).vitesseSouhaitee, 0, 0, 0);
	vecteurCartesien(&(*mobile).forceBatiment, 0, 0, 0);
	vecteurCartesien(&(*mobile).forceMobiles, 0, 0, 0);
	vecteurCartesien(&(*mobile).forceMurs, 0, 0, 0);
	vecteurCartesien(&(*mobile).sommeForces, 0, 0, 0);

	mobileInitialisePosition(mobile, 0, 0, 0);

	mobileInitialiseDt(mobile, dt);

	mobileInitialiseTaille(mobile, MOBILE_IMP);
	mobileInitialiseMasse(mobile, MASSE_IMP);
	mobileInitialiseNervosite(mobile, NERVOSITE_IMP);
	mobileInitialiseCelerite(mobile, CELERITE_IMP);

	mobileInitialiseVivacite(mobile, VIVACITE_IMP);

	return 0;
	}

int mobileInitialisePosition(mobileT * mobile, float x, float y, int z)
	{
	vecteurCartesien(&(*mobile).nouveau, x, y, z);
	vecteurCartesien(&(*mobile).actuel, x, y, z);
	vecteurCartesien(&(*mobile).ancien, x, y, z);

	return 0;
	}

int mobileInitialiseDt(mobileT * mobile, float dt)
	{
	int retour = 0;

	(*mobile).dt = dt;

	if( (*mobile).dt > DT_MAX )
		{
		(*mobile).dt = DT_MAX; retour ++;
		}
	else { if( (*mobile).dt < DT_MIN )
			{
			(*mobile).dt = DT_MIN; retour ++;
			}
		}

	return retour;
	}

int mobileInitialiseTaille(mobileT * mobile, int taille)
	{
	int retour = 0;

	(*mobile).taille = taille;

	if( (*mobile).taille > MOBILE_MAX )
		{
		(*mobile).taille = MOBILE_MAX; retour ++;
		}
	else { if( (*mobile).taille < MOBILE_MIN )
			{
			(*mobile).taille = MOBILE_MIN; retour ++;
			}
		}

	(*mobile).rayon = 0.5*(*mobile).taille;

	return retour;
	}



int mobileInitialiseMasse(mobileT * mobile, float masse)
	{
	int retour = 0;

	(*mobile).masse = masse;

	if( (*mobile).masse >  MASSE_MAX )
		{
		(*mobile).masse = MASSE_MAX; retour ++;
		}
	else { if( (*mobile).masse < MASSE_MIN )
			{
			(*mobile).masse = MASSE_MIN; retour ++;
			}
		}

	(*mobile).dt2surM = (*mobile).dt*(*mobile).dt/(*mobile).masse;

	return retour;
	}



int mobileInitialiseNervosite(mobileT * mobile, float nervosite)
	{
	int retour = 0;

	(*mobile).nervosite = nervosite;

	if( (*mobile).nervosite > NERVOSITE_MAX )
		{
		(*mobile).nervosite = NERVOSITE_MAX; retour ++;
		}
	else { if( (*mobile).nervosite < NERVOSITE_MIN )
			{
			(*mobile).nervosite = NERVOSITE_MIN; retour ++;
			}
		}

	(*mobile).dtsurtau = (*mobile).dt*(*mobile).nervosite;

	return retour;
	}


int mobileInitialiseCelerite(mobileT * mobile, float celerite)
	{
	int retour = 0;

	(*mobile).celerite = celerite;

	if( (*mobile).celerite > CELERITE_MAX )
		{
		(*mobile).celerite = CELERITE_MAX; retour ++;
		}
	else { if( (*mobile).celerite < CELERITE_MIN )
			{
			(*mobile).celerite = CELERITE_MIN; retour ++;
			}
		}

	return retour;
	}

int mobileInitialiseVivacite(mobileT * mobile, float vivacite)
	{
	int retour = 0;

	(*mobile).vivacite = vivacite;

	if( (*mobile).vivacite > VIVACITE_MAX )
		{
		(*mobile).vivacite = VIVACITE_MAX; retour ++;
		}
	else { if( (*mobile).vivacite < VIVACITE_MIN )
			{
			(*mobile).vivacite = VIVACITE_MIN; retour ++;
			}
		}

	return retour;
	}


	//		Initialisation sans test de valeur
void mobileInitialiseMasseEco(mobileT * mobile, float masse, float dt2surM)
	{

	(*mobile).masse = masse;

	(*mobile).dt2surM = dt2surM;

	return;
	}

void mobileInitialiseNervositeEco(mobileT * mobile, float nervosite, float dtsurtau)
	{

	(*mobile).nervosite = nervosite;

	(*mobile).dtsurtau = dtsurtau;

	return;
	}

void mobileInitialiseCeleriteEco(mobileT * mobile, float celerite)
	{

	(*mobile).celerite = celerite;

	return;
	}

				//				-------------
				//				  ÉVOLUTION
				//				-------------

float mobileCalculVitesse(mobileT * mobile)
	{	// vitesse = nouveau - ancien = vitesse en unité de dt
	vecteurDifferenceCartesien2D(&(*mobile).nouveau, &(*mobile).actuel, &(*mobile).vitesse); // v3 = v1 - v2
	return sqrt(vecteurScalaireCartesien2D(&(*mobile).vitesse, &(*mobile).vitesse));
	}

int mobileIncremente(mobileT * mobile)
	{
	vecteurEgaleCartesien(&(*mobile).actuel, &(*mobile).ancien); // v2 = v1
	vecteurEgaleCartesien(&(*mobile).nouveau, &(*mobile).actuel); // v2 = v1
	return 0;
	}

int mobileInertie(mobileT * mobile)
	{// nouveau = 2 actuel - ancien + somme des forces

		// nouveau = 2 actuel - ancien
	vecteurSommeCartesien2D(&(*mobile).actuel, &(*mobile).actuel, &(*mobile).nouveau); // v3 = v1 + v2
	vecteurDifferenceCartesien2D(&(*mobile).nouveau, &(*mobile).ancien, &(*mobile).nouveau); // v3 = v1 - v2


		// nouveau += somme des forces
	vecteurSommeCartesien2D(&(*mobile).sommeForces, &(*mobile).nouveau, &(*mobile).nouveau); // v3 = v1 + v2
	
	return 0;
	}

float mobileCouplage(mobileT * mobile, vecteurT * vitesseSouhaitee)
	{
		// vitesse = nouveau - actuel
	vecteurDifferenceCartesien2D(&(*mobile).nouveau, &(*mobile).actuel, &(*mobile).vitesse); // v3 = v1 - v2

		// vitesseSouhaite = dt vitesseSouhaite
	vecteurProduitCartesien2D(vitesseSouhaitee, (*mobile).dt, &(*mobile).vitesseSouhaitee); // v2 = lambda v1

		// force = vitesse souhaite - vitesse (le tout fois dt)
	vecteurDifferenceCartesien2D(&(*mobile).vitesseSouhaitee, &(*mobile).vitesse, &(*mobile).forceBatiment); // v3 = v1 - v2

		//  force = dtsurtau * FORCE_COUPLAGE * force
	vecteurProduitCartesien2D(&(*mobile).forceBatiment, (*mobile).dtsurtau, &(*mobile).forceBatiment); // v2 = lambda v1

	return vecteurNormeCartesien2D(&(*mobile).forceBatiment);
	}

int mobileMemeEtage(mobileT * mobile1, mobileT * mobile2)
	{	// = 0 si étage différent, 1 si même étage, -1 si sortie
	int meme = 0;
	if((*mobile1).nouveau.z == -1 || (*mobile2).nouveau.z == -1)
		meme = -1;
	else
		if((*mobile1).nouveau.z == (*mobile2).nouveau.z)
			meme = 1;

	return meme;
	}

int mobileDistanceArithmetique(mobileT * mobile1, mobileT * mobile2)
	{	// En pixel, retourne la distance arithmétique (dx+dy)
	int X = (*mobile1).nouveau.x - (*mobile2).nouveau.x;
	int Y = (*mobile1).nouveau.y - (*mobile2).nouveau.y;

	if(X<0) { X=-X; }
	if(Y<0) { Y=-Y; }

	return X+Y;
	}

int mobileProximite(mobileT * mobile1, mobileT * mobile2)
	{	// retourne 1 si les mobiles sont proches, 0 sinon
	if(mobileMemeEtage(mobile1, mobile2)==1)
		{
		int proximite=(*mobile1).taille + (*mobile2).taille;
		if(mobileDistanceArithmetique(mobile1, mobile2) < proximite)
			return 1;
		}
	return 0;
	}

float mobileAjouteForceMobile(mobileT * mobile1, mobileT * mobile2)
	{
	float force = 0;
	vecteurT vecteur; // r = actuel1 - actuel2  puis normalisation
	vecteurCartesien(&vecteur, 0, 0, 0);

		// Vecteur = nouveau1 - nouveau2
	vecteurDifferenceCartesien2D(&(*mobile1).nouveau, &(*mobile2).nouveau, &vecteur); // v3 = v1 - v2

		// Vecteur = unitaire (nouveau1 - nouveau2)
	float distance = vecteurNormaliseCartesien2D(&vecteur); // normalise, renvoie la norme initiale
	float distanceMin=(*mobile1).rayon + (*mobile2).rayon;

	if(distance < distanceMin)	//	Calcul de la force
		{
		force = FORCE_CONTACT_MOBILE * (*mobile1).dt2surM * (distanceMin - distance); // norme de la force

			// Vecteur = force * unitaire
		vecteurProduitCartesien2D(&vecteur, force, &vecteur); // v2 = lambda v1

			// Ajoute la force sur 1
		vecteurSommeCartesien2D(&(*mobile1).forceMobiles, &vecteur, &(*mobile1).forceMobiles); // v3 = v1 + v2

			// Vecteur = - vecteur
		vecteurProduitCartesien2D(&vecteur, -1, &vecteur); // v2 = lambda v1

			// Ajoute -force sur 2
		vecteurSommeCartesien2D(&(*mobile2).forceMobiles, &vecteur, &(*mobile2).forceMobiles); // v3 = v1 + v2
		}

	return vecteurNormeCartesien2D(&vecteur);
	}

float mobileAjouteForceMur(mobileT * mobile, int DX, int DY, vecteurT * angle)
	{
	float force = 0;
		// Position de l'mobile
	float x = (*mobile).nouveau.x;
	float y = (*mobile).nouveau.y;
		// Position de la cellule
	int X = (int)(x/CELLULE);
	int Y = (int)(y/CELLULE);
		// vecteur temporaire
	vecteurT vecteur; // r = actuel1 - actuel2  puis normalisation

		// vecteur = position du mur
	if(DX==0)
		vecteurCartesien(&vecteur, x, Y*CELLULE + CELLULESUR2 + DY*CELLULESUR2, 0);
	if(DY==0)
		vecteurCartesien(&vecteur, X*CELLULE + CELLULESUR2 + DX*CELLULESUR2, y, 0);
	if(DX!=0 && DY!=0)
		vecteurCartesien(&vecteur, X*CELLULE + CELLULESUR2 + DX*CELLULESUR2, Y*CELLULE + CELLULESUR2 + DY*CELLULESUR2, 0);

		// Vecteur = nouveau - mur
	vecteurDifferenceCartesien2D(&(*mobile).nouveau, &vecteur, &vecteur); // v3 = v1 - v2
		// Vecteur = unitaire (nouveau - mur)
	float distance = vecteurNormaliseCartesien2D(&vecteur); // normalise, renvoie la norme initiale

	float distanceMin = (*mobile).rayon;

	if(distance<distanceMin) // 
		{
		force = FORCE_CONTACT_MUR*(*mobile).dt2surM*(distanceMin - distance); // norme de la forceSUR2

			// Vecteur = force * unitaire
		vecteurProduitCartesien2D(angle, force, &vecteur); // v2 = lambda v1

			// Ajoute la force sur 1
		vecteurSommeCartesien2D(&(*mobile).forceMurs, &vecteur, &(*mobile).forceMurs); // v3 = v1 + v2
		}

	return force;
	}


					//				-------------------------------
					//				  CHANGEMENT  DES  PARAMÈTRES
					//				-------------------------------

int mobileChangeMasse(mobileT * mobile, float facteur)
	{
	int retour = 0;

	(*mobile).masse = (*mobile).masse * facteur;

	if( (*mobile).masse >  MASSE_MAX )
		{
		(*mobile).masse = MASSE_MAX; retour ++;
		}
	else { if( (*mobile).masse < MASSE_MIN )
			{
			(*mobile).masse = MASSE_MIN; retour ++;
			}
		}

	(*mobile).dt2surM = (*mobile).dt*(*mobile).dt/(*mobile).masse;

	return retour;
	}

int mobileChangeNervosite(mobileT * mobile, float facteur)
	{
	int retour = 0;

	(*mobile).nervosite = (*mobile).nervosite * facteur;

	if( (*mobile).nervosite > NERVOSITE_MAX )
		{
		(*mobile).nervosite = NERVOSITE_MAX; retour ++;
		}
	else { if( (*mobile).nervosite < NERVOSITE_MIN )
			{
			(*mobile).nervosite = NERVOSITE_MIN; retour ++;
			}
		}

	(*mobile).dtsurtau = (*mobile).dt*(*mobile).nervosite;

	return retour;
	}

int mobileChangeCelerite(mobileT * mobile, float facteur)
	{
	int retour = 0;

	(*mobile).celerite = (*mobile).celerite * facteur;

	if( (*mobile).celerite > CELERITE_MAX )
		{
		(*mobile).celerite = CELERITE_MAX; retour ++;
		}
	else { if( (*mobile).celerite < CELERITE_MIN )
			{
			(*mobile).celerite = CELERITE_MIN; retour ++;
			}
		}

	return retour;
	}

int mobileChangeVivacite(mobileT * mobile, int impact)
	{

	(*mobile).vivacite = (*mobile).vivacite - impact;

	if( (*mobile).vivacite < 0 )
		{
		fprintf(stderr, "\nMobile supprimé\n"); return 1;
		}

	return 0;
	}

int mobileImpactVivacite(mobileT * mobile)
	{

	(*mobile).vivacite --;
	fprintf(stderr, "	mobile.vivacite = %d \n", (*mobile).vivacite);

	if( (*mobile).vivacite < 0 )
		{
		fprintf(stderr, "Mobile supprimé\n\n");
		(*mobile).nouveau.z=-3; // Abandon du mobile.
		return 1;
		}

	return 0;
	}


						//				-------------
						//				  AFFICHAGE
						//				-------------

int mobileAffiche(mobileT * mobile)
	{
	fprintf(stderr, "\nAffiche mobile\n");
	fprintf(stderr, "  nouveau x : %f , actuel x : %f, ancien x : %f\n", (*mobile).nouveau.x, (*mobile).actuel.x, (*mobile).nouveau.x);
	fprintf(stderr, "  nouveau y : %f , actuel y : %f, ancien y : %f\n", (*mobile).nouveau.y, (*mobile).actuel.y, (*mobile).nouveau.y);

	fprintf(stderr, "  vitesse x : %f , vitesse y : %f\n", (*mobile).vitesse.x, (*mobile).vitesse.y);
	fprintf(stderr, "  vitesseSouhaite x : %f , vitesseSouhaite y : %f\n", (*mobile).vitesseSouhaitee.x, (*mobile).vitesseSouhaitee.y);
	fprintf(stderr, "  forceExterieur x : %f , forceExterieur y : %f\n\n", (*mobile).forceBatiment.x, (*mobile).forceBatiment.y);


	fprintf(stderr, "  rayon : %f\n", (*mobile).rayon);
	fprintf(stderr, "  masse : %f\n", (*mobile).masse);
	fprintf(stderr, "  nervosite : %f\n", (*mobile).nervosite);
	fprintf(stderr, "  celerite : %f\n", (*mobile).celerite);
	fprintf(stderr, "  dtsurtau : %f\n", (*mobile).dtsurtau);
	fprintf(stderr, "  dt2surM : %f\n", (*mobile).dt2surM);
	fprintf(stderr, "  dt : %f\n", (*mobile).dt);
	fprintf(stderr, "  taille : %d\n\n", (*mobile).taille);

	return 0;
	}

///////////////////////////////////////////////////////////////////////////
