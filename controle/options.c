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


#include "options.h"

void optionsInitial(optionsT * option, char *opt);
void optionsNombre(optionsT * option, char *opt);
void optionsMasse(optionsT * option, char *opt);
void optionsNervosite(optionsT * option, char *opt);

void optionsDt(optionsT * option, char *opt);
void optionsFond(optionsT * option, char *opt);
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
		if(strcmp(opt[i], "nervosite")==0 && opt[i+1]!=NULL)
			optionsNervosite(option, opt[i+1]);		// Nervosité des humains
		if(strcmp(opt[i], "masse")==0 && opt[i+1]!=NULL)
			optionsMasse(option, opt[i+1]);		// Masse des humains
/*
		if(strcmp(opt[i], "nombre")==0 && opt[i+1]!=NULL)
			optionsNombre(option, opt[i+1]);		// Nombre d'humain
*/
		if(strcmp(opt[i], "fond")==0 && opt[i+1]!=NULL)
			optionsFond(option, opt[i+1]);	// Couleur du fond
		if(strcmp(opt[i], "dt")==0 && opt[i+1]!=NULL)
			optionsDt(option, opt[i+1]);		// discrétisation du temps
		if(strcmp(opt[i], "duree")==0 && opt[i+1]!=NULL)
			optionsDuree(option, opt[i+1]);	// Nombre d'évolution du système entre les affichages.
		if(strcmp(opt[i], "pause")==0 && opt[i+1]!=NULL)
			optionsPause(option, opt[i+1]);	// temps de pause en ms
		if(strcmp(opt[i], "mode")==0 && opt[i+1]!=NULL)
			optionsMode(option, opt[i+1]);	// Mode -1 : Wait, 1 : Poll
		if(strcmp(opt[i], "aide")==0)
			optionsAide();	// Affiche l'aide.
		if(strcmp(opt[i], "help")==0)
			optionsAide();	// Affiche l'aide.

  		i++;
  		}
		while(i<nb);
	return 0;
	}

    	// Numero du fichier d'initialisation
void optionsInitial(optionsT * option, char *opt)
	{
	int initial = atoi(opt);
	if(initial>-255 && initial<255)
		{
		(*option).initial = initial;
		printf("Option initial valide, Initial = %d\n", (*option).initial);
		}
	else
		{
		printf("Option initial non valide, initial = %d\n", (*option).initial);
		printf("Option initial : -255 < initial < 255\n");
		}
	return;
	}

	// Nervosité des humains maximale Nervosite nervositeNERVOSITE_MAX
void optionsNervosite(optionsT * option, char *opt)
	{
	float nervosite = atof(opt);
	if(nervosite>0.0 && nervosite<NERVOSITE_MAX)
		{
		(*option).nervosite = nervosite;
		printf("Option nervosite valide, dt = %f\n", (*option).nervosite);
		}
	else
		{
		printf("Option nervosite non valide, dt = %f\n", (*option).nervosite);
		printf("Option nervosite : 0.0 < dt < %f\n", NERVOSITE_MAX);
		}
	return;
	}
/*
    	// Nombre d'humains
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
    	// Masse des humains
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
		printf("Option masse : %d < masse < %d\n", MASSE_MIN, MASSE_MAX);
		}
	return;
	}

    	// Couleur du fond 
void optionsFond(optionsT * option, char *opt)
	{
	int fond = atoi(opt);
	if(fond>0 && fond<255)
		{
		(*option).fond = fond;
		printf("Option fond valide, fond = %d\n", (*option).fond);
		}
	else
		{
		printf("Option fond non valide, fond = %d\n", (*option).fond);
		printf("Option fond : 0 < fond < 255\n");
		}
	return;
	}

    	// discrétisation du temps 
void optionsDt(optionsT * option, char *opt)
	{
	float dt = atof(opt);
	if(dt>0.0 && dt<DT_MAX)
		{
		(*option).dt = dt;
		printf("Option dt valide, dt = %f\n", (*option).dt);
		}
	else
		{
		printf("Option dt non valide, dt = %f\n", (*option).dt);
		printf("Option dt : 0.0 < dt < %f\n", DT_MAX);
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
		printf("Option duree : 0.0 < duree < %d\n", DUREE_MAX);
		}
	return;
	}

    	// Temps de pause en ms après affichage graphique
void optionsPause(optionsT * option, char *opt)
	{
	int pause = atoi(opt);
	if(pause>5 || pause<555)
		{
		(*option).pause = pause;
		printf("Option t valide, pause = %d\n", (*option).pause);
		}
	else
		{
		printf("Option t non valide, pause = %d\n", (*option).pause);
		printf("Option t : 5 < pause < 555\n");
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

void optionsAide(void)
	{
	printf("\n\nAide de SimFoule, le simulateur d'évacuation de foule\n\n");

	printf("OPTIONS DE LA LIGNE DE COMMANDE \n\n");

	printf(" fond		0 < fond < 255		couleur du fond de l'affichage (fond noir : 0, fond blanc : 255)\n");
	printf(" dt		0.0 < dt < %4.4f	discrétisation du temps\n", DT_MAX);
	printf(" masse		%d < dt < %d		masse des humains\n", MASSE_MIN, MASSE_MAX);
	//printf(" dissipation	0.0 < dissipation < %4.4f	dissipation\n", DISSIPATION_MAX);
	printf(" pause		5 < pause < 555		pause entre les affichages en ms\n");
	printf(" duree		1 < duree < %d		nombre d'évolution du système entre les affichages\n", DUREE_MAX);
	printf(" mode		= -1 ou 1		mode avec ou sans attente (Mode -1 : Wait, 1 : Poll)\n");
	//printf("	flèches haut, bas, gauche, droite\n\n");

	printf("\nCOMMANDES CLAVIER\n");
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
*/
	printf("	F5 : affiche les observables\n");

	printf("	Entrée : change le mode temporel (avec ou sans attente)\n");

	printf("	+, - : augmente, diminue la vitesse de la simulation\n");
	printf("	F9, F10, F11, F12 : diminuent, augmentent la vitesse de la simulation\n");

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

