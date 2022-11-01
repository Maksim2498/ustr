#ifndef USTR_CVIEW_T_H
#define USTR_CVIEW_T_H

#include <stddef.h>

#include "char_t.h"

typedef struct {
    const uc32_t *chars;
    size_t len;
} ucv32_t;

#endif