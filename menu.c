#include "prototypes.h"

//Gestion des menus
int onMenu =0, menuType, choice;
SDL_Texture *titlescreen;

int getOnMenu(void) {
	return onMenu;
}

int getMenuType(void) {
	return menuType;
}

void setOnMenu(int valeur) {
	onMenu = valeur;
}

void initMenus(void) {
}

void cleanMenus(void) {
	// Lib�re la texture de l'�cran-titre
	if (titlescreen != NULL) {

		SDL_DestroyTexture(titlescreen);
		titlescreen = NULL;
	}
}

void updateStartMenu(Input *input) {
	//Si on appuie sur BAS
	if (input->down == 1) {
		//Si choice = O (il est sur start), on le met � 1 (quit)
		if (choice == 0)
			choice++;

		input->down = 0;
	}

	//Si on appuie sur HAUT
	if (input->up == 1) {
		//Si choice = 1 (il est sur Quit), on le met � 0 (Start)
		if (choice == 1)
			choice--;

		input->up = 0;
	}

	if (input->enter) {
		if (choice == 0) {

           	onServeur();

            // ON LANCE LE SERVEUR
		}
		//Sinon, on quitte le jeu
		else if (choice == 1) {
			//exit(0);
			onClient() ;

			// ON LANCE UN CLIENT
		}
		input->enter = 0;
	}
}

void drawStartMenu(void) {

    if(getOnMenu() != 3 ) {
        char text[200];

        //On affiche l'�cran-titre
        drawImage(titlescreen, 0, 0);

        //Si l'option n'est pas en surbrillance, on l'affiche normalement
        if (choice != 0) {
            sprintf(text, "CREER UNE NOUVELLE PARTIE");
            //Ombrage en noir
            drawString(text, 375, 252, 0, 0, 0, 255);
            drawString(text, 373, 250, 255, 255, 255, 255);
        }
        if (choice != 1) {
            sprintf(text, "REJOINDRE UNE PARTIE");
            //Ombrage en noir
            drawString(text, 425, 292, 0, 0, 0, 255);
            drawString(text, 422, 290, 255, 255, 255, 255);
        }

        //Si l'option est en surbrillance, on change la couleur
        if (choice == 0) {
            sprintf(text, "CREER UNE NOUVELLE PARTIE");
            //Ombrage en noir
            drawString(text, 375, 252, 0, 0, 0, 255);
            drawString(text, 373, 250, 255, 255, 0, 255);
        }
        else if (choice == 1) {
            sprintf(text, "REJOINDRE UNE PARTIE");
            //Ombrage en noir
            drawString(text, 425, 292, 0, 0, 0, 255);
            drawString(text, 422, 290, 255, 255, 0, 255);
        }
    }

}

