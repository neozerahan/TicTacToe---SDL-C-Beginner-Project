#ifndef FONTHANDLER_H
#define FONTHANDLER_H

#include "SDL2/SDL_render.h"
#include "gameObjects.h"
#include "global.h"
#include <stdio.h>

void CreateFont(TTF_Font **font);
void DrawText(Text *text, SDL_Renderer *renderer, TTF_Font *font, unsigned char allign 
        );
void InitializeText(Text *text, SDL_Renderer *renderer, TTF_Font *font, unsigned int x, 
        unsigned int y ,char * textInput, unsigned char allign);

int CreateText(Text *textObj, char *text , SDL_Renderer *renderer, TTF_Font *font, 
        SDL_Color color);

int ShowText(Text *textObj, SDL_Renderer *renderer, int x, int y, uint8_t allign);
#endif
