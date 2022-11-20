#include "sprintf.h"

int s21_sprintf(char *str, const char *format, ...);

int main(void) {
  char test_int = 0;
  sprintf(test_int, "%d", "1");
  printf("%d\n", &test_int);
  // s21_sprintf(test_int, "%c", "1");
  // printf("%s\n", &test_int);
  return 0;
}