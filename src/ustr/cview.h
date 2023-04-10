#ifndef USTR_CVIEW_H
#define USTR_CVIEW_H

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

#define UCV32_CEXPAND(view) ucv32_cchars(view), (view).len
#define UCV16_CEXPAND(view) ucv16_cchars(view), (view).len
#define  UCV8_CEXPAND(view)  ucv8_cchars(view), (view).len

// Creation

// - Generic

#define ucv32_from(from)                  \
    _Generic((from),                      \
        const uc32_t *: ucv32_from_uz32,  \
        uc32_t *:       ucv32_from_uz32,  \
        ucv32_t:        ucv32_from_ucv32, \
        uv32_t:         ucv32_from_uv32,  \
        const us32_t *: ucv32_from_us32,  \
        us32_t *:       ucv32_from_us32,  \
        default:        ucv32_from_bool   \
    )((from))

#define ucv32_from_range(from, begin, len)      \
    _Generic((from),                            \
        const uc32_t *: ucv32_from_uz32_range,  \
        uc32_t *:       ucv32_from_uz32_range,  \
        ucv32_t:        ucv32_from_ucv32_range, \
        uv32_t:         ucv32_from_uv32_range,  \
        const us32_t *: ucv32_from_us32_range,  \
        us32_t *:       ucv32_from_us32_range   \
    )((from), (begin), (len))


#define ucv16_from(from)                  \
    _Generic((from),                      \
        const uc16_t *: ucv16_from_uz16,  \
        uc16_t *:       ucv16_from_uz16,  \
        ucv16_t:        ucv16_from_ucv16, \
        uv16_t:         ucv16_from_uv16,  \
        const us16_t *: ucv16_from_us16,  \
        us16_t *:       ucv16_from_us16,  \
        default:        ucv16_from_bool   \
    )((from))

#define ucv16_from_range(from, begin, len)      \
    _Generic((from),                            \
        const uc16_t *: ucv16_from_uz16_range,  \
        uc16_t *:       ucv16_from_uz16_range,  \
        ucv16_t:        ucv16_from_ucv16_range, \
        uv16_t:         ucv16_from_uv16_range,  \
        const us16_t *: ucv16_from_us16_range,  \
        us16_t *:       ucv16_from_us16_range   \
    )((from), (begin), (len))


#define ucv8_from(from)                \
    _Generic((from),                   \
        const uc8_t *: ucv8_from_uz8,  \
        uc8_t *:       ucv8_from_uz8,  \
        ucv8_t:        ucv8_from_ucv8, \
        uv8_t:         ucv8_from_uv8,  \
        const us8_t *: ucv8_from_us8,  \
        us8_t *:       ucv8_from_us8,  \
        default:       ucv8_from_bool  \
    )((from))

#define ucv8_from_range(from, begin, len)    \
    _Generic((from),                         \
        const uc8_t *: ucv8_from_uz8_range,  \
        uc8_t *:       ucv8_from_uz8_range,  \
        ucv8_t:        ucv8_from_ucv8_range, \
        uv8_t:         ucv8_from_uv8_range,  \
        const us8_t *: ucv8_from_us8_range,  \
        us8_t *:       ucv8_from_us8_range   \
    )((from), (begin), (len))

// - Conversion

UEXPORT ucv32_t ucv32_from_uz32(UNULLABLE const uc32_t *from);
UEXPORT ucv32_t ucv32_from_uz32_range(const uc32_t *from, size_t begin, size_t len);
UEXPORT ucv32_t ucv32_from_uz32n(const uc32_t *from, size_t from_len);
UEXPORT ucv32_t ucv32_from_uz32n_range(const uc32_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT ucv32_t ucv32_from_ucv32(ucv32_t from);
UEXPORT ucv32_t ucv32_from_ucv32_range(ucv32_t from, size_t begin, size_t len);
UEXPORT ucv32_t ucv32_from_uv32(uv32_t from);
UEXPORT ucv32_t ucv32_from_uv32_range(uv32_t from, size_t begin, size_t len);
UEXPORT ucv32_t ucv32_from_us32(const us32_t *from);
UEXPORT ucv32_t ucv32_from_us32_range(const us32_t *from, size_t begin, size_t len);

UEXPORT ucv16_t ucv16_from_uz16(UNULLABLE const uc16_t *from);
UEXPORT ucv16_t ucv16_from_uz16_range(const uc16_t *from, size_t begin, size_t len);
UEXPORT ucv16_t ucv16_from_uz16n(const uc16_t *from, size_t from_len);
UEXPORT ucv16_t ucv16_from_uz16n_range(const uc16_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT ucv16_t ucv16_from_ucv16(ucv16_t from);
UEXPORT ucv16_t ucv16_from_ucv16_range(ucv16_t from, size_t begin, size_t len);
UEXPORT ucv16_t ucv16_from_uv16(uv16_t from);
UEXPORT ucv16_t ucv16_from_uv16_range(uv16_t from, size_t begin, size_t len);
UEXPORT ucv16_t ucv16_from_us16(const us16_t *from);
UEXPORT ucv16_t ucv16_from_us16_range(const us16_t *from, size_t begin, size_t len);

UEXPORT ucv8_t ucv8_from_uz8(UNULLABLE const uc8_t *from);
UEXPORT ucv8_t ucv8_from_uz8_range(const uc8_t *from, size_t begin, size_t len);
UEXPORT ucv8_t ucv8_from_uz8n(const uc8_t *from, size_t from_len);
UEXPORT ucv8_t ucv8_from_uz8n_range(const uc8_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT ucv8_t ucv8_from_ucv8(ucv8_t from);
UEXPORT ucv8_t ucv8_from_ucv8_range(ucv8_t from, size_t begin, size_t len);
UEXPORT ucv8_t ucv8_from_uv8(uv8_t from);
UEXPORT ucv8_t ucv8_from_uv8_range(uv8_t from, size_t begin, size_t len);
UEXPORT ucv8_t ucv8_from_us8(const us8_t *from);
UEXPORT ucv8_t ucv8_from_us8_range(const us8_t *from, size_t begin, size_t len);

// - From bool

UEXPORT ucv32_t ucv32_from_bool(bool from);
UEXPORT ucv32_t ucv32_from_case_bool(ucase_t ca, bool from);
UEXPORT ucv32_t ucv32_from_lower_bool(bool from);
UEXPORT ucv32_t ucv32_from_upper_bool(bool from);

UEXPORT ucv16_t ucv16_from_bool(bool from);
UEXPORT ucv16_t ucv16_from_case_bool(ucase_t ca, bool from);
UEXPORT ucv16_t ucv16_from_lower_bool(bool from);
UEXPORT ucv16_t ucv16_from_upper_bool(bool from);

UEXPORT ucv8_t ucv8_from_bool(bool from);
UEXPORT ucv8_t ucv8_from_case_bool(ucase_t ca, bool from);
UEXPORT ucv8_t ucv8_from_lower_bool(bool from);
UEXPORT ucv8_t ucv8_from_upper_bool(bool from);

// To bytes

UEXPORT size_t ucv32_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, ucv32_t from);
UEXPORT size_t ucv16_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, ucv16_t from);
UEXPORT size_t ucv8_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, ucv8_t from);

// Length

UEXPORT size_t ucv32_len(ucv32_t view);
UEXPORT size_t ucv32_len_n(ucv32_t view, unsigned n);
UEXPORT size_t ucv32_len_32(ucv32_t view);
UEXPORT size_t ucv32_len_16(ucv32_t view);
UEXPORT size_t ucv32_len_8(ucv32_t view);

UEXPORT size_t ucv16_len(ucv16_t view);
UEXPORT size_t ucv16_len_n(ucv16_t view, unsigned n);
UEXPORT size_t ucv16_len_32(ucv16_t view);
UEXPORT size_t ucv16_len_16(ucv16_t view);
UEXPORT size_t ucv16_len_8(ucv16_t view);

UEXPORT size_t ucv8_len(ucv8_t view);
UEXPORT size_t ucv8_len_n(ucv8_t view, unsigned n);
UEXPORT size_t ucv8_len_32(ucv8_t view);
UEXPORT size_t ucv8_len_16(ucv8_t view);
UEXPORT size_t ucv8_len_8(ucv8_t view);


UEXPORT void ucv32_set_len(ucv32_t *view, size_t len);
UEXPORT void ucv16_set_len(ucv16_t *view, size_t len);
UEXPORT void ucv8_set_len(ucv8_t *view, size_t len);


UEXPORT size_t ucv32_add_len(ucv32_t *view, ptrdiff_t delta);
UEXPORT size_t ucv16_add_len(ucv16_t *view, ptrdiff_t delta);
UEXPORT size_t ucv8_add_len(ucv8_t *view, ptrdiff_t delta);

// Compare

#define ucv32_cmp(lhs, rhs)              \
    _Generic((rhs),                      \
        default:        ucv32_cmp_uc32,  \
        const uc32_t *: ucv32_cmp_uz32,  \
        uc32_t *:       ucv32_cmp_uz32,  \
        ucv32_t:        ucv32_cmp_ucv32, \
        uv32_t:         ucv32_cmp_uv32,  \
        const us32_t *: ucv32_cmp_us32,  \
        us32_t *:       ucv32_cmp_us32   \
    )((lhs), (rhs))

UEXPORT int ucv32_cmp_uc32(ucv32_t lhs, uc32_t rhs);
UEXPORT int ucv32_cmp_uz32(ucv32_t lhs, const uc32_t *rhs);
UEXPORT int ucv32_cmp_uz32n(ucv32_t lhs, const uc32_t *rhs, size_t rhs_len);
UEXPORT int ucv32_cmp_ucv32(ucv32_t lhs, ucv32_t rhs);
UEXPORT int ucv32_cmp_uv32(ucv32_t lhs, uv32_t rhs);
UEXPORT int ucv32_cmp_us32(ucv32_t lhs, const us32_t *rhs);

