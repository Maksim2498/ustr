#ifndef USTR_TYPE_FMT_INT_H
#define USTR_TYPE_FMT_INT_H

#include <stdbool.h>
#include <stddef.h>

#include <ustr/type/cview.h>

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
    UIFMT_GROUP_SIZE_UNUSED = 0,
    UIFMT_PRECISON_UNUSED   = 0
};

struct uifmt {
    ucv32_t        group_separator;
    size_t         leading_zeroes_limit;
    size_t         start_from;
    size_t         max_len;              // counts characters before start_from
    unsigned char  group_size;           // if 0 then unused
    unsigned char  precision;            // if 0 then unused
    ucase_t        radix_prefix_case;
    ucase_t        digit_case;
    uradix_t       radix;
    bool           show_plus;
    bool           show_minus;
    bool           show_radix_prefix;
};

#endif