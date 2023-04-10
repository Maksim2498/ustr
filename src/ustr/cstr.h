#ifndef USTR_CSTR_H
#define USTR_CSTR_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "type/fmt/case.h"
#include "type/fmt/float.h"
#include "type/fmt/int.h"
#include "type/attr.h"
#include "type/char.h"
#include "type/cview.h"
#include "type/encoding.h"
#include "type/str.h"
#include "type/view.h"
#include "util/export.h"

// Creation

// - Generic

#define uz32_from_range(to, from, begin, len)  \
    _Generic((from),                           \
        const uc32_t *: uz32_from_uz32_range,  \
        uc32_t *:       uz32_from_uz32_range,  \
        ucv32_t:        uz32_from_ucv32_range, \
        uv32_t:         uz32_from_uv32_range,  \
        const us32_t *: uz32_from_us32_range,  \
        us32_t *:       uz32_from_us32_range,  \
                                               \
        const uc16_t *: uz32_from_uz16_range,  \
        uc16_t *:       uz32_from_uz16_range,  \
        ucv16_t:        uz32_from_ucv16_range, \
        uv16_t:         uz32_from_uv16_range,  \
        const us16_t *: uz32_from_us16_range,  \
        us16_t *:       uz32_from_us16_range,  \
                                               \
        const uc8_t *:  uz32_from_uz8_range,   \
        uc8_t *:        uz32_from_uz8_range,   \
        ucv8_t:         uz32_from_ucv8_range,  \
        uv8_t:          uz32_from_uv8_range,   \
        const us8_t *:  uz32_from_us8_range,   \
        us8_t *:        uz32_from_us8_range    \
    )((to), (from), (begin), (len))

#define uz32_from(to, from)                  \
    _Generic((from),                         \
                                             \
        /* Conversion */                     \
                                             \
        const uc32_t *:     uz32_from_uz32,  \
        uc32_t *:           uz32_from_uz32,  \
        ucv32_t:            uz32_from_ucv32, \
        uv32_t:             uz32_from_uv32,  \
        const us32_t *:     uz32_from_us32,  \
        us32_t *:           uz32_from_us32,  \
                                             \
        const uc16_t *:     uz32_from_uz16,  \
        uc16_t *:           uz32_from_uz16,  \
        ucv16_t:            uz32_from_ucv16, \
        uv16_t:             uz32_from_uv16,  \
        const us16_t *:     uz32_from_us16,  \
        us16_t *:           uz32_from_us16,  \
                                             \
        const uc8_t *:      uz32_from_uz8,   \
        uc8_t *:            uz32_from_uz8,   \
        ucv8_t:             uz32_from_ucv8,  \
        uv8_t:              uz32_from_uv8,   \
        const us8_t *:      uz32_from_us8,   \
        us8_t *:            uz32_from_us8,   \
                                             \
        /* From float */                     \
                                             \
        float:              uz32_from_float, \
        double:             uz32_from_float, \
        long double:        uz32_from_float, \
                                             \
        /* From int */                       \
                                             \
        char:               uz32_from_int,   \
        short:              uz32_from_int,   \
        int:                uz32_from_int,   \
        long:               uz32_from_int,   \
        long long:          uz32_from_int,   \
                                             \
        unsigned char:      uz32_from_uint,  \
        unsigned short:     uz32_from_uint,  \
        unsigned:           uz32_from_uint,  \
        unsigned long:      uz32_from_uint,  \
        unsigned long long: uz32_from_uint   \
    )((to), (from))

#define uz32_from_n(to, from, from_len)  \
    _Generic((from),                     \
        const uc32_t *: uz32_from_uz32n, \
        uc32_t *:       uz32_from_uz32n, \
        const uc16_t *: uz32_from_uz16n, \
        uc16_t *:       uz32_from_uz16n, \
        const uc8_t  *: uz32_from_uz8n,  \
        uc8_t  *:       uz32_from_uz8n   \
    )((to), (from), (from_len))

#define uz32_from_le(to, from)            \
    _Generic((from),                      \
        const uc32_t *: uz32_from_uz32le, \
        uc32_t *:       uz32_from_uz32le, \
        const uc16_t *: uz32_from_uz16le, \
        uc16_t *:       uz32_from_uz16le, \
        const uc8_t  *: uz32_from_uz8,    \
        uc8_t  *:       uz32_from_uz8     \
    )((to), (from))

#define uz32_from_len(to, from, from_len)  \
    _Generic((from),                       \
        const uc32_t *: uz32_from_uz32len, \
        uc32_t *:       uz32_from_uz32len, \
        const uc16_t *: uz32_from_uz16len, \
        uc16_t *:       uz32_from_uz16len, \
        const uc8_t  *: uz32_from_uz8n,    \
        uc8_t  *:       uz32_from_uz8n     \
    )((to), (from), (from_len))

#define uz32_from_be(to, from)            \
    _Generic((from),                      \
        const uc32_t *: uz32_from_uz32be, \
        uc32_t *:       uz32_from_uz32be, \
        const uc16_t *: uz32_from_uz16be, \
        uc16_t *:       uz32_from_uz16be, \
        const uc8_t  *: uz32_from_uz8,    \
        uc8_t  *:       uz32_from_uz8     \
    )((to), (from))

#define uz32_from_ben(to, from, from_len)  \
    _Generic((from),                       \
        const uc32_t *: uz32_from_uz32ben, \
        uc32_t *:       uz32_from_uz32ben, \
        const uc16_t *: uz32_from_uz16ben, \
        uc16_t *:       uz32_from_uz16ben, \
        const uc8_t  *: uz32_from_uz8n,    \
        uc8_t  *:       uz32_from_uz8n     \
    )((to), (from), (from_len))

#define uz32le_from(to, from)             \
    _Generic((from),                      \
        const uc32_t *: uz32le_from_uz32, \
        uc32_t *:       uz32le_from_uz32, \
        const uc16_t *: uz32le_from_uz16, \
        uc16_t *:       uz32le_from_uz16, \
        const uc8_t  *: uz32le_from_uz8,  \
        uc8_t  *:       uz32le_from_uz8   \
    )((to), (from))

#define uz32le_from_n(to, from, from_len)  \
    _Generic((from),                       \
        const uc32_t *: uz32le_from_uz32n, \
        uc32_t *:       uz32le_from_uz32n, \
        const uc16_t *: uz32le_from_uz16n, \
        uc16_t *:       uz32le_from_uz16n, \
        const uc8_t  *: uz32le_from_uz8n,  \
        uc8_t  *:       uz32le_from_uz8n   \
    )((to), (from), (from_len))

#define uz32le_from_le(to, from)            \
    _Generic((from),                        \
        const uc32_t *: uz32le_from_uz32le, \
        uc32_t *:       uz32le_from_uz32le, \
        const uc16_t *: uz32le_from_uz16le, \
        uc16_t *:       uz32le_from_uz16le, \
        const uc8_t  *: uz32le_from_uz8,    \
        uc8_t  *:       uz32le_from_uz8     \
    )((to), (from))

#define uz32le_from_len(to, from, from_len)  \
    _Generic((from),                         \
        const uc32_t *: uz32le_from_uz32len, \
        uc32_t *:       uz32le_from_uz32len, \
        const uc16_t *: uz32le_from_uz16len, \
        uc16_t *:       uz32le_from_uz16len, \
        const uc8_t  *: uz32le_from_uz8n,    \
        uc8_t  *:       uz32le_from_uz8n     \
    )((to), (from), (from_len))

#define uz32le_from_be(to, from)            \
    _Generic((from),                        \
        const uc32_t *: uz32le_from_uz32be, \
        uc32_t *:       uz32le_from_uz32be, \
        const uc16_t *: uz32le_from_uz16be, \
        uc16_t *:       uz32le_from_uz16be, \
        const uc8_t  *: uz32le_from_uz8,    \
        uc8_t  *:       uz32le_from_uz8     \
    )((to), (from))

#define uz32le_from_ben(to, from, from_len)  \
    _Generic((from),                         \
        const uc32_t *: uz32le_from_uz32ben, \
        uc32_t *:       uz32le_from_uz32ben, \
        const uc16_t *: uz32le_from_uz16ben, \
        uc16_t *:       uz32le_from_uz16ben, \
        const uc8_t  *: uz32le_from_uz8n,    \
        uc8_t  *:       uz32le_from_uz8n     \
    )((to), (from), (from_len))

#define uz32be_from(to, from)             \
    _Generic((from),                      \
        const uc32_t *: uz32be_from_uz32, \
        uc32_t *:       uz32be_from_uz32, \
        const uc16_t *: uz32be_from_uz16, \
        uc16_t *:       uz32be_from_uz16, \
        const uc8_t  *: uz32be_from_uz8,  \
        uc8_t  *:       uz32be_from_uz8   \
    )((to), (from))

#define uz32be_from_n(to, from, from_len)  \
    _Generic((from),                       \
        const uc32_t *: uz32be_from_uz32n, \
        uc32_t *:       uz32be_from_uz32n, \
        const uc16_t *: uz32be_from_uz16n, \
        uc16_t *:       uz32be_from_uz16n, \
        const uc8_t  *: uz32be_from_uz8n,  \
        uc8_t  *:       uz32be_from_uz8n   \
    )((to), (from), (from_len))

#define uz32be_from_le(to, from)            \
    _Generic((from),                        \
        const uc32_t *: uz32be_from_uz32le, \
        uc32_t *:       uz32be_from_uz32le, \
        const uc16_t *: uz32be_from_uz16le, \
        uc16_t *:       uz32be_from_uz16le, \
        const uc8_t  *: uz32be_from_uz8,    \
        uc8_t  *:       uz32be_from_uz8     \
    )((to), (from))

#define uz32be_from_len(to, from, from_len)  \
    _Generic((from),                         \
        const uc32_t *: uz32be_from_uz32len, \
        uc32_t *:       uz32be_from_uz32len, \
        const uc16_t *: uz32be_from_uz16len, \
        uc16_t *:       uz32be_from_uz16len, \
        const uc8_t  *: uz32be_from_uz8n,    \
        uc8_t  *:       uz32be_from_uz8n     \
    )((to), (from), (from_len))

#define uz32be_from_be(to, from)            \
    _Generic((from),                        \
        const uc32_t *: uz32be_from_uz32be, \
        uc32_t *:       uz32be_from_uz32be, \
        const uc16_t *: uz32be_from_uz16be, \
        uc16_t *:       uz32be_from_uz16be, \
        const uc8_t  *: uz32be_from_uz8,    \
        uc8_t  *:       uz32be_from_uz8     \
    )((to), (from))

#define uz32be_from_ben(to, from, from_len)  \
    _Generic((from),                         \
        const uc32_t *: uz32be_from_uz32ben, \
        uc32_t *:       uz32be_from_uz32ben, \
        const uc16_t *: uz32be_from_uz16ben, \
        uc16_t *:       uz32be_from_uz16ben, \
        const uc8_t  *: uz32be_from_uz8n,    \
        uc8_t  *:       uz32be_from_uz8n     \
    )((to), (from), (from_len))


#define uz16_from_range(to, from, begin, len)  \
    _Generic((from),                           \
        const uc32_t *: uz16_from_uz32_range,  \
        uc32_t *:       uz16_from_uz32_range,  \
        ucv32_t:        uz16_from_ucv32_range, \
        uv32_t:         uz16_from_uv32_range,  \
        const us32_t *: uz16_from_us32_range,  \
        us32_t *:       uz16_from_us32_range,  \
                                               \
        const uc16_t *: uz16_from_uz16_range,  \
        uc16_t *:       uz16_from_uz16_range,  \
        ucv16_t:        uz16_from_ucv16_range, \
        uv16_t:         uz16_from_uv16_range,  \
        const us16_t *: uz16_from_us16_range,  \
        us16_t *:       uz16_from_us16_range,  \
                                               \
        const uc8_t *:  uz16_from_uz8_range,   \
        uc8_t *:        uz16_from_uz8_range,   \
        ucv8_t:         uz16_from_ucv8_range,  \
        uv8_t:          uz16_from_uv8_range,   \
        const us8_t *:  uz16_from_us8_range,   \
        us8_t *:        uz16_from_us8_range    \
    )((to), (from), (begin), (len))

#define uz16_from(to, from)                  \
    _Generic((from),                         \
                                             \
        /* Conversion */                     \
                                             \
        const uc32_t *:     uz16_from_uz32,  \
        uc32_t *:           uz16_from_uz32,  \
        ucv32_t:            uz16_from_ucv32, \
        uv32_t:             uz16_from_uv32,  \
        const us32_t *:     uz16_from_us32,  \
        us32_t *:           uz16_from_us32,  \
                                             \
        const uc16_t *:     uz16_from_uz16,  \
        uc16_t *:           uz16_from_uz16,  \
        ucv16_t:            uz16_from_ucv16, \
        uv16_t:             uz16_from_uv16,  \
        const us16_t *:     uz16_from_us16,  \
        us16_t *:           uz16_from_us16,  \
                                             \
        const uc8_t *:      uz16_from_uz8,   \
        uc8_t *:            uz16_from_uz8,   \
        ucv8_t:             uz16_from_ucv8,  \
        uv8_t:              uz16_from_uv8,   \
        const us8_t *:      uz16_from_us8,   \
        us8_t *:            uz16_from_us8,   \
                                             \
        /* From float */                     \
                                             \
        float:              uz16_from_float, \
        double:             uz16_from_float, \
        long double:        uz16_from_float, \
                                             \
        /* From int */                       \
                                             \
        char:               uz16_from_int,   \
        short:              uz16_from_int,   \
        int:                uz16_from_int,   \
        long:               uz16_from_int,   \
        long long:          uz16_from_int,   \
                                             \
        unsigned char:      uz16_from_uint,  \
        unsigned short:     uz16_from_uint,  \
        unsigned:           uz16_from_uint,  \
        unsigned long:      uz16_from_uint,  \
        unsigned long long: uz16_from_uint   \
    )((to), (from))

#define uz16_from_n(to, from, from_len)  \
    _Generic((from),                     \
        const uc32_t *: uz16_from_uz32n, \
        uc32_t *:       uz16_from_uz32n, \
        const uc16_t *: uz16_from_uz16n, \
        uc16_t *:       uz16_from_uz16n, \
        const uc8_t  *: uz16_from_uz8n,  \
        uc8_t  *:       uz16_from_uz8n   \
    )((to), (from), (from_len))

#define uz16_from_le(to, from)            \
    _Generic((from),                      \
        const uc32_t *: uz16_from_uz32le, \
        uc32_t *:       uz16_from_uz32le, \
        const uc16_t *: uz16_from_uz16le, \
        uc16_t *:       uz16_from_uz16le, \
        const uc8_t  *: uz16_from_uz8,    \
        uc8_t  *:       uz16_from_uz8     \
    )((to), (from))

#define uz16_from_len(to, from, from_len)  \
    _Generic((from),                       \
        const uc32_t *: uz16_from_uz32len, \
        uc32_t *:       uz16_from_uz32len, \
        const uc16_t *: uz16_from_uz16len, \
        uc16_t *:       uz16_from_uz16len, \
        const uc8_t  *: uz16_from_uz8n,    \
        uc8_t  *:       uz16_from_uz8n     \
    )((to), (from), (from_len))

#define uz16_from_be(to, from)            \
    _Generic((from),                      \
        const uc32_t *: uz16_from_uz32be, \
        uc32_t *:       uz16_from_uz32be, \
        const uc16_t *: uz16_from_uz16be, \
        uc16_t *:       uz16_from_uz16be, \
        const uc8_t  *: uz16_from_uz8,    \
        uc8_t  *:       uz16_from_uz8     \
    )((to), (from))

#define uz16_from_ben(to, from, from_len)  \
    _Generic((from),                       \
        const uc32_t *: uz16_from_uz32ben, \
        uc32_t *:       uz16_from_uz32ben, \
        const uc16_t *: uz16_from_uz16ben, \
        uc16_t *:       uz16_from_uz16ben, \
        const uc8_t  *: uz16_from_uz8n,    \
        uc8_t  *:       uz16_from_uz8n     \
    )((to), (from), (from_len))

#define uz16le_from(to, from)             \
    _Generic((from),                      \
        const uc32_t *: uz16le_from_uz32, \
        uc32_t *:       uz16le_from_uz32, \
        const uc16_t *: uz16le_from_uz16, \
        uc16_t *:       uz16le_from_uz16, \
        const uc8_t  *: uz16le_from_uz8,  \
        uc8_t  *:       uz16le_from_uz8   \
    )((to), (from))

#define uz16le_from_n(to, from, from_len)  \
    _Generic((from),                       \
        const uc32_t *: uz16le_from_uz32n, \
        uc32_t *:       uz16le_from_uz32n, \
        const uc16_t *: uz16le_from_uz16n, \
        uc16_t *:       uz16le_from_uz16n, \
        const uc8_t  *: uz16le_from_uz8n,  \
        uc8_t  *:       uz16le_from_uz8n   \
    )((to), (from), (from_len))

#define uz16le_from_le(to, from)            \
    _Generic((from),                        \
        const uc32_t *: uz16le_from_uz32le, \
        uc32_t *:       uz16le_from_uz32le, \
        const uc16_t *: uz16le_from_uz16le, \
        uc16_t *:       uz16le_from_uz16le, \
        const uc8_t  *: uz16le_from_uz8,    \
        uc8_t  *:       uz16le_from_uz8     \
    )((to), (from))

#define uz16le_from_len(to, from, from_len)  \
    _Generic((from),                         \
        const uc32_t *: uz16le_from_uz32len, \
        uc32_t *:       uz16le_from_uz32len, \
        const uc16_t *: uz16le_from_uz16len, \
        uc16_t *:       uz16le_from_uz16len, \
        const uc8_t  *: uz16le_from_uz8n,    \
        uc8_t  *:       uz16le_from_uz8n     \
    )((to), (from), (from_len))

#define uz16le_from_be(to, from)            \
    _Generic((from),                        \
        const uc32_t *: uz16le_from_uz32be, \
        uc32_t *:       uz16le_from_uz32be, \
        const uc16_t *: uz16le_from_uz16be, \
        uc16_t *:       uz16le_from_uz16be, \
        const uc8_t  *: uz16le_from_uz8,    \
        uc8_t  *:       uz16le_from_uz8     \
    )((to), (from))

#define uz16le_from_ben(to, from, from_len)  \
    _Generic((from),                         \
        const uc32_t *: uz16le_from_uz32ben, \
        uc32_t *:       uz16le_from_uz32ben, \
        const uc16_t *: uz16le_from_uz16ben, \
        uc16_t *:       uz16le_from_uz16ben, \
        const uc8_t  *: uz16le_from_uz8n,    \
        uc8_t  *:       uz16le_from_uz8n     \
    )((to), (from), (from_len))

#define uz16be_from(to, from)             \
    _Generic((from),                      \
        const uc32_t *: uz16be_from_uz32, \
        uc32_t *:       uz16be_from_uz32, \
        const uc16_t *: uz16be_from_uz16, \
        uc16_t *:       uz16be_from_uz16, \
        const uc8_t  *: uz16be_from_uz8,  \
        uc8_t  *:       uz16be_from_uz8   \
    )((to), (from))

#define uz16be_from_n(to, from, from_len)  \
    _Generic((from),                       \
        const uc32_t *: uz16be_from_uz32n, \
        uc32_t *:       uz16be_from_uz32n, \
        const uc16_t *: uz16be_from_uz16n, \
        uc16_t *:       uz16be_from_uz16n, \
        const uc8_t  *: uz16be_from_uz8n,  \
        uc8_t  *:       uz16be_from_uz8n   \
    )((to), (from), (from_len))

#define uz16be_from_le(to, from)            \
    _Generic((from),                        \
        const uc32_t *: uz16be_from_uz32le, \
        uc32_t *:       uz16be_from_uz32le, \
        const uc16_t *: uz16be_from_uz16le, \
        uc16_t *:       uz16be_from_uz16le, \
        const uc8_t  *: uz16be_from_uz8,    \
        uc8_t  *:       uz16be_from_uz8     \
    )((to), (from))

#define uz16be_from_len(to, from, from_len)  \
    _Generic((from),                         \
        const uc32_t *: uz16be_from_uz32len, \
        uc32_t *:       uz16be_from_uz32len, \
        const uc16_t *: uz16be_from_uz16len, \
        uc16_t *:       uz16be_from_uz16len, \
        const uc8_t  *: uz16be_from_uz8n,    \
        uc8_t  *:       uz16be_from_uz8n     \
    )((to), (from), (from_len))

#define uz16be_from_be(to, from)            \
    _Generic((from),                        \
        const uc32_t *: uz16be_from_uz32be, \
        uc32_t *:       uz16be_from_uz32be, \
        const uc16_t *: uz16be_from_uz16be, \
        uc16_t *:       uz16be_from_uz16be, \
        const uc8_t  *: uz16be_from_uz8,    \
        uc8_t  *:       uz16be_from_uz8     \
    )((to), (from))

#define uz16be_from_ben(to, from, from_len)  \
    _Generic((from),                         \
        const uc32_t *: uz16be_from_uz32ben, \
        uc32_t *:       uz16be_from_uz32ben, \
        const uc16_t *: uz16be_from_uz16ben, \
        uc16_t *:       uz16be_from_uz16ben, \
        const uc8_t  *: uz16be_from_uz8n,    \
        uc8_t  *:       uz16be_from_uz8n     \
    )((to), (from), (from_len))


#define uz8_from_range(to, from, begin, len)  \
    _Generic((from),                          \
        const uc32_t *: uz8_from_uz32_range,  \
        uc32_t *:       uz8_from_uz32_range,  \
        ucv32_t:        uz8_from_ucv32_range, \
        uv32_t:         uz8_from_uv32_range,  \
        const us32_t *: uz8_from_us32_range,  \
        us32_t *:       uz8_from_us32_range,  \
                                              \
        const uc16_t *: uz8_from_uz16_range,  \
        uc16_t *:       uz8_from_uz16_range,  \
        ucv16_t:        uz8_from_ucv16_range, \
        uv16_t:         uz8_from_uv16_range,  \
        const us16_t *: uz8_from_us16_range,  \
        us16_t *:       uz8_from_us16_range,  \
                                              \
        const uc8_t *:  uz8_from_uz8_range,   \
        uc8_t *:        uz8_from_uz8_range,   \
        ucv8_t:         uz8_from_ucv8_range,  \
        uv8_t:          uz8_from_uv8_range,   \
        const us8_t *:  uz8_from_us8_range,   \
        us8_t *:        uz8_from_us8_range    \
    )((to), (from), (begin), (len))

#define uz8_from(to, from)                  \
    _Generic((from),                        \
                                            \
        /* Conversion */                    \
                                            \
        const uc32_t *:     uz8_from_uz32,  \
        uc32_t *:           uz8_from_uz32,  \
        ucv32_t:            uz8_from_ucv32, \
        uv32_t:             uz8_from_uv32,  \
        const us32_t *:     uz8_from_us32,  \
        us32_t *:           uz8_from_us32,  \
                                            \
        const uc16_t *:     uz8_from_uz16,  \
        uc16_t *:           uz8_from_uz16,  \
        ucv16_t:            uz8_from_ucv16, \
        uv16_t:             uz8_from_uv16,  \
        const us16_t *:     uz8_from_us16,  \
        us16_t *:           uz8_from_us16,  \
                                            \
        const uc8_t *:      uz8_from_uz8,   \
        uc8_t *:            uz8_from_uz8,   \
        ucv8_t:             uz8_from_ucv8,  \
        uv8_t:              uz8_from_uv8,   \
        const us8_t *:      uz8_from_us8,   \
        us8_t *:            uz8_from_us8,   \
                                            \
        /* From float */                    \
                                            \
        float:              uz8_from_float, \
        double:             uz8_from_float, \
        long double:        uz8_from_float, \
                                            \
        /* From int */                      \
                                            \
        char:               uz8_from_int,   \
        short:              uz8_from_int,   \
        int:                uz8_from_int,   \
        long:               uz8_from_int,   \
        long long:          uz8_from_int,   \
                                            \
        unsigned char:      uz8_from_uint,  \
        unsigned short:     uz8_from_uint,  \
        unsigned:           uz8_from_uint,  \
        unsigned long:      uz8_from_uint,  \
        unsigned long long: uz8_from_uint   \
    )((to), (from))

#define uz8_from_n(to, from, from_len)  \
    _Generic((from),                    \
        const uc32_t *: uz8_from_uz32n, \
        uc32_t *:       uz8_from_uz32n, \
        const uc16_t *: uz8_from_uz16n, \
        uc16_t *:       uz8_from_uz16n, \
        const uc8_t  *: uz8_from_uz8n,  \
        uc8_t  *:       uz8_from_uz8n   \
    )((to), (from), (from_len))

#define uz8_from_le(to, from)            \
    _Generic((from),                     \
        const uc32_t *: uz8_from_uz32le, \
        uc32_t *:       uz8_from_uz32le, \
        const uc16_t *: uz8_from_uz16le, \
        uc16_t *:       uz8_from_uz16le, \
        const uc8_t  *: uz8_from_uz8,    \
        uc8_t  *:       uz8_from_uz8     \
    )((to), (from))

#define uz8_from_len(to, from, from_len)  \
    _Generic((from),                      \
        const uc32_t *: uz8_from_uz32len, \
        uc32_t *:       uz8_from_uz32len, \
        const uc16_t *: uz8_from_uz16len, \
        uc16_t *:       uz8_from_uz16len, \
        const uc8_t  *: uz8_from_uz8n,    \
        uc8_t  *:       uz8_from_uz8n     \
    )((to), (from), (from_len))

#define uz8_from_be(to, from)            \
    _Generic((from),                     \
        const uc32_t *: uz8_from_uz32be, \
        uc32_t *:       uz8_from_uz32be, \
        const uc16_t *: uz8_from_uz16be, \
        uc16_t *:       uz8_from_uz16be, \
        const uc8_t  *: uz8_from_uz8,    \
        uc8_t  *:       uz8_from_uz8     \
    )((to), (from))

#define uz8_from_ben(to, from, from_len)  \
    _Generic((from),                      \
        const uc32_t *: uz8_from_uz32ben, \
        uc32_t *:       uz8_from_uz32ben, \
        const uc16_t *: uz8_from_uz16ben, \
        uc16_t *:       uz8_from_uz16ben, \
        const uc8_t  *: uz8_from_uz8n,    \
        uc8_t  *:       uz8_from_uz8n     \
    )((to), (from), (from_len))

#define uz8le_from(to, from)             \
    _Generic((from),                     \
        const uc32_t *: uz8le_from_uz32, \
        uc32_t *:       uz8le_from_uz32, \
        const uc16_t *: uz8le_from_uz16, \
        uc16_t *:       uz8le_from_uz16, \
        const uc8_t  *: uz8le_from_uz8,  \
        uc8_t  *:       uz8le_from_uz8   \
    )((to), (from))

#define uz8le_from_n(to, from, from_len)  \
    _Generic((from),                      \
        const uc32_t *: uz8le_from_uz32n, \
        uc32_t *:       uz8le_from_uz32n, \
        const uc16_t *: uz8le_from_uz16n, \
        uc16_t *:       uz8le_from_uz16n, \
        const uc8_t  *: uz8le_from_uz8n,  \
        uc8_t  *:       uz8le_from_uz8n   \
    )((to), (from), (from_len))

#define uz8le_from_le(to, from)            \
    _Generic((from),                       \
        const uc32_t *: uz8le_from_uz32le, \
        uc32_t *:       uz8le_from_uz32le, \
        const uc16_t *: uz8le_from_uz16le, \
        uc16_t *:       uz8le_from_uz16le, \
        const uc8_t  *: uz8le_from_uz8,    \
        uc8_t  *:       uz8le_from_uz8     \
    )((to), (from))

#define uz8le_from_len(to, from, from_len)  \
    _Generic((from),                        \
        const uc32_t *: uz8le_from_uz32len, \
        uc32_t *:       uz8le_from_uz32len, \
        const uc16_t *: uz8le_from_uz16len, \
        uc16_t *:       uz8le_from_uz16len, \
        const uc8_t  *: uz8le_from_uz8n,    \
        uc8_t  *:       uz8le_from_uz8n     \
    )((to), (from), (from_len))

#define uz8le_from_be(to, from)            \
    _Generic((from),                       \
        const uc32_t *: uz8le_from_uz32be, \
        uc32_t *:       uz8le_from_uz32be, \
        const uc16_t *: uz8le_from_uz16be, \
        uc16_t *:       uz8le_from_uz16be, \
        const uc8_t  *: uz8le_from_uz8,    \
        uc8_t  *:       uz8le_from_uz8     \
    )((to), (from))

#define uz8le_from_ben(to, from, from_len)  \
    _Generic((from),                        \
        const uc32_t *: uz8le_from_uz32ben, \
        uc32_t *:       uz8le_from_uz32ben, \
        const uc16_t *: uz8le_from_uz16ben, \
        uc16_t *:       uz8le_from_uz16ben, \
        const uc8_t  *: uz8le_from_uz8n,    \
        uc8_t  *:       uz8le_from_uz8n     \
    )((to), (from), (from_len))

#define uz8be_from(to, from)             \
    _Generic((from),                     \
        const uc32_t *: uz8be_from_uz32, \
        uc32_t *:       uz8be_from_uz32, \
        const uc16_t *: uz8be_from_uz16, \
        uc16_t *:       uz8be_from_uz16, \
        const uc8_t  *: uz8be_from_uz8,  \
        uc8_t  *:       uz8be_from_uz8   \
    )((to), (from))

#define uz8be_from_n(to, from, from_len)  \
    _Generic((from),                      \
        const uc32_t *: uz8be_from_uz32n, \
        uc32_t *:       uz8be_from_uz32n, \
        const uc16_t *: uz8be_from_uz16n, \
        uc16_t *:       uz8be_from_uz16n, \
        const uc8_t  *: uz8be_from_uz8n,  \
        uc8_t  *:       uz8be_from_uz8n   \
    )((to), (from), (from_len))

#define uz8be_from_le(to, from)            \
    _Generic((from),                       \
        const uc32_t *: uz8be_from_uz32le, \
        uc32_t *:       uz8be_from_uz32le, \
        const uc16_t *: uz8be_from_uz16le, \
        uc16_t *:       uz8be_from_uz16le, \
        const uc8_t  *: uz8be_from_uz8,    \
        uc8_t  *:       uz8be_from_uz8     \
    )((to), (from))

#define uz8be_from_len(to, from, from_len)  \
    _Generic((from),                        \
        const uc32_t *: uz8be_from_uz32len, \
        uc32_t *:       uz8be_from_uz32len, \
        const uc16_t *: uz8be_from_uz16len, \
        uc16_t *:       uz8be_from_uz16len, \
        const uc8_t  *: uz8be_from_uz8n,    \
        uc8_t  *:       uz8be_from_uz8n     \
    )((to), (from), (from_len))

#define uz8be_from_be(to, from)            \
    _Generic((from),                       \
        const uc32_t *: uz8be_from_uz32be, \
        uc32_t *:       uz8be_from_uz32be, \
        const uc16_t *: uz8be_from_uz16be, \
        uc16_t *:       uz8be_from_uz16be, \
        const uc8_t  *: uz8be_from_uz8,    \
        uc8_t  *:       uz8be_from_uz8     \
    )((to), (from))

#define uz8be_from_ben(to, from, from_len)  \
    _Generic((from),                        \
        const uc32_t *: uz8be_from_uz32ben, \
        uc32_t *:       uz8be_from_uz32ben, \
        const uc16_t *: uz8be_from_uz16ben, \
        uc16_t *:       uz8be_from_uz16ben, \
        const uc8_t  *: uz8be_from_uz8n,    \
        uc8_t  *:       uz8be_from_uz8n     \
    )((to), (from), (from_len))

// - Conversion

