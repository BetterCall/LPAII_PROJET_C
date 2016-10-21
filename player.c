#include "prototypes.h"

GameObject player;
SDL_Texture *playerSpriteSheet;

//Renvoie le GameObject player (h�ros)
GameObject *getPlayer(void) {
	return &player;
}
//Renvoie les coordonn�es x du h�ros
int getPlayerx(void) {
	return player.x;
}
//Renvoie les coordonn�es y du h�ros
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

//Lib�re le sprite du h�ros � la fin du jeu
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

	//On rajoute un timer au cas o� notre h�ros mourrait lamentablement...
	//Si le timer vaut 0, c'est que tout va bien, sinon, on le d�cr�mente jusqu'� 0, et l�,
	//on r�initialise.
	//C'est pour �a qu'on ne g�re le joueur que si ce timer vaut 0.
	if (player.timerMort == 0) {
		//On g�re le timer de l'invincibilit�
		if (player.invincibleTimer > 0)
			player.invincibleTimer--;
		//On r�initialise notre vecteur de d�placement lat�ral (X), pour �viter que le perso
		//ne fonce de plus en plus vite pour atteindre la vitesse de la lumi�re ! ;)
		//Essayez de le d�sactiver pour voir !
		player.dirX = 0 ;
		player.dirY = 0 ;

		if(input->run == 1)
            player.isRunning = 1 ;
        else
            player.isRunning = 0 ;

		//Si on d�tecte un appui sur la touche fl�ch�e droite
        if (input->right == 1) {
			//On augmente les coordonn�es en x du joueur
			player.dirX += PLAYER_SPEED + player.isRunning ;
			//Et on indique qu'il va � droite (pour le flip
			//de l'affichage, rappelez-vous).
			player.direction = RIGHT;
			//Si ce n'�tait pas son �tat auparavant et qu'il est bien sur
			//le sol (car l'anim' sera diff�rente s'il est en l'air)
			if (player.etat != WALK) {
				//On enregistre l'anim' de la marche et on l'initialise � 0
				player.etat = WALK;
				player.frameNumber = 0;
				player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				player.frameMax = 8;
			}
		}
		//Voil�, au lieu de changer directement les coordonn�es du joueur, on passe par un vecteur
		//qui sera utilis� par la fonction mapCollision(), qui regardera si on peut ou pas d�placer
		//le joueur selon ce vecteur et changera les coordonn�es du player en fonction.
		else if (input->left == 1) {
			player.dirX -= PLAYER_SPEED + player.isRunning ;
			//Et on indique qu'il va � gauche (pour le flip
			//de l'affichage, rappelez-vous).
            player.direction = LEFT;
			//Si ce n'�tait pas son �tat auparavant et qu'il est bien sur
			//le sol (car l'anim' sera diff�rente s'il est en l'air)
			if (player.etat != WALK) {
				//On enregistre l'anim' de la marche et on l'initialise � 0
				player.etat = WALK;
				player.frameNumber = 0;
				player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				player.frameMax = 8;
			}
		}
		//Si on d�tecte un appui sur la touche fl�ch�e haut
		else if (input->up == 1) {
			//On augmente les coordonn�es en x du joueur
			player.dirY -= PLAYER_SPEED + player.isRunning ;
			//Et on indique qu'il va � droite (pour le flip
			//de l'affichage, rappelez-vous).
			player.direction = UP;
			//Si ce n'�tait pas son �tat auparavant et qu'il est bien sur
			//le sol (car l'anim' sera diff�rente s'il est en l'air)
			if (player.etat != WALK) {
				//On enregistre l'anim' de la marche et on l'initialise � 0
				player.etat = WALK;
				player.frameNumber = 0;
				player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				player.frameMax = 8;
			}
		}
		//Si on d�tecte un appui sur la touche fl�ch�e bas
		else if (input->down == 1) {
			//On augmente les coordonn�es en x du joueur
			player.dirY += PLAYER_SPEED + player.isRunning ;
			//Et on indique qu'il va � droite (pour le flip
			//de l'affichage, rappelez-vous).
			player.direction = DOWN;
			//Si ce n'�tait pas son �tat auparavant et qu'il est bien sur
			//le sol (car l'anim' sera diff�rente s'il est en l'air)
			if (player.etat != WALK) {
				//On enregistre l'anim' de la marche et on l'initialise � 0
				player.etat = WALK;
				player.frameNumber = 0;
				player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				player.frameMax = 8;
			}
		}
		//Si on d�tecte un appui sur la touche fl�ch�e bas
		else if (input->attack == 1) {
            doSword() ;
            input->attack = 0 ;
		}
		else if(input->magie) {
            createSpell(player, PLAYER) ;
            input->magie = 0 ;
            setPlayerSpell(1);
		}
		//Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivit� (Idle)
		else if (input->right == 0 && input->left == 0 && input->up == 0 && input->down == 0) {
			//On teste si le joueur n'�tait pas d�j� inactif, pour ne pas recharger l'animation
			//� chaque tour de boucle
			if (player.etat != IDLE) {
				//On enregistre l'anim' de l'inactivit� et on l'initialise � 0
				player.etat = IDLE;
				player.frameNumber = 0;
				player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				player.frameMax = 8;
			}
		}
		//On g�re le scrolling (fonction ci-dessous)
		centerScrollingOnPlayer();
		mapCollision(&player) ;
	}

	//Gestion de la mort quand le h�ros tombe dans un trou :
	//Si timerMort est diff�rent de 0, c'est qu'il faut r�initialiser le joueur.
	//On ignore alors ce qui pr�c�de et on joue cette boucle (un wait en fait) jusqu'� ce que
	// timerMort == 1. A ce moment-l�, on le d�cr�mente encore -> il vaut 0 et on r�initialise
	//le jeu avec notre bonne vieille fonction d'initialisation ;) !
	if (player.timerMort > 0) {

		player.timerMort--;
		if (player.timerMort == 0) {
			// Si on est mort, on r�initialise le niveau
			changeLevel();
			//initializePlayer(0);
		}
	}
}

