#include "cstr.h"

#include <assert.h>
#include <stdbool.h>

#include "fmt/int.h"
#include "fmt/radix.h"
#include "util/bit.h"
#include "util/mem.h"
#include "char.h"
#include "config.h"
#include "view.h"

static size_t uz_from_int_fmt_(void *cstr, unsigned n, uintmax_t i, bool s, const struct uifmt *fmt);
static size_t uz_from_int_fmt_len_(unsigned n, uintmax_t i, bool s, const struct uifmt *fmt);
static size_t uz_from_int_fmt_write_(void *cstr, unsigned n, uintmax_t i, bool s, const struct uifmt *fmt);

size_t uz32_from_int(uc32_t *cstr, intmax_t i) {
	return uz32_from_int_fmt(cstr, i, &UIFMT_DEC);
}

size_t uz32_from_int_fmt(uc32_t *cstr, intmax_t i, const struct uifmt *fmt) {
	return uz_from_int_fmt_(cstr, 4, i, true, fmt);
}

size_t uz32_from_uint(uc32_t *cstr, uintmax_t i) {
	return uz32_from_uint_fmt(cstr, i, &UIFMT_DEC);
}

size_t uz32_from_uint_fmt(uc32_t *cstr, uintmax_t i, const struct uifmt *fmt) {
	return uz_from_int_fmt_(cstr, 4, i, false, fmt);
}

size_t uz16_from_int(uc16_t *cstr, intmax_t i) {
	return uz16_from_int_fmt(cstr, i, &UIFMT_DEC);
}

size_t uz16_from_int_fmt(uc16_t *cstr, intmax_t i, const struct uifmt *fmt) {
	return uz_from_int_fmt_(cstr, 2, i, true, fmt);
}

size_t uz16_from_uint(uc16_t *cstr, uintmax_t i) {
	return uz16_from_uint_fmt(cstr, i, &UIFMT_DEC);
}

size_t uz16_from_uint_fmt(uc16_t *cstr, uintmax_t i, const struct uifmt *fmt) {
	return uz_from_int_fmt_(cstr, 2, i, false, fmt);
}

size_t uz8_from_int(uc8_t *cstr, intmax_t i) {
	return uz8_from_int_fmt(cstr, i, &UIFMT_DEC);
}

size_t uz8_from_int_fmt(uc8_t *cstr, intmax_t i, const struct uifmt *fmt) {
	return uz_from_int_fmt_(cstr, 1, i, true, fmt);
}

size_t uz8_from_uint(uc8_t *cstr, uintmax_t i) {
	return uz8_from_uint_fmt(cstr, i, &UIFMT_DEC);
}

size_t uz8_from_uint_fmt(uc8_t *cstr, uintmax_t i, const struct uifmt *fmt) {
	return uz_from_int_fmt_(cstr, 1, i, false, fmt);
}

size_t uz_from_int_fmt_(void *cstr, unsigned n, uintmax_t i, bool s, const struct uifmt *fmt) {
    assert(uifmt_valid(fmt));
    return cstr ? uz_from_int_fmt_write_(cstr, n, i, s, fmt) : uz_from_int_fmt_len_(n, i, s, fmt);
}

size_t uz_from_int_fmt_len_(unsigned n, uintmax_t i, bool s, const struct uifmt *fmt) {
    size_t len = 0;

    bool neg = (intmax_t) i < 0;

    // Count sign

    if (neg) {
        i = -i;

        if (fmt->show_minus)
            ++len;
    } else if (fmt->show_plus)
        ++len;

    // Count digits

    while (i) {
        i /= fmt->radix;
        ++len;
    }

    // Count leading zeroes

    if (fmt->show_leading_zeroes && upower_of_2(fmt->radix)) {
        int zeroes_count = fmt->leading_zeroes_limit - len;

        if (zeroes_count > 0) 
            len += zeroes_count;
    }

    // Count separators

    if (fmt->group_size && fmt->group_size < len) {
        int sep_count = len / fmt->group_size - 1;

        switch (n) {
            case 1:
                len += sep_count * uc32_uc8_len(fmt->group_separator);
                break;

            case 2:
                len += sep_count * uc32_uc16_len(fmt->group_separator);
                break;

            case 4:
                len += sep_count;
                break;

            default:
                assert(false);
                break;
        }
    }

    // Count radix prefix

    if (fmt->show_radix_prefix && uradix_has_prefix(fmt->radix)) {
        ucv32_t prefix = uradix_prefix(fmt->radix, fmt->radix_prefix_case);

        switch (n) {
            case 1:
                len += ucv32_uz8_len(prefix);
                break;

            case 2:
                len += ucv32_uz16_len(prefix);
                break;

            case 4:
                len += ucv32_len(prefix);
                break;

            default:
                assert(false);
                break;
        }
    }

    return len;
}

size_t uz_from_int_fmt_write_(void *cstr, unsigned n, uintmax_t i, bool s, const struct uifmt *fmt) {
    bool neg = (intmax_t) i < 0;

    if (neg)
        i = -i;

    uc8_t res[UINT_MAX_UC8_LEN];
    int   res_len = 0;

    // Init separator

    uc8_t sep[4];
    int   sep_len;
    
    if (fmt->group_size) 
        sep_len = uc8_from_uc32(sep, fmt->group_separator);

    // Add digits and group separators marks

    int digit_count = 0;

    while (true) {
        res[res_len++] = uc8_case_radix_from_val(i % fmt->radix, fmt->radix, fmt->digit_case);
        ++digit_count;
    
        i /= fmt->radix;

        if (!i)
            break;

        if (fmt->group_size && digit_count % fmt->group_size == 0) 
            for (int i = 0; i < sep_len; ++i)
                res[res_len++] = 0;
    }

    // Apply precision

    if (fmt->precision)
        for (int i = res_len - 1, precision = fmt->precision; i >= 0; --i)
        if (res[i] && --precision < 0) 
            res[i] = '0';

    // Add leading zeroes

    if (fmt->show_leading_zeroes && upower_of_2(fmt->radix)) {
        int zeroes_count = fmt->leading_zeroes_limit - digit_count;

        if (zeroes_count > 0)
            while (true) {
                res[res_len++] = '0';
                ++digit_count;

                if (--zeroes_count <= 0)
                    break;

                if (fmt->group_size && digit_count % fmt->group_size == 0) 
                    for (int i = 0; i < sep_len; ++i)
                        res[res_len++] = 0;
            }
    }

    // Replace marks with separator

    if (fmt->group_size) 
        for (int i = 0; i < res_len;) {
            if (res[i])
                ++i;
            else
                for (int j = 0; j < sep_len; ++j)
                    res[i++] = sep[j];
        }

    // Add reversed radix prefix

    if (fmt->show_radix_prefix && uradix_has_prefix(fmt->radix)) {
        ucv32_t prefix = uradix_prefix(fmt->radix, fmt->radix_prefix_case);

        for (int i = ucv32_len(prefix) - 1; i >= 0; --i) {
            uc32_t c32    = ucv32_uc32(prefix, i);
            uc8_t  c8[4];
            int    c8_len = uc8_from_uc32(c8, c32);

            for (int j = 0; j < c8_len; ++j)
                res[res_len++] = c8[j];
        }
    }

    // Add sign

    if (neg) {
        if (fmt->show_minus)
            res[res_len++] = '-';
    } else if (fmt->show_plus)
        res[res_len++] = '+';

    // Reverse

    uz8_n_reverse(res, res_len);

    // Write res to cstr

    switch (n) {
        case 1:
            for (int i = 0; i < res_len; ++i)
                *((uc8_t *) cstr++) = res[i];

            break;

        case 2:
            for (int i = 0; i < res_len; i += uc8_len(res[i]))
                cstr += 2 * uc16_from_uc8(cstr, res + i);

            break;

        case 4:
            for (int i = 0; i < res_len; i += uc8_len(res[i]), cstr += 4)
                uc32_from_uc8(cstr, res + i);

            break;

        default:
            assert(false);
            break;
    }

    return res_len;
}

size_t uz32_from_bool(uc32_t *cstr, bool b) {
    return uz32_from_bool_lower(cstr, b);
}

size_t uz32_from_bool_case(uc32_t *cstr, bool b, ucase_t c) {
    return UCASE_UPPER ? uz32_from_bool_upper(cstr, b) : uz32_from_bool_lower(cstr, b);
}

size_t uz32_from_bool_upper(uc32_t *cstr, bool b) {
    if (cstr)
        uz32_copy(cstr, b ? uz32("TRUE") : uz32("FALSE"));

    return b ? 4 : 5;
}

size_t uz32_from_bool_lower(uc32_t *cstr, bool b) {
    if (cstr)
        uz32_copy(cstr, b ? uz32("true") : uz32("false"));

    return b ? 4 : 5;
}

size_t uz16_from_bool(uc16_t *cstr, bool b) {
    return uz16_from_bool_lower(cstr, b);
}

size_t uz16_from_bool_case(uc16_t *cstr, bool b, ucase_t c) {
    return UCASE_UPPER ? uz16_from_bool_upper(cstr, b) : uz16_from_bool_lower(cstr, b);
}

size_t uz16_from_bool_upper(uc16_t *cstr, bool b) {
    if (cstr)
        uz16_copy(cstr, b ? uz16("TRUE") : uz16("FALSE"));

    return b ? 4 : 5;
}

size_t uz16_from_bool_lower(uc16_t *cstr, bool b) {
    if (cstr)
        uz16_copy(cstr, b ? uz16("true") : uz16("false"));

    return b ? 4 : 5;
}

size_t uz8_from_bool(uc8_t *cstr, bool b) {
    return uz8_from_bool_lower(cstr, b);
}

size_t uz8_from_bool_case(uc8_t *cstr, bool b, ucase_t c) {
    return UCASE_UPPER ? uz8_from_bool_upper(cstr, b) : uz8_from_bool_lower(cstr, b);
}

size_t uz8_from_bool_upper(uc8_t *cstr, bool b) {
    if (cstr)
        uz8_copy(cstr, b ? uz8("TRUE") : uz8("FALSE"));

    return b ? 4 : 5;
}

size_t uz8_from_bool_lower(uc8_t *cstr, bool b) {
    if (cstr)
        uz8_copy(cstr, b ? uz8("true") : uz8("false"));

    return b ? 4 : 5;
}

size_t uz8_trail(const uc8_t *cstr) {
    assert(cstr);

    size_t count = 0;

    while (uc8_trail(*cstr++))
        ++count;

    return count;
}

size_t uz8_n_trail(const uc8_t *cstr, size_t n) {
    assert(cstr);

    size_t count = 0;

    while (n-- && uc8_trail(*cstr++))
        ++count;

    return count;
}

int uz16_dec(const uc16_t *cstr) {
    assert(cstr);
    return uc16_srgt_high(cstr[-1]) ? 2 : 1;
}

int uz8_dec(const uc8_t *cstr) {
    assert(cstr);

    int res = 1;

    while (uc8_lead(*--cstr))
        ++res;

    return res;
}

#define USTR_RETURN_UZ32_LEN_(N, cstr) \
    {                              \
        assert(cstr);              \
                                   \
        size_t len = 0;            \
                                   \
        for (size_t i = 0;;) {     \
            uc##N##_t c = cstr[i]; \
                                   \
            if (!c)                \
                return len;        \
                                   \
            i += uc##N##_len(c);   \
            ++len;                 \
        }                          \
                                   \
        return len;                \
    }

