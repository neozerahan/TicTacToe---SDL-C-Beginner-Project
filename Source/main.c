#include <stdint.h>
#include<stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include "../Include/global.h"
#include "../Include/windowHandler.h"
#include "../Include/drawing.h"
#include "../Include\collision.h"
#include "../Include\logic.h"
#include "../Include\fontHandler.h"

void ProcessEvents(gameData *currentGameData);

int InitializeCellData(CellData *cellData, WindowInfo gameWindow, 
        Renderer *boardDrawData, SDL_Texture *spriteSheet);

int InitializeBoardDrawData(Renderer *boardDrawData,WindowInfo gameWindow, SDL_Texture *spriteSheet);

int InitializeGameData(gameData *currentGameData, SDL_Renderer *gameWindowRenderer, Player *player01, Player *player02);

int main()
{

    TTF_Init();         

    //--------------------------------------------//
    //INITIALIZE WINDOW...
    WindowInfo gameWindow = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, 
        SCREEN_HEIGHT, NULL, NULL};

    CreateWindow(&gameWindow);
    RenderWindow(gameWindow);

    //--------------------------------------------//

    //INITIALIZE PLAYERS...
    Player player01 = {0, 1, 0};  
    InitializeRect(&player01.playerTexRect, O_SHAPE);

    Player player02 = {0, 2, 0};  
    InitializeRect(&player02.playerTexRect, X_SHAPE);

    //--------------------------------------------//

    //INITIALIZE GAME DATA...
    gameData currentGameData = {0};
    InitializeGameData(&currentGameData, gameWindow.mainRenderer, &player01, &player02);

    //--------------------------------------------//

    //INIT BOARD RENDERER...
    Renderer boardDrawData = {0};
    InitializeBoardDrawData(&boardDrawData, gameWindow , currentGameData.spriteSheet);

    //--------------------------------------------//

    //INITIALIZE CELLS...
    CellData cellData = {0};
    InitializeCellData(&cellData, gameWindow, &boardDrawData, currentGameData.spriteSheet);

    //--------------------------------------------//

    RenderText(currentGameData, gameWindow.mainRenderer, gameWindow.rect, 
            &boardDrawData.rect);

    SDL_RenderPresent(gameWindow.mainRenderer);

       //GAME LOOP...
    while(currentGameData.isRunning)
    {
        while(SDL_WaitEvent(&currentGameData.event))
        {
            //EVENTS...
            ProcessEvents(&currentGameData);

            //QUIT GAME...
            if(currentGameData.isRunning == FALSE) break;

            //GAMEPLAY LOGIC...
            if(logic(&currentGameData, gameWindow, &cellData))
            {
                //RENDERING...
                SDL_RenderClear(gameWindow.mainRenderer);
                RenderBoard(gameWindow, currentGameData, &cellData, &boardDrawData);
                SDL_RenderPresent(gameWindow.mainRenderer);
            }
        }

        //FREE RESOURCE...
        SDL_DestroyTexture(currentGameData.spriteSheet);
        free(cellData.cellCollection);

        CloseWindow(&gameWindow);

        return 0;
    }
}

void ProcessEvents(gameData *currentGameData)
{
    //Click the close button...
    if(currentGameData->event.type == SDL_QUIT)
    {
        printf("Quit requested!\n");
        currentGameData->isRunning = FALSE;
    } 

    //Press Escape...
    if(currentGameData->event.type == SDL_KEYDOWN)
    {
        printf("Keyboard pressed!\n");
        if(currentGameData->event.key.keysym.sym==SDLK_ESCAPE)
        {
            currentGameData->isRunning = FALSE;
        }
    }

    if(currentGameData->event.type == SDL_MOUSEBUTTONDOWN)
    {
        //if it is left-mouse button..
        if(currentGameData->event.button.button == 1)
        { 
            currentGameData->canDraw =  TRUE;
        }
    }
}

int InitializeCellData(CellData *cellData, WindowInfo gameWindow, 
        Renderer *boardDrawData, SDL_Texture *spriteSheet)
{
    cellData->cellCollection = malloc((ROWS * COLUMNS) * sizeof(Cell));

    if(cellData->cellCollection == NULL)
    {
        printf("Unable to initialize memmory for Cell Collection...\n");
        return FALSE;
    }

    int cellCount = 0;
    for(int i =0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {

            InitializeRect(&cellData->cellCollection[cellCount].rect, CELL_SIZE * j , CELL_SIZE * i, 
                    CELL_SIZE, CELL_SIZE);
            cellData->cellCollection[cellCount].playerNumber = 0;
            cellCount++;
        }
    }

    SetCellDetectionBox(cellData);

    DrawCells(cellData->cellCollection, gameWindow, *boardDrawData, spriteSheet);

    return TRUE;
}

int InitializeBoardDrawData(Renderer *boardDrawData,WindowInfo gameWindow, SDL_Texture *spriteSheet)
{

    SDL_Rect boardDrawDataRect = { (SCREEN_WIDTH * 0.5) - 
        (BOARD_RESOLUTION * 0.5), (SCREEN_HEIGHT * 0.5) - (BOARD_RESOLUTION * 0.5) + 10, 
            BOARD_RESOLUTION, BOARD_RESOLUTION};

    boardDrawData->rect = boardDrawDataRect;

    DrawBoard(boardDrawData, gameWindow, spriteSheet);

    return 1;
}

int InitializeGameData(gameData *currentGameData, SDL_Renderer *gameWindowRenderer, Player *player01, Player *player02)
{
    currentGameData->isRunning = TRUE;
    currentGameData->canDraw = FALSE;
    currentGameData->player01 = player01;
    currentGameData->player02 = player02;
    currentGameData->currentTurn = PLAYER_1_TURN;

    if(!LoadSpriteSheetTexture(&currentGameData->spriteSheet, gameWindowRenderer, 
                "../Resource/PNG/SpriteSheet.png"))
    {
        printf("Loading image Sprite Sheet texture...%s\n", SDL_GetError());
        return 0;
    }

    CreateFont(&currentGameData->font); 
    if(currentGameData->font == NULL)
    {
        printf("Unable to initialize the font...%s\n", SDL_GetError());
        return 0;
    }
    currentGameData->turnText.text = "Player 1"; 
    currentGameData->currentTurnText.text = "Current Turn:";
    currentGameData->titleText.text = "TIC TAC TOE";

    return 1;
}
