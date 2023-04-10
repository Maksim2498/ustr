#ifndef USTR_VIEW_H
#define USTR_VIEW_H

#include <stdbool.h>
#include <stddef.h>

#include "type/fmt/case.h"
#include "type/attr.h"
#include "type/char.h"
#include "type/cview.h"
#include "type/encoding.h"
#include "type/str.h"
#include "type/view.h"
#include "util/export.h"

// Expand

#define UV32_CEXPAND(view) uv32_cchars(view), (view).len
#define  UV32_EXPAND(view)  uv32_chars(view), (view).len

#define UV16_CEXPAND(view) uv16_cchars(view), (view).len
#define  UV16_EXPAND(view)  uv16_chars(view), (view).len

#define  UV8_CEXPAND(view)  uv8_cchars(view), (view).len
#define   UV8_EXPAND(view)   uv8_chars(view), (view).len

// Creation

// - Conversion

#define uv32_from(from)           \
    _Generic((from),              \
        uc32_t *: uv32_from_uz32, \
        uv32_t:   uv32_from_uv32, \
        us32_t *: uv32_from_us32  \
    )((from))

#define uv32_from_range(from, begin, len) \
    _Generic((from),                      \
        uc32_t *: uv32_from_uz32_range,   \
        uv32_t:   uv32_from_uv32_range,   \
        us32_t *: uv32_from_us32_range    \
    )((from), (begin), (len))

UEXPORT uv32_t uv32_from_uz32(uc32_t *from);
UEXPORT uv32_t uv32_from_uz32_range(uc32_t *from, size_t begin, size_t len);
UEXPORT uv32_t uv32_from_uz32n(uc32_t *from, size_t from_len);
UEXPORT uv32_t uv32_from_uz32n_range(uc32_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT uv32_t uv32_from_uv32(uv32_t from);
UEXPORT uv32_t uv32_from_uv32_range(uv32_t from, size_t begin, size_t len);
UEXPORT uv32_t uv32_from_us32(us32_t *from);
UEXPORT uv32_t uv32_from_us32_range(us32_t *from, size_t begin, size_t len);

#define uv16_from(from)           \
    _Generic((from),              \
        uc16_t *: uv16_from_uz16, \
        uv16_t:   uv16_from_uv16, \
        us16_t *: uv16_from_us16  \
    )((from))

#define uv16_from_range(from, begin, len) \
    _Generic((from),                      \
        uc16_t *: uv16_from_uz16_range,   \
        uv16_t:   uv16_from_uv16_range,   \
        us16_t *: uv16_from_us16_range    \
    )((from), (begin), (len))

UEXPORT uv16_t uv16_from_uz16(uc16_t *from);
UEXPORT uv16_t uv16_from_uz16_range(uc16_t *from, size_t begin, size_t len);
UEXPORT uv16_t uv16_from_uz16n(uc16_t *from, size_t from_len);
UEXPORT uv16_t uv16_from_uz16n_range(uc16_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT uv16_t uv16_from_uv16(uv16_t from);
UEXPORT uv16_t uv16_from_uv16_range(uv16_t from, size_t begin, size_t len);
UEXPORT uv16_t uv16_from_us16(us16_t *from);
UEXPORT uv16_t uv16_from_us16_range(us16_t *from, size_t begin, size_t len);

#define uv8_from(from)         \
    _Generic((from),           \
        uc8_t *: uv8_from_uz8, \
        uv8_t:   uv8_from_uv8, \
        us8_t *: uv8_from_us8  \
    )((from))

#define uv8_from_range(from, begin, len) \
    _Generic((from),                     \
        uc8_t *: uv8_from_uz8_range,     \
        uv8_t:   uv8_from_uv8_range,     \
        us8_t *: uv8_from_us8_range      \
    )((from), (begin), (len))

UEXPORT uv8_t uv8_from_uz8(uc8_t *from);
UEXPORT uv8_t uv8_from_uz8_range(uc8_t *from, size_t begin, size_t len);
UEXPORT uv8_t uv8_from_uz8n(uc8_t *from, size_t from_len);
UEXPORT uv8_t uv8_from_uz8n_range(uc8_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT uv8_t uv8_from_uv8(uv8_t from);
UEXPORT uv8_t uv8_from_uv8_range(uv8_t from, size_t begin, size_t len);
UEXPORT uv8_t uv8_from_us8(us8_t *from);
UEXPORT uv8_t uv8_from_us8_range(us8_t *from, size_t begin, size_t len);

// To bytes

UEXPORT size_t uv32_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, uv32_t from);
UEXPORT size_t uv16_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, uv16_t from);
UEXPORT size_t uv8_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, uv8_t from);

// Length

UEXPORT size_t uv32_len(uv32_t view);
UEXPORT size_t uv32_len_n(uv32_t view, unsigned n);
UEXPORT size_t uv32_len_32(uv32_t view);
UEXPORT size_t uv32_len_16(uv32_t view);
UEXPORT size_t uv32_len_8(uv32_t view);

UEXPORT size_t uv16_len(uv16_t view);
UEXPORT size_t uv16_len_n(uv16_t view, unsigned n);
UEXPORT size_t uv16_len_32(uv16_t view);
UEXPORT size_t uv16_len_16(uv16_t view);
UEXPORT size_t uv16_len_8(uv16_t view);

UEXPORT size_t uv8_len(uv8_t view);
UEXPORT size_t uv8_len_n(uv8_t view, unsigned n);
UEXPORT size_t uv8_len_32(uv8_t view);
UEXPORT size_t uv8_len_16(uv8_t view);
UEXPORT size_t uv8_len_8(uv8_t view);


UEXPORT void uv32_set_len(uv32_t *view, size_t len);
UEXPORT void uv16_set_len(uv16_t *view, size_t len);
UEXPORT void uv8_set_len(uv8_t *view, size_t len);


UEXPORT size_t uv32_add_len(uv32_t *view, ptrdiff_t delta);
UEXPORT size_t uv16_add_len(uv16_t *view, ptrdiff_t delta);
UEXPORT size_t uv8_add_len(uv8_t *view, ptrdiff_t delta);

// Compare

#define uv32_cmp(lhs, rhs)              \
    _Generic((rhs),                     \
        default:        uv32_cmp_uc32,  \
        const uc32_t *: uv32_cmp_uz32,  \
        uc32_t *:       uv32_cmp_uz32,  \
        ucv32_t:        uv32_cmp_ucv32, \
        uv32_t:         uv32_cmp_uv32,  \
        const us32_t *: uv32_cmp_us32,  \
        us32_t *:       uv32_cmp_us32   \
    )((lhs), (rhs))

UEXPORT int uv32_cmp_uc32(uv32_t lhs, uc32_t rhs);
UEXPORT int uv32_cmp_uz32(uv32_t lhs, const uc32_t *rhs);
UEXPORT int uv32_cmp_uz32n(uv32_t lhs, const uc32_t *rhs, size_t rhs_len);
UEXPORT int uv32_cmp_ucv32(uv32_t lhs, ucv32_t rhs);
UEXPORT int uv32_cmp_uv32(uv32_t lhs, uv32_t rhs);
UEXPORT int uv32_cmp_us32(uv32_t lhs, const us32_t *rhs);

#define uv16_cmp(lhs, rhs)              \
    _Generic((rhs),                     \
        default:        uv16_cmp_uc16,  \
        const uc16_t *: uv16_cmp_uz16,  \
        uc16_t *:       uv16_cmp_uz16,  \
        ucv16_t:        uv16_cmp_ucv16, \
        uv16_t:         uv16_cmp_uv16,  \
        const us16_t *: uv16_cmp_us16,  \
        us16_t *:       uv16_cmp_us16   \
    )((lhs), (rhs))

UEXPORT int uv16_cmp_uc16(uv16_t lhs, uc16_t rhs);
UEXPORT int uv16_cmp_uz16(uv16_t lhs, const uc16_t *rhs);
UEXPORT int uv16_cmp_uz16n(uv16_t lhs, const uc16_t *rhs, size_t rhs_len);
UEXPORT int uv16_cmp_ucv16(uv16_t lhs, ucv16_t rhs);
UEXPORT int uv16_cmp_uv16(uv16_t lhs, uv16_t rhs);
UEXPORT int uv16_cmp_us16(uv16_t lhs, const us16_t *rhs);

#define uv8_cmp(lhs, rhs)            \
    _Generic((rhs),                  \
        default:       uv8_cmp_uc8,  \
        const uc8_t *: uv8_cmp_uz8,  \
        uc8_t *:       uv8_cmp_uz8,  \
        ucv8_t:        uv8_cmp_ucv8, \
        uv8_t:         uv8_cmp_uv8,  \
        const us8_t *: uv8_cmp_us8,  \
        us8_t *:       uv8_cmp_us8   \
    )((lhs), (rhs))

UEXPORT int uv8_cmp_uc8(uv8_t lhs, uc8_t rhs);
UEXPORT int uv8_cmp_uz8(uv8_t lhs, const uc8_t *rhs);
UEXPORT int uv8_cmp_uz8n(uv8_t lhs, const uc8_t *rhs, size_t rhs_len);
UEXPORT int uv8_cmp_ucv8(uv8_t lhs, ucv8_t rhs);
UEXPORT int uv8_cmp_uv8(uv8_t lhs, uv8_t rhs);
UEXPORT int uv8_cmp_us8(uv8_t lhs, const us8_t *rhs);

// Fill

#define uv32_fill(view, with)            \
    _Generic((with),                     \
        default:        uv32_fill_uc32,  \
        const uc32_t *: uv32_fill_uz32,  \
        uc32_t *:       uv32_fill_uz32,  \
        ucv32_t:        uv32_fill_ucv32, \
        uv32_t:         uv32_fill_uv32,  \
        const us32_t *: uv32_fill_us32,  \
        us32_t *:       uv32_fill_us32   \
    )((view), (with))

UEXPORT void uv32_fill_uc32(uv32_t view, uc32_t with);
UEXPORT void uv32_fill_uz32(uv32_t view, const uc32_t *with);
UEXPORT void uv32_fill_uz32n(uv32_t view, const uc32_t *with, size_t with_len);
UEXPORT void uv32_fill_ucv32(uv32_t view, ucv32_t with);
UEXPORT void uv32_fill_uv32(uv32_t view, uv32_t with);
UEXPORT void uv32_fill_us32(uv32_t view, const us32_t *with);

#define uv16_fill(view, with)            \
    _Generic((with),                     \
        default:        uv16_fill_uc16,  \
        const uc16_t *: uv16_fill_uz16,  \
        uc16_t *:       uv16_fill_uz16,  \
        ucv16_t:        uv16_fill_ucv16, \
        uv16_t:         uv16_fill_uv16,  \
        const us16_t *: uv16_fill_us16,  \
        us16_t *:       uv16_fill_us16   \
    )((view), (with))

