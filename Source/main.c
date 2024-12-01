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

void InitializeButton(Button *button, char * text, int x, int y, TTF_Font *font, 
        SDL_Renderer *renderer, int collisionOffsetX, int collisionOffsetY);

void FadeIn(CustomRect *transRect, SDL_Renderer *renderer, SDL_Texture *transTexture,
        Uint8 NEXT_TRANS_STATE, Uint16 fadeSpeed, SDL_Rect *screenRect);

void FadeOut(CustomRect *transRect, SDL_Renderer *renderer, SDL_Texture *transTexture,
        Uint8 NEXT_TRANS_STATE, Uint16 fadeSpeed, SDL_Rect *screenRect);

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

    //INITIALIZE TEXT OBJECTS...
    InitializeText(&currentGameData.titleText, gameWindow.mainRenderer, currentGameData.font,
            512/2, 0, "TIC TAC TOE",ALLIGN_MID);

    InitializeText(&currentGameData.currentTurnText,gameWindow.mainRenderer, currentGameData.font,
            SCREEN_WIDTH * 0.5 - 150, 65, "Current Turn: ", ALLIGN_LEFT);

    InitializeText(&currentGameData.turnTextP1, gameWindow.mainRenderer, currentGameData.font, 
            currentGameData.currentTurnText.rect.x + 
            currentGameData.currentTurnText.rect.w + 25 
            , currentGameData.currentTurnText.rect.y, 
            "Player 01", ALLIGN_LEFT);

    InitializeText(&currentGameData.turnTextP2, gameWindow.mainRenderer, currentGameData.font, 
            currentGameData.currentTurnText.rect.x + 
            currentGameData.currentTurnText.rect.w + 25 
            , currentGameData.currentTurnText.rect.y, 
            "Player 02", ALLIGN_LEFT);

    InitializeText(&currentGameData.winTextP1, gameWindow.mainRenderer, currentGameData.font, SCREEN_CENTER,
               88-25, "Player 1 Wins!!!",ALLIGN_MID);

    InitializeText(&currentGameData.winTextP2, gameWindow.mainRenderer, currentGameData.font, SCREEN_CENTER,
               88-25, "Player 2 Wins!!!",ALLIGN_MID);

    //--------------------------------------------//
    
    //INITIALIZE BUTTON OBJECTS...

    Button newGameButton = {0};
    InitializeButton(&newGameButton, "New Game", 512/2, currentGameData.titleText.rect.h + 100, 
            currentGameData.font, gameWindow.mainRenderer, 140, 100);

    Button quitGameButton = {0};
    InitializeButton(&quitGameButton, "Quit Game", 512/2, newGameButton.rect.h + 
            newGameButton.rect.y + 25, currentGameData.font, gameWindow.mainRenderer, 140, 
            100);

    //--------------------------------------------//
   
    CustomRect transRect = {
        {0,0,800,600},
        {0,0,0,255},
        0,
    };

    //--------------------------------------------//
    //GAME LOOP...
    while(currentGameData.isRunning)
    {

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
            if(transRect.transState == TRANS_STATE_NONE)
            {
                SDL_RenderClear(gameWindow.mainRenderer);

                SDL_Rect menuRenderRect = {140, 100, 512, 512};

                SDL_RenderSetViewport(gameWindow.mainRenderer, &menuRenderRect);

                SDL_RenderCopy(gameWindow.mainRenderer, currentGameData.titleText.texture,0, 
                        &currentGameData.titleText.rect);

                SDL_RenderCopy(gameWindow.mainRenderer, newGameButton.text.texture, 0, 
                        &newGameButton.text.rect);

                SDL_RenderCopy(gameWindow.mainRenderer, quitGameButton.text.texture, 0, 
                        &quitGameButton.text.rect);
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
                SDL_RenderClear(gameWindow.mainRenderer);

                RenderScreen(gameWindow, currentGameData, &cellData, &boardDrawData);

                FadeOut( &transRect, gameWindow.mainRenderer, 
                        currentGameData.transitionTexture, TRANS_STATE_FINISH, 25, gameWindow.rect);
            }

            //ON FADE TRANSITION COMPLETE...
            else if(transRect.transState == TRANS_STATE_FINISH)
            {
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

            //GAMEPLAY LOGIC...
            if(logic(&currentGameData, gameWindow, &cellData))
            {
                //RENDERING...
                SDL_RenderClear(gameWindow.mainRenderer);

                RenderScreen(gameWindow, currentGameData, &cellData, &boardDrawData);

                SDL_RenderPresent(gameWindow.mainRenderer);
            }
        }

        SDL_Delay(16);
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

        if(currentGameData->gameState == GAME_STATE_MENU) return;

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
    currentGameData->currentTurnText.text = "Current Turn:";
    currentGameData->titleText.text = "TIC TAC TOE";
    currentGameData->gameState = GAME_STATE_MENU;

    return 1;
}

void InitializeButton(Button *button, char * text, int x, int y, TTF_Font *font, 
        SDL_Renderer *renderer, int collisionOffsetX, int collisionOffsetY)
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

    InitializeText(&button->text, renderer, font, x, y, text, ALLIGN_MID);     

    button->rect.h = button->text.rect.h;
    button->rect.w = button->text.rect.w;
    button->rect.x = button->text.rect.x;
    button->rect.y = button->text.rect.y;

    button->collisionBox.x1 = button->rect.x + collisionOffsetX;
    button->collisionBox.x2 = button->rect.x + button->rect.w + collisionOffsetX;
    button->collisionBox.y1 = button->rect.y + collisionOffsetY;
    button->collisionBox.y2 = button->rect.y + button->rect.h + collisionOffsetY;  
}

void FadeIn(CustomRect *transRect, SDL_Renderer *renderer, SDL_Texture *transTexture,
        Uint8 NEXT_TRANS_STATE, Uint16 fadeSpeed, SDL_Rect *screenRect)
{
    SDL_RenderSetViewport(renderer, screenRect);
    SDL_SetTextureBlendMode(transTexture, SDL_BLENDMODE_BLEND);
    if(transRect->alphaValue <= 255)
    {
        SDL_SetTextureAlphaMod(transTexture, 
                transRect->alphaValue);

        SDL_RenderCopy(renderer, transTexture, 
                NULL, NULL);

        transRect->alphaValue += fadeSpeed;
        if(transRect->alphaValue >= 255) 
        {
            transRect->transState = NEXT_TRANS_STATE;
            transRect->alphaValue = 255;
        }
    }
}

void FadeOut(CustomRect *transRect, SDL_Renderer *renderer, SDL_Texture *transTexture,
        Uint8 NEXT_TRANS_STATE, Uint16 fadeSpeed, SDL_Rect *screenRect)
{
    SDL_RenderSetViewport(renderer, screenRect); 
    SDL_SetTextureBlendMode(transTexture, SDL_BLENDMODE_BLEND);
    if(transRect->alphaValue >= 0)
    {
        SDL_SetTextureAlphaMod(transTexture, 
                transRect->alphaValue);

        SDL_RenderCopy(renderer, transTexture, 
                NULL, NULL);

        transRect->alphaValue -= fadeSpeed;
        if(transRect->alphaValue <= 0) 
        {
            transRect->transState = NEXT_TRANS_STATE;
            transRect->alphaValue = 0;
        }
    }
}