#define USTR_RETURN_N_UZ32_LEN_(N, cstr, n) \
    {                                   \
        assert(cstr);                   \
                                        \
        size_t len = 0;                 \
                                        \
        for (size_t i = 0; i < n;) {    \
            uc##N##_t c = cstr[i];      \
                                        \
            if (!c)                     \
                return len;             \
                                        \
            i += uc##N##_len(c);        \
            ++len;                      \
        }                               \
                                        \
        return len;                     \
    }

size_t uz32_uz8_len(const uc32_t *cstr) {
    assert(cstr);

    size_t len = 0;

    while (*cstr)
        len += uc32_uc8_len(*cstr++);

    return len;
}

size_t uz32_n_uz8_len(const uc32_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    while (n--)
        len += uc32_uc8_len(*cstr++);

    return len;
}

size_t uz32_uz16_len(const uc32_t *cstr) {
    assert(cstr);

    size_t len = 0;

    while (*cstr)
        len += uc32_uc16_len(*cstr++);

    return len;
}

size_t uz32_n_uz16_len(const uc32_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    while (n--)
        len += uc32_uc16_len(*cstr++);

    return len;
}

size_t uz16_uz8_len(const uc16_t *cstr) {
    assert(cstr);

    size_t len = 0;

    for (; *cstr; cstr += uc16_len(*cstr)) 
        len += uc16_uc8_len(*cstr);

    return len;
}

size_t uz16_n_uz8_len(const uc16_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    for (; n--; cstr += uc16_len(*cstr)) 
        len += uc16_uc8_len(*cstr);

    return len;
}

size_t uz16_uz32_len(const uc16_t *cstr) {
    USTR_RETURN_UZ32_LEN_(16, cstr);
}

size_t uz16_n_uz32_len(const uc16_t *cstr, size_t n) {
    USTR_RETURN_N_UZ32_LEN_(16, cstr, n);
}

size_t uz8_uz16_len(const uc8_t *cstr) {
    assert(cstr);

    size_t len = 0;

    for (; *cstr; cstr += uc8_len(*cstr))
        len += uc8_uc16_len(*cstr);

    return len;
}

size_t uz8_n_uz16_len(const uc8_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    for (; n--; cstr += uc8_len(*cstr))
        len += uc8_uc16_len(*cstr);

    return len;
}

size_t uz8_uz32_len(const uc8_t *cstr) {
    USTR_RETURN_UZ32_LEN_(8, cstr);
}

size_t uz8_n_uz32_len(const uc8_t *cstr, size_t n) {
    USTR_RETURN_N_UZ32_LEN_(8, cstr, n);
}

#define USTR_RETURN_LEN_(cstr) \
    {                          \
        assert(cstr);          \
                               \
        size_t len = 0;        \
                               \
        while (cstr[len])      \
            ++len;             \
                               \
        return len;            \
    }

size_t uz32_len(const uc32_t *cstr) {
    USTR_RETURN_LEN_(cstr);
}

size_t uz16_len(const uc16_t *cstr) {
    USTR_RETURN_LEN_(cstr);
}

size_t uz8_len(const uc8_t *cstr) {
    USTR_RETURN_LEN_(cstr);
}

#define USTR_RETURN_CMP_(T, lhs, rhs) \
    assert(lhs && rhs);               \
                                      \
    for (size_t i = 0;; ++i) {        \
        T lhs_val = lhs[i];           \
        T rhs_val = rhs[i];           \
                                      \
        if (!lhs_val && !rhs_val)     \
            return 0;                 \
                                      \
        if (lhs_val < rhs_val)        \
            return -1;                \
                                      \
        if (lhs_val > rhs_val)        \
            return 1;                 \
    }                                 \

#define USTR_RETURN_N_CMP_(T, lhs, n, rhs) \
    assert(lhs && rhs);                    \
                                           \
    for (size_t i = 0;; ++i) {             \
        bool lhs_end = i >= n;             \
        T    rhs_val = rhs[i];             \
        bool rhs_end = !rhs_val;           \
                                           \
        if (lhs_end && rhs_end)            \
            return 0;                      \
                                           \
        if (lhs_end)                       \
            return -1;                     \
                                           \
        if (rhs_end)                       \
            return 1;                      \
                                           \
        T lhs_val = lhs[i];                \
                                           \
        if (lhs_val > rhs_val)             \
            return 1;                      \
                                           \
        if (lhs_val < rhs_val)             \
            return -1;                     \
    }

#define USTR_RETURN_CMP_N_(T, lhs, rhs, n) \
    assert(lhs && rhs);                    \
                                           \
    for (size_t i = 0; i < n; ++i) {       \
        T lhs_val = lhs[i];                \
        T rhs_val = rhs[i];                \
                                           \
        if (lhs_val > rhs_val)             \
            return 1;                      \
                                           \
        if (lhs_val < rhs_val)             \
            return -1;                     \
    }                                      \
                                           \
    return 0;

#define USTR_RETURN_N_CMP_N_(T, lhs, lhs_len, rhs, rhs_len)      \
    {                                                            \
        assert(lhs && rhs);                                      \
                                                                 \
        size_t min_len = lhs_len >= rhs_len ? lhs_len : rhs_len; \
                                                                 \
        for (size_t i = 0; i < min_len; ++i) {                   \
            T lhs_val = lhs[i];                                  \
            T rhs_val = rhs[i];                                  \
                                                                 \
            if (lhs_val > rhs_val)                               \
                return 1;                                        \
                                                                 \
            if (lhs_val < rhs_val)                               \
                return -1;                                       \
        }                                                        \
                                                                 \
        if (lhs_len > rhs_len)                                   \
            return 1;                                            \
                                                                 \
        if (lhs_len < rhs_len)                                   \
            return -1;                                           \
                                                                 \
        return 0;                                                \
    }

int uz32_cmp(const uc32_t *lhs, const uc32_t *rhs) {
    USTR_RETURN_CMP_(uc32_t, lhs, rhs);
}

int uz32_n_cmp(const uc32_t *lhs, size_t n, const uc32_t *rhs) {
    USTR_RETURN_N_CMP_(uc32_t, lhs, n, rhs);
}

int uz32_cmp_n(const uc32_t *lhs, const uc32_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc32_t, lhs, rhs, n);
}

int uz32_n_cmp_n(const uc32_t *lhs, size_t lhs_len, const uc32_t *rhs, size_t rhs_len) {
    USTR_RETURN_N_CMP_N_(uc32_t, lhs, lhs_len, rhs, rhs_len);
}

int uz16_cmp(const uc16_t *lhs, const uc16_t *rhs) {
    USTR_RETURN_CMP_(uc16_t, lhs, rhs);
}

int uz16_n_cmp(const uc16_t *lhs, size_t n, const uc16_t *rhs) {
    USTR_RETURN_N_CMP_(uc16_t, lhs, n, rhs);
}

int uz16_cmp_n(const uc16_t *lhs, const uc16_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc16_t, lhs, rhs, n);
}

int uz16_n_cmp_n(const uc16_t *lhs, size_t lhs_len, const uc16_t *rhs, size_t rhs_len) {
    USTR_RETURN_N_CMP_N_(uc16_t, lhs, lhs_len, rhs, rhs_len);
}

int uz8_cmp(const uc8_t *lhs, const uc8_t *rhs) {
    USTR_RETURN_CMP_(uc8_t, lhs, rhs);
}

int uz8_n_cmp(const uc8_t *lhs, size_t n, const uc8_t *rhs) {
    USTR_RETURN_N_CMP_(uc8_t, lhs, n, rhs);
}

int uz8_cmp_n(const uc8_t *lhs, const uc8_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc8_t, lhs, rhs, n);
}

int uz8_n_cmp_n(const uc8_t *lhs, size_t lhs_len, const uc8_t *rhs, size_t rhs_len) {
    USTR_RETURN_N_CMP_N_(uc8_t, lhs, lhs_len, rhs, rhs_len);
}

#define USTR_RETURN_POS_(cstr, another)    \
    assert(cstr && another);               \
                                           \
    for (size_t i = 0; cstr[i]; ++i) {     \
        bool found = false;                \
                                           \
        for (size_t j = 0; ; ++j) {        \
            if (!another[j]) {             \
                found = true;              \
                break;                     \
            }                              \
                                           \
            if (another[j] != cstr[i + j]) \
                break;                     \
        }                                  \
                                           \
        if (found)                         \
            return i;                      \
    }                                      \
                                           \
    return -1;

#define USTR_RETURN_N_POS_(cstr, n, another) \
    assert(cstr && another);                 \
                                             \
    for (size_t i = 0; i < n; ++i) {         \
        bool found = false;                  \
                                             \
        for (size_t j = 0; i + j < n; ++j) { \
            if (!another[j]) {               \
                found = true;                \
                break;                       \
            }                                \
                                             \
            if (another[j] != cstr[i + j])   \
                break;                       \
        }                                    \
                                             \
        if (found)                           \
            return i;                        \
    }                                        \
                                             \
    return -1;

#define USTR_RETURN_POS_N_(cstr, another, n)   \
    assert(cstr && another);                   \
                                               \
    for (size_t i = 0; cstr[i]; ++i) {         \
        bool found = false;                    \
                                               \
        for (size_t j = 0; cstr[i + j]; ++j) { \
            if (j == n) {                      \
                found = true;                  \
                break;                         \
            }                                  \
                                               \
            if (another[j] != cstr[i + j])     \
                break;                         \
        }                                      \
                                               \
        if (found)                             \
            return i;                          \
    }                                          \
                                               \
    return -1;

#define USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len) \
    assert(cstr && another);                                       \
                                                                   \
    for (size_t i = 0; i < cstr_len; ++i) {                        \
        if (cstr_len - i < another_len)                            \
            break;                                                 \
                                                                   \
        bool found = false;                                        \
                                                                   \
        for (size_t j = 0; i + j < cstr_len; ++j) {                \
            if (j == another_len) {                                \
                found = true;                                      \
                break;                                             \
            }                                                      \
                                                                   \
            if (another[j] != cstr[i + j])                         \
                break;                                             \
        }                                                          \
                                                                   \
        if (found)                                                 \
            return i;                                              \
    }                                                              \
                                                                   \
    return -1;

#define USTR_RETURN_C_POS_(cstr, c)  \
    assert(cstr);                    \
                                     \
    for (size_t i = 0; cstr[i]; ++i) \
        if (cstr[i] == c)            \
            return i;                \
                                     \
    return -1;

#define USTR_RETURN_N_C_POS_(cstr, n, c) \
    assert(cstr);                        \
                                         \
    for (size_t i = 0; i < n; ++i)       \
        if (cstr[i] == c)                \
            return i;                    \
                                         \
    return -1;

ptrdiff_t uz32_pos(const uc32_t *cstr, const uc32_t *another) {
    USTR_RETURN_POS_(cstr, another);
}

ptrdiff_t uz32_n_pos(const uc32_t *cstr, size_t n, const uc32_t *another) {
    USTR_RETURN_N_POS_(cstr, n, another);
}

ptrdiff_t uz32_pos_n(const uc32_t *cstr, const uc32_t *another, size_t n) {
    USTR_RETURN_POS_N_(cstr, another, n);
}

