#include "prototypes.h"

GameObject sword;
SDL_Texture *swordSpriteSheet;

void loadSwordImage(void) {
    swordSpriteSheet = loadImage("graphics/sword.png");
}

void cleanSwordImage(void) {
    if (swordSpriteSheet != NULL)
        SDL_DestroyTexture(swordSpriteSheet);
}

void resetSword(void) {
    //nombreShuriken = 0;
}

void createSword(void) {

    //On enregistre la taille de l'image
    SDL_QueryTexture(
        swordSpriteSheet,
        NULL,
        NULL,
        &sword.w,
        &sword.h
    );

    //Rotation en SDL2
    sword.rotation = 0;
    //Centre du shuriken pour la rotation (le sprite fait 20 x 20 pixels)
    sword.center.x = 10;
    sword.center.y = 10;

    /* Direction du shuriken
    Les valeurs sont proportionnelles au perso - à adpater
    manuellement selon les cas :) */
    if (getPlayerDirection() == RIGHT) {
        sword.x = getPlayerx() ;// + 15;
        sword.y = getPlayery() ;//+ 20;
        sword.rotation = 180 ;
        sword.direction = RIGHT;
    } else  if (getPlayerDirection() == LEFT) {
        sword.x = getPlayerx() ;// - 15;
        sword.y = getPlayery() ;// + 20;
        sword.direction = LEFT;
        sword.rotation = 45 ;
    } else  if (getPlayerDirection() == UP) {
        sword.x = getPlayerx() ;//:+ 10;
        sword.y = getPlayery() ;
        sword.direction = UP ;
        sword.rotation = 90 ;
    } else {
        sword.x = getPlayerx() ;//+ 10;
        sword.y = getPlayery() ;//+ PLAYER_HEIGTH;
        sword.direction = DOWN ;
        sword.rotation = 0 ;
    }
}

int rotaTest = 90 ;
void doSword(void) {

    for(rotaTest ; rotaTest <= 0 ; rotaTest-=10) {
    if(getPlayerDirection() == DOWN ) {

        sword.x = getPlayerx() + PLAYER_WIDTH/2 ;// -getStartX() ;
        sword.y = getPlayery() + PLAYER_HEIGTH ;//² -getStartY() ;
        sword.rotation += 10 ;
    } else if (getPlayerDirection() == UP) {
        sword.x = getPlayerx() + PLAYER_WIDTH/2 ;//  - getStartX() ;
        sword.y = getPlayery() ;//  - getStartY() ;
        sword.rotation -= 10 ;
    } else if (getPlayerDirection() == RIGHT) {
        sword.x = getPlayerx() +PLAYER_WIDTH  ;// - getStartX() ;
        sword.y = getPlayery()  +PLAYER_HEIGTH /2;// - getStartY() ;
        sword.rotation -= 10 ;
    } else if (getPlayerDirection() == LEFT) {
        sword.x = getPlayerx() ;// - getStartX() ;
        sword.y = getPlayery() +PLAYER_HEIGTH/2 ;// - getStartY() ;
        sword.rotation += 10 ;
    }
    //rotaTest += 10;
    //On fait tourner le shuriken en SDL2
    //sword.rotation += 10;
    SDL_Delay(TIME_BETWEEN_2_FRAMES_SWORD);
   // if (rotaTest >= 80) {
     //   rotaTest = 0;
    //}
    }
    rotaTest = 90 ;
}

void drawSword(void) {

    drawImagePlus (
        swordSpriteSheet,
        sword.x - getStartX(),
        sword.y - getStartY(),
        sword.rotation,
        sword.center,
        SDL_FLIP_NONE
    );

}

// Test de collision monstre-shuriken
int swordCollide(GameObject *player) {

    int collision = 0;

        //On teste pour voir s'il n'y a pas collision, si c'est le cas, on ne fait rien
        if ((player->x >= sword.x + sword.w)
        || (player->x + player->w <= sword.x)
        || (player->y >= player->y + sword.h)
        || (player->y + player->h <= sword.y)
        )
        ;
        //Sinon, il y a collision.
        else {
            //On passe collision à 1
            collision = 1;
        }
    //On renvoie la valeur de collision à la fin
    return collision;
}


