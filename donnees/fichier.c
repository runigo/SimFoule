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


#include "fichier.h"

int fichierEcriture(batimentT * batiment, int numero)
	{
	(void)batiment;
	(void)numero;

	FILE *fichier;

	fichier = fopen("./donnees/enregistrement/temporaire.simfoule", "w");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		int statut;
		int i, j, k;

		int etageX = (*batiment).etage[0].etageX;
		fprintf(fichier, "%d ", etageX);

		int etageY = (*batiment).etage[0].etageY;
		fprintf(fichier, "%d ", etageY);

		int batimentZ = (*batiment).batimentZ;
		fprintf(fichier, "%d\n", batimentZ);

		for(k=0;k<batimentZ;k++)
			{
			(*batiment).etage[k].etage = k;
			for(j=0;j<etageY;j++)
				{
				for(i=0;i<etageX;i++)
					{
					statut = celluleDonneStatut(&(*batiment).etage[k].cellule[i][j]);
					fprintf(fichier, "%d ", statut);
					//fprintf(stderr, "%d ", statut);
					}
				fprintf(fichier, "\n");
				//fprintf(stderr, "\n");
				}
			}
		fclose(fichier);
		}
/*
	switch (numero)
		{
		case 10: // Touche W
			fichier = fopen("./donnees/enregistrement/situation_q.simfoule", "w");break;
		default:
			;
		}
*/
	return 0;
	}

int fichierLecture(batimentT * batiment, int numero)
	{
	int i, j, k;
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
		case 20: // Touche W
			fichier = fopen("./donnees/enregistrement/situation_w.simfoule", "r");break;
		case 21: // Touche X
			fichier = fopen("./donnees/enregistrement/situation_x.simfoule", "r");break;
		case 22: // Touche C
			fichier = fopen("./donnees/enregistrement/situation_c.simfoule", "r");break;
		case 23: // Touche V
			fichier = fopen("./donnees/enregistrement/situation_v.simfoule", "r");break;
		case 24: // Touche B
			fichier = fopen("./donnees/enregistrement/situation_b.simfoule", "r");break;
		case 25: // Touche N
			fichier = fopen("./donnees/enregistrement/situation_n.simfoule", "r");break;
		default:
			;
		}

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier de réinitialisation\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{

		printf("  Initialisation du batiment %d\n", numero);

		int statut=0;
		int retour=0;
		int etageX=50;	//	Nombre de cellule suivant x
		int etageY=25;	//	Nombre de cellule suivant y
		int etageZ=1;	//	Nombre d'étage

			// Volume du batiment

		retour=fscanf(fichier, "%d %d %d", &etageX, &etageY, &etageZ);
		if(retour==0)
			{
			fprintf(stderr, "ERREUR : fichierLecture(%d) : Retour fscanf = 0\n", numero);
			}
		if(retour<0)
			{
			fprintf(stderr, "ERREUR : fichierLecture(%d) : Retour fscanf < 0\n", numero);
			}

		(*batiment).batimentZ=etageZ;
		
		for(k=0;k<etageZ;k++)
			{
			(*batiment).etage[k].etageX=etageX;
			(*batiment).etage[k].etageY=etageY;
			}

			// Plan et occupation du batiment

		for(k=0;k<etageZ;k++)
			{
			(*batiment).etage[k].etage = k;
			for(j=0;j<etageY;j++)
				{
				for(i=0;i<etageX;i++)
					{
					statut = 0;
					retour=fscanf(fichier, "%d", &statut);
					if(retour==0)
						{
						fprintf(stderr, "ERREUR : fichierLecture(%d) : Retour fscanf = 0\n", numero);
						}
					if(retour<0)
						{
						fprintf(stderr, "ERREUR : fichierLecture(%d) : Retour fscanf < 0\n", numero);
						}
					celluleInitialiseStatut(&(*batiment).etage[k].cellule[i][j], statut);
					}
				}
			}
		fclose(fichier);
		}

		// Calcul du nombre de mobile
	int nombre = 0;
	for(k=0;k<(*batiment).batimentZ;k++)
		{
		for(i=0;i<(*batiment).etage[k].etageX;i++)
			{
			for(j=0;j<(*batiment).etage[k].etageY;j++)
				{
				if(celluleDonneStatut(&(*batiment).etage[k].cellule[i][j])==9)
					nombre++;
				}
			}
		}

	return nombre;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
