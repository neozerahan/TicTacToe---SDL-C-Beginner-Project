#ifndef FONTHANDLER_H
#define FONTHANDLER_H

#include "SDL2/SDL_render.h"
#include "gameObjects.h"
#include "global.h"
#include <stdio.h>

void CreateFont(TTF_Font **font);
void DrawText(Text *text, SDL_Renderer *renderer, TTF_Font *font, unsigned char allign 
        );
void DrawTitleText(Text *text, SDL_Renderer *renderer, TTF_Font *font, unsigned int x, 
        unsigned int y ,char * textInput, unsigned char allign);
#endif
