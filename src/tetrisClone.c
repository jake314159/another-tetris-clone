// http://www.willusher.io/sdl2%20tutorials/2013/12/18/lesson-6-true-type-fonts-with-sdl_ttf/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "tetrisClone.h"
#include "piece_picker.h"

#define SCORE_BUFFER_SIZE 20

SDL_Texture *background;

const char* WINDOW_NAME = "Tetris clone";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int fontSize = 48;
const char* fontFile = "fonts/sample.ttf";
const int score_x = 440;
const int score_y = 70;
const SDL_Color score_color = { 255, 255, 255 };

DROP* dropData;
int nextPiece = 0;
int useClip = 0;
SDL_Rect blockClips[NUMBER_OF_BLOCKS];
SDL_Texture *blocks;
TTF_Font *font;

int drop_x = DROP_START_X;
int drop_y = DROP_START_Y;
int grid[10][16] = {0};
int rotation = 0;

unsigned long score = 0;
unsigned long scoreInBuffer = -1;
char score_buffer[SCORE_BUFFER_SIZE];

MODE mode = MODE_RUNNING;

bool draw_required = true; //Has there been a change requiring a redraw?

int fallTimer = 0;
int fallTimerLimit = 35;//35; // 6 is quite playable -- 4 is near impossible
int fallTimerMin = 4;

void drawPiece(SDL_Renderer* ren, PIECE *p, int xOrigin, int yOrigin, int color) 
{
    int i, x, y;
    for(i=0; i<4; i++) {
        BLOCK *b = &(p->blocks[i]);
        x =  GRID_START_X + BLOCK_SIZE * (xOrigin + b->x);
        y =  GRID_START_Y + BLOCK_SIZE * (yOrigin + b->y);
        if( y >= GRID_START_Y ) {
            renderTextureClip(blocks, ren, x, y, &blockClips[color]);
        }
    }
}

void deleteLine(int y)
{
    int x;
    for(; y>0; y--) {
        for(x=0; x<10; x++) {
            grid[x][y] = grid[x][y-1];
        }
    }
    //clear top line
    for(x=0; x<10; x++) {
        grid[x][0] = 0;
    }
}

void clearLines()
{
    int x, y;
    bool lineFull;
    for(y=0; y<16; y++) {
        lineFull = true; //assume the line is full
        for(x=0; x<10; x++) {
            int color = grid[x][y];
            if(color == 0) {
                lineFull = false;
                break;
            }
        }

        if(lineFull) {
            deleteLine(y);
            incScore();
        }
    }
}

// Checks if the piece is allowed to be where it is
bool checkIfValidPosition()
{
    DROP *d = (DROP*)dropData+useClip+1;
    int r = rotation%(d->rotations);
    PIECE *p = &(d->peice[r]);
    int i, x, y;

    for(i=0; i<4; i++) {  //Check if this fall is valid
        BLOCK *b = &(p->blocks[i]);
        x =  (drop_x + b->x);
        y =  (drop_y + b->y);
        if(x >= 0 && x < 10 && y < 16) {
            if( y < 0 ) {
                return true; //nothing can be above the grid
            } else {
                if(grid[x][y] != 0) {
                    return false;
                }
            }
        } else {
            return false;
        }
    }
    return true;
}

void incScore()
{
    score += 1;
    if(fallTimerLimit <= fallTimerMin) {

    } else if( fallTimerLimit >= 10) {
        if(score%((score/10)+1) == 0) { 
            fallTimerLimit -=1;
        }
    } else {
        if ((score%(400/fallTimerLimit)) == 0) {
            fallTimerLimit -= 1;
        }
    }
    printf("Score %lu    Delay: %d\n", score, fallTimerLimit);
}

void dropPiece()
{
    DROP *d = (DROP*)dropData+useClip+1;
    int r = rotation%(d->rotations);
    PIECE *p = &(d->peice[r]);
    int i, x, y;

    bool keepFalling = true;
    while(keepFalling) {
        drop_y += 1;
        if(!checkIfValidPosition()) {
            keepFalling = false;
        }
    }
    drop_y -= 1; //that last step wasn't valid so undo

    //Add to grid
    for(i=0; i<4; i++) {
        BLOCK *b = &(p->blocks[i]);
        x =  (drop_x + b->x);
        y =  (drop_y + b->y);
        if(x >= 0 && y >= 0 && x < 10 && y < 16) {
            grid[x][y] = useClip+1;
        }
    }

    drop_x = DROP_START_X;
    drop_y = DROP_START_Y;
    useClip = nextPiece;
    nextPiece = pickNewPiece();
    rotation = 0;
    fallTimer = 0;
    clearLines();
    if(!checkIfValidPosition()) {
        //Game over
        mode = MODE_GAMEOVER;
    }
}

void draw_score(SDL_Renderer* ren)
{
    if(scoreInBuffer != score) {
        sprintf(score_buffer, "%lu", score);
        scoreInBuffer = score;
    }
    SDL_Texture *font_image = renderText(score_buffer, font, score_color, ren);
    if (font_image == NULL){
        exit(1);
    }            
        renderTexture(font_image, ren, score_x, score_y);
}

