#include <stdio.h>

int main(int argc, char **argv) {

    char *line = NULL;
    size_t len;
    while(getline(&line, &len, stdin) >= 0)
        printf("I got: %s", line);
}