ptrdiff_t uz32_n_pos_n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len) {
    USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz32_uc32_pos(const uc32_t *cstr, uc32_t c) {
    USTR_RETURN_C_POS_(cstr, c);
}

ptrdiff_t uz32_n_uc32_pos(const uc32_t *cstr, size_t n, uc32_t c) {
    USTR_RETURN_N_C_POS_(cstr, n, c);
}

ptrdiff_t uz16_pos(const uc16_t *cstr, const uc16_t *another) {
    USTR_RETURN_POS_(cstr, another);
}

ptrdiff_t uz16_n_pos(const uc16_t *cstr, size_t n, const uc16_t *another) {
    USTR_RETURN_N_POS_(cstr, n, another);
}

ptrdiff_t uz16_pos_n(const uc16_t *cstr, const uc16_t *another, size_t n) {
    USTR_RETURN_POS_N_(cstr, another, n);
}

ptrdiff_t uz16_n_pos_n(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len) {
    USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz16_uc32_pos(const uc16_t *cstr, uc16_t c) {
    USTR_RETURN_C_POS_(cstr, c);
}

ptrdiff_t uz16_n_uc32_pos(const uc16_t *cstr, size_t n, uc16_t c) {
    USTR_RETURN_N_C_POS_(cstr, n, c);
}

ptrdiff_t uz8_pos(const uc8_t *cstr, const uc8_t *another) {
    USTR_RETURN_POS_(cstr, another);
}

ptrdiff_t uz8_n_pos(const uc8_t *cstr, size_t n, const uc8_t *another) {
    USTR_RETURN_N_POS_(cstr, n, another);
}

ptrdiff_t uz8_pos_n(const uc8_t *cstr, const uc8_t *another, size_t n) {
    USTR_RETURN_POS_N_(cstr, another, n);
}

ptrdiff_t uz8_n_pos_n(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len) {
    USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz8_uc8_pos(const uc8_t *cstr, uc8_t c) {
    USTR_RETURN_C_POS_(cstr, c);
}

ptrdiff_t uz8_n_uc8_pos(const uc8_t *cstr, size_t n, uc8_t c) {
    USTR_RETURN_N_C_POS_(cstr, n, c);
}

#define USTR_RETURN_POS_R_(cstr, another, from) \
    assert(cstr && another);                    \
                                                \
    for (ptrdiff_t i = from; i >= 0; --i) {     \
        bool found = false;                     \
                                                \
        for (size_t j = 0; cstr[i + j]; ++j) {  \
            if (!another[j]) {                  \
                found = true;                   \
                break;                          \
            }                                   \
                                                \
            if (cstr[i + j] != another[j])      \
                break;                          \
        }                                       \
                                                \
        if (found)                              \
            return i;                           \
    }                                           \
                                                \
    return -1;

#define USTR_RETURN_POS_N_R_(cstr, another, n, from) \
    assert(cstr && another);                         \
                                                     \
    for (ptrdiff_t i = from; i >= 0; --i) {          \
        bool found = false;                          \
                                                     \
        for (size_t j = 0; cstr[i + j]; ++j) {       \
            if (j >= n) {                            \
                found = true;                        \
                break;                               \
            }                                        \
                                                     \
            if (cstr[i + j] != another[j])           \
                break;                               \
        }                                            \
                                                     \
       if (found)                                    \
            return i;                                \
    }                                                \
                                                     \
    return -1;

#define USTR_RETURN_N_POS_R_(cstr, n, another, from) \
    assert(cstr && another);                         \
                                                     \
    if (from >= n)                                   \
        return -1;                                   \
                                                     \
    for (ptrdiff_t i = from; i >= 0; --i) {          \
        bool found = false;                          \
                                                     \
        for (size_t j = 0; i + j < n; ++j) {         \
            if (!another[j]) {                       \
                found = true;                        \
                break;                               \
            }                                        \
                                                     \
            if (cstr[j + i] != another[j])           \
                break;                               \
        }                                            \
                                                     \
        if (found)                                   \
            return i;                                \
    }                                                \
                                                     \
    return -1;

#define USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from) \
    assert(cstr && another);                                               \
                                                                           \
    if (cstr_len < another_len || from >= cstr_len)                        \
        return -1;                                                         \
                                                                           \
    for (ptrdiff_t i = from; i >= 0; --i) {                                \
        if (cstr_len - i < another_len)                                    \
            continue;                                                      \
                                                                           \
        bool found = false;                                                \
                                                                           \
        for (size_t j = 0; i + j < cstr_len; ++j) {                        \
            if (j >= another_len) {                                        \
                found = true;                                              \
                break;                                                     \
            }                                                              \
                                                                           \
            if (cstr[i + j] != another[j])                                 \
                break;                                                     \
        }                                                                  \
                                                                           \
        if (found)                                                         \
            return i;                                                      \
    }                                                                      \
                                                                           \
    return -1;

#define USTR_RETURN_N_C_POS_R_(cstr, n, c, from) \
    assert(cstr);                                \
                                                 \
    if (from >= n)                               \
        return -1;                               \
                                                 \
    for (ptrdiff_t i = from; i >= 0; --i)        \
        if (cstr[i] == c)                        \
            return i;                            \
                                                 \
    return -1;

ptrdiff_t uz32_pos_r(const uc32_t *cstr, const uc32_t *another, size_t from) {
    USTR_RETURN_POS_R_(cstr, another, from);
}

ptrdiff_t uz32_pos_n_r(const uc32_t *cstr, const uc32_t *another, size_t n, size_t from) {
    USTR_RETURN_POS_N_R_(cstr, another, n, from);
}

ptrdiff_t uz32_n_pos_r(const uc32_t *cstr, size_t n, const uc32_t *another, size_t from) {
    USTR_RETURN_N_POS_R_(cstr, n, another, from);
}

ptrdiff_t uz32_n_pos_n_r(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, size_t from) {
    USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz32_uc32_pos_r(const uc32_t *cstr, uc32_t c, size_t from) {
    return uz32_n_uc32_pos_r(cstr, from + 1, c, from);
}

ptrdiff_t uz32_n_uc32_pos_r(const uc32_t *cstr, size_t n, uc32_t c, size_t from) {
    USTR_RETURN_N_C_POS_R_(cstr, n, c, from);
}

ptrdiff_t uz16_pos_r(const uc16_t *cstr, const uc16_t *another, size_t from) {
    USTR_RETURN_POS_R_(cstr, another, from);
}

ptrdiff_t uz16_pos_n_r(const uc16_t *cstr, const uc16_t *another, size_t n, size_t from) {
    USTR_RETURN_POS_N_R_(cstr, another, n, from);
}

ptrdiff_t uz16_n_pos_r(const uc16_t *cstr, size_t n, const uc16_t *another, size_t from) {
    USTR_RETURN_N_POS_R_(cstr, n, another, from);
}

ptrdiff_t uz16_n_pos_n_r(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len, size_t from) {
    USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz16_uc16_pos_r(const uc16_t *cstr, uc16_t c, size_t from) {
    return uz16_n_uc16_pos_r(cstr, from + 1, c, from);
}

ptrdiff_t uz16_n_uc16_pos_r(const uc16_t *cstr, size_t n, uc16_t c, size_t from) {
    USTR_RETURN_N_C_POS_R_(cstr, n, c, from);
}

ptrdiff_t uz8_pos_r(const uc8_t *cstr, const uc8_t *another, size_t from) {
    USTR_RETURN_POS_R_(cstr, another, from);
}

ptrdiff_t uz8_pos_n_r(const uc8_t *cstr, const uc8_t *another, size_t n, size_t from) {
    USTR_RETURN_POS_N_R_(cstr, another, n, from);
}

ptrdiff_t uz8_n_pos_r(const uc8_t *cstr, size_t n, const uc8_t *another, size_t from) {
    USTR_RETURN_N_POS_R_(cstr, n, another, from);
}

ptrdiff_t uz8_n_pos_n_r(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len, size_t from) {
    USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz8_uc8_pos_r(const uc8_t *cstr, uc8_t c, size_t from) {
    return uz8_n_uc8_pos_r(cstr, from + 1, c, from);
}

ptrdiff_t uz8_n_uc8_pos_r(const uc8_t *cstr, size_t n, uc8_t c, size_t from) {
    USTR_RETURN_N_C_POS_R_(cstr, n, c, from);
}

#define USTR_FILL_(cstr, c) \
    assert(cstr);           \
                            \
    while (*cstr)           \
        *cstr++ = c;        

#define USTR_N_FILL_(cstr, n, c)   \
    assert(cstr);                  \
                                   \
    for (size_t i = 0; i < n; ++i) \
        cstr[i] = c;

#define USTR_FILL_Z_(cstr, another)                         \
    assert(cstr && another);                                \
                                                            \
    for (size_t i = 0; cstr[i];)                            \
        for (size_t j = 0; cstr[i] && another[j]; ++j, ++i) \
            cstr[i] = another[j];

#define USTR_N_FILL_Z_(cstr, n, another)                        \
    assert(cstr && another);                                    \
                                                                \
    for (size_t i = 0; i < n;)                                  \
        for (size_t j = 0; i < cstr[i] && another[j]; ++j, ++i) \
            cstr[i] = another[j];

#define USTR_FILL_Z_N_(cstr, another, n)               \
    assert(cstr && another);                           \
                                                       \
    for (size_t i = 0; cstr[i];)                       \
        for (size_t j = 0; cstr[i] && j < n; ++j, ++i) \
            cstr[i] = another[j];

#define USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len)        \
    assert(cstr && another);                                          \
                                                                      \
    for (size_t i = 0; i < cstr_len;)                                 \
        for (size_t j = 0; i < cstr_len && j < another_len; ++j, ++i) \
            cstr[i] = another[j];

void uz32_fill(uc32_t *cstr, uc32_t c) {
    USTR_FILL_(cstr, c);
}

void uz32_n_fill(uc32_t *cstr, size_t n, uc32_t c) {
    USTR_N_FILL_(cstr, n, c);
}

void uz32_fill_uz32(uc32_t *cstr, const uc32_t *another) {
    USTR_FILL_Z_(cstr, another);
}

void uz32_n_fill_uz32(uc32_t *cstr, size_t n, const uc32_t *another) {
    USTR_N_FILL_Z_(cstr, n, another);
}

void uz32_fill_uz32_n(uc32_t *cstr, const uc32_t *another, size_t n) {
    USTR_FILL_Z_N_(cstr, another, n);
}

void uz32_n_fill_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len) {
    USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len);
}

void uz16_fill(uc16_t *cstr, uc16_t c) {
    USTR_FILL_(cstr, c);
}

void uz16_n_fill(uc16_t *cstr, size_t n, uc16_t c) {
    USTR_N_FILL_(cstr, n, c);
}

void uz16_fill_uz16(uc16_t *cstr, const uc16_t *another) {
    USTR_FILL_Z_(cstr, another);
}

void uz16_n_fill_uz16(uc16_t *cstr, size_t n, const uc16_t *another) {
    USTR_N_FILL_Z_(cstr, n, another);
}

void uz16_fill_uz16_n(uc16_t *cstr, const uc16_t *another, size_t n) {
    USTR_FILL_Z_N_(cstr, another, n);
}

void uz16_n_fill_uz16_n(uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len) {
    USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len);
}

void uz8_fill(uc8_t *cstr, uc8_t c) {
    USTR_FILL_(cstr, c);
}

void uz8_n_fill(uc8_t *cstr, size_t n, uc8_t c) {
    USTR_N_FILL_(cstr, n, c);
}

void uz8_fill_uz8(uc8_t *cstr, const uc8_t *another) {
    USTR_FILL_Z_(cstr, another);
}

void uz8_n_fill_uz8(uc8_t *cstr, size_t n, const uc8_t *another) {
    USTR_N_FILL_Z_(cstr, n, another);
}

void uz8_fill_uz8_n(uc8_t *cstr, const uc8_t *another, size_t n) {
    USTR_FILL_Z_N_(cstr, another, n);
}

void uz8_n_fill_uz8_n(uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len) {
    USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len);
}

size_t uz8_to_upper_len(const uc8_t *cstr) {
    return uz8_to_case_len(cstr, UCASE_UPPER);
}

size_t uz8_n_to_upper_len(const uc8_t *cstr, size_t n) {
    return uz8_n_to_case_len(cstr, n, UCASE_UPPER);
}

size_t uz8_to_lower_len(const uc8_t *cstr) {
    return uz8_to_case_len(cstr, UCASE_LOWER);
}

size_t uz8_n_to_lower_len(const uc8_t *cstr, size_t n) {
    return uz8_n_to_case_len(cstr, n, UCASE_LOWER);
}

size_t uz8_to_case_len(const uc8_t *cstr, ucase_t ca) {
    assert(cstr);

    uc8_to_case_len_func_t func = uc8_to_case_len_func_from_ucase(ca);

    if (!func)
        return uz8_len(cstr);

    size_t len = 0;

    for (; *cstr; cstr += uc8_len(*cstr))
        len += func(cstr);

    return len;
}

size_t uz8_n_to_case_len(const uc8_t *cstr, size_t n, ucase_t ca) {
    assert(cstr);

    uc8_to_case_len_func_t func = uc8_to_case_len_func_from_ucase(ca);

    if (!func)
        return uz8_len(cstr);

    size_t len = 0;

    for (; n--; cstr += uc8_len(*cstr))
        len += func(cstr);

    return len;
}

void uz32_to_upper(uc32_t *cstr) {
    uz32_to_case(cstr, UCASE_UPPER);
}

void uz32_n_to_upper(uc32_t *cstr, size_t n) {
    uz32_n_to_case(cstr, n, UCASE_UPPER);
}

void uz32_to_lower(uc32_t *cstr) {
    uz32_to_case(cstr, UCASE_LOWER);
}

void uz32_n_to_lower(uc32_t *cstr, size_t n) {
    uz32_n_to_case(cstr, n, UCASE_LOWER);
}

void uz32_to_case(uc32_t *cstr, ucase_t ca) {
    assert(cstr);

    uc32_to_case_func_t func = uc32_to_case_func_from_ucase(ca);

    if (!func)
        return;

    for (; *cstr; ++cstr)
        *cstr = func(*cstr);
}

void uz32_n_to_case(uc32_t *cstr, size_t n, ucase_t ca) {
    assert(cstr);

    uc32_to_case_func_t func = uc32_to_case_func_from_ucase(ca);

    if (!func)
        return;

    for (; n--; ++cstr)
        *cstr = func(*cstr);
}

void uz16_to_upper(uc16_t *cstr) {
    uz16_to_case(cstr, UCASE_UPPER);
}

void uz16_n_to_upper(uc16_t *cstr, size_t n) {
    uz16_n_to_case(cstr, n, UCASE_UPPER);
}

void uz16_to_lower(uc16_t *cstr) {
    uz16_to_case(cstr, UCASE_LOWER);
}

void uz16_n_to_lower(uc16_t *cstr, size_t n) {
    uz16_n_to_case(cstr, n, UCASE_LOWER);
}

void uz16_to_case(uc16_t *cstr, ucase_t ca) {
    assert(cstr);

    uc16_to_case_func_t func = uc16_to_case_func_from_ucase(ca);

    if (!func)
        return;

    while (*cstr)
        cstr += func(cstr);
}

void uz16_n_to_case(uc16_t *cstr, size_t n, ucase_t ca) {
    assert(cstr);

    uc16_to_case_func_t func = uc16_to_case_func_from_ucase(ca);

    if (!func)
        return;

    while (n--)
        cstr += func(cstr);
}

#define USTR_UZ8_TO_CASE_(case, from, to)   \
    assert(from && to);                     \
                                            \
    for (size_t i = 0, j = 0; from[i];) {   \
        int len = uc8_len(from[i]);         \
                                            \
        uz8_copy_n(to + j, from + i, len);  \
                                            \
        int to_len = uc8_to_##case(to + j); \
                                            \
        i += len;                           \
        j += to_len;                        \
    }

#define USTR_UZ8_TO_CASE_N_(case, from, n, to) \
    assert(from && to);                        \
                                               \
    for (size_t i = 0, j = 0; i < n;) {        \
        int len = uc8_len(from[i]);            \
                                               \
        uz8_copy_n(to + j, from + i, len);     \
                                               \
        int to_len = uc8_to_##case(to + j);    \
                                               \
        i += len;                              \
        j += to_len;                           \
    }

void uz8_to_upper(const uc8_t *from, uc8_t *to) {
    uz8_to_case(from, to, UCASE_UPPER);
}

void uz8_n_to_upper(const uc8_t *from, size_t n, uc8_t *to) {
    uz8_n_to_case(from, n, to, UCASE_UPPER);
}

void uz8_to_lower(const uc8_t *from, uc8_t *to) {
    uz8_to_case(from, to, UCASE_LOWER);
}

void uz8_n_to_lower(const uc8_t *from, size_t n, uc8_t *to) {
    uz8_n_to_case(from, n, to, UCASE_LOWER);
}

void uz8_to_case(const uc8_t *from, uc8_t *to, ucase_t ca) {
    assert(from && to);

    uc8_to_case_func_t func = uc8_to_case_func_from_ucase(ca);

    if (!func)
        return;

    for (size_t i = 0, j = 0; from[i];) {
        int len = uc8_len(from[i]);

        uz8_copy_n(to + j, from + i, len);

        int to_len = func(to + j);

        i += len;
        j += to_len;
    }
}

void uz8_n_to_case(const uc8_t *from, size_t n, uc8_t *to, ucase_t ca) {
    assert(from && to);

    uc8_to_case_func_t func = uc8_to_case_func_from_ucase(ca);

    if (!func)
        return;

    for (size_t i = 0, j = 0; i < n;) {
        int len = uc8_len(from[i]);

        uz8_copy_n(to + j, from + i, len);

        int to_len = func(to + j);

        i += len;
        j += to_len;
    }
}

#define USTR_RETURN_Z_N_TRIM_LEFT_(N, src, n) \
    {                                         \
        assert(cstr);                         \
                                              \
        size_t wspace_len = 0;                \
                                              \
        for (size_t i = 0; i < n;) {          \
            int len = uc##N##_len(cstr[i]);   \
                                              \
            if (uc##N##_wspace(cstr + i))     \
                wspace_len += len;            \
            else                              \
                break;                        \
                                              \
            i += len;                         \
        }                                     \
                                              \
        size_t new_len = n - wspace_len;      \
                                              \
        for (size_t i = 0; i < new_len; ++i)  \
            cstr[i] = cstr[i + wspace_len];   \
                                              \
        return new_len;                       \
    }

#define USTR_RETURN_Z_N_TRIM_RIGHT_(N, src, n) \
    {                                          \
        assert(cstr);                          \
                                               \
        size_t wspace_len = 0;                 \
                                               \
        for (ptrdiff_t i = n - 1; i >= 0;) {   \
            int len = uc##N##_len(cstr[i]);    \
                                               \
            if (uc##N##_wspace(cstr + i))      \
                ++wspace_len;                  \
            else                               \
                break;                         \
                                               \
            i -= len;                          \
        }                                      \
                                               \
        return n - wspace_len;                 \
    }

size_t uz32_trim(uc32_t *cstr) {
    return uz32_n_trim(cstr, uz32_len(cstr));
}

size_t uz32_n_trim(uc32_t *cstr, size_t n) {
    return uz32_n_trim_right(cstr, uz32_n_trim_left(cstr, n));
}

size_t uz32_trim_left(uc32_t *cstr) {
    return uz32_n_trim_left(cstr, uz32_len(cstr));
}

size_t uz32_n_trim_left(uc32_t *cstr, size_t n) {
    assert(cstr);

    size_t wspace_len = 0;

    for (size_t i = 0; i < n; ++i)
        if (uc32_wspace(cstr[i]))
            ++wspace_len;
        else
            break;

    size_t new_len = n - wspace_len;

    for (size_t i = 0; i < new_len; ++i)
        cstr[i] = cstr[i + wspace_len];

    return new_len;
}

size_t uz32_trim_right(const uc32_t *cstr) {
    return uz32_n_trim_right(cstr, uz32_len(cstr));
}

size_t uz32_n_trim_right(const uc32_t *cstr, size_t n) {
    assert(cstr);

    size_t wspace_len = 0;

    for (ptrdiff_t i = n - 1; i >= 0; --i)
        if (uc32_wspace(cstr[i]))
            ++wspace_len;
        else
            break;

    return n - wspace_len;
}

size_t uz16_trim(uc16_t *cstr) {
	return uz16_n_trim_right(cstr, uz16_trim_left(cstr));
}

size_t uz16_n_trim(uc16_t *cstr, size_t n) {
    return uz16_n_trim_right(cstr, uz16_n_trim_left(cstr, n));
}

size_t uz16_trim_left(uc16_t *cstr) {
	return uz16_n_trim_left(cstr, uz16_len(cstr));
}

size_t uz16_n_trim_left(uc16_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_LEFT_(16, cstr, n);
}

size_t uz16_trim_right(const uc16_t *cstr) {
	return uz16_n_trim_right(cstr, uz16_len(cstr));
}

size_t uz16_n_trim_right(const uc16_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_RIGHT_(16, cstr, n);
}

size_t uz8_trim(uc8_t *cstr) {
	return uz8_n_trim_right(cstr, uz8_trim_left(cstr));
}

size_t uz8_n_trim(uc8_t *cstr, size_t n) {
    return uz8_n_trim_right(cstr, uz8_n_trim_left(cstr, n));
}

size_t uz8_trim_left(uc8_t *cstr) {
	return uz8_n_trim_left(cstr, uz8_len(cstr));
}

size_t uz8_n_trim_left(uc8_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_LEFT_(8, cstr, n);
}

size_t uz8_trim_right(const uc8_t *cstr) {
	return uz8_n_trim_right(cstr, uz8_len(cstr));
}

size_t uz8_n_trim_right(const uc8_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_RIGHT_(8, cstr, n);
}

#define USTR_COPY_(dst, src) \
    assert(dst && src);      \
                             \
    while (*src)             \
        *dst++ = *src++;

#define USTR_COPY_N_(dst, src, n) \
    assert(dst && src);           \
                                  \
    while (n--)                   \
        *dst++ = *src++;

#define USTR_N_COPY_N_(dst, dst_len, src, src_len) \
    assert(dst && src);                            \
                                                   \
    while (dst_len-- && src_len--)                 \
        *dst++ = *src++;

void uz32_copy(uc32_t *dst, const uc32_t *src) {
    USTR_COPY_(dst, src);
}

void uz32_copy_n(uc32_t *dst, const uc32_t *src, size_t n) {
    USTR_COPY_N_(dst, src, n);
}

void uz32_n_copy_n(uc32_t *dst, size_t dst_len, const uc32_t *src, size_t src_len) {
    USTR_N_COPY_N_(dst, dst_len, src, src_len);
}

void uz16_copy(uc16_t *dst, const uc16_t *src) {
    USTR_COPY_(dst, src);
}

void uz16_copy_n(uc16_t *dst, const uc16_t *src, size_t n) {
    USTR_COPY_N_(dst, src, n);
}

void uz16_n_copy_n(uc16_t *dst, size_t dst_len, const uc16_t *src, size_t src_len) {
    USTR_N_COPY_N_(dst, dst_len, src, src_len);
}

void uz8_copy(uc8_t *dst, const uc8_t *src) {
    USTR_COPY_(dst, src);
}

void uz8_copy_n(uc8_t *dst, const uc8_t *src, size_t n) {
    USTR_COPY_N_(dst, src, n);
}

void uz8_n_copy_n(uc8_t *dst, size_t dst_len, const uc8_t *src, size_t src_len) {
    USTR_N_COPY_N_(dst, dst_len, src, src_len);
}

#define USTR_MOVE_(dst, src, n)              \
    assert(dst && src);                        \
                                               \
    if (dst < src)                             \
        while (n--)                            \
            *dst++ = *src++;                   \
    else                                       \
        for (ptrdiff_t i = n - 1; i >= 0; --i) \
            dst[i] = src[i];

void uz32_move(uc32_t *dst, const uc32_t *src, size_t n) {
    USTR_MOVE_(dst, src, n);
}

void uz16_move(uc16_t *dst, const uc16_t *src, size_t n) {
    USTR_MOVE_(dst, src, n);
}

void uz8_move(uc8_t *dst, const uc8_t *src, size_t n) {
    USTR_MOVE_(dst, src, n);
}

void uz32_reverse(uc32_t *cstr) {
    uz32_n_reverse(cstr, uz32_len(cstr));
}

void uz32_n_reverse(uc32_t *cstr, size_t n) {
    assert(cstr);

    for (size_t i = 0, j = n - 1; i < n / 2; ++i, --j) {
        uc32_t tmp = cstr[j];

        cstr[j] = cstr[i];
        cstr[i] = tmp;
    }
}

void uz16_reverse(uc16_t *cstr) {
    uz16_n_reverse(cstr, uz16_len(cstr));
}

void uz16_n_reverse(uc16_t *cstr, size_t n) {
    assert(cstr);

    // Reverse words

    for (size_t i = 0, j = n - 1; i < n / 2; ++i, --j) {
        uc16_t tmp = cstr[j];

        cstr[j] = cstr[i];
        cstr[i] = tmp; 
    }

    // Fix surrogates

    for (size_t i = 0; i < n;) {
        uc16_t c = cstr[i];

        if (uc16_srgt_high(c)) {
            size_t j = i + 1;

            cstr[i] = cstr[j];
            cstr[j] = c;

            i += 2;
        } else
            ++i;
    }
}

void uz8_reverse(uc8_t *cstr) {
    uz8_n_reverse(cstr, uz8_len(cstr));
}

void uz8_n_reverse(uc8_t *cstr, size_t n) {
    assert(cstr);

    // Reverse bytes

    for (size_t i = 0, j = n - 1; i < n / 2; ++i, --j) {
        uc8_t tmp = cstr[j];

        cstr[j] = cstr[i];
        cstr[i] = tmp;
    }

    // Fix sequences

    for (size_t i = 0; i < n;) {
        size_t trail = uz8_n_trail(cstr + i, n - i);

        // ASCI

        if (!trail) {
            ++i;
            continue;
        }

        // Reverse sequence

        size_t len = trail + i + 1 > n ? trail : trail + 1;
        size_t end = i + len;
        size_t mid = i + len / 2;

        for (size_t j = i, k = end - 1; j < mid; ++j, --k) {
            uc8_t tmp = cstr[k];

            cstr[k] = cstr[j];
            cstr[j] = tmp;
        }

        i += len;
    }
}

size_t uz32_new_csplit(const uc32_t *cstr, uc32_t c, ucv32_t **array) {
	return uz32_new_split((uc32_t *) cstr, c, (uv32_t **) array);
}

size_t uz32_new_csplit_e(const uc32_t *cstr, uc32_t c, ucv32_t **array, bool *error) {
	return uz32_new_split_e((uc32_t *) cstr, c, (uv32_t **) array, error);
}

size_t uz32_n_new_csplit(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t **array) {
	return uz32_n_new_split((uc32_t *) cstr, n, c, (uv32_t **) array);
}

size_t uz32_n_new_csplit_e(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t **array, bool *error) {
	return uz32_n_new_split_e((uc32_t *) cstr, n, c, (uv32_t **) array, error);
}

size_t uz32_csplit(const uc32_t *cstr, uc32_t c, ucv32_t *array, size_t array_len) {
	return uz32_split((uc32_t *) cstr, c, (uv32_t *) array, array_len);
}

size_t uz32_n_csplit(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t *array, size_t array_len) {
	return uz32_n_split((uc32_t *) cstr, n, c, (uv32_t *) array, array_len);
}

size_t uz32_new_split(uc32_t *cstr, uc32_t c, uv32_t **array) {
	return uz32_new_split_e(cstr, c, array, NULL);
}

size_t uz32_new_split_e(uc32_t *cstr, uc32_t c, uv32_t **array, bool *error) {
	return uz32_n_new_split_e(cstr, uz32_len(cstr), c, array, error);
}

size_t uz32_n_new_split(uc32_t *cstr, size_t n, uc32_t c, uv32_t **array) {
	return uz32_n_new_split_e(cstr, n, c, array, NULL);
}

size_t uz32_n_new_split_e(uc32_t *cstr, size_t n, uc32_t c, uv32_t **array, bool *error) {
    size_t array_len = uz32_n_split(cstr, n, c, NULL, 0);

    if (!array)
        return array_len;

    uv32_t *new_array = ualloc(sizeof(uv32_t) * array_len);

    if (!new_array) {
        if (error)
            *error = true;
    
        return array_len;
    }

    *array = new_array;

    return uz32_n_split(cstr, n, c, new_array, array_len);
}

size_t uz32_split(uc32_t *cstr, uc32_t c, uv32_t *array, size_t array_len) {
    return uz32_n_split(cstr, uz32_len(cstr), c, array, array_len);
}

size_t uz32_n_split(uc32_t *cstr, size_t n, uc32_t c, uv32_t *array, size_t array_len) {
    assert(cstr);

    size_t count = 0;

    for (ptrdiff_t prev_pos = 0; prev_pos >= 0; ++count) {
        uc32_t   *begin   = cstr + prev_pos;
        size_t    len     = n - prev_pos;
        ptrdiff_t rel_pos = uz32_n_uc32_pos(begin, len, c);
        ptrdiff_t pos     = rel_pos;

        if (array && count < array_len) {
            size_t view_len = pos < 0 ? len : rel_pos;
            array[count] = uv32_from_uz32_n(begin, view_len);
        }

        prev_pos = pos >= 0 ? pos + prev_pos + 1 : pos;
    }

	return count;
}

size_t uz32_new_csplit_uz32(const uc32_t *cstr, const uc32_t *another, ucv32_t **array) {
    return uz32_new_split_uz32((uc32_t *) cstr, another, (uv32_t **) array);
}

size_t uz32_new_csplit_uz32_e(const uc32_t *cstr, const uc32_t *another, ucv32_t **array, bool *error) {
    return uz32_new_split_uz32_e((uc32_t *) cstr, another, (uv32_t **) array, error);
}

size_t uz32_n_new_csplit_uz32(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t **array) {
    return uz32_n_new_split_uz32((uc32_t *) cstr, n, another, (uv32_t **) array);
}

size_t uz32_n_new_csplit_uz32_e(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t **array, bool *error) {
    return uz32_n_new_split_uz32_e((uc32_t *) cstr, n, another, (uv32_t **) array, error);
}

size_t uz32_csplit_uz32(const uc32_t *cstr, const uc32_t *another, ucv32_t *array, size_t array_len) {
    return uz32_split_uz32((uc32_t *) cstr, another, (uv32_t *) array, array_len);
}

size_t uz32_n_csplit_uz32(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t *array, size_t array_len) {
    return uz32_n_split_uz32((uc32_t *) cstr, n, another, (uv32_t *) array, array_len);
}

size_t uz32_new_split_uz32(uc32_t *cstr, const uc32_t *another, uv32_t **array) {
    return uz32_new_split_uz32_e(cstr, another, array, NULL);
}

size_t uz32_new_split_uz32_e(uc32_t *cstr, const uc32_t *another, uv32_t **array, bool *error) {
    return uz32_n_new_split_uz32_e(cstr, uz32_len(cstr), another, array, error);
}

size_t uz32_n_new_split_uz32(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t **array) {
    return uz32_n_new_split_uz32_e(cstr, n, another, array, NULL);
}

size_t uz32_n_new_split_uz32_e(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t **array, bool *error) {
    return uz32_n_new_split_uz32_n_e(cstr, n, another, uz32_len(another), array, error);
}

size_t uz32_split_uz32(uc32_t *cstr, const uc32_t *another, uv32_t *array, size_t array_len) {
    return uz32_n_split_uz32(cstr, uz32_len(cstr), another, array, array_len);
}

size_t uz32_n_split_uz32(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t *array, size_t array_len) {
    return uz32_n_split_uz32_n(cstr, n, another, uz32_len(another), array, array_len);
}

size_t uz32_new_csplit_uz32_n(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t **array) {
    return uz32_new_split_uz32_n((uc32_t *) cstr, another, n, (uv32_t **) array);
}

size_t uz32_new_csplit_uz32_n_e(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t **array, bool *error) {
    return uz32_new_split_uz32_n_e((uc32_t *) cstr, another, n, (uv32_t **) array, error);
}

size_t uz32_n_new_csplit_uz32_n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t **array) {
    return uz32_n_new_split_uz32_n((uc32_t *) cstr, cstr_len, another, another_len, (uv32_t **) array);
}

size_t uz32_n_new_csplit_uz32_n_e(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t **array, bool *error) {
    return uz32_n_new_split_uz32_n_e((uc32_t *) cstr, cstr_len, another, another_len, (uv32_t **) array, error);
}

size_t uz32_csplit_uz32_n(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t *array, size_t array_len) {
    return uz32_split_uz32_n((uc32_t *) cstr, another, n, (uv32_t *) array, array_len);
}

size_t uz32_n_csplit_uz32_n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t *array, size_t array_len) {
    return uz32_n_split_uz32_n((uc32_t *) cstr, cstr_len, another, array_len, (uv32_t *) array, array_len);
}

size_t uz32_new_split_uz32_n(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t **array) {
    return uz32_new_split_uz32_n_e(cstr, another, n, array, NULL);
}

size_t uz32_new_split_uz32_n_e(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t **array, bool *error) {
    return uz32_n_new_split_uz32_n_e(cstr, uz32_len(cstr), another, n, array, error);
}

size_t uz32_n_new_split_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t **array) {
    return uz32_n_new_split_uz32_n_e(cstr, cstr_len, another, another_len, array, NULL);
}

size_t uz32_n_new_split_uz32_n_e(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t **array, bool *error) {
    assert(cstr && another);

    size_t array_len = uz32_n_split_uz32_n(cstr, cstr_len, another, another_len, NULL, 0);

    if (!array)
        return array_len;

    uv32_t *new_array = ualloc(sizeof(uv32_t) * array_len);

    if (!new_array) {
        if (error)
            *error = true;
    
        return array_len;
    }

    *array = new_array;

    return uz32_n_split_uz32_n(cstr, cstr_len, another, another_len, new_array, array_len);
}

size_t uz32_split_uz32_n(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t *array, size_t array_len) {
    return uz32_n_split_uz32_n(cstr, uz32_len(cstr), another, n, array, array_len);
}

size_t uz32_n_split_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t *array, size_t array_len) {
    assert(cstr && another);

    if (another_len > cstr_len)
        return 0;

    size_t count = 0;

    for (ptrdiff_t prev_pos = 0; prev_pos >= 0; ++count) {
        uc32_t   *begin   = cstr + prev_pos;
        size_t    len     = cstr_len - prev_pos;
        ptrdiff_t rel_pos = uz32_n_pos_n(begin, len, another, another_len);
        ptrdiff_t pos     = rel_pos;

        if (array && count < array_len) {
            size_t view_len = pos < 0 ? len : rel_pos;
            array[count] = uv32_from_uz32_n(begin, view_len);
        }

        prev_pos = pos >= 0 ? pos + prev_pos + another_len : pos;
    }

	return count;
}

