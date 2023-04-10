#ifndef USTR_TYPE_CVIEW_H
#define USTR_TYPE_CVIEW_H

#include <stddef.h>

#include <ustr/util/export.h>

#include "char.h"

// Typedefs

typedef struct {
    const uc32_t *chars;
    size_t        len;
} ucv32_t;

typedef struct {
    const uc16_t *chars;
    size_t        len;
} ucv16_t;

typedef struct {
    const uc8_t *chars;
    size_t       len;
} ucv8_t;

// Creation

#define ucv32(literal)                                   \
    (ucv32_t) {                                          \
        .chars = (const uc32_t *) (U##literal),          \
        .len   = sizeof(U##literal) / sizeof(uc32_t) - 1 \
    }

#define ucv16(literal)                                   \
    (ucv16_t) {                                          \
        .chars = (const uc16_t *) (u##literal),          \
        .len   = sizeof(u##literal) / sizeof(uc16_t) - 1 \
    }

#define ucv8(literal)                                    \
    (ucv8_t) {                                           \
        .chars = (const uc8_t *) (u8##literal),          \
        .len   = sizeof(u8##literal) / sizeof(uc8_t) - 1 \
    }

// Null

#define UCVX_NULL_CTC(X) ((ucv##X##_t) { \
    .chars = NULL,                       \
    .len   = 0                           \
})

#define UCV32_NULL_CTC UCVX_NULL_CTC(32)
UEXPORT static const ucv32_t UCV32_NULL = UCV32_NULL_CTC; 

#define UCV16_NULL_CTC UCVX_NULL_CTC(16)
UEXPORT static const ucv16_t UCV16_NULL = UCV16_NULL_CTC; 

#define UCV8_NULL_CTC UCVX_NULL_CTC(8)
UEXPORT static const ucv8_t UCV8_NULL = UCV8_NULL_CTC; 

// Empty

#define UCVX_EMPTY_CTC(X) ucv##X("")

#define UCV32_EMPTY_CTC UCVX_EMPTY_CTC(32)
UEXPORT static const ucv32_t UCV32_EMPTY = UCV32_EMPTY_CTC;

#define UCV16_EMPTY_CTC UCVX_EMPTY_CTC(16)
UEXPORT static const ucv16_t UCV16_EMPTY = UCV16_EMPTY_CTC;

#define UCV8_EMPTY_CTC UCVX_EMPTY_CTC(8)
UEXPORT static const ucv8_t UCV8_EMPTY = UCV8_EMPTY_CTC;

#endif