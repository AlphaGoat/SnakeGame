#include <stdio.h>
#include <stdlib.h>

#include "game_space.h"
#include "snake.h"


const struct SnakeBodySegment NullSeg = {0};

// TODO: Try to get this working....
int GenerateSnake(int row, int col, int segs2generate, int direction,
         struct Snake *snek_ptr, int **GameGrid) {
    /* Checks for a path free of obstacles to place snake
     * :param row:            row of starting position
     * :param col:            column of starting position
     * :param segs2generate:  number of snake body segments left to generate
     * :param direction:      direction to last segment that was laid down,
     *                        relative to the current position (up, down,
     *                        right, or left)
     * :param npc_snek_flag:  flag that tells generator whether or not the
     *                        snake will be controlled by the player or not
     *                        (npc snakes have different appearance on board
     *                        from player snake to allow user to differentiate)
     * :param snek_ptr:       Pointer to snake structure containing and
     *                        tracking all body segments of snake 
     * :param GameGrid:       pointer to 2-D array of game grid
     */
    int snek_length = snek_ptr->length;
    int npc_flag = snek_ptr->npc;
    // Are we out of bounds?
    if (row >= HEIGHT || row < 0 || col >= WIDTH || col < 0) {
        return 0;
    }

    // Check to see if current space is occupied
    else if (GameGrid[row][col] != blank_space) {
        return 0;
    }

    // Check to see if this is the last segment of snake.
    // If so, generate a tail and return success!
    else if (segs2generate == 1) {
        int seg_number = snek_length - 1;
        if (npc_flag) {
            GenerateSnakeSegment(snek_ptr, row, col, direction, seg_number,
                 npc_snk_body, GameGrid);
        }
        else {
            GenerateSnakeSegment(snek_ptr, row, col, direction, seg_number,
                    snk_body, GameGrid);
        }
        return 1;
    }

    // If space is not occupied, generate snake segment
    else if (segs2generate == snek_length){
        // If this is the first step through recursion, then generate a snake head
        if (npc_flag) {
            GenerateSnakeSegment(snek_ptr, row, col, direction, 
                    0, npc_snk_head, GameGrid);
        }
        else {
            GenerateSnakeSegment(snek_ptr, row, col, direction, 
                    0, snk_head, GameGrid);
        } 

        // Otherwise, generate a body segment
    }
    else {
        int seg_number = (snek_length - segs2generate);
//        printf("On seg_number: %d\n", seg_number);
        if (npc_flag) {
            GenerateSnakeSegment(snek_ptr, row, col, direction,
                    seg_number, npc_snk_body, GameGrid);
        }
        else {
            GenerateSnakeSegment(snek_ptr, row, col, direction, 
                    seg_number, snk_body, GameGrid);
        }
    }

    // Check all paths around current position to see if 
    // further snake segments can be laid out
    // UP ----
    if (direction != up) {
        if (GenerateSnake(row-1, col, segs2generate-1, down, 
                    snek_ptr, GameGrid)) {
            return 1;
        }
    }

    // DOWN ----
    if (direction != down) {
        if (GenerateSnake(row+1, col, segs2generate-1, up, 
                    snek_ptr, GameGrid)) {
            return 1;
        }
    }

    // RIGHT ----
    if (direction != right) {
        if (GenerateSnake(row, col+1, segs2generate-1, left, 
                    snek_ptr, GameGrid)) {
            return 1;
        }
    }

    // LEFT ----
    if (direction != left) {
        if (GenerateSnake(row, col-1, segs2generate-1, right, 
                    snek_ptr, GameGrid)) {
            return 1;
        }
    }

    // If there are no more spaces to go, remove the snake segment
    // from current position
    // Remove segment from GameGrid
    GameGrid[row][col] = blank_space;
    int seg_number = (snek_length - segs2generate);
//    snek->segments[n] = NULL;
    snek_ptr->segments[seg_number] = NullSeg;
    return 0;
}
//
void GenerateSnakeSegment(struct Snake *snek_ptr, int row, int col,
        int direction, int seg_number, int seg_type, int **GameGrid) {
    /* Wrapper function to generate a snake segment
     * :param snek:    pointer to snake structure
     * :param row:     row we are placing body segment
     * :param col:     column we are placing body segment
     * :param direction: direction that body segment is facing
     */
    struct SnakeBodySegment body_segment;
    body_segment.pos_y = row;
    body_segment.pos_x = col;
    body_segment.direction = direction;
    body_segment.type = seg_type;
    snek_ptr->segments[seg_number] = body_segment;

    // Place segment on GameGrid
    GameGrid[row][col] = seg_type;
}

