#ifndef USTR_TYPE_FMT_FMT_H
#define USTR_TYPE_FMT_FMT_H

#include "case.h"
#include "radix.h"
#include "type.h"

struct uigfmt {
    uradix_t radix;
    ucase_t  digit_case;
    bool     show_plus;
    ucase_t  radix_prefix_case;
    bool     show_radix_prefix;
};

struct ufgfmt {
    ucase_t exp_case;
    bool    scientific;
    bool    show_plus;
};

struct ubgfmt {
    ucase_t char_case;
};

struct ufmt {
    size_t   precision;
    unsigned len;
    bool     arg_precision;
    bool     use_precision;
    utype_t  type;

    union {
        struct uigfmt i;
        struct ufgfmt f;
        struct ubgfmt b;
    };
};

#endif