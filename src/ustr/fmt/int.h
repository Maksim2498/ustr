#ifndef USTR_FMT_INT_H
#define USTR_FMT_INT_H

#include <stdbool.h>

#include <ustr/type/fmt/case.h>
#include <ustr/type/fmt/int.h>

static const struct uifmt UIFMT_BIN = {
    .group_size          = 0,
    .precision           = 0,
    .radix               = 2,
    .radix_prefix_case   = UCASE_LOWER,
    .show_plus           = false,
    .show_minus          = true,
    .show_radix_prefix   = true,
    .show_leading_zeroes = false
};

static const struct uifmt UIFMT_OCT = {
    .group_size          = 0,
    .precision           = 0,
    .radix               = 8,
    .radix_prefix_case   = UCASE_LOWER,
    .show_plus           = false,
    .show_minus          = true,
    .show_radix_prefix   = true,
    .show_leading_zeroes = false
};

static const struct uifmt UIFMT_DEC = {
    .group_size        = 0,
    .precision         = 0,
    .radix             = 10,
    .show_plus         = false,
    .show_minus        = true
};

static const struct uifmt UIFMT_HEX = {
    .group_size          = 0,
    .precision           = 0,
    .radix               = 16,
    .radix_prefix_case   = UCASE_LOWER,
    .digit_case          = UCASE_UPPER,
    .show_plus           = false,
    .show_minus          = true,
    .show_radix_prefix   = true,
    .show_leading_zeroes = false
};

bool uifmt_valid(const struct uifmt *fmt);

#endif