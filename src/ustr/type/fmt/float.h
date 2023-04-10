#ifndef USTR_TYPE_FMT_FLOAT_H
#define USTR_TYPE_FMT_FLOAT_H

#include <stdbool.h>
#include <stddef.h>

#include <ustr/type/cview.h>
#include <ustr/util/export.h>

#include "case.h"
#include "plus.h"

// Output

// - Struct

struct ufmt32_float_output {
    ucv32_t       nan;
    ucv32_t       inf;

    unsigned char precision;

    ucase_t       exp_case;
    bool          scientific;

    uplus_t       plus;
};

struct ufmt16_float_output {
    ucv16_t       nan;
    ucv16_t       inf;

    unsigned char precision;

    ucase_t       exp_case;
    bool          scientific;

    uplus_t       plus;
};

struct ufmt8_float_output {
    ucv8_t        nan;
    ucv8_t        inf;

    unsigned char precision;

    ucase_t       exp_case;
    bool          scientific;

    uplus_t       plus;
};

// - Predefined

#define UFMTX_FLOAT_OUTPUT_CTC(X) ((struct ufmt##X##_float_output) { \
    .nan = ucv##X("NaN"),                                            \
    .inf = ucv##X("∞"),                                              \
                                                                     \
    .precision = 0,                                                  \
                                                                     \
    .exp_case   = UCASE_LOWER,                                       \
    .scientific = false,                                             \
                                                                     \
    .plus       = UPLUS_NONE                                         \
})

#define UFMT32_FLOAT_OUTPUT_CTC UFMTX_FLOAT_OUTPUT_CTC(32)
UEXPORT static const struct ufmt32_float_output UFMT32_FLOAT_OUTPUT = UFMT32_FLOAT_OUTPUT_CTC;

#define UFMT16_FLOAT_OUTPUT_CTC UFMTX_FLOAT_OUTPUT_CTC(16)
UEXPORT static const struct ufmt16_float_output UFMT16_FLOAT_OUTPUT = UFMT16_FLOAT_OUTPUT_CTC;

#define UFMT8_FLOAT_OUTPUT_CTC UFMTX_FLOAT_OUTPUT_CTC(8)
UEXPORT static const struct ufmt8_float_output UFMT8_FLOAT_OUTPUT = UFMT8_FLOAT_OUTPUT_CTC;

#endif