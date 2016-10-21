//Rabidja 3 - nouvelle version int�gralement en SDL 2.0
//Copyright / Droits d'auteur : www.meruvia.fr - J�r�mie F. Bellanger


#include "prototypes.h"

Map map;
int nombreMonstres ;

/**
*
*   int getStartX(void)
*
**/
int getStartX(void) {
	return map.startX;
}

/**
*
*   setStartX(int valeur)
*
**/
void setStartX(int valeur) {
	map.startX = valeur;
}

/**
*
*   int getStartY(void)
*
**/
int getStartY(void) {
	return map.startY;
}

/**
*
*   void setStartY(void)
*
**/
void setStartY(int valeur) {
	map.startY = valeur;
}

/**
*
*   int getStartX(void)
*
**/
int getMaxX(void) {
	return map.maxX;
}

/**
*
*   int getMaxY(void)
*
**/
int getMaxY(void) {
	return map.maxY;
}

/**
*
*   int getBeginX(void)
*
**/
int getBeginX(void) {
	return map.beginx;
}

/**
*
*   int getBeginY(void)
*
**/
int getBeginY(void) {
	return map.beginy;
}

/**
*
*   int getTileValue(void)
*
**/
int getTileValue(int x, int y) {
    return map.tile4[y][x] ;
}

/**
*
*   SDL_Texture *getBackground(void)
*
**/
SDL_Texture *getBackground(void) {
	return map.background;
}
/*
SDL_Texture *getTileSetA() {
    map.tileSet ;
}
SDL_Texture *getTileSetB() {
    map.tileSetB ;
}
*/

/**
*
*   int getStartX(void)
*
**/
void initMaps(void) {
	// Charge l'image du fond (background)
	map.background = loadImage("graphics/background.png");

	//On initialise le timer
	map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;
	map.tileSetNumber = 0;

}

/**
*
*   int getStartX(void)
*
**/
void loadMap(char *name) {

	int x, y;
	FILE *fp;

	fp = fopen(
            name,
            "rb"
         );

	// Si on ne peut pas ouvrir le fichier, on quitte
	if (fp == NULL) {
        printf (
            "Failed to open map %s\n",
            name
        );
        exit(1);
	}

	/* Lit les donn�es du fichier dans la map */

	/* Lit les coordonn�es de d�but du joueur */
	fscanf(
        fp,
        "%d",
        &map.beginx
    );
	fscanf(
        fp,
        "%d",
        &map.beginy
    );

	/* Read the number of the tileset */
	fscanf (
        fp,
        "%d",
        &map.tilesetAffiche
    );

	map.maxX = map.maxY = 0;

	for (y = 0; y < MAX_MAP_Y; y++) {

		for (x = 0; x < MAX_MAP_X; x++) {
			/* On lit le num�ro de la tile et on le copie dans notre tableau */
			fscanf(
                fp,
                "%d",
                &map.tile[y][x]
            );

			/* Permet de d�terminer la taille de la map (voir plus bas) */
			if (map.tile[y][x] > 0) {

				if (x > map.maxX)
					map.maxX = x;

				if (y > map.maxY)
					map.maxY = y;
			}
		}
	}
	//Deuxi�me couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++) {
		for (x = 0; x < MAX_MAP_X; x++) {

			/* On lit le num�ro de la tile et on le copie dans notre tableau */
			fscanf (
                fp,
                "%d",
                &map.tile2[y][x]
            );
		}
	}

	//Troisi�me couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++) {
		for (x = 0; x < MAX_MAP_X; x++) {

			/* On lit le num�ro de la tile et on le copie dans notre tableau */
			fscanf (
                fp,
                "%d",
                &map.tile3[y][x]
            );
		}
	}
	//Quatrieme couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++) {
		for (x = 0; x < MAX_MAP_X; x++) {
			/* On lit le num�ro de la tile et on le copie dans notre tableau */
			fscanf (
                fp,
                "%d",
                &map.tile4[y][x]
            );
		}
	}

	//On charge les variables supplementaires
	y = MAX_MAP_Y * 4 ;
    /**
    voir la suite
    **/

	/* maxX et maxY sont les coordonn�es de fin de la map.
	On les trouve d�s qu'il n'y a plus que des z�ros � la suite.
	Comme �a, on peut faire des maps de tailles diff�rentes avec la m�me
	structure de fichier. */
	map.maxX = (map.maxX + 1) * TILE_SIZE;
	map.maxY = (map.maxY + 1) * TILE_SIZE;

	/* Et on referme le fichier */
	fclose(fp);

}

