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


#include "fichier.h"

int fichierEcriture(batimentT * batiment, optionsT * options, char * nom)
	{
	(void)options;

	FILE *fichier;

	char chemin[120] = "./donnees/enregistrement/construction_";

	char * extension = ".simfoule";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "w");

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

int fichierLecture(batimentT * batiment, optionsT * options, char * nom)
	{
	int i, j, k;
	FILE *fichier; // pointeur sur FILE

	char chemin[120] = "./donnees/enregistrement/situation_";

	if((*options).initial == 1)
		{
		strcpy(chemin,"./donnees/enregistrement/construction_");
		}

	char * extension = ".simfoule";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "r");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier de réinitialisation\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		return -1;
		}
	else
		{

		printf("  Initialisation du batiment %s\n", chemin);

		int statut=0;
		int retour=0;
		int etageX=50;	//	Nombre de cellule suivant x
		int etageY=25;	//	Nombre de cellule suivant y
		int etageZ=1;	//	Nombre d'étage

			// Volume du batiment

		retour=fscanf(fichier, "%d %d %d", &etageX, &etageY, &etageZ);
		if(retour==0)
			{
			fprintf(stderr, "ERREUR : fichierLecture(%s) : Retour fscanf = 0\n", chemin);
			}
		if(retour<0)
			{
			fprintf(stderr, "ERREUR : fichierLecture(%s) : Retour fscanf < 0\n", chemin);
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
						fprintf(stderr, "ERREUR : fichierLecture(%s) : Retour fscanf = 0\n", chemin);
						}
					if(retour<0)
						{
						fprintf(stderr, "ERREUR : fichierLecture(%s) : Retour fscanf < 0\n", chemin);
						}
					celluleInitialiseStatut(&(*batiment).etage[k].cellule[i][j], statut);
					}
				}
			}
		fclose(fichier);
		}

	return 0;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
