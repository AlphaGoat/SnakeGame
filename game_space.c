#include <stdio.h>
#include <stdlib.h>

#include "game_space.h"

// The Game Grid will consist of an array
// of pointers to integer values
//int **GameGrid;

void GenerateSnake(int length, int speed, int direction, 
        int pos_x, int pos_y, int **GameGrid) {
    /* Generate a snake structure (Actually a case for several smaller structure,
     * each consisting of a body segment of the snake, whose positions and direction
     * of travel are tracked seperately
     *
     * :param length:    length of the snake (i.e., how many body segments it is 
     *                   composed of
     * :param speed:     speed of the snake
     * :param direction: starting direction for all body segments of snake. An 
     *                   internal direction parameters will be tracked seperately
     *                   for each body segment
     * :param pos_x:     column where the head of the snake will start
     * :param pos_y:     row where the head of the snake will start
     */
    struct SnakeBodySegment segments[length];
    // Loop to initialize each body segment of the snake
    int next_pos_x;
    int next_pos_y;
    int next_direction;
    for (int i = 0; i < length; i++) {
        // Initialization for snake's head
        if (i == 0) {
            segments[i].pos_x = pos_x;
            segments[i].pos_y = pos_y;
            segments[i].direction = direction;
            // point linked direction to head's own direction, so that
            // they are the same (head of snake determines direction of travel)
            segments[i].linked_direction = &segments[i].direction;
            segments[i].type = snk_head;
        }
        // Initialization for snake's tail (same as with body segment,
        // only the type for display on the game grid is different)
        else if (i == (length - 1)) {
            segments[i].pos_x = next_pos_x;
            segments[i].pos_y = next_pos_y;
            segments[i].direction = next_direction;
            segments[i].linked_direction = &segments[i-1].direction;
            segments[i].type = snk_tail;
        }
        // Initialization for snake's body
        else {
            segments[i].pos_x = next_pos_x;
            segments[i].pos_y = next_pos_y;
            segments[i].direction = next_direction;
            segments[i].linked_direction = &segments[i-1].direction;
            segments[i].type = snk_body;
        }

        // determine x,y position of next body segment        
        switch(segments[i].direction) {
            case down:
                next_pos_y = segments[i].pos_y + 1;
            case up:
                next_pos_y = segments[i].pos_y - 1;
            case left:
                next_pos_x = segments[i].pos_x + 1;
            case right:
                next_pos_x = segments[i].pos_x - 1;
        }

        // Check if that position will put the snake in conflict with 
        // any other piece of the board
//        if (GameGrid[next_pos_y][next_pos_x] != blank_space) {
//            if (segments[i].direction
//                    }
//                    }
//                    }
            }
}

//int * CheckForSpaceConflict(int row, int col, 
//    int linkedDirection, int **GameGrid) {
//    /* Function that checks grid for potential conflict,
//     * and proposes a different set of coordinates based on
//     * conflict resolution
//     */
//    
//    // Check space above given row/col
    
    

        

        



void GenerateGameSpace(struct Snake snek, int foodGenProb, int wallGenProb, int **GameGrid){

    if (GameGrid == NULL) {
        printf("malloc of size (%d,%d) failed!\n", HEIGHT, WIDTH);
        exit(1);
    }

    // Store whatever remainder is left over after
    // dividing the snake's length in two 
    int wall_buffer = 2; // Buffer to leave between ends of snake and wall

    // Create a buffer on the outer edge of grid
//    for (int i = 0; i < WIDTH; i++) {
//        GameGrid[0][i] = hwall;
//        GameGrid[HEIGHT-1][i] = hwall;
//    }

    for (int i = 1; i < HEIGHT-1; i++) {
        GameGrid[i][0] = vwall;
        GameGrid[i][WIDTH-1] = vwall;
    }

    // Generate snake body
    for (int i = 1; i < snek.length+1; i++) {
        // Place snake at top left of board and leave enough room for
        // whole body
        if (i == 1) 
            GameGrid[1][i] = snk_tail;
        else if (i == snek.length)
            GameGrid[1][i] = snk_head;
        else
            GameGrid[1][i] = snk_body;
    }

    // As the parameter passed into the function for wall generation
    // probability does not specify probability of vertical wall gen
    // vs horiz wall gen, determine a halfway point to make decision
    int wallDecisionPoint = (wallGenProb / 2) + foodGenProb;

    // Randomly generate food and wall tiles
    for (int i = 1; i < HEIGHT-1; i++) {
        for (int j = 1; j < WIDTH-1; j++) {
            // Ensure that the space that we are placing the tiles
            // on is not occupied
            if (GameGrid[i][j] != blank_space)
                continue;

            // We're going to be abusing rand alot, aren't we...
            int roll = rand() % 100;
            if (roll < foodGenProb) 
                GameGrid[i][j] = food;
            else if ((roll >= foodGenProb) && 
                    (roll < foodGenProb + wallGenProb)) {
                if (roll < wallDecisionPoint) 
                    horizontalWallSocket(i, j, 0, 0, GameGrid);
                else
                    verticalWallSocket(i, j, 0, 0, GameGrid);
            }
        }
    }
}

