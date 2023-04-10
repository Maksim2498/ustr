#ifndef USTR_TYPE_STR_H
#define USTR_TYPE_STR_H

#include <stddef.h>

#include "char.h"

// Struct

typedef struct {
    uc32_t *chars;
    size_t  len;
    size_t  cap;
} us32_t;

typedef struct {
    uc16_t *chars;
    size_t  len;
    size_t  cap;
} us16_t;

typedef struct {
    uc8_t *chars;
    size_t len;
    size_t  cap;
} us8_t;

// Null

#define USX_NULL_CTC(X) ((us##X##_t) { \
    .chars = NULL,                     \
    .len   = 0,                        \
    .cap   = 0                         \
})

#define US32_NULL_CTC USX_NULL_CTC(32)
UEXPORT static const us32_t US32_NULL = US32_NULL_CTC;

#define US16_NULL_CTC USX_NULL_CTC(16)
UEXPORT static const us16_t US16_NULL = US16_NULL_CTC;

#define US8_NULL_CTC USX_NULL_CTC(8)
UEXPORT static const us8_t US8_NULL = US8_NULL_CTC;

#endif