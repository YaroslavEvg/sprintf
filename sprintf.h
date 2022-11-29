#include <check.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>  //удалить
#include <stdlib.h>
#include <wchar.h>
#define DEBUG

#ifdef DEBUG
#include <string.h>
#define STR_LEN strlen
#define LEN_LONG_LONG_INT 21
#define S21_NULL (void *)0
typedef long unsigned s21_size_t;
#define LOG_INFO(M, ...) \
  fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define S21_NULL (void *)0
typedef long unsigned s21_size_t;
#define LOG_INFO(M, ...)
#define STR_LEN s21_strlen
#endif

//[flags][width][.precision][size]conversion
typedef struct sprintf {
  int error;
  struct {
    int minus;
    int plus;
    int space;
    int grid;
    int zero;
    int flags;
  } flags;
  struct {
    int size;
  } width;
  struct {
    int size;
  } accuracy;
  struct {
    int h;
    int l;
    int L;
  } modifiers;
  char conversion;
} opt;

enum Token { DOWN, UP };

void flags_info(opt *opt);
int num_digs(long long int n, int radix);
void s21_sprintf(char *str, const char *format, ...);
void init_struct(opt *opt);
void up_flags(opt *opt, const char *format, int *i);
void up_width(opt *opt, const char *format, int *i, va_list arg);
void up_accur(opt *opt, const char *format, int *i, va_list arg);
void str_to_int(int *error, const char *format, int *i, int *digit,
                va_list arg);
void up_modif(opt *opt, const char *format, int *i);
void log_modif(opt *opt);
void specifier(char *str, opt *opt, const char *format, int *i, int *simbol_n,
               va_list arg);
void spec_d(char *str, int *simbol_n, opt *opt, va_list arg);
void write_d(long long int arg_d, opt *opt, char *str, int *simbol_n);
void flags(opt *opt, char *str, long long int arg_d, int *simbol_n);
// void flag_minus(opt *opt, char *str, long long int arg_d, int *simbol_n);
void s21_itoa(opt *opt, char *memory_str, long long int arg);
void func_width(opt *opt, char *str, long long int arg_d, int *simbol_n);
void flag_width_more(opt *opt, char *str, int *simbol_n, int int_size);
void flag_minus(opt *opt, long long int arg_d, char *str, int *simbol_n);
