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
#include "npc_behavior.h"

#define MAX_INPUT_SIZE 1

static int rand_snek_flag;

// Command line arguments
static struct option long_options[] =
    {
        /* These options set a flag */
        {"random_sneks", no_argument, &rand_snek_flag, 1},
        /* These options don't set a flag */
        {"version",       no_argument,       0, 'v'},
        {"help",          no_argument,       0, 'h'},
        {"num_sneks",     required_argument, 0, 's'},
        {"turn_time",     required_argument, 0, 't'},
        {"food_gen_prob", required_argument, 0, 'f'},
        {0, 0, 0, 0}
};

const int MAX_SNAKE_BUF = 10;

int main(int argc, char **argv) {

    int c;

    /* Seeds random number generator */
    time_t t;
    srand((unsigned) time(&t));

    // Pre initialize game variables
//    int num_sneks = 1;
    float turn_time = 1.0;
    int food_gen_prob = 1; // (1/100) chance of empty square spawning more food

    /*---------------- TEST ----------------------------- */
 //   int fd;
 //   fd = open_device(); 
 //   // Set terminal in raw mode to handle user input
 //   if (tty_raw(fd) != 0) {
 //       printf("Error. Unable to set terminal in raw mode\n");
 //       printf("Exiting game.\n");
 //       tty_reset(fd);
 //       close(fd);
 //       return 1;
 //   }
    
 //   float test_float;
 //   char float_buff[3] = "1.5";
 //   test_float = atof(float_buff);
//    test_float = atof("2.3");
//    printf("value of test_float, after conversion: %f", test);
//    long test_long;
//    char test_str[30] = "40587 this is a test";
//    char *test_ptr;
//    test_long = strtol(test_str, &test_ptr, 10);
//    test_int = atoi("3");
//    printf("value of test_int, after conversion: %d", test_int);
//    tty_reset(fd);
    /*---------------- TEST ----------------------------- */
    
    // Manage commamnd line arguments
//    while(1) {
//        int option_index = 0;
//
//        c = getopt_long(argc, argv, "vhs:t:f:",
//                long_options, &option_index);
//
//        /* Detect the end of the options */
//        if (c == -1) 
//            break;
//
//        switch(c) {
//            case 0:
//                /* If this option set a flag, do nothing else now */
//                if (long_options[option_index].flag != 0) 
//                    break;
//                printf("option %s", long_options[option_index].name);
//                if (optarg)
//                    printf(" with arg %s", optarg);
//                printf("\n");
//                break;
//
//            case 'v':
//                /* Version flag */
//                printf("SnakeGame v1.0");
//                return 0;
//
//            case 'h':
//                /* Help argument */
//                print_help_statement();
//
//            case 's':
//                if (optarg)
//                    num_sneks = atoi(optarg);
//                else {
//                    printf("Error: argument not read.\n");
//                    printf("Try specifying arg val with '=' next time\n");
//                }
//
//            case 't':
//                if (optarg) {
//                    printf("This is the argument to turn_time: %s", optarg);
//                    turn_time = atof(optarg);
//                }
//                else {
//                    printf("Error: argument not read.\n");
//                    printf("Try specifying arg val with '=' next time\n");
//                }
//
//            case 'f':
//                food_gen_prob = atoi(optarg);
//        }
//    }
    const int num_sneks = 3;

    char *line = NULL;
    size_t len;
    
    // initialize variables for snek generation
    const int snake_length = 5;
    const int speed = 1;

    // Generate random game grid
    int **GameGrid;
    GameGrid = (int **) malloc(HEIGHT * sizeof(int*));
    for (int row = 0; row < HEIGHT; row++) {
        GameGrid[row] = (int *) malloc(WIDTH * sizeof(int));
    }
    GenerateGameSpace(5, 10, GameGrid);

    // Generate snakes in game grid
    int num_snakes_gen_counter = 0;
    // test counter, just to ensure that the while loop exits 
    int test_counter = 0;
    
    struct Snake snek_array[MAX_SNAKE_BUF];
    // Place snakes in random positions on Game Grid
    for (int i = 0; i < num_sneks; i++) {
        // If first iteration, generate player snake first
        if (i == 0){
            struct Snake player_snek;
            player_snek.length = snake_length;
            player_snek.alive = 1;
            player_snek.npc = 0;
            randomlyPlaceSneks(&player_snek, GameGrid);
            snek_array[0] = player_snek;
        }
        else {
            struct Snake npc_snek;
            npc_snek.length = snake_length;
            npc_snek.alive = 1;
            npc_snek.npc = 1;
            randomlyPlaceSneks(&npc_snek, GameGrid);
            snek_array[i] = npc_snek;
        }
    }

//    freeGameGridMemory(GameGrid);


    // Open port to terminal being accessed by the user 
    // playing the game
    int fd;
    fd = open_device(); 

    char user_input[MAX_INPUT_SIZE];

    // Start game by printing out initial state of board
    printf("Welcome to the Game of Snakes!\n");
    printf("Pwease no steppy\n");
    printGameBoard(GameGrid);
    sleep(5.0);

    // Init vars for game loop
    int score = 0;

    // pointer to player snake 'alive' flag (1-alive, 0-dead)
    int *alive_flag;
    alive_flag = &snek_array[0].alive;

    // Initiate game loop
    while (*alive_flag) {

        // Loop over all generated snakes
        for (int j = 0; j < num_sneks; j++) {

            struct Snake *snek;
            snek = &snek_array[j];
            int x_pos = snek->segments[0].pos_x;

            // The first snake in the array will always be the user
            if (j == 0) {
                // Set terminal in raw mode to handle user input
                if (tty_raw(fd) != 0) {
                    printf("Error. Unable to set terminal in raw mode\n");
                    printf("Exiting game.\n");
                    tty_reset(fd);
                    close(fd);
                    return 1;
                }

                // Stop game for moment to give user time to react
//                int input_recieved = 0; // Flag to close input buffer to further user input
                clock_t start = clock();
                clock_t end;
                double time_taken;
//                struct SnakeBodySegment *head;
//                head = &(curr_snek->segments[0]);
                while(time_taken < turn_time) {

                    // Check if user has input a command
        //            if (!input_recieved)
                    read(fd, user_input, MAX_INPUT_SIZE);

                    // Parse input
                    if (strcmp(&user_input[0], "q") == 0) {
         //               input_recieved = 1;
                        exitGame(fd);
                        break; // Shouldn't get to this line...hopefully
                    }
                    else if (strcmp(&user_input[0], "w") == 0){
                        snek->segments[0].direction = up;
                    }
                    else if (strcmp(&user_input[0], "d") == 0){
                        snek->segments[0].direction = right;
                    }
                    else if (strcmp(&user_input[0], "s") == 0){
                        snek->segments[0].direction = down;
                    }
                    else if (strcmp(&user_input[0], "a") == 0){
                        snek->segments[0].direction = left;
                    }
                    end = clock();
                    time_taken = ((double)(end - start))/CLOCKS_PER_SEC;
                }
                // Reset timer
                time_taken = 0.0;
//                printf("user_input: %s\n", user_input);
//                printf("user_input first char: %s\n", &user_input[0]);
            }
            // Perform actions for npc snakes
            else {
                // Check if snake is still alive. If not, no action needs
                // to be taken
                if (snek->alive) 
                    basicNPCSnekBehavior(snek, GameGrid);
                else
                    continue;
            }
                

            // Flush terminal input buffer
            //user_input[0] = '\0';
            
            // For some inexplicable reason, this is necessary 
            // changing the direction of the head
            // segment initializes it's pos_x to a random value
            snek->segments[0].pos_x = x_pos;

            // Move snek
            for (int i = 0; i < snake_length; i++) {
                // Clear space previously occupied by snake segment
                struct SnakeBodySegment *segment;
                segment = &(snek->segments[i]);
                int pre_row = segment->pos_y;
                int pre_col = segment->pos_x;
                GameGrid[pre_row][pre_col] = blank_space;

                // Resolve collisions
                if(!movement(segment, GameGrid)) {
                    int post_row = segment->pos_y;
                    int post_col = segment->pos_x;
                    // If the object the snake collided with is food,
                    // increase user score and continue
                    if (GameGrid[post_row][post_col] == food) {
                        // If player snake, increase score
                        if (j == 0)
                            score += 500;

                        GameGrid[post_row][post_col] = segment->type;
                    }
                    // If the snake collides with anything else, it dies
                    else {
                        // If the snake is the player, set 'snake_alive'
                        // flag to zero, and end game
//                        if (j == 0) {
                        snek->alive = 0;
                        
                        GameGrid[post_row][post_col] = collision; 
                    }
                }
                // Update direction of travel for body segment,
                // and store the direction of travel from this turn
                if (i > 0) {
                    segment->prev_direction = segment->direction;
                    segment->direction = snek->segments[i-1].prev_direction;
                }
                else if (i == 0) {
                    segment->prev_direction = segment->direction;
//                    segment->direction = segment->direction;
                }
            }

            // Print out current state of game board. Need to set
            // terminal in canonical mode first
            tty_reset(fd);
            printf("Score: %d\n", score);
            printGameBoard(GameGrid);

            // Randomly generate food
            randomlyGenerateFood(food_gen_prob, GameGrid);
        }
    }

    // Free memory for game grid
    freeGameGridMemory(GameGrid);

    // Reset terminal to canonical mode, close connection 
    // to terminal, and end game
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
        segment->pos_y = segment->pos_y - 1;
        // Check for collision
        if (GameGrid[row-1][col] != blank_space) {
            return 0;
        }
        GameGrid[row-1][col] = segment->type;
    }

    else if (direction == down) {
        segment->pos_y = segment->pos_y + 1;
        if (GameGrid[row+1][col] != blank_space) {
            return 0;
        }
        GameGrid[row+1][col] = segment->type;
    }

    else if (direction == left) {
        segment->pos_x = segment->pos_x - 1;
        if (GameGrid[row][col-1] != blank_space) {
            return 0;
        }
        GameGrid[row][col-1] = segment->type;
    }

    else {
        segment->pos_x = segment->pos_x + 1;
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




