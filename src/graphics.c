#include "fonctions.h"


SDL_Surface *loadImage(char *name)
{
	/* Load the image using SDL Image */

	SDL_Surface *temp = IMG_Load(name);
	SDL_Surface *image=  NULL;

	if (temp == NULL)
	{
		printf("Failed to load image %s\n", name);
		return NULL;
	}

	image = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	if (image == NULL)
	{
		printf("Failed to convert image %s to native format\n", name);

		return NULL;
	}

	if( image != NULL )
        {
            //Map the color key, 3* 0xFF pour transparent, sans font blanc
            Uint32 colorkey = SDL_MapRGB( (*image).format, 255, 255, 255 );
            SDL_SetColorKey( image, SDL_SRCCOLORKEY, colorkey );
        }


	/* Return the processed image */
	return image;
}


TTF_Font *loadFont(char *name, int size)
{
	/* Use SDL_TTF to load the font at the specified size */

	TTF_Font *Font = TTF_OpenFont(name, size);

	if (Font == NULL)
	{
		printf("Failed to open Font %s: %s\n", name, TTF_GetError());

		exit(1);
	}

	return Font;
}



void drawImage(SDL_Surface *image, int x, int y)
{
	SDL_Rect dest;

	/* Set the blitting rectangle to the size of the src image */

	dest.x = x;
	dest.y = y;
	dest.w = (*image).w;
	dest.h = (*image).h;

	/* Blit the entire image onto the screen at coordinates x and y */

	SDL_BlitSurface(image, NULL, screen, &dest);
}


void drawMenu(char *text, int x, int y, TTF_Font *Font)
{
	SDL_Rect dest;
	SDL_Surface *surface;
	SDL_Color foregroundColor;

	/* White text on a black background */

	foregroundColor.r = 0;
	foregroundColor.g = 0;
	foregroundColor.b = 0;

	/* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

	surface = TTF_RenderUTF8_Blended(Font,text,foregroundColor);

	if (surface == NULL)
	{
		printf("Couldn't create String %s: %s\n", text, SDL_GetError());

		return;
	}

	/* Blit the entire surface to the screen */

	dest.x = ((*screen).w - (*surface).w )/ 2 +x;
	dest.y = ((*screen).h - (*surface).h) / 3 + y;
	dest.w = (*surface).w;
	dest.h = (*surface).h;


	SDL_BlitSurface(surface, NULL, screen, &dest);

	/* Free the generated string image */

	SDL_FreeSurface(surface);
}

void drawText(char *text, int x, int y, TTF_Font *textFont)    // Param�tres d'affichage de l'interface sur la carte noir/bleu
{
    SDL_Rect dest;
    SDL_Surface *surface;
    SDL_Color foregroundColor;

    /* White text on a black background */

    foregroundColor.r = 250;
    foregroundColor.g = 250;
    foregroundColor.b = 250;


    /* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

    surface = TTF_RenderUTF8_Blended(textFont, text, foregroundColor);

    if (surface == NULL)
    {
        printf("Couldn't create String %s: %s\n", text, SDL_GetError());

        return;
    }

    /* Blit the entire surface to the screen */

    dest.x = x;
    dest.y = y;
    dest.w = (*surface).w;
    dest.h = (*surface).h;


    SDL_BlitSurface(surface, NULL, screen, &dest);

    /* Free the generated string image */

    SDL_FreeSurface(surface);
}


void loadSprite(int index, char *name)
{
	/* Load the image into the next slot in the sprite bank */
	printf("index: %d\n", index);
	if (index >= MAX_SPRITES || index < 0)
	{
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);

		exit(1);
	}

	sprite[index].image = loadImage(name);

	if (sprite[index].image == NULL)
	{
		exit(1);
	}
}

SDL_Surface *getSprite(int index)
{
	if (index >= MAX_SPRITES || index < 0)
	{
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);

		exit(1);
	}

	return sprite[index].image;
}

void freeSprites()
{
	int i;

	/* Loop through the sprite bank and clear the images */

	for (i=0;i<MAX_SPRITES;i++)
	{
		if (sprite[i].image != NULL)
		{
			SDL_FreeSurface(sprite[i].image);
		}
	}
}

void loadAllSprites()
{
	Font = loadFont("sfd/Market_Deco.ttf", 30);
	textFont = loadFont("sfd/Market_Deco.ttf", 15);
	loadSprite(PLAYER_SPRITE, "gfx/Roger_Clean.png");
	loadSprite(BACKGROUND_SPRITE, "gfx/TerrainV1.png");
	loadSprite(OFFICER_SPRITE, "gfx/Agent_Clean.png");
}


void updateScreen()
{
	/* Blank the screen */
	SDL_FillRect(screen, NULL, 0);

	switch(Game.stade) {
	  case 0:
	    drawImage(getSprite(BACKGROUND_SPRITE), 0, 0);
	    drawMenu("START GAME", 0, 0, Font);
	    drawMenu("ABOUT", 0, 130, Font);
	    drawMenu("QUIT", 0, 260, Font);
	    break;


	  case 1:
		doEnnemi();
		movePlayer();
		drawImage(getSprite(BACKGROUND_SPRITE), 0, 0);
		drawPlayer();
		drawOfficer();
		collision();
		drawInterface();
	    break;


	  case 2:
	    drawImage(getSprite(BACKGROUND_SPRITE), 0, 0);
	    drawMenu("GAME OVER !", 0, 0, Font);
	    break;
	}


	SDL_Flip(screen);
}
