#ifndef USTR_FMT_INT_H
#define USTR_FMT_INT_H

#include <stdbool.h>
#include <limits.h>

#include <ustr/type/fmt/case.h>
#include <ustr/type/fmt/int.h>

static const struct uifmt UIFMT_BIN = {
    .start_from           = 0,
    .max_len              = SIZE_MAX,
    .leading_zeroes_limit = 0,
    .group_size           = 0,
    .precision            = UCHAR_MAX,
    .radix                = 2,
    .radix_prefix_case    = UCASE_LOWER,
    .show_plus            = false,
    .show_minus           = true,
    .show_radix_prefix    = true
};

static const struct uifmt UIFMT_OCT = {
    .start_from           = 0,
    .max_len              = SIZE_MAX,
    .leading_zeroes_limit = 0,
    .group_size           = 0,
    .precision            = UCHAR_MAX,
    .radix                = 8,
    .radix_prefix_case    = UCASE_LOWER,
    .show_plus            = false,
    .show_minus           = true,
    .show_radix_prefix    = true
};

static const struct uifmt UIFMT_DEC = {
    .start_from           = 0,
    .max_len              = SIZE_MAX,
    .leading_zeroes_limit = 0,
    .group_size           = 0,
    .precision            = UCHAR_MAX,
    .radix                = 10,
    .show_plus            = false,
    .show_minus           = true
};

static const struct uifmt UIFMT_HEX = {
    .start_from           = 0,
    .max_len              = SIZE_MAX,
    .leading_zeroes_limit = 0,
    .group_size           = 0,
    .precision            = UCHAR_MAX,
    .radix                = 16,
    .radix_prefix_case    = UCASE_LOWER,
    .digit_case           = UCASE_UPPER,
    .show_plus            = false,
    .show_minus           = true,
    .show_radix_prefix    = true
};

bool uifmt_valid(const struct uifmt *fmt);

#endif