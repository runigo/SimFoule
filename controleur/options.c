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


#include "options.h"

void optionsInitial(optionsT * option, char *opt);
void optionsNombre(optionsT * option, char *opt);
void optionsTaille(optionsT * option, char *opt);
void optionsMasse(optionsT * option, char *opt);
void optionsNervosite(optionsT * option, char *opt);

void optionsDt(optionsT * option, char *opt);
void optionsPause(optionsT * option, char *opt);
void optionsMode(optionsT * option, char *opt);
void optionsDuree(optionsT * option, char *opt);
void optionsAide(void);

int optionsTraitement(optionsT * option, int nb, char *opt[])
	{
	int i=0;
	//fprintf(stderr, "\nNombre d'option : %d\n", nb);
	do
		{


		if(strcmp(opt[i], "initial")==0 && opt[i+1]!=NULL)
			optionsInitial(option, opt[i+1]);	// Numéro du fichier d'initialisation.
		if(strcmp(opt[i], "taille")==0 && opt[i+1]!=NULL)
			optionsTaille(option, opt[i+1]);		// Taille des mobiles
		if(strcmp(opt[i], "nervosite")==0 && opt[i+1]!=NULL)
			optionsNervosite(option, opt[i+1]);		// Nervosité des mobiles
		if(strcmp(opt[i], "masse")==0 && opt[i+1]!=NULL)
			optionsMasse(option, opt[i+1]);			// Masse des mobiles
/*
		if(strcmp(opt[i], "nombre")==0 && opt[i+1]!=NULL)
			optionsNombre(option, opt[i+1]);		// Nombre de mobile
*/
		if(strcmp(opt[i], "dt")==0 && opt[i+1]!=NULL)
			optionsDt(option, opt[i+1]);		// discrétisation du temps
		if(strcmp(opt[i], "duree")==0 && opt[i+1]!=NULL)
			optionsDuree(option, opt[i+1]);	// Nombre d'évolution du système entre les affichages.
		if(strcmp(opt[i], "mode")==0 && opt[i+1]!=NULL)
			optionsMode(option, opt[i+1]);		// Mode -1 : Wait, 1 : Poll
/*
		if(strcmp(opt[i], "dessineAngle")==0 && opt[i+1]!=NULL)
			optionsDuree(option, opt[i+1]);	// Dessin des directions.
		if(strcmp(opt[i], "dessineMur")==0 && opt[i+1]!=NULL)
			optionsPause(option, opt[i+1]);	// Dessin des murs
		if(strcmp(opt[i], "dessineMobile")==0 && opt[i+1]!=NULL)
			optionsMode(option, opt[i+1]);	// Dessin des mobiles
*/
		if(strcmp(opt[i], "aide")==0)
			optionsAide();		// Affiche l'aide.
		if(strcmp(opt[i], "help")==0)
			optionsAide();		// Affiche l'aide.

  		i++;
  		}
		while(i<nb);
	return 0;
	}

    	// Numero du fichier d'initialisation
void optionsInitial(optionsT * option, char *opt)
	{
	int initial = atoi(opt);
	if(initial>INITIAL_MIN && initial<INITIAL_MAX)
		{
		(*option).initial = initial;
		printf("Option initial valide, Initial = %d\n", (*option).initial);
		}
	else
		{
		printf("Option initial non valide, initial = %d\n", (*option).initial);
		printf("Option initial : %d < initial < %d\n",INITIAL_MIN, INITIAL_MAX);
		}
	return;
	}

    	// Taille des mobiles
void optionsTaille(optionsT * option, char *opt)
	{
	int taille = atoi(opt);

	if(taille>MOBILE_MIN && taille<MOBILE_MAX)
		{
		(*option).taille = taille;
		printf("Option taille valide, taille = %d\n", (*option).taille);
		}
	else
		{
		printf("Option taille non valide, taille = %d\n", (*option).taille);
		printf("Option taille : %d < taille < %d\n", MOBILE_MIN, MOBILE_MAX);
		}
	return;
	}

	// Nervosité des mobiles maximale Nervosite nervositeNERVOSITE_MAX
