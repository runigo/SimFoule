# Copyright décembre 2019, Stephan Runigo
# runigo@free.fr
# SimFoule 2.2  simulateur de foule
# Ce logiciel est un programme informatique servant à simuler l'évacuation
# d'une foule dans un batiment et à en donner une représentation graphique.
# Ce logiciel est régi par la licence CeCILL soumise au droit français et
# respectant les principes de diffusion des logiciels libres. Vous pouvez
# utiliser, modifier et/ou redistribuer ce programme sous les conditions
# de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
# sur le site "http://www.cecill.info".
# En contrepartie de l'accessibilité au code source et des droits de copie,
# de modification et de redistribution accordés par cette licence, il n'est
# offert aux utilisateurs qu'une garantie limitée. Pour les mêmes raisons,
# seule une responsabilité restreinte pèse sur l'auteur du programme, le
# titulaire des droits patrimoniaux et les concédants successifs.
# A cet égard l'attention de l'utilisateur est attirée sur les risques
# associés au chargement, à l'utilisation, à la modification et/ou au
# développement et à la reproduction du logiciel par l'utilisateur étant
# donné sa spécificité de logiciel libre, qui peut le rendre complexe à
# manipuler et qui le réserve donc à des développeurs et des professionnels
# avertis possédant des connaissances informatiques approfondies. Les
# utilisateurs sont donc invités à charger et tester l'adéquation du
# logiciel à leurs besoins dans des conditions permettant d'assurer la
# sécurité de leurs systèmes et ou de leurs données et, plus généralement,
# à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
# Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
# pris connaissance de la licence CeCILL, et que vous en avez accepté les
# termes.


CC=gcc
EXEC=SimFoule
CFLAGS= -Wall -Wextra -Werror --std=c99
LDFLAGS= -Wall -Wextra -Werror --std=c99 -lm -lpthread
#
# gcc principale.c -o principale -lm -Wall -Wextra -lSDL2 -lSDL2main
#  ` sdl2-config --libs`
#
OBJDIR = ./obj

all : $(EXEC)

$(EXEC) : $(OBJDIR)/principale.o $(OBJDIR)/controleur.o $(OBJDIR)/controleurClavier.o $(OBJDIR)/controleurSouris.o $(OBJDIR)/donnees.o $(OBJDIR)/fichier.o $(OBJDIR)/options.o $(OBJDIR)/systeme.o $(OBJDIR)/construction.o $(OBJDIR)/batiment.o $(OBJDIR)/projection.o $(OBJDIR)/graphe.o $(OBJDIR)/interface.o $(OBJDIR)/commandes.o $(OBJDIR)/graphique.o $(OBJDIR)/horloge.o $(OBJDIR)/points.o $(OBJDIR)/etage.o $(OBJDIR)/cellule.o $(OBJDIR)/foule.o $(OBJDIR)/chaine.o $(OBJDIR)/mobile.o $(OBJDIR)/vecteur.o
	$(CC) -g  $(OBJDIR)/principale.o $(OBJDIR)/controleur.o $(OBJDIR)/controleurClavier.o $(OBJDIR)/controleurSouris.o $(OBJDIR)/donnees.o $(OBJDIR)/fichier.o $(OBJDIR)/options.o $(OBJDIR)/systeme.o $(OBJDIR)/construction.o $(OBJDIR)/batiment.o $(OBJDIR)/projection.o $(OBJDIR)/graphe.o $(OBJDIR)/interface.o $(OBJDIR)/commandes.o $(OBJDIR)/graphique.o $(OBJDIR)/horloge.o $(OBJDIR)/points.o $(OBJDIR)/etage.o $(OBJDIR)/cellule.o $(OBJDIR)/foule.o $(OBJDIR)/chaine.o $(OBJDIR)/mobile.o $(OBJDIR)/vecteur.o ` sdl2-config --libs` $(LDFLAGS) -o $(EXEC)