UEXPORT void uv16_fill_uc16(uv16_t view, uc16_t with);
UEXPORT void uv16_fill_uz16(uv16_t view, const uc16_t *with);
UEXPORT void uv16_fill_uz16n(uv16_t view, const uc16_t *with, size_t with_len);
UEXPORT void uv16_fill_ucv16(uv16_t view, ucv16_t with);
UEXPORT void uv16_fill_uv16(uv16_t view, uv16_t with);
UEXPORT void uv16_fill_us16(uv16_t view, const us16_t *with);

#define uv8_fill(view, with)          \
    _Generic((with),                  \
        default:       uv8_fill_uc8,  \
        const uc8_t *: uv8_fill_uz8,  \
        uc8_t *:       uv8_fill_uz8,  \
        ucv8_t:        uv8_fill_ucv8, \
        uv8_t:         uv8_fill_uv8,  \
        const us8_t *: uv8_fill_us8,  \
        us8_t *:       uv8_fill_us8   \
    )((view), (with))

UEXPORT void uv8_fill_uc8(uv8_t view, uc8_t with);
UEXPORT void uv8_fill_uz8(uv8_t view, const uc8_t *with);
UEXPORT void uv8_fill_uz8n(uv8_t view, const uc8_t *with, size_t with_len);
UEXPORT void uv8_fill_ucv8(uv8_t view, ucv8_t with);
UEXPORT void uv8_fill_uv8(uv8_t view, uv8_t with);
UEXPORT void uv8_fill_us8(uv8_t view, const us8_t *with);

// White space

UEXPORT size_t uv32_wspace_len(uv32_t view);
UEXPORT size_t uv16_wspace_len(uv16_t view);
UEXPORT size_t uv8_wspace_len(uv8_t view);

// Trim

UEXPORT size_t uv32_trim(uv32_t *view);
UEXPORT size_t uv32_ltrim(uv32_t *view);
UEXPORT size_t uv32_rtrim(uv32_t *view);

UEXPORT size_t uv16_trim(uv16_t *view);
UEXPORT size_t uv16_ltrim(uv16_t *view);
UEXPORT size_t uv16_rtrim(uv16_t *view);

UEXPORT size_t uv8_trim(uv8_t *view);
UEXPORT size_t uv8_ltrim(uv8_t *view);
UEXPORT size_t uv8_rtrim(uv8_t *view);

// Case change

UEXPORT void uv32_to_case(uv32_t view, ucase_t ca);
UEXPORT void uv32_to_lower(uv32_t view);
UEXPORT void uv32_to_upper(uv32_t view);

UEXPORT void uv16_to_case(uv16_t view, ucase_t ca);
UEXPORT void uv16_to_lower(uv16_t view);
UEXPORT void uv16_to_upper(uv16_t view);

// Case change length

UEXPORT size_t uv8_case_len(uv8_t view, ucase_t ca);
UEXPORT size_t uv8_lower_len(uv8_t view);
UEXPORT size_t uv8_upper_len(uv8_t view);

// Split

#define uv32_new_csplit(view, sep, array)             \
    uv32_new_csplit_e((view), (sep), (array), (NULL))

#define uv32_new_csplit_e(view, sep, array, error) \
    _Generic((sep),                                \
        default:        uv32_new_csplit_uc32_e,    \
        const uc32_t *: uv32_new_csplit_uz32_e,    \
        uc32_t *:       uv32_new_csplit_uz32_e,    \
        ucv32_t:        uv32_new_csplit_ucv32_e,   \
        uv32_t:         uv32_new_csplit_uv32_e,    \
        const us32_t *: uv32_new_csplit_us32_e,    \
        us32_t *:       uv32_new_csplit_us32_e     \
    )((view), (sep), (array), (error))

#define uv32_csplit(view, sep, array, array_len) \
    _Generic((sep),                              \
        default:        uv32_csplit_uc32,        \
        const uc32_t *: uv32_csplit_uz32,        \
        uc32_t *:       uv32_csplit_uz32,        \
        ucv32_t:        uv32_csplit_ucv32,       \
        uv32_t:         uv32_csplit_uv32,        \
        const us32_t *: uv32_csplit_us32,        \
        us32_t *:       uv32_csplit_us32         \
    )((view), (sep), (array), (array_len))

