#ifndef USTR_TYPE_FMT_CASE_H
#define USTR_TYPE_FMT_CASE_H

#include <ustr/cview.h>

typedef union {
    UCASE_UPPER
    UCASE_LOWER,
    UCASE_COUNT
} ucase_t;

#endif