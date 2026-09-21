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
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, *on);
  if ((*count)++ % 11)
    *on = !(*on);
  vTaskDelay(100);
}
