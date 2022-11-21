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
        LOG_INFO("Up_width: Width string int %d", opt.width.size);
        up_accur(&opt, format, &i);
        LOG_INFO("Up_accu: Width string int %d", opt.accuracy.size);
        j = 1;
      }
    }
  }
  va_end(arg);
}

void up_accur(opt *opt, const char *format, int *i) {
  if (!opt->error) {
    LOG_INFO("Accuracy точка %c", format[*i]);
    if (format[*i] == '.') {
    }
  }
}

void up_width(opt *opt, const char *format, int *i) {
  if (opt->flags.flags) (*i)++;
  if (format[*i] == '*')
    opt->width.opt = STAR;  //  Здесь остановился
  else {
    if ('0' <= format[*i] && format[*i] <= '9') {
      char *ch = NULL;
      int k = 0;
      for (; '0' <= format[(*i)] && format[(*i)] <= '9'; (*i)++, k++) {
        if (!opt->error || k < 5) {
          char *tmp = (char *)realloc(ch, sizeof(char) * (k + 1));
          if (tmp != NULL) {
            ch = tmp;
            ch[k] = format[(*i)];
            ch[k + 1] = 0;
          } else {
            opt->error = UP;
            fprintf(stderr, "Error realloc\n");
          }
        }
      }
      if (!opt->error) {
        if (atoi(ch) < 65535) {
          opt->width.size = atoi(ch);
          opt->width.opt = UP;
        } else {
          opt->error = UP;
          fprintf(stderr, "Use a width less than 65535\n");
        }
        free(ch);
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