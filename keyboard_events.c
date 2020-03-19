/* Code from W.Richard Steven's Unix Programming Book
 */
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "termios.h"
#include "unistd.h"

#include "keyboard_events.h"

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

void exitGame(int fd) {
    /* Actions to perform after ctrl-c event */
    tty_reset(fd);
    close(fd);
    printf("Quitting Game\n");
    exit(EXIT_SUCCESS);
}

//int main(int argc, char **argv){
////    close(fd);
//    int DeviceHandle;
//    DeviceHandle = open_device();
////    atexit(exitint);
//
////    signal(SIGINT, sigint);
//    char input[MAX_STRING_SIZE] = {0};
//
//    printf("Got this far\n"); 
//
//    if (tty_raw(DeviceHandle) == 0) {
//        int upArrow = 0;
//        for(int i = 0; i < 10; i++) {
//            printf("Enter input: ");
//            sleep(1);
//            read(DeviceHandle, input, MAX_STRING_SIZE);
//            printf("%s\n", input);
//           //     for (int i = 0; i < MAX_STRING_SIZE; i++) {
//           //         if (input[i] == '\33') {
//           //             if (input[i+2] == 'A') {
//           //                 upArrow = 1;
//           //                 break;
//           //             }
//           //         }
//           //     }
//           // }
//            printf("iteration: %d\n", i);
//            if (strcmp(input, "q") == 0) {
//                sigint(DeviceHandle);
//            }
//        }
//        tty_reset(DeviceHandle);
//    }
//
//    close(DeviceHandle);
//    printf("closing device");
//    return 0;
//}
//
