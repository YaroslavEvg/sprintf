#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int num_digs(long long int n, int radix) {
  if (n < 0) n *= -1;
  int c = 0;
  do {
    c++;
    n /= radix;
  } while (n > 0);
  return c;
}
void s21_itoa(char *memory_str, long long int arg) {
  int i = num_digs(arg, 10) - 1;
  for (; arg > 9; i--) {
    memory_str[i] = (arg % 10) + 48;
    arg = arg / 10;
  }
}

int main(void) {
  char *tmp = (char *)calloc(21, sizeof(char));
  s21_itoa(tmp, 123456789012345);
  printf("%s\n", tmp);
  free(tmp);
  return 0;
}