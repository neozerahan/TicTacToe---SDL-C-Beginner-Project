#ifndef UI_H
#define UI_H

#include "SDL2/SDL.h"
#include "gameObjects.h"
#include "fontHandler.h"

void FadeOut(CustomRect *transRect, SDL_Renderer *renderer, SDL_Texture *transTexture,
        Uint8 NEXT_TRANS_STATE, Uint16 fadeSpeed, SDL_Rect *screenRect);

void FadeIn(CustomRect *transRect, SDL_Renderer *renderer, SDL_Texture *transTexture,
        Uint8 NEXT_TRANS_STATE, Uint16 fadeSpeed, SDL_Rect *screenRect);

void DrawButton(Button *button, SDL_Renderer *renderer, SDL_Window *window, int x, 
        int y, int collisionOffSetX, int collisionOffsetY, uint8_t allign , uint8_t showCollisionBox);

#endif
