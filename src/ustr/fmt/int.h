#ifndef USTR_FMT_INT_H
#define USTR_FMT_INT_H

#include <stddef.h>
#include <stdint.h>

#include <ustr/type/fmt/int.h>
#include <ustr/type/util/write.h>
#include <ustr/util/export.h>

// Format

UEXPORT size_t uwrite_int_32(intmax_t val, const struct ufmt32_int_output *fmt, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_uint_32(uintmax_t val, const struct ufmt32_int_output *fmt, uwrite_uc32_t write, void *write_arg);

UEXPORT size_t uwrite_int_16(intmax_t val, const struct ufmt16_int_output *fmt, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_uint_16(uintmax_t val, const struct ufmt16_int_output *fmt, uwrite_uc16_t write, void *write_arg);

UEXPORT size_t uwrite_int_8(intmax_t val, const struct ufmt8_int_output *fmt, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_uint_8(uintmax_t val, const struct ufmt8_int_output *fmt, uwrite_uc8_t write, void *write_arg);

// Valid

UEXPORT bool ufmt32_int_output_valid(const struct ufmt32_int_output *fmt);
UEXPORT bool ufmt16_int_output_valid(const struct ufmt16_int_output *fmt);
UEXPORT bool ufmt8_int_output_valid(const struct ufmt8_int_output *fmt);

#endif