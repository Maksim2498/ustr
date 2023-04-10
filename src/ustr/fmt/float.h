#ifndef USTR_FMT_FLOAT_H
#define USTR_FMT_FLOAT_H

#include <ustr/type/fmt/float.h>
#include <ustr/type/util/write.h>
#include <ustr/util/export.h>

// Format

UEXPORT size_t uwrite_float_32(double val, const struct ufmt32_float_output *fmt, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_float_16(double val, const struct ufmt16_float_output *fmt, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_float_8(double val, const struct ufmt8_float_output *fmt, uwrite_uc8_t write, void *write_arg);

// Valid

UEXPORT bool ufmt32_float_output_valid(const struct ufmt32_float_output *fmt);
UEXPORT bool ufmt16_float_output_valid(const struct ufmt16_float_output *fmt);
UEXPORT bool ufmt8_float_output_valid(const struct ufmt8_float_output *fmt);

#endif