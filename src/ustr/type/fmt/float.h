#ifndef USTR_TYPE_FMT_FLOAT_H
#define USTR_TYPE_FMT_FLOAT_H

#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

#include <ustr/type/cview.h>

#include "case.h"

enum {
    UFFMT_AUTO_PRECISION = UCHAR_MAX
};

struct uffmt {
    ucv32_t       nan;
    ucv32_t       inf;
    size_t        start_from;
    size_t        max_len;
    unsigned char precision;
    ucase_t       exp_case;
    bool          scientific;
    bool          show_plus;
    bool          show_minus;
};

#endif