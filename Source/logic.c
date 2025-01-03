#include "..\Include\logic.h"
#include <stdint.h>

int logic(gameData *currentGameData,WindowInfo gameWindow, CellData *cellData)
{
    unsigned char result = 0;
    if(currentGameData->canDraw)
    {
        int cellNum = CheckCellDetection(currentGameData->mousePos.x, 
                currentGameData->mousePos.y, cellData); 

        //if cell number is within the cell count...
        if(cellNum >= 0 & cellNum <= 8)
        {
            //Check if cell is occupied...
            if(cellData->cellCollection[cellNum].playerNumber > 0) 
            {
                printf("This cell is occupied!\n");
                currentGameData->canDraw = FALSE;
                return FALSE;
            }

            //Process Player 1 turn...
            else if(currentGameData->currentTurn == PLAYER_1_TURN)
            {
                ProcessPlayerTurn(gameWindow, currentGameData, currentGameData->player01, 
                        cellData, cellNum, PLAYER_1_TURN, PLAYER_2_TURN);
            }

            //Process Player 2 turn...
            else if(currentGameData->currentTurn == PLAYER_2_TURN)
            {
                 ProcessPlayerTurn(gameWindow, currentGameData, currentGameData->player02, 
                         cellData, cellNum, PLAYER_2_TURN, PLAYER_1_TURN);
            }
            result = TRUE;
        }
        else
        {
            result = FALSE;
        }

        currentGameData->canDraw = FALSE;
    }
        return result;
}

void ProcessPlayerTurn(WindowInfo gameWindow, gameData *currentGameData, Player * player,
        CellData *cellData, int cellNum, const unsigned short int currentPlayerNumber, 
        const unsigned short int nextPlayerNumber)
{
    cellData->cellCollection[cellNum].playerNumber = currentPlayerNumber; 
    player->turnCount++;
    currentGameData->currentTurn =  nextPlayerNumber;

    //Only check win condition if more than 2 turns have passed...
    if(player->turnCount > 2)
    {
       if(CheckWin(cellNum, cellData->cellCollection, currentPlayerNumber))
       {
           if(currentPlayerNumber == PLAYER_1_TURN)
           {
               currentGameData->didWin = PLAYER_1_TURN; 
           }
           else
           {
               currentGameData->didWin = PLAYER_2_TURN; 
           }

           printf("Player %d WINS!\n", currentPlayerNumber);
       }
    }

    //Draw if current players turncount has placed more than 6 shapes
    //and has not yet won, then it is DRAW...
    if(player->turnCount >= 5)
    {
        if(currentGameData->didWin == 0)
        {
            currentGameData->didWin = GAME_IS_DRAW;
            printf("GAME IS A DRAW!!!");
        }
    }
}