/**
*
*   int getStartX(void)
*
**/
void drawMap(int layer) {
	int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

	/* On initialise mapX � la 1�re colonne qu'on doit blitter.
	Celle-ci correspond au x de la map (en pixels) divis�s par la taille d'une tile (32)
	pour obtenir la bonne colonne de notre map
	Exemple : si x du d�but de la map = 1026, on fait 1026 / 32
	et on sait qu'on doit commencer par afficher la 32eme colonne de tiles de notre map */
	mapX = map.startX / TILE_SIZE;

	/* Coordonn�es de d�part pour l'affichage de la map : permet
	de d�terminer � quels coordonn�es blitter la 1�re colonne de tiles au pixel pr�s
	(par exemple, si la 1�re colonne n'est visible qu'en partie, on devra commencer � blitter
	hors �cran, donc avoir des coordonn�es n�gatives - d'o� le -1). */
	x1 = (map.startX % TILE_SIZE) * -1;

	/* Calcul des coordonn�es de la fin de la map : jusqu'o� doit-on blitter ?
	Logiquement, on doit aller � x1 (d�part) + SCREEN_WIDTH (la largeur de l'�cran).
	Mais si on a commenc� � blitter en dehors de l'�cran la premi�re colonne, il
	va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
	blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
	if(x1 != 0)
	x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forc�ment, c'est plus long ;)*/
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	/* On fait exactement pareil pour calculer y */
	mapY = map.startY / TILE_SIZE;
	y1 = (map.startY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);


	//On met en place un timer pour animer la map (chapitre 19)
	if (map.mapTimer <= 0){
		if (map.tileSetNumber == 0){

			map.tileSetNumber = 1;
			map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;

		} else {

			map.tileSetNumber = 0;
			map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;
		}

	} else map.mapTimer--;


	/* Dessine la carte en commen�ant par startX et startY */

	/* On dessine ligne par ligne en commen�ant par y1 (0) jusqu'� y2 (480)
	A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
	de tile (qui fait 32 pixels de hauteur) */
	if (layer == 1) {
		for (y = y1; y < y2; y += TILE_SIZE) {

			/* A chaque d�but de ligne, on r�initialise mapX qui contient la colonne
			(0 au d�but puisqu'on ne scrolle pas) */
			mapX = map.startX / TILE_SIZE;

			/* A chaque colonne de tile, on dessine la bonne tile en allant
			de x = 0 � x = 640 */
			for (x = x1; x < x2; x += TILE_SIZE) {

				/* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
				de la tile */
				a = map.tile[mapY][mapX];

				/* Calcul pour obtenir son y (pour un tileset de 10 tiles
				par ligne, d'o� le 10 */
				ysource = a / 10 * TILE_SIZE;
				/* Et son x */
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (map.tileSetNumber == 0)
					drawTile(map.tileSet, x, y, xsource, ysource);
				else
					drawTile(map.tileSetB, x, y, xsource, ysource);

				mapX++;
			}
			mapY++;
		}
	} else if (layer == 2) {

		//Deuxi�me couche de tiles ;)
		for (y = y1; y < y2; y += TILE_SIZE) {
			mapX = map.startX / TILE_SIZE;
			for (x = x1; x < x2; x += TILE_SIZE) {

                if(map.tile4[mapY][mapX] != 0 ) {
                    if(map.tile4[mapY][mapX] >= TILE_MONSTRE_DEBUT && map.tile4[mapY][mapX] <= TILE_MONSTRE_FIN  ) {
                        initializeEnnemy(mapX *PLAYER_HEIGTH , mapY *PLAYER_HEIGTH) ;
                        //On efface la tile pour eviter les spawn infini
                        map.tile4[mapY][mapX] = 0 ;
                    }
                }

				/* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
				de la tile */
				a = map.tile2[mapY][mapX];

				/* Calcul pour obtenir son y (pour un tileset de 10 tiles
				par ligne, d'o� le 10 */
				ysource = a / 10 * TILE_SIZE;
				/* Et son x */
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (map.tileSetNumber == 0)
					drawTile(map.tileSet, x, y, xsource, ysource);
				else
					drawTile(map.tileSetB, x, y, xsource, ysource);

				mapX++;
			}
			mapY++;
		}
	} else if (layer == 3) {
		//Troisi�me couche de tiles ;)
		for (y = y1; y < y2; y += TILE_SIZE) {
			mapX = map.startX / TILE_SIZE;

			for (x = x1; x < x2; x += TILE_SIZE) {

                if(map.tile4[mapY][mapX] != 0 ) {
                    if(map.tile4[mapY][mapX] >= TILE_MONSTRE_DEBUT && map.tile4[mapY][mapX] <= TILE_MONSTRE_FIN  ) {
                        initializeEnnemy(mapX *PLAYER_HEIGTH , mapY *PLAYER_HEIGTH) ;
                        //On efface la tile pour eviter les spawn infini
                        map.tile4[mapY][mapX] = 0 ;
                    }
                }

				/* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
				de la tile */
				a = map.tile3[mapY][mapX];

				/* Calcul pour obtenir son y (pour un tileset de 10 tiles
				par ligne, d'o� le 10 */
				ysource = a / 10 * TILE_SIZE;
				/* Et son x */
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (map.tileSetNumber == 0)
					drawTile(map.tileSet, x, y, xsource, ysource);
				else
					drawTile(map.tileSetB, x, y, xsource, ysource);

				mapX++;
			}
			mapY++;
		}
	}

}

