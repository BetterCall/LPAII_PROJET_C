
#include "prototypes.h"

/**
*
*   PLAYER
*
**/

/**
*
*   GETTER/SETTER
*

GameObject *getPlayer(void){
	return &player;
}

**/
int getGameobjectX(GameObject entity){
	return entity.x;
}
int getGameobjectY(GameObject entity) {
	return entity.y;
}
int getGameobjectLife(GameObject entity) {
    return entity.life ;
}

int getGameobjectDir(GameObject entity) {
    return entity.direction ;
}


void setGameobjectX (GameObject entity,int valeur) {
	entity.x = valeur;
}
void setGameobjectY(GameObject entity, int valeur) {
	entity.y = valeur;
}
void setGameobjectLife(GameObject entity, int valeur) {
    entity.life = valeur ;
}
void setGameobjectIsAttacking(GameObject entity) {
    entity.isAttacking = !entity.isRunning ;
}

void killEntity(GameObject entity) {
    entity.timerMort = 1 ;
}

void entityHurts(GameObject entity ,GameObject *monster) {
    //entity == player
    if(entity.invincibleTimer == 0 ) {
        entity.life-- ;
        entity.invincibleTimer = 80 ;
        monster->timerMort = 1 ;
    }
}

void cleanGameobjectSprite(SDL_Texture *entityTexture) {
	if (entityTexture != NULL) {
		SDL_DestroyTexture(entityTexture);
		entityTexture = NULL;
	}
}

void initializeGameobject (
    GameObject *entity ,
    int type ,              //Joueur ou spell
    int life ,              //Joueur 3 spell 1
    int direction ,
    int dirX , int dirY ,
    int frameNumber ,       //Indique le numéro de la frame où commencer
    int frameMax ,
    int frameTimer,
    int x , int y ,         //position de depart
    int w , int h,          // Taille
    SDL_Point center
) {
    // SI l'entité est un joueur on initialise ses spells
    if (type == PLAYER || type == ENNEMY ) {
        //nombre de shuriken a 0
        //resetSpell() ;
    }
    //type de l'objet
    entity->type = type ; // voir define pour avoir les possibilités
    // a l'initialisation le joueur est immobile et les spell ne prenne que la qu'une rangée de sprite
    entity->etat = IDLE;
    // inutile pour les spell mais permet une uniformation des informations envoyées de joueur a joueur
    entity->isAttacking = 0 ;
	entity->life = life;
	//Timer d'invincibilité à 0
	entity->invincibleTimer = 0;
	//Indique l'état et la direction de notre héros
	entity->direction = direction;
	entity->dirX = dirX ;
	entity->dirY = dirY ;
    // A quelle frame commencer
	entity->frameNumber = frameNumber;
	//...la valeur de son chrono ou timer
	entity->frameTimer = frameTimer;
	// Le nombre de frame pour le sprite
	entity->frameMax = frameMax;
    // position en x et y de l'element
	entity->x = x ; // - getBeginX();
	entity->y = y ;//- getBeginY();
    // dimensions de l'element
	entity->w = w;
	entity->h = h;
	//Variables nécessaires au fonctionnement de la gestion des collisions
	entity->timerMort = 0;
	entity->isAttacking = 0 ;
	entity->isRunning = 0 ;
	entity->rotation = 0 ;
	entity->center = center ;
}


/**
*
*   int collide(GameObject *player , GameObject *monster)
*
*       @param GameObject *player
*       @param GameObject *monster
*       @return int
*
***/
// fonction collision
int collide(GameObject *player , GameObject *monster) {

    //On teste pour voir s'il n'y a pas collision, si c'est le cas, on ne fait rien
        if ((player->x >= monster->x + monster->w)
        || (player->x + player->w <= monster->x)
        || (player->y >= monster->y + monster->h)
        || (player->y + player->h <= monster->y)
        )
            return 0 ;

        else
            return 1 ;
}
