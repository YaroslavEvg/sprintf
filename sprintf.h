#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>  //удалить
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
// #define DEBUG

#ifdef DEBUG
#define S21_NULL (void*)0
typedef long unsigned s21_size_t;
#define LOG_INFO(M, ...) \
  fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define STR_LEN strlen
#else
#define S21_NULL (void*)0
typedef long unsigned s21_size_t;
#define LOG_INFO(M, ...)
// #define STR_LEN s21_strlen
#define STR_LEN strlen
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
    int opt;
    unsigned int size;
  } width;
  struct {
    int opt;
    unsigned int size;
  } accuracy;
  struct {
    int h;
    int hh;
    int l;
    int ll;
    int L;
  } modifiers;
  char conversion;
} opt;
