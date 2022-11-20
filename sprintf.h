#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>  //удалить
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#define DEBUG

#ifdef DEBUG
#define LOG_INFO(M, ...) \
  fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define STR_LEN strlen
#else
#define LOG_INFO(M, ...)
#define STR_LEN s21_strlen
#endif

//[flags][width][.precision][size]conversion
typedef struct sprintf {
  struct {
    int minus;
    int plus;
    int space;
    int grid;
    int zero;
  } flags;
  int width;
  int accuracy;
  struct {
    int h;
    int hh;
    int l;
    int ll;
    int L;
  } modifiers;
  char conversion;
} opt;
