#include <stdlib.h>

// 7*4 elements
// 2 of each piece
#define PIECE_LIST_LENGTH 14
int pieceList[] = {0,1,2,3,4,5,6,0,1,2,3,4,5,6,0,1,2,3,4,5,6};
int piece_pos = PIECE_LIST_LENGTH;

void shuffle_pieces()
{

    int i, r, t;
    int todo = PIECE_LIST_LENGTH-1;
    for(i=0; i<PIECE_LIST_LENGTH-1; i++) {
        r = rand()%todo;
        t = pieceList[i];
        pieceList[i] = pieceList[i+r];
        pieceList[i+r] = t;
        todo--;
    }

    piece_pos = 0;
}

int pickNewPiece()
{
    if(piece_pos >= PIECE_LIST_LENGTH) shuffle_pieces();
    return pieceList[piece_pos++];
}
