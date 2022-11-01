#ifndef USTR_VIEW_H
#define USTR_VIEW_H

#include <stdbool.h>
#include <stddef.h>

#include "cview_t.h"
#include "str_t.h"
#include "view_t.h"

// Creation

#define uv32(literal)                                \
    (uv32_t) {                                       \
        .chars = (U##literal),                       \
        .len   = sizeof(U##literal) / sizeof(uc32_t) \
    }

uv32_t uv32_from_us32(us32_t *str);
uv32_t uv32_from_us32_range(us32_t *str, size_t from, size_t len);
uv32_t uv32_from_uv32_range(uv32_t view, size_t from, size_t len);
uv32_t uv32_from_chars(uc32_t *chars);
uv32_t uv32_from_charsn(uc32_t *str, size_t n);

// Char

uc32_t uv32_char(uv32_t view, size_t index);
void uv32_set_char(uv32_t view, uc32_t c, size_t index);

// Cmp

int uv32_cmp_pr(const uv32_t *lhs, const uv32_t *rhs);
int uv32_cmp_p(const uv32_t *lhs, const uv32_t *rhs);
int uv32_cmp_r(uv32_t lhs, uv32_t rhs);
int uv32_cmp(uv32_t lhs, uv32_t rhs);

// Search

// - Forward

ptrdiff_t uv32_char_pos(uv32_t view, uc32_t c);
ptrdiff_t uv32_char_pos_from(uv32_t view, uc32_t c, size_t from);
ptrdiff_t uv32_chars_pos(uv32_t view, const uc32_t *chars);
ptrdiff_t uv32_chars_pos_from(uv32_t view, const uc32_t *chars, size_t from);
ptrdiff_t uv32_charsn_pos(uv32_t view, const uc32_t *chars, size_t n);
ptrdiff_t uv32_charsn_pos_from(uv32_t view, const uc32_t *chars, size_t n, size_t from);
ptrdiff_t uv32_uv32_pos(uv32_t view, uv32_t another);
ptrdiff_t uv32_uv32_pos_from(uv32_t view, uv32_t another, size_t from);
ptrdiff_t uv32_ucv32_pos(uv32_t view, ucv32_t another);
ptrdiff_t uv32_ucv32_pos_from(uv32_t view, ucv32_t another, size_t from);
ptrdiff_t uv32_us32_pos(uv32_t view, const us32_t *str);

// - Backward

ptrdiff_t uv32_char_pos_r(uv32_t view, uc32_t c);
ptrdiff_t uv32_char_pos_from_r(uv32_t view, uc32_t c, size_t from);
ptrdiff_t uv32_chars_pos_r(uv32_t view, const uc32_t *chars);
ptrdiff_t uv32_chars_pos_from_r(uv32_t view, const uc32_t *chars, size_t from);
ptrdiff_t uv32_charsn_pos_r(uv32_t view, const uc32_t *chars, size_t n);
ptrdiff_t uv32_chars32n_pos_from_r(uv32_t view, const uc32_t *chars, size_t n, size_t from);
ptrdiff_t uv32_uv32_pos_r(uv32_t view, uv32_t another);
ptrdiff_t uv32_uv32_pos_from_r(uv32_t view, uv32_t another, size_t from);
ptrdiff_t uv32_ucv32_pos_r(uv32_t view, ucv32_t another);
ptrdiff_t uv32_ucv32_pos_from_r(uv32_t view, ucv32_t another, size_t from);
ptrdiff_t uv32_us32_pos_r(uv32_t view, const us32_t *str);
ptrdiff_t uv32_us32_pos_from_r(uv32_t view, const us32_t *str, size_t from);
ptrdiff_t uv32_us32_pos_from_r(uv32_t view, const us32_t *str, size_t from);

// Fill

void uv32_fill(uv32_t view, uc32_t c);
void uv32_fill_range(uv32_t view, uc32_t c, size_t from, size_t len);
void uv32_fill_chars(uv32_t view, const uc32_t *chars);
void uv32_fill_chars_range(uv32_t view, const uc32_t *chars, size_t from, size_t len);
void uv32_fill_charsn(uv32_t view, const uc32_t *chars, size_t n);
void uv32_fill_charsn_range(uv32_t view, const uc32_t *chars, size_t n, size_t from, size_t len);
void uv32_fill_uv32(uv32_t view, uv32_t another);
void uv32_fill_uv32_from(uv32_t view, uv32_t another, size_t from);
void uv32_fill_uv32_range(uv32_t view, uv32_t another, size_t from, size_t to);
void uv32_fill_ucv32(uv32_t view, ucv32_t another);
void uv32_fill_ucv32_from(uv32_t view, ucv32_t another, size_t from);
void uv32_fill_ucv32_range(uv32_t view, ucv32_t another, size_t from, size_t to);
void uv32_fill_us32(uv32_t view, const us32_t *str);
void uv32_fill_us32_from(uv32_t view, const us32_t *str, size_t from);
void uv32_fill_us32_range(uv32_t view, const us32_t *str, size_t from, size_t to);

// Case change

void uv32_to_upper(uv32_t view);
void uv32_to_lower(uv32_t view);

// Iteration

uc32_t *uv32_begin(uv32_t view);
const uc32_t *uv32_cbegin(uv32_t view);
uc32_t *uv32_end(uv32_t view);
const uc32_t *uv32_cend(uv32_t view);
uc32_t *uv32_at(uv32_t view);
const uc32_t *uv32_cat(uv32_t view);

// Len

bool uv32_bounds(uv32_t view);
size_t uv32_len(uv32_t view);
bool uv32_empty(uv32_t view);

// Valid

bool uv32_valid(uv32_t view);

#endif