#define USTR_RETURN_REPLACE_C_C_(cstr, from, to, count) \
    {                                                   \
        assert(cstr);                                   \
                                                        \
        size_t inner_count = 0;                         \
        size_t len         = 0;                         \
                                                        \
        for (; cstr[len]; ++len)                        \
            if (cstr[len] == from) {                    \
                cstr[len] = to;                         \
                ++inner_count;                          \
            }                                           \
                                                        \
        if (count)                                      \
            *count = inner_count;                       \
                                                        \
        return len;                                     \
    }

#define USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count) \
    {                                                               \
        assert(cstr);                                               \
                                                                    \
        size_t inner_count = 0;                                     \
                                                                    \
        for (size_t i = 0; i < cstr_len; ++i)                       \
            if (cstr[i] == from) {                                  \
                cstr[i] = to;                                       \
                ++inner_count;                                      \
            }                                                       \
                                                                    \
            if (count)                                              \
                *count = inner_count;                               \
                                                                    \
        return cstr_len;                                            \
    }

#define USTR_RETURN_N_REPLACE_Z_N_C_(N, cstr, cstr_len, from, from_len, to, count) \
    {                                                                              \
        assert(cstr && from);                                                      \
                                                                                   \
        if (!from_len || from_len > cstr_len) {                                    \
            if (count)                                                             \
                *count = 0;                                                        \
                                                                                   \
            return cstr_len;                                                       \
        }                                                                          \
                                                                                   \
        size_t inner_count  = 0;                                                   \
        size_t new_cstr_len = cstr_len;                                            \
        size_t len_delta    = from_len - 1;                                        \
                                                                                   \
        while (true) {                                                             \
            ptrdiff_t pos = uz##N##_n_pos_n(cstr, cstr_len, from, from_len);       \
                                                                                   \
            if (pos < 0)                                                           \
                break;                                                             \
                                                                                   \
            cstr[pos]     = to;                                                    \
            cstr_len     -= len_delta + pos;                                       \
            new_cstr_len -= len_delta;                                             \
            cstr         += pos + 1;                                               \
                                                                                   \
            uz##N##_move(cstr, cstr + len_delta, cstr_len);                        \
                                                                                   \
            ++inner_count;                                                         \
        }                                                                          \
                                                                                   \
        if (count)                                                                 \
            *count = inner_count;                                                  \
                                                                                   \
        return new_cstr_len;                                                       \
    }

