#ifndef USTR_CVIEW_H
#define USTR_CVIEW_H

#include <stdbool.h>
#include <stddef.h>

#include "char_t.h"
#include "cview_t.h"
#include "str_t.h"
#include "view_t.h"

// uc8_t

// - Creation

#define ucv8(literal)                                \
    (ucv8_t) {                                       \
        .chars = (u8##literal),                      \
        .len   = sizeof(u8##literal) / sizeof(uc8_t) \
    }

// uc16_t

// - Creation

#define ucv16(literal)                               \
    (ucv16_t) {                                      \
        .chars = (u##literal),                       \
        .len   = sizeof(u##literal) / sizeof(uc16_t) \
    }

// uc32_t

// - Creation

#define ucv32(literal)                               \
    (ucv32_t) {                                      \
        .chars = (U##literal),                       \
        .len   = sizeof(U##literal) / sizeof(uc32_t) \
    }

ucv32_t ucv32_from_us32(const us32_t *str);
ucv32_t ucv32_from_us32_range(const us32_t *str, size_t from, size_t len);
ucv32_t ucv32_from_uv32_range(const uv32_t view, size_t from, size_t len);
ucv32_t ucv32_from_cstr(const uc32_t *cstr);
ucv32_t ucv32_from_cstrn(const uc32_t *cstr, size_t n);

// - Char

uc32_t ucv32_char(ucv32_t view, size_t index);

// - Cmp

int ucv32_cmp(ucv32_t lhs, ucv32_t rhs);
int ucv32_cmp_n(ucv32_t lhs, ucv32_t rhs, size_t n);
int ucv32_cmp_uv32(ucv32_t lhs, uv32_t rhs);
int ucv32_cmp_uv32_n(ucv32_t lhs, uv32_t rhs, size_t n);
int ucv32_cmp_us32(ucv32_t lhs, const us32_t *rhs);
int ucv32_cmp_us32_n(ucv32_t lhs, const us32_t *rhs, size_t n);
int ucv32_cmp_cstr(ucv32_t lhs, const uc32_t *cstr);
int ucv32_cmp_cstrn(ucv32_t lhs, const uc32_t *cstr, size_t n);

// - Search

// -- Forward

ptrdiff_t ucv32_char_pos(ucv32_t view, uc32_t c);
ptrdiff_t ucv32_char_pos_from(ucv32_t view, uc32_t c, size_t from);
ptrdiff_t ucv32_cstr_pos(ucv32_t view, const uc32_t *cstr);
ptrdiff_t ucv32_cstr_pos_from(ucv32_t view, const uc32_t *cstr, size_t from);
ptrdiff_t ucv32_cstrn_pos(ucv32_t view, const uc32_t *cstr, size_t n);
ptrdiff_t ucv32_cstrn_pos_from(ucv32_t view, const uc32_t *cstr, size_t n, size_t from);
ptrdiff_t ucv32_uv32_pos(ucv32_t view, uv32_t another);
ptrdiff_t ucv32_uv32_pos_from(ucv32_t view, uv32_t another, size_t from);
ptrdiff_t ucv32_ucv32_pos(ucv32_t view, ucv32_t another);
ptrdiff_t ucv32_ucv32_pos_from(ucv32_t view, ucv32_t another, size_t from);
ptrdiff_t ucv32_us32_pos(ucv32_t view, const us32_t *str);

// -- Backward

ptrdiff_t ucv32_char_pos_r(ucv32_t view, uc32_t c);
ptrdiff_t ucv32_char_pos_from_r(ucv32_t view, uc32_t c, size_t from);
ptrdiff_t ucv32_cstr_pos_r(ucv32_t view, const uc32_t *cstr);
ptrdiff_t ucv32_cstr_pos_from_r(ucv32_t view, const uc32_t *cstr, size_t from);
ptrdiff_t ucv32_cstrn_pos_r(ucv32_t view, const uc32_t *cstr, size_t n);
ptrdiff_t ucv32_cstrn_pos_from_r(ucv32_t view, const uc32_t *cstr, size_t n, size_t from);
ptrdiff_t ucv32_uv32_pos_r(ucv32_t view, uv32_t another);
ptrdiff_t ucv32_uv32_pos_from_r(ucv32_t view, uv32_t another, size_t from);
ptrdiff_t ucv32_ucv32_pos_r(ucv32_t view, ucv32_t another);
ptrdiff_t ucv32_ucv32_pos_from_r(ucv32_t view, ucv32_t another, size_t from);
ptrdiff_t ucv32_us32_pos_r(ucv32_t view, const us32_t *str);
ptrdiff_t ucv32_us32_pos_from_r(ucv32_t view, const us32_t *str, size_t from);
ptrdiff_t ucv32_us32_pos_from_r(ucv32_t view, const us32_t *str, size_t from);

// - Iteration

const uc32_t *ucv32_cbegin(ucv32_t view);
const uc32_t *ucv32_cend(ucv32_t view);
const uc32_t *ucv32_cat(ucv32_t view);

// - Len

bool ucv32_bounds(ucv32_t view);
size_t ucv32_len(ucv32_t view);
bool ucv32_empty(ucv32_t view);

// - Valid

bool ucv32_valid(ucv32_t view);

#endif