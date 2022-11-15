#ifndef USTR_STR_T_H
#define USTR_STR_T_H

#include <stddef.h>

#include "char_t.h"

typedef struct {
    uc32_t *chars;
    size_t len;
    size_t cap;
} us32_t;

#endif