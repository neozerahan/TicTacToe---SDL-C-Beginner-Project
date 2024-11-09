#ifndef WINDOW_HANDLER_H
#define WINDOW_HANDLER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"

typedef struct windowInfo
{
    int x;
    int y;
    int width;
    int height;
    SDL_Rect *rect;
    SDL_Window *mainWindow;
    SDL_Renderer *mainRenderer;
} WindowInfo;

void RenderWindow(WindowInfo gameWindow);
int CreateWindow(WindowInfo *window);
void CloseWindow(WindowInfo *window);

#endif
