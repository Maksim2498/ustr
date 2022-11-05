#ifndef USTR_VIEW_H
#define USTR_VIEW_H

#include <stdbool.h>
#include <stddef.h>

#include "char_t.h"
#include "cview_t.h"
#include "str_t.h"
#include "view_t.h"

// uv8_t

// - Creation

#define uv8(literal)                                 \
    (uv8_t) {                                        \
        .chars = (u8##literal),                      \
        .len   = sizeof(u8##literal) / sizeof(uc8_t) \
    }

// uv16_t

// - Creation

#define uv16(literal)                                \
    (uv16_t) {                                       \
        .chars = (u##literal),                       \
        .len   = sizeof(u##literal) / sizeof(uc16_t) \
    }

// uv32_t

// - Creation

#define uv32(literal)                                \
    (uv32_t) {                                       \
        .chars = (U##literal),                       \
        .len   = sizeof(U##literal) / sizeof(uc32_t) \
    }

uv32_t uv32_from_us32(us32_t *str);
uv32_t uv32_from_us32_range(us32_t *str, size_t from, size_t len);
uv32_t uv32_from_uv32_range(uv32_t view, size_t from, size_t len);
uv32_t uv32_from_cstr(uc32_t *cstr);
uv32_t uv32_from_cstrn(uc32_t *cstr, size_t n);

// - Char

uc32_t uv32_char(uv32_t view, size_t index);
void uv32_set_char(uv32_t view, uc32_t c, size_t index);

// - Cmp

int uv32_cmp(uv32_t lhs, uv32_t rhs);
int uv32_cmp_n(uv32_t lhs, uv32_t rhs, size_t n);
int uv32_cmp_ucv32(uv32_t lhs, ucv32_t rhs);
int uv32_cmp_ucv32_n(uv32_t lhs, ucv32_t rhs, size_t n);
int uv32_cmp_us32(uv32_t lhs, const us32_t *rhs);
int uv32_cmp_us32_n(uv32_t lhs, const us32_t *rhs, size_t n);
int uv32_cmp_cstr(uv32_t lhs, const uc32_t *cstr);
int uv32_cmp_cstrn(uv32_t lhs, const uc32_t *cstr, size_t n);

// - Search

// -- Forward

ptrdiff_t uv32_char_pos(uv32_t view, uc32_t c);
ptrdiff_t uv32_char_pos_from(uv32_t view, uc32_t c, size_t from);
ptrdiff_t uv32_cstr_pos(uv32_t view, const uc32_t *cstr);
ptrdiff_t uv32_cstr_pos_from(uv32_t view, const uc32_t *cstr, size_t from);
ptrdiff_t uv32_cstrn_pos(uv32_t view, const uc32_t *cstr, size_t n);
ptrdiff_t uv32_cstrn_pos_from(uv32_t view, const uc32_t *cstr, size_t n, size_t from);
ptrdiff_t uv32_uv32_pos(uv32_t view, uv32_t another);
ptrdiff_t uv32_uv32_pos_from(uv32_t view, uv32_t another, size_t from);
ptrdiff_t uv32_ucv32_pos(uv32_t view, ucv32_t another);
ptrdiff_t uv32_ucv32_pos_from(uv32_t view, ucv32_t another, size_t from);
ptrdiff_t uv32_us32_pos(uv32_t view, const us32_t *str);

// -- Backward

ptrdiff_t uv32_char_pos_r(uv32_t view, uc32_t c);
ptrdiff_t uv32_char_pos_from_r(uv32_t view, uc32_t c, size_t from);
ptrdiff_t uv32_cstr_pos_r(uv32_t view, const uc32_t *cstr);
ptrdiff_t uv32_cstr_pos_from_r(uv32_t view, const uc32_t *cstr, size_t from);
ptrdiff_t uv32_cstrn_pos_r(uv32_t view, const uc32_t *cstr, size_t n);
ptrdiff_t uv32_cstrn_pos_from_r(uv32_t view, const uc32_t *cstr, size_t n, size_t from);
ptrdiff_t uv32_uv32_pos_r(uv32_t view, uv32_t another);
ptrdiff_t uv32_uv32_pos_from_r(uv32_t view, uv32_t another, size_t from);
ptrdiff_t uv32_ucv32_pos_r(uv32_t view, ucv32_t another);
ptrdiff_t uv32_ucv32_pos_from_r(uv32_t view, ucv32_t another, size_t from);
ptrdiff_t uv32_us32_pos_r(uv32_t view, const us32_t *str);
ptrdiff_t uv32_us32_pos_from_r(uv32_t view, const us32_t *str, size_t from);
ptrdiff_t uv32_us32_pos_from_r(uv32_t view, const us32_t *str, size_t from);

// - Fill

void uv32_fill(uv32_t view, uc32_t c);
void uv32_fill_range(uv32_t view, uc32_t c, size_t from, size_t len);
void uv32_fill_cstr(uv32_t view, const uc32_t *cstr);
void uv32_fill_cstr_range(uv32_t view, const uc32_t *cstr, size_t from, size_t len);
void uv32_fill_cstrn(uv32_t view, const uc32_t *cstr, size_t n);
void uv32_fill_cstrn_range(uv32_t view, const uc32_t *cstr, size_t n, size_t from, size_t len);
void uv32_fill_uv32(uv32_t view, uv32_t another);
void uv32_fill_uv32_from(uv32_t view, uv32_t another, size_t from);
void uv32_fill_uv32_range(uv32_t view, uv32_t another, size_t from, size_t to);
void uv32_fill_ucv32(uv32_t view, ucv32_t another);
void uv32_fill_ucv32_from(uv32_t view, ucv32_t another, size_t from);
void uv32_fill_ucv32_range(uv32_t view, ucv32_t another, size_t from, size_t to);
void uv32_fill_us32(uv32_t view, const us32_t *str);
void uv32_fill_us32_from(uv32_t view, const us32_t *str, size_t from);
void uv32_fill_us32_range(uv32_t view, const us32_t *str, size_t from, size_t to);

// - Case Change

void uv32_to_upper(uv32_t view);
void uv32_to_lower(uv32_t view);

// - Iteration

uc32_t *uv32_begin(uv32_t view);
const uc32_t *uv32_cbegin(uv32_t view);
uc32_t *uv32_end(uv32_t view);
const uc32_t *uv32_cend(uv32_t view);
uc32_t *uv32_at(uv32_t view);
const uc32_t *uv32_cat(uv32_t view);

// - Len

bool uv32_bounds(uv32_t view);
size_t uv32_len(uv32_t view);
bool uv32_empty(uv32_t view);

// - Valid

bool uv32_valid(uv32_t view);

#endif