/**
*
*   int getStartX(void)
*
**/
void testDefilement(void) {
    //Test de d�filement de la map

    //On commence � faire d�filer vers la droite (valeur == 0)
    if (map.testdefil == 0) {
        //Tant que le d�but du blittage de la map est inf�rieur aux coordonn�es
        //en X de la fin de la map (- la largeur de l'�cran pour ne pas afficher
        //du noir), on fait d�filer la map.
        if (map.startX < map.maxX - SCREEN_WIDTH)
        //Vous pouvez changer cette valeur pour faire d�filer la map plus ou moins vite
            map.startX += 2;
        else
            map.testdefil = 1;
    }
    //Une fois au bout, on fait d�filer vers le bas (valeur == 1)
    else if (map.testdefil == 1) {

        if (map.startY < map.maxY - SCREEN_HEIGHT)
        //Vous pouvez changer cette valeur pour faire d�filer la map plus ou moins vite
            map.startY += 2;
        else
            map.testdefil = 2;
    }
    //Une fois en bas, on fait d�filer vers la gauche (valeur == 2)
    else if (map.testdefil == 2) {
        if (map.startX > 0)
        //Vous pouvez changer cette valeur pour faire d�filer la map plus ou moins vite
            map.startX -= 2;
        else
            map.testdefil = 3;
    }
    //Puis on remonte au point de d�part (valeur == 3) et on recommence
    else if (map.testdefil == 3) {
        if (map.startY > 0)
            //Vous pouvez changer cette valeur pour faire d�filer la map plus ou moins vite
            map.startY -= 2;
        else
            map.testdefil = 0;
    }
}

