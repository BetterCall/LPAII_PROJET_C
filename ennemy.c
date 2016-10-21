
#include "prototypes.h"

GameObject ennemy ;
SDL_Texture *EnnemySprite ;

/**
*
*   GameObject *getEnemy()
*
*       @return GameObject
*
**/
GameObject *getEnnemy() {
    return &ennemy;
}

void setEnnemy(GameObject pEnnemy) {
    ennemy = pEnnemy ;
}

/**
*
*   void initEnnemySprite(void)
*
**/
void loadEnnemyImage(void) {
    EnnemySprite = loadImage("graphics/rabidja.png");
}

/**
*
*   void playerHurts(GameObject *monster)
*
*       @param GameObject *monster
*
**/
void playerHurts(GameObject *ennemy) {

    if(ennemy->invincibleTimer == 0 ) {
        ennemy->life-- ;
        ennemy->invincibleTimer = 80 ;
    }
}
void ennemyHurts(GameObject *ennemy) {

    if(ennemy->invincibleTimer == 0 ) {
        ennemy->life-- ;
        ennemy->invincibleTimer = 80 ;
    }
}
int initEnnemySprite(void) {
    EnnemySprite = loadImage("graphics/rabidja.png") ;
}

/**
*
*   void cleanMonsters(void)
*
*
**/
void cleanEnnemy(void) {
    if (EnnemySprite != NULL){
        SDL_DestroyTexture(EnnemySprite) ;
        EnnemySprite = NULL ;
    }
}

int getEnnemyLife() {
    return ennemy.life ;
}
void setEnnemyLife(int pLife) {
    ennemy.life = pLife ;
}
/**
*
*   void initializeNewMonster(int x , int y)
*
*       @param int x
*       @param int y
*
**/
void initializeEnnemy(int x , int y) {

    ennemy.frameNumber = 0 ;
    ennemy.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER ;

    ennemy.direction = LEFT ;

    ennemy.x = x ;
    ennemy.y = y ;

    ennemy.w = ENNEMY_WIDTH ;
    ennemy.h = ENNEMY_HEIGHT ;

    ennemy.timerMort = 0 ;

    ennemy.life = 3 ;

}

void killEnnemy() {
    //Affiche you win
    cleanEnnemy() ;
    drawEndMenu() ;
}

/**
*
*   vo id updateMonster(Input *input)
*
*       @param Input *input
*
**/

void updateEnnemy() {

    if (ennemy.life < 1) {
        drawEndMenu() ;
    }

    if(ennemy.timerMort == 0) {
        ennemy.dirX = 0 ;
        ennemy.dirY = 0 ;

        //deplacement
        if( ennemy.direction == UP)
            ennemy.dirY -= PLAYER_SPEED;
        else if( ennemy.direction == DOWN)
            ennemy.dirY += PLAYER_SPEED;
        else if( ennemy.direction == LEFT)
            ennemy.dirX -= PLAYER_SPEED;
        else if( ennemy.direction == RIGHT)
            ennemy.dirX += PLAYER_SPEED ;
    }
    if(ennemy.timerMort > 0 ) {
        ennemy.timerMort-- ;
    }

}

/**
*
*   void drawEnnemy ()
*
**/

void drawEnnemy(void) {

	/* Gestion du timer */
	// Si notre timer (un compte à rebours en fait) arrive à zéro
	if (ennemy.frameTimer <= 0){

		//On le réinitialise
		ennemy.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

		//Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
		ennemy.frameNumber++;

		//Mais si on dépasse la frame max, il faut revenir à la première :
		if (ennemy.frameNumber >= ennemy.frameMax)
			ennemy.frameNumber = 0;

	}
	//Sinon, on décrémente notre timer
	else {
        if(ennemy.etat != IDLE)
            ennemy.frameTimer -= 1 + (ennemy.isRunning * 2 ) ;
        else
            ennemy.frameTimer-- ;
	}


	//Ensuite, on peut passer la main à notre fonction

	/* Rectangle de destination à dessiner */
	SDL_Rect dest;

	// On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle
	//au scrolling :
	dest.x = ennemy.x - getStartX();
	dest.y = ennemy.y - getStartY();
	dest.w = ennemy.w;
	dest.h = ennemy.h;

	/* Rectangle source */
	SDL_Rect src;

	//Pour connaître le X de la bonne frame à dessiner, il suffit de multiplier
	//la largeur du sprite par le numéro de la frame à afficher -> 0 = 0; 1 = 40; 2 = 80...
	src.x = ennemy.frameNumber * ennemy.w;
    src.y = ennemy.etat * 3 * ennemy.h ;
    /*
        if ( player.direction == LEFT )
            player.directionn = RIGHT // On retournera le sprite
        else
            player.direction = player.direction
    */
    src.y += (( ennemy.direction == LEFT ? RIGHT : ennemy.direction ))*ennemy.h  ;
    src.y += ennemy.isAttacking * 6 * ennemy.h ;

	src.w = ennemy.w ;
	src.h = ennemy.h ;

    // Si le joeur a ete touche on le fait clignoter
    if(ennemy.invincibleTimer > 0) {

        if( !(ennemy.frameNumber % 2) ) {

            if(ennemy.direction == LEFT) {

                SDL_RenderCopyEx(
                    getrenderer(),
                    EnnemySprite,
                    &src,
                    &dest,
                    0,
                    0,
                    SDL_FLIP_NONE
                );
            } else {
                SDL_RenderCopyEx(
                    getrenderer(),
                    EnnemySprite,
                    &src, &dest,
                    0, 0,
                    SDL_FLIP_HORIZONTAL
                );
            }
        }
    } else {

        if(ennemy.direction == LEFT) {
            SDL_RenderCopyEx(
                getrenderer(),
                EnnemySprite,
                &src,
                &dest,
                0,
                0,
                SDL_FLIP_NONE
            );
        } else {
            SDL_RenderCopyEx(
                getrenderer(),
                EnnemySprite,
                &src,
                &dest,
                0,
                0,
                SDL_FLIP_HORIZONTAL
            );
        }
    }
}