$(OBJDIR)/principale.o : controleur/principale.c controleur/principale.h
	$(CC) -c -g controleur/principale.c $(CFLAGS) -o $@

$(OBJDIR)/controleur.o : controleur/controleur.c controleur/controleur.h
	$(CC) -c -g controleur/controleur.c $(CFLAGS) -o $@

$(OBJDIR)/controleurClavier.o : controleur/controleurClavier.c controleur/controleurClavier.h
	$(CC) -c -g controleur/controleurClavier.c $(CFLAGS) -o $@

$(OBJDIR)/controleurSouris.o : controleur/controleurSouris.c controleur/controleurSouris.h
	$(CC) -c -g controleur/controleurSouris.c $(CFLAGS) -o $@

$(OBJDIR)/projection.o : controleur/projection.c controleur/projection.h
	$(CC) -c -g controleur/projection.c $(CFLAGS) -o $@

$(OBJDIR)/options.o : controleur/options.c controleur/options.h
	$(CC) -c -g controleur/options.c $(CFLAGS) -o $@

$(OBJDIR)/donnees.o : donnees/donnees.c donnees/donnees.h
	$(CC) -c -g donnees/donnees.c $(CFLAGS) -o $@

$(OBJDIR)/fichier.o : donnees/fichier.c donnees/fichier.h
	$(CC) -c -g donnees/fichier.c $(CFLAGS) -o $@

$(OBJDIR)/graphe.o : interface/graphe.c interface/graphe.h
	$(CC) -c -g interface/graphe.c $(CFLAGS) -o $@

$(OBJDIR)/interface.o : interface/interface.c interface/interface.h
	$(CC) -c -g interface/interface.c $(CFLAGS) -o $@

$(OBJDIR)/commandes.o : interface/commandes.c interface/commandes.h
	$(CC) -c -g interface/commandes.c $(CFLAGS) -o $@

$(OBJDIR)/horloge.o : interface/horloge.c interface/horloge.h
	$(CC) -c -g interface/horloge.c $(CFLAGS) -o $@

$(OBJDIR)/graphique.o : interface/graphique.c interface/graphique.h
	$(CC) -c -g interface/graphique.c $(CFLAGS) -o $@

$(OBJDIR)/points.o : interface/points.c interface/points.h
	$(CC) -c -g interface/points.c $(CFLAGS) -o $@

$(OBJDIR)/systeme.o : modele/systeme.c modele/systeme.h
	$(CC) -c -g modele/systeme.c $(CFLAGS) -o $@

$(OBJDIR)/construction.o : modele/construction.c modele/construction.h
	$(CC) -c -g modele/construction.c $(CFLAGS) -o $@

$(OBJDIR)/batiment.o : modele/batiment.c modele/batiment.h
	$(CC) -c -g modele/batiment.c $(CFLAGS) -o $@

$(OBJDIR)/etage.o : modele/etage.c modele/etage.h
	$(CC) -c -g modele/etage.c $(CFLAGS) -o $@

$(OBJDIR)/cellule.o : modele/cellule.c modele/cellule.h
	$(CC) -c -g modele/cellule.c $(CFLAGS) -o $@

$(OBJDIR)/foule.o : modele/foule.c modele/foule.h
	$(CC) -c -g modele/foule.c $(CFLAGS) -o $@

$(OBJDIR)/chaine.o : modele/chaine.c modele/chaine.h
	$(CC) -c -g modele/chaine.c $(CFLAGS) -o $@

$(OBJDIR)/mobile.o : modele/mobile.c modele/mobile.h
	$(CC) -c -g modele/mobile.c $(CFLAGS) -o $@

$(OBJDIR)/vecteur.o : modele/vecteur.c modele/vecteur.h
	$(CC) -c -g modele/vecteur.c $(CFLAGS) -o $@

clean :
	rm $(OBJDIR)/*.o

net : clean
	rm $(EXEC)

