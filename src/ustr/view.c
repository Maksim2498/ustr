#include "view.h"

#include <assert.h>

#include "fmt/case.h"
#include "cstr.h"
#include "str.h"
#include "view.h"
    
#define UVX_FROM_UZX(from, X)                 \
    return (uv##X##_t) {                      \
        .chars = from,                        \
        .len   = from ? uz##X##_len(from) : 0 \
    }

#define UVX_FROM_UZX_RANGE(from, begin, len, X)      \
    assert(uz##X##_ebounds_range(from, begin, len)); \
                                                     \
    return (uv##X##_t) {                             \
        .chars = from + begin,                       \
        .len   = len                                 \
    }

#define UVX_FROM_UZXN(from, from_len, X) \
    assert(from);                        \
                                         \
    return (uv##X##_t) {                 \
        .chars = from,                   \
        .len   = from_len                \
    }

#define UVX_FROM_UZXN_RANGE(from, from_len, begin, len, X) \
    assert(uebounds_range(from_len, begin, len));          \
                                                           \
    return (uv##X##_t) {                                   \
        .chars = from + begin,                             \
        .len   = len                                       \
    }

uv32_t uv32_from_uz32(uc32_t *from) {
    UVX_FROM_UZX(from, 32);
}

uv32_t uv32_from_uz32_range(uc32_t *from, size_t begin, size_t len) {
    UVX_FROM_UZX_RANGE(from, begin, len, 32);
}

uv32_t uv32_from_uz32n(uc32_t *from, size_t from_len) {
    UVX_FROM_UZXN(from, from_len, 32);
}

uv32_t uv32_from_uz32n_range(uc32_t *from, size_t from_len, size_t begin, size_t len) {
    UVX_FROM_UZXN_RANGE(from, from_len, begin, len, 32);
}

uv32_t uv32_from_uv32(uv32_t from) {
    return uv32_from_uz32n(UV32_EXPAND(from));
}

uv32_t uv32_from_uv32_range(uv32_t from, size_t begin, size_t len) {
    return uv32_from_uz32n_range(UV32_EXPAND(from), begin, len);
}

uv32_t uv32_from_us32(us32_t *from) {
    return uv32_from_uz32n(US32_EXPAND(from));
}

uv32_t uv32_from_us32_range(us32_t *from, size_t begin, size_t len) {
    return uv32_from_uz32n_range(US32_EXPAND(from), begin, len);
}

uv16_t uv16_from_uz16(uc16_t *from) {
    UVX_FROM_UZX(from, 16);
}

uv16_t uv16_from_uz16_range(uc16_t *from, size_t begin, size_t len) {
    UVX_FROM_UZX_RANGE(from, begin, len, 16);
}

uv16_t uv16_from_uz16n(uc16_t *from, size_t from_len) {
    UVX_FROM_UZXN(from, from_len, 16);
}

uv16_t uv16_from_uz16n_range(uc16_t *from, size_t from_len, size_t begin, size_t len) {
    UVX_FROM_UZXN_RANGE(from, from_len, begin, len, 16);
}

uv16_t uv16_from_uv16(uv16_t from) {
    return uv16_from_uz16n(UV16_EXPAND(from));
}

uv16_t uv16_from_uv16_range(uv16_t from, size_t begin, size_t len) {
    return uv16_from_uz16n_range(UV16_EXPAND(from), begin, len);
}

uv16_t uv16_from_us16(us16_t *from) {
    return uv16_from_uz16n(US16_EXPAND(from));
}

uv16_t uv16_from_us16_range(us16_t *from, size_t begin, size_t len) {
    return uv16_from_uz16n_range(US16_EXPAND(from), begin, len);
}

uv8_t uv8_from_uz8(uc8_t *from) {
    UVX_FROM_UZX(from, 8);
}

uv8_t uv8_from_uz8_range(uc8_t *from, size_t begin, size_t len) {
    UVX_FROM_UZX_RANGE(from, begin, len, 8);
}

uv8_t uv8_from_uz8n(uc8_t *from, size_t from_len) {
    UVX_FROM_UZXN(from, from_len, 8);
}

uv8_t uv8_from_uz8n_range(uc8_t *from, size_t from_len, size_t begin, size_t len) {
    UVX_FROM_UZXN_RANGE(from, from_len, begin, len, 8);
}

uv8_t uv8_from_uv8(uv8_t from) {
    return uv8_from_uz8n(UV8_EXPAND(from));
}

uv8_t uv8_from_uv8_range(uv8_t from, size_t begin, size_t len) {
    return uv8_from_uz8n_range(UV8_EXPAND(from), begin, len);
}

uv8_t uv8_from_us8(us8_t *from) {
    return uv8_from_uz8n(US8_EXPAND(from));
}

uv8_t uv8_from_us8_range(us8_t *from, size_t begin, size_t len) {
    return uv8_from_uz8n_range(US8_EXPAND(from), begin, len);
}

size_t uv32_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, uv32_t from) {
    return uz32n_to_bytes(to, encoding, UV32_CEXPAND(from));
}

size_t uv16_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, uv16_t from) {
    return uz16n_to_bytes(to, encoding, UV16_CEXPAND(from));
}

size_t uv8_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, uv8_t from) {
    return uz8n_to_bytes(to, encoding, UV8_CEXPAND(from));
}

size_t uv32_len(uv32_t view) {
    return uz32n_len(UV32_CEXPAND(view));
}

size_t uv32_len_n(uv32_t view, unsigned n) {
    return uz32n_len_n(UV32_CEXPAND(view), n);
}

size_t uv32_len_32(uv32_t view) {
    return uz32n_len_32(UV32_CEXPAND(view));
}

size_t uv32_len_16(uv32_t view) {
    return uz32n_len_16(UV32_CEXPAND(view));
}

size_t uv32_len_8(uv32_t view) {
    return uz32n_len_8(UV32_CEXPAND(view));
}

size_t uv16_len(uv16_t view) {
    return uz16n_len(UV16_CEXPAND(view));
}

size_t uv16_len_n(uv16_t view, unsigned n) {
    return uz16n_len_n(UV16_CEXPAND(view), n);
}

size_t uv16_len_32(uv16_t view) {
    return uz16n_len_32(UV16_CEXPAND(view));
}

size_t uv16_len_16(uv16_t view) {
    return uz16n_len_16(UV16_CEXPAND(view));
}

size_t uv16_len_8(uv16_t view) {
    return uz16n_len_8(UV16_CEXPAND(view));
}

size_t uv8_len(uv8_t view) {
    return uz8n_len(UV8_CEXPAND(view));
}

size_t uv8_len_n(uv8_t view, unsigned n) {
    return uz8n_len_n(UV8_CEXPAND(view), n);
}

size_t uv8_len_32(uv8_t view) {
    return uz8n_len_32(UV8_CEXPAND(view));
}

size_t uv8_len_16(uv8_t view) {
    return uz8n_len_16(UV8_CEXPAND(view));
}

size_t uv8_len_8(uv8_t view) {
    return uz8n_len_8(UV8_CEXPAND(view));
}

