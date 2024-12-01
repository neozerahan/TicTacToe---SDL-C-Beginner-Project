#ifndef COLLISION_H
#define COLLISION_H

#include "..\Include\global.h"
#include "..\Include\gameObjects.h"
#include <stdio.h>

void SetCellDetectionBox(CellData * cellData);

int  CheckCellDetection(Sint32 const xMouse, Sint32 const yMouse, 
        const CellData *cellData);

int CheckCollision( CellCollisionBox collisionBox, MousePos mousePos);

#endif
