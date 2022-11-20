#include "sprintf.h"

void s21_sprintf(char *str, const char *format, ...);
void init_struct(opt *opt);

int main(void) {
  char string[1024] = {};
  sprintf(string, "%d", 1);
  LOG_INFO("sprintf orig str %s, len %ld", string, strlen(string));
  s21_sprintf(string, "%sdada");
  return 0;
}

void s21_sprintf(char *str, const char *format, ...) {
  (void)str;
  opt opt = {};
  setlocale(LC_ALL, "");
  setlocale(LC_ALL, "en_US.UTF-8");
  va_list arg;
  va_start(arg, format);
  int agr_len = STR_LEN(format);
  LOG_INFO("Длинна строки %d, строка \"%s\"", agr_len, format);
  for (int i = 0; i < agr_len; i++) {
    if (format[i] == '%') {
      init_struct(&opt);
      for (int j = 0; j == 1; i++) {
      }
    }
  }
  va_end(arg);
}

void init_struct(opt *opt) {
  opt->accuracy = 0;
  opt->conversion = 0;
  opt->flags.grid = 0;
  opt->flags.minus = 0;
  opt->flags.plus = 0;
  opt->flags.space = 0;
  opt->flags.zero = 0;
  opt->modifiers.h = 0;
  opt->modifiers.hh = 0;
  opt->modifiers.l = 0;
  opt->modifiers.ll = 0;
  opt->modifiers.L = 0;
  opt->width = 0;
  opt->conversion = 0;
}