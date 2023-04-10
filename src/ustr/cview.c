#include "cview.h"

#include <assert.h>

#include "fmt/case.h"
#include "cstr.h"
#include "str.h"
#include "view.h"

#define UCVX_FROM_UZX(from, X)                \
    return (ucv##X##_t) {                     \
        .chars = from,                        \
        .len   = from ? uz##X##_len(from) : 0 \
    }

#define UCVX_FROM_UZX_RANGE(from, begin, len, X)     \
    assert(uz##X##_ebounds_range(from, begin, len)); \
                                                     \
    return (ucv##X##_t) {                            \
        .chars = from + begin,                       \
        .len   = len                                 \
    }

#define UCVX_FROM_UZXN(from, from_len, X) \
    assert(from);                         \
                                          \
    return (ucv##X##_t) {                 \
        .chars = from,                    \
        .len   = from_len                 \
    }

#define UCVX_FROM_UZXN_RANGE(from, from_len, begin, len, X) \
    assert(uebounds_range(from_len, begin, len));           \
                                                            \
    return (ucv##X##_t) {                                   \
        .chars = from + begin,                              \
        .len   = len                                        \
    }

#define UCVX_FROM_UCVX(from, X)   \
    assert(ucv##X##_valid(from)); \
                                  \
    return (ucv##X##_t) {         \
        .chars = from.chars,      \
        .len   = from.len         \
    }

#define UCVX_FROM_UCVX_RANGE(from, begin, len, X)     \
    assert(ucv##X##_ebounds_range(from, begin, len)); \
                                                      \
    return (ucv##X##_t) {                             \
        .chars = from.chars + begin,                  \
        .len   = len                                  \
    }

#define UCVX_FROM_UVX(from, X)   \
    assert(uv##X##_valid(from)); \
                                 \
    return (ucv##X##_t) {        \
        .chars = from.chars,     \
        .len   = from.len        \
    };

#define UCVX_FROM_UVX_RANGE(from, begin, len, X)     \
    assert(uv##X##_ebounds_range(from, begin, len)); \
                                                     \
    return (ucv##X##_t) {                            \
        .chars = from.chars + begin,                 \
        .len   = len                                 \
    }

#define UCVX_FROM_USX(from, X)   \
    assert(us##X##_valid(from)); \
                                 \
    return (ucv##X##_t) {        \
        .chars = from->chars,    \
        .len   = from->len       \
    };

#define UCVX_FROM_USX_RANGE(from, begin, len, X)     \
    assert(us##X##_ebounds_range(from, begin, len)); \
                                                     \
    return (ucv##X##_t) {                            \
        .chars = from->chars + begin,                \
        .len   = len                                 \
    }

ucv32_t ucv32_from_uz32(UNULLABLE const uc32_t *from) {
    UCVX_FROM_UZX(from, 32);
}

ucv32_t ucv32_from_uz32_range(const uc32_t *from, size_t begin, size_t len) {
    UCVX_FROM_UZX_RANGE(from, begin, len, 32);
}

ucv32_t ucv32_from_uz32n(const uc32_t *from, size_t from_len) {
    UCVX_FROM_UZXN(from, from_len, 32);
}

ucv32_t ucv32_from_uz32n_range(const uc32_t *from, size_t from_len, size_t begin, size_t len) {
    UCVX_FROM_UZXN_RANGE(from, from_len, begin, len, 32);
}

ucv32_t ucv32_from_ucv32(ucv32_t from) {
    UCVX_FROM_UCVX(from, 32);
}

ucv32_t ucv32_from_ucv32_range(ucv32_t from, size_t begin, size_t len) {
    UCVX_FROM_UCVX_RANGE(from, begin, len, 32);
}

ucv32_t ucv32_from_uv32(uv32_t from) {
    UCVX_FROM_UVX(from, 32);
}

ucv32_t ucv32_from_uv32_range(uv32_t from, size_t begin, size_t len) {
    UCVX_FROM_UVX_RANGE(from, begin, len, 32);
}

ucv32_t ucv32_from_us32(const us32_t *from) {
    UCVX_FROM_USX(from, 32);
}

ucv32_t ucv32_from_us32_range(const us32_t *from, size_t begin, size_t len) {
    UCVX_FROM_USX_RANGE(from, begin, len, 32);
}

ucv16_t ucv16_from_uz16(UNULLABLE const uc16_t *from) {
    UCVX_FROM_UZX(from, 16);
}

ucv16_t ucv16_from_uz16_range(const uc16_t *from, size_t begin, size_t len) {
    UCVX_FROM_UZX_RANGE(from, begin, len, 16);
}

ucv16_t ucv16_from_uz16n(const uc16_t *from, size_t from_len) {
    UCVX_FROM_UZXN(from, from_len, 16);
}

ucv16_t ucv16_from_uz16n_range(const uc16_t *from, size_t from_len, size_t begin, size_t len) {
    UCVX_FROM_UZXN_RANGE(from, from_len, begin, len, 16);
}

ucv16_t ucv16_from_ucv16(ucv16_t from) {
    UCVX_FROM_UCVX(from, 16);
}

ucv16_t ucv16_from_ucv16_range(ucv16_t from, size_t begin, size_t len) {
    UCVX_FROM_UCVX_RANGE(from, begin, len, 16);
}

ucv16_t ucv16_from_uv16(uv16_t from) {
    UCVX_FROM_UVX(from, 16);
}

ucv16_t ucv16_from_uv16_range(uv16_t from, size_t begin, size_t len) {
    UCVX_FROM_UVX_RANGE(from, begin, len, 16);
}

ucv16_t ucv16_from_us16(const us16_t *from) {
    UCVX_FROM_USX(from, 16);
}

ucv16_t ucv16_from_us16_range(const us16_t *from, size_t begin, size_t len) {
    UCVX_FROM_USX_RANGE(from, begin, len, 16);
}

ucv8_t ucv8_from_uz8(UNULLABLE const uc8_t *from) {
    UCVX_FROM_UZX(from, 8);
}

ucv8_t ucv8_from_uz8_range(const uc8_t *from, size_t begin, size_t len) {
    UCVX_FROM_UZX_RANGE(from, begin, len, 8);
}

ucv8_t ucv8_from_uz8n(const uc8_t *from, size_t from_len) {
    UCVX_FROM_UZXN(from, from_len, 8);
}

ucv8_t ucv8_from_uz8n_range(const uc8_t *from, size_t from_len, size_t begin, size_t len) {
    UCVX_FROM_UZXN_RANGE(from, from_len, begin, len, 8);
}

ucv8_t ucv8_from_ucv8(ucv8_t from) {
    UCVX_FROM_UCVX(from, 8);
}

ucv8_t ucv8_from_ucv8_range(ucv8_t from, size_t begin, size_t len) {
    UCVX_FROM_UCVX_RANGE(from, begin, len, 8);
}

ucv8_t ucv8_from_uv8(uv8_t from) {
    UCVX_FROM_UVX(from, 8);
}

ucv8_t ucv8_from_uv8_range(uv8_t from, size_t begin, size_t len) {
    UCVX_FROM_UVX_RANGE(from, begin, len, 8);
}

ucv8_t ucv8_from_us8(const us8_t *from) {
    UCVX_FROM_USX(from, 8);
}

ucv8_t ucv8_from_us8_range(const us8_t *from, size_t begin, size_t len) {
    UCVX_FROM_USX_RANGE(from, begin, len, 8);
}

#define UCVX_FROM_CASE_BOOL(ca, from, X)                      \
    assert(ucase_valid_output(ca));                           \
                                                              \
    return UCASE_UPPER == ca ? ucv##X##_from_upper_bool(from) \
                             : ucv##X##_from_lower_bool(from)

#define UCVX_FROM_LOWER_BOOL(from, X)              \
    return from ? ucv##X("true") : ucv##X("false")

#define UCVX_FROM_UPPER_BOOL(from, X)              \
    return from ? ucv##X("TRUE") : ucv##X("FALSE")

ucv32_t ucv32_from_bool(bool from) {
    return ucv32_from_lower_bool(from);
}

ucv32_t ucv32_from_case_bool(ucase_t ca, bool from) {
    UCVX_FROM_CASE_BOOL(ca, from, 32);
}

ucv32_t ucv32_from_lower_bool(bool from) {
    UCVX_FROM_LOWER_BOOL(from, 32);
}

ucv32_t ucv32_from_upper_bool(bool from) {
    UCVX_FROM_UPPER_BOOL(from, 32);
}

ucv16_t ucv16_from_bool(bool from) {
    return ucv16_from_lower_bool(from);
}

ucv16_t ucv16_from_case_bool(ucase_t ca, bool from) {
    UCVX_FROM_CASE_BOOL(ca, from, 16);
}

ucv16_t ucv16_from_lower_bool(bool from) {
    UCVX_FROM_LOWER_BOOL(from, 16);
}

ucv16_t ucv16_from_upper_bool(bool from) {
    UCVX_FROM_UPPER_BOOL(from, 16);
}

ucv8_t ucv8_from_bool(bool from) {
    return ucv8_from_lower_bool(from);
}

ucv8_t ucv8_from_case_bool(ucase_t ca, bool from) {
    UCVX_FROM_CASE_BOOL(ca, from, 8);
}

ucv8_t ucv8_from_lower_bool(bool from) {
    UCVX_FROM_LOWER_BOOL(from, 8);
}

ucv8_t ucv8_from_upper_bool(bool from) {
    UCVX_FROM_UPPER_BOOL(from, 8);
}

size_t ucv32_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, ucv32_t from) {
    return uz32n_to_bytes(to, encoding, UCV32_CEXPAND(from));
}

size_t ucv16_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, ucv16_t from) {
    return uz16n_to_bytes(to, encoding, UCV16_CEXPAND(from));
}

size_t ucv8_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, ucv8_t from) {
    return uz8n_to_bytes(to, encoding, UCV8_CEXPAND(from));
}

#define UCVX_LEN(view, X)         \
    assert(ucv##X##_valid(view)); \
    return view.len

#define UCVX_LEN_N(view, n, X)                               \
    return uz##X##n_len_n(ucv##X##_cchars(view), view.len, n)

#define UCVX_LEN_Y(view, X, Y)                               \
    return uz##X##n_len_##Y(ucv##X##_cchars(view), view.len)

size_t ucv32_len(ucv32_t view) {
    UCVX_LEN(view, 32);
}

size_t ucv32_len_n(ucv32_t view, unsigned n) {
    UCVX_LEN_N(view, n, 32);
}

size_t ucv32_len_32(ucv32_t view) {
    UCVX_LEN_Y(view, 32, 32);
}

size_t ucv32_len_16(ucv32_t view) {
    UCVX_LEN_Y(view, 32, 16);
}

size_t ucv32_len_8(ucv32_t view) {
    UCVX_LEN_Y(view, 32, 8);
}

size_t ucv16_len(ucv16_t view) {
    UCVX_LEN(view, 16);
}

size_t ucv16_len_n(ucv16_t view, unsigned n) {
    UCVX_LEN_N(view, n, 16);
}

size_t ucv16_len_32(ucv16_t view) {
    UCVX_LEN_Y(view, 16, 32);
}

size_t ucv16_len_16(ucv16_t view) {
    UCVX_LEN_Y(view, 16, 16);
}

size_t ucv16_len_8(ucv16_t view) {
    UCVX_LEN_Y(view, 16, 8);
}

size_t ucv8_len(ucv8_t view) {
    UCVX_LEN(view, 8);
}

size_t ucv8_len_n(ucv8_t view, unsigned n) {
    UCVX_LEN_N(view, n, 8);
}

size_t ucv8_len_32(ucv8_t view) {
    UCVX_LEN_Y(view, 8, 32);
}

size_t ucv8_len_16(ucv8_t view) {
    UCVX_LEN_Y(view, 8, 16);
}

size_t ucv8_len_8(ucv8_t view) {
    UCVX_LEN_Y(view, 8, 8);
}

#define UCVX_SET_LEN(view, len, X)                           \
    assert(ucv##X##_valid_p(view) && (view->chars || !len)); \
    view->len = len

void ucv32_set_len(ucv32_t *view, size_t len) {
    UCVX_SET_LEN(view, len, 32);
}

void ucv16_set_len(ucv16_t *view, size_t len) {
    UCVX_SET_LEN(view, len, 16);
}

void ucv8_set_len(ucv8_t *view, size_t len) {
    UCVX_SET_LEN(view, len, 8);
}

#define UCVX_ADD_LEN(view, delta, X)                                   \
    assert(ucv##X##_valid_p(view) && -(ptrdiff_t) view->len <= delta); \
    return view->len += delta

size_t ucv32_add_len(ucv32_t *view, ptrdiff_t delta) {
    UCVX_ADD_LEN(view, delta, 32);
}

size_t ucv16_add_len(ucv16_t *view, ptrdiff_t delta) {
    UCVX_ADD_LEN(view, delta, 16);
}

size_t ucv8_add_len(ucv8_t *view, ptrdiff_t delta) {
    UCVX_ADD_LEN(view, delta, 8);
}

int ucv32_cmp_uc32(ucv32_t lhs, uc32_t rhs) {
    return uz32n_cmp_uc32(UCV32_CEXPAND(lhs), rhs);
}

int ucv32_cmp_uz32(ucv32_t lhs, const uc32_t *rhs) {
    return uz32n_cmp_uz32(UCV32_CEXPAND(lhs), rhs);
}

int ucv32_cmp_uz32n(ucv32_t lhs, const uc32_t *rhs, size_t rhs_len) {
    return uz32n_cmp_uz32n(UCV32_CEXPAND(lhs), rhs, rhs_len);
}

int ucv32_cmp_ucv32(ucv32_t lhs, ucv32_t rhs) {
    return uz32n_cmp_ucv32(UCV32_CEXPAND(lhs), rhs);
}

int ucv32_cmp_uv32(ucv32_t lhs, uv32_t rhs) {
    return uz32n_cmp_uv32(UCV32_CEXPAND(lhs), rhs);
}

int ucv32_cmp_us32(ucv32_t lhs, const us32_t *rhs) {
    return uz32n_cmp_us32(UCV32_CEXPAND(lhs), rhs);
}

int ucv16_cmp_uc16(ucv16_t lhs, uc16_t rhs) {
    return uz16n_cmp_uc16(UCV16_CEXPAND(lhs), rhs);
}

int ucv16_cmp_uz16(ucv16_t lhs, const uc16_t *rhs) {
    return uz16n_cmp_uz16(UCV16_CEXPAND(lhs), rhs);
}

int ucv16_cmp_uz16n(ucv16_t lhs, const uc16_t *rhs, size_t rhs_len) {
    return uz16n_cmp_uz16n(UCV16_CEXPAND(lhs), rhs, rhs_len);
}

int ucv16_cmp_ucv16(ucv16_t lhs, ucv16_t rhs) {
    return uz16n_cmp_ucv16(UCV16_CEXPAND(lhs), rhs);
}

int ucv16_cmp_uv16(ucv16_t lhs, uv16_t rhs) {
    return uz16n_cmp_uv16(UCV16_CEXPAND(lhs), rhs);
}

int ucv16_cmp_us16(ucv16_t lhs, const us16_t *rhs) {
    return uz16n_cmp_us16(UCV16_CEXPAND(lhs), rhs);
}

int ucv8_cmp_uc8(ucv8_t lhs, uc8_t rhs) {
    return uz8n_cmp_uc8(UCV8_CEXPAND(lhs), rhs);
}

int ucv8_cmp_uz8(ucv8_t lhs, const uc8_t *rhs) {
    return uz8n_cmp_uz8(UCV8_CEXPAND(lhs), rhs);
}

int ucv8_cmp_uz8n(ucv8_t lhs, const uc8_t *rhs, size_t rhs_len) {
    return uz8n_cmp_uz8n(UCV8_CEXPAND(lhs), rhs, rhs_len);
}

int ucv8_cmp_ucv8(ucv8_t lhs, ucv8_t rhs) {
    return uz8n_cmp_ucv8(UCV8_CEXPAND(lhs), rhs);
}

int ucv8_cmp_uv8(ucv8_t lhs, uv8_t rhs) {
    return uz8n_cmp_uv8(UCV8_CEXPAND(lhs), rhs);
}

int ucv8_cmp_us8(ucv8_t lhs, const us8_t *rhs) {
    return uz8n_cmp_us8(UCV8_CEXPAND(lhs), rhs);
}

size_t ucv32_wspace_len(ucv32_t view) {
    return uz32n_wspace_len(UCV32_CEXPAND(view));
}

size_t ucv16_wspace_len(ucv16_t view) {
    return uz16n_wspace_len(UCV16_CEXPAND(view));
}

size_t ucv8_wspace_len(ucv8_t view) {
    return uz8n_wspace_len(UCV8_CEXPAND(view));
}

#define UCVX_TRIM(view, X)       \
    return ucv##X##_ltrim(view), \
           ucv##X##_rtrim(view)
    
#define UCVX_LTRIM(view, X)                                           \
    assert(ucv##X##_valid_p(view));                                   \
                                                                      \
    size_t wspace_len = uz##X##n_wspace_len(UCV##X##_CEXPAND(*view)); \
                                                                      \
    view->chars += wspace_len;                                        \
    view->len   -= wspace_len;                                        \
                                                                      \
    return view->len

#define UCVX_RTRIM(view, X)                                    \
    assert(ucv##X##_valid_p(view));                            \
    return view->len = uz##X##n_rtrim(UCV##X##_CEXPAND(*view))

size_t ucv32_trim(ucv32_t *view) {
    UCVX_TRIM(view, 32);
}

size_t ucv32_ltrim(ucv32_t *view) {
    UCVX_LTRIM(view, 32);
}

size_t ucv32_rtrim(ucv32_t *view) {
    UCVX_RTRIM(view, 32);
}

size_t ucv16_trim(ucv16_t *view) {
    UCVX_TRIM(view, 16);
}

size_t ucv16_ltrim(ucv16_t *view) {
    UCVX_LTRIM(view, 16);
}

size_t ucv16_rtrim(ucv16_t *view) {
    UCVX_RTRIM(view, 16);
}

size_t ucv8_trim(ucv8_t *view) {
    UCVX_TRIM(view, 8);
}

size_t ucv8_ltrim(ucv8_t *view) {
    UCVX_LTRIM(view, 8);
}

size_t ucv8_rtrim(ucv8_t *view) {
    UCVX_RTRIM(view, 8);
}

size_t ucv8_case_len(ucv8_t view, ucase_t ca) {
    return uz8n_case_len(UCV8_CEXPAND(view), ca);
}

size_t ucv8_lower_len(ucv8_t view) {
    return uz8n_lower_len(UCV8_CEXPAND(view));
}

size_t ucv8_upper_len(ucv8_t view) {
    return uz8n_upper_len(UCV8_CEXPAND(view));
}

size_t ucv32_new_csplit_uc32(ucv32_t view, uc32_t sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uc32(UCV32_CEXPAND(view), sep, array);
}

size_t ucv32_new_csplit_uc32_e(ucv32_t view, uc32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uc32_e(UCV32_CEXPAND(view), sep, array, error);
}

size_t ucv32_csplit_uc32(ucv32_t view, uc32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uc32(UCV32_CEXPAND(view), sep, array, array_len);
}

size_t ucv32_new_csplit_uz32(ucv32_t view, const uc32_t *sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uz32(UCV32_CEXPAND(view), sep, array);
}

size_t ucv32_new_csplit_uz32_e(ucv32_t view, const uc32_t *sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32_e(UCV32_CEXPAND(view), sep, array, error);
}

size_t ucv32_csplit_uz32(ucv32_t view, const uc32_t *sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32(UCV32_CEXPAND(view), sep, array, array_len);
}

size_t ucv32_new_csplit_uz32n(ucv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uz32n(UCV32_CEXPAND(view), sep, sep_len, array);
}

size_t ucv32_new_csplit_uz32n_e(ucv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(UCV32_CEXPAND(view), sep, sep_len, array, error);
}

size_t ucv32_csplit_uz32n(ucv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(UCV32_CEXPAND(view), sep, sep_len, array, array_len);
}

size_t ucv32_new_csplit_ucv32(ucv32_t view, ucv32_t sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_ucv32(UCV32_CEXPAND(view), sep, array);
}

size_t ucv32_new_csplit_ucv32_e(ucv32_t view, ucv32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_ucv32_e(UCV32_CEXPAND(view), sep, array, error);
}

size_t ucv32_csplit_ucv32(ucv32_t view, ucv32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_ucv32(UCV32_CEXPAND(view), sep, array, array_len);
}

size_t ucv32_new_csplit_uv32(ucv32_t view, uv32_t sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uv32(UCV32_CEXPAND(view), sep, array);
}

size_t ucv32_new_csplit_uv32_e(ucv32_t view, uv32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uv32_e(UCV32_CEXPAND(view), sep, array, error);
}

size_t ucv32_csplit_uv32(ucv32_t view, uv32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uv32(UCV32_CEXPAND(view), sep, array, array_len);
}

size_t ucv32_new_csplit_us32(ucv32_t view, const us32_t *sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_us32(UCV32_CEXPAND(view), sep, array);
}

size_t ucv32_new_csplit_us32_e(ucv32_t view, const us32_t *sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_us32_e(UCV32_CEXPAND(view), sep, array, error);
}

size_t ucv32_csplit_us32(ucv32_t view, const us32_t *sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_us32(UCV32_CEXPAND(view), sep, array, array_len);
}

size_t ucv16_new_csplit_uc16(ucv16_t view, uc16_t sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uc16(UCV16_CEXPAND(view), sep, array);
}

size_t ucv16_new_csplit_uc16_e(ucv16_t view, uc16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uc16_e(UCV16_CEXPAND(view), sep, array, error);
}

size_t ucv16_csplit_uc16(ucv16_t view, uc16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uc16(UCV16_CEXPAND(view), sep, array, array_len);
}

size_t ucv16_new_csplit_uz16(ucv16_t view, const uc16_t *sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uz16(UCV16_CEXPAND(view), sep, array);
}

size_t ucv16_new_csplit_uz16_e(ucv16_t view, const uc16_t *sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uz16_e(UCV16_CEXPAND(view), sep, array, error);
}

size_t ucv16_csplit_uz16(ucv16_t view, const uc16_t *sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uz16(UCV16_CEXPAND(view), sep, array, array_len);
}

size_t ucv16_new_csplit_uz16n(ucv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uz16n(UCV16_CEXPAND(view), sep, sep_len, array);
}

size_t ucv16_new_csplit_uz16n_e(ucv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uz16n_e(UCV16_CEXPAND(view), sep, sep_len, array, error);
}

size_t ucv16_csplit_uz16n(ucv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uz16n(UCV16_CEXPAND(view), sep, sep_len, array, array_len);
}

size_t ucv16_new_csplit_ucv16(ucv16_t view, ucv16_t sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_ucv16(UCV16_CEXPAND(view), sep, array);
}

size_t ucv16_new_csplit_ucv16_e(ucv16_t view, ucv16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_ucv16_e(UCV16_CEXPAND(view), sep, array, error);
}

size_t ucv16_csplit_ucv16(ucv16_t view, ucv16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_ucv16(UCV16_CEXPAND(view), sep, array, array_len);
}

size_t ucv16_new_csplit_uv16(ucv16_t view, uv16_t sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uv16(UCV16_CEXPAND(view), sep, array);
}

size_t ucv16_new_csplit_uv16_e(ucv16_t view, uv16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uv16_e(UCV16_CEXPAND(view), sep, array, error);
}

size_t ucv16_csplit_uv16(ucv16_t view, uv16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uv16(UCV16_CEXPAND(view), sep, array, array_len);
}

size_t ucv16_new_csplit_us16(ucv16_t view, const us16_t *sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_us16(UCV16_CEXPAND(view), sep, array);
}

size_t ucv16_new_csplit_us16_e(ucv16_t view, const us16_t *sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_us16_e(UCV16_CEXPAND(view), sep, array, error);
}

size_t ucv16_csplit_us16(ucv16_t view, const us16_t *sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_us16(UCV16_CEXPAND(view), sep, array, array_len);
}

size_t ucv8_new_csplit_uc8(ucv8_t view, uc8_t sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uc8(UCV8_CEXPAND(view), sep, array);
}

size_t ucv8_new_csplit_uc8_e(ucv8_t view, uc8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uc8_e(UCV8_CEXPAND(view), sep, array, error);
}

size_t ucv8_csplit_uc8(ucv8_t view, uc8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uc8(UCV8_CEXPAND(view), sep, array, array_len);
}

size_t ucv8_new_csplit_uz8(ucv8_t view, const uc8_t *sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uz8(UCV8_CEXPAND(view), sep, array);
}

size_t ucv8_new_csplit_uz8_e(ucv8_t view, const uc8_t *sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uz8_e(UCV8_CEXPAND(view), sep, array, error);
}

size_t ucv8_csplit_uz8(ucv8_t view, const uc8_t *sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uz8(UCV8_CEXPAND(view), sep, array, array_len);
}

size_t ucv8_new_csplit_uz8n(ucv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uz8n(UCV8_CEXPAND(view), sep, sep_len, array);
}

size_t ucv8_new_csplit_uz8n_e(ucv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uz8n_e(UCV8_CEXPAND(view), sep, sep_len, array, error);
}

size_t ucv8_csplit_uz8n(ucv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uz8n(UCV8_CEXPAND(view), sep, sep_len, array, array_len);
}

size_t ucv8_new_csplit_ucv8(ucv8_t view, ucv8_t sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_ucv8(UCV8_CEXPAND(view), sep, array);
}

size_t ucv8_new_csplit_ucv8_e(ucv8_t view, ucv8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_ucv8_e(UCV8_CEXPAND(view), sep, array, error);
}

size_t ucv8_csplit_ucv8(ucv8_t view, ucv8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_ucv8(UCV8_CEXPAND(view), sep, array, array_len);
}

size_t ucv8_new_csplit_uv8(ucv8_t view, uv8_t sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uv8(UCV8_CEXPAND(view), sep, array);
}

size_t ucv8_new_csplit_uv8_e(ucv8_t view, uv8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uv8_e(UCV8_CEXPAND(view), sep, array, error);
}

size_t ucv8_csplit_uv8(ucv8_t view, uv8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uv8(UCV8_CEXPAND(view), sep, array, array_len);
}

size_t ucv8_new_csplit_us8(ucv8_t view, const us8_t *sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_us8(UCV8_CEXPAND(view), sep, array);
}

size_t ucv8_new_csplit_us8_e(ucv8_t view, const us8_t *sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_us8_e(UCV8_CEXPAND(view), sep, array, error);
}

size_t ucv8_csplit_us8(ucv8_t view, const us8_t *sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_us8(UCV8_CEXPAND(view), sep, array, array_len);
}

bool ucv32_contains_uc32(ucv32_t view, uc32_t target) {
    return uz32n_contains_uc32(UCV32_CEXPAND(view), target);
}

bool ucv32_contains_uz32(ucv32_t view, const uc32_t *target) {
    return uz32n_contains_uz32(UCV32_CEXPAND(view), target);
}

bool ucv32_contains_uz32n(ucv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_contains_uz32n(UCV32_CEXPAND(view), target, target_len);
}

bool ucv32_contains_ucv32(ucv32_t view, ucv32_t target) {
    return uz32n_contains_ucv32(UCV32_CEXPAND(view), target);
}

bool ucv32_contains_uv32(ucv32_t view, uv32_t target) {
    return uz32n_contains_uv32(UCV32_CEXPAND(view), target);
}

bool ucv32_contains_us32(ucv32_t view, const us32_t *target) {
    return uz32n_contains_us32(UCV32_CEXPAND(view), target);
}

bool ucv16_contains_uc16(ucv16_t view, uc16_t target) {
    return uz16n_contains_uc16(UCV16_CEXPAND(view), target);
}

bool ucv16_contains_uz16(ucv16_t view, const uc16_t *target) {
    return uz16n_contains_uz16(UCV16_CEXPAND(view), target);
}

bool ucv16_contains_uz16n(ucv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_contains_uz16n(UCV16_CEXPAND(view), target, target_len);
}

bool ucv16_contains_ucv16(ucv16_t view, ucv16_t target) {
    return uz16n_contains_ucv16(UCV16_CEXPAND(view), target);
}

bool ucv16_contains_uv16(ucv16_t view, uv16_t target) {
    return uz16n_contains_uv16(UCV16_CEXPAND(view), target);
}

bool ucv16_contains_us16(ucv16_t view, const us16_t *target) {
    return uz16n_contains_us16(UCV16_CEXPAND(view), target);
}

bool ucv8_contains_uc8(ucv8_t view, uc8_t target) {
    return uz8n_contains_uc8(UCV8_CEXPAND(view), target);
}

bool ucv8_contains_uz8(ucv8_t view, const uc8_t *target) {
    return uz8n_contains_uz8(UCV8_CEXPAND(view), target);
}

bool ucv8_contains_uz8n(ucv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_contains_uz8n(UCV8_CEXPAND(view), target, target_len);
}

bool ucv8_contains_ucv8(ucv8_t view, ucv8_t target) {
    return uz8n_contains_ucv8(UCV8_CEXPAND(view), target);
}

bool ucv8_contains_uv8(ucv8_t view, uv8_t target) {
    return uz8n_contains_uv8(UCV8_CEXPAND(view), target);
}

bool ucv8_contains_us8(ucv8_t view, const us8_t *target) {
    return uz8n_contains_us8(UCV8_CEXPAND(view), target);
}

#define UCVX_FIND_UTX_FROM(view, target, from, X, T)                          \
    assert(ucv##X##_ebounds(view, from));                                     \
    return uz##X##n_find_u##T##X##_from(UCV##X##_CEXPAND(view), target, from)

#define UCVX_FIND_UZXN_FROM(view, target, target_len, from, X)                           \
    assert(ucv##X##_ebounds(view, from));                                                \
    return uz##X##n_find_uz##X##n_from(UCV##X##_CEXPAND(view), target, target_len, from)

ptrdiff_t ucv32_find_uc32(ucv32_t view, uc32_t target) {
    return uz32n_find_uc32(UCV32_CEXPAND(view), target);
}

ptrdiff_t ucv32_find_uc32_from(ucv32_t view, uc32_t target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 32, c);
}

ptrdiff_t ucv32_find_uz32(ucv32_t view, const uc32_t *target) {
    return uz32n_find_uz32(UCV32_CEXPAND(view), target);
}

ptrdiff_t ucv32_find_uz32_from(ucv32_t view, const uc32_t *target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 32, z);
}

ptrdiff_t ucv32_find_uz32n(ucv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_find_uz32n(UCV32_CEXPAND(view), target, target_len);
}

ptrdiff_t ucv32_find_uz32n_from(ucv32_t view, const uc32_t *target, size_t target_len, size_t from) {
    UCVX_FIND_UZXN_FROM(view, target, target_len, from, 32);
}

ptrdiff_t ucv32_find_ucv32(ucv32_t view, ucv32_t target) {
    return uz32n_find_ucv32(UCV32_CEXPAND(view), target);
}

ptrdiff_t ucv32_find_ucv32_from(ucv32_t view, ucv32_t target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 32, cv);
}

ptrdiff_t ucv32_find_uv32(ucv32_t view, uv32_t target) {
    return uz32n_find_uv32(UCV32_CEXPAND(view), target);
}

ptrdiff_t ucv32_find_uv32_from(ucv32_t view, uv32_t target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 32, v);
}

ptrdiff_t ucv32_find_us32(ucv32_t view, const us32_t *target) {
    return uz32n_find_us32(UCV32_CEXPAND(view), target);
}

ptrdiff_t ucv32_find_us32_from(ucv32_t view, const us32_t *target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 32, s);
}

ptrdiff_t ucv16_find_uc16(ucv16_t view, uc16_t target) {
    return uz16n_find_uc16(UCV16_CEXPAND(view), target);
}

ptrdiff_t ucv16_find_uc16_from(ucv16_t view, uc16_t target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 16, c);
}

ptrdiff_t ucv16_find_uz16(ucv16_t view, const uc16_t *target) {
    return uz16n_find_uz16(UCV16_CEXPAND(view), target);
}

ptrdiff_t ucv16_find_uz16_from(ucv16_t view, const uc16_t *target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 16, z);
}

ptrdiff_t ucv16_find_uz16n(ucv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_find_uz16n(UCV16_CEXPAND(view), target, target_len);
}

ptrdiff_t ucv16_find_uz16n_from(ucv16_t view, const uc16_t *target, size_t target_len, size_t from) {
    UCVX_FIND_UZXN_FROM(view, target, target_len, from, 16);
}

ptrdiff_t ucv16_find_ucv16(ucv16_t view, ucv16_t target) {
    return uz16n_find_ucv16(UCV16_CEXPAND(view), target);
}

ptrdiff_t ucv16_find_ucv16_from(ucv16_t view, ucv16_t target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 16, cv);
}

ptrdiff_t ucv16_find_uv16(ucv16_t view, uv16_t target) {
    return uz16n_find_uv16(UCV16_CEXPAND(view), target);
}

ptrdiff_t ucv16_find_uv16_from(ucv16_t view, uv16_t target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 16, v);
}

ptrdiff_t ucv16_find_us16(ucv16_t view, const us16_t *target) {
    return uz16n_find_us16(UCV16_CEXPAND(view), target);
}

ptrdiff_t ucv16_find_us16_from(ucv16_t view, const us16_t *target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 16, s);
}

ptrdiff_t ucv8_find_uc8(ucv8_t view, uc8_t target) {
    return uz8n_find_uc8(UCV8_CEXPAND(view), target);
}

ptrdiff_t ucv8_find_uc8_from(ucv8_t view, uc8_t target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 8, c);
}

