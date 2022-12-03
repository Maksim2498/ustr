#ifndef USTR_TYPE_FMT_FMT_H
#define USTR_TYPE_FMT_FMT_H

#include "case.h"
#include "radix.h"
#include "type.h"

struct uigfmt {
    ucase_t  digit_case;
    uradix_t radix;
    size_t   precision;
};

struct ufgfmt {
    ucase_t exp_case;
    bool    scientific;
};

struct ucgfmt {
    size_t count;
    bool   arg_count;
};

struct ubgfmt {
    ucase_t c;
};

struct usgfmt {
    size_t len;
    bool   arg_len;
    bool   type_len;
};

struct ufmt {
    size_t  len;
    utype_t type;

    union {
        struct uigfmt i;
        struct ufgfmt f;
        struct ucgfmt c;
        struct ubgfmt b;
        struct usgfmt s;
    };
};

#endif