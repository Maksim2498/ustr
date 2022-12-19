#include "int.h"

#include <assert.h>

#include <ustr/fmt/case.h>
#include <ustr/fmt/radix.h>
#include <ustr/cview.h>

#include "fmt.h"

struct uifmt uifmt_from_ufmt(const struct ufmt *fmt, va_list *args) {
    assert(ufmt_valid(fmt) && args);

    struct uifmt res = UIFMT_DEC;

    res.digit_case        = fmt->i.digit_case;
    res.radix             = fmt->i.radix;
    res.radix_prefix_case = fmt->i.radix_prefix_case;
    res.show_plus         = fmt->i.show_plus;
    res.show_radix_prefix = fmt->i.show_radix_prefix;

    if (fmt->use_precision)
        res.precision = fmt->arg_precision ? va_arg(*args, size_t) : fmt->precision;

    return res;
}

bool uifmt_valid(const struct uifmt *fmt) {
    return fmt
        && uradix_valid(fmt->radix)
        && (!fmt->group_size || ucv32_valid(fmt->group_separator))
        && (!uradix_has_prefix(fmt->radix) || ucase_valid(fmt->radix_prefix_case))
        && (fmt->radix <= 10               || ucase_valid(fmt->digit_case));
}