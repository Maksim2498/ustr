#include "radix.h"

#include <assert.h>

ucv32_t uradix_prefix(unsigned radix, ucase_t ca) {
    assert(uradix_valid(radix));

    switch (radix) {
        case 2:
            return UCASE_UPPER == ca ? UBIN_PREFIX_UPPER : UBIN_PREFIX_LOWER;

        case 8:
            return UCASE_UPPER == ca ? UOCT_PREFIX_UPPER : UOCT_PREFIX_LOWER;

        case 16:
            return UCASE_UPPER == ca ? UHEX_PREFIX_UPPER : UHEX_PREFIX_LOWER;
        
        default:
            return ucv32_mk();
    }
}

bool uradix_valid(unsigned radix) {
    return 2 <= radix && radix <= URADIX_MAX;
}