ptrdiff_t ucv8_find_uz8(ucv8_t view, const uc8_t *target) {
    return uz8n_find_uz8(UCV8_CEXPAND(view), target);
}

ptrdiff_t ucv8_find_uz8_from(ucv8_t view, const uc8_t *target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 8, z);
}

ptrdiff_t ucv8_find_uz8n(ucv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_find_uz8n(UCV8_CEXPAND(view), target, target_len);
}

ptrdiff_t ucv8_find_uz8n_from(ucv8_t view, const uc8_t *target, size_t target_len, size_t from) {
    UCVX_FIND_UZXN_FROM(view, target, target_len, from, 8);
}

ptrdiff_t ucv8_find_ucv8(ucv8_t view, ucv8_t target) {
    return uz8n_find_ucv8(UCV8_CEXPAND(view), target);
}

ptrdiff_t ucv8_find_ucv8_from(ucv8_t view, ucv8_t target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 8, cv);
}

ptrdiff_t ucv8_find_uv8(ucv8_t view, uv8_t target) {
    return uz8n_find_uv8(UCV8_CEXPAND(view), target);
}

ptrdiff_t ucv8_find_uv8_from(ucv8_t view, uv8_t target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 8, v);
}

ptrdiff_t ucv8_find_us8(ucv8_t view, const us8_t *target) {
    return uz8n_find_us8(UCV8_CEXPAND(view), target);
}