int horizontalWallSocket(int row, int col, int ljoint, int rjoint, int **GameGrid) {
    /* 
     * Encapsulates all logic to generate walls in game grid
     *     :param row: row number of socket
     *     :param col: column number of socket
     *     :param ljoint: Is this wall attached to another socket by
     *                    a joint on its left? If so, left or right?
     *
     *                    0: No left attachments 
     *                    1: Attached on left
     *
     *      :param rjoint: Attached on the right?
     *                  
     *                     0: No right attachments
     *                     1: Attached on right
     *
     *      :param GameGrid: pointer to game grid
     */

    // First things first...check to see if given coordinates are 
    // unoccupied
    if (GameGrid[row][col] == blank_space)
        GameGrid[row][col] = hwall;
    // If space is occupied by another piece already...return an error 
    else
        return -1;

    // Attach piece to left joint, if necessary
    if (!ljoint) {

        // Only attach a wall socket to the left joint if it would remain
        // in game space
        if (col != 0){

            // Error code to see if joint succesfully attached
            int larm;

            // Would adding a vertical wall to upper diagonal put it 
            // outside game space?
            if (row == 0) 
                larm = rollForLeftHorizJoint(row, col, 40, 0, 20, 40, GameGrid);
            // Would adding a vertical wall to lower diagonal put it
            // outside game space?
            else if (row == HEIGHT - 1)
                larm = rollForLeftHorizJoint(row, col, 40, 20, 0, 40, GameGrid);
            else
                larm = rollForLeftHorizJoint(row, col, 40, 10, 10, 40, GameGrid);
        }
    }
    
    // Now attach piece to right joint, if unoccupied
    else if (!rjoint) {

        // Only attach a wall socket to the right joint if it would remain
        // in game space
        if (col != WIDTH-1) {
            // Determine the socket that we will attach to the left 
            // arm of the horizontal wall socket
            
            // Error code to see if joint succesfully attached
            int rarm;

            // Would adding a vertical wall to upper diagonal put it
            // outside game space? If so, make prob of generating it 0%
            if (row == 0) 
                rarm = rollForRightHorizJoint(row, col, 40, 0, 20, 40, GameGrid);
            // Check if putting a vertical wall on lower diagonal would put it outside
            // game space
            else if (row == HEIGHT - 1)
                rarm = rollForRightHorizJoint(row, col, 40, 20, 0, 40, GameGrid);
            else
                rarm = rollForRightHorizJoint(row, col, 40, 10, 10, 40, GameGrid);
        }
    }

    return 1;
} 

int verticalWallSocket(int row, int col, int ujoint, int djoint, int **GameGrid) {
    /* 
     * Encapsulates all logic to generate walls in game grid
     *     :param row: row number of socket
     *     :param col: column number of socket
     *     :param ljoint: Is this wall attached to another socket by
     *                    a joint on its left? If so, left or right?
     *
     *                    0: No left attachments 
     *                    1: Attached on left
     *
     *      :param rjoint: Attached on the right?
     *                  
     *                     0: No right attachments
     *                     1: Attached on right
     *
     *      :param GameGrid: pointer to game grid
     */

    // First things first...check to see if given coordinates are 
    // unoccupied
    if (GameGrid[row][col] == blank_space)
        GameGrid[row][col] = vwall;
    // If space is occupied by another piece already...return an error 
    else
        return -1;

    // Attach piece to left joint, if necessary
    if (!ujoint) {

        // Only attach a wall socket to the left joint if it would remain
        // in game space
        if (row != 0){

            // Error code to see if joint succesfully attached
            int uarm;

            // Would adding a vertical wall to upper diagonal put it 
            // outside game space?
            if (col == 0) 
                uarm = rollForUpperVertJoint(row, col, 40, 0, 20, 40, GameGrid);
            // Would adding a vertical wall to lower diagonal put it
            // outside game space?
            else if (col == WIDTH - 1)
                uarm = rollForUpperVertJoint(row, col, 40, 20, 0, 40, GameGrid);
            else
                uarm = rollForUpperVertJoint(row, col, 40, 10, 10, 40, GameGrid);
        }
    }
    
    // Now attach piece to right joint, if unoccupied
    else if (!djoint) {

        // Only attach a wall socket to the right joint if it would remain
        // in game space
        if (col != WIDTH-1) {
            // Determine the socket that we will attach to the left 
            // arm of the horizontal wall socket
            
            // Error code to see if joint succesfully attached
            int darm;

            // Would adding a vertical wall to upper diagonal put it
            // outside game space? If so, make prob of generating it 0%
            if (row == 0) 
                darm = rollForLowerVertJoint(row, col, 40, 0, 20, 40, GameGrid);
            // Check if putting a vertical wall on lower diagonal would put it outside
            // game space
            else if (row == HEIGHT - 1)
                darm = rollForLowerVertJoint(row, col, 40, 20, 0, 40, GameGrid);
            else
                darm = rollForLowerVertJoint(row, col, 40, 10, 10, 40, GameGrid);
        }
    }

    return 1;
} 