void GenerateGameSpace(int foodGenProb, int wallGenProb, int **GameGrid){


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

//    // Generate snake body
//    for (int i = 0; i < snake_length; i++) {
//        // Place snake at top left of board and leave enough room for
//        // whole body
//        if (i == 0) {
//            struct SnakeBodySegment head_segment;
//            head_segment.direction = right;
//            //head_segment.linked_direction = &head_segment.direction;
//            head_segment.pos_x = snake_length;
//            head_segment.pos_y = 1;
//            head_segment.type = snk_head;
//            snek_ptr[i] = head_segment;
//            GameGrid[head_segment.pos_y][head_segment.pos_x] = snk_head;
//        }
//        else if (i == snake_length-1) {
//            struct SnakeBodySegment tail_segment; 
//            tail_segment.direction = right;
//            //tail_segment.linked_direction = &snek_ptr[i-1].direction; 
//            tail_segment.pos_x = 1;
//            tail_segment.pos_y = 1;
//            tail_segment.type = snk_tail;
//            snek_ptr[i] = tail_segment;
//            GameGrid[1][1] = snk_tail;
//        }
//        else {
//            struct SnakeBodySegment body_segment; 
//            body_segment.direction = right;
//            //body_segment.linked_direction = &snek_ptr[i-1].direction; 
//            body_segment.pos_x = snake_length - i;
//            body_segment.pos_y = 1;
//            body_segment.type = snk_body;
//            snek_ptr[i] = body_segment;
//            GameGrid[1][body_segment.pos_x] = snk_body;
//        }
//    }

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

void printGameBoard(int **GameGrid) {
    // As the name implies, prints out the current status of game board
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%d", GameGrid[i][j]);

            // Move onto next line if we are at end of column
            if (j == WIDTH - 1)
                printf("\n");
        }
    }
    printf("\n");
}

void randomlyGenerateFood(int foodGenProb, int **GameGrid) {
    /* Function to randomly generate food on GameGrid */
    for (int i; i < HEIGHT; i++) {
        for (int j; j < WIDTH; j++) {
            if (GameGrid[i][j] == blank_space) {
                int roll = rand() % 100;
                if (roll < foodGenProb) {
                    GameGrid[i][j] = food;
                }
            }
        }
    }
}

void randomlyPlaceSneks(struct Snake *snek_ptr, int **GameGrid) {
    /* Randomly places all sneks in input array
     * on Game Grid*/

    // Generate snakes in game grid
    // Initialize counter to keep track of the number of snakes
    // that have been generated
    int counter = 0;

    // test counter, just to ensure that the while loop exits 
    int test_counter = 0;
    int snake_generated = 0;
    while (!snake_generated) {
        // Randomly generate a starting point for the snake 
        // in the game grid and the direction of travel for the snake
        int start_row = 1 + (rand() % 19);
        int start_col = 1 + (rand() % 19);
        int direction = rand() % 4;

        int segs2generate;
        segs2generate = snek_ptr->length;


        if (GenerateSnake(start_row, start_col, segs2generate, direction, 
                    snek_ptr, GameGrid)) {
            snake_generated = 1;
        }

        // JUST FOR TESTING PURPOSES
        test_counter += 1;
        if (test_counter > 100) {
            printf("Too many iterations in while loop\n");
            exit(0);
            freeGameGridMemory(GameGrid);
        }
            // Iterate num_snakes_counter by one
    }

}


int cleanUpDeadSnek(struct Snake *snek, int **GameGrid) {
    /* Removes spaces in Game Grid that used to be occupied
     * by snake
     */
    for (int i = 0; i < snek->length; i++) {
        int row = snek->segments[i].pos_y;
        int col = snek->segments[i].pos_x;
        GameGrid[row][col] = blank_space;
        // What if dead snakes became food?
        // GameGrid[row][col] = food;
    }
    return 1;
}


void freeGameGridMemory(int **GameGrid) {
    for (int i = 0; i < HEIGHT; i++) {
        free(GameGrid[i]);
    }
    free(GameGrid);
    GameGrid = NULL;
}

