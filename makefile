
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

$(EXEC) : $(OBJDIR)/principale.o $(OBJDIR)/controleur.o $(OBJDIR)/donnees.o $(OBJDIR)/fichier.o $(OBJDIR)/options.o $(OBJDIR)/batiment.o $(OBJDIR)/projection.o $(OBJDIR)/graphe.o $(OBJDIR)/interface.o $(OBJDIR)/points.o $(OBJDIR)/etage.o $(OBJDIR)/cellule.o $(OBJDIR)/foule.o $(OBJDIR)/chaine.o $(OBJDIR)/humain.o $(OBJDIR)/vecteur.o
	$(CC) -g  $(OBJDIR)/principale.o $(OBJDIR)/controleur.o $(OBJDIR)/donnees.o $(OBJDIR)/fichier.o $(OBJDIR)/options.o $(OBJDIR)/batiment.o $(OBJDIR)/projection.o $(OBJDIR)/graphe.o $(OBJDIR)/interface.o $(OBJDIR)/points.o $(OBJDIR)/etage.o $(OBJDIR)/cellule.o $(OBJDIR)/foule.o $(OBJDIR)/chaine.o $(OBJDIR)/humain.o $(OBJDIR)/vecteur.o ` sdl2-config --libs` $(LDFLAGS) -o $(EXEC)

$(OBJDIR)/principale.o : controle/principale.c controle/principale.h
	$(CC) -c -g controle/principale.c $(CFLAGS) -o $@

$(OBJDIR)/controleur.o : controle/controleur.c controle/controleur.h
	$(CC) -c -g controle/controleur.c $(CFLAGS) -o $@

$(OBJDIR)/projection.o : controle/projection.c controle/projection.h
	$(CC) -c -g controle/projection.c $(CFLAGS) -o $@

$(OBJDIR)/donnees.o : donnees/donnees.c donnees/donnees.h
	$(CC) -c -g donnees/donnees.c $(CFLAGS) -o $@

$(OBJDIR)/fichier.o : donnees/fichier.c donnees/fichier.h
	$(CC) -c -g donnees/fichier.c $(CFLAGS) -o $@

$(OBJDIR)/options.o : donnees/options.c donnees/options.h
	$(CC) -c -g donnees/options.c $(CFLAGS) -o $@

$(OBJDIR)/batiment.o : donnees/batiment.c donnees/batiment.h
	$(CC) -c -g donnees/batiment.c $(CFLAGS) -o $@

$(OBJDIR)/graphe.o : graphisme/graphe.c graphisme/graphe.h
	$(CC) -c -g graphisme/graphe.c $(CFLAGS) -o $@

$(OBJDIR)/interface.o : graphisme/interface.c graphisme/interface.h
	$(CC) -c -g graphisme/interface.c $(CFLAGS) -o $@

$(OBJDIR)/points.o : graphisme/points.c graphisme/points.h
	$(CC) -c -g graphisme/points.c $(CFLAGS) -o $@

$(OBJDIR)/etage.o : modele/etage.c modele/etage.h
	$(CC) -c -g modele/etage.c $(CFLAGS) -o $@

$(OBJDIR)/cellule.o : modele/cellule.c modele/cellule.h
	$(CC) -c -g modele/cellule.c $(CFLAGS) -o $@

$(OBJDIR)/foule.o : modele/foule.c modele/foule.h
	$(CC) -c -g modele/foule.c $(CFLAGS) -o $@

$(OBJDIR)/chaine.o : modele/chaine.c modele/chaine.h
	$(CC) -c -g modele/chaine.c $(CFLAGS) -o $@

$(OBJDIR)/humain.o : modele/humain.c modele/humain.h
	$(CC) -c -g modele/humain.c $(CFLAGS) -o $@

$(OBJDIR)/vecteur.o : modele/vecteur.c modele/vecteur.h
	$(CC) -c -g modele/vecteur.c $(CFLAGS) -o $@

clean :
	rm $(OBJDIR)/*.o

net : clean
	rm $(EXEC)

