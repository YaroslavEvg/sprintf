#include "sprintf.h"

int main(void) {
  char test[] = "%-+20ld";
  long long int a = 123456789012345, b = 44, c = 8;
  char string[1024] = {};
  sprintf(string, test, a, b, c);
  char string2[1024] = {};
  s21_sprintf(string2, test, a, b, c);
  LOG_INFO("sprintf orig str %s, len %ld", string, strlen(string));
  LOG_INFO("sprintf MYYY str %s, len %ld", string2, strlen(string2));
  return 0;
}

void s21_sprintf(char *str, const char *format, ...) {
  opt opt = {};
  init_struct(&opt);
  setlocale(LC_ALL, "");
  setlocale(LC_ALL, "en_US.UTF-8");
  va_list arg;
  va_start(arg, format);
  int agr_len = STR_LEN(format);
  LOG_INFO("Длинна строки %d, строка \"%s\"", agr_len, format);
  int simbol_n = 0;
  for (int i = 0; i < agr_len; i++) {
    if (format[i] == '%') {
      for (int j = 0; j != 1;) {
        i++;
        up_flags(&opt, format, &i);
        up_width(&opt, format, &i, arg);
        up_accur(&opt, format, &i, arg);
        up_modif(&opt, format, &i);
        specifier(str, &opt, format, &i, &simbol_n, arg);
        init_struct(&opt);
        j = 1;
      }
    }
  }
  va_end(arg);
}

void spec_d(char *str, int *simbol_n, opt *opt, va_list arg) {
  if (!opt->error) {
    if (opt->modifiers.h) {
      long long int arg_d = (long long int)(short int)va_arg(arg, int);
      write_d(arg_d, opt, str, simbol_n);
    } else if (opt->modifiers.l) {
      long long int arg_d = (long long int)(long int)va_arg(arg, long int);
      write_d(arg_d, opt, str, simbol_n);
    } else {
      long long int arg_d = (long long int)(int)va_arg(arg, int);
      write_d(arg_d, opt, str, simbol_n);
    }
    if (opt->accuracy.size != DOWN) opt->flags.zero = DOWN;
  }
}

void write_d(long long int arg_d, opt *opt, char *str, int *simbol_n) {
  if (!opt->error) {
    LOG_INFO("write spec d int %lld", arg_d);
    flags(opt, str, arg_d, simbol_n);
  }
}
void flags(opt *opt, char *str, long long int arg_d, int *simbol_n) {
  if (!opt->error) {
    if (opt->width.size < 0) opt->flags.minus = UP;
    func_width(opt, str, arg_d, simbol_n);
    // if (opt->flags.minus) flag_minus(opt, str, arg_d, simbol_n);
    // else if (opt->flags.space)
    //   flag_space();
    // else if (opt->flags.grid)
    //   flag_grid();
    // else if (opt->flags.zero)
    //   flag_zero();
  }
}
void func_width(opt *opt, char *str, long long int arg_d, int *simbol_n) {
  if (!opt->error) {
    int int_size = num_digs(arg_d, 10);
    char *tmp = (char *)calloc(LEN_LONG_LONG_INT, sizeof(char));
    if (tmp != NULL) {
      s21_itoa(opt, tmp, arg_d);
      if (opt->width.size > int_size) {
        if (opt->flags.minus) {
          flag_minus(opt, arg_d, str, simbol_n);
          str[(*simbol_n)] = 0;
          strcat(str, tmp);
          *simbol_n = STR_LEN(str);
          flag_width_more(opt, str, simbol_n, int_size);
          LOG_INFO("Один %s", str);
        } else {
          flag_width_more(opt, str, simbol_n, int_size);
          flag_minus(opt, arg_d, str, simbol_n);
          LOG_INFO("Два%s", str);
          str[++(*simbol_n)] = 0;
          strcat(str, tmp);
          *simbol_n = STR_LEN(str);
          LOG_INFO("Два%s", str);
        }
      } else {
        if (opt->flags.minus) {
          flag_minus(opt, arg_d, str, simbol_n);
          str[(*simbol_n)] = 0;
          strcat(str, tmp);
          *simbol_n = STR_LEN(str);
          LOG_INFO("Три %s", str);
        } else {
          flag_minus(opt, arg_d, str, simbol_n);
          str[(*simbol_n)] = 0;
          strcat(str, tmp);
          *simbol_n = STR_LEN(str);
          LOG_INFO("Четыре %s", str);
        }
      }
      free(tmp);
    }
  }
}
void flag_width_more(opt *opt, char *str, int *simbol_n, int int_size) {
  for (int i = 0; i < opt->width.size - int_size; i++) {
    str[(*simbol_n)++] = '=';
  }
}
void flag_minus(opt *opt, long long int arg_d, char *str, int *simbol_n) {
  if (arg_d < 0 || opt->flags.plus) {
    if (opt->flags.plus)
      str[(*simbol_n)++] = '+';
    else if (arg_d < 0)
      str[(*simbol_n)++] = '-';
    opt->width.size--;
  }
}
// void flag_minus(opt *opt, char *str, long long int arg_d, int *simbol_n) {
//   if (!opt->error) {
//     int int_size = num_digs(arg_d, 10);
//     char *tmp = (char *)calloc(LEN_LONG_LONG_INT, sizeof(char));
//     if (tmp != NULL) {
//       s21_itoa(opt, tmp, arg_d);
//       if (opt->width.size > int_size) {
//         for (int i = *simbol_n + opt->width.size - int_size; *simbol_n < i;
//              (*simbol_n)++) {
//           str[*simbol_n] = ' ';
//           (*simbol_n)++;
//           // доделать, не правильно выводит
//   1
//}
//         str[*simbol_n] = 0;
//         printf("%s|%s\n", tmp, str);
//         (*simbol_n)++;
//       }
//       strcat(str, tmp);
//     } else {
//       opt->error = UP;
//     }
//     free(tmp);
//   }
// }
int num_digs(long long int n, int radix) {
  if (n < 0) n *= -1;
  int c = 0;
  do {
    c++;
    n /= radix;
  } while (n > 0);
  return c;
}
void s21_itoa(opt *opt, char *memory_str, long long int arg) {
  if (!opt->error) {
    int i = num_digs(arg, 10);
    if (arg < 0) arg *= -1;
    memory_str[i--] = '\0';
    for (; i > -1; i--) {
      memory_str[i] = (arg % 10) + 48;
      arg = arg / 10;
    }
    LOG_INFO("s21_itoa %s", memory_str);
  }
}
void specifier(char *str, opt *opt, const char *format, int *i, int *simbol_n,
               va_list arg) {
  if (!opt->error) {
    if (format[*i] == 'c') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
    } else if (format[*i] == 'd') {
      LOG_INFO("Спецификатор %%%c", format[*i]);
      spec_d(str, simbol_n, opt, arg);
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
      (*i)++;
    } else if (format[(*i)] == 'l') {
      opt->modifiers.l = UP;
      (*i)++;
    } else if (format[(*i)] == 'L') {
      opt->modifiers.L = UP;
      (*i)++;
    }
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
      str_to_int(&(opt->error), format, i, &(opt->accuracy.size), arg);
    }
    LOG_INFO("Up_accu: int %d", opt->accuracy.size);
  }
}