UEXPORT size_t uz32_from_uz32(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT size_t uz32_from_uz32_range(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t begin, size_t len);
UEXPORT size_t uz32_from_uz32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32_from_uz32n_range(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT size_t uz32_from_ucv32(UNULLABLE UOUT uc32_t *to, ucv32_t from);
UEXPORT size_t uz32_from_ucv32_range(UNULLABLE UOUT uc32_t *to, ucv32_t from, size_t begin, size_t len);
UEXPORT size_t uz32_from_uv32(UNULLABLE UOUT uc32_t *to, uv32_t from);
UEXPORT size_t uz32_from_uv32_range(UNULLABLE UOUT uc32_t *to, uv32_t from, size_t begin, size_t len);
UEXPORT size_t uz32_from_us32(UNULLABLE UOUT uc32_t *to, const us32_t *from);
UEXPORT size_t uz32_from_us32_range(UNULLABLE UOUT uc32_t *to, const us32_t *from, size_t begin, size_t len);

UEXPORT size_t uz32_from_uz16(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT size_t uz32_from_uz16_range(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t begin, size_t len);
UEXPORT size_t uz32_from_uz16n(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz32_from_uz16n_range(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT size_t uz32_from_ucv16(UNULLABLE UOUT uc32_t *to, ucv16_t from);
UEXPORT size_t uz32_from_ucv16_range(UNULLABLE UOUT uc32_t *to, ucv16_t from, size_t begin, size_t len);
UEXPORT size_t uz32_from_uv16(UNULLABLE UOUT uc32_t *to, uv16_t from);
UEXPORT size_t uz32_from_uv16_range(UNULLABLE UOUT uc32_t *to, uv16_t from, size_t begin, size_t len);
UEXPORT size_t uz32_from_us16(UNULLABLE UOUT uc32_t *to, const us16_t *from);
UEXPORT size_t uz32_from_us16_range(UNULLABLE UOUT uc32_t *to, const us16_t *from, size_t begin, size_t len);

UEXPORT size_t uz32_from_uz8(UNULLABLE UOUT uc32_t *to, const uc8_t *from);
UEXPORT size_t uz32_from_uz8_range(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t begin, size_t len);
UEXPORT size_t uz32_from_uz8n(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len);
UEXPORT size_t uz32_from_uz8n_range(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT size_t uz32_from_ucv8(UNULLABLE UOUT uc32_t *to, ucv8_t from);
UEXPORT size_t uz32_from_ucv8_range(UNULLABLE UOUT uc32_t *to, ucv8_t from, size_t begin, size_t len);
UEXPORT size_t uz32_from_uv8(UNULLABLE UOUT uc32_t *to, uv8_t from);
UEXPORT size_t uz32_from_uv8_range(UNULLABLE UOUT uc32_t *to, uv8_t from, size_t begin, size_t len);
UEXPORT size_t uz32_from_us8(UNULLABLE UOUT uc32_t *to, const us8_t *from);
UEXPORT size_t uz32_from_us8_range(UNULLABLE UOUT uc32_t *to, const us8_t *from, size_t begin, size_t len);

UEXPORT size_t uz32_from_bytes(UNULLABLE UOUT uc32_t *to, const void *from, uencoding_t encoding);
UEXPORT size_t uz32_from_bytesn(UNULLABLE UOUT uc32_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t uz32_from_uz32le(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT size_t uz32_from_uz32len(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32_from_uz16le(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT size_t uz32_from_uz16len(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz32_from_uz32be(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT size_t uz32_from_uz32ben(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32_from_uz16be(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT size_t uz32_from_uz16ben(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);

UEXPORT size_t uz32le_from_bytes(UNULLABLE UOUT uc32_t *to, const void *from, uencoding_t encoding);
UEXPORT size_t uz32le_from_bytesn(UNULLABLE UOUT uc32_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t uz32le_from_uz32(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT size_t uz32le_from_uz32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32le_from_uz16(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT size_t uz32le_from_uz16n(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz32le_from_uz8(UNULLABLE UOUT uc32_t *to, const uc8_t *from);
UEXPORT size_t uz32le_from_uz8n(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len);
UEXPORT size_t uz32le_from_uz32le(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT size_t uz32le_from_uz32len(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32le_from_uz16le(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT size_t uz32le_from_uz16len(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz32le_from_uz32be(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT size_t uz32le_from_uz32ben(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32le_from_uz16be(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT size_t uz32le_from_uz16ben(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);

UEXPORT size_t uz32be_from_bytes(UNULLABLE UOUT uc32_t *to, const void *from, uencoding_t encoding);
UEXPORT size_t uz32be_from_bytesn(UNULLABLE UOUT uc32_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t uz32be_from_uz32(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT size_t uz32be_from_uz32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32be_from_uz16(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT size_t uz32be_from_uz16n(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz32be_from_uz8(UNULLABLE UOUT uc32_t *to, const uc8_t *from);
UEXPORT size_t uz32be_from_uz8n(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len);
UEXPORT size_t uz32be_from_uz32le(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT size_t uz32be_from_uz32len(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32be_from_uz16le(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT size_t uz32be_from_uz16len(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz32be_from_uz32be(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT size_t uz32be_from_uz32ben(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32be_from_uz16be(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT size_t uz32be_from_uz16ben(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);


UEXPORT size_t uz16_from_uz32(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT size_t uz16_from_uz32_range(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t begin, size_t len);
UEXPORT size_t uz16_from_uz32n(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz16_from_uz32n_range(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT size_t uz16_from_ucv32(UNULLABLE UOUT uc16_t *to, ucv32_t from);
UEXPORT size_t uz16_from_ucv32_range(UNULLABLE UOUT uc16_t *to, ucv32_t from, size_t begin, size_t len);
UEXPORT size_t uz16_from_uv32(UNULLABLE UOUT uc16_t *to, uv32_t from);
UEXPORT size_t uz16_from_uv32_range(UNULLABLE UOUT uc16_t *to, uv32_t from, size_t begin, size_t len);
UEXPORT size_t uz16_from_us32(UNULLABLE UOUT uc16_t *to, const us32_t *from);
UEXPORT size_t uz16_from_us32_range(UNULLABLE UOUT uc16_t *to, const us32_t *from, size_t begin, size_t len);

UEXPORT size_t uz16_from_uz16(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT size_t uz16_from_uz16_range(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t begin, size_t len);
UEXPORT size_t uz16_from_uz16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz16_from_uz16n_range(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT size_t uz16_from_ucv16(UNULLABLE UOUT uc16_t *to, ucv16_t from);
UEXPORT size_t uz16_from_ucv16_range(UNULLABLE UOUT uc16_t *to, ucv16_t from, size_t begin, size_t len);
UEXPORT size_t uz16_from_uv16(UNULLABLE UOUT uc16_t *to, uv16_t from);
UEXPORT size_t uz16_from_uv16_range(UNULLABLE UOUT uc16_t *to, uv16_t from, size_t begin, size_t len);
UEXPORT size_t uz16_from_us16(UNULLABLE UOUT uc16_t *to, const us16_t *from);
UEXPORT size_t uz16_from_us16_range(UNULLABLE UOUT uc16_t *to, const us16_t *from, size_t begin, size_t len);

UEXPORT size_t uz16_from_uz8(UNULLABLE UOUT uc16_t *to, const uc8_t *from);
UEXPORT size_t uz16_from_uz8_range(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t begin, size_t len);
UEXPORT size_t uz16_from_uz8n(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len);
UEXPORT size_t uz16_from_uz8n_range(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT size_t uz16_from_ucv8(UNULLABLE UOUT uc16_t *to, ucv8_t from);
UEXPORT size_t uz16_from_ucv8_range(UNULLABLE UOUT uc16_t *to, ucv8_t from, size_t begin, size_t len);
UEXPORT size_t uz16_from_uv8(UNULLABLE UOUT uc16_t *to, uv8_t from);
UEXPORT size_t uz16_from_uv8_range(UNULLABLE UOUT uc16_t *to, uv8_t from, size_t begin, size_t len);
UEXPORT size_t uz16_from_us8(UNULLABLE UOUT uc16_t *to, const us8_t *from);
UEXPORT size_t uz16_from_us8_range(UNULLABLE UOUT uc16_t *to, const us8_t *from, size_t begin, size_t len);

UEXPORT size_t uz16_from_bytes(UNULLABLE UOUT uc16_t *to, const void *from, uencoding_t encoding);
UEXPORT size_t uz16_from_bytesn(UNULLABLE UOUT uc16_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t uz16_from_uz32le(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT size_t uz16_from_uz32len(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz16_from_uz16le(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT size_t uz16_from_uz16len(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz16_from_uz32be(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT size_t uz16_from_uz32ben(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz16_from_uz16be(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT size_t uz16_from_uz16ben(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);

UEXPORT size_t uz16le_from_bytes(UNULLABLE UOUT uc16_t *to, const void *from, uencoding_t encoding);
UEXPORT size_t uz16le_from_bytesn(UNULLABLE UOUT uc16_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t uz16le_from_uz32(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT size_t uz16le_from_uz32n(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz16le_from_uz16(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT size_t uz16le_from_uz16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz16le_from_uz8(UNULLABLE UOUT uc16_t *to, const uc8_t *from);
UEXPORT size_t uz16le_from_uz8n(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len);
UEXPORT size_t uz16le_from_uz32le(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT size_t uz16le_from_uz32len(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz16le_from_uz16le(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT size_t uz16le_from_uz16len(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz16le_from_uz32be(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT size_t uz16le_from_uz32ben(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz16le_from_uz16be(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT size_t uz16le_from_uz16ben(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);

UEXPORT size_t uz16be_from_bytes(UNULLABLE UOUT uc16_t *to, const void *from, uencoding_t encoding);
UEXPORT size_t uz16be_from_bytesn(UNULLABLE UOUT uc16_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t uz16be_from_uz32(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT size_t uz16be_from_uz32n(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz16be_from_uz16(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT size_t uz16be_from_uz16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz16be_from_uz8(UNULLABLE UOUT uc16_t *to, const uc8_t *from);
UEXPORT size_t uz16be_from_uz8n(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len);
UEXPORT size_t uz16be_from_uz32le(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT size_t uz16be_from_uz32len(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz16be_from_uz16le(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT size_t uz16be_from_uz16len(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz16be_from_uz32be(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT size_t uz16be_from_uz32ben(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz16be_from_uz16be(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT size_t uz16be_from_uz16ben(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);


UEXPORT size_t uz8_from_uz32(UNULLABLE UOUT uc8_t *to, const uc32_t *from);
UEXPORT size_t uz8_from_uz32_range(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t begin, size_t len);
UEXPORT size_t uz8_from_uz32n(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz8_from_uz32n_range(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT size_t uz8_from_ucv32(UNULLABLE UOUT uc8_t *to, ucv32_t from);
UEXPORT size_t uz8_from_ucv32_range(UNULLABLE UOUT uc8_t *to, ucv32_t from, size_t begin, size_t len);
UEXPORT size_t uz8_from_uv32(UNULLABLE UOUT uc8_t *to, uv32_t from);
UEXPORT size_t uz8_from_uv32_range(UNULLABLE UOUT uc8_t *to, uv32_t from, size_t begin, size_t len);
UEXPORT size_t uz8_from_us32(UNULLABLE UOUT uc8_t *to, const us32_t *from);
UEXPORT size_t uz8_from_us32_range(UNULLABLE UOUT uc8_t *to, const us32_t *from, size_t begin, size_t len);

UEXPORT size_t uz8_from_uz16(UNULLABLE UOUT uc8_t *to, const uc16_t *from);
UEXPORT size_t uz8_from_uz16_range(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t begin, size_t len);
UEXPORT size_t uz8_from_uz16n(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz8_from_uz16n_range(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT size_t uz8_from_ucv16(UNULLABLE UOUT uc8_t *to, ucv16_t from);
UEXPORT size_t uz8_from_ucv16_range(UNULLABLE UOUT uc8_t *to, ucv16_t from, size_t begin, size_t len);
UEXPORT size_t uz8_from_uv16(UNULLABLE UOUT uc8_t *to, uv16_t from);
UEXPORT size_t uz8_from_uv16_range(UNULLABLE UOUT uc8_t *to, uv16_t from, size_t begin, size_t len);
UEXPORT size_t uz8_from_us16(UNULLABLE UOUT uc8_t *to, const us16_t *from);
UEXPORT size_t uz8_from_us16_range(UNULLABLE UOUT uc8_t *to, const us16_t *from, size_t begin, size_t len);

UEXPORT size_t uz8_from_uz8(UNULLABLE UOUT uc8_t *to, const uc8_t *from);
UEXPORT size_t uz8_from_uz8_range(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t begin, size_t len);
UEXPORT size_t uz8_from_uz8n(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len);
UEXPORT size_t uz8_from_uz8n_range(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT size_t uz8_from_ucv8(UNULLABLE UOUT uc8_t *to, ucv8_t from);
UEXPORT size_t uz8_from_ucv8_range(UNULLABLE UOUT uc8_t *to, ucv8_t from, size_t begin, size_t len);
UEXPORT size_t uz8_from_uv8(UNULLABLE UOUT uc8_t *to, uv8_t from);
UEXPORT size_t uz8_from_uv8_range(UNULLABLE UOUT uc8_t *to, uv8_t from, size_t begin, size_t len);
UEXPORT size_t uz8_from_us8(UNULLABLE UOUT uc8_t *to, const us8_t *from);
UEXPORT size_t uz8_from_us8_range(UNULLABLE UOUT uc8_t *to, const us8_t *from, size_t begin, size_t len);

UEXPORT size_t uz8_from_bytes(UNULLABLE UOUT uc8_t *to, const void *from, uencoding_t encoding);
UEXPORT size_t uz8_from_bytesn(UNULLABLE UOUT uc8_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t uz8_from_uz32le(UNULLABLE UOUT uc8_t *to, const uc32_t *from);
UEXPORT size_t uz8_from_uz32len(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz8_from_uz16le(UNULLABLE UOUT uc8_t *to, const uc16_t *from);
UEXPORT size_t uz8_from_uz16len(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len);
UEXPORT size_t uz8_from_uz32be(UNULLABLE UOUT uc8_t *to, const uc32_t *from);
UEXPORT size_t uz8_from_uz32ben(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len);
UEXPORT size_t uz8_from_uz16be(UNULLABLE UOUT uc8_t *to, const uc16_t *from);
UEXPORT size_t uz8_from_uz16ben(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len);

// - From format

#define uz32_from_fmt(to, from, ...)         \
    _Generic((from),                         \
        const uc32_t *: uz32_from_fmt_uz32,  \
        uc32_t *:       uz32_from_fmt_uz32,  \
        ucv32_t:        uz32_from_fmt_ucv32, \
        uv32_t:         uz32_from_fmt_uv32,  \
        const us32_t *: uz32_from_fmt_us32,  \
        us32_t *:       uz32_from_fmt_us32   \
    )((to), (from), __VA_ARGS__)

#define uz32_from_fmt_v(to, from, args)        \
    _Generic((from),                           \
        const uc32_t *: uz32_from_fmt_uz32_v,  \
        uc32_t *:       uz32_from_fmt_uz32_v,  \
        ucv32_t:        uz32_from_fmt_ucv32_v, \
        uv32_t:         uz32_from_fmt_uv32_v,  \
        const us32_t *: uz32_from_fmt_us32_v,  \
        us32_t *:       uz32_from_fmt_us32_v   \
    )((to), (from), (args))

UEXPORT size_t uz32_from_fmt_uz32(UNULLABLE UOUT uc32_t *to, const uc32_t *from, ...);
UEXPORT size_t uz32_from_fmt_uz32_v(UNULLABLE UOUT uc32_t *to, const uc32_t *from, va_list *args);
UEXPORT size_t uz32_from_fmt_uz32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len, ...);
UEXPORT size_t uz32_from_fmt_uz32n_v(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len, va_list *args);
UEXPORT size_t uz32_from_fmt_ucv32(UNULLABLE UOUT uc32_t *to, ucv32_t from, ...);
UEXPORT size_t uz32_from_fmt_ucv32_v(UNULLABLE UOUT uc32_t *to, ucv32_t from, va_list *args);
UEXPORT size_t uz32_from_fmt_uv32(UNULLABLE UOUT uc32_t *to, uv32_t from, ...);
UEXPORT size_t uz32_from_fmt_uv32_v(UNULLABLE UOUT uc32_t *to, uv32_t from, va_list *args);
UEXPORT size_t uz32_from_fmt_us32(UNULLABLE UOUT uc32_t *to, const us32_t *from, ...);
UEXPORT size_t uz32_from_fmt_us32_v(UNULLABLE UOUT uc32_t *to, const us32_t *from, va_list *args);

#define uz16_from_fmt(to, from, ...)         \
    _Generic((from),                         \
        const uc16_t *: uz16_from_fmt_uz16,  \
        uc16_t *:       uz16_from_fmt_uz16,  \
        ucv16_t:        uz16_from_fmt_ucv16, \
        uv16_t:         uz16_from_fmt_uv16,  \
        const us16_t *: uz16_from_fmt_us16,  \
        us16_t *:       uz16_from_fmt_us16   \
    )((to), (from), __VA_ARGS__)

#define uz16_from_fmt_v(to, from, args)        \
    _Generic((from),                           \
        const uc16_t *: uz16_from_fmt_uz16_v,  \
        uc16_t *:       uz16_from_fmt_uz16_v,  \
        ucv16_t:        uz16_from_fmt_ucv16_v, \
        uv16_t:         uz16_from_fmt_uv16_v,  \
        const us16_t *: uz16_from_fmt_us16_v,  \
        us16_t *:       uz16_from_fmt_us16_v   \
    )((to), (from), (args))

UEXPORT size_t uz16_from_fmt_uz16(UNULLABLE UOUT uc16_t *to, const uc16_t *from, ...);
UEXPORT size_t uz16_from_fmt_uz16_v(UNULLABLE UOUT uc16_t *to, const uc16_t *from, va_list *args);
UEXPORT size_t uz16_from_fmt_uz16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len, ...);
UEXPORT size_t uz16_from_fmt_uz16n_v(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len, va_list *args);
UEXPORT size_t uz16_from_fmt_ucv16(UNULLABLE UOUT uc16_t *to, ucv16_t from, ...);
UEXPORT size_t uz16_from_fmt_ucv16_v(UNULLABLE UOUT uc16_t *to, ucv16_t from, va_list *args);
UEXPORT size_t uz16_from_fmt_uv16(UNULLABLE UOUT uc16_t *to, uv16_t from, ...);
UEXPORT size_t uz16_from_fmt_uv16_v(UNULLABLE UOUT uc16_t *to, uv16_t from, va_list *args);
UEXPORT size_t uz16_from_fmt_us16(UNULLABLE UOUT uc16_t *to, const us16_t *from, ...);
UEXPORT size_t uz16_from_fmt_us16_v(UNULLABLE UOUT uc16_t *to, const us16_t *from, va_list *args);

#define uz8_from_fmt(to, from, ...)       \
    _Generic((from),                      \
        const uc8_t *: uz8_from_fmt_uz8,  \
        uc8_t *:       uz8_from_fmt_uz8,  \
        ucv8_t:        uz8_from_fmt_ucv8, \
        uv8_t:         uz8_from_fmt_uv8,  \
        const us8_t *: uz8_from_fmt_us8,  \
        us8_t *:       uz8_from_fmt_us8   \
    )((to), (from), __VA_ARGS__)

#define uz8_from_fmt_v(to, from, args)      \
    _Generic((from),                        \
        const uc8_t *: uz8_from_fmt_uz8_v,  \
        uc8_t *:       uz8_from_fmt_uz8_v,  \
        ucv8_t:        uz8_from_fmt_ucv8_v, \
        uv8_t:         uz8_from_fmt_uv8_v,  \
        const us8_t *: uz8_from_fmt_us8_v,  \
        us8_t *:       uz8_from_fmt_us8_v   \
    )((to), (from), (args))

UEXPORT size_t uz8_from_fmt_uz8(UNULLABLE UOUT uc8_t *to, const uc8_t *from, ...);
UEXPORT size_t uz8_from_fmt_uz8_v(UNULLABLE UOUT uc8_t *to, const uc8_t *from, va_list *args);
UEXPORT size_t uz8_from_fmt_uz8n(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, ...);
UEXPORT size_t uz8_from_fmt_uz8n_v(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, va_list *args);
UEXPORT size_t uz8_from_fmt_ucv8(UNULLABLE UOUT uc8_t *to, ucv8_t from, ...);
UEXPORT size_t uz8_from_fmt_ucv8_v(UNULLABLE UOUT uc8_t *to, ucv8_t from, va_list *args);
UEXPORT size_t uz8_from_fmt_uv8(UNULLABLE UOUT uc8_t *to, uv8_t from, ...);
UEXPORT size_t uz8_from_fmt_uv8_v(UNULLABLE UOUT uc8_t *to, uv8_t from, va_list *args);
UEXPORT size_t uz8_from_fmt_us8(UNULLABLE UOUT uc8_t *to, const us8_t *from, ...);
UEXPORT size_t uz8_from_fmt_us8_v(UNULLABLE UOUT uc8_t *to, const us8_t *from, va_list *args);

// - From float

UEXPORT size_t uz32_from_float(UNULLABLE UOUT uc32_t *to, double from);
UEXPORT size_t uz32_from_float_fmt(UNULLABLE UOUT uc32_t *to, double from, const struct ufmt32_float_output *fmt);

UEXPORT size_t uz16_from_float(UNULLABLE UOUT uc16_t *to, double from);
UEXPORT size_t uz16_from_float_fmt(UNULLABLE UOUT uc16_t *to, double from, const struct ufmt16_float_output *fmt);

UEXPORT size_t uz8_from_float(UNULLABLE UOUT uc8_t *to, double from);
UEXPORT size_t uz8_from_float_fmt(UNULLABLE UOUT uc8_t *to, double from, const struct ufmt8_float_output *fmt);

// - From int

UEXPORT size_t uz32_from_int(UNULLABLE UOUT uc32_t *to, intmax_t from);
UEXPORT size_t uz32_from_int_fmt(UNULLABLE UOUT uc32_t *to, intmax_t from, const struct ufmt32_int_output *fmt);
UEXPORT size_t uz32_from_uint(UNULLABLE UOUT uc32_t *to, uintmax_t from);
UEXPORT size_t uz32_from_uint_fmt(UNULLABLE UOUT uc32_t *to, uintmax_t from, const struct ufmt32_int_output *fmt);

UEXPORT size_t uz16_from_int(UNULLABLE UOUT uc16_t *to, intmax_t from);
UEXPORT size_t uz16_from_int_fmt(UNULLABLE UOUT uc16_t *to, intmax_t from, const struct ufmt16_int_output *fmt);
UEXPORT size_t uz16_from_uint(UNULLABLE UOUT uc16_t *to, uintmax_t from);
UEXPORT size_t uz16_from_uint_fmt(UNULLABLE UOUT uc16_t *to, uintmax_t from, const struct ufmt16_int_output *fmt);

UEXPORT size_t uz8_from_int(UNULLABLE UOUT uc8_t *to, intmax_t from);
UEXPORT size_t uz8_from_int_fmt(UNULLABLE UOUT uc8_t *to, intmax_t from, const struct ufmt8_int_output *fmt);
UEXPORT size_t uz8_from_uint(UNULLABLE UOUT uc8_t *to, uintmax_t from);
UEXPORT size_t uz8_from_uint_fmt(UNULLABLE UOUT uc8_t *to, uintmax_t from, const struct ufmt8_int_output *fmt);

// - From bool

UEXPORT size_t uz32_from_bool(UNULLABLE UOUT uc32_t *to, bool from);
UEXPORT size_t uz32_from_case_bool(UNULLABLE UOUT uc32_t *to, ucase_t ca, bool from);
UEXPORT size_t uz32_from_lower_bool(UNULLABLE UOUT uc32_t *to, bool from);
UEXPORT size_t uz32_from_upper_bool(UNULLABLE UOUT uc32_t *to, bool from);

UEXPORT size_t uz16_from_bool(UNULLABLE UOUT uc16_t *to, bool from);
UEXPORT size_t uz16_from_case_bool(UNULLABLE UOUT uc16_t *to, ucase_t ca, bool from);
UEXPORT size_t uz16_from_lower_bool(UNULLABLE UOUT uc16_t *to, bool from);
UEXPORT size_t uz16_from_upper_bool(UNULLABLE UOUT uc16_t *to, bool from);

UEXPORT size_t uz8_from_bool(UNULLABLE UOUT uc8_t *to, bool from);
UEXPORT size_t uz8_from_case_bool(UNULLABLE UOUT uc8_t *to, ucase_t ca, bool from);
UEXPORT size_t uz8_from_lower_bool(UNULLABLE UOUT uc8_t *to, bool from);
UEXPORT size_t uz8_from_upper_bool(UNULLABLE UOUT uc8_t *to, bool from);

// To bytes

UEXPORT size_t uz32_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from);
UEXPORT size_t uz32le_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from);
UEXPORT size_t uz32be_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from);

UEXPORT size_t uz32n_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32len_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from, size_t from_len);
UEXPORT size_t uz32ben_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from, size_t from_len);


UEXPORT size_t uz16_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from);
UEXPORT size_t uz16le_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from);
UEXPORT size_t uz16be_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from);

UEXPORT size_t uz16n_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from, size_t from_len);
UEXPORT size_t uz16len_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from, size_t from_len);
UEXPORT size_t uz16ben_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from, size_t from_len);


UEXPORT size_t uz8_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc8_t *from);

UEXPORT size_t uz8n_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc8_t *from, size_t from_len);

// Length

UEXPORT size_t uz32_len(const uc32_t *cstr);
UEXPORT size_t uz32_len_n(const uc32_t *cstr, unsigned n);
UEXPORT size_t uz32_len_32(const uc32_t *cstr);
UEXPORT size_t uz32_len_16(const uc32_t *cstr);
UEXPORT size_t uz32_len_8(const uc32_t *cstr);

UEXPORT size_t uz32n_len(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32n_len_n(const uc32_t *cstr, size_t cstr_len, unsigned n);
UEXPORT size_t uz32n_len_32(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32n_len_16(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32n_len_8(const uc32_t *cstr, size_t cstr_len);


UEXPORT size_t uz32le_len(const uc32_t *cstr);
UEXPORT size_t uz32le_len_n(const uc32_t *cstr, unsigned n);
UEXPORT size_t uz32le_len_32(const uc32_t *cstr);
UEXPORT size_t uz32le_len_16(const uc32_t *cstr);
UEXPORT size_t uz32le_len_8(const uc32_t *cstr);

UEXPORT size_t uz32len_len(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32len_len_n(const uc32_t *cstr, size_t cstr_len, unsigned n);
UEXPORT size_t uz32len_len_32(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32len_len_16(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32len_len_8(const uc32_t *cstr, size_t cstr_len);


UEXPORT size_t uz32be_len(const uc32_t *cstr);
UEXPORT size_t uz32be_len_n(const uc32_t *cstr, unsigned n);
UEXPORT size_t uz32be_len_32(const uc32_t *cstr);
UEXPORT size_t uz32be_len_16(const uc32_t *cstr);
UEXPORT size_t uz32be_len_8(const uc32_t *cstr);

UEXPORT size_t uz32ben_len(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32ben_len_n(const uc32_t *cstr, size_t cstr_len, unsigned n);
UEXPORT size_t uz32ben_len_32(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32ben_len_16(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32ben_len_8(const uc32_t *cstr, size_t cstr_len);



UEXPORT size_t uz16_len(const uc16_t *cstr);
UEXPORT size_t uz16_len_n(const uc16_t *cstr, unsigned n);
UEXPORT size_t uz16_len_32(const uc16_t *cstr);
UEXPORT size_t uz16_len_16(const uc16_t *cstr);
UEXPORT size_t uz16_len_8(const uc16_t *cstr);

UEXPORT size_t uz16n_len(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16n_len_n(const uc16_t *cstr, size_t cstr_len, unsigned n);
UEXPORT size_t uz16n_len_32(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16n_len_16(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16n_len_8(const uc16_t *cstr, size_t cstr_len);


UEXPORT size_t uz16le_len(const uc16_t *cstr);
UEXPORT size_t uz16le_len_n(const uc16_t *cstr, unsigned n);
UEXPORT size_t uz16le_len_32(const uc16_t *cstr);
UEXPORT size_t uz16le_len_16(const uc16_t *cstr);
UEXPORT size_t uz16le_len_8(const uc16_t *cstr);

UEXPORT size_t uz16len_len(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16len_len_n(const uc16_t *cstr, size_t cstr_len, unsigned n);
UEXPORT size_t uz16len_len_32(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16len_len_16(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16len_len_8(const uc16_t *cstr, size_t cstr_len);


UEXPORT size_t uz16be_len(const uc16_t *cstr);
UEXPORT size_t uz16be_len_n(const uc16_t *cstr, unsigned n);
UEXPORT size_t uz16be_len_32(const uc16_t *cstr);
UEXPORT size_t uz16be_len_16(const uc16_t *cstr);
UEXPORT size_t uz16be_len_8(const uc16_t *cstr);

UEXPORT size_t uz16ben_len(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16ben_len_n(const uc16_t *cstr, size_t cstr_len, unsigned n);
UEXPORT size_t uz16ben_len_32(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16ben_len_16(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16ben_len_8(const uc16_t *cstr, size_t cstr_len);



UEXPORT size_t uz8_len(const uc8_t *cstr);
UEXPORT size_t uz8_len_n(const uc8_t *cstr, unsigned n);
UEXPORT size_t uz8_len_32(const uc8_t *cstr);
UEXPORT size_t uz8_len_16(const uc8_t *cstr);
UEXPORT size_t uz8_len_8(const uc8_t *cstr);

UEXPORT size_t uz8n_len(const uc8_t *cstr, size_t cstr_len);
UEXPORT size_t uz8n_len_n(const uc8_t *cstr, size_t cstr_len, unsigned n);
UEXPORT size_t uz8n_len_32(const uc8_t *cstr, size_t cstr_len);
UEXPORT size_t uz8n_len_16(const uc8_t *cstr, size_t cstr_len);
UEXPORT size_t uz8n_len_8(const uc8_t *cstr, size_t cstr_len);

// Trailing length

UEXPORT size_t uz8_trail(const uc8_t *cstr);
UEXPORT size_t uz8n_trail(const uc8_t *cstr, size_t cstr_len);

// Compare

#define uz32_cmp(lhs, rhs)              \
    _Generic((rhs),                     \
        default:        uz32_cmp_uc32,  \
        const uc32_t *: uz32_cmp_uz32,  \
        uc32_t *:       uz32_cmp_uz32,  \
        ucv32_t:        uz32_cmp_ucv32, \
        uv32_t:         uz32_cmp_uv32,  \
        const us32_t *: uz32_cmp_us32,  \
        us32_t *:       uz32_cmp_us32   \
    )((lhs), (rhs))

UEXPORT int uz32_cmp_uc32(const uc32_t *lhs, uc32_t rhs);
UEXPORT int uz32_cmp_uz32(const uc32_t *lhs, const uc32_t *rhs);
UEXPORT int uz32_cmp_uz32n(const uc32_t *lhs, const uc32_t *rhs, size_t rhs_len);
UEXPORT int uz32_cmp_ucv32(const uc32_t *lhs, ucv32_t rhs);
UEXPORT int uz32_cmp_uv32(const uc32_t *lhs, uv32_t rhs);
UEXPORT int uz32_cmp_us32(const uc32_t *lhs, const us32_t *rhs);

#define uz32n_cmp(lhs, lhs_len, rhs)     \
    _Generic((rhs),                      \
        default:        uz32n_cmp_uc32,  \
        const uc32_t *: uz32n_cmp_uz32,  \
        uc32_t *:       uz32n_cmp_uz32,  \
        ucv32_t:        uz32n_cmp_ucv32, \
        uv32_t:         uz32n_cmp_uv32,  \
        const us32_t *: uz32n_cmp_us32,  \
        us32_t *:       uz32n_cmp_us32   \
    )((lhs), (lhs_len), (rhs))

UEXPORT int uz32n_cmp_uc32(const uc32_t *lhs, size_t lhs_len, uc32_t rhs);
UEXPORT int uz32n_cmp_uz32(const uc32_t *lhs, size_t lhs_len, const uc32_t *rhs);
UEXPORT int uz32n_cmp_uz32n(const uc32_t *lhs, size_t lhs_len, const uc32_t *rhs, size_t rhs_len);
UEXPORT int uz32n_cmp_ucv32(const uc32_t *lhs, size_t lhs_len, ucv32_t rhs);
UEXPORT int uz32n_cmp_uv32(const uc32_t *lhs, size_t lhs_len, uv32_t rhs);
UEXPORT int uz32n_cmp_us32(const uc32_t *lhs, size_t lhs_len, const us32_t *rhs);


#define uz16_cmp(lhs, rhs)              \
    _Generic((rhs),                     \
        default:        uz16_cmp_uc16,  \
        const uc16_t *: uz16_cmp_uz16,  \
        uc16_t *:       uz16_cmp_uz16,  \
        ucv16_t:        uz16_cmp_ucv16, \
        uv16_t:         uz16_cmp_uv16,  \
        const us16_t *: uz16_cmp_us16,  \
        us16_t *:       uz16_cmp_us16   \
    )((lhs), (rhs))

UEXPORT int uz16_cmp_uc16(const uc16_t *lhs, uc16_t rhs);
UEXPORT int uz16_cmp_uz16(const uc16_t *lhs, const uc16_t *rhs);
UEXPORT int uz16_cmp_uz16n(const uc16_t *lhs, const uc16_t *rhs, size_t rhs_len);
UEXPORT int uz16_cmp_ucv16(const uc16_t *lhs, ucv16_t rhs);
UEXPORT int uz16_cmp_uv16(const uc16_t *lhs, uv16_t rhs);
UEXPORT int uz16_cmp_us16(const uc16_t *lhs, const us16_t *rhs);

#define uz16n_cmp(lhs, lhs_len, rhs)     \
    _Generic((rhs),                      \
        default:  uz16n_cmp_uc16,        \
        const uc16_t *: uz16n_cmp_uz16,  \
        uc16_t *:       uz16n_cmp_uz16,  \
        ucv16_t:        uz16n_cmp_ucv16, \
        uv16_t:         uz16n_cmp_uv16,  \
        const us16_t *: uz16n_cmp_us16,  \
        us16_t *:       uz16n_cmp_us16   \
    )((lhs), (lhs_len), (rhs))

UEXPORT int uz16n_cmp_uc16(const uc16_t *lhs, size_t lhs_len, uc16_t rhs);
UEXPORT int uz16n_cmp_uz16(const uc16_t *lhs, size_t lhs_len, const uc16_t *rhs);
UEXPORT int uz16n_cmp_uz16n(const uc16_t *lhs, size_t lhs_len, const uc16_t *rhs, size_t rhs_len);
UEXPORT int uz16n_cmp_ucv16(const uc16_t *lhs, size_t lhs_len, ucv16_t rhs);
UEXPORT int uz16n_cmp_uv16(const uc16_t *lhs, size_t lhs_len, uv16_t rhs);
UEXPORT int uz16n_cmp_us16(const uc16_t *lhs, size_t lhs_len, const us16_t *rhs);


#define uz8_cmp(lhs, rhs)            \
    _Generic((rhs),                  \
        default:       uz8_cmp_uc8,  \
        const uc8_t *: uz8_cmp_uz8,  \
        uc8_t *:       uz8_cmp_uz8,  \
        ucv8_t:        uz8_cmp_ucv8, \
        uv8_t:         uz8_cmp_uv8,  \
        const us8_t *: uz8_cmp_us8,  \
        us8_t *:       uz8_cmp_us8   \
    )((lhs), (rhs))

UEXPORT int uz8_cmp_uc8(const uc8_t *lhs, uc8_t rhs);
UEXPORT int uz8_cmp_uz8(const uc8_t *lhs, const uc8_t *rhs);
UEXPORT int uz8_cmp_uz8n(const uc8_t *lhs, const uc8_t *rhs, size_t rhs_len);
UEXPORT int uz8_cmp_ucv8(const uc8_t *lhs, ucv8_t rhs);
UEXPORT int uz8_cmp_uv8(const uc8_t *lhs, uv8_t rhs);
UEXPORT int uz8_cmp_us8(const uc8_t *lhs, const us8_t *rhs);

#define uz8n_cmp(lhs, lhs_len, rhs)   \
    _Generic((rhs),                   \
        default:       uz8n_cmp_uc8,  \
        const uc8_t *: uz8n_cmp_uz8,  \
        uc8_t *:       uz8n_cmp_uz8,  \
        ucv8_t:        uz8n_cmp_ucv8, \
        uv8_t:         uz8n_cmp_uv8,  \
        const us8_t *: uz8n_cmp_us8,  \
        us8_t *:       uz8n_cmp_us8   \
    )((lhs), (lhs_len), (rhs))

UEXPORT int uz8n_cmp_uc8(const uc8_t *lhs, size_t lhs_len, uc8_t rhs);
UEXPORT int uz8n_cmp_uz8(const uc8_t *lhs, size_t lhs_len, const uc8_t *rhs);
UEXPORT int uz8n_cmp_uz8n(const uc8_t *lhs, size_t lhs_len, const uc8_t *rhs, size_t rhs_len);
UEXPORT int uz8n_cmp_ucv8(const uc8_t *lhs, size_t lhs_len, ucv8_t rhs);
UEXPORT int uz8n_cmp_uv8(const uc8_t *lhs, size_t lhs_len, uv8_t rhs);
UEXPORT int uz8n_cmp_us8(const uc8_t *lhs, size_t lhs_len, const us8_t *rhs);

// Fill

#define uz32_fill(cstr, with)           \
    _Generic((with),                    \
        default:        uz32_fill_uc32, \
        const uc32_t *: uz32_fill_uz32, \
        uc32_t *:       uz32_fill_uz32, \
        ucv32_t:        uz32_fill_ucv32,\
        uv32_t:         uz32_fill_uv32, \
        const us32_t *: uz32_fill_us32, \
        us32_t *:       uz32_fill_us32  \
    )((cstr), (with))

UEXPORT void uz32_fill_uc32(UINOUT uc32_t *cstr, uc32_t with);
UEXPORT void uz32_fill_uz32(UINOUT uc32_t *cstr, const uc32_t *with);
UEXPORT void uz32_fill_uz32n(UINOUT uc32_t *cstr, const uc32_t *with, size_t with_len);
UEXPORT void uz32_fill_ucv32(UINOUT uc32_t *cstr, ucv32_t with);
UEXPORT void uz32_fill_uv32(UINOUT uc32_t *cstr, uv32_t with);
UEXPORT void uz32_fill_us32(UINOUT uc32_t *cstr, const us32_t *with);

#define uz32n_fill(cstr, cstr_len, with)  \
    _Generic((with),                      \
        default:        uz32n_fill_uc32,  \
        const uc32_t *: uz32n_fill_uz32,  \
        uc32_t *:       uz32n_fill_uz32,  \
        ucv32_t:        uz32n_fill_ucv32, \
        uv32_t:         uz32n_fill_uv32,  \
        const us32_t *: uz32n_fill_us32,  \
        us32_t *:       uz32n_fill_us32   \
    )((cstr), (cstr_len), (with))

UEXPORT void uz32n_fill_uc32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t with);
UEXPORT void uz32n_fill_uz32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *with);
UEXPORT void uz32n_fill_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *with, size_t with_len);
UEXPORT void uz32n_fill_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t with);
UEXPORT void uz32n_fill_uv32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t with);
UEXPORT void uz32n_fill_us32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *with);


#define uz16_fill(cstr, with)            \
    _Generic((with),                     \
        default:        uz16_fill_uc16,  \
        const uc16_t *: uz16_fill_uz16,  \
        uc16_t *:       uz16_fill_uz16,  \
        ucv16_t:        uz16_fill_ucv16, \
        uv16_t:         uz16_fill_uv16,  \
        const us16_t *: uz16_fill_us16,  \
        us16_t *:       uz16_fill_us16   \
    )((cstr), (with))

UEXPORT void uz16_fill_uc16(UINOUT uc16_t *cstr, uc16_t with);
UEXPORT void uz16_fill_uz16(UINOUT uc16_t *cstr, const uc16_t *with);
UEXPORT void uz16_fill_uz16n(UINOUT uc16_t *cstr, const uc16_t *with, size_t with_len);
UEXPORT void uz16_fill_ucv16(UINOUT uc16_t *cstr, ucv16_t with);
UEXPORT void uz16_fill_uv16(UINOUT uc16_t *cstr, uv16_t with);
UEXPORT void uz16_fill_us16(UINOUT uc16_t *cstr, const us16_t *with);

#define uz16n_fill(cstr, cstr_len, with)  \
    _Generic((with),                      \
        default:        uz16n_fill_uc16,  \
        const uc16_t *: uz16n_fill_uz16,  \
        uc16_t *:       uz16n_fill_uz16,  \
        ucv16_t:        uz16n_fill_ucv16, \
        uv16_t:         uz16n_fill_uv16,  \
        const us16_t *: uz16n_fill_us16,  \
        us16_t *:       uz16n_fill_us16   \
    )((cstr), (cstr_len), (with))

UEXPORT void uz16n_fill_uc16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t with);
UEXPORT void uz16n_fill_uz16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *with);
UEXPORT void uz16n_fill_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *with, size_t with_len);
UEXPORT void uz16n_fill_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t with);
UEXPORT void uz16n_fill_uv16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t with);
UEXPORT void uz16n_fill_us16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *with);


#define uz8_fill(cstr, with)          \
    _Generic((with),                  \
        default:       uz8_fill_uc8,  \
        const uc8_t *: uz8_fill_uz8,  \
        uc8_t *:       uz8_fill_uz8,  \
        ucv8_t:        uz8_fill_ucv8, \
        uv8_t:         uz8_fill_uv8,  \
        const us8_t *: uz8_fill_us8,  \
        us8_t *:       uz8_fill_us8   \
    )((cstr), (with))

UEXPORT void uz8_fill_uc8(UINOUT uc8_t *cstr, uc8_t with);
UEXPORT void uz8_fill_uz8(UINOUT uc8_t *cstr, const uc8_t *with);
UEXPORT void uz8_fill_uz8n(UINOUT uc8_t *cstr, const uc8_t *with, size_t with_len);
UEXPORT void uz8_fill_ucv8(UINOUT uc8_t *cstr, ucv8_t with);
UEXPORT void uz8_fill_uv8(UINOUT uc8_t *cstr, uv8_t with);
UEXPORT void uz8_fill_us8(UINOUT uc8_t *cstr, const us8_t *with);

#define uz8n_fill(cstr, cstr_len, with) \
    _Generic((with),                    \
        default:       uz8n_fill_uc8,   \
        const uc8_t *: uz8n_fill_uz8,   \
        uc8_t *:       uz8n_fill_uz8,   \
        ucv8_t:        uz8n_fill_ucv8,  \
        uv8_t:         uz8n_fill_uv8,   \
        const us8_t *: uz8n_fill_us8,   \
        us8_t *:       uz8n_fill_us8    \
    )((cstr), (cstr_len), (with))

UEXPORT void uz8n_fill_uc8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t with);
UEXPORT void uz8n_fill_uz8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *with);
UEXPORT void uz8n_fill_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *with, size_t with_len);
UEXPORT void uz8n_fill_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t with);
UEXPORT void uz8n_fill_uv8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t with);
UEXPORT void uz8n_fill_us8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *with);

// Move

UEXPORT void uz32_move(UOUT uc32_t *to, const uc32_t *from, size_t n);
UEXPORT void uz16_move(UOUT uc16_t *to, const uc16_t *from, size_t n);
UEXPORT void uz8_move(UOUT uc8_t *to, const uc8_t *from, size_t n);

// White space

UEXPORT size_t uz32_wspace_len(const uc32_t *cstr);
UEXPORT size_t uz32n_wspace_len(const uc32_t *cstr, size_t cstr_len);

UEXPORT size_t uz16_wspace_len(const uc16_t *cstr);
UEXPORT size_t uz16n_wspace_len(const uc16_t *cstr, size_t cstr_len);

UEXPORT size_t uz8_wspace_len(const uc8_t *cstr);
UEXPORT size_t uz8n_wspace_len(const uc8_t *cstr, size_t cstr_len);

// Trim

UEXPORT size_t uz32_trim(uc32_t *cstr);
UEXPORT size_t uz32_ltrim(UINOUT uc32_t *cstr);
UEXPORT size_t uz32_rtrim(const uc32_t *cstr);

UEXPORT size_t uz32n_trim(uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32n_ltrim(UINOUT uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uz32n_rtrim(const uc32_t *cstr, size_t cstr_len);


UEXPORT size_t uz16_trim(uc16_t *cstr);
UEXPORT size_t uz16_ltrim(UINOUT uc16_t *cstr);
UEXPORT size_t uz16_rtrim(const uc16_t *cstr);

UEXPORT size_t uz16n_trim(uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16n_ltrim(UINOUT uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uz16n_rtrim(const uc16_t *cstr, size_t cstr_len);


UEXPORT size_t uz8_trim(uc8_t *cstr);
UEXPORT size_t uz8_ltrim(UINOUT uc8_t *cstr);
UEXPORT size_t uz8_rtrim(const uc8_t *cstr);

UEXPORT size_t uz8n_trim(uc8_t *cstr, size_t cstr_len);
UEXPORT size_t uz8n_ltrim(UINOUT uc8_t *cstr, size_t cstr_len);
UEXPORT size_t uz8n_rtrim(const uc8_t *cstr, size_t cstr_len);

// Case change

UEXPORT void uz32_to_case(UOUT uc32_t *to, const uc32_t *from, ucase_t ca);
UEXPORT void uz32_to_lower(UOUT uc32_t *to, const uc32_t *from);
UEXPORT void uz32_to_upper(UOUT uc32_t *to, const uc32_t *from);

UEXPORT void uz32n_to_case(UOUT uc32_t *to, const uc32_t *from, size_t from_len, ucase_t ca);
UEXPORT void uz32n_to_lower(UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT void uz32n_to_upper(UOUT uc32_t *to, const uc32_t *from, size_t from_len);



UEXPORT void uz16_to_case(UOUT uc16_t *to, const uc16_t *from, ucase_t ca);
UEXPORT void uz16_to_lower(UOUT uc16_t *to, const uc16_t *from);
UEXPORT void uz16_to_upper(UOUT uc16_t *to, const uc16_t *from);

UEXPORT void uz16n_to_case(UOUT uc16_t *to, const uc16_t *from, size_t from_len, ucase_t ca);
UEXPORT void uz16n_to_lower(UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT void uz16n_to_upper(UOUT uc16_t *to, const uc16_t *from, size_t from_len);



UEXPORT size_t uz8_to_case(UNULLABLE UOUT uc8_t *to, const uc8_t *from, ucase_t ca);
UEXPORT size_t uz8_to_case_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, ucase_t ca, bool *error);
UEXPORT size_t uz8_to_lower(UNULLABLE UOUT uc8_t *to, const uc8_t *from);
UEXPORT size_t uz8_to_lower_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, bool *error);
UEXPORT size_t uz8_to_upper(UNULLABLE UOUT uc8_t *to, const uc8_t *from);
UEXPORT size_t uz8_to_upper_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, bool *error);

UEXPORT size_t uz8n_to_case(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, ucase_t ca);
UEXPORT size_t uz8n_to_case_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, ucase_t ca, bool *error);
UEXPORT size_t uz8n_to_lower(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len);
UEXPORT size_t uz8n_to_lower_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, bool *error);
UEXPORT size_t uz8n_to_upper(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len);
UEXPORT size_t uz8n_to_upper_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, bool *error);


UEXPORT size_t uz8_to_case_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from, ucase_t ca);
UEXPORT size_t uz8_to_lower_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from);
UEXPORT size_t uz8_to_upper_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from);

UEXPORT size_t uz8n_to_case_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, ucase_t ca);
UEXPORT size_t uz8n_to_lower_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len);
UEXPORT size_t uz8n_to_upper_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len);

// Case change length

UEXPORT size_t uz8_case_len(const uc8_t *from, ucase_t ca);
UEXPORT size_t uz8_lower_len(const uc8_t *from);
UEXPORT size_t uz8_upper_len(const uc8_t *from);

UEXPORT size_t uz8n_case_len(const uc8_t *from, size_t from_len, ucase_t ca);
UEXPORT size_t uz8n_lower_len(const uc8_t *from, size_t from_len);
UEXPORT size_t uz8n_upper_len(const uc8_t *from, size_t from_len);

// Reverse

UEXPORT void uz32_reverse(uc32_t *cstr);
UEXPORT void uz32n_reverse(uc32_t *cstr, size_t cstr_len);

UEXPORT void uz16_reverse(uc16_t *cstr);
UEXPORT void uz16n_reverse(uc16_t *cstr, size_t cstr_len);

UEXPORT void uz8_reverse(uc8_t *cstr);
UEXPORT void uz8n_reverse(uc8_t *cstr, size_t cstr_len);

// Advance

UEXPORT uc32_t *uz32_advance(uc32_t *cstr, size_t n);
UEXPORT const uc32_t *uz32_cadvance(const uc32_t *cstr, size_t n);

UEXPORT uc16_t *uz16_advance(uc16_t *cstr, size_t n);
UEXPORT const uc16_t *uz16_cadvance(const uc16_t *cstr, size_t n);

UEXPORT uc8_t *uz8_advance(uc8_t *cstr, size_t n);
UEXPORT const uc8_t *uz8_cadvance(const uc8_t *cstr, size_t n);

// Retreat

UEXPORT uc32_t *uz32_retreat(uc32_t *cstr, size_t n);
UEXPORT const uc32_t *uz32_cretreat(const uc32_t *cstr, size_t n);

UEXPORT uc16_t *uz16_retreat(uc16_t *cstr, size_t n);
UEXPORT const uc16_t *uz16_cretreat(const uc16_t *cstr, size_t n);

UEXPORT uc8_t *uz8_retreat(uc8_t *cstr, size_t n);
UEXPORT const uc8_t *uz8_cretreat(const uc8_t *cstr, size_t n);

// Split

#define uz32_new_csplit(cstr, sep, array)           \
    uz32_new_csplit_e((cstr), (sep), (array), NULL)

#define uz32_new_csplit_e(cstr, sep, array, error) \
    _Generic((sep),                                \
        default:        uz32_new_csplit_uc32_e,    \
        const uc32_t *: uz32_new_csplit_uz32_e,    \
        uc32_t *:       uz32_new_csplit_uz32_e,    \
        ucv32_t:        uz32_new_csplit_ucv32_e,   \
        uv32_t:         uz32_new_csplit_uv32_e,    \
        const us32_t *: uz32_new_csplit_us32_e,    \
        us32_t *:       uz32_new_csplit_us32_e     \
    )((cstr), (sep), (array), (error))

#define uz32_csplit(cstr, sep, array, array_len) \
    _Generic((sep),                              \
        default:        uz32_csplit_uc32,        \
        const uc32_t *: uz32_csplit_uz32,        \
        uc32_t *:       uz32_csplit_uz32,        \
        ucv32_t:        uz32_csplit_ucv32,       \
        uv32_t:         uz32_csplit_uv32,        \
        const us32_t *: uz32_csplit_us32,        \
        us32_t *:       uz32_csplit_us32         \
    )((cstr), (sep), (array), (array_len))

UEXPORT size_t uz32_new_csplit_uc32(const uc32_t *cstr, uc32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32_new_csplit_uc32_e(const uc32_t *cstr, uc32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32_csplit_uc32(const uc32_t *cstr, uc32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uz32_new_csplit_uz32(const uc32_t *cstr, const uc32_t *sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32_new_csplit_uz32_e(const uc32_t *cstr, const uc32_t *sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32_csplit_uz32(const uc32_t *cstr, const uc32_t *sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uz32_new_csplit_uz32n(const uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32_new_csplit_uz32n_e(const uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32_csplit_uz32n(const uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uz32_new_csplit_ucv32(const uc32_t *cstr, ucv32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32_new_csplit_ucv32_e(const uc32_t *cstr, ucv32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32_csplit_ucv32(const uc32_t *cstr, ucv32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uz32_new_csplit_uv32(const uc32_t *cstr, uv32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32_new_csplit_uv32_e(const uc32_t *cstr, uv32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32_csplit_uv32(const uc32_t *cstr, uv32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uz32_new_csplit_us32(const uc32_t *cstr, const us32_t *sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32_new_csplit_us32_e(const uc32_t *cstr, const us32_t *sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32_csplit_us32(const uc32_t *cstr, const us32_t *sep, UNULLABLE ucv32_t *array, size_t array_len);


#define uz32_new_split(cstr, sep, array)           \
    uz32_new_split_e((cstr), (sep), (array), NULL)

#define uz32_new_split_e(cstr, sep, array, error)                  \
    uz32_new_csplit_e((cstr), (sep), (ucv32_t **) (array), (error))

#define uz32_split(cstr, sep, array, array_len)                  \
    uz32_csplit((cstr), (sep), (ucv32_t *) (array), (array_len))

UEXPORT size_t uz32_new_split_uc32(uc32_t *cstr, uc32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t uz32_new_split_uc32_e(uc32_t *cstr, uc32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32_split_uc32(uc32_t *cstr, uc32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uz32_new_split_uz32(uc32_t *cstr, const uc32_t *sep, UNULLABLE uv32_t **array);
UEXPORT size_t uz32_new_split_uz32_e(uc32_t *cstr, const uc32_t *sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32_split_uz32(uc32_t *cstr, const uc32_t *sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uz32_new_split_uz32n(uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array);
UEXPORT size_t uz32_new_split_uz32n_e(uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32_split_uz32n(uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uz32_new_split_ucv32(uc32_t *cstr, ucv32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t uz32_new_split_ucv32_e(uc32_t *cstr, ucv32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32_split_ucv32(uc32_t *cstr, ucv32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uz32_new_split_uv32(uc32_t *cstr, uv32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t uz32_new_split_uv32_e(uc32_t *cstr, uv32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32_split_uv32(uc32_t *cstr, uv32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uz32_new_split_us32(uc32_t *cstr, const us32_t *sep, UNULLABLE uv32_t **array);
UEXPORT size_t uz32_new_split_us32_e(uc32_t *cstr, const us32_t *sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32_split_us32(uc32_t *cstr, const us32_t *sep, UNULLABLE uv32_t *array, size_t array_len);



#define uz32n_new_csplit(cstr, cstr_len, sep, array)             \
    uz32n_new_csplit_e((cstr), (cstr_len), (sep), (array), NULL)

#define uz32n_new_csplit_e(cstr, cstr_len, sep, array, error) \
    _Generic((sep),                                           \
        default:        uz32n_new_csplit_uc32_e,              \
        const uc32_t *: uz32n_new_csplit_uz32_e,              \
        uc32_t *:       uz32n_new_csplit_uz32_e,              \
        ucv32_t:        uz32n_new_csplit_ucv32_e,             \
        uv32_t:         uz32n_new_csplit_uv32_e,              \
        const us32_t *: uz32n_new_csplit_us32_e,              \
        us32_t *:       uz32n_new_csplit_us32_e               \
    )((cstr), (cstr_len), (sep), (array), (error))

#define uz32n_csplit(cstr, cstr_len, sep, array, array_len) \
    _Generic((sep),                                         \
        default:        uz32n_csplit_uc32,                  \
        const uc32_t *: uz32n_csplit_uz32,                  \
        uc32_t *:       uz32n_csplit_uz32,                  \
        ucv32_t:        uz32n_csplit_ucv32,                 \
        uv32_t:         uz32n_csplit_uv32,                  \
        const us32_t *: uz32n_csplit_us32,                  \
        us32_t *:       uz32n_csplit_us32                   \
    )((cstr), (cstr_len), (sep), (array), (array_len))

UEXPORT size_t uz32n_new_csplit_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32n_new_csplit_uc32_e(const uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32n_csplit_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uz32n_new_csplit_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32n_new_csplit_uz32_e(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32n_csplit_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uz32n_new_csplit_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32n_new_csplit_uz32n_e(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32n_csplit_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uz32n_new_csplit_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32n_new_csplit_ucv32_e(const uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32n_csplit_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uz32n_new_csplit_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32n_new_csplit_uv32_e(const uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32n_csplit_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uz32n_new_csplit_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uz32n_new_csplit_us32_e(const uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uz32n_csplit_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE ucv32_t *array, size_t array_len);


#define uz32n_new_split(cstr, cstr_len, sep, array)             \
    uz32n_new_split_e((cstr), (cstr_len), (sep), (array), NULL)

#define uz32n_new_split_e(cstr, cstr_len, sep, array, error)                    \
    uz32n_new_csplit_e((cstr), (cstr_len), (sep), (ucv32_t **) (array), (error))

#define uz32n_split(cstr, cstr_len, sep, array, array_len)                    \
    uz32n_csplit((cstr), (cstr_len), (sep), (ucv32_t *) (array), (array_len))

UEXPORT size_t uz32n_new_split_uc32(uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t uz32n_new_split_uc32_e(uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32n_split_uc32(uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uz32n_new_split_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE uv32_t **array);
UEXPORT size_t uz32n_new_split_uz32_e(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32n_split_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uz32n_new_split_uz32n(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array);
UEXPORT size_t uz32n_new_split_uz32n_e(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32n_split_uz32n(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uz32n_new_split_ucv32(uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t uz32n_new_split_ucv32_e(uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32n_split_ucv32(uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uz32n_new_split_uv32(uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t uz32n_new_split_uv32_e(uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32n_split_uv32(uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uz32n_new_split_us32(uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE uv32_t **array);
UEXPORT size_t uz32n_new_split_us32_e(uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uz32n_split_us32(uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE uv32_t *array, size_t array_len);




#define uz16_new_csplit(cstr, sep, array)           \
    uz16_new_csplit_e((cstr), (sep), (array), NULL)

#define uz16_new_csplit_e(cstr, sep, array, error) \
    _Generic((sep),                                \
        default:        uz16_new_csplit_uc16_e,    \
        const uc16_t *: uz16_new_csplit_uz16_e,    \
        uc16_t *:       uz16_new_csplit_uz16_e,    \
        ucv16_t:        uz16_new_csplit_ucv16_e,   \
        uv16_t:         uz16_new_csplit_uv16_e,    \
        const us16_t *: uz16_new_csplit_us16_e,    \
        us16_t *:       uz16_new_csplit_us16_e     \
    )((cstr), (sep), (array), (error))

#define uz16_csplit(cstr, sep, array, array_len) \
    _Generic((sep),                              \
        default:        uz16_csplit_uc16,        \
        const uc16_t *: uz16_csplit_uz16,        \
        uc16_t *:       uz16_csplit_uz16,        \
        ucv16_t:        uz16_csplit_ucv16,       \
        uv16_t:         uz16_csplit_uv16,        \
        const us16_t *: uz16_csplit_us16,        \
        us16_t *:       uz16_csplit_us16         \
    )((cstr), (sep), (array), (array_len))

UEXPORT size_t uz16_new_csplit_uc16(const uc16_t *cstr, uc16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16_new_csplit_uc16_e(const uc16_t *cstr, uc16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16_csplit_uc16(const uc16_t *cstr, uc16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uz16_new_csplit_uz16(const uc16_t *cstr, const uc16_t *sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16_new_csplit_uz16_e(const uc16_t *cstr, const uc16_t *sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16_csplit_uz16(const uc16_t *cstr, const uc16_t *sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uz16_new_csplit_uz16n(const uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16_new_csplit_uz16n_e(const uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16_csplit_uz16n(const uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uz16_new_csplit_ucv16(const uc16_t *cstr, ucv16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16_new_csplit_ucv16_e(const uc16_t *cstr, ucv16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16_csplit_ucv16(const uc16_t *cstr, ucv16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uz16_new_csplit_uv16(const uc16_t *cstr, uv16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16_new_csplit_uv16_e(const uc16_t *cstr, uv16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16_csplit_uv16(const uc16_t *cstr, uv16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uz16_new_csplit_us16(const uc16_t *cstr, const us16_t *sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16_new_csplit_us16_e(const uc16_t *cstr, const us16_t *sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16_csplit_us16(const uc16_t *cstr, const us16_t *sep, UNULLABLE ucv16_t *array, size_t array_len);


#define uz16_new_split(cstr, sep, array)           \
    uz16_new_split_e((cstr), (sep), (array), NULL)

#define uz16_new_split_e(cstr, sep, array, error)                  \
    uz16_new_csplit_e((cstr), (sep), (ucv16_t **) (array), (error))

#define uz16_split(cstr, sep, array, array_len)                  \
    uz16_csplit((cstr), (sep), (ucv16_t *) (array), (array_len))

UEXPORT size_t uz16_new_split_uc16(uc16_t *cstr, uc16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t uz16_new_split_uc16_e(uc16_t *cstr, uc16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16_split_uc16(uc16_t *cstr, uc16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uz16_new_split_uz16(uc16_t *cstr, const uc16_t *sep, UNULLABLE uv16_t **array);
UEXPORT size_t uz16_new_split_uz16_e(uc16_t *cstr, const uc16_t *sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16_split_uz16(uc16_t *cstr, const uc16_t *sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uz16_new_split_uz16n(uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array);
UEXPORT size_t uz16_new_split_uz16n_e(uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16_split_uz16n(uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uz16_new_split_ucv16(uc16_t *cstr, ucv16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t uz16_new_split_ucv16_e(uc16_t *cstr, ucv16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16_split_ucv16(uc16_t *cstr, ucv16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uz16_new_split_uv16(uc16_t *cstr, uv16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t uz16_new_split_uv16_e(uc16_t *cstr, uv16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16_split_uv16(uc16_t *cstr, uv16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uz16_new_split_us16(uc16_t *cstr, const us16_t *sep, UNULLABLE uv16_t **array);
UEXPORT size_t uz16_new_split_us16_e(uc16_t *cstr, const us16_t *sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16_split_us16(uc16_t *cstr, const us16_t *sep, UNULLABLE uv16_t *array, size_t array_len);



#define uz16n_new_csplit(cstr, cstr_len, sep, array)             \
    uz16n_new_csplit_e((cstr), (cstr_len), (sep), (array), NULL)

#define uz16n_new_csplit_e(cstr, cstr_len, sep, array, error) \
    _Generic((sep),                                           \
        default:        uz16n_new_csplit_uc16_e,              \
        const uc16_t *: uz16n_new_csplit_uz16_e,              \
        uc16_t *:       uz16n_new_csplit_uz16_e,              \
        ucv16_t:        uz16n_new_csplit_ucv16_e,             \
        uv16_t:         uz16n_new_csplit_uv16_e,              \
        const us16_t *: uz16n_new_csplit_us16_e,              \
        us16_t *:       uz16n_new_csplit_us16_e               \
    )((cstr), (cstr_len), (sep), (array), (error))

#define uz16n_csplit(cstr, cstr_len, sep, array, array_len) \
    _Generic((sep),                                         \
        default:        uz16n_csplit_uc16,                  \
        const uc16_t *: uz16n_csplit_uz16,                  \
        uc16_t *:       uz16n_csplit_uz16,                  \
        ucv16_t:        uz16n_csplit_ucv16,                 \
        uv16_t:         uz16n_csplit_uv16,                  \
        const us16_t *: uz16n_csplit_us16,                  \
        us16_t *:       uz16n_csplit_us16                   \
    )((cstr), (cstr_len), (sep), (array), (array_len))

UEXPORT size_t uz16n_new_csplit_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16n_new_csplit_uc16_e(const uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16n_csplit_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uz16n_new_csplit_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16n_new_csplit_uz16_e(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16n_csplit_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uz16n_new_csplit_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16n_new_csplit_uz16n_e(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16n_csplit_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uz16n_new_csplit_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16n_new_csplit_ucv16_e(const uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16n_csplit_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uz16n_new_csplit_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16n_new_csplit_uv16_e(const uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16n_csplit_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uz16n_new_csplit_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uz16n_new_csplit_us16_e(const uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uz16n_csplit_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE ucv16_t *array, size_t array_len);


#define uz16n_new_split(cstr, cstr_len, sep, array)             \
    uz16n_new_split_e((cstr), (cstr_len), (sep), (array), NULL)

#define uz16n_new_split_e(cstr, cstr_len, sep, array, error)                    \
    uz16n_new_csplit_e((cstr), (cstr_len), (sep), (ucv16_t **) (array), (error))

#define uz16n_split(cstr, cstr_len, sep, array, array_len)                    \
    uz16n_csplit((cstr), (cstr_len), (sep), (ucv16_t *) (array), (array_len))

UEXPORT size_t uz16n_new_split_uc16(uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t uz16n_new_split_uc16_e(uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16n_split_uc16(uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uz16n_new_split_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE uv16_t **array);
UEXPORT size_t uz16n_new_split_uz16_e(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16n_split_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uz16n_new_split_uz16n(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array);
UEXPORT size_t uz16n_new_split_uz16n_e(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16n_split_uz16n(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uz16n_new_split_ucv16(uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t uz16n_new_split_ucv16_e(uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16n_split_ucv16(uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uz16n_new_split_uv16(uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t uz16n_new_split_uv16_e(uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16n_split_uv16(uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uz16n_new_split_us16(uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE uv16_t **array);
UEXPORT size_t uz16n_new_split_us16_e(uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uz16n_split_us16(uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE uv16_t *array, size_t array_len);




#define uz8_new_csplit(cstr, sep, array)           \
    uz8_new_csplit_e((cstr), (sep), (array), NULL)

#define uz8_new_csplit_e(cstr, sep, array, error) \
    _Generic((sep),                               \
        default:       uz8_new_csplit_uc8_e,      \
        const uc8_t *: uz8_new_csplit_uz8_e,      \
        uc8_t *:       uz8_new_csplit_uz8_e,      \
        ucv8_t:        uz8_new_csplit_ucv8_e,     \
        uv8_t:         uz8_new_csplit_uv8_e,      \
        const us8_t *: uz8_new_csplit_us8_e,      \
        us8_t *:       uz8_new_csplit_us8_e       \
    )((cstr), (sep), (array), (error))

#define uz8_csplit(cstr, sep, array, array_len) \
    _Generic((sep),                             \
        default:       uz8_csplit_uc8,          \
        const uc8_t *: uz8_csplit_uz8,          \
        uc8_t *:       uz8_csplit_uz8,          \
        ucv8_t:        uz8_csplit_ucv8,         \
        uv8_t:         uz8_csplit_uv8,          \
        const us8_t *: uz8_csplit_us8,          \
        us8_t *:       uz8_csplit_us8           \
    )((cstr), (sep), (array), (array_len))

UEXPORT size_t uz8_new_csplit_uc8(const uc8_t *cstr, uc8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8_new_csplit_uc8_e(const uc8_t *cstr, uc8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8_csplit_uc8(const uc8_t *cstr, uc8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uz8_new_csplit_uz8(const uc8_t *cstr, const uc8_t *sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8_new_csplit_uz8_e(const uc8_t *cstr, const uc8_t *sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8_csplit_uz8(const uc8_t *cstr, const uc8_t *sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uz8_new_csplit_uz8n(const uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8_new_csplit_uz8n_e(const uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8_csplit_uz8n(const uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uz8_new_csplit_ucv8(const uc8_t *cstr, ucv8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8_new_csplit_ucv8_e(const uc8_t *cstr, ucv8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8_csplit_ucv8(const uc8_t *cstr, ucv8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uz8_new_csplit_uv8(const uc8_t *cstr, uv8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8_new_csplit_uv8_e(const uc8_t *cstr, uv8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8_csplit_uv8(const uc8_t *cstr, uv8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uz8_new_csplit_us8(const uc8_t *cstr, const us8_t *sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8_new_csplit_us8_e(const uc8_t *cstr, const us8_t *sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8_csplit_us8(const uc8_t *cstr, const us8_t *sep, UNULLABLE ucv8_t *array, size_t array_len);


#define uz8_new_split(cstr, sep, array)           \
    uz8_new_split_e((cstr), (sep), (array), NULL)

#define uz8_new_split_e(cstr, sep, array, error)                 \
    uz8_new_csplit_e((cstr), (sep), (ucv8_t **) (array), (error))

#define uz8_split(cstr, sep, array, array_len)                 \
    uz8_csplit((cstr), (sep), (ucv8_t *) (array), (array_len))

UEXPORT size_t uz8_new_split_uc8(uc8_t *cstr, uc8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t uz8_new_split_uc8_e(uc8_t *cstr, uc8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8_split_uc8(uc8_t *cstr, uc8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uz8_new_split_uz8(uc8_t *cstr, const uc8_t *sep, UNULLABLE uv8_t **array);
UEXPORT size_t uz8_new_split_uz8_e(uc8_t *cstr, const uc8_t *sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8_split_uz8(uc8_t *cstr, const uc8_t *sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uz8_new_split_uz8n(uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array);
UEXPORT size_t uz8_new_split_uz8n_e(uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8_split_uz8n(uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uz8_new_split_ucv8(uc8_t *cstr, ucv8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t uz8_new_split_ucv8_e(uc8_t *cstr, ucv8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8_split_ucv8(uc8_t *cstr, ucv8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uz8_new_split_uv8(uc8_t *cstr, uv8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t uz8_new_split_uv8_e(uc8_t *cstr, uv8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8_split_uv8(uc8_t *cstr, uv8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uz8_new_split_us8(uc8_t *cstr, const us8_t *sep, UNULLABLE uv8_t **array);
UEXPORT size_t uz8_new_split_us8_e(uc8_t *cstr, const us8_t *sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8_split_us8(uc8_t *cstr, const us8_t *sep, UNULLABLE uv8_t *array, size_t array_len);



#define uz8n_new_csplit(cstr, cstr_len, sep, array)             \
    uz8n_new_csplit_e((cstr), (cstr_len), (sep), (array), NULL)

#define uz8n_new_csplit_e(cstr, cstr_len, sep, array, error) \
    _Generic((sep),                                          \
        default:       uz8n_new_csplit_uc8_e,                \
        const uc8_t *: uz8n_new_csplit_uz8_e,                \
        uc8_t *:       uz8n_new_csplit_uz8_e,                \
        ucv8_t:        uz8n_new_csplit_ucv8_e,               \
        uv8_t:         uz8n_new_csplit_uv8_e,                \
        const us8_t *: uz8n_new_csplit_us8_e,                \
        us8_t *:       uz8n_new_csplit_us8_e                 \
    )((cstr), (cstr_len), (sep), (array), (error))

#define uz8n_csplit(cstr, cstr_len, sep, array, array_len) \
    _Generic((sep),                                        \
        default:       uz8n_csplit_uc8,                    \
        const uc8_t *: uz8n_csplit_uz8,                    \
        uc8_t *:       uz8n_csplit_uz8,                    \
        ucv8_t:        uz8n_csplit_ucv8,                   \
        uv8_t:         uz8n_csplit_uv8,                    \
        const us8_t *: uz8n_csplit_us8,                    \
        us8_t *:       uz8n_csplit_us8                     \
    )((cstr), (cstr_len), (sep), (array), (array_len))

UEXPORT size_t uz8n_new_csplit_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8n_new_csplit_uc8_e(const uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8n_csplit_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uz8n_new_csplit_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8n_new_csplit_uz8_e(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8n_csplit_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uz8n_new_csplit_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8n_new_csplit_uz8n_e(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8n_csplit_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uz8n_new_csplit_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8n_new_csplit_ucv8_e(const uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8n_csplit_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uz8n_new_csplit_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8n_new_csplit_uv8_e(const uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8n_csplit_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uz8n_new_csplit_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uz8n_new_csplit_us8_e(const uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uz8n_csplit_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE ucv8_t *array, size_t array_len);


#define uz8n_new_split(cstr, cstr_len, sep, array)             \
    uz8n_new_split_e((cstr), (cstr_len), (sep), (array), NULL)

#define uz8n_new_split_e(cstr, cstr_len, sep, array, error)                   \
    uz8n_new_csplit_e((cstr), (cstr_len), (sep), (ucv8_t **) (array), (error))

#define uz8n_split(cstr, cstr_len, sep, array, array_len)                   \
    uz8n_csplit((cstr), (cstr_len), (sep), (ucv8_t *) (array), (array_len))

UEXPORT size_t uz8n_new_split_uc8(uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t uz8n_new_split_uc8_e(uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8n_split_uc8(uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uz8n_new_split_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE uv8_t **array);
UEXPORT size_t uz8n_new_split_uz8_e(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8n_split_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uz8n_new_split_uz8n(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array);
UEXPORT size_t uz8n_new_split_uz8n_e(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8n_split_uz8n(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uz8n_new_split_ucv8(uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t uz8n_new_split_ucv8_e(uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8n_split_ucv8(uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uz8n_new_split_uv8(uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t uz8n_new_split_uv8_e(uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8n_split_uv8(uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uz8n_new_split_us8(uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE uv8_t **array);
UEXPORT size_t uz8n_new_split_us8_e(uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uz8n_split_us8(uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE uv8_t *array, size_t array_len);

// Contains

#define uz32_contains(cstr, target)          \
    _Generic((target),                       \
        default:        uz32_contains_uc32,  \
        const uc32_t *: uz32_contains_uz32,  \
        uc32_t *:       uz32_contains_uz32,  \
        ucv32_t:        uz32_contains_ucv32, \
        uv32_t:         uz32_contains_uv32,  \
        const us32_t *: uz32_contains_us32,  \
        us32_t *:       uz32_contains_us32   \
    )((cstr), (target))

UEXPORT bool uz32_contains_uc32(const uc32_t *cstr, uc32_t target);
UEXPORT bool uz32_contains_uz32(const uc32_t *cstr, const uc32_t *target);
UEXPORT bool uz32_contains_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len);
UEXPORT bool uz32_contains_ucv32(const uc32_t *cstr, ucv32_t target);
UEXPORT bool uz32_contains_uv32(const uc32_t *cstr, uv32_t target);
UEXPORT bool uz32_contains_us32(const uc32_t *cstr, const us32_t *target);

#define uz32n_contains(cstr, cstr_len, target) \
    _Generic((target),                         \
        default:        uz32n_contains_uc32,   \
        const uc32_t *: uz32n_contains_uz32,   \
        uc32_t *:       uz32n_contains_uz32,   \
        ucv32_t:        uz32n_contains_ucv32,  \
        uv32_t:         uz32n_contains_uv32,   \
        const us32_t *: uz32n_contains_us32,   \
        us32_t *:       uz32n_contains_us32    \
    )((cstr), (cstr_len), (target))

UEXPORT bool uz32n_contains_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target);
UEXPORT bool uz32n_contains_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target);
UEXPORT bool uz32n_contains_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len);
UEXPORT bool uz32n_contains_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target);
UEXPORT bool uz32n_contains_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target);
UEXPORT bool uz32n_contains_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target);


#define uz16_contains(cstr, target)          \
    _Generic((target),                       \
        default:        uz16_contains_uc16,  \
        const uc16_t *: uz16_contains_uz16,  \
        uc16_t *:       uz16_contains_uz16,  \
        ucv16_t:        uz16_contains_ucv16, \
        uv16_t:         uz16_contains_uv16,  \
        const us16_t *: uz16_contains_us16,  \
        us16_t *:       uz16_contains_us16   \
    )((cstr), (target))

UEXPORT bool uz16_contains_uc16(const uc16_t *cstr, uc16_t target);
UEXPORT bool uz16_contains_uz16(const uc16_t *cstr, const uc16_t *target);
UEXPORT bool uz16_contains_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len);
UEXPORT bool uz16_contains_ucv16(const uc16_t *cstr, ucv16_t target);
UEXPORT bool uz16_contains_uv16(const uc16_t *cstr, uv16_t target);
UEXPORT bool uz16_contains_us16(const uc16_t *cstr, const us16_t *target);

#define uz16n_contains(cstr, cstr_len, target) \
    _Generic((target),                         \
        default:        uz16n_contains_uc16,   \
        const uc16_t *: uz16n_contains_uz16,   \
        uc16_t *:       uz16n_contains_uz16,   \
        ucv16_t:        uz16n_contains_ucv16,  \
        uv16_t:         uz16n_contains_uv16,   \
        const us16_t *: uz16n_contains_us16,   \
        us16_t *:       uz16n_contains_us16    \
    )((cstr), (cstr_len), (target))

UEXPORT bool uz16n_contains_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target);
UEXPORT bool uz16n_contains_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target);
UEXPORT bool uz16n_contains_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len);
UEXPORT bool uz16n_contains_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target);
UEXPORT bool uz16n_contains_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target);
UEXPORT bool uz16n_contains_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target);


#define uz8_contains(cstr, target)       \
    _Generic((target),                   \
        default:       uz8_contains_uc8, \
        const uc8_t *: uz8_contains_uz8, \
        uc8_t *:       uz8_contains_uz8, \
        ucv8_t:        uz8_contains_ucv8,\
        uv8_t:         uz8_contains_uv8, \
        const us8_t *: uz8_contains_us8, \
        us8_t *:       uz8_contains_us8  \
    )((cstr), (target))

UEXPORT bool uz8_contains_uc8(const uc8_t *cstr, uc8_t target);
UEXPORT bool uz8_contains_uz8(const uc8_t *cstr, const uc8_t *target);
UEXPORT bool uz8_contains_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len);
UEXPORT bool uz8_contains_ucv8(const uc8_t *cstr, ucv8_t target);
UEXPORT bool uz8_contains_uv8(const uc8_t *cstr, uv8_t target);
UEXPORT bool uz8_contains_us8(const uc8_t *cstr, const us8_t *target);

#define uz8n_contains(cstr, cstr_len, target) \
    _Generic((target),                        \
        default:       uz8n_contains_uc8,     \
        const uc8_t *: uz8n_contains_uz8,     \
        uc8_t *:       uz8n_contains_uz8,     \
        ucv8_t:        uz8n_contains_ucv8,    \
        uv8_t:         uz8n_contains_uv8,     \
        const us8_t *: uz8n_contains_us8,     \
        us8_t *:       uz8n_contains_us8      \
    )((cstr), (cstr_len), (target))

UEXPORT bool uz8n_contains_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target);
UEXPORT bool uz8n_contains_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target);
UEXPORT bool uz8n_contains_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len);
UEXPORT bool uz8n_contains_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target);
UEXPORT bool uz8n_contains_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target);
UEXPORT bool uz8n_contains_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target);

// Search

// - Forward

#define uz32_find(cstr, target)          \
    _Generic((target),                   \
        default:        uz32_find_uc32,  \
        const uc32_t *: uz32_find_uz32,  \
        uc32_t *:       uz32_find_uz32,  \
        ucv32_t:        uz32_find_ucv32, \
        uv32_t:         uz32_find_uv32,  \
        const us32_t *: uz32_find_us32,  \
        us32_t *:       uz32_find_us32   \
    )((cstr), (target))

#define uz32_find_from(cstr, target, from)    \
    _Generic((target),                        \
        default:        uz32_find_uc32_from,  \
        const uc32_t *: uz32_find_uz32_from,  \
        uc32_t *:       uz32_find_uz32_from,  \
        ucv32_t:        uz32_find_ucv32_from, \
        uv32_t:         uz32_find_uv32_from,  \
        const us32_t *: uz32_find_us32_from,  \
        us32_t *:       uz32_find_us32_from   \
    )((cstr), (target), (from))

UEXPORT ptrdiff_t uz32_find_uc32(const uc32_t *cstr, uc32_t target);
UEXPORT ptrdiff_t uz32_find_uc32_from(const uc32_t *cstr, uc32_t target, size_t from);
UEXPORT ptrdiff_t uz32_find_uz32(const uc32_t *cstr, const uc32_t *target);
UEXPORT ptrdiff_t uz32_find_uz32_from(const uc32_t *cstr, const uc32_t *target, size_t from);
UEXPORT ptrdiff_t uz32_find_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len);
UEXPORT ptrdiff_t uz32_find_uz32n_from(const uc32_t *cstr, const uc32_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz32_find_ucv32(const uc32_t *cstr, ucv32_t target);
UEXPORT ptrdiff_t uz32_find_ucv32_from(const uc32_t *cstr, ucv32_t target, size_t from);
UEXPORT ptrdiff_t uz32_find_uv32(const uc32_t *cstr, uv32_t target);
UEXPORT ptrdiff_t uz32_find_uv32_from(const uc32_t *cstr, uv32_t target, size_t from);
UEXPORT ptrdiff_t uz32_find_us32(const uc32_t *cstr, const us32_t *target);
UEXPORT ptrdiff_t uz32_find_us32_from(const uc32_t *cstr, const us32_t *target, size_t from);

#define uz32n_find(cstr, cstr_len, target) \
    _Generic((target),                     \
        default:        uz32n_find_uc32,   \
        const uc32_t *: uz32n_find_uz32,   \
        uc32_t *:       uz32n_find_uz32,   \
        ucv32_t:        uz32n_find_ucv32,  \
        uv32_t:         uz32n_find_uv32,   \
        const us32_t *: uz32n_find_us32,   \
        us32_t *:       uz32n_find_us32    \
    )((cstr), (cstr_len), (target))

#define uz32n_find_from(cstr, cstr_len, target, from) \
    _Generic((target),                                \
        default:        uz32n_find_uc32_from,         \
        const uc32_t *: uz32n_find_uz32_from,         \
        uc32_t *:       uz32n_find_uz32_from,         \
        ucv32_t:        uz32n_find_ucv32_from,        \
        uv32_t:         uz32n_find_uv32_from,         \
        const us32_t *: uz32n_find_us32_from,         \
        us32_t *:       uz32n_find_us32_from          \
    )((cstr), (cstr_len), (target), (from))

UEXPORT ptrdiff_t uz32n_find_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target);
UEXPORT ptrdiff_t uz32n_find_uc32_from(const uc32_t *cstr, size_t cstr_len, uc32_t target, size_t from);
UEXPORT ptrdiff_t uz32n_find_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target);
UEXPORT ptrdiff_t uz32n_find_uz32_from(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t from);
UEXPORT ptrdiff_t uz32n_find_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len);
UEXPORT ptrdiff_t uz32n_find_uz32n_from(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz32n_find_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target);
UEXPORT ptrdiff_t uz32n_find_ucv32_from(const uc32_t *cstr, size_t cstr_len, ucv32_t target, size_t from);
UEXPORT ptrdiff_t uz32n_find_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target);
UEXPORT ptrdiff_t uz32n_find_uv32_from(const uc32_t *cstr, size_t cstr_len, uv32_t target, size_t from);
UEXPORT ptrdiff_t uz32n_find_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target);
UEXPORT ptrdiff_t uz32n_find_us32_from(const uc32_t *cstr, size_t cstr_len, const us32_t *target, size_t from);


#define uz16_find(cstr, target)          \
    _Generic((target),                   \
        default:        uz16_find_uc16,  \
        const uc16_t *: uz16_find_uz16,  \
        uc16_t *:       uz16_find_uz16,  \
        ucv16_t:        uz16_find_ucv16, \
        uv16_t:         uz16_find_uv16,  \
        const us16_t *: uz16_find_us16,  \
        us16_t *:       uz16_find_us16   \
    )((cstr), (target))

#define uz16_find_from(cstr, target, from)    \
    _Generic((target),                        \
        default:        uz16_find_uc16_from,  \
        const uc16_t *: uz16_find_uz16_from,  \
        uc16_t *:       uz16_find_uz16_from,  \
        ucv16_t:        uz16_find_ucv16_from, \
        uv16_t:         uz16_find_uv16_from,  \
        const us16_t *: uz16_find_us16_from,  \
        us16_t *:       uz16_find_us16_from   \
    )((cstr), (target), (from))

UEXPORT ptrdiff_t uz16_find_uc16(const uc16_t *cstr, uc16_t target);
UEXPORT ptrdiff_t uz16_find_uc16_from(const uc16_t *cstr, uc16_t target, size_t from);
UEXPORT ptrdiff_t uz16_find_uz16(const uc16_t *cstr, const uc16_t *target);
UEXPORT ptrdiff_t uz16_find_uz16_from(const uc16_t *cstr, const uc16_t *target, size_t from);
UEXPORT ptrdiff_t uz16_find_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len);
UEXPORT ptrdiff_t uz16_find_uz16n_from(const uc16_t *cstr, const uc16_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz16_find_ucv16(const uc16_t *cstr, ucv16_t target);
UEXPORT ptrdiff_t uz16_find_ucv16_from(const uc16_t *cstr, ucv16_t target, size_t from);
UEXPORT ptrdiff_t uz16_find_uv16(const uc16_t *cstr, uv16_t target);
UEXPORT ptrdiff_t uz16_find_uv16_from(const uc16_t *cstr, uv16_t target, size_t from);
UEXPORT ptrdiff_t uz16_find_us16(const uc16_t *cstr, const us16_t *target);
UEXPORT ptrdiff_t uz16_find_us16_from(const uc16_t *cstr, const us16_t *target, size_t from);

#define uz16n_find(cstr, cstr_len, target) \
    _Generic((target),                     \
        default:        uz16n_find_uc16,   \
        const uc16_t *: uz16n_find_uz16,   \
        uc16_t *:       uz16n_find_uz16,   \
        ucv16_t:        uz16n_find_ucv16,  \
        uv16_t:         uz16n_find_uv16,   \
        const us16_t *: uz16n_find_us16,   \
        us16_t *:       uz16n_find_us16    \
    )((cstr), (cstr_len), (target))

#define uz16n_find_from(cstr, cstr_len, target, from) \
    _Generic((target),                                \
        default:        uz16n_find_uc16_from,         \
        const uc16_t *: uz16n_find_uz16_from,         \
        uc16_t *:       uz16n_find_uz16_from,         \
        ucv16_t:        uz16n_find_ucv16_from,        \
        uv16_t:         uz16n_find_uv16_from,         \
        const us16_t *: uz16n_find_us16_from,         \
        us16_t *:       uz16n_find_us16_from          \
    )((cstr), (cstr_len), (target), (from))

UEXPORT ptrdiff_t uz16n_find_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target);
UEXPORT ptrdiff_t uz16n_find_uc16_from(const uc16_t *cstr, size_t cstr_len, uc16_t target, size_t from);
UEXPORT ptrdiff_t uz16n_find_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target);
UEXPORT ptrdiff_t uz16n_find_uz16_from(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t from);
UEXPORT ptrdiff_t uz16n_find_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len);
UEXPORT ptrdiff_t uz16n_find_uz16n_from(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz16n_find_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target);
UEXPORT ptrdiff_t uz16n_find_ucv16_from(const uc16_t *cstr, size_t cstr_len, ucv16_t target, size_t from);
UEXPORT ptrdiff_t uz16n_find_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target);
UEXPORT ptrdiff_t uz16n_find_uv16_from(const uc16_t *cstr, size_t cstr_len, uv16_t target, size_t from);
UEXPORT ptrdiff_t uz16n_find_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target);
UEXPORT ptrdiff_t uz16n_find_us16_from(const uc16_t *cstr, size_t cstr_len, const us16_t *target, size_t from);


#define uz8_find(cstr, target)        \
    _Generic((target),                \
        default:       uz8_find_uc8,  \
        const uc8_t *: uz8_find_uz8,  \
        uc8_t *:       uz8_find_uz8,  \
        ucv8_t:        uz8_find_ucv8, \
        uv8_t:         uz8_find_uv8,  \
        const us8_t *: uz8_find_us8,  \
        us8_t *:       uz8_find_us8   \
    )((cstr), (target))

#define uz8_find_from(cstr, target, from)  \
    _Generic((target),                     \
        default:       uz8_find_uc8_from,  \
        const uc8_t *: uz8_find_uz8_from,  \
        uc8_t *:       uz8_find_uz8_from,  \
        ucv8_t:        uz8_find_ucv8_from, \
        uv8_t:         uz8_find_uv8_from,  \
        const us8_t *: uz8_find_us8_from,  \
        us8_t *:       uz8_find_us8_from   \
    )((cstr), (target), (from))

UEXPORT ptrdiff_t uz8_find_uc8(const uc8_t *cstr, uc8_t target);
UEXPORT ptrdiff_t uz8_find_uc8_from(const uc8_t *cstr, uc8_t target, size_t from);
UEXPORT ptrdiff_t uz8_find_uz8(const uc8_t *cstr, const uc8_t *target);
UEXPORT ptrdiff_t uz8_find_uz8_from(const uc8_t *cstr, const uc8_t *target, size_t from);
UEXPORT ptrdiff_t uz8_find_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len);
UEXPORT ptrdiff_t uz8_find_uz8n_from(const uc8_t *cstr, const uc8_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz8_find_ucv8(const uc8_t *cstr, ucv8_t target);
UEXPORT ptrdiff_t uz8_find_ucv8_from(const uc8_t *cstr, ucv8_t target, size_t from);
UEXPORT ptrdiff_t uz8_find_uv8(const uc8_t *cstr, uv8_t target);
UEXPORT ptrdiff_t uz8_find_uv8_from(const uc8_t *cstr, uv8_t target, size_t from);
UEXPORT ptrdiff_t uz8_find_us8(const uc8_t *cstr, const us8_t *target);
UEXPORT ptrdiff_t uz8_find_us8_from(const uc8_t *cstr, const us8_t *target, size_t from);

#define uz8n_find(cstr, cstr_len, target) \
    _Generic((target),                    \
        default:       uz8n_find_uc8,     \
        const uc8_t *: uz8n_find_uz8,     \
        uc8_t *:       uz8n_find_uz8,     \
        ucv8_t:        uz8n_find_ucv8,    \
        uv8_t:         uz8n_find_uv8,     \
        const us8_t *: uz8n_find_us8,     \
        us8_t *:       uz8n_find_us8      \
    )((cstr), (cstr_len), (target))

#define uz8n_find_from(cstr, cstr_len, target, from) \
    _Generic((target),                               \
        default:       uz8n_find_uc8_from,           \
        const uc8_t *: uz8n_find_uz8_from,           \
        uc8_t *:       uz8n_find_uz8_from,           \
        ucv8_t:        uz8n_find_ucv8_from,          \
        uv8_t:         uz8n_find_uv8_from,           \
        const us8_t *: uz8n_find_us8_from,           \
        us8_t *:       uz8n_find_us8_from            \
    )((cstr), (cstr_len), (target), (from))

UEXPORT ptrdiff_t uz8n_find_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target);
UEXPORT ptrdiff_t uz8n_find_uc8_from(const uc8_t *cstr, size_t cstr_len, uc8_t target, size_t from);
UEXPORT ptrdiff_t uz8n_find_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target);
UEXPORT ptrdiff_t uz8n_find_uz8_from(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t from);
UEXPORT ptrdiff_t uz8n_find_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len);
UEXPORT ptrdiff_t uz8n_find_uz8n_from(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz8n_find_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target);
UEXPORT ptrdiff_t uz8n_find_ucv8_from(const uc8_t *cstr, size_t cstr_len, ucv8_t target, size_t from);
UEXPORT ptrdiff_t uz8n_find_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target);
UEXPORT ptrdiff_t uz8n_find_uv8_from(const uc8_t *cstr, size_t cstr_len, uv8_t target, size_t from);
UEXPORT ptrdiff_t uz8n_find_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target);
UEXPORT ptrdiff_t uz8n_find_us8_from(const uc8_t *cstr, size_t cstr_len, const us8_t *target, size_t from);

// - Backward

#define uz32_rfind(cstr, target)          \
    _Generic((target),                    \
        default:        uz32_rfind_uc32,  \
        const uc32_t *: uz32_rfind_uz32,  \
        uc32_t *:       uz32_rfind_uz32,  \
        ucv32_t:        uz32_rfind_ucv32, \
        uv32_t:         uz32_rfind_uv32,  \
        const us32_t *: uz32_rfind_us32,  \
        us32_t *:       uz32_rfind_us32   \
    )((cstr), (target))

#define uz32_rfind_from(cstr, target, from)    \
    _Generic((target),                         \
        default:        uz32_rfind_uc32_from,  \
        const uc32_t *: uz32_rfind_uz32_from,  \
        uc32_t *:       uz32_rfind_uz32_from,  \
        ucv32_t:        uz32_rfind_ucv32_from, \
        uv32_t:         uz32_rfind_uv32_from,  \
        const us32_t *: uz32_rfind_us32_from,  \
        us32_t *:       uz32_rfind_us32_from   \
    )((cstr), (target), (from))

UEXPORT ptrdiff_t uz32_rfind_uc32(const uc32_t *cstr, uc32_t target);
UEXPORT ptrdiff_t uz32_rfind_uc32_from(const uc32_t *cstr, uc32_t target, size_t from);
UEXPORT ptrdiff_t uz32_rfind_uz32(const uc32_t *cstr, const uc32_t *target);
UEXPORT ptrdiff_t uz32_rfind_uz32_from(const uc32_t *cstr, const uc32_t *target, size_t from);
UEXPORT ptrdiff_t uz32_rfind_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len);
UEXPORT ptrdiff_t uz32_rfind_uz32n_from(const uc32_t *cstr, const uc32_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz32_rfind_ucv32(const uc32_t *cstr, ucv32_t target);
UEXPORT ptrdiff_t uz32_rfind_ucv32_from(const uc32_t *cstr, ucv32_t target, size_t from);
UEXPORT ptrdiff_t uz32_rfind_uv32(const uc32_t *cstr, uv32_t target);
UEXPORT ptrdiff_t uz32_rfind_uv32_from(const uc32_t *cstr, uv32_t target, size_t from);
UEXPORT ptrdiff_t uz32_rfind_us32(const uc32_t *cstr, const us32_t *target);
UEXPORT ptrdiff_t uz32_rfind_us32_from(const uc32_t *cstr, const us32_t *target, size_t from);

#define uz32n_rfind(cstr, cstr_len, target) \
    _Generic((target),                      \
        default:        uz32n_rfind_uc32,   \
        const uc32_t *: uz32n_rfind_uz32,   \
        uc32_t *:       uz32n_rfind_uz32,   \
        ucv32_t:        uz32n_rfind_ucv32,  \
        uv32_t:         uz32n_rfind_uv32,   \
        const us32_t *: uz32n_rfind_us32,   \
        us32_t *:       uz32n_rfind_us32    \
    )((cstr), (cstr_len), (target))

#define uz32n_rfind_from(cstr, cstr_len, target, from) \
    _Generic((target),                                 \
        default:        uz32n_rfind_uc32_from,         \
        const uc32_t *: uz32n_rfind_uz32_from,         \
        uc32_t *:       uz32n_rfind_uz32_from,         \
        ucv32_t:        uz32n_rfind_ucv32_from,        \
        uv32_t:         uz32n_rfind_uv32_from,         \
        const us32_t *: uz32n_rfind_us32_from,         \
        us32_t *:       uz32n_rfind_us32_from          \
    )((cstr), (cstr_len), (target), (from))

UEXPORT ptrdiff_t uz32n_rfind_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target);
UEXPORT ptrdiff_t uz32n_rfind_uc32_from(const uc32_t *cstr, size_t cstr_len, uc32_t target, size_t from);
UEXPORT ptrdiff_t uz32n_rfind_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target);
UEXPORT ptrdiff_t uz32n_rfind_uz32_from(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t from);
UEXPORT ptrdiff_t uz32n_rfind_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len);
UEXPORT ptrdiff_t uz32n_rfind_uz32n_from(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz32n_rfind_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target);
UEXPORT ptrdiff_t uz32n_rfind_ucv32_from(const uc32_t *cstr, size_t cstr_len, ucv32_t target, size_t from);
UEXPORT ptrdiff_t uz32n_rfind_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target);
UEXPORT ptrdiff_t uz32n_rfind_uv32_from(const uc32_t *cstr, size_t cstr_len, uv32_t target, size_t from);
UEXPORT ptrdiff_t uz32n_rfind_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target);
UEXPORT ptrdiff_t uz32n_rfind_us32_from(const uc32_t *cstr, size_t cstr_len, const us32_t *target, size_t from);


#define uz16_rfind(cstr, target)          \
    _Generic((target),                    \
        default:        uz16_rfind_uc16,  \
        const uc16_t *: uz16_rfind_uz16,  \
        uc16_t *:       uz16_rfind_uz16,  \
        ucv16_t:        uz16_rfind_ucv16, \
        uv16_t:         uz16_rfind_uv16,  \
        const us16_t *: uz16_rfind_us16,  \
        us16_t *:       uz16_rfind_us16   \
    )((cstr), (target))

#define uz16_rfind_from(cstr, target, from)    \
    _Generic((target),                         \
        default:        uz16_rfind_uc16_from,  \
        const uc16_t *: uz16_rfind_uz16_from,  \
        uc16_t *:       uz16_rfind_uz16_from,  \
        ucv16_t:        uz16_rfind_ucv16_from, \
        uv16_t:         uz16_rfind_uv16_from,  \
        const us16_t *: uz16_rfind_us16_from,  \
        us16_t *:       uz16_rfind_us16_from   \
    )((cstr), (target), (from))

UEXPORT ptrdiff_t uz16_rfind_uc16(const uc16_t *cstr, uc16_t target);
UEXPORT ptrdiff_t uz16_rfind_uc16_from(const uc16_t *cstr, uc16_t target, size_t from);
UEXPORT ptrdiff_t uz16_rfind_uz16(const uc16_t *cstr, const uc16_t *target);
UEXPORT ptrdiff_t uz16_rfind_uz16_from(const uc16_t *cstr, const uc16_t *target, size_t from);
UEXPORT ptrdiff_t uz16_rfind_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len);
UEXPORT ptrdiff_t uz16_rfind_uz16n_from(const uc16_t *cstr, const uc16_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz16_rfind_ucv16(const uc16_t *cstr, ucv16_t target);
UEXPORT ptrdiff_t uz16_rfind_ucv16_from(const uc16_t *cstr, ucv16_t target, size_t from);
UEXPORT ptrdiff_t uz16_rfind_uv16(const uc16_t *cstr, uv16_t target);
UEXPORT ptrdiff_t uz16_rfind_uv16_from(const uc16_t *cstr, uv16_t target, size_t from);
UEXPORT ptrdiff_t uz16_rfind_us16(const uc16_t *cstr, const us16_t *target);
UEXPORT ptrdiff_t uz16_rfind_us16_from(const uc16_t *cstr, const us16_t *target, size_t from);

#define uz16n_rfind(cstr, cstr_len, target) \
    _Generic((target),                      \
        default:        uz16n_rfind_uc16,   \
        const uc16_t *: uz16n_rfind_uz16,   \
        uc16_t *:       uz16n_rfind_uz16,   \
        ucv16_t:        uz16n_rfind_ucv16,  \
        uv16_t:         uz16n_rfind_uv16,   \
        const us16_t *: uz16n_rfind_us16,   \
        us16_t *:       uz16n_rfind_us16    \
    )((cstr), (cstr_len), (target))

#define uz16n_rfind_from(cstr, cstr_len, target, from) \
    _Generic((target),                                 \
        default:        uz16n_rfind_uc16_from,         \
        const uc16_t *: uz16n_rfind_uz16_from,         \
        uc16_t *:       uz16n_rfind_uz16_from,         \
        ucv16_t:        uz16n_rfind_ucv16_from,        \
        uv16_t:         uz16n_rfind_uv16_from,         \
        const us16_t *: uz16n_rfind_us16_from,         \
        us16_t *:       uz16n_rfind_us16_from          \
    )((cstr), (cstr_len), (target), (from))

UEXPORT ptrdiff_t uz16n_rfind_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target);
UEXPORT ptrdiff_t uz16n_rfind_uc16_from(const uc16_t *cstr, size_t cstr_len, uc16_t target, size_t from);
UEXPORT ptrdiff_t uz16n_rfind_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target);
UEXPORT ptrdiff_t uz16n_rfind_uz16_from(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t from);
UEXPORT ptrdiff_t uz16n_rfind_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len);
UEXPORT ptrdiff_t uz16n_rfind_uz16n_from(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz16n_rfind_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target);
UEXPORT ptrdiff_t uz16n_rfind_ucv16_from(const uc16_t *cstr, size_t cstr_len, ucv16_t target, size_t from);
UEXPORT ptrdiff_t uz16n_rfind_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target);
UEXPORT ptrdiff_t uz16n_rfind_uv16_from(const uc16_t *cstr, size_t cstr_len, uv16_t target, size_t from);
UEXPORT ptrdiff_t uz16n_rfind_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target);
UEXPORT ptrdiff_t uz16n_rfind_us16_from(const uc16_t *cstr, size_t cstr_len, const us16_t *target, size_t from);


#define uz8_rfind(cstr, target)        \
    _Generic((target),                 \
        default:       uz8_rfind_uc8,  \
        const uc8_t *: uz8_rfind_uz8,  \
        uc8_t *:       uz8_rfind_uz8,  \
        ucv8_t:        uz8_rfind_ucv8, \
        uv8_t:         uz8_rfind_uv8,  \
        const us8_t *: uz8_rfind_us8,  \
        us8_t *:       uz8_rfind_us8   \
    )((cstr), (target))

#define uz8_rfind_from(cstr, target, from)  \
    _Generic((target),                      \
        default:       uz8_rfind_uc8_from,  \
        const uc8_t *: uz8_rfind_uz8_from,  \
        uc8_t *:       uz8_rfind_uz8_from,  \
        ucv8_t:        uz8_rfind_ucv8_from, \
        uv8_t:         uz8_rfind_uv8_from,  \
        const us8_t *: uz8_rfind_us8_from,  \
        us8_t *:       uz8_rfind_us8_from   \
    )((cstr), (target), (from))

UEXPORT ptrdiff_t uz8_rfind_uc8(const uc8_t *cstr, uc8_t target);
UEXPORT ptrdiff_t uz8_rfind_uc8_from(const uc8_t *cstr, uc8_t target, size_t from);
UEXPORT ptrdiff_t uz8_rfind_uz8(const uc8_t *cstr, const uc8_t *target);
UEXPORT ptrdiff_t uz8_rfind_uz8_from(const uc8_t *cstr, const uc8_t *target, size_t from);
UEXPORT ptrdiff_t uz8_rfind_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len);
UEXPORT ptrdiff_t uz8_rfind_uz8n_from(const uc8_t *cstr, const uc8_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz8_rfind_ucv8(const uc8_t *cstr, ucv8_t target);
UEXPORT ptrdiff_t uz8_rfind_ucv8_from(const uc8_t *cstr, ucv8_t target, size_t from);
UEXPORT ptrdiff_t uz8_rfind_uv8(const uc8_t *cstr, uv8_t target);
UEXPORT ptrdiff_t uz8_rfind_uv8_from(const uc8_t *cstr, uv8_t target, size_t from);
UEXPORT ptrdiff_t uz8_rfind_us8(const uc8_t *cstr, const us8_t *target);
UEXPORT ptrdiff_t uz8_rfind_us8_from(const uc8_t *cstr, const us8_t *target, size_t from);

#define uz8n_rfind(cstr, cstr_len, target) \
    _Generic((target),                     \
        default:       uz8n_rfind_uc8,     \
        const uc8_t *: uz8n_rfind_uz8,     \
        uc8_t *:       uz8n_rfind_uz8,     \
        ucv8_t:        uz8n_rfind_ucv8,    \
        uv8_t:         uz8n_rfind_uv8,     \
        const us8_t *: uz8n_rfind_us8,     \
        us8_t *:       uz8n_rfind_us8      \
    )((cstr), (cstr_len), (target))

#define uz8n_rfind_from(cstr, cstr_len, target, from) \
    _Generic((target),                                \
        default:       uz8n_rfind_uc8_from,           \
        const uc8_t *: uz8n_rfind_uz8_from,           \
        uc8_t *:       uz8n_rfind_uz8_from,           \
        ucv8_t:        uz8n_rfind_ucv8_from,          \
        uv8_t:         uz8n_rfind_uv8_from,           \
        const us8_t *: uz8n_rfind_us8_from,           \
        us8_t *:       uz8n_rfind_us8_from            \
    )((cstr), (cstr_len), (target), (from))

UEXPORT ptrdiff_t uz8n_rfind_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target);
UEXPORT ptrdiff_t uz8n_rfind_uc8_from(const uc8_t *cstr, size_t cstr_len, uc8_t target, size_t from);
UEXPORT ptrdiff_t uz8n_rfind_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target);
UEXPORT ptrdiff_t uz8n_rfind_uz8_from(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t from);
UEXPORT ptrdiff_t uz8n_rfind_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len);
UEXPORT ptrdiff_t uz8n_rfind_uz8n_from(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uz8n_rfind_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target);
UEXPORT ptrdiff_t uz8n_rfind_ucv8_from(const uc8_t *cstr, size_t cstr_len, ucv8_t target, size_t from);
UEXPORT ptrdiff_t uz8n_rfind_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target);
UEXPORT ptrdiff_t uz8n_rfind_uv8_from(const uc8_t *cstr, size_t cstr_len, uv8_t target, size_t from);
UEXPORT ptrdiff_t uz8n_rfind_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target);
UEXPORT ptrdiff_t uz8n_rfind_us8_from(const uc8_t *cstr, size_t cstr_len, const us8_t *target, size_t from);

// Erase

#define uz32_erase(cstr, target)    \
    _Generic((target),              \
        default:  uz32_erase_uc32,  \
        uc32_t *: uz32_erase_uz32,  \
        ucv32_t:  uz32_erase_ucv32, \
        uv32_t:   uz32_erase_uv32,  \
        us32_t *: uz32_erase_us32   \
    )((cstr), (target))

UEXPORT size_t uz32_erase_uc32(UINOUT uc32_t *cstr, uc32_t target);
UEXPORT size_t uz32_erase_uz32(UINOUT uc32_t *cstr, const uc32_t *target);
UEXPORT size_t uz32_erase_uz32n(UINOUT uc32_t *cstr, const uc32_t *target, size_t target_len);
UEXPORT size_t uz32_erase_ucv32(UINOUT uc32_t *cstr, ucv32_t target);
UEXPORT size_t uz32_erase_uv32(UINOUT uc32_t *cstr, uv32_t target);
UEXPORT size_t uz32_erase_us32(UINOUT uc32_t *cstr, const us32_t *target);

#define uz32n_erase(cstr, cstr_len, target) \
    _Generic((target),                      \
        default:  uz32n_erase_uc32,         \
        uc32_t *: uz32n_erase_uz32,         \
        ucv32_t:  uz32n_erase_ucv32,        \
        uv32_t:   uz32n_erase_uv32,         \
        us32_t *: uz32n_erase_us32          \
    )((cstr), (cstr_len), (target))

UEXPORT size_t uz32n_erase_uc32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t target);
UEXPORT size_t uz32n_erase_uz32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *target);
UEXPORT size_t uz32n_erase_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len);
UEXPORT size_t uz32n_erase_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t target);
UEXPORT size_t uz32n_erase_uv32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t target);
UEXPORT size_t uz32n_erase_us32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *target);

#define uz16_erase(cstr, target)    \
    _Generic((target),              \
        default:  uz16_erase_uc16,  \
        uc16_t *: uz16_erase_uz16,  \
        ucv16_t:  uz16_erase_ucv16, \
        uv16_t:   uz16_erase_uv16,  \
        us16_t *: uz16_erase_us16   \
    )((cstr), (target))

UEXPORT size_t uz16_erase_uc16(UINOUT uc16_t *cstr, uc16_t target);
UEXPORT size_t uz16_erase_uz16(UINOUT uc16_t *cstr, const uc16_t *target);
UEXPORT size_t uz16_erase_uz16n(UINOUT uc16_t *cstr, const uc16_t *target, size_t target_len);
UEXPORT size_t uz16_erase_ucv16(UINOUT uc16_t *cstr, ucv16_t target);
UEXPORT size_t uz16_erase_uv16(UINOUT uc16_t *cstr, uv16_t target);
UEXPORT size_t uz16_erase_us16(UINOUT uc16_t *cstr, const us16_t *target);

#define uz16n_erase(cstr, cstr_len, target) \
    _Generic((target),                      \
        default:  uz16n_erase_uc16,         \
        uc16_t *: uz16n_erase_uz16,         \
        ucv16_t:  uz16n_erase_ucv16,        \
        uv16_t:   uz16n_erase_uv16,         \
        us16_t *: uz16n_erase_us16          \
    )((cstr), (cstr_len), (target))

UEXPORT size_t uz16n_erase_uc16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t target);
UEXPORT size_t uz16n_erase_uz16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *target);
UEXPORT size_t uz16n_erase_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len);
UEXPORT size_t uz16n_erase_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t target);
UEXPORT size_t uz16n_erase_uv16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t target);
UEXPORT size_t uz16n_erase_us16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *target);

#define uz8_erase(cstr, target)  \
    _Generic((target),           \
        default:  uz8_erase_uc8, \
        uc8_t *: uz8_erase_uz8,  \
        ucv8_t:  uz8_erase_ucv8, \
        uv8_t:   uz8_erase_uv8,  \
        us8_t *: uz8_erase_us8   \
    )((cstr), (target))

UEXPORT size_t uz8_erase_uc8(UINOUT uc8_t *cstr, uc8_t target);
UEXPORT size_t uz8_erase_uz8(UINOUT uc8_t *cstr, const uc8_t *target);
UEXPORT size_t uz8_erase_uz8n(UINOUT uc8_t *cstr, const uc8_t *target, size_t target_len);
UEXPORT size_t uz8_erase_ucv8(UINOUT uc8_t *cstr, ucv8_t target);
UEXPORT size_t uz8_erase_uv8(UINOUT uc8_t *cstr, uv8_t target);
UEXPORT size_t uz8_erase_us8(UINOUT uc8_t *cstr, const us8_t *target);

#define uz8n_erase(cstr, cstr_len, target) \
    _Generic((target),                     \
        default:  uz8n_erase_uc8,          \
        uc8_t *: uz8n_erase_uz8,           \
        ucv8_t:  uz8n_erase_ucv8,          \
        uv8_t:   uz8n_erase_uv8,           \
        us8_t *: uz8n_erase_us8            \
    )((cstr), (cstr_len), (target))

UEXPORT size_t uz8n_erase_uc8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t target);
UEXPORT size_t uz8n_erase_uz8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *target);
UEXPORT size_t uz8n_erase_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len);
UEXPORT size_t uz8n_erase_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t target);
UEXPORT size_t uz8n_erase_uv8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t target);
UEXPORT size_t uz8n_erase_us8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *target);

// Replace

#define uz32_replace(cstr, from, to)                  \
    _Generic((from),                                  \
        default: _Generic((to),                       \
            default:        uz32_replace_uc32_uc32,   \
            const uc32_t *: uz32_replace_uc32_uz32,   \
            uc32_t *:       uz32_replace_uc32_uz32,   \
            ucv32_t:        uz32_replace_uc32_ucv32,  \
            uv32_t:         uz32_replace_uc32_uv32,   \
            const us32_t *: uz32_replace_uc32_us32,   \
            us32_t *:       uz32_replace_uc32_us32    \
        ),                                            \
        const uc32_t *: _Generic((to),                \
            default:        uz32_replace_uz32_uc32,   \
            const uc32_t *: uz32_replace_uz32_uz32,   \
            uc32_t *:       uz32_replace_uz32_uz32,   \
            ucv32_t:        uz32_replace_uz32_ucv32,  \
            uv32_t:         uz32_replace_uz32_uv32,   \
            const us32_t *: uz32_replace_uz32_us32,   \
            us32_t *:       uz32_replace_uz32_us32    \
        ),                                            \
        uc32_t *: _Generic((to),                      \
            default:        uz32_replace_uz32_uc32,   \
            const uc32_t *: uz32_replace_uz32_uz32,   \
            uc32_t *:       uz32_replace_uz32_uz32,   \
            ucv32_t:        uz32_replace_uz32_ucv32,  \
            uv32_t:         uz32_replace_uz32_uv32,   \
            const us32_t *: uz32_replace_uz32_us32,   \
            us32_t *:       uz32_replace_uz32_us32    \
        ),                                            \
        ucv32_t: _Generic((to),                       \
            default:        uz32_replace_ucv32_uc32,  \
            const uc32_t *: uz32_replace_ucv32_uz32,  \
            uc32_t *:       uz32_replace_ucv32_uz32,  \
            ucv32_t:        uz32_replace_ucv32_ucv32, \
            uv32_t:         uz32_replace_ucv32_uv32,  \
            const us32_t *: uz32_replace_ucv32_us32,  \
            us32_t *:       uz32_replace_ucv32_us32   \
        ),                                            \
        uv32_t: _Generic((to),                        \
            default:        uz32_replace_uv32_uc32,   \
            const uc32_t *: uz32_replace_uv32_uz32,   \
            uc32_t *:       uz32_replace_uv32_uz32,   \
            ucv32_t:        uz32_replace_uv32_ucv32,  \
            uv32_t:         uz32_replace_uv32_uv32,   \
            const us32_t *: uz32_replace_uv32_us32,   \
            us32_t *:       uz32_replace_uv32_us32    \
        ),                                            \
        const us32_t *: _Generic((to),                \
            default:        uz32_replace_us32_uc32,   \
            const uc32_t *: uz32_replace_us32_uz32,   \
            uc32_t *:       uz32_replace_us32_uz32,   \
            ucv32_t:        uz32_replace_us32_ucv32,  \
            uv32_t:         uz32_replace_us32_uv32,   \
            const us32_t *: uz32_replace_us32_us32,   \
            us32_t *:       uz32_replace_us32_us32    \
        )                                             \
        us32_t *: _Generic((to),                      \
            default:        uz32_replace_us32_uc32,   \
            const uc32_t *: uz32_replace_us32_uz32,   \
            uc32_t *:       uz32_replace_us32_uz32,   \
            ucv32_t:        uz32_replace_us32_ucv32,  \
            uv32_t:         uz32_replace_us32_uv32,   \
            const us32_t *: uz32_replace_us32_us32,   \
            us32_t *:       uz32_replace_us32_us32    \
        )                                             \
    )((cstr), (from), (to))

UEXPORT size_t uz32_replace_uc32_uc32(UINOUT uc32_t *cstr, uc32_t from, uc32_t to);
UEXPORT size_t uz32_replace_uc32_uz32(UINOUT uc32_t *cstr, uc32_t from, const uc32_t *to);
UEXPORT size_t uz32_replace_uc32_uz32n(UINOUT uc32_t *cstr, uc32_t from, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32_replace_uc32_ucv32(UINOUT uc32_t *cstr, uc32_t from, ucv32_t to);
UEXPORT size_t uz32_replace_uc32_uv32(UINOUT uc32_t *cstr, uc32_t from, uv32_t to);
UEXPORT size_t uz32_replace_uc32_us32(UINOUT uc32_t *cstr, uc32_t from, const us32_t *to);

UEXPORT size_t uz32_replace_uz32_uc32(UINOUT uc32_t *cstr, const uc32_t *from, uc32_t to);
UEXPORT size_t uz32_replace_uz32_uz32(UINOUT uc32_t *cstr, const uc32_t *from, const uc32_t *to);
UEXPORT size_t uz32_replace_uz32_uz32n(UINOUT uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32_replace_uz32_ucv32(UINOUT uc32_t *cstr, const uc32_t *from, ucv32_t to);
UEXPORT size_t uz32_replace_uz32_uv32(UINOUT uc32_t *cstr, const uc32_t *from, uv32_t to);
UEXPORT size_t uz32_replace_uz32_us32(UINOUT uc32_t *cstr, const uc32_t *from, const us32_t *to);

UEXPORT size_t uz32_replace_uz32n_uc32(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to);
UEXPORT size_t uz32_replace_uz32n_uz32(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to);
UEXPORT size_t uz32_replace_uz32n_uz32n(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32_replace_uz32n_ucv32(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, ucv32_t to);
UEXPORT size_t uz32_replace_uz32n_uv32(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, uv32_t to);
UEXPORT size_t uz32_replace_uz32n_us32(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, const us32_t *to);

UEXPORT size_t uz32_replace_ucv32_uc32(UINOUT uc32_t *cstr, ucv32_t from, uc32_t to);
UEXPORT size_t uz32_replace_ucv32_uz32(UINOUT uc32_t *cstr, ucv32_t from, const uc32_t *to);
UEXPORT size_t uz32_replace_ucv32_uz32n(UINOUT uc32_t *cstr, ucv32_t from, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32_replace_ucv32_ucv32(UINOUT uc32_t *cstr, ucv32_t from, ucv32_t to);
UEXPORT size_t uz32_replace_ucv32_uv32(UINOUT uc32_t *cstr, ucv32_t from, uv32_t to);
UEXPORT size_t uz32_replace_ucv32_us32(UINOUT uc32_t *cstr, ucv32_t from, const us32_t *to);

UEXPORT size_t uz32_replace_uv32_uc32(UINOUT uc32_t *cstr, uv32_t from, uc32_t to);
UEXPORT size_t uz32_replace_uv32_uz32(UINOUT uc32_t *cstr, uv32_t from, const uc32_t *to);
UEXPORT size_t uz32_replace_uv32_uz32n(UINOUT uc32_t *cstr, uv32_t from, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32_replace_uv32_ucv32(UINOUT uc32_t *cstr, uv32_t from, ucv32_t to);
UEXPORT size_t uz32_replace_uv32_uv32(UINOUT uc32_t *cstr, uv32_t from, uv32_t to);
UEXPORT size_t uz32_replace_uv32_us32(UINOUT uc32_t *cstr, uv32_t from, const us32_t *to);

UEXPORT size_t uz32_replace_us32_uc32(UINOUT uc32_t *cstr, const us32_t *from, uc32_t to);
UEXPORT size_t uz32_replace_us32_uz32(UINOUT uc32_t *cstr, const us32_t *from, const uc32_t *to);
UEXPORT size_t uz32_replace_us32_uz32n(UINOUT uc32_t *cstr, const us32_t *from, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32_replace_us32_ucv32(UINOUT uc32_t *cstr, const us32_t *from, ucv32_t to);
UEXPORT size_t uz32_replace_us32_uv32(UINOUT uc32_t *cstr, const us32_t *from, uv32_t to);
UEXPORT size_t uz32_replace_us32_us32(UINOUT uc32_t *cstr, const us32_t *from, const us32_t *to);


#define uz32n_replace(cstr, cstr_len, from, to)        \
    _Generic((from),                                   \
        default: _Generic((to),                        \
            default:        uz32n_replace_uc32_uc32,   \
            const uc32_t *: uz32n_replace_uc32_uz32,   \
            uc32_t *:       uz32n_replace_uc32_uz32,   \
            ucv32_t:        uz32n_replace_uc32_ucv32,  \
            uv32_t:         uz32n_replace_uc32_uv32,   \
            const us32_t *: uz32n_replace_uc32_us32,   \
            us32_t *:       uz32n_replace_uc32_us32    \
        ),                                             \
        const uc32_t *: _Generic((to),                 \
            default:        uz32n_replace_uz32_uc32,   \
            const uc32_t *: uz32n_replace_uz32_uz32,   \
            uc32_t *:       uz32n_replace_uz32_uz32,   \
            ucv32_t:        uz32n_replace_uz32_ucv32,  \
            uv32_t:         uz32n_replace_uz32_uv32,   \
            const us32_t *: uz32n_replace_uz32_us32,   \
            us32_t *:       uz32n_replace_uz32_us32    \
        ),                                             \
        uc32_t *: _Generic((to),                       \
            default:        uz32n_replace_uz32_uc32,   \
            const uc32_t *: uz32n_replace_uz32_uz32,   \
            uc32_t *:       uz32n_replace_uz32_uz32,   \
            ucv32_t:        uz32n_replace_uz32_ucv32,  \
            uv32_t:         uz32n_replace_uz32_uv32,   \
            const us32_t *: uz32n_replace_uz32_us32,   \
            us32_t *:       uz32n_replace_uz32_us32    \
        ),                                             \
        ucv32_t: _Generic((to),                        \
            default:        uz32n_replace_ucv32_uc32,  \
            const uc32_t *: uz32n_replace_ucv32_uz32,  \
            uc32_t *:       uz32n_replace_ucv32_uz32,  \
            ucv32_t:        uz32n_replace_ucv32_ucv32, \
            uv32_t:         uz32n_replace_ucv32_uv32,  \
            const us32_t *: uz32n_replace_ucv32_us32,  \
            us32_t *:       uz32n_replace_ucv32_us32   \
        ),                                             \
        uv32_t: _Generic((to),                         \
            default:        uz32n_replace_uv32_uc32,   \
            const uc32_t *: uz32n_replace_uv32_uz32,   \
            uc32_t *:       uz32n_replace_uv32_uz32,   \
            ucv32_t:        uz32n_replace_uv32_ucv32,  \
            uv32_t:         uz32n_replace_uv32_uv32,   \
            const us32_t *: uz32n_replace_uv32_us32,   \
            us32_t *:       uz32n_replace_uv32_us32    \
        ),                                             \
        const us32_t *: _Generic((to),                 \
            default:        uz32n_replace_us32_uc32,   \
            const uc32_t *: uz32n_replace_us32_uz32,   \
            uc32_t *:       uz32n_replace_us32_uz32,   \
            ucv32_t:        uz32n_replace_us32_ucv32,  \
            uv32_t:         uz32n_replace_us32_uv32,   \
            const us32_t *: uz32n_replace_us32_us32,   \
            us32_t *:       uz32n_replace_us32_us32    \
        )                                              \
        us32_t *: _Generic((to),                       \
            default:        uz32n_replace_us32_uc32,   \
            const uc32_t *: uz32n_replace_us32_uz32,   \
            uc32_t *:       uz32n_replace_us32_uz32,   \
            ucv32_t:        uz32n_replace_us32_ucv32,  \
            uv32_t:         uz32n_replace_us32_uv32,   \
            const us32_t *: uz32n_replace_us32_us32,   \
            us32_t *:       uz32n_replace_us32_us32    \
        )                                              \
    )((cstr), (cstr_len), (from), (to))

UEXPORT size_t uz32n_replace_uc32_uc32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to);
UEXPORT size_t uz32n_replace_uc32_uz32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to);
UEXPORT size_t uz32n_replace_uc32_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32n_replace_uc32_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, ucv32_t to);
UEXPORT size_t uz32n_replace_uc32_uv32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, uv32_t to);
UEXPORT size_t uz32n_replace_uc32_us32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, const us32_t *to);

UEXPORT size_t uz32n_replace_uz32_uc32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to);
UEXPORT size_t uz32n_replace_uz32_uz32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to);
UEXPORT size_t uz32n_replace_uz32_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32n_replace_uz32_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, ucv32_t to);
UEXPORT size_t uz32n_replace_uz32_uv32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, uv32_t to);
UEXPORT size_t uz32n_replace_uz32_us32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, const us32_t *to);

UEXPORT size_t uz32n_replace_uz32n_uc32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to);
UEXPORT size_t uz32n_replace_uz32n_uz32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to);
UEXPORT size_t uz32n_replace_uz32n_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32n_replace_uz32n_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, ucv32_t to);
UEXPORT size_t uz32n_replace_uz32n_uv32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uv32_t to);
UEXPORT size_t uz32n_replace_uz32n_us32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const us32_t *to);

UEXPORT size_t uz32n_replace_ucv32_uc32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, uc32_t to);
UEXPORT size_t uz32n_replace_ucv32_uz32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, const uc32_t *to);
UEXPORT size_t uz32n_replace_ucv32_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32n_replace_ucv32_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, ucv32_t to);
UEXPORT size_t uz32n_replace_ucv32_uv32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, uv32_t to);
UEXPORT size_t uz32n_replace_ucv32_us32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, const us32_t *to);

UEXPORT size_t uz32n_replace_uv32_uc32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, uc32_t to);
UEXPORT size_t uz32n_replace_uv32_uz32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, const uc32_t *to);
UEXPORT size_t uz32n_replace_uv32_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32n_replace_uv32_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, ucv32_t to);
UEXPORT size_t uz32n_replace_uv32_uv32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, uv32_t to);
UEXPORT size_t uz32n_replace_uv32_us32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, const us32_t *to);

UEXPORT size_t uz32n_replace_us32_uc32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, uc32_t to);
UEXPORT size_t uz32n_replace_us32_uz32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, const uc32_t *to);
UEXPORT size_t uz32n_replace_us32_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, const uc32_t *to, size_t to_len);
UEXPORT size_t uz32n_replace_us32_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, ucv32_t to);
UEXPORT size_t uz32n_replace_us32_uv32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, uv32_t to);
UEXPORT size_t uz32n_replace_us32_us32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, const us32_t *to);


#define uz16_replace(cstr, from, to)                  \
    _Generic((from),                                  \
        default: _Generic((to),                       \
            default:        uz16_replace_uc16_uc16,   \
            const uc16_t *: uz16_replace_uc16_uz16,   \
            uc16_t *:       uz16_replace_uc16_uz16,   \
            ucv16_t:        uz16_replace_uc16_ucv16,  \
            uv16_t:         uz16_replace_uc16_uv16,   \
            const us16_t *: uz16_replace_uc16_us16,   \
            us16_t *:       uz16_replace_uc16_us16    \
        ),                                            \
        const uc16_t *: _Generic((to),                \
            default:        uz16_replace_uz16_uc16,   \
            const uc16_t *: uz16_replace_uz16_uz16,   \
            uc16_t *:       uz16_replace_uz16_uz16,   \
            ucv16_t:        uz16_replace_uz16_ucv16,  \
            uv16_t:         uz16_replace_uz16_uv16,   \
            const us16_t *: uz16_replace_uz16_us16,   \
            us16_t *:       uz16_replace_uz16_us16    \
        ),                                            \
        uc16_t *: _Generic((to),                      \
            default:        uz16_replace_uz16_uc16,   \
            const uc16_t *: uz16_replace_uz16_uz16,   \
            uc16_t *:       uz16_replace_uz16_uz16,   \
            ucv16_t:        uz16_replace_uz16_ucv16,  \
            uv16_t:         uz16_replace_uz16_uv16,   \
            const us16_t *: uz16_replace_uz16_us16,   \
            us16_t *:       uz16_replace_uz16_us16    \
        ),                                            \
        ucv16_t: _Generic((to),                       \
            default:        uz16_replace_ucv16_uc16,  \
            const uc16_t *: uz16_replace_ucv16_uz16,  \
            uc16_t *:       uz16_replace_ucv16_uz16,  \
            ucv16_t:        uz16_replace_ucv16_ucv16, \
            uv16_t:         uz16_replace_ucv16_uv16,  \
            const us16_t *: uz16_replace_ucv16_us16,  \
            us16_t *:       uz16_replace_ucv16_us16   \
        ),                                            \
        uv16_t: _Generic((to),                        \
            default:        uz16_replace_uv16_uc16,   \
            const uc16_t *: uz16_replace_uv16_uz16,   \
            uc16_t *:       uz16_replace_uv16_uz16,   \
            ucv16_t:        uz16_replace_uv16_ucv16,  \
            uv16_t:         uz16_replace_uv16_uv16,   \
            const us16_t *: uz16_replace_uv16_us16,   \
            us16_t *:       uz16_replace_uv16_us16    \
        ),                                            \
        const us16_t *: _Generic((to),                \
            default:        uz16_replace_us16_uc16,   \
            const uc16_t *: uz16_replace_us16_uz16,   \
            uc16_t *:       uz16_replace_us16_uz16,   \
            ucv16_t:        uz16_replace_us16_ucv16,  \
            uv16_t:         uz16_replace_us16_uv16,   \
            const us16_t *: uz16_replace_us16_us16,   \
            us16_t *:       uz16_replace_us16_us16    \
        )                                             \
        us16_t *: _Generic((to),                      \
            default:        uz16_replace_us16_uc16,   \
            const uc16_t *: uz16_replace_us16_uz16,   \
            uc16_t *:       uz16_replace_us16_uz16,   \
            ucv16_t:        uz16_replace_us16_ucv16,  \
            uv16_t:         uz16_replace_us16_uv16,   \
            const us16_t *: uz16_replace_us16_us16,   \
            us16_t *:       uz16_replace_us16_us16    \
        )                                             \
    )((cstr), (from), (to))

UEXPORT size_t uz16_replace_uc16_uc16(UINOUT uc16_t *cstr, uc16_t from, uc16_t to);
UEXPORT size_t uz16_replace_uc16_uz16(UINOUT uc16_t *cstr, uc16_t from, const uc16_t *to);
UEXPORT size_t uz16_replace_uc16_uz16n(UINOUT uc16_t *cstr, uc16_t from, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16_replace_uc16_ucv16(UINOUT uc16_t *cstr, uc16_t from, ucv16_t to);
UEXPORT size_t uz16_replace_uc16_uv16(UINOUT uc16_t *cstr, uc16_t from, uv16_t to);
UEXPORT size_t uz16_replace_uc16_us16(UINOUT uc16_t *cstr, uc16_t from, const us16_t *to);

UEXPORT size_t uz16_replace_uz16_uc16(UINOUT uc16_t *cstr, const uc16_t *from, uc16_t to);
UEXPORT size_t uz16_replace_uz16_uz16(UINOUT uc16_t *cstr, const uc16_t *from, const uc16_t *to);
UEXPORT size_t uz16_replace_uz16_uz16n(UINOUT uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16_replace_uz16_ucv16(UINOUT uc16_t *cstr, const uc16_t *from, ucv16_t to);
UEXPORT size_t uz16_replace_uz16_uv16(UINOUT uc16_t *cstr, const uc16_t *from, uv16_t to);
UEXPORT size_t uz16_replace_uz16_us16(UINOUT uc16_t *cstr, const uc16_t *from, const us16_t *to);

UEXPORT size_t uz16_replace_uz16n_uc16(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to);
UEXPORT size_t uz16_replace_uz16n_uz16(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to);
UEXPORT size_t uz16_replace_uz16n_uz16n(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16_replace_uz16n_ucv16(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, ucv16_t to);
UEXPORT size_t uz16_replace_uz16n_uv16(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, uv16_t to);
UEXPORT size_t uz16_replace_uz16n_us16(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, const us16_t *to);

UEXPORT size_t uz16_replace_ucv16_uc16(UINOUT uc16_t *cstr, ucv16_t from, uc16_t to);
UEXPORT size_t uz16_replace_ucv16_uz16(UINOUT uc16_t *cstr, ucv16_t from, const uc16_t *to);
UEXPORT size_t uz16_replace_ucv16_uz16n(UINOUT uc16_t *cstr, ucv16_t from, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16_replace_ucv16_ucv16(UINOUT uc16_t *cstr, ucv16_t from, ucv16_t to);
UEXPORT size_t uz16_replace_ucv16_uv16(UINOUT uc16_t *cstr, ucv16_t from, uv16_t to);
UEXPORT size_t uz16_replace_ucv16_us16(UINOUT uc16_t *cstr, ucv16_t from, const us16_t *to);

UEXPORT size_t uz16_replace_uv16_uc16(UINOUT uc16_t *cstr, uv16_t from, uc16_t to);
UEXPORT size_t uz16_replace_uv16_uz16(UINOUT uc16_t *cstr, uv16_t from, const uc16_t *to);
UEXPORT size_t uz16_replace_uv16_uz16n(UINOUT uc16_t *cstr, uv16_t from, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16_replace_uv16_ucv16(UINOUT uc16_t *cstr, uv16_t from, ucv16_t to);
UEXPORT size_t uz16_replace_uv16_uv16(UINOUT uc16_t *cstr, uv16_t from, uv16_t to);
UEXPORT size_t uz16_replace_uv16_us16(UINOUT uc16_t *cstr, uv16_t from, const us16_t *to);

UEXPORT size_t uz16_replace_us16_uc16(UINOUT uc16_t *cstr, const us16_t *from, uc16_t to);
UEXPORT size_t uz16_replace_us16_uz16(UINOUT uc16_t *cstr, const us16_t *from, const uc16_t *to);
UEXPORT size_t uz16_replace_us16_uz16n(UINOUT uc16_t *cstr, const us16_t *from, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16_replace_us16_ucv16(UINOUT uc16_t *cstr, const us16_t *from, ucv16_t to);
UEXPORT size_t uz16_replace_us16_uv16(UINOUT uc16_t *cstr, const us16_t *from, uv16_t to);
UEXPORT size_t uz16_replace_us16_us16(UINOUT uc16_t *cstr, const us16_t *from, const us16_t *to);

#define uz16n_replace(cstr, cstr_len, from, to)        \
    _Generic((from),                                   \
        default: _Generic((to),                        \
            default:        uz16n_replace_uc16_uc16,   \
            const uc16_t *: uz16n_replace_uc16_uz16,   \
            uc16_t *:       uz16n_replace_uc16_uz16,   \
            ucv16_t:        uz16n_replace_uc16_ucv16,  \
            uv16_t:         uz16n_replace_uc16_uv16,   \
            const us16_t *: uz16n_replace_uc16_us16,   \
            us16_t *:       uz16n_replace_uc16_us16    \
        ),                                             \
        const uc16_t *: _Generic((to),                 \
            default:        uz16n_replace_uz16_uc16,   \
            const uc16_t *: uz16n_replace_uz16_uz16,   \
            uc16_t *:       uz16n_replace_uz16_uz16,   \
            ucv16_t:        uz16n_replace_uz16_ucv16,  \
            uv16_t:         uz16n_replace_uz16_uv16,   \
            const us16_t *: uz16n_replace_uz16_us16,   \
            us16_t *:       uz16n_replace_uz16_us16    \
        ),                                             \
        uc16_t *: _Generic((to),                       \
            default:        uz16n_replace_uz16_uc16,   \
            const uc16_t *: uz16n_replace_uz16_uz16,   \
            uc16_t *:       uz16n_replace_uz16_uz16,   \
            ucv16_t:        uz16n_replace_uz16_ucv16,  \
            uv16_t:         uz16n_replace_uz16_uv16,   \
            const us16_t *: uz16n_replace_uz16_us16,   \
            us16_t *:       uz16n_replace_uz16_us16    \
        ),                                             \
        ucv16_t: _Generic((to),                        \
            default:        uz16n_replace_ucv16_uc16,  \
            const uc16_t *: uz16n_replace_ucv16_uz16,  \
            uc16_t *:       uz16n_replace_ucv16_uz16,  \
            ucv16_t:        uz16n_replace_ucv16_ucv16, \
            uv16_t:         uz16n_replace_ucv16_uv16,  \
            const us16_t *: uz16n_replace_ucv16_us16,  \
            us16_t *:       uz16n_replace_ucv16_us16   \
        ),                                             \
        uv16_t: _Generic((to),                         \
            default:        uz16n_replace_uv16_uc16,   \
            const uc16_t *: uz16n_replace_uv16_uz16,   \
            uc16_t *:       uz16n_replace_uv16_uz16,   \
            ucv16_t:        uz16n_replace_uv16_ucv16,  \
            uv16_t:         uz16n_replace_uv16_uv16,   \
            const us16_t *: uz16n_replace_uv16_us16,   \
            us16_t *:       uz16n_replace_uv16_us16    \
        ),                                             \
        const us16_t *: _Generic((to),                 \
            default:        uz16n_replace_us16_uc16,   \
            const uc16_t *: uz16n_replace_us16_uz16,   \
            uc16_t *:       uz16n_replace_us16_uz16,   \
            ucv16_t:        uz16n_replace_us16_ucv16,  \
            uv16_t:         uz16n_replace_us16_uv16,   \
            const us16_t *: uz16n_replace_us16_us16,   \
            us16_t *:       uz16n_replace_us16_us16    \
        )                                              \
        us16_t *: _Generic((to),                       \
            default:        uz16n_replace_us16_uc16,   \
            const uc16_t *: uz16n_replace_us16_uz16,   \
            uc16_t *:       uz16n_replace_us16_uz16,   \
            ucv16_t:        uz16n_replace_us16_ucv16,  \
            uv16_t:         uz16n_replace_us16_uv16,   \
            const us16_t *: uz16n_replace_us16_us16,   \
            us16_t *:       uz16n_replace_us16_us16    \
        )                                              \
    )((cstr), (cstr_len), (from), (to))

UEXPORT size_t uz16n_replace_uc16_uc16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to);
UEXPORT size_t uz16n_replace_uc16_uz16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to);
UEXPORT size_t uz16n_replace_uc16_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16n_replace_uc16_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, ucv16_t to);
UEXPORT size_t uz16n_replace_uc16_uv16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, uv16_t to);
UEXPORT size_t uz16n_replace_uc16_us16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, const us16_t *to);

UEXPORT size_t uz16n_replace_uz16_uc16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to);
UEXPORT size_t uz16n_replace_uz16_uz16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to);
UEXPORT size_t uz16n_replace_uz16_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16n_replace_uz16_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, ucv16_t to);
UEXPORT size_t uz16n_replace_uz16_uv16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, uv16_t to);
UEXPORT size_t uz16n_replace_uz16_us16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, const us16_t *to);

UEXPORT size_t uz16n_replace_uz16n_uc16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to);
UEXPORT size_t uz16n_replace_uz16n_uz16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to);
UEXPORT size_t uz16n_replace_uz16n_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16n_replace_uz16n_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, ucv16_t to);
UEXPORT size_t uz16n_replace_uz16n_uv16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uv16_t to);
UEXPORT size_t uz16n_replace_uz16n_us16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const us16_t *to);

UEXPORT size_t uz16n_replace_ucv16_uc16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, uc16_t to);
UEXPORT size_t uz16n_replace_ucv16_uz16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, const uc16_t *to);
UEXPORT size_t uz16n_replace_ucv16_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16n_replace_ucv16_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, ucv16_t to);
UEXPORT size_t uz16n_replace_ucv16_uv16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, uv16_t to);
UEXPORT size_t uz16n_replace_ucv16_us16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, const us16_t *to);

UEXPORT size_t uz16n_replace_uv16_uc16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, uc16_t to);
UEXPORT size_t uz16n_replace_uv16_uz16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, const uc16_t *to);
UEXPORT size_t uz16n_replace_uv16_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16n_replace_uv16_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, ucv16_t to);
UEXPORT size_t uz16n_replace_uv16_uv16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, uv16_t to);
UEXPORT size_t uz16n_replace_uv16_us16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, const us16_t *to);

UEXPORT size_t uz16n_replace_us16_uc16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, uc16_t to);
UEXPORT size_t uz16n_replace_us16_uz16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, const uc16_t *to);
UEXPORT size_t uz16n_replace_us16_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, const uc16_t *to, size_t to_len);
UEXPORT size_t uz16n_replace_us16_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, ucv16_t to);
UEXPORT size_t uz16n_replace_us16_uv16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, uv16_t to);
UEXPORT size_t uz16n_replace_us16_us16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, const us16_t *to);

#define uz8_replace(cstr, from, to)               \
    _Generic((from),                              \
        default: _Generic((to),                   \
            default:       uz8_replace_uc8_uc8,   \
            const uc8_t *: uz8_replace_uc8_uz8,   \
            uc8_t *:       uz8_replace_uc8_uz8,   \
            ucv8_t:        uz8_replace_uc8_ucv8,  \
            uv8_t:         uz8_replace_uc8_uv8,   \
            const us8_t *: uz8_replace_uc8_us8,   \
            us8_t *:       uz8_replace_uc8_us8    \
        ),                                        \
        const uc8_t *: _Generic((to),             \
            default:       uz8_replace_uz8_uc8,   \
            const uc8_t *: uz8_replace_uz8_uz8,   \
            uc8_t *:       uz8_replace_uz8_uz8,   \
            ucv8_t:        uz8_replace_uz8_ucv8,  \
            uv8_t:         uz8_replace_uz8_uv8,   \
            const us8_t *: uz8_replace_uz8_us8,   \
            us8_t *:       uz8_replace_uz8_us8    \
        ),                                        \
        uc8_t *: _Generic((to),                   \
            default:       uz8_replace_uz8_uc8,   \
            const uc8_t *: uz8_replace_uz8_uz8,   \
            uc8_t *:       uz8_replace_uz8_uz8,   \
            ucv8_t:        uz8_replace_uz8_ucv8,  \
            uv8_t:         uz8_replace_uz8_uv8,   \
            const us8_t *: uz8_replace_uz8_us8,   \
            us8_t *:       uz8_replace_uz8_us8    \
        ),                                        \
        ucv8_t: _Generic((to),                    \
            default:       uz8_replace_ucv8_uc8,  \
            const uc8_t *: uz8_replace_ucv8_uz8,  \
            uc8_t *:       uz8_replace_ucv8_uz8,  \
            ucv8_t:        uz8_replace_ucv8_ucv8, \
            uv8_t:         uz8_replace_ucv8_uv8,  \
            const us8_t *: uz8_replace_ucv8_us8,  \
            us8_t *:       uz8_replace_ucv8_us8   \
        ),                                        \
        uv8_t: _Generic((to),                     \
            default:       uz8_replace_uv8_uc8,   \
            const uc8_t *: uz8_replace_uv8_uz8,   \
            uc8_t *:       uz8_replace_uv8_uz8,   \
            ucv8_t:        uz8_replace_uv8_ucv8,  \
            uv8_t:         uz8_replace_uv8_uv8,   \
            const us8_t *: uz8_replace_uv8_us8,   \
            us8_t *:       uz8_replace_uv8_us8    \
        ),                                        \
        const us8_t *: _Generic((to),             \
            default:       uz8_replace_us8_uc8,   \
            const uc8_t *: uz8_replace_us8_uz8,   \
            uc8_t *:       uz8_replace_us8_uz8,   \
            ucv8_t:        uz8_replace_us8_ucv8,  \
            uv8_t:         uz8_replace_us8_uv8,   \
            const us8_t *: uz8_replace_us8_us8,   \
            us8_t *:       uz8_replace_us8_us8    \
        )                                         \
        us8_t *: _Generic((to),                   \
            default:       uz8_replace_us8_uc8,   \
            const uc8_t *: uz8_replace_us8_uz8,   \
            uc8_t *:       uz8_replace_us8_uz8,   \
            ucv8_t:        uz8_replace_us8_ucv8,  \
            uv8_t:         uz8_replace_us8_uv8,   \
            const us8_t *: uz8_replace_us8_us8,   \
            us8_t *:       uz8_replace_us8_us8    \
        )                                         \
    )((cstr), (from), (to))

UEXPORT size_t uz8_replace_uc8_uc8(UINOUT uc8_t *cstr, uc8_t from, uc8_t to);
UEXPORT size_t uz8_replace_uc8_uz8(UINOUT uc8_t *cstr, uc8_t from, const uc8_t *to);
UEXPORT size_t uz8_replace_uc8_uz8n(UINOUT uc8_t *cstr, uc8_t from, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8_replace_uc8_ucv8(UINOUT uc8_t *cstr, uc8_t from, ucv8_t to);
UEXPORT size_t uz8_replace_uc8_uv8(UINOUT uc8_t *cstr, uc8_t from, uv8_t to);
UEXPORT size_t uz8_replace_uc8_us8(UINOUT uc8_t *cstr, uc8_t from, const us8_t *to);

UEXPORT size_t uz8_replace_uz8_uc8(UINOUT uc8_t *cstr, const uc8_t *from, uc8_t to);
UEXPORT size_t uz8_replace_uz8_uz8(UINOUT uc8_t *cstr, const uc8_t *from, const uc8_t *to);
UEXPORT size_t uz8_replace_uz8_uz8n(UINOUT uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8_replace_uz8_ucv8(UINOUT uc8_t *cstr, const uc8_t *from, ucv8_t to);
UEXPORT size_t uz8_replace_uz8_uv8(UINOUT uc8_t *cstr, const uc8_t *from, uv8_t to);
UEXPORT size_t uz8_replace_uz8_us8(UINOUT uc8_t *cstr, const uc8_t *from, const us8_t *to);

UEXPORT size_t uz8_replace_uz8n_uc8(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to);
UEXPORT size_t uz8_replace_uz8n_uz8(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to);
UEXPORT size_t uz8_replace_uz8n_uz8n(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8_replace_uz8n_ucv8(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, ucv8_t to);
UEXPORT size_t uz8_replace_uz8n_uv8(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, uv8_t to);
UEXPORT size_t uz8_replace_uz8n_us8(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, const us8_t *to);

UEXPORT size_t uz8_replace_ucv8_uc8(UINOUT uc8_t *cstr, ucv8_t from, uc8_t to);
UEXPORT size_t uz8_replace_ucv8_uz8(UINOUT uc8_t *cstr, ucv8_t from, const uc8_t *to);
UEXPORT size_t uz8_replace_ucv8_uz8n(UINOUT uc8_t *cstr, ucv8_t from, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8_replace_ucv8_ucv8(UINOUT uc8_t *cstr, ucv8_t from, ucv8_t to);
UEXPORT size_t uz8_replace_ucv8_uv8(UINOUT uc8_t *cstr, ucv8_t from, uv8_t to);
UEXPORT size_t uz8_replace_ucv8_us8(UINOUT uc8_t *cstr, ucv8_t from, const us8_t *to);

UEXPORT size_t uz8_replace_uv8_uc8(UINOUT uc8_t *cstr, uv8_t from, uc8_t to);
UEXPORT size_t uz8_replace_uv8_uz8(UINOUT uc8_t *cstr, uv8_t from, const uc8_t *to);
UEXPORT size_t uz8_replace_uv8_uz8n(UINOUT uc8_t *cstr, uv8_t from, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8_replace_uv8_ucv8(UINOUT uc8_t *cstr, uv8_t from, ucv8_t to);
UEXPORT size_t uz8_replace_uv8_uv8(UINOUT uc8_t *cstr, uv8_t from, uv8_t to);
UEXPORT size_t uz8_replace_uv8_us8(UINOUT uc8_t *cstr, uv8_t from, const us8_t *to);

UEXPORT size_t uz8_replace_us8_uc8(UINOUT uc8_t *cstr, const us8_t *from, uc8_t to);
UEXPORT size_t uz8_replace_us8_uz8(UINOUT uc8_t *cstr, const us8_t *from, const uc8_t *to);
UEXPORT size_t uz8_replace_us8_uz8n(UINOUT uc8_t *cstr, const us8_t *from, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8_replace_us8_ucv8(UINOUT uc8_t *cstr, const us8_t *from, ucv8_t to);
UEXPORT size_t uz8_replace_us8_uv8(UINOUT uc8_t *cstr, const us8_t *from, uv8_t to);
UEXPORT size_t uz8_replace_us8_us8(UINOUT uc8_t *cstr, const us8_t *from, const us8_t *to);


#define uz8n_replace(cstr, cstr_len, from, to)     \
    _Generic((from),                               \
        default: _Generic((to),                    \
            default:       uz8n_replace_uc8_uc8,   \
            const uc8_t *: uz8n_replace_uc8_uz8,   \
            uc8_t *:       uz8n_replace_uc8_uz8,   \
            ucv8_t:        uz8n_replace_uc8_ucv8,  \
            uv8_t:         uz8n_replace_uc8_uv8,   \
            const us8_t *: uz8n_replace_uc8_us8,   \
            us8_t *:       uz8n_replace_uc8_us8    \
        ),                                         \
        const uc8_t *: _Generic((to),              \
            default:       uz8n_replace_uz8_uc8,   \
            const uc8_t *: uz8n_replace_uz8_uz8,   \
            uc8_t *:       uz8n_replace_uz8_uz8,   \
            ucv8_t:        uz8n_replace_uz8_ucv8,  \
            uv8_t:         uz8n_replace_uz8_uv8,   \
            const us8_t *: uz8n_replace_uz8_us8,   \
            us8_t *:       uz8n_replace_uz8_us8    \
        ),                                         \
        uc8_t *: _Generic((to),                    \
            default:       uz8n_replace_uz8_uc8,   \
            const uc8_t *: uz8n_replace_uz8_uz8,   \
            uc8_t *:       uz8n_replace_uz8_uz8,   \
            ucv8_t:        uz8n_replace_uz8_ucv8,  \
            uv8_t:         uz8n_replace_uz8_uv8,   \
            const us8_t *: uz8n_replace_uz8_us8,   \
            us8_t *:       uz8n_replace_uz8_us8    \
        ),                                         \
        ucv8_t: _Generic((to),                     \
            default:       uz8n_replace_ucv8_uc8,  \
            const uc8_t *: uz8n_replace_ucv8_uz8,  \
            uc8_t *:       uz8n_replace_ucv8_uz8,  \
            ucv8_t:        uz8n_replace_ucv8_ucv8, \
            uv8_t:         uz8n_replace_ucv8_uv8,  \
            const us8_t *: uz8n_replace_ucv8_us8,  \
            us8_t *:       uz8n_replace_ucv8_us8   \
        ),                                         \
        uv8_t: _Generic((to),                      \
            default:       uz8n_replace_uv8_uc8,   \
            const uc8_t *: uz8n_replace_uv8_uz8,   \
            uc8_t *:       uz8n_replace_uv8_uz8,   \
            ucv8_t:        uz8n_replace_uv8_ucv8,  \
            uv8_t:         uz8n_replace_uv8_uv8,   \
            const us8_t *: uz8n_replace_uv8_us8,   \
            us8_t *:       uz8n_replace_uv8_us8    \
        ),                                         \
        const us8_t *: _Generic((to),              \
            default:       uz8n_replace_us8_uc8,   \
            const uc8_t *: uz8n_replace_us8_uz8,   \
            uc8_t *:       uz8n_replace_us8_uz8,   \
            ucv8_t:        uz8n_replace_us8_ucv8,  \
            uv8_t:         uz8n_replace_us8_uv8,   \
            const us8_t *: uz8n_replace_us8_us8,   \
            us8_t *:       uz8n_replace_us8_us8    \
        )                                          \
        us8_t *: _Generic((to),                    \
            default:       uz8n_replace_us8_uc8,   \
            const uc8_t *: uz8n_replace_us8_uz8,   \
            uc8_t *:       uz8n_replace_us8_uz8,   \
            ucv8_t:        uz8n_replace_us8_ucv8,  \
            uv8_t:         uz8n_replace_us8_uv8,   \
            const us8_t *: uz8n_replace_us8_us8,   \
            us8_t *:       uz8n_replace_us8_us8    \
        )                                          \
    )((cstr), (cstr_len), (from), (to))

UEXPORT size_t uz8n_replace_uc8_uc8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to);
UEXPORT size_t uz8n_replace_uc8_uz8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to);
UEXPORT size_t uz8n_replace_uc8_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8n_replace_uc8_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, ucv8_t to);
UEXPORT size_t uz8n_replace_uc8_uv8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, uv8_t to);
UEXPORT size_t uz8n_replace_uc8_us8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, const us8_t *to);

UEXPORT size_t uz8n_replace_uz8_uc8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to);
UEXPORT size_t uz8n_replace_uz8_uz8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to);
UEXPORT size_t uz8n_replace_uz8_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8n_replace_uz8_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, ucv8_t to);
UEXPORT size_t uz8n_replace_uz8_uv8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, uv8_t to);
UEXPORT size_t uz8n_replace_uz8_us8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, const us8_t *to);

UEXPORT size_t uz8n_replace_uz8n_uc8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to);
UEXPORT size_t uz8n_replace_uz8n_uz8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to);
UEXPORT size_t uz8n_replace_uz8n_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8n_replace_uz8n_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, ucv8_t to);
UEXPORT size_t uz8n_replace_uz8n_uv8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uv8_t to);
UEXPORT size_t uz8n_replace_uz8n_us8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const us8_t *to);

UEXPORT size_t uz8n_replace_ucv8_uc8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, uc8_t to);
UEXPORT size_t uz8n_replace_ucv8_uz8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, const uc8_t *to);
UEXPORT size_t uz8n_replace_ucv8_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8n_replace_ucv8_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, ucv8_t to);
UEXPORT size_t uz8n_replace_ucv8_uv8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, uv8_t to);
UEXPORT size_t uz8n_replace_ucv8_us8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, const us8_t *to);

UEXPORT size_t uz8n_replace_uv8_uc8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, uc8_t to);
UEXPORT size_t uz8n_replace_uv8_uz8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, const uc8_t *to);
UEXPORT size_t uz8n_replace_uv8_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8n_replace_uv8_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, ucv8_t to);
UEXPORT size_t uz8n_replace_uv8_uv8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, uv8_t to);
UEXPORT size_t uz8n_replace_uv8_us8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, const us8_t *to);

UEXPORT size_t uz8n_replace_us8_uc8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, uc8_t to);
UEXPORT size_t uz8n_replace_us8_uz8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, const uc8_t *to);
UEXPORT size_t uz8n_replace_us8_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, const uc8_t *to, size_t to_len);
UEXPORT size_t uz8n_replace_us8_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, ucv8_t to);
UEXPORT size_t uz8n_replace_us8_uv8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, uv8_t to);
UEXPORT size_t uz8n_replace_us8_us8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, const us8_t *to);

// Replaced length

#define uz32_replaced_len(cstr, from, to)                  \
    _Generic((from),                                       \
        default: _Generic((to),                            \
            default:        uz32_replaced_len_uc32_uc32,   \
            const uc32_t *: uz32_replaced_len_uc32_uz32,   \
            uc32_t *:       uz32_replaced_len_uc32_uz32,   \
            ucv32_t:        uz32_replaced_len_uc32_ucv32,  \
            uv32_t:         uz32_replaced_len_uc32_uv32,   \
            const us32_t *: uz32_replaced_len_uc32_us32,   \
            us32_t *:       uz32_replaced_len_uc32_us32    \
        ),                                                 \
        const uc32_t *: _Generic((to),                     \
            default:        uz32_replaced_len_uz32_uc32,   \
            const uc32_t *: uz32_replaced_len_uz32_uz32,   \
            uc32_t *:       uz32_replaced_len_uz32_uz32,   \
            ucv32_t:        uz32_replaced_len_uz32_ucv32,  \
            uv32_t:         uz32_replaced_len_uz32_uv32,   \
            const us32_t *: uz32_replaced_len_uz32_us32,   \
            us32_t *:       uz32_replaced_len_uz32_us32    \
        ),                                                 \
        uc32_t *: _Generic((to),                           \
            default:        uz32_replaced_len_uz32_uc32,   \
            const uc32_t *: uz32_replaced_len_uz32_uz32,   \
            uc32_t *:       uz32_replaced_len_uz32_uz32,   \
            ucv32_t:        uz32_replaced_len_uz32_ucv32,  \
            uv32_t:         uz32_replaced_len_uz32_uv32,   \
            const us32_t *: uz32_replaced_len_uz32_us32,   \
            us32_t *:       uz32_replaced_len_uz32_us32    \
        ),                                                 \
        ucv32_t: _Generic((to),                            \
            default:        uz32_replaced_len_ucv32_uc32,  \
            const uc32_t *: uz32_replaced_len_ucv32_uz32,  \
            uc32_t *:       uz32_replaced_len_ucv32_uz32,  \
            ucv32_t:        uz32_replaced_len_ucv32_ucv32, \
            uv32_t:         uz32_replaced_len_ucv32_uv32,  \
            const us32_t *: uz32_replaced_len_ucv32_us32,  \
            us32_t *:       uz32_replaced_len_ucv32_us32   \
        ),                                                 \
        uv32_t: _Generic((to),                             \
            default:        uz32_replaced_len_uv32_uc32,   \
            const uc32_t *: uz32_replaced_len_uv32_uz32,   \
            uc32_t *:       uz32_replaced_len_uv32_uz32,   \
            ucv32_t:        uz32_replaced_len_uv32_ucv32,  \
            uv32_t:         uz32_replaced_len_uv32_uv32,   \
            const us32_t *: uz32_replaced_len_uv32_us32,   \
            us32_t *:       uz32_replaced_len_uv32_us32    \
        ),                                                 \
        const us32_t *: _Generic((to),                     \
            default:        uz32_replaced_len_us32_uc32,   \
            const uc32_t *: uz32_replaced_len_us32_uz32,   \
            uc32_t *:       uz32_replaced_len_us32_uz32,   \
            ucv32_t:        uz32_replaced_len_us32_ucv32,  \
            uv32_t:         uz32_replaced_len_us32_uv32,   \
            const us32_t *: uz32_replaced_len_us32_us32,   \
            us32_t *:       uz32_replaced_len_us32_us32    \
        )                                                  \
        us32_t *: _Generic((to),                           \
            default:        uz32_replaced_len_us32_uc32,   \
            const uc32_t *: uz32_replaced_len_us32_uz32,   \
            uc32_t *:       uz32_replaced_len_us32_uz32,   \
            ucv32_t:        uz32_replaced_len_us32_ucv32,  \
            uv32_t:         uz32_replaced_len_us32_uv32,   \
            const us32_t *: uz32_replaced_len_us32_us32,   \
            us32_t *:       uz32_replaced_len_us32_us32    \
        )                                                  \
    )((cstr), (from), (to))

UEXPORT size_t uz32_replaced_len_uc32_uc32(const uc32_t *cstr, uc32_t from, uc32_t to);
UEXPORT size_t uz32_replaced_len_uc32_uz32(const uc32_t *cstr, uc32_t from, const uc32_t *to);
UEXPORT size_t uz32_replaced_len_uc32_uz32n(const uc32_t *cstr, uc32_t from, size_t to_len);
UEXPORT size_t uz32_replaced_len_uc32_ucv32(const uc32_t *cstr, uc32_t from, ucv32_t to);
UEXPORT size_t uz32_replaced_len_uc32_uv32(const uc32_t *cstr, uc32_t from, uv32_t to);
UEXPORT size_t uz32_replaced_len_uc32_us32(const uc32_t *cstr, uc32_t from, const us32_t *to);

UEXPORT size_t uz32_replaced_len_uz32_uc32(const uc32_t *cstr, const uc32_t *from, uc32_t to);
UEXPORT size_t uz32_replaced_len_uz32_uz32(const uc32_t *cstr, const uc32_t *from, const uc32_t *to);
UEXPORT size_t uz32_replaced_len_uz32_uz32n(const uc32_t *cstr, const uc32_t *from, size_t to_len);
UEXPORT size_t uz32_replaced_len_uz32_ucv32(const uc32_t *cstr, const uc32_t *from, ucv32_t to);
UEXPORT size_t uz32_replaced_len_uz32_uv32(const uc32_t *cstr, const uc32_t *from, uv32_t to);
UEXPORT size_t uz32_replaced_len_uz32_us32(const uc32_t *cstr, const uc32_t *from, const us32_t *to);

UEXPORT size_t uz32_replaced_len_uz32n_uc32(const uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to);
UEXPORT size_t uz32_replaced_len_uz32n_uz32(const uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to);
UEXPORT size_t uz32_replaced_len_uz32n_uz32n(const uc32_t *cstr, const uc32_t *from, size_t from_len, size_t to_len);
UEXPORT size_t uz32_replaced_len_uz32n_ucv32(const uc32_t *cstr, const uc32_t *from, size_t from_len, ucv32_t to);
UEXPORT size_t uz32_replaced_len_uz32n_uv32(const uc32_t *cstr, const uc32_t *from, size_t from_len, uv32_t to);
UEXPORT size_t uz32_replaced_len_uz32n_us32(const uc32_t *cstr, const uc32_t *from, size_t from_len, const us32_t *to);

UEXPORT size_t uz32_replaced_len_ucv32_uc32(const uc32_t *cstr, ucv32_t from, uc32_t to);
UEXPORT size_t uz32_replaced_len_ucv32_uz32(const uc32_t *cstr, ucv32_t from, const uc32_t *to);
UEXPORT size_t uz32_replaced_len_ucv32_uz32n(const uc32_t *cstr, ucv32_t from, size_t to_len);
UEXPORT size_t uz32_replaced_len_ucv32_ucv32(const uc32_t *cstr, ucv32_t from, ucv32_t to);
UEXPORT size_t uz32_replaced_len_ucv32_uv32(const uc32_t *cstr, ucv32_t from, uv32_t to);
UEXPORT size_t uz32_replaced_len_ucv32_us32(const uc32_t *cstr, ucv32_t from, const us32_t *to);

UEXPORT size_t uz32_replaced_len_uv32_uc32(const uc32_t *cstr, uv32_t from, uc32_t to);
UEXPORT size_t uz32_replaced_len_uv32_uz32(const uc32_t *cstr, uv32_t from, const uc32_t *to);
UEXPORT size_t uz32_replaced_len_uv32_uz32n(const uc32_t *cstr, uv32_t from, size_t to_len);
UEXPORT size_t uz32_replaced_len_uv32_ucv32(const uc32_t *cstr, uv32_t from, ucv32_t to);
UEXPORT size_t uz32_replaced_len_uv32_uv32(const uc32_t *cstr, uv32_t from, uv32_t to);
UEXPORT size_t uz32_replaced_len_uv32_us32(const uc32_t *cstr, uv32_t from, const us32_t *to);

UEXPORT size_t uz32_replaced_len_us32_uc32(const uc32_t *cstr, const us32_t *from, uc32_t to);
UEXPORT size_t uz32_replaced_len_us32_uz32(const uc32_t *cstr, const us32_t *from, const uc32_t *to);
UEXPORT size_t uz32_replaced_len_us32_uz32n(const uc32_t *cstr, const us32_t *from, size_t to_len);
UEXPORT size_t uz32_replaced_len_us32_ucv32(const uc32_t *cstr, const us32_t *from, ucv32_t to);
UEXPORT size_t uz32_replaced_len_us32_uv32(const uc32_t *cstr, const us32_t *from, uv32_t to);
UEXPORT size_t uz32_replaced_len_us32_us32(const uc32_t *cstr, const us32_t *from, const us32_t *to);

#define uz32n_replaced_len(cstr, cstr_len, from, to)        \
    _Generic((from),                                        \
        default: _Generic((to),                             \
            default:        uz32n_replaced_len_uc32_uc32,   \
            const uc32_t *: uz32n_replaced_len_uc32_uz32,   \
            uc32_t *:       uz32n_replaced_len_uc32_uz32,   \
            ucv32_t:        uz32n_replaced_len_uc32_ucv32,  \
            uv32_t:         uz32n_replaced_len_uc32_uv32,   \
            const us32_t *: uz32n_replaced_len_uc32_us32,   \
            us32_t *:       uz32n_replaced_len_uc32_us32    \
        ),                                                  \
        const uc32_t *: _Generic((to),                      \
            default:        uz32n_replaced_len_uz32_uc32,   \
            const uc32_t *: uz32n_replaced_len_uz32_uz32,   \
            uc32_t *:       uz32n_replaced_len_uz32_uz32,   \
            ucv32_t:        uz32n_replaced_len_uz32_ucv32,  \
            uv32_t:         uz32n_replaced_len_uz32_uv32,   \
            const us32_t *: uz32n_replaced_len_uz32_us32,   \
            us32_t *:       uz32n_replaced_len_uz32_us32    \
        ),                                                  \
        uc32_t *: _Generic((to),                            \
            default:        uz32n_replaced_len_uz32_uc32,   \
            const uc32_t *: uz32n_replaced_len_uz32_uz32,   \
            uc32_t *:       uz32n_replaced_len_uz32_uz32,   \
            ucv32_t:        uz32n_replaced_len_uz32_ucv32,  \
            uv32_t:         uz32n_replaced_len_uz32_uv32,   \
            const us32_t *: uz32n_replaced_len_uz32_us32,   \
            us32_t *:       uz32n_replaced_len_uz32_us32    \
        ),                                                  \
        ucv32_t: _Generic((to),                             \
            default:        uz32n_replaced_len_ucv32_uc32,  \
            const uc32_t *: uz32n_replaced_len_ucv32_uz32,  \
            uc32_t *:       uz32n_replaced_len_ucv32_uz32,  \
            ucv32_t:        uz32n_replaced_len_ucv32_ucv32, \
            uv32_t:         uz32n_replaced_len_ucv32_uv32,  \
            const us32_t *: uz32n_replaced_len_ucv32_us32,  \
            us32_t *:       uz32n_replaced_len_ucv32_us32   \
        ),                                                  \
        uv32_t: _Generic((to),                              \
            default:        uz32n_replaced_len_uv32_uc32,   \
            const uc32_t *: uz32n_replaced_len_uv32_uz32,   \
            uc32_t *:       uz32n_replaced_len_uv32_uz32,   \
            ucv32_t:        uz32n_replaced_len_uv32_ucv32,  \
            uv32_t:         uz32n_replaced_len_uv32_uv32,   \
            const us32_t *: uz32n_replaced_len_uv32_us32,   \
            us32_t *:       uz32n_replaced_len_uv32_us32    \
        ),                                                  \
        const us32_t *: _Generic((to),                      \
            default:        uz32n_replaced_len_us32_uc32,   \
            const uc32_t *: uz32n_replaced_len_us32_uz32,   \
            uc32_t *:       uz32n_replaced_len_us32_uz32,   \
            ucv32_t:        uz32n_replaced_len_us32_ucv32,  \
            uv32_t:         uz32n_replaced_len_us32_uv32,   \
            const us32_t *: uz32n_replaced_len_us32_us32,   \
            us32_t *:       uz32n_replaced_len_us32_us32    \
        )                                                   \
        us32_t *: _Generic((to),                            \
            default:        uz32n_replaced_len_us32_uc32,   \
            const uc32_t *: uz32n_replaced_len_us32_uz32,   \
            uc32_t *:       uz32n_replaced_len_us32_uz32,   \
            ucv32_t:        uz32n_replaced_len_us32_ucv32,  \
            uv32_t:         uz32n_replaced_len_us32_uv32,   \
            const us32_t *: uz32n_replaced_len_us32_us32,   \
            us32_t *:       uz32n_replaced_len_us32_us32    \
        )                                                   \
    )((cstr), (cstr_len), (from), (to))

UEXPORT size_t uz32n_replaced_len_uc32_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to);
UEXPORT size_t uz32n_replaced_len_uc32_uz32(const uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to);
UEXPORT size_t uz32n_replaced_len_uc32_uz32n(const uc32_t *cstr, size_t cstr_len, uc32_t from, size_t to_len);
UEXPORT size_t uz32n_replaced_len_uc32_ucv32(const uc32_t *cstr, size_t cstr_len, uc32_t from, ucv32_t to);
UEXPORT size_t uz32n_replaced_len_uc32_uv32(const uc32_t *cstr, size_t cstr_len, uc32_t from, uv32_t to);
UEXPORT size_t uz32n_replaced_len_uc32_us32(const uc32_t *cstr, size_t cstr_len, uc32_t from, const us32_t *to);

UEXPORT size_t uz32n_replaced_len_uz32_uc32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to);
UEXPORT size_t uz32n_replaced_len_uz32_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to);
UEXPORT size_t uz32n_replaced_len_uz32_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t to_len);
UEXPORT size_t uz32n_replaced_len_uz32_ucv32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, ucv32_t to);
UEXPORT size_t uz32n_replaced_len_uz32_uv32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, uv32_t to);
UEXPORT size_t uz32n_replaced_len_uz32_us32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const us32_t *to);

UEXPORT size_t uz32n_replaced_len_uz32n_uc32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to);
UEXPORT size_t uz32n_replaced_len_uz32n_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to);
UEXPORT size_t uz32n_replaced_len_uz32n_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, size_t to_len);
UEXPORT size_t uz32n_replaced_len_uz32n_ucv32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, ucv32_t to);
UEXPORT size_t uz32n_replaced_len_uz32n_uv32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uv32_t to);
UEXPORT size_t uz32n_replaced_len_uz32n_us32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const us32_t *to);

UEXPORT size_t uz32n_replaced_len_ucv32_uc32(const uc32_t *cstr, size_t cstr_len, ucv32_t from, uc32_t to);
UEXPORT size_t uz32n_replaced_len_ucv32_uz32(const uc32_t *cstr, size_t cstr_len, ucv32_t from, const uc32_t *to);
UEXPORT size_t uz32n_replaced_len_ucv32_uz32n(const uc32_t *cstr, size_t cstr_len, ucv32_t from, size_t to_len);
UEXPORT size_t uz32n_replaced_len_ucv32_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t from, ucv32_t to);
UEXPORT size_t uz32n_replaced_len_ucv32_uv32(const uc32_t *cstr, size_t cstr_len, ucv32_t from, uv32_t to);
UEXPORT size_t uz32n_replaced_len_ucv32_us32(const uc32_t *cstr, size_t cstr_len, ucv32_t from, const us32_t *to);

UEXPORT size_t uz32n_replaced_len_uv32_uc32(const uc32_t *cstr, size_t cstr_len, uv32_t from, uc32_t to);
UEXPORT size_t uz32n_replaced_len_uv32_uz32(const uc32_t *cstr, size_t cstr_len, uv32_t from, const uc32_t *to);
UEXPORT size_t uz32n_replaced_len_uv32_uz32n(const uc32_t *cstr, size_t cstr_len, uv32_t from, size_t to_len);
UEXPORT size_t uz32n_replaced_len_uv32_ucv32(const uc32_t *cstr, size_t cstr_len, uv32_t from, ucv32_t to);
UEXPORT size_t uz32n_replaced_len_uv32_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t from, uv32_t to);
UEXPORT size_t uz32n_replaced_len_uv32_us32(const uc32_t *cstr, size_t cstr_len, uv32_t from, const us32_t *to);

UEXPORT size_t uz32n_replaced_len_us32_uc32(const uc32_t *cstr, size_t cstr_len, const us32_t *from, uc32_t to);
UEXPORT size_t uz32n_replaced_len_us32_uz32(const uc32_t *cstr, size_t cstr_len, const us32_t *from, const uc32_t *to);
UEXPORT size_t uz32n_replaced_len_us32_uz32n(const uc32_t *cstr, size_t cstr_len, const us32_t *from, size_t to_len);
UEXPORT size_t uz32n_replaced_len_us32_ucv32(const uc32_t *cstr, size_t cstr_len, const us32_t *from, ucv32_t to);
UEXPORT size_t uz32n_replaced_len_us32_uv32(const uc32_t *cstr, size_t cstr_len, const us32_t *from, uv32_t to);
UEXPORT size_t uz32n_replaced_len_us32_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *from, const us32_t *to);

#define uz16_replaced_len(cstr, from, to)                  \
    _Generic((from),                                       \
        default: _Generic((to),                            \
            default:        uz16_replaced_len_uc16_uc16,   \
            const uc16_t *: uz16_replaced_len_uc16_uz16,   \
            uc16_t *:       uz16_replaced_len_uc16_uz16,   \
            ucv16_t:        uz16_replaced_len_uc16_ucv16,  \
            uv16_t:         uz16_replaced_len_uc16_uv16,   \
            const us16_t *: uz16_replaced_len_uc16_us16,   \
            us16_t *:       uz16_replaced_len_uc16_us16    \
        ),                                                 \
        const uc16_t *: _Generic((to),                     \
            default:        uz16_replaced_len_uz16_uc16,   \
            const uc16_t *: uz16_replaced_len_uz16_uz16,   \
            uc16_t *:       uz16_replaced_len_uz16_uz16,   \
            ucv16_t:        uz16_replaced_len_uz16_ucv16,  \
            uv16_t:         uz16_replaced_len_uz16_uv16,   \
            const us16_t *: uz16_replaced_len_uz16_us16,   \
            us16_t *:       uz16_replaced_len_uz16_us16    \
        ),                                                 \
        uc16_t *: _Generic((to),                           \
            default:        uz16_replaced_len_uz16_uc16,   \
            const uc16_t *: uz16_replaced_len_uz16_uz16,   \
            uc16_t *:       uz16_replaced_len_uz16_uz16,   \
            ucv16_t:        uz16_replaced_len_uz16_ucv16,  \
            uv16_t:         uz16_replaced_len_uz16_uv16,   \
            const us16_t *: uz16_replaced_len_uz16_us16,   \
            us16_t *:       uz16_replaced_len_uz16_us16    \
        ),                                                 \
        ucv16_t: _Generic((to),                            \
            default:        uz16_replaced_len_ucv16_uc16,  \
            const uc16_t *: uz16_replaced_len_ucv16_uz16,  \
            uc16_t *:       uz16_replaced_len_ucv16_uz16,  \
            ucv16_t:        uz16_replaced_len_ucv16_ucv16, \
            uv16_t:         uz16_replaced_len_ucv16_uv16,  \
            const us16_t *: uz16_replaced_len_ucv16_us16,  \
            us16_t *:       uz16_replaced_len_ucv16_us16   \
        ),                                                 \
        uv16_t: _Generic((to),                             \
            default:        uz16_replaced_len_uv16_uc16,   \
            const uc16_t *: uz16_replaced_len_uv16_uz16,   \
            uc16_t *:       uz16_replaced_len_uv16_uz16,   \
            ucv16_t:        uz16_replaced_len_uv16_ucv16,  \
            uv16_t:         uz16_replaced_len_uv16_uv16,   \
            const us16_t *: uz16_replaced_len_uv16_us16,   \
            us16_t *:       uz16_replaced_len_uv16_us16    \
        ),                                                 \
        const us16_t *: _Generic((to),                     \
            default:        uz16_replaced_len_us16_uc16,   \
            const uc16_t *: uz16_replaced_len_us16_uz16,   \
            uc16_t *:       uz16_replaced_len_us16_uz16,   \
            ucv16_t:        uz16_replaced_len_us16_ucv16,  \
            uv16_t:         uz16_replaced_len_us16_uv16,   \
            const us16_t *: uz16_replaced_len_us16_us16,   \
            us16_t *:       uz16_replaced_len_us16_us16    \
        )                                                  \
        us16_t *: _Generic((to),                           \
            default:        uz16_replaced_len_us16_uc16,   \
            const uc16_t *: uz16_replaced_len_us16_uz16,   \
            uc16_t *:       uz16_replaced_len_us16_uz16,   \
            ucv16_t:        uz16_replaced_len_us16_ucv16,  \
            uv16_t:         uz16_replaced_len_us16_uv16,   \
            const us16_t *: uz16_replaced_len_us16_us16,   \
            us16_t *:       uz16_replaced_len_us16_us16    \
        )                                                  \
    )((cstr), (from), (to))

UEXPORT size_t uz16_replaced_len_uc16_uc16(const uc16_t *cstr, uc16_t from, uc16_t to);
UEXPORT size_t uz16_replaced_len_uc16_uz16(const uc16_t *cstr, uc16_t from, const uc16_t *to);
UEXPORT size_t uz16_replaced_len_uc16_uz16n(const uc16_t *cstr, uc16_t from, size_t to_len);
UEXPORT size_t uz16_replaced_len_uc16_ucv16(const uc16_t *cstr, uc16_t from, ucv16_t to);
UEXPORT size_t uz16_replaced_len_uc16_uv16(const uc16_t *cstr, uc16_t from, uv16_t to);
UEXPORT size_t uz16_replaced_len_uc16_us16(const uc16_t *cstr, uc16_t from, const us16_t *to);

UEXPORT size_t uz16_replaced_len_uz16_uc16(const uc16_t *cstr, const uc16_t *from, uc16_t to);
UEXPORT size_t uz16_replaced_len_uz16_uz16(const uc16_t *cstr, const uc16_t *from, const uc16_t *to);
UEXPORT size_t uz16_replaced_len_uz16_uz16n(const uc16_t *cstr, const uc16_t *from, size_t to_len);
UEXPORT size_t uz16_replaced_len_uz16_ucv16(const uc16_t *cstr, const uc16_t *from, ucv16_t to);
UEXPORT size_t uz16_replaced_len_uz16_uv16(const uc16_t *cstr, const uc16_t *from, uv16_t to);
UEXPORT size_t uz16_replaced_len_uz16_us16(const uc16_t *cstr, const uc16_t *from, const us16_t *to);

UEXPORT size_t uz16_replaced_len_uz16n_uc16(const uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to);
UEXPORT size_t uz16_replaced_len_uz16n_uz16(const uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to);
UEXPORT size_t uz16_replaced_len_uz16n_uz16n(const uc16_t *cstr, const uc16_t *from, size_t from_len, size_t to_len);
UEXPORT size_t uz16_replaced_len_uz16n_ucv16(const uc16_t *cstr, const uc16_t *from, size_t from_len, ucv16_t to);
UEXPORT size_t uz16_replaced_len_uz16n_uv16(const uc16_t *cstr, const uc16_t *from, size_t from_len, uv16_t to);
UEXPORT size_t uz16_replaced_len_uz16n_us16(const uc16_t *cstr, const uc16_t *from, size_t from_len, const us16_t *to);

UEXPORT size_t uz16_replaced_len_ucv16_uc16(const uc16_t *cstr, ucv16_t from, uc16_t to);
UEXPORT size_t uz16_replaced_len_ucv16_uz16(const uc16_t *cstr, ucv16_t from, const uc16_t *to);
UEXPORT size_t uz16_replaced_len_ucv16_uz16n(const uc16_t *cstr, ucv16_t from, size_t to_len);
UEXPORT size_t uz16_replaced_len_ucv16_ucv16(const uc16_t *cstr, ucv16_t from, ucv16_t to);
UEXPORT size_t uz16_replaced_len_ucv16_uv16(const uc16_t *cstr, ucv16_t from, uv16_t to);
UEXPORT size_t uz16_replaced_len_ucv16_us16(const uc16_t *cstr, ucv16_t from, const us16_t *to);

UEXPORT size_t uz16_replaced_len_uv16_uc16(const uc16_t *cstr, uv16_t from, uc16_t to);
UEXPORT size_t uz16_replaced_len_uv16_uz16(const uc16_t *cstr, uv16_t from, const uc16_t *to);
UEXPORT size_t uz16_replaced_len_uv16_uz16n(const uc16_t *cstr, uv16_t from, size_t to_len);
UEXPORT size_t uz16_replaced_len_uv16_ucv16(const uc16_t *cstr, uv16_t from, ucv16_t to);
UEXPORT size_t uz16_replaced_len_uv16_uv16(const uc16_t *cstr, uv16_t from, uv16_t to);
UEXPORT size_t uz16_replaced_len_uv16_us16(const uc16_t *cstr, uv16_t from, const us16_t *to);

UEXPORT size_t uz16_replaced_len_us16_uc16(const uc16_t *cstr, const us16_t *from, uc16_t to);
UEXPORT size_t uz16_replaced_len_us16_uz16(const uc16_t *cstr, const us16_t *from, const uc16_t *to);
UEXPORT size_t uz16_replaced_len_us16_uz16n(const uc16_t *cstr, const us16_t *from, size_t to_len);
UEXPORT size_t uz16_replaced_len_us16_ucv16(const uc16_t *cstr, const us16_t *from, ucv16_t to);
UEXPORT size_t uz16_replaced_len_us16_uv16(const uc16_t *cstr, const us16_t *from, uv16_t to);
UEXPORT size_t uz16_replaced_len_us16_us16(const uc16_t *cstr, const us16_t *from, const us16_t *to);

#define uz16n_replaced_len(cstr, cstr_len, from, to)        \
    _Generic((from),                                        \
        default: _Generic((to),                             \
            default:        uz16n_replaced_len_uc16_uc16,   \
            const uc16_t *: uz16n_replaced_len_uc16_uz16,   \
            uc16_t *:       uz16n_replaced_len_uc16_uz16,   \
            ucv16_t:        uz16n_replaced_len_uc16_ucv16,  \
            uv16_t:         uz16n_replaced_len_uc16_uv16,   \
            const us16_t *: uz16n_replaced_len_uc16_us16,   \
            us16_t *:       uz16n_replaced_len_uc16_us16    \
        ),                                                  \
        const uc16_t *: _Generic((to),                      \
            default:        uz16n_replaced_len_uz16_uc16,   \
            const uc16_t *: uz16n_replaced_len_uz16_uz16,   \
            uc16_t *:       uz16n_replaced_len_uz16_uz16,   \
            ucv16_t:        uz16n_replaced_len_uz16_ucv16,  \
            uv16_t:         uz16n_replaced_len_uz16_uv16,   \
            const us16_t *: uz16n_replaced_len_uz16_us16,   \
            us16_t *:       uz16n_replaced_len_uz16_us16    \
        ),                                                  \
        uc16_t *: _Generic((to),                            \
            default:        uz16n_replaced_len_uz16_uc16,   \
            const uc16_t *: uz16n_replaced_len_uz16_uz16,   \
            uc16_t *:       uz16n_replaced_len_uz16_uz16,   \
            ucv16_t:        uz16n_replaced_len_uz16_ucv16,  \
            uv16_t:         uz16n_replaced_len_uz16_uv16,   \
            const us16_t *: uz16n_replaced_len_uz16_us16,   \
            us16_t *:       uz16n_replaced_len_uz16_us16    \
        ),                                                  \
        ucv16_t: _Generic((to),                             \
            default:        uz16n_replaced_len_ucv16_uc16,  \
            const uc16_t *: uz16n_replaced_len_ucv16_uz16,  \
            uc16_t *:       uz16n_replaced_len_ucv16_uz16,  \
            ucv16_t:        uz16n_replaced_len_ucv16_ucv16, \
            uv16_t:         uz16n_replaced_len_ucv16_uv16,  \
            const us16_t *: uz16n_replaced_len_ucv16_us16,  \
            us16_t *:       uz16n_replaced_len_ucv16_us16   \
        ),                                                  \
        uv16_t: _Generic((to),                              \
            default:        uz16n_replaced_len_uv16_uc16,   \
            const uc16_t *: uz16n_replaced_len_uv16_uz16,   \
            uc16_t *:       uz16n_replaced_len_uv16_uz16,   \
            ucv16_t:        uz16n_replaced_len_uv16_ucv16,  \
            uv16_t:         uz16n_replaced_len_uv16_uv16,   \
            const us16_t *: uz16n_replaced_len_uv16_us16,   \
            us16_t *:       uz16n_replaced_len_uv16_us16    \
        ),                                                  \
        const us16_t *: _Generic((to),                      \
            default:        uz16n_replaced_len_us16_uc16,   \
            const uc16_t *: uz16n_replaced_len_us16_uz16,   \
            uc16_t *:       uz16n_replaced_len_us16_uz16,   \
            ucv16_t:        uz16n_replaced_len_us16_ucv16,  \
            uv16_t:         uz16n_replaced_len_us16_uv16,   \
            const us16_t *: uz16n_replaced_len_us16_us16,   \
            us16_t *:       uz16n_replaced_len_us16_us16    \
        )                                                   \
        us16_t *: _Generic((to),                            \
            default:        uz16n_replaced_len_us16_uc16,   \
            const uc16_t *: uz16n_replaced_len_us16_uz16,   \
            uc16_t *:       uz16n_replaced_len_us16_uz16,   \
            ucv16_t:        uz16n_replaced_len_us16_ucv16,  \
            uv16_t:         uz16n_replaced_len_us16_uv16,   \
            const us16_t *: uz16n_replaced_len_us16_us16,   \
            us16_t *:       uz16n_replaced_len_us16_us16    \
        )                                                   \
    )((cstr), (cstr_len), (from), (to))

UEXPORT size_t uz16n_replaced_len_uc16_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to);
UEXPORT size_t uz16n_replaced_len_uc16_uz16(const uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to);
UEXPORT size_t uz16n_replaced_len_uc16_uz16n(const uc16_t *cstr, size_t cstr_len, uc16_t from, size_t to_len);
UEXPORT size_t uz16n_replaced_len_uc16_ucv16(const uc16_t *cstr, size_t cstr_len, uc16_t from, ucv16_t to);
UEXPORT size_t uz16n_replaced_len_uc16_uv16(const uc16_t *cstr, size_t cstr_len, uc16_t from, uv16_t to);
UEXPORT size_t uz16n_replaced_len_uc16_us16(const uc16_t *cstr, size_t cstr_len, uc16_t from, const us16_t *to);

UEXPORT size_t uz16n_replaced_len_uz16_uc16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to);
UEXPORT size_t uz16n_replaced_len_uz16_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to);
UEXPORT size_t uz16n_replaced_len_uz16_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t to_len);
UEXPORT size_t uz16n_replaced_len_uz16_ucv16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, ucv16_t to);
UEXPORT size_t uz16n_replaced_len_uz16_uv16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, uv16_t to);
UEXPORT size_t uz16n_replaced_len_uz16_us16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const us16_t *to);

UEXPORT size_t uz16n_replaced_len_uz16n_uc16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to);
UEXPORT size_t uz16n_replaced_len_uz16n_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to);
UEXPORT size_t uz16n_replaced_len_uz16n_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, size_t to_len);
UEXPORT size_t uz16n_replaced_len_uz16n_ucv16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, ucv16_t to);
UEXPORT size_t uz16n_replaced_len_uz16n_uv16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uv16_t to);
UEXPORT size_t uz16n_replaced_len_uz16n_us16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const us16_t *to);

UEXPORT size_t uz16n_replaced_len_ucv16_uc16(const uc16_t *cstr, size_t cstr_len, ucv16_t from, uc16_t to);
UEXPORT size_t uz16n_replaced_len_ucv16_uz16(const uc16_t *cstr, size_t cstr_len, ucv16_t from, const uc16_t *to);
UEXPORT size_t uz16n_replaced_len_ucv16_uz16n(const uc16_t *cstr, size_t cstr_len, ucv16_t from, size_t to_len);
UEXPORT size_t uz16n_replaced_len_ucv16_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t from, ucv16_t to);
UEXPORT size_t uz16n_replaced_len_ucv16_uv16(const uc16_t *cstr, size_t cstr_len, ucv16_t from, uv16_t to);
UEXPORT size_t uz16n_replaced_len_ucv16_us16(const uc16_t *cstr, size_t cstr_len, ucv16_t from, const us16_t *to);

UEXPORT size_t uz16n_replaced_len_uv16_uc16(const uc16_t *cstr, size_t cstr_len, uv16_t from, uc16_t to);
UEXPORT size_t uz16n_replaced_len_uv16_uz16(const uc16_t *cstr, size_t cstr_len, uv16_t from, const uc16_t *to);
UEXPORT size_t uz16n_replaced_len_uv16_uz16n(const uc16_t *cstr, size_t cstr_len, uv16_t from, size_t to_len);
UEXPORT size_t uz16n_replaced_len_uv16_ucv16(const uc16_t *cstr, size_t cstr_len, uv16_t from, ucv16_t to);
UEXPORT size_t uz16n_replaced_len_uv16_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t from, uv16_t to);
UEXPORT size_t uz16n_replaced_len_uv16_us16(const uc16_t *cstr, size_t cstr_len, uv16_t from, const us16_t *to);

UEXPORT size_t uz16n_replaced_len_us16_uc16(const uc16_t *cstr, size_t cstr_len, const us16_t *from, uc16_t to);
UEXPORT size_t uz16n_replaced_len_us16_uz16(const uc16_t *cstr, size_t cstr_len, const us16_t *from, const uc16_t *to);
UEXPORT size_t uz16n_replaced_len_us16_uz16n(const uc16_t *cstr, size_t cstr_len, const us16_t *from, size_t to_len);
UEXPORT size_t uz16n_replaced_len_us16_ucv16(const uc16_t *cstr, size_t cstr_len, const us16_t *from, ucv16_t to);
UEXPORT size_t uz16n_replaced_len_us16_uv16(const uc16_t *cstr, size_t cstr_len, const us16_t *from, uv16_t to);
UEXPORT size_t uz16n_replaced_len_us16_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *from, const us16_t *to);


#define uz8_replaced_len(cstr, from, to)               \
    _Generic((from),                                   \
        default: _Generic((to),                        \
            default:       uz8_replaced_len_uc8_uc8,   \
            const uc8_t *: uz8_replaced_len_uc8_uz8,   \
            uc8_t *:       uz8_replaced_len_uc8_uz8,   \
            ucv8_t:        uz8_replaced_len_uc8_ucv8,  \
            uv8_t:         uz8_replaced_len_uc8_uv8,   \
            const us8_t *: uz8_replaced_len_uc8_us8,   \
            us8_t *:       uz8_replaced_len_uc8_us8    \
        ),                                             \
        const uc8_t *: _Generic((to),                  \
            default:       uz8_replaced_len_uz8_uc8,   \
            const uc8_t *: uz8_replaced_len_uz8_uz8,   \
            uc8_t *:       uz8_replaced_len_uz8_uz8,   \
            ucv8_t:        uz8_replaced_len_uz8_ucv8,  \
            uv8_t:         uz8_replaced_len_uz8_uv8,   \
            const us8_t *: uz8_replaced_len_uz8_us8,   \
            us8_t *:       uz8_replaced_len_uz8_us8    \
        ),                                             \
        uc8_t *: _Generic((to),                        \
            default:       uz8_replaced_len_uz8_uc8,   \
            const uc8_t *: uz8_replaced_len_uz8_uz8,   \
            uc8_t *:       uz8_replaced_len_uz8_uz8,   \
            ucv8_t:        uz8_replaced_len_uz8_ucv8,  \
            uv8_t:         uz8_replaced_len_uz8_uv8,   \
            const us8_t *: uz8_replaced_len_uz8_us8,   \
            us8_t *:       uz8_replaced_len_uz8_us8    \
        ),                                             \
        ucv8_t: _Generic((to),                         \
            default:       uz8_replaced_len_ucv8_uc8,  \
            const uc8_t *: uz8_replaced_len_ucv8_uz8,  \
            uc8_t *:       uz8_replaced_len_ucv8_uz8,  \
            ucv8_t:        uz8_replaced_len_ucv8_ucv8, \
            uv8_t:         uz8_replaced_len_ucv8_uv8,  \
            const us8_t *: uz8_replaced_len_ucv8_us8,  \
            us8_t *:       uz8_replaced_len_ucv8_us8   \
        ),                                             \
        uv8_t: _Generic((to),                          \
            default:       uz8_replaced_len_uv8_uc8,   \
            const uc8_t *: uz8_replaced_len_uv8_uz8,   \
            uc8_t *:       uz8_replaced_len_uv8_uz8,   \
            ucv8_t:        uz8_replaced_len_uv8_ucv8,  \
            uv8_t:         uz8_replaced_len_uv8_uv8,   \
            const us8_t *: uz8_replaced_len_uv8_us8,   \
            us8_t *:       uz8_replaced_len_uv8_us8    \
        ),                                             \
        const us8_t *: _Generic((to),                  \
            default:       uz8_replaced_len_us8_uc8,   \
            const uc8_t *: uz8_replaced_len_us8_uz8,   \
            uc8_t *:       uz8_replaced_len_us8_uz8,   \
            ucv8_t:        uz8_replaced_len_us8_ucv8,  \
            uv8_t:         uz8_replaced_len_us8_uv8,   \
            const us8_t *: uz8_replaced_len_us8_us8,   \
            us8_t *:       uz8_replaced_len_us8_us8    \
        )                                              \
        us8_t *: _Generic((to),                        \
            default:       uz8_replaced_len_us8_uc8,   \
            const uc8_t *: uz8_replaced_len_us8_uz8,   \
            uc8_t *:       uz8_replaced_len_us8_uz8,   \
            ucv8_t:        uz8_replaced_len_us8_ucv8,  \
            uv8_t:         uz8_replaced_len_us8_uv8,   \
            const us8_t *: uz8_replaced_len_us8_us8,   \
            us8_t *:       uz8_replaced_len_us8_us8    \
        )                                              \
    )((cstr), (from), (to))

UEXPORT size_t uz8_replaced_len_uc8_uc8(const uc8_t *cstr, uc8_t from, uc8_t to);
UEXPORT size_t uz8_replaced_len_uc8_uz8(const uc8_t *cstr, uc8_t from, const uc8_t *to);
UEXPORT size_t uz8_replaced_len_uc8_uz8n(const uc8_t *cstr, uc8_t from, size_t to_len);
UEXPORT size_t uz8_replaced_len_uc8_ucv8(const uc8_t *cstr, uc8_t from, ucv8_t to);
UEXPORT size_t uz8_replaced_len_uc8_uv8(const uc8_t *cstr, uc8_t from, uv8_t to);
UEXPORT size_t uz8_replaced_len_uc8_us8(const uc8_t *cstr, uc8_t from, const us8_t *to);

UEXPORT size_t uz8_replaced_len_uz8_uc8(const uc8_t *cstr, const uc8_t *from, uc8_t to);
UEXPORT size_t uz8_replaced_len_uz8_uz8(const uc8_t *cstr, const uc8_t *from, const uc8_t *to);
UEXPORT size_t uz8_replaced_len_uz8_uz8n(const uc8_t *cstr, const uc8_t *from, size_t to_len);
UEXPORT size_t uz8_replaced_len_uz8_ucv8(const uc8_t *cstr, const uc8_t *from, ucv8_t to);
UEXPORT size_t uz8_replaced_len_uz8_uv8(const uc8_t *cstr, const uc8_t *from, uv8_t to);
UEXPORT size_t uz8_replaced_len_uz8_us8(const uc8_t *cstr, const uc8_t *from, const us8_t *to);

UEXPORT size_t uz8_replaced_len_uz8n_uc8(const uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to);
UEXPORT size_t uz8_replaced_len_uz8n_uz8(const uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to);
UEXPORT size_t uz8_replaced_len_uz8n_uz8n(const uc8_t *cstr, const uc8_t *from, size_t from_len, size_t to_len);
UEXPORT size_t uz8_replaced_len_uz8n_ucv8(const uc8_t *cstr, const uc8_t *from, size_t from_len, ucv8_t to);
UEXPORT size_t uz8_replaced_len_uz8n_uv8(const uc8_t *cstr, const uc8_t *from, size_t from_len, uv8_t to);
UEXPORT size_t uz8_replaced_len_uz8n_us8(const uc8_t *cstr, const uc8_t *from, size_t from_len, const us8_t *to);

UEXPORT size_t uz8_replaced_len_ucv8_uc8(const uc8_t *cstr, ucv8_t from, uc8_t to);
UEXPORT size_t uz8_replaced_len_ucv8_uz8(const uc8_t *cstr, ucv8_t from, const uc8_t *to);
UEXPORT size_t uz8_replaced_len_ucv8_uz8n(const uc8_t *cstr, ucv8_t from, size_t to_len);
UEXPORT size_t uz8_replaced_len_ucv8_ucv8(const uc8_t *cstr, ucv8_t from, ucv8_t to);
UEXPORT size_t uz8_replaced_len_ucv8_uv8(const uc8_t *cstr, ucv8_t from, uv8_t to);
UEXPORT size_t uz8_replaced_len_ucv8_us8(const uc8_t *cstr, ucv8_t from, const us8_t *to);

UEXPORT size_t uz8_replaced_len_uv8_uc8(const uc8_t *cstr, uv8_t from, uc8_t to);
UEXPORT size_t uz8_replaced_len_uv8_uz8(const uc8_t *cstr, uv8_t from, const uc8_t *to);
UEXPORT size_t uz8_replaced_len_uv8_uz8n(const uc8_t *cstr, uv8_t from, size_t to_len);
UEXPORT size_t uz8_replaced_len_uv8_ucv8(const uc8_t *cstr, uv8_t from, ucv8_t to);
UEXPORT size_t uz8_replaced_len_uv8_uv8(const uc8_t *cstr, uv8_t from, uv8_t to);
UEXPORT size_t uz8_replaced_len_uv8_us8(const uc8_t *cstr, uv8_t from, const us8_t *to);

UEXPORT size_t uz8_replaced_len_us8_uc8(const uc8_t *cstr, const us8_t *from, uc8_t to);
UEXPORT size_t uz8_replaced_len_us8_uz8(const uc8_t *cstr, const us8_t *from, const uc8_t *to);
UEXPORT size_t uz8_replaced_len_us8_uz8n(const uc8_t *cstr, const us8_t *from, size_t to_len);
UEXPORT size_t uz8_replaced_len_us8_ucv8(const uc8_t *cstr, const us8_t *from, ucv8_t to);
UEXPORT size_t uz8_replaced_len_us8_uv8(const uc8_t *cstr, const us8_t *from, uv8_t to);
UEXPORT size_t uz8_replaced_len_us8_us8(const uc8_t *cstr, const us8_t *from, const us8_t *to);


#define uz8n_replaced_len(cstr, cstr_len, from, to)     \
    _Generic((from),                                    \
        default: _Generic((to),                         \
            default:       uz8n_replaced_len_uc8_uc8,   \
            const uc8_t *: uz8n_replaced_len_uc8_uz8,   \
            uc8_t *:       uz8n_replaced_len_uc8_uz8,   \
            ucv8_t:        uz8n_replaced_len_uc8_ucv8,  \
            uv8_t:         uz8n_replaced_len_uc8_uv8,   \
            const us8_t *: uz8n_replaced_len_uc8_us8,   \
            us8_t *:       uz8n_replaced_len_uc8_us8    \
        ),                                              \
        const uc8_t *: _Generic((to),                   \
            default:       uz8n_replaced_len_uz8_uc8,   \
            const uc8_t *: uz8n_replaced_len_uz8_uz8,   \
            uc8_t *:       uz8n_replaced_len_uz8_uz8,   \
            ucv8_t:        uz8n_replaced_len_uz8_ucv8,  \
            uv8_t:         uz8n_replaced_len_uz8_uv8,   \
            const us8_t *: uz8n_replaced_len_uz8_us8,   \
            us8_t *:       uz8n_replaced_len_uz8_us8    \
        ),                                              \
        uc8_t *: _Generic((to),                         \
            default:       uz8n_replaced_len_uz8_uc8,   \
            const uc8_t *: uz8n_replaced_len_uz8_uz8,   \
            uc8_t *:       uz8n_replaced_len_uz8_uz8,   \
            ucv8_t:        uz8n_replaced_len_uz8_ucv8,  \
            uv8_t:         uz8n_replaced_len_uz8_uv8,   \
            const us8_t *: uz8n_replaced_len_uz8_us8,   \
            us8_t *:       uz8n_replaced_len_uz8_us8    \
        ),                                              \
        ucv8_t: _Generic((to),                          \
            default:       uz8n_replaced_len_ucv8_uc8,  \
            const uc8_t *: uz8n_replaced_len_ucv8_uz8,  \
            uc8_t *:       uz8n_replaced_len_ucv8_uz8,  \
            ucv8_t:        uz8n_replaced_len_ucv8_ucv8, \
            uv8_t:         uz8n_replaced_len_ucv8_uv8,  \
            const us8_t *: uz8n_replaced_len_ucv8_us8,  \
            us8_t *:       uz8n_replaced_len_ucv8_us8   \
        ),                                              \
        uv8_t: _Generic((to),                           \
            default:       uz8n_replaced_len_uv8_uc8,   \
            const uc8_t *: uz8n_replaced_len_uv8_uz8,   \
            uc8_t *:       uz8n_replaced_len_uv8_uz8,   \
            ucv8_t:        uz8n_replaced_len_uv8_ucv8,  \
            uv8_t:         uz8n_replaced_len_uv8_uv8,   \
            const us8_t *: uz8n_replaced_len_uv8_us8,   \
            us8_t *:       uz8n_replaced_len_uv8_us8    \
        ),                                              \
        const us8_t *: _Generic((to),                   \
            default:       uz8n_replaced_len_us8_uc8,   \
            const uc8_t *: uz8n_replaced_len_us8_uz8,   \
            uc8_t *:       uz8n_replaced_len_us8_uz8,   \
            ucv8_t:        uz8n_replaced_len_us8_ucv8,  \
            uv8_t:         uz8n_replaced_len_us8_uv8,   \
            const us8_t *: uz8n_replaced_len_us8_us8,   \
            us8_t *:       uz8n_replaced_len_us8_us8    \
        )                                               \
        us8_t *: _Generic((to),                         \
            default:       uz8n_replaced_len_us8_uc8,   \
            const uc8_t *: uz8n_replaced_len_us8_uz8,   \
            uc8_t *:       uz8n_replaced_len_us8_uz8,   \
            ucv8_t:        uz8n_replaced_len_us8_ucv8,  \
            uv8_t:         uz8n_replaced_len_us8_uv8,   \
            const us8_t *: uz8n_replaced_len_us8_us8,   \
            us8_t *:       uz8n_replaced_len_us8_us8    \
        )                                               \
    )((cstr), (cstr_len), (from), (to))

UEXPORT size_t uz8n_replaced_len_uc8_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to);
UEXPORT size_t uz8n_replaced_len_uc8_uz8(const uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to);
UEXPORT size_t uz8n_replaced_len_uc8_uz8n(const uc8_t *cstr, size_t cstr_len, uc8_t from, size_t to_len);
UEXPORT size_t uz8n_replaced_len_uc8_ucv8(const uc8_t *cstr, size_t cstr_len, uc8_t from, ucv8_t to);
UEXPORT size_t uz8n_replaced_len_uc8_uv8(const uc8_t *cstr, size_t cstr_len, uc8_t from, uv8_t to);
UEXPORT size_t uz8n_replaced_len_uc8_us8(const uc8_t *cstr, size_t cstr_len, uc8_t from, const us8_t *to);

UEXPORT size_t uz8n_replaced_len_uz8_uc8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to);
UEXPORT size_t uz8n_replaced_len_uz8_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to);
UEXPORT size_t uz8n_replaced_len_uz8_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t to_len);
UEXPORT size_t uz8n_replaced_len_uz8_ucv8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, ucv8_t to);
UEXPORT size_t uz8n_replaced_len_uz8_uv8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, uv8_t to);
UEXPORT size_t uz8n_replaced_len_uz8_us8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const us8_t *to);

UEXPORT size_t uz8n_replaced_len_uz8n_uc8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to);
UEXPORT size_t uz8n_replaced_len_uz8n_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to);
UEXPORT size_t uz8n_replaced_len_uz8n_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, size_t to_len);
UEXPORT size_t uz8n_replaced_len_uz8n_ucv8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, ucv8_t to);
UEXPORT size_t uz8n_replaced_len_uz8n_uv8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uv8_t to);
UEXPORT size_t uz8n_replaced_len_uz8n_us8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const us8_t *to);

UEXPORT size_t uz8n_replaced_len_ucv8_uc8(const uc8_t *cstr, size_t cstr_len, ucv8_t from, uc8_t to);
UEXPORT size_t uz8n_replaced_len_ucv8_uz8(const uc8_t *cstr, size_t cstr_len, ucv8_t from, const uc8_t *to);
UEXPORT size_t uz8n_replaced_len_ucv8_uz8n(const uc8_t *cstr, size_t cstr_len, ucv8_t from, size_t to_len);
UEXPORT size_t uz8n_replaced_len_ucv8_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t from, ucv8_t to);
UEXPORT size_t uz8n_replaced_len_ucv8_uv8(const uc8_t *cstr, size_t cstr_len, ucv8_t from, uv8_t to);
UEXPORT size_t uz8n_replaced_len_ucv8_us8(const uc8_t *cstr, size_t cstr_len, ucv8_t from, const us8_t *to);

UEXPORT size_t uz8n_replaced_len_uv8_uc8(const uc8_t *cstr, size_t cstr_len, uv8_t from, uc8_t to);
UEXPORT size_t uz8n_replaced_len_uv8_uz8(const uc8_t *cstr, size_t cstr_len, uv8_t from, const uc8_t *to);
UEXPORT size_t uz8n_replaced_len_uv8_uz8n(const uc8_t *cstr, size_t cstr_len, uv8_t from, size_t to_len);
UEXPORT size_t uz8n_replaced_len_uv8_ucv8(const uc8_t *cstr, size_t cstr_len, uv8_t from, ucv8_t to);
UEXPORT size_t uz8n_replaced_len_uv8_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t from, uv8_t to);
UEXPORT size_t uz8n_replaced_len_uv8_us8(const uc8_t *cstr, size_t cstr_len, uv8_t from, const us8_t *to);

UEXPORT size_t uz8n_replaced_len_us8_uc8(const uc8_t *cstr, size_t cstr_len, const us8_t *from, uc8_t to);
UEXPORT size_t uz8n_replaced_len_us8_uz8(const uc8_t *cstr, size_t cstr_len, const us8_t *from, const uc8_t *to);
UEXPORT size_t uz8n_replaced_len_us8_uz8n(const uc8_t *cstr, size_t cstr_len, const us8_t *from, size_t to_len);
UEXPORT size_t uz8n_replaced_len_us8_ucv8(const uc8_t *cstr, size_t cstr_len, const us8_t *from, ucv8_t to);
UEXPORT size_t uz8n_replaced_len_us8_uv8(const uc8_t *cstr, size_t cstr_len, const us8_t *from, uv8_t to);
UEXPORT size_t uz8n_replaced_len_us8_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *from, const us8_t *to);

// Count

#define uz32_count(cstr, target)          \
    _Generic((target),                    \
        default:        uz32_count_uc32,  \
        const uc32_t *: uz32n_count_uz32, \
        uc32_t *:       uz32_count_uz32,  \
        ucv32_t:        uz32_count_ucv32, \
        uv32_t:         uz32_count_uv32,  \
        const us32_t *: uz32_count_us32,  \
        us32_t *:       uz32_count_us32   \
    )((cstr), (target))

UEXPORT size_t uz32_count_uc32(const uc32_t *cstr, uc32_t target);
UEXPORT size_t uz32_count_uz32(const uc32_t *cstr, const uc32_t *target);
UEXPORT size_t uz32_count_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len);
UEXPORT size_t uz32_count_ucv32(const uc32_t *cstr, ucv32_t target);
UEXPORT size_t uz32_count_uv32(const uc32_t *cstr, uv32_t target);
UEXPORT size_t uz32_count_us32(const uc32_t *cstr, const us32_t *target);

#define uz32n_count(cstr, cstr_len, target) \
    _Generic((target),                      \
        default:        uz32n_count_uc32,   \
        const uc32_t *: uz32n_count_uz32,   \
        uc32_t *:       uz32n_count_uz32,   \
        ucv32_t:        uz32n_count_ucv32,  \
        uv32_t:         uz32n_count_uv32,   \
        const us32_t *: uz32n_count_us32,   \
        us32_t *:       uz32n_count_us32    \
    )((cstr), (cstr_len), (target))

UEXPORT size_t uz32n_count_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target);
UEXPORT size_t uz32n_count_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target);
UEXPORT size_t uz32n_count_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len);
UEXPORT size_t uz32n_count_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target);
UEXPORT size_t uz32n_count_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target);
UEXPORT size_t uz32n_count_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target);

#define uz16_count(cstr, target)          \
    _Generic((target),                    \
        default:        uz16_count_uc16,  \
        const uc16_t *: uz16_count_uz16,  \
        uc16_t *:       uz16_count_uz16,  \
        ucv16_t:        uz16_count_ucv16, \
        uv16_t:         uz16_count_uv16,  \
        const us16_t *: uz16_count_us16,  \
        us16_t *:       uz16_count_us16   \
    )((cstr), (target))

UEXPORT size_t uz16_count_uc16(const uc16_t *cstr, uc16_t target);
UEXPORT size_t uz16_count_uz16(const uc16_t *cstr, const uc16_t *target);
UEXPORT size_t uz16_count_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len);
UEXPORT size_t uz16_count_ucv16(const uc16_t *cstr, ucv16_t target);
UEXPORT size_t uz16_count_uv16(const uc16_t *cstr, uv16_t target);
UEXPORT size_t uz16_count_us16(const uc16_t *cstr, const us16_t *target);

#define uz16n_count(cstr, cstr_len, target) \
    _Generic((target),                      \
        default:        uz16n_count_uc16,   \
        const uc16_t *: uz16_count_uz16,    \
        uc16_t *:       uz16n_count_uz16,   \
        ucv16_t:        uz16n_count_ucv16,  \
        uv16_t:         uz16n_count_uv16,   \
        const us16_t *: uz16n_count_us16,   \
        us16_t *:       uz16n_count_us16    \
    )((cstr), (cstr_len), (target))

UEXPORT size_t uz16n_count_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target);
UEXPORT size_t uz16n_count_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target);
UEXPORT size_t uz16n_count_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len);
UEXPORT size_t uz16n_count_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target);
UEXPORT size_t uz16n_count_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target);
UEXPORT size_t uz16n_count_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target);

