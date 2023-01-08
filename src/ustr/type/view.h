#ifndef USTR_TYPE_VIEW_H
#define USTR_TYPE_VIEW_H

#include <stddef.h>

#include "char.h"

typedef struct {
    uc32_t *chars;
    size_t  len;
} uv32_t;

#endif