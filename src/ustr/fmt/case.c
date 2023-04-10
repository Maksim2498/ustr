#include "case.h"

#include <assert.h>

#define UCASE_NAME_X(c, X)                 \
    assert(ucase_valid(c));                \
                                           \
    switch (c) {                           \
        case UCASE_NONE:                   \
            return UCASE_NONE_NAME_##X;    \
                                           \
        case UCASE_UPPER:                  \
            return UCASE_UPPER_NAME_##X;   \
                                           \
        case UCASE_LOWER:                  \
            return UCASE_LOWER_NAME_##X;   \
                                           \
        default:                           \
            return ucv##X("invalid case"); \
    }

ucv32_t ucase_name_32(ucase_t c) {
    UCASE_NAME_X(c, 32);
}

ucv16_t ucase_name_16(ucase_t c) {
    UCASE_NAME_X(c, 16);
}

ucv8_t ucase_name_8(ucase_t c) {
    UCASE_NAME_X(c, 8);
}

bool ucase_valid(ucase_t c) {
    return c < UCASE_COUNT;
}

bool ucase_valid_output(ucase_t c) {
    return UCASE_LOWER == c
        || UCASE_UPPER == c;
}