#ifndef DRAWING_H
#define DRAWING_H

#include <stdio.h>
#include "..\Include\SDL2\SDL.h"
#include "..\Include\imageLoader.h"
#include "..\Include\global.h"
#include "..\Include\windowHandler.h"
#include "..\Include\GameObjects.h"
#include "..\Include\collision.h"
#include "fontHandler.h"

void DrawCells(Cell *cellCollection,WindowInfo gameWindow, Renderer boardRenderer, SDL_Texture 
        *cellTexture);

void DrawPlayerShape(WindowInfo gameWindow, SDL_Texture * spriteSheet ,
        SDL_Rect cellRect, SDL_Rect  * playerRect);

void DrawBoard(Renderer *boardRenderer, WindowInfo gameWindow, SDL_Texture *spriteSheet);

void InitializeRect(SDL_Rect *rect, int x, int y, int width, int height);

void RenderBoard(WindowInfo gameWindow, 
        gameData currentGameData, CellData *cellData, Renderer *boardRenderer);

void RenderText(gameData currentGameData, SDL_Renderer *textRenderer, SDL_Rect *textRendererRect,
         SDL_Rect *boardRendererRect);
#endif
