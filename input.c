//Rabidja 3 - nouvelle version int�gralement en SDL 2.0
//Copyright / Droits d'auteur : www.meruvia.fr - J�r�mie F. Bellanger


#include "prototypes.h"

/**
*
*   void gestionInputs (Input *input)
*
*       @param Input *input
*
**/
void gestionInputs(Input *input) {
	//On g�re le clavier (on rajoutera plus tard la gestion
	//des joysticks ;) )
	getInput(input);
}

/**
*
*   void getInputs (Input *input)
*
*       @param Input *input
*
**/
void getInput(Input *input) {

	SDL_Event event;

	/* Keymapping : g�re les appuis sur les touches et les enregistre
	dans la structure input */

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

			case SDL_QUIT:
				exit(0);
			break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						exit(0);
					break;

					case SDLK_DELETE:
						input->erase = 1;
					break;

					case SDLK_SPACE:
						input->run = 1;
                    break;

                  	case SDLK_a:
						input->attack = 1;
                    break;

                    case SDLK_z:
						input->magie = 1;
                    break;

					case SDLK_LEFT:
						input->left = 1;
					break;

					case SDLK_RIGHT:
						input->right = 1;
					break;

					case SDLK_DOWN:
						input->down = 1;
					break;

					case SDLK_UP:
						input->up = 1;
					break;


					case SDLK_RETURN:
						input->enter = 1;
					break;


					default:
					break;
				}
			break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_DELETE:
						input->erase = 0;
					break;

                   case SDLK_SPACE:
						input->run = 0;
                    break;

                  	case SDLK_a:
						input->attack = 0;
                    break;

                    case SDLK_z:
						input->magie = 0;
                    break;

					case SDLK_LEFT:
						input->left = 0;
					break;

					case SDLK_RIGHT:
						input->right = 0;
					break;

					case SDLK_DOWN:
						input->down = 0;
					break;

					case SDLK_UP:
						input->up = 0;
					break;

					case SDLK_RETURN:
						input->enter = 0;
					break;

					default:
					break;
				}
			break;

		}

	}
}


