//Rabidja 3 - nouvelle version intégralement en SDL 2.0
//Copyright / Droits d'auteur : www.meruvia.fr - Jérémie F. Bellanger

#ifndef PROTOTYPES
#define PROTOTYPES

#include "structs.h"

/* Catalogue des prototypes des fonctions utilisées.
   On le complétera au fur et à mesure. */

    /**
    *
    *   DRAW.C
    *   variables globales
    *       SDL_Texture *HUD_vie
    *
    **/
    extern void initHUD(void) ;
    extern void cleanHUD(void) ;
    extern void drawGame(void) ;
    extern void drawHUD(void) ;
    extern SDL_Texture *loadImage(char *name)  ;
    extern void drawImage(SDL_Texture *image, int x, int y) ;
    extern void drawImagePlus(SDL_Texture *image , int x , int y, double rotation , SDL_Point center, SDL_RendererFlip flip );
    extern void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy) ;
    extern void delay(unsigned int frameLimit) ;

    /**
    *
    *   FONT.C
    *
    **/
    extern void loadFont(char *name, int size) ;
    extern void closeFont() ;
    extern void drawString(char *text, int x, int y, int r, int g, int b, int a) ;

    /**
    *
    *   INIT.C
    *
    **/
    extern SDL_Renderer *getrenderer(void)  ;
    extern void init(char *title) ;
    extern void loadGame(void) ;
    extern void cleanup() ;

    /**
    *
    *   INPUT.C
    *
    **/
    extern void gestionInputs(Input *input) ;
    extern void getInput(Input *input) ;

    /**
    *
    *   MAP.C
    *
    **/
    extern int getStartX(void ) ;
    extern void setStartX(int valeur)  ;
    extern int getStartY(void) ;
    extern void setStartY(int valeur) ;
    extern int getMaxX(void) ;
    extern int getMaxY(void) ;
    extern int getBeginX(void) ;
    extern int getBeginY(void);
    extern int getTileValue(int x, int y) ;
    extern SDL_Texture *getBackground(void);
    extern void initMaps(void);
    extern void loadMap(char *name) ;
    extern void drawMap(int layer);
    extern void testDefilement(void);
    extern int mapCollisionMagic(GameObject *entity);
    extern void mapCollision(GameObject *entity);
    extern void changeLevel(void);
    extern void cleanMaps(void);

    /**
    *
    *   MENU.C
    *
    **/
    extern int getOnMenu(void) ;
    extern int getMenuType(void) ;
    extern void setOnMenu(int pOnMenu) ;
    extern void initMenus(void) ;
    extern void cleanMenus(void);
    extern void updateStartMenu(Input *input) ;
    extern void updatePauseMenu(Input *input) ;
    extern void drawStartMenu(void) ;
    extern void drawPauseMenu(void) ;

    /**
    *
    *   PLAYER.C
    *
    **/
    extern GameObject *getPlayer(void) ;
    extern int getPlayerx(void) ;
    extern void setPlayerx(int valeur) ;
    extern int getPlayery(void) ;
    extern void setPlayery(int valeur) ;
    extern int getLevel(void) ;
    extern void setPlayerIsAttacking(int valeur) ;
    extern void SetValeurDuNiveau(int valeur) ;
    extern int getPlayerDirection (void);
    extern int getLife(void) ;
    extern void killPlayer(void) ;
    extern void playerHurts(GameObject *monster) ;
    extern void initPlayerSprites(void);
    extern void initSwordSprites(void) ;
    extern void cleanPlayer(void) ;
    extern void initializePlayer() ;
    extern void updatePlayer(Input *input) ;
    extern void drawPlayer(void) ;
    extern void centerScrollingOnPlayer(void) ;

    /**
    *
    *   SWORD.C
    *
    **/
    extern void loadSwordImage(void) ;
    extern void cleanSwordImage(void) ;
    extern void resetSword(void) ;
    extern void createSword(void) ;
    extern void doSword(void) ;
    extern void drawSword(void) ;
    extern int swordCollide(GameObject *player) ;

    /**
    *
    *   SOCKET.C
    *
    **/

void* reception_message(void* data_Clt_in) ;
/*
	thread
	Fontion en attente de message
	affichage du message recu dans "boxAffichageMsg"

	Si le message recu = "closeSocket"
	Procedure de fermeture des autres sockets

*/
void* emission_message(void* data_Clt_out) ;
void* serveurEnAttente(void* data_Clt_out) ;
/*
	thread
	Fonction en attente de nouvelles connexions

	creation de la socket serveur

*/


	//Prototype de la fonction qui permet la creation des deux threads
	// thread d'ecoute en attente de nouveau message recu
	// thread d'envoie qui permet d'envoyer a l'autre poste un message
void* ouvertureCommunicationServeur(void* data_Srv);
void* ouvertureClient(void* data_Srv);
//creation thread de communication envoie / reception

void ouvertureCommunicationClient();

extern void onServer(void ) ;
extern void onClient() ;


#endif
