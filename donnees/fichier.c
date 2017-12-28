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


#include "fichier.h"

void fichierEcriture(etageT * etage, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */

	switch (numero)
		{
		case 10:
			fichier = fopen("./donnees/enregistrement/situation_q.simfoule", "w");break;
		case 11:
			fichier = fopen("./donnees/enregistrement/situation_s.simfoule", "w");break;
		case 12:
			fichier = fopen("./donnees/enregistrement/situation_d.simfoule", "w");break;
		case 13:
			fichier = fopen("./donnees/enregistrement/situation_f.simfoule", "w");break;
		case 14:
			fichier = fopen("./donnees/enregistrement/situation_g.simfoule", "w");break;
		case 15:
			fichier = fopen("./donnees/enregistrement/situation_h.simfoule", "w");break;
		default:
			;
		}
	//fichier = fopen("fluxon.sicp", "w");  /* write */

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		int statut;
		int i, j;
		for(j=0;j<BATIMENT;j++)
			{
			for(i=0;i<BATIMENT-1;i++)
				{
				statut = etageDonneStatutCellule(etage, i,j);
				fprintf(fichier, "%d ", statut);
				}
			statut = etageDonneStatutCellule(etage, i,j);
			fprintf(fichier, "%d", statut);
			}
		fclose(fichier);
		}

	return;
	}

void fichierLecture(etageT * etage, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */

	switch (numero)
		{
		case 0: // Touche A
			fichier = fopen("./donnees/enregistrement/situation_a.simfoule", "r");break;
		case 1: // Touche Z
			fichier = fopen("./donnees/enregistrement/situation_z.simfoule", "r");break;
		case 2: // Touche E
			fichier = fopen("./donnees/enregistrement/situation_e.simfoule", "r");break;
		case 3: // Touche R
			fichier = fopen("./donnees/enregistrement/situation_r.simfoule", "r");break;
		case 4: // Touche T
			fichier = fopen("./donnees/enregistrement/situation_t.simfoule", "r");break;
		case 5: // Touche Y
			fichier = fopen("./donnees/enregistrement/situation_y.simfoule", "r");break;
		case 6: // Touche U
			fichier = fopen("./donnees/enregistrement/situation_u.simfoule", "r");break;
		case 7: // Touche I
			fichier = fopen("./donnees/enregistrement/situation_i.simfoule", "r");break;
		case 8: // Touche O
			fichier = fopen("./donnees/enregistrement/situation_o.simfoule", "r");break;
		case 9: // Touche P
			fichier = fopen("./donnees/enregistrement/situation_p.simfoule", "r");break;
		case 10: // Touche Q
			fichier = fopen("./donnees/enregistrement/situation_q.simfoule", "r");break;
		case 11: // Touche S
			fichier = fopen("./donnees/enregistrement/situation_s.simfoule", "r");break;
		case 12: // Touche D
			fichier = fopen("./donnees/enregistrement/situation_d.simfoule", "r");break;
		case 13: // Touche F
			fichier = fopen("./donnees/enregistrement/situation_f.simfoule", "r");break;
		case 14: // Touche G
			fichier = fopen("./donnees/enregistrement/situation_g.simfoule", "r");break;
		case 15: // Touche H
			fichier = fopen("./donnees/enregistrement/situation_h.simfoule", "r");break;
		case 16: // Touche J
			fichier = fopen("./donnees/enregistrement/situation_j.simfoule", "r");break;
		case 17: // Touche K
			fichier = fopen("./donnees/enregistrement/situation_k.simfoule", "r");break;
		case 18: // Touche L
			fichier = fopen("./donnees/enregistrement/situation_l.simfoule", "r");break;
		case 19: // Touche M
			fichier = fopen("./donnees/enregistrement/situation_m.simfoule", "r");break;
		default:
			;
		}
	//fichier = fopen("fluxon.sicp", "r");  /* read */
	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier de réinitialisation\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		int statut;
		int i, j;
		for(j=0;j<BATIMENT;j++)
			{
			for(i=0;i<BATIMENT-1;i++)
				{
				statut = 0;
				fscanf(fichier, "%d ", &statut);
				etageInitialiseStatutCellule(etage, i, j, statut);
				}
			fscanf(fichier, "%d\n", &statut);
			etageInitialiseStatutCellule(etage, i, j, statut);
			}
		fclose(fichier);
		}

	return;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
/*
Copyright janvier 2017, Stephan Runigo
runigo@free.fr
SiCF 1.1.1  simulateur de corde vibrante et spectre
Ce logiciel est un programme informatique servant à simuler l'équation
d'une chaîne de pendules et à en donner une représentation graphique en
trois dimensions.
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

