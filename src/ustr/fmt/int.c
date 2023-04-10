#include "int.h"

#include <assert.h>
#include <stdbool.h>
#include <limits.h>

#include <ustr/fmt/case.h>
#include <ustr/fmt/plus.h>
#include <ustr/fmt/radix.h>
#include <ustr/char.h>
#include <ustr/cview.h>

enum {
    UMAX_DIGITS = sizeof(uintmax_t) * CHAR_BIT
};

static unsigned ufill_digits_buffer(uc8_t *digits, uintmax_t val, ucase_t digit_case, uradix_t radix, unsigned precision) {
    unsigned digit_count = 0;

    // Convert

    do {
        digits[digit_count++] = uc8_case_radix_from_val(digit_case, radix, val % radix);
        val /= radix;
    } while (val);

    // Apply precision

    if (precision && digit_count > precision)
        for (int i = digit_count - precision - 1; i >= 0; --i)
            digits[i] = '0';

    return digit_count;
}

#define utry_write(c)              \
    do {                           \
        if (write((c), write_arg)) \
            return written;        \
                                   \
        ++written;                 \
    } while (false)

#define utry_write_ucvx(view, X)                                                                      \
    for (const uc##X##_t *it = ucv##X##_cbegin((view)), *end = ucv##X##_cend((view)); it < end; ++it) \
        utry_write(*it);

#define UWRITE_ANY_INT_X(val, s, fmt, write, write_arg, X)                                                \
    assert(ufmt##X##_int_output_valid(fmt) && write);                                                     \
                                                                                                          \
    size_t written = 0;                                                                                   \
                                                                                                          \
    /* Check sign and make absolute */                                                                    \
                                                                                                          \
    bool neg = s && (intmax_t) val < 0;                                                                   \
                                                                                                          \
    if (neg)                                                                                              \
        val = -val;                                                                                       \
                                                                                                          \
    /* Fill digit buffer */                                                                               \
                                                                                                          \
    uc8_t    digits[UMAX_DIGITS];                                                                         \
    unsigned digit_count = ufill_digits_buffer(digits, val, fmt->digit_case, fmt->radix, fmt->precision); \
                                                                                                          \
    /* Write sign */                                                                                      \
                                                                                                          \
    if (neg)                                                                                              \
        utry_write('-');                                                                                  \
     else                                                                                                 \
        switch (fmt->plus) {                                                                              \
            case UPLUS_SPACE:                                                                             \
                utry_write(' ');                                                                          \
                break;                                                                                    \
                                                                                                          \
            case UPLUS_SIGN:                                                                              \
                utry_write('+');                                                                          \
        }                                                                                                 \
                                                                                                          \
    /* Write radix prefix */                                                                              \
                                                                                                          \
    if (fmt->show_radix_prefix && uradix_has_prefix(fmt->radix))                                          \
        utry_write_ucvx(uradix_prefix_##X(fmt->radix, fmt->radix_prefix_case), X);                        \
                                                                                                          \
    /* Write leading zeroes */                                                                            \
                                                                                                          \
    bool     need_leading_zeroes = fmt->min_digits > digit_count;                                         \
    unsigned digits_left         = need_leading_zeroes ? fmt->min_digits : digit_count;                   \
                                                                                                          \
    if (need_leading_zeroes) {                                                                            \
        unsigned zero_count = fmt->min_digits - digit_count;                                              \
                                                                                                          \
        while (zero_count--) {                                                                            \
            utry_write('0');                                                                              \
                                                                                                          \
            --digits_left;                                                                                \
                                                                                                          \
            if (0 == digits_left % fmt->group_size)                                                       \
                utry_write_ucvx(fmt->group_sep, X);                                                       \
        }                                                                                                 \
    }                                                                                                     \
                                                                                                          \
    /* Write digits */                                                                                    \
                                                                                                          \
    while (digits_left--) {                                                                               \
        utry_write(digits[digits_left]);                                                                  \
                                                                                                          \
        if (digits_left && 0 == digits_left % fmt->group_size)                                            \
            utry_write_ucvx(fmt->group_sep, X);                                                           \
    }                                                                                                     \
                                                                                                          \
    return written

static size_t ufmt_any_int_32(uintmax_t val, bool s, const struct ufmt32_int_output *fmt, uwrite_uc32_t write, void *write_arg) {
    UWRITE_ANY_INT_X(val, s, fmt, write, write_arg, 32);
}

size_t uwrite_int_32(intmax_t val, const struct ufmt32_int_output *fmt, uwrite_uc32_t write, void *write_arg) {
    return ufmt_any_int_32(val, true, fmt, write, write_arg);
}

size_t uwrite_uint_32(uintmax_t val, const struct ufmt32_int_output *fmt, uwrite_uc32_t write, void *write_arg) {
    return ufmt_any_int_32(val, false, fmt, write, write_arg);
}

static size_t ufmt_any_int_16(uintmax_t val, bool s, const struct ufmt16_int_output *fmt, uwrite_uc16_t write, void *write_arg) {
    UWRITE_ANY_INT_X(val, s, fmt, write, write_arg, 16);
}

size_t uwrite_int_16(intmax_t val, const struct ufmt16_int_output *fmt, uwrite_uc16_t write, void *write_arg) {
    return ufmt_any_int_16(val, true, fmt, write, write_arg);
}

size_t uwrite_uint_16(uintmax_t val, const struct ufmt16_int_output *fmt, uwrite_uc16_t write, void *write_arg) {
    return ufmt_any_int_16(val, false, fmt, write, write_arg);
}

static size_t ufmt_any_int_8(uintmax_t val, bool s, const struct ufmt8_int_output *fmt, uwrite_uc8_t write, void *write_arg) {
    UWRITE_ANY_INT_X(val, s, fmt, write, write_arg, 8);
}

size_t uwrite_int_8(intmax_t val, const struct ufmt8_int_output *fmt, uwrite_uc8_t write, void *write_arg) {
    return ufmt_any_int_8(val, true, fmt, write, write_arg);
}

size_t uwrite_uint_8(uintmax_t val, const struct ufmt8_int_output *fmt, uwrite_uc8_t write, void *write_arg) {
    return ufmt_any_int_8(val, false, fmt, write, write_arg);
}

#define UFMTX_OUTPUT_INT_VALID(fmt, X)                                                                          \
    if (!fmt)                                                                                                   \
        return false;                                                                                           \
                                                                                                                \
    if (fmt->group_size && !ucv##X##_valid(fmt->group_sep))                                                     \
        return false;                                                                                           \
                                                                                                                \
    if (fmt->show_radix_prefix && uradix_has_prefix(fmt->radix) && !ucase_valid_output(fmt->radix_prefix_case)) \
        return false;                                                                                           \
                                                                                                                \
    if (fmt->radix > 10 && !ucase_valid_output(fmt->digit_case))                                                \
        return false;                                                                                           \
                                                                                                                \
    return uplus_valid(fmt->plus)

bool ufmt32_int_output_valid(const struct ufmt32_int_output *fmt) {
    UFMTX_OUTPUT_INT_VALID(fmt, 32);
}

bool ufmt16_int_output_valid(const struct ufmt16_int_output *fmt) {
    UFMTX_OUTPUT_INT_VALID(fmt, 16);
}

bool ufmt8_int_output_valid(const struct ufmt8_int_output *fmt) {
    UFMTX_OUTPUT_INT_VALID(fmt, 8);
}