void optionsNervosite(optionsT * option, char *opt)
	{
	float nervosite = atof(opt);
	if(nervosite>NERVOSITE_MIN && nervosite<NERVOSITE_MAX)
		{
		(*option).nervosite = nervosite;
		printf("Option nervosite valide, nervosite = %f\n", (*option).nervosite);
		}
	else
		{
		printf("Option nervosite non valide, nervosite = %f\n", (*option).nervosite);
		printf("Option nervosite : %f < nervosite < %f\n", NERVOSITE_MIN, NERVOSITE_MAX);
		}
	return;
	}
/*
    	// Nombre de mobiles
void optionsNombre(optionsT * options, char *opt)
	{
	int nombre = atoi(opt);
	if(nombre > 0 && nombre < NOMBRE_MAX)
		{
		(*options).nombre = nombre;
		printf("Option nombre valide, nombre = %d\n", (*options).nombre);
		}
	else
		{
		printf("Option nombre non valide, nombre = %d\n", (*options).nombre);
		printf("Option nombre : 0.0 < nombre < %d\n", NOMBRE_MAX);
		}
	return;
	}
*/
    	// Masse des mobiles
void optionsMasse(optionsT * option, char *opt)
	{
	float masse = atof(opt);
	if(masse>MASSE_MIN && masse<MASSE_MAX)
		{
		(*option).masse = masse;
		printf("Option masse valide, masse = %f\n", (*option).masse);
		}
	else
		{
		printf("Option masse non valide, masse = %f\n", (*option).masse);
		printf("Option masse : %f < masse < %f\n", MASSE_MIN, MASSE_MAX);
		}
	return;
	}

    	// discrétisation du temps 
void optionsDt(optionsT * option, char *opt)
	{
	float dt = atof(opt);
	if(dt>DT_MIN && dt<DT_MAX)
		{
		(*option).dt = dt;
		printf("Option dt valide, dt = %f\n", (*option).dt);
		}
	else
		{
		printf("Option dt non valide, dt = %f\n", (*option).dt);
		printf("Option dt : %f < dt < %f\n", DT_MIN, DT_MAX);
		}
	return;
	}

    	// Nombre d'évolution du système entre les affichages
void optionsDuree(optionsT * option, char *opt)
	{
	int duree = atoi(opt);
	if ( duree > 0 && duree < DUREE_MAX)
		{
		(*option).duree = duree;
		printf("Option duree valide, duree = %d\n", (*option).duree);
		}
	else
		{
		printf("Option duree non valide, duree = %d\n", (*option).duree);
		printf("Option duree : 0 < duree < %d\n", DUREE_MAX);
		}
	return;
	}

		// Mode  -1 : Wait, 1 : Poll
void optionsMode(optionsT * option, char *opt)
	{
	int mode = atoi(opt);
	if(mode==1 || mode==-1)
		{
		(*option).mode = mode;
		printf("Option mode valide, mode = %d\n", (*option).mode);
		}
	else
		{
		printf("Option mode non valide, mode = %d\n", (*option).mode);
		printf("Option mode : mode = +/- 1\n");
		}
	return;
	}

			//	Dessin des graphes 0 ou 1
		int dessineAngle;
		int dessineMur;
		int dessineMobile;

    	// dessineAngle
void optionsDessineAngle(optionsT * option, char *opt)
	{
	int dessineAngle = atoi(opt);
	if(dessineAngle>0 && dessineAngle<255)
		{
		(*option).dessineAngle = dessineAngle;
		printf("Option dessineAngle valide, dessineAngle = %d\n", (*option).dessineAngle);
		}
	else
		{
		printf("Option dessineAngle non valide, dessineAngle = %d\n", (*option).dessineAngle);
		printf("Option dessineAngle : 0 < dessineAngle < 255\n");
		}
	return;
	}

    	// dessineMur 
void optionsdessineMur(optionsT * option, char *opt)
	{
	int dessineMur = atoi(opt);
	if(dessineMur>0 && dessineMur<255)
		{
		(*option).dessineMur = dessineMur;
		printf("Option dessineMur valide, dessineMur = %d\n", (*option).dessineMur);
		}
	else
		{
		printf("Option dessineMur non valide, dessineMur = %d\n", (*option).dessineMur);
		printf("Option dessineMur : 0 < dessineMur < 255\n");
		}
	return;
	}

    	// dessineMobile