#define uz8_count(cstr, target)        \
    _Generic((target),                 \
        default:       uz8_count_uc8,  \
        const uc8_t *: uz8_count_uz8,  \
        uc8_t *:       uz8_count_uz8,  \
        ucv8_t:        uz8_count_ucv8, \
        uv8_t:         uz8_count_uv8,  \
        const us8_t *: uz8_count_us8,  \
        us8_t *:       uz8_count_us8   \
    )((cstr), (target))

UEXPORT size_t uz8_count_uc8(const uc8_t *cstr, uc8_t target);
UEXPORT size_t uz8_count_uz8(const uc8_t *cstr, const uc8_t *target);
UEXPORT size_t uz8_count_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len);
UEXPORT size_t uz8_count_ucv8(const uc8_t *cstr, ucv8_t target);
UEXPORT size_t uz8_count_uv8(const uc8_t *cstr, uv8_t target);
UEXPORT size_t uz8_count_us8(const uc8_t *cstr, const us8_t *target);

#define uz8n_count(cstr, cstr_len, target) \
    _Generic((target),                     \
        default:       uz8n_count_uc8,     \
        const uc8_t *: uz8_count_uz8,      \
        uc8_t *:       uz8n_count_uz8,     \
        ucv8_t:        uz8n_count_ucv8,    \
        uv8_t:         uz8n_count_uv8,     \
        const us8_t *: uz8n_count_us8,     \
        us8_t *:       uz8n_count_us8      \
    )((cstr), (cstr_len), (target))

