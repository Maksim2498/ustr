#include "case.h"

ucv32_t ucase_name(ucase_t c) {
    switch (c) {
        case UCASE_NONE:
            return UCASE_NONE_NAME;

        case UCASE_UPPER:
            return UCASE_UPPER_NAME;

        case UCASE_LOWER:
            return UCASE_LOWER_NAME;

        default:
            return ucv32("invalid case");
    }
}

bool ucase_valid(ucase_t c) {
    return c < UCASE_COUNT;
}