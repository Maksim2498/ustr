#ifndef USTR_STR_T_H
#define USTR_STR_T_H

#include <stddef.h>

#include "char_t.h"

typedef struct {
    uc32_t *chars;
    size_t len;
    size_t cap;
} us32_t;

typedef struct {
    uc16_t *chars;
    size_t len;
    size_t cap;
} us16_t;

typedef struct {
    uc8_t *chars;
    size_t len;
    size_t cap;
} us8_t;

#endif