UEXPORT size_t uz8n_count_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target);
UEXPORT size_t uz8n_count_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target);
UEXPORT size_t uz8n_count_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len);
UEXPORT size_t uz8n_count_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target);
UEXPORT size_t uz8n_count_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target);
UEXPORT size_t uz8n_count_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target);

// Bounds

UEXPORT bool uz32_bounds(const uc32_t *cstr, size_t index);
UEXPORT bool uz32_ebounds(const uc32_t *cstr, size_t index);
UEXPORT bool uz32_bounds_range(const uc32_t *cstr, size_t begin, size_t len);
UEXPORT bool uz32_ebounds_range(const uc32_t *cstr, size_t begin, size_t len);

UEXPORT bool uz16_bounds(const uc16_t *cstr, size_t index);
UEXPORT bool uz16_ebounds(const uc16_t *cstr, size_t index);
UEXPORT bool uz16_bounds_range(const uc16_t *cstr, size_t begin, size_t len);
UEXPORT bool uz16_ebounds_range(const uc16_t *cstr, size_t begin, size_t len);

UEXPORT bool uz8_bounds(const uc8_t *cstr, size_t index);
UEXPORT bool uz8_ebounds(const uc8_t *cstr, size_t index);
UEXPORT bool uz8_bounds_range(const uc8_t *cstr, size_t begin, size_t len);
UEXPORT bool uz8_ebounds_range(const uc8_t *cstr, size_t begin, size_t len);

