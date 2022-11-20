#include "sprintf.h"

int s21_sprintf(char *str, const char *format, ...);

int main(void) {
  char *string[1024] = {};
  s21_sprintf(string, "%d", "A");
  printf("%s\n", string);
  return 0;
}

int s21_sprintf(char *str, const char *format, ...) {
  setlocale(LC_ALL, "");
  setlocale(LC_ALL, "en_US.UTF-8");


}