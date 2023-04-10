#include "radix.h"

#include <assert.h>

#include "case.h"

#define URADIX_PREFIX_X(radix, ca, X)                         \
    assert(uradix_valid(radix) && ucase_valid_output(ca));    \
                                                              \
    switch (radix) {                                          \
        case 2:                                               \
            return UCASE_UPPER == ca ? UBIN_PREFIX_UPPER_##X  \
                                     : UBIN_PREFIX_LOWER_##X; \
                                                              \
        case 8:                                               \
            return UCASE_UPPER == ca ? UOCT_PREFIX_UPPER_##X  \
                                     : UOCT_PREFIX_LOWER_##X; \
                                                              \
        case 16:                                              \
            return UCASE_UPPER == ca ? UHEX_PREFIX_UPPER_##X  \
                                     : UHEX_PREFIX_LOWER_##X; \
                                                              \
        default:                                              \
            return UCV##X##_NULL;                             \
    }

ucv32_t uradix_prefix_32(uradix_t radix, ucase_t ca) {
    URADIX_PREFIX_X(radix, ca, 32);
}

ucv16_t uradix_prefix_16(uradix_t radix, ucase_t ca) {
    URADIX_PREFIX_X(radix, ca, 16);
}

ucv8_t uradix_prefix_8(uradix_t radix, ucase_t ca) {
    URADIX_PREFIX_X(radix, ca, 8);
}

bool uradix_has_prefix(uradix_t radix) {
    assert(uradix_valid(radix));

    switch (radix) {
        case 2:
        case 8:
        case 16:
            return true;

        default:
            return false;
    }
}

bool uradix_valid(uradix_t radix) {
    return 2 <= radix && radix <= URADIX_MAX;
}