UEXPORT bool ubounds_range(size_t len, size_t range_begin, size_t range_len);
UEXPORT bool uebounds_range(size_t len, size_t range_begin, size_t range_len);

// Starts with

#define uz32_starts_with(cstr, target)          \
    _Generic((target),                          \
        default:        uz32_starts_with_uc32,  \
        const uc32_t *: uz32_starts_with_uz32,  \
        uc32_t *:       uz32_starts_with_uz32,  \
        ucv32_t:        uz32_starts_with_ucv32, \
        uv32_t:         uz32_starts_with_uv32,  \
        const us32_t *: uz32_starts_with_us32,  \
        us32_t *:       uz32_starts_with_us32   \
    )((cstr), (target))

UEXPORT bool uz32_starts_with_uc32(const uc32_t *cstr, uc32_t target);
UEXPORT bool uz32_starts_with_uz32(const uc32_t *cstr, const uc32_t *target);
UEXPORT bool uz32_starts_with_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len);
UEXPORT bool uz32_starts_with_ucv32(const uc32_t *cstr, ucv32_t target);
UEXPORT bool uz32_starts_with_uv32(const uc32_t *cstr, uv32_t target);
UEXPORT bool uz32_starts_with_us32(const uc32_t *cstr, const us32_t *target);

#define uz32n_starts_with(cstr, cstr_len, target) \
    _Generic((target),                            \
        default:        uz32n_starts_with_uc32,   \
        const uc32_t *: uz32_starts_with_uz32,    \
        uc32_t *:       uz32n_starts_with_uz32,   \
        ucv32_t:        uz32n_starts_with_ucv32,  \
        uv32_t:         uz32n_starts_with_uv32,   \
        const us32_t *: uz32n_starts_with_us32,   \
        us32_t *:       uz32n_starts_with_us32    \
    )((cstr), (cstr_len), (target))

