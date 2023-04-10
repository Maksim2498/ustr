#ifndef USTR_TYPE_FMT_CASE_H
#define USTR_TYPE_FMT_CASE_H

#include <ustr/util/name.h>

// Name

UEXPORT_NAME(UCASE_NONE,  "NONE");
UEXPORT_NAME(UCASE_UPPER, "UPPER");
UEXPORT_NAME(UCASE_LOWER, "LOWER");

// Type

enum {
    UCASE_ANY,
    UCASE_NONE = UCASE_ANY,
    UCASE_UPPER,
    UCASE_LOWER,
    UCASE_COUNT
};

typedef unsigned char ucase_t;

#endif