#include <stdio.h>
#include <stdlib.h>

#include "game_space.h"

// The Game Grid will consist of an array
// of pointers to integer values
//int **GameGrid;

//void GenerateSnake(int length, int speed, int direction, 
//        int pos_x, int pos_y, int **GameGrid) {
//    /* Generate a snake structure (Actually a case for several smaller structure,
//     * each consisting of a body segment of the snake, whose positions and direction
//     * of travel are tracked seperately
//     *
//     * :param length:    length of the snake (i.e., how many body segments it is 
//     *                   composed of
//     * :param speed:     speed of the snake
//     * :param direction: starting direction for all body segments of snake. An 
//     *                   internal direction parameters will be tracked seperately
//     *                   for each body segment
//     * :param pos_x:     column where the head of the snake will start
//     * :param pos_y:     row where the head of the snake will start
//     */
//    struct SnakeBodySegment segments[length];
//    // Loop to initialize each body segment of the snake
//    int next_pos_x;
//    int next_pos_y;
//    int next_direction;
//    for (int i = 0; i < length; i++) {
//        // Initialization for snake's head
//        if (i == 0) {
//            segments[i].pos_x = pos_x;
//            segments[i].pos_y = pos_y;
//            segments[i].direction = direction;
//            // point linked direction to head's own direction, so that
//            // they are the same (head of snake determines direction of travel)
//            segments[i].linked_direction = &segments[i].direction;
//            segments[i].type = snk_head;
//        }
//        // Initialization for snake's tail (same as with body segment,
//        // only the type for display on the game grid is different)
//        else if (i == (length - 1)) {
//            segments[i].pos_x = next_pos_x;
//            segments[i].pos_y = next_pos_y;
//            segments[i].direction = next_direction;
//            segments[i].linked_direction = &segments[i-1].direction;
//            segments[i].type = snk_tail;
//        }
//        // Initialization for snake's body
//        else {
//            segments[i].pos_x = next_pos_x;
//            segments[i].pos_y = next_pos_y;
//            segments[i].direction = next_direction;
//            segments[i].linked_direction = &segments[i-1].direction;
//            segments[i].type = snk_body;
//        }
//
//        // determine x,y position of next body segment        
//        switch(segments[i].direction) {
//            case down:
//                next_pos_y = segments[i].pos_y + 1;
//            case up:
//                next_pos_y = segments[i].pos_y - 1;
//            case left:
//                next_pos_x = segments[i].pos_x + 1;
//            case right:
//                next_pos_x = segments[i].pos_x - 1;
//        }
//
//        // Check if that position will put the snake in conflict with 
//        // any other piece of the board
////        if (GameGrid[next_pos_y][next_pos_x] != blank_space) {
////            if (segments[i].direction
////                    }
////                    }
////                    }
//            }
//}

// TODO: Try to get this working....
//int GenerateSnake(int row, int col, int length, int direction,
//        struct Snake *snek, int **GameGrid) {
//    /* Checks for a path free of obstacles to place snake
//     * :param row:       row of starting position
//     * :param col:       column of starting position
//     * :param length:    length of snake
//     * :param direction: direction to last segment that was laid down,
//     *                   relative to the current position (up, down,
//     *                   right, or left)
//     * :param snek:      Pointer to snake structure containing and
//     *                   tracking all body segments of snake 
//     * :param GameGrid:  pointer to 2-D array of game grid
//     */
//    // Are we out of bounds?
//    if (row >= HEIGHT || row < 0 || col >= WIDTH || col < 0) {
//        return 0;
//    }
//
//    // Check to see if current space is occupied
//    else if (GameGrid[row][col] != blank_space) {
//        return 0;
//    }
//
//    // Check to see if this is the last segment of snake.
//    // If so, generate a tail and return success!
//    else if (length == 1) {
//        GenerateSnakeSegment(snek, row, col, direction, snek->length-1, 
//                snk_tail, GameGrid);
//        return 1;
//    }
//
//    // If space is not occupied, generate snake segment
//    else {
//        // If this is the first step through recursion, then generate a snake head
//        if (length == snek->length) {
//            GenerateSnakeSegment(snek, row, col, direction, 0, snk_head, GameGrid);
//            printf("Generating head (seg_number 0)\n");
//        }
//        // Otherwise, generate a body segment
//        else {
//            int seg_number = (snek->length - length);
//            printf("On seg_number: %d\n", seg_number);
//            GenerateSnakeSegment(snek, row, col, direction, 
//                    seg_number, snk_body, GameGrid);
//        }
//    }
//
//    // Check all paths around current position to see if 
//    // further snake segments can be laid out
//    // UP ----
//    if (direction != up) {
//        if (GenerateSnake(row-1, col, length-1, down, snek, GameGrid)) {
//            return 1;
//        }
//    }
//
//    // DOWN ----
//    else if (direction != down) {
//        if (GenerateSnake(row+1, col, length-1, up, snek, GameGrid)) {
//            return 1;
//        }
//    }
//
//    // RIGHT ----
//    else if (direction != right) {
//        if (GenerateSnake(row, col+1, length-1, left, snek, GameGrid)) {
//            return 1;
//        }
//    }
//
//    // LEFT ----
//    else if (direction != left) {
//        if (GenerateSnake(row, col-1, length-1, right, snek, GameGrid)) {
//            return 1;
//        }
//    }
//
//    // If there are no more spaces to go, remove the snake segment
//    // from current position
//    else {
//        printf("Generating a null segment\n");
//        int n = (snek->length-length);
////        snek->segments[n] = NULL;
//        snek->segments[n] = NullSeg;
//        GameGrid[row][col] = blank_space;
//        return 0;
//    }
//}
//
//void GenerateSnakeSegment(struct Snake *snek, int row, int col,
//        int direction, int seg_number, int seg_type) {
//    /* Wrapper function to generate a snake segment
//     * :param snek:    pointer to snake structure
//     * :param row:     row we are placing body segment
//     * :param col:     column we are placing body segment
//     * :param direction: direction that body segment is facing
//     * :param linked_direction: direction that body segment that comes before 
//     *                          this one in snake structure is facing
//     */
//    struct SnakeBodySegment body_segment;
//    body_segment.pos_y = row;
//    body_segment.pos_x = col;
//    body_segment.direction = direction;
//
//    if (seg_type == snk_tail) {
//        body_segment.linked_direction = &(snek->segments[seg_number-1].direction);
//    }
//
//    else if (seg_type == snk_body) {
//        body_segment.linked_direction = &(snek->segments[seg_number-1].direction);
//    }
//
//    else {
//        body_segment.linked_direction = &body_segment.direction;
//    }
//
//    snek->segments[seg_number] = body_segment;
//}