#define ucv16_cmp(lhs, rhs)              \
    _Generic((rhs),                      \
        default:        ucv16_cmp_uc16,  \
        const uc16_t *: ucv16_cmp_uz16,  \
        uc16_t *:       ucv16_cmp_uz16,  \
        ucv16_t:        ucv16_cmp_ucv16, \
        uv16_t:         ucv16_cmp_uv16,  \
        const us16_t *: ucv16_cmp_us16,  \
        us16_t *:       ucv16_cmp_us16   \
    )((lhs), (rhs))

UEXPORT int ucv16_cmp_uc16(ucv16_t lhs, uc16_t rhs);
UEXPORT int ucv16_cmp_uz16(ucv16_t lhs, const uc16_t *rhs);
UEXPORT int ucv16_cmp_uz16n(ucv16_t lhs, const uc16_t *rhs, size_t rhs_len);
UEXPORT int ucv16_cmp_ucv16(ucv16_t lhs, ucv16_t rhs);
UEXPORT int ucv16_cmp_uv16(ucv16_t lhs, uv16_t rhs);
UEXPORT int ucv16_cmp_us16(ucv16_t lhs, const us16_t *rhs);

#define ucv8_cmp(lhs, rhs)            \
    _Generic((rhs),                   \
        default:       ucv8_cmp_uc8,  \
        const uc8_t *: ucv8_cmp_uz8,  \
        uc8_t *:       ucv8_cmp_uz8,  \
        ucv8_t:        ucv8_cmp_ucv8, \
        uv8_t:         ucv8_cmp_uv8,  \
        const us8_t *: ucv8_cmp_us8,  \
        us8_t *:       ucv8_cmp_us8   \
    )((lhs), (rhs))

UEXPORT int ucv8_cmp_uc8(ucv8_t lhs, uc8_t rhs);
UEXPORT int ucv8_cmp_uz8(ucv8_t lhs, const uc8_t *rhs);
UEXPORT int ucv8_cmp_uz8n(ucv8_t lhs, const uc8_t *rhs, size_t rhs_len);
UEXPORT int ucv8_cmp_ucv8(ucv8_t lhs, ucv8_t rhs);
UEXPORT int ucv8_cmp_uv8(ucv8_t lhs, uv8_t rhs);
UEXPORT int ucv8_cmp_us8(ucv8_t lhs, const us8_t *rhs);

// White space

UEXPORT size_t ucv32_wspace_len(ucv32_t view);
UEXPORT size_t ucv16_wspace_len(ucv16_t view);
UEXPORT size_t ucv8_wspace_len(ucv8_t view);

// Trim

UEXPORT size_t ucv32_trim(ucv32_t *view);
UEXPORT size_t ucv32_ltrim(ucv32_t *view);
UEXPORT size_t ucv32_rtrim(ucv32_t *view);

UEXPORT size_t ucv16_trim(ucv16_t *view);
UEXPORT size_t ucv16_ltrim(ucv16_t *view);
UEXPORT size_t ucv16_rtrim(ucv16_t *view);

UEXPORT size_t ucv8_trim(ucv8_t *view);
UEXPORT size_t ucv8_ltrim(ucv8_t *view);
UEXPORT size_t ucv8_rtrim(ucv8_t *view);

// Case change length

UEXPORT size_t ucv8_case_len(ucv8_t view, ucase_t ca);
UEXPORT size_t ucv8_lower_len(ucv8_t view);
UEXPORT size_t ucv8_upper_len(ucv8_t view);

// Split

#define ucv32_new_csplit(view, sep, array)             \
    ucv32_new_csplit_e((view), (sep), (array), (NULL))

#define ucv32_new_csplit_e(view, sep, array, error) \
    _Generic((sep),                                 \
        default:        ucv32_new_csplit_uc32_e,    \
        const uc32_t *: ucv32_new_csplit_uz32_e,    \
        uc32_t *:       ucv32_new_csplit_uz32_e,    \
        ucv32_t:        ucv32_new_csplit_ucv32_e,   \
        uv32_t:         ucv32_new_csplit_uv32_e,    \
        const us32_t *: ucv32_new_csplit_us32_e,    \
        us32_t *:       ucv32_new_csplit_us32_e     \
    )((view), (sep), (array), (error))

#define ucv32_csplit(view, sep, array, array_len) \
    _Generic((sep),                               \
        default:        ucv32_csplit_uc32,        \
        const uc32_t *: ucv32_csplit_uz32,        \
        uc32_t *:       ucv32_csplit_uz32,        \
        ucv32_t:        ucv32_csplit_ucv32,       \
        uv32_t:         ucv32_csplit_uv32,        \
        const us32_t *: ucv32_csplit_us32,        \
        us32_t *:       ucv32_csplit_us32         \
    )((view), (sep), (array), (array_len))

