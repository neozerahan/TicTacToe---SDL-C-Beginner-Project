#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"


typedef struct Renderer
{
    SDL_Rect rect;
}Renderer;

typedef struct Text
{
    SDL_Color color;
    SDL_Rect rect;
    SDL_Surface *surface;
    SDL_Texture *texture;
    char *text;
}Text;

typedef struct gameData
{
    int isRunning;
    SDL_Event event;
    int canDraw;
    struct Player * player01;
    struct Player * player02;
    int currentTurn;
    SDL_Texture *spriteSheet;
    TTF_Font *font;
    Text turnText;
    Text titleText;
    Text currentTurnText;
}gameData;

typedef struct CellCollisionBox
{
    unsigned int x1;
    unsigned int x2;
    unsigned int y1;
    unsigned int y2;
}CellCollisionBox;

typedef struct Cell
{
    SDL_Rect rect;
    int playerNumber;
    CellCollisionBox collisionBox;
}Cell;

typedef struct CellData
{
    SDL_Texture *cellTexture;
    Cell *cellCollection;
}CellData;

typedef struct Player
{
    unsigned short int turnCount;       //The player's current turn count. Max = 3...
    unsigned short int playerNumber;    //Either player 1 or 2...
    SDL_Rect playerTexRect;            //Position of the texture in the sprite sheet...
}Player;

#endif


