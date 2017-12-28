/*
Copyright décembre 2017, Stephan Runigo
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

int controleurSuppression(controleurT * controleur)
	{
	fprintf(stderr, "Suppression de l'interface\n");
	interfaceDestruction(&(*controleur).interface);
	fprintf(stderr, "Suppression du graphe\n");
	grapheSuppression(&(*controleur).graphe);
	fprintf(stderr, "Suppression de la foule\n");
	fouleSuppression(&(*controleur).foule);
	return 0;
	}
/*
int controleurCreation(controleurT * controleur)
	{
	interfaceInitialisation(&(*controleur).interface);
	grapheCreation(&(*controleur).graphe, NOMBRE);
	grapheInitialisation((*controleur).interface.rendu, &(*controleur).graphe);
	return 0;
	}
*/
int controleurSimulationGraphique(controleurT * controleur)
{
    
	while((*controleur).interface.continu) {
		while(SDL_PollEvent(&(*controleur).interface.evenement))
			{
			if((*controleur).interface.evenement.type == SDL_QUIT)
				{
				(*controleur).interface.continu = false;
				}

			switch((*controleur).interface.evenement.type)
				{
				case SDL_QUIT:
					(*controleur).interface.continu = false;
					break;
				case SDL_KEYDOWN:
					switch((*controleur).interface.evenement.key.keysym.sym)
					{
					case SDLK_i:
					break;
					}
				break;
			}
		}

	interfaceNettoyage(&(*controleur).interface);

	projectionEtagePlan(&(*controleur).etage, &(*controleur).projection, &(*controleur).graphe);
	projectionFoulePoints(&(*controleur).foule, &(*controleur).projection, &(*controleur).graphe);

	grapheDessineMur((*controleur).interface.rendu, &(*controleur).graphe);
	grapheDessineHumain((*controleur).interface.rendu, &(*controleur).graphe);

	interfaceMiseAJour(&(*controleur).interface);

	SDL_Delay((*controleur).options.pause);
    }
    return 0;
}
