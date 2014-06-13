
/*

   [][]     BLOCK 1
   [][]


   [][][][] BLOCK 2


     [][]   BLOCK 3
   [][]


   [][]     BLOCK 4
     [][]

    
   [][][]  BLOCK 5
   []


   [][][]  BLOCK 6
       []


   [][][]  BLOCK 7
     []

*/


typedef struct BLOCK {
    char x;
    char y;
} BLOCK;

typedef struct PIECE {
    BLOCK blocks[4];
} PIECE;

typedef struct DROP {
    int rotations; //Number of rotations avalible
    PIECE peice[4];
} DROP;

//Returns an array of drops
DROP* getDrops();


