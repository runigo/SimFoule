#include "../modele/cellule.h"

double celluleInitialise(celluleT * cellule)
	{
	(void)cellule;
	printf("celluleInitialise");
	return 0;
	}

int celluleCreationMur(celluleT * cellule, int X, int Y)
	{
	(void)cellule;
	(void)X;
	(void)Y;
	return 0;
	}

int celluleCreationSortie(celluleT * cellule, int X, int Y)
	{
	(void)cellule;
	(void)X;
	(void)Y;
	return 0;
	}

bool celluleMur(celluleT * cellule, int X, int Y)
	{
	(void)cellule;
	(void)X;
	(void)Y;
	return false;
	}

bool celluleSortie(celluleT * cellule, int X, int Y)
	{
	(void)cellule;
	(void)X;
	(void)Y;
	return true;
	}

