
#include "prototypes.h"

int nombreSpellPlayer = 0 ;
int nombreSpellEnnemy = 0 ;
GameObject spellPlayer[10];
GameObject spellEnnemy[10];
SDL_Texture *SpellSprite;

SDL_Texture *getSpellSprite(void) {
    return &SpellSprite ;
}

/**
*
*   void loadShurikenImage(void)
*       Charge le sprite
*
**/
void loadSpellImage(void) {
    SpellSprite = loadImage("graphics/magic.png");
}

/**
*
*   void cleanShurikenImage(void)
*       Detruit la texture et passe le pointer a NULL
*
**/
void cleanSpellImage(void) {
    if (SpellSprite != NULL)
        SDL_DestroyTexture(SpellSprite);
}

/**
*
*   int getShurikenNumber(void)
*
*       @return int
**/
int getSpellNumberPlayer(void) {
    return nombreSpellPlayer;
}

/**
*
*   void resetShuriken(void)
*
**/
void resetSpell(void) {
    nombreSpellPlayer = 0;
    nombreSpellEnnemy = 0;
}

/**
*
*   void createShuriken(void)
*
*
**/
void createSpell(GameObject entity , int type) {

    if(type == PLAYER) {
        /* Si on peut créer un shuriken, on le crée */
        if (nombreSpellPlayer < MAGIC_MAX) {
            //On enregistre la taille de l'image
            SDL_QueryTexture(
                SpellSprite,
                NULL,
                NULL,
                &spellPlayer[nombreSpellPlayer].w,
                &spellPlayer[nombreSpellPlayer].h
            );

            //Rotation en SDL2
            spellPlayer[nombreSpellPlayer].rotation = 0;
            //Centre du shuriken pour la rotation (le sprite fait 20 x 20 pixels)
            spellPlayer[nombreSpellPlayer].center.x = 10;
            spellPlayer[nombreSpellPlayer].center.y = 10;
            spellPlayer[nombreSpellPlayer].h = 20;
            spellPlayer[nombreSpellPlayer].w = 20;

            spellPlayer[nombreSpellPlayer].dirX = spellPlayer[nombreSpellPlayer].dirY = 0 ;

            /* Direction du shuriken
            Les valeurs sont proportionnelles au perso - à adpater
            manuellement selon les cas :) */
            if ( entity.direction == RIGHT) {
                spellPlayer[nombreSpellPlayer].x = entity.x + PLAYER_WIDTH +5;
                spellPlayer[nombreSpellPlayer].y = entity.y + PLAYER_HEIGTH/2;
                spellPlayer[nombreSpellPlayer].direction = RIGHT;
                spellPlayer[nombreSpellPlayer].dirX += MAGIC_SPEED ;

            } else  if (entity.direction == LEFT) {
                spellPlayer[nombreSpellPlayer].x = entity.x - 5;
                spellPlayer[nombreSpellPlayer].y = entity.y + PLAYER_HEIGTH/2;
                spellPlayer[nombreSpellPlayer].direction = LEFT;
                spellPlayer[nombreSpellPlayer].dirX -= MAGIC_SPEED ;
            } else  if (entity.direction == UP) {
                spellPlayer[nombreSpellPlayer].x = entity.x + 10;
                spellPlayer[nombreSpellPlayer].y = entity.y - PLAYER_HEIGTH / 2  - 5;
                spellPlayer[nombreSpellPlayer].direction = UP ;
                spellPlayer[nombreSpellPlayer].dirY -= MAGIC_SPEED ;
            } else {
                spellPlayer[nombreSpellPlayer].x = entity.x + PLAYER_WIDTH/2;
                spellPlayer[nombreSpellPlayer].y = entity.y + PLAYER_HEIGTH + 5;
                spellPlayer[nombreSpellPlayer].direction = DOWN ;
                spellPlayer[nombreSpellPlayer].dirY += MAGIC_SPEED ;
            }
            nombreSpellPlayer++;
        }
    }
    else if (type == ENNEMY ) {
        if (nombreSpellEnnemy < MAGIC_MAX) {
            //On enregistre la taille de l'image
            SDL_QueryTexture(
                SpellSprite,
                NULL,
                NULL,
                &spellEnnemy[nombreSpellEnnemy].w,
                &spellEnnemy[nombreSpellEnnemy].h
            );

            //Rotation en SDL2
            spellEnnemy[nombreSpellEnnemy].rotation = 0;
            //Centre du shuriken pour la rotation (le sprite fait 20 x 20 pixels)
            spellEnnemy[nombreSpellEnnemy].center.x = 10;
            spellEnnemy[nombreSpellEnnemy].center.y = 10;
            spellEnnemy[nombreSpellEnnemy].h = 20;
            spellEnnemy[nombreSpellEnnemy].w = 20;

            spellEnnemy[nombreSpellEnnemy].dirX = spellEnnemy[nombreSpellEnnemy].dirY = 0 ;

            /* Direction du shuriken
            Les valeurs sont proportionnelles au perso - à adpater
            manuellement selon les cas :) */
            if ( entity.direction == RIGHT) {
                spellEnnemy[nombreSpellEnnemy].x = entity.x + PLAYER_WIDTH + 5;
                spellEnnemy[nombreSpellEnnemy].y = entity.y + PLAYER_HEIGTH/2;
                spellEnnemy[nombreSpellEnnemy].direction = RIGHT;
                spellEnnemy[nombreSpellEnnemy].dirX += MAGIC_SPEED ;

            } else  if (entity.direction == LEFT) {
                spellEnnemy[nombreSpellEnnemy].x = entity.x - 5;
                spellEnnemy[nombreSpellEnnemy].y = entity.y + PLAYER_WIDTH/2;
                spellEnnemy[nombreSpellEnnemy].direction = LEFT;
                spellEnnemy[nombreSpellEnnemy].dirX -= MAGIC_SPEED ;
            } else  if (entity.direction == UP) {
                spellEnnemy[nombreSpellEnnemy].x = entity.x + PLAYER_WIDTH/2;
                spellEnnemy[nombreSpellEnnemy].y = entity.y - PLAYER_HEIGTH - 5 ;
                spellEnnemy[nombreSpellEnnemy].direction = UP ;
                spellEnnemy[nombreSpellEnnemy].dirY -= MAGIC_SPEED ;
            } else {
                spellEnnemy[nombreSpellEnnemy].x = entity.x + PLAYER_WIDTH/2;
                spellEnnemy[nombreSpellEnnemy].y = entity.y + PLAYER_HEIGTH + 5;
                spellEnnemy[nombreSpellEnnemy].direction = DOWN ;
                spellEnnemy[nombreSpellEnnemy].dirY += MAGIC_SPEED ;
            }
            nombreSpellEnnemy++;
        }
    }
}

