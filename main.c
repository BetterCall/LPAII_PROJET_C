
#include "prototypes.h"

/* Déclaration des variables / structures utilisées par le jeu */
Input input;



int main(int argc, char *argv[]) {

    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go =1 ;

    //initialisation des sockets
    WSADATA wsa;
    WSAStartup(
        MAKEWORD(2,2) , //transforme les deux entiers d'un octect en un seul de 2 octets
        &wsa
    ) ;

    // Initialisation de la SDL
    init("Projet LP AII SDL2");

    loadGame();
    // Initialisation du Joueur Principal
    //initializeEnnemy()

    atexit(cleanup);

    // Boucle du jeu
    while (go == 1) {

        //Gestion du clavier
        gestionInputs(&input);

        if(getOnMenu() == 3) {
            drawEndMenu();
        } else {

            // Mise a jour du jeu
            if (getOnMenu() == 0) {
                updatePlayer(&input);
                updateEnnemy();
                doSpell(PLAYER);
                doSpell(ENNEMY) ;

            } else {
                // Sinon on met a jour l'affichage du menu
                updateStartMenu(&input);
            }

            //Si on n'est pas dans un menu, on affiche le jeu
            if (getOnMenu() == 0){
                drawGame();
            } else {

                drawStartMenu();
                SDL_RenderPresent(getrenderer());
                SDL_Delay(1);

            }

            // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;
        }
    }




    // On quitte
    //exit(0);

    exit(0) ;
}

