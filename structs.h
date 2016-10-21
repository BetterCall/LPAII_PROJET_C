//Rabidja 3 - nouvelle version intégralement en SDL 2.0
//Copyright / Droits d'auteur : www.meruvia.fr - Jérémie F. Bellanger

#ifndef DEF_STRUCTS
    #define DEF_STRUCTS

    #include "defs.h"

    /* Structures qui seront utilisées pour gérer le jeu */

    // Structure pour gérer l'input (clavier puis joystick)
    typedef struct Input {

        int left, right, up, down, jump, attack, run , magie, enter, erase, pause;

    } Input;

    // Structure pour gérer la map à afficher
    typedef struct Map {

        SDL_Texture *background;
        SDL_Texture *tileSet, *tileSetB;

        //Numéro du tileset à utiliser
        int tilesetAffiche;

        /* Coordonnées de départ du héros, lorsqu'il commence le niveau */
        int beginx, beginy;

        /* Coordonnées de début, lorsqu'on doit dessiner la map */
        int startX, startY;

        /* Coordonnées max de fin de la map */
        int maxX, maxY;

        /* Tableau à double dimension représentant la map de tiles */
        int tile[MAX_MAP_Y][MAX_MAP_X];

        //Deuxième couche de tiles
        int tile2[MAX_MAP_Y][MAX_MAP_X];

        //Troisième couche de tiles
        int tile3[MAX_MAP_Y][MAX_MAP_X];

        // quatrieme couche pour les collision
        int tile4[MAX_MAP_Y][MAX_MAP_X];

        /* Timer et numéro du tileset à afficher pour animer la map */
        int mapTimer, tileSetNumber;

        int level ;

        // variable pour testDefilement
        int testdefil ;

    } Map;

    // Structure pour gérer nos sprites
    typedef struct GameObject {

        int type ;
        // Points de vie/santé + chrono d'invicibilité
        int life, invincibleTimer;
        // Coordonnées du sprite
        int x, y;
        // Largeur, hauteur du sprite
        int h, w;
        // Variables utiles pour l'animation :
        // Numéro de la frame (= image) en cours + timer
        int frameNumber, frameTimer, frameMax;
        // Nombre max de frames, état du sprite et direction
        //   dans laquelle il se déplace (gauche / droite)
        int etat, direction;
        int isRunning ;
        int isAttacking ;
        // Variables utiles pour la gestion des collisions :
        // chrono une fois mort
        int timerMort;
        //Vecteurs de déplacement temporaires avant détection
        //des collisions avec la map
        float dirX, dirY;
        int rotation ;
        SDL_Point center ;

        int spell;

    } GameObject;

    typedef struct Monster {

        // Points de vie/santé + chrono d'invicibilité
        float life ;
        int invincibleTimer;

        int type ;
        int isHurt ;
        int hurtDirection;

        // Coordonnées du sprite
        int x, y;

        // Largeur, hauteur du sprite
        int h, w;

        // Checkpoint pour le héros (actif ou non)
        int checkpointActif;
        // + coordonnées de respawn (réapparition)
        int respawnX, respawnY;

        // Variables utiles pour l'animation :
        // Numéro de la frame (= image) en cours + timer
        int frameNumber, frameTimer, frameMax;
        // Nombre max de frames, état du sprite et direction
        //   dans laquelle il se déplace (gauche / droite)
        int etat, direction;

        // timer pour IA
        int IATimer ;

        // Variables utiles pour la gestion des collisions :
        // chrono une fois mort
        int timerMort;
        //Vecteurs de déplacement temporaires avant détection
        //des collisions avec la map
        float dirX, dirY;
        //Sauvegarde des coordonnées de départ
        int saveX, saveY;


    } Monster;

#endif


