/* Code from W.Richard Steven's Unix Programming Book
 */
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include "termios.h"
#include "unistd.h"

#define MAX_STRING_SIZE 100

static struct termios  save_termios;
static int             term_saved;

int device_handle;

int tty_raw(int fd) {       /* RAW! mode */
    struct termios buf;

    if (tcgetattr(fd, &save_termios) < 0) /* get the original state */
        return -1;

    buf = save_termios;

    buf.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
                    /* echo off, canonical mode off, extended input
                     * processing off, signal chars off */

    buf.c_iflag &= ~(BRKINT | ICRNL | ISTRIP | IXON);
                    /* no SIGINT on BREAK, CR-toNL off, input parity
                     * check off, don't strip the 8th bit on input,
                     * output flow control off 
                     */

    buf.c_cflag &= ~(CSIZE | PARENB);
                    /* clear size bits, parity checking off */

    buf.c_cflag |= CS8;
                    /* set 8 bits/char */

    buf.c_oflag &= ~(OPOST);

    buf.c_cc[VMIN] = 1; /* 1 byte at a time */
    buf.c_cc[VTIME] = 0; // No timer on input

    if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
        return -1;

    term_saved = 1;

    return 0;
}

int tty_reset(int fd) {
    if (term_saved)
        if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
            return -1;

    return 0;
}

int open_device() {
    const char device[] = "/dev/tty";
    int fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        printf("failed to open port\n");
        return fd;
    }
    return fd;
}

void sigint(int fd) {
    /* Actions to perform after ctrl-c event */
    tty_reset(fd);
    close(fd);
}

int main(int argc, char **argv){
    // Print "Hello World" to terminal
//    FILE *f = fopen("/dev/tty", "w");
//    fprintf(f, "Hello, world!\n");

//    // Test reading input from terminal
//    char input[MAX_STRING_SIZE] = {0};
//
//    // Test opening terminal input
//    int fd = open_device();
//    if (tty_raw(fd)) {
//        int upArrow = 0;
//
//        printf("Opened device");
//
//        size_t bytes_read = read(fd, input, MAX_STRING_SIZE);
//        for (int i = 0; i < (int) bytes_read; i++) {
//            if (input[i] == '\33') {
//                if (input[i+2] == 'A') {
//                    upArrow = 1;
//                    break;
//                }
//            }
//        }
//
//    if (upArrow) {
//        printf("Registered 'arrow-up' event");
//    }
//
////            fgets(input, sizeof(input), stdin);
////            flush_input(input);
//            
//        tty_reset(fd);
//    }
//    close(fd);
    device_handle = open_device();

    signal(SIGINT, sigint);
    char input[MAX_STRING_SIZE] = {0};

    if (tty_raw(device_handle)) {
        int upArrow = 0;
        printf("opened device");

        while(1) {
            while(read(device_handle, input, MAX_STRING_SIZE > 0)) {
                for (int i = 0; i < MAX_STRING_SIZE; i++) {
                    if (input[i] == '\33') {
                        if (input[i+2] == 'A') {
                            upArrow = 1;
                            break;
                        }
                    }
                }
            }
        }
        tty_reset(device_handle);
    }

    close(device_handle);
    return 0;
 }

