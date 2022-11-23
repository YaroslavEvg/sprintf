#include "sprintf.h"

void s21_sprintf(char *str, const char *format, ...);
void init_struct(opt *opt);
void up_flags(opt *opt, const char *format, int *i);
void up_width(opt *opt, const char *format, int *i, va_list arg);
void up_accur(opt *opt, const char *format, int *i, va_list arg);
void str_to_int(int *error, int *op, const char *format, int *i, int *digit,
                va_list arg);
void up_modif(opt *opt, const char *format, int *i);
void log_modif(opt *opt);
void specifier(opt *opt, const char *format, int *i);

int main(void) {
  char test[] = "%-2.1ld %+*.*hc %09.8hi %le %hE";
  int a = 66, b = 44, c = 8;
  char string[1024] = {};
  sprintf(string, test, a, b, c);
  char string2[1024] = {};
  s21_sprintf(string2, test, a, b, c);
  LOG_INFO("sprintf orig str %s, len %ld", string, strlen(string));
  LOG_INFO("sprintf MYYY str %s, len %ld", string2, strlen(string2));
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
      for (int j = 0; j != 1;) {
        i++;
        up_flags(&opt, format, &i);
        up_width(&opt, format, &i, arg);
        up_accur(&opt, format, &i, arg);
        up_modif(&opt, format, &i);
        specifier(&opt, format, &i);
        j = 1;
      }
    }
  }
  va_end(arg);
}

void specifier(opt *opt, const char *format, int *i) {
  (void)opt;
  (void)i;
  if (!opt->error) {
    if (format[*i] == 'c') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'd') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'i') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'e') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'E') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'f') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'g') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'G') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'o') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 's') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'u') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'x') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'X') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'p') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'n') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == '%') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    }
  }
}

void up_modif(opt *opt, const char *format, int *i) {
  if (!opt->error) {
    if (format[(*i)] == 'h') {
      opt->modifiers.h = UP;
    } else if (format[(*i)] == 'l') {
      opt->modifiers.l = UP;
    } else if (format[(*i)] == 'L')
      opt->modifiers.L = UP;
    log_modif(opt);
  }
}

void log_modif(opt *opt) {
  if (!opt->error) {
    LOG_INFO("Up_modif \"h\": %d", opt->modifiers.h);
    LOG_INFO("Up_modif \"l\": %d", opt->modifiers.l);
    LOG_INFO("Up_modif \"L\": %d", opt->modifiers.L);
  }
}

void up_accur(opt *opt, const char *format, int *i, va_list arg) {
  if (!opt->error) {
    if (format[*i] == '.') {
      (*i)++;
      str_to_int(&(opt->error), &(opt->accuracy.opt), format, i,
                 &(opt->accuracy.size), arg);
    }
    LOG_INFO("Up_accu: %d, int %d", opt->accuracy.opt, opt->accuracy.size);
  }
}

void up_width(opt *opt, const char *format, int *i, va_list arg) {
  if (opt->flags.flags) (*i)++;
  str_to_int(&(opt->error), &(opt->width.opt), format, i, &(opt->width.size),
             arg);
#ifdef DEBUG
  if (!opt->error)
    LOG_INFO("Up_width: %d, int %d", opt->width.opt, opt->width.size);
#endif
}

void str_to_int(int *error, int *op, const char *format, int *i, int *digit,
                va_list arg) {
  if (format[*i] == '*') {
    *op = STAR;
    *digit = va_arg(arg, int);
    (*i)++;
    if (*digit > 1023) *error = UP;
  } else {
    if ('0' <= format[*i] && format[*i] <= '9') {
      char ch[4] = {0};
      for (int k = 0; '0' <= format[(*i)] && format[(*i)] <= '9'; (*i)++, k++) {
        if (k < 4) {
          ch[k] = format[(*i)];
          ch[k + 1] = 0;
        } else if (k > 3 && *error != UP) {
          *error = UP;
        }
      }
      if (atoi(ch) < 1024) {
        *digit = atoi(ch);
        *op = UP;
      } else {
        *error = UP;
      }
    }
  }
  if (*error == UP)
    fprintf(stderr, "Use a width and accuracy less than 1024\n");
}

void up_flags(opt *opt, const char *format, int *i) {
  if (format[*i] == '-') opt->flags.flags = opt->flags.minus = UP;
  if (format[*i] == '+') opt->flags.flags = opt->flags.plus = UP;
  if (format[*i] == ' ') opt->flags.flags = opt->flags.space = UP;
  if (format[*i] == '#') opt->flags.flags = opt->flags.grid = UP;
  if (format[*i] == '0') opt->flags.flags = opt->flags.zero = UP;
  LOG_INFO("Up_flags: %d", opt->flags.flags);
}

void init_struct(opt *opt) {
  opt->accuracy.opt = DOWN;
  opt->accuracy.size = DOWN;
  opt->conversion = DOWN;
  opt->flags.grid = DOWN;
  opt->flags.minus = DOWN;
  opt->flags.plus = DOWN;
  opt->flags.space = DOWN;
  opt->flags.zero = DOWN;
  opt->modifiers.h = DOWN;
  opt->modifiers.l = DOWN;
  opt->modifiers.L = DOWN;
  opt->width.opt = DOWN;
  opt->width.size = DOWN;
  opt->conversion = DOWN;
  opt->error = DOWN;
}