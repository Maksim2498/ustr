#ifndef USTR_TYPE_CVIEW_H
#define USTR_TYPE_CVIEW_H

#include <stddef.h>

#include "char.h"

typedef struct {
    const uc32_t *chars;
    size_t len;
} ucv32_t;

#endif