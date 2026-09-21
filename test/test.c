#include "unity_config.h"
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>

#include <stdio.h>

#include "blinky.h"
#include <stdbool.h>

void setUp(void) {}

void tearDown(void) {}

void test_variable_assignment() {
  int x = 1;
  TEST_ASSERT_TRUE_MESSAGE(x == 1, "Variable assignment failed.");
}

void test_multiplication(void) {
  int x = 30;
  int y = 6;
  int z = x / y;
  TEST_ASSERT_TRUE_MESSAGE(
      z == 5, "Multiplication of two integers returned incorrect value.");
}

void test_check_and_toggle(void) {
  printf("testing toggle\n");

  bool on = false;
  unsigned int count = 0;
  printf("first loop\n");
  for (int i = 0; i < 10; i++) {
    printf("i = %d\n", i);
    check_and_toggle(&on, &count);
    TEST_ASSERT_FALSE_MESSAGE(on,
                              "`on` must stay off for the first 10 iterations");
  }

  printf("checking 11th\n");
  check_and_toggle(&on, &count);
  TEST_ASSERT_TRUE_MESSAGE(on, "`on` must turn on after 11 iterations");

  printf("second loop\n");
  for (int i = 0; i < 10; i++) {
    printf("i = %d\n", i);
    check_and_toggle(&on, &count);
    TEST_ASSERT_TRUE_MESSAGE(
        on, "`on` must stay on for the first 10 iterations after turning on");
  }

  printf("checking 2nd 11th\n");
  check_and_toggle(&on, &count);
  TEST_ASSERT_TRUE_MESSAGE(on,
                           "`on` must turn off after another 11 iterations");
}

int main(void) {
  stdio_init_all();
  while (1) {
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_variable_assignment);
    RUN_TEST(test_multiplication);
    RUN_TEST(test_check_and_toggle);
    sleep_ms(5000);
    UNITY_END();
  }
}
