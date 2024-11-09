#include "..\Include\collision.h"

int CheckCellDetection(Sint32 const xMouse, Sint32 const yMouse, 
        const CellData *cellData)
{
    int found = FALSE;
    int cellNum = 100;
    for(int i = 0; i < TOTAL_CELL_COUNT; i++)
    {
        if(xMouse > cellData->cellCollection[i].collisionBox.x1 
                & xMouse < cellData->cellCollection[i].collisionBox.x2
                & yMouse > cellData->cellCollection[i].collisionBox.y1 
                & yMouse < cellData->cellCollection[i].collisionBox.y2) 
        { 
            printf("Mouse is in the box %d\n", i + 1);
            printf("-------------------------\n");
            found = TRUE;
            cellNum = i;
            return cellNum; 
        }
    }

    if(!found)
    {
        printf("Mouse is outside!\n");
    }
    printf("Couldn't find Cell Num = %d\n", cellNum);
    return cellNum;
}

void SetCellDetectionBox(CellData *cellData)
{
    unsigned short counter = 0; 

    unsigned short int cellBaseXPos = 200;
    unsigned short int cellBaseYPos = 110;
    unsigned short cellSize = CELL_SIZE;

    printf("Cell Data!\n");

    for(int i = 0; i < ROWS; i++)
    {
        for(int j =0; j < COLUMNS; j++)
        {
            cellData->cellCollection[counter].collisionBox.x1 =  cellBaseXPos + (CELL_SIZE * j);

            cellData->cellCollection[counter].collisionBox.x2 =  
                cellData->cellCollection[counter].collisionBox.x1 + CELL_SIZE;

            cellData->cellCollection[counter].collisionBox.y1 =  cellBaseYPos + (CELL_SIZE * i);

            cellData->cellCollection[counter].collisionBox.y2 =  
                cellData->cellCollection[counter].collisionBox.y1 + CELL_SIZE;

            printf("Cell %d --> X1: %d, X2: %d,Y1: %d, Y2: %d\n", 
                    counter, 
                    cellData->cellCollection[counter].collisionBox.x1, 
                    cellData->cellCollection[counter].collisionBox.x2,
                    cellData->cellCollection[counter].collisionBox.y1, 
                    cellData->cellCollection[counter].collisionBox.y2);

            counter++;
        }
    }
}