void up_width(opt *opt, const char *format, int *i, va_list arg) {
  str_to_int(&(opt->error), format, i, &(opt->width.size), arg);
#ifdef DEBUG
  if (!opt->error) LOG_INFO("Up_width: int %d", opt->width.size);
#endif
}

void str_to_int(int *error, const char *format, int *i, int *digit,
                va_list arg) {
  if (format[*i] == '*') {
    *digit = va_arg(arg, int);
    (*i)++;
    if (*digit > 1023) *error = UP;  //
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
      } else {
        *error = UP;
      }
    }
  }
  if (*error == UP)
    fprintf(stderr, "Use a width and accuracy less than 1024\n");
}

void up_flags(opt *opt, const char *format, int *i) {
  int x = 1;
  while (x) {
    if (format[*i] == '-') {
      (*i)++;
      opt->flags.flags = opt->flags.minus = UP;
      continue;
    } else if (format[*i] == '+') {
      (*i)++;
      opt->flags.flags = opt->flags.plus = UP;
      continue;
    } else if (format[*i] == ' ') {
      (*i)++;
      opt->flags.flags = opt->flags.space = UP;
      continue;
    } else if (format[*i] == '#') {
      (*i)++;
      opt->flags.flags = opt->flags.grid = UP;
      continue;
    } else if (format[*i] == '0') {
      (*i)++;
      opt->flags.flags = opt->flags.zero = UP;
    }
    x = 0;
  }
  flags_info(opt);
}
void flags_info(opt *opt) {
  LOG_INFO("Up_flags: %d", opt->flags.flags);
  LOG_INFO("Up_flags -: %d", opt->flags.minus);
  LOG_INFO("Up_flags +: %d", opt->flags.plus);
  LOG_INFO("Up_flags ' ': %d", opt->flags.space);
  LOG_INFO("Up_flags #: %d", opt->flags.grid);
  LOG_INFO("Up_flags 0: %d", opt->flags.zero);
}
void init_struct(opt *opt) {
  opt->accuracy.size = DOWN;
  opt->conversion = DOWN;
  opt->flags.grid = DOWN;
  opt->flags.minus = DOWN;
  opt->flags.plus = DOWN;
  opt->flags.space = DOWN;
  opt->flags.zero = DOWN;
  opt->flags.flags = DOWN;
  opt->modifiers.h = DOWN;
  opt->modifiers.l = DOWN;
  opt->modifiers.L = DOWN;
  opt->width.size = DOWN;
  opt->conversion = DOWN;
  opt->error = DOWN;
}