ptrdiff_t ucv8_find_us8_from(ucv8_t view, const us8_t *target, size_t from) {
    UCVX_FIND_UTX_FROM(view, target, from, 8, s);
}

#define UCVX_RFIND_UTX_FROM(view, target, from, X, T)                         \
    assert(ucv##X##_ebounds(view, from));                                     \
    return uz##X##n_rfind_u##T##X##_from(UCV##X##_CEXPAND(view), target, from)

#define UCVX_RFIND_UZXN_FROM(view, target, target_len, from, X)                          \
    assert(ucv##X##_ebounds(view, from));                                                \
    return uz##X##n_rfind_uz##X##n_from(UCV##X##_CEXPAND(view), target, target_len, from)

ptrdiff_t ucv32_rfind_uc32(ucv32_t view, uc32_t target) {
    return uz32n_rfind_uc32(UCV32_CEXPAND(view), target);
}

ptrdiff_t ucv32_rfind_uc32_from(ucv32_t view, uc32_t target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 32, c);
}

ptrdiff_t ucv32_rfind_uz32(ucv32_t view, const uc32_t *target) {
    return uz32n_rfind_uz32(UCV32_CEXPAND(view), target);
}

ptrdiff_t ucv32_rfind_uz32_from(ucv32_t view, const uc32_t *target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 32, z);
}

