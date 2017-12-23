#include "../controle/principale.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    
    controleurT controleur;

	controleurInitialisation(&controleur);

	controleurSimulation(&controleur);

	controleurDestruction(&controleur);

    return 0;
}