void GenerateGameSpace(int foodGenProb, int wallGenProb, 
        int **GameGrid, struct SnakeBodySegment *snek_ptr, int snake_length){

    // Initialize game grid with blank spaces
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            GameGrid[i][j] = blank_space;
        }
    }

    // Create a buffer on the outer edge of grid
    for (int i = 0; i < WIDTH; i++) {
        GameGrid[0][i] = hwall;
        GameGrid[HEIGHT-1][i] = hwall;
    }

    for (int i = 1; i < HEIGHT-1; i++) {
        GameGrid[i][0] = vwall;
        GameGrid[i][WIDTH-1] = vwall;
    }

    // Generate snake body
    for (int i = 0; i < snake_length; i++) {
        // Place snake at top left of board and leave enough room for
        // whole body
        if (i == 0) {
            struct SnakeBodySegment head_segment;
            head_segment.direction = right;
            head_segment.linked_direction = &head_segment.direction;
            head_segment.pos_x = snake_length;
            head_segment.pos_y = 1;
            head_segment.type = snk_head;
            snek_ptr[i] = head_segment;
            GameGrid[head_segment.pos_y][head_segment.pos_x] = snk_head;
        }
        else if (i == snake_length-1) {
            struct SnakeBodySegment tail_segment; 
            tail_segment.direction = right;
            tail_segment.linked_direction = &snek_ptr[i-1].direction; 
            tail_segment.pos_x = 1;
            tail_segment.pos_y = 1;
            tail_segment.type = snk_tail;
            snek_ptr[i] = tail_segment;
            GameGrid[1][1] = snk_tail;
        }
        else {
            struct SnakeBodySegment body_segment; 
            body_segment.direction = right;
            body_segment.linked_direction = &snek_ptr[i-1].direction; 
            body_segment.pos_x = snake_length - i;
            body_segment.pos_y = 1;
            body_segment.type = snk_tail;
            snek_ptr[i] = body_segment;
            GameGrid[1][body_segment.pos_x] = snk_body;
        }
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
    int length = 5;
    int speed = 2;
    // Initialize snake
    struct SnakeBodySegment snake[length];
    struct SnakeBodySegment *snek_ptr = snake;

    // Initialize GameGrid
    int **GameGrid;

    // Initialize Game Grid
    GameGrid = (int **) malloc(HEIGHT * sizeof(int*));
    for (int row = 0; row < HEIGHT; row++) {
        GameGrid[row] = (int *) malloc(WIDTH * sizeof(int));
    }

    if (GameGrid == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    GenerateGameSpace(5, 10, GameGrid, snek_ptr, length);

    // print game board
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%d", GameGrid[i][j]);

            // Move onto next line if we are at end of column
            if (j == WIDTH - 1)
                printf("\n");
        }
    }

//    // Test generating snake
//    int snake_length = snek.length;
//    int break_outer_loop = 0;
//    for (int i = 1; i < HEIGHT-1; i++) {
//        if (break_outer_loop) {
//            break;
//        }
//        for (int j = 1; j < WIDTH-1; j++) {
//            if (GenerateSnake(i, j, snake_length, up, snek_ptr, GameGrid)) {
//                printf("Breaking snake generation loop\n");
//                break_outer_loop = 1;
//                break;
//            }
//        }
//    }
//
//    // Print out the size of array
//    size_t gameGridSize = sizeof(GameGrid) / sizeof(int);
//    printf("Size of GameGrid: %zu\n", gameGridSize);
    

//    // Check to see if any of the segments of the snake are null.
//    // If they are, then we failed in generating the snake
//    for (int i = 0; i < snek.length; i++) {
//        if (
//                snek.segments[i].direction == NullSeg.direction &&
//                snek.segments[i].linked_direction == NullSeg.linked_direction &&
//                snek.segments[i].pos_x == NullSeg.pos_x &&
//                snek.segments[i].pos_y == NullSeg.pos_y &&
//                snek.segments[i].type == NullSeg.type) {
//            printf("Segment %d of snake is a null value.", i);
//            printf("Exiting test run");
//            return 0;
//        }
//    }
//
//
//    // print game board with snake
//    for (int i = 0; i < HEIGHT; i++) {
//        for (int j = 0; j < WIDTH; j++) {
//            printf("%d", GameGrid[i][j]);
//
//            // Move onto next line if we are at end of column
//            if (j == WIDTH - 1)
//                printf("\n");
//        }
//    }

    // Go, my memory! Be free!
    for (int i = 0; i < HEIGHT; i++) {
        int *row_ptr = GameGrid[i];
        free(row_ptr);
    }
    free(GameGrid);
    return 1;
}
