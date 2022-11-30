#include "int.h"

#include <stdint.h>
#include <limits.h>

#include <ustr/fmt/radix.h>
#include <ustr/util/bit.h>

bool uifmt_valid(const struct uifmt *fmt) {
    if (!fmt)
        return false;

    if (!uradix_valid(fmt->radix))
        return false;

    if (upower_of_2(fmt->radix) 
     && fmt->show_leading_zeroes
     && fmt->leading_zeroes_limit > CHAR_BIT * sizeof(intmax_t))
        return false;

    return true;
}