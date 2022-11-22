#include "sprintf.h"

void s21_sprintf(char *str, const char *format, ...);
void init_struct(opt *opt);
void up_flags(opt *opt, const char *format, int *i);
void up_width(opt *opt, const char *format, int *i);
void up_accur(opt *opt, const char *format, int *i);
void str_to_int(int *error, int *opt, const char *format, int *i, int *digit);
void up_modif(opt *opt, const char *format, int *i);
void log_modif(opt *opt);

int main(void) {
  char string[1024] = {};
  // sprintf(string, "%d", 1);
  // LOG_INFO("sprintf orig str %s, len %ld", string, strlen(string));
  s21_sprintf(string, "%-65534.12l");
  // fclose(stdin);
  // fclose(stdout);
  // fclose(stderr);
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
        up_width(&opt, format, &i);
        up_accur(&opt, format, &i);
        up_modif(&opt, format, &i);
        j = 1;
      }
    }
  }
  va_end(arg);
}

void up_modif(opt *opt, const char *format, int *i) {
  if (!opt->error) {
    if (format[(*i)] == 'h') {
      if (format[(*i) + 1] == 'h') {
        opt->modifiers.hh = UP;
        (*i)++;
      } else
        opt->modifiers.h = UP;
    } else if (format[(*i)] == 'l') {
      if (format[(*i) + 1] == 'l') {
        opt->modifiers.ll = UP;
        (*i)++;
      } else
        opt->modifiers.l = UP;
    } else if (format[(*i)] == 'L')
      opt->modifiers.L = UP;
    log_modif(opt);
    (*i)++;
  }
}

void log_modif(opt *opt) {
  if (!opt->error) {
    LOG_INFO("Up_modif \"h\": %d", opt->modifiers.h);
    LOG_INFO("Up_modif \"hh\": %d", opt->modifiers.hh);
    LOG_INFO("Up_modif \"l\": %d", opt->modifiers.l);
    LOG_INFO("Up_modif \"ll\": %d", opt->modifiers.ll);
    LOG_INFO("Up_modif \"L\": %d", opt->modifiers.L);
  }
}

void up_accur(opt *opt, const char *format, int *i) {
  if (!opt->error) {
    if (format[*i] == '.') {
      (*i)++;
      str_to_int(&(opt->error), &(opt->accuracy.opt), format, i,
                 &(opt->accuracy.size));
    }
    LOG_INFO("Up_accu: %d, int %d", opt->accuracy.opt, opt->accuracy.size);
  }
}

void up_width(opt *opt, const char *format, int *i) {
  if (opt->flags.flags) (*i)++;
  str_to_int(&(opt->error), &(opt->width.opt), format, i, &(opt->width.size));
  LOG_INFO("Up_width: %d, int %d", opt->width.opt, opt->width.size);
}

void str_to_int(int *error, int *opt, const char *format, int *i, int *digit) {
  if (format[*i] == '*') {
    *opt = STAR;
    (*i)++;
  } else {
    if ('0' <= format[*i] && format[*i] <= '9') {
      char ch[5] = {0};
      for (int k = 0; '0' <= format[(*i)] && format[(*i)] <= '9'; (*i)++, k++) {
        ch[k] = format[(*i)];
        ch[k + 1] = 0;
      }
      if (atoi(ch) < 65535) {
        *digit = atoi(ch);
        *opt = UP;
      } else {
        *error = UP;
        fprintf(stderr, "Use a width less than 65535\n");
      }
    }
  }
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
  opt->modifiers.hh = DOWN;
  opt->modifiers.l = DOWN;
  opt->modifiers.ll = DOWN;
  opt->modifiers.L = DOWN;
  opt->width.opt = DOWN;
  opt->width.size = DOWN;
  opt->conversion = DOWN;
  opt->error = DOWN;
}