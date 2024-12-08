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
#include "../Include\UI.h"

void ProcessEvents(gameData *currentGameData);

int InitializeCellData(CellData *cellData, WindowInfo gameWindow, 
        Renderer *boardDrawData, SDL_Texture *spriteSheet);

int InitializeBoardDrawData(Renderer *boardDrawData,WindowInfo gameWindow, SDL_Texture *spriteSheet);

int InitializeGameData(gameData *currentGameData, SDL_Renderer *gameWindowRenderer, Player *player01, Player *player02);

void InitializeButton(Button *button, char * text, TTF_Font *font, 
        SDL_Renderer *renderer, SDL_Color fontColor);

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
  
    SDL_Color white = {COLOR_WHITE};
    
    //INITIALIZE BUTTON OBJECTS...
    Button newGameButton = {0};
    InitializeButton(&newGameButton, "New Game", currentGameData.font, gameWindow.mainRenderer, 
             white);

    Button quitGameButton = {0};
    InitializeButton(&quitGameButton, "Quit Game", currentGameData.font, 
            gameWindow.mainRenderer, white);

    //--------------------------------------------//
    
    //Used for transitioning screen...
    CustomRect transRect = {
        {0,0,800,600},
        {0,0,0,255},
        0,
    };

    //TARGET FPS SET TO 60 in globals.h....
    int desiredFPSInMS = 1000/TARGET_FPS;

    //--------------------------------------------//
    //GAME LOOP...
    while(currentGameData.isRunning)
    {
        int lastFrameTime = SDL_GetTicks();
        //MENU STATE...
        if(currentGameData.gameState == GAME_STATE_MENU)
        {
            while(SDL_PollEvent(&currentGameData.event))
            {
                //EVENTS...
                ProcessEvents(&currentGameData);

                //QUIT GAME...
                if(currentGameData.isRunning == FALSE) break;

                //PRESS NEW GAME BUTTON...
                if(CheckCollision(newGameButton.collisionBox, currentGameData.mousePos) == TRUE)
                {
                    transRect.transState = TRANS_STATE_IN;        
                    currentGameData.mousePos.x = 0;
                    currentGameData.mousePos.y = 0;
                }

                //PRESS QUIT GAME BUTTON...
                if(CheckCollision(quitGameButton.collisionBox, currentGameData.mousePos))
                {
                    currentGameData.isRunning = FALSE;
                }
            }

            //Rendering in MAIN MENU STATE...
            if(transRect.transState == TRANS_STATE_NONE || transRect.transState == 
                    TRANS_STATE_OUT_MENU)
            {
                SDL_SetRenderDrawColor(gameWindow.mainRenderer , 128,128,128,255);
                SDL_RenderClear(gameWindow.mainRenderer);
                SDL_Rect menuRenderRect = {140, 100, 512, 512};

                SDL_RenderSetViewport(gameWindow.mainRenderer, &menuRenderRect);

                ShowText(&currentGameData.titleText, gameWindow.mainRenderer, 512 * 0.5, 0, 
                        ALLIGN_MID);

                DrawButton(&newGameButton, gameWindow.mainRenderer, gameWindow.mainWindow,
                        512 * 0.5,currentGameData.titleText.rect.h + 100,140 ,100,ALLIGN_MID, FALSE);

                DrawButton(&quitGameButton, gameWindow.mainRenderer, gameWindow.mainWindow, 
                        512 * 0.5, newGameButton.rect.h + newGameButton.rect.y, 140,100,
                        ALLIGN_MID, FALSE);
            }

            if(transRect.transState == TRANS_STATE_OUT_MENU) {
                FadeOut(&transRect, gameWindow.mainRenderer, currentGameData.transitionTexture, 
                        TRANS_STATE_FINISH_MENU, 25, gameWindow.rect);
            }
            else if( transRect.transState == TRANS_STATE_FINISH_MENU)
            {
                transRect.transState = TRANS_STATE_NONE;

                currentGameData.gameState = GAME_STATE_MENU;

                for(int i = 0; i < ROWS*COLUMNS; i++)
                    cellData.cellCollection[i].playerNumber = 0;

                currentGameData.didWin = 0;
            }

            //ON FADE IN...
            if(transRect.transState == TRANS_STATE_IN)
            { 
                FadeIn(&transRect, gameWindow.mainRenderer, 
                        currentGameData.transitionTexture, TRANS_STATE_OUT, 25, gameWindow.rect);
            } 

            //ON FADE OUT...
            else if (transRect.transState == TRANS_STATE_OUT)
            {
                SDL_SetRenderDrawColor(gameWindow.mainRenderer , 128,128,128,255);
                SDL_RenderClear(gameWindow.mainRenderer);

                RenderScreen(gameWindow, currentGameData, &cellData, &boardDrawData);

                FadeOut( &transRect, gameWindow.mainRenderer, 
                        currentGameData.transitionTexture, TRANS_STATE_FINISH, 25, gameWindow.rect);
            }

            //ON FADE TRANSITION COMPLETE...
            else if(transRect.transState == TRANS_STATE_FINISH)
            {
                printf("In IN_TRANS_STATE_FINISH\n"); 
                currentGameData.gameState = GAME_STATE_IN_GAME;
                transRect.transState = TRANS_STATE_NONE;

                RenderScreen(gameWindow, currentGameData, &cellData, &boardDrawData);
            }

            SDL_RenderPresent(gameWindow.mainRenderer);
        }


        //IN GAME STATE...
        if(currentGameData.gameState == GAME_STATE_IN_GAME)
        {
            while(SDL_PollEvent(&currentGameData.event))
            {
                //EVENTS...
                ProcessEvents(&currentGameData);

                //QUIT GAME...
                if(currentGameData.isRunning == FALSE) break;
            }

            logic(&currentGameData, gameWindow, &cellData);

            //RENDERING...
            SDL_SetRenderDrawColor(gameWindow.mainRenderer , 128,128,128,255);
            SDL_RenderClear(gameWindow.mainRenderer);

            RenderScreen(gameWindow, currentGameData, &cellData, &boardDrawData);

            //If player 1 or player 2 wins the game...
            if(currentGameData.didWin == PLAYER_1_TURN || currentGameData.didWin == PLAYER_2_TURN)
            {
                DrawButton(&newGameButton, gameWindow.mainRenderer, gameWindow.mainWindow, 
                        SCREEN_WIDTH * 0.25, 500 + 25 , 0, 0, FALSE, FALSE);

                DrawButton(&quitGameButton, gameWindow.mainRenderer, gameWindow.mainWindow, 
                        SCREEN_WIDTH * 0.75, 500 + 25 , 0, 0, ALLIGN_RIGHT, FALSE);

                if(CheckCollision(newGameButton.collisionBox, currentGameData.mousePos))
                {
                    transRect.transState = TRANS_STATE_IN;
                    currentGameData.mousePos.x = 0;
                    currentGameData.mousePos.y = 0;
                }

                if(CheckCollision(quitGameButton.collisionBox, currentGameData.mousePos))
                {
                    currentGameData.isRunning = FALSE;
                }
            }

            //Fade in transition if new game button is pressed...
            if(transRect.transState == TRANS_STATE_IN)
            {
                FadeIn(&transRect, gameWindow.mainRenderer, currentGameData.transitionTexture, 
                        TRANS_STATE_OUT_MENU, 25, gameWindow.rect);
            }

            //Go to Menu once the transition fade-in is complete...
            if(transRect.transState == TRANS_STATE_OUT_MENU) 
                currentGameData.gameState = GAME_STATE_MENU;

            SDL_RenderPresent(gameWindow.mainRenderer);
        }

        int currentFrameTime = SDL_GetTicks();

        int deltaTime = currentFrameTime - lastFrameTime;

        if(deltaTime < desiredFPSInMS)
        {
            deltaTime = desiredFPSInMS - deltaTime;
            SDL_Delay(deltaTime);
        }
    }

    //FREE RESOURCE...
    SDL_DestroyTexture(currentGameData.spriteSheet);
    SDL_DestroyTexture(currentGameData.winTextP1.texture);
    SDL_DestroyTexture(currentGameData.winTextP2.texture);
    SDL_DestroyTexture(currentGameData.currentTurnText.texture);
    SDL_DestroyTexture(currentGameData.transitionTexture);
    SDL_DestroyTexture(currentGameData.turnTextP1.texture);
    SDL_DestroyTexture(currentGameData.turnTextP2.texture);
    SDL_DestroyTexture(currentGameData.titleText.texture);

    free(cellData.cellCollection);

    TTF_Quit();

    CloseWindow(&gameWindow);

    return 0;
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

        currentGameData->mousePos.x = currentGameData->event.motion.x;
        currentGameData->mousePos.y = currentGameData->event.motion.y;
        printf("Mouse Pos: %d\n", currentGameData->mousePos.x);

        if(currentGameData->gameState == GAME_STATE_MENU) return;

        if(currentGameData->didWin > 0) return;
        //if it is left-mouse button..
        if(currentGameData->event.button.button == SDL_BUTTON_LEFT)
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
    currentGameData->didWin = FALSE;

    if(!LoadSpriteSheetTexture(&currentGameData->spriteSheet, gameWindowRenderer, 
                "../Resource/PNG/SpriteSheet.png"))
    {
        printf("Loading image Sprite Sheet texture...%s\n", SDL_GetError());
        return 0;
    }

    if(!LoadSpriteSheetTexture(&currentGameData->transitionTexture, gameWindowRenderer, 
                "../Resource/PNG/Transition.png"))
    {
        printf("Loading image Transition texture...%s\n", SDL_GetError());
        return 0;
    }


    CreateFont(&currentGameData->font); 
    if(currentGameData->font == NULL)
    {
        printf("Unable to initialize the font...%s\n", SDL_GetError());
        return 0;
    }
    SDL_Color white = {COLOR_WHITE};
    
    CreateText(&currentGameData->titleText, "TIC TAC TOE", gameWindowRenderer, 
            currentGameData->font, white);  

    CreateText(&currentGameData->currentTurnText, "Current Turn:", gameWindowRenderer,
            currentGameData->font, white);

    CreateText(&currentGameData->turnTextP1, "Player 1", gameWindowRenderer, 
            currentGameData->font, white); 

    CreateText(&currentGameData->turnTextP2, "Player 2", gameWindowRenderer, 
            currentGameData->font, white); 

    CreateText(&currentGameData->winTextP1, "Player 1 Wins!!!", gameWindowRenderer, 
            currentGameData->font, white); 

    CreateText(&currentGameData->winTextP2, "Player 2 Wins!!!", gameWindowRenderer, 
            currentGameData->font, white); 
    
    currentGameData->gameState = GAME_STATE_MENU;

    return 1;
}

void InitializeButton(Button *button, char * text,TTF_Font *font, 
        SDL_Renderer *renderer, SDL_Color fontColor)
{
    if(renderer == NULL)
    {
        printf("Failed to initialize button because renderer is NULL... %s\n", SDL_GetError());
        return;
    }

    if(font == NULL)
    {
        printf("Failed to initialize button because font is NULL... %s\n", SDL_GetError());
        return;
    }

    //InitializeText(&button->text, renderer, font, x, y, text, ALLIGN_MID);     

    CreateText(&button->text, text, renderer, font, fontColor);

    button->rect = button->text.rect;

    button->collisionBox.x1 = button->rect.x; 
    button->collisionBox.x2 = button->rect.x + button->rect.w;
    button->collisionBox.y1 = button->rect.y;
    button->collisionBox.y2 = button->rect.y + button->rect.h;  
}
