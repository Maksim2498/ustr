#ifndef USTR_TYPE_STR_H
#define USTR_TYPE_STR_H

#include <stddef.h>

#include "char.h"

typedef struct {
    uc32_t *chars;
    size_t len;
    size_t cap;
} us32_t;

#endif