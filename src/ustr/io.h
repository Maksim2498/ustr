#ifndef USTR_IO_H
#define USTR_IO_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "type/fmt/case.h"
#include "type/fmt/float.h"
#include "type/fmt/int.h"
#include "type/char.h"
#include "type/cview.h"
#include "type/str.h"
#include "type/view.h"
#include "util/export.h"

// Output

// - Generic

#define uprint(val)                       \
    _Generic((val),                       \
        char:               uprint_uc8,   \
                                          \
        float:              uprint_float, \
        double:             uprint_float, \
        long double:        uprint_float, \
                                          \
        signed char:        uprint_int,   \
        unsigned char:      uprint_uint,  \
        short:              uprint_int,   \
        unsigned short:     uprint_uint,  \
        int:                uprint_int,   \
        unsigned:           uprint_uint,  \
        long:               uprint_int,   \
        unsigned long:      uprint_uint,  \
        long long:          uprint_int,   \
        unsigned long long: uprint_uint,  \
                                          \
        const uc32_t *:     uprint_uz32,  \
        uc32_t *:           uprint_uz32,  \
        const uc16_t *:     uprint_uz16,  \
        uc16_t *:           uprint_uz16,  \
        const uc8_t *:      uprint_uz8,   \
        uc8_t *:            uprint_uz8,   \
                                          \
        ucv32_t:            uprint_ucv32, \
        ucv16_t:            uprint_ucv16, \
        ucv8_t:             uprint_ucv8,  \
                                          \
        uv32_t:             uprint_uv32,  \
        uv16_t:             uprint_uv16,  \
        uv8_t:              uprint_uv8,   \
                                          \
        const us32_t *:     uprint_us32,  \
        us32_t *:           uprint_us32,  \
        const us16_t *:     uprint_us16,  \
        us16_t *:           uprint_us16,  \
        const us8_t *:      uprint_us8,   \
        us8_t *:            uprint_us8    \
    )((val))

#define uprintln(val)                       \
    _Generic((val),                         \
        char:               uprintln_uc8,   \
                                            \
        float:              uprintln_float, \
        double:             uprintln_float, \
        long double:        uprintln_float, \
                                            \
        signed char:        uprintln_int,   \
        unsigned char:      uprintln_uint,  \
        short:              uprintln_int,   \
        unsigned short:     uprintln_uint,  \
        int:                uprintln_int,   \
        unsigned:           uprintln_uint,  \
        long:               uprintln_int,   \
        unsigned long:      uprintln_uint,  \
        long long:          uprintln_int,   \
        unsigned long long: uprintln_uint,  \
                                            \
        const uc32_t *:     uprintln_uz32,  \
        uc32_t *:           uprintln_uz32,  \
        const uc16_t *:     uprintln_uz16,  \
        uc16_t *:           uprintln_uz16,  \
        const uc8_t *:      uprintln_uz8,   \
        uc8_t *:            uprintln_uz8,   \
                                            \
        ucv32_t:            uprintln_ucv32, \
        ucv16_t:            uprintln_ucv16, \
        ucv8_t:             uprintln_ucv8,  \
                                            \
        uv32_t:             uprintln_uv32,  \
        uv16_t:             uprintln_uv16,  \
        uv8_t:              uprintln_uv8,   \
                                            \
        const us32_t *:     uprintln_us32,  \
        us32_t *:           uprintln_us32,  \
        const us16_t *:     uprintln_us16,  \
        us16_t *:           uprintln_us16,  \
        const us8_t *:      uprintln_us8,   \
        us8_t *:            uprintln_us8    \
    )((val))

#define ufprint(file, val)                 \
    _Generic((val),                        \
        char:               ufprint_uc8,   \
                                           \
        float:              ufprint_float, \
        double:             ufprint_float, \
        long double:        ufprint_float, \
                                           \
        signed char:        ufprint_int,   \
        unsigned char:      ufprint_uint,  \
        short:              ufprint_int,   \
        unsigned short:     ufprint_uint,  \
        int:                ufprint_int,   \
        unsigned:           ufprint_uint,  \
        long:               ufprint_int,   \
        unsigned long:      ufprint_uint,  \
        long long:          ufprint_int,   \
        unsigned long long: ufprint_uint,  \
                                           \
        const uc32_t *:     ufprint_uz32,  \
        uc32_t *:           ufprint_uz32,  \
        const uc16_t *:     ufprint_uz16,  \
        uc16_t *:           ufprint_uz16,  \
        const uc8_t *:      ufprint_uz8,   \
        uc8_t *:            ufprint_uz8,   \
                                           \
        ucv32_t:            ufprint_ucv32, \
        ucv16_t:            ufprint_ucv16, \
        ucv8_t:             ufprint_ucv8,  \
                                           \
        uv32_t:             ufprint_uv32,  \
        uv16_t:             ufprint_uv16,  \
        uv8_t:              ufprint_uv8,   \
                                           \
        const us32_t *:     ufprint_us32,  \
        us32_t *:           ufprint_us32,  \
        const us16_t *:     ufprint_us16,  \
        us16_t *:           ufprint_us16,  \
        const us8_t *:      ufprint_us8,   \
        us8_t *:            ufprint_us8    \
    )((file), (val))

#define ufprintln(file, val)                 \
    _Generic((val),                          \
        char:               ufprintln_uc8,   \
                                             \
        float:              ufprintln_float, \
        double:             ufprintln_float, \
        long double:        ufprintln_float, \
                                             \
        signed char:        ufprintln_int,   \
        unsigned char:      ufprintln_uint,  \
        short:              ufprintln_int,   \
        unsigned short:     ufprintln_uint,  \
        int:                ufprintln_int,   \
        unsigned:           ufprintln_uint,  \
        long:               ufprintln_int,   \
        unsigned long:      ufprintln_uint,  \
        long long:          ufprintln_int,   \
        unsigned long long: ufprintln_uint,  \
                                             \
        const uc32_t *:     ufprintln_uz32,  \
        uc32_t *:           ufprintln_uz32,  \
        const uc16_t *:     ufprintln_uz16,  \
        uc16_t *:           ufprintln_uz16,  \
        const uc8_t *:      ufprintln_uz8,   \
        uc8_t *:            ufprintln_uz8,   \
                                             \
        ucv32_t:            ufprintln_ucv32, \
        ucv16_t:            ufprintln_ucv16, \
        ucv8_t:             ufprintln_ucv8,  \
                                             \
        uv32_t:             ufprintln_uv32,  \
        uv16_t:             ufprintln_uv16,  \
        uv8_t:              ufprintln_uv8,   \
                                             \
        const us32_t *:     ufprintln_us32,  \
        us32_t *:           ufprintln_us32,  \
        const us16_t *:     ufprintln_us16,  \
        us16_t *:           ufprintln_us16,  \
        const us8_t *:      ufprintln_us8,   \
        us8_t *:            ufprintln_us8    \
    )((file), (val))

