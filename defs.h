//Rabidja 3 - nouvelle version intégralement en SDL 2.0
//Copyright / Droits d'auteur : www.meruvia.fr - Jérémie F. Bellanger

#ifndef DEF_DEFS
    #define DEF_DEFS

    /**
    *
    *   Librairies standardes
    *
    **/
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    /**
    *
    *   SDL2 et Dependances
    *
    **/
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>

    /**
    *
    *   Informations Taille de la fenetre
    *
    **/
    #define SCREEN_WIDTH 800  //px
    #define SCREEN_HEIGHT 480 //px

    /**
    *
    *   Taille Max de la map
    *
    **/
    #define MAX_MAP_X 80 //tiles
    #define MAX_MAP_Y 80 //tiles

    #define TILE_SIZE 32

    /**
    *
    *   GAMEOBJECT
    *
    **/
    // Type de joueur
    #define PLAYER 0
    #define ENNEMY 1
    #define MAGIC  2
    #define SWORD  3

    #define TIME_BETWEEN_2_FRAMES 20
    #define TIME_BETWEEN_2_FRAMES_PLAYER 4
    #define TIME_BETWEEN_2_FRAMES_SWORD 1

    // Taille du joueur
    #define PLAYER_WIDTH 40
    #define PLAYER_HEIGTH 48

    #define PLAYER_SPEED 3

    //Valeurs attribuées aux états/directions
    #define IDLE 0
    #define WALK 1

    #define DEAD 4


    /**
    *
    *  direction
    *
    **/
    #define DOWN 0
    #define UP 1
    #define RIGHT 2
    #define LEFT 3

    /**
    *
    *   Taille de la camera
    *
    **/
    #define LIMITE_X 400
    #define LIMITE_Y 220
    #define LIMITE_W 100
    #define LIMITE_H 80


    /**
    *
    *   MAGIC.C
    *
    **/
    #define MAGIC_MAX   6
    #define MAGIC_SPEED 6

    #define LEVEL_MAX 5

    /**
    *
    *   CONTENU DES TILES
    *
    **/
    #define MUR   1
    #define SPE1  10
    #define SPE2  11
    #define SPE3  12
    #define SPE4  13
    #define SPE5  14
    #define SPE6  15
    #define SPE7  16
    #define SPE8  17
    #define SPE9  18
    #define SPE10 19

    #define TILE_MONSTRE 40
    #define TILE_MONSTRE_DEBUT 20
    #define TILE_MONSTRE_FIN 39

    /**
    *
    *   ENNEMY.C
    *
    **/
    #define ENNEMY_MAX    50
    #define ENNEMY_HEIGHT 48
    #define ENNEMY_WIDTH  40

    #define TIME_BETWEEN_2_SHOTS  30


    #define TILE_POWER_UP_COEUR 32

    #define START 0

    /**
    *
    *   SOCKET.C
    *
    **/
    // Gestion du temps
    #include <time.h>
    #define closesocket(param) close(param)
    #define PORT 4004
    #include <windows.h>

    #include <pthread.h>
    #include <winsock2.h>


    typedef int socklen_t ;


#endif
