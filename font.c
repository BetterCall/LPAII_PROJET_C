#include "prototypes.h"

/* Déclaration de notre police de caractères (font) */
TTF_Font *font;

/**
*
*   loadFont(char *name, int size)
*       charge une police d'ecriture
*       @param char *name  nom de la police
*       @param int size    taille de la police
*
**/
void loadFont(char *name, int size) {

    font = TTF_OpenFont(name, size);
    if (font == NULL) {
        printf(
            "Failed to open Font %s: %s\n",
            name,
            TTF_GetError()
        );
        exit(1);
    }
}


/**
*
*   closeFont
*       decharge la police d'ecriture
*
**/
void closeFont(void) {
    /* On ferme la police (font) */
    if (font != NULL)
        TTF_CloseFont(font);
}


/**
*
*   void drawString(char *text, int x, int y, int r, int g, int b, int a)
*       Affiche une chaine de caracteres
*       @param char *text
*       @param int x
*       @param int y
*       @param int r    niveau de Rouge
*       @param int g    niveau de Vert
*       @param int b    niveau de Bleu
*       @param int a    niveau de Transparence
*
**/
void drawString(char *text, int x, int y, int r, int g, int b, int a)  {

    SDL_Rect dest;
    SDL_Surface *surface; //Pour écrire le texte
    SDL_Texture *texture; //Pour convertir la surface en texture
    SDL_Color foregroundColor;

    /* Couleur du texte RGBA */
    foregroundColor.r = r;
    foregroundColor.g = g;
    foregroundColor.b = b;
    foregroundColor.a = a;


    /* On utilise SDL_TTF pour générer une SDL_Surface à partir d'une chaîne de caractères (string) */
    surface = TTF_RenderUTF8_Blended (
                font,
                text,
                foregroundColor
              );

    if (surface != NULL) {
        /* NOUS MODIFIONS QUELQUE PEU NOTRE CODE POUR PROFITER DE LA MEMOIRE GRAPHIQUE
        QUI GERE LES TEXTURES */
        // Conversion de l'image en texture
        texture = SDL_CreateTextureFromSurface(
                      getrenderer(),
                      surface
                  );

        // On se débarrasse du pointeur vers une surface
        /* On libère la SDL_Surface temporaire (pour éviter les fuites de mémoire) */
        SDL_FreeSurface(surface);
        surface = NULL;

        // On dessine cette texture à l'écran
        dest.x = x;
        dest.y = y;

        SDL_QueryTexture(
            texture,
            NULL,
            NULL,
            &dest.w,
            &dest.h
        );
        SDL_RenderCopy (
            getrenderer(),
            texture,
            NULL,
            &dest
        );

        //On supprime la texture
        SDL_DestroyTexture(texture);

    } else {
        printf (
            "La chaine n'a pu être écrite %s: %s\n",
            text,
            TTF_GetError()
        );
        exit(0);
    }
}