int rollForLeftHorizJoint(int row, int col, int horizProb,
       int upVertProb, int downVertProb, int blankSpaceProb,
       int **GameGrid) {
   /*
    * Function rolling for what socket to attach to the right
    * joint of a horizontal wall piece
    *
    * :param row: row of the original horizontal wall piece
    * :param col: column of the original horizontal wall piece
    * :param horizProb: probability of attaching horizontal wall piece to right joint
    * :param upVertProb: probability of attaching vertical wall piece to upper
    *                    diagonal of right joint
    * :param downVertProb: probability of attaching vertical wall piece to bottom
    *                      diagonal of right joint
    * :param emptySpaceProb: probability of no attachment to joint
    *  NOTE: all probabilities are expressed as integers from 0-100 (i.e., 40% prob
    *        of horizontal wall piece attachment is horizProb = 40
    */

    // Check to see if probabilities add up to 100. If not, return error
    int totalProb = horizProb + upVertProb + downVertProb + blankSpaceProb;
    if ((totalProb) > 100 || (totalProb) < 100) 
        return -1;

    // Perform 'roll'
    int roll = rand() % 100;
    
    if (roll < horizProb) 
        horizontalWallSocket(row, col-1, 0, 1, GameGrid);
 
    else if (roll >= horizProb && roll < (horizProb + upVertProb))
        verticalWallSocket(row-1, col-1, 0, 1, GameGrid);

    else if (roll >= (horizProb + upVertProb) && 
            roll < (horizProb + upVertProb + downVertProb))
        verticalWallSocket(row+1, col-1, 1, 0, GameGrid);

    // If the checks for the rest fail, the adjacent space to the parent
    // horizontal wall piece will remain empty

    return 1;
}

int rollForRightHorizJoint(int row, int col, int horizProb,
       int upVertProb, int downVertProb, int blankSpaceProb, 
       int **GameGrid) {
   /*
    * Function rolling for what socket to attach to the left
    * joint of a horizontal wall piece
    *
    * :param row: row of the original horizontal wall piece
    * :param col: column of the original horizontal wall piece
    * :param horizProb: probability of attaching horizontal wall piece to left joint
    * :param upVertProb: probability of attaching vertical wall piece to upper
    *                    diagonal of left joint
    * :param downVertProb: probability og attaching vertical wall piece to bottom
    *                      diagonal of left joint
    * :param emptySpaceProb: probability of no attachment to joint
    * NOTE: all probabilities are expressed as integers from 0-100 (i.e., 40% prob
    *       of horizontal wall piece attachment is horizProb = 40
    */

    // Check to see if probabilities add up to 100. If not, return error
    int totalProb = horizProb + upVertProb + downVertProb;
    if ((totalProb) > 100 || (totalProb) < 100) 
        return -1;

    // Perform 'roll'
    int roll = rand() % 100;
    
    if (roll < horizProb) 
        horizontalWallSocket(row, col+1, 1, 0, GameGrid);
 
    else if (roll >= horizProb && roll < (horizProb + upVertProb))
        verticalWallSocket(row-1, col+1, 0, 1, GameGrid);

    else if (roll >= (horizProb + upVertProb) && 
            roll < (horizProb + upVertProb + downVertProb))
        verticalWallSocket(row+1, col+1, 1, 0, GameGrid);

    // If the checks for the rest fail, the adjacent space to the parent
    // horizontal wall piece will remain empty

    return 1;
}