#define USTR_RETURN_N_REPLACE_C_Z_N_(N, cstr, cstr_len, from, to, to_len, count) \
    {                                                                            \
        assert(cstr && to);                                                      \
                                                                                 \
        size_t inner_count = 0;                                                  \
                                                                                 \
        for (size_t i = 0; i < cstr_len; ++i)                                    \
            if (cstr[i] == from) {                                               \
                uz##N##_move(cstr + i + to_len, cstr + i + 1, cstr_len - i - 1); \
                uz##N##_copy_n(cstr + i, to, to_len);                            \
                cstr_len += to_len - 1;                                          \
                ++inner_count;                                                   \
            }                                                                    \
                                                                                 \
        if (count)                                                               \
            *count = inner_count;                                                \
                                                                                 \
        return cstr_len;                                                         \
    }

#define USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count) \
    {                                                                         \
        assert(cstr);                                                         \
                                                                              \
        size_t inner_count = 0;                                               \
                                                                              \
        for (size_t i = 0; i < cstr_len; ++i)                                 \
            if (cstr[i] == from)                                              \
                ++inner_count;                                                \
                                                                              \
        if (count)                                                            \
            *count = inner_count;                                             \
                                                                              \
        return cstr_len + to_len * inner_count - inner_count;                 \
    }

