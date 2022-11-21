#include "sprintf.h"

void s21_sprintf(char *str, const char *format, ...);
void init_struct(opt *opt);
void up_flags(opt *opt, const char *format, int *i);
void up_width(opt *opt, const char *format, int *i);
void up_accur(opt *opt, const char *format, int *i);

int main(void) {
  char string[1024] = {};
  sprintf(string, "%d", 1);
  LOG_INFO("sprintf orig str %s, len %ld", string, strlen(string));
  s21_sprintf(string, "%-65534.12");
  fclose(stdin);
  fclose(stdout);
  fclose(stderr);
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
        LOG_INFO("Up_flags: simbol %c, flag %d", format[i], opt.flags.minus);
        up_width(&opt, format, &i);
        LOG_INFO("Up_width: Width string %s, int %d", ch, opt->width.size);
        up_accu(&opt, format, &i);
        LOG_INFO("Up_accu: Width string %s, int %d", ch, opt->width.size);
        j = 1;
      }
    }
  }
  va_end(arg);
}

void up_accur(opt *opt, const char *format, int *i) {}

void up_width(opt *opt, const char *format, int *i) {
  if (opt->flags.flags) (*i)++;
  if ('0' <= format[*i] && format[*i] <= '9') {
    char *ch = NULL;
    int k = 0;
    for (int j = *i; '0' <= format[j] && format[j] <= '9'; j++, k++) {
      if (!opt->error || k < 5) {
        char *tmp = (char *)realloc(ch, sizeof(char) * (k + 1));
        if (tmp != NULL) {
          ch = tmp;
          ch[k] = format[j];
          ch[k + 1] = 0;
        } else {
          opt->error = 1;
          fprintf(stderr, "Error realloc\n");
        }
      }
    }
    if (!opt->error) {
      if (atoi(ch) < 65535) {
        opt->width.size = 0;
        opt->width.size = atoi(ch);
        opt->width.opt = 1;
      } else {
        opt->error = 1;
        fprintf(stderr, "Use a width less than 65535\n");
      }
      free(ch);
    }
  }
}

void up_flags(opt *opt, const char *format, int *i) {
  if (format[*i] == '-') opt->flags.flags = opt->flags.minus = 1;
  if (format[*i] == '+') opt->flags.flags = opt->flags.plus = 1;
  if (format[*i] == ' ') opt->flags.flags = opt->flags.space = 1;
  if (format[*i] == '#') opt->flags.flags = opt->flags.grid = 1;
  if (format[*i] == '0') opt->flags.flags = opt->flags.zero = 1;
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
  opt->width.opt = 0;
  opt->width.size = 0;
  opt->conversion = 0;
  opt->error = 0;
}