int rollForUpperVertJoint(int row, int col, int vertProb,
       int rightHorizProb, int leftHorizProb, int blankSpaceProb,
       int **GameGrid) {
   /*
    * Function rolling for what socket to attach to the upper
    * joint of a vertical wall piece
    *
    * :param row: row of the original horizontal wall piece
    * :param col: column of the original horizontal wall piece
    * :param horizProb: probability of attaching horizontal wall piece to right joint
    * :param upVertProb: probability of attaching vertical wall piece to upper
    *                    diagonal of right joint
    * :param downVertProb: probability of attaching vertical wall piece to bottom
    *                      diagonal of right joint
    * :param emptySpaceProb: probability of no attachment to joint
    *  NOTE: all probabilities are expressed as integers from 0-100 (i.e., 40% prob
    *        of horizontal wall piece attachment is horizProb = 40
    */

    // Check to see if probabilities add up to 100. If not, return error
    int totalProb = vertProb + rightHorizProb + leftHorizProb + blankSpaceProb;
    if ((totalProb) > 100 || (totalProb) < 100) 
        return -1;

    // Perform 'roll'
    int roll = rand() % 100;
    
    if (roll < vertProb) 
        verticalWallSocket(row-1, col, 0, 1, GameGrid);
 
    else if (roll >= vertProb && roll < (vertProb + rightHorizProb))
        horizontalWallSocket(row-1, col+1, 0, 1, GameGrid);

    else if (roll >= (vertProb + rightHorizProb) && 
            roll < (vertProb + rightHorizProb + leftHorizProb))
        horizontalWallSocket(row-1, col-1, 1, 0, GameGrid);

    // If the checks for the rest fail, the adjacent space to the parent
    // horizontal wall piece will remain empty

    return 1;
}

int rollForLowerVertJoint(int row, int col, int vertProb,
       int rightHorizProb, int leftHorizProb, int blankSpaceProb, 
       int **GameGrid) {
   /*
    * Function rolling for what socket to attach to the left
    * joint of a horizontal wall piece
    *
    * :param row: row of the original horizontal wall piece
    * :param col: column of the original horizontal wall piece
    * :param horizProb: probability of attaching horizontal wall piece to left joint
    * :param upVertProb: probability of attaching vertical wall piece to upper
    *                    diagonal of left joint
    * :param downVertProb: probability og attaching vertical wall piece to bottom
    *                      diagonal of left joint
    * :param emptySpaceProb: probability of no attachment to joint
    * NOTE: all probabilities are expressed as integers from 0-100 (i.e., 40% prob
    *       of horizontal wall piece attachment is horizProb = 40
    */

    // Check to see if probabilities add up to 100. If not, return error
    int totalProb = vertProb + rightHorizProb + leftHorizProb + blankSpaceProb;
    if ((totalProb) > 100 || (totalProb) < 100) 
        return -1;

    // Perform 'roll'
    int roll = rand() % 100;
    
    if (roll < vertProb) 
        verticalWallSocket(row+1, col, 0, 1, GameGrid);
 
    else if (roll >= vertProb && roll < (vertProb + rightHorizProb))
        horizontalWallSocket(row+1, col+1, 0, 1, GameGrid);

    else if (roll >= (vertProb + rightHorizProb) && 
            roll < (vertProb + rightHorizProb + leftHorizProb))
        horizontalWallSocket(row+1, col-1, 1, 0, GameGrid);

    // If the checks for the rest fail, the adjacent space to the parent
    // horizontal wall piece will remain empty

    return 1;
}

int main() {
    int length = 3;
    int speed = 2;
    // Initialize snake
    struct Snake snek = {};
    snek.length = length;
    snek.speed = speed;
    snek.pos_x = (WIDTH / 2) + (snek.length / 2);
    snek.pos_y = (HEIGHT / 2);

    // Initialize GameGrid
    int **GameGrid;

    // Initialize Game Grid
    GameGrid = (int **) malloc(HEIGHT * sizeof(int*));
    for (int row = 0; row < HEIGHT; row++) {
        GameGrid[row] = (int *) malloc(WIDTH * sizeof(int));
    }

    GenerateGameSpace(snek, 5, 10, GameGrid);

    // print game board
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%d", GameGrid[i][j]);

            // Move onto next line if we are at end of column
            if (j == WIDTH - 1)
                printf("\n");
        }
    }

//    free(GameGrid);
}
