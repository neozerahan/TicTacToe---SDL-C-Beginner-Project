#include "../Include/windowHandler.h"
#include "../Include/SDL2/SDL_image.h"
#include <stdio.h>

int CreateWindow(WindowInfo *window)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL. %s\n", SDL_GetError());
        return 0;
    }
    else
    {
        printf("SDL initialized!\n");
    }

    window->mainWindow = SDL_CreateWindow("Hello Triangle", window->x , 
            window->y, window->width, window->height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(window == NULL)
    {
        printf("Unable to create window -- %s\n", SDL_GetError());                 
        return 0;
    }
    else
    {
        printf("Window Creation successful!\n");                 
        window->mainRenderer  = SDL_CreateRenderer(window->mainWindow, -1, SDL_RENDERER_ACCELERATED);
    }

    return 1;
}

void CloseWindow(WindowInfo *window)
{
    SDL_DestroyRenderer(window->mainRenderer);
    window->mainRenderer = NULL;

    SDL_DestroyWindow(window->mainWindow);
    window->mainWindow = NULL;

    IMG_Quit();   
    SDL_Quit();
    printf("SDL Quit successful!\n");
}

void RenderWindow(WindowInfo gameWindow)
{
    //Painting the window renderer to grey color...
    SDL_SetRenderDrawColor(gameWindow.mainRenderer, 80,80,80, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gameWindow.mainRenderer);
    SDL_RenderPresent(gameWindow.mainRenderer);
}