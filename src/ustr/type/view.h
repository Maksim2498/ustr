#ifndef USTR_TYPE_VIEW_H
#define USTR_TYPE_VIEW_H

#include <stddef.h>

#include <ustr/util/export.h>

#include "char.h"

// Struct

typedef struct {
    uc32_t *chars;
    size_t  len;
} uv32_t;

typedef struct {
    uc16_t *chars;
    size_t  len;
} uv16_t;

typedef struct {
    uc8_t *chars;
    size_t len;
} uv8_t;

// Null

#define UVX_NULL_CTC(X) ((uv##X##_t) { \
    .chars = NULL,                     \
    .len   = 0                         \
})

#define UV32_NULL_CTC UVX_NULL_CTC(32)
UEXPORT static const uv32_t UV32_NULL = UV32_NULL_CTC; 

#define UV16_NULL_CTC UVX_NULL_CTC(16)
UEXPORT static const uv16_t UV16_NULL = UV16_NULL_CTC; 

#define UV8_NULL_CTC UVX_NULL_CTC(8)
UEXPORT static const uv8_t UV8_NULL = UV8_NULL_CTC; 

// Empty

#define UVX_EMTPY_CTC(X) ((uv##X##_t) { \
    .chars = uz##X(""),                 \
    .len   = 0                          \
})

#define UV32_EMTPY_CTC UVX_EMTPY_CTC(32)
UEXPORT static const uv32_t UV32_EMTPY = UV32_EMTPY_CTC;

#define UV16_EMTPY_CTC UVX_EMTPY_CTC(16)
UEXPORT static const uv16_t UV16_EMTPY = UV16_EMTPY_CTC;

#define UV8_EMTPY_CTC UVX_EMTPY_CTC(8)
UEXPORT static const uv8_t UV8_EMTPY = UV8_EMTPY_CTC;


#endif