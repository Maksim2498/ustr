#ifndef USTR_TYPE_CHAR_H
#define USTR_TYPE_CHAR_H

#include <stdint.h>
#include <limits.h>

#include <ustr/config.h>

enum {
    // BOM

    UBOM_LITTLE_ENDIAN = 0xFFFE,
    UBOM_BIG_ENDIAN    = 0xFEFF,
    UBOM_UTF_8         = 0xEFBBBF,

    // Max code point

    UMAX_CP            = 0x10FFFF,

    // Limits

    UC32_MAX           = UINT_LEAST32_MAX,
    UC16_MAX           = UINT_LEAST16_MAX,
    UC8_MAX            = UCHAR_MAX,
};

// Char types

typedef uint_least32_t uc32_t;
typedef uint_least16_t uc16_t;
typedef unsigned char  uc8_t;

// Char arg types

typedef uarg_uint_least32_t uarg_uc32_t;
typedef uarg_uint_least16_t uarg_uc16_t;
typedef unsigned            uarg_uc8_t;

// uc8_t case len func type

typedef unsigned (*uc8_case_len_func_t)(const uc8_t *);

// char to case func types

typedef uc32_t   (*uc32_to_case_func_t)(uc32_t                  );
typedef unsigned (*uc16_to_case_func_t)(uc16_t *, const uc16_t *);
typedef unsigned (* uc8_to_case_func_t)(uc8_t  *, const uc8_t  *);

#endif