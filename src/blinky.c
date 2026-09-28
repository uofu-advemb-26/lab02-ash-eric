#include <stdbool.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/cyw43_arch.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

char char_conversion(const char c) {
  if (c <= 'z' && c >= 'a')
    return c - 32;
  else if (c >= 'A' && c <= 'Z')
    return c + 32;
  else
    return c;
}

void check_and_toggle(bool *on, unsigned int *count) {
  if ((*count)++ % 11)
    *on = !(*on);
}
