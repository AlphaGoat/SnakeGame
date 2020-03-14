#ifndef SNAKE_H
#define SNAKE_H

#define WIDTH 20
#define HEIGHT 20

struct SnakeBodySegment {
    int pos_x;
    int pos_y;
    int direction; // Direction of travel for body segment at moment in time
    int *linked_direction; // Direction of travel for body segment ahead of this body part
    int type;
};


struct Snake {
//    int pos_x; // current x-position of snake's head
//    int pos_y; // current y-position of snake's head
//    int length;
//    int speed;
//    int direction;
    int speed;
    struct SnakeBodySegment segments[];
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
    snk_tail,
} GameTypes;


const char *left_triangle = '\u25c0';
const char *right_triangle = '\u25b6';
const char *up_triangle = '\u25b2';
const char *down_triangle = '\u25bc';

const char *black_square = '\u25a0';

const char *black_octagon = '\u2bc4';


// Functions defined in snake.c
void GenerateGameSpace(struct Snake snek, int foodGenProb, 
        int wallGenProb, int **GameGrid);

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

#endif