// - Fmt

#define uprint_fmt(fmt, ...)              \
    _Generic((fmt),                       \
        const uc32_t *: uprint_fmt_uz32,  \
        uc32_t *:       uprint_fmt_uz32,  \
        ucv32_t:        uprint_fmt_ucv32, \
        uv32_t:         uprint_fmt_uv32,  \
        const us32_t *: uprint_fmt_us32,  \
        us32_t *:       uprint_fmt_us32,  \
                                          \
        const uc16_t *: uprint_fmt_uz16,  \
        uc16_t *:       uprint_fmt_uz16,  \
        ucv16_t:        uprint_fmt_ucv16, \
        uv16_t:         uprint_fmt_uv16,  \
        const us16_t *: uprint_fmt_us16,  \
        us16_t *:       uprint_fmt_us16,  \
                                          \
        const uc8_t *:  uprint_fmt_uz8,   \
        uc8_t *:        uprint_fmt_uz8,   \
        ucv8_t:         uprint_fmt_ucv8,  \
        uv8_t:          uprint_fmt_uv8,   \
        const us8_t *:  uprint_fmt_us8,   \
        us8_t *:        uprint_fmt_us8    \
    )((fmt), __VA_ARGS__)

#define uprint_fmt_v(fmt, args)             \
    _Generic((fmt),                         \
        const uc32_t *: uprint_fmt_uz32_v,  \
        uc32_t *:       uprint_fmt_uz32_v,  \
        ucv32_t:        uprint_fmt_ucv32_v, \
        uv32_t:         uprint_fmt_uv32_v,  \
        const us32_t *: uprint_fmt_us32_v,  \
        us32_t *:       uprint_fmt_us32_v,  \
                                            \
        const uc16_t *: uprint_fmt_uz16_v,  \
        uc16_t *:       uprint_fmt_uz16_v,  \
        ucv16_t:        uprint_fmt_ucv16_v, \
        uv16_t:         uprint_fmt_uv16_v,  \
        const us16_t *: uprint_fmt_us16_v,  \
        us16_t *:       uprint_fmt_us16_v,  \
                                            \
        const uc8_t *:  uprint_fmt_uz8_v,   \
        uc8_t *:        uprint_fmt_uz8_v,   \
        ucv8_t:         uprint_fmt_ucv8_v,  \
        uv8_t:          uprint_fmt_uv8_v,   \
        const us8_t *:  uprint_fmt_us8_v,   \
        us8_t *:        uprint_fmt_us8_v    \
    )((fmt), (args))

#define uprint_fmt_n(fmt, fmt_len, ...)    \
    _Generic((fmt),                        \
        const uc32_t *: uprint_fmt_uz32n,  \
        uc32_t *:       uprint_fmt_uz32n,  \
                                           \
        const uc16_t *: uprint_fmt_uz16n,  \
        uc16_t *:       uprint_fmt_uz16n,  \
                                           \
        const uc8_t *:  uprint_fmt_uz8n,   \
        uc8_t *:        uprint_fmt_uz8n    \
    )((fmt), (fmt_len), __VA_ARGS__)

#define uprint_fmt_n_v(fmt, fmt_len, args)  \
    _Generic((fmt),                         \
        const uc32_t *: uprint_fmt_uz32n_v, \
        uc32_t *:       uprint_fmt_uz32n_v, \
                                            \
        const uc16_t *: uprint_fmt_uz16n_v, \
        uc16_t *:       uprint_fmt_uz16n_v, \
                                            \
        const uc8_t *:  uprint_fmt_uz8n_v,  \
        uc8_t *:        uprint_fmt_uz8n_v   \
    )((fmt), (fmt_len), (args))

UEXPORT size_t uprint_fmt_uz32(const uc32_t *fmt, ...);
UEXPORT size_t uprint_fmt_uz32n(const uc32_t *fmt, size_t fmt_len, ...);
UEXPORT size_t uprint_fmt_ucv32(ucv32_t fmt, ...);
UEXPORT size_t uprint_fmt_uv32(uv32_t fmt, ...);
UEXPORT size_t uprint_fmt_us32(const us32_t *fmt, ...);

