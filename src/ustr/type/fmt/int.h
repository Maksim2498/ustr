#ifndef USTR_TYPE_FMT_INT_H
#define USTR_TYPE_FMT_INT_H

#include <stdbool.h>
#include <stddef.h>

#include <ustr/type/cview.h>

#include "case.h"
#include "plus.h"
#include "radix.h"

// Value: 2498249824982498
//
//            |  precision  |
//            |-------------|
// Formatted: +2,498,249,824,000,000
//            ^ ^   |___|                radix: 10 - from 2 to 36
//            | |   |                    show_radix_prefix: true/false - doesn't matter for radix with no prefix
//            | |   |                                       (only 2, 8, and 16 has prefix)
//            | |   +- group size        prefix_case: UCASE_UPPER/UCASE_LOWER - doesn't matter for radix with no prefix
//            | |                        digit_case: UCASE_UPPER/UCASE_LOWER - doesn't matter for radix <= 10
//            | +- group separator
//            |
//            +- plus

// Output

// - Struct

struct ufmt32_int_output {
    ucv32_t       group_sep;
    unsigned char group_size; // 0 if unused

    unsigned char precision;  // 0 if unused
    unsigned char min_digits;

    bool          show_radix_prefix;
    ucase_t       radix_prefix_case;
    uradix_t      radix;

    ucase_t       digit_case;

    uplus_t       plus;
};

struct ufmt16_int_output {
    ucv16_t       group_sep;
    unsigned char group_size; // 0 if unused

    unsigned char precision;  // 0 if unused
    unsigned char min_digits;

    bool          show_radix_prefix;
    ucase_t       radix_prefix_case;
    uradix_t      radix;

    ucase_t       digit_case;

    uplus_t       plus;
};

struct ufmt8_int_output {
    ucv8_t        group_sep;
    unsigned char group_size; // 0 if unused

    unsigned char precision;  // 0 if unused
    unsigned char min_digits;

    bool          show_radix_prefix;
    ucase_t       radix_prefix_case;
    uradix_t      radix;

    ucase_t       digit_case;

    uplus_t       plus;
};

// - Predefined

#define UFMTX_INT_OUTPUT_R_CTC(X, R) ((struct ufmt##X##_int_output) { \
    .group_sep         = UCV##X##_EMPTY_CTC,                          \
    .group_size        = 0,                                           \
                                                                      \
    .precision         = 0,                                           \
    .min_digits        = 0,                                           \
                                                                      \
    .show_radix_prefix = false,                                       \
    .radix_prefix_case = UCASE_LOWER,                                 \
    .radix             = R,                                           \
                                                                      \
    .digit_case        = UCASE_UPPER,                                 \
                                                                      \
    .plus              = UPLUS_NONE                                   \
})

// -- Binary 

#define UFMT32_INT_OUTPUT_BIN_CTC UFMTX_INT_OUTPUT_R_CTC(32, 2)
static const struct ufmt32_int_output UFMT32_INT_OUTPUT_BIN = UFMT32_INT_OUTPUT_BIN_CTC;

#define UFMT16_INT_OUTPUT_BIN_CTC UFMTX_INT_OUTPUT_R_CTC(16, 2)
static const struct ufmt16_int_output UFMT16_INT_OUTPUT_BIN = UFMT16_INT_OUTPUT_BIN_CTC;

#define UFMT8_INT_OUTPUT_BIN_CTC UFMTX_INT_OUTPUT_R_CTC(8, 2)
static const struct ufmt8_int_output UFMT8_INT_OUTPUT_BIN = UFMT8_INT_OUTPUT_BIN_CTC;

// -- Octal

#define UFMT32_INT_OUTPUT_OCT_CTC UFMTX_INT_OUTPUT_R_CTC(32, 8)
static const struct ufmt32_int_output UFMT32_INT_OUTPUT_OCT = UFMT32_INT_OUTPUT_OCT_CTC;

#define UFMT16_INT_OUTPUT_OCT_CTC UFMTX_INT_OUTPUT_R_CTC(16, 8)
static const struct ufmt16_int_output UFMT16_INT_OUTPUT_OCT = UFMT16_INT_OUTPUT_OCT_CTC;

#define UFMT8_INT_OUTPUT_OCT_CTC UFMTX_INT_OUTPUT_R_CTC(8, 8)
static const struct ufmt8_int_output UFMT8_INT_OUTPUT_OCT = UFMT8_INT_OUTPUT_OCT_CTC;

// -- Decimal

#define UFMT32_INT_OUTPUT_DEC_CTC UFMTX_INT_OUTPUT_R_CTC(32, 10)
static const struct ufmt32_int_output UFMT32_INT_OUTPUT_DEC = UFMT32_INT_OUTPUT_DEC_CTC;

#define UFMT16_INT_OUTPUT_DEC_CTC UFMTX_INT_OUTPUT_R_CTC(16, 10)
static const struct ufmt16_int_output UFMT16_INT_OUTPUT_DEC = UFMT16_INT_OUTPUT_DEC_CTC;

#define UFMT8_INT_OUTPUT_DEC_CTC UFMTX_INT_OUTPUT_R_CTC(8, 10)
static const struct ufmt8_int_output UFMT8_INT_OUTPUT_DEC = UFMT8_INT_OUTPUT_DEC_CTC;

// -- Hexadecimal

#define UFMT32_INT_OUTPUT_HEX_CTC UFMTX_INT_OUTPUT_R_CTC(32, 16)
static const struct ufmt32_int_output UFMT32_INT_OUTPUT_HEX = UFMT32_INT_OUTPUT_HEX_CTC;

#define UFMT16_INT_OUTPUT_HEX_CTC UFMTX_INT_OUTPUT_R_CTC(16, 16)
static const struct ufmt16_int_output UFMT16_INT_OUTPUT_HEX = UFMT16_INT_OUTPUT_HEX_CTC;

#define UFMT8_INT_OUTPUT_HEX_CTC UFMTX_INT_OUTPUT_R_CTC(8, 16)
static const struct ufmt8_int_output UFMT8_INT_OUTPUT_HEX = UFMT8_INT_OUTPUT_HEX_CTC;

#endif