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

// Creation

// - Char

#define uc32(literal) (const uc32_t *)  U##literal
#define uc16(literal) (const uc16_t *)  u##literal
#define uc8(literal)  (const uc8_t  *) u8##literal

// - String

#define uz32(literal) (uc32_t *)  U##literal
#define uz16(literal) (uc16_t *)  u##literal
#define  uz8(literal) (uc8_t  *) u8##literal

#endif