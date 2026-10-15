#include "unity_config.h"
#include <pico/cyw43_arch.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>

#include <stdio.h>

#include "blinky.h"
#include <stdbool.h>

void setUp(void) {}

void tearDown(void) {}

void test_check_and_toggle(void) {
  bool on = false;
  unsigned int count = 0;
  for (int i = 0; i < 100; i++) {
    bool next_toggles = (i % 11);
    bool current_on = on;
    check_and_toggle(&on, &count);
    bool toggled = current_on != on;
    TEST_ASSERT_EQUAL_MESSAGE(next_toggles, toggled,
                              "Unexpected unequal; should toggle every time "
                              "except for when i is not div by 11");
  }
}

void test_char_conversion(void) {
  for (char c = 0; c <= 'A'; c++) {
    char res = char_conversion(c);
    if (c <= 'z' && c >= 'a')
      TEST_ASSERT_EQUAL_MESSAGE(c - 32, res,
                                "If 'a' <= c <= 'z', res should be c - 32");
    else if (c >= 'A' && c <= 'Z')
      TEST_ASSERT_EQUAL_MESSAGE(c + 32, res,
                                "If 'A' <= c <= 'Z', res should be c + 32");
    else
      TEST_ASSERT_EQUAL_MESSAGE(
          c, res, "If c is outside of alphabetic range, res should be c");
  }
}

int main(void) {
  stdio_init_all();
  while (1) {
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_check_and_toggle);
    RUN_TEST(test_char_conversion);
    sleep_ms(5000);
    UNITY_END();
  }
}