#define UVX_SET_LEN(view, len, X)                           \
    assert(uv##X##_valid_p(view) && (view->chars || !len)); \
    view->len = len

void uv32_set_len(uv32_t *view, size_t len) {
    UVX_SET_LEN(view, len, 32);
}

void uv16_set_len(uv16_t *view, size_t len) {
    UVX_SET_LEN(view, len, 16);
}

void uv8_set_len(uv8_t *view, size_t len) {
    UVX_SET_LEN(view, len, 8);
}

#define UVX_ADD_LEN(view, delta, X)                                   \
    assert(uv##X##_valid_p(view) && -(ptrdiff_t) view->len <= delta); \
    return view->len += delta

size_t uv32_add_len(uv32_t *view, ptrdiff_t delta) {
    UVX_ADD_LEN(view, delta, 32);
}

size_t uv16_add_len(uv16_t *view, ptrdiff_t delta) {
    UVX_ADD_LEN(view, delta, 16);
}

size_t uv8_add_len(uv8_t *view, ptrdiff_t delta) {
    UVX_ADD_LEN(view, delta, 8);
}

int uv32_cmp_uc32(uv32_t lhs, uc32_t rhs) {
    return uz32n_cmp_uc32(UV32_CEXPAND(lhs), rhs);
}

int uv32_cmp_uz32(uv32_t lhs, const uc32_t *rhs) {
    return uz32n_cmp_uz32(UV32_CEXPAND(lhs), rhs);
}

int uv32_cmp_uz32n(uv32_t lhs, const uc32_t *rhs, size_t rhs_len) {
    return uz32n_cmp_uz32n(UV32_CEXPAND(lhs), rhs, rhs_len);
}

int uv32_cmp_ucv32(uv32_t lhs, ucv32_t rhs) {
    return uz32n_cmp_ucv32(UV32_CEXPAND(lhs), rhs);
}

int uv32_cmp_uv32(uv32_t lhs, uv32_t rhs) {
    return uz32n_cmp_uv32(UV32_CEXPAND(lhs), rhs);
}

int uv32_cmp_us32(uv32_t lhs, const us32_t *rhs) {
    return uz32n_cmp_us32(UV32_CEXPAND(lhs), rhs);
}

int uv16_cmp_uc16(uv16_t lhs, uc16_t rhs) {
    return uz16n_cmp_uc16(UV16_CEXPAND(lhs), rhs);
}

int uv16_cmp_uz16(uv16_t lhs, const uc16_t *rhs) {
    return uz16n_cmp_uz16(UV16_CEXPAND(lhs), rhs);
}

int uv16_cmp_uz16n(uv16_t lhs, const uc16_t *rhs, size_t rhs_len) {
    return uz16n_cmp_uz16n(UV16_CEXPAND(lhs), rhs, rhs_len);
}

int uv16_cmp_ucv16(uv16_t lhs, ucv16_t rhs) {
    return uz16n_cmp_ucv16(UV16_CEXPAND(lhs), rhs);
}

int uv16_cmp_uv16(uv16_t lhs, uv16_t rhs) {
    return uz16n_cmp_uv16(UV16_CEXPAND(lhs), rhs);
}

int uv16_cmp_us16(uv16_t lhs, const us16_t *rhs) {
    return uz16n_cmp_us16(UV16_CEXPAND(lhs), rhs);
}

int uv8_cmp_uc8(uv8_t lhs, uc8_t rhs) {
    return uz8n_cmp_uc8(UV8_CEXPAND(lhs), rhs);
}

int uv8_cmp_uz8(uv8_t lhs, const uc8_t *rhs) {
    return uz8n_cmp_uz8(UV8_CEXPAND(lhs), rhs);
}

int uv8_cmp_uz8n(uv8_t lhs, const uc8_t *rhs, size_t rhs_len) {
    return uz8n_cmp_uz8n(UV8_CEXPAND(lhs), rhs, rhs_len);
}

int uv8_cmp_ucv8(uv8_t lhs, ucv8_t rhs) {
    return uz8n_cmp_ucv8(UV8_CEXPAND(lhs), rhs);
}

int uv8_cmp_uv8(uv8_t lhs, uv8_t rhs) {
    return uz8n_cmp_uv8(UV8_CEXPAND(lhs), rhs);
}

int uv8_cmp_us8(uv8_t lhs, const us8_t *rhs) {
    return uz8n_cmp_us8(UV8_CEXPAND(lhs), rhs);
}

void uv32_fill_uc32(uv32_t view, uc32_t with) {
    return uz32n_fill_uc32(UV32_EXPAND(view), with);
}

void uv32_fill_uz32(uv32_t view, const uc32_t *with) {
    return uz32n_fill_uz32(UV32_EXPAND(view), with);
}

void uv32_fill_uz32n(uv32_t view, const uc32_t *with, size_t with_len) {
    return uz32n_fill_uz32n(UV32_EXPAND(view), with, with_len);
}

void uv32_fill_ucv32(uv32_t view, ucv32_t with) {
    return uz32n_fill_ucv32(UV32_EXPAND(view), with);
}

void uv32_fill_uv32(uv32_t view, uv32_t with) {
    return uz32n_fill_uv32(UV32_EXPAND(view), with);
}

void uv32_fill_us32(uv32_t view, const us32_t *with) {
    return uz32n_fill_us32(UV32_EXPAND(view), with);
}

void uv16_fill_uc16(uv16_t view, uc16_t with) {
    return uz16n_fill_uc16(UV16_EXPAND(view), with);
}

void uv16_fill_uz16(uv16_t view, const uc16_t *with) {
    return uz16n_fill_uz16(UV16_EXPAND(view), with);
}

void uv16_fill_uz16n(uv16_t view, const uc16_t *with, size_t with_len) {
    return uz16n_fill_uz16n(UV16_EXPAND(view), with, with_len);
}

void uv16_fill_ucv16(uv16_t view, ucv16_t with) {
    return uz16n_fill_ucv16(UV16_EXPAND(view), with);
}

void uv16_fill_uv16(uv16_t view, uv16_t with) {
    return uz16n_fill_uv16(UV16_EXPAND(view), with);
}

void uv16_fill_us16(uv16_t view, const us16_t *with) {
    return uz16n_fill_us16(UV16_EXPAND(view), with);
}

void uv8_fill_uc8(uv8_t view, uc8_t with) {
    return uz8n_fill_uc8(UV8_EXPAND(view), with);
}

void uv8_fill_uz8(uv8_t view, const uc8_t *with) {
    return uz8n_fill_uz8(UV8_EXPAND(view), with);
}

void uv8_fill_uz8n(uv8_t view, const uc8_t *with, size_t with_len) {
    return uz8n_fill_uz8n(UV8_EXPAND(view), with, with_len);
}

void uv8_fill_ucv8(uv8_t view, ucv8_t with) {
    return uz8n_fill_ucv8(UV8_EXPAND(view), with);
}

void uv8_fill_uv8(uv8_t view, uv8_t with) {
    return uz8n_fill_uv8(UV8_EXPAND(view), with);
}

void uv8_fill_us8(uv8_t view, const us8_t *with) {
    return uz8n_fill_us8(UV8_EXPAND(view), with);
}

size_t uv32_wspace_len(uv32_t view) {
    return uz32n_wspace_len(UV32_CEXPAND(view));
}

size_t uv16_wspace_len(uv16_t view) {
    return uz16n_wspace_len(UV16_CEXPAND(view));
}

size_t uv8_wspace_len(uv8_t view) {
    return uz8n_wspace_len(UV8_CEXPAND(view));
}

#define UVX_TRIM(view, X)       \
    return uv##X##_ltrim(view), \
           uv##X##_rtrim(view)
    
#define UVX_LTRIM(view, X)                                           \
    assert(uv##X##_valid_p(view));                                   \
                                                                     \
    size_t wspace_len = uz##X##n_wspace_len(UV##X##_CEXPAND(*view)); \
                                                                     \
    view->chars += wspace_len;                                       \
    view->len   -= wspace_len;                                       \
                                                                     \
    return view->len

#define UVX_RTRIM(view, X)                                    \
    assert(uv##X##_valid_p(view));                            \
    return view->len = uz##X##n_rtrim(UV##X##_CEXPAND(*view))

size_t uv32_trim(uv32_t *view) {
    UVX_TRIM(view, 32);
}

size_t uv32_ltrim(uv32_t *view) {
    UVX_LTRIM(view, 32);
}

size_t uv32_rtrim(uv32_t *view) {
    UVX_RTRIM(view, 32);
}

size_t uv16_trim(uv16_t *view) {
    UVX_TRIM(view, 16);
}

size_t uv16_ltrim(uv16_t *view) {
    UVX_LTRIM(view, 16);
}

size_t uv16_rtrim(uv16_t *view) {
    UVX_RTRIM(view, 16);
}

size_t uv8_trim(uv8_t *view) {
    UVX_TRIM(view, 8);
}

size_t uv8_ltrim(uv8_t *view) {
    UVX_LTRIM(view, 8);
}

size_t uv8_rtrim(uv8_t *view) {
    UVX_RTRIM(view, 8);
}

#define UVX_TO_CASE(view, ca, X)                           \
    assert(uv##X##_valid(view) && ucase_valid(ca));        \
                                                           \
    if (!view.chars)                                       \
        return;                                            \
                                                           \
    uz##X##n_to_case(view.chars, view.chars, view.len, ca)

#define UVX_TO_C(view, X, C)                          \
    assert(uv##X##_valid(view));                      \
                                                      \
    if (!view.chars)                                  \
        return;                                       \
                                                      \
    uz##X##n_to_##C(view.chars, view.chars, view.len)

void uv32_to_case(uv32_t view, ucase_t ca) {
    UVX_TO_CASE(view, ca, 32);
}

void uv32_to_lower(uv32_t view) {
    UVX_TO_C(view, 32, lower);
}

void uv32_to_upper(uv32_t view) {
    UVX_TO_C(view, 32, upper);
}

void uv16_to_case(uv16_t view, ucase_t ca) {
    UVX_TO_CASE(view, ca, 16);
}

void uv16_to_lower(uv16_t view) {
    UVX_TO_C(view, 16, lower);
}

void uv16_to_upper(uv16_t view) {
    UVX_TO_C(view, 16, upper);
}

size_t uv8_case_len(uv8_t view, ucase_t ca) {
    return uz8n_case_len(UV8_CEXPAND(view), ca);
}

size_t uv8_lower_len(uv8_t view) {
    return uz8n_lower_len(UV8_CEXPAND(view));
}

size_t uv8_upper_len(uv8_t view) {
    return uz8n_upper_len(UV8_CEXPAND(view));
}

size_t uv32_new_csplit_uc32(uv32_t view, uc32_t sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uc32(UV32_CEXPAND(view), sep, array);
}

size_t uv32_new_csplit_uc32_e(uv32_t view, uc32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uc32_e(UV32_CEXPAND(view), sep, array, error);
}

size_t uv32_csplit_uc32(uv32_t view, uc32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uc32(UV32_CEXPAND(view), sep, array, array_len);
}

size_t uv32_new_csplit_uz32(uv32_t view, const uc32_t *sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uz32(UV32_CEXPAND(view), sep, array);
}

size_t uv32_new_csplit_uz32_e(uv32_t view, const uc32_t *sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32_e(UV32_CEXPAND(view), sep, array, error);
}

size_t uv32_csplit_uz32(uv32_t view, const uc32_t *sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32(UV32_CEXPAND(view), sep, array, array_len);
}

size_t uv32_new_csplit_uz32n(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uz32n(UV32_CEXPAND(view), sep, sep_len, array);
}

size_t uv32_new_csplit_uz32n_e(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(UV32_CEXPAND(view), sep, sep_len, array, error);
}

size_t uv32_csplit_uz32n(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(UV32_CEXPAND(view), sep, sep_len, array, array_len);
}

size_t uv32_new_csplit_ucv32(uv32_t view, ucv32_t sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_ucv32(UV32_CEXPAND(view), sep, array);
}

size_t uv32_new_csplit_ucv32_e(uv32_t view, ucv32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_ucv32_e(UV32_CEXPAND(view), sep, array, error);
}

size_t uv32_csplit_ucv32(uv32_t view, ucv32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_ucv32(UV32_CEXPAND(view), sep, array, array_len);
}

size_t uv32_new_csplit_uv32(uv32_t view, uv32_t sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uv32(UV32_CEXPAND(view), sep, array);
}

size_t uv32_new_csplit_uv32_e(uv32_t view, uv32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uv32_e(UV32_CEXPAND(view), sep, array, error);
}

size_t uv32_csplit_uv32(uv32_t view, uv32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uv32(UV32_CEXPAND(view), sep, array, array_len);
}

size_t uv32_new_csplit_us32(uv32_t view, const us32_t *sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_us32(UV32_CEXPAND(view), sep, array);
}

size_t uv32_new_csplit_us32_e(uv32_t view, const us32_t *sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_us32_e(UV32_CEXPAND(view), sep, array, error);
}

size_t uv32_csplit_us32(uv32_t view, const us32_t *sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_us32(UV32_CEXPAND(view), sep, array, array_len);
}

size_t uv32_new_split_uc32(uv32_t view, uc32_t sep, UNULLABLE uv32_t **array) {
    return uz32n_new_split_uc32(UV32_EXPAND(view), sep, array);
}

size_t uv32_new_split_uc32_e(uv32_t view, uc32_t sep, UNULLABLE uv32_t **array, bool *error) {
    return uz32n_new_split_uc32_e(UV32_EXPAND(view), sep, array, error);
}

size_t uv32_split_uc32(uv32_t view, uc32_t sep, UNULLABLE uv32_t *array, size_t array_len) {
    return uz32n_split_uc32(UV32_EXPAND(view), sep, array, array_len);
}

size_t uv32_new_split_uz32(uv32_t view, const uc32_t *sep, UNULLABLE uv32_t **array) {
    return uz32n_new_split_uz32(UV32_EXPAND(view), sep, array);
}

size_t uv32_new_split_uz32_e(uv32_t view, const uc32_t *sep, UNULLABLE uv32_t **array, bool *error) {
    return uz32n_new_split_uz32_e(UV32_EXPAND(view), sep, array, error);
}

size_t uv32_split_uz32(uv32_t view, const uc32_t *sep, UNULLABLE uv32_t *array, size_t array_len) {
    return uz32n_split_uz32(UV32_EXPAND(view), sep, array, array_len);
}

size_t uv32_new_split_uz32n(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array) {
    return uz32n_new_split_uz32n(UV32_EXPAND(view), sep, sep_len, array);
}

size_t uv32_new_split_uz32n_e(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array, bool *error) {
    return uz32n_new_split_uz32n_e(UV32_EXPAND(view), sep, sep_len, array, error);
}

size_t uv32_split_uz32n(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t *array, size_t array_len) {
    return uz32n_split_uz32n(UV32_EXPAND(view), sep, sep_len, array, array_len);
}

size_t uv32_new_split_ucv32(uv32_t view, ucv32_t sep, UNULLABLE uv32_t **array) {
    return uz32n_new_split_ucv32(UV32_EXPAND(view), sep, array);
}

size_t uv32_new_split_ucv32_e(uv32_t view, ucv32_t sep, UNULLABLE uv32_t **array, bool *error) {
    return uz32n_new_split_ucv32_e(UV32_EXPAND(view), sep, array, error);
}

size_t uv32_split_ucv32(uv32_t view, ucv32_t sep, UNULLABLE uv32_t *array, size_t array_len) {
    return uz32n_split_ucv32(UV32_EXPAND(view), sep, array, array_len);
}

size_t uv32_new_split_uv32(uv32_t view, uv32_t sep, UNULLABLE uv32_t **array) {
    return uz32n_new_split_uv32(UV32_EXPAND(view), sep, array);
}

size_t uv32_new_split_uv32_e(uv32_t view, uv32_t sep, UNULLABLE uv32_t **array, bool *error) {
    return uz32n_new_split_uv32_e(UV32_EXPAND(view), sep, array, error);
}

size_t uv32_split_uv32(uv32_t view, uv32_t sep, UNULLABLE uv32_t *array, size_t array_len) {
    return uz32n_split_uv32(UV32_EXPAND(view), sep, array, array_len);
}

size_t uv32_new_split_us32(uv32_t view, const us32_t *sep, UNULLABLE uv32_t **array) {
    return uz32n_new_split_us32(UV32_EXPAND(view), sep, array);
}

size_t uv32_new_split_us32_e(uv32_t view, const us32_t *sep, UNULLABLE uv32_t **array, bool *error) {
    return uz32n_new_split_us32_e(UV32_EXPAND(view), sep, array, error);
}

size_t uv32_split_us32(uv32_t view, const us32_t *sep, UNULLABLE uv32_t *array, size_t array_len) {
    return uz32n_split_us32(UV32_EXPAND(view), sep, array, array_len);
}

size_t uv16_new_csplit_uc16(uv16_t view, uc16_t sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uc16(UV16_CEXPAND(view), sep, array);
}

size_t uv16_new_csplit_uc16_e(uv16_t view, uc16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uc16_e(UV16_CEXPAND(view), sep, array, error);
}

size_t uv16_csplit_uc16(uv16_t view, uc16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uc16(UV16_CEXPAND(view), sep, array, array_len);
}

size_t uv16_new_csplit_uz16(uv16_t view, const uc16_t *sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uz16(UV16_CEXPAND(view), sep, array);
}

size_t uv16_new_csplit_uz16_e(uv16_t view, const uc16_t *sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uz16_e(UV16_CEXPAND(view), sep, array, error);
}

size_t uv16_csplit_uz16(uv16_t view, const uc16_t *sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uz16(UV16_CEXPAND(view), sep, array, array_len);
}

size_t uv16_new_csplit_uz16n(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uz16n(UV16_CEXPAND(view), sep, sep_len, array);
}

size_t uv16_new_csplit_uz16n_e(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uz16n_e(UV16_CEXPAND(view), sep, sep_len, array, error);
}

size_t uv16_csplit_uz16n(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uz16n(UV16_CEXPAND(view), sep, sep_len, array, array_len);
}

size_t uv16_new_csplit_ucv16(uv16_t view, ucv16_t sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_ucv16(UV16_CEXPAND(view), sep, array);
}

size_t uv16_new_csplit_ucv16_e(uv16_t view, ucv16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_ucv16_e(UV16_CEXPAND(view), sep, array, error);
}

size_t uv16_csplit_ucv16(uv16_t view, ucv16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_ucv16(UV16_CEXPAND(view), sep, array, array_len);
}

size_t uv16_new_csplit_uv16(uv16_t view, uv16_t sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uv16(UV16_CEXPAND(view), sep, array);
}

size_t uv16_new_csplit_uv16_e(uv16_t view, uv16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uv16_e(UV16_CEXPAND(view), sep, array, error);
}

size_t uv16_csplit_uv16(uv16_t view, uv16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uv16(UV16_CEXPAND(view), sep, array, array_len);
}

size_t uv16_new_csplit_us16(uv16_t view, const us16_t *sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_us16(UV16_CEXPAND(view), sep, array);
}

size_t uv16_new_csplit_us16_e(uv16_t view, const us16_t *sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_us16_e(UV16_CEXPAND(view), sep, array, error);
}

size_t uv16_csplit_us16(uv16_t view, const us16_t *sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_us16(UV16_CEXPAND(view), sep, array, array_len);
}

size_t uv16_new_split_uc16(uv16_t view, uc16_t sep, UNULLABLE uv16_t **array) {
    return uz16n_new_split_uc16(UV16_EXPAND(view), sep, array);
}

size_t uv16_new_split_uc16_e(uv16_t view, uc16_t sep, UNULLABLE uv16_t **array, bool *error) {
    return uz16n_new_split_uc16_e(UV16_EXPAND(view), sep, array, error);
}

size_t uv16_split_uc16(uv16_t view, uc16_t sep, UNULLABLE uv16_t *array, size_t array_len) {
    return uz16n_split_uc16(UV16_EXPAND(view), sep, array, array_len);
}

size_t uv16_new_split_uz16(uv16_t view, const uc16_t *sep, UNULLABLE uv16_t **array) {
    return uz16n_new_split_uz16(UV16_EXPAND(view), sep, array);
}

size_t uv16_new_split_uz16_e(uv16_t view, const uc16_t *sep, UNULLABLE uv16_t **array, bool *error) {
    return uz16n_new_split_uz16_e(UV16_EXPAND(view), sep, array, error);
}

size_t uv16_split_uz16(uv16_t view, const uc16_t *sep, UNULLABLE uv16_t *array, size_t array_len) {
    return uz16n_split_uz16(UV16_EXPAND(view), sep, array, array_len);
}

size_t uv16_new_split_uz16n(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array) {
    return uz16n_new_split_uz16n(UV16_EXPAND(view), sep, sep_len, array);
}

size_t uv16_new_split_uz16n_e(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array, bool *error) {
    return uz16n_new_split_uz16n_e(UV16_EXPAND(view), sep, sep_len, array, error);
}

size_t uv16_split_uz16n(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t *array, size_t array_len) {
    return uz16n_split_uz16n(UV16_EXPAND(view), sep, sep_len, array, array_len);
}

size_t uv16_new_split_ucv16(uv16_t view, ucv16_t sep, UNULLABLE uv16_t **array) {
    return uz16n_new_split_ucv16(UV16_EXPAND(view), sep, array);
}

size_t uv16_new_split_ucv16_e(uv16_t view, ucv16_t sep, UNULLABLE uv16_t **array, bool *error) {
    return uz16n_new_split_ucv16_e(UV16_EXPAND(view), sep, array, error);
}

size_t uv16_split_ucv16(uv16_t view, ucv16_t sep, UNULLABLE uv16_t *array, size_t array_len) {
    return uz16n_split_ucv16(UV16_EXPAND(view), sep, array, array_len);
}

size_t uv16_new_split_uv16(uv16_t view, uv16_t sep, UNULLABLE uv16_t **array) {
    return uz16n_new_split_uv16(UV16_EXPAND(view), sep, array);
}

size_t uv16_new_split_uv16_e(uv16_t view, uv16_t sep, UNULLABLE uv16_t **array, bool *error) {
    return uz16n_new_split_uv16_e(UV16_EXPAND(view), sep, array, error);
}

size_t uv16_split_uv16(uv16_t view, uv16_t sep, UNULLABLE uv16_t *array, size_t array_len) {
    return uz16n_split_uv16(UV16_EXPAND(view), sep, array, array_len);
}

size_t uv16_new_split_us16(uv16_t view, const us16_t *sep, UNULLABLE uv16_t **array) {
    return uz16n_new_split_us16(UV16_EXPAND(view), sep, array);
}

size_t uv16_new_split_us16_e(uv16_t view, const us16_t *sep, UNULLABLE uv16_t **array, bool *error) {
    return uz16n_new_split_us16_e(UV16_EXPAND(view), sep, array, error);
}

size_t uv16_split_us16(uv16_t view, const us16_t *sep, UNULLABLE uv16_t *array, size_t array_len) {
    return uz16n_split_us16(UV16_EXPAND(view), sep, array, array_len);
}

size_t uv8_new_csplit_uc8(uv8_t view, uc8_t sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uc8(UV8_CEXPAND(view), sep, array);
}

size_t uv8_new_csplit_uc8_e(uv8_t view, uc8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uc8_e(UV8_CEXPAND(view), sep, array, error);
}

size_t uv8_csplit_uc8(uv8_t view, uc8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uc8(UV8_CEXPAND(view), sep, array, array_len);
}

size_t uv8_new_csplit_uz8(uv8_t view, const uc8_t *sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uz8(UV8_CEXPAND(view), sep, array);
}

size_t uv8_new_csplit_uz8_e(uv8_t view, const uc8_t *sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uz8_e(UV8_CEXPAND(view), sep, array, error);
}

size_t uv8_csplit_uz8(uv8_t view, const uc8_t *sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uz8(UV8_CEXPAND(view), sep, array, array_len);
}

size_t uv8_new_csplit_uz8n(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uz8n(UV8_CEXPAND(view), sep, sep_len, array);
}

size_t uv8_new_csplit_uz8n_e(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uz8n_e(UV8_CEXPAND(view), sep, sep_len, array, error);
}

size_t uv8_csplit_uz8n(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uz8n(UV8_CEXPAND(view), sep, sep_len, array, array_len);
}

size_t uv8_new_csplit_ucv8(uv8_t view, ucv8_t sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_ucv8(UV8_CEXPAND(view), sep, array);
}

size_t uv8_new_csplit_ucv8_e(uv8_t view, ucv8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_ucv8_e(UV8_CEXPAND(view), sep, array, error);
}

size_t uv8_csplit_ucv8(uv8_t view, ucv8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_ucv8(UV8_CEXPAND(view), sep, array, array_len);
}

size_t uv8_new_csplit_uv8(uv8_t view, uv8_t sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uv8(UV8_CEXPAND(view), sep, array);
}

size_t uv8_new_csplit_uv8_e(uv8_t view, uv8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uv8_e(UV8_CEXPAND(view), sep, array, error);
}

size_t uv8_csplit_uv8(uv8_t view, uv8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uv8(UV8_CEXPAND(view), sep, array, array_len);
}

size_t uv8_new_csplit_us8(uv8_t view, const us8_t *sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_us8(UV8_CEXPAND(view), sep, array);
}

size_t uv8_new_csplit_us8_e(uv8_t view, const us8_t *sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_us8_e(UV8_CEXPAND(view), sep, array, error);
}

size_t uv8_csplit_us8(uv8_t view, const us8_t *sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_us8(UV8_CEXPAND(view), sep, array, array_len);
}

size_t uv8_new_split_uc8(uv8_t view, uc8_t sep, UNULLABLE uv8_t **array) {
    return uz8n_new_split_uc8(UV8_EXPAND(view), sep, array);
}

size_t uv8_new_split_uc8_e(uv8_t view, uc8_t sep, UNULLABLE uv8_t **array, bool *error) {
    return uz8n_new_split_uc8_e(UV8_EXPAND(view), sep, array, error);
}

size_t uv8_split_uc8(uv8_t view, uc8_t sep, UNULLABLE uv8_t *array, size_t array_len) {
    return uz8n_split_uc8(UV8_EXPAND(view), sep, array, array_len);
}

size_t uv8_new_split_uz8(uv8_t view, const uc8_t *sep, UNULLABLE uv8_t **array) {
    return uz8n_new_split_uz8(UV8_EXPAND(view), sep, array);
}

size_t uv8_new_split_uz8_e(uv8_t view, const uc8_t *sep, UNULLABLE uv8_t **array, bool *error) {
    return uz8n_new_split_uz8_e(UV8_EXPAND(view), sep, array, error);
}

size_t uv8_split_uz8(uv8_t view, const uc8_t *sep, UNULLABLE uv8_t *array, size_t array_len) {
    return uz8n_split_uz8(UV8_EXPAND(view), sep, array, array_len);
}

size_t uv8_new_split_uz8n(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array) {
    return uz8n_new_split_uz8n(UV8_EXPAND(view), sep, sep_len, array);
}

size_t uv8_new_split_uz8n_e(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array, bool *error) {
    return uz8n_new_split_uz8n_e(UV8_EXPAND(view), sep, sep_len, array, error);
}

size_t uv8_split_uz8n(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t *array, size_t array_len) {
    return uz8n_split_uz8n(UV8_EXPAND(view), sep, sep_len, array, array_len);
}

size_t uv8_new_split_ucv8(uv8_t view, ucv8_t sep, UNULLABLE uv8_t **array) {
    return uz8n_new_split_ucv8(UV8_EXPAND(view), sep, array);
}

size_t uv8_new_split_ucv8_e(uv8_t view, ucv8_t sep, UNULLABLE uv8_t **array, bool *error) {
    return uz8n_new_split_ucv8_e(UV8_EXPAND(view), sep, array, error);
}

size_t uv8_split_ucv8(uv8_t view, ucv8_t sep, UNULLABLE uv8_t *array, size_t array_len) {
    return uz8n_split_ucv8(UV8_EXPAND(view), sep, array, array_len);
}

size_t uv8_new_split_uv8(uv8_t view, uv8_t sep, UNULLABLE uv8_t **array) {
    return uz8n_new_split_uv8(UV8_EXPAND(view), sep, array);
}

size_t uv8_new_split_uv8_e(uv8_t view, uv8_t sep, UNULLABLE uv8_t **array, bool *error) {
    return uz8n_new_split_uv8_e(UV8_EXPAND(view), sep, array, error);
}

size_t uv8_split_uv8(uv8_t view, uv8_t sep, UNULLABLE uv8_t *array, size_t array_len) {
    return uz8n_split_uv8(UV8_EXPAND(view), sep, array, array_len);
}

size_t uv8_new_split_us8(uv8_t view, const us8_t *sep, UNULLABLE uv8_t **array) {
    return uz8n_new_split_us8(UV8_EXPAND(view), sep, array);
}

size_t uv8_new_split_us8_e(uv8_t view, const us8_t *sep, UNULLABLE uv8_t **array, bool *error) {
    return uz8n_new_split_us8_e(UV8_EXPAND(view), sep, array, error);
}

size_t uv8_split_us8(uv8_t view, const us8_t *sep, UNULLABLE uv8_t *array, size_t array_len) {
    return uz8n_split_us8(UV8_EXPAND(view), sep, array, array_len);
}

bool uv32_contains_uc32(uv32_t view, uc32_t target) {
    return uz32n_contains_uc32(UV32_CEXPAND(view), target);
}

bool uv32_contains_uz32(uv32_t view, const uc32_t *target) {
    return uz32n_contains_uz32(UV32_CEXPAND(view), target);
}

bool uv32_contains_uz32n(uv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_contains_uz32n(UV32_CEXPAND(view), target, target_len);
}

bool uv32_contains_ucv32(uv32_t view, ucv32_t target) {
    return uz32n_contains_ucv32(UV32_CEXPAND(view), target);
}

bool uv32_contains_uv32(uv32_t view, uv32_t target) {
    return uz32n_contains_uv32(UV32_CEXPAND(view), target);
}

bool uv32_contains_us32(uv32_t view, const us32_t *target) {
    return uz32n_contains_us32(UV32_CEXPAND(view), target);
}

bool uv16_contains_uc16(uv16_t view, uc16_t target) {
    return uz16n_contains_uc16(UV16_CEXPAND(view), target);
}

bool uv16_contains_uz16(uv16_t view, const uc16_t *target) {
    return uz16n_contains_uz16(UV16_CEXPAND(view), target);
}

bool uv16_contains_uz16n(uv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_contains_uz16n(UV16_CEXPAND(view), target, target_len);
}

bool uv16_contains_ucv16(uv16_t view, ucv16_t target) {
    return uz16n_contains_ucv16(UV16_CEXPAND(view), target);
}

bool uv16_contains_uv16(uv16_t view, uv16_t target) {
    return uz16n_contains_uv16(UV16_CEXPAND(view), target);
}

bool uv16_contains_us16(uv16_t view, const us16_t *target) {
    return uz16n_contains_us16(UV16_CEXPAND(view), target);
}

bool uv8_contains_uc8(uv8_t view, uc8_t target) {
    return uz8n_contains_uc8(UV8_CEXPAND(view), target);
}

bool uv8_contains_uz8(uv8_t view, const uc8_t *target) {
    return uz8n_contains_uz8(UV8_CEXPAND(view), target);
}

bool uv8_contains_uz8n(uv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_contains_uz8n(UV8_CEXPAND(view), target, target_len);
}

bool uv8_contains_ucv8(uv8_t view, ucv8_t target) {
    return uz8n_contains_ucv8(UV8_CEXPAND(view), target);
}

bool uv8_contains_uv8(uv8_t view, uv8_t target) {
    return uz8n_contains_uv8(UV8_CEXPAND(view), target);
}

bool uv8_contains_us8(uv8_t view, const us8_t *target) {
    return uz8n_contains_us8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv32_find_uc32(uv32_t view, uc32_t target) {
    return uz32n_find_uc32(UV32_CEXPAND(view), target);
}

ptrdiff_t uv32_find_uc32_from(uv32_t view, uc32_t target, size_t from) {
    return uz32n_find_uc32_from(UV32_CEXPAND(view), target, from);
}

ptrdiff_t uv32_find_uz32(uv32_t view, const uc32_t *target) {
    return uz32n_find_uz32(UV32_CEXPAND(view), target);
}

ptrdiff_t uv32_find_uz32_from(uv32_t view, const uc32_t *target, size_t from) {
    return uz32n_find_uz32_from(UV32_CEXPAND(view), target, from);
}

ptrdiff_t uv32_find_uz32n(uv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_find_uz32n(UV32_CEXPAND(view), target, target_len);
}

ptrdiff_t uv32_find_uz32n_from(uv32_t view, const uc32_t *target, size_t target_len, size_t from) {
    return uz32n_find_uz32n_from(UV32_CEXPAND(view), target, target_len, from);
}

ptrdiff_t uv32_find_ucv32(uv32_t view, ucv32_t target) {
    return uz32n_find_ucv32(UV32_CEXPAND(view), target);
}

ptrdiff_t uv32_find_ucv32_from(uv32_t view, ucv32_t target, size_t from) {
    return uz32n_find_ucv32_from(UV32_CEXPAND(view), target, from);
}

ptrdiff_t uv32_find_uv32(uv32_t view, uv32_t target) {
    return uz32n_find_uv32(UV32_CEXPAND(view), target);
}

ptrdiff_t uv32_find_uv32_from(uv32_t view, uv32_t target, size_t from) {
    return uz32n_find_uv32_from(UV32_CEXPAND(view), target, from);
}

ptrdiff_t uv32_find_us32(uv32_t view, const us32_t *target) {
    return uz32n_find_us32(UV32_CEXPAND(view), target);
}

ptrdiff_t uv32_find_us32_from(uv32_t view, const us32_t *target, size_t from) {
    return uz32n_find_us32_from(UV32_CEXPAND(view), target, from);
}

ptrdiff_t uv16_find_uc16(uv16_t view, uc16_t target) {
    return uz16n_find_uc16(UV16_CEXPAND(view), target);
}

ptrdiff_t uv16_find_uc16_from(uv16_t view, uc16_t target, size_t from) {
    return uz16n_find_uc16_from(UV16_CEXPAND(view), target, from);
}

ptrdiff_t uv16_find_uz16(uv16_t view, const uc16_t *target) {
    return uz16n_find_uz16(UV16_CEXPAND(view), target);
}

ptrdiff_t uv16_find_uz16_from(uv16_t view, const uc16_t *target, size_t from) {
    return uz16n_find_uz16_from(UV16_CEXPAND(view), target, from);
}

ptrdiff_t uv16_find_uz16n(uv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_find_uz16n(UV16_CEXPAND(view), target, target_len);
}

ptrdiff_t uv16_find_uz16n_from(uv16_t view, const uc16_t *target, size_t target_len, size_t from) {
    return uz16n_find_uz16n_from(UV16_CEXPAND(view), target, target_len, from);
}

ptrdiff_t uv16_find_ucv16(uv16_t view, ucv16_t target) {
    return uz16n_find_ucv16(UV16_CEXPAND(view), target);
}

ptrdiff_t uv16_find_ucv16_from(uv16_t view, ucv16_t target, size_t from) {
    return uz16n_find_ucv16_from(UV16_CEXPAND(view), target, from);
}

ptrdiff_t uv16_find_uv16(uv16_t view, uv16_t target) {
    return uz16n_find_uv16(UV16_CEXPAND(view), target);
}

ptrdiff_t uv16_find_uv16_from(uv16_t view, uv16_t target, size_t from) {
    return uz16n_find_uv16_from(UV16_CEXPAND(view), target, from);
}

ptrdiff_t uv16_find_us16(uv16_t view, const us16_t *target) {
    return uz16n_find_us16(UV16_CEXPAND(view), target);
}

ptrdiff_t uv16_find_us16_from(uv16_t view, const us16_t *target, size_t from) {
    return uz16n_find_us16_from(UV16_CEXPAND(view), target, from);
}

ptrdiff_t uv8_find_uc8(uv8_t view, uc8_t target) {
    return uz8n_find_uc8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv8_find_uc8_from(uv8_t view, uc8_t target, size_t from) {
    return uz8n_find_uc8_from(UV8_CEXPAND(view), target, from);
}

ptrdiff_t uv8_find_uz8(uv8_t view, const uc8_t *target) {
    return uz8n_find_uz8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv8_find_uz8_from(uv8_t view, const uc8_t *target, size_t from) {
    return uz8n_find_uz8_from(UV8_CEXPAND(view), target, from);
}

ptrdiff_t uv8_find_uz8n(uv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_find_uz8n(UV8_CEXPAND(view), target, target_len);
}

ptrdiff_t uv8_find_uz8n_from(uv8_t view, const uc8_t *target, size_t target_len, size_t from) {
    return uz8n_find_uz8n_from(UV8_CEXPAND(view), target, target_len, from);
}

ptrdiff_t uv8_find_ucv8(uv8_t view, ucv8_t target) {
    return uz8n_find_ucv8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv8_find_ucv8_from(uv8_t view, ucv8_t target, size_t from) {
    return uz8n_find_ucv8_from(UV8_CEXPAND(view), target, from);
}

ptrdiff_t uv8_find_uv8(uv8_t view, uv8_t target) {
    return uz8n_find_uv8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv8_find_uv8_from(uv8_t view, uv8_t target, size_t from) {
    return uz8n_find_uv8_from(UV8_CEXPAND(view), target, from);
}

ptrdiff_t uv8_find_us8(uv8_t view, const us8_t *target) {
    return uz8n_find_us8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv8_find_us8_from(uv8_t view, const us8_t *target, size_t from) {
    return uz8n_find_us8_from(UV8_CEXPAND(view), target, from);
}

ptrdiff_t uv32_rfind_uc32(uv32_t view, uc32_t target) {
    return uz32n_rfind_uc32(UV32_CEXPAND(view), target);
}

ptrdiff_t uv32_rfind_uc32_from(uv32_t view, uc32_t target, size_t from) {
    return uz32n_rfind_uc32_from(UV32_CEXPAND(view), target, from);
}

ptrdiff_t uv32_rfind_uz32(uv32_t view, const uc32_t *target) {
    return uz32n_rfind_uz32(UV32_CEXPAND(view), target);
}

ptrdiff_t uv32_rfind_uz32_from(uv32_t view, const uc32_t *target, size_t from) {
    return uz32n_rfind_uz32_from(UV32_CEXPAND(view), target, from);
}

ptrdiff_t uv32_rfind_uz32n(uv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_rfind_uz32n(UV32_CEXPAND(view), target, target_len);
}

ptrdiff_t uv32_rfind_uz32n_from(uv32_t view, const uc32_t *target, size_t target_len, size_t from) {
    return uz32n_rfind_uz32n_from(UV32_CEXPAND(view), target, target_len, from);
}

ptrdiff_t uv32_rfind_ucv32(uv32_t view, ucv32_t target) {
    return uz32n_rfind_ucv32(UV32_CEXPAND(view), target);
}

ptrdiff_t uv32_rfind_ucv32_from(uv32_t view, ucv32_t target, size_t from) {
    return uz32n_rfind_ucv32_from(UV32_CEXPAND(view), target, from);
}

ptrdiff_t uv32_rfind_uv32(uv32_t view, uv32_t target) {
    return uz32n_rfind_uv32(UV32_CEXPAND(view), target);
}

ptrdiff_t uv32_rfind_uv32_from(uv32_t view, uv32_t target, size_t from) {
    return uz32n_rfind_uv32_from(UV32_CEXPAND(view), target, from);
}

ptrdiff_t uv32_rfind_us32(uv32_t view, const us32_t *target) {
    return uz32n_rfind_us32(UV32_CEXPAND(view), target);
}

ptrdiff_t uv32_rfind_us32_from(uv32_t view, const us32_t *target, size_t from) {
    return uz32n_rfind_us32_from(UV32_CEXPAND(view), target, from);
}

ptrdiff_t uv16_rfind_uc16(uv16_t view, uc16_t target) {
    return uz16n_rfind_uc16(UV16_CEXPAND(view), target);
}

ptrdiff_t uv16_rfind_uc16_from(uv16_t view, uc16_t target, size_t from) {
    return uz16n_rfind_uc16_from(UV16_CEXPAND(view), target, from);
}

ptrdiff_t uv16_rfind_uz16(uv16_t view, const uc16_t *target) {
    return uz16n_rfind_uz16(UV16_CEXPAND(view), target);
}

ptrdiff_t uv16_rfind_uz16_from(uv16_t view, const uc16_t *target, size_t from) {
    return uz16n_rfind_uz16_from(UV16_CEXPAND(view), target, from);
}

ptrdiff_t uv16_rfind_uz16n(uv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_rfind_uz16n(UV16_CEXPAND(view), target, target_len);
}

ptrdiff_t uv16_rfind_uz16n_from(uv16_t view, const uc16_t *target, size_t target_len, size_t from) {
    return uz16n_rfind_uz16n_from(UV16_CEXPAND(view), target, target_len, from);
}

ptrdiff_t uv16_rfind_ucv16(uv16_t view, ucv16_t target) {
    return uz16n_rfind_ucv16(UV16_CEXPAND(view), target);
}

ptrdiff_t uv16_rfind_ucv16_from(uv16_t view, ucv16_t target, size_t from) {
    return uz16n_rfind_ucv16_from(UV16_CEXPAND(view), target, from);
}

ptrdiff_t uv16_rfind_uv16(uv16_t view, uv16_t target) {
    return uz16n_rfind_uv16(UV16_CEXPAND(view), target);
}

ptrdiff_t uv16_rfind_uv16_from(uv16_t view, uv16_t target, size_t from) {
    return uz16n_rfind_uv16_from(UV16_CEXPAND(view), target, from);
}

ptrdiff_t uv16_rfind_us16(uv16_t view, const us16_t *target) {
    return uz16n_rfind_us16(UV16_CEXPAND(view), target);
}

ptrdiff_t uv16_rfind_us16_from(uv16_t view, const us16_t *target, size_t from) {
    return uz16n_rfind_us16_from(UV16_CEXPAND(view), target, from);
}

ptrdiff_t uv8_rfind_uc8(uv8_t view, uc8_t target) {
    return uz8n_rfind_uc8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv8_rfind_uc8_from(uv8_t view, uc8_t target, size_t from) {
    return uz8n_rfind_uc8_from(UV8_CEXPAND(view), target, from);
}

ptrdiff_t uv8_rfind_uz8(uv8_t view, const uc8_t *target) {
    return uz8n_rfind_uz8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv8_rfind_uz8_from(uv8_t view, const uc8_t *target, size_t from) {
    return uz8n_rfind_uz8_from(UV8_CEXPAND(view), target, from);
}

ptrdiff_t uv8_rfind_uz8n(uv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_rfind_uz8n(UV8_CEXPAND(view), target, target_len);
}

ptrdiff_t uv8_rfind_uz8n_from(uv8_t view, const uc8_t *target, size_t target_len, size_t from) {
    return uz8n_rfind_uz8n_from(UV8_CEXPAND(view), target, target_len, from);
}

ptrdiff_t uv8_rfind_ucv8(uv8_t view, ucv8_t target) {
    return uz8n_rfind_ucv8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv8_rfind_ucv8_from(uv8_t view, ucv8_t target, size_t from) {
    return uz8n_rfind_ucv8_from(UV8_CEXPAND(view), target, from);
}

ptrdiff_t uv8_rfind_uv8(uv8_t view, uv8_t target) {
    return uz8n_rfind_uv8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv8_rfind_uv8_from(uv8_t view, uv8_t target, size_t from) {
    return uz8n_rfind_uv8_from(UV8_CEXPAND(view), target, from);
}

ptrdiff_t uv8_rfind_us8(uv8_t view, const us8_t *target) {
    return uz8n_rfind_us8(UV8_CEXPAND(view), target);
}

ptrdiff_t uv8_rfind_us8_from(uv8_t view, const us8_t *target, size_t from) {
    return uz8n_rfind_us8_from(UV8_CEXPAND(view), target, from);
}

size_t uv32_erase_uc32(UINOUT uv32_t view, uc32_t target) {
    return uz32n_erase_uc32(UV32_EXPAND(view), target);
}

size_t uv32_erase_uz32(UINOUT uv32_t view, const uc32_t *target) {
    return uz32n_erase_uz32(UV32_EXPAND(view), target);
}

size_t uv32_erase_uz32n(UINOUT uv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_erase_uz32n(UV32_EXPAND(view), target, target_len);
}

size_t uv32_erase_ucv32(UINOUT uv32_t view, ucv32_t target) {
    return uz32n_erase_ucv32(UV32_EXPAND(view), target);
}

size_t uv32_erase_uv32(UINOUT uv32_t view, uv32_t target) {
    return uz32n_erase_uv32(UV32_EXPAND(view), target);
}

size_t uv32_erase_us32(UINOUT uv32_t view, const us32_t *target) {
    return uz32n_erase_us32(UV32_EXPAND(view), target);
}

size_t uv16_erase_uc16(UINOUT uv16_t view, uc16_t target) {
    return uz16n_erase_uc16(UV16_EXPAND(view), target);
}

size_t uv16_erase_uz16(UINOUT uv16_t view, const uc16_t *target) {
    return uz16n_erase_uz16(UV16_EXPAND(view), target);
}

size_t uv16_erase_uz16n(UINOUT uv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_erase_uz16n(UV16_EXPAND(view), target, target_len);
}

size_t uv16_erase_ucv16(UINOUT uv16_t view, ucv16_t target) {
    return uz16n_erase_ucv16(UV16_EXPAND(view), target);
}

size_t uv16_erase_uv16(UINOUT uv16_t view, uv16_t target) {
    return uz16n_erase_uv16(UV16_EXPAND(view), target);
}

size_t uv16_erase_us16(UINOUT uv16_t view, const us16_t *target) {
    return uz16n_erase_us16(UV16_EXPAND(view), target);
}

size_t uv8_erase_uc8(UINOUT uv8_t view, uc8_t target) {
    return uz8n_erase_uc8(UV8_EXPAND(view), target);
}

size_t uv8_erase_uz8(UINOUT uv8_t view, const uc8_t *target) {
    return uz8n_erase_uz8(UV8_EXPAND(view), target);
}

size_t uv8_erase_uz8n(UINOUT uv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_erase_uz8n(UV8_EXPAND(view), target, target_len);
}

size_t uv8_erase_ucv8(UINOUT uv8_t view, ucv8_t target) {
    return uz8n_erase_ucv8(UV8_EXPAND(view), target);
}

size_t uv8_erase_uv8(UINOUT uv8_t view, uv8_t target) {
    return uz8n_erase_uv8(UV8_EXPAND(view), target);
}

size_t uv8_erase_us8(UINOUT uv8_t view, const us8_t *target) {
    return uz8n_erase_us8(UV8_EXPAND(view), target);
}

size_t uv32_replace_uc32_uc32(uv32_t view, uc32_t from, uc32_t to) {
    return uz32n_replace_uc32_uc32(UV32_EXPAND(view), from, to);
}

size_t uv32_replace_uz32_uc32(uv32_t view, const uc32_t *from, uc32_t to) {
    return uz32n_replace_uz32_uc32(UV32_EXPAND(view), from, to);
}

size_t uv32_replace_uz32n_uc32(uv32_t view, const uc32_t *from, size_t from_len, uc32_t to) {
    return uz32n_replace_uz32n_uc32(UV32_EXPAND(view), from, from_len, to);
}

size_t uv32_replace_ucv32_uc32(uv32_t view, ucv32_t from, uc32_t to) {
    return uz32n_replace_ucv32_uc32(UV32_EXPAND(view), from, to);
}

size_t uv32_replace_uv32_uc32(uv32_t view, uv32_t from, uc32_t to) {
    return uz32n_replace_uv32_uc32(UV32_EXPAND(view), from, to);
}

size_t uv32_replace_us32_uc32(uv32_t view, const us32_t *from, uc32_t to) {
    return uz32n_replace_us32_uc32(UV32_EXPAND(view), from, to);
}

size_t uv16_replace_uc16_uc16(uv16_t view, uc16_t from, uc16_t to) {
    return uz16n_replace_uc16_uc16(UV16_EXPAND(view), from, to);
}

size_t uv16_replace_uz16_uc16(uv16_t view, const uc16_t *from, uc16_t to) {
    return uz16n_replace_uz16_uc16(UV16_EXPAND(view), from, to);
}

size_t uv16_replace_uz16n_uc16(uv16_t view, const uc16_t *from, size_t from_len, uc16_t to) {
    return uz16n_replace_uz16n_uc16(UV16_EXPAND(view), from, from_len, to);
}

size_t uv16_replace_ucv16_uc16(uv16_t view, ucv16_t from, uc16_t to) {
    return uz16n_replace_ucv16_uc16(UV16_EXPAND(view), from, to);
}

size_t uv16_replace_uv16_uc16(uv16_t view, uv16_t from, uc16_t to) {
    return uz16n_replace_uv16_uc16(UV16_EXPAND(view), from, to);
}

size_t uv16_replace_us16_uc16(uv16_t view, const us16_t *from, uc16_t to) {
    return uz16n_replace_us16_uc16(UV16_EXPAND(view), from, to);
}

size_t uv8_replace_uc8_uc8(uv8_t view, uc8_t from, uc8_t to) {
    return uz8n_replace_uc8_uc8(UV8_EXPAND(view), from, to);
}

size_t uv8_replace_uz8_uc8(uv8_t view, const uc8_t *from, uc8_t to) {
    return uz8n_replace_uz8_uc8(UV8_EXPAND(view), from, to);
}

size_t uv8_replace_uz8n_uc8(uv8_t view, const uc8_t *from, size_t from_len, uc8_t to) {
    return uz8n_replace_uz8n_uc8(UV8_EXPAND(view), from, from_len, to);
}

size_t uv8_replace_ucv8_uc8(uv8_t view, ucv8_t from, uc8_t to) {
    return uz8n_replace_ucv8_uc8(UV8_EXPAND(view), from, to);
}

size_t uv8_replace_uv8_uc8(uv8_t view, uv8_t from, uc8_t to) {
    return uz8n_replace_uv8_uc8(UV8_EXPAND(view), from, to);
}

size_t uv8_replace_us8_uc8(uv8_t view, const us8_t *from, uc8_t to) {
    return uz8n_replace_us8_uc8(UV8_EXPAND(view), from, to);
}

size_t uv32_replaced_len_uc32_uz32(uv32_t view, uc32_t from, const uc32_t *to) {
    return uz32n_replaced_len_uc32_uz32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uc32_uz32n(uv32_t view, uc32_t from, size_t to_len) {
    return uz32n_replaced_len_uc32_uz32n(UV32_CEXPAND(view), from, to_len);
}

size_t uv32_replaced_len_uc32_ucv32(uv32_t view, uc32_t from, ucv32_t to) {
    return uz32n_replaced_len_uc32_ucv32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uc32_uv32(uv32_t view, uc32_t from, uv32_t to) {
    return uz32n_replaced_len_uc32_uv32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uc32_us32(uv32_t view, uc32_t from, const us32_t *to) {
    return uz32n_replaced_len_uc32_us32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uz32_uc32(uv32_t view, const uc32_t *from, uc32_t to) {
    return uz32n_replaced_len_uz32_uc32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uz32_uz32(uv32_t view, const uc32_t *from, const uc32_t *to) {
    return uz32n_replaced_len_uz32_uz32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uz32_uz32n(uv32_t view, const uc32_t *from, size_t to_len) {
    return uz32n_replaced_len_uz32_uz32n(UV32_CEXPAND(view), from, to_len);
}

size_t uv32_replaced_len_uz32_ucv32(uv32_t view, const uc32_t *from, ucv32_t to) {
    return uz32n_replaced_len_uz32_ucv32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uz32_uv32(uv32_t view, const uc32_t *from, uv32_t to) {
    return uz32n_replaced_len_uz32_uv32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uz32_us32(uv32_t view, const uc32_t *from, const us32_t *to) {
    return uz32n_replaced_len_uz32_us32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uz32n_uc32(uv32_t view, const uc32_t *from, size_t from_len, uc32_t to) {
    return uz32n_replaced_len_uz32n_uc32(UV32_CEXPAND(view), from, from_len, to);
}

size_t uv32_replaced_len_uz32n_uz32(uv32_t view, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32n_replaced_len_uz32n_uz32(UV32_CEXPAND(view), from, from_len, to);
}

size_t uv32_replaced_len_uz32n_uz32n(uv32_t view, const uc32_t *from, size_t from_len, size_t to_len) {
    return uz32n_replaced_len_uz32n_uz32n(UV32_CEXPAND(view), from, from_len, to_len);
}

size_t uv32_replaced_len_uz32n_ucv32(uv32_t view, const uc32_t *from, size_t from_len, ucv32_t to) {
    return uz32n_replaced_len_uz32n_ucv32(UV32_CEXPAND(view), from, from_len, to);
}

size_t uv32_replaced_len_uz32n_uv32(uv32_t view, const uc32_t *from, size_t from_len, uv32_t to) {
    return uz32n_replaced_len_uz32n_uv32(UV32_CEXPAND(view), from, from_len, to);
}

size_t uv32_replaced_len_uz32n_us32(uv32_t view, const uc32_t *from, size_t from_len, const us32_t *to) {
    return uz32n_replaced_len_uz32n_us32(UV32_CEXPAND(view), from, from_len, to);
}

size_t uv32_replaced_len_ucv32_uc32(uv32_t view, ucv32_t from, uc32_t to) {
    return uz32n_replaced_len_ucv32_uc32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_ucv32_uz32(uv32_t view, ucv32_t from, const uc32_t *to) {
    return uz32n_replaced_len_ucv32_uz32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_ucv32_uz32n(uv32_t view, ucv32_t from, size_t to_len) {
    return uz32n_replaced_len_ucv32_uz32n(UV32_CEXPAND(view), from, to_len);
}

size_t uv32_replaced_len_ucv32_ucv32(uv32_t view, ucv32_t from, ucv32_t to) {
    return uz32n_replaced_len_ucv32_ucv32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_ucv32_uv32(uv32_t view, ucv32_t from, uv32_t to) {
    return uz32n_replaced_len_ucv32_uv32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_ucv32_us32(uv32_t view, ucv32_t from, const us32_t *to) {
    return uz32n_replaced_len_ucv32_us32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uv32_uc32(uv32_t view, uv32_t from, uc32_t to) {
    return uz32n_replaced_len_uv32_uc32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uv32_uz32(uv32_t view, uv32_t from, const uc32_t *to) {
    return uz32n_replaced_len_uv32_uz32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uv32_uz32n(uv32_t view, uv32_t from, size_t to_len) {
    return uz32n_replaced_len_uv32_uz32n(UV32_CEXPAND(view), from, to_len);
}

size_t uv32_replaced_len_uv32_ucv32(uv32_t view, uv32_t from, ucv32_t to) {
    return uz32n_replaced_len_uv32_ucv32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uv32_uv32(uv32_t view, uv32_t from, uv32_t to) {
    return uz32n_replaced_len_uv32_uv32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_uv32_us32(uv32_t view, uv32_t from, const us32_t *to) {
    return uz32n_replaced_len_uv32_us32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_us32_uc32(uv32_t view, const us32_t *from, uc32_t to) {
    return uz32n_replaced_len_us32_uc32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_us32_uz32(uv32_t view, const us32_t *from, const uc32_t *to) {
    return uz32n_replaced_len_us32_uz32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_us32_uz32n(uv32_t view, const us32_t *from, size_t to_len) {
    return uz32n_replaced_len_us32_uz32n(UV32_CEXPAND(view), from, to_len);
}

size_t uv32_replaced_len_us32_ucv32(uv32_t view, const us32_t *from, ucv32_t to) {
    return uz32n_replaced_len_us32_ucv32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_us32_uv32(uv32_t view, const us32_t *from, uv32_t to) {
    return uz32n_replaced_len_us32_uv32(UV32_CEXPAND(view), from, to);
}

size_t uv32_replaced_len_us32_us32(uv32_t view, const us32_t *from, const us32_t *to) {
    return uz32n_replaced_len_us32_us32(UV32_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uc16_uz16(uv16_t view, uc16_t from, const uc16_t *to) {
    return uz16n_replaced_len_uc16_uz16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uc16_uz16n(uv16_t view, uc16_t from, size_t to_len) {
    return uz16n_replaced_len_uc16_uz16n(UV16_CEXPAND(view), from, to_len);
}

size_t uv16_replaced_len_uc16_ucv16(uv16_t view, uc16_t from, ucv16_t to) {
    return uz16n_replaced_len_uc16_ucv16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uc16_uv16(uv16_t view, uc16_t from, uv16_t to) {
    return uz16n_replaced_len_uc16_uv16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uc16_us16(uv16_t view, uc16_t from, const us16_t *to) {
    return uz16n_replaced_len_uc16_us16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uz16_uc16(uv16_t view, const uc16_t *from, uc16_t to) {
    return uz16n_replaced_len_uz16_uc16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uz16_uz16(uv16_t view, const uc16_t *from, const uc16_t *to) {
    return uz16n_replaced_len_uz16_uz16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uz16_uz16n(uv16_t view, const uc16_t *from, size_t to_len) {
    return uz16n_replaced_len_uz16_uz16n(UV16_CEXPAND(view), from, to_len);
}

size_t uv16_replaced_len_uz16_ucv16(uv16_t view, const uc16_t *from, ucv16_t to) {
    return uz16n_replaced_len_uz16_ucv16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uz16_uv16(uv16_t view, const uc16_t *from, uv16_t to) {
    return uz16n_replaced_len_uz16_uv16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uz16_us16(uv16_t view, const uc16_t *from, const us16_t *to) {
    return uz16n_replaced_len_uz16_us16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uz16n_uc16(uv16_t view, const uc16_t *from, size_t from_len, uc16_t to) {
    return uz16n_replaced_len_uz16n_uc16(UV16_CEXPAND(view), from, from_len, to);
}

size_t uv16_replaced_len_uz16n_uz16(uv16_t view, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16n_replaced_len_uz16n_uz16(UV16_CEXPAND(view), from, from_len, to);
}

size_t uv16_replaced_len_uz16n_uz16n(uv16_t view, const uc16_t *from, size_t from_len, size_t to_len) {
    return uz16n_replaced_len_uz16n_uz16n(UV16_CEXPAND(view), from, from_len, to_len);
}

size_t uv16_replaced_len_uz16n_ucv16(uv16_t view, const uc16_t *from, size_t from_len, ucv16_t to) {
    return uz16n_replaced_len_uz16n_ucv16(UV16_CEXPAND(view), from, from_len, to);
}

size_t uv16_replaced_len_uz16n_uv16(uv16_t view, const uc16_t *from, size_t from_len, uv16_t to) {
    return uz16n_replaced_len_uz16n_uv16(UV16_CEXPAND(view), from, from_len, to);
}

size_t uv16_replaced_len_uz16n_us16(uv16_t view, const uc16_t *from, size_t from_len, const us16_t *to) {
    return uz16n_replaced_len_uz16n_us16(UV16_CEXPAND(view), from, from_len, to);
}

size_t uv16_replaced_len_ucv16_uc16(uv16_t view, ucv16_t from, uc16_t to) {
    return uz16n_replaced_len_ucv16_uc16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_ucv16_uz16(uv16_t view, ucv16_t from, const uc16_t *to) {
    return uz16n_replaced_len_ucv16_uz16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_ucv16_uz16n(uv16_t view, ucv16_t from, size_t to_len) {
    return uz16n_replaced_len_ucv16_uz16n(UV16_CEXPAND(view), from, to_len);
}

size_t uv16_replaced_len_ucv16_ucv16(uv16_t view, ucv16_t from, ucv16_t to) {
    return uz16n_replaced_len_ucv16_ucv16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_ucv16_uv16(uv16_t view, ucv16_t from, uv16_t to) {
    return uz16n_replaced_len_ucv16_uv16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_ucv16_us16(uv16_t view, ucv16_t from, const us16_t *to) {
    return uz16n_replaced_len_ucv16_us16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uv16_uc16(uv16_t view, uv16_t from, uc16_t to) {
    return uz16n_replaced_len_uv16_uc16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uv16_uz16(uv16_t view, uv16_t from, const uc16_t *to) {
    return uz16n_replaced_len_uv16_uz16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uv16_uz16n(uv16_t view, uv16_t from, size_t to_len) {
    return uz16n_replaced_len_uv16_uz16n(UV16_CEXPAND(view), from, to_len);
}

size_t uv16_replaced_len_uv16_ucv16(uv16_t view, uv16_t from, ucv16_t to) {
    return uz16n_replaced_len_uv16_ucv16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uv16_uv16(uv16_t view, uv16_t from, uv16_t to) {
    return uz16n_replaced_len_uv16_uv16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_uv16_us16(uv16_t view, uv16_t from, const us16_t *to) {
    return uz16n_replaced_len_uv16_us16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_us16_uc16(uv16_t view, const us16_t *from, uc16_t to) {
    return uz16n_replaced_len_us16_uc16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_us16_uz16(uv16_t view, const us16_t *from, const uc16_t *to) {
    return uz16n_replaced_len_us16_uz16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_us16_uz16n(uv16_t view, const us16_t *from, size_t to_len) {
    return uz16n_replaced_len_us16_uz16n(UV16_CEXPAND(view), from, to_len);
}

size_t uv16_replaced_len_us16_ucv16(uv16_t view, const us16_t *from, ucv16_t to) {
    return uz16n_replaced_len_us16_ucv16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_us16_uv16(uv16_t view, const us16_t *from, uv16_t to) {
    return uz16n_replaced_len_us16_uv16(UV16_CEXPAND(view), from, to);
}

size_t uv16_replaced_len_us16_us16(uv16_t view, const us16_t *from, const us16_t *to) {
    return uz16n_replaced_len_us16_us16(UV16_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uc8_uz8(uv8_t view, uc8_t from, const uc8_t *to) {
    return uz8n_replaced_len_uc8_uz8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uc8_uz8n(uv8_t view, uc8_t from, size_t to_len) {
    return uz8n_replaced_len_uc8_uz8n(UV8_CEXPAND(view), from, to_len);
}

size_t uv8_replaced_len_uc8_ucv8(uv8_t view, uc8_t from, ucv8_t to) {
    return uz8n_replaced_len_uc8_ucv8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uc8_uv8(uv8_t view, uc8_t from, uv8_t to) {
    return uz8n_replaced_len_uc8_uv8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uc8_us8(uv8_t view, uc8_t from, const us8_t *to) {
    return uz8n_replaced_len_uc8_us8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uz8_uc8(uv8_t view, const uc8_t *from, uc8_t to) {
    return uz8n_replaced_len_uz8_uc8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uz8_uz8(uv8_t view, const uc8_t *from, const uc8_t *to) {
    return uz8n_replaced_len_uz8_uz8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uz8_uz8n(uv8_t view, const uc8_t *from, size_t to_len) {
    return uz8n_replaced_len_uz8_uz8n(UV8_CEXPAND(view), from, to_len);
}

size_t uv8_replaced_len_uz8_ucv8(uv8_t view, const uc8_t *from, ucv8_t to) {
    return uz8n_replaced_len_uz8_ucv8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uz8_uv8(uv8_t view, const uc8_t *from, uv8_t to) {
    return uz8n_replaced_len_uz8_uv8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uz8_us8(uv8_t view, const uc8_t *from, const us8_t *to) {
    return uz8n_replaced_len_uz8_us8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uz8n_uc8(uv8_t view, const uc8_t *from, size_t from_len, uc8_t to) {
    return uz8n_replaced_len_uz8n_uc8(UV8_CEXPAND(view), from, from_len, to);
}

size_t uv8_replaced_len_uz8n_uz8(uv8_t view, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8n_replaced_len_uz8n_uz8(UV8_CEXPAND(view), from, from_len, to);
}

size_t uv8_replaced_len_uz8n_uz8n(uv8_t view, const uc8_t *from, size_t from_len, size_t to_len) {
    return uz8n_replaced_len_uz8n_uz8n(UV8_CEXPAND(view), from, from_len, to_len);
}

size_t uv8_replaced_len_uz8n_ucv8(uv8_t view, const uc8_t *from, size_t from_len, ucv8_t to) {
    return uz8n_replaced_len_uz8n_ucv8(UV8_CEXPAND(view), from, from_len, to);
}

size_t uv8_replaced_len_uz8n_uv8(uv8_t view, const uc8_t *from, size_t from_len, uv8_t to) {
    return uz8n_replaced_len_uz8n_uv8(UV8_CEXPAND(view), from, from_len, to);
}

size_t uv8_replaced_len_uz8n_us8(uv8_t view, const uc8_t *from, size_t from_len, const us8_t *to) {
    return uz8n_replaced_len_uz8n_us8(UV8_CEXPAND(view), from, from_len, to);
}

size_t uv8_replaced_len_ucv8_uc8(uv8_t view, ucv8_t from, uc8_t to) {
    return uz8n_replaced_len_ucv8_uc8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_ucv8_uz8(uv8_t view, ucv8_t from, const uc8_t *to) {
    return uz8n_replaced_len_ucv8_uz8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_ucv8_uz8n(uv8_t view, ucv8_t from, size_t to_len) {
    return uz8n_replaced_len_ucv8_uz8n(UV8_CEXPAND(view), from, to_len);
}

size_t uv8_replaced_len_ucv8_ucv8(uv8_t view, ucv8_t from, ucv8_t to) {
    return uz8n_replaced_len_ucv8_ucv8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_ucv8_uv8(uv8_t view, ucv8_t from, uv8_t to) {
    return uz8n_replaced_len_ucv8_uv8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_ucv8_us8(uv8_t view, ucv8_t from, const us8_t *to) {
    return uz8n_replaced_len_ucv8_us8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uv8_uc8(uv8_t view, uv8_t from, uc8_t to) {
    return uz8n_replaced_len_uv8_uc8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uv8_uz8(uv8_t view, uv8_t from, const uc8_t *to) {
    return uz8n_replaced_len_uv8_uz8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uv8_uz8n(uv8_t view, uv8_t from, size_t to_len) {
    return uz8n_replaced_len_uv8_uz8n(UV8_CEXPAND(view), from, to_len);
}

size_t uv8_replaced_len_uv8_ucv8(uv8_t view, uv8_t from, ucv8_t to) {
    return uz8n_replaced_len_uv8_ucv8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uv8_uv8(uv8_t view, uv8_t from, uv8_t to) {
    return uz8n_replaced_len_uv8_uv8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_uv8_us8(uv8_t view, uv8_t from, const us8_t *to) {
    return uz8n_replaced_len_uv8_us8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_us8_uc8(uv8_t view, const us8_t *from, uc8_t to) {
    return uz8n_replaced_len_us8_uc8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_us8_uz8(uv8_t view, const us8_t *from, const uc8_t *to) {
    return uz8n_replaced_len_us8_uz8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_us8_uz8n(uv8_t view, const us8_t *from, size_t to_len) {
    return uz8n_replaced_len_us8_uz8n(UV8_CEXPAND(view), from, to_len);
}

size_t uv8_replaced_len_us8_ucv8(uv8_t view, const us8_t *from, ucv8_t to) {
    return uz8n_replaced_len_us8_ucv8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_us8_uv8(uv8_t view, const us8_t *from, uv8_t to) {
    return uz8n_replaced_len_us8_uv8(UV8_CEXPAND(view), from, to);
}

size_t uv8_replaced_len_us8_us8(uv8_t view, const us8_t *from, const us8_t *to) {
    return uz8n_replaced_len_us8_us8(UV8_CEXPAND(view), from, to);
}

size_t uv32_count_uc32(uv32_t view, uc32_t target) {
    return uz32n_count_uc32(UV32_CEXPAND(view), target);
}

size_t uv32_count_uz32(uv32_t view, const uc32_t *target) {
    return uz32n_count_uz32(UV32_CEXPAND(view), target);
}

size_t uv32_count_uz32n(uv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_count_uz32n(UV32_CEXPAND(view), target, target_len);
}

size_t uv32_count_ucv32(uv32_t view, ucv32_t target) {
    return uz32n_count_ucv32(UV32_CEXPAND(view), target);
}

size_t uv32_count_uv32(uv32_t view, uv32_t target) {
    return uz32n_count_uv32(UV32_CEXPAND(view), target);
}

size_t uv32_count_us32(uv32_t view, const us32_t *target) {
    return uz32n_count_us32(UV32_CEXPAND(view), target);
}

size_t uv16_count_uc16(uv16_t view, uc16_t target) {
    return uz16n_count_uc16(UV16_CEXPAND(view), target);
}

size_t uv16_count_uz16(uv16_t view, const uc16_t *target) {
    return uz16n_count_uz16(UV16_CEXPAND(view), target);
}

size_t uv16_count_uz16n(uv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_count_uz16n(UV16_CEXPAND(view), target, target_len);
}

size_t uv16_count_ucv16(uv16_t view, ucv16_t target) {
    return uz16n_count_ucv16(UV16_CEXPAND(view), target);
}

size_t uv16_count_uv16(uv16_t view, uv16_t target) {
    return uz16n_count_uv16(UV16_CEXPAND(view), target);
}

size_t uv16_count_us16(uv16_t view, const us16_t *target) {
    return uz16n_count_us16(UV16_CEXPAND(view), target);
}

size_t uv8_count_uc8(uv8_t view, uc8_t target) {
    return uz8n_count_uc8(UV8_CEXPAND(view), target);
}

size_t uv8_count_uz8(uv8_t view, const uc8_t *target) {
    return uz8n_count_uz8(UV8_CEXPAND(view), target);
}

size_t uv8_count_uz8n(uv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_count_uz8n(UV8_CEXPAND(view), target, target_len);
}

size_t uv8_count_ucv8(uv8_t view, ucv8_t target) {
    return uz8n_count_ucv8(UV8_CEXPAND(view), target);
}

size_t uv8_count_uv8(uv8_t view, uv8_t target) {
    return uz8n_count_uv8(UV8_CEXPAND(view), target);
}

size_t uv8_count_us8(uv8_t view, const us8_t *target) {
    return uz8n_count_us8(UV8_CEXPAND(view), target);
}

#define UVX_BOUNDS(view, index, X) \
    assert(uv##X##_valid(view));   \
    return index < view.len

#define UVX_EBOUNDS(view, index, X) \
    assert(uv##X##_valid(view));    \
    return index <= view.len
    
#define UVX_BOUNDS_RANGE(view, begin, len, X) \
    assert(uv##X##_valid(view));              \
    return ubounds_range(view.len, begin, len)

#define UVX_EBOUNDS_RANGE(view, begin, len, X) \
    assert(uv##X##_valid(view));               \
    return uebounds_range(view.len, begin, len)

bool uv32_bounds(uv32_t view, size_t index) {
    UVX_BOUNDS(view, index, 32);
}

bool uv32_ebounds(uv32_t view, size_t index) {
    UVX_EBOUNDS(view, index, 32);
}

bool uv32_bounds_range(uv32_t view, size_t begin, size_t len) {
    UVX_BOUNDS_RANGE(view, begin, len, 32);
}

bool uv32_ebounds_range(uv32_t view, size_t begin, size_t len) {
    UVX_EBOUNDS_RANGE(view, begin, len, 32);
}

bool uv16_bounds(uv16_t view, size_t index) {
    UVX_BOUNDS(view, index, 16);
}

bool uv16_ebounds(uv16_t view, size_t index) {
    UVX_EBOUNDS(view, index, 16);
}

bool uv16_bounds_range(uv16_t view, size_t begin, size_t len) {
    UVX_BOUNDS_RANGE(view, begin, len, 16);
}

bool uv16_ebounds_range(uv16_t view, size_t begin, size_t len) {
    UVX_EBOUNDS_RANGE(view, begin, len, 16);
}

bool uv8_bounds(uv8_t view, size_t index) {
    UVX_BOUNDS(view, index, 8);
}

bool uv8_ebounds(uv8_t view, size_t index) {
    UVX_EBOUNDS(view, index, 8);
}

bool uv8_bounds_range(uv8_t view, size_t begin, size_t len) {
    UVX_BOUNDS_RANGE(view, begin, len, 8);
}

bool uv8_ebounds_range(uv8_t view, size_t begin, size_t len) {
    UVX_EBOUNDS_RANGE(view, begin, len, 8);
}

bool uv32_starts_with_uc32(uv32_t view, uc32_t target) {
    return uz32n_starts_with_uc32(UV32_CEXPAND(view), target);
}

bool uv32_starts_with_uz32(uv32_t view, const uc32_t *target) {
    return uz32n_starts_with_uz32(UV32_CEXPAND(view), target);
}

bool uv32_starts_with_uz32n(uv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_starts_with_uz32n(UV32_CEXPAND(view), target, target_len);
}

bool uv32_starts_with_ucv32(uv32_t view, ucv32_t target) {
    return uz32n_starts_with_ucv32(UV32_CEXPAND(view), target);
}

bool uv32_starts_with_uv32(uv32_t view, uv32_t target) {
    return uz32n_starts_with_uv32(UV32_CEXPAND(view), target);
}

bool uv32_starts_with_us32(uv32_t view, const us32_t *target) {
    return uz32n_starts_with_us32(UV32_CEXPAND(view), target);
}

bool uv16_starts_with_uc16(uv16_t view, uc16_t target) {
    return uz16n_starts_with_uc16(UV16_CEXPAND(view), target);
}

bool uv16_starts_with_uz16(uv16_t view, const uc16_t *target) {
    return uz16n_starts_with_uz16(UV16_CEXPAND(view), target);
}

bool uv16_starts_with_uz16n(uv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_starts_with_uz16n(UV16_CEXPAND(view), target, target_len);
}

bool uv16_starts_with_ucv16(uv16_t view, ucv16_t target) {
    return uz16n_starts_with_ucv16(UV16_CEXPAND(view), target);
}

bool uv16_starts_with_uv16(uv16_t view, uv16_t target) {
    return uz16n_starts_with_uv16(UV16_CEXPAND(view), target);
}

bool uv16_starts_with_us16(uv16_t view, const us16_t *target) {
    return uz16n_starts_with_us16(UV16_CEXPAND(view), target);
}

bool uv8_starts_with_uc8(uv8_t view, uc8_t target) {
    return uz8n_starts_with_uc8(UV8_CEXPAND(view), target);
}

bool uv8_starts_with_uz8(uv8_t view, const uc8_t *target) {
    return uz8n_starts_with_uz8(UV8_CEXPAND(view), target);
}

bool uv8_starts_with_uz8n(uv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_starts_with_uz8n(UV8_CEXPAND(view), target, target_len);
}

bool uv8_starts_with_ucv8(uv8_t view, ucv8_t target) {
    return uz8n_starts_with_ucv8(UV8_CEXPAND(view), target);
}

bool uv8_starts_with_uv8(uv8_t view, uv8_t target) {
    return uz8n_starts_with_uv8(UV8_CEXPAND(view), target);
}

bool uv8_starts_with_us8(uv8_t view, const us8_t *target) {
    return uz8n_starts_with_us8(UV8_CEXPAND(view), target);
}

bool uv32_ends_with_uc32(uv32_t view, uc32_t target) {
    return uz32n_ends_with_uc32(UV32_CEXPAND(view), target);
}

bool uv32_ends_with_uz32(uv32_t view, const uc32_t *target) {
    return uz32n_ends_with_uz32(UV32_CEXPAND(view), target);
}

bool uv32_ends_with_uz32n(uv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_ends_with_uz32n(UV32_CEXPAND(view), target, target_len);
}

bool uv32_ends_with_ucv32(uv32_t view, ucv32_t target) {
    return uz32n_ends_with_ucv32(UV32_CEXPAND(view), target);
}

bool uv32_ends_with_uv32(uv32_t view, uv32_t target) {
    return uz32n_ends_with_uv32(UV32_CEXPAND(view), target);
}

bool uv32_ends_with_us32(uv32_t view, const us32_t *target) {
    return uz32n_ends_with_us32(UV32_CEXPAND(view), target);
}

bool uv16_ends_with_uc16(uv16_t view, uc16_t target) {
    return uz16n_ends_with_uc16(UV16_CEXPAND(view), target);
}

bool uv16_ends_with_uz16(uv16_t view, const uc16_t *target) {
    return uz16n_ends_with_uz16(UV16_CEXPAND(view), target);
}

bool uv16_ends_with_uz16n(uv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_ends_with_uz16n(UV16_CEXPAND(view), target, target_len);
}

bool uv16_ends_with_ucv16(uv16_t view, ucv16_t target) {
    return uz16n_ends_with_ucv16(UV16_CEXPAND(view), target);
}

bool uv16_ends_with_uv16(uv16_t view, uv16_t target) {
    return uz16n_ends_with_uv16(UV16_CEXPAND(view), target);
}

bool uv16_ends_with_us16(uv16_t view, const us16_t *target) {
    return uz16n_ends_with_us16(UV16_CEXPAND(view), target);
}

bool uv8_ends_with_uc8(uv8_t view, uc8_t target) {
    return uz8n_ends_with_uc8(UV8_CEXPAND(view), target);
}

bool uv8_ends_with_uz8(uv8_t view, const uc8_t *target) {
    return uz8n_ends_with_uz8(UV8_CEXPAND(view), target);
}

bool uv8_ends_with_uz8n(uv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_ends_with_uz8n(UV8_CEXPAND(view), target, target_len);
}

bool uv8_ends_with_ucv8(uv8_t view, ucv8_t target) {
    return uz8n_ends_with_ucv8(UV8_CEXPAND(view), target);
}

bool uv8_ends_with_uv8(uv8_t view, uv8_t target) {
    return uz8n_ends_with_uv8(UV8_CEXPAND(view), target);
}

bool uv8_ends_with_us8(uv8_t view, const us8_t *target) {
    return uz8n_ends_with_us8(UV8_CEXPAND(view), target);
}

#define UVX_BEGIN(view, X)       \
    assert(uv##X##_valid(view)); \
    return view.chars

const uc32_t *uv32_cbegin(uv32_t view) {
    UVX_BEGIN(view, 32);
}

const uc16_t *uv16_cbegin(uv16_t view) {
    UVX_BEGIN(view, 16);
}

const uc8_t *uv8_cbegin(uv8_t view) {
    UVX_BEGIN(view, 8);
}

uc32_t *uv32_begin(uv32_t view) {
    UVX_BEGIN(view, 32);
}

uc16_t *uv16_begin(uv16_t view) {
    UVX_BEGIN(view, 16);
}

uc8_t *uv8_begin(uv8_t view) {
    UVX_BEGIN(view, 8);
}

#define UVX_OFFSET(view, offset, X)        \
    assert(uv##X##_ebounds(view, offset)); \
    return view.chars + offset

const uc32_t *uv32_coffset(uv32_t view, size_t offset) {
    UVX_OFFSET(view, offset, 32);
}

const uc16_t *uv16_coffset(uv16_t view, size_t offset) {
    UVX_OFFSET(view, offset, 16);
}

const uc8_t *uv8_coffset(uv8_t view, size_t offset) {
    UVX_OFFSET(view, offset, 8);
}

uc32_t *uv32_offset(uv32_t view, size_t offset) {
    UVX_OFFSET(view, offset, 32);
}

uc16_t *uv16_offset(uv16_t view, size_t offset) {
    UVX_OFFSET(view, offset, 16);
}

uc8_t *uv8_offset(uv8_t view, size_t offset) {
    UVX_OFFSET(view, offset, 8);
}

#define UVX_END(view, X)         \
    assert(uv##X##_valid(view)); \
    return view.chars + view.len

const uc32_t *uv32_cend(uv32_t view) {
    UVX_END(view, 32);
}

const uc16_t *uv16_cend(uv16_t view) {
    UVX_END(view, 16);
}

const uc8_t *uv8_cend(uv8_t view) {
    UVX_END(view, 8);
}

uc32_t *uv32_end(uv32_t view) {
    UVX_END(view, 32);
}

uc16_t *uv16_end(uv16_t view) {
    UVX_END(view, 16);
}

uc8_t *uv8_end(uv8_t view) {
    UVX_END(view, 8);
}

#define UVX_EMPTY(view, X)       \
    assert(uv##X##_valid(view)); \
    return !view.len

bool uv32_empty(uv32_t view) {
    UVX_EMPTY(view, 32);
}

bool uv16_empty(uv16_t view) {
    UVX_EMPTY(view, 16);
}

bool uv8_empty(uv8_t view) {
    UVX_EMPTY(view, 8);
}

#define UVX_AT(view, at, X)           \
    assert(uv##X##_bounds(view, at)); \
    return view.chars[at]

uc32_t uv32_at(uv32_t view, size_t at) {
    UVX_AT(view, at, 32);
}

uc16_t uv16_at(uv16_t view, size_t at) {
    UVX_AT(view, at, 16);
}

uc8_t uv8_at(uv8_t view, size_t at) {
    UVX_AT(view, at, 8);
}

#define UVX_CCHARS(view, X)                        \
    assert(uv##X##_valid(view));                   \
    static const uc##X##_t *chars = uz##X("NULL"); \
    return view.chars ? view.chars : chars

const uc32_t *uv32_cchars(uv32_t view) {
    UVX_CCHARS(view, 32);
}

uc32_t *uv32_chars(uv32_t view) {
    assert(uv32_valid(view));
    static uc32_t chars[] = U"NULL";
    return view.chars ? view.chars : chars;
}

const uc16_t *uv16_cchars(uv16_t view) {
    UVX_CCHARS(view, 16);
}

uc16_t *uv16_chars(uv16_t view) {
    assert(uv16_valid(view));
    static uc16_t chars[] = u"NULL";
    return view.chars ? view.chars : chars;
}

const uc8_t *uv8_cchars(uv8_t view) {
    UVX_CCHARS(view, 8);
}

uc8_t *uv8_chars(uv8_t view) {
    assert(uv8_valid(view));
    static char chars[] = u8"NULL";
    return view.chars ? view.chars : (uc8_t *) chars;
}

#define UVX_SET_CHARS(view, chars, X) \
    assert(uv##X##_valid_p(view));    \
                                      \
    view->chars = chars;              \
                                      \
    if (!chars)                       \
        view->len = 0;

void uv32_set_chars(UINOUT uv32_t *view, uc32_t *chars) {
    UVX_SET_CHARS(view, chars, 32);
}

void uv16_set_chars(UINOUT uv16_t *view, uc16_t *chars) {
    UVX_SET_CHARS(view, chars, 16);
}

void uv8_set_chars(UINOUT uv8_t *view, uc8_t *chars) {
    UVX_SET_CHARS(view, chars, 8);
}

#define UVX_VALID(view) \
    return view.chars   \
        || !view.len

bool uv32_valid_p(const uv32_t *view) {
    return view && uv32_valid(*view);
}

bool uv32_valid(uv32_t view) {
    UVX_VALID(view);
}

bool uv16_valid_p(const uv16_t *view) {
    return view && uv16_valid(*view);
}

bool uv16_valid(uv16_t view) {
    UVX_VALID(view);
}

bool uv8_valid_p(const uv8_t *view) {
    return view && uv8_valid(*view);
}

bool uv8_valid(uv8_t view) {
    UVX_VALID(view);
}