ptrdiff_t ucv32_rfind_uz32n(ucv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_rfind_uz32n(UCV32_CEXPAND(view), target, target_len);
}

ptrdiff_t ucv32_rfind_uz32n_from(ucv32_t view, const uc32_t *target, size_t target_len, size_t from) {
    UCVX_RFIND_UZXN_FROM(view, target, target_len, from, 32);
}

ptrdiff_t ucv32_rfind_ucv32(ucv32_t view, ucv32_t target) {
    return uz32n_rfind_ucv32(UCV32_CEXPAND(view), target);
}

ptrdiff_t ucv32_rfind_ucv32_from(ucv32_t view, ucv32_t target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 32, cv);
}

ptrdiff_t ucv32_rfind_uv32(ucv32_t view, uv32_t target) {
    return uz32n_rfind_uv32(UCV32_CEXPAND(view), target);
}

ptrdiff_t ucv32_rfind_uv32_from(ucv32_t view, uv32_t target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 32, v);
}

ptrdiff_t ucv32_rfind_us32(ucv32_t view, const us32_t *target) {
    return uz32n_rfind_us32(UCV32_CEXPAND(view), target);
}

ptrdiff_t ucv32_rfind_us32_from(ucv32_t view, const us32_t *target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 32, s);
}

ptrdiff_t ucv16_rfind_uc16(ucv16_t view, uc16_t target) {
    return uz16n_rfind_uc16(UCV16_CEXPAND(view), target);
}

