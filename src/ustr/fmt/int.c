#include "int.h"

#include <ustr/fmt/case.h>
#include <ustr/fmt/radix.h>
#include <ustr/cview.h>

bool uifmt_valid(const struct uifmt *fmt) {
    return fmt
        && uradix_valid(fmt->radix)
        && (!fmt->group_size || ucv32_valid(fmt->group_separator))
        && (!uradix_has_prefix(fmt->radix) || ucase_valid(fmt->radix_prefix_case))
        && (fmt->radix <= 10               || ucase_valid(fmt->digit_case));
}