uint8_t CheckWin(int selectedCell, Cell *cellCollection, uint8_t currentPlayerNumber)
{
    //CHECK FIRST ROW...
    if(selectedCell == 0)
    {
        printf("Check FIRST ROW - DIAGONAL HORIZONTAL\n");
        if(CheckCellForWin(cellCollection, FIRST_ROW_ID, currentPlayerNumber, DIRECTION_HORIZONTAL))
            return TRUE;

        printf("Check FIRST ROW - DIAGONAL VERTICAL\n");
        if(CheckCellForWin(cellCollection, FIRST_ROW_ID, currentPlayerNumber, DIRECTION_VERTICAL))
            return TRUE;

        printf("Check FIRST COLUMN - DIAGONAL\n");
        if(CheckCellForWin(cellCollection, FIRST_ROW_ID, currentPlayerNumber, DIRECTION_DIAGONAL))
            return TRUE;
    }

    if(selectedCell == 1)
    {
        printf("Check FIRST ROW - HORIZONTAL\n");
        if(CheckCellForWin(cellCollection, FIRST_ROW_ID, currentPlayerNumber, DIRECTION_HORIZONTAL))
            return TRUE;

        printf("Check SECOND COLUMN - VERTICAL\n");
        if(CheckCellForWin(cellCollection, SECOND_COLUMN_ID, currentPlayerNumber, DIRECTION_VERTICAL))
            return TRUE;
    }

    if(selectedCell == 2)
    {
        printf("Check FIRST ROW - HORIZONTAL\n");
        if(CheckCellForWin(cellCollection, FIRST_ROW_ID, currentPlayerNumber, DIRECTION_HORIZONTAL))
            return TRUE;

        printf("Check THIRD COLUMN - VERTICAL\n");
        if(CheckCellForWin(cellCollection, THIRD_COLUMN_ID, currentPlayerNumber, DIRECTION_VERTICAL))
            return TRUE;

        printf("Check THIRD COLUMN - REVERSE DIAGONAL\n");
        if(CheckCellForWin(cellCollection, THIRD_COLUMN_ID, currentPlayerNumber, 
                    DIRECTION_REVERSE_DIAGONAL))
            return TRUE;
    }

    if(selectedCell == 3)
    {
        printf("Check SECOND ROW - HORIZONTAL\n");
        if(CheckCellForWin(cellCollection, SECOND_ROW_ID, currentPlayerNumber, DIRECTION_HORIZONTAL))
            return TRUE;

        printf("Check FIRST ROW - VERTICAL\n");
        if(CheckCellForWin(cellCollection, FIRST_ROW_ID, currentPlayerNumber, DIRECTION_VERTICAL))
            return TRUE;
    }

    if(selectedCell == 4)
    {
        printf("Check SECOND ROW - HORIZONTAL\n");
        if(CheckCellForWin(cellCollection, SECOND_ROW_ID, currentPlayerNumber, DIRECTION_HORIZONTAL))
            return TRUE;

        printf("Check SECOND COLUMN - VERTICAL\n");
        if(CheckCellForWin(cellCollection, SECOND_COLUMN_ID, currentPlayerNumber, DIRECTION_VERTICAL))
            return TRUE;

        printf("Check THIRD COLUMN - DIAGONAL\n");
        if(CheckCellForWin(cellCollection, THIRD_COLUMN_ID, currentPlayerNumber, 
                    DIRECTION_REVERSE_DIAGONAL))
            return TRUE;

        printf("Check FIRST COLUMN - DIAGONAL\n");
        if(CheckCellForWin(cellCollection, FIRST_ROW_ID, currentPlayerNumber, DIRECTION_DIAGONAL))
            return TRUE;
    }

    if(selectedCell == 5)
    {
        printf("Check SECOND ROW - HORIZONTAL\n");
        if(CheckCellForWin(cellCollection, SECOND_ROW_ID, currentPlayerNumber, DIRECTION_HORIZONTAL))
            return TRUE;

        printf("Check THIRD COLUMN - VERTICAL\n");
        if(CheckCellForWin(cellCollection, THIRD_COLUMN_ID, currentPlayerNumber, DIRECTION_VERTICAL))
            return TRUE;
    }

    if(selectedCell == 6)
    {
        printf("Check FIRST ROW - VERTICAL\n");
        if(CheckCellForWin(cellCollection, FIRST_ROW_ID, currentPlayerNumber, DIRECTION_VERTICAL))
            return TRUE;

        printf("Check THIRD ROW - HORIZONTAL \n");
        if(CheckCellForWin(cellCollection, THIRD_ROW_ID, currentPlayerNumber, DIRECTION_HORIZONTAL))
            return TRUE;

        printf("Check THIRD COLUMN - REVERSE DIAGONAL\n");
        if(CheckCellForWin(cellCollection, THIRD_COLUMN_ID, currentPlayerNumber, 
                    DIRECTION_REVERSE_DIAGONAL))
            return TRUE;
    }

    if(selectedCell == 7)
    {
        printf("Check THIRD ROW - HORIZONTAL\n");
        if(CheckCellForWin(cellCollection, THIRD_ROW_ID, currentPlayerNumber, DIRECTION_HORIZONTAL))
            return TRUE;

        printf("Check SECOND COLUMN - VERTICAL\n");
        if(CheckCellForWin(cellCollection, SECOND_COLUMN_ID, currentPlayerNumber, DIRECTION_VERTICAL))
            return TRUE;
    }

    if(selectedCell == 8)
    {
        printf("Check  THIRD ROW - HORIZONTAL\n");
        if(CheckCellForWin(cellCollection, THIRD_ROW_ID, currentPlayerNumber, DIRECTION_HORIZONTAL))
            return TRUE;

        printf("Check THIRD COLUMN - VERTICAL\n");
        if(CheckCellForWin(cellCollection, THIRD_COLUMN_ID, currentPlayerNumber, DIRECTION_VERTICAL))
            return TRUE;

        printf("Check FIRST COLUMN - DIAGONAL\n");
        if(CheckCellForWin(cellCollection, FIRST_ROW_ID, currentPlayerNumber, DIRECTION_DIAGONAL))
            return TRUE;
    }
    return FALSE;
}


uint8_t CheckCellForWin(Cell *cellCollection, uint8_t rowID, int currentPlayerNumber, 
        uint8_t direction)
{
    const uint8_t NUMBER_OF_CELLS_TO_CHECK = 2; 

    uint8_t maxCellToCheck = rowID + direction * NUMBER_OF_CELLS_TO_CHECK;
    
    for(int i = rowID; i <= maxCellToCheck; i+=direction)
    {
        printf("Processing check for next cell and same cell!\n");
        printf("Cell Player Number = %d\n", cellCollection[i].playerNumber);
        printf("current Player Number = %d\n", currentPlayerNumber);
        if(cellCollection[i].playerNumber != currentPlayerNumber)
        {
            return FALSE;
        }
    }
    return TRUE;
}
