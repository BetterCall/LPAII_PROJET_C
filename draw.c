//Rabidja 3 - nouvelle version intégralement en SDL 2.0
//Copyright / Droits d'auteur : www.meruvia.fr - Jérémie F. Bellanger


#include "prototypes.h"

//HUD
SDL_Texture *HUD_vie ;
int end = 0 ;

int getEnd (void) {
    return end ;
}
void setEnd(int pEnd) {
    end = pEnd ;
}

/**
*
*   void initHUD(void)
*       charge la texture HUD_vie a partir de son image
*
**/
void initHUD(void) {
    HUD_vie = loadImage("graphics/life.png") ;
}
/**
*
*   void cleanHUD(void)(void)
*       detruit la texture HUD_vie, passe le pointer a NULL
*
**/
void cleanHUD(void) {


    if(HUD_vie != NULL) {
        SDL_DestroyTexture(HUD_vie) ;
        HUD_vie = NULL ;
    }
}
/**
*
*   void drawHUD(void)
*       affiche le HUD (point de vie sur la couche superieur)
*
**/
void drawHUD(void) {

    // variable qui contiendra le texte
    char text[200] ;

    int i ;


    //affiche le nb de vie en bas a droite s'adapte a l'ecran
    drawImage (
        HUD_vie,
        SCREEN_WIDTH -120 ,
        SCREEN_HEIGHT - 60
    );

    sprintf (
        text,
        "X %d" ,
        getPlayerLife()
    );

    drawString (
        text ,
        SCREEN_WIDTH - 80 ,
        SCREEN_HEIGHT - 60 ,
        0,0,0,
        255
    ) ;
    drawString (
        text ,
        SCREEN_WIDTH - 82 ,
        SCREEN_HEIGHT - 62 ,
        255,255,255,
        255
    ) ;


}

void drawEndMenu(void) {

    char text2[200] ;

    if(getPlayerLife()>0 && getEnnemyLife() == 0 ) {
        sprintf(text2 , "VOUS AVEZ GAGNE !") ;
        setOnMenu(3) ;
    } else if ( getPlayerLife() == 0 ) {
        sprintf(text2 , "VOUS AVEZ PERDU !") ;
        setOnMenu(3) ;
    } else {
        sprintf(text2, " ") ;
    }

    drawString(text2, 270, 150, 0, 0, 0, 255);
    drawString(text2, 272, 152, 255, 255, 255, 255);

}


/**
*
*   void drawGame(void)
*
**/
void drawGame(void) {

    int i ;

	// Affiche le fond (background) aux coordonnées (0,0)
	drawImage(getBackground(), 0, 0);

	/* Affiche la map de tiles : layer 2 (couche du fond) */
	drawMap(2);

	/* Affiche la map de tiles : layer 1 (couche active : sol, etc.)*/
	drawMap(1);
    drawEndMenu() ;
	/* Affiche le joueur */
	drawPlayer() ;
    drawEnnemy() ;

    //Affiche les shuriken
    drawSpell();

	/* Affiche la map de tiles : layer 3 (couche en foreground / devant) */
	drawMap(3);

	drawHUD() ;


	// Affiche l'écran
	SDL_RenderPresent(getrenderer());

    // Délai pour laisser respirer le proc
    SDL_Delay(1);
}


/**
*
*   SDL_Texture *loadImage(char *name)
*       DESCRIPTION
*       @param char* adresse de l'image
*       @return SDL_Texture
*
**/
SDL_Texture *loadImage(char *name) {

	/* Charge les images avec SDL Image dans une SDL_Surface */
	SDL_Surface *loadedImage = NULL;
	SDL_Texture *texture = NULL;
	loadedImage = IMG_Load(name);

	if (loadedImage != NULL) {
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(getrenderer(), loadedImage);
		// On se débarrasse du pointeur vers une surface
		SDL_FreeSurface(loadedImage);
		loadedImage = NULL;
	}
	else
		printf("L'image n'a pas pu être chargée! SDL_Error :  %s\n", SDL_GetError());

	return texture;
}

/**
*
*   void drawImage(SDL_Texture *image, int x, int y)
*       DESCRIPTION
*       @param SDL_Texture *image
*       @param int x
*       @param int y
*
**/
void drawImage(SDL_Texture *image, int x, int y) {

	SDL_Rect dest;

	/* Règle le rectangle à dessiner selon la taille de l'image source */
	dest.x = x;
	dest.y = y;

	/* Dessine l'image entière sur l'écran aux coordonnées x et y */
	SDL_QueryTexture(
        image,
        NULL,
        NULL,
        &dest.w,
        &dest.h
    );
	SDL_RenderCopy (
        getrenderer(),
        image,
        NULL,
        &dest
    );
}

/**
*
*   void drawImagePlus(SDL_Texture *image , int x , int y, double rotation , SDL_Point center, SDL_RendererFlip flip )
*       DESCRIPTION
*       @param SDL_Texture *image
*       @param int x
*       @param double rotation
*       @param SDL_Point center
*       @param SDL_RendererFlip film
*
**/
void drawImagePlus(SDL_Texture *image , int x , int y, double rotation , SDL_Point center, SDL_RendererFlip flip ) {

    //fonction SDL 2 permettant de gere le flip et les rotations
    SDL_Rect dest ;
    dest.x = x ;
    dest.y = y ;

    // dessine l'image aux coordonnée x y
    SDL_QueryTexture (
        image,
        NULL,
        NULL,
        &dest.w,
        &dest.h
    );
    SDL_RenderCopyEx (
        getrenderer(),
        image,
        NULL ,
        &dest ,
        rotation,
        &center ,
        flip
    );
}

/**
*
*   void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy)
*       DESCRIPTION
*       @param SDL_Texture *image
*       @param int destx
*       @param int desty
*       @param int srcx
*       @param int srcy
*
**/
void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy){
	/* Rectangle de destination à dessiner */
	SDL_Rect dest;

	dest.x = destx;
	dest.y = desty;
	dest.w = TILE_SIZE;
	dest.h = TILE_SIZE;

	/* Rectangle source */
	SDL_Rect src;

	src.x = srcx;
	src.y = srcy;
	src.w = TILE_SIZE;
	src.h = TILE_SIZE;

	/* Dessine la tile choisie sur l'écran aux coordonnées x et y */
	SDL_RenderCopy(
        getrenderer(),
        image,
        &src,
        &dest
    );
}

/**
*
*   void delay(unsigned int frameLimit)
*       DESCRIPTION
*       @param unsigned int frameLimit
*
**/
void delay(unsigned int frameLimit) {

	// Gestion des 60 fps (images/stories/seconde)
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
		return;

	if (frameLimit > ticks + 16)
		SDL_Delay(16);
	else
		SDL_Delay(frameLimit - ticks);
}

