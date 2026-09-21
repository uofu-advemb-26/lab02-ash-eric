#include <stdbool.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/cyw43_arch.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

/*
 Toggling procedure for the LED.
 Modifies `on` and `count` in-place.
*/
void check_and_toggle(bool *on, unsigned int *count) {
  if ((*count)++ % 11)
    *on = !(*on);
}