UEXPORT size_t uprint_fmt_uz32_v(const uc32_t *fmt, va_list *args);
UEXPORT size_t uprint_fmt_uz32n_v(const uc32_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t uprint_fmt_ucv32_v(ucv32_t fmt, va_list *args);
UEXPORT size_t uprint_fmt_uv32_v(uv32_t fmt, va_list *args);
UEXPORT size_t uprint_fmt_us32_v(const us32_t *fmt, va_list *args);


UEXPORT size_t uprint_fmt_uz16(const uc16_t *fmt, ...);
UEXPORT size_t uprint_fmt_uz16n(const uc16_t *fmt, size_t fmt_len, ...);
UEXPORT size_t uprint_fmt_ucv16(ucv16_t fmt, ...);
UEXPORT size_t uprint_fmt_uv16(uv16_t fmt, ...);
UEXPORT size_t uprint_fmt_us16(const us16_t *fmt, ...);

UEXPORT size_t uprint_fmt_uz16_v(const uc16_t *fmt, va_list *args);
UEXPORT size_t uprint_fmt_uz16n_v(const uc16_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t uprint_fmt_ucv16_v(ucv16_t fmt, va_list *args);
UEXPORT size_t uprint_fmt_uv16_v(uv16_t fmt, va_list *args);
UEXPORT size_t uprint_fmt_us16_v(const us16_t *fmt, va_list *args);


UEXPORT size_t uprint_fmt_uz8(const uc8_t *fmt, ...);
UEXPORT size_t uprint_fmt_uz8n(const uc8_t *fmt, size_t fmt_len, ...);
UEXPORT size_t uprint_fmt_ucv8(ucv8_t fmt, ...);
UEXPORT size_t uprint_fmt_uv8(uv8_t fmt, ...);
UEXPORT size_t uprint_fmt_us8(const us8_t *fmt, ...);

UEXPORT size_t uprint_fmt_uz8_v(const uc8_t *fmt, va_list *args);
UEXPORT size_t uprint_fmt_uz8n_v(const uc8_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t uprint_fmt_ucv8_v(ucv8_t fmt, va_list *args);
UEXPORT size_t uprint_fmt_uv8_v(uv8_t fmt, va_list *args);
UEXPORT size_t uprint_fmt_us8_v(const us8_t *fmt, va_list *args);


#define uprintln_fmt(fmt, ...)              \
    _Generic((fmt),                         \
        const uc32_t *: uprintln_fmt_uz32,  \
        uc32_t *:       uprintln_fmt_uz32,  \
        ucv32_t:        uprintln_fmt_ucv32, \
        uv32_t:         uprintln_fmt_uv32,  \
        const us32_t *: uprintln_fmt_us32,  \
        us32_t *:       uprintln_fmt_us32,  \
                                            \
        const uc16_t *: uprintln_fmt_uz16,  \
        uc16_t *:       uprintln_fmt_uz16,  \
        ucv16_t:        uprintln_fmt_ucv16, \
        uv16_t:         uprintln_fmt_uv16,  \
        const us16_t *: uprintln_fmt_us16,  \
        us16_t *:       uprintln_fmt_us16,  \
                                            \
        const uc8_t *:  uprintln_fmt_uz8,   \
        uc8_t *:        uprintln_fmt_uz8,   \
        ucv8_t:         uprintln_fmt_ucv8,  \
        uv8_t:          uprintln_fmt_uv8,   \
        const us8_t *:  uprintln_fmt_us8,   \
        us8_t *:        uprintln_fmt_us8    \
    )((fmt), __VA_ARGS__)

#define uprintln_fmt_v(fmt, args)             \
    _Generic((fmt),                           \
        const uc32_t *: uprintln_fmt_uz32_v,  \
        uc32_t *:       uprintln_fmt_uz32_v,  \
        ucv32_t:        uprintln_fmt_ucv32_v, \
        uv32_t:         uprintln_fmt_uv32_v,  \
        const us32_t *: uprintln_fmt_us32_v,  \
        us32_t *:       uprintln_fmt_us32_v,  \
                                            \
        const uc16_t *: uprintln_fmt_uz16_v,  \
        uc16_t *:       uprintln_fmt_uz16_v,  \
        ucv16_t:        uprintln_fmt_ucv16_v, \
        uv16_t:         uprintln_fmt_uv16_v,  \
        const us16_t *: uprintln_fmt_us16_v,  \
        us16_t *:       uprintln_fmt_us16_v,  \
                                            \
        const uc8_t *:  uprintln_fmt_uz8_v,   \
        uc8_t *:        uprintln_fmt_uz8_v,   \
        ucv8_t:         uprintln_fmt_ucv8_v,  \
        uv8_t:          uprintln_fmt_uv8_v,   \
        const us8_t *:  uprintln_fmt_us8_v,   \
        us8_t *:        uprintln_fmt_us8_v    \
    )((fmt), (args))

#define uprintln_fmt_n(fmt, fmt_len, ...)    \
    _Generic((fmt),                          \
        const uc32_t *: uprintln_fmt_uz32n,  \
        uc32_t *:       uprintln_fmt_uz32n,  \
                                             \
        const uc16_t *: uprintln_fmt_uz16n,  \
        uc16_t *:       uprintln_fmt_uz16n,  \
                                             \
        const uc8_t *:  uprintln_fmt_uz8n,   \
        uc8_t *:        uprintln_fmt_uz8n    \
    )((fmt), (fmt_len), __VA_ARGS__)

#define uprintln_fmt_n_v(fmt, fmt_len, args)  \
    _Generic((fmt),                           \
        const uc32_t *: uprintln_fmt_uz32n_v, \
        uc32_t *:       uprintln_fmt_uz32n_v, \
                                              \
        const uc16_t *: uprintln_fmt_uz16n_v, \
        uc16_t *:       uprintln_fmt_uz16n_v, \
                                              \
        const uc8_t *:  uprintln_fmt_uz8n_v,  \
        uc8_t *:        uprintln_fmt_uz8n_v   \
    )((fmt), (fmt_len), (args))

UEXPORT size_t uprintln_fmt_uz32(const uc32_t *fmt, ...);
UEXPORT size_t uprintln_fmt_uz32n(const uc32_t *fmt, size_t fmt_len, ...);
UEXPORT size_t uprintln_fmt_ucv32(ucv32_t fmt, ...);
UEXPORT size_t uprintln_fmt_uv32(uv32_t fmt, ...);
UEXPORT size_t uprintln_fmt_us32(const us32_t *fmt, ...);

UEXPORT size_t uprintln_fmt_uz32_v(const uc32_t *fmt, va_list *args);
UEXPORT size_t uprintln_fmt_uz32n_v(const uc32_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t uprintln_fmt_ucv32_v(ucv32_t fmt, va_list *args);
UEXPORT size_t uprintln_fmt_uv32_v(uv32_t fmt, va_list *args);
UEXPORT size_t uprintln_fmt_us32_v(const us32_t *fmt, va_list *args);


UEXPORT size_t uprintln_fmt_uz16(const uc16_t *fmt, ...);
UEXPORT size_t uprintln_fmt_uz16n(const uc16_t *fmt, size_t fmt_len, ...);
UEXPORT size_t uprintln_fmt_ucv16(ucv16_t fmt, ...);
UEXPORT size_t uprintln_fmt_uv16(uv16_t fmt, ...);
UEXPORT size_t uprintln_fmt_us16(const us16_t *fmt, ...);

UEXPORT size_t uprintln_fmt_uz16_v(const uc16_t *fmt, va_list *args);
UEXPORT size_t uprintln_fmt_uz16n_v(const uc16_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t uprintln_fmt_ucv16_v(ucv16_t fmt, va_list *args);
UEXPORT size_t uprintln_fmt_uv16_v(uv16_t fmt, va_list *args);
UEXPORT size_t uprintln_fmt_us16_v(const us16_t *fmt, va_list *args);


UEXPORT size_t uprintln_fmt_uz8(const uc8_t *fmt, ...);
UEXPORT size_t uprintln_fmt_uz8n(const uc8_t *fmt, size_t fmt_len, ...);
UEXPORT size_t uprintln_fmt_ucv8(ucv8_t fmt, ...);
UEXPORT size_t uprintln_fmt_uv8(uv8_t fmt, ...);
UEXPORT size_t uprintln_fmt_us8(const us8_t *fmt, ...);

UEXPORT size_t uprintln_fmt_uz8_v(const uc8_t *fmt, va_list *args);
UEXPORT size_t uprintln_fmt_uz8n_v(const uc8_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t uprintln_fmt_ucv8_v(ucv8_t fmt, va_list *args);
UEXPORT size_t uprintln_fmt_uv8_v(uv8_t fmt, va_list *args);
UEXPORT size_t uprintln_fmt_us8_v(const us8_t *fmt, va_list *args);



#define ufprint_fmt(file, fmt, ...)        \
    _Generic((fmt),                        \
        const uc32_t *: ufprint_fmt_uz32,  \
        uc32_t *:       ufprint_fmt_uz32,  \
        ucv32_t:        ufprint_fmt_ucv32, \
        uv32_t:         ufprint_fmt_uv32,  \
        const us32_t *: ufprint_fmt_us32,  \
        us32_t *:       ufprint_fmt_us32,  \
                                           \
        const uc16_t *: ufprint_fmt_uz16,  \
        uc16_t *:       ufprint_fmt_uz16,  \
        ucv16_t:        ufprint_fmt_ucv16, \
        uv16_t:         ufprint_fmt_uv16,  \
        const us16_t *: ufprint_fmt_us16,  \
        us16_t *:       ufprint_fmt_us16,  \
                                           \
        const uc8_t *:  ufprint_fmt_uz8,   \
        uc8_t *:        ufprint_fmt_uz8,   \
        ucv8_t:         ufprint_fmt_ucv8,  \
        uv8_t:          ufprint_fmt_uv8,   \
        const us8_t *:  ufprint_fmt_us8,   \
        us8_t *:        ufprint_fmt_us8    \
    )((file), (fmt), __VA_ARGS__)

#define ufprint_fmt_v(file, fmt, args)       \
    _Generic((fmt),                          \
        const uc32_t *: ufprint_fmt_uz32_v,  \
        uc32_t *:       ufprint_fmt_uz32_v,  \
        ucv32_t:        ufprint_fmt_ucv32_v, \
        uv32_t:         ufprint_fmt_uv32_v,  \
        const us32_t *: ufprint_fmt_us32_v,  \
        us32_t *:       ufprint_fmt_us32_v,  \
                                             \
        const uc16_t *: ufprint_fmt_uz16_v,  \
        uc16_t *:       ufprint_fmt_uz16_v,  \
        ucv16_t:        ufprint_fmt_ucv16_v, \
        uv16_t:         ufprint_fmt_uv16_v,  \
        const us16_t *: ufprint_fmt_us16_v,  \
        us16_t *:       ufprint_fmt_us16_v,  \
                                             \
        const uc8_t *:  ufprint_fmt_uz8_v,   \
        uc8_t *:        ufprint_fmt_uz8_v,   \
        ucv8_t:         ufprint_fmt_ucv8_v,  \
        uv8_t:          ufprint_fmt_uv8_v,   \
        const us8_t *:  ufprint_fmt_us8_v,   \
        us8_t *:        ufprint_fmt_us8_v    \
    )((file), (fmt), (args))

#define ufprint_fmt_n(file, fmt, fmt_len, ...) \
    _Generic((fmt),                            \
        const uc32_t *: ufprint_fmt_uz32n,     \
        uc32_t *:       ufprint_fmt_uz32n,     \
                                               \
        const uc16_t *: ufprint_fmt_uz16n,     \
        uc16_t *:       ufprint_fmt_uz16n,     \
                                               \
        const uc8_t *:  ufprint_fmt_uz8n,      \
        uc8_t *:        ufprint_fmt_uz8n       \
    )((file), (fmt), (fmt_len), __VA_ARGS__)

#define ufprint_fmt_n_v(file, fmt, fmt_len, args) \
    _Generic((fmt),                               \
        const uc32_t *: ufprint_fmt_uz32n_v,      \
        uc32_t *:       ufprint_fmt_uz32n_v,      \
                                                  \
        const uc16_t *: ufprint_fmt_uz16n_v,      \
        uc16_t *:       ufprint_fmt_uz16n_v,      \
                                                  \
        const uc8_t *:  ufprint_fmt_uz8n_v,       \
        uc8_t *:        ufprint_fmt_uz8n_v        \
    )((file), (fmt), (fmt_len), (args))

UEXPORT size_t ufprint_fmt_uz32(FILE *file, const uc32_t *fmt, ...);
UEXPORT size_t ufprint_fmt_uz32n(FILE *file, const uc32_t *fmt, size_t fmt_len, ...);
UEXPORT size_t ufprint_fmt_ucv32(FILE *file, ucv32_t fmt, ...);
UEXPORT size_t ufprint_fmt_uv32(FILE *file, uv32_t fmt, ...);
UEXPORT size_t ufprint_fmt_us32(FILE *file, const us32_t *fmt, ...);

UEXPORT size_t ufprint_fmt_uz32_v(FILE *file, const uc32_t *fmt, va_list *args);
UEXPORT size_t ufprint_fmt_uz32n_v(FILE *file, const uc32_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t ufprint_fmt_ucv32_v(FILE *file, ucv32_t fmt, va_list *args);
UEXPORT size_t ufprint_fmt_uv32_v(FILE *file, uv32_t fmt, va_list *args);
UEXPORT size_t ufprint_fmt_us32_v(FILE *file, const us32_t *fmt, va_list *args);


UEXPORT size_t ufprint_fmt_uz16(FILE *file, const uc16_t *fmt, ...);
UEXPORT size_t ufprint_fmt_uz16n(FILE *file, const uc16_t *fmt, size_t fmt_len, ...);
UEXPORT size_t ufprint_fmt_ucv16(FILE *file, ucv16_t fmt, ...);
UEXPORT size_t ufprint_fmt_uv16(FILE *file, uv16_t fmt, ...);
UEXPORT size_t ufprint_fmt_us16(FILE *file, const us16_t *fmt, ...);

UEXPORT size_t ufprint_fmt_uz16_v(FILE *file, const uc16_t *fmt, va_list *args);
UEXPORT size_t ufprint_fmt_uz16n_v(FILE *file, const uc16_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t ufprint_fmt_ucv16_v(FILE *file, ucv16_t fmt, va_list *args);
UEXPORT size_t ufprint_fmt_uv16_v(FILE *file, uv16_t fmt, va_list *args);
UEXPORT size_t ufprint_fmt_us16_v(FILE *file, const us16_t *fmt, va_list *args);


UEXPORT size_t ufprint_fmt_uz8(FILE *file, const uc8_t *fmt, ...);
UEXPORT size_t ufprint_fmt_uz8n(FILE *file, const uc8_t *fmt, size_t fmt_len, ...);
UEXPORT size_t ufprint_fmt_ucv8(FILE *file, ucv8_t fmt, ...);
UEXPORT size_t ufprint_fmt_uv8(FILE *file, uv8_t fmt, ...);
UEXPORT size_t ufprint_fmt_us8(FILE *file, const us8_t *fmt, ...);

UEXPORT size_t ufprint_fmt_uz8_v(FILE *file, const uc8_t *fmt, va_list *args);
UEXPORT size_t ufprint_fmt_uz8n_v(FILE *file, const uc8_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t ufprint_fmt_ucv8_v(FILE *file, ucv8_t fmt, va_list *args);
UEXPORT size_t ufprint_fmt_uv8_v(FILE *file, uv8_t fmt, va_list *args);
UEXPORT size_t ufprint_fmt_us8_v(FILE *file, const us8_t *fmt, va_list *args);


#define ufprintln_fmt(file, fmt, ...)        \
    _Generic((fmt),                          \
        const uc32_t *: ufprintln_fmt_uz32,  \
        uc32_t *:       ufprintln_fmt_uz32,  \
        ucv32_t:        ufprintln_fmt_ucv32, \
        uv32_t:         ufprintln_fmt_uv32,  \
        const us32_t *: ufprintln_fmt_us32,  \
        us32_t *:       ufprintln_fmt_us32,  \
                                             \
        const uc16_t *: ufprintln_fmt_uz16,  \
        uc16_t *:       ufprintln_fmt_uz16,  \
        ucv16_t:        ufprintln_fmt_ucv16, \
        uv16_t:         ufprintln_fmt_uv16,  \
        const us16_t *: ufprintln_fmt_us16,  \
        us16_t *:       ufprintln_fmt_us16,  \
                                             \
        const uc8_t *:  ufprintln_fmt_uz8,   \
        uc8_t *:        ufprintln_fmt_uz8,   \
        ucv8_t:         ufprintln_fmt_ucv8,  \
        uv8_t:          ufprintln_fmt_uv8,   \
        const us8_t *:  ufprintln_fmt_us8,   \
        us8_t *:        ufprintln_fmt_us8    \
    )((file), (fmt), __VA_ARGS__)

#define ufprintln_fmt_v(file, fmt, args)       \
    _Generic((fmt),                            \
        const uc32_t *: ufprintln_fmt_uz32_v,  \
        uc32_t *:       ufprintln_fmt_uz32_v,  \
        ucv32_t:        ufprintln_fmt_ucv32_v, \
        uv32_t:         ufprintln_fmt_uv32_v,  \
        const us32_t *: ufprintln_fmt_us32_v,  \
        us32_t *:       ufprintln_fmt_us32_v,  \
                                               \
        const uc16_t *: ufprintln_fmt_uz16_v,  \
        uc16_t *:       ufprintln_fmt_uz16_v,  \
        ucv16_t:        ufprintln_fmt_ucv16_v, \
        uv16_t:         ufprintln_fmt_uv16_v,  \
        const us16_t *: ufprintln_fmt_us16_v,  \
        us16_t *:       ufprintln_fmt_us16_v,  \
                                               \
        const uc8_t *:  ufprintln_fmt_uz8_v,   \
        uc8_t *:        ufprintln_fmt_uz8_v,   \
        ucv8_t:         ufprintln_fmt_ucv8_v,  \
        uv8_t:          ufprintln_fmt_uv8_v,   \
        const us8_t *:  ufprintln_fmt_us8_v,   \
        us8_t *:        ufprintln_fmt_us8_v    \
    )((file), (fmt), (args))

#define ufprintln_fmt_n(file, fmt, fmt_len, ...) \
    _Generic((fmt),                              \
        const uc32_t *: ufprintln_fmt_uz32n,     \
        uc32_t *:       ufprintln_fmt_uz32n,     \
                                                 \
        const uc16_t *: ufprintln_fmt_uz16n,     \
        uc16_t *:       ufprintln_fmt_uz16n,     \
                                                 \
        const uc8_t *:  ufprintln_fmt_uz8n,      \
        uc8_t *:        ufprintln_fmt_uz8n       \
    )((file), (fmt), (fmt_len), __VA_ARGS__)

#define ufprintln_fmt_n_v(file, fmt, fmt_len, args) \
    _Generic((fmt),                                 \
        const uc32_t *: ufprintln_fmt_uz32n_v,      \
        uc32_t *:       ufprintln_fmt_uz32n_v,      \
                                                    \
        const uc16_t *: ufprintln_fmt_uz16n_v,      \
        uc16_t *:       ufprintln_fmt_uz16n_v,      \
                                                    \
        const uc8_t *:  ufprintln_fmt_uz8n_v,       \
        uc8_t *:        ufprintln_fmt_uz8n_v        \
    )((file), (fmt), (fmt_len), (args))

UEXPORT size_t ufprintln_fmt_uz32(FILE *file, const uc32_t *fmt, ...);
UEXPORT size_t ufprintln_fmt_uz32n(FILE *file, const uc32_t *fmt, size_t fmt_len, ...);
UEXPORT size_t ufprintln_fmt_ucv32(FILE *file, ucv32_t fmt, ...);
UEXPORT size_t ufprintln_fmt_uv32(FILE *file, uv32_t fmt, ...);
UEXPORT size_t ufprintln_fmt_us32(FILE *file, const us32_t *fmt, ...);

UEXPORT size_t ufprintln_fmt_uz32_v(FILE *file, const uc32_t *fmt, va_list *args);
UEXPORT size_t ufprintln_fmt_uz32n_v(FILE *file, const uc32_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t ufprintln_fmt_ucv32_v(FILE *file, ucv32_t fmt, va_list *args);
UEXPORT size_t ufprintln_fmt_uv32_v(FILE *file, uv32_t fmt, va_list *args);
UEXPORT size_t ufprintln_fmt_us32_v(FILE *file, const us32_t *fmt, va_list *args);


UEXPORT size_t ufprintln_fmt_uz16(FILE *file, const uc16_t *fmt, ...);
UEXPORT size_t ufprintln_fmt_uz16n(FILE *file, const uc16_t *fmt, size_t fmt_len, ...);
UEXPORT size_t ufprintln_fmt_ucv16(FILE *file, ucv16_t fmt, ...);
UEXPORT size_t ufprintln_fmt_uv16(FILE *file, uv16_t fmt, ...);
UEXPORT size_t ufprintln_fmt_us16(FILE *file, const us16_t *fmt, ...);

UEXPORT size_t ufprintln_fmt_uz16_v(FILE *file, const uc16_t *fmt, va_list *args);
UEXPORT size_t ufprintln_fmt_uz16n_v(FILE *file, const uc16_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t ufprintln_fmt_ucv16_v(FILE *file, ucv16_t fmt, va_list *args);
UEXPORT size_t ufprintln_fmt_uv16_v(FILE *file, uv16_t fmt, va_list *args);
UEXPORT size_t ufprintln_fmt_us16_v(FILE *file, const us16_t *fmt, va_list *args);


UEXPORT size_t ufprintln_fmt_uz8(FILE *file, const uc8_t *fmt, ...);
UEXPORT size_t ufprintln_fmt_uz8n(FILE *file, const uc8_t *fmt, size_t fmt_len, ...);
UEXPORT size_t ufprintln_fmt_ucv8(FILE *file, ucv8_t fmt, ...);
UEXPORT size_t ufprintln_fmt_uv8(FILE *file, uv8_t fmt, ...);
UEXPORT size_t ufprintln_fmt_us8(FILE *file, const us8_t *fmt, ...);

UEXPORT size_t ufprintln_fmt_uz8_v(FILE *file, const uc8_t *fmt, va_list *args);
UEXPORT size_t ufprintln_fmt_uz8n_v(FILE *file, const uc8_t *fmt, size_t fmt_len, va_list *args);
UEXPORT size_t ufprintln_fmt_ucv8_v(FILE *file, ucv8_t fmt, va_list *args);
UEXPORT size_t ufprintln_fmt_uv8_v(FILE *file, uv8_t fmt, va_list *args);
UEXPORT size_t ufprintln_fmt_us8_v(FILE *file, const us8_t *fmt, va_list *args);

// - Int

#define uprint_int_fmt(val, fmt)                            \
    _Generic((fmt),                                         \
        const struct ufmt32_int_output *: uprint_int_fmt32, \
        struct ufmt32_int_output *:       uprint_int_fmt32, \
        const struct ufmt16_int_output *: uprint_int_fmt16, \
        struct ufmt16_int_output *:       uprint_int_fmt16, \
        const struct ufmt8_int_output *:  uprint_int_fmt8,  \
        struct ufmt8_int_output *:        uprint_int_fmt8   \
    )((val), (fmt))

UEXPORT size_t uprint_int(intmax_t val);
UEXPORT size_t uprint_int_fmt32(intmax_t val, const struct ufmt32_int_output *fmt);
UEXPORT size_t uprint_int_fmt16(intmax_t val, const struct ufmt16_int_output *fmt);
UEXPORT size_t uprint_int_fmt8(intmax_t val, const struct ufmt8_int_output *fmt);

#define uprint_uint_fmt(val, fmt)                            \
    _Generic((fmt),                                          \
        const struct ufmt32_int_output *: uprint_uint_fmt32, \
        struct ufmt32_int_output *:       uprint_uint_fmt32, \
        const struct ufmt16_int_output *: uprint_uint_fmt16, \
        struct ufmt16_int_output *:       uprint_uint_fmt16, \
        const struct ufmt8_int_output *:  uprint_uint_fmt8,  \
        struct ufmt8_int_output *:        uprint_uint_fmt8   \
    )((val), (fmt))

UEXPORT size_t uprint_uint(uintmax_t val);
UEXPORT size_t uprint_uint_fmt32(uintmax_t val, const struct ufmt32_int_output *fmt);
UEXPORT size_t uprint_uint_fmt16(uintmax_t val, const struct ufmt16_int_output *fmt);
UEXPORT size_t uprint_uint_fmt8(uintmax_t val, const struct ufmt8_int_output *fmt);


#define uprintln_int_fmt(val, fmt)                            \
    _Generic((fmt),                                           \
        const struct ufmt32_int_output *: uprintln_int_fmt32, \
        struct ufmt32_int_output *:       uprintln_int_fmt32, \
        const struct ufmt16_int_output *: uprintln_int_fmt16, \
        struct ufmt16_int_output *:       uprintln_int_fmt16, \
        const struct ufmt8_int_output *:  uprintln_int_fmt8,  \
        struct ufmt8_int_output *:        uprintln_int_fmt8   \
    )((val), (fmt))

UEXPORT size_t uprintln_int(intmax_t val);
UEXPORT size_t uprintln_int_fmt32(intmax_t val, const struct ufmt32_int_output *fmt);
UEXPORT size_t uprintln_int_fmt16(intmax_t val, const struct ufmt16_int_output *fmt);
UEXPORT size_t uprintln_int_fmt8(intmax_t val, const struct ufmt8_int_output *fmt);

#define uprintln_uint_fmt(val, fmt)                            \
    _Generic((fmt),                                            \
        const struct ufmt32_int_output *: uprintln_uint_fmt32, \
        struct ufmt32_int_output *:       uprintln_uint_fmt32, \
        const struct ufmt16_int_output *: uprintln_uint_fmt16, \
        struct ufmt16_int_output *:       uprintln_uint_fmt16, \
        const struct ufmt8_int_output *:  uprintln_uint_fmt8,  \
        struct ufmt8_int_output *:        uprintln_uint_fmt8   \
    )((val), (fmt))

UEXPORT size_t uprintln_uint(uintmax_t val);
UEXPORT size_t uprintln_uint_fmt32(uintmax_t val, const struct ufmt32_int_output *fmt);
UEXPORT size_t uprintln_uint_fmt16(uintmax_t val, const struct ufmt16_int_output *fmt);
UEXPORT size_t uprintln_uint_fmt8(uintmax_t val, const struct ufmt8_int_output *fmt);



#define ufprint_int_fmt(fle, val, fmt)                       \
    _Generic((fmt),                                          \
        const struct ufmt32_int_output *: ufprint_int_fmt32, \
        struct ufmt32_int_output *:       ufprint_int_fmt32, \
        const struct ufmt16_int_output *: ufprint_int_fmt16, \
        struct ufmt16_int_output *:       ufprint_int_fmt16, \
        const struct ufmt8_int_output *:  ufprint_int_fmt8,  \
        struct ufmt8_int_output *:        ufprint_int_fmt8   \
    )((file), (val), (fmt))

UEXPORT size_t ufprint_int(FILE *file, intmax_t val);
UEXPORT size_t ufprint_int_fmt32(FILE *file, intmax_t val, const struct ufmt32_int_output *fmt);
UEXPORT size_t ufprint_int_fmt16(FILE *file, intmax_t val, const struct ufmt16_int_output *fmt);
UEXPORT size_t ufprint_int_fmt8(FILE *file, intmax_t val, const struct ufmt8_int_output *fmt);

#define ufprint_uint_fmt(fle, val, fmt)                       \
    _Generic((fmt),                                           \
        const struct ufmt32_int_output *: ufprint_uint_fmt32, \
        struct ufmt32_int_output *:       ufprint_uint_fmt32, \
        const struct ufmt16_int_output *: ufprint_uint_fmt16, \
        struct ufmt16_int_output *:       ufprint_uint_fmt16, \
        const struct ufmt8_int_output *:  ufprint_uint_fmt8,  \
        struct ufmt8_int_output *:        ufprint_uint_fmt8   \
    )((file), (val), (fmt))

UEXPORT size_t ufprint_uint(FILE *file, uintmax_t val);
UEXPORT size_t ufprint_uint_fmt32(FILE *file, uintmax_t val, const struct ufmt32_int_output *fmt);
UEXPORT size_t ufprint_uint_fmt16(FILE *file, uintmax_t val, const struct ufmt16_int_output *fmt);
UEXPORT size_t ufprint_uint_fmt8(FILE *file, uintmax_t val, const struct ufmt8_int_output *fmt);


#define ufprintln_int_fmt(fle, val, fmt)                       \
    _Generic((fmt),                                            \
        const struct ufmt32_int_output *: ufprintln_int_fmt32, \
        struct ufmt32_int_output *:       ufprintln_int_fmt32, \
        const struct ufmt16_int_output *: ufprintln_int_fmt16, \
        struct ufmt16_int_output *:       ufprintln_int_fmt16, \
        const struct ufmt8_int_output *:  ufprintln_int_fmt8,  \
        struct ufmt8_int_output *:        ufprintln_int_fmt8   \
    )((file), (val), (fmt))

UEXPORT size_t ufprintln_int(FILE *file, intmax_t val);
UEXPORT size_t ufprintln_int_fmt32(FILE *file, intmax_t val, const struct ufmt32_int_output *fmt);
UEXPORT size_t ufprintln_int_fmt16(FILE *file, intmax_t val, const struct ufmt16_int_output *fmt);
UEXPORT size_t ufprintln_int_fmt8(FILE *file, intmax_t val, const struct ufmt8_int_output *fmt);

#define ufprintln_uint_fmt(fle, val, fmt)                       \
    _Generic((fmt),                                             \
        const struct ufmt32_int_output *: ufprintln_uint_fmt32, \
        struct ufmt32_int_output *:       ufprintln_uint_fmt32, \
        const struct ufmt16_int_output *: ufprintln_uint_fmt16, \
        struct ufmt16_int_output *:       ufprintln_uint_fmt16, \
        const struct ufmt8_int_output *:  ufprintln_uint_fmt8,  \
        struct ufmt8_int_output *:        ufprintln_uint_fmt8   \
    )((file), (val), (fmt))

UEXPORT size_t ufprintln_uint(FILE *file, uintmax_t val);
UEXPORT size_t ufprintln_uint_fmt32(FILE *file, uintmax_t val, const struct ufmt32_int_output *fmt);
UEXPORT size_t ufprintln_uint_fmt16(FILE *file, uintmax_t val, const struct ufmt16_int_output *fmt);
UEXPORT size_t ufprintln_uint_fmt8(FILE *file, uintmax_t val, const struct ufmt8_int_output *fmt);

// - Float

#define uprint_float_fmt(val, fmt)                              \
    _Generic((fmt),                                             \
        const struct ufmt32_float_output *: uprint_float_fmt32, \
        struct ufmt32_float_output *:       uprint_float_fmt32, \
        const struct ufmt16_float_output *: uprint_float_fmt16, \
        struct ufmt16_float_output *:       uprint_float_fmt16, \
        const struct ufmt8_float_output *:  uprint_float_fmt8,  \
        struct ufmt8_float_output *:        uprint_float_fmt8   \
    )((val), (fmt))

UEXPORT size_t uprint_float(double val);
UEXPORT size_t uprint_float_fmt32(double val, const struct ufmt32_float_output *fmt);
UEXPORT size_t uprint_float_fmt16(double val, const struct ufmt16_float_output *fmt);
UEXPORT size_t uprint_float_fmt8(double val, const struct ufmt8_float_output *fmt);

#define uprintln_float_fmt(val, fmt)                              \
    _Generic((fmt),                                               \
        const struct ufmt32_float_output *: uprintln_float_fmt32, \
        struct ufmt32_float_output *:       uprintln_float_fmt32, \
        const struct ufmt16_float_output *: uprintln_float_fmt16, \
        struct ufmt16_float_output *:       uprintln_float_fmt16, \
        const struct ufmt8_float_output *:  uprintln_float_fmt8,  \
        struct ufmt8_float_output *:        uprintln_float_fmt8   \
    )((val), (fmt))

UEXPORT size_t uprintln_float(double val);
UEXPORT size_t uprintln_float_fmt32(double val, const struct ufmt32_float_output *fmt);
UEXPORT size_t uprintln_float_fmt16(double val, const struct ufmt16_float_output *fmt);
UEXPORT size_t uprintln_float_fmt8(double val, const struct ufmt8_float_output *fmt);


#define ufprint_float_fmt(file, val, fmt)                        \
    _Generic((fmt),                                              \
        const struct ufmt32_float_output *: ufprint_float_fmt32, \
        struct ufmt32_float_output *:       ufprint_float_fmt32, \
        const struct ufmt16_float_output *: ufprint_float_fmt16, \
        struct ufmt16_float_output *:       ufprint_float_fmt16, \
        const struct ufmt8_float_output *:  ufprint_float_fmt8,  \
        struct ufmt8_float_output *:        ufprint_float_fmt8   \
    )((file), (val), (fmt))

UEXPORT size_t ufprint_float(FILE *file, double val);
UEXPORT size_t ufprint_float_fmt32(FILE *file, double val, const struct ufmt32_float_output *fmt);
UEXPORT size_t ufprint_float_fmt16(FILE *file, double val, const struct ufmt16_float_output *fmt);
UEXPORT size_t ufprint_float_fmt8(FILE *file, double val, const struct ufmt8_float_output *fmt);

#define ufprintln_float_fmt(file, val, fmt)                        \
    _Generic((fmt),                                                \
        const struct ufmt32_float_output *: ufprintln_float_fmt32, \
        struct ufmt32_float_output *:       ufprintln_float_fmt32, \
        const struct ufmt16_float_output *: ufprintln_float_fmt16, \
        struct ufmt16_float_output *:       ufprintln_float_fmt16, \
        const struct ufmt8_float_output *:  ufprintln_float_fmt8,  \
        struct ufmt8_float_output *:        ufprintln_float_fmt8   \
    )((file), (val), (fmt))

UEXPORT size_t ufprintln_float(FILE *file, double val);
UEXPORT size_t ufprintln_float_fmt32(FILE *file, double val, const struct ufmt32_float_output *fmt);
UEXPORT size_t ufprintln_float_fmt16(FILE *file, double val, const struct ufmt16_float_output *fmt);
UEXPORT size_t ufprintln_float_fmt8(FILE *file, double val, const struct ufmt8_float_output *fmt);

// - Bool

UEXPORT size_t uprint_bool(bool val);
UEXPORT size_t uprint_case_bool(ucase_t ca, bool val);
UEXPORT size_t uprint_lower_bool(bool val);
UEXPORT size_t uprint_upper_bool(bool val);

UEXPORT size_t uprintln_bool(bool val);
UEXPORT size_t uprintln_case_bool(ucase_t ca, bool val);
UEXPORT size_t uprintln_lower_bool(bool val);
UEXPORT size_t uprintln_upper_bool(bool val);


UEXPORT size_t ufprint_bool(FILE *file, bool val);
UEXPORT size_t ufprint_case_bool(FILE *file, ucase_t ca, bool val);
UEXPORT size_t ufprint_lower_bool(FILE *file, bool val);
UEXPORT size_t ufprint_upper_bool(FILE *file, bool val);

UEXPORT size_t ufprintln_bool(FILE *file, bool val);
UEXPORT size_t ufprintln_case_bool(FILE *file, ucase_t ca, bool val);
UEXPORT size_t ufprintln_lower_bool(FILE *file, bool val);
UEXPORT size_t ufprintln_upper_bool(FILE *file, bool val);

// - Char

UEXPORT size_t uprint_uc32(uc32_t c);
UEXPORT size_t uprint_uc16(uc16_t c);
UEXPORT size_t uprint_uc8(uc8_t c);

UEXPORT size_t uprint_uc32n(uc32_t c, size_t n);
UEXPORT size_t uprint_uc16n(uc16_t c, size_t n);
UEXPORT size_t uprint_uc8n(uc8_t c, size_t n);


UEXPORT size_t uprintln_uc32(uc32_t c);
UEXPORT size_t uprintln_uc16(uc16_t c);
UEXPORT size_t uprintln_uc8(uc8_t c);

UEXPORT size_t uprintln_uc32n(uc32_t c, size_t n);
UEXPORT size_t uprintln_uc16n(uc16_t c, size_t n);
UEXPORT size_t uprintln_uc8n(uc8_t c, size_t n);



UEXPORT size_t ufprint_uc32(FILE *file, uc32_t c);
UEXPORT size_t ufprint_uc16(FILE *file, uc16_t c);
UEXPORT size_t ufprint_uc8(FILE *file, uc8_t c);

UEXPORT size_t ufprint_uc32n(FILE *file, uc32_t c, size_t n);
UEXPORT size_t ufprint_uc16n(FILE *file, uc16_t c, size_t n);
UEXPORT size_t ufprint_uc8n(FILE *file, uc8_t c, size_t n);


UEXPORT size_t ufprintln_uc32(FILE *file, uc32_t c);
UEXPORT size_t ufprintln_uc16(FILE *file, uc16_t c);
UEXPORT size_t ufprintln_uc8(FILE *file, uc8_t c);

UEXPORT size_t ufprintln_uc32n(FILE *file, uc32_t c, size_t n);
UEXPORT size_t ufprintln_uc16n(FILE *file, uc16_t c, size_t n);
UEXPORT size_t ufprintln_uc8n(FILE *file, uc8_t c, size_t n);

// - CStr

UEXPORT size_t uprint_uz32(const uc32_t *cstr);
UEXPORT size_t uprint_uz16(const uc16_t *cstr);
UEXPORT size_t uprint_uz8(const uc8_t *cstr);

UEXPORT size_t uprint_uz32n(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uprint_uz16n(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uprint_uz8n(const uc8_t *cstr, size_t cstr_len);


UEXPORT size_t uprintln_uz32(const uc32_t *cstr);
UEXPORT size_t uprintln_uz16(const uc16_t *cstr);
UEXPORT size_t uprintln_uz8(const uc8_t *cstr);

UEXPORT size_t uprintln_uz32n(const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t uprintln_uz16n(const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t uprintln_uz8n(const uc8_t *cstr, size_t cstr_len);



UEXPORT size_t ufprint_uz32(FILE *file, const uc32_t *cstr);
UEXPORT size_t ufprint_uz16(FILE *file, const uc16_t *cstr);
UEXPORT size_t ufprint_uz8(FILE *file, const uc8_t *cstr);

UEXPORT size_t ufprint_uz32n(FILE *file, const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t ufprint_uz16n(FILE *file, const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t ufprint_uz8n(FILE *file, const uc8_t *cstr, size_t cstr_len);


UEXPORT size_t ufprintln_uz32(FILE *file, const uc32_t *cstr);
UEXPORT size_t ufprintln_uz16(FILE *file, const uc16_t *cstr);
UEXPORT size_t ufprintln_uz8(FILE *file, const uc8_t *cstr);

UEXPORT size_t ufprintln_uz32n(FILE *file, const uc32_t *cstr, size_t cstr_len);
UEXPORT size_t ufprintln_uz16n(FILE *file, const uc16_t *cstr, size_t cstr_len);
UEXPORT size_t ufprintln_uz8n(FILE *file, const uc8_t *cstr, size_t cstr_len);

// - CView

UEXPORT size_t uprint_ucv32(ucv32_t view);
UEXPORT size_t uprint_ucv16(ucv16_t view);
UEXPORT size_t uprint_ucv8(ucv8_t view);

UEXPORT size_t uprintln_ucv32(ucv32_t view);
UEXPORT size_t uprintln_ucv16(ucv16_t view);
UEXPORT size_t uprintln_ucv8(ucv8_t view);


UEXPORT size_t ufprint_ucv32(FILE *file, ucv32_t view);
UEXPORT size_t ufprint_ucv16(FILE *file, ucv16_t view);
UEXPORT size_t ufprint_ucv8(FILE *file, ucv8_t view);

UEXPORT size_t ufprintln_ucv32(FILE *file, ucv32_t view);
UEXPORT size_t ufprintln_ucv16(FILE *file, ucv16_t view);
UEXPORT size_t ufprintln_ucv8(FILE *file, ucv8_t view);

// - Str

UEXPORT size_t uprint_us32(const us32_t *str);
UEXPORT size_t uprint_us16(const us16_t *str);
UEXPORT size_t uprint_us8(const us8_t *str);

UEXPORT size_t uprintln_us32(const us32_t *str);
UEXPORT size_t uprintln_us16(const us16_t *str);
UEXPORT size_t uprintln_us8(const us8_t *str);


UEXPORT size_t ufprint_us32(FILE *file, const us32_t *str);
UEXPORT size_t ufprint_us16(FILE *file, const us16_t *str);
UEXPORT size_t ufprint_us8(FILE *file, const us8_t *str);

UEXPORT size_t ufprintln_us32(FILE *file, const us32_t *str);
UEXPORT size_t ufprintln_us16(FILE *file, const us16_t *str);
UEXPORT size_t ufprintln_us8(FILE *file, const us8_t *str);

// - View

UEXPORT size_t uprint_uv32(uv32_t view);
UEXPORT size_t uprint_uv16(uv16_t view);
UEXPORT size_t uprint_uv8(uv8_t view);

UEXPORT size_t uprintln_uv32(uv32_t view);
UEXPORT size_t uprintln_uv16(uv16_t view);
UEXPORT size_t uprintln_uv8(uv8_t view);


UEXPORT size_t ufprint_uv32(FILE *file, uv32_t view);
UEXPORT size_t ufprint_uv16(FILE *file, uv16_t view);
UEXPORT size_t ufprint_uv8(FILE *file, uv8_t view);

UEXPORT size_t ufprintln_uv32(FILE *file, uv32_t view);
UEXPORT size_t ufprintln_uv16(FILE *file, uv16_t view);
UEXPORT size_t ufprintln_uv8(FILE *file, uv8_t view);

// -- New line

UEXPORT size_t uprint_new_line(void);
UEXPORT size_t ufprint_new_line(FILE *file);

#endif