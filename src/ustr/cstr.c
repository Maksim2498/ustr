#include "cstr.h"

#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#include "fmt/case.h"
#include "fmt/float.h"
#include "fmt/fmt.h"
#include "fmt/int.h"
#include "fmt/radix.h"
#include "fmt/type.h"
#include "util/mem.h"
#include "char.h"
#include "config.h"
#include "cview.h"
#include "str.h"
#include "view.h"

static size_t uz_from_float_fmt_(void *cstr, unsigned n, double f, const struct uffmt *fmt);
static size_t uz_from_float_fmt_len_(unsigned n, double f, const struct uffmt *fmt);
static size_t uz_from_float_fmt_write_(void *cstr, unsigned n, double f, const struct uffmt *fmt);

static size_t uz_from_int_fmt_(void *cstr, unsigned n, uintmax_t i, bool s, const struct uifmt *fmt);
static size_t uz_from_int_fmt_len_(unsigned n, uintmax_t i, bool s, const struct uifmt *fmt);
static size_t uz_from_int_fmt_write_(void *cstr, unsigned n, uintmax_t i, bool s, const struct uifmt *fmt);

static void uz_write_uc8_(void **cstr, unsigned n, uc8_t c, size_t *len, size_t start_from, size_t max_len);
static void uz_write_ucv32_(void **cstr, unsigned n, ucv32_t view, size_t *len, size_t start_from, size_t max_len);

size_t uz32_from_fmt(uc32_t *cstr, const uc32_t *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    size_t res = uz32_from_fmt_v(cstr, fmt, &args);
    va_end(args);
    return res;
}

size_t uz32_from_fmt_v(uc32_t *cstr, const uc32_t *fmt, va_list *args) {
    return uz32_from_fmt_n_v(cstr, fmt, uz32_len(fmt), args);
}

size_t uz32_from_fmt_n(uc32_t *cstr, const uc32_t *fmt, size_t n, ...) {
    va_list args;
    va_start(args, n);
    size_t res = uz32_from_fmt_n_v(cstr, fmt, n, &args);
    va_end(args);
    return res;
}

