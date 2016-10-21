#include "prototypes.h"

GameObject player;
SDL_Texture *playerSpriteSheet;

//Renvoie le GameObject player (héros)
GameObject *getPlayer(void) {
	return &player;
}
//Renvoie les coordonnées x du héros
int getPlayerx(void) {
	return player.x;
}
//Renvoie les coordonnées y du héros
int getPlayery(void) {
	return player.y;
}


int getPlayerLife() {
    return player.life ;
}

void setPlayerLife(int pLife) {
    player.life = pLife ;
}

void setPlayerIsAttacking(int valeur) {
    player.isAttacking = valeur ;
}
int getPlayerDirection (void) {
    return player.direction ;
}


int getPlayerSpell(void) {
    return player.spell ;
}
void setPlayerSpell(int pSpell) {
    player.spell = pSpell ;
}

void loadPlayerImage(void) {
    playerSpriteSheet = loadImage("graphics/rabidja.png");
}

//Libère le sprite du héros à la fin du jeu
void cleanPlayer(void) {
	if (playerSpriteSheet != NULL) {
		SDL_DestroyTexture(playerSpriteSheet);
		playerSpriteSheet = NULL;
	}
}

void killPlayer(void) {
    cleanPlayer() ;
    drawEndMenu() ;
}
void updatePlayer(Input *input) {

    if (player.life < 1) {
        drawEndMenu() ;
    }

	//On rajoute un timer au cas où notre héros mourrait lamentablement...
	//Si le timer vaut 0, c'est que tout va bien, sinon, on le décrémente jusqu'à 0, et là,
	//on réinitialise.
	//C'est pour ça qu'on ne gère le joueur que si ce timer vaut 0.
	if (player.timerMort == 0) {
		//On gère le timer de l'invincibilité
		if (player.invincibleTimer > 0)
			player.invincibleTimer--;
		//On réinitialise notre vecteur de déplacement latéral (X), pour éviter que le perso
		//ne fonce de plus en plus vite pour atteindre la vitesse de la lumière ! ;)
		//Essayez de le désactiver pour voir !
		player.dirX = 0 ;
		player.dirY = 0 ;

		if(input->run == 1)
            player.isRunning = 1 ;
        else
            player.isRunning = 0 ;

		//Si on détecte un appui sur la touche fléchée droite
        if (input->right == 1) {
			//On augmente les coordonnées en x du joueur
			player.dirX += PLAYER_SPEED + player.isRunning ;
			//Et on indique qu'il va à droite (pour le flip
			//de l'affichage, rappelez-vous).
			player.direction = RIGHT;
			//Si ce n'était pas son état auparavant et qu'il est bien sur
			//le sol (car l'anim' sera différente s'il est en l'air)
			if (player.etat != WALK) {
				//On enregistre l'anim' de la marche et on l'initialise à 0
				player.etat = WALK;
				player.frameNumber = 0;
				player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				player.frameMax = 8;
			}
		}
		//Voilà, au lieu de changer directement les coordonnées du joueur, on passe par un vecteur
		//qui sera utilisé par la fonction mapCollision(), qui regardera si on peut ou pas déplacer
		//le joueur selon ce vecteur et changera les coordonnées du player en fonction.
		else if (input->left == 1) {
			player.dirX -= PLAYER_SPEED + player.isRunning ;
			//Et on indique qu'il va à gauche (pour le flip
			//de l'affichage, rappelez-vous).
            player.direction = LEFT;
			//Si ce n'était pas son état auparavant et qu'il est bien sur
			//le sol (car l'anim' sera différente s'il est en l'air)
			if (player.etat != WALK) {
				//On enregistre l'anim' de la marche et on l'initialise à 0
				player.etat = WALK;
				player.frameNumber = 0;
				player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				player.frameMax = 8;
			}
		}
		//Si on détecte un appui sur la touche fléchée haut
		else if (input->up == 1) {
			//On augmente les coordonnées en x du joueur
			player.dirY -= PLAYER_SPEED + player.isRunning ;
			//Et on indique qu'il va à droite (pour le flip
			//de l'affichage, rappelez-vous).
			player.direction = UP;
			//Si ce n'était pas son état auparavant et qu'il est bien sur
			//le sol (car l'anim' sera différente s'il est en l'air)
			if (player.etat != WALK) {
				//On enregistre l'anim' de la marche et on l'initialise à 0
				player.etat = WALK;
				player.frameNumber = 0;
				player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				player.frameMax = 8;
			}
		}
		//Si on détecte un appui sur la touche fléchée bas
		else if (input->down == 1) {
			//On augmente les coordonnées en x du joueur
			player.dirY += PLAYER_SPEED + player.isRunning ;
			//Et on indique qu'il va à droite (pour le flip
			//de l'affichage, rappelez-vous).
			player.direction = DOWN;
			//Si ce n'était pas son état auparavant et qu'il est bien sur
			//le sol (car l'anim' sera différente s'il est en l'air)
			if (player.etat != WALK) {
				//On enregistre l'anim' de la marche et on l'initialise à 0
				player.etat = WALK;
				player.frameNumber = 0;
				player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				player.frameMax = 8;
			}
		}
		//Si on détecte un appui sur la touche fléchée bas
		else if (input->attack == 1) {
            doSword() ;
            input->attack = 0 ;
		}
		else if(input->magie) {
            createSpell(player, PLAYER) ;
            input->magie = 0 ;
            setPlayerSpell(1);
		}
		//Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivité (Idle)
		else if (input->right == 0 && input->left == 0 && input->up == 0 && input->down == 0) {
			//On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
			//à chaque tour de boucle
			if (player.etat != IDLE) {
				//On enregistre l'anim' de l'inactivité et on l'initialise à 0
				player.etat = IDLE;
				player.frameNumber = 0;
				player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				player.frameMax = 8;
			}
		}
		//On gère le scrolling (fonction ci-dessous)
		centerScrollingOnPlayer();
		mapCollision(&player) ;
	}

	//Gestion de la mort quand le héros tombe dans un trou :
	//Si timerMort est différent de 0, c'est qu'il faut réinitialiser le joueur.
	//On ignore alors ce qui précède et on joue cette boucle (un wait en fait) jusqu'à ce que
	// timerMort == 1. A ce moment-là, on le décrémente encore -> il vaut 0 et on réinitialise
	//le jeu avec notre bonne vieille fonction d'initialisation ;) !
	if (player.timerMort > 0) {

		player.timerMort--;
		if (player.timerMort == 0) {
			// Si on est mort, on réinitialise le niveau
			changeLevel();
			//initializePlayer(0);
		}
	}
}