/**
*
*   void doShuriken(void)
*
**/
void doSpell(int type) {

    int i;

    if ( type == PLAYER) {
         //On passe en boucle tous les shurikens ;)
        for (i = 0; i < nombreSpellPlayer; i++) {

            if(mapCollisionMagic(&spellPlayer[i])) {
                spellPlayer[i] = spellPlayer[nombreSpellPlayer - 1];
                nombreSpellPlayer--;
            }

            //On fait tourner le shuriken en SDL2
            spellPlayer[i].rotation += 20;
            if (spellPlayer[i].rotation >= 360)
                spellPlayer[i].rotation = 0;

             /* S'il sort de l'écran, on supprime le shuriken */
            if (spellPlayer[i].x < getStartX() || spellPlayer[i].x > getStartX() + SCREEN_WIDTH ||
                spellPlayer[i].y < getStartY() || spellPlayer[i].y > getStartY() + SCREEN_HEIGHT ) {
                spellPlayer[i] = spellPlayer[nombreSpellPlayer - 1];
                nombreSpellPlayer--;
            }
        }
    } else if (type == ENNEMY ) {

             //On passe en boucle tous les shurikens ;)
        for (i = 0; i < nombreSpellEnnemy; i++) {

            if(mapCollisionMagic(&spellEnnemy[i])) {
                spellEnnemy[i] = spellEnnemy[nombreSpellEnnemy - 1];
                nombreSpellEnnemy--;
            }
            //On fait tourner le shuriken en SDL2
            spellEnnemy[i].rotation += 20;
            if (spellEnnemy[i].rotation >= 360)
                spellEnnemy[i].rotation = 0;

             /* S'il sort de l'écran, on supprime le shuriken */
            if (spellEnnemy[i].x < getStartX() || spellEnnemy[i].x > getStartX() + SCREEN_WIDTH ||
                spellEnnemy[i].y < getStartY() || spellEnnemy[i].y > getStartY() + SCREEN_HEIGHT ) {
                spellEnnemy[i] = spellEnnemy[nombreSpellEnnemy - 1];
                nombreSpellEnnemy--;
            }
        }
    }
}

/**
*
*   void drawShuriken(void)
*
**/
void drawSpell(void) {

    int i;

    //On affiche tous les shurikens
    for (i = 0; i < nombreSpellPlayer; i++) {

        drawImagePlus (
            SpellSprite,
            spellPlayer[i].x - getStartX(),
            spellPlayer[i].y - getStartY(),
            spellPlayer[i].rotation,
            spellPlayer[i].center,
            SDL_FLIP_NONE
        );
    }
     //On affiche tous les shurikens
    for (i = 0; i < nombreSpellEnnemy; i++) {

        drawImagePlus (
            SpellSprite,
            spellEnnemy[i].x - getStartX(),
            spellEnnemy[i].y - getStartY(),
            spellEnnemy[i].rotation,
            spellEnnemy[i].center,
            SDL_FLIP_NONE
        );
    }

}

/**
*
*   int shurikenCollide(GameObject *player)
*
*       @param GameObject *player
*       @return int
*
**/
// Test de collision monstre-shuriken
int spellCollide() {

    int i , j ;
    int collision = 0;

    for (i = 0; i < nombreSpellPlayer; i++) {

        if(collide( &spellPlayer[i] , getEnnemy() ) ) {

            spellPlayer[i] = spellPlayer[nombreSpellPlayer - 1];
            nombreSpellPlayer--;

            if(getEnnemyLife() < 1) {
                setOnMenu(3) ;
            }
           collision = 1 ;
        }
    }
    for (i = 0; i < nombreSpellEnnemy; i++) {

        if(collide( &spellEnnemy[i] , getPlayer() ) ) {

            spellEnnemy[i] = spellEnnemy[nombreSpellEnnemy - 1];
            nombreSpellEnnemy--;

            if(getPlayerLife() >= 1) {
                setPlayerLife( getPlayerLife() -1 )  ;
            } else {
                setOnMenu(3) ;
           }
           collision = 1 ;
        }
    }


    //On renvoie la valeur de collision à la fin
    return collision;
}