UEXPORT size_t uv32_new_csplit_uc32(uv32_t view, uc32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uv32_new_csplit_uc32_e(uv32_t view, uc32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uv32_csplit_uc32(uv32_t view, uc32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uv32_new_csplit_uz32(uv32_t view, const uc32_t *sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uv32_new_csplit_uz32_e(uv32_t view, const uc32_t *sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uv32_csplit_uz32(uv32_t view, const uc32_t *sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uv32_new_csplit_uz32n(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array);
UEXPORT size_t uv32_new_csplit_uz32n_e(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uv32_csplit_uz32n(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uv32_new_csplit_ucv32(uv32_t view, ucv32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uv32_new_csplit_ucv32_e(uv32_t view, ucv32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uv32_csplit_ucv32(uv32_t view, ucv32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uv32_new_csplit_uv32(uv32_t view, uv32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uv32_new_csplit_uv32_e(uv32_t view, uv32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uv32_csplit_uv32(uv32_t view, uv32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t uv32_new_csplit_us32(uv32_t view, const us32_t *sep, UNULLABLE ucv32_t **array);
UEXPORT size_t uv32_new_csplit_us32_e(uv32_t view, const us32_t *sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t uv32_csplit_us32(uv32_t view, const us32_t *sep, UNULLABLE ucv32_t *array, size_t array_len);

#define uv32_new_split(cstr, sep, array)           \
    uv32_new_split_e((cstr), (sep), (array), NULL)

#define uv32_new_split_e(cstr, sep, array, error)                   \
    uv32_new_csplit_e((cstr), (sep), (ucv32_t **) (array), (error))

#define uv32_split(cstr, sep, array, array_len)                  \
    uv32_csplit((cstr), (sep), (ucv32_t *) (array), (array_len))

UEXPORT size_t uv32_new_split_uc32(uv32_t view, uc32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t uv32_new_split_uc32_e(uv32_t view, uc32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uv32_split_uc32(uv32_t view, uc32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uv32_new_split_uz32(uv32_t view, const uc32_t *sep, UNULLABLE uv32_t **array);
UEXPORT size_t uv32_new_split_uz32_e(uv32_t view, const uc32_t *sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uv32_split_uz32(uv32_t view, const uc32_t *sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uv32_new_split_uz32n(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array);
UEXPORT size_t uv32_new_split_uz32n_e(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uv32_split_uz32n(uv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uv32_new_split_ucv32(uv32_t view, ucv32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t uv32_new_split_ucv32_e(uv32_t view, ucv32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uv32_split_ucv32(uv32_t view, ucv32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uv32_new_split_uv32(uv32_t view, uv32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t uv32_new_split_uv32_e(uv32_t view, uv32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uv32_split_uv32(uv32_t view, uv32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t uv32_new_split_us32(uv32_t view, const us32_t *sep, UNULLABLE uv32_t **array);
UEXPORT size_t uv32_new_split_us32_e(uv32_t view, const us32_t *sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t uv32_split_us32(uv32_t view, const us32_t *sep, UNULLABLE uv32_t *array, size_t array_len);


#define uv16_new_csplit(view, sep, array)             \
    uv16_new_csplit_e((view), (sep), (array), (NULL))

#define uv16_new_csplit_e(view, sep, array, error) \
    _Generic((sep),                                \
        default:        uv16_new_csplit_uc16_e,    \
        const uc16_t *: uv16_new_csplit_uz16_e,    \
        uc16_t *:       uv16_new_csplit_uz16_e,    \
        ucv16_t:        uv16_new_csplit_ucv16_e,   \
        uv16_t:         uv16_new_csplit_uv16_e,    \
        const us16_t *: uv16_new_csplit_us16_e,    \
        us16_t *:       uv16_new_csplit_us16_e     \
    )((view), (sep), (array), (error))

#define uv16_csplit(view, sep, array, array_len) \
    _Generic((sep),                              \
        default:        uv16_csplit_uc16,        \
        const uc16_t *: uv16_csplit_uz16,        \
        uc16_t *:       uv16_csplit_uz16,        \
        ucv16_t:        uv16_csplit_ucv16,       \
        uv16_t:         uv16_csplit_uv16,        \
        const us16_t *: uv16_csplit_us16,        \
        us16_t *:       uv16_csplit_us16         \
    )((view), (sep), (array), (array_len))

UEXPORT size_t uv16_new_csplit_uc16(uv16_t view, uc16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uv16_new_csplit_uc16_e(uv16_t view, uc16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uv16_csplit_uc16(uv16_t view, uc16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uv16_new_csplit_uz16(uv16_t view, const uc16_t *sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uv16_new_csplit_uz16_e(uv16_t view, const uc16_t *sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uv16_csplit_uz16(uv16_t view, const uc16_t *sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uv16_new_csplit_uz16n(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array);
UEXPORT size_t uv16_new_csplit_uz16n_e(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uv16_csplit_uz16n(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uv16_new_csplit_ucv16(uv16_t view, ucv16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uv16_new_csplit_ucv16_e(uv16_t view, ucv16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uv16_csplit_ucv16(uv16_t view, ucv16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uv16_new_csplit_uv16(uv16_t view, uv16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uv16_new_csplit_uv16_e(uv16_t view, uv16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uv16_csplit_uv16(uv16_t view, uv16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t uv16_new_csplit_us16(uv16_t view, const us16_t *sep, UNULLABLE ucv16_t **array);
UEXPORT size_t uv16_new_csplit_us16_e(uv16_t view, const us16_t *sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t uv16_csplit_us16(uv16_t view, const us16_t *sep, UNULLABLE ucv16_t *array, size_t array_len);

#define uv16_new_split(cstr, sep, array)           \
    uv16_new_split_e((cstr), (sep), (array), NULL)

#define uv16_new_split_e(cstr, sep, array, error)                   \
    uv16_new_csplit_e((cstr), (sep), (ucv16_t **) (array), (error))

#define uv16_split(cstr, sep, array, array_len)                  \
    uv16_csplit((cstr), (sep), (ucv16_t *) (array), (array_len))

UEXPORT size_t uv16_new_split_uc16(uv16_t view, uc16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t uv16_new_split_uc16_e(uv16_t view, uc16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uv16_split_uc16(uv16_t view, uc16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uv16_new_split_uz16(uv16_t view, const uc16_t *sep, UNULLABLE uv16_t **array);
UEXPORT size_t uv16_new_split_uz16_e(uv16_t view, const uc16_t *sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uv16_split_uz16(uv16_t view, const uc16_t *sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uv16_new_split_uz16n(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array);
UEXPORT size_t uv16_new_split_uz16n_e(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uv16_split_uz16n(uv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uv16_new_split_ucv16(uv16_t view, ucv16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t uv16_new_split_ucv16_e(uv16_t view, ucv16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uv16_split_ucv16(uv16_t view, ucv16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uv16_new_split_uv16(uv16_t view, uv16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t uv16_new_split_uv16_e(uv16_t view, uv16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uv16_split_uv16(uv16_t view, uv16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t uv16_new_split_us16(uv16_t view, const us16_t *sep, UNULLABLE uv16_t **array);
UEXPORT size_t uv16_new_split_us16_e(uv16_t view, const us16_t *sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t uv16_split_us16(uv16_t view, const us16_t *sep, UNULLABLE uv16_t *array, size_t array_len);


#define uv8_new_csplit(view, sep, array)             \
    uv8_new_csplit_e((view), (sep), (array), (NULL))

#define uv8_new_csplit_e(view, sep, array, error) \
    _Generic((sep),                               \
        default:       uv8_new_csplit_uc8_e,      \
        const uc8_t *: uv8_new_csplit_uz8_e,      \
        uc8_t *:       uv8_new_csplit_uz8_e,      \
        ucv8_t:        uv8_new_csplit_ucv8_e,     \
        uv8_t:         uv8_new_csplit_uv8_e,      \
        const us8_t *: uv8_new_csplit_us8_e,      \
        us8_t *:       uv8_new_csplit_us8_e       \
    )((view), (sep), (array), (error))

#define uv8_csplit(view, sep, array, array_len) \
    _Generic((sep),                             \
        default:       uv8_csplit_uc8,          \
        const uc8_t *: uv8_csplit_uz8,          \
        uc8_t *:       uv8_csplit_uz8,          \
        ucv8_t:        uv8_csplit_ucv8,         \
        uv8_t:         uv8_csplit_uv8,          \
        const us8_t *: uv8_csplit_us8,          \
        us8_t *:       uv8_csplit_us8           \
    )((view), (sep), (array), (array_len))

UEXPORT size_t uv8_new_csplit_uc8(uv8_t view, uc8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uv8_new_csplit_uc8_e(uv8_t view, uc8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uv8_csplit_uc8(uv8_t view, uc8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uv8_new_csplit_uz8(uv8_t view, const uc8_t *sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uv8_new_csplit_uz8_e(uv8_t view, const uc8_t *sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uv8_csplit_uz8(uv8_t view, const uc8_t *sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uv8_new_csplit_uz8n(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array);
UEXPORT size_t uv8_new_csplit_uz8n_e(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uv8_csplit_uz8n(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uv8_new_csplit_ucv8(uv8_t view, ucv8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uv8_new_csplit_ucv8_e(uv8_t view, ucv8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uv8_csplit_ucv8(uv8_t view, ucv8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uv8_new_csplit_uv8(uv8_t view, uv8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uv8_new_csplit_uv8_e(uv8_t view, uv8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uv8_csplit_uv8(uv8_t view, uv8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t uv8_new_csplit_us8(uv8_t view, const us8_t *sep, UNULLABLE ucv8_t **array);
UEXPORT size_t uv8_new_csplit_us8_e(uv8_t view, const us8_t *sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t uv8_csplit_us8(uv8_t view, const us8_t *sep, UNULLABLE ucv8_t *array, size_t array_len);

#define uv8_new_split(cstr, sep, array)           \
    uv8_new_split_e((cstr), (sep), (array), NULL)

#define uv8_new_split_e(cstr, sep, array, error)                  \
    uv8_new_csplit_e((cstr), (sep), (ucv8_t **) (array), (error))

#define uv8_split(cstr, sep, array, array_len)                 \
    uv8_csplit((cstr), (sep), (ucv8_t *) (array), (array_len))

UEXPORT size_t uv8_new_split_uc8(uv8_t view, uc8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t uv8_new_split_uc8_e(uv8_t view, uc8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uv8_split_uc8(uv8_t view, uc8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uv8_new_split_uz8(uv8_t view, const uc8_t *sep, UNULLABLE uv8_t **array);
UEXPORT size_t uv8_new_split_uz8_e(uv8_t view, const uc8_t *sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uv8_split_uz8(uv8_t view, const uc8_t *sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uv8_new_split_uz8n(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array);
UEXPORT size_t uv8_new_split_uz8n_e(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uv8_split_uz8n(uv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uv8_new_split_ucv8(uv8_t view, ucv8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t uv8_new_split_ucv8_e(uv8_t view, ucv8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uv8_split_ucv8(uv8_t view, ucv8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uv8_new_split_uv8(uv8_t view, uv8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t uv8_new_split_uv8_e(uv8_t view, uv8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uv8_split_uv8(uv8_t view, uv8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t uv8_new_split_us8(uv8_t view, const us8_t *sep, UNULLABLE uv8_t **array);
UEXPORT size_t uv8_new_split_us8_e(uv8_t view, const us8_t *sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t uv8_split_us8(uv8_t view, const us8_t *sep, UNULLABLE uv8_t *array, size_t array_len);

// Contains

#define uv32_contains(view, target)          \
    _Generic((target),                       \
        default:        uv32_contains_uc32,  \
        const uc32_t *: uv32_contains_uz32,  \
        uc32_t *:       uv32_contains_uz32,  \
        ucv32_t:        uv32_contains_ucv32, \
        uv32_t:         uv32_contains_uv32,  \
        const us32_t *: uv32_contains_us32,  \
        us32_t *:       uv32_contains_us32   \
    )((view), (target))

UEXPORT bool uv32_contains_uc32(uv32_t view, uc32_t target);
UEXPORT bool uv32_contains_uz32(uv32_t view, const uc32_t *target);
UEXPORT bool uv32_contains_uz32n(uv32_t view, const uc32_t *target, size_t target_len);
UEXPORT bool uv32_contains_ucv32(uv32_t view, ucv32_t target);
UEXPORT bool uv32_contains_uv32(uv32_t view, uv32_t target);
UEXPORT bool uv32_contains_us32(uv32_t view, const us32_t *target);

#define uv16_contains(view, target)          \
    _Generic((target),                       \
        default:        uv16_contains_uc16,  \
        const uc16_t *: uv16_contains_uz16,  \
        uc16_t *:       uv16_contains_uz16,  \
        ucv16_t:        uv16_contains_ucv16, \
        uv16_t:         uv16_contains_uv16,  \
        const us16_t *: uv16_contains_us16,  \
        us16_t *:       uv16_contains_us16   \
    )((view), (target))

UEXPORT bool uv16_contains_uc16(uv16_t view, uc16_t target);
UEXPORT bool uv16_contains_uz16(uv16_t view, const uc16_t *target);
UEXPORT bool uv16_contains_uz16n(uv16_t view, const uc16_t *target, size_t target_len);
UEXPORT bool uv16_contains_ucv16(uv16_t view, ucv16_t target);
UEXPORT bool uv16_contains_uv16(uv16_t view, uv16_t target);
UEXPORT bool uv16_contains_us16(uv16_t view, const us16_t *target);

#define uv8_contains(view, target)        \
    _Generic((target),                    \
        default:       uv8_contains_uc8,  \
        const uc8_t *: uv8_contains_uz8,  \
        uc8_t *:       uv8_contains_uz8,  \
        ucv8_t:        uv8_contains_ucv8, \
        uv8_t:         uv8_contains_uv8,  \
        const us8_t *: uv8_contains_us8,  \
        us8_t *:       uv8_contains_us8   \
    )((view), (target))

UEXPORT bool uv8_contains_uc8(uv8_t view, uc8_t target);
UEXPORT bool uv8_contains_uz8(uv8_t view, const uc8_t *target);
UEXPORT bool uv8_contains_uz8n(uv8_t view, const uc8_t *target, size_t target_len);
UEXPORT bool uv8_contains_ucv8(uv8_t view, ucv8_t target);
UEXPORT bool uv8_contains_uv8(uv8_t view, uv8_t target);
UEXPORT bool uv8_contains_us8(uv8_t view, const us8_t *target);

// Search

// - Forward

#define uv32_find(view, target)          \
    _Generic((target),                   \
        default:        uv32_find_uc32,  \
        const uc32_t *: uv32_find_uz32,  \
        uc32_t *:       uv32_find_uz32,  \
        ucv32_t:        uv32_find_ucv32, \
        uv32_t:         uv32_find_uv32,  \
        const us32_t *: uv32_find_us32,  \
        us32_t *:       uv32_find_us32   \
    )((view), (target))

#define uv32_find_from(view, target, from)    \
    _Generic((target),                        \
        default:        uv32_find_uc32_from,  \
        const uc32_t *: uv32_find_uz32_from,  \
        uc32_t *:       uv32_find_uz32_from,  \
        ucv32_t:        uv32_find_ucv32_from, \
        uv32_t:         uv32_find_uv32_from,  \
        const us32_t *: uv32_find_us32_from,  \
        us32_t *:       uv32_find_us32_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t uv32_find_uc32(uv32_t view, uc32_t target);
UEXPORT ptrdiff_t uv32_find_uc32_from(uv32_t view, uc32_t target, size_t from);
UEXPORT ptrdiff_t uv32_find_uz32(uv32_t view, const uc32_t *target);
UEXPORT ptrdiff_t uv32_find_uz32_from(uv32_t view, const uc32_t *target, size_t from);
UEXPORT ptrdiff_t uv32_find_uz32n(uv32_t view, const uc32_t *target, size_t target_len);
UEXPORT ptrdiff_t uv32_find_uz32n_from(uv32_t view, const uc32_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uv32_find_ucv32(uv32_t view, ucv32_t target);
UEXPORT ptrdiff_t uv32_find_ucv32_from(uv32_t view, ucv32_t target, size_t from);
UEXPORT ptrdiff_t uv32_find_uv32(uv32_t view, uv32_t target);
UEXPORT ptrdiff_t uv32_find_uv32_from(uv32_t view, uv32_t target, size_t from);
UEXPORT ptrdiff_t uv32_find_us32(uv32_t view, const us32_t *target);
UEXPORT ptrdiff_t uv32_find_us32_from(uv32_t view, const us32_t *target, size_t from);

#define uv16_find(view, target)          \
    _Generic((target),                   \
        default:        uv16_find_uc16,  \
        const uc16_t *: uv16_find_uz16,  \
        uc16_t *:       uv16_find_uz16,  \
        ucv16_t:        uv16_find_ucv16, \
        uv16_t:         uv16_find_uv16,  \
        const us16_t *: uv16_find_us16,  \
        us16_t *:       uv16_find_us16   \
    )((view), (target))

#define uv16_find_from(view, target, from)    \
    _Generic((target),                        \
        default:        uv16_find_uc16_from,  \
        const uc16_t *: uv16_find_uz16_from,  \
        uc16_t *:       uv16_find_uz16_from,  \
        ucv16_t:        uv16_find_ucv16_from, \
        uv16_t:         uv16_find_uv16_from,  \
        const us16_t *: uv16_find_us16_from,  \
        us16_t *:       uv16_find_us16_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t uv16_find_uc16(uv16_t view, uc16_t target);
UEXPORT ptrdiff_t uv16_find_uc16_from(uv16_t view, uc16_t target, size_t from);
UEXPORT ptrdiff_t uv16_find_uz16(uv16_t view, const uc16_t *target);
UEXPORT ptrdiff_t uv16_find_uz16_from(uv16_t view, const uc16_t *target, size_t from);
UEXPORT ptrdiff_t uv16_find_uz16n(uv16_t view, const uc16_t *target, size_t target_len);
UEXPORT ptrdiff_t uv16_find_uz16n_from(uv16_t view, const uc16_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uv16_find_ucv16(uv16_t view, ucv16_t target);
UEXPORT ptrdiff_t uv16_find_ucv16_from(uv16_t view, ucv16_t target, size_t from);
UEXPORT ptrdiff_t uv16_find_uv16(uv16_t view, uv16_t target);
UEXPORT ptrdiff_t uv16_find_uv16_from(uv16_t view, uv16_t target, size_t from);
UEXPORT ptrdiff_t uv16_find_us16(uv16_t view, const us16_t *target);
UEXPORT ptrdiff_t uv16_find_us16_from(uv16_t view, const us16_t *target, size_t from);

#define uv8_find(view, target)        \
    _Generic((target),                \
        default:       uv8_find_uc8,  \
        const uc8_t *: uv8_find_uz8,  \
        uc8_t *:       uv8_find_uz8,  \
        ucv8_t:        uv8_find_ucv8, \
        uv8_t:         uv8_find_uv8,  \
        const us8_t *: uv8_find_us8,  \
        us8_t *:       uv8_find_us8   \
    )((view), (target))

#define uv8_find_from(view, target, from)  \
    _Generic((target),                     \
        default:       uv8_find_uc8_from,  \
        const uc8_t *: uv8_find_uz8_from,  \
        uc8_t *:       uv8_find_uz8_from,  \
        ucv8_t:        uv8_find_ucv8_from, \
        uv8_t:         uv8_find_uv8_from,  \
        const us8_t *: uv8_find_us8_from,  \
        us8_t *:       uv8_find_us8_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t uv8_find_uc8(uv8_t view, uc8_t target);
UEXPORT ptrdiff_t uv8_find_uc8_from(uv8_t view, uc8_t target, size_t from);
UEXPORT ptrdiff_t uv8_find_uz8(uv8_t view, const uc8_t *target);
UEXPORT ptrdiff_t uv8_find_uz8_from(uv8_t view, const uc8_t *target, size_t from);
UEXPORT ptrdiff_t uv8_find_uz8n(uv8_t view, const uc8_t *target, size_t target_len);
UEXPORT ptrdiff_t uv8_find_uz8n_from(uv8_t view, const uc8_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uv8_find_ucv8(uv8_t view, ucv8_t target);
UEXPORT ptrdiff_t uv8_find_ucv8_from(uv8_t view, ucv8_t target, size_t from);
UEXPORT ptrdiff_t uv8_find_uv8(uv8_t view, uv8_t target);
UEXPORT ptrdiff_t uv8_find_uv8_from(uv8_t view, uv8_t target, size_t from);
UEXPORT ptrdiff_t uv8_find_us8(uv8_t view, const us8_t *target);
UEXPORT ptrdiff_t uv8_find_us8_from(uv8_t view, const us8_t *target, size_t from);

// - Backward

#define uv32_rfind(view, target)          \
    _Generic((target),                    \
        default:        uv32_rfind_uc32,  \
        const uc32_t *: uv32_rfind_uz32,  \
        uc32_t *:       uv32_rfind_uz32,  \
        ucv32_t:        uv32_rfind_ucv32, \
        uv32_t:         uv32_rfind_uv32,  \
        const us32_t *: uv32_rfind_us32,  \
        us32_t *:       uv32_rfind_us32   \
    )((view), (target))

#define uv32_rfind_from(view, target, from)    \
    _Generic((target),                         \
        default:        uv32_rfind_uc32_from,  \
        const uc32_t *: uv32_rfind_uz32_from,  \
        uc32_t *:       uv32_rfind_uz32_from,  \
        ucv32_t:        uv32_rfind_ucv32_from, \
        uv32_t:         uv32_rfind_uv32_from,  \
        const us32_t *: uv32_rfind_us32_from,  \
        us32_t *:       uv32_rfind_us32_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t uv32_rfind_uc32(uv32_t view, uc32_t target);
UEXPORT ptrdiff_t uv32_rfind_uc32_from(uv32_t view, uc32_t target, size_t from);
UEXPORT ptrdiff_t uv32_rfind_uz32(uv32_t view, const uc32_t *target);
UEXPORT ptrdiff_t uv32_rfind_uz32_from(uv32_t view, const uc32_t *target, size_t from);
UEXPORT ptrdiff_t uv32_rfind_uz32n(uv32_t view, const uc32_t *target, size_t target_len);
UEXPORT ptrdiff_t uv32_rfind_uz32n_from(uv32_t view, const uc32_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uv32_rfind_ucv32(uv32_t view, ucv32_t target);
UEXPORT ptrdiff_t uv32_rfind_ucv32_from(uv32_t view, ucv32_t target, size_t from);
UEXPORT ptrdiff_t uv32_rfind_uv32(uv32_t view, uv32_t target);
UEXPORT ptrdiff_t uv32_rfind_uv32_from(uv32_t view, uv32_t target, size_t from);
UEXPORT ptrdiff_t uv32_rfind_us32(uv32_t view, const us32_t *target);
UEXPORT ptrdiff_t uv32_rfind_us32_from(uv32_t view, const us32_t *target, size_t from);

#define uv16_rfind(view, target)          \
    _Generic((target),                    \
        default:        uv16_rfind_uc16,  \
        const uc16_t *: uv16_rfind_uz16,  \
        uc16_t *:       uv16_rfind_uz16,  \
        ucv16_t:        uv16_rfind_ucv16, \
        uv16_t:         uv16_rfind_uv16,  \
        const us16_t *: uv16_rfind_us16,  \
        us16_t *:       uv16_rfind_us16   \
    )((view), (target))

#define uv16_rfind_from(view, target, from)    \
    _Generic((target),                         \
        default:        uv16_rfind_uc16_from,  \
        const uc16_t *: uv16_rfind_uz16_from,  \
        uc16_t *:       uv16_rfind_uz16_from,  \
        ucv16_t:        uv16_rfind_ucv16_from, \
        uv16_t:         uv16_rfind_uv16_from,  \
        const us16_t *: uv16_rfind_us16_from,  \
        us16_t *:       uv16_rfind_us16_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t uv16_rfind_uc16(uv16_t view, uc16_t target);
UEXPORT ptrdiff_t uv16_rfind_uc16_from(uv16_t view, uc16_t target, size_t from);
UEXPORT ptrdiff_t uv16_rfind_uz16(uv16_t view, const uc16_t *target);
UEXPORT ptrdiff_t uv16_rfind_uz16_from(uv16_t view, const uc16_t *target, size_t from);
UEXPORT ptrdiff_t uv16_rfind_uz16n(uv16_t view, const uc16_t *target, size_t target_len);
UEXPORT ptrdiff_t uv16_rfind_uz16n_from(uv16_t view, const uc16_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uv16_rfind_ucv16(uv16_t view, ucv16_t target);
UEXPORT ptrdiff_t uv16_rfind_ucv16_from(uv16_t view, ucv16_t target, size_t from);
UEXPORT ptrdiff_t uv16_rfind_uv16(uv16_t view, uv16_t target);
UEXPORT ptrdiff_t uv16_rfind_uv16_from(uv16_t view, uv16_t target, size_t from);
UEXPORT ptrdiff_t uv16_rfind_us16(uv16_t view, const us16_t *target);
UEXPORT ptrdiff_t uv16_rfind_us16_from(uv16_t view, const us16_t *target, size_t from);

#define uv8_rfind(view, target)        \
    _Generic((target),                 \
        default:       uv8_rfind_uc8,  \
        const uc8_t *: uv8_rfind_uz8,  \
        uc8_t *:       uv8_rfind_uz8,  \
        ucv8_t:        uv8_rfind_ucv8, \
        uv8_t:         uv8_rfind_uv8,  \
        const us8_t *: uv8_rfind_us8,  \
        us8_t *:       uv8_rfind_us8   \
    )((view), (target))

#define uv8_rfind_from(view, target, from)  \
    _Generic((target),                      \
        default:       uv8_rfind_uc8_from,  \
        const uc8_t *: uv8_rfind_uz8_from,  \
        uc8_t *:       uv8_rfind_uz8_from,  \
        ucv8_t:        uv8_rfind_ucv8_from, \
        uv8_t:         uv8_rfind_uv8_from,  \
        const us8_t *: uv8_rfind_us8_from,  \
        us8_t *:       uv8_rfind_us8_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t uv8_rfind_uc8(uv8_t view, uc8_t target);
UEXPORT ptrdiff_t uv8_rfind_uc8_from(uv8_t view, uc8_t target, size_t from);
UEXPORT ptrdiff_t uv8_rfind_uz8(uv8_t view, const uc8_t *target);
UEXPORT ptrdiff_t uv8_rfind_uz8_from(uv8_t view, const uc8_t *target, size_t from);
UEXPORT ptrdiff_t uv8_rfind_uz8n(uv8_t view, const uc8_t *target, size_t target_len);
UEXPORT ptrdiff_t uv8_rfind_uz8n_from(uv8_t view, const uc8_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t uv8_rfind_ucv8(uv8_t view, ucv8_t target);
UEXPORT ptrdiff_t uv8_rfind_ucv8_from(uv8_t view, ucv8_t target, size_t from);
UEXPORT ptrdiff_t uv8_rfind_uv8(uv8_t view, uv8_t target);
UEXPORT ptrdiff_t uv8_rfind_uv8_from(uv8_t view, uv8_t target, size_t from);
UEXPORT ptrdiff_t uv8_rfind_us8(uv8_t view, const us8_t *target);
UEXPORT ptrdiff_t uv8_rfind_us8_from(uv8_t view, const us8_t *target, size_t from);

// Erase

#define uv32_erase(view, target)          \
    _Generic((target),                    \
        default:        uv32_erase_uc32,  \
        const uc32_t *: uv32_erase_uz32,  \
        uc32_t *:       uv32_erase_uz32,  \
        ucv32_t:        uv32_erase_ucv32, \
        uv32_t:         uv32_erase_uv32,  \
        const us32_t *: uv32_erase_us32,  \
        us32_t *:       uv32_erase_us32   \
    )((view), (target))

UEXPORT size_t uv32_erase_uc32(uv32_t view, uc32_t target);
UEXPORT size_t uv32_erase_uz32(uv32_t view, const uc32_t *target);
UEXPORT size_t uv32_erase_uz32n(uv32_t view, const uc32_t *target, size_t target_len);
UEXPORT size_t uv32_erase_ucv32(uv32_t view, ucv32_t target);
UEXPORT size_t uv32_erase_uv32(uv32_t view, uv32_t target);
UEXPORT size_t uv32_erase_us32(uv32_t view, const us32_t *target);

#define uv16_erase(view, target)          \
    _Generic((target),                    \
        default:        uv16_erase_uc16,  \
        const uc16_t *: uv16_erase_uz16,  \
        uc16_t *:       uv16_erase_uz16,  \
        ucv16_t:        uv16_erase_ucv16, \
        uv16_t:         uv16_erase_uv16,  \
        const us16_t *: uv16_erase_us16,  \
        us16_t *:       uv16_erase_us16   \
    )((view), (target))

UEXPORT size_t uv16_erase_uc16(uv16_t view, uc16_t target);
UEXPORT size_t uv16_erase_uz16(uv16_t view, const uc16_t *target);
UEXPORT size_t uv16_erase_uz16n(uv16_t view, const uc16_t *target, size_t target_len);
UEXPORT size_t uv16_erase_ucv16(uv16_t view, ucv16_t target);
UEXPORT size_t uv16_erase_uv16(uv16_t view, uv16_t target);
UEXPORT size_t uv16_erase_us16(uv16_t view, const us16_t *target);

#define uv8_erase(view, target)        \
    _Generic((target),                 \
        default:       uv8_erase_uc8,  \
        const uc8_t *: uv8_erase_uz8,  \
        uc8_t *:       uv8_erase_uz8,  \
        ucv8_t:        uv8_erase_ucv8, \
        uv8_t:         uv8_erase_uv8,  \
        const us8_t *: uv8_erase_us8,  \
        us8_t *:       uv8_erase_us8   \
    )((view), (target))

UEXPORT size_t uv8_erase_uc8(uv8_t view, uc8_t target);
UEXPORT size_t uv8_erase_uz8(uv8_t view, const uc8_t *target);
UEXPORT size_t uv8_erase_uz8n(uv8_t view, const uc8_t *target, size_t target_len);
UEXPORT size_t uv8_erase_ucv8(uv8_t view, ucv8_t target);
UEXPORT size_t uv8_erase_uv8(uv8_t view, uv8_t target);
UEXPORT size_t uv8_erase_us8(uv8_t view, const us8_t *target);

// Replace

#define uv32_replace(view, from, to)             \
    _Generic((from),                             \
        default:        uv32_replace_uc32_uc32,  \
        const uc32_t *: uv32_replace_uz32_uc32,  \
        uc32_t *:       uv32_replace_uz32_uc32,  \
        ucv32_t:        uv32_replace_ucv32_uc32, \
        uv32_t:         uv32_replace_uv32_uc32,  \
        const us32_t *: uv32_replace_us32_uc32,  \
        us32_t *:       uv32_replace_us32_uc32   \
    )((view), (from), (to))

UEXPORT size_t uv32_replace_uc32_uc32(uv32_t view, uc32_t from, uc32_t to);
UEXPORT size_t uv32_replace_uz32_uc32(uv32_t view, const uc32_t *from, uc32_t to);
UEXPORT size_t uv32_replace_uz32n_uc32(uv32_t view, const uc32_t *from, size_t from_len, uc32_t to);
UEXPORT size_t uv32_replace_ucv32_uc32(uv32_t view, ucv32_t from, uc32_t to);
UEXPORT size_t uv32_replace_uv32_uc32(uv32_t view, uv32_t from, uc32_t to);
UEXPORT size_t uv32_replace_us32_uc32(uv32_t view, const us32_t *from, uc32_t to);

#define uv16_replace(view, from, to)             \
    _Generic((from),                             \
        default:        uv16_replace_uc16_uc16,  \
        const uc16_t *: uv16_replace_uz16_uc16,  \
        uc16_t *:       uv16_replace_uz16_uc16,  \
        ucv16_t:        uv16_replace_ucv16_uc16, \
        uv16_t:         uv16_replace_uv16_uc16,  \
        const us16_t *: uv16_replace_us16_uc16,  \
        us16_t *:       uv16_replace_us16_uc16   \
    )((view), (from), (to))

UEXPORT size_t uv16_replace_uc16_uc16(uv16_t view, uc16_t from, uc16_t to);
UEXPORT size_t uv16_replace_uz16_uc16(uv16_t view, const uc16_t *from, uc16_t to);
UEXPORT size_t uv16_replace_uz16n_uc16(uv16_t view, const uc16_t *from, size_t from_len, uc16_t to);
UEXPORT size_t uv16_replace_ucv16_uc16(uv16_t view, ucv16_t from, uc16_t to);
UEXPORT size_t uv16_replace_uv16_uc16(uv16_t view, uv16_t from, uc16_t to);
UEXPORT size_t uv16_replace_us16_uc16(uv16_t view, const us16_t *from, uc16_t to);

#define uv8_replace(view, from, to)          \
    _Generic((from),                         \
        default:       uv8_replace_uc8_uc8,  \
        const uc8_t *: uv8_replace_uz8_uc8,  \
        uc8_t *:       uv8_replace_uz8_uc8,  \
        ucv8_t:        uv8_replace_ucv8_uc8, \
        uv8_t:         uv8_replace_uv8_uc8,  \
        const us8_t *: uv8_replace_us8_uc8,  \
        us8_t *:       uv8_replace_us8_uc8   \
    )((view), (from), (to))

UEXPORT size_t uv8_replace_uc8_uc8(uv8_t view, uc8_t from, uc8_t to);
UEXPORT size_t uv8_replace_uz8_uc8(uv8_t view, const uc8_t *from, uc8_t to);
UEXPORT size_t uv8_replace_uz8n_uc8(uv8_t view, const uc8_t *from, size_t from_len, uc8_t to);
UEXPORT size_t uv8_replace_ucv8_uc8(uv8_t view, ucv8_t from, uc8_t to);
UEXPORT size_t uv8_replace_uv8_uc8(uv8_t view, uv8_t from, uc8_t to);
UEXPORT size_t uv8_replace_us8_uc8(uv8_t view, const us8_t *from, uc8_t to);

// Replaced length

#define uv32_replaced_len(view, from, to)                  \
    _Generic((from),                                       \
        default: _Generic((to),                            \
            default:        uv32_replaced_len_uc32_uc32,   \
            const uc32_t *: uv32_replaced_len_uc32_uz32,   \
            uc32_t *:       uv32_replaced_len_uc32_uz32,   \
            ucv32_t:        uv32_replaced_len_uc32_ucv32,  \
            uv32_t:         uv32_replaced_len_uc32_uv32,   \
            const us32_t *: uv32_replaced_len_uc32_us32,   \
            us32_t *:       uv32_replaced_len_uc32_us32    \
        ),                                                 \
        const uc32_t *: _Generic((to),                     \
            default:        uv32_replaced_len_uz32_uc32,   \
            const uc32_t *: uv32_replaced_len_uz32_uz32,   \
            uc32_t *:       uv32_replaced_len_uz32_uz32,   \
            ucv32_t:        uv32_replaced_len_uz32_ucv32,  \
            uv32_t:         uv32_replaced_len_uz32_uv32,   \
            const us32_t *: uv32_replaced_len_uz32_us32,   \
            us32_t *:       uv32_replaced_len_uz32_us32    \
        ),                                                 \
        uc32_t *: _Generic((to),                           \
            default:        uv32_replaced_len_uz32_uc32,   \
            const uc32_t *: uv32_replaced_len_uz32_uz32,   \
            uc32_t *:       uv32_replaced_len_uz32_uz32,   \
            ucv32_t:        uv32_replaced_len_uz32_ucv32,  \
            uv32_t:         uv32_replaced_len_uz32_uv32,   \
            const us32_t *: uv32_replaced_len_uz32_us32,   \
            us32_t *:       uv32_replaced_len_uz32_us32    \
        ),                                                 \
        ucv32_t: _Generic((to),                            \
            default:        uv32_replaced_len_ucv32_uc32,  \
            const uc32_t *: uv32_replaced_len_ucv32_uz32,  \
            uc32_t *:       uv32_replaced_len_ucv32_uz32,  \
            ucv32_t:        uv32_replaced_len_ucv32_ucv32, \
            uv32_t:         uv32_replaced_len_ucv32_uv32,  \
            const us32_t *: uv32_replaced_len_ucv32_us32,  \
            us32_t *:       uv32_replaced_len_ucv32_us32   \
        ),                                                 \
        uv32_t: _Generic((to),                             \
            default:        uv32_replaced_len_uv32_uc32,   \
            const uc32_t *: uv32_replaced_len_uv32_uz32,   \
            uc32_t *:       uv32_replaced_len_uv32_uz32,   \
            ucv32_t:        uv32_replaced_len_uv32_ucv32,  \
            uv32_t:         uv32_replaced_len_uv32_uv32,   \
            const us32_t *: uv32_replaced_len_uv32_us32,   \
            us32_t *:       uv32_replaced_len_uv32_us32    \
        ),                                                 \
        const us32_t *: _Generic((to),                     \
            default:        uv32_replaced_len_us32_uc32,   \
            const uc32_t *: uv32_replaced_len_us32_uz32,   \
            uc32_t *:       uv32_replaced_len_us32_uz32,   \
            ucv32_t:        uv32_replaced_len_us32_ucv32,  \
            uv32_t:         uv32_replaced_len_us32_uv32,   \
            const us32_t *: uv32_replaced_len_us32_us32,   \
            us32_t *:       uv32_replaced_len_us32_us32    \
        )                                                  \
        us32_t *: _Generic((to),                           \
            default:        uv32_replaced_len_us32_uc32,   \
            const uc32_t *: uv32_replaced_len_us32_uz32,   \
            uc32_t *:       uv32_replaced_len_us32_uz32,   \
            ucv32_t:        uv32_replaced_len_us32_ucv32,  \
            uv32_t:         uv32_replaced_len_us32_uv32,   \
            const us32_t *: uv32_replaced_len_us32_us32,   \
            us32_t *:       uv32_replaced_len_us32_us32    \
        )                                                  \
    )((view), (from), (to))

UEXPORT size_t uv32_replaced_len_uc32_uz32(uv32_t view, uc32_t from, const uc32_t *to);
UEXPORT size_t uv32_replaced_len_uc32_uz32n(uv32_t view, uc32_t from, size_t to_len);
UEXPORT size_t uv32_replaced_len_uc32_ucv32(uv32_t view, uc32_t from, ucv32_t to);
UEXPORT size_t uv32_replaced_len_uc32_uv32(uv32_t view, uc32_t from, uv32_t to);
UEXPORT size_t uv32_replaced_len_uc32_us32(uv32_t view, uc32_t from, const us32_t *to);

UEXPORT size_t uv32_replaced_len_uz32_uc32(uv32_t view, const uc32_t *from, uc32_t to);
UEXPORT size_t uv32_replaced_len_uz32_uz32(uv32_t view, const uc32_t *from, const uc32_t *to);
UEXPORT size_t uv32_replaced_len_uz32_uz32n(uv32_t view, const uc32_t *from, size_t to_len);
UEXPORT size_t uv32_replaced_len_uz32_ucv32(uv32_t view, const uc32_t *from, ucv32_t to);
UEXPORT size_t uv32_replaced_len_uz32_uv32(uv32_t view, const uc32_t *from, uv32_t to);
UEXPORT size_t uv32_replaced_len_uz32_us32(uv32_t view, const uc32_t *from, const us32_t *to);

UEXPORT size_t uv32_replaced_len_uz32n_uc32(uv32_t view, const uc32_t *from, size_t from_len, uc32_t to);
UEXPORT size_t uv32_replaced_len_uz32n_uz32(uv32_t view, const uc32_t *from, size_t from_len, const uc32_t *to);
UEXPORT size_t uv32_replaced_len_uz32n_uz32n(uv32_t view, const uc32_t *from, size_t from_len, size_t to_len);
UEXPORT size_t uv32_replaced_len_uz32n_ucv32(uv32_t view, const uc32_t *from, size_t from_len, ucv32_t to);
UEXPORT size_t uv32_replaced_len_uz32n_uv32(uv32_t view, const uc32_t *from, size_t from_len, uv32_t to);
UEXPORT size_t uv32_replaced_len_uz32n_us32(uv32_t view, const uc32_t *from, size_t from_len, const us32_t *to);

UEXPORT size_t uv32_replaced_len_ucv32_uc32(uv32_t view, ucv32_t from, uc32_t to);
UEXPORT size_t uv32_replaced_len_ucv32_uz32(uv32_t view, ucv32_t from, const uc32_t *to);
UEXPORT size_t uv32_replaced_len_ucv32_uz32n(uv32_t view, ucv32_t from, size_t to_len);
UEXPORT size_t uv32_replaced_len_ucv32_ucv32(uv32_t view, ucv32_t from, ucv32_t to);
UEXPORT size_t uv32_replaced_len_ucv32_uv32(uv32_t view, ucv32_t from, uv32_t to);
UEXPORT size_t uv32_replaced_len_ucv32_us32(uv32_t view, ucv32_t from, const us32_t *to);

UEXPORT size_t uv32_replaced_len_uv32_uc32(uv32_t view, uv32_t from, uc32_t to);
UEXPORT size_t uv32_replaced_len_uv32_uz32(uv32_t view, uv32_t from, const uc32_t *to);
UEXPORT size_t uv32_replaced_len_uv32_uz32n(uv32_t view, uv32_t from, size_t to_len);
UEXPORT size_t uv32_replaced_len_uv32_ucv32(uv32_t view, uv32_t from, ucv32_t to);
UEXPORT size_t uv32_replaced_len_uv32_uv32(uv32_t view, uv32_t from, uv32_t to);
UEXPORT size_t uv32_replaced_len_uv32_us32(uv32_t view, uv32_t from, const us32_t *to);

UEXPORT size_t uv32_replaced_len_us32_uc32(uv32_t view, const us32_t *from, uc32_t to);
UEXPORT size_t uv32_replaced_len_us32_uz32(uv32_t view, const us32_t *from, const uc32_t *to);
UEXPORT size_t uv32_replaced_len_us32_uz32n(uv32_t view, const us32_t *from, size_t to_len);
UEXPORT size_t uv32_replaced_len_us32_ucv32(uv32_t view, const us32_t *from, ucv32_t to);
UEXPORT size_t uv32_replaced_len_us32_uv32(uv32_t view, const us32_t *from, uv32_t to);
UEXPORT size_t uv32_replaced_len_us32_us32(uv32_t view, const us32_t *from, const us32_t *to);

#define uv16_replaced_len(view, from, to)                  \
    _Generic((from),                                       \
        default: _Generic((to),                            \
            default:        uv16_replaced_len_uc16_uc16,   \
            const uc16_t *: uv16_replaced_len_uc16_uz16,   \
            uc16_t *:       uv16_replaced_len_uc16_uz16,   \
            ucv16_t:        uv16_replaced_len_uc16_ucv16,  \
            uv16_t:         uv16_replaced_len_uc16_uv16,   \
            const us16_t *: uv16_replaced_len_uc16_us16,   \
            us16_t *:       uv16_replaced_len_uc16_us16    \
        ),                                                 \
        const uc16_t *: _Generic((to),                     \
            default:        uv16_replaced_len_uz16_uc16,   \
            const uc16_t *: uv16_replaced_len_uz16_uz16,   \
            uc16_t *:       uv16_replaced_len_uz16_uz16,   \
            ucv16_t:        uv16_replaced_len_uz16_ucv16,  \
            uv16_t:         uv16_replaced_len_uz16_uv16,   \
            const us16_t *: uv16_replaced_len_uz16_us16,   \
            us16_t *:       uv16_replaced_len_uz16_us16    \
        ),                                                 \
        uc16_t *: _Generic((to),                           \
            default:        uv16_replaced_len_uz16_uc16,   \
            const uc16_t *: uv16_replaced_len_uz16_uz16,   \
            uc16_t *:       uv16_replaced_len_uz16_uz16,   \
            ucv16_t:        uv16_replaced_len_uz16_ucv16,  \
            uv16_t:         uv16_replaced_len_uz16_uv16,   \
            const us16_t *: uv16_replaced_len_uz16_us16,   \
            us16_t *:       uv16_replaced_len_uz16_us16    \
        ),                                                 \
        ucv16_t: _Generic((to),                            \
            default:        uv16_replaced_len_ucv16_uc16,  \
            const uc16_t *: uv16_replaced_len_ucv16_uz16,  \
            uc16_t *:       uv16_replaced_len_ucv16_uz16,  \
            ucv16_t:        uv16_replaced_len_ucv16_ucv16, \
            uv16_t:         uv16_replaced_len_ucv16_uv16,  \
            const us16_t *: uv16_replaced_len_ucv16_us16,  \
            us16_t *:       uv16_replaced_len_ucv16_us16   \
        ),                                                 \
        uv16_t: _Generic((to),                             \
            default:        uv16_replaced_len_uv16_uc16,   \
            const uc16_t *: uv16_replaced_len_uv16_uz16,   \
            uc16_t *:       uv16_replaced_len_uv16_uz16,   \
            ucv16_t:        uv16_replaced_len_uv16_ucv16,  \
            uv16_t:         uv16_replaced_len_uv16_uv16,   \
            const us16_t *: uv16_replaced_len_uv16_us16,   \
            us16_t *:       uv16_replaced_len_uv16_us16    \
        ),                                                 \
        const us16_t *: _Generic((to),                     \
            default:        uv16_replaced_len_us16_uc16,   \
            const uc16_t *: uv16_replaced_len_us16_uz16,   \
            uc16_t *:       uv16_replaced_len_us16_uz16,   \
            ucv16_t:        uv16_replaced_len_us16_ucv16,  \
            uv16_t:         uv16_replaced_len_us16_uv16,   \
            const us16_t *: uv16_replaced_len_us16_us16,   \
            us16_t *:       uv16_replaced_len_us16_us16    \
        )                                                  \
        us16_t *: _Generic((to),                           \
            default:        uv16_replaced_len_us16_uc16,   \
            const uc16_t *: uv16_replaced_len_us16_uz16,   \
            uc16_t *:       uv16_replaced_len_us16_uz16,   \
            ucv16_t:        uv16_replaced_len_us16_ucv16,  \
            uv16_t:         uv16_replaced_len_us16_uv16,   \
            const us16_t *: uv16_replaced_len_us16_us16,   \
            us16_t *:       uv16_replaced_len_us16_us16    \
        )                                                  \
    )((view), (from), (to))

UEXPORT size_t uv16_replaced_len_uc16_uz16(uv16_t view, uc16_t from, const uc16_t *to);
UEXPORT size_t uv16_replaced_len_uc16_uz16n(uv16_t view, uc16_t from, size_t to_len);
UEXPORT size_t uv16_replaced_len_uc16_ucv16(uv16_t view, uc16_t from, ucv16_t to);
UEXPORT size_t uv16_replaced_len_uc16_uv16(uv16_t view, uc16_t from, uv16_t to);
UEXPORT size_t uv16_replaced_len_uc16_us16(uv16_t view, uc16_t from, const us16_t *to);

UEXPORT size_t uv16_replaced_len_uz16_uc16(uv16_t view, const uc16_t *from, uc16_t to);
UEXPORT size_t uv16_replaced_len_uz16_uz16(uv16_t view, const uc16_t *from, const uc16_t *to);
UEXPORT size_t uv16_replaced_len_uz16_uz16n(uv16_t view, const uc16_t *from, size_t to_len);
UEXPORT size_t uv16_replaced_len_uz16_ucv16(uv16_t view, const uc16_t *from, ucv16_t to);
UEXPORT size_t uv16_replaced_len_uz16_uv16(uv16_t view, const uc16_t *from, uv16_t to);
UEXPORT size_t uv16_replaced_len_uz16_us16(uv16_t view, const uc16_t *from, const us16_t *to);

UEXPORT size_t uv16_replaced_len_uz16n_uc16(uv16_t view, const uc16_t *from, size_t from_len, uc16_t to);
UEXPORT size_t uv16_replaced_len_uz16n_uz16(uv16_t view, const uc16_t *from, size_t from_len, const uc16_t *to);
UEXPORT size_t uv16_replaced_len_uz16n_uz16n(uv16_t view, const uc16_t *from, size_t from_len, size_t to_len);
UEXPORT size_t uv16_replaced_len_uz16n_ucv16(uv16_t view, const uc16_t *from, size_t from_len, ucv16_t to);
UEXPORT size_t uv16_replaced_len_uz16n_uv16(uv16_t view, const uc16_t *from, size_t from_len, uv16_t to);
UEXPORT size_t uv16_replaced_len_uz16n_us16(uv16_t view, const uc16_t *from, size_t from_len, const us16_t *to);

UEXPORT size_t uv16_replaced_len_ucv16_uc16(uv16_t view, ucv16_t from, uc16_t to);
UEXPORT size_t uv16_replaced_len_ucv16_uz16(uv16_t view, ucv16_t from, const uc16_t *to);
UEXPORT size_t uv16_replaced_len_ucv16_uz16n(uv16_t view, ucv16_t from, size_t to_len);
UEXPORT size_t uv16_replaced_len_ucv16_ucv16(uv16_t view, ucv16_t from, ucv16_t to);
UEXPORT size_t uv16_replaced_len_ucv16_uv16(uv16_t view, ucv16_t from, uv16_t to);
UEXPORT size_t uv16_replaced_len_ucv16_us16(uv16_t view, ucv16_t from, const us16_t *to);

UEXPORT size_t uv16_replaced_len_uv16_uc16(uv16_t view, uv16_t from, uc16_t to);
UEXPORT size_t uv16_replaced_len_uv16_uz16(uv16_t view, uv16_t from, const uc16_t *to);
UEXPORT size_t uv16_replaced_len_uv16_uz16n(uv16_t view, uv16_t from, size_t to_len);
UEXPORT size_t uv16_replaced_len_uv16_ucv16(uv16_t view, uv16_t from, ucv16_t to);
UEXPORT size_t uv16_replaced_len_uv16_uv16(uv16_t view, uv16_t from, uv16_t to);
UEXPORT size_t uv16_replaced_len_uv16_us16(uv16_t view, uv16_t from, const us16_t *to);

UEXPORT size_t uv16_replaced_len_us16_uc16(uv16_t view, const us16_t *from, uc16_t to);
UEXPORT size_t uv16_replaced_len_us16_uz16(uv16_t view, const us16_t *from, const uc16_t *to);
UEXPORT size_t uv16_replaced_len_us16_uz16n(uv16_t view, const us16_t *from, size_t to_len);
UEXPORT size_t uv16_replaced_len_us16_ucv16(uv16_t view, const us16_t *from, ucv16_t to);
UEXPORT size_t uv16_replaced_len_us16_uv16(uv16_t view, const us16_t *from, uv16_t to);
UEXPORT size_t uv16_replaced_len_us16_us16(uv16_t view, const us16_t *from, const us16_t *to);

#define uv8_replaced_len(view, from, to)               \
    _Generic((from),                                   \
        default: _Generic((to),                        \
            default:       uv8_replaced_len_uc8_uc8,   \
            const uc8_t *: uv8_replaced_len_uc8_uz8,   \
            uc8_t *:       uv8_replaced_len_uc8_uz8,   \
            ucv8_t:        uv8_replaced_len_uc8_ucv8,  \
            uv8_t:         uv8_replaced_len_uc8_uv8,   \
            const us8_t *: uv8_replaced_len_uc8_us8,   \
            us8_t *:       uv8_replaced_len_uc8_us8    \
        ),                                             \
        const uc8_t *: _Generic((to),                  \
            default:       uv8_replaced_len_uz8_uc8,   \
            const uc8_t *: uv8_replaced_len_uz8_uz8,   \
            uc8_t *:       uv8_replaced_len_uz8_uz8,   \
            ucv8_t:        uv8_replaced_len_uz8_ucv8,  \
            uv8_t:         uv8_replaced_len_uz8_uv8,   \
            const us8_t *: uv8_replaced_len_uz8_us8,   \
            us8_t *:       uv8_replaced_len_uz8_us8    \
        ),                                             \
        uc8_t *: _Generic((to),                        \
            default:       uv8_replaced_len_uz8_uc8,   \
            const uc8_t *: uv8_replaced_len_uz8_uz8,   \
            uc8_t *:       uv8_replaced_len_uz8_uz8,   \
            ucv8_t:        uv8_replaced_len_uz8_ucv8,  \
            uv8_t:         uv8_replaced_len_uz8_uv8,   \
            const us8_t *: uv8_replaced_len_uz8_us8,   \
            us8_t *:       uv8_replaced_len_uz8_us8    \
        ),                                             \
        ucv8_t: _Generic((to),                         \
            default:       uv8_replaced_len_ucv8_uc8,  \
            const uc8_t *: uv8_replaced_len_ucv8_uz8,  \
            uc8_t *:       uv8_replaced_len_ucv8_uz8,  \
            ucv8_t:        uv8_replaced_len_ucv8_ucv8, \
            uv8_t:         uv8_replaced_len_ucv8_uv8,  \
            const us8_t *: uv8_replaced_len_ucv8_us8,  \
            us8_t *:       uv8_replaced_len_ucv8_us8   \
        ),                                             \
        uv8_t: _Generic((to),                          \
            default:       uv8_replaced_len_uv8_uc8,   \
            const uc8_t *: uv8_replaced_len_uv8_uz8,   \
            uc8_t *:       uv8_replaced_len_uv8_uz8,   \
            ucv8_t:        uv8_replaced_len_uv8_ucv8,  \
            uv8_t:         uv8_replaced_len_uv8_uv8,   \
            const us8_t *: uv8_replaced_len_uv8_us8,   \
            us8_t *:       uv8_replaced_len_uv8_us8    \
        ),                                             \
        const us8_t *: _Generic((to),                  \
            default:       uv8_replaced_len_us8_uc8,   \
            const uc8_t *: uv8_replaced_len_us8_uz8,   \
            uc8_t *:       uv8_replaced_len_us8_uz8,   \
            ucv8_t:        uv8_replaced_len_us8_ucv8,  \
            uv8_t:         uv8_replaced_len_us8_uv8,   \
            const us8_t *: uv8_replaced_len_us8_us8,   \
            us8_t *:       uv8_replaced_len_us8_us8    \
        )                                              \
        us8_t *: _Generic((to),                        \
            default:       uv8_replaced_len_us8_uc8,   \
            const uc8_t *: uv8_replaced_len_us8_uz8,   \
            uc8_t *:       uv8_replaced_len_us8_uz8,   \
            ucv8_t:        uv8_replaced_len_us8_ucv8,  \
            uv8_t:         uv8_replaced_len_us8_uv8,   \
            const us8_t *: uv8_replaced_len_us8_us8,   \
            us8_t *:       uv8_replaced_len_us8_us8    \
        )                                              \
    )((view), (from), (to))

UEXPORT size_t uv8_replaced_len_uc8_uz8(uv8_t view, uc8_t from, const uc8_t *to);
UEXPORT size_t uv8_replaced_len_uc8_uz8n(uv8_t view, uc8_t from, size_t to_len);
UEXPORT size_t uv8_replaced_len_uc8_ucv8(uv8_t view, uc8_t from, ucv8_t to);
UEXPORT size_t uv8_replaced_len_uc8_uv8(uv8_t view, uc8_t from, uv8_t to);
UEXPORT size_t uv8_replaced_len_uc8_us8(uv8_t view, uc8_t from, const us8_t *to);

UEXPORT size_t uv8_replaced_len_uz8_uc8(uv8_t view, const uc8_t *from, uc8_t to);
UEXPORT size_t uv8_replaced_len_uz8_uz8(uv8_t view, const uc8_t *from, const uc8_t *to);
UEXPORT size_t uv8_replaced_len_uz8_uz8n(uv8_t view, const uc8_t *from, size_t to_len);
UEXPORT size_t uv8_replaced_len_uz8_ucv8(uv8_t view, const uc8_t *from, ucv8_t to);
UEXPORT size_t uv8_replaced_len_uz8_uv8(uv8_t view, const uc8_t *from, uv8_t to);
UEXPORT size_t uv8_replaced_len_uz8_us8(uv8_t view, const uc8_t *from, const us8_t *to);

UEXPORT size_t uv8_replaced_len_uz8n_uc8(uv8_t view, const uc8_t *from, size_t from_len, uc8_t to);
UEXPORT size_t uv8_replaced_len_uz8n_uz8(uv8_t view, const uc8_t *from, size_t from_len, const uc8_t *to);
UEXPORT size_t uv8_replaced_len_uz8n_uz8n(uv8_t view, const uc8_t *from, size_t from_len, size_t to_len);
UEXPORT size_t uv8_replaced_len_uz8n_ucv8(uv8_t view, const uc8_t *from, size_t from_len, ucv8_t to);
UEXPORT size_t uv8_replaced_len_uz8n_uv8(uv8_t view, const uc8_t *from, size_t from_len, uv8_t to);
UEXPORT size_t uv8_replaced_len_uz8n_us8(uv8_t view, const uc8_t *from, size_t from_len, const us8_t *to);

UEXPORT size_t uv8_replaced_len_ucv8_uc8(uv8_t view, ucv8_t from, uc8_t to);
UEXPORT size_t uv8_replaced_len_ucv8_uz8(uv8_t view, ucv8_t from, const uc8_t *to);
UEXPORT size_t uv8_replaced_len_ucv8_uz8n(uv8_t view, ucv8_t from, size_t to_len);
UEXPORT size_t uv8_replaced_len_ucv8_ucv8(uv8_t view, ucv8_t from, ucv8_t to);
UEXPORT size_t uv8_replaced_len_ucv8_uv8(uv8_t view, ucv8_t from, uv8_t to);
UEXPORT size_t uv8_replaced_len_ucv8_us8(uv8_t view, ucv8_t from, const us8_t *to);

UEXPORT size_t uv8_replaced_len_uv8_uc8(uv8_t view, uv8_t from, uc8_t to);
UEXPORT size_t uv8_replaced_len_uv8_uz8(uv8_t view, uv8_t from, const uc8_t *to);
UEXPORT size_t uv8_replaced_len_uv8_uz8n(uv8_t view, uv8_t from, size_t to_len);
UEXPORT size_t uv8_replaced_len_uv8_ucv8(uv8_t view, uv8_t from, ucv8_t to);
UEXPORT size_t uv8_replaced_len_uv8_uv8(uv8_t view, uv8_t from, uv8_t to);
UEXPORT size_t uv8_replaced_len_uv8_us8(uv8_t view, uv8_t from, const us8_t *to);

UEXPORT size_t uv8_replaced_len_us8_uc8(uv8_t view, const us8_t *from, uc8_t to);
UEXPORT size_t uv8_replaced_len_us8_uz8(uv8_t view, const us8_t *from, const uc8_t *to);
UEXPORT size_t uv8_replaced_len_us8_uz8n(uv8_t view, const us8_t *from, size_t to_len);
UEXPORT size_t uv8_replaced_len_us8_ucv8(uv8_t view, const us8_t *from, ucv8_t to);
UEXPORT size_t uv8_replaced_len_us8_uv8(uv8_t view, const us8_t *from, uv8_t to);
UEXPORT size_t uv8_replaced_len_us8_us8(uv8_t view, const us8_t *from, const us8_t *to);

// Count

#define uv32_count(view, target)          \
    _Generic((target),                    \
        default:        uv32_count_uc32,  \
        const uc32_t *: uv32_count_uz32,  \
        uc32_t *:       uv32_count_uz32,  \
        ucv32_t:        uv32_count_ucv32, \
        uv32_t:         uv32_count_uv32,  \
        const us32_t *: uv32_count_us32,  \
        us32_t *:       uv32_count_us32   \
    )((view), (target))

UEXPORT size_t uv32_count_uc32(uv32_t view, uc32_t target);
UEXPORT size_t uv32_count_uz32(uv32_t view, const uc32_t *target);
UEXPORT size_t uv32_count_uz32n(uv32_t view, const uc32_t *target, size_t target_len);
UEXPORT size_t uv32_count_ucv32(uv32_t view, ucv32_t target);
UEXPORT size_t uv32_count_uv32(uv32_t view, uv32_t target);
UEXPORT size_t uv32_count_us32(uv32_t view, const us32_t *target);

#define uv16_count(view, target)          \
    _Generic((target),                    \
        default:        uv16_count_uc16,  \
        const uc16_t *: uv16_count_uz16,  \
        uc16_t *:       uv16_count_uz16,  \
        ucv16_t:        uv16_count_ucv16, \
        uv16_t:         uv16_count_uv16,  \
        const us16_t *: uv16_count_us16,  \
        us16_t *:       uv16_count_us16   \
    )((view), (target))

UEXPORT size_t uv16_count_uc16(uv16_t view, uc16_t target);
UEXPORT size_t uv16_count_uz16(uv16_t view, const uc16_t *target);
UEXPORT size_t uv16_count_uz16n(uv16_t view, const uc16_t *target, size_t target_len);
UEXPORT size_t uv16_count_ucv16(uv16_t view, ucv16_t target);
UEXPORT size_t uv16_count_uv16(uv16_t view, uv16_t target);
UEXPORT size_t uv16_count_us16(uv16_t view, const us16_t *target);

#define uv8_count(view, target)        \
    _Generic((target),                 \
        default:       uv8_count_uc8,  \
        const uc8_t *: uv8_count_uz8,  \
        uc8_t *:       uv8_count_uz8,  \
        ucv8_t:        uv8_count_ucv8, \
        uv8_t:         uv8_count_uv8,  \
        const us8_t *: uv8_count_us8,  \
        us8_t *:       uv8_count_us8   \
    )((view), (target))

UEXPORT size_t uv8_count_uc8(uv8_t view, uc8_t target);
UEXPORT size_t uv8_count_uz8(uv8_t view, const uc8_t *target);
UEXPORT size_t uv8_count_uz8n(uv8_t view, const uc8_t *target, size_t target_len);
UEXPORT size_t uv8_count_ucv8(uv8_t view, ucv8_t target);
UEXPORT size_t uv8_count_uv8(uv8_t view, uv8_t target);
UEXPORT size_t uv8_count_us8(uv8_t view, const us8_t *target);

// Bounds

UEXPORT bool uv32_bounds(uv32_t view, size_t index);
UEXPORT bool uv32_ebounds(uv32_t view, size_t index);
UEXPORT bool uv32_bounds_range(uv32_t view, size_t begin, size_t len);
UEXPORT bool uv32_ebounds_range(uv32_t view, size_t begin, size_t len);

UEXPORT bool uv16_bounds(uv16_t view, size_t index);
UEXPORT bool uv16_ebounds(uv16_t view, size_t index);
UEXPORT bool uv16_bounds_range(uv16_t view, size_t begin, size_t len);
UEXPORT bool uv16_ebounds_range(uv16_t view, size_t begin, size_t len);

UEXPORT bool uv8_bounds(uv8_t view, size_t index);
UEXPORT bool uv8_ebounds(uv8_t view, size_t index);
UEXPORT bool uv8_bounds_range(uv8_t view, size_t begin, size_t len);
UEXPORT bool uv8_ebounds_range(uv8_t view, size_t begin, size_t len);

// Starts with

#define uv32_starts_with(view, target)          \
    _Generic((target),                          \
        default:        uv32_starts_with_uc32,  \
        const uc32_t *: uv32_starts_with_uz32,  \
        uc32_t *:       uv32_starts_with_uz32,  \
        ucv32_t:        uv32_starts_with_ucv32, \
        uv32_t:         uv32_starts_with_uv32,  \
        const us32_t *: uv32_starts_with_us32,  \
        us32_t *:       uv32_starts_with_us32   \
    )((view), (target))

UEXPORT bool uv32_starts_with_uc32(uv32_t view, uc32_t target);
UEXPORT bool uv32_starts_with_uz32(uv32_t view, const uc32_t *target);
UEXPORT bool uv32_starts_with_uz32n(uv32_t view, const uc32_t *target, size_t target_len);
UEXPORT bool uv32_starts_with_ucv32(uv32_t view, ucv32_t target);
UEXPORT bool uv32_starts_with_uv32(uv32_t view, uv32_t target);
UEXPORT bool uv32_starts_with_us32(uv32_t view, const us32_t *target);

#define uv16_starts_with(view, target)          \
    _Generic((target),                          \
        default:        uv16_starts_with_uc16,  \
        const uc16_t *: uv16_starts_with_uz16,  \
        uc16_t *:       uv16_starts_with_uz16,  \
        ucv16_t:        uv16_starts_with_ucv16, \
        uv16_t:         uv16_starts_with_uv16,  \
        const us16_t *: uv16_starts_with_us16,  \
        us16_t *:       uv16_starts_with_us16   \
    )((view), (target))

UEXPORT bool uv16_starts_with_uc16(uv16_t view, uc16_t target);
UEXPORT bool uv16_starts_with_uz16(uv16_t view, const uc16_t *target);
UEXPORT bool uv16_starts_with_uz16n(uv16_t view, const uc16_t *target, size_t target_len);
UEXPORT bool uv16_starts_with_ucv16(uv16_t view, ucv16_t target);
UEXPORT bool uv16_starts_with_uv16(uv16_t view, uv16_t target);
UEXPORT bool uv16_starts_with_us16(uv16_t view, const us16_t *target);

#define uv8_starts_with(view, target)        \
    _Generic((target),                       \
        default:       uv8_starts_with_uc8,  \
        const uc8_t *: uv8_starts_with_uz8,  \
        uc8_t *:       uv8_starts_with_uz8,  \
        ucv8_t:        uv8_starts_with_ucv8, \
        uv8_t:         uv8_starts_with_uv8,  \
        const us8_t *: uv8_starts_with_us8,  \
        us8_t *:       uv8_starts_with_us8   \
    )((view), (target))

UEXPORT bool uv8_starts_with_uc8(uv8_t view, uc8_t target);
UEXPORT bool uv8_starts_with_uz8(uv8_t view, const uc8_t *target);
UEXPORT bool uv8_starts_with_uz8n(uv8_t view, const uc8_t *target, size_t target_len);
UEXPORT bool uv8_starts_with_ucv8(uv8_t view, ucv8_t target);
UEXPORT bool uv8_starts_with_uv8(uv8_t view, uv8_t target);
UEXPORT bool uv8_starts_with_us8(uv8_t view, const us8_t *target);

// Ends with

#define uv32_ends_with(view, target)          \
    _Generic((target),                        \
        default:        uv32_ends_with_uc32,  \
        const uc32_t *: uv32_ends_with_uz32,  \
        uc32_t *:       uv32_ends_with_uz32,  \
        ucv32_t:        uv32_ends_with_ucv32, \
        uv32_t:         uv32_ends_with_uv32,  \
        const us32_t *: uv32_ends_with_us32,  \
        us32_t *:       uv32_ends_with_us32   \
    )((view), (target))

UEXPORT bool uv32_ends_with_uc32(uv32_t view, uc32_t target);
UEXPORT bool uv32_ends_with_uz32(uv32_t view, const uc32_t *target);
UEXPORT bool uv32_ends_with_uz32n(uv32_t view, const uc32_t *target, size_t target_len);
UEXPORT bool uv32_ends_with_ucv32(uv32_t view, ucv32_t target);
UEXPORT bool uv32_ends_with_uv32(uv32_t view, uv32_t target);
UEXPORT bool uv32_ends_with_us32(uv32_t view, const us32_t *target);

#define uv16_ends_with(view, target)          \
    _Generic((target),                        \
        default:        uv16_ends_with_uc16,  \
        const uc16_t *: uv16_ends_with_uz16,  \
        uc16_t *:       uv16_ends_with_uz16,  \
        ucv16_t:        uv16_ends_with_ucv16, \
        uv16_t:         uv16_ends_with_uv16,  \
        const us16_t *: uv16_ends_with_us16,  \
        us16_t *:       uv16_ends_with_us16   \
    )((view), (target))

UEXPORT bool uv16_ends_with_uc16(uv16_t view, uc16_t target);
UEXPORT bool uv16_ends_with_uz16(uv16_t view, const uc16_t *target);
UEXPORT bool uv16_ends_with_uz16n(uv16_t view, const uc16_t *target, size_t target_len);
UEXPORT bool uv16_ends_with_ucv16(uv16_t view, ucv16_t target);
UEXPORT bool uv16_ends_with_uv16(uv16_t view, uv16_t target);
UEXPORT bool uv16_ends_with_us16(uv16_t view, const us16_t *target);

#define uv8_ends_with(view, target)        \
    _Generic((target),                     \
        default:       uv8_ends_with_uc8,  \
        const uc8_t *: uv8_ends_with_uz8,  \
        uc8_t *:       uv8_ends_with_uz8,  \
        ucv8_t:        uv8_ends_with_ucv8, \
        uv8_t:         uv8_ends_with_uv8,  \
        const us8_t *: uv8_ends_with_us8,  \
        us8_t *:       uv8_ends_with_us8   \
    )((view), (target))

UEXPORT bool uv8_ends_with_uc8(uv8_t view, uc8_t target);
UEXPORT bool uv8_ends_with_uz8(uv8_t view, const uc8_t *target);
UEXPORT bool uv8_ends_with_uz8n(uv8_t view, const uc8_t *target, size_t target_len);
UEXPORT bool uv8_ends_with_ucv8(uv8_t view, ucv8_t target);
UEXPORT bool uv8_ends_with_uv8(uv8_t view, uv8_t target);
UEXPORT bool uv8_ends_with_us8(uv8_t view, const us8_t *target);

// Iteration

// - Begin

UEXPORT const uc32_t *uv32_cbegin(uv32_t view);
UEXPORT const uc16_t *uv16_cbegin(uv16_t view);
UEXPORT const uc8_t *uv8_cbegin(uv8_t view);

UEXPORT uc32_t *uv32_begin(uv32_t view);
UEXPORT uc16_t *uv16_begin(uv16_t view);
UEXPORT uc8_t *uv8_begin(uv8_t view);

// - Offset

UEXPORT const uc32_t *uv32_coffset(uv32_t view, size_t offset);
UEXPORT const uc16_t *uv16_coffset(uv16_t view, size_t offset);
UEXPORT const uc8_t *uv8_coffset(uv8_t view, size_t offset);

UEXPORT uc32_t *uv32_offset(uv32_t view, size_t offset);
UEXPORT uc16_t *uv16_offset(uv16_t view, size_t offset);
UEXPORT uc8_t *uv8_offset(uv8_t view, size_t offset);

// - End

UEXPORT const uc32_t *uv32_cend(uv32_t view);
UEXPORT const uc16_t *uv16_cend(uv16_t view);
UEXPORT const uc8_t *uv8_cend(uv8_t view);

UEXPORT uc32_t *uv32_end(uv32_t view);
UEXPORT uc16_t *uv16_end(uv16_t view);
UEXPORT uc8_t *uv8_end(uv8_t view);

// Empty

UEXPORT bool uv32_empty(uv32_t view);
UEXPORT bool uv16_empty(uv16_t view);
UEXPORT bool uv8_empty(uv8_t view);

// At

UEXPORT uc32_t uv32_at(uv32_t view, size_t at);
UEXPORT uc16_t uv16_at(uv16_t view, size_t at);
UEXPORT uc8_t uv8_at(uv8_t view, size_t at);

// Chars

UEXPORT const uc32_t *uv32_cchars(uv32_t view);
UEXPORT uc32_t *uv32_chars(uv32_t view);

UEXPORT const uc16_t *uv16_cchars(uv16_t view);
UEXPORT uc16_t *uv16_chars(uv16_t view);

UEXPORT const uc8_t *uv8_cchars(uv8_t view);
UEXPORT uc8_t *uv8_chars(uv8_t view);

UEXPORT void uv32_set_chars(uv32_t *view, uc32_t *chars);
UEXPORT void uv16_set_chars(uv16_t *view, uc16_t *chars);
UEXPORT void uv8_set_chars(uv8_t *view, uc8_t *chars);

// Valid

UEXPORT bool uv32_valid_p(const uv32_t *view);
UEXPORT bool uv32_valid(uv32_t view);

UEXPORT bool uv16_valid_p(const uv16_t *view);
UEXPORT bool uv16_valid(uv16_t view);

UEXPORT bool uv8_valid_p(const uv8_t *view);
UEXPORT bool uv8_valid(uv8_t view);

#endif