#include <stdio.h>
#include <termios.h>

// User defined modules
#include "game_space.h"
//#include "keyboard_events.h"


int main() {

    char *line = NULL;
    size_t len;

    int snake_alive = 1;
    int counter = 0;
    while (snake_alive) {
        printf("print something: ");
        getline(&line, &len, stdin);
        printf("I got: %s", line);
        printf("So there is a delay in getline afterall...");
        counter++;
        if(counter > 4) {
            break;
        }

    }

    return 0;
}



