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

void RenderScreen(WindowInfo gameWindow, 
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

    //Prints the PLAYER VICTORY.
    //#TODO: Create a function for below...
    if(currentGameData.didWin > FALSE)
    {
        SDL_RenderSetViewport(gameWindow.mainRenderer, gameWindow.rect);
        Text winText = {0}; 
        if(currentGameData.didWin == PLAYER_1_TURN)
        {
            winText.text = "Player 1 Wins!!!";
        }
        else if( currentGameData.didWin == PLAYER_2_TURN)
        {
            winText.text = "Player 2 Wins!!!";
        }

        DrawTitleText(&winText, gameWindow.mainRenderer, currentGameData.font, SCREEN_CENTER,
               88-25, winText.text,ALLIGN_MID);
    }
}

void RenderText(gameData currentGameData, SDL_Renderer *textRenderer, SDL_Rect *textRendererRect,
          SDL_Rect *boardRendererRect)
{
    SDL_RenderSetViewport(textRenderer, textRendererRect);

    DrawTitleText(&currentGameData.titleText, textRenderer, currentGameData.font, SCREEN_CENTER, 0,
            currentGameData.titleText.text, ALLIGN_MID);

   
    //Render the CURRENT PLAYER TEXT only if player does not win...
    if(currentGameData.didWin == FALSE)
    {
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
                currentGameData.currentTurnText.rect.x + 
                currentGameData.currentTurnText.rect.w + 25 
                , currentGameData.currentTurnText.rect.y, 
                currentGameData.turnText.text, ALLIGN_LEFT);

        //Draws player shape besides player turn...
        //TODO: Make this into a function...
        SDL_Rect shapeRect = {currentGameData.turnText.rect.x + 
            currentGameData.turnText.rect.w,currentGameData.turnText.rect.y 
                ,38,38};

        if(currentGameData.currentTurn == PLAYER_1_TURN)
        {
            SDL_RenderCopy(textRenderer, currentGameData.spriteSheet, 
                    &currentGameData.player01->playerTexRect, &shapeRect); 
        }
        else if( currentGameData.currentTurn == PLAYER_2_TURN)
        {
            SDL_RenderCopy(textRenderer, currentGameData.spriteSheet, 
                    &currentGameData.player02->playerTexRect, &shapeRect); 
        }
    }

    SDL_RenderSetViewport(textRenderer, boardRendererRect);
}

void InitializeRect(SDL_Rect *rect, int x, int y, int width, int height )
{
    rect->x = x;
    rect->y = y;
    rect->w = width;
    rect->h = height;
}