/**
*
*   int getStartX(void)
*
**/
int mapCollisionMagic(GameObject *entity) {

    int i, x1, x2, y1, y2;
    int destroy = 0 ;

	/* Ensuite, on va tester les mouvements horizontaux en premier
	(axe des X). On va se servir de i comme compteur pour notre boucle.
	En fait, on va d�couper notre sprite en blocs de tiles pour voir
	quelles tiles il est susceptible de recouvrir.
	On va donc commencer en donnant la valeur de Tile_Size � i pour qu'il
	teste la tile o� se trouve le x du joueur mais aussi la suivante SAUF
	dans le cas o� notre sprite serait inf�rieur � 	la taille d'une tile.
	Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
	Et on testera ensuite 2 fois la m�me tile. Mais comme �a notre code
	sera op�rationnel quelle que soit la taille de nos sprites ! */

	if (entity->h > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = entity->h;


	//On lance alors une boucle for infinie car on l'interrompra selon
	//les r�sultats de nos calculs
	for (;;) {

		//On va calculer ici les coins de notre sprite � gauche et �
		//droite pour voir quelle tile ils touchent.
		x1 = (entity->x + entity->dirX) / TILE_SIZE;
		x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

		//M�me chose avec y, sauf qu'on va descendre au fur et � mesure
		//pour tester toute la hauteur de notre sprite, gr�ce � notre
		//fameuse variable i.
		y1 = (entity->y) / TILE_SIZE;
		y2 = (entity->y + i - 1) / TILE_SIZE;

		//De l�, on va tester les mouvements initi�s dans updatePlayer
		//gr�ce aux vecteurs dirX et dirY, tout en testant avant qu'on
		//se situe bien dans les limites de l'�cran.
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {

			//Si on a un mouvement � droite
			if (entity->dirX > 0) {

				//On v�rifie si les tiles recouvertes sont solides
				if (map.tile4[y1][x2] == MUR || map.tile4[y2][x2] == MUR ) {

					// Si c'est le cas, on place le joueur aussi pr�s que possible
					// de ces tiles, en mettant � jour ses coordonn�es. Enfin, on
					//r�initialise son vecteur d�placement (dirX).

					entity->x = x2 * TILE_SIZE;
					entity->x -= entity->w + 1;
					entity->dirX = 0;
					destroy = 1 ;

				}
			}

			//M�me chose � gauche
			else if (entity->dirX < 0) {

				if (map.tile4[y1][x1] == MUR || map.tile4[y2][x1] == MUR ) {

					entity->x = (x1 + 1) * TILE_SIZE;
					entity->dirX = 0;
					destroy = 1 ;
				}
			}
		}

		//On sort de la boucle si on a test� toutes les tiles le long de la hauteur du sprite.
		if (i == entity->h)
			break;

		//Sinon, on teste les tiles sup�rieures en se limitant � la heuteur du sprite.
		i += TILE_SIZE;

		if (i > entity->h)
			i = entity->h;
	}

	//On recommence la m�me chose avec le mouvement vertical (axe des Y)
	if (entity->w > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = entity->w;


	for (;;) {

		x1 = (entity->x) / TILE_SIZE;
		x2 = (entity->x + i) / TILE_SIZE;

		y1 = (entity->y + entity->dirY) / TILE_SIZE;
		y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {

			if (entity->dirY > 0) {
				/* D�placement en bas */

				if (map.tile4[y2][x1] == MUR || map.tile4[y2][x2] == MUR ) {

					//Si la tile est une plateforme ou une tile solide, on y colle le joueur et
					//on le d�clare sur le sol (onGround).
					entity->y = y2 * TILE_SIZE;
					entity->y -= entity->h;
					entity->dirY = 0;
					destroy = 1 ;
				}

			} else if (entity->dirY < 0) {

				/* D�placement vers le haut */
				if (map.tile4[y1][x1] == MUR || map.tile4[y1][x2] == MUR ) {

					entity->y = (y1 + 1) * TILE_SIZE;
					entity->dirY = 0;
					destroy = 1 ;
				}
			}
		}

		//On teste la largeur du sprite (m�me technique que pour la hauteur pr�c�demment)
		if (i == entity->w)
			break;


		i += TILE_SIZE;

		if (i > entity->w)
			i = entity->w;

	}

	/* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqu� */
	entity->x += entity->dirX;
	entity->y += entity->dirY;

	//Et on contraint son d�placement aux limites de l'�cran.
	if (entity->x < 0)
		entity->x = 0;

	else if (entity->x + entity->w >= map.maxX) {
		//Si on touche le bord droit de l'�cran, on annule
		//et on limite le d�placement du joueur
		entity->x = map.maxX - entity->w - 1;
	}

	//Maintenant, s'il sort de l'�cran par le bas (chute dans un trou sans fond), on lance le timer
	//qui g�re sa mort et sa r�initialisation (plus tard on g�rera aussi les vies).
	if (entity->y > map.maxY)
		entity->timerMort = 60;

    return destroy  ;

}

/**
*
*   int getStartX(void)
*
**/
void mapCollision(GameObject *entity) {

	int i, x1, x2, y1, y2;

	/* Ensuite, on va tester les mouvements horizontaux en premier
	(axe des X). On va se servir de i comme compteur pour notre boucle.
	En fait, on va d�couper notre sprite en blocs de tiles pour voir
	quelles tiles il est susceptible de recouvrir.
	On va donc commencer en donnant la valeur de Tile_Size � i pour qu'il
	teste la tile o� se trouve le x du joueur mais aussi la suivante SAUF
	dans le cas o� notre sprite serait inf�rieur � 	la taille d'une tile.
	Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
	Et on testera ensuite 2 fois la m�me tile. Mais comme �a notre code
	sera op�rationnel quelle que soit la taille de nos sprites ! */

	if (entity->h > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = entity->h;


	//On lance alors une boucle for infinie car on l'interrompra selon
	//les r�sultats de nos calculs
	for (;;) {

		//On va calculer ici les coins de notre sprite � gauche et �
		//droite pour voir quelle tile ils touchent.
		x1 = (entity->x + entity->dirX) / TILE_SIZE;
		x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

		//M�me chose avec y, sauf qu'on va descendre au fur et � mesure
		//pour tester toute la hauteur de notre sprite, gr�ce � notre
		//fameuse variable i.
		y1 = (entity->y) / TILE_SIZE;
		y2 = (entity->y + i - 1) / TILE_SIZE;

		//De l�, on va tester les mouvements initi�s dans updatePlayer
		//gr�ce aux vecteurs dirX et dirY, tout en testant avant qu'on
		//se situe bien dans les limites de l'�cran.
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {

			//Si on a un mouvement � droite
			if (entity->dirX > 0) {

				//On v�rifie si les tiles recouvertes sont solides
				if (map.tile4[y1][x2] == MUR || map.tile4[y2][x2] == MUR ) {

					// Si c'est le cas, on place le joueur aussi pr�s que possible
					// de ces tiles, en mettant � jour ses coordonn�es. Enfin, on
					//r�initialise son vecteur d�placement (dirX).

					entity->x = x2 * TILE_SIZE;
					entity->x -= entity->w + 1;
					entity->dirX = 0;

				}
			}

			//M�me chose � gauche
			else if (entity->dirX < 0) {

				if (map.tile4[y1][x1] == MUR || map.tile4[y2][x1] == MUR ) {

					entity->x = (x1 + 1) * TILE_SIZE;
					entity->dirX = 0;
				}
			}
		}

		//On sort de la boucle si on a test� toutes les tiles le long de la hauteur du sprite.
		if (i == entity->h)
			break;

		//Sinon, on teste les tiles sup�rieures en se limitant � la heuteur du sprite.
		i += TILE_SIZE;

		if (i > entity->h)
			i = entity->h;
	}

	//On recommence la m�me chose avec le mouvement vertical (axe des Y)
	if (entity->w > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = entity->w;


	for (;;) {

		x1 = (entity->x) / TILE_SIZE;
		x2 = (entity->x + i) / TILE_SIZE;

		y1 = (entity->y + entity->dirY) / TILE_SIZE;
		y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {

			if (entity->dirY > 0) {
				/* D�placement en bas */

				if (map.tile4[y2][x1] == MUR || map.tile4[y2][x2] == MUR ) {

					//Si la tile est une plateforme ou une tile solide, on y colle le joueur et
					//on le d�clare sur le sol (onGround).
					entity->y = y2 * TILE_SIZE;
					entity->y -= entity->h;
					entity->dirY = 0;
				}

			} else if (entity->dirY < 0) {

				/* D�placement vers le haut */
				if (map.tile4[y1][x1] == MUR || map.tile4[y1][x2] == MUR ) {

					entity->y = (y1 + 1) * TILE_SIZE;
					entity->dirY = 0;
				}
			}
		}

		//On teste la largeur du sprite (m�me technique que pour la hauteur pr�c�demment)
		if (i == entity->w)
			break;


		i += TILE_SIZE;

		if (i > entity->w)
			i = entity->w;

	}

	/* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqu� */
	entity->x += entity->dirX;
	entity->y += entity->dirY;

	//Et on contraint son d�placement aux limites de l'�cran.
	if (entity->x < 0)
		entity->x = 0;

	else if (entity->x + entity->w >= map.maxX) {
		//Si on touche le bord droit de l'�cran, on annule
		//et on limite le d�placement du joueur
		entity->x = map.maxX - entity->w - 1;
	}

	//Maintenant, s'il sort de l'�cran par le bas (chute dans un trou sans fond), on lance le timer
	//qui g�re sa mort et sa r�initialisation (plus tard on g�rera aussi les vies).
	if (entity->y > map.maxY)
		entity->timerMort = 60;
}

/**
*
*   int getStartX(void)
*
**/
void changeLevel(void) {

	char file[200];

	/* Charge la map depuis le fichier */
	sprintf (
        file,
        "map/map%d.txt",
        1
    );

	loadMap(file);

	//Charge le tileset
	if (map.tileSet != NULL)
		SDL_DestroyTexture(map.tileSet);

	if (map.tileSetB != NULL)
		SDL_DestroyTexture(map.tileSetB);


	sprintf (
        file,
        "graphics/tileset%d.png",
        map.tilesetAffiche
    );
	map.tileSet = loadImage(file);

	sprintf (
        file,
        "graphics/tileset%dB.png",
        map.tilesetAffiche
    );

	map.tileSetB = loadImage(file);

}

/**
*
*   int getStartX(void)
*
**/
void cleanMaps(void) {

	// Lib�re la texture du background
	if (map.background != NULL) {

		SDL_DestroyTexture(map.background);
		map.background = NULL;
	}

	// Lib�re les textures des tilesets
	if (map.tileSet != NULL) {
		SDL_DestroyTexture(map.tileSet);
		map.tileSet = NULL;
	}

	if (map.tileSetB != NULL) {
		SDL_DestroyTexture(map.tileSetB);
		map.tileSetB = NULL;
	}
}

