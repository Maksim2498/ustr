#include "float.h"

#include <ustr/fmt/case.h>
#include <ustr/fmt/plus.h>
#include <ustr/cview.h>

size_t uwrite_float_32(double val, const struct ufmt32_float_output *fmt, uwrite_uc32_t write, void *write_arg) {
    // TODO
    return 0;
}

size_t uwrite_float_16(double val, const struct ufmt16_float_output *fmt, uwrite_uc16_t write, void *write_arg) {
    // TODO
    return 0;
}

size_t uwrite_float_8(double val, const struct ufmt8_float_output *fmt, uwrite_uc8_t write, void *write_arg) {
    // TODO
    return 0;
}

#define UFMTX_FLOAT_OUTPUT_VALID(fmt, X) \
    return fmt                           \
        && ucv##X##_valid(fmt->nan)      \
        && ucv##X##_valid(fmt->inf)      \
        && ucase_valid(fmt->exp_case)    \
        && uplus_valid(fmt->plus)

bool ufmt32_float_output_valid(const struct ufmt32_float_output *fmt) {
    UFMTX_FLOAT_OUTPUT_VALID(fmt, 32);
}

bool ufmt16_float_output_valid(const struct ufmt16_float_output *fmt) {
    UFMTX_FLOAT_OUTPUT_VALID(fmt, 16);
}

bool ufmt8_float_output_valid(const struct ufmt8_float_output *fmt) {
    UFMTX_FLOAT_OUTPUT_VALID(fmt, 8);
}