UEXPORT bool uz32n_starts_with_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target);
UEXPORT bool uz32n_starts_with_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target);
UEXPORT bool uz32n_starts_with_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len);
UEXPORT bool uz32n_starts_with_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target);
UEXPORT bool uz32n_starts_with_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target);
UEXPORT bool uz32n_starts_with_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target);


#define uz16_starts_with(cstr, target)          \
    _Generic((target),                          \
        default:        uz16_starts_with_uc16,  \
        const uc16_t *: uz16_starts_with_uz16,  \
        uc16_t *:       uz16_starts_with_uz16,  \
        ucv16_t:        uz16_starts_with_ucv16, \
        uv16_t:         uz16_starts_with_uv16,  \
        const us16_t *: uz16_starts_with_us16,  \
        us16_t *:       uz16_starts_with_us16   \
    )((cstr), (target))

UEXPORT bool uz16_starts_with_uc16(const uc16_t *cstr, uc16_t target);
UEXPORT bool uz16_starts_with_uz16(const uc16_t *cstr, const uc16_t *target);
UEXPORT bool uz16_starts_with_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len);
UEXPORT bool uz16_starts_with_ucv16(const uc16_t *cstr, ucv16_t target);
UEXPORT bool uz16_starts_with_uv16(const uc16_t *cstr, uv16_t target);
UEXPORT bool uz16_starts_with_us16(const uc16_t *cstr, const us16_t *target);

