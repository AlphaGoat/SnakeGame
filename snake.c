#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

// User defined modules
#include "game_space.h"
#include "keyboard_events.h"

#define MAX_STRING_SIZE 100

int main() {

    char *line = NULL;
    size_t len;
    
    // Initialize snek
    int length = 5;
    int speed = 1;
    int direction = right;
    struct Snake snek = {};
    snek.length = length;
    snek.speed = speed;
    snek.direction = direction;
    snek.pos_x = (WIDTH / 2) + (snek.length / 2);
    snek.pos_y = (HEIGHT / 2);

    // Generate random game grid
    int **GameGrid;
    GenerateGameSpace(snek, 5, 10, GameGrid);

    // Set terminal in raw mode so that we can
    // process input from user as game is playing
    int fd;
    fd = open_device(); 
    if (tty_raw(fd) != 0) {
        printf("Error. Unable to set terminal in raw mode\n");
        printf("Exiting game.\n");
        tty_reset(fd);
        close(fd);
        return 1;
    }

    char user_input[MAX_STRING_SIZE];

    // Initiate game loop
    int snek_alive = 1;
    int score = 0;
    while (snek_alive) {

        // Check if user has input a command
        read(fd, user_input, MAX_STRING_SIZE);

        // Parse input
        if (strcmp(user_input, "q") == 0) {
            exitGame(fd);
        }
        else if (strcmp(user_input, "w") == 0) {
            snek.direction = up;
        }
        else if (strcmp(user_input, "d") == 0) {
            snek.direction = right;
        }
        else if (strcmp(user_input, "s") == 0) {
            snek.direction = down;
        }
        else if (strcmp(user_input, "a") == 0) {
            snek.direction = left;
        }

        // Move snek
        switch(snek.direction) {
            case up:
                ++snek.pos_y;
                break;
            case right:
                ++snek.pos_x;
                break;
            case down:
                --snek.pos_y;
                break;
            case left:
                --snek.pos_x;
                break;
        }
    }

    return 0;
}



