#ifndef USTR_FMT_FLOAT_H
#define USTR_FMT_FLOAT_H

#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

#include <ustr/type/fmt/case.h>
#include <ustr/type/fmt/float.h>
#include <ustr/type/fmt/fmt.h>
#include <ustr/cview.h>

static const struct uffmt UFFMT = {
    .nan        = ucv32("NaN"),
    .inf        = ucv32("∞"),
    .start_from = 0,
    .max_len    = SIZE_MAX,
    .precision  = UFFMT_AUTO_PRECISION,
    .exp_case   = UCASE_LOWER,
    .scientific = false,
    .show_plus  = false,
    .show_minus = true
};

struct uffmt uffmt_from_ufmt(const struct ufmt *fmt, va_list *args);

bool uffmt_valid(const struct uffmt *fmt);

#endif