#include "..\Include\drawing.h"

void DrawBoard(Renderer *boardRenderer, WindowInfo gameWindow, SDL_Texture *spriteSheet)
{
    SDL_RenderSetViewport(gameWindow.mainRenderer, &boardRenderer->rect);
    SDL_Rect boardRendererTextureRect  = {BOARD_RENDERER_SHAPE};
    SDL_RenderCopy(gameWindow.mainRenderer, spriteSheet, &boardRendererTextureRect, NULL);
}

void DrawCells(Cell *cellCollection, WindowInfo gameWindow, Renderer boardRenderer, 
        SDL_Texture *cellTexture)
{
    int cellCount = 0;
    for(int i =0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            SDL_Rect cellTexturePos = {CELL_RENDERER_SHAPE};
            //Draw in the renderer...
            SDL_RenderCopy(gameWindow.mainRenderer, cellTexture, &cellTexturePos, 
                    &cellCollection[cellCount].rect);
            cellCount++;
        }
    }
}

void RenderBoard(WindowInfo gameWindow, 
        gameData currentGameData, CellData *cellData, Renderer *boardRenderer)
{
    if(currentGameData.spriteSheet == NULL)
    {
        printf("The sprite sheet is null. Cannot render shapes in screen!\n");
        return;
    }
    else if(gameWindow.mainRenderer == NULL)
    {
        printf("Unable to load the game window renderer while rending shapes!\n");
        return;
    }

    unsigned short cellCount = ROWS * COLUMNS;


    DrawBoard(boardRenderer, gameWindow, currentGameData.spriteSheet);

    DrawCells(cellData->cellCollection, gameWindow, *boardRenderer, currentGameData.spriteSheet);

    RenderText(currentGameData, gameWindow.mainRenderer, gameWindow.rect,
            &boardRenderer->rect);
    for(int i = 0; i < cellCount; i++)
    {
        SDL_Rect playerRect = {0};
        if(cellData->cellCollection[i].playerNumber == PLAYER_1_TURN)
        {
            printf("Drawing player 1!\n");
            playerRect = currentGameData.player01->playerTexRect;  
        }
        else if(cellData->cellCollection[i].playerNumber == PLAYER_2_TURN)
        {
            printf("Drawing player 2!\n");
            playerRect = currentGameData.player02->playerTexRect;  
        }
        SDL_RenderCopy(gameWindow.mainRenderer, currentGameData.spriteSheet, 
                &playerRect, &cellData->cellCollection[i].rect);
    }

}

void RenderText(gameData currentGameData, SDL_Renderer *textRenderer, SDL_Rect *textRendererRect,
          SDL_Rect *boardRendererRect)
{
    SDL_RenderSetViewport(textRenderer, textRendererRect);

    DrawTitleText(&currentGameData.titleText, textRenderer, currentGameData.font, SCREEN_CENTER, 0,
            currentGameData.titleText.text, ALLIGN_MID);

    DrawTitleText(&currentGameData.currentTurnText, textRenderer, currentGameData.font, 
            SCREEN_WIDTH * 0.5 - 150, 65 , currentGameData.currentTurnText.text, 
            ALLIGN_LEFT);

    if(currentGameData.currentTurn == PLAYER_1_TURN)
    {
        currentGameData.turnText.text = "Player 1";    
    }
    else
    {
        currentGameData.turnText.text = "Player 2";    
    }
 
    DrawTitleText(&currentGameData.turnText, textRenderer, currentGameData.font, 
            currentGameData.currentTurnText.rect.x + currentGameData.currentTurnText.rect.w + 25 
            , currentGameData.currentTurnText.rect.y, 
            currentGameData.turnText.text, ALLIGN_LEFT);

    SDL_RenderSetViewport(textRenderer, boardRendererRect);
}

void InitializeRect(SDL_Rect *rect, int x, int y, int width, int height )
{
    rect->x = x;
    rect->y = y;
    rect->w = width;
    rect->h = height;
}
