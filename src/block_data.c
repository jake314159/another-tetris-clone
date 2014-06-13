#include <stdlib.h>
#include "block_data.h"

//See http://colinfahey.com/tetris/tetris.html

DROP* getDrops()
{

    DROP* drops = malloc(8*sizeof(DROP));

    //BLock 1
    drops[1].rotations = 1;
    drops[1].peice[0].blocks[0].x = 0;
    drops[1].peice[0].blocks[0].y = 0;
    drops[1].peice[0].blocks[1].x = 0;
    drops[1].peice[0].blocks[1].y = -1;
    drops[1].peice[0].blocks[2].x = -1;
    drops[1].peice[0].blocks[2].y = 0;
    drops[1].peice[0].blocks[3].x = -1;
    drops[1].peice[0].blocks[3].y = -1;

    //BLock 2
    drops[2].rotations = 2;
    drops[2].peice[0].blocks[0].x = -2;
    drops[2].peice[0].blocks[0].y = 0;
    drops[2].peice[0].blocks[1].x = -1;
    drops[2].peice[0].blocks[1].y = 0;
    drops[2].peice[0].blocks[2].x = 0;
    drops[2].peice[0].blocks[2].y = 0;
    drops[2].peice[0].blocks[3].x = 1;
    drops[2].peice[0].blocks[3].y = 0;

    drops[2].peice[1].blocks[0].x = 0;
    drops[2].peice[1].blocks[0].y = 1;
    drops[2].peice[1].blocks[1].x = 0;
    drops[2].peice[1].blocks[1].y = 0;
    drops[2].peice[1].blocks[2].x = 0;
    drops[2].peice[1].blocks[2].y = -1;
    drops[2].peice[1].blocks[3].x = 0;
    drops[2].peice[1].blocks[3].y = -2;

    //Block 3
    drops[3].rotations = 2;
    drops[3].peice[0].blocks[0].x = 0;
    drops[3].peice[0].blocks[0].y = 0;
    drops[3].peice[0].blocks[1].x = 1;
    drops[3].peice[0].blocks[1].y = 0;
    drops[3].peice[0].blocks[2].x = 0;
    drops[3].peice[0].blocks[2].y = -1;
    drops[3].peice[0].blocks[3].x = -1;
    drops[3].peice[0].blocks[3].y = -1;

    drops[3].peice[1].blocks[0].x = 0;
    drops[3].peice[1].blocks[0].y = 0;
    drops[3].peice[1].blocks[1].x = 0;
    drops[3].peice[1].blocks[1].y = 1;
    drops[3].peice[1].blocks[2].x = 1;
    drops[3].peice[1].blocks[2].y = 0;
    drops[3].peice[1].blocks[3].x = 1;
    drops[3].peice[1].blocks[3].y = -1;

    //Block 4
    drops[4].rotations = 2;
    drops[4].peice[0].blocks[0].x = 0;
    drops[4].peice[0].blocks[0].y = 0;
    drops[4].peice[0].blocks[1].x = -1;
    drops[4].peice[0].blocks[1].y = 0;
    drops[4].peice[0].blocks[2].x = 0;
    drops[4].peice[0].blocks[2].y = -1;
    drops[4].peice[0].blocks[3].x = 1;
    drops[4].peice[0].blocks[3].y = -1;

    drops[4].peice[1].blocks[0].x = 0;
    drops[4].peice[1].blocks[0].y = 0;
    drops[4].peice[1].blocks[1].x = 0;
    drops[4].peice[1].blocks[1].y = -1;
    drops[4].peice[1].blocks[2].x = 1;
    drops[4].peice[1].blocks[2].y = 0;
    drops[4].peice[1].blocks[3].x = 1;
    drops[4].peice[1].blocks[3].y = 1;

    //Block 5
    drops[5].rotations = 4;
    drops[5].peice[0].blocks[0].x = 0;
    drops[5].peice[0].blocks[0].y = 0;
    drops[5].peice[0].blocks[1].x = -1;
    drops[5].peice[0].blocks[1].y = 0;
    drops[5].peice[0].blocks[2].x = -1;
    drops[5].peice[0].blocks[2].y = -1;
    drops[5].peice[0].blocks[3].x = 1;
    drops[5].peice[0].blocks[3].y = 0;

    drops[5].peice[1].blocks[0].x = 0;
    drops[5].peice[1].blocks[0].y = 0;
    drops[5].peice[1].blocks[1].x = 0;
    drops[5].peice[1].blocks[1].y = -1;
    drops[5].peice[1].blocks[2].x = 1;
    drops[5].peice[1].blocks[2].y = -1;
    drops[5].peice[1].blocks[3].x = 0;
    drops[5].peice[1].blocks[3].y = 1;

    drops[5].peice[2].blocks[0].x = 0;
    drops[5].peice[2].blocks[0].y = 0;
    drops[5].peice[2].blocks[1].x = -1;
    drops[5].peice[2].blocks[1].y = 0;
    drops[5].peice[2].blocks[2].x = 1;
    drops[5].peice[2].blocks[2].y = 0;
    drops[5].peice[2].blocks[3].x = 1;
    drops[5].peice[2].blocks[3].y = 1;

    drops[5].peice[3].blocks[0].x = 0;
    drops[5].peice[3].blocks[0].y = 0;
    drops[5].peice[3].blocks[1].x = 0;
    drops[5].peice[3].blocks[1].y = -1;
    drops[5].peice[3].blocks[2].x = 0;
    drops[5].peice[3].blocks[2].y = 1;
    drops[5].peice[3].blocks[3].x = -1;
    drops[5].peice[3].blocks[3].y = 1;

    //Block 6
    drops[6].rotations = 4;
    drops[6].peice[0].blocks[0].x = 0;
    drops[6].peice[0].blocks[0].y = 0;
    drops[6].peice[0].blocks[1].x = -1;
    drops[6].peice[0].blocks[1].y = 0;
    drops[6].peice[0].blocks[2].x = 1;
    drops[6].peice[0].blocks[2].y = 0;
    drops[6].peice[0].blocks[3].x = 1;
    drops[6].peice[0].blocks[3].y = -1;

    drops[6].peice[1].blocks[0].x = 0;
    drops[6].peice[1].blocks[0].y = 0;
    drops[6].peice[1].blocks[1].x = 0;
    drops[6].peice[1].blocks[1].y = -1;
    drops[6].peice[1].blocks[2].x = 0;
    drops[6].peice[1].blocks[2].y = 1;
    drops[6].peice[1].blocks[3].x = 1;
    drops[6].peice[1].blocks[3].y = 1;

    drops[6].peice[2].blocks[0].x = 0;
    drops[6].peice[2].blocks[0].y = 0;
    drops[6].peice[2].blocks[1].x = -1;
    drops[6].peice[2].blocks[1].y = 0;
    drops[6].peice[2].blocks[2].x = -1;
    drops[6].peice[2].blocks[2].y = 1;
    drops[6].peice[2].blocks[3].x = 1;
    drops[6].peice[2].blocks[3].y = 0;

    drops[6].peice[3].blocks[0].x = 0;
    drops[6].peice[3].blocks[0].y = 0;
    drops[6].peice[3].blocks[1].x = 0;
    drops[6].peice[3].blocks[1].y = -1;
    drops[6].peice[3].blocks[2].x = 0;
    drops[6].peice[3].blocks[2].y = 1;
    drops[6].peice[3].blocks[3].x = -1;
    drops[6].peice[3].blocks[3].y = -1;

    //Block 7
    drops[7].rotations = 4;
    drops[7].peice[0].blocks[0].x = 0;
    drops[7].peice[0].blocks[0].y = 0;
    drops[7].peice[0].blocks[1].x = 0;
    drops[7].peice[0].blocks[1].y = -1;
    drops[7].peice[0].blocks[2].x = -1;
    drops[7].peice[0].blocks[2].y = 0;
    drops[7].peice[0].blocks[3].x = 1;
    drops[7].peice[0].blocks[3].y = 0;

    drops[7].peice[1].blocks[0].x = 0;
    drops[7].peice[1].blocks[0].y = 0;
    drops[7].peice[1].blocks[1].x = 0;
    drops[7].peice[1].blocks[1].y = -1;
    drops[7].peice[1].blocks[2].x = 0;
    drops[7].peice[1].blocks[2].y = 1;
    drops[7].peice[1].blocks[3].x = 1;
    drops[7].peice[1].blocks[3].y = 0;

    drops[7].peice[2].blocks[0].x = 0;
    drops[7].peice[2].blocks[0].y = 0;
    drops[7].peice[2].blocks[1].x = 0;
    drops[7].peice[2].blocks[1].y = 1;
    drops[7].peice[2].blocks[2].x = -1;
    drops[7].peice[2].blocks[2].y = 0;
    drops[7].peice[2].blocks[3].x = 1;
    drops[7].peice[2].blocks[3].y = 0;

    drops[7].peice[3].blocks[0].x = 0;
    drops[7].peice[3].blocks[0].y = 0;
    drops[7].peice[3].blocks[1].x = 0;
    drops[7].peice[3].blocks[1].y = -1;
    drops[7].peice[3].blocks[2].x = -1;
    drops[7].peice[3].blocks[2].y = 0;
    drops[7].peice[3].blocks[3].x = 0;
    drops[7].peice[3].blocks[3].y = 1;

    return drops;
}