UEXPORT size_t ucv32_new_csplit_uc32(ucv32_t view, uc32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t ucv32_new_csplit_uc32_e(ucv32_t view, uc32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t ucv32_csplit_uc32(ucv32_t view, uc32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t ucv32_new_csplit_uz32(ucv32_t view, const uc32_t *sep, UNULLABLE ucv32_t **array);
UEXPORT size_t ucv32_new_csplit_uz32_e(ucv32_t view, const uc32_t *sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t ucv32_csplit_uz32(ucv32_t view, const uc32_t *sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t ucv32_new_csplit_uz32n(ucv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array);
UEXPORT size_t ucv32_new_csplit_uz32n_e(ucv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t ucv32_csplit_uz32n(ucv32_t view, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t ucv32_new_csplit_ucv32(ucv32_t view, ucv32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t ucv32_new_csplit_ucv32_e(ucv32_t view, ucv32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t ucv32_csplit_ucv32(ucv32_t view, ucv32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t ucv32_new_csplit_uv32(ucv32_t view, uv32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t ucv32_new_csplit_uv32_e(ucv32_t view, uv32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t ucv32_csplit_uv32(ucv32_t view, uv32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t ucv32_new_csplit_us32(ucv32_t view, const us32_t *sep, UNULLABLE ucv32_t **array);
UEXPORT size_t ucv32_new_csplit_us32_e(ucv32_t view, const us32_t *sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t ucv32_csplit_us32(ucv32_t view, const us32_t *sep, UNULLABLE ucv32_t *array, size_t array_len);

#define ucv16_new_csplit(view, sep, array)             \
    ucv16_new_csplit_e((view), (sep), (array), (NULL))

#define ucv16_new_csplit_e(view, sep, array, error) \
    _Generic((sep),                                 \
        default:        ucv16_new_csplit_uc16_e,    \
        const uc16_t *: ucv16_new_csplit_uz16_e,    \
        uc16_t *:       ucv16_new_csplit_uz16_e,    \
        ucv16_t:        ucv16_new_csplit_ucv16_e,   \
        uv16_t:         ucv16_new_csplit_uv16_e,    \
        const us16_t *: ucv16_new_csplit_us16_e,    \
        us16_t *:       ucv16_new_csplit_us16_e     \
    )((view), (sep), (array), (error))

#define ucv16_csplit(view, sep, array, array_len) \
    _Generic((sep),                               \
        default:        ucv16_csplit_uc16,        \
        const uc16_t *: ucv16_csplit_uz16,        \
        uc16_t *:       ucv16_csplit_uz16,        \
        ucv16_t:        ucv16_csplit_ucv16,       \
        uv16_t:         ucv16_csplit_uv16,        \
        const us16_t *: ucv16_csplit_us16,        \
        us16_t *:       ucv16_csplit_us16         \
    )((view), (sep), (array), (array_len))

UEXPORT size_t ucv16_new_csplit_uc16(ucv16_t view, uc16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t ucv16_new_csplit_uc16_e(ucv16_t view, uc16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t ucv16_csplit_uc16(ucv16_t view, uc16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t ucv16_new_csplit_uz16(ucv16_t view, const uc16_t *sep, UNULLABLE ucv16_t **array);
UEXPORT size_t ucv16_new_csplit_uz16_e(ucv16_t view, const uc16_t *sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t ucv16_csplit_uz16(ucv16_t view, const uc16_t *sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t ucv16_new_csplit_uz16n(ucv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array);
UEXPORT size_t ucv16_new_csplit_uz16n_e(ucv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t ucv16_csplit_uz16n(ucv16_t view, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t ucv16_new_csplit_ucv16(ucv16_t view, ucv16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t ucv16_new_csplit_ucv16_e(ucv16_t view, ucv16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t ucv16_csplit_ucv16(ucv16_t view, ucv16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t ucv16_new_csplit_uv16(ucv16_t view, uv16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t ucv16_new_csplit_uv16_e(ucv16_t view, uv16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t ucv16_csplit_uv16(ucv16_t view, uv16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t ucv16_new_csplit_us16(ucv16_t view, const us16_t *sep, UNULLABLE ucv16_t **array);
UEXPORT size_t ucv16_new_csplit_us16_e(ucv16_t view, const us16_t *sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t ucv16_csplit_us16(ucv16_t view, const us16_t *sep, UNULLABLE ucv16_t *array, size_t array_len);

#define ucv8_new_csplit(view, sep, array)             \
    ucv8_new_csplit_e((view), (sep), (array), (NULL))

#define ucv8_new_csplit_e(view, sep, array, error) \
    _Generic((sep),                                \
        default:       ucv8_new_csplit_uc8_e,      \
        const uc8_t *: ucv8_new_csplit_uz8_e,      \
        uc8_t *:       ucv8_new_csplit_uz8_e,      \
        ucv8_t:        ucv8_new_csplit_ucv8_e,     \
        uv8_t:         ucv8_new_csplit_uv8_e,      \
        const us8_t *: ucv8_new_csplit_us8_e,      \
        us8_t *:       ucv8_new_csplit_us8_e       \
    )((view), (sep), (array), (error))

#define ucv8_csplit(view, sep, array, array_len) \
    _Generic((sep),                              \
        default:       ucv8_csplit_uc8,          \
        const uc8_t *: ucv8_csplit_uz8,          \
        uc8_t *:       ucv8_csplit_uz8,          \
        ucv8_t:        ucv8_csplit_ucv8,         \
        uv8_t:         ucv8_csplit_uv8,          \
        const us8_t *: ucv8_csplit_us8,          \
        us8_t *:       ucv8_csplit_us8           \
    )((view), (sep), (array), (array_len))

UEXPORT size_t ucv8_new_csplit_uc8(ucv8_t view, uc8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t ucv8_new_csplit_uc8_e(ucv8_t view, uc8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t ucv8_csplit_uc8(ucv8_t view, uc8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t ucv8_new_csplit_uz8(ucv8_t view, const uc8_t *sep, UNULLABLE ucv8_t **array);
UEXPORT size_t ucv8_new_csplit_uz8_e(ucv8_t view, const uc8_t *sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t ucv8_csplit_uz8(ucv8_t view, const uc8_t *sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t ucv8_new_csplit_uz8n(ucv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array);
UEXPORT size_t ucv8_new_csplit_uz8n_e(ucv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t ucv8_csplit_uz8n(ucv8_t view, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t ucv8_new_csplit_ucv8(ucv8_t view, ucv8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t ucv8_new_csplit_ucv8_e(ucv8_t view, ucv8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t ucv8_csplit_ucv8(ucv8_t view, ucv8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t ucv8_new_csplit_uv8(ucv8_t view, uv8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t ucv8_new_csplit_uv8_e(ucv8_t view, uv8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t ucv8_csplit_uv8(ucv8_t view, uv8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t ucv8_new_csplit_us8(ucv8_t view, const us8_t *sep, UNULLABLE ucv8_t **array);
UEXPORT size_t ucv8_new_csplit_us8_e(ucv8_t view, const us8_t *sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t ucv8_csplit_us8(ucv8_t view, const us8_t *sep, UNULLABLE ucv8_t *array, size_t array_len);

// Contains

#define ucv32_contains(view, target)          \
    _Generic((target),                        \
        default:        ucv32_contains_uc32,  \
        const uc32_t *: ucv32_contains_uz32,  \
        uc32_t *:       ucv32_contains_uz32,  \
        ucv32_t:        ucv32_contains_ucv32, \
        uv32_t:         ucv32_contains_uv32,  \
        const us32_t *: ucv32_contains_us32,  \
        us32_t *:       ucv32_contains_us32   \
    )((view), (target))

UEXPORT bool ucv32_contains_uc32(ucv32_t view, uc32_t target);
UEXPORT bool ucv32_contains_uz32(ucv32_t view, const uc32_t *target);
UEXPORT bool ucv32_contains_uz32n(ucv32_t view, const uc32_t *target, size_t target_len);
UEXPORT bool ucv32_contains_ucv32(ucv32_t view, ucv32_t target);
UEXPORT bool ucv32_contains_uv32(ucv32_t view, uv32_t target);
UEXPORT bool ucv32_contains_us32(ucv32_t view, const us32_t *target);

#define ucv16_contains(view, target)          \
    _Generic((target),                        \
        default:        ucv16_contains_uc16,  \
        const uc16_t *: ucv16_contains_uz16,  \
        uc16_t *:       ucv16_contains_uz16,  \
        ucv16_t:        ucv16_contains_ucv16, \
        uv16_t:         ucv16_contains_uv16,  \
        const us16_t *: ucv16_contains_us16,  \
        us16_t *:       ucv16_contains_us16   \
    )((view), (target))

UEXPORT bool ucv16_contains_uc16(ucv16_t view, uc16_t target);
UEXPORT bool ucv16_contains_uz16(ucv16_t view, const uc16_t *target);
UEXPORT bool ucv16_contains_uz16n(ucv16_t view, const uc16_t *target, size_t target_len);
UEXPORT bool ucv16_contains_ucv16(ucv16_t view, ucv16_t target);
UEXPORT bool ucv16_contains_uv16(ucv16_t view, uv16_t target);
UEXPORT bool ucv16_contains_us16(ucv16_t view, const us16_t *target);

#define ucv8_contains(view, target)        \
    _Generic((target),                     \
        default:       ucv8_contains_uc8,  \
        const uc8_t *: ucv8_contains_uz8,  \
        uc8_t *:       ucv8_contains_uz8,  \
        ucv8_t:        ucv8_contains_ucv8, \
        uv8_t:         ucv8_contains_uv8,  \
        const us8_t *: ucv8_contains_us8,  \
        us8_t *:       ucv8_contains_us8   \
    )((view), (target))

UEXPORT bool ucv8_contains_uc8(ucv8_t view, uc8_t target);
UEXPORT bool ucv8_contains_uz8(ucv8_t view, const uc8_t *target);
UEXPORT bool ucv8_contains_uz8n(ucv8_t view, const uc8_t *target, size_t target_len);
UEXPORT bool ucv8_contains_ucv8(ucv8_t view, ucv8_t target);
UEXPORT bool ucv8_contains_uv8(ucv8_t view, uv8_t target);
UEXPORT bool ucv8_contains_us8(ucv8_t view, const us8_t *target);

// Search

// - Forward

#define ucv32_find(view, target)          \
    _Generic((target),                    \
        default:        ucv32_find_uc32,  \
        const uc32_t *: ucv32_find_uz32,  \
        uc32_t *:       ucv32_find_uz32,  \
        ucv32_t:        ucv32_find_ucv32, \
        uv32_t:         ucv32_find_uv32,  \
        const us32_t *: ucv32_find_us32,  \
        us32_t *:       ucv32_find_us32   \
    )((view), (target))

#define ucv32_find_from(view, target, from)    \
    _Generic((target),                         \
        default:        ucv32_find_uc32_from,  \
        const uc32_t *: ucv32_find_uz32_from,  \
        uc32_t *:       ucv32_find_uz32_from,  \
        ucv32_t:        ucv32_find_ucv32_from, \
        uv32_t:         ucv32_find_uv32_from,  \
        const us32_t *: ucv32_find_us32_from,  \
        us32_t *:       ucv32_find_us32_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t ucv32_find_uc32(ucv32_t view, uc32_t target);
UEXPORT ptrdiff_t ucv32_find_uc32_from(ucv32_t view, uc32_t target, size_t from);
UEXPORT ptrdiff_t ucv32_find_uz32(ucv32_t view, const uc32_t *target);
UEXPORT ptrdiff_t ucv32_find_uz32_from(ucv32_t view, const uc32_t *target, size_t from);
UEXPORT ptrdiff_t ucv32_find_uz32n(ucv32_t view, const uc32_t *target, size_t target_len);
UEXPORT ptrdiff_t ucv32_find_uz32n_from(ucv32_t view, const uc32_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t ucv32_find_ucv32(ucv32_t view, ucv32_t target);
UEXPORT ptrdiff_t ucv32_find_ucv32_from(ucv32_t view, ucv32_t target, size_t from);
UEXPORT ptrdiff_t ucv32_find_uv32(ucv32_t view, uv32_t target);
UEXPORT ptrdiff_t ucv32_find_uv32_from(ucv32_t view, uv32_t target, size_t from);
UEXPORT ptrdiff_t ucv32_find_us32(ucv32_t view, const us32_t *target);
UEXPORT ptrdiff_t ucv32_find_us32_from(ucv32_t view, const us32_t *target, size_t from);

#define ucv16_find(view, target)          \
    _Generic((target),                    \
        default:        ucv16_find_uc16,  \
        const uc16_t *: ucv16_find_uz16,  \
        uc16_t *:       ucv16_find_uz16,  \
        ucv16_t:        ucv16_find_ucv16, \
        uv16_t:         ucv16_find_uv16,  \
        const us16_t *: ucv16_find_us16,  \
        us16_t *:       ucv16_find_us16   \
    )((view), (target))

#define ucv16_find_from(view, target, from)    \
    _Generic((target),                         \
        default:        ucv16_find_uc16_from,  \
        const uc16_t *: ucv16_find_uz16_from,  \
        uc16_t *:       ucv16_find_uz16_from,  \
        ucv16_t:        ucv16_find_ucv16_from, \
        uv16_t:         ucv16_find_uv16_from,  \
        const us16_t *: ucv16_find_us16_from,  \
        us16_t *:       ucv16_find_us16_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t ucv16_find_uc16(ucv16_t view, uc16_t target);
UEXPORT ptrdiff_t ucv16_find_uc16_from(ucv16_t view, uc16_t target, size_t from);
UEXPORT ptrdiff_t ucv16_find_uz16(ucv16_t view, const uc16_t *target);
UEXPORT ptrdiff_t ucv16_find_uz16_from(ucv16_t view, const uc16_t *target, size_t from);
UEXPORT ptrdiff_t ucv16_find_uz16n(ucv16_t view, const uc16_t *target, size_t target_len);
UEXPORT ptrdiff_t ucv16_find_uz16n_from(ucv16_t view, const uc16_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t ucv16_find_ucv16(ucv16_t view, ucv16_t target);
UEXPORT ptrdiff_t ucv16_find_ucv16_from(ucv16_t view, ucv16_t target, size_t from);
UEXPORT ptrdiff_t ucv16_find_uv16(ucv16_t view, uv16_t target);
UEXPORT ptrdiff_t ucv16_find_uv16_from(ucv16_t view, uv16_t target, size_t from);
UEXPORT ptrdiff_t ucv16_find_us16(ucv16_t view, const us16_t *target);
UEXPORT ptrdiff_t ucv16_find_us16_from(ucv16_t view, const us16_t *target, size_t from);

#define ucv8_find(view, target)        \
    _Generic((target),                 \
        default:       ucv8_find_uc8,  \
        const uc8_t *: ucv8_find_uz8,  \
        uc8_t *:       ucv8_find_uz8,  \
        ucv8_t:        ucv8_find_ucv8, \
        uv8_t:         ucv8_find_uv8,  \
        const us8_t *: ucv8_find_us8,  \
        us8_t *:       ucv8_find_us8   \
    )((view), (target))

#define ucv8_find_from(view, target, from)  \
    _Generic((target),                      \
        default:       ucv8_find_uc8_from,  \
        const uc8_t *: ucv8_find_uz8_from,  \
        uc8_t *:       ucv8_find_uz8_from,  \
        ucv8_t:        ucv8_find_ucv8_from, \
        uv8_t:         ucv8_find_uv8_from,  \
        const us8_t *: ucv8_find_us8_from,  \
        us8_t *:       ucv8_find_us8_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t ucv8_find_uc8(ucv8_t view, uc8_t target);
UEXPORT ptrdiff_t ucv8_find_uc8_from(ucv8_t view, uc8_t target, size_t from);
UEXPORT ptrdiff_t ucv8_find_uz8(ucv8_t view, const uc8_t *target);
UEXPORT ptrdiff_t ucv8_find_uz8_from(ucv8_t view, const uc8_t *target, size_t from);
UEXPORT ptrdiff_t ucv8_find_uz8n(ucv8_t view, const uc8_t *target, size_t target_len);
UEXPORT ptrdiff_t ucv8_find_uz8n_from(ucv8_t view, const uc8_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t ucv8_find_ucv8(ucv8_t view, ucv8_t target);
UEXPORT ptrdiff_t ucv8_find_ucv8_from(ucv8_t view, ucv8_t target, size_t from);
UEXPORT ptrdiff_t ucv8_find_uv8(ucv8_t view, uv8_t target);
UEXPORT ptrdiff_t ucv8_find_uv8_from(ucv8_t view, uv8_t target, size_t from);
UEXPORT ptrdiff_t ucv8_find_us8(ucv8_t view, const us8_t *target);
UEXPORT ptrdiff_t ucv8_find_us8_from(ucv8_t view, const us8_t *target, size_t from);

// - Backward

#define ucv32_rfind(view, target)          \
    _Generic((target),                     \
        default:        ucv32_rfind_uc32,  \
        const uc32_t *: ucv32_rfind_uz32,  \
        uc32_t *:       ucv32_rfind_uz32,  \
        ucv32_t:        ucv32_rfind_ucv32, \
        uv32_t:         ucv32_rfind_uv32,  \
        const us32_t *: ucv32_rfind_us32,  \
        us32_t *:       ucv32_rfind_us32   \
    )((view), (target))

#define ucv32_rfind_from(view, target, from)    \
    _Generic((target),                          \
        default:        ucv32_rfind_uc32_from,  \
        const uc32_t *: ucv32_rfind_uz32_from,  \
        uc32_t *:       ucv32_rfind_uz32_from,  \
        ucv32_t:        ucv32_rfind_ucv32_from, \
        uv32_t:         ucv32_rfind_uv32_from,  \
        const us32_t *: ucv32_rfind_us32_from,  \
        us32_t *:       ucv32_rfind_us32_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t ucv32_rfind_uc32(ucv32_t view, uc32_t target);
UEXPORT ptrdiff_t ucv32_rfind_uc32_from(ucv32_t view, uc32_t target, size_t from);
UEXPORT ptrdiff_t ucv32_rfind_uz32(ucv32_t view, const uc32_t *target);
UEXPORT ptrdiff_t ucv32_rfind_uz32_from(ucv32_t view, const uc32_t *target, size_t from);
UEXPORT ptrdiff_t ucv32_rfind_uz32n(ucv32_t view, const uc32_t *target, size_t target_len);
UEXPORT ptrdiff_t ucv32_rfind_uz32n_from(ucv32_t view, const uc32_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t ucv32_rfind_ucv32(ucv32_t view, ucv32_t target);
UEXPORT ptrdiff_t ucv32_rfind_ucv32_from(ucv32_t view, ucv32_t target, size_t from);
UEXPORT ptrdiff_t ucv32_rfind_uv32(ucv32_t view, uv32_t target);
UEXPORT ptrdiff_t ucv32_rfind_uv32_from(ucv32_t view, uv32_t target, size_t from);
UEXPORT ptrdiff_t ucv32_rfind_us32(ucv32_t view, const us32_t *target);
UEXPORT ptrdiff_t ucv32_rfind_us32_from(ucv32_t view, const us32_t *target, size_t from);

#define ucv16_rfind(view, target)          \
    _Generic((target),                     \
        default:        ucv16_rfind_uc16,  \
        const uc16_t *: ucv16_rfind_uz16,  \
        uc16_t *:       ucv16_rfind_uz16,  \
        ucv16_t:        ucv16_rfind_ucv16, \
        uv16_t:         ucv16_rfind_uv16,  \
        const us16_t *: ucv16_rfind_us16,  \
        us16_t *:       ucv16_rfind_us16   \
    )((view), (target))

#define ucv16_rfind_from(view, target, from)    \
    _Generic((target),                          \
        default:        ucv16_rfind_uc16_from,  \
        const uc16_t *: ucv16_rfind_uz16_from,  \
        uc16_t *:       ucv16_rfind_uz16_from,  \
        ucv16_t:        ucv16_rfind_ucv16_from, \
        uv16_t:         ucv16_rfind_uv16_from,  \
        const us16_t *: ucv16_rfind_us16_from,  \
        us16_t *:       ucv16_rfind_us16_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t ucv16_rfind_uc16(ucv16_t view, uc16_t target);
UEXPORT ptrdiff_t ucv16_rfind_uc16_from(ucv16_t view, uc16_t target, size_t from);
UEXPORT ptrdiff_t ucv16_rfind_uz16(ucv16_t view, const uc16_t *target);
UEXPORT ptrdiff_t ucv16_rfind_uz16_from(ucv16_t view, const uc16_t *target, size_t from);
UEXPORT ptrdiff_t ucv16_rfind_uz16n(ucv16_t view, const uc16_t *target, size_t target_len);
UEXPORT ptrdiff_t ucv16_rfind_uz16n_from(ucv16_t view, const uc16_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t ucv16_rfind_ucv16(ucv16_t view, ucv16_t target);
UEXPORT ptrdiff_t ucv16_rfind_ucv16_from(ucv16_t view, ucv16_t target, size_t from);
UEXPORT ptrdiff_t ucv16_rfind_uv16(ucv16_t view, uv16_t target);
UEXPORT ptrdiff_t ucv16_rfind_uv16_from(ucv16_t view, uv16_t target, size_t from);
UEXPORT ptrdiff_t ucv16_rfind_us16(ucv16_t view, const us16_t *target);
UEXPORT ptrdiff_t ucv16_rfind_us16_from(ucv16_t view, const us16_t *target, size_t from);

#define ucv8_rfind(view, target)        \
    _Generic((target),                  \
        default:       ucv8_rfind_uc8,  \
        const uc8_t *: ucv8_rfind_uz8,  \
        uc8_t *:       ucv8_rfind_uz8,  \
        ucv8_t:        ucv8_rfind_ucv8, \
        uv8_t:         ucv8_rfind_uv8,  \
        const us8_t *: ucv8_rfind_us8,  \
        us8_t *:       ucv8_rfind_us8   \
    )((view), (target))

#define ucv8_rfind_from(view, target, from)  \
    _Generic((target),                       \
        default:       ucv8_rfind_uc8_from,  \
        const uc8_t *: ucv8_rfind_uz8_from,  \
        uc8_t *:       ucv8_rfind_uz8_from,  \
        ucv8_t:        ucv8_rfind_ucv8_from, \
        uv8_t:         ucv8_rfind_uv8_from,  \
        const us8_t *: ucv8_rfind_us8_from,  \
        us8_t *:       ucv8_rfind_us8_from   \
    )((view), (target), (from))

UEXPORT ptrdiff_t ucv8_rfind_uc8(ucv8_t view, uc8_t target);
UEXPORT ptrdiff_t ucv8_rfind_uc8_from(ucv8_t view, uc8_t target, size_t from);
UEXPORT ptrdiff_t ucv8_rfind_uz8(ucv8_t view, const uc8_t *target);
UEXPORT ptrdiff_t ucv8_rfind_uz8_from(ucv8_t view, const uc8_t *target, size_t from);
UEXPORT ptrdiff_t ucv8_rfind_uz8n(ucv8_t view, const uc8_t *target, size_t target_len);
UEXPORT ptrdiff_t ucv8_rfind_uz8n_from(ucv8_t view, const uc8_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t ucv8_rfind_ucv8(ucv8_t view, ucv8_t target);
UEXPORT ptrdiff_t ucv8_rfind_ucv8_from(ucv8_t view, ucv8_t target, size_t from);
UEXPORT ptrdiff_t ucv8_rfind_uv8(ucv8_t view, uv8_t target);
UEXPORT ptrdiff_t ucv8_rfind_uv8_from(ucv8_t view, uv8_t target, size_t from);
UEXPORT ptrdiff_t ucv8_rfind_us8(ucv8_t view, const us8_t *target);
UEXPORT ptrdiff_t ucv8_rfind_us8_from(ucv8_t view, const us8_t *target, size_t from);

// Replaced length

#define ucv32_replaced_len(view, from, to)                  \
    _Generic((from),                                        \
        default: _Generic((to),                             \
            default:        ucv32_replaced_len_uc32_uc32,   \
            const uc32_t *: ucv32_replaced_len_uc32_uz32,   \
            uc32_t *:       ucv32_replaced_len_uc32_uz32,   \
            ucv32_t:        ucv32_replaced_len_uc32_ucv32,  \
            uv32_t:         ucv32_replaced_len_uc32_uv32,   \
            const us32_t *: ucv32_replaced_len_uc32_us32,   \
            us32_t *:       ucv32_replaced_len_uc32_us32    \
        ),                                                  \
        const uc32_t *: _Generic((to),                      \
            default:        ucv32_replaced_len_uz32_uc32,   \
            const uc32_t *: ucv32_replaced_len_uz32_uz32,   \
            uc32_t *:       ucv32_replaced_len_uz32_uz32,   \
            ucv32_t:        ucv32_replaced_len_uz32_ucv32,  \
            uv32_t:         ucv32_replaced_len_uz32_uv32,   \
            const us32_t *: ucv32_replaced_len_uz32_us32,   \
            us32_t *:       ucv32_replaced_len_uz32_us32    \
        ),                                                  \
        uc32_t *: _Generic((to),                            \
            default:        ucv32_replaced_len_uz32_uc32,   \
            const uc32_t *: ucv32_replaced_len_uz32_uz32,   \
            uc32_t *:       ucv32_replaced_len_uz32_uz32,   \
            ucv32_t:        ucv32_replaced_len_uz32_ucv32,  \
            uv32_t:         ucv32_replaced_len_uz32_uv32,   \
            const us32_t *: ucv32_replaced_len_uz32_us32,   \
            us32_t *:       ucv32_replaced_len_uz32_us32    \
        ),                                                  \
        ucv32_t: _Generic((to),                             \
            default:        ucv32_replaced_len_ucv32_uc32,  \
            const uc32_t *: ucv32_replaced_len_ucv32_uz32,  \
            uc32_t *:       ucv32_replaced_len_ucv32_uz32,  \
            ucv32_t:        ucv32_replaced_len_ucv32_ucv32, \
            uv32_t:         ucv32_replaced_len_ucv32_uv32,  \
            const us32_t *: ucv32_replaced_len_ucv32_us32,  \
            us32_t *:       ucv32_replaced_len_ucv32_us32   \
        ),                                                 \
        uv32_t: _Generic((to),                             \
            default:        ucv32_replaced_len_uv32_uc32,   \
            const uc32_t *: ucv32_replaced_len_uv32_uz32,   \
            uc32_t *:       ucv32_replaced_len_uv32_uz32,   \
            ucv32_t:        ucv32_replaced_len_uv32_ucv32,  \
            uv32_t:         ucv32_replaced_len_uv32_uv32,   \
            const us32_t *: ucv32_replaced_len_uv32_us32,   \
            us32_t *:       ucv32_replaced_len_uv32_us32    \
        ),                                                  \
        const us32_t *: _Generic((to),                      \
            default:        ucv32_replaced_len_us32_uc32,   \
            const uc32_t *: ucv32_replaced_len_us32_uz32,   \
            uc32_t *:       ucv32_replaced_len_us32_uz32,   \
            ucv32_t:        ucv32_replaced_len_us32_ucv32,  \
            uv32_t:         ucv32_replaced_len_us32_uv32,   \
            const us32_t *: ucv32_replaced_len_us32_us32,   \
            us32_t *:       ucv32_replaced_len_us32_us32    \
        )                                                   \
        us32_t *: _Generic((to),                            \
            default:        ucv32_replaced_len_us32_uc32,   \
            const uc32_t *: ucv32_replaced_len_us32_uz32,   \
            uc32_t *:       ucv32_replaced_len_us32_uz32,   \
            ucv32_t:        ucv32_replaced_len_us32_ucv32,  \
            uv32_t:         ucv32_replaced_len_us32_uv32,   \
            const us32_t *: ucv32_replaced_len_us32_us32,   \
            us32_t *:       ucv32_replaced_len_us32_us32    \
        )                                                   \
    )((view), (from), (to))

UEXPORT size_t ucv32_replaced_len_uc32_uz32(ucv32_t view, uc32_t from, const uc32_t *to);
UEXPORT size_t ucv32_replaced_len_uc32_uz32n(ucv32_t view, uc32_t from, size_t to_len);
UEXPORT size_t ucv32_replaced_len_uc32_ucv32(ucv32_t view, uc32_t from, ucv32_t to);
UEXPORT size_t ucv32_replaced_len_uc32_uv32(ucv32_t view, uc32_t from, uv32_t to);
UEXPORT size_t ucv32_replaced_len_uc32_us32(ucv32_t view, uc32_t from, const us32_t *to);

UEXPORT size_t ucv32_replaced_len_uz32_uc32(ucv32_t view, const uc32_t *from, uc32_t to);
UEXPORT size_t ucv32_replaced_len_uz32_uz32(ucv32_t view, const uc32_t *from, const uc32_t *to);
UEXPORT size_t ucv32_replaced_len_uz32_uz32n(ucv32_t view, const uc32_t *from, size_t to_len);
UEXPORT size_t ucv32_replaced_len_uz32_ucv32(ucv32_t view, const uc32_t *from, ucv32_t to);
UEXPORT size_t ucv32_replaced_len_uz32_uv32(ucv32_t view, const uc32_t *from, uv32_t to);
UEXPORT size_t ucv32_replaced_len_uz32_us32(ucv32_t view, const uc32_t *from, const us32_t *to);

UEXPORT size_t ucv32_replaced_len_uz32n_uc32(ucv32_t view, const uc32_t *from, size_t from_len, uc32_t to);
UEXPORT size_t ucv32_replaced_len_uz32n_uz32(ucv32_t view, const uc32_t *from, size_t from_len, const uc32_t *to);
UEXPORT size_t ucv32_replaced_len_uz32n_uz32n(ucv32_t view, const uc32_t *from, size_t from_len, size_t to_len);
UEXPORT size_t ucv32_replaced_len_uz32n_ucv32(ucv32_t view, const uc32_t *from, size_t from_len, ucv32_t to);
UEXPORT size_t ucv32_replaced_len_uz32n_uv32(ucv32_t view, const uc32_t *from, size_t from_len, uv32_t to);
UEXPORT size_t ucv32_replaced_len_uz32n_us32(ucv32_t view, const uc32_t *from, size_t from_len, const us32_t *to);

UEXPORT size_t ucv32_replaced_len_ucv32_uc32(ucv32_t view, ucv32_t from, uc32_t to);
UEXPORT size_t ucv32_replaced_len_ucv32_uz32(ucv32_t view, ucv32_t from, const uc32_t *to);
UEXPORT size_t ucv32_replaced_len_ucv32_uz32n(ucv32_t view, ucv32_t from, size_t to_len);
UEXPORT size_t ucv32_replaced_len_ucv32_ucv32(ucv32_t view, ucv32_t from, ucv32_t to);
UEXPORT size_t ucv32_replaced_len_ucv32_uv32(ucv32_t view, ucv32_t from, uv32_t to);
UEXPORT size_t ucv32_replaced_len_ucv32_us32(ucv32_t view, ucv32_t from, const us32_t *to);

UEXPORT size_t ucv32_replaced_len_uv32_uc32(ucv32_t view, uv32_t from, uc32_t to);
UEXPORT size_t ucv32_replaced_len_uv32_uz32(ucv32_t view, uv32_t from, const uc32_t *to);
UEXPORT size_t ucv32_replaced_len_uv32_uz32n(ucv32_t view, uv32_t from, size_t to_len);
UEXPORT size_t ucv32_replaced_len_uv32_ucv32(ucv32_t view, uv32_t from, ucv32_t to);
UEXPORT size_t ucv32_replaced_len_uv32_uv32(ucv32_t view, uv32_t from, uv32_t to);
UEXPORT size_t ucv32_replaced_len_uv32_us32(ucv32_t view, uv32_t from, const us32_t *to);

UEXPORT size_t ucv32_replaced_len_us32_uc32(ucv32_t view, const us32_t *from, uc32_t to);
UEXPORT size_t ucv32_replaced_len_us32_uz32(ucv32_t view, const us32_t *from, const uc32_t *to);
UEXPORT size_t ucv32_replaced_len_us32_uz32n(ucv32_t view, const us32_t *from, size_t to_len);
UEXPORT size_t ucv32_replaced_len_us32_ucv32(ucv32_t view, const us32_t *from, ucv32_t to);
UEXPORT size_t ucv32_replaced_len_us32_uv32(ucv32_t view, const us32_t *from, uv32_t to);
UEXPORT size_t ucv32_replaced_len_us32_us32(ucv32_t view, const us32_t *from, const us32_t *to);

#define ucv16_replaced_len(view, from, to)                  \
    _Generic((from),                                        \
        default: _Generic((to),                             \
            default:        ucv16_replaced_len_uc16_uc16,   \
            const uc16_t *: ucv16_replaced_len_uc16_uz16,   \
            uc16_t *:       ucv16_replaced_len_uc16_uz16,   \
            ucv16_t:        ucv16_replaced_len_uc16_ucv16,  \
            uv16_t:         ucv16_replaced_len_uc16_uv16,   \
            const us16_t *: ucv16_replaced_len_uc16_us16,   \
            us16_t *:       ucv16_replaced_len_uc16_us16    \
        ),                                                  \
        const uc16_t *: _Generic((to),                      \
            default:        ucv16_replaced_len_uz16_uc16,   \
            const uc16_t *: ucv16_replaced_len_uz16_uz16,   \
            uc16_t *:       ucv16_replaced_len_uz16_uz16,   \
            ucv16_t:        ucv16_replaced_len_uz16_ucv16,  \
            uv16_t:         ucv16_replaced_len_uz16_uv16,   \
            const us16_t *: ucv16_replaced_len_uz16_us16,   \
            us16_t *:       ucv16_replaced_len_uz16_us16    \
        ),                                                  \
        uc16_t *: _Generic((to),                            \
            default:        ucv16_replaced_len_uz16_uc16,   \
            const uc16_t *: ucv16_replaced_len_uz16_uz16,   \
            uc16_t *:       ucv16_replaced_len_uz16_uz16,   \
            ucv16_t:        ucv16_replaced_len_uz16_ucv16,  \
            uv16_t:         ucv16_replaced_len_uz16_uv16,   \
            const us16_t *: ucv16_replaced_len_uz16_us16,   \
            us16_t *:       ucv16_replaced_len_uz16_us16    \
        ),                                                  \
        ucv16_t: _Generic((to),                             \
            default:        ucv16_replaced_len_ucv16_uc16,  \
            const uc16_t *: ucv16_replaced_len_ucv16_uz16,  \
            uc16_t *:       ucv16_replaced_len_ucv16_uz16,  \
            ucv16_t:        ucv16_replaced_len_ucv16_ucv16, \
            uv16_t:         ucv16_replaced_len_ucv16_uv16,  \
            const us16_t *: ucv16_replaced_len_ucv16_us16,  \
            us16_t *:       ucv16_replaced_len_ucv16_us16   \
        ),                                                 \
        uv16_t: _Generic((to),                             \
            default:        ucv16_replaced_len_uv16_uc16,   \
            const uc16_t *: ucv16_replaced_len_uv16_uz16,   \
            uc16_t *:       ucv16_replaced_len_uv16_uz16,   \
            ucv16_t:        ucv16_replaced_len_uv16_ucv16,  \
            uv16_t:         ucv16_replaced_len_uv16_uv16,   \
            const us16_t *: ucv16_replaced_len_uv16_us16,   \
            us16_t *:       ucv16_replaced_len_uv16_us16    \
        ),                                                  \
        const us16_t *: _Generic((to),                      \
            default:        ucv16_replaced_len_us16_uc16,   \
            const uc16_t *: ucv16_replaced_len_us16_uz16,   \
            uc16_t *:       ucv16_replaced_len_us16_uz16,   \
            ucv16_t:        ucv16_replaced_len_us16_ucv16,  \
            uv16_t:         ucv16_replaced_len_us16_uv16,   \
            const us16_t *: ucv16_replaced_len_us16_us16,   \
            us16_t *:       ucv16_replaced_len_us16_us16    \
        )                                                   \
        us16_t *: _Generic((to),                            \
            default:        ucv16_replaced_len_us16_uc16,   \
            const uc16_t *: ucv16_replaced_len_us16_uz16,   \
            uc16_t *:       ucv16_replaced_len_us16_uz16,   \
            ucv16_t:        ucv16_replaced_len_us16_ucv16,  \
            uv16_t:         ucv16_replaced_len_us16_uv16,   \
            const us16_t *: ucv16_replaced_len_us16_us16,   \
            us16_t *:       ucv16_replaced_len_us16_us16    \
        )                                                   \
    )((view), (from), (to))

UEXPORT size_t ucv16_replaced_len_uc16_uz16(ucv16_t view, uc16_t from, const uc16_t *to);
UEXPORT size_t ucv16_replaced_len_uc16_uz16n(ucv16_t view, uc16_t from, size_t to_len);
UEXPORT size_t ucv16_replaced_len_uc16_ucv16(ucv16_t view, uc16_t from, ucv16_t to);
UEXPORT size_t ucv16_replaced_len_uc16_uv16(ucv16_t view, uc16_t from, uv16_t to);
UEXPORT size_t ucv16_replaced_len_uc16_us16(ucv16_t view, uc16_t from, const us16_t *to);

UEXPORT size_t ucv16_replaced_len_uz16_uc16(ucv16_t view, const uc16_t *from, uc16_t to);
UEXPORT size_t ucv16_replaced_len_uz16_uz16(ucv16_t view, const uc16_t *from, const uc16_t *to);
UEXPORT size_t ucv16_replaced_len_uz16_uz16n(ucv16_t view, const uc16_t *from, size_t to_len);
UEXPORT size_t ucv16_replaced_len_uz16_ucv16(ucv16_t view, const uc16_t *from, ucv16_t to);
UEXPORT size_t ucv16_replaced_len_uz16_uv16(ucv16_t view, const uc16_t *from, uv16_t to);
UEXPORT size_t ucv16_replaced_len_uz16_us16(ucv16_t view, const uc16_t *from, const us16_t *to);

UEXPORT size_t ucv16_replaced_len_uz16n_uc16(ucv16_t view, const uc16_t *from, size_t from_len, uc16_t to);
UEXPORT size_t ucv16_replaced_len_uz16n_uz16(ucv16_t view, const uc16_t *from, size_t from_len, const uc16_t *to);
UEXPORT size_t ucv16_replaced_len_uz16n_uz16n(ucv16_t view, const uc16_t *from, size_t from_len, size_t to_len);
UEXPORT size_t ucv16_replaced_len_uz16n_ucv16(ucv16_t view, const uc16_t *from, size_t from_len, ucv16_t to);
UEXPORT size_t ucv16_replaced_len_uz16n_uv16(ucv16_t view, const uc16_t *from, size_t from_len, uv16_t to);
UEXPORT size_t ucv16_replaced_len_uz16n_us16(ucv16_t view, const uc16_t *from, size_t from_len, const us16_t *to);

UEXPORT size_t ucv16_replaced_len_ucv16_uc16(ucv16_t view, ucv16_t from, uc16_t to);
UEXPORT size_t ucv16_replaced_len_ucv16_uz16(ucv16_t view, ucv16_t from, const uc16_t *to);
UEXPORT size_t ucv16_replaced_len_ucv16_uz16n(ucv16_t view, ucv16_t from, size_t to_len);
UEXPORT size_t ucv16_replaced_len_ucv16_ucv16(ucv16_t view, ucv16_t from, ucv16_t to);
UEXPORT size_t ucv16_replaced_len_ucv16_uv16(ucv16_t view, ucv16_t from, uv16_t to);
UEXPORT size_t ucv16_replaced_len_ucv16_us16(ucv16_t view, ucv16_t from, const us16_t *to);

UEXPORT size_t ucv16_replaced_len_uv16_uc16(ucv16_t view, uv16_t from, uc16_t to);
UEXPORT size_t ucv16_replaced_len_uv16_uz16(ucv16_t view, uv16_t from, const uc16_t *to);
UEXPORT size_t ucv16_replaced_len_uv16_uz16n(ucv16_t view, uv16_t from, size_t to_len);
UEXPORT size_t ucv16_replaced_len_uv16_ucv16(ucv16_t view, uv16_t from, ucv16_t to);
UEXPORT size_t ucv16_replaced_len_uv16_uv16(ucv16_t view, uv16_t from, uv16_t to);
UEXPORT size_t ucv16_replaced_len_uv16_us16(ucv16_t view, uv16_t from, const us16_t *to);

UEXPORT size_t ucv16_replaced_len_us16_uc16(ucv16_t view, const us16_t *from, uc16_t to);
UEXPORT size_t ucv16_replaced_len_us16_uz16(ucv16_t view, const us16_t *from, const uc16_t *to);
UEXPORT size_t ucv16_replaced_len_us16_uz16n(ucv16_t view, const us16_t *from, size_t to_len);
UEXPORT size_t ucv16_replaced_len_us16_ucv16(ucv16_t view, const us16_t *from, ucv16_t to);
UEXPORT size_t ucv16_replaced_len_us16_uv16(ucv16_t view, const us16_t *from, uv16_t to);
UEXPORT size_t ucv16_replaced_len_us16_us16(ucv16_t view, const us16_t *from, const us16_t *to);

#define ucv8_replaced_len(view, from, to)               \
    _Generic((from),                                    \
        default: _Generic((to),                         \
            default:       ucv8_replaced_len_uc8_uc8,   \
            const uc8_t *: ucv8_replaced_len_uc8_uz8,   \
            uc8_t *:       ucv8_replaced_len_uc8_uz8,   \
            ucv8_t:        ucv8_replaced_len_uc8_ucv8,  \
            uv8_t:         ucv8_replaced_len_uc8_uv8,   \
            const us8_t *: ucv8_replaced_len_uc8_us8,   \
            us8_t *:       ucv8_replaced_len_uc8_us8    \
        ),                                              \
        const uc8_t *: _Generic((to),                   \
            default:       ucv8_replaced_len_uz8_uc8,   \
            const uc8_t *: ucv8_replaced_len_uz8_uz8,   \
            uc8_t *:       ucv8_replaced_len_uz8_uz8,   \
            ucv8_t:        ucv8_replaced_len_uz8_ucv8,  \
            uv8_t:         ucv8_replaced_len_uz8_uv8,   \
            const us8_t *: ucv8_replaced_len_uz8_us8,   \
            us8_t *:       ucv8_replaced_len_uz8_us8    \
        ),                                              \
        uc8_t *: _Generic((to),                         \
            default:       ucv8_replaced_len_uz8_uc8,   \
            const uc8_t *: ucv8_replaced_len_uz8_uz8,   \
            uc8_t *:       ucv8_replaced_len_uz8_uz8,   \
            ucv8_t:        ucv8_replaced_len_uz8_ucv8,  \
            uv8_t:         ucv8_replaced_len_uz8_uv8,   \
            const us8_t *: ucv8_replaced_len_uz8_us8,   \
            us8_t *:       ucv8_replaced_len_uz8_us8    \
        ),                                              \
        ucv8_t: _Generic((to),                          \
            default:       ucv8_replaced_len_ucv8_uc8,  \
            const uc8_t *: ucv8_replaced_len_ucv8_uz8,  \
            uc8_t *:       ucv8_replaced_len_ucv8_uz8,  \
            ucv8_t:        ucv8_replaced_len_ucv8_ucv8, \
            uv8_t:         ucv8_replaced_len_ucv8_uv8,  \
            const us8_t *: ucv8_replaced_len_ucv8_us8,  \
            us8_t *:       ucv8_replaced_len_ucv8_us8   \
        ),                                              \
        uv8_t: _Generic((to),                           \
            default:       ucv8_replaced_len_uv8_uc8,   \
            const uc8_t *: ucv8_replaced_len_uv8_uz8,   \
            uc8_t *:       ucv8_replaced_len_uv8_uz8,   \
            ucv8_t:        ucv8_replaced_len_uv8_ucv8,  \
            uv8_t:         ucv8_replaced_len_uv8_uv8,   \
            const us8_t *: ucv8_replaced_len_uv8_us8,   \
            us8_t *:       ucv8_replaced_len_uv8_us8    \
        ),                                              \
        const us8_t *: _Generic((to),                   \
            default:       ucv8_replaced_len_us8_uc8,   \
            const uc8_t *: ucv8_replaced_len_us8_uz8,   \
            uc8_t *:       ucv8_replaced_len_us8_uz8,   \
            ucv8_t:        ucv8_replaced_len_us8_ucv8,  \
            uv8_t:         ucv8_replaced_len_us8_uv8,   \
            const us8_t *: ucv8_replaced_len_us8_us8,   \
            us8_t *:       ucv8_replaced_len_us8_us8    \
        )                                               \
        us8_t *: _Generic((to),                         \
            default:       ucv8_replaced_len_us8_uc8,   \
            const uc8_t *: ucv8_replaced_len_us8_uz8,   \
            uc8_t *:       ucv8_replaced_len_us8_uz8,   \
            ucv8_t:        ucv8_replaced_len_us8_ucv8,  \
            uv8_t:         ucv8_replaced_len_us8_uv8,   \
            const us8_t *: ucv8_replaced_len_us8_us8,   \
            us8_t *:       ucv8_replaced_len_us8_us8    \
        )                                               \
    )((view), (from), (to))

UEXPORT size_t ucv8_replaced_len_uc8_uz8(ucv8_t view, uc8_t from, const uc8_t *to);
UEXPORT size_t ucv8_replaced_len_uc8_uz8n(ucv8_t view, uc8_t from, size_t to_len);
UEXPORT size_t ucv8_replaced_len_uc8_ucv8(ucv8_t view, uc8_t from, ucv8_t to);
UEXPORT size_t ucv8_replaced_len_uc8_uv8(ucv8_t view, uc8_t from, uv8_t to);
UEXPORT size_t ucv8_replaced_len_uc8_us8(ucv8_t view, uc8_t from, const us8_t *to);

UEXPORT size_t ucv8_replaced_len_uz8_uc8(ucv8_t view, const uc8_t *from, uc8_t to);
UEXPORT size_t ucv8_replaced_len_uz8_uz8(ucv8_t view, const uc8_t *from, const uc8_t *to);
UEXPORT size_t ucv8_replaced_len_uz8_uz8n(ucv8_t view, const uc8_t *from, size_t to_len);
UEXPORT size_t ucv8_replaced_len_uz8_ucv8(ucv8_t view, const uc8_t *from, ucv8_t to);
UEXPORT size_t ucv8_replaced_len_uz8_uv8(ucv8_t view, const uc8_t *from, uv8_t to);
UEXPORT size_t ucv8_replaced_len_uz8_us8(ucv8_t view, const uc8_t *from, const us8_t *to);

UEXPORT size_t ucv8_replaced_len_uz8n_uc8(ucv8_t view, const uc8_t *from, size_t from_len, uc8_t to);
UEXPORT size_t ucv8_replaced_len_uz8n_uz8(ucv8_t view, const uc8_t *from, size_t from_len, const uc8_t *to);
UEXPORT size_t ucv8_replaced_len_uz8n_uz8n(ucv8_t view, const uc8_t *from, size_t from_len, size_t to_len);
UEXPORT size_t ucv8_replaced_len_uz8n_ucv8(ucv8_t view, const uc8_t *from, size_t from_len, ucv8_t to);
UEXPORT size_t ucv8_replaced_len_uz8n_uv8(ucv8_t view, const uc8_t *from, size_t from_len, uv8_t to);
UEXPORT size_t ucv8_replaced_len_uz8n_us8(ucv8_t view, const uc8_t *from, size_t from_len, const us8_t *to);

UEXPORT size_t ucv8_replaced_len_ucv8_uc8(ucv8_t view, ucv8_t from, uc8_t to);
UEXPORT size_t ucv8_replaced_len_ucv8_uz8(ucv8_t view, ucv8_t from, const uc8_t *to);
UEXPORT size_t ucv8_replaced_len_ucv8_uz8n(ucv8_t view, ucv8_t from, size_t to_len);
UEXPORT size_t ucv8_replaced_len_ucv8_ucv8(ucv8_t view, ucv8_t from, ucv8_t to);
UEXPORT size_t ucv8_replaced_len_ucv8_uv8(ucv8_t view, ucv8_t from, uv8_t to);
UEXPORT size_t ucv8_replaced_len_ucv8_us8(ucv8_t view, ucv8_t from, const us8_t *to);

UEXPORT size_t ucv8_replaced_len_uv8_uc8(ucv8_t view, uv8_t from, uc8_t to);
UEXPORT size_t ucv8_replaced_len_uv8_uz8(ucv8_t view, uv8_t from, const uc8_t *to);
UEXPORT size_t ucv8_replaced_len_uv8_uz8n(ucv8_t view, uv8_t from, size_t to_len);
UEXPORT size_t ucv8_replaced_len_uv8_ucv8(ucv8_t view, uv8_t from, ucv8_t to);
UEXPORT size_t ucv8_replaced_len_uv8_uv8(ucv8_t view, uv8_t from, uv8_t to);
UEXPORT size_t ucv8_replaced_len_uv8_us8(ucv8_t view, uv8_t from, const us8_t *to);

UEXPORT size_t ucv8_replaced_len_us8_uc8(ucv8_t view, const us8_t *from, uc8_t to);
UEXPORT size_t ucv8_replaced_len_us8_uz8(ucv8_t view, const us8_t *from, const uc8_t *to);
UEXPORT size_t ucv8_replaced_len_us8_uz8n(ucv8_t view, const us8_t *from, size_t to_len);
UEXPORT size_t ucv8_replaced_len_us8_ucv8(ucv8_t view, const us8_t *from, ucv8_t to);
UEXPORT size_t ucv8_replaced_len_us8_uv8(ucv8_t view, const us8_t *from, uv8_t to);
UEXPORT size_t ucv8_replaced_len_us8_us8(ucv8_t view, const us8_t *from, const us8_t *to);

// Count

#define ucv32_count(view, target)          \
    _Generic((target),                     \
        default:        ucv32_count_uc32,  \
        const uc32_t *: ucv32_count_uz32,  \
        uc32_t *:       ucv32_count_uz32,  \
        ucv32_t:        ucv32_count_ucv32, \
        uv32_t:         ucv32_count_uv32,  \
        const us32_t *: ucv32_count_us32,  \
        us32_t *:       ucv32_count_us32   \
    )((view), (target))

UEXPORT size_t ucv32_count_uc32(ucv32_t view, uc32_t target);
UEXPORT size_t ucv32_count_uz32(ucv32_t view, const uc32_t *target);
UEXPORT size_t ucv32_count_uz32n(ucv32_t view, const uc32_t *target, size_t target_len);
UEXPORT size_t ucv32_count_ucv32(ucv32_t view, ucv32_t target);
UEXPORT size_t ucv32_count_uv32(ucv32_t view, uv32_t target);
UEXPORT size_t ucv32_count_us32(ucv32_t view, const us32_t *target);

#define ucv16_count(view, target)          \
    _Generic((target),                     \
        default:        ucv16_count_uc16,  \
        const uc16_t *: ucv16_count_uz16,  \
        uc16_t *:       ucv16_count_uz16,  \
        ucv16_t:        ucv16_count_ucv16, \
        uv16_t:         ucv16_count_uv16,  \
        const us16_t *: ucv16_count_us16,  \
        us16_t *:       ucv16_count_us16   \
    )((view), (target))

UEXPORT size_t ucv16_count_uc16(ucv16_t view, uc16_t target);
UEXPORT size_t ucv16_count_uz16(ucv16_t view, const uc16_t *target);
UEXPORT size_t ucv16_count_uz16n(ucv16_t view, const uc16_t *target, size_t target_len);
UEXPORT size_t ucv16_count_ucv16(ucv16_t view, ucv16_t target);
UEXPORT size_t ucv16_count_uv16(ucv16_t view, uv16_t target);
UEXPORT size_t ucv16_count_us16(ucv16_t view, const us16_t *target);

#define ucv8_count(view, target)        \
    _Generic((target),                  \
        default:       ucv8_count_uc8,  \
        const uc8_t *: ucv8_count_uz8,  \
        uc8_t *:       ucv8_count_uz8,  \
        ucv8_t:        ucv8_count_ucv8, \
        uv8_t:         ucv8_count_uv8,  \
        const us8_t *: ucv8_count_us8,  \
        us8_t *:       ucv8_count_us8   \
    )((view), (target))

UEXPORT size_t ucv8_count_uc8(ucv8_t view, uc8_t target);
UEXPORT size_t ucv8_count_uz8(ucv8_t view, const uc8_t *target);
UEXPORT size_t ucv8_count_uz8n(ucv8_t view, const uc8_t *target, size_t target_len);
UEXPORT size_t ucv8_count_ucv8(ucv8_t view, ucv8_t target);
UEXPORT size_t ucv8_count_uv8(ucv8_t view, uv8_t target);
UEXPORT size_t ucv8_count_us8(ucv8_t view, const us8_t *target);

// Bounds

UEXPORT bool ucv32_bounds(ucv32_t view, size_t index);
UEXPORT bool ucv32_ebounds(ucv32_t view, size_t index);
UEXPORT bool ucv32_bounds_range(ucv32_t view, size_t begin, size_t len);
UEXPORT bool ucv32_ebounds_range(ucv32_t view, size_t begin, size_t len);

UEXPORT bool ucv16_bounds(ucv16_t view, size_t index);
UEXPORT bool ucv16_ebounds(ucv16_t view, size_t index);
UEXPORT bool ucv16_bounds_range(ucv16_t view, size_t begin, size_t len);
UEXPORT bool ucv16_ebounds_range(ucv16_t view, size_t begin, size_t len);

UEXPORT bool ucv8_bounds(ucv8_t view, size_t index);
UEXPORT bool ucv8_ebounds(ucv8_t view, size_t index);
UEXPORT bool ucv8_bounds_range(ucv8_t view, size_t begin, size_t len);
UEXPORT bool ucv8_ebounds_range(ucv8_t view, size_t begin, size_t len);

// Starts with

#define ucv32_starts_with(view, target)          \
    _Generic((target),                           \
        default:        ucv32_starts_with_uc32,  \
        const uc32_t *: ucv32_starts_with_uz32,  \
        uc32_t *:       ucv32_starts_with_uz32,  \
        ucv32_t:        ucv32_starts_with_ucv32, \
        uv32_t:         ucv32_starts_with_uv32,  \
        const us32_t *: ucv32_starts_with_us32,  \
        us32_t *:       ucv32_starts_with_us32   \
    )((view), (target))

UEXPORT bool ucv32_starts_with_uc32(ucv32_t view, uc32_t target);
UEXPORT bool ucv32_starts_with_uz32(ucv32_t view, const uc32_t *target);
UEXPORT bool ucv32_starts_with_uz32n(ucv32_t view, const uc32_t *target, size_t target_len);
UEXPORT bool ucv32_starts_with_ucv32(ucv32_t view, ucv32_t target);
UEXPORT bool ucv32_starts_with_uv32(ucv32_t view, uv32_t target);
UEXPORT bool ucv32_starts_with_us32(ucv32_t view, const us32_t *target);

#define ucv16_starts_with(view, target)          \
    _Generic((target),                           \
        default:        ucv16_starts_with_uc16,  \
        const uc16_t *: ucv16_starts_with_uz16,  \
        uc16_t *:       ucv16_starts_with_uz16,  \
        ucv16_t:        ucv16_starts_with_ucv16, \
        uv16_t:         ucv16_starts_with_uv16,  \
        const us16_t *: ucv16_starts_with_us16,  \
        us16_t *:       ucv16_starts_with_us16   \
    )((view), (target))

UEXPORT bool ucv16_starts_with_uc16(ucv16_t view, uc16_t target);
UEXPORT bool ucv16_starts_with_uz16(ucv16_t view, const uc16_t *target);
UEXPORT bool ucv16_starts_with_uz16n(ucv16_t view, const uc16_t *target, size_t target_len);
UEXPORT bool ucv16_starts_with_ucv16(ucv16_t view, ucv16_t target);
UEXPORT bool ucv16_starts_with_uv16(ucv16_t view, uv16_t target);
UEXPORT bool ucv16_starts_with_us16(ucv16_t view, const us16_t *target);

#define ucv8_starts_with(view, target)        \
    _Generic((target),                        \
        default:       ucv8_starts_with_uc8,  \
        const uc8_t *: ucv8_starts_with_uz8,  \
        uc8_t *:       ucv8_starts_with_uz8,  \
        ucv8_t:        ucv8_starts_with_ucv8, \
        uv8_t:         ucv8_starts_with_uv8,  \
        const us8_t *: ucv8_starts_with_us8,  \
        us8_t *:       ucv8_starts_with_us8   \
    )((view), (target))

UEXPORT bool ucv8_starts_with_uc8(ucv8_t view, uc8_t target);
UEXPORT bool ucv8_starts_with_uz8(ucv8_t view, const uc8_t *target);
UEXPORT bool ucv8_starts_with_uz8n(ucv8_t view, const uc8_t *target, size_t target_len);
UEXPORT bool ucv8_starts_with_ucv8(ucv8_t view, ucv8_t target);
UEXPORT bool ucv8_starts_with_uv8(ucv8_t view, uv8_t target);
UEXPORT bool ucv8_starts_with_us8(ucv8_t view, const us8_t *target);

// Ends with

#define ucv32_ends_with(view, target)          \
    _Generic((target),                         \
        default:        ucv32_ends_with_uc32,  \
        const uc32_t *: ucv32_ends_with_uz32,  \
        uc32_t *:       ucv32_ends_with_uz32,  \
        ucv32_t:        ucv32_ends_with_ucv32, \
        uv32_t:         ucv32_ends_with_uv32,  \
        const us32_t *: ucv32_ends_with_us32,  \
        us32_t *:       ucv32_ends_with_us32   \
    )((view), (target))

UEXPORT bool ucv32_ends_with_uc32(ucv32_t view, uc32_t target);
UEXPORT bool ucv32_ends_with_uz32(ucv32_t view, const uc32_t *target);
UEXPORT bool ucv32_ends_with_uz32n(ucv32_t view, const uc32_t *target, size_t target_len);
UEXPORT bool ucv32_ends_with_ucv32(ucv32_t view, ucv32_t target);
UEXPORT bool ucv32_ends_with_uv32(ucv32_t view, uv32_t target);
UEXPORT bool ucv32_ends_with_us32(ucv32_t view, const us32_t *target);

#define ucv16_ends_with(view, target)          \
    _Generic((target),                         \
        default:        ucv16_ends_with_uc16,  \
        const uc16_t *: ucv16_ends_with_uz16,  \
        uc16_t *:       ucv16_ends_with_uz16,  \
        ucv16_t:        ucv16_ends_with_ucv16, \
        uv16_t:         ucv16_ends_with_uv16,  \
        const us16_t *: ucv16_ends_with_us16,  \
        us16_t *:       ucv16_ends_with_us16   \
    )((view), (target))

UEXPORT bool ucv16_ends_with_uc16(ucv16_t view, uc16_t target);
UEXPORT bool ucv16_ends_with_uz16(ucv16_t view, const uc16_t *target);
UEXPORT bool ucv16_ends_with_uz16n(ucv16_t view, const uc16_t *target, size_t target_len);
UEXPORT bool ucv16_ends_with_ucv16(ucv16_t view, ucv16_t target);
UEXPORT bool ucv16_ends_with_uv16(ucv16_t view, uv16_t target);
UEXPORT bool ucv16_ends_with_us16(ucv16_t view, const us16_t *target);

#define ucv8_ends_with(view, target)        \
    _Generic((target),                      \
        default:       ucv8_ends_with_uc8,  \
        const uc8_t *: ucv8_ends_with_uz8,  \
        uc8_t *:       ucv8_ends_with_uz8,  \
        ucv8_t:        ucv8_ends_with_ucv8, \
        uv8_t:         ucv8_ends_with_uv8,  \
        const us8_t *: ucv8_ends_with_us8,  \
        us8_t *:       ucv8_ends_with_us8   \
    )((view), (target))

UEXPORT bool ucv8_ends_with_uc8(ucv8_t view, uc8_t target);
UEXPORT bool ucv8_ends_with_uz8(ucv8_t view, const uc8_t *target);
UEXPORT bool ucv8_ends_with_uz8n(ucv8_t view, const uc8_t *target, size_t target_len);
UEXPORT bool ucv8_ends_with_ucv8(ucv8_t view, ucv8_t target);
UEXPORT bool ucv8_ends_with_uv8(ucv8_t view, uv8_t target);
UEXPORT bool ucv8_ends_with_us8(ucv8_t view, const us8_t *target);

// Iteration

// - Begin

UEXPORT const uc32_t *ucv32_cbegin(ucv32_t view);
UEXPORT const uc16_t *ucv16_cbegin(ucv16_t view);
UEXPORT const uc8_t *ucv8_cbegin(ucv8_t view);

// - Offset

UEXPORT const uc32_t *ucv32_coffset(ucv32_t view, size_t offset);
UEXPORT const uc16_t *ucv16_coffset(ucv16_t view, size_t offset);
UEXPORT const uc8_t *ucv8_coffset(ucv8_t view, size_t offset);

// - End

UEXPORT const uc32_t *ucv32_cend(ucv32_t view);
UEXPORT const uc16_t *ucv16_cend(ucv16_t view);
UEXPORT const uc8_t *ucv8_cend(ucv8_t view);

// Empty

UEXPORT bool ucv32_empty(ucv32_t view);
UEXPORT bool ucv16_empty(ucv16_t view);
UEXPORT bool ucv8_empty(ucv8_t view);

// At

UEXPORT uc32_t ucv32_at(ucv32_t view, size_t at);
UEXPORT uc16_t ucv16_at(ucv16_t view, size_t at);
UEXPORT uc8_t ucv8_at(ucv8_t view, size_t at);

// Chars

UEXPORT const uc32_t *ucv32_cchars(ucv32_t view);
UEXPORT const uc16_t *ucv16_cchars(ucv16_t view);
UEXPORT const uc8_t *ucv8_cchars(ucv8_t view);

UEXPORT void ucv32_set_chars(ucv32_t *view, const uc32_t *chars);
UEXPORT void ucv16_set_chars(ucv16_t *view, const uc16_t *chars);
UEXPORT void ucv8_set_chars(ucv8_t *view, const uc8_t *chars);

// Valid

UEXPORT bool ucv32_valid_p(const ucv32_t *view);
UEXPORT bool ucv32_valid(ucv32_t view);

UEXPORT bool ucv16_valid_p(const ucv16_t *view);
UEXPORT bool ucv16_valid(ucv16_t view);

UEXPORT bool ucv8_valid_p(const ucv8_t *view);
UEXPORT bool ucv8_valid(ucv8_t view);

#endif