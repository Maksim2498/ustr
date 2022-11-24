#ifndef USTR_TYPE_FMT_INT_H
#define USTR_TYPE_FMT_INT_H

#include <stdbool.h>

#include <ustr/type/char.h>
#include <ustr/type/cview.h>

#include "case.h"

// Value:      2498249824982498
// Formatted: +2,498,249,824,000,000
//            ^ ^   |___|   |_______|       radix: 10 - from 2 to 36
//            | |   |       |               show_radix_prefix: true/false - doesn't matter for radix with no prefix
//            | |   |       +- precision                                    (only 2, 8, and 16 has prefix)
//            | |   |                       prefix_case: UCASE_UPPER/UCASE_LOWER - doesn't matter for radix with no prefix
//            | |   +- group size           digit_case: UCASE_UPPER/UCASE_LOWER - doesn't matter for radix <= 10
//            | |
//            | +- group separator
//            |
//            +- show plus

struct uifmt {
    ucv32_t       group_separator;
    unsigned char group_size;
    unsigned char precision;
    unsigned char radix;
    unsigned char prefix_case;
    unsigned char digit_case;
    bool          show_plus;
    bool          show_radix_prefix;
};

#endif