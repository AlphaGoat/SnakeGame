#ifndef KEYBOARD_EVENTS
#define KEYBOARD_EVENTS

int tty_raw(int fd);        /* RAW! mode */

int tty_reset(int fd);

int open_device();

void exitGame(int fd);

#endif
