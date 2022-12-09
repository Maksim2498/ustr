#ifndef USTR_TYPE_FMT_FLOAT_H
#define USTR_TYPE_FMT_FLOAT_H

#include <stdbool.h>
#include <stddef.h>

#include <ustr/type/cview.h>

#include "case.h"

struct uffmt {
    ucv32_t nan;
    ucv32_t inf;
    size_t  start_from;
    size_t  max_len;
    ucase_t exp_case;
    bool    scientific;
    bool    show_plus;
    bool    show_minus;
};

#endif