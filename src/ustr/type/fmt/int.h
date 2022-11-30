#ifndef USTR_TYPE_FMT_INT_H
#define USTR_TYPE_FMT_INT_H

#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#include <ustr/type/char.h>

#include "case.h"
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
//            +- show plus

enum {
    UINT_MAX_UC8_LEN = 4 * CHAR_BIT * sizeof(intmax_t) - 1 // When group_size is 1
                     +     CHAR_BIT * sizeof(intmax_t)     // Max binary length
                     + 1                                   // Sign
                     + 4 * 2,                              // Max radix prefix length

    UINT_MAX_UC16_LEN = 2 * CHAR_BIT * sizeof(intmax_t) - 1 // When group_size is 1
                      +     CHAR_BIT * sizeof(intmax_t)     // Max binary length
                      + 1                                   // Sign
                      + 2 * 2,                              // Max radix prefix length

    UINT_MAX_UC32_LEN = CHAR_BIT * sizeof(intmax_t) - 1 // When group_size is 1
                      + CHAR_BIT * sizeof(intmax_t)     // Max binary length
                      + 1                               // Sign
                      + 2                               // Max radix prefix length
};

struct uifmt {
    uc32_t         group_separator;
    unsigned short leading_zeroes_limit;
    unsigned char  group_size;
    unsigned char  precision;
    ucase_t        radix_prefix_case;
    ucase_t        digit_case;
    uradix_t       radix;
    bool           show_plus;
    bool           show_minus;
    bool           show_radix_prefix;
    bool           show_leading_zeroes; // Only for radix = 2^n
};

#endif