ptrdiff_t ucv16_rfind_uc16_from(ucv16_t view, uc16_t target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 16, c);
}

ptrdiff_t ucv16_rfind_uz16(ucv16_t view, const uc16_t *target) {
    return uz16n_rfind_uz16(UCV16_CEXPAND(view), target);
}

ptrdiff_t ucv16_rfind_uz16_from(ucv16_t view, const uc16_t *target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 16, z);
}

ptrdiff_t ucv16_rfind_uz16n(ucv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_rfind_uz16n(UCV16_CEXPAND(view), target, target_len);
}

ptrdiff_t ucv16_rfind_uz16n_from(ucv16_t view, const uc16_t *target, size_t target_len, size_t from) {
    UCVX_RFIND_UZXN_FROM(view, target, target_len, from, 16);
}

ptrdiff_t ucv16_rfind_ucv16(ucv16_t view, ucv16_t target) {
    return uz16n_rfind_ucv16(UCV16_CEXPAND(view), target);
}

ptrdiff_t ucv16_rfind_ucv16_from(ucv16_t view, ucv16_t target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 16, cv);
}

ptrdiff_t ucv16_rfind_uv16(ucv16_t view, uv16_t target) {
    return uz16n_rfind_uv16(UCV16_CEXPAND(view), target);
}

ptrdiff_t ucv16_rfind_uv16_from(ucv16_t view, uv16_t target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 16, v);
}

ptrdiff_t ucv16_rfind_us16(ucv16_t view, const us16_t *target) {
    return uz16n_rfind_us16(UCV16_CEXPAND(view), target);
}

ptrdiff_t ucv16_rfind_us16_from(ucv16_t view, const us16_t *target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 16, s);
}

ptrdiff_t ucv8_rfind_uc8(ucv8_t view, uc8_t target) {
    return uz8n_rfind_uc8(UCV8_CEXPAND(view), target);
}

ptrdiff_t ucv8_rfind_uc8_from(ucv8_t view, uc8_t target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 8, c);
}

ptrdiff_t ucv8_rfind_uz8(ucv8_t view, const uc8_t *target) {
    return uz8n_rfind_uz8(UCV8_CEXPAND(view), target);
}

ptrdiff_t ucv8_rfind_uz8_from(ucv8_t view, const uc8_t *target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 8, z);
}

ptrdiff_t ucv8_rfind_uz8n(ucv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_rfind_uz8n(UCV8_CEXPAND(view), target, target_len);
}

ptrdiff_t ucv8_rfind_uz8n_from(ucv8_t view, const uc8_t *target, size_t target_len, size_t from) {
    UCVX_RFIND_UZXN_FROM(view, target, target_len, from, 8);
}

ptrdiff_t ucv8_rfind_ucv8(ucv8_t view, ucv8_t target) {
    return uz8n_rfind_ucv8(UCV8_CEXPAND(view), target);
}

ptrdiff_t ucv8_rfind_ucv8_from(ucv8_t view, ucv8_t target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 8, cv);
}

ptrdiff_t ucv8_rfind_uv8(ucv8_t view, uv8_t target) {
    return uz8n_rfind_uv8(UCV8_CEXPAND(view), target);
}

ptrdiff_t ucv8_rfind_uv8_from(ucv8_t view, uv8_t target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 8, v);
}

ptrdiff_t ucv8_rfind_us8(ucv8_t view, const us8_t *target) {
    return uz8n_rfind_us8(UCV8_CEXPAND(view), target);
}

ptrdiff_t ucv8_rfind_us8_from(ucv8_t view, const us8_t *target, size_t from) {
    UCVX_RFIND_UTX_FROM(view, target, from, 8, s);
}

