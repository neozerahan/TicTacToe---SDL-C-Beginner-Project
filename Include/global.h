#ifndef GLOBAL_H
#define GLOBAL_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_video.h"

#define TRUE  1
#define FALSE 0
#define ROWS    3
#define COLUMNS 3
#define TOTAL_CELL_COUNT ROWS * COLUMNS

#define FIRST_ROW_ID 0
#define SECOND_ROW_ID 3
#define THIRD_ROW_ID 6

#define SECOND_COLUMN_ID 1
#define THIRD_COLUMN_ID 2

#define DIRECTION_HORIZONTAL 1
#define DIRECTION_VERTICAL 3
#define DIRECTION_DIAGONAL 4
#define DIRECTION_REVERSE_DIAGONAL 2

#define CELL_SIZE 133 

#define BOARD_RESOLUTION 400

#define PLAYER_1_TURN 1
#define PLAYER_2_TURN 2
#define SCREEN_WIDTH   800
#define SCREEN_HEIGHT  600 
#define SCREEN_CENTER SCREEN_WIDTH * 0.5
#define O_SHAPE 0,0,128,128
#define X_SHAPE 128,0,128,128
#define BOARD_RENDERER_SHAPE 256,0,128,128
#define CELL_RENDERER_SHAPE 256 + 128,0,128,128

//Used to calculate the cell bounds...
#define CELL_BASE_X_POS 200
#define CELL_BASE_Y_POS 110

#define ALLIGN_LEFT 0b1
#define ALLIGN_MID 0b10
#define ALLIGN_RIGHT 0b100

#define GAME_STATE_MENU 1
#define GAME_STATE_IN_GAME 2
#define GAME_STATE_RESULT 3
#define GAME_STATE_PAUSE 4

#define TRANS_STATE_NONE 0
#define TRANS_STATE_IN 1
#define TRANS_STATE_OUT 2
#define TRANS_STATE_FINISH 3

#endif
