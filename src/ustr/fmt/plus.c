#include "plus.h"

#include <assert.h>

#define UPLUS_NAME_X(plus, X)            \
    assert(uplus_valid(plus));           \
                                         \
    switch (plus) {                      \
        case UPLUS_NONE:                 \
            return UPLUS_NONE_NAME_##X;  \
                                         \
        case UPLUS_SIGN:                 \
            return UPLUS_SIGN_NAME_##X;  \
                                         \
        case UPLUS_SPACE:                \
            return UPLUS_SPACE_NAME_##X; \
                                         \
        default:                         \
            assert(false);               \
            return ucv##X("not a plus"); \
    }

ucv32_t uplus_name_32(uplus_t plus) {
    UPLUS_NAME_X(plus, 32);
}

ucv16_t uplus_name_16(uplus_t plus) {
    UPLUS_NAME_X(plus, 16);
}

ucv8_t uplus_name_8(uplus_t plus) {
    UPLUS_NAME_X(plus, 8);
}

uc32_t uplus_uc32(uplus_t plus) {
    return uplus_uc8(plus);
}

uc16_t uplus_uc16(uplus_t plus) {
    return uplus_uc8(plus);
}

uc8_t uplus_uc8(uplus_t plus) {
    assert(uplus_valid(plus));

    switch (plus) {
        case UPLUS_SPACE:
            return ' ';

        case UPLUS_SIGN:
            return '+';

        default:
            return 0;
    }
}

bool uplus_valid(uplus_t plus) {
    return plus < UPLUS_COUNT;
}