size_t uz32_from_fmt_n_v(uc32_t *cstr, const uc32_t *fmt_cstr, size_t n, va_list *args) {
    assert(fmt_cstr && args);

    size_t len = 0;

    for (size_t i = 0; i < n;) {
        uc32_t c = fmt_cstr[i++];

        if (U'%' != c || i == n) {
            if (cstr)
                cstr[len++] = c;
            else
                ++len;

            continue;
        }

        struct ufmt fmt = ufmt_from_uz32n(fmt_cstr + i, n - i);

        struct uifmt ifmt;
        struct uffmt ffmt;
        size_t       precision;

        switch (utype_group(fmt.type)) {
            case UTGROUP_INT:
                ifmt = uifmt_from_ufmt(&fmt, args);
                break;

            case UTGROUP_FLOAT:
                ffmt = uffmt_from_ufmt(&fmt, args);
                break;

            case UTGROUP_CHAR:
            case UTGROUP_STR:
                if (fmt.use_precision)
                    precision = fmt.arg_precision ? va_arg(*args, size_t) : fmt.precision;
        }

        switch (fmt.type) {
            case UTYPE_FLOAT: {
                float val = va_arg(*args, double);
                len += uz32_from_float_fmt(cstr ? cstr + len : NULL, val, &ffmt); 
                break;
            }

            case UTYPE_DOUBLE: {
                double val = va_arg(*args, double);
                len += uz32_from_float_fmt(cstr ? cstr + len : NULL, val, &ffmt); 
                break;
            }

            case UTYPE_LDOUBLE: {
                long double val = va_arg(*args, long double);
                len += uz32_from_float_fmt(cstr ? cstr + len : NULL, val, &ffmt); 
                break;
            }

            case UTYPE_SINT: {
                short val = va_arg(*args, int);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_USINT: {
                unsigned short val = va_arg(*args, unsigned);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT: {
                int val = va_arg(*args, int);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT: {
                unsigned val = va_arg(*args, unsigned);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LINT: {
                long val = va_arg(*args, long);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULINT: {
                unsigned long val = va_arg(*args, unsigned long);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LLINT: {
                long long val = va_arg(*args, long long);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULLINT: {
                unsigned long long val = va_arg(*args, unsigned long long);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_8: {
                int8_t val = va_arg(*args, uarg_int8_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_8: {
                uint8_t val = va_arg(*args, uarg_uint8_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_16: {
                int16_t val = va_arg(*args, uarg_int16_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_16: {
                uint16_t val = va_arg(*args, uarg_uint16_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_32: {
                int32_t val = va_arg(*args, uarg_int32_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_32: {
                uint32_t val = va_arg(*args, uarg_uint32_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_64: {
                int64_t val = va_arg(*args, uarg_int64_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_64: {
                uint64_t val = va_arg(*args, uarg_uint64_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_8: {
                int_fast8_t val = va_arg(*args, uarg_int_fast8_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_8: {
                uint_fast8_t val = va_arg(*args, uarg_uint_fast8_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_16: {
                int_fast16_t val = va_arg(*args, uarg_int_fast16_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_16: {
                uint_fast16_t val = va_arg(*args, uarg_uint_fast16_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_32: {
                int_fast32_t val = va_arg(*args, uarg_int_fast32_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_32: {
                uint_fast32_t val = va_arg(*args, uarg_uint_fast32_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_64: {
                int_fast64_t val = va_arg(*args, uarg_int_fast64_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_64: {
                uint_fast64_t val = va_arg(*args, uarg_uint_fast64_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_8: {
                int_least8_t val = va_arg(*args, uarg_int_least8_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_8: {
                uint_least8_t val = va_arg(*args, uarg_uint_least8_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_16: {
                int_least16_t val = va_arg(*args, uarg_int_least16_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_16: {
                uint_least16_t val = va_arg(*args, uarg_uint_least16_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_32: {
                int_least32_t val = va_arg(*args, uarg_int_least32_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_32: {
                uint_least32_t val = va_arg(*args, uarg_uint_least32_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_64: {
                int_least64_t val = va_arg(*args, uarg_int_least64_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_64: {
                uint_least64_t val = va_arg(*args, uarg_uint_least64_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_MAX: {
                intmax_t val = va_arg(*args, intmax_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UMAX: {
                uintmax_t val = va_arg(*args, uintmax_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_PTR: {
                intptr_t val = va_arg(*args, intptr_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UPTR: {
                uintptr_t val = va_arg(*args, uintptr_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_SIZE: {
                size_t val = va_arg(*args, size_t);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_PTRDIFF: {
                ptrdiff_t val = va_arg(*args, ptrdiff_t);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_CHAR: {
                char   val   = va_arg(*args, int);
                size_t count = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count;
                    break;
                }

                while (count--)
                    cstr[len++] = val;

                break;
			}

            case UTYPE_SCHAR: {
                signed char val = va_arg(*args, int);
                len += uz32_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UCHAR: {
                unsigned char val = va_arg(*args, unsigned);
                len += uz32_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_CSTR: {
                const char *val   = va_arg(*args, const char *);
                size_t      count = fmt.use_precision ? precision : strlen(val);
                
                if (!cstr) {
                    len += count;
                    break;
                }
                
                while (count--)
                    cstr[len++] = *val++;
                
                break;
			}

            case UTYPE_BOOL: {
                bool val = va_arg(*args, int);
                len += uz32_from_case_bool(cstr ? cstr + len : NULL, val, fmt.b.char_case);
                break;
			}

            case UTYPE_UC8: {
                uc8_t  val   = va_arg(*args, uarg_uc8_t);
                size_t count = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count;
                    break;
                }

                while (count--)
                    cstr[len++] = val;

                break;
			}

            case UTYPE_UC16: {
                uc16_t val   = va_arg(*args, uarg_uc16_t);
                size_t count = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count;
                    break;
                }

                while (count--)
                    cstr[len++] = val;

                break;
			}

            case UTYPE_UC32: {
                uc32_t val   = va_arg(*args, uarg_uc32_t);
                size_t count = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count;
                    break;
                }

                while (count--)
                    cstr[len++] = val;

                break;
			}

            case UTYPE_UZ8: {
                const uc8_t *val = va_arg(*args, const uc8_t *);

                if (!cstr) {
                    len += fmt.use_precision ? uz8n_len_32(val, precision) 
                                             : uz8_len_32(val);

                    break;
                }

                len += fmt.use_precision ? uz32_from_uz8n(cstr + len, val, precision) 
                                         : uz32_from_uz8(cstr + len, val);

                break;
			}

            case UTYPE_UZ16: {
                const uc16_t *val = va_arg(*args, const uc16_t *);

                if (!cstr) {
                    len += fmt.use_precision ? uz16n_len_32(val, precision) 
                                             : uz16_len_32(val);

                    break;
                }

                len += fmt.use_precision ? uz32_from_uz16n(cstr + len, val, precision) 
                                         : uz32_from_uz16(cstr + len, val);

                break;
			}

            case UTYPE_UZ32: {
                const uc32_t *val   = va_arg(*args, const uc32_t *);
                size_t        count = fmt.use_precision ? precision : uz32_len(val);

                if (!cstr) {
                    len += count;
                    break;
                }

                len += uz32_copy_n(cstr + len, val, count);

                break;
			}

            case UTYPE_US32: {
                const us32_t *val = va_arg(*args, const us32_t *);
                size_t        count;

                if (fmt.use_precision) {
                    assert(us32_ebounds(val, precision));
                    count = precision;
                } else
                    count = us32_len(val);
                
                if (!cstr) {
                    len += count;
                    break;
                }

                len += uz32_copy_n(cstr + len, us32_cchars(val), count);
                
                break;
			}

            case UTYPE_UV32: {
                uv32_t val = va_arg(*args, uv32_t);
                size_t count;

                if (fmt.use_precision) {
                    assert(uv32_ebounds(val, precision));
                    count = precision;
                } else
                    count = uv32_len(val);
                
                if (!cstr) {
                    len += count;
                    break;
                }

                len += uz32_copy_n(cstr + len, uv32_cchars(val), count);

                break;
			}

            case UTYPE_UCV32: {
                ucv32_t val = va_arg(*args, ucv32_t);
                size_t  count;

                if (fmt.use_precision) {
                    assert(ucv32_ebounds(val, precision));
                    count = precision;
                } else
                    count = ucv32_len(val);
                
                if (!cstr) {
                    len += count;
                    break;
                }

                len += uz32_copy_n(cstr + len, ucv32_cchars(val), count);

                break;
			}

            case UTYPE_CUSTOM: {
                uz_from_t val = va_arg(*args, uz_from_t);
                len += val(cstr ? cstr + len : NULL, 4, &fmt, args);
                break;
			}

            case UTYPE_UNKNOWN: {
                if (cstr)
                    cstr[len++] = c;
                else
                    ++len;

                continue;
			}

            default:
                assert(false);
        }

        i += fmt.len;
    }

    return len;
}

size_t uz16_from_fmt(uc16_t *cstr, const uc16_t *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    size_t res = uz16_from_fmt_v(cstr, fmt, &args);
    va_end(args);
    return res;
}

size_t uz16_from_fmt_v(uc16_t *cstr, const uc16_t *fmt, va_list *args) {
    return uz16_from_fmt_n_v(cstr, fmt, uz16_len(fmt), args);
}

size_t uz16_from_fmt_n(uc16_t *cstr, const uc16_t *fmt, size_t n, ...) {
    va_list args;
    va_start(args, n);
    size_t res = uz16_from_fmt_n_v(cstr, fmt, n, &args);
    va_end(args);
    return res;
}

size_t uz16_from_fmt_n_v(uc16_t *cstr, const uc16_t *fmt_cstr, size_t n, va_list *args) {
    assert(fmt_cstr && args);

    size_t len = 0;

    for (size_t i = 0; i < n;) {
        uc16_t c = fmt_cstr[i++];

        if (U'%' != c || i == n) {
            if (cstr)
                cstr[len++] = c;
            else
                ++len;

            continue;
        }

        struct ufmt fmt = ufmt_from_uz16n(fmt_cstr + i, n - i);

        struct uifmt ifmt;
        struct uffmt ffmt;
        size_t       precision;

        switch (utype_group(fmt.type)) {
            case UTGROUP_INT:
                ifmt = uifmt_from_ufmt(&fmt, args);
                break;

            case UTGROUP_FLOAT:
                ffmt = uffmt_from_ufmt(&fmt, args);
                break;

            case UTGROUP_CHAR:
            case UTGROUP_STR:
                if (fmt.use_precision)
                    precision = fmt.arg_precision ? va_arg(*args, size_t) : fmt.precision;
        }

        switch (fmt.type) {
            case UTYPE_FLOAT: {
                float val = va_arg(*args, double);
                len += uz16_from_float_fmt(cstr ? cstr + len : NULL, val, &ffmt); 
                break;
            }

            case UTYPE_DOUBLE: {
                double val = va_arg(*args, double);
                len += uz16_from_float_fmt(cstr ? cstr + len : NULL, val, &ffmt); 
                break;
            }

            case UTYPE_LDOUBLE: {
                long double val = va_arg(*args, long double);
                len += uz16_from_float_fmt(cstr ? cstr + len : NULL, val, &ffmt); 
                break;
            }

            case UTYPE_SINT: {
                short val = va_arg(*args, int);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_USINT: {
                unsigned short val = va_arg(*args, unsigned);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT: {
                int val = va_arg(*args, int);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT: {
                unsigned val = va_arg(*args, unsigned);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LINT: {
                long val = va_arg(*args, long);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULINT: {
                unsigned long val = va_arg(*args, unsigned long);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LLINT: {
                long long val = va_arg(*args, long long);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULLINT: {
                unsigned long long val = va_arg(*args, unsigned long long);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_8: {
                int8_t val = va_arg(*args, uarg_int8_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_8: {
                uint8_t val = va_arg(*args, uarg_uint8_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_16: {
                int16_t val = va_arg(*args, uarg_int16_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_16: {
                uint16_t val = va_arg(*args, uarg_uint16_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_32: {
                int32_t val = va_arg(*args, uarg_int32_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_32: {
                uint32_t val = va_arg(*args, uarg_uint32_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_64: {
                int64_t val = va_arg(*args, uarg_int64_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_64: {
                uint64_t val = va_arg(*args, uarg_uint64_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_8: {
                int_fast8_t val = va_arg(*args, uarg_int_fast8_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_8: {
                uint_fast8_t val = va_arg(*args, uarg_uint_fast8_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_16: {
                int_fast16_t val = va_arg(*args, uarg_int_fast16_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_16: {
                uint_fast16_t val = va_arg(*args, uarg_uint_fast16_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_32: {
                int_fast32_t val = va_arg(*args, uarg_int_fast32_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_32: {
                uint_fast32_t val = va_arg(*args, uarg_uint_fast32_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_64: {
                int_fast64_t val = va_arg(*args, uarg_int_fast64_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_64: {
                uint_fast64_t val = va_arg(*args, uarg_uint_fast64_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_8: {
                int_least8_t val = va_arg(*args, uarg_int_least8_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_8: {
                uint_least8_t val = va_arg(*args, uarg_uint_least8_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_16: {
                int_least16_t val = va_arg(*args, uarg_int_least16_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_16: {
                uint_least16_t val = va_arg(*args, uarg_uint_least16_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_32: {
                int_least32_t val = va_arg(*args, uarg_int_least32_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_32: {
                uint_least32_t val = va_arg(*args, uarg_uint_least32_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_64: {
                int_least64_t val = va_arg(*args, uarg_int_least64_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_64: {
                uint_least64_t val = va_arg(*args, uarg_uint_least64_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_MAX: {
                intmax_t val = va_arg(*args, intmax_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UMAX: {
                uintmax_t val = va_arg(*args, uintmax_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_PTR: {
                intptr_t val = va_arg(*args, intptr_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UPTR: {
                uintptr_t val = va_arg(*args, uintptr_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_SIZE: {
                size_t val = va_arg(*args, size_t);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_PTRDIFF: {
                ptrdiff_t val = va_arg(*args, ptrdiff_t);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_CHAR: {
                char   val   = va_arg(*args, int);
                size_t count = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count;
                    break;
                }

                while (count--)
                    cstr[len++] = val;

                break;
			}

            case UTYPE_SCHAR: {
                signed char val = va_arg(*args, int);
                len += uz16_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UCHAR: {
                unsigned char val = va_arg(*args, unsigned);
                len += uz16_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_CSTR: {
                const char *val   = va_arg(*args, const char *);
                size_t      count = fmt.use_precision ? precision : strlen(val);
                
                if (!cstr) {
                    len += count;
                    break;
                }
                
                while (count--)
                    cstr[len++] = *val++;
                
                break;
			}

            case UTYPE_BOOL: {
                bool val = va_arg(*args, int);
                len += uz16_from_case_bool(cstr ? cstr + len : NULL, val, fmt.b.char_case);
                break;
			}

            case UTYPE_UC8: {
                uc8_t  val   = va_arg(*args, uarg_uc8_t);
                size_t count = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count;
                    break;
                }

                while (count--)
                    cstr[len++] = val;

                break;
			}

            case UTYPE_UC16: {
                uc16_t val   = va_arg(*args, uarg_uc16_t);
                size_t count = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count;
                    break;
                }

                while (count--)
                    cstr[len++] = val;

                break;
			}

            case UTYPE_UC32: {
                uc32_t   val     = va_arg(*args, uarg_uc32_t);
                uc16_t   c16[2];
                unsigned c16_len = uc16_from_uc32(c16, val);
                size_t   count   = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += c16_len * count;
                    break;
                }

                while (count--)
                    for (unsigned i = 0; i < c16_len; ++i)
                        cstr[len++] = c16[i];

                break;
			}

            case UTYPE_UZ8: {
                const uc8_t *val = va_arg(*args, const uc8_t *);

                if (!cstr) {
                    len += fmt.use_precision ? uz8n_len_16(val, precision) 
                                             : uz8_len_16(val);

                    break;
                }

                len += fmt.use_precision ? uz16_from_uz8n(cstr + len, val, precision) 
                                         : uz16_from_uz8(cstr + len, val);

                break;
			}

            case UTYPE_UZ16: {
                const uc16_t *val   = va_arg(*args, const uc16_t *);
                size_t        count = fmt.use_precision ? precision : uz16_len(val);

                if (!cstr) {
                    len += count;
                    break;
                }

                len += uz16_copy_n(cstr + len, val, count);

                break;
			}

            case UTYPE_UZ32: {
                const uc32_t *val = va_arg(*args, const uc32_t *);

                if (!cstr) {
                    len += fmt.use_precision ? uz32n_len_16(val, precision) 
                                             : uz32_len_16(val);

                    break;
                }

                len += fmt.use_precision ? uz16_from_uz32n(cstr + len, val, precision)
                                         : uz16_from_uz32(cstr + len, val);

                break;
			}

            case UTYPE_US32: {
                const us32_t *val = va_arg(*args, const us32_t *);
                
                if (!cstr) {
                    len += fmt.use_precision ? us32_len_16_to(val, precision)
                                             : us32_len_16(val);

                    break;
                }

                if (fmt.use_precision) {
                    assert(us32_ebounds(val, precision));
                    len += uz16_from_uz32n(cstr + len, us32_cchars(val), precision);
                    break;
                }

                len += uz16_from_uz32n(cstr + len, US32_CEXPAND(val));
                
                break;
			}

            case UTYPE_UV32: {
                uv32_t val = va_arg(*args, uv32_t);

                if (!cstr) {
                    len += fmt.use_precision ? uv32_len_16_to(val, precision)
                                             : uv32_len_16(val);

                    break;
                }

                if (fmt.use_precision) {
                    assert(uv32_ebounds(val, precision));
                    len += uz16_from_uz32n(cstr + len, uv32_cchars(val), precision);
                    break;
                }

                len += uz16_from_uz32n(cstr + len, UV32_CEXPAND(val));

                break;
			}

            case UTYPE_UCV32: {
                ucv32_t val = va_arg(*args, ucv32_t);

                if (!cstr) {
                    len += fmt.use_precision ? ucv32_len_16_to(val, precision)
                                             : ucv32_len_16(val);

                    break;
                }

                if (fmt.use_precision) {
                    assert(ucv32_ebounds(val, precision));
                    len += uz16_from_uz32n(cstr + len, ucv32_cchars(val), precision);
                    break;
                }

                len += uz16_from_uz32n(cstr + len, UCV32_CEXPAND(val));

                break;
			}

            case UTYPE_CUSTOM: {
                uz_from_t val = va_arg(*args, uz_from_t);
                len += val(cstr ? cstr + len : NULL, 2, &fmt, args);
                break;
			}

            case UTYPE_UNKNOWN: {
                if (cstr)
                    cstr[len++] = c;
                else
                    ++len;

                continue;
			}

            default:
                assert(false);
        }

        i += fmt.len;
    }

    return len;
}

size_t uz8_from_fmt(uc8_t *cstr, const uc8_t *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    size_t res = uz8_from_fmt_v(cstr, fmt, &args);
    va_end(args);
    return res;
}

size_t uz8_from_fmt_v(uc8_t *cstr, const uc8_t *fmt, va_list *args) {
    return uz8_from_fmt_n_v(cstr, fmt, uz8_len(fmt), args);
}

size_t uz8_from_fmt_n(uc8_t *cstr, const uc8_t *fmt, size_t n, ...) {
    va_list args;
    va_start(args, n);
    size_t res = uz8_from_fmt_n_v(cstr, fmt, n, &args);
    va_end(args);
    return res;
}

size_t uz8_from_fmt_n_v(uc8_t *cstr, const uc8_t *fmt_cstr, size_t n, va_list *args) {
    assert(fmt_cstr && args);

    size_t len = 0;

    for (size_t i = 0; i < n;) {
        uc8_t c = fmt_cstr[i++];

        if (U'%' != c || i == n) {
            if (cstr)
                cstr[len++] = c;
            else
                ++len;

            continue;
        }

        struct ufmt fmt = ufmt_from_uz8n(fmt_cstr + i, n - i);

        struct uifmt ifmt;
        struct uffmt ffmt;
        size_t       precision;

        switch (utype_group(fmt.type)) {
            case UTGROUP_INT:
                ifmt = uifmt_from_ufmt(&fmt, args);
                break;

            case UTGROUP_FLOAT:
                ffmt = uffmt_from_ufmt(&fmt, args);
                break;

            case UTGROUP_CHAR:
            case UTGROUP_STR:
                if (fmt.use_precision)
                    precision = fmt.arg_precision ? va_arg(*args, size_t) : fmt.precision;
        }

        switch (fmt.type) {
            case UTYPE_FLOAT: {
                float val = va_arg(*args, double);
                len += uz8_from_float_fmt(cstr ? cstr + len : NULL, val, &ffmt); 
                break;
            }

            case UTYPE_DOUBLE: {
                double val = va_arg(*args, double);
                len += uz8_from_float_fmt(cstr ? cstr + len : NULL, val, &ffmt); 
                break;
            }

            case UTYPE_LDOUBLE: {
                long double val = va_arg(*args, long double);
                len += uz8_from_float_fmt(cstr ? cstr + len : NULL, val, &ffmt); 
                break;
            }

            case UTYPE_SINT: {
                short val = va_arg(*args, int);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_USINT: {
                unsigned short val = va_arg(*args, unsigned);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT: {
                int val = va_arg(*args, int);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT: {
                unsigned val = va_arg(*args, unsigned);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LINT: {
                long val = va_arg(*args, long);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULINT: {
                unsigned long val = va_arg(*args, unsigned long);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LLINT: {
                long long val = va_arg(*args, long long);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULLINT: {
                unsigned long long val = va_arg(*args, unsigned long long);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_8: {
                int8_t val = va_arg(*args, uarg_int8_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_8: {
                uint8_t val = va_arg(*args, uarg_uint8_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_16: {
                int16_t val = va_arg(*args, uarg_int16_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_16: {
                uint16_t val = va_arg(*args, uarg_uint16_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_32: {
                int32_t val = va_arg(*args, uarg_int32_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_32: {
                uint32_t val = va_arg(*args, uarg_uint32_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_INT_64: {
                int64_t val = va_arg(*args, uarg_int64_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UINT_64: {
                uint64_t val = va_arg(*args, uarg_uint64_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_8: {
                int_fast8_t val = va_arg(*args, uarg_int_fast8_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_8: {
                uint_fast8_t val = va_arg(*args, uarg_uint_fast8_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_16: {
                int_fast16_t val = va_arg(*args, uarg_int_fast16_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_16: {
                uint_fast16_t val = va_arg(*args, uarg_uint_fast16_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_32: {
                int_fast32_t val = va_arg(*args, uarg_int_fast32_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_32: {
                uint_fast32_t val = va_arg(*args, uarg_uint_fast32_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_FAST_64: {
                int_fast64_t val = va_arg(*args, uarg_int_fast64_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UFAST_64: {
                uint_fast64_t val = va_arg(*args, uarg_uint_fast64_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_8: {
                int_least8_t val = va_arg(*args, uarg_int_least8_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_8: {
                uint_least8_t val = va_arg(*args, uarg_uint_least8_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_16: {
                int_least16_t val = va_arg(*args, uarg_int_least16_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_16: {
                uint_least16_t val = va_arg(*args, uarg_uint_least16_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_32: {
                int_least32_t val = va_arg(*args, uarg_int_least32_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_32: {
                uint_least32_t val = va_arg(*args, uarg_uint_least32_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_LEAST_64: {
                int_least64_t val = va_arg(*args, uarg_int_least64_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_ULEAST_64: {
                uint_least64_t val = va_arg(*args, uarg_uint_least64_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_MAX: {
                intmax_t val = va_arg(*args, intmax_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UMAX: {
                uintmax_t val = va_arg(*args, uintmax_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_PTR: {
                intptr_t val = va_arg(*args, intptr_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UPTR: {
                uintptr_t val = va_arg(*args, uintptr_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_SIZE: {
                size_t val = va_arg(*args, size_t);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_PTRDIFF: {
                ptrdiff_t val = va_arg(*args, ptrdiff_t);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_CHAR: {
                char val     = va_arg(*args, int);
                size_t count = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count;
                    break;
                }

                while (count--)
                    cstr[len++] = val;

                break;
			}

            case UTYPE_SCHAR: {
                signed char val = va_arg(*args, int);
                len += uz8_from_int_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_UCHAR: {
                unsigned char val = va_arg(*args, unsigned);
                len += uz8_from_uint_fmt(cstr ? cstr + len : NULL, val, &ifmt);
                break;
			}

            case UTYPE_CSTR: {
                const char *val   = va_arg(*args, const char *);
                size_t      count = fmt.use_precision ? precision : strlen(val);
                
                if (!cstr) {
                    len += count;
                    break;
                }

                while (count--)
                    cstr[len++] = *val++;
                
                break;
			}

            case UTYPE_BOOL: {
                bool val = va_arg(*args, int);
                len += uz8_from_case_bool(cstr ? cstr + len : NULL, val, fmt.b.char_case);
                break;
			}

            case UTYPE_UC8: {
                uc8_t val    = va_arg(*args, uarg_uc8_t);
                size_t count = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count;
                    break;
                }

                while (count--)
                    cstr[len++] = val;

                break;
			}

            case UTYPE_UC16: {
                uc16_t val = va_arg(*args, uarg_uc16_t);

                uc16_t c16[2] = { val, 0 };

                uc8_t    c8[4];
                unsigned c8_len = uc8_from_uc16(c8, c16);
                size_t   count  = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count * c8_len;
                    break;
                }

                while (count--)
                    for (size_t i = 0; i < c8_len; ++i)
                        cstr[len++] = c8[i];

                break;
			}

            case UTYPE_UC32: {
                uc32_t val = va_arg(*args, uarg_uc32_t);

                uc8_t    c8[4];
                unsigned c8_len = uc8_from_uc32(c8, val);
                size_t   count  = fmt.use_precision ? precision : 1;

                if (!cstr) {
                    len += count * c8_len;
                    break;
                }

                while (count--)
                    for (size_t i = 0; i < count; ++i)
                        cstr[len++] = c8[i];

                break;
			}

            case UTYPE_UZ8: {
                const uc8_t *val   = va_arg(*args, const uc8_t *);
                size_t       count = fmt.use_precision ? precision : uz8_len(val);

                if (!cstr) {
                    len += count;
                    break;
                }

                len += uz8_copy_n(cstr + len, val, count);

                break;
			}

            case UTYPE_UZ16: {
                const uc16_t *val = va_arg(*args, const uc16_t *);

                if (!cstr) {
                    len += fmt.use_precision ? uz16n_len_8(val, precision) 
                                             : uz16_len_8(val);

                    break;
                }

                len += fmt.use_precision ? uz8_from_uz16n(cstr + len, val, precision)
                                         : uz8_from_uz16(cstr + len, val);

                break;
			}

            case UTYPE_UZ32: {
                const uc32_t *val = va_arg(*args, const uc32_t *);

                if (!cstr) {
                    len += fmt.use_precision ? uz32n_len_8(val, precision)
                                             : uz32_len_8(val);

                    break;
                }

                len += fmt.use_precision ? uz8_from_uz32n(cstr + len, val, precision)
                                         : uz8_from_uz32(cstr + len, val);

                break;
			}

            case UTYPE_US32: {
                const us32_t *val = va_arg(*args, const us32_t *);
                
                if (!cstr) {
                    len += fmt.use_precision ? us32_len_8_to(val, precision)
                                             : us32_len_8(val);

                    break;
                }

                if (fmt.use_precision) {
                    assert(us32_ebounds(val, precision));
                    len += uz8_from_uz32n(cstr + len, us32_cchars(val), precision);
                    break;
                }

                len += uz8_from_uz32n(cstr + len, US32_CEXPAND(val));
                
                break;
			}

            case UTYPE_UV32: {
                uv32_t val = va_arg(*args, uv32_t);

                if (!cstr) {
                    len += fmt.use_precision ? uv32_len_8_to(val, precision)
                                             : uv32_len_8(val);

                    break;
                }

                if (fmt.use_precision) {
                    assert(uv32_ebounds(val, precision));
                    len += uz8_from_uz32n(cstr + len, uv32_cchars(val), precision);
                    break;
                }

                len += uz8_from_uz32n(cstr + len, UV32_CEXPAND(val));

                break;
			}

            case UTYPE_UCV32: {
                ucv32_t val = va_arg(*args, ucv32_t);

                if (!cstr) {
                    len += fmt.use_precision ? ucv32_len_8_to(val, precision)
                                             : ucv32_len_8(val);

                    break;
                }

                if (fmt.use_precision) {
                    assert(ucv32_ebounds(val, precision));
                    len += uz8_from_uz32n(cstr + len, ucv32_cchars(val), precision);
                    break;
                }

                len += uz8_from_uz32n(cstr + len, UCV32_CEXPAND(val));

                break;
			}

            case UTYPE_CUSTOM: {
                uz_from_t val = va_arg(*args, uz_from_t);
                len += val(cstr ? cstr + len : NULL, 1, &fmt, args);
                break;
			}

            case UTYPE_UNKNOWN: {
                if (cstr)
                    cstr[len++] = c;
                else
                    ++len;

                continue;
			}

            default:
                assert(false);
        }

        i += fmt.len;
    }

    return len;
}

size_t uz32_from_float(uc32_t *cstr, double f) {
    return uz32_from_float_fmt(cstr, f, &UFFMT);
}

size_t uz32_from_float_fmt(uc32_t *cstr, double f, const struct uffmt *fmt) {
    return uz_from_float_fmt_(cstr, 4, f, fmt);
}

size_t uz16_from_float(uc16_t *cstr, double f) {
    return uz16_from_float_fmt(cstr, f, &UFFMT);
}

size_t uz16_from_float_fmt(uc16_t *cstr, double f, const struct uffmt *fmt) {
    return uz_from_float_fmt_(cstr, 2, f, fmt);
}

size_t uz8_from_float(uc8_t *cstr, double f) {
    return uz8_from_float_fmt(cstr, f, &UFFMT);
}

size_t uz8_from_float_fmt(uc8_t *cstr, double f, const struct uffmt *fmt) {
    return uz_from_float_fmt_(cstr, 1, f, fmt);
}

size_t uz_from_float_fmt_(void *cstr, unsigned n, double f, const struct uffmt *fmt) {
    assert(uffmt_valid(fmt));
    return cstr ? uz_from_float_fmt_write_(cstr, n, f, fmt) : uz_from_float_fmt_len_(n, f, fmt);
}

size_t uz_from_float_fmt_len_(unsigned n, double f, const struct uffmt *fmt) {
    size_t len = 0;

    // NaN

    if (isnan(f)) {
        len += ucv32_len_n(fmt->nan, n);
        goto exit;
    } 
    
    // Sign
    
    if (f < 0 && fmt->show_minus || f >= 0 && fmt->show_plus)
        ++len;
    
    // Inf

    if (isinf(f)) {
        len += ucv32_len_n(fmt->inf, n);
        goto exit;
    }

    // Finite

    // TODO
    len += 3; // 0.0

exit:
    return len > fmt->start_from ? len - fmt->start_from : 0;
}

size_t uz_from_float_fmt_write_(void *cstr, unsigned n, double f, const struct uffmt *fmt) {
    void  *init_cstr = cstr;
    size_t len       = 0;

    // NaN

    if (isnan(f)) {
        uz_write_ucv32_(&cstr, n, fmt->nan, &len, fmt->start_from, fmt->max_len);
        goto exit;
    }

    // Sign

    if (f < 0) {
        if (fmt->show_minus)
            uz_write_uc8_(&cstr, n, '-', &len, fmt->start_from, fmt->max_len);
    } else if (fmt->show_plus)
        uz_write_uc8_(&cstr, n, '+', &len, fmt->start_from, fmt->max_len);

    // Inf

    if (isinf(f)) {
        uz_write_ucv32_(&cstr, n, fmt->inf, &len, fmt->start_from, fmt->max_len);
        goto exit;
    }

    // Finite

    // TODO
    uz_write_ucv32_(&cstr, n, ucv32("0.0"), &len, fmt->start_from, fmt->max_len);

exit:
    return (cstr - init_cstr) / n;
}

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
    // Prepare

    size_t len = 0;
    bool   neg = s && (intmax_t) i < 0;

    if (neg)
        i = -i;

    // Count digits

    do {
        i /= fmt->radix;
        ++len;
    } while (i);

    // Count leading zeroes

    if (fmt->leading_zeroes_limit > len)
        len += fmt->leading_zeroes_limit - len;

    // Count separators

    if (fmt->group_size && fmt->group_size < len) {
        int sep_count = (len - 1) / fmt->group_size;
        len += sep_count * ucv32_len_n(fmt->group_separator, n);
    }

    // Count sign

    if (neg && fmt->show_minus || !neg && fmt->show_plus)
        ++len;

    // Count radix prefix

    if (fmt->show_radix_prefix && uradix_has_prefix(fmt->radix)) {
        ucv32_t prefix = uradix_prefix(fmt->radix, fmt->radix_prefix_case);
        len += ucv32_len_n(prefix, n);
    }

    // Take in account start_from

    return len > fmt->start_from ? len - fmt->start_from : 0;
}

size_t uz_from_int_fmt_write_(void *cstr, unsigned n, uintmax_t i, bool s, const struct uifmt *fmt) {
    void *init_cstr = cstr;

    // Save sign and make unsigned if needed

    bool neg = s && (intmax_t) i < 0;

    if (neg)
        i = -i;

    // Create digit buffer

    enum {
        MAX_DIGITS = CHAR_BIT * sizeof(intmax_t)
    };

    uc8_t  digits[MAX_DIGITS];
    size_t digit_count = 0;

    // Fill digit buffer

    do {
        digits[digit_count++] = uc32_case_radix_from_val(fmt->digit_case, fmt->radix, i % fmt->radix);
        i /= fmt->radix;
    } while (i);

    // Apply precision

    if (fmt->precision && digit_count > fmt->precision)
        uz8n_fill_uc8(digits, digit_count - fmt->precision, '0');

    // Write sign

    size_t len = 0;

    if (neg) {
        if (fmt->show_minus)
            uz_write_uc8_(&cstr, n, '-', &len, fmt->start_from, fmt->max_len);
    } else if (fmt->show_plus) 
        uz_write_uc8_(&cstr, n, '+', &len, fmt->start_from, fmt->max_len);

    // Write radix prefix

    if (fmt->show_radix_prefix && uradix_has_prefix(fmt->radix)) {
        ucv32_t prefix = uradix_prefix(fmt->radix, fmt->radix_prefix_case);
        uz_write_ucv32_(&cstr, n, prefix, &len, fmt->start_from, fmt->max_len);
    }

    // Write leading zeroes

    size_t digit_num = digit_count - 1;

    if (fmt->leading_zeroes_limit > digit_count) {
        size_t zero_count = fmt->leading_zeroes_limit - digit_count;

        digit_num += zero_count;

        for (; zero_count--; --digit_num) {
            uz_write_uc8_(&cstr, n, '0', &len, fmt->start_from, fmt->max_len);

            if (fmt->group_size && digit_num % fmt->group_size == 0)
                uz_write_ucv32_(&cstr, n, fmt->group_separator, &len, fmt->start_from, fmt->max_len);
        }
    }

    // Write digits with separators

    for (size_t i = digit_count - 1;; --i, --digit_num) {
        uz_write_uc8_(&cstr, n, digits[i], &len, fmt->start_from, fmt->max_len);

        if (!i)
            break;

        if (fmt->group_size && digit_num % fmt->group_size == 0)
            uz_write_ucv32_(&cstr, n, fmt->group_separator, &len, fmt->start_from, fmt->max_len);
    }

    return (cstr - init_cstr) / n;
}

void uz_write_uc8_(void **cstr, unsigned n, uc8_t c, size_t *len, size_t start_from, size_t max_len) {
    if (start_from <= *len && *len < max_len)
        switch (n) {
            case 1:
                *((uc8_t *) *cstr) = c;
                *cstr += sizeof(uc8_t);
                break;

            case 2:
                *((uc16_t *) *cstr) = c;
                *cstr += sizeof(uc16_t);
                break;

            case 4:
                *((uc32_t *) *cstr) = c;
                *cstr += sizeof(uc32_t);
                break;

            default:
                assert(false);
                return;
        }

    ++*len;
}

void uz_write_ucv32_(void **cstr, unsigned n, ucv32_t view, size_t *len, size_t start_from, size_t max_len) {
    switch (n) {
        case 1:
            for (const uc32_t *it = ucv32_cbegin(view), *end = ucv32_cend(view); it != end; ++it) {
                if (start_from <= *len && *len < max_len) {
                    unsigned c8_len = uc8_from_uc32(*cstr, *it);

                    *cstr += c8_len * sizeof(uc8_t);
                    *len  += c8_len;
                } else
                    *len += uc32_len_8(*it);
            }

            break;

        case 2:
            for (const uc32_t *it = ucv32_cbegin(view), *end = ucv32_cend(view); it != end; ++it) 
                if (start_from <= *len && *len < max_len) {
                    unsigned c16_len = uc16_from_uc32(*cstr, *it);

                    *cstr += c16_len * sizeof(uc16_t);
                    *len  += c16_len;
                } else
                    *len += uc32_len_16(*it);

            break;

        case 4: 
            for (const uc32_t *it = ucv32_cbegin(view), *end = ucv32_cend(view); it != end; ++it) {
                if (start_from <= *len && *len < max_len) {
                    *((uc32_t *) *cstr) = *it;
                    *cstr += sizeof(uc32_t);
                }

                ++*len;
            }

            break;

        default:
            assert(false);
    }
}

size_t uz32_from_bool(uc32_t *cstr, bool b) {
    return uz32_from_lower_bool(cstr, b);
}

size_t uz32_from_case_bool(uc32_t *cstr, bool b, ucase_t c) {
    return ucase_upper(c) ? uz32_from_upper_bool(cstr, b) : uz32_from_lower_bool(cstr, b);
}

size_t uz32_from_upper_bool(uc32_t *cstr, bool b) {
    if (cstr)
        uz32_copy(cstr, b ? uz32("TRUE") : uz32("FALSE"));

    return b ? 4 : 5;
}

size_t uz32_from_lower_bool(uc32_t *cstr, bool b) {
    if (cstr)
        uz32_copy(cstr, b ? uz32("true") : uz32("false"));

    return b ? 4 : 5;
}

size_t uz16_from_bool(uc16_t *cstr, bool b) {
    return uz16_from_lower_bool(cstr, b);
}

size_t uz16_from_case_bool(uc16_t *cstr, bool b, ucase_t c) {
    return ucase_upper(b) ? uz16_from_upper_bool(cstr, b) : uz16_from_lower_bool(cstr, b);
}

size_t uz16_from_upper_bool(uc16_t *cstr, bool b) {
    if (cstr)
        uz16_copy(cstr, b ? uz16("TRUE") : uz16("FALSE"));

    return b ? 4 : 5;
}

size_t uz16_from_lower_bool(uc16_t *cstr, bool b) {
    if (cstr)
        uz16_copy(cstr, b ? uz16("true") : uz16("false"));

    return b ? 4 : 5;
}

size_t uz8_from_bool(uc8_t *cstr, bool b) {
    return uz8_from_lower_bool(cstr, b);
}

size_t uz8_from_case_bool(uc8_t *cstr, bool b, ucase_t c) {
    return ucase_upper(c) ? uz8_from_upper_bool(cstr, b) : uz8_from_lower_bool(cstr, b);
}

size_t uz8_from_upper_bool(uc8_t *cstr, bool b) {
    if (cstr)
        uz8_copy(cstr, b ? uz8("TRUE") : uz8("FALSE"));

    return b ? 4 : 5;
}

size_t uz8_from_lower_bool(uc8_t *cstr, bool b) {
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

size_t uz8n_trail(const uc8_t *cstr, size_t n) {
    assert(cstr);

    size_t count = 0;

    while (n-- && uc8_trail(*cstr++))
        ++count;

    return count;
}

size_t uz32_advance(const uc32_t *cstr, size_t n) {
    assert(cstr);
    return n;
}

size_t uz16_advance(const uc16_t *cstr, size_t n) {
    assert(cstr);

    size_t res = 0;

    while (n--)
        res += uc16_len(cstr[res]);

    return res;
}

size_t uz8_advance(const uc8_t *cstr, size_t n) {
    assert(cstr);

    size_t res = 0;

    while (n--)
        res += uc8_len(cstr[res]);

    return res;
}

size_t uz32_retreat(const uc32_t *cstr, size_t n) {
    assert(cstr);
    return n;
}

size_t uz16_retreat(const uc16_t *cstr, size_t n) {
    assert(cstr);

    size_t res = 0;

    while (n--)
        res += uc16_srgt_high(cstr[res - 1]) ? 2 : 1;

    return res;
}

size_t uz8_retreat(const uc8_t *cstr, size_t n) {
    assert(cstr);

    size_t res = 0;

    while (n--) {
        --cstr;
        ++res;

        while (uc8_trail(*cstr)) {
            --cstr;
            ++res;
        }
    }

    return res;
}

size_t uz32_from_uz8(uc32_t *to, const uc8_t *from) {
    return uz32_from_uz8n(to, from, uz8_len(from));
}

size_t uz32_from_uz8n(uc32_t *to, const uc8_t *from, size_t n) {
    assert(from);

    if (!to)
        return uz8n_len_32(from, n);

    size_t len = 0;

    for (size_t i = 0; i < n;) {
        to[len++] = uc32_from_uc8(from + i);
        i        += uc8_len(from[i]);
    }

	return len;
}

size_t uz32_from_uz16(uc32_t *to, const uc16_t *from) {
    return uz32_from_uz16n(to, from, uz16_len(from));
}

size_t uz32_from_uz16n(uc32_t *to, const uc16_t *from, size_t n) {
    assert(from);
 
    if (!to)
        return uz16n_len_32(from, n);
 
    size_t len = 0;

    for (size_t i = 0; i < n;) {
        to[len++] = uc32_from_uc16(from + i);
        i        += uc16_len(from[i]);
    }

	return len;
}

size_t uz16_from_uz8(uc16_t *to, const uc8_t *from) {
    return uz16_from_uz8n(to, from, uz8_len(from));
}

size_t uz16_from_uz8n(uc16_t *to, const uc8_t *from, size_t n) {
    assert(from);

    if (!to)
        return uz8n_len_16(from, n);

    size_t len = 0;

    for (size_t i = 0; i < n;) {
        len += uc16_from_uc8(to + len, from + i);
        i   += uc8_len(from[i]);
    }

	return len;
}

size_t uz16_from_uz32(uc16_t *to, const uc32_t *from) {
    assert(from);

    if (!to)
        return uz32_len_16(from);

    size_t len = 0;

    while (*from)
        len += uc16_from_uc32(to + len, *from++);

	return len;
}

size_t uz16_from_uz32n(uc16_t *to, const uc32_t *from, size_t n) {
    assert(from);

    if (!to)
        return uz32n_len_16(from, n);

    size_t len = 0;

    while (n--)
        len += uc16_from_uc32(to + len, *from++);

	return len;
}

size_t uz8_from_uz16(uc8_t *to, const uc16_t *from) {
    return uz8_from_uz16n(to, from, uz16_len(from));
}

size_t uz8_from_uz16n(uc8_t *to, const uc16_t *from, size_t n) {
    assert(from);

    if (!to)
        return uz16n_len_8(from, n);

    size_t len = 0;

    for (size_t i = 0; i < n;) {
        len += uc8_from_uc16(to + len, from + i);
        i   += uc16_len(from[i]);
    }

	return len;
}

size_t uz8_from_uz32(uc8_t *to, const uc32_t *from) {
    assert(from);

    if (!to)
        return uz32_len_8(from);

    size_t len = 0;

    while (*from)
        len += uc8_from_uc32(to + len, *from++);

	return len;
}

size_t uz8_from_uz32n(uc8_t *to, const uc32_t *from, size_t n) {
    assert(from);

    if (!to)
        return uz32n_len_8(from, n);

    size_t len = 0;

    while (n--)
        len += uc8_from_uc32(to + len, *from++);

	return len;
}

size_t uz32_len_n(const uc32_t *cstr, unsigned n) {
    assert(cstr);

    switch (n) {
        case 1:
            return uz32_len_8(cstr);

        case 2:
            return uz32_len_16(cstr);

        case 4:
            return uz32_len_32(cstr);

        default:
            assert(false);
            return 0;
    }
}

size_t uz32n_len_n(const uc32_t *cstr, size_t cstr_len, unsigned n) {
    assert(cstr);

    switch (n) {
        case 1:
            return uz32n_len_8(cstr, cstr_len);

        case 2:
            return uz32n_len_16(cstr, cstr_len);

        case 4:
            return uz32n_len_32(cstr, cstr_len);

        default:
            assert(false);
            return 0;
    }
}

size_t uz32_len_8(const uc32_t *cstr) {
    assert(cstr);

    size_t len = 0;

    while (*cstr)
        len += uc32_len_8(*cstr++);

    return len;
}

size_t uz32n_len_8(const uc32_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    while (n--)
        len += uc32_len_8(*cstr++);

    return len;
}

size_t uz32_len_16(const uc32_t *cstr) {
    assert(cstr);

    size_t len = 0;

    while (*cstr)
        len += uc32_len_16(*cstr++);

    return len;
}

size_t uz32n_len_16(const uc32_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    while (n--)
        len += uc32_len_16(*cstr++);

    return len;
}

size_t uz32_len_32(const uc32_t *cstr) {
    return uz32_len(cstr);
}

size_t uz32n_len_32(const uc32_t *cstr, size_t n) {
    assert(cstr);
    return n;
}

size_t uz16_len_n(const uc16_t *cstr, unsigned n) {
    assert(cstr);

    switch (n) {
        case 1:
            return uz16_len_8(cstr);

        case 2:
            return uz16_len_16(cstr);

        case 4:
            return uz16_len_32(cstr);

        default:
            assert(false);
            return 0;
    }
}

size_t uz16n_len_n(const uc16_t *cstr, size_t cstr_len, unsigned n) {
    assert(cstr);

    switch (n) {
        case 1:
            return uz16n_len_8(cstr, cstr_len);

        case 2:
            return uz16n_len_16(cstr, cstr_len);

        case 4:
            return uz16n_len_32(cstr, cstr_len);

        default:
            assert(false);
            return 0;
    }
}

size_t uz16_len_8(const uc16_t *cstr) {
    return uz16n_len_8(cstr, uz16_len(cstr));
}

size_t uz16n_len_8(const uc16_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    for (size_t i = 0; i < n;) {
        uc16_t c = cstr[i];

        i   += uc16_len(c);
        len += uc16_len_8(c);
    }

    return len;
}

size_t uz16_len_16(const uc16_t *cstr) {
    return uz16_len(cstr);
}

size_t uz16n_len_16(const uc16_t *cstr, size_t n) {
    assert(cstr);
    return n;
}

size_t uz16_len_32(const uc16_t *cstr) {
    return uz16n_len_32(cstr, uz16_len(cstr));
}

size_t uz16n_len_32(const uc16_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    for (size_t i = 0; i < n;) {
        i += uc16_len(cstr[i]);
        ++len;
    }

    return len;
}

size_t uz8_len_n(const uc8_t *cstr, unsigned n) {
    assert(cstr);

    switch (n) {
        case 1:
            return uz8_len_8(cstr);

        case 2:
            return uz8_len_16(cstr);

        case 4:
            return uz8_len_32(cstr);

        default:
            assert(false);
            return 0;
    }
}

size_t uz8n_len_n(const uc8_t *cstr, size_t cstr_len, unsigned n) {
    assert(cstr);

    switch (n) {
        case 1:
            return uz8n_len_8(cstr, cstr_len);

        case 2:
            return uz8n_len_16(cstr, cstr_len);

        case 4:
            return uz8n_len_32(cstr, cstr_len);

        default:
            assert(false);
            return 0;
    }
}

size_t uz8_len_8(const uc8_t *cstr) {
    return uz8_len(cstr);
}

size_t uz8n_len_8(const uc8_t *cstr, size_t n) {
    assert(cstr);
    return n;
}

size_t uz8_len_16(const uc8_t *cstr) {
    return uz8n_len_16(cstr, uz8_len(cstr));
}

size_t uz8n_len_16(const uc8_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    for (size_t i = 0; i < n;) {
        uc8_t c = cstr[i];

        i   += uc8_len(c);
        len += uc8_len_16(c);
    }

    return len;
}

size_t uz8_len_32(const uc8_t *cstr) {
    return uz8n_len_32(cstr, uz8_len(cstr));
}

size_t uz8n_len_32(const uc8_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    for (size_t i = 0; i < n;) {
        i += uc8_len(cstr[i]);
        ++len;
    }

    return len;
}

size_t uz32_len(const uc32_t *cstr) {
    assert(cstr);
    const uc32_t *init_cstr = cstr;
    while (*cstr++);
    return cstr - init_cstr - 1;
}

size_t uz16_len(const uc16_t *cstr) {
    assert(cstr);
    const uc16_t *init_cstr = cstr;
    while (*cstr++);
    return cstr - init_cstr - 1;
}

size_t uz8_len(const uc8_t *cstr) {
    assert(cstr);
    const uc8_t *init_cstr = cstr;
    while (*cstr++);
    return cstr - init_cstr - 1;
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

int uz32n_cmp(const uc32_t *lhs, size_t n, const uc32_t *rhs) {
    USTR_RETURN_N_CMP_(uc32_t, lhs, n, rhs);
}

int uz32_cmp_n(const uc32_t *lhs, const uc32_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc32_t, lhs, rhs, n);
}

int uz32n_cmp_n(const uc32_t *lhs, size_t lhs_len, const uc32_t *rhs, size_t rhs_len) {
    USTR_RETURN_N_CMP_N_(uc32_t, lhs, lhs_len, rhs, rhs_len);
}

int uz16_cmp(const uc16_t *lhs, const uc16_t *rhs) {
    USTR_RETURN_CMP_(uc16_t, lhs, rhs);
}

int uz16n_cmp(const uc16_t *lhs, size_t n, const uc16_t *rhs) {
    USTR_RETURN_N_CMP_(uc16_t, lhs, n, rhs);
}

int uz16_cmp_n(const uc16_t *lhs, const uc16_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc16_t, lhs, rhs, n);
}

int uz16n_cmp_n(const uc16_t *lhs, size_t lhs_len, const uc16_t *rhs, size_t rhs_len) {
    USTR_RETURN_N_CMP_N_(uc16_t, lhs, lhs_len, rhs, rhs_len);
}

int uz8_cmp(const uc8_t *lhs, const uc8_t *rhs) {
    USTR_RETURN_CMP_(uc8_t, lhs, rhs);
}

int uz8n_cmp(const uc8_t *lhs, size_t n, const uc8_t *rhs) {
    USTR_RETURN_N_CMP_(uc8_t, lhs, n, rhs);
}

int uz8_cmp_n(const uc8_t *lhs, const uc8_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc8_t, lhs, rhs, n);
}

int uz8n_cmp_n(const uc8_t *lhs, size_t lhs_len, const uc8_t *rhs, size_t rhs_len) {
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
    return uz32_pos_uz32(cstr, another);
}

ptrdiff_t uz32n_pos(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len) {
    return uz32n_pos_uz32n(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz32_pos_uz32(const uc32_t *cstr, const uc32_t *another) {
    USTR_RETURN_POS_(cstr, another);
}

ptrdiff_t uz32n_pos_uz32(const uc32_t *cstr, size_t n, const uc32_t *another) {
    USTR_RETURN_N_POS_(cstr, n, another);
}

ptrdiff_t uz32_pos_uz32n(const uc32_t *cstr, const uc32_t *another, size_t n) {
    USTR_RETURN_POS_N_(cstr, another, n);
}

ptrdiff_t uz32n_pos_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len) {
    USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz32_pos_uc32(const uc32_t *cstr, uc32_t c) {
    USTR_RETURN_C_POS_(cstr, c);
}

ptrdiff_t uz32n_pos_uc32(const uc32_t *cstr, size_t n, uc32_t c) {
    USTR_RETURN_N_C_POS_(cstr, n, c);
}

ptrdiff_t uz16_pos(const uc16_t *cstr, const uc16_t *another) {
    return uz16_pos_uz16(cstr, another);
}

ptrdiff_t uz16n_pos(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len) {
    return uz16n_pos_uz16n(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz16_pos_uz16(const uc16_t *cstr, const uc16_t *another) {
    USTR_RETURN_POS_(cstr, another);
}

ptrdiff_t uz16n_pos_uz16(const uc16_t *cstr, size_t n, const uc16_t *another) {
    USTR_RETURN_N_POS_(cstr, n, another);
}

ptrdiff_t uz16_pos_uz16n(const uc16_t *cstr, const uc16_t *another, size_t n) {
    USTR_RETURN_POS_N_(cstr, another, n);
}

ptrdiff_t uz16n_pos_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len) {
    USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz16_pos_uc16(const uc16_t *cstr, uc16_t c) {
    USTR_RETURN_C_POS_(cstr, c);
}

ptrdiff_t uz16n_pos_uc16(const uc16_t *cstr, size_t n, uc16_t c) {
    USTR_RETURN_N_C_POS_(cstr, n, c);
}

ptrdiff_t uz8_pos(const uc8_t *cstr, const uc8_t *another) {
    return uz8_pos_uz8(cstr, another);
}

ptrdiff_t uz8n_pos(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len) {
    return uz8n_pos_uz8n(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz8_pos_uz8(const uc8_t *cstr, const uc8_t *another) {
    USTR_RETURN_POS_(cstr, another);
}

ptrdiff_t uz8n_pos_uz8(const uc8_t *cstr, size_t n, const uc8_t *another) {
    USTR_RETURN_N_POS_(cstr, n, another);
}

ptrdiff_t uz8_pos_uz8n(const uc8_t *cstr, const uc8_t *another, size_t n) {
    USTR_RETURN_POS_N_(cstr, another, n);
}

ptrdiff_t uz8n_pos_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len) {
    USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz8_pos_uc8(const uc8_t *cstr, uc8_t c) {
    USTR_RETURN_C_POS_(cstr, c);
}

ptrdiff_t uz8n_pos_uc8(const uc8_t *cstr, size_t n, uc8_t c) {
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

ptrdiff_t uz32_rpos(const uc32_t *cstr, const uc32_t *another, size_t from) {
    return uz32_rpos_uz32(cstr, another, from);
}

ptrdiff_t uz32n_rpos(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, size_t from) {
    return uz32n_rpos_uz32n(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz32_rpos_uz32(const uc32_t *cstr, const uc32_t *another, size_t from) {
    USTR_RETURN_POS_R_(cstr, another, from);
}

ptrdiff_t uz32_rpos_uz32n(const uc32_t *cstr, const uc32_t *another, size_t n, size_t from) {
    USTR_RETURN_POS_N_R_(cstr, another, n, from);
}

ptrdiff_t uz32n_rpos_uz32(const uc32_t *cstr, size_t n, const uc32_t *another, size_t from) {
    USTR_RETURN_N_POS_R_(cstr, n, another, from);
}

ptrdiff_t uz32n_rpos_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, size_t from) {
    USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz32_rpos_uc32(const uc32_t *cstr, uc32_t c, size_t from) {
    return uz32n_rpos_uc32(cstr, from + 1, c, from);
}

ptrdiff_t uz32n_rpos_uc32(const uc32_t *cstr, size_t n, uc32_t c, size_t from) {
    USTR_RETURN_N_C_POS_R_(cstr, n, c, from);
}

ptrdiff_t uz16_rpos(const uc16_t *cstr, const uc16_t *another, size_t from) {
    return uz16_rpos_uz16(cstr, another, from);
}

ptrdiff_t uz16n_rpos(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len, size_t from) {
    return uz16n_rpos_uz16n(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz16_rpos_uz16(const uc16_t *cstr, const uc16_t *another, size_t from) {
    USTR_RETURN_POS_R_(cstr, another, from);
}

ptrdiff_t uz16_rpos_uz16n(const uc16_t *cstr, const uc16_t *another, size_t n, size_t from) {
    USTR_RETURN_POS_N_R_(cstr, another, n, from);
}

ptrdiff_t uz16n_rpos_uz16(const uc16_t *cstr, size_t n, const uc16_t *another, size_t from) {
    USTR_RETURN_N_POS_R_(cstr, n, another, from);
}

ptrdiff_t uz16n_rpos_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len, size_t from) {
    USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz16_rpos_uc16(const uc16_t *cstr, uc16_t c, size_t from) {
    return uz16n_rpos_uc16(cstr, from + 1, c, from);
}

ptrdiff_t uz16n_rpos_uc16(const uc16_t *cstr, size_t n, uc16_t c, size_t from) {
    USTR_RETURN_N_C_POS_R_(cstr, n, c, from);
}

ptrdiff_t uz8_rpos(const uc8_t *cstr, const uc8_t *another, size_t from) {
    return uz8_rpos_uz8(cstr, another, from);
}

ptrdiff_t uz8n_rpos(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len, size_t from) {
    return uz8n_rpos_uz8n(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz8_rpos_uz8(const uc8_t *cstr, const uc8_t *another, size_t from) {
    USTR_RETURN_POS_R_(cstr, another, from);
}

ptrdiff_t uz8_rpos_uz8n(const uc8_t *cstr, const uc8_t *another, size_t n, size_t from) {
    USTR_RETURN_POS_N_R_(cstr, another, n, from);
}

ptrdiff_t uz8n_rpos_uz8(const uc8_t *cstr, size_t n, const uc8_t *another, size_t from) {
    USTR_RETURN_N_POS_R_(cstr, n, another, from);
}

ptrdiff_t uz8n_rpos_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len, size_t from) {
    USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz8_rpos_uc8(const uc8_t *cstr, uc8_t c, size_t from) {
    return uz8n_rpos_uc8(cstr, from + 1, c, from);
}

ptrdiff_t uz8n_rpos_uc8(const uc8_t *cstr, size_t n, uc8_t c, size_t from) {
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
    return uz32_fill_uc32(cstr, c);
}

void uz32n_fill(uc32_t *cstr, size_t n, uc32_t c) {
    return uz32n_fill_uc32(cstr, n, c);
}

void uz32_fill_uc32(uc32_t *cstr, uc32_t c) {
    USTR_FILL_(cstr, c);
}

void uz32n_fill_uc32(uc32_t *cstr, size_t n, uc32_t c) {
    USTR_N_FILL_(cstr, n, c);
}

void uz32_fill_uz32(uc32_t *cstr, const uc32_t *another) {
    USTR_FILL_Z_(cstr, another);
}

void uz32n_fill_uz32(uc32_t *cstr, size_t n, const uc32_t *another) {
    USTR_N_FILL_Z_(cstr, n, another);
}

void uz32_fill_uz32n(uc32_t *cstr, const uc32_t *another, size_t n) {
    USTR_FILL_Z_N_(cstr, another, n);
}

void uz32n_fill_uz32n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len) {
    USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len);
}

void uz16_fill(uc16_t *cstr, uc16_t c) {
    return uz16_fill_uc16(cstr, c);
}

void uz16n_fill(uc16_t *cstr, size_t n, uc16_t c) {
    return uz16n_fill_uc16(cstr, n, c);
}

void uz16_fill_uc16(uc16_t *cstr, uc16_t c) {
    USTR_FILL_(cstr, c);
}

void uz16n_fill_uc16(uc16_t *cstr, size_t n, uc16_t c) {
    USTR_N_FILL_(cstr, n, c);
}

void uz16_fill_uz16(uc16_t *cstr, const uc16_t *another) {
    USTR_FILL_Z_(cstr, another);
}

void uz16n_fill_uz16(uc16_t *cstr, size_t n, const uc16_t *another) {
    USTR_N_FILL_Z_(cstr, n, another);
}

void uz16_fill_uz16n(uc16_t *cstr, const uc16_t *another, size_t n) {
    USTR_FILL_Z_N_(cstr, another, n);
}

void uz16n_fill_uz16n(uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len) {
    USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len);
}

void uz8_fill(uc8_t *cstr, uc8_t c) {
    return uz8_fill_uc8(cstr, c);
}

void uz8n_fill(uc8_t *cstr, size_t n, uc8_t c) {
    return uz8n_fill_uc8(cstr, n, c);
}

void uz8_fill_uc8(uc8_t *cstr, uc8_t c) {
    USTR_FILL_(cstr, c);
}

void uz8n_fill_uc8(uc8_t *cstr, size_t n, uc8_t c) {
    USTR_N_FILL_(cstr, n, c);
}

void uz8_fill_uz8(uc8_t *cstr, const uc8_t *another) {
    USTR_FILL_Z_(cstr, another);
}

void uz8n_fill_uz8(uc8_t *cstr, size_t n, const uc8_t *another) {
    USTR_N_FILL_Z_(cstr, n, another);
}

void uz8_fill_uz8n(uc8_t *cstr, const uc8_t *another, size_t n) {
    USTR_FILL_Z_N_(cstr, another, n);
}

void uz8n_fill_uz8n(uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len) {
    USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len);
}

size_t uz8_upper_len(const uc8_t *cstr) {
    return uz8_to_case_len(cstr, UCASE_UPPER);
}

size_t uz8n_upper_len(const uc8_t *cstr, size_t n) {
    return uz8n_case_len(cstr, n, UCASE_UPPER);
}

size_t uz8_to_lower_len(const uc8_t *cstr) {
    return uz8_to_case_len(cstr, UCASE_LOWER);
}

size_t uz8n_lower_len(const uc8_t *cstr, size_t n) {
    return uz8n_case_len(cstr, n, UCASE_LOWER);
}

size_t uz8_to_case_len(const uc8_t *cstr, ucase_t ca) {
    assert(cstr);

    uc8_case_len_func_t func = uc8_case_len_func_from_ucase(ca);

    if (!func)
        return uz8_len(cstr);

    size_t len = 0;

    for (; *cstr; cstr += uc8_len(*cstr))
        len += func(cstr);

    return len;
}

size_t uz8n_case_len(const uc8_t *cstr, size_t n, ucase_t ca) {
    assert(cstr);

    uc8_case_len_func_t func = uc8_case_len_func_from_ucase(ca);

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

void uz32n_to_upper(uc32_t *cstr, size_t n) {
    uz32n_to_case(cstr, n, UCASE_UPPER);
}

void uz32_to_lower(uc32_t *cstr) {
    uz32_to_case(cstr, UCASE_LOWER);
}

void uz32n_to_lower(uc32_t *cstr, size_t n) {
    uz32n_to_case(cstr, n, UCASE_LOWER);
}

void uz32_to_case(uc32_t *cstr, ucase_t ca) {
    assert(cstr);

    uc32_to_case_func_t func = uc32_to_case_func_from_ucase(ca);

    if (!func)
        return;

    for (; *cstr; ++cstr)
        *cstr = func(*cstr);
}

void uz32n_to_case(uc32_t *cstr, size_t n, ucase_t ca) {
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

void uz16n_to_upper(uc16_t *cstr, size_t n) {
    uz16n_to_case(cstr, n, UCASE_UPPER);
}

void uz16_to_lower(uc16_t *cstr) {
    uz16_to_case(cstr, UCASE_LOWER);
}

void uz16n_to_lower(uc16_t *cstr, size_t n) {
    uz16n_to_case(cstr, n, UCASE_LOWER);
}

void uz16_to_case(uc16_t *cstr, ucase_t ca) {
    assert(cstr);

    uc16_to_case_func_t func = uc16_to_case_func_from_ucase(ca);

    if (!func)
        return;

    while (*cstr)
        cstr += func(cstr, cstr);
}

void uz16n_to_case(uc16_t *cstr, size_t n, ucase_t ca) {
    assert(cstr);

    uc16_to_case_func_t func = uc16_to_case_func_from_ucase(ca);

    if (!func)
        return;

    while (n--)
        cstr += func(cstr, cstr);
}

#define USTR_UZ8_TO_CASE_(case, from, to)        \
    assert(from && to);                          \
                                                 \
    for (size_t i = 0, j = 0; from[i];) {        \
        unsigned len = uc8_len(from[i]);         \
                                                 \
        uz8_copy_n(to + j, from + i, len);       \
                                                 \
        unsigned to_len = uc8_to_##case(to + j); \
                                                 \
        i += len;                                \
        j += to_len;                             \
    }

#define USTR_UZ8_TO_CASE_N_(case, from, n, to)   \
    assert(from && to);                          \
                                                 \
    for (size_t i = 0, j = 0; i < n;) {          \
        unsigned len = uc8_len(from[i]);         \
                                                 \
        uz8_copy_n(to + j, from + i, len);       \
                                                 \
        unsigned to_len = uc8_to_##case(to + j); \
                                                 \
        i += len;                                \
        j += to_len;                             \
    }

void uz8_to_upper(const uc8_t *from, uc8_t *to) {
    uz8_to_case(from, to, UCASE_UPPER);
}

void uz8n_to_upper(const uc8_t *from, size_t n, uc8_t *to) {
    uz8n_to_case(from, n, to, UCASE_UPPER);
}

void uz8_to_lower(const uc8_t *from, uc8_t *to) {
    uz8_to_case(from, to, UCASE_LOWER);
}

void uz8n_to_lower(const uc8_t *from, size_t n, uc8_t *to) {
    uz8n_to_case(from, n, to, UCASE_LOWER);
}

void uz8_to_case(const uc8_t *from, uc8_t *to, ucase_t ca) {
    assert(from && to);

    uc8_to_case_func_t func = uc8_to_case_func_from_ucase(ca);

    if (!func)
        return;

    for (size_t i = 0, j = 0; from[i];) {
        unsigned len = uc8_len(from[i]);

        uz8_copy_n(to + j, from + i, len);

        unsigned to_len = func(to + j, to + j);

        i += len;
        j += to_len;
    }
}

void uz8n_to_case(const uc8_t *from, size_t n, uc8_t *to, ucase_t ca) {
    assert(from && to);

    uc8_to_case_func_t func = uc8_to_case_func_from_ucase(ca);

    if (!func)
        return;

    for (size_t i = 0, j = 0; i < n;) {
        unsigned len = uc8_len(from[i]);

        uz8_copy_n(to + j, from + i, len);

        unsigned to_len = func(to + j, to + j);

        i += len;
        j += to_len;
    }
}

#define USTR_RETURN_Z_N_TRIM_LEFT_(N, src, n)    \
    {                                            \
        assert(cstr);                            \
                                                 \
        size_t wspace_len = 0;                   \
                                                 \
        for (size_t i = 0; i < n;) {             \
            unsigned len = uc##N##_len(cstr[i]); \
                                                 \
            if (uc##N##_wspace(cstr + i))        \
                wspace_len += len;               \
            else                                 \
                break;                           \
                                                 \
            i += len;                            \
        }                                        \
                                                 \
        size_t new_len = n - wspace_len;         \
                                                 \
        for (size_t i = 0; i < new_len; ++i)     \
            cstr[i] = cstr[i + wspace_len];      \
                                                 \
        return new_len;                          \
    }

#define USTR_RETURN_Z_N_TRIM_RIGHT_(N, src, n)   \
    {                                            \
        assert(cstr);                            \
                                                 \
        size_t wspace_len = 0;                   \
                                                 \
        for (ptrdiff_t i = n - 1; i >= 0;) {     \
            unsigned len = uc##N##_len(cstr[i]); \
                                                 \
            if (uc##N##_wspace(cstr + i))        \
                ++wspace_len;                    \
            else                                 \
                break;                           \
                                                 \
            i -= len;                            \
        }                                        \
                                                 \
        return n - wspace_len;                   \
    }

size_t uz32_trim(uc32_t *cstr) {
    return uz32n_trim(cstr, uz32_len(cstr));
}

size_t uz32n_trim(uc32_t *cstr, size_t n) {
    return uz32n_rtrim(cstr, uz32n_ltrim(cstr, n));
}

size_t uz32_ltrim(uc32_t *cstr) {
    return uz32n_ltrim(cstr, uz32_len(cstr));
}

size_t uz32n_ltrim(uc32_t *cstr, size_t n) {
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

size_t uz32_rtrim(const uc32_t *cstr) {
    return uz32n_rtrim(cstr, uz32_len(cstr));
}

size_t uz32n_rtrim(const uc32_t *cstr, size_t n) {
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
	return uz16n_rtrim(cstr, uz16_ltrim(cstr));
}

size_t uz16n_trim(uc16_t *cstr, size_t n) {
    return uz16n_rtrim(cstr, uz16n_ltrim(cstr, n));
}

size_t uz16_ltrim(uc16_t *cstr) {
	return uz16n_ltrim(cstr, uz16_len(cstr));
}

size_t uz16n_ltrim(uc16_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_LEFT_(16, cstr, n);
}

size_t uz16_rtrim(const uc16_t *cstr) {
	return uz16n_rtrim(cstr, uz16_len(cstr));
}

size_t uz16n_rtrim(const uc16_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_RIGHT_(16, cstr, n);
}

size_t uz8_trim(uc8_t *cstr) {
	return uz8n_rtrim(cstr, uz8_ltrim(cstr));
}

size_t uz8n_trim(uc8_t *cstr, size_t n) {
    return uz8n_rtrim(cstr, uz8n_ltrim(cstr, n));
}

size_t uz8_ltrim(uc8_t *cstr) {
	return uz8n_ltrim(cstr, uz8_len(cstr));
}

size_t uz8n_ltrim(uc8_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_LEFT_(8, cstr, n);
}

size_t uz8_rtrim(const uc8_t *cstr) {
	return uz8n_rtrim(cstr, uz8_len(cstr));
}

size_t uz8n_rtrim(const uc8_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_RIGHT_(8, cstr, n);
}

#define USTR_RETURN_COPY_(dst, src) \
    {                               \
        assert(dst && src);         \
                                    \
        size_t len = 0;             \
                                    \
        for (; *src; ++len)         \
            *dst++ = *src++;        \
                                    \
        return len;                 \
    }

#define USTR_RETURN_COPY_N_(dst, src, n) \
    assert(dst && src);                  \
                                         \
    for (size_t i = 0; i < n; ++i)       \
        *dst++ = *src++;                 \
                                         \
    return n;

#define USTR_RETURN_N_COPY_N_(dst, dst_len, src, src_len)    \
    {                                                        \
        assert(dst && src);                                  \
                                                             \
        size_t min = dst_len <= src_len ? dst_len : src_len; \
                                                             \
        for (size_t i = 0; i < min; ++i)                     \
            *dst++ = *src++;                                 \
                                                             \
        return min;                                          \
    }

size_t uz32_copy(uc32_t *dst, const uc32_t *src) {
    USTR_RETURN_COPY_(dst, src);
}

size_t uz32_copy_n(uc32_t *dst, const uc32_t *src, size_t n) {
    USTR_RETURN_COPY_N_(dst, src, n);
}

size_t uz32n_copy_n(uc32_t *dst, size_t dst_len, const uc32_t *src, size_t src_len) {
    USTR_RETURN_N_COPY_N_(dst, dst_len, src, src_len);
}

size_t uz16_copy(uc16_t *dst, const uc16_t *src) {
    USTR_RETURN_COPY_(dst, src);
}

size_t uz16_copy_n(uc16_t *dst, const uc16_t *src, size_t n) {
    USTR_RETURN_COPY_N_(dst, src, n);
}

size_t uz16n_copy_n(uc16_t *dst, size_t dst_len, const uc16_t *src, size_t src_len) {
    USTR_RETURN_N_COPY_N_(dst, dst_len, src, src_len);
}

size_t uz8_copy(uc8_t *dst, const uc8_t *src) {
    USTR_RETURN_COPY_(dst, src);
}

size_t uz8_copy_n(uc8_t *dst, const uc8_t *src, size_t n) {
    USTR_RETURN_COPY_N_(dst, src, n);
}

size_t uz8n_copy_n(uc8_t *dst, size_t dst_len, const uc8_t *src, size_t src_len) {
    USTR_RETURN_N_COPY_N_(dst, dst_len, src, src_len);
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
    uz32n_reverse(cstr, uz32_len(cstr));
}

void uz32n_reverse(uc32_t *cstr, size_t n) {
    assert(cstr);

    for (size_t i = 0, j = n - 1; i < n / 2; ++i, --j) {
        uc32_t tmp = cstr[j];

        cstr[j] = cstr[i];
        cstr[i] = tmp;
    }
}

void uz16_reverse(uc16_t *cstr) {
    uz16n_reverse(cstr, uz16_len(cstr));
}

void uz16n_reverse(uc16_t *cstr, size_t n) {
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
    uz8n_reverse(cstr, uz8_len(cstr));
}

void uz8n_reverse(uc8_t *cstr, size_t n) {
    assert(cstr);

    // Reverse bytes

    for (size_t i = 0, j = n - 1; i < n / 2; ++i, --j) {
        uc8_t tmp = cstr[j];

        cstr[j] = cstr[i];
        cstr[i] = tmp;
    }

    // Fix sequences

    for (size_t i = 0; i < n;) {
        size_t trail = uz8n_trail(cstr + i, n - i);

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

size_t uz32_new_csplit(const uc32_t *cstr, const uc32_t *another, ucv32_t **array) {
    return uz32_new_csplit_uz32(cstr, another, array);
}

size_t uz32_new_csplit_e(const uc32_t *cstr, const uc32_t *another, ucv32_t **array, bool *error) {
    return uz32_new_csplit_uz32_e(cstr, another, array, error);
}

size_t uz32n_new_csplit(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t **array) {
    return uz32n_new_csplit_uz32n(cstr, cstr_len, another, another_len, array);
}

size_t uz32n_new_csplit_e(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(cstr, cstr_len, another, another_len, array, error);
}

size_t uz32_csplit(const uc32_t *cstr, const uc32_t *another, ucv32_t *array, size_t array_len) {
    return uz32_csplit_uz32(cstr, another, array, array_len);
}

size_t uz32n_csplit(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(cstr, cstr_len, another, another_len, array, array_len);
}

size_t uz32_new_split(uc32_t *cstr, const uc32_t *another, uv32_t **array) {
    return uz32_new_split_uz32(cstr, another, array);
}

size_t uz32_new_split_e(uc32_t *cstr, const uc32_t *another, uv32_t **array, bool *error) {
    return uz32_new_split_uz32_e(cstr, another, array, error);
}

size_t uz32n_new_split(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t **array) {
    return uz32n_new_split_uz32n(cstr, cstr_len, another, another_len, array);
}

size_t uz32n_new_split_e(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t **array, bool *error) {
    return uz32n_new_split_uz32n_e(cstr, cstr_len, another, another_len, array, error);
}

size_t uz32_split(uc32_t *cstr, const uc32_t *another, uv32_t *array, size_t array_len) {
    return uz32_split_uz32(cstr, another, array, array_len);
}

size_t uz32n_split(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t *array, size_t array_len) {
    return uz32n_split_uz32n(cstr, cstr_len, another, another_len, array, array_len);
}

size_t uz32_new_csplit_uc32(const uc32_t *cstr, uc32_t c, ucv32_t **array) {
	return uz32_new_split_uc32((uc32_t *) cstr, c, (uv32_t **) array);
}

size_t uz32_new_csplit_uc32_e(const uc32_t *cstr, uc32_t c, ucv32_t **array, bool *error) {
	return uz32_new_split_uc32_e((uc32_t *) cstr, c, (uv32_t **) array, error);
}

size_t uz32n_new_csplit_uc32(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t **array) {
	return uz32n_new_split_uc32((uc32_t *) cstr, n, c, (uv32_t **) array);
}

size_t uz32n_new_csplit_uc32_e(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t **array, bool *error) {
	return uz32n_new_split_uc32_e((uc32_t *) cstr, n, c, (uv32_t **) array, error);
}

size_t uz32_csplit_uc32(const uc32_t *cstr, uc32_t c, ucv32_t *array, size_t array_len) {
	return uz32_split_uc32((uc32_t *) cstr, c, (uv32_t *) array, array_len);
}

size_t uz32n_csplit_uc32(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t *array, size_t array_len) {
	return uz32n_split_uc32((uc32_t *) cstr, n, c, (uv32_t *) array, array_len);
}

size_t uz32_new_split_uc32(uc32_t *cstr, uc32_t c, uv32_t **array) {
	return uz32_new_split_uc32_e(cstr, c, array, NULL);
}

size_t uz32_new_split_uc32_e(uc32_t *cstr, uc32_t c, uv32_t **array, bool *error) {
	return uz32n_new_split_uc32_e(cstr, uz32_len(cstr), c, array, error);
}

size_t uz32n_new_split_uc32(uc32_t *cstr, size_t n, uc32_t c, uv32_t **array) {
	return uz32n_new_split_uc32_e(cstr, n, c, array, NULL);
}

size_t uz32n_new_split_uc32_e(uc32_t *cstr, size_t n, uc32_t c, uv32_t **array, bool *error) {
    size_t array_len = uz32n_split_uc32(cstr, n, c, NULL, 0);

    if (!array)
        return array_len;

    uv32_t *new_array = ualloc(sizeof(uv32_t) * array_len);

    if (!new_array) {
        if (error)
            *error = true;
    
        return array_len;
    }

    *array = new_array;

    return uz32n_split_uc32(cstr, n, c, new_array, array_len);
}

size_t uz32_split_uc32(uc32_t *cstr, uc32_t c, uv32_t *array, size_t array_len) {
    return uz32n_split_uc32(cstr, uz32_len(cstr), c, array, array_len);
}

size_t uz32n_split_uc32(uc32_t *cstr, size_t n, uc32_t c, uv32_t *array, size_t array_len) {
    assert(cstr);

    size_t count = 0;

    for (ptrdiff_t prev_pos = 0; prev_pos >= 0; ++count) {
        uc32_t   *begin   = cstr + prev_pos;
        size_t    len     = n - prev_pos;
        ptrdiff_t rel_pos = uz32n_pos_uc32(begin, len, c);
        ptrdiff_t pos     = rel_pos;

        if (array && count < array_len) {
            size_t view_len = pos < 0 ? len : rel_pos;
            array[count] = uv32_from_uz32n(begin, view_len);
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

size_t uz32n_new_csplit_uz32(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t **array) {
    return uz32n_new_split_uz32((uc32_t *) cstr, n, another, (uv32_t **) array);
}

size_t uz32n_new_csplit_uz32_e(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t **array, bool *error) {
    return uz32n_new_split_uz32_e((uc32_t *) cstr, n, another, (uv32_t **) array, error);
}

size_t uz32_csplit_uz32(const uc32_t *cstr, const uc32_t *another, ucv32_t *array, size_t array_len) {
    return uz32_split_uz32((uc32_t *) cstr, another, (uv32_t *) array, array_len);
}

size_t uz32n_csplit_uz32(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t *array, size_t array_len) {
    return uz32n_split_uz32((uc32_t *) cstr, n, another, (uv32_t *) array, array_len);
}

size_t uz32_new_split_uz32(uc32_t *cstr, const uc32_t *another, uv32_t **array) {
    return uz32_new_split_uz32_e(cstr, another, array, NULL);
}

size_t uz32_new_split_uz32_e(uc32_t *cstr, const uc32_t *another, uv32_t **array, bool *error) {
    return uz32n_new_split_uz32_e(cstr, uz32_len(cstr), another, array, error);
}

size_t uz32n_new_split_uz32(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t **array) {
    return uz32n_new_split_uz32_e(cstr, n, another, array, NULL);
}

size_t uz32n_new_split_uz32_e(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t **array, bool *error) {
    return uz32n_new_split_uz32n_e(cstr, n, another, uz32_len(another), array, error);
}

size_t uz32_split_uz32(uc32_t *cstr, const uc32_t *another, uv32_t *array, size_t array_len) {
    return uz32n_split_uz32(cstr, uz32_len(cstr), another, array, array_len);
}

size_t uz32n_split_uz32(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t *array, size_t array_len) {
    return uz32n_split_uz32n(cstr, n, another, uz32_len(another), array, array_len);
}

size_t uz32_new_csplit_uz32n(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t **array) {
    return uz32_new_split_uz32n((uc32_t *) cstr, another, n, (uv32_t **) array);
}

size_t uz32_new_csplit_uz32n_e(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t **array, bool *error) {
    return uz32_new_split_uz32n_e((uc32_t *) cstr, another, n, (uv32_t **) array, error);
}

size_t uz32n_new_csplit_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t **array) {
    return uz32n_new_split_uz32n((uc32_t *) cstr, cstr_len, another, another_len, (uv32_t **) array);
}

size_t uz32n_new_csplit_uz32n_e(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t **array, bool *error) {
    return uz32n_new_split_uz32n_e((uc32_t *) cstr, cstr_len, another, another_len, (uv32_t **) array, error);
}

size_t uz32_csplit_uz32n(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t *array, size_t array_len) {
    return uz32_split_uz32n((uc32_t *) cstr, another, n, (uv32_t *) array, array_len);
}

size_t uz32n_csplit_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t *array, size_t array_len) {
    return uz32n_split_uz32n((uc32_t *) cstr, cstr_len, another, array_len, (uv32_t *) array, array_len);
}

size_t uz32_new_split_uz32n(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t **array) {
    return uz32_new_split_uz32n_e(cstr, another, n, array, NULL);
}

size_t uz32_new_split_uz32n_e(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t **array, bool *error) {
    return uz32n_new_split_uz32n_e(cstr, uz32_len(cstr), another, n, array, error);
}

size_t uz32n_new_split_uz32n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t **array) {
    return uz32n_new_split_uz32n_e(cstr, cstr_len, another, another_len, array, NULL);
}

size_t uz32n_new_split_uz32n_e(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t **array, bool *error) {
    assert(cstr && another);

    size_t array_len = uz32n_split_uz32n(cstr, cstr_len, another, another_len, NULL, 0);

    if (!array)
        return array_len;

    uv32_t *new_array = ualloc(sizeof(uv32_t) * array_len);

    if (!new_array) {
        if (error)
            *error = true;
    
        return array_len;
    }

    *array = new_array;

    return uz32n_split_uz32n(cstr, cstr_len, another, another_len, new_array, array_len);
}

size_t uz32_split_uz32n(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t *array, size_t array_len) {
    return uz32n_split_uz32n(cstr, uz32_len(cstr), another, n, array, array_len);
}

size_t uz32n_split_uz32n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t *array, size_t array_len) {
    assert(cstr && another);

    if (another_len > cstr_len)
        return 0;

    size_t count = 0;

    for (ptrdiff_t prev_pos = 0; prev_pos >= 0; ++count) {
        uc32_t   *begin   = cstr + prev_pos;
        size_t    len     = cstr_len - prev_pos;
        ptrdiff_t rel_pos = uz32n_pos_uz32n(begin, len, another, another_len);
        ptrdiff_t pos     = rel_pos;

        if (array && count < array_len) {
            size_t view_len = pos < 0 ? len : rel_pos;
            array[count] = uv32_from_uz32n(begin, view_len);
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
            ptrdiff_t pos = uz##N##n_pos(cstr, cstr_len, from, from_len);          \
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
            ptrdiff_t pos = uz##N##n_pos(cstr, cstr_len, from, from_len);                    \
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
            ptrdiff_t pos = uz##N##n_pos(cstr, cstr_len, from, from_len);                    \
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

size_t uz32n_replace_uc32_uc32(uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to) {
    return uz32n_replace_uc32_uc32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32n_replace_uc32_uc32_c(uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count);
}

size_t uz32_replace_uz32_uc32(uc32_t *cstr, const uc32_t *from, uc32_t to) {
    return uz32_replace_uz32_uc32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uz32_uc32_c(uc32_t *cstr, const uc32_t *from, uc32_t to, size_t *count) {
	return uz32_replace_uz32n_uc32_c(cstr, from, uz32_len(from), to, count);
}

size_t uz32n_replace_uz32_uc32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to) {
    return uz32n_replace_uz32_uc32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32n_replace_uz32_uc32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to, size_t *count) {
	return uz32n_replace_uz32n_uc32_c(cstr, cstr_len, from, uz32_len(from), to, count);
}

size_t uz32_replace_uz32n_uc32(uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to) {
    return uz32_replace_uz32n_uc32_c(cstr, from, from_len, to, NULL);
}

size_t uz32_replace_uz32n_uc32_c(uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to, size_t *count) {
    return uz32n_replace_uz32n_uc32_c(cstr, uz32_len(cstr), from, from_len, to, count);
}

size_t uz32n_replace_uz32n_uc32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to) {
    return uz32n_replace_uz32n_uc32_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz32n_replace_uz32n_uc32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_C_(32, cstr, cstr_len, from, from_len, to, count);
}

size_t uz32_replace_uc32_uz32(uc32_t *cstr, uc32_t from, const uc32_t *to) {
    return uz32_replace_uc32_uz32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uc32_uz32_c(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32n_replace_uc32_uz32n_c(cstr, uz32_len(cstr), from, to, uz32_len(to), count);
}

size_t uz32_replace_len_uc32_uz32(const uc32_t *cstr, uc32_t from, const uc32_t *to) {
    return uz32_replace_len_uc32_uz32_c(cstr, from, to, NULL);
}

size_t uz32_replace_len_uc32_uz32_c(const uc32_t *cstr, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32n_replace_len_uc32_uz32n_c(cstr, uz32_len(cstr), from, uz32_len(to), count);
}

size_t uz32n_replace_uc32_uz32(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to) {
    return uz32n_replace_uc32_uz32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32n_replace_uc32_uz32_c(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32n_replace_uc32_uz32n_c(cstr, cstr_len, from, to, uz32_len(to), count);
}

size_t uz32n_replace_len_uc32_uz32(const uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to) {
    return uz32n_replace_len_uc32_uz32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32n_replace_len_uc32_uz32_c(const uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32n_replace_len_uc32_uz32n_c(cstr, cstr_len, from, uz32_len(to), count);
}

size_t uz32_replace_uc32_uz32n(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t to_len) {
    return uz32_replace_uc32_uz32n_c(cstr, from, to, to_len, NULL);
}

size_t uz32_replace_uc32_uz32n_c(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32n_replace_uc32_uz32n_c(cstr, uz32_len(cstr), from, to, to_len, count);
}

size_t uz32_replace_len_uc32_uz32n(const uc32_t *cstr, uc32_t from, size_t to_len) {
    return uz32_replace_len_uc32_uz32n_c(cstr, from, to_len, NULL);
}

size_t uz32_replace_len_uc32_uz32n_c(const uc32_t *cstr, uc32_t from, size_t to_len, size_t *count) {
	return uz32n_replace_len_uc32_uz32n_c(cstr, uz32_len(cstr), from, to_len, count);
}

size_t uz32n_replace_uc32_uz32n(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t to_len) {
    return uz32n_replace_uc32_uz32n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz32n_replace_uc32_uz32n_c(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_(32, cstr, cstr_len, from, to, to_len, count);
}

size_t uz32n_replace_len_uc32_uz32n(const uc32_t *cstr, size_t cstr_len, uc32_t from, size_t to_len) {
    return uz32n_replace_len_uc32_uz32n_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz32n_replace_len_uc32_uz32n_c(const uc32_t *cstr, size_t cstr_len, uc32_t from, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count);
}

size_t uz32_replace_uz32_uz32(uc32_t *cstr, const uc32_t *from, const uc32_t *to) {
    return uz32_replace_uz32_uz32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uz32_uz32_c(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32n_replace_uz32n_uz32n_c(cstr, uz32_len(cstr), from, uz32_len(from), to, uz32_len(to), count);
}

size_t uz32_replace_len_uz32_uz32(const uc32_t *cstr, const uc32_t *from, const uc32_t *to) {
    return uz32_replace_len_uz32_uz32_c(cstr, from, to, NULL);
}

size_t uz32_replace_len_uz32_uz32_c(const uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32n_replace_len_uz32n_uz32n_c(cstr, uz32_len(cstr), from, uz32_len(from), uz32_len(to), count);
}

size_t uz32n_replace_uz32_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to) {
    return uz32n_replace_uz32_uz32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32n_replace_uz32_uz32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32n_replace_uz32n_uz32n_c(cstr, cstr_len, from, uz32_len(from), to, uz32_len(to), count);
}

size_t uz32n_replace_len_uz32_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to) {
    return uz32n_replace_len_uz32_uz32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32n_replace_len_uz32_uz32_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32n_replace_len_uz32n_uz32n_c(cstr, cstr_len, from, uz32_len(from), uz32_len(to), count);
}

size_t uz32_replace_uz32n_uz32(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32_replace_uz32n_uz32_c(cstr, from, from_len, to, NULL);
}

size_t uz32_replace_uz32n_uz32_c(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32n_replace_uz32n_uz32n_c(cstr, uz32_len(cstr), from, from_len, to, uz32_len(to), count);
}

size_t uz32_replace_len_uz32n_uz32(const uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32_replace_len_uz32n_uz32_c(cstr, from, from_len, to, NULL);
}

size_t uz32_replace_len_uz32n_uz32_c(const uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32n_replace_len_uz32n_uz32n_c(cstr, uz32_len(cstr), from, from_len, uz32_len(to), count);
}

size_t uz32n_replace_uz32n_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32n_replace_uz32n_uz32_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz32n_replace_uz32n_uz32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32n_replace_uz32n_uz32n_c(cstr, cstr_len, from, from_len, to, uz32_len(to), count);
}

size_t uz32n_replace_len_uz32n_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32n_replace_len_uz32n_uz32_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz32n_replace_len_uz32n_uz32_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32n_replace_len_uz32n_uz32n_c(cstr, cstr_len, from, from_len, uz32_len(to), count);
}

size_t uz32_replace_uz32_uz32n(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t to_len) {
    return uz32_replace_uz32_uz32n_c(cstr, from, to, to_len, NULL);
}

size_t uz32_replace_uz32_uz32n_c(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32n_replace_uz32n_uz32n_c(cstr, uz32_len(cstr), from, uz32_len(from), to, to_len, count);
}

size_t uz32_replace_len_uz32_uz32n(const uc32_t *cstr, const uc32_t *from, size_t to_len) {
    return uz32_replace_len_uz32_uz32n_c(cstr, from, to_len, NULL);
}

size_t uz32_replace_len_uz32_uz32n_c(const uc32_t *cstr, const uc32_t *from, size_t to_len, size_t *count) {
	return uz32n_replace_len_uz32n_uz32n_c(cstr, uz32_len(cstr), from, uz32_len(from), to_len, count);
}

size_t uz32n_replace_uz32_uz32n(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t to_len) {
    return uz32n_replace_uz32_uz32n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz32n_replace_uz32_uz32n_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32n_replace_uz32n_uz32n_c(cstr, cstr_len, from, uz32_len(from), to, to_len, count);
}

size_t uz32n_replace_len_uz32_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t to_len) {
    return uz32n_replace_len_uz32_uz32n_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz32n_replace_len_uz32_uz32n_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t to_len, size_t *count) {
	return uz32n_replace_len_uz32n_uz32n_c(cstr, cstr_len, from, uz32_len(from), to_len, count);
}

size_t uz32_replace_uz32n_uz32n(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len) {
    return uz32_replace_uz32n_uz32n_c(cstr, from, from_len, to, to_len, NULL);
}

size_t uz32_replace_uz32n_uz32n_c(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32n_replace_uz32n_uz32n_c(cstr, uz32_len(cstr), from, from_len, to, to_len, count);
}

size_t uz32_replace_len_uz32n_uz32n(const uc32_t *cstr, const uc32_t *from, size_t from_len, size_t to_len) {
    return uz32_replace_len_uz32n_uz32n_c(cstr, from, from_len, to_len, NULL);
}

size_t uz32_replace_len_uz32n_uz32n_c(const uc32_t *cstr, const uc32_t *from, size_t from_len, size_t to_len, size_t *count) {
	return uz32n_replace_len_uz32n_uz32n_c(cstr, uz32_len(cstr), from, from_len, to_len, count);
}

size_t uz32n_replace_uz32n_uz32n(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len) {
    return uz32n_replace_uz32n_uz32n_c(cstr, cstr_len, from, from_len, to, to_len, NULL);
}

size_t uz32n_replace_uz32n_uz32n_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_(32, cstr, cstr_len, from, from_len, to, to_len, count);
}

size_t uz32n_replace_len_uz32n_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, size_t to_len) {
    return uz32n_replace_len_uz32n_uz32n_c(cstr, cstr_len, from, from_len, to_len, NULL);
}

size_t uz32n_replace_len_uz32n_uz32n_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(32, cstr, cstr_len, from, from_len, to_len, count);
}

size_t uz16_replace_uc16_uc16(uc16_t *cstr, uc16_t from, uc16_t to) {
    return uz16_replace_uc16_uc16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uc16_uc16_c(uc16_t *cstr, uc16_t from, uc16_t to, size_t *count) {
    USTR_RETURN_REPLACE_C_C_(cstr, from, to, count);
}

size_t uz16n_replace_uc16_uc16(uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to) {
    return uz16n_replace_uc16_uc16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16n_replace_uc16_uc16_c(uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count);
}

size_t uz16_replace_uz16_uc16(uc16_t *cstr, const uc16_t *from, uc16_t to) {
    return uz16_replace_uz16_uc16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uz16_uc16_c(uc16_t *cstr, const uc16_t *from, uc16_t to, size_t *count) {
	return uz16_replace_uz16n_uc16_c(cstr, from, uz16_len(from), to, count);
}

size_t uz16n_replace_uz16_uc16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to) {
    return uz16n_replace_uz16_uc16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16n_replace_uz16_uc16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to, size_t *count) {
	return uz16n_replace_uz16n_uc16_c(cstr, cstr_len, from, uz16_len(from), to, count);
}

size_t uz16_replace_uz16n_uc16(uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to) {
    return uz16_replace_uz16n_uc16_c(cstr, from, from_len, to, NULL);
}

size_t uz16_replace_uz16n_uc16_c(uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to, size_t *count) {
    return uz16n_replace_uz16n_uc16_c(cstr, uz16_len(cstr), from, from_len, to, count);
}

size_t uz16n_replace_uz16n_uc16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to) {
    return uz16n_replace_uz16n_uc16_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz16n_replace_uz16n_uc16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_C_(16, cstr, cstr_len, from, from_len, to, count);
}

size_t uz16_replace_uc16_uz16(uc16_t *cstr, uc16_t from, const uc16_t *to) {
    return uz16_replace_uc16_uz16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uc16_uz16_c(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16n_replace_uc16_uz16n_c(cstr, uz16_len(cstr), from, to, uz16_len(to), count);
}

size_t uz16_replace_len_uc16_uz16(const uc16_t *cstr, uc16_t from, const uc16_t *to) {
    return uz16_replace_len_uc16_uz16_c(cstr, from, to, NULL);
}

size_t uz16_replace_len_uc16_uz16_c(const uc16_t *cstr, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16n_replace_len_uc16_uz16n_c(cstr, uz16_len(cstr), from, uz16_len(to), count);
}

size_t uz16n_replace_uc16_uz16(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to) {
    return uz16n_replace_uc16_uz16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16n_replace_uc16_uz16_c(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16n_replace_uc16_uz16n_c(cstr, cstr_len, from, to, uz16_len(to), count);
}

size_t uz16n_replace_len_uc16_uz16(const uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to) {
    return uz16n_replace_len_uc16_uz16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16n_replace_len_uc16_uz16_c(const uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16n_replace_len_uc16_uz16n_c(cstr, cstr_len, from, uz16_len(to), count);
}

size_t uz16_replace_uc16_uz16n(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t to_len) {
    return uz16_replace_uc16_uz16n_c(cstr, from, to, to_len, NULL);
}

size_t uz16_replace_uc16_uz16n_c(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16n_replace_uc16_uz16n_c(cstr, uz16_len(cstr), from, to, to_len, count);
}

size_t uz16_replace_len_uc16_uz16n(const uc16_t *cstr, uc16_t from, size_t to_len) {
    return uz16_replace_len_uc16_uz16n_c(cstr, from, to_len, NULL);
}

size_t uz16_replace_len_uc16_uz16n_c(const uc16_t *cstr, uc16_t from, size_t to_len, size_t *count) {
	return uz16n_replace_len_uc16_uz16n_c(cstr, uz16_len(cstr), from, to_len, count);
}

size_t uz16n_replace_uc16_uz16n(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t to_len) {
    return uz16n_replace_uc16_uz16n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz16n_replace_uc16_uz16n_c(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_(16, cstr, cstr_len, from, to, to_len, count);
}

size_t uz16n_replace_len_uc16_uz16n(const uc16_t *cstr, size_t cstr_len, uc16_t from, size_t to_len) {
    return uz16n_replace_len_uc16_uz16n_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz16n_replace_len_uc16_uz16n_c(const uc16_t *cstr, size_t cstr_len, uc16_t from, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count);
}

size_t uz16_replace_uz16_uz16(uc16_t *cstr, const uc16_t *from, const uc16_t *to) {
    return uz16_replace_uz16_uz16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uz16_uz16_c(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16n_replace_uz16n_uz16n_c(cstr, uz16_len(cstr), from, uz16_len(from), to, uz16_len(to), count);
}

size_t uz16_replace_len_uz16_uz16(const uc16_t *cstr, const uc16_t *from, const uc16_t *to) {
    return uz16_replace_len_uz16_uz16_c(cstr, from, to, NULL);
}

size_t uz16_replace_len_uz16_uz16_c(const uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16n_replace_len_uz16n_uz16n_c(cstr, uz16_len(cstr), from, uz16_len(from), uz16_len(to), count);
}

size_t uz16n_replace_uz16_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to) {
    return uz16n_replace_uz16_uz16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16n_replace_uz16_uz16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16n_replace_uz16n_uz16n_c(cstr, cstr_len, from, uz16_len(from), to, uz16_len(to), count);
}

size_t uz16n_replace_len_uz16_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to) {
    return uz16n_replace_len_uz16_uz16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16n_replace_len_uz16_uz16_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16n_replace_len_uz16n_uz16n_c(cstr, cstr_len, from, uz16_len(from), uz16_len(to), count);
}

size_t uz16_replace_uz16n_uz16(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16_replace_uz16n_uz16_c(cstr, from, from_len, to, NULL);
}

size_t uz16_replace_uz16n_uz16_c(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16n_replace_uz16n_uz16n_c(cstr, uz16_len(cstr), from, from_len, to, uz16_len(to), count);
}

size_t uz16_replace_len_uz16n_uz16(const uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16_replace_len_uz16n_uz16_c(cstr, from, from_len, to, NULL);
}

size_t uz16_replace_len_uz16n_uz16_c(const uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16n_replace_len_uz16n_uz16n_c(cstr, uz16_len(cstr), from, from_len, uz16_len(to), count);
}

size_t uz16n_replace_uz16n_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16n_replace_uz16n_uz16_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz16n_replace_uz16n_uz16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16n_replace_uz16n_uz16n_c(cstr, cstr_len, from, from_len, to, uz16_len(to), count);
}

size_t uz16n_replace_len_uz16n_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16n_replace_len_uz16n_uz16_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz16n_replace_len_uz16n_uz16_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16n_replace_len_uz16n_uz16n_c(cstr, cstr_len, from, from_len, uz16_len(to), count);
}

size_t uz16_replace_uz16_uz16n(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t to_len) {
    return uz16_replace_uz16_uz16n_c(cstr, from, to, to_len, NULL);
}

size_t uz16_replace_uz16_uz16n_c(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16n_replace_uz16n_uz16n_c(cstr, uz16_len(cstr), from, uz16_len(from), to, to_len, count);
}

size_t uz16_replace_len_uz16_uz16n(const uc16_t *cstr, const uc16_t *from, size_t to_len) {
    return uz16_replace_len_uz16_uz16n_c(cstr, from, to_len, NULL);
}

size_t uz16_replace_len_uz16_uz16n_c(const uc16_t *cstr, const uc16_t *from, size_t to_len, size_t *count) {
	return uz16n_replace_len_uz16n_uz16n_c(cstr, uz16_len(cstr), from, uz16_len(from), to_len, count);
}

size_t uz16n_replace_uz16_uz16n(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t to_len) {
    return uz16n_replace_uz16_uz16n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz16n_replace_uz16_uz16n_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16n_replace_uz16n_uz16n_c(cstr, cstr_len, from, uz16_len(from), to, to_len, count);
}

size_t uz16n_replace_len_uz16_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t to_len) {
    return uz16n_replace_len_uz16_uz16n_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz16n_replace_len_uz16_uz16n_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t to_len, size_t *count) {
	return uz16n_replace_len_uz16n_uz16n_c(cstr, cstr_len, from, uz16_len(from), to_len, count);
}

size_t uz16_replace_uz16n_uz16n(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len) {
    return uz16_replace_uz16n_uz16n_c(cstr, from, from_len, to, to_len, NULL);
}

size_t uz16_replace_uz16n_uz16n_c(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16n_replace_uz16n_uz16n_c(cstr, uz16_len(cstr), from, from_len, to, to_len, count);
}

size_t uz16_replace_len_uz16n_uz16n(const uc16_t *cstr, const uc16_t *from, size_t from_len, size_t to_len) {
    return uz16_replace_len_uz16n_uz16n_c(cstr, from, from_len, to_len, NULL);
}

size_t uz16_replace_len_uz16n_uz16n_c(const uc16_t *cstr, const uc16_t *from, size_t from_len, size_t to_len, size_t *count) {
	return uz16n_replace_len_uz16n_uz16n_c(cstr, uz16_len(cstr), from, from_len, to_len, count);
}

size_t uz16n_replace_uz16n_uz16n(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len) {
    return uz16n_replace_uz16n_uz16n_c(cstr, cstr_len, from, from_len, to, to_len, NULL);
}

size_t uz16n_replace_uz16n_uz16n_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_(16, cstr, cstr_len, from, from_len, to, to_len, count);
}

size_t uz16n_replace_len_uz16n_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, size_t to_len) {
    return uz16n_replace_len_uz16n_uz16n_c(cstr, cstr_len, from, from_len, to_len, NULL);
}

size_t uz16n_replace_len_uz16n_uz16n_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(16, cstr, cstr_len, from, from_len, to_len, count);
}

size_t uz8_replace_uc8_uc8(uc8_t *cstr, uc8_t from, uc8_t to) {
    return uz8_replace_uc8_uc8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uc8_uc8_c(uc8_t *cstr, uc8_t from, uc8_t to, size_t *count) {
    USTR_RETURN_REPLACE_C_C_(cstr, from, to, count);
}

size_t uz8n_replace_uc8_uc8(uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to) {
    return uz8n_replace_uc8_uc8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8n_replace_uc8_uc8_c(uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count);
}

size_t uz8_replace_uz8_uc8(uc8_t *cstr, const uc8_t *from, uc8_t to) {
    return uz8_replace_uz8_uc8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uz8_uc8_c(uc8_t *cstr, const uc8_t *from, uc8_t to, size_t *count) {
	return uz8_replace_uz8n_uc8_c(cstr, from, uz8_len(from), to, count);
}

size_t uz8n_replace_uz8_uc8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to) {
    return uz8n_replace_uz8_uc8_c(cstr, cstr_len, from, to, NULL);
}
    
size_t uz8n_replace_uz8_uc8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to, size_t *count) {
	return uz8n_replace_uz8n_uc8_c(cstr, cstr_len, from, uz8_len(from), to, count);
}

size_t uz8_replace_uz8n_uc8(uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to) {
    return uz8_replace_uz8n_uc8_c(cstr, from, from_len, to, NULL);
}

size_t uz8_replace_uz8n_uc8_c(uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to, size_t *count) {
    return uz8n_replace_uz8n_uc8_c(cstr, uz8_len(cstr), from, from_len, to, count);
}

size_t uz8n_replace_uz8n_uc8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to) {
    return uz8n_replace_uz8n_uc8_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz8n_replace_uz8n_uc8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_C_(8, cstr, cstr_len, from, from_len, to, count);
}

size_t uz8_replace_uc8_uz8(uc8_t *cstr, uc8_t from, const uc8_t *to) {
    return uz8_replace_uc8_uz8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uc8_uz8_c(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8n_replace_uc8_uz8n_c(cstr, uz8_len(cstr), from, to, uz8_len(to), count);
}

size_t uz8_replace_len_uc8_uz8(const uc8_t *cstr, uc8_t from, const uc8_t *to) {
    return uz8_replace_len_uc8_uz8_c(cstr, from, to, NULL);
}

size_t uz8_replace_len_uc8_uz8_c(const uc8_t *cstr, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8n_replace_len_uc8_uz8n_c(cstr, uz8_len(cstr), from, uz8_len(to), count);
}

size_t uz8n_replace_uc8_uz8(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to) {
    return uz8n_replace_uc8_uz8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8n_replace_uc8_uz8_c(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8n_replace_uc8_uz8n_c(cstr, cstr_len, from, to, uz8_len(to), count);
}

size_t uz8n_replace_len_uc8_uz8(const uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to) {
    return uz8n_replace_len_uc8_uz8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8n_replace_len_uc8_uz8_c(const uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8n_replace_len_uc8_uz8n_c(cstr, cstr_len, from, uz8_len(to), count);
}

size_t uz8_replace_uc8_uz8n(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t to_len) {
    return uz8_replace_uc8_uz8n_c(cstr, from, to, to_len, NULL);
}

size_t uz8_replace_uc8_uz8n_c(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8n_replace_uc8_uz8n_c(cstr, uz8_len(cstr), from, to, to_len, count);
}

size_t uz8_replace_len_uc8_uz8n(const uc8_t *cstr, uc8_t from, size_t to_len) {
    return uz8_replace_len_uc8_uz8n_c(cstr, from, to_len, NULL);
}

size_t uz8_replace_len_uc8_uz8n_c(const uc8_t *cstr, uc8_t from, size_t to_len, size_t *count) {
	return uz8n_replace_len_uc8_uz8n_c(cstr, uz8_len(cstr), from, to_len, count);
}

size_t uz8n_replace_uc8_uz8n(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t to_len) {
    return uz8n_replace_uc8_uz8n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz8n_replace_uc8_uz8n_c(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_(8, cstr, cstr_len, from, to, to_len, count);
}

size_t uz8n_replace_len_uc8_uz8n(const uc8_t *cstr, size_t cstr_len, uc8_t from, size_t to_len) {
    return uz8n_replace_len_uc8_uz8n_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz8n_replace_len_uc8_uz8n_c(const uc8_t *cstr, size_t cstr_len, uc8_t from, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count);
}

size_t uz8_replace_uz8_uz8(uc8_t *cstr, const uc8_t *from, const uc8_t *to) {
    return uz8_replace_uz8_uz8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uz8_uz8_c(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8n_replace_uz8n_uz8n_c(cstr, uz8_len(cstr), from, uz8_len(from), to, uz8_len(to), count);
}

size_t uz8_replace_len_uz8_uz8(const uc8_t *cstr, const uc8_t *from, const uc8_t *to) {
    return uz8_replace_len_uz8_uz8_c(cstr, from, to, NULL);
}

size_t uz8_replace_len_uz8_uz8_c(const uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8n_replace_len_uz8n_uz8n_c(cstr, uz8_len(cstr), from, uz8_len(from), uz8_len(to), count);
}

size_t uz8n_replace_uz8_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to) {
    return uz8n_replace_uz8_uz8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8n_replace_uz8_uz8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8n_replace_uz8n_uz8n_c(cstr, cstr_len, from, uz8_len(from), to, uz8_len(to), count);
}

size_t uz8n_replace_len_uz8_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to) {
    return uz8n_replace_len_uz8_uz8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8n_replace_len_uz8_uz8_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8n_replace_len_uz8n_uz8n_c(cstr, cstr_len, from, uz8_len(from), uz8_len(to), count);
}

size_t uz8_replace_uz8n_uz8(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8_replace_uz8n_uz8_c(cstr, from, from_len, to, NULL);
}

size_t uz8_replace_uz8n_uz8_c(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8n_replace_uz8n_uz8n_c(cstr, uz8_len(cstr), from, from_len, to, uz8_len(to), count);
}

size_t uz8_replace_len_uz8n_uz8(const uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8_replace_len_uz8n_uz8_c(cstr, from, from_len, to, NULL);
}

size_t uz8_replace_len_uz8n_uz8_c(const uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8n_replace_len_uz8n_uz8n_c(cstr, uz8_len(cstr), from, from_len, uz8_len(to), count);
}

size_t uz8n_replace_uz8n_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8n_replace_uz8n_uz8_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz8n_replace_uz8n_uz8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8n_replace_uz8n_uz8n_c(cstr, cstr_len, from, from_len, to, uz8_len(to), count);
}

size_t uz8n_replace_len_uz8n_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8n_replace_len_uz8n_uz8_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz8n_replace_len_uz8n_uz8_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8n_replace_len_uz8n_uz8n_c(cstr, cstr_len, from, from_len, uz8_len(to), count);
}

size_t uz8_replace_uz8_uz8n(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t to_len) {
    return uz8_replace_uz8_uz8n_c(cstr, from, to, to_len, NULL);
}

size_t uz8_replace_uz8_uz8n_c(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8n_replace_uz8n_uz8n_c(cstr, uz8_len(cstr), from, uz8_len(from), to, to_len, count);
}

size_t uz8_replace_len_uz8_uz8n(const uc8_t *cstr, const uc8_t *from, size_t to_len) {
    return uz8_replace_len_uz8_uz8n_c(cstr, from, to_len, NULL);
}

size_t uz8_replace_len_uz8_uz8n_c(const uc8_t *cstr, const uc8_t *from, size_t to_len, size_t *count) {
	return uz8n_replace_len_uz8n_uz8n_c(cstr, uz8_len(cstr), from, uz8_len(from), to_len, count);
}

size_t uz8n_replace_uz8_uz8n(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t to_len) {
    return uz8n_replace_uz8_uz8n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz8n_replace_uz8_uz8n_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8n_replace_uz8n_uz8n_c(cstr, cstr_len, from, uz8_len(from), to, to_len, count);
}

size_t uz8n_replace_len_uz8_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t to_len) {
    return uz8n_replace_len_uz8_uz8n_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz8n_replace_len_uz8_uz8n_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t to_len, size_t *count) {
	return uz8n_replace_len_uz8n_uz8n_c(cstr, cstr_len, from, uz8_len(from), to_len, count);
}

size_t uz8_replace_uz8n_uz8n(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len) {
    return uz8_replace_uz8n_uz8n_c(cstr, from, from_len, to, to_len, NULL);
}

size_t uz8_replace_uz8n_uz8n_c(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8n_replace_uz8n_uz8n_c(cstr, uz8_len(cstr), from, from_len, to, to_len, count);
}

size_t uz8_replace_len_uz8n_uz8n(const uc8_t *cstr, const uc8_t *from, size_t from_len, size_t to_len) {
    return uz8_replace_len_uz8n_uz8n_c(cstr, from, from_len, to_len, NULL);
}

size_t uz8_replace_len_uz8n_uz8n_c(const uc8_t *cstr, const uc8_t *from, size_t from_len, size_t to_len, size_t *count) {
    return uz8n_replace_len_uz8n_uz8n_c(cstr, uz8_len(cstr), from, from_len, to_len, count);
}

size_t uz8n_replace_uz8n_uz8n(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len) {
    return uz8n_replace_uz8n_uz8n_c(cstr, cstr_len, from, from_len, to, to_len, NULL);
}

size_t uz8n_replace_uz8n_uz8n_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_(8, cstr, cstr_len, from, from_len, to, to_len, count);
}

size_t uz8n_replace_len_uz8n_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, size_t to_len) {
    return uz8n_replace_len_uz8n_uz8n_c(cstr, cstr_len, from, from_len, to_len, NULL);
}

size_t uz8n_replace_len_uz8n_uz8n_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(8, cstr, cstr_len, from, from_len, to_len, count);
}