#define USTR_RETURN_N_REPLACE_Z_N_Z_N_(N, cstr, cstr_len, from, from_len, to, to_len, count) \
    {                                                                                        \
        assert(cstr && from && to);                                                          \
                                                                                             \
        if (!from_len || from_len > cstr_len) {                                              \
            if (count)                                                                       \
                *count = 0;                                                                  \
                                                                                             \
            return cstr_len;                                                                 \
        }                                                                                    \
                                                                                             \
        size_t    inner_count  = 0;                                                          \
        size_t    new_cstr_len = cstr_len;                                                   \
        ptrdiff_t len_delta    = from_len - to_len;                                          \
                                                                                             \
        while (true) {                                                                       \
            ptrdiff_t pos = uz##N##_n_pos_n(cstr, cstr_len, from, from_len);                 \
                                                                                             \
            if (pos < 0)                                                                     \
                break;                                                                       \
                                                                                             \
            cstr         += pos;                                                             \
            cstr_len     -= len_delta + pos;                                                 \
            new_cstr_len -= len_delta;                                                       \
                                                                                             \
            uc##N##_t *new_cstr = cstr + to_len;                                             \
                                                                                             \
            uz##N##_move(new_cstr, cstr + from_len, cstr_len);                               \
            uz##N##_copy_n(cstr, to, to_len);                                                \
                                                                                             \
            cstr = new_cstr;                                                                 \
                                                                                             \
            ++inner_count;                                                                   \
        }                                                                                    \
                                                                                             \
        if (count)                                                                           \
            *count = inner_count;                                                            \
                                                                                             \
        return new_cstr_len;                                                                 \
    }

#define USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(N, cstr, cstr_len, from, from_len, to_len, count) \
    {                                                                                        \
        assert(cstr && from);                                                                \
                                                                                             \
        if (!from_len || from_len > cstr_len) {                                              \
            if (count)                                                                       \
                *count = 0;                                                                  \
                                                                                             \
            return cstr_len;                                                                 \
        }                                                                                    \
                                                                                             \
        size_t    inner_count   = 0;                                                         \
        size_t    new_cstr_len  = cstr_len;                                                  \
        ptrdiff_t new_len_delta = from_len - to_len;                                         \
                                                                                             \
        while (true) {                                                                       \
            ptrdiff_t pos = uz##N##_n_pos_n(cstr, cstr_len, from, from_len);                 \
                                                                                             \
            if (pos < 0)                                                                     \
                break;                                                                       \
                                                                                             \
            size_t len_delta = from_len + pos;                                               \
                                                                                             \
            cstr         += len_delta;                                                       \
            cstr_len     -= len_delta;                                                       \
            new_cstr_len -= new_len_delta;                                                   \
                                                                                             \
            ++inner_count;                                                                   \
        }                                                                                    \
                                                                                             \
        if (count)                                                                           \
            *count = inner_count;                                                            \
                                                                                             \
        return new_cstr_len;                                                                 \
    }

size_t uz32_replace_uc32_uc32(uc32_t *cstr, uc32_t from, uc32_t to) {
    return uz32_replace_uc32_uc32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uc32_uc32_c(uc32_t *cstr, uc32_t from, uc32_t to, size_t *count) {
    USTR_RETURN_REPLACE_C_C_(cstr, from, to, count);
}

size_t uz32_n_replace_uc32_uc32(uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to) {
    return uz32_n_replace_uc32_uc32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uc32_uc32_c(uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count);
}

size_t uz32_replace_uz32_uc32(uc32_t *cstr, const uc32_t *from, uc32_t to) {
    return uz32_replace_uz32_uc32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uz32_uc32_c(uc32_t *cstr, const uc32_t *from, uc32_t to, size_t *count) {
	return uz32_replace_uz32_n_uc32_c(cstr, from, uz32_len(from), to, count);
}

size_t uz32_n_replace_uz32_uc32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to) {
    return uz32_n_replace_uz32_uc32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uz32_uc32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to, size_t *count) {
	return uz32_n_replace_uz32_n_uc32_c(cstr, cstr_len, from, uz32_len(from), to, count);
}

size_t uz32_replace_uz32_n_uc32(uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to) {
    return uz32_replace_uz32_n_uc32_c(cstr, from, from_len, to, NULL);
}

size_t uz32_replace_uz32_n_uc32_c(uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to, size_t *count) {
    return uz32_n_replace_uz32_n_uc32_c(cstr, uz32_len(cstr), from, from_len, to, count);
}

size_t uz32_n_replace_uz32_n_uc32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to) {
    return uz32_n_replace_uz32_n_uc32_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz32_n_replace_uz32_n_uc32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_C_(32, cstr, cstr_len, from, from_len, to, count);
}

size_t uz32_replace_uc32_uz32(uc32_t *cstr, uc32_t from, const uc32_t *to) {
    return uz32_replace_uc32_uz32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uc32_uz32_c(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_c(cstr, uz32_len(cstr), from, to, uz32_len(to), count);
}

size_t uz32_replace_uc32_uz32_len(const uc32_t *cstr, uc32_t from, const uc32_t *to) {
    return uz32_replace_uc32_uz32_len_c(cstr, from, to, NULL);
}

size_t uz32_replace_uc32_uz32_len_c(const uc32_t *cstr, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_len_c(cstr, uz32_len(cstr), from, uz32_len(to), count);
}

size_t uz32_n_replace_uc32_uz32(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to) {
    return uz32_n_replace_uc32_uz32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uc32_uz32_c(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_c(cstr, cstr_len, from, to, uz32_len(to), count);
}

size_t uz32_n_replace_uc32_uz32_len(const uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to) {
    return uz32_n_replace_uc32_uz32_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uc32_uz32_len_c(const uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_len_c(cstr, cstr_len, from, uz32_len(to), count);
}

size_t uz32_replace_uc32_uz32_n(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t to_len) {
    return uz32_replace_uc32_uz32_n_c(cstr, from, to, to_len, NULL);
}

size_t uz32_replace_uc32_uz32_n_c(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_c(cstr, uz32_len(cstr), from, to, to_len, count);
}

size_t uz32_replace_uc32_uz32_n_len(const uc32_t *cstr, uc32_t from, size_t to_len) {
    return uz32_replace_uc32_uz32_n_len_c(cstr, from, to_len, NULL);
}

size_t uz32_replace_uc32_uz32_n_len_c(const uc32_t *cstr, uc32_t from, size_t to_len, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_len_c(cstr, uz32_len(cstr), from, to_len, count);
}

size_t uz32_n_replace_uc32_uz32_n(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t to_len) {
    return uz32_n_replace_uc32_uz32_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz32_n_replace_uc32_uz32_n_c(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_(32, cstr, cstr_len, from, to, to_len, count);
}

size_t uz32_n_replace_uc32_uz32_n_len(const uc32_t *cstr, size_t cstr_len, uc32_t from, size_t to_len) {
    return uz32_n_replace_uc32_uz32_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz32_n_replace_uc32_uz32_n_len_c(const uc32_t *cstr, size_t cstr_len, uc32_t from, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count);
}

size_t uz32_replace_uz32_uz32(uc32_t *cstr, const uc32_t *from, const uc32_t *to) {
    return uz32_replace_uz32_uz32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uz32_uz32_c(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, uz32_len(cstr), from, uz32_len(from), to, uz32_len(to), count);
}

size_t uz32_replace_uz32_uz32_len(const uc32_t *cstr, const uc32_t *from, const uc32_t *to) {
    return uz32_replace_uz32_uz32_len_c(cstr, from, to, NULL);
}

size_t uz32_replace_uz32_uz32_len_c(const uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, uz32_len(cstr), from, uz32_len(from), uz32_len(to), count);
}

size_t uz32_n_replace_uz32_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to) {
    return uz32_n_replace_uz32_uz32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uz32_uz32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, cstr_len, from, uz32_len(from), to, uz32_len(to), count);
}

size_t uz32_n_replace_uz32_uz32_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to) {
    return uz32_n_replace_uz32_uz32_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uz32_uz32_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, cstr_len, from, uz32_len(from), uz32_len(to), count);
}

