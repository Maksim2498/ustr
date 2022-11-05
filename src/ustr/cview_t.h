#ifndef USTR_CVIEW_T_H
#define USTR_CVIEW_T_H

#include <stddef.h>

#include "char_t.h"

typedef struct {
    const uc32_t *chars;
    size_t len;
} ucv32_t;

typedef struct {
    const uc16_t *chars;
    size_t len;
} ucv16_t;

typedef struct {
    const uc8_t *chars;
    size_t len;
} ucv8_t;

#endif