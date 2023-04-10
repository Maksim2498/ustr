#ifndef USTR_FMT_FMT_H
#define USTR_FMT_FMT_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include <ustr/type/fmt/float.h>
#include <ustr/type/fmt/fmt.h>
#include <ustr/type/fmt/int.h>
#include <ustr/type/util/write.h>
#include <ustr/type/char.h>
#include <ustr/type/cview.h>
#include <ustr/type/str.h>
#include <ustr/type/view.h>
#include <ustr/util/export.h>

// Group format

// - Int

// -- Expand

UEXPORT struct ufmt32_int_output ufmt_int_group_output_expand_32(const struct ufmt_int_group_output *fmt);
UEXPORT struct ufmt16_int_output ufmt_int_group_output_expand_16(const struct ufmt_int_group_output *fmt);
UEXPORT struct ufmt8_int_output ufmt_int_group_output_expand_8(const struct ufmt_int_group_output *fmt);

// -- Valid

UEXPORT bool ufmt_int_group_output_valid(const struct ufmt_int_group_output *fmt);

// - Float

// -- Expand

UEXPORT struct ufmt32_float_output ufmt_float_group_output_expand_32(const struct ufmt_float_group_output *fmt);
UEXPORT struct ufmt16_float_output ufmt_float_group_output_expand_16(const struct ufmt_float_group_output *fmt);
UEXPORT struct ufmt8_float_output ufmt_float_group_output_expand_8(const struct ufmt_float_group_output *fmt);

// -- Valid

UEXPORT bool ufmt_float_group_output_valid(const struct ufmt_float_group_output *fmt);

// - Bool

// -- Valid

UEXPORT bool ufmt_bool_group_output_valid(const struct ufmt_bool_group_output *fmt);

// Format

// - Create

UEXPORT struct ufmt_output ufmt_output_from_uz32(const uc32_t *from);
UEXPORT struct ufmt_output ufmt_output_from_uz32n(const uc32_t *from, size_t from_len);
UEXPORT struct ufmt_output ufmt_output_from_ucv32(ucv32_t from);
UEXPORT struct ufmt_output ufmt_output_from_us32(const us32_t *from);
UEXPORT struct ufmt_output ufmt_output_from_uv32(uv32_t from);

UEXPORT struct ufmt_output ufmt_output_from_uz16(const uc16_t *from);
UEXPORT struct ufmt_output ufmt_output_from_uz16n(const uc16_t *from, size_t from_len);
UEXPORT struct ufmt_output ufmt_output_from_ucv16(ucv16_t from);
UEXPORT struct ufmt_output ufmt_output_from_us16(const us16_t *from);
UEXPORT struct ufmt_output ufmt_output_from_uv16(uv16_t from);

UEXPORT struct ufmt_output ufmt_output_from_uz8(const uc8_t *from);
UEXPORT struct ufmt_output ufmt_output_from_uz8n(const uc8_t *from, size_t from_len);
UEXPORT struct ufmt_output ufmt_output_from_ucv8(ucv8_t from);
UEXPORT struct ufmt_output ufmt_output_from_us8(const us8_t *from);
UEXPORT struct ufmt_output ufmt_output_from_uv8(uv8_t from);

// - Format

#define uwrite_fmt_32(fmt, write, write_arg) \
    _Generic((fmt),                          \
        const uc32_t *: uwrite_fmt_uz32_32,  \
        uc32_t *:       uwrite_fmt_uz32_32,  \
        ucv32_t:        uwrite_fmt_ucv32_32, \
        const us32_t *: uwrite_fmt_us32_32,  \
        us32_t *:       uwrite_fmt_us32_32,  \
        uv32_t:         uwrite_fmt_uv32_32   \
    )((fmt), (write), (write_arg))

UEXPORT size_t uwrite_fmt_uz32_32(const uc32_t *fmt, uwrite_uc32_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_uz32_32_v(const uc32_t *fmt, uwrite_uc32_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_uz32n_32(const uc32_t *fmt, size_t fmt_len, uwrite_uc32_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_uz32n_32_v(const uc32_t *fmt, size_t fmt_len, uwrite_uc32_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_ucv32_32(ucv32_t fmt, uwrite_uc32_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_ucv32_32_v(ucv32_t fmt, uwrite_uc32_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_us32_32(const us32_t *fmt, uwrite_uc32_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_us32_32_v(const us32_t *fmt, uwrite_uc32_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_uv32_32(uv32_t fmt, uwrite_uc32_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_uv32_32_v(uv32_t fmt, uwrite_uc32_t write, void *write_arg, va_list *args); 

#define uwrite_fmt_16(fmt, write, write_arg) \
    _Generic((fmt),                          \
        const uc16_t *: uwrite_fmt_uz16_16,  \
        uc16_t *:       uwrite_fmt_uz16_16,  \
        ucv16_t:        uwrite_fmt_ucv16_16, \
        const us16_t *: uwrite_fmt_us16_16,  \
        us16_t *:       uwrite_fmt_us16_16,  \
        uv16_t:         uwrite_fmt_uv16_16   \
    )((fmt), (write), (write_arg))

UEXPORT size_t uwrite_fmt_uz16_16(const uc16_t *fmt, uwrite_uc16_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_uz16_16_v(const uc16_t *fmt, uwrite_uc16_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_uz16n_16(const uc16_t *fmt, size_t fmt_len, uwrite_uc16_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_uz16n_16_v(const uc16_t *fmt, size_t fmt_len, uwrite_uc16_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_ucv16_16(ucv16_t fmt, uwrite_uc16_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_ucv16_16_v(ucv16_t fmt, uwrite_uc16_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_us16_16(const us16_t *fmt, uwrite_uc16_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_us16_16_v(const us16_t *fmt, uwrite_uc16_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_uv16_16(uv16_t fmt, uwrite_uc16_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_uv16_16_v(uv16_t fmt, uwrite_uc16_t write, void *write_arg, va_list *args); 

#define uwrite_fmt_8(fmt, write, write_arg) \
    _Generic((fmt),                         \
        const uc8_t *: uwrite_fmt_uz8_8,    \
        uc8_t *:       uwrite_fmt_uz8_8,    \
        ucv8_t:        uwrite_fmt_ucv8_8,   \
        const us8_t *: uwrite_fmt_us8_8,    \
        us8_t *:       uwrite_fmt_us8_8,    \
        uv8_t:         uwrite_fmt_uv8_8     \
    )((fmt), (write), (write_arg))

UEXPORT size_t uwrite_fmt_uz8_8(const uc8_t *fmt, uwrite_uc8_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_uz8_8_v(const uc8_t *fmt, uwrite_uc8_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_uz8n_8(const uc8_t *fmt, size_t fmt_len, uwrite_uc8_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_uz8n_8_v(const uc8_t *fmt, size_t fmt_len, uwrite_uc8_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_ucv8_8(ucv8_t fmt, uwrite_uc8_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_ucv8_8_v(ucv8_t fmt, uwrite_uc8_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_us8_8(const us8_t *fmt, uwrite_uc8_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_us8_8_v(const us8_t *fmt, uwrite_uc8_t write, void *write_arg, va_list *args); 
UEXPORT size_t uwrite_fmt_uv8_8(uv8_t fmt, uwrite_uc8_t write, void *write_arg, ...);
UEXPORT size_t uwrite_fmt_uv8_8_v(uv8_t fmt, uwrite_uc8_t write, void *write_arg, va_list *args); 

// - Valid

UEXPORT bool ufmt_output_valid(const struct ufmt_output *fmt);

#endif