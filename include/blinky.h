#ifndef BLINKY_H
#define BLINKY_H

#include <stdbool.h>

/*
 Toggling procedure for the LED.
 Modifies `on` and `count` in-place.
*/
void check_and_toggle(bool *on, unsigned int *count);

/*
 Externally identical behavior for the original char logic
 in `hello_freertos.c`.
 Refactored for easier testing.
*/
char char_conversion(const char c);

#endif
