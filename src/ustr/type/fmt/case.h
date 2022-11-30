#ifndef USTR_TYPE_FMT_CASE_H
#define USTR_TYPE_FMT_CASE_H

enum {
    UCASE_ANY,
    UCASE_NONE = UCASE_ANY,
    UCASE_UPPER,
    UCASE_LOWER,
    UCASE_COUNT
};

typedef unsigned char ucase_t;

#endif