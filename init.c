//Rabidja 3 - nouvelle version intégralement en SDL 2.0
//Copyright / Droits d'auteur : www.meruvia.fr - Jérémie F. Bellanger

#include "prototypes.h"

SDL_Window *screen;
SDL_Renderer *renderer;
Mix_Music *myMus ;

/**
*
*   SDL_Renderer *getrenderer(void)
*
*       @return SDL_Renderer
*
**/
SDL_Renderer *getrenderer(void) {
	return renderer;
}

/**
*
*   void init(char *title)
*
*       @param char *title
*
**/
void init(char *title) {

	/* On crée la fenêtre, représentée par le pointeur jeu.window en utilisant la largeur et la
	hauteur définies dans les defines (defs.h).
	Nouveautés SDL2 : on peut centrer la fenêtre avec SDL_WINDOWPOS_CENTERED, et choisir la taille
	de la fenêtre, pour que la carte graphique l'agrandisse automatiquement. Notez aussi qu'on peut
	maintenant créer plusieurs fenêtres. */

	screen = SDL_CreateWindow(
                title,
		        SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
             );

	//On crée un renderer pour la SDL et on active la synchro verticale : VSYNC
	renderer = SDL_CreateRenderer (
                    screen,
                    -1,
                    SDL_RENDERER_PRESENTVSYNC
                );

	// Si on n'y arrive pas, on quitte en enregistrant l'erreur dans stdout.txt
    if (screen == NULL || renderer == NULL) {
        printf (
            "Impossible d'initialiser le mode écran à %d x %d: %s\n",
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_GetError()
        );
        exit(1);
    }

	//Initialisation du chargement des images png avec SDL_Image 2
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf (
            "SDL_image n'a pu être initialisée! SDL_image Error: %s\n",
            IMG_GetError()
        );
		exit(1);
	}

	//On cache le curseur de la souris
	SDL_ShowCursor(SDL_DISABLE);

	//On initialise SDL_TTF 2 qui gérera l'écriture de texte
	if (TTF_Init() < 0) {
		printf (
            "Impossible d'initialiser SDL TTF: %s\n",
            TTF_GetError()
        );
		exit(1);
	}

	/* Chargement de la police */
    loadFont (
        "font/GenBasB.ttf",
        32
    );

	//On initialise SDL_Mixer 2, qui gérera la musique et les effets sonores
	int flags = MIX_INIT_MP3;
	int initted = Mix_Init(flags);
	if ((initted & flags) != flags) {

		printf(
            "Mix_Init: Failed to init SDL_Mixer\n"
        );
		printf (
            "Mix_Init: %s\n",
            Mix_GetError()
        );
		exit(1);
	}

	/* Open 44.1KHz, signed 16bit, system byte order,
	stereo audio, using 1024 byte chunks (voir la doc pour plus d'infos ;) ) */
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf (
            "Mix_OpenAudio: %s\n",
            Mix_GetError()
        );
		exit(1);
	} else {
        myMus = Mix_LoadMUS("musics/1.mid");

        /* On lance la musique */
        Mix_PlayMusic(myMus, 1);
    }
	// Définit le nombre de pistes audio (channels) à mixer
	Mix_AllocateChannels(32);
}

/**
*
*   void loadGame(void)
*
*
**/
void loadGame(void){

	//On charge les données pour la map
	initMaps();
	//On charge les feuilles de sprites (spritesheet)
	loadPlayerImage() ;
	loadSpellImage() ;
	loadEnnemyImage() ;
	//On commence au premier niveau
	changeLevel();
	// chargement du hud
	initHUD() ;

	setOnMenu(1) ;
}

/**
*
*   void cleanup(void)
*
*
**/
void cleanup(void) {
	//Nettoie les sprites de la map
	cleanMaps();
	cleanMenus() ;

    /* Libère le sprite du héros */
	cleanPlayer();
	cleanEnnemy() ;

    cleanHUD() ;

	//On quitte SDL_Mixer 2 et on décharge la mémoire
	Mix_CloseAudio();
	Mix_Quit();

	//On fait le ménage et on remet les pointeurs à NULL
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(screen);
	screen = NULL;

	//On quitte SDL_TTF 2
	TTF_Quit();

	//On quitte la SDL
	SDL_Quit();

	//On ferme les sockets
    WSACleanup() ;

}



