#ifndef USTR_VIEW_T_H
#define USTR_VIEW_T_H

#include <stddef.h>

#include "char_t.h"

typedef struct {
    uc32_t *chars;
    size_t len;
} uv32_t;

#endif