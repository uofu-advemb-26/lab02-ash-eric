/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdbool.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/cyw43_arch.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

#include "blinky.h"

// int count = 0;
// bool on = false;

#define MAIN_TASK_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define BLINK_TASK_PRIORITY (tskIDLE_PRIORITY + 2UL)
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

/*
 Blinky task. Self explanatory.
*/
void blink_task(__unused void *params) {
  bool on = false;
  // unsigned to avoid undefined behavior
  unsigned int count = 0;

  hard_assert(cyw43_arch_init() == PICO_OK);

  // loop forever toggling the LED
  while (true) {
    check_and_toggle(&on, &count);
  }
}

/*
 Repeat main loop.
 Aside from starting the blinky task, serves as a bastardization
 of a REPL.
*/
void main_task(__unused void *params) {
  xTaskCreate(blink_task, "BlinkThread", BLINK_TASK_STACK_SIZE, NULL,
              BLINK_TASK_PRIORITY, NULL);
  char c;
  while (c = getchar()) {
    if (c <= 'z' && c >= 'a')
      putchar(c - 32);
    else if (c >= 'A' && c <= 'Z')
      putchar(c + 32);
    else
      putchar(c);
  }
}

/*
 `main` procedure; sets up all of the necessary peripherals and
 the main task at boot. First stop after the boot sequence.
*/
int main(void) {
  stdio_init_all();
  const char *rtos_name;
  rtos_name = "FreeRTOS";
  TaskHandle_t task;
  xTaskCreate(main_task, "MainThread", MAIN_TASK_STACK_SIZE, NULL,
              MAIN_TASK_PRIORITY, &task);

  // load-bearing scheduler start procedure
  vTaskStartScheduler();
  return 0;
}
