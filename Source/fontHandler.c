#include "..\Include\fontHandler.h"
#include <stdint.h>

void CreateFont(TTF_Font **font)
{
    *font = TTF_OpenFont("../Resource/Fonts/OpenSans.ttf", 25); 
    if(font == NULL)
    {
        printf("Unable to load font... %s\n", SDL_GetError());
        return;
    }
}

int CreateText(Text *textObj, char *text, SDL_Renderer *renderer, TTF_Font *font, 
        SDL_Color color)
{
    //Surface creation...
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, color); 
    if(textSurface == NULL) 
    {
        printf("Unable to create surface during font creation\n");
        return 0;
    }

    //Font texture... 
    textObj->texture = SDL_CreateTextureFromSurface(renderer, textSurface); 
    if(textObj->texture == NULL)
    {
        printf("Unable to create texture during font creation\n");
        return 0;
    }

    //Initialize size...
    textObj->rect.h = textSurface->h;
    textObj->rect.w = textSurface->w;
    textObj->rect.x = 0;
    textObj->rect.y = 0;

    printf("Initialized Font successfully: %s\n", text);
    return 1;
}

int ShowText(Text *textObj, SDL_Renderer *renderer, int x, int y, uint8_t allign)
{

    if(renderer == NULL)
    {
        printf("Cannot draw text. Renderer is NULL!\n");
        return 0;
    }

    if(allign == 0)
        textObj->rect.x = x;
    else if(allign == ALLIGN_MID) 
        textObj->rect.x = x - textObj->rect.w * 0.5;
    else if(allign == ALLIGN_RIGHT)
        textObj->rect.x = x - textObj->rect.w;

    textObj->rect.y = y;

    SDL_RenderCopy(renderer, textObj->texture, NULL, &textObj->rect);
    return 1;
}