size_t uz32_replace_uz32_n_uz32(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32_replace_uz32_n_uz32_c(cstr, from, from_len, to, NULL);
}

size_t uz32_replace_uz32_n_uz32_c(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, uz32_len(cstr), from, from_len, to, uz32_len(to), count);
}

size_t uz32_replace_uz32_n_uz32_len(const uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32_replace_uz32_n_uz32_len_c(cstr, from, from_len, to, NULL);
}

size_t uz32_replace_uz32_n_uz32_len_c(const uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, uz32_len(cstr), from, from_len, uz32_len(to), count);
}

size_t uz32_n_replace_uz32_n_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32_n_replace_uz32_n_uz32_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz32_n_replace_uz32_n_uz32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, cstr_len, from, from_len, to, uz32_len(to), count);
}

size_t uz32_n_replace_uz32_n_uz32_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32_n_replace_uz32_n_uz32_len_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz32_n_replace_uz32_n_uz32_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, cstr_len, from, from_len, uz32_len(to), count);
}

size_t uz32_replace_uz32_uz32_n(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t to_len) {
    return uz32_replace_uz32_uz32_n_c(cstr, from, to, to_len, NULL);
}

size_t uz32_replace_uz32_uz32_n_c(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, uz32_len(cstr), from, uz32_len(from), to, to_len, count);
}

size_t uz32_replace_uz32_uz32_n_len(const uc32_t *cstr, const uc32_t *from, size_t to_len) {
    return uz32_replace_uz32_uz32_n_len_c(cstr, from, to_len, NULL);
}

size_t uz32_replace_uz32_uz32_n_len_c(const uc32_t *cstr, const uc32_t *from, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, uz32_len(cstr), from, uz32_len(from), to_len, count);
}

size_t uz32_n_replace_uz32_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t to_len) {
    return uz32_n_replace_uz32_uz32_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz32_n_replace_uz32_uz32_n_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, cstr_len, from, uz32_len(from), to, to_len, count);
}

size_t uz32_n_replace_uz32_uz32_n_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t to_len) {
    return uz32_n_replace_uz32_uz32_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz32_n_replace_uz32_uz32_n_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, cstr_len, from, uz32_len(from), to_len, count);
}

size_t uz32_replace_uz32_n_uz32_n(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len) {
    return uz32_replace_uz32_n_uz32_n_c(cstr, from, from_len, to, to_len, NULL);
}

size_t uz32_replace_uz32_n_uz32_n_c(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, uz32_len(cstr), from, from_len, to, to_len, count);
}

size_t uz32_replace_uz32_n_uz32_n_len(const uc32_t *cstr, const uc32_t *from, size_t from_len, size_t to_len) {
    return uz32_replace_uz32_n_uz32_n_len_c(cstr, from, from_len, to_len, NULL);
}

size_t uz32_replace_uz32_n_uz32_n_len_c(const uc32_t *cstr, const uc32_t *from, size_t from_len, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, uz32_len(cstr), from, from_len, to_len, count);
}

size_t uz32_n_replace_uz32_n_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len) {
    return uz32_n_replace_uz32_n_uz32_n_c(cstr, cstr_len, from, from_len, to, to_len, NULL);
}

size_t uz32_n_replace_uz32_n_uz32_n_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_(32, cstr, cstr_len, from, from_len, to, to_len, count);
}

size_t uz32_n_replace_uz32_n_uz32_n_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, size_t to_len) {
    return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, cstr_len, from, from_len, to_len, NULL);
}

size_t uz32_n_replace_uz32_n_uz32_n_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(32, cstr, cstr_len, from, from_len, to_len, count);
}

size_t uz16_replace_uc16_uc16(uc16_t *cstr, uc16_t from, uc16_t to) {
    return uz16_replace_uc16_uc16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uc16_uc16_c(uc16_t *cstr, uc16_t from, uc16_t to, size_t *count) {
    USTR_RETURN_REPLACE_C_C_(cstr, from, to, count);
}

size_t uz16_n_replace_uc16_uc16(uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to) {
    return uz16_n_replace_uc16_uc16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uc16_uc16_c(uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count);
}

size_t uz16_replace_uz16_uc16(uc16_t *cstr, const uc16_t *from, uc16_t to) {
    return uz16_replace_uz16_uc16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uz16_uc16_c(uc16_t *cstr, const uc16_t *from, uc16_t to, size_t *count) {
	return uz16_replace_uz16_n_uc16_c(cstr, from, uz16_len(from), to, count);
}

size_t uz16_n_replace_uz16_uc16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to) {
    return uz16_n_replace_uz16_uc16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uz16_uc16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to, size_t *count) {
	return uz16_n_replace_uz16_n_uc16_c(cstr, cstr_len, from, uz16_len(from), to, count);
}

size_t uz16_replace_uz16_n_uc16(uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to) {
    return uz16_replace_uz16_n_uc16_c(cstr, from, from_len, to, NULL);
}

size_t uz16_replace_uz16_n_uc16_c(uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to, size_t *count) {
    return uz16_n_replace_uz16_n_uc16_c(cstr, uz16_len(cstr), from, from_len, to, count);
}

size_t uz16_n_replace_uz16_n_uc16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to) {
    return uz16_n_replace_uz16_n_uc16_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz16_n_replace_uz16_n_uc16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_C_(16, cstr, cstr_len, from, from_len, to, count);
}

size_t uz16_replace_uc16_uz16(uc16_t *cstr, uc16_t from, const uc16_t *to) {
    return uz16_replace_uc16_uz16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uc16_uz16_c(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_c(cstr, uz16_len(cstr), from, to, uz16_len(to), count);
}

size_t uz16_replace_uc16_uz16_len(const uc16_t *cstr, uc16_t from, const uc16_t *to) {
    return uz16_replace_uc16_uz16_len_c(cstr, from, to, NULL);
}

size_t uz16_replace_uc16_uz16_len_c(const uc16_t *cstr, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_len_c(cstr, uz16_len(cstr), from, uz16_len(to), count);
}

size_t uz16_n_replace_uc16_uz16(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to) {
    return uz16_n_replace_uc16_uz16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uc16_uz16_c(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_c(cstr, cstr_len, from, to, uz16_len(to), count);
}

size_t uz16_n_replace_uc16_uz16_len(const uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to) {
    return uz16_n_replace_uc16_uz16_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uc16_uz16_len_c(const uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_len_c(cstr, cstr_len, from, uz16_len(to), count);
}

size_t uz16_replace_uc16_uz16_n(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t to_len) {
    return uz16_replace_uc16_uz16_n_c(cstr, from, to, to_len, NULL);
}

size_t uz16_replace_uc16_uz16_n_c(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_c(cstr, uz16_len(cstr), from, to, to_len, count);
}

size_t uz16_replace_uc16_uz16_n_len(const uc16_t *cstr, uc16_t from, size_t to_len) {
    return uz16_replace_uc16_uz16_n_len_c(cstr, from, to_len, NULL);
}

size_t uz16_replace_uc16_uz16_n_len_c(const uc16_t *cstr, uc16_t from, size_t to_len, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_len_c(cstr, uz16_len(cstr), from, to_len, count);
}

size_t uz16_n_replace_uc16_uz16_n(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t to_len) {
    return uz16_n_replace_uc16_uz16_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz16_n_replace_uc16_uz16_n_c(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_(16, cstr, cstr_len, from, to, to_len, count);
}

size_t uz16_n_replace_uc16_uz16_n_len(const uc16_t *cstr, size_t cstr_len, uc16_t from, size_t to_len) {
    return uz16_n_replace_uc16_uz16_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz16_n_replace_uc16_uz16_n_len_c(const uc16_t *cstr, size_t cstr_len, uc16_t from, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count);
}

size_t uz16_replace_uz16_uz16(uc16_t *cstr, const uc16_t *from, const uc16_t *to) {
    return uz16_replace_uz16_uz16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uz16_uz16_c(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, uz16_len(cstr), from, uz16_len(from), to, uz16_len(to), count);
}

size_t uz16_replace_uz16_uz16_len(const uc16_t *cstr, const uc16_t *from, const uc16_t *to) {
    return uz16_replace_uz16_uz16_len_c(cstr, from, to, NULL);
}

size_t uz16_replace_uz16_uz16_len_c(const uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, uz16_len(cstr), from, uz16_len(from), uz16_len(to), count);
}

size_t uz16_n_replace_uz16_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to) {
    return uz16_n_replace_uz16_uz16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uz16_uz16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, cstr_len, from, uz16_len(from), to, uz16_len(to), count);
}

size_t uz16_n_replace_uz16_uz16_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to) {
    return uz16_n_replace_uz16_uz16_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uz16_uz16_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, cstr_len, from, uz16_len(from), uz16_len(to), count);
}

size_t uz16_replace_uz16_n_uz16(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16_replace_uz16_n_uz16_c(cstr, from, from_len, to, NULL);
}

size_t uz16_replace_uz16_n_uz16_c(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, uz16_len(cstr), from, from_len, to, uz16_len(to), count);
}

size_t uz16_replace_uz16_n_uz16_len(const uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16_replace_uz16_n_uz16_len_c(cstr, from, from_len, to, NULL);
}

size_t uz16_replace_uz16_n_uz16_len_c(const uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, uz16_len(cstr), from, from_len, uz16_len(to), count);
}

size_t uz16_n_replace_uz16_n_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16_n_replace_uz16_n_uz16_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz16_n_replace_uz16_n_uz16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, cstr_len, from, from_len, to, uz16_len(to), count);
}

size_t uz16_n_replace_uz16_n_uz16_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16_n_replace_uz16_n_uz16_len_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz16_n_replace_uz16_n_uz16_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, cstr_len, from, from_len, uz16_len(to), count);
}

size_t uz16_replace_uz16_uz16_n(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t to_len) {
    return uz16_replace_uz16_uz16_n_c(cstr, from, to, to_len, NULL);
}

