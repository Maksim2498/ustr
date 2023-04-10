#include "bool.h"

#include <assert.h>

#include "case.h"

#define UFMT_BOOL_X(val, ca, write, write_arg, X)                                         \
    assert(ucase_valid_output(ca) && write);                                              \
                                                                                          \
    size_t           written = 0;                                                         \
    const uc##X##_t *str     = val ? UCASE_UPPER == ca ? uz##X("TRUE")  : uz##X("true")   \
                                   : UCASE_UPPER == ca ? uz##X("FALSE") : uz##X("false"); \
                                                                                          \
    while (*str) {                                                                        \
        if (write(*str++, write_arg))                                                     \
            break;                                                                        \
                                                                                          \
        ++written;                                                                        \
    }                                                                                     \
                                                                                          \
    return written

size_t uwrite_bool_32(bool val, ucase_t ca, uwrite_uc32_t write, void *write_arg) {
    UFMT_BOOL_X(val, ca, write, write_arg, 32);
}

size_t uwrite_bool_16(bool val, ucase_t ca, uwrite_uc16_t write, void *write_arg) {
    UFMT_BOOL_X(val, ca, write, write_arg, 16);
}

size_t uwrite_bool_8(bool val, ucase_t ca, uwrite_uc8_t write, void *write_arg) {
    UFMT_BOOL_X(val, ca, write, write_arg, 8);
}