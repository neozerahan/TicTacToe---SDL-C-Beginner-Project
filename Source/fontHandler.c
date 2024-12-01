#include "..\Include\fontHandler.h"

void CreateFont(TTF_Font **font)
{
    *font = TTF_OpenFont("../Resource/Fonts/OpenSans.ttf", 25); 
    if(font == NULL)
    {
        printf("Unable to load font... %s\n", SDL_GetError());
        return;
    }
}

void DrawText(Text *text, SDL_Renderer *renderer, TTF_Font *font,unsigned char allign)
{
    SDL_Surface *textSurface = TTF_RenderText_Blended(font,text->text, text->color); 
    if(textSurface == NULL)
    {
        printf("Unable to initialize the text surface...%s\n", SDL_GetError());
        return; 
    }

    text->texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(text->texture == NULL)
    {
        printf("Unable to initialize the text texture...%s\n", SDL_GetError());
        return; 
    }

    if(allign & ALLIGN_MID)
    {
        text->rect.x -= textSurface->w * 0.5;
        //printf("Allign Mid!\n");
    }
    else if (allign & ALLIGN_RIGHT)
    {
        text->rect.x += textSurface->w;
        //printf("Allign Right!\n");
    }
    else if ( allign & ALLIGN_LEFT)
    {
        //text->rect.x -= textSurface->w;
        printf("Allign Left!\n");
    }

    text->rect.w *= textSurface->w;
    text->rect.h *= textSurface->h;
    //SDL_RenderCopy(renderer, text->texture, 0, &text->rect);
    SDL_FreeSurface(textSurface);
}

//TODO: Make a seprate function to initialize the font rect so that we don't have to do it
//everytime we render the font...
void InitializeText(Text *text, SDL_Renderer *renderer, TTF_Font *font, unsigned int x, unsigned int y ,
        char * textInput, unsigned char allign)
{
    SDL_Color whiteColor = {255,255,255,255};
    text->color = whiteColor; 
    SDL_Rect textGameTitleRect = {x,y, 1,1};
    text->rect = textGameTitleRect;
    text->text = textInput;
    DrawText(text, renderer, font, allign);
}
