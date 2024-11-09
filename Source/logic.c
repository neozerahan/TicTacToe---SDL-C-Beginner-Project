#include "..\Include\logic.h"

int logic(gameData *currentGameData,WindowInfo gameWindow, CellData *cellData)
{
    unsigned char result = 0;
    if(currentGameData->canDraw)
    {
        Sint32 xMouse = 0;
        Sint32 yMouse = 0;

        xMouse = currentGameData->event.motion.x;
        yMouse = currentGameData->event.motion.y;

        int cellNum = CheckCellDetection(xMouse, yMouse, cellData); 

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

            //RenderBoard(gameWindow, *currentGameData,cellCollection);
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
}

//LOGIC FOR CHECKING WIN CONDITION...
// --> Make a check function...
// --> make it work horizontal i.e i+1  (1,2,3)
// --> make it work vertical i.e i+3    (1,4,7) 
// --> make it work diagonally i.e i+4  (1,5,9) 
// --> make an array which checks based on the cell number i.e if 2 then it will check the
// necessary cells for matching shapes...