void optionsdessineMobile(optionsT * option, char *opt)
	{
	int dessineMobile = atoi(opt);
	if(dessineMobile>0 && dessineMobile<255)
		{
		(*option).dessineMobile = dessineMobile;
		printf("Option dessineMobile valide, dessineMobile = %d\n", (*option).dessineMobile);
		}
	else
		{
		printf("Option dessineMobile non valide, dessineMobile = %d\n", (*option).dessineMobile);
		printf("Option dessineMobile : 0 < dessineMobile < 255\n");
		}
	return;
	}

void optionsAide(void)
	{
	printf("\n\nAide de SimFoule, le simulateur d'évacuation de foule\n\n");

	printf("OPTIONS DE LA LIGNE DE COMMANDE \n\n");

	printf(" fond		0 < fond < 255		couleur du fond de l'affichage (fond noir : 0, fond blanc : 255)\n");
	printf(" dt		%4.5f < dt < %4.2f	discrétisation du temps\n", DT_MIN, DT_MAX);
	printf(" duree		1 < duree < %d		nombre d'évolution du système entre les affichages\n", DUREE_MAX);
	printf(" mode		= -1 ou 1		mode avec ou sans attente (Mode -1 : Wait, 1 : Poll)\n");
	printf(" pause		5 < pause < 555		pause entre les affichages en ms\n");

	printf(" initial	%d < initial < %d	numéro du fichier d'initialisation\n", INITIAL_MIN, INITIAL_MAX);
	printf(" taille		%d < taille < %d	taille des mobiles\n", MOBILE_MIN, MOBILE_MAX);
	printf(" masse		%f < masse < %f		masse des mobiles\n", MASSE_MIN, MASSE_MAX);
	printf(" nervosite	%4.3f < nervosite < %4.1f	nervosité des mobiles\n", NERVOSITE_MIN, NERVOSITE_MAX);
	//printf("	flèches haut, bas, gauche, droite\n\n");
	printf(" dessineAngle		= 0 ou 1	Dessine ou non les directions\n");
	printf(" dessineMur		= 0 ou 1	Dessine ou non les murs\n");
	printf(" dessineMobile		= 0 ou 1	Dessine ou non les mobiles\n");

	printf("\nCOMMANDES CLAVIER\n\n");
/*
	printf("	a, q : augmenter, diminuer le couplage\n");
	printf("	z, s : augmenter, diminuer la masse\n");

	printf("	e, d : diminuer, augmenter la dissipation\n");
	printf("	r, f : retire, forme la dissipation\n");
	printf("	v : forme l'extrémité absorbante\n");

	printf("	t, g : augmenter, diminuer la gravitation\n");
	printf("	y, h : ajoute, enlève un déphasage de 2pi\n");

	printf("	w : conditions aux limites périodique\n");
	printf("	x : extrémités libres\n");
	printf("	c : extrémités fixe\n");
	printf("	b, n : fixe une extrémité, libère l'autre\n");

	printf("	flêche droite : allume, éteint le courant Josephson\n");
	printf("	flêches haut, bas : augmente diminue l'intensité\n");
	printf("	flêche gauche : change le sens du courant\n");

	printf("	u, j : augmenter, diminuer l'amplitude du générateur\n");
	printf("	i : démarre une impulsion\n");
	printf("	o : démarre, éteint le générateur\n");
	printf("	l : démarre le signal carrée\n");
	printf("	p, m : augmenter, diminuer la fréquence\n");

	printf("	F5 : affiche les observables\n");
*/
	printf("	Entrée : change le mode temporel (avec ou sans attente)\n");

	//printf("	+, - : augmente, diminue la vitesse de la simulation\n");
	printf("	F9, F10, F11, F12 : diminuent, augmentent la vitesse de la simulation\n");

	printf("	F6	Dessine ou non les directions\n");
	printf("	F7	Dessine ou non les murs\n");
	printf("	F8	Dessine ou non les mobiles\n");

	fprintf(stderr, "\nSortie de SimFoule\n");
	exit(EXIT_FAILURE);
	return;
	}

/////////////////////////////////////////////////////////////////////
/*
Copyright novembre 2017, Stephan Runigo
runigo@free.fr
SiCF 1.2  simulateur de corde vibrante et spectre
Ce logiciel est un programme informatique servant à simuler l'équation
d'une corde vibrante, à calculer sa transformée de fourier, et à donner
une représentation graphique de ces fonctions. 
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