void drawPlayer(void) {

	/* Gestion du timer */
	// Si notre timer (un compte à rebours en fait) arrive à zéro
	if (player.frameTimer <= 0){
		//On le réinitialise
		player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
		//Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
		player.frameNumber++;
		//Mais si on dépasse la frame max, il faut revenir à la première :
		if (player.frameNumber >= player.frameMax)
			player.frameNumber = 0;
	}
	//Sinon, on décrémente notre timer
	else {
        if(player.etat != IDLE)
            player.frameTimer -= 1 + (player.isRunning * 2 ) ;
        else
            player.frameTimer-- ;
	}
	//Ensuite, on peut passer la main à notre fonction
	/* Rectangle de destination à dessiner */
	SDL_Rect dest;

	// On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle
	//au scrolling :
	dest.x = player.x - getStartX();
	dest.y = player.y - getStartY();
	dest.w = player.w;
	dest.h = player.h;

	/* Rectangle source */
	SDL_Rect src;
	//Pour connaître le X de la bonne frame à dessiner, il suffit de multiplier
	//la largeur du sprite par le numéro de la frame à afficher -> 0 = 0; 1 = 40; 2 = 80...
	src.x = player.frameNumber * player.w;
    src.y = player.etat * 3 * player.h ;
    /*
        if ( player.direction == LEFT )
            player.directionn = RIGHT // On retournera le sprite
        else
            player.direction = player.direction
    */
    src.y += (( player.direction == LEFT ? RIGHT : player.direction ))*player.h  ;
    src.y += player.isAttacking * 6 * player.h ;

	src.w = player.w;
	src.h = player.h  ;

    // Si le joeur a ete touche on le fait clignoter
    if(player.invincibleTimer > 0) {

        if( !(player.frameNumber % 2) ) {

            if(player.direction == LEFT) {

                SDL_RenderCopyEx(
                    getrenderer(),
                    playerSpriteSheet,
                    &src,
                    &dest,
                    0,
                    0,
                    SDL_FLIP_NONE
                );
            } else {
                SDL_RenderCopyEx(
                    getrenderer(),
                    playerSpriteSheet,
                    &src, &dest,
                    0, 0,
                    SDL_FLIP_HORIZONTAL
                );
            }
        }
    } else {

        if(player.direction == LEFT) {
            SDL_RenderCopyEx(
                getrenderer(),
                playerSpriteSheet,
                &src,
                &dest,
                0,
                0,
                SDL_FLIP_NONE
            );
        } else {
            SDL_RenderCopyEx(
                getrenderer(),
                playerSpriteSheet,
                &src,
                &dest,
                0,
                0,
                SDL_FLIP_HORIZONTAL
            );
        }
    }
    spellCollide() ;
}


void centerScrollingOnPlayer(void) {

	//Gere la camera sur le joueur
	int cxperso = player.x + player.w / 2;
	int cyperso = player.y + player.h / 2;
	int xlimmin = getStartX() + LIMITE_X;
	int xlimmax = xlimmin + LIMITE_W;
	int ylimmin = getStartY() + LIMITE_Y;
	int ylimmax = ylimmin + LIMITE_H;

	//Effet de retour en arrière quand on est mort :
	if (cxperso < getStartX()) {
		setStartX(getStartX() - 30);
	}

	//Si on dépasse par la gauche
	else if (cxperso < xlimmin){
		setStartX(getStartX() - 3);
	}

	if (cxperso > getStartX() + SCREEN_WIDTH) {
		setStartX(getStartX() + 30);
	}

	//Si on dépasse par la droite, on avance la caméra
	else if (cxperso > xlimmax) {
		setStartX(getStartX() + 3);
	}

	//Si on arrive au bout de la map à gauche, on stoppe le scrolling
	if (getStartX() < 0) {
		setStartX(0);
	}

	//Si on arrive au bout de la map à droite, on stoppe le scrolling à la
	//valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
	else if (getStartX() + SCREEN_WIDTH >= getMaxX()) {
		setStartX(getMaxX() - SCREEN_WIDTH);
	}

	//Si on dépasse par le haut, on remonte la caméra
	if (cyperso < ylimmin) {
		setStartY(getStartY() - 3 -player.isRunning);
	}

	//Si on dépasse par le bas, on descend la caméra
	if (cyperso > ylimmax) {
        setStartY(getStartY() + 3 + player.isRunning);
    }

	//Si on arrive au bout de la map en haut,
	if (getStartY() < 0){
		setStartY(0);
	}

	//Si on arrive au bout de la map en bas, on stoppe le scrolling à la
	//valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir ;) ).
	else if (getStartY() + SCREEN_HEIGHT >= getMaxY()){
		setStartY(getMaxY() - SCREEN_HEIGHT);
	}

}




