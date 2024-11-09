#include <stdio.h>
#include "..\Include\imageLoader.h"

int LoadSpriteSheetTexture(SDL_Texture **texture, SDL_Renderer *screenRenderer, const char * filePath)
{
    SDL_Surface *rawImage = IMG_Load(filePath);
    if(rawImage == NULL)
    {
        printf("Unable to load the raw image in Path %s\n%s", filePath, SDL_GetError());
        return 0;
    }
    else
    {
        if(screenRenderer == NULL)
        {
            printf("Unable to get renderer...\n");
            exit(1);
        }
        *texture = SDL_CreateTextureFromSurface(screenRenderer, rawImage);
        if(*texture != NULL)
        {
            printf("Image conversion succesfull! -- %s\n", filePath);
            return 1;
        }
        else
        {
            printf("Image conversion failed! -- %s\n", filePath);
            return 0;
        }
        SDL_FreeSurface(rawImage);
    }
}