#define uz16n_starts_with(cstr, cstr_len, target) \
    _Generic((target),                            \
        default:        uz16n_starts_with_uc16,   \
        const uc16_t *: uz16n_starts_with_uz16,   \
        uc16_t *:       uz16n_starts_with_uz16,   \
        ucv16_t:        uz16n_starts_with_ucv16,  \
        uv16_t:         uz16n_starts_with_uv16,   \
        const us16_t *: uz16n_starts_with_us16,   \
        us16_t *:       uz16n_starts_with_us16    \
    )((cstr), (cstr_len), (target))

UEXPORT bool uz16n_starts_with_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target);
UEXPORT bool uz16n_starts_with_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target);
UEXPORT bool uz16n_starts_with_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len);
UEXPORT bool uz16n_starts_with_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target);
UEXPORT bool uz16n_starts_with_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target);
UEXPORT bool uz16n_starts_with_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target);


#define uz8_starts_with(cstr, target)        \
    _Generic((target),                       \
        default:       uz8_starts_with_uc8,  \
        const uc8_t *: uz8_starts_with_uz8,  \
        uc8_t *:       uz8_starts_with_uz8,  \
        ucv8_t:        uz8_starts_with_ucv8, \
        uv8_t:         uz8_starts_with_uv8,  \
        const us8_t *: uz8_starts_with_us8,  \
        us8_t *:       uz8_starts_with_us8   \
    )((cstr), (target))