void drawPlayer(void) {

	/* Gestion du timer */
	// Si notre timer (un compte � rebours en fait) arrive � z�ro
	if (player.frameTimer <= 0){
		//On le r�initialise
		player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
		//Et on incr�mente notre variable qui compte les frames de 1 pour passer � la suivante
		player.frameNumber++;
		//Mais si on d�passe la frame max, il faut revenir � la premi�re :
		if (player.frameNumber >= player.frameMax)
			player.frameNumber = 0;
	}
	//Sinon, on d�cr�mente notre timer
	else {
        if(player.etat != IDLE)
            player.frameTimer -= 1 + (player.isRunning * 2 ) ;
        else
            player.frameTimer-- ;
	}
	//Ensuite, on peut passer la main � notre fonction
	/* Rectangle de destination � dessiner */
	SDL_Rect dest;

	// On soustrait des coordonn�es de notre h�ros, ceux du d�but de la map, pour qu'il colle
	//au scrolling :
	dest.x = player.x - getStartX();
	dest.y = player.y - getStartY();
	dest.w = player.w;
	dest.h = player.h;

	/* Rectangle source */
	SDL_Rect src;
	//Pour conna�tre le X de la bonne frame � dessiner, il suffit de multiplier
	//la largeur du sprite par le num�ro de la frame � afficher -> 0 = 0; 1 = 40; 2 = 80...
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

	//Effet de retour en arri�re quand on est mort :
	if (cxperso < getStartX()) {
		setStartX(getStartX() - 30);
	}

	//Si on d�passe par la gauche
	else if (cxperso < xlimmin){
		setStartX(getStartX() - 3);
	}

	if (cxperso > getStartX() + SCREEN_WIDTH) {
		setStartX(getStartX() + 30);
	}

	//Si on d�passe par la droite, on avance la cam�ra
	else if (cxperso > xlimmax) {
		setStartX(getStartX() + 3);
	}

	//Si on arrive au bout de la map � gauche, on stoppe le scrolling
	if (getStartX() < 0) {
		setStartX(0);
	}

	//Si on arrive au bout de la map � droite, on stoppe le scrolling � la
	//valeur Max de la map - la moiti� d'un �cran (pour ne pas afficher du noir).
	else if (getStartX() + SCREEN_WIDTH >= getMaxX()) {
		setStartX(getMaxX() - SCREEN_WIDTH);
	}

	//Si on d�passe par le haut, on remonte la cam�ra
	if (cyperso < ylimmin) {
		setStartY(getStartY() - 3 -player.isRunning);
	}

	//Si on d�passe par le bas, on descend la cam�ra
	if (cyperso > ylimmax) {
        setStartY(getStartY() + 3 + player.isRunning);
    }

	//Si on arrive au bout de la map en haut,
	if (getStartY() < 0){
		setStartY(0);
	}

	//Si on arrive au bout de la map en bas, on stoppe le scrolling � la
	//valeur Max de la map - la moiti� d'un �cran (pour ne pas afficher du noir ;) ).
	else if (getStartY() + SCREEN_HEIGHT >= getMaxY()){
		setStartY(getMaxY() - SCREEN_HEIGHT);
	}

}