void draw_game_running(SDL_Renderer* ren)
{
    int bW, bH;
    SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
    renderTexture(background, ren, 0, 0);

    //draw the fixed peices
    int i, j, x, y;
    for(i=0; i<10; i++) {
        for(j=0; j<16; j++) {
            x =  GRID_START_X + BLOCK_SIZE * i;
            y =  GRID_START_Y + BLOCK_SIZE * j;
            int color = grid[i][j];
            if(color>0)
                renderTextureClip(blocks, ren, x, y, &blockClips[color-1]);
        }
    }

    DROP *d = (DROP*)dropData+useClip+1;
    int r = rotation%(d->rotations);
    PIECE *p = &(d->peice[r]);
    x = drop_x;
    y = drop_y;
    drawPiece(ren, p, x, y, useClip);
    
    //Draw the next piece to the right
    DROP *dN = (DROP*)dropData+nextPiece+1;
    PIECE *pN = &(dN->peice[0]); //rotation 0
    x = drop_x;
    y = drop_y;
    drawPiece(ren, pN, NEXT_PIECE_X, NEXT_PIECE_Y, nextPiece);
}

void draw_game_paused(SDL_Renderer* ren)
{
    renderTexture(background, ren, 0, 0);
}

int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    if(init_SDL_all() != 0) {
        return 1;
    }

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        WINDOW_NAME,                       // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        SCREEN_WIDTH,                      // width, in pixels
        SCREEN_HEIGHT,                     // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (window == NULL) {
        return logSDLError("Could not create window");
    }

    SDL_Renderer* ren;

    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (ren == NULL) {
        return logSDLError("Could not create renderer");
    }

    dropData = getDrops();

    srand(time(NULL));

    //Open the font
	font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL){
		return logSDLError("TTF_OpenFont");
	}	

    background = loadTexture("images/bkg.png", ren);
    SDL_Texture *image = loadTexture("images/image.bmp", ren);
    if (background == NULL || image == NULL) {
	    return 4;
    }

    SDL_Texture *sheet = loadTexture("images/sheet.png", ren);
    blocks = loadTexture("images/blocks.png", ren);

    //iW and iH are the clip width and height
    //We'll be drawing only clips so get a center position for the w/h of a clip
    int iW = 100, iH = 100;
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;

    //Setup the clips for our image
    SDL_Rect clips[4];
    int i;
    for (i = 0; i < 4; ++i){
	    clips[i].x = i / 2 * iW;
	    clips[i].y = i % 2 * iH;
	    clips[i].w = iW;
	    clips[i].h = iH;
    }

    //Specify a default clip to start with
    for(i=0; i < NUMBER_OF_BLOCKS; i++) {
        blockClips[i].x = i * BLOCK_SIZE;
	    blockClips[i].y = 0;
	    blockClips[i].w = BLOCK_SIZE;
	    blockClips[i].h = BLOCK_SIZE;
    }
    
    nextPiece = pickNewPiece();
    useClip = pickNewPiece();

    //SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example
    //Our event structure
    SDL_Event e;
    bool quit = false;
    while (!quit){

        SDL_Delay(FRAME_TIME_DELAY);

        // Event loop for each possible game mode
        if(mode == MODE_GAMEOVER) {
            printf("\nGAME OVER\nScore: %lu\n\n", score);
            quit = true;
            break;
        } else if(mode == MODE_PAUSE) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym){
                        case SDLK_p:
                            mode = MODE_RUNNING;
                            break;
                        case SDLK_q:
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        default:
                            break;
                    }
                }
            }
        } else if(mode == MODE_RUNNING) {
	        while (SDL_PollEvent(&e)) {
		        if (e.type == SDL_QUIT)
			        quit = true;
                if (e.type == SDL_KEYDOWN){
		            switch (e.key.keysym.sym){
                        case SDLK_UP:
                            rotation += 1;
                            if(!checkIfValidPosition()) {
                                rotation -= 1;
                            }
                            draw_required = true;
                            break;
			            case SDLK_ESCAPE:
                        case SDLK_q:
				            quit = true;
				            break;
                        case SDLK_DOWN:
                            drop_y += 1;
                            draw_required = true;
                            if(!checkIfValidPosition()) { 
                                drop_y -= 1;
                                dropPiece();
                            }
                            break;
                        case SDLK_LEFT:
                            drop_x -= 1;
                            draw_required = true;
                            if(!checkIfValidPosition()) drop_x += 1;
                            break;
                        case SDLK_RIGHT:
                            drop_x += 1;
                            draw_required = true;
                            if(!checkIfValidPosition()) drop_x -= 1;
                            break;
                        case SDLK_SPACE:
                            draw_required = true;
                            dropPiece();
                            break;
                        case SDLK_p:
                            if(mode == MODE_PAUSE)  mode = MODE_RUNNING;
                            else                    mode = MODE_PAUSE;
                            break;
			            default:
				            break;
		           }
	            }
	        }
        }

        if(mode == MODE_RUNNING) {
            fallTimer++;
            if(fallTimer >= fallTimerLimit) {
                fallTimer = 0;
                drop_y += 1;
                draw_required = true;
                if(!checkIfValidPosition()) { 
                    drop_y -= 1;
                    dropPiece();
                }
            }
        }

        if(draw_required) {
            SDL_RenderClear(ren);

	        //Render the scene
            switch(mode) {
                case MODE_RUNNING:
	                draw_game_running(ren);
                    break;
                case MODE_PAUSE:
                    draw_game_paused(ren);
                    break;
                default:
                    break;
            }

            draw_score(ren);

            SDL_RenderPresent(ren);

        }
        
    }

    // Close and destroy the window
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    SDL_DestroyTexture(sheet);
    SDL_DestroyTexture(blocks);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}