size_t ucv32_replaced_len_uc32_uz32(ucv32_t view, uc32_t from, const uc32_t *to) {
    return uz32n_replaced_len_uc32_uz32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uc32_uz32n(ucv32_t view, uc32_t from, size_t to_len) {
    return uz32n_replaced_len_uc32_uz32n(UCV32_CEXPAND(view), from, to_len);
}

size_t ucv32_replaced_len_uc32_ucv32(ucv32_t view, uc32_t from, ucv32_t to) {
    return uz32n_replaced_len_uc32_ucv32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uc32_uv32(ucv32_t view, uc32_t from, uv32_t to) {
    return uz32n_replaced_len_uc32_uv32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uc32_us32(ucv32_t view, uc32_t from, const us32_t *to) {
    return uz32n_replaced_len_uc32_us32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uz32_uc32(ucv32_t view, const uc32_t *from, uc32_t to) {
    return uz32n_replaced_len_uz32_uc32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uz32_uz32(ucv32_t view, const uc32_t *from, const uc32_t *to) {
    return uz32n_replaced_len_uz32_uz32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uz32_uz32n(ucv32_t view, const uc32_t *from, size_t to_len) {
    return uz32n_replaced_len_uz32_uz32n(UCV32_CEXPAND(view), from, to_len);
}

size_t ucv32_replaced_len_uz32_ucv32(ucv32_t view, const uc32_t *from, ucv32_t to) {
    return uz32n_replaced_len_uz32_ucv32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uz32_uv32(ucv32_t view, const uc32_t *from, uv32_t to) {
    return uz32n_replaced_len_uz32_uv32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uz32_us32(ucv32_t view, const uc32_t *from, const us32_t *to) {
    return uz32n_replaced_len_uz32_us32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uz32n_uc32(ucv32_t view, const uc32_t *from, size_t from_len, uc32_t to) {
    return uz32n_replaced_len_uz32n_uc32(UCV32_CEXPAND(view), from, from_len, to);
}

size_t ucv32_replaced_len_uz32n_uz32(ucv32_t view, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32n_replaced_len_uz32n_uz32(UCV32_CEXPAND(view), from, from_len, to);
}

size_t ucv32_replaced_len_uz32n_uz32n(ucv32_t view, const uc32_t *from, size_t from_len, size_t to_len) {
    return uz32n_replaced_len_uz32n_uz32n(UCV32_CEXPAND(view), from, from_len, to_len);
}

size_t ucv32_replaced_len_uz32n_ucv32(ucv32_t view, const uc32_t *from, size_t from_len, ucv32_t to) {
    return uz32n_replaced_len_uz32n_ucv32(UCV32_CEXPAND(view), from, from_len, to);
}

size_t ucv32_replaced_len_uz32n_uv32(ucv32_t view, const uc32_t *from, size_t from_len, uv32_t to) {
    return uz32n_replaced_len_uz32n_uv32(UCV32_CEXPAND(view), from, from_len, to);
}

size_t ucv32_replaced_len_uz32n_us32(ucv32_t view, const uc32_t *from, size_t from_len, const us32_t *to) {
    return uz32n_replaced_len_uz32n_us32(UCV32_CEXPAND(view), from, from_len, to);
}

size_t ucv32_replaced_len_ucv32_uc32(ucv32_t view, ucv32_t from, uc32_t to) {
    return uz32n_replaced_len_ucv32_uc32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_ucv32_uz32(ucv32_t view, ucv32_t from, const uc32_t *to) {
    return uz32n_replaced_len_ucv32_uz32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_ucv32_uz32n(ucv32_t view, ucv32_t from, size_t to_len) {
    return uz32n_replaced_len_ucv32_uz32n(UCV32_CEXPAND(view), from, to_len);
}

size_t ucv32_replaced_len_ucv32_ucv32(ucv32_t view, ucv32_t from, ucv32_t to) {
    return uz32n_replaced_len_ucv32_ucv32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_ucv32_uv32(ucv32_t view, ucv32_t from, uv32_t to) {
    return uz32n_replaced_len_ucv32_uv32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_ucv32_us32(ucv32_t view, ucv32_t from, const us32_t *to) {
    return uz32n_replaced_len_ucv32_us32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uv32_uc32(ucv32_t view, uv32_t from, uc32_t to) {
    return uz32n_replaced_len_uv32_uc32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uv32_uz32(ucv32_t view, uv32_t from, const uc32_t *to) {
    return uz32n_replaced_len_uv32_uz32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uv32_uz32n(ucv32_t view, uv32_t from, size_t to_len) {
    return uz32n_replaced_len_uv32_uz32n(UCV32_CEXPAND(view), from, to_len);
}

size_t ucv32_replaced_len_uv32_ucv32(ucv32_t view, uv32_t from, ucv32_t to) {
    return uz32n_replaced_len_uv32_ucv32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uv32_uv32(ucv32_t view, uv32_t from, uv32_t to) {
    return uz32n_replaced_len_uv32_uv32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_uv32_us32(ucv32_t view, uv32_t from, const us32_t *to) {
    return uz32n_replaced_len_uv32_us32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_us32_uc32(ucv32_t view, const us32_t *from, uc32_t to) {
    return uz32n_replaced_len_us32_uc32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_us32_uz32(ucv32_t view, const us32_t *from, const uc32_t *to) {
    return uz32n_replaced_len_us32_uz32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_us32_uz32n(ucv32_t view, const us32_t *from, size_t to_len) {
    return uz32n_replaced_len_us32_uz32n(UCV32_CEXPAND(view), from, to_len);
}

size_t ucv32_replaced_len_us32_ucv32(ucv32_t view, const us32_t *from, ucv32_t to) {
    return uz32n_replaced_len_us32_ucv32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_us32_uv32(ucv32_t view, const us32_t *from, uv32_t to) {
    return uz32n_replaced_len_us32_uv32(UCV32_CEXPAND(view), from, to);
}

size_t ucv32_replaced_len_us32_us32(ucv32_t view, const us32_t *from, const us32_t *to) {
    return uz32n_replaced_len_us32_us32(UCV32_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uc16_uz16(ucv16_t view, uc16_t from, const uc16_t *to) {
    return uz16n_replaced_len_uc16_uz16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uc16_uz16n(ucv16_t view, uc16_t from, size_t to_len) {
    return uz16n_replaced_len_uc16_uz16n(UCV16_CEXPAND(view), from, to_len);
}

size_t ucv16_replaced_len_uc16_ucv16(ucv16_t view, uc16_t from, ucv16_t to) {
    return uz16n_replaced_len_uc16_ucv16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uc16_uv16(ucv16_t view, uc16_t from, uv16_t to) {
    return uz16n_replaced_len_uc16_uv16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uc16_us16(ucv16_t view, uc16_t from, const us16_t *to) {
    return uz16n_replaced_len_uc16_us16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uz16_uc16(ucv16_t view, const uc16_t *from, uc16_t to) {
    return uz16n_replaced_len_uz16_uc16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uz16_uz16(ucv16_t view, const uc16_t *from, const uc16_t *to) {
    return uz16n_replaced_len_uz16_uz16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uz16_uz16n(ucv16_t view, const uc16_t *from, size_t to_len) {
    return uz16n_replaced_len_uz16_uz16n(UCV16_CEXPAND(view), from, to_len);
}

size_t ucv16_replaced_len_uz16_ucv16(ucv16_t view, const uc16_t *from, ucv16_t to) {
    return uz16n_replaced_len_uz16_ucv16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uz16_uv16(ucv16_t view, const uc16_t *from, uv16_t to) {
    return uz16n_replaced_len_uz16_uv16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uz16_us16(ucv16_t view, const uc16_t *from, const us16_t *to) {
    return uz16n_replaced_len_uz16_us16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uz16n_uc16(ucv16_t view, const uc16_t *from, size_t from_len, uc16_t to) {
    return uz16n_replaced_len_uz16n_uc16(UCV16_CEXPAND(view), from, from_len, to);
}

size_t ucv16_replaced_len_uz16n_uz16(ucv16_t view, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16n_replaced_len_uz16n_uz16(UCV16_CEXPAND(view), from, from_len, to);
}

size_t ucv16_replaced_len_uz16n_uz16n(ucv16_t view, const uc16_t *from, size_t from_len, size_t to_len) {
    return uz16n_replaced_len_uz16n_uz16n(UCV16_CEXPAND(view), from, from_len, to_len);
}

size_t ucv16_replaced_len_uz16n_ucv16(ucv16_t view, const uc16_t *from, size_t from_len, ucv16_t to) {
    return uz16n_replaced_len_uz16n_ucv16(UCV16_CEXPAND(view), from, from_len, to);
}

size_t ucv16_replaced_len_uz16n_uv16(ucv16_t view, const uc16_t *from, size_t from_len, uv16_t to) {
    return uz16n_replaced_len_uz16n_uv16(UCV16_CEXPAND(view), from, from_len, to);
}

size_t ucv16_replaced_len_uz16n_us16(ucv16_t view, const uc16_t *from, size_t from_len, const us16_t *to) {
    return uz16n_replaced_len_uz16n_us16(UCV16_CEXPAND(view), from, from_len, to);
}

size_t ucv16_replaced_len_ucv16_uc16(ucv16_t view, ucv16_t from, uc16_t to) {
    return uz16n_replaced_len_ucv16_uc16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_ucv16_uz16(ucv16_t view, ucv16_t from, const uc16_t *to) {
    return uz16n_replaced_len_ucv16_uz16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_ucv16_uz16n(ucv16_t view, ucv16_t from, size_t to_len) {
    return uz16n_replaced_len_ucv16_uz16n(UCV16_CEXPAND(view), from, to_len);
}

size_t ucv16_replaced_len_ucv16_ucv16(ucv16_t view, ucv16_t from, ucv16_t to) {
    return uz16n_replaced_len_ucv16_ucv16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_ucv16_uv16(ucv16_t view, ucv16_t from, uv16_t to) {
    return uz16n_replaced_len_ucv16_uv16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_ucv16_us16(ucv16_t view, ucv16_t from, const us16_t *to) {
    return uz16n_replaced_len_ucv16_us16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uv16_uc16(ucv16_t view, uv16_t from, uc16_t to) {
    return uz16n_replaced_len_uv16_uc16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uv16_uz16(ucv16_t view, uv16_t from, const uc16_t *to) {
    return uz16n_replaced_len_uv16_uz16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uv16_uz16n(ucv16_t view, uv16_t from, size_t to_len) {
    return uz16n_replaced_len_uv16_uz16n(UCV16_CEXPAND(view), from, to_len);
}

size_t ucv16_replaced_len_uv16_ucv16(ucv16_t view, uv16_t from, ucv16_t to) {
    return uz16n_replaced_len_uv16_ucv16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uv16_uv16(ucv16_t view, uv16_t from, uv16_t to) {
    return uz16n_replaced_len_uv16_uv16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_uv16_us16(ucv16_t view, uv16_t from, const us16_t *to) {
    return uz16n_replaced_len_uv16_us16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_us16_uc16(ucv16_t view, const us16_t *from, uc16_t to) {
    return uz16n_replaced_len_us16_uc16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_us16_uz16(ucv16_t view, const us16_t *from, const uc16_t *to) {
    return uz16n_replaced_len_us16_uz16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_us16_uz16n(ucv16_t view, const us16_t *from, size_t to_len) {
    return uz16n_replaced_len_us16_uz16n(UCV16_CEXPAND(view), from, to_len);
}

size_t ucv16_replaced_len_us16_ucv16(ucv16_t view, const us16_t *from, ucv16_t to) {
    return uz16n_replaced_len_us16_ucv16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_us16_uv16(ucv16_t view, const us16_t *from, uv16_t to) {
    return uz16n_replaced_len_us16_uv16(UCV16_CEXPAND(view), from, to);
}

size_t ucv16_replaced_len_us16_us16(ucv16_t view, const us16_t *from, const us16_t *to) {
    return uz16n_replaced_len_us16_us16(UCV16_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uc8_uz8(ucv8_t view, uc8_t from, const uc8_t *to) {
    return uz8n_replaced_len_uc8_uz8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uc8_uz8n(ucv8_t view, uc8_t from, size_t to_len) {
    return uz8n_replaced_len_uc8_uz8n(UCV8_CEXPAND(view), from, to_len);
}

size_t ucv8_replaced_len_uc8_ucv8(ucv8_t view, uc8_t from, ucv8_t to) {
    return uz8n_replaced_len_uc8_ucv8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uc8_uv8(ucv8_t view, uc8_t from, uv8_t to) {
    return uz8n_replaced_len_uc8_uv8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uc8_us8(ucv8_t view, uc8_t from, const us8_t *to) {
    return uz8n_replaced_len_uc8_us8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uz8_uc8(ucv8_t view, const uc8_t *from, uc8_t to) {
    return uz8n_replaced_len_uz8_uc8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uz8_uz8(ucv8_t view, const uc8_t *from, const uc8_t *to) {
    return uz8n_replaced_len_uz8_uz8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uz8_uz8n(ucv8_t view, const uc8_t *from, size_t to_len) {
    return uz8n_replaced_len_uz8_uz8n(UCV8_CEXPAND(view), from, to_len);
}

size_t ucv8_replaced_len_uz8_ucv8(ucv8_t view, const uc8_t *from, ucv8_t to) {
    return uz8n_replaced_len_uz8_ucv8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uz8_uv8(ucv8_t view, const uc8_t *from, uv8_t to) {
    return uz8n_replaced_len_uz8_uv8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uz8_us8(ucv8_t view, const uc8_t *from, const us8_t *to) {
    return uz8n_replaced_len_uz8_us8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uz8n_uc8(ucv8_t view, const uc8_t *from, size_t from_len, uc8_t to) {
    return uz8n_replaced_len_uz8n_uc8(UCV8_CEXPAND(view), from, from_len, to);
}

size_t ucv8_replaced_len_uz8n_uz8(ucv8_t view, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8n_replaced_len_uz8n_uz8(UCV8_CEXPAND(view), from, from_len, to);
}

size_t ucv8_replaced_len_uz8n_uz8n(ucv8_t view, const uc8_t *from, size_t from_len, size_t to_len) {
    return uz8n_replaced_len_uz8n_uz8n(UCV8_CEXPAND(view), from, from_len, to_len);
}

size_t ucv8_replaced_len_uz8n_ucv8(ucv8_t view, const uc8_t *from, size_t from_len, ucv8_t to) {
    return uz8n_replaced_len_uz8n_ucv8(UCV8_CEXPAND(view), from, from_len, to);
}

size_t ucv8_replaced_len_uz8n_uv8(ucv8_t view, const uc8_t *from, size_t from_len, uv8_t to) {
    return uz8n_replaced_len_uz8n_uv8(UCV8_CEXPAND(view), from, from_len, to);
}

size_t ucv8_replaced_len_uz8n_us8(ucv8_t view, const uc8_t *from, size_t from_len, const us8_t *to) {
    return uz8n_replaced_len_uz8n_us8(UCV8_CEXPAND(view), from, from_len, to);
}

size_t ucv8_replaced_len_ucv8_uc8(ucv8_t view, ucv8_t from, uc8_t to) {
    return uz8n_replaced_len_ucv8_uc8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_ucv8_uz8(ucv8_t view, ucv8_t from, const uc8_t *to) {
    return uz8n_replaced_len_ucv8_uz8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_ucv8_uz8n(ucv8_t view, ucv8_t from, size_t to_len) {
    return uz8n_replaced_len_ucv8_uz8n(UCV8_CEXPAND(view), from, to_len);
}

size_t ucv8_replaced_len_ucv8_ucv8(ucv8_t view, ucv8_t from, ucv8_t to) {
    return uz8n_replaced_len_ucv8_ucv8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_ucv8_uv8(ucv8_t view, ucv8_t from, uv8_t to) {
    return uz8n_replaced_len_ucv8_uv8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_ucv8_us8(ucv8_t view, ucv8_t from, const us8_t *to) {
    return uz8n_replaced_len_ucv8_us8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uv8_uc8(ucv8_t view, uv8_t from, uc8_t to) {
    return uz8n_replaced_len_uv8_uc8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uv8_uz8(ucv8_t view, uv8_t from, const uc8_t *to) {
    return uz8n_replaced_len_uv8_uz8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uv8_uz8n(ucv8_t view, uv8_t from, size_t to_len) {
    return uz8n_replaced_len_uv8_uz8n(UCV8_CEXPAND(view), from, to_len);
}

size_t ucv8_replaced_len_uv8_ucv8(ucv8_t view, uv8_t from, ucv8_t to) {
    return uz8n_replaced_len_uv8_ucv8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uv8_uv8(ucv8_t view, uv8_t from, uv8_t to) {
    return uz8n_replaced_len_uv8_uv8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_uv8_us8(ucv8_t view, uv8_t from, const us8_t *to) {
    return uz8n_replaced_len_uv8_us8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_us8_uc8(ucv8_t view, const us8_t *from, uc8_t to) {
    return uz8n_replaced_len_us8_uc8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_us8_uz8(ucv8_t view, const us8_t *from, const uc8_t *to) {
    return uz8n_replaced_len_us8_uz8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_us8_uz8n(ucv8_t view, const us8_t *from, size_t to_len) {
    return uz8n_replaced_len_us8_uz8n(UCV8_CEXPAND(view), from, to_len);
}

size_t ucv8_replaced_len_us8_ucv8(ucv8_t view, const us8_t *from, ucv8_t to) {
    return uz8n_replaced_len_us8_ucv8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_us8_uv8(ucv8_t view, const us8_t *from, uv8_t to) {
    return uz8n_replaced_len_us8_uv8(UCV8_CEXPAND(view), from, to);
}

size_t ucv8_replaced_len_us8_us8(ucv8_t view, const us8_t *from, const us8_t *to) {
    return uz8n_replaced_len_us8_us8(UCV8_CEXPAND(view), from, to);
}

size_t ucv32_count_uc32(ucv32_t view, uc32_t target) {
    return uz32n_count_uc32(UCV32_CEXPAND(view), target);
}

size_t ucv32_count_uz32(ucv32_t view, const uc32_t *target) {
    return uz32n_count_uz32(UCV32_CEXPAND(view), target);
}

size_t ucv32_count_uz32n(ucv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_count_uz32n(UCV32_CEXPAND(view), target, target_len);
}

size_t ucv32_count_ucv32(ucv32_t view, ucv32_t target) {
    return uz32n_count_ucv32(UCV32_CEXPAND(view), target);
}

size_t ucv32_count_uv32(ucv32_t view, uv32_t target) {
    return uz32n_count_uv32(UCV32_CEXPAND(view), target);
}

size_t ucv32_count_us32(ucv32_t view, const us32_t *target) {
    return uz32n_count_us32(UCV32_CEXPAND(view), target);
}

size_t ucv16_count_uc16(ucv16_t view, uc16_t target) {
    return uz16n_count_uc16(UCV16_CEXPAND(view), target);
}

size_t ucv16_count_uz16(ucv16_t view, const uc16_t *target) {
    return uz16n_count_uz16(UCV16_CEXPAND(view), target);
}

size_t ucv16_count_uz16n(ucv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_count_uz16n(UCV16_CEXPAND(view), target, target_len);
}

size_t ucv16_count_ucv16(ucv16_t view, ucv16_t target) {
    return uz16n_count_ucv16(UCV16_CEXPAND(view), target);
}

size_t ucv16_count_uv16(ucv16_t view, uv16_t target) {
    return uz16n_count_uv16(UCV16_CEXPAND(view), target);
}

size_t ucv16_count_us16(ucv16_t view, const us16_t *target) {
    return uz16n_count_us16(UCV16_CEXPAND(view), target);
}

size_t ucv8_count_uc8(ucv8_t view, uc8_t target) {
    return uz8n_count_uc8(UCV8_CEXPAND(view), target);
}

size_t ucv8_count_uz8(ucv8_t view, const uc8_t *target) {
    return uz8n_count_uz8(UCV8_CEXPAND(view), target);
}

size_t ucv8_count_uz8n(ucv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_count_uz8n(UCV8_CEXPAND(view), target, target_len);
}

size_t ucv8_count_ucv8(ucv8_t view, ucv8_t target) {
    return uz8n_count_ucv8(UCV8_CEXPAND(view), target);
}

size_t ucv8_count_uv8(ucv8_t view, uv8_t target) {
    return uz8n_count_uv8(UCV8_CEXPAND(view), target);
}

size_t ucv8_count_us8(ucv8_t view, const us8_t *target) {
    return uz8n_count_us8(UCV8_CEXPAND(view), target);
}

#define UCVX_BOUNDS(view, index, X) \
    assert(ucv##X##_valid(view));   \
    return index < view.len

#define UCVX_EBOUNDS(view, index, X) \
    assert(ucv##X##_valid(view));    \
    return index <= view.len
    
#define UCVX_BOUNDS_RANGE(view, begin, len, X) \
    assert(ucv##X##_valid(view));              \
    return ubounds_range(view.len, begin, len)

#define UCVX_EBOUNDS_RANGE(view, begin, len, X) \
    assert(ucv##X##_valid(view));               \
    return uebounds_range(view.len, begin, len)

bool ucv32_bounds(ucv32_t view, size_t index) {
    UCVX_BOUNDS(view, index, 32);
}

bool ucv32_ebounds(ucv32_t view, size_t index) {
    UCVX_EBOUNDS(view, index, 32);
}

bool ucv32_bounds_range(ucv32_t view, size_t begin, size_t len) {
    UCVX_BOUNDS_RANGE(view, begin, len, 32);
}

bool ucv32_ebounds_range(ucv32_t view, size_t begin, size_t len) {
    UCVX_EBOUNDS_RANGE(view, begin, len, 32);
}

bool ucv16_bounds(ucv16_t view, size_t index) {
    UCVX_BOUNDS(view, index, 16);
}

bool ucv16_ebounds(ucv16_t view, size_t index) {
    UCVX_EBOUNDS(view, index, 16);
}

bool ucv16_bounds_range(ucv16_t view, size_t begin, size_t len) {
    UCVX_BOUNDS_RANGE(view, begin, len, 16);
}

bool ucv16_ebounds_range(ucv16_t view, size_t begin, size_t len) {
    UCVX_EBOUNDS_RANGE(view, begin, len, 16);
}

bool ucv8_bounds(ucv8_t view, size_t index) {
    UCVX_BOUNDS(view, index, 8);
}

bool ucv8_ebounds(ucv8_t view, size_t index) {
    UCVX_EBOUNDS(view, index, 8);
}

bool ucv8_bounds_range(ucv8_t view, size_t begin, size_t len) {
    UCVX_BOUNDS_RANGE(view, begin, len, 8);
}

bool ucv8_ebounds_range(ucv8_t view, size_t begin, size_t len) {
    UCVX_EBOUNDS_RANGE(view, begin, len, 8);
}

bool ucv32_starts_with_uc32(ucv32_t view, uc32_t target) {
    return uz32n_starts_with_uc32(UCV32_CEXPAND(view), target);
}

bool ucv32_starts_with_uz32(ucv32_t view, const uc32_t *target) {
    return uz32n_starts_with_uz32(UCV32_CEXPAND(view), target);
}

bool ucv32_starts_with_uz32n(ucv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_starts_with_uz32n(UCV32_CEXPAND(view), target, target_len);
}

bool ucv32_starts_with_ucv32(ucv32_t view, ucv32_t target) {
    return uz32n_starts_with_ucv32(UCV32_CEXPAND(view), target);
}

bool ucv32_starts_with_uv32(ucv32_t view, uv32_t target) {
    return uz32n_starts_with_uv32(UCV32_CEXPAND(view), target);
}

bool ucv32_starts_with_us32(ucv32_t view, const us32_t *target) {
    return uz32n_starts_with_us32(UCV32_CEXPAND(view), target);
}

bool ucv16_starts_with_uc16(ucv16_t view, uc16_t target) {
    return uz16n_starts_with_uc16(UCV16_CEXPAND(view), target);
}

bool ucv16_starts_with_uz16(ucv16_t view, const uc16_t *target) {
    return uz16n_starts_with_uz16(UCV16_CEXPAND(view), target);
}

bool ucv16_starts_with_uz16n(ucv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_starts_with_uz16n(UCV16_CEXPAND(view), target, target_len);
}

bool ucv16_starts_with_ucv16(ucv16_t view, ucv16_t target) {
    return uz16n_starts_with_ucv16(UCV16_CEXPAND(view), target);
}

bool ucv16_starts_with_uv16(ucv16_t view, uv16_t target) {
    return uz16n_starts_with_uv16(UCV16_CEXPAND(view), target);
}

bool ucv16_starts_with_us16(ucv16_t view, const us16_t *target) {
    return uz16n_starts_with_us16(UCV16_CEXPAND(view), target);
}

bool ucv8_starts_with_uc8(ucv8_t view, uc8_t target) {
    return uz8n_starts_with_uc8(UCV8_CEXPAND(view), target);
}

bool ucv8_starts_with_uz8(ucv8_t view, const uc8_t *target) {
    return uz8n_starts_with_uz8(UCV8_CEXPAND(view), target);
}

bool ucv8_starts_with_uz8n(ucv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_starts_with_uz8n(UCV8_CEXPAND(view), target, target_len);
}

bool ucv8_starts_with_ucv8(ucv8_t view, ucv8_t target) {
    return uz8n_starts_with_ucv8(UCV8_CEXPAND(view), target);
}

bool ucv8_starts_with_uv8(ucv8_t view, uv8_t target) {
    return uz8n_starts_with_uv8(UCV8_CEXPAND(view), target);
}

bool ucv8_starts_with_us8(ucv8_t view, const us8_t *target) {
    return uz8n_starts_with_us8(UCV8_CEXPAND(view), target);
}

bool ucv32_ends_with_uc32(ucv32_t view, uc32_t target) {
    return uz32n_ends_with_uc32(UCV32_CEXPAND(view), target);
}

bool ucv32_ends_with_uz32(ucv32_t view, const uc32_t *target) {
    return uz32n_ends_with_uz32(UCV32_CEXPAND(view), target);
}

bool ucv32_ends_with_uz32n(ucv32_t view, const uc32_t *target, size_t target_len) {
    return uz32n_ends_with_uz32n(UCV32_CEXPAND(view), target, target_len);
}

bool ucv32_ends_with_ucv32(ucv32_t view, ucv32_t target) {
    return uz32n_ends_with_ucv32(UCV32_CEXPAND(view), target);
}

bool ucv32_ends_with_uv32(ucv32_t view, uv32_t target) {
    return uz32n_ends_with_uv32(UCV32_CEXPAND(view), target);
}

bool ucv32_ends_with_us32(ucv32_t view, const us32_t *target) {
    return uz32n_ends_with_us32(UCV32_CEXPAND(view), target);
}

bool ucv16_ends_with_uc16(ucv16_t view, uc16_t target) {
    return uz16n_ends_with_uc16(UCV16_CEXPAND(view), target);
}

bool ucv16_ends_with_uz16(ucv16_t view, const uc16_t *target) {
    return uz16n_ends_with_uz16(UCV16_CEXPAND(view), target);
}

bool ucv16_ends_with_uz16n(ucv16_t view, const uc16_t *target, size_t target_len) {
    return uz16n_ends_with_uz16n(UCV16_CEXPAND(view), target, target_len);
}

bool ucv16_ends_with_ucv16(ucv16_t view, ucv16_t target) {
    return uz16n_ends_with_ucv16(UCV16_CEXPAND(view), target);
}

bool ucv16_ends_with_uv16(ucv16_t view, uv16_t target) {
    return uz16n_ends_with_uv16(UCV16_CEXPAND(view), target);
}

bool ucv16_ends_with_us16(ucv16_t view, const us16_t *target) {
    return uz16n_ends_with_us16(UCV16_CEXPAND(view), target);
}

bool ucv8_ends_with_uc8(ucv8_t view, uc8_t target) {
    return uz8n_ends_with_uc8(UCV8_CEXPAND(view), target);
}

bool ucv8_ends_with_uz8(ucv8_t view, const uc8_t *target) {
    return uz8n_ends_with_uz8(UCV8_CEXPAND(view), target);
}

bool ucv8_ends_with_uz8n(ucv8_t view, const uc8_t *target, size_t target_len) {
    return uz8n_ends_with_uz8n(UCV8_CEXPAND(view), target, target_len);
}

bool ucv8_ends_with_ucv8(ucv8_t view, ucv8_t target) {
    return uz8n_ends_with_ucv8(UCV8_CEXPAND(view), target);
}

bool ucv8_ends_with_uv8(ucv8_t view, uv8_t target) {
    return uz8n_ends_with_uv8(UCV8_CEXPAND(view), target);
}

bool ucv8_ends_with_us8(ucv8_t view, const us8_t *target) {
    return uz8n_ends_with_us8(UCV8_CEXPAND(view), target);
}

#define UCVX_CBEIGN(view, X)      \
    assert(ucv##X##_valid(view)); \
    return view.chars;

const uc32_t *ucv32_cbegin(ucv32_t view) {
    UCVX_CBEIGN(view, 32);
}

const uc16_t *ucv16_cbegin(ucv16_t view) {
    UCVX_CBEIGN(view, 16);
}

const uc8_t *ucv8_cbegin(ucv8_t view) {
    UCVX_CBEIGN(view, 8);
}

#define UCVX_COFFSET(view, offset, X)       \
    assert(ucv##X##_ebounds(view, offset)); \
    return view.chars + offset

const uc32_t *ucv32_coffset(ucv32_t view, size_t offset) {
    UCVX_COFFSET(view, offset, 32);
}

const uc16_t *ucv16_coffset(ucv16_t view, size_t offset) {
    UCVX_COFFSET(view, offset, 16);
}

const uc8_t *ucv8_coffset(ucv8_t view, size_t offset) {
    UCVX_COFFSET(view, offset, 8);
}

#define UCVX_CEND(view, X)        \
    assert(ucv##X##_valid(view)); \
    return view.chars + view.len

const uc32_t *ucv32_cend(ucv32_t view) {
    UCVX_CEND(view, 32);
}

const uc16_t *ucv16_cend(ucv16_t view) {
    UCVX_CEND(view, 16);
}

const uc8_t *ucv8_cend(ucv8_t view) {
    UCVX_CEND(view, 8);
}

#define UCVX_EMPTY(view, X)       \
    assert(ucv##X##_valid(view)); \
    return !view.len

bool ucv32_empty(ucv32_t view) {
    UCVX_EMPTY(view, 32);
}

bool ucv16_empty(ucv16_t view) {
    UCVX_EMPTY(view, 16);
}

bool ucv8_empty(ucv8_t view) {
    UCVX_EMPTY(view, 8);
}

#define UCVX_AT(view, at, X)           \
    assert(ucv##X##_bounds(view, at)); \
    return view.chars[at]

uc32_t ucv32_at(ucv32_t view, size_t at) {
    UCVX_AT(view, at, 32);
}

uc16_t ucv16_at(ucv16_t view, size_t at) {
    UCVX_AT(view, at, 16);
}

uc8_t ucv8_at(ucv8_t view, size_t at) {
    UCVX_AT(view, at, 8);
}

#define UCVX_CCHARS(view, X)                       \
    assert(ucv##X##_valid(view));                  \
    static const uc##X##_t *chars = uz##X("NULL"); \
    return view.chars ? view.chars : chars

const uc32_t *ucv32_cchars(ucv32_t view) {
    UCVX_CCHARS(view, 32);
}

const uc16_t *ucv16_cchars(ucv16_t view) {
    UCVX_CCHARS(view, 16);
}

const uc8_t *ucv8_cchars(ucv8_t view) {
    UCVX_CCHARS(view, 8);
}
    
#define UCVX_SET_CHARS(view, chars, X) \
    assert(ucv##X##_valid_p(view));    \
                                       \
    view->chars = chars;               \
                                       \
    if (!chars)                        \
        view->len = 0;

void ucv32_set_chars(ucv32_t *view, const uc32_t *chars) {
    UCVX_SET_CHARS(view, chars, 32);
}

void ucv16_set_chars(ucv16_t *view, const uc16_t *chars) {
    UCVX_SET_CHARS(view, chars, 16);
}

void ucv8_set_chars(ucv8_t *view, const uc8_t *chars) {
    UCVX_SET_CHARS(view, chars, 8);
}

bool ucv32_valid_p(const ucv32_t *view) {
    return view && ucv32_valid(*view);
}

#define UCVX_VALID(view) \
    return view.chars    \
        || !view.len

bool ucv32_valid(ucv32_t view) {
    UCVX_VALID(view);
}

bool ucv16_valid_p(const ucv16_t *view) {
    return view && ucv16_valid(*view);
}

bool ucv16_valid(ucv16_t view) {
    UCVX_VALID(view);
}

bool ucv8_valid_p(const ucv8_t *view) {
    return view && ucv8_valid(*view);
}

bool ucv8_valid(ucv8_t view) {
    UCVX_VALID(view);
}