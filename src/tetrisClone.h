
#include "SDL_functions.h"
#include "block_data.h"

#define NUMBER_OF_BLOCKS 7
#define BLOCK_SIZE 25
#define GRID_START_X 40
#define GRID_START_Y 40
#define DROP_START_X 3
#define DROP_START_Y 1


void drawPiece(SDL_Renderer* ren, PIECE *p, int xOrigin, int yOrigin, int color);
void deleteLine(int y);
void clearLines();
bool checkIfValidPosition();
void dropPiece();
void incScore();


typedef enum {
    MODE_RUNNING,
    MODE_GAMEOVER,
    MODE_START,
    MODE_PAUSE
} MODE;