UEXPORT bool uz8_starts_with_uc8(const uc8_t *cstr, uc8_t target);
UEXPORT bool uz8_starts_with_uz8(const uc8_t *cstr, const uc8_t *target);
UEXPORT bool uz8_starts_with_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len);
UEXPORT bool uz8_starts_with_ucv8(const uc8_t *cstr, ucv8_t target);
UEXPORT bool uz8_starts_with_uv8(const uc8_t *cstr, uv8_t target);
UEXPORT bool uz8_starts_with_us8(const uc8_t *cstr, const us8_t *target);

#define uz8n_starts_with(cstr, cstr_len, target) \
    _Generic((target),                           \
        default:       uz8n_starts_with_uc8,     \
        const uc8_t *: uz8n_starts_with_uz8,     \
        uc8_t *:       uz8n_starts_with_uz8,     \
        ucv8_t:        uz8n_starts_with_ucv8,    \
        uv8_t:         uz8n_starts_with_uv8,     \
        const us8_t *: uz8n_starts_with_us8,     \
        us8_t *:       uz8n_starts_with_us8      \
    )((cstr), (cstr_len), (target))

UEXPORT bool uz8n_starts_with_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target);
UEXPORT bool uz8n_starts_with_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target);
UEXPORT bool uz8n_starts_with_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len);
UEXPORT bool uz8n_starts_with_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target);
UEXPORT bool uz8n_starts_with_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target);
UEXPORT bool uz8n_starts_with_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target);

// Ends with

#define uz32_ends_with(cstr, target)          \
    _Generic((target),                        \
        default:        uz32_ends_with_uc32,  \
        const uc32_t *: uz32_ends_with_uz32,  \
        uc32_t *:       uz32_ends_with_uz32,  \
        ucv32_t:        uz32_ends_with_ucv32, \
        uv32_t:         uz32_ends_with_uv32,  \
        const us32_t *: uz32_ends_with_us32,  \
        us32_t *:       uz32_ends_with_us32   \
    )((cstr), (target))

UEXPORT bool uz32_ends_with_uc32(const uc32_t *cstr, uc32_t target);
UEXPORT bool uz32_ends_with_uz32(const uc32_t *cstr, const uc32_t *target);
UEXPORT bool uz32_ends_with_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len);
UEXPORT bool uz32_ends_with_ucv32(const uc32_t *cstr, ucv32_t target);
UEXPORT bool uz32_ends_with_uv32(const uc32_t *cstr, uv32_t target);
UEXPORT bool uz32_ends_with_us32(const uc32_t *cstr, const us32_t *target);

#define uz32n_ends_with(cstr, cstr_len, target) \
    _Generic((target),                          \
        default:        uz32n_ends_with_uc32,   \
        const uc32_t *: uz32n_ends_with_uz32,   \
        uc32_t *:       uz32n_ends_with_uz32,   \
        ucv32_t:        uz32n_ends_with_ucv32,  \
        uv32_t:         uz32n_ends_with_uv32,   \
        const us32_t *: uz32n_ends_with_us32,   \
        us32_t *:       uz32n_ends_with_us32    \
    )((cstr), (cstr_len), (target))

UEXPORT bool uz32n_ends_with_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target);
UEXPORT bool uz32n_ends_with_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target);
UEXPORT bool uz32n_ends_with_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len);
UEXPORT bool uz32n_ends_with_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target);
UEXPORT bool uz32n_ends_with_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target);
UEXPORT bool uz32n_ends_with_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target);


#define uz16_ends_with(cstr, target)          \
    _Generic((target),                        \
        default:        uz16_ends_with_uc16,  \
        const uc16_t *: uz16_ends_with_uz16,  \
        uc16_t *:       uz16_ends_with_uz16,  \
        ucv16_t:        uz16_ends_with_ucv16, \
        uv16_t:         uz16_ends_with_uv16,  \
        const us16_t *: uz16_ends_with_us16,  \
        us16_t *:       uz16_ends_with_us16   \
    )((cstr), (target))

UEXPORT bool uz16_ends_with_uc16(const uc16_t *cstr, uc16_t target);
UEXPORT bool uz16_ends_with_uz16(const uc16_t *cstr, const uc16_t *target);
UEXPORT bool uz16_ends_with_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len);
UEXPORT bool uz16_ends_with_ucv16(const uc16_t *cstr, ucv16_t target);
UEXPORT bool uz16_ends_with_uv16(const uc16_t *cstr, uv16_t target);
UEXPORT bool uz16_ends_with_us16(const uc16_t *cstr, const us16_t *target);

#define uz16n_ends_with(cstr, cstr_len, target) \
    _Generic((target),                          \
        default:        uz16n_ends_with_uc16,   \
        const uc16_t *: uz16n_ends_with_uz16,   \
        uc16_t *:       uz16n_ends_with_uz16,   \
        ucv16_t:        uz16n_ends_with_ucv16,  \
        uv16_t:         uz16n_ends_with_uv16,   \
        const us16_t *: uz16n_ends_with_us16,   \
        us16_t *:       uz16n_ends_with_us16    \
    )((cstr), (cstr_len), (target))

UEXPORT bool uz16n_ends_with_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target);
UEXPORT bool uz16n_ends_with_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target);
UEXPORT bool uz16n_ends_with_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len);
UEXPORT bool uz16n_ends_with_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target);
UEXPORT bool uz16n_ends_with_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target);
UEXPORT bool uz16n_ends_with_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target);


#define uz8_ends_with(cstr, target)        \
    _Generic((target),                     \
        default:       uz8_ends_with_uc8,  \
        const uc8_t *: uz8_ends_with_uz8,  \
        uc8_t *:       uz8_ends_with_uz8,  \
        ucv8_t:        uz8_ends_with_ucv8, \
        uv8_t:         uz8_ends_with_uv8,  \
        const us8_t *: uz8_ends_with_us8,  \
        us8_t *:       uz8_ends_with_us8   \
    )((cstr), (target))

UEXPORT bool uz8_ends_with_uc8(const uc8_t *cstr, uc8_t target);
UEXPORT bool uz8_ends_with_uz8(const uc8_t *cstr, const uc8_t *target);
UEXPORT bool uz8_ends_with_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len);
UEXPORT bool uz8_ends_with_ucv8(const uc8_t *cstr, ucv8_t target);
UEXPORT bool uz8_ends_with_uv8(const uc8_t *cstr, uv8_t target);
UEXPORT bool uz8_ends_with_us8(const uc8_t *cstr, const us8_t *target);

#define uz8n_ends_with(cstr, cstr_len, target) \
    _Generic((target),                         \
        default:       uz8n_ends_with_uc8,     \
        const uc8_t *: uz8n_ends_with_uz8,     \
        uc8_t *:       uz8n_ends_with_uz8,     \
        ucv8_t:        uz8n_ends_with_ucv8,    \
        uv8_t:         uz8n_ends_with_uv8,     \
        const us8_t *: uz8n_ends_with_us8,     \
        us8_t *:       uz8n_ends_with_us8      \
    )((cstr), (cstr_len), (target))

UEXPORT bool uz8n_ends_with_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target);
UEXPORT bool uz8n_ends_with_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target);
UEXPORT bool uz8n_ends_with_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len);
UEXPORT bool uz8n_ends_with_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target);
UEXPORT bool uz8n_ends_with_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target);
UEXPORT bool uz8n_ends_with_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target);

#endif