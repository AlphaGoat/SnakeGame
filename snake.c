#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>


// User defined modules
#include "game_space.h"
#include "snake.h"
#include "keyboard_events.h"

#define MAX_STRING_SIZE 100

static int rand_snek_flag;

// Command line arguments
static struct option long_options[] =
    {
        /* These options set a flag */
        {"random_sneks", no_argument, &rand_snek_flag, 1},
        /* These options don't set a flag */
        {"version", no_argument,          0, 'v'},
        {"help",    no_argument,          0, 'h'},
        {"num_sneks", optional_argument,  0, 's'},
        {"turn_time", optional_argument,  0, 't'},
        {0, 0, 0, 0}
};


int main(int argc, char **argv) {

    int c;

    // Pre initialize game variables
    int num_sneks = 1;
    float turn_time = 1.0;

    // Manage commamnd line arguments
    while(1) {
        int option_index = 0;

        c = getopt_long(argc, argv, "vhs::t::",
                long_options, &option_index);

        /* Detect the end of the options */
        if (c == -1) 
            break;

        switch(c) {
            case 0:
                /* If this option set a flag, do nothing else now */
                if (long_options[option_index].flag != 0) 
                    break;
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
                break;

            case 'v':
                /* Version flag */
                printf("SnakeGame v1.0");
                return 0;

            case 'h':
                /* Help argument */
                print_help_statement();

            case 's':
                num_sneks = atoi(optarg);

            case 't':
                turn_time = atof(optarg);
        }
    }


    char *line = NULL;
    size_t len;
    
    // Initialize snek
    int snake_length = 5;
    int speed = 1;

    struct SnakeBodySegment snek[snake_length];
    struct SnakeBodySegment *snek_ptr;
    snek_ptr = snek;

    // Generate random game grid
    int **GameGrid;
    GameGrid = (int **) malloc(HEIGHT * sizeof(int*));
    for (int row = 0; row < HEIGHT; row++) {
        GameGrid[row] = (int *) malloc(WIDTH * sizeof(int));
    }
    GenerateGameSpace(5, 10, GameGrid, snek, snake_length);

    // Open port to terminal being accessed by the user 
    // playing the game
    int fd;
    fd = open_device(); 

    char user_input[MAX_STRING_SIZE];

    // Start game by printing out initial state of board
    printGameBoard(GameGrid);

    // Initiate game loop
    int snek_alive = 1;
    int score = 0;
    while (snek_alive) {

        // Set terminal in raw mode to handle user input
        if (tty_raw(fd) != 0) {
            printf("Error. Unable to set terminal in raw mode\n");
            printf("Exiting game.\n");
            tty_reset(fd);
            close(fd);
            return 1;
        }

        // Stop game for moment to give user time to react
        int input_recieved = 0; // Flag to close input buffer to further user input
        clock_t start = clock();
        clock_t end;
        double time_taken;
        while(time_taken < turn_time) {

            // Check if user has input a command
//            if (!input_recieved)
            read(fd, user_input, MAX_STRING_SIZE);

            // Parse input
            if (strcmp(user_input, "q") == 0) {
 //               input_recieved = 1;
                exitGame(fd);
                break; // Shouldn't get to this line...hopefully
            }
            else if (strcmp(user_input, "w") == 0) {
//                input_recieved = 1;
                snek[0].direction = up;
            }
            else if (strcmp(user_input, "d") == 0) {
 //               input_recieved = 1;
                snek[0].direction = right;
            }
            else if (strcmp(user_input, "s") == 0) {
//                input_recieved = 1;
                snek[0].direction = down;
            }
            else if (strcmp(user_input, "a") == 0) {
//                input_recieved = 1;
                snek[0].direction = left;
            }
            end = clock();
            time_taken = ((double)(end - start))/CLOCKS_PER_SEC;
        }
        // Reset timer
        time_taken = 0.0;

        // Flush terminal input buffer
        user_input[0] = '\0';

        // Move snek
        for (int i = 0; i < snake_length; i++) {
            // Clear space previously occupied by snake segment
            int pre_row = snek[i].pos_y;
            int pre_col = snek[i].pos_x;
            GameGrid[pre_row][pre_col] = blank_space;

            // Resolve collisions
            if(!movement(&snek[i], GameGrid)) {
                int post_row = snek[i].pos_y;
                int post_col = snek[i].pos_x;
                // If the object the snake collided with is food,
                // increase user score and continue
                if (GameGrid[post_row][post_col] == food) {
                    score += 500;
                    GameGrid[post_row][post_col] = snek[i].type;
                }
                // If the snake collides with anything else, it dies
                else {
                    snek_alive = 0;
                    GameGrid[post_row][post_col] = collision; 
                }
            }
            // Update direction of travel for body segment,
            // and store the direction of travel from this turn
            if (i > 1) {
                snek[i].prev_direction = snek[i].direction;
                snek[i].direction = snek[i-1].prev_direction;
            }
            else if (i == 1) {
                snek[i].prev_direction = snek[i].direction;
                snek[i].direction = snek[0].direction;
            }
        }

        // Print out current state of game board. Need to set
        // terminal in canonical mode first
        tty_reset(fd);
        printf("Score: %d\n", score);
        printGameBoard(GameGrid);

        // Randomly generate food
        int foodGenProb = 1; // (1/100) chance of empty square spawning more food
        randomlyGenerateFood(foodGenProb, GameGrid);
    }

    exitGame(fd);

    return 0;
}

int movement(struct SnakeBodySegment *segment, int **GameGrid) {

    int row;
    int col;

    int direction = segment->direction;

    row = segment->pos_y;
    col = segment->pos_x;

    if (direction == up) {
        --segment->pos_y; 
        // Check for collision
        if (GameGrid[row-1][col] != blank_space) {
            return 0;
        }
        GameGrid[row-1][col] = segment->type;
    }

    else if (direction == down) {
        ++segment->pos_y;
        if (GameGrid[row+1][col] != blank_space) {
            return 0;
        }
        GameGrid[row+1][col] = segment->type;
    }

    else if (direction == left) {
        --segment->pos_x;
        if (GameGrid[row][col-1] != blank_space) {
            return 0;
        }
        GameGrid[row][col-1] = segment->type;
    }

    else {
        ++segment->pos_x;
        if (GameGrid[row][col+1] != blank_space) {
            return 0;
        }
        GameGrid[row][col+1] = segment->type;
    }
    return 1;
}

void print_help_statement(){
    printf("Help Options\n");
}





