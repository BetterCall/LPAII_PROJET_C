//Rabidja 3 - nouvelle version int�gralement en SDL 2.0
//Copyright / Droits d'auteur : www.meruvia.fr - J�r�mie F. Bellanger

#ifndef DEF_STRUCTS
    #define DEF_STRUCTS

    #include "defs.h"

    /* Structures qui seront utilis�es pour g�rer le jeu */

    // Structure pour g�rer l'input (clavier puis joystick)
    typedef struct Input {

        int left, right, up, down, jump, attack, run , magie, enter, erase, pause;

    } Input;

    // Structure pour g�rer la map � afficher
    typedef struct Map {

        SDL_Texture *background;
        SDL_Texture *tileSet, *tileSetB;

        //Num�ro du tileset � utiliser
        int tilesetAffiche;

        /* Coordonn�es de d�part du h�ros, lorsqu'il commence le niveau */
        int beginx, beginy;

        /* Coordonn�es de d�but, lorsqu'on doit dessiner la map */
        int startX, startY;

        /* Coordonn�es max de fin de la map */
        int maxX, maxY;

        /* Tableau � double dimension repr�sentant la map de tiles */
        int tile[MAX_MAP_Y][MAX_MAP_X];

        //Deuxi�me couche de tiles
        int tile2[MAX_MAP_Y][MAX_MAP_X];

        //Troisi�me couche de tiles
        int tile3[MAX_MAP_Y][MAX_MAP_X];

        // quatrieme couche pour les collision
        int tile4[MAX_MAP_Y][MAX_MAP_X];

        /* Timer et num�ro du tileset � afficher pour animer la map */
        int mapTimer, tileSetNumber;

        int level ;

        // variable pour testDefilement
        int testdefil ;

    } Map;

    // Structure pour g�rer nos sprites
    typedef struct GameObject {

        int type ;
        // Points de vie/sant� + chrono d'invicibilit�
        int life, invincibleTimer;
        // Coordonn�es du sprite
        int x, y;
        // Largeur, hauteur du sprite
        int h, w;
        // Variables utiles pour l'animation :
        // Num�ro de la frame (= image) en cours + timer
        int frameNumber, frameTimer, frameMax;
        // Nombre max de frames, �tat du sprite et direction
        //   dans laquelle il se d�place (gauche / droite)
        int etat, direction;
        int isRunning ;
        int isAttacking ;
        // Variables utiles pour la gestion des collisions :
        // chrono une fois mort
        int timerMort;
        //Vecteurs de d�placement temporaires avant d�tection
        //des collisions avec la map
        float dirX, dirY;
        int rotation ;
        SDL_Point center ;

        int spell;

    } GameObject;

    typedef struct Monster {

        // Points de vie/sant� + chrono d'invicibilit�
        float life ;
        int invincibleTimer;

        int type ;
        int isHurt ;
        int hurtDirection;

        // Coordonn�es du sprite
        int x, y;

        // Largeur, hauteur du sprite
        int h, w;

        // Checkpoint pour le h�ros (actif ou non)
        int checkpointActif;
        // + coordonn�es de respawn (r�apparition)
        int respawnX, respawnY;

        // Variables utiles pour l'animation :
        // Num�ro de la frame (= image) en cours + timer
        int frameNumber, frameTimer, frameMax;
        // Nombre max de frames, �tat du sprite et direction
        //   dans laquelle il se d�place (gauche / droite)
        int etat, direction;

        // timer pour IA
        int IATimer ;

        // Variables utiles pour la gestion des collisions :
        // chrono une fois mort
        int timerMort;
        //Vecteurs de d�placement temporaires avant d�tection
        //des collisions avec la map
        float dirX, dirY;
        //Sauvegarde des coordonn�es de d�part
        int saveX, saveY;


    } Monster;

#endif


