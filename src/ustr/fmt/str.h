#ifndef USTR_FMT_STR_H
#define USTR_FMT_STR_H

#include <stddef.h>

#include <ustr/type/util/write.h>
#include <ustr/type/char.h>
#include <ustr/type/cview.h>
#include <ustr/type/str.h>
#include <ustr/type/view.h>
#include <ustr/util/export.h>

#define uwrite_32(val, write, write_arg) \
    _Generic((val),                      \
        const uc32_t *: uwrite_uz32_32,  \
        uc32_t *:       uwrite_ucv32_32, \
        ucv32_t:        uwrite_ucv32_32, \
        const us32_t *: uwrite_us32_32,  \
        us32_t *:       uwrite_us32_32,  \
        uv32_t:         uwrite_uv32_32,  \
                                         \
        const uc16_t *: uwrite_uz16_32,  \
        uc16_t *:       uwrite_ucv16_32, \
        ucv16_t:        uwrite_ucv16_32, \
        const us16_t *: uwrite_us16_32,  \
        us16_t *:       uwrite_us16_32,  \
        uv16_t:         uwrite_uv16_32,  \
                                         \
        const uc8_t *: uwrite_uz8_32,    \
        uc8_t *:       uwrite_ucv8_32,   \
        ucv8_t:        uwrite_ucv8_32,   \
        const us8_t *: uwrite_us8_32,    \
        us8_t *:       uwrite_us8_32,    \
        uv8_t:         uwrite_uv8_32     \
    )((val), (write), (write_arg))

UEXPORT size_t uwrite_uz32_32(const uc32_t *val, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_uz32n_32(const uc32_t *val, size_t val_len, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_ucv32_32(ucv32_t val, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_us32_32(const us32_t *val, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_uv32_32(uv32_t val, uwrite_uc32_t write, void *write_arg);

UEXPORT size_t uwrite_uz16_32(const uc16_t *val, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_uz16n_32(const uc16_t *val, size_t val_len, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_ucv16_32(ucv16_t val, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_us16_32(const us16_t *val, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_uv16_32(uv16_t val, uwrite_uc32_t write, void *write_arg);

UEXPORT size_t uwrite_uz8_32(const uc8_t *val, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_uz8n_32(const uc8_t *val, size_t val_len, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_ucv8_32(ucv8_t val, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_us8_32(const us8_t *val, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_uv8_32(uv8_t val, uwrite_uc32_t write, void *write_arg);

#define uwrite_16(val, write, write_arg) \
    _Generic((val),                      \
        const uc32_t *: uwrite_uz32_16,  \
        uc32_t *:       uwrite_ucv32_16, \
        ucv32_t:        uwrite_ucv32_16, \
        const us32_t *: uwrite_us32_16,  \
        us32_t *:       uwrite_us32_16,  \
        uv32_t:         uwrite_uv32_16,  \
                                         \
        const uc16_t *: uwrite_uz16_16,  \
        uc16_t *:       uwrite_ucv16_16, \
        ucv16_t:        uwrite_ucv16_16, \
        const us16_t *: uwrite_us16_16,  \
        us16_t *:       uwrite_us16_16,  \
        uv16_t:         uwrite_uv16_16,  \
                                         \
        const uc8_t *: uwrite_uz8_16,    \
        uc8_t *:       uwrite_ucv8_16,   \
        ucv8_t:        uwrite_ucv8_16,   \
        const us8_t *: uwrite_us8_16,    \
        us8_t *:       uwrite_us8_16,    \
        uv8_t:         uwrite_uv8_16     \
    )((val), (write), (write_arg))

UEXPORT size_t uwrite_uz32_16(const uc32_t *val, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_uz32n_16(const uc32_t *val, size_t val_len, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_ucv32_16(ucv32_t val, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_us32_16(const us32_t *val, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_uv32_16(uv32_t val, uwrite_uc16_t write, void *write_arg);

UEXPORT size_t uwrite_uz16_16(const uc16_t *val, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_uz16n_16(const uc16_t *val, size_t val_len, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_ucv16_16(ucv16_t val, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_us16_16(const us16_t *val, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_uv16_16(uv16_t val, uwrite_uc16_t write, void *write_arg);

UEXPORT size_t uwrite_uz8_16(const uc8_t *val, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_uz8n_16(const uc8_t *val, size_t val_len, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_ucv8_16(ucv8_t val, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_us8_16(const us8_t *val, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_uv8_16(uv8_t val, uwrite_uc16_t write, void *write_arg);

#define uwrite_8(val, write, write_arg) \
    _Generic((val),                     \
        const uc32_t *: uwrite_uz32_8,  \
        uc32_t *:       uwrite_ucv32_8, \
        ucv32_t:        uwrite_ucv32_8, \
        const us32_t *: uwrite_us32_8,  \
        us32_t *:       uwrite_us32_8,  \
        uv32_t:         uwrite_uv32_8,  \
                                        \
        const uc16_t *: uwrite_uz16_8,  \
        uc16_t *:       uwrite_ucv16_8, \
        ucv16_t:        uwrite_ucv16_8, \
        const us16_t *: uwrite_us16_8,  \
        us16_t *:       uwrite_us16_8,  \
        uv16_t:         uwrite_uv16_8,  \
                                        \
        const uc8_t *: uwrite_uz8_8,    \
        uc8_t *:       uwrite_ucv8_8,   \
        ucv8_t:        uwrite_ucv8_8,   \
        const us8_t *: uwrite_us8_8,    \
        us8_t *:       uwrite_us8_8,    \
        uv8_t:         uwrite_uv8_8     \
    )((val), (write), (write_arg))

UEXPORT size_t uwrite_uz32_8(const uc32_t *val, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_uz32n_8(const uc32_t *val, size_t val_len, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_ucv32_8(ucv32_t val, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_us32_8(const us32_t *val, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_uv32_8(uv32_t val, uwrite_uc8_t write, void *write_arg);

UEXPORT size_t uwrite_uz16_8(const uc16_t *val, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_uz16n_8(const uc16_t *val, size_t val_len, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_ucv16_8(ucv16_t val, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_us16_8(const us16_t *val, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_uv16_8(uv16_t val, uwrite_uc8_t write, void *write_arg);

UEXPORT size_t uwrite_uz8_8(const uc8_t *val, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_uz8n_8(const uc8_t *val, size_t val_len, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_ucv8_8(ucv8_t val, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_us8_8(const us8_t *val, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_uv8_8(uv8_t val, uwrite_uc8_t write, void *write_arg);

#endif