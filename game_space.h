#ifndef __GAMESPACE_H
#define __GAMESPACE_H

#define WIDTH 20
#define HEIGHT 20

//int **GameGrid[WIDTH][HEIGHT];
#define SNAKE_MAX_LEN  10

struct SnakeBodySegment {
    int pos_x;
    int pos_y;
    int direction; // Direction of travel for body segment at moment in time
    int prev_direction; // Direction of travel from last turn
    int type;
};

//struct SnakeBodySegment NullSeg = {-1, -1, -1, -1, -1};


//template <int len>
struct Snake{
////    int pos_x; // current x-position of snake's head
////    int pos_y; // current y-position of snake's head
    int length;
    int alive;
    int npc;
////    int speed;
////    int direction;
//////    int speed;
    struct SnakeBodySegment segments[SNAKE_MAX_LEN];
};


typedef enum {
    up,
    down,
    right,
    left,
} Directions;

typedef enum {
    blank_space,
    vwall,
    hwall,
    food,
    snk_head,
    snk_body,
//    snk_tail,
    npc_snk_head,
    npc_snk_body,
//    npc_snk_tail,
    collision,
} GameTypes;


//const char *left_triangle = '\u25c0';
//const char *right_triangle = '\u25b6';
//const char *up_triangle = '\u25b2';
//const char *down_triangle = '\u25bc';
//
//const char *black_square = '\u25a0';
//
//const char *black_octagon = '\u2bc4';


// Functions defined in snake.c
int GenerateSnake(int row, int col, int segs2generate, int direction,
        struct Snake *snek_ptr, int **GameGrid);

void GenerateSnakeSegment(struct Snake *snek_ptr, int row, int col,
        int direction, int seg_number, int seg_type, int **GameGrid);

void GenerateGameSpace(int foodGenProb, int wallGenProb, int **GameGrid);

int horizontalWallSocket(int row, int col, int ljoint, int rjoint, int **GameGrid);

int verticalWallSocket(int row, int col, int ujoint, int djoint, int **GameGrid);

int rollForLeftHorizJoint(int row, int col, int horizProb,
       int upVertProb, int downVertProb, int blankSpaceProb,
       int **GameGrid);

int rollForRightHorizJoint(int row, int col, int horizProb,
       int upVertProb, int downVertProb, int blankSpaceProb, 
       int **GameGrid);

int rollForUpperVertJoint(int row, int col, int vertProb,
       int rightHorizProb, int leftHorizProb, int blankSpaceProb,
       int **GameGrid);

int rollForLowerVertJoint(int row, int col, int vertProb,
       int rightHorizProb, int leftHorizProb, int blankSpaceProb, 
       int **GameGrid);

void printGameBoard(int **GameGrid);

void randomlyGenerateFood(int foodGenProb, int **GameGrid);

void randomlyPlaceSneks(struct Snake *snek_ptr, int **GameGrid);

int cleanUpDeadSnek(struct Snake *snek, int **GameGrid);

void freeGameGridMemory(int **GameGrid);

#endif