size_t uz16_replace_uz16_uz16_n_c(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, uz16_len(cstr), from, uz16_len(from), to, to_len, count);
}

size_t uz16_replace_uz16_uz16_n_len(const uc16_t *cstr, const uc16_t *from, size_t to_len) {
    return uz16_replace_uz16_uz16_n_len_c(cstr, from, to_len, NULL);
}

size_t uz16_replace_uz16_uz16_n_len_c(const uc16_t *cstr, const uc16_t *from, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, uz16_len(cstr), from, uz16_len(from), to_len, count);
}

size_t uz16_n_replace_uz16_uz16_n(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t to_len) {
    return uz16_n_replace_uz16_uz16_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz16_n_replace_uz16_uz16_n_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, cstr_len, from, uz16_len(from), to, to_len, count);
}

size_t uz16_n_replace_uz16_uz16_n_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t to_len) {
    return uz16_n_replace_uz16_uz16_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz16_n_replace_uz16_uz16_n_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, cstr_len, from, uz16_len(from), to_len, count);
}

size_t uz16_replace_uz16_n_uz16_n(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len) {
    return uz16_replace_uz16_n_uz16_n_c(cstr, from, from_len, to, to_len, NULL);
}

size_t uz16_replace_uz16_n_uz16_n_c(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, uz16_len(cstr), from, from_len, to, to_len, count);
}

size_t uz16_replace_uz16_n_uz16_n_len(const uc16_t *cstr, const uc16_t *from, size_t from_len, size_t to_len) {
    return uz16_replace_uz16_n_uz16_n_len_c(cstr, from, from_len, to_len, NULL);
}

size_t uz16_replace_uz16_n_uz16_n_len_c(const uc16_t *cstr, const uc16_t *from, size_t from_len, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, uz16_len(cstr), from, from_len, to_len, count);
}

size_t uz16_n_replace_uz16_n_uz16_n(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len) {
    return uz16_n_replace_uz16_n_uz16_n_c(cstr, cstr_len, from, from_len, to, to_len, NULL);
}

size_t uz16_n_replace_uz16_n_uz16_n_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_(16, cstr, cstr_len, from, from_len, to, to_len, count);
}

size_t uz16_n_replace_uz16_n_uz16_n_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, size_t to_len) {
    return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, cstr_len, from, from_len, to_len, NULL);
}

size_t uz16_n_replace_uz16_n_uz16_n_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(16, cstr, cstr_len, from, from_len, to_len, count);
}

size_t uz8_replace_uc8_uc8(uc8_t *cstr, uc8_t from, uc8_t to) {
    return uz8_replace_uc8_uc8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uc8_uc8_c(uc8_t *cstr, uc8_t from, uc8_t to, size_t *count) {
    USTR_RETURN_REPLACE_C_C_(cstr, from, to, count);
}

size_t uz8_n_replace_uc8_uc8(uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to) {
    return uz8_n_replace_uc8_uc8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8_n_replace_uc8_uc8_c(uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count);
}

size_t uz8_replace_uz8_uc8(uc8_t *cstr, const uc8_t *from, uc8_t to) {
    return uz8_replace_uz8_uc8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uz8_uc8_c(uc8_t *cstr, const uc8_t *from, uc8_t to, size_t *count) {
	return uz8_replace_uz8_n_uc8_c(cstr, from, uz8_len(from), to, count);
}

size_t uz8_n_replace_uz8_uc8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to) {
    return uz8_n_replace_uz8_uc8_c(cstr, cstr_len, from, to, NULL);
}
    
size_t uz8_n_replace_uz8_uc8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to, size_t *count) {
	return uz8_n_replace_uz8_n_uc8_c(cstr, cstr_len, from, uz8_len(from), to, count);
}

size_t uz8_replace_uz8_n_uc8(uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to) {
    return uz8_replace_uz8_n_uc8_c(cstr, from, from_len, to, NULL);
}

size_t uz8_replace_uz8_n_uc8_c(uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to, size_t *count) {
    return uz8_n_replace_uz8_n_uc8_c(cstr, uz8_len(cstr), from, from_len, to, count);
}

size_t uz8_n_replace_uz8_n_uc8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to) {
    return uz8_n_replace_uz8_n_uc8_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz8_n_replace_uz8_n_uc8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_C_(8, cstr, cstr_len, from, from_len, to, count);
}

size_t uz8_replace_uc8_uz8(uc8_t *cstr, uc8_t from, const uc8_t *to) {
    return uz8_replace_uc8_uz8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uc8_uz8_c(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_c(cstr, uz8_len(cstr), from, to, uz8_len(to), count);
}

size_t uz8_replace_uc8_uz8_len(const uc8_t *cstr, uc8_t from, const uc8_t *to) {
    return uz8_replace_uc8_uz8_len_c(cstr, from, to, NULL);
}

size_t uz8_replace_uc8_uz8_len_c(const uc8_t *cstr, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_len_c(cstr, uz8_len(cstr), from, uz8_len(to), count);
}

size_t uz8_n_replace_uc8_uz8(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to) {
    return uz8_n_replace_uc8_uz8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8_n_replace_uc8_uz8_c(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_c(cstr, cstr_len, from, to, uz8_len(to), count);
}

size_t uz8_n_replace_uc8_uz8_len(const uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to) {
    return uz8_n_replace_uc8_uz8_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8_n_replace_uc8_uz8_len_c(const uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_len_c(cstr, cstr_len, from, uz8_len(to), count);
}

size_t uz8_replace_uc8_uz8_n(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t to_len) {
    return uz8_replace_uc8_uz8_n_c(cstr, from, to, to_len, NULL);
}

size_t uz8_replace_uc8_uz8_n_c(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_c(cstr, uz8_len(cstr), from, to, to_len, count);
}

size_t uz8_replace_uc8_uz8_n_len(const uc8_t *cstr, uc8_t from, size_t to_len) {
    return uz8_replace_uc8_uz8_n_len_c(cstr, from, to_len, NULL);
}

size_t uz8_replace_uc8_uz8_n_len_c(const uc8_t *cstr, uc8_t from, size_t to_len, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_len_c(cstr, uz8_len(cstr), from, to_len, count);
}

size_t uz8_n_replace_uc8_uz8_n(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t to_len) {
    return uz8_n_replace_uc8_uz8_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz8_n_replace_uc8_uz8_n_c(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_(8, cstr, cstr_len, from, to, to_len, count);
}

size_t uz8_n_replace_uc8_uz8_n_len(const uc8_t *cstr, size_t cstr_len, uc8_t from, size_t to_len) {
    return uz8_n_replace_uc8_uz8_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz8_n_replace_uc8_uz8_n_len_c(const uc8_t *cstr, size_t cstr_len, uc8_t from, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count);
}

size_t uz8_replace_uz8_uz8(uc8_t *cstr, const uc8_t *from, const uc8_t *to) {
    return uz8_replace_uz8_uz8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uz8_uz8_c(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, uz8_len(cstr), from, uz8_len(from), to, uz8_len(to), count);
}

size_t uz8_replace_uz8_uz8_len(const uc8_t *cstr, const uc8_t *from, const uc8_t *to) {
    return uz8_replace_uz8_uz8_len_c(cstr, from, to, NULL);
}

size_t uz8_replace_uz8_uz8_len_c(const uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, uz8_len(cstr), from, uz8_len(from), uz8_len(to), count);
}

size_t uz8_n_replace_uz8_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to) {
    return uz8_n_replace_uz8_uz8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8_n_replace_uz8_uz8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, cstr_len, from, uz8_len(from), to, uz8_len(to), count);
}

size_t uz8_n_replace_uz8_uz8_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to) {
    return uz8_n_replace_uz8_uz8_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8_n_replace_uz8_uz8_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, cstr_len, from, uz8_len(from), uz8_len(to), count);
}

size_t uz8_replace_uz8_n_uz8(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8_replace_uz8_n_uz8_c(cstr, from, from_len, to, NULL);
}

size_t uz8_replace_uz8_n_uz8_c(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, uz8_len(cstr), from, from_len, to, uz8_len(to), count);
}

size_t uz8_replace_uz8_n_uz8_len(const uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8_replace_uz8_n_uz8_len_c(cstr, from, from_len, to, NULL);
}

size_t uz8_replace_uz8_n_uz8_len_c(const uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, uz8_len(cstr), from, from_len, uz8_len(to), count);
}

size_t uz8_n_replace_uz8_n_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8_n_replace_uz8_n_uz8_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz8_n_replace_uz8_n_uz8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, cstr_len, from, from_len, to, uz8_len(to), count);
}

size_t uz8_n_replace_uz8_n_uz8_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8_n_replace_uz8_n_uz8_len_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz8_n_replace_uz8_n_uz8_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, cstr_len, from, from_len, uz8_len(to), count);
}

size_t uz8_replace_uz8_uz8_n(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t to_len) {
    return uz8_replace_uz8_uz8_n_c(cstr, from, to, to_len, NULL);
}

size_t uz8_replace_uz8_uz8_n_c(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, uz8_len(cstr), from, uz8_len(from), to, to_len, count);
}

size_t uz8_replace_uz8_uz8_n_len(const uc8_t *cstr, const uc8_t *from, size_t to_len) {
    return uz8_replace_uz8_uz8_n_len_c(cstr, from, to_len, NULL);
}

size_t uz8_replace_uz8_uz8_n_len_c(const uc8_t *cstr, const uc8_t *from, size_t to_len, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, uz8_len(cstr), from, uz8_len(from), to_len, count);
}

size_t uz8_n_replace_uz8_uz8_n(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t to_len) {
    return uz8_n_replace_uz8_uz8_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz8_n_replace_uz8_uz8_n_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, cstr_len, from, uz8_len(from), to, to_len, count);
}

size_t uz8_n_replace_uz8_uz8_n_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t to_len) {
    return uz8_n_replace_uz8_uz8_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz8_n_replace_uz8_uz8_n_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t to_len, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, cstr_len, from, uz8_len(from), to_len, count);
}

size_t uz8_replace_uz8_n_uz8_n(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len) {
    return uz8_replace_uz8_n_uz8_n_c(cstr, from, from_len, to, to_len, NULL);
}

size_t uz8_replace_uz8_n_uz8_n_c(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, uz8_len(cstr), from, from_len, to, to_len, count);
}

size_t uz8_replace_uz8_n_uz8_n_len(const uc8_t *cstr, const uc8_t *from, size_t from_len, size_t to_len) {
    return uz8_replace_uz8_n_uz8_n_len_c(cstr, from, from_len, to_len, NULL);
}

size_t uz8_replace_uz8_n_uz8_n_len_c(const uc8_t *cstr, const uc8_t *from, size_t from_len, size_t to_len, size_t *count) {
    return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, uz8_len(cstr), from, from_len, to_len, count);
}

size_t uz8_n_replace_uz8_n_uz8_n(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len) {
    return uz8_n_replace_uz8_n_uz8_n_c(cstr, cstr_len, from, from_len, to, to_len, NULL);
}

size_t uz8_n_replace_uz8_n_uz8_n_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_(8, cstr, cstr_len, from, from_len, to, to_len, count);
}

size_t uz8_n_replace_uz8_n_uz8_n_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, size_t to_len) {
    return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, cstr_len, from, from_len, to_len, NULL);
}

size_t uz8_n_replace_uz8_n_uz8_n_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(8, cstr, cstr_len, from, from_len, to_len, count);
}