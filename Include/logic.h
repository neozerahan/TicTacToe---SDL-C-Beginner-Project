#ifndef LOGIC_H
#define LOGIC_H
#include "..\Include\Drawing.h"
#include "fontHandler.h"

//Main game logic which includes check for collision, processing player turn, etc...
int logic(gameData *currentGameData, WindowInfo gameWindow, 
        CellData *cellData);

// Process the player turn which includes drawing, setting the values, etc...
void ProcessPlayerTurn(WindowInfo gameWindow, gameData *currentGameData, Player * player ,
        CellData *cellData, int cellNum, const unsigned short int currentPlayerNumber, 
        const unsigned short int nextPlayerNumber);

uint8_t CheckCellForWin(Cell *cellCollection, uint8_t rowID, int currentPlayerNumber,
        uint8_t direction);

uint8_t CheckWin(int selectedCell, Cell *cellCollection, uint8_t currentPlayerNumber);
#endif
