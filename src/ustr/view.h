#ifndef USTR_VIEW_H
#define USTR_VIEW_H

#include <stdbool.h>
#include <stddef.h>

#include "type/fmt/case.h"
#include "type/char.h"
#include "type/cview.h"
#include "type/str.h"
#include "type/view.h"

// Expand

#define UV32_EXPAND(view)  uv32_chars(view),  (view).len
#define UV32_CEXPAND(view) uv32_cchars(view), (view).len

// Creation

#define uv32(literal)                                    \
    (uv32_t) {                                           \
        .chars = (U##literal),                           \
        .len   = sizeof(U##literal) / sizeof(uc32_t) - 1 \
    }

uv32_t uv32_mk(void);
uv32_t uv32_from_range(uv32_t view, size_t from, size_t len);
uv32_t uv32_from_us32(us32_t *str);
uv32_t uv32_from_us32_range(us32_t *str, size_t from, size_t len);
uv32_t uv32_from_uz32(uc32_t *cstr);
uv32_t uv32_from_uz32_n(uc32_t *cstr, size_t n);

// Cross-UTF Len

size_t uv32_n_len_from(uv32_t view, unsigned n, size_t from);
size_t uv32_32_len_from(uv32_t view, size_t from);
size_t uv32_16_len_from(uv32_t view, size_t from);
size_t uv32_8_len_from(uv32_t view, size_t from);

size_t uv32_n_len_to(uv32_t view, unsigned n, size_t to);
size_t uv32_32_len_to(uv32_t view, size_t to);
size_t uv32_16_len_to(uv32_t view, size_t to);
size_t uv32_8_len_to(uv32_t view, size_t to);

size_t uv32_n_len_range(uv32_t view, unsigned n, size_t from, size_t len);
size_t uv32_32_len_range(uv32_t view, size_t from, size_t len);
size_t uv32_16_len_range(uv32_t view, size_t from, size_t len);
size_t uv32_8_len_range(uv32_t view, size_t from, size_t len);

size_t uv32_n_len(uv32_t view, unsigned n);
size_t uv32_32_len(uv32_t view);
size_t uv32_16_len(uv32_t view);
size_t uv32_8_len(uv32_t view);

// Reverse

void uv32_reverse(uv32_t view);

// Trim

size_t uv32_trim(uv32_t *view);
size_t uv32_trim_left(uv32_t *view);
size_t uv32_trim_right(uv32_t *view);

// Char

uc32_t uv32_at(uv32_t view, size_t index);
void uv32_set_at(uv32_t view, uc32_t c, size_t index);

// Cmp

int uv32_cmp(uv32_t lhs, uv32_t rhs);
int uv32_cmp_n(uv32_t lhs, uv32_t rhs, size_t n);
int uv32_cmp_ucv32(uv32_t lhs, ucv32_t rhs);
int uv32_cmp_ucv32_n(uv32_t lhs, ucv32_t rhs, size_t n);
int uv32_cmp_us32(uv32_t lhs, const us32_t *rhs);
int uv32_cmp_us32_n(uv32_t lhs, const us32_t *rhs, size_t n);
int uv32_cmp_uz32(uv32_t lhs, const uc32_t *rhs);
int uv32_cmp_uz32_n(uv32_t lhs, const uc32_t *rhs, size_t n);

// Search

// - Forward

ptrdiff_t uv32_pos(uv32_t view, uv32_t another);
ptrdiff_t uv32_pos_from(uv32_t view, uv32_t another, size_t from);
ptrdiff_t uv32_uc32_pos(uv32_t view, uc32_t c);
ptrdiff_t uv32_uc32_pos_from(uv32_t view, uc32_t c, size_t from);
ptrdiff_t uv32_uz32_pos(uv32_t view, const uc32_t *cstr);
ptrdiff_t uv32_uz32_pos_from(uv32_t view, const uc32_t *cstr, size_t from);
ptrdiff_t uv32_uz32_n_pos(uv32_t view, const uc32_t *cstr, size_t n);
ptrdiff_t uv32_uz32_n_pos_from(uv32_t view, const uc32_t *cstr, size_t n, size_t from);
ptrdiff_t uv32_ucv32_pos(uv32_t view, ucv32_t another);
ptrdiff_t uv32_ucv32_pos_from(uv32_t view, ucv32_t another, size_t from);
ptrdiff_t uv32_us32_pos(uv32_t view, const us32_t *str);
ptrdiff_t uv32_us32_pos_from(uv32_t view, const us32_t *str, size_t from);

// - Backward

ptrdiff_t uv32_pos_r(uv32_t view, uv32_t another);
ptrdiff_t uv32_pos_from_r(uv32_t view, uv32_t another, size_t from);
ptrdiff_t uv32_uc32_pos_r(uv32_t view, uc32_t c);
ptrdiff_t uv32_uc32_pos_from_r(uv32_t view, uc32_t c, size_t from);
ptrdiff_t uv32_uz32_pos_r(uv32_t view, const uc32_t *cstr);
ptrdiff_t uv32_uz32_pos_from_r(uv32_t view, const uc32_t *cstr, size_t from);
ptrdiff_t uv32_uz32_n_pos_r(uv32_t view, const uc32_t *cstr, size_t n);
ptrdiff_t uv32_uz32_n_pos_from_r(uv32_t view, const uc32_t *cstr, size_t n, size_t from);
ptrdiff_t uv32_ucv32_pos_r(uv32_t view, ucv32_t another);
ptrdiff_t uv32_ucv32_pos_from_r(uv32_t view, ucv32_t another, size_t from);
ptrdiff_t uv32_us32_pos_r(uv32_t view, const us32_t *str);
ptrdiff_t uv32_us32_pos_from_r(uv32_t view, const us32_t *str, size_t from);

// Fill

void uv32_fill(uv32_t view, uc32_t c);
void uv32_fill_from(uv32_t view, uc32_t c, size_t from);
void uv32_fill_to(uv32_t view, uc32_t c, size_t to);
void uv32_fill_range(uv32_t view, uc32_t c, size_t from, size_t len);
void uv32_fill_uz32(uv32_t view, const uc32_t *cstr);
void uv32_fill_uz32_from(uv32_t view, const uc32_t *cstr, size_t from);
void uv32_fill_uz32_to(uv32_t view, const uc32_t *cstr, size_t to);
void uv32_fill_uz32_range(uv32_t view, const uc32_t *cstr, size_t from, size_t len);
void uv32_fill_uz32_n(uv32_t view, const uc32_t *cstr, size_t n);
void uv32_fill_uz32_n_from(uv32_t view, const uc32_t *cstr, size_t n, size_t from);
void uv32_fill_uz32_n_to(uv32_t view, const uc32_t *cstr, size_t n, size_t to);
void uv32_fill_uz32_n_range(uv32_t view, const uc32_t *cstr, size_t n, size_t from, size_t len);
void uv32_fill_uv32(uv32_t view, uv32_t another);
void uv32_fill_uv32_from(uv32_t view, uv32_t another, size_t from);
void uv32_fill_uv32_to(uv32_t view, uv32_t another, size_t to);
void uv32_fill_uv32_range(uv32_t view, uv32_t another, size_t from, size_t len);
void uv32_fill_ucv32(uv32_t view, ucv32_t another);
void uv32_fill_ucv32_from(uv32_t view, ucv32_t another, size_t from);
void uv32_fill_ucv32_to(uv32_t view, ucv32_t another, size_t to);
void uv32_fill_ucv32_range(uv32_t view, ucv32_t another, size_t from, size_t len);
void uv32_fill_us32(uv32_t view, const us32_t *str);
void uv32_fill_us32_from(uv32_t view, const us32_t *str, size_t from);
void uv32_fill_us32_to(uv32_t view, const us32_t *str, size_t to);
void uv32_fill_us32_range(uv32_t view, const us32_t *str, size_t from, size_t len);

// Case Change

void uv32_to_case(uv32_t view, ucase_t ca);
void uv32_to_upper(uv32_t view);
void uv32_to_lower(uv32_t view);

// Iteration

uc32_t *uv32_begin(uv32_t view);
const uc32_t *uv32_cbegin(uv32_t view);
uc32_t *uv32_end(uv32_t view);
const uc32_t *uv32_cend(uv32_t view);
uc32_t *uv32_offset(uv32_t view, size_t index);
const uc32_t *uv32_coffset(uv32_t view, size_t index);

// Len

bool uv32_bounds(uv32_t view, size_t index);
bool uv32_ebounds(uv32_t view, size_t index);
bool uv32_bounds_range(uv32_t view, size_t from, size_t len);
bool uv32_ebounds_range(uv32_t view, size_t from, size_t len);

size_t uv32_len(uv32_t view);
size_t uv32_len(uv32_t view);
size_t uv32_add_len(uv32_t *view, ptrdiff_t delta);

bool uv32_empty(uv32_t view);

// Split

size_t uv32_new_csplit(uv32_t view, uc32_t c, ucv32_t **array);
size_t uv32_new_csplit_e(uv32_t view, uc32_t c, ucv32_t **array, bool *error);
size_t uv32_csplit(uv32_t view, uc32_t c, ucv32_t *array, size_t array_len);
size_t uv32_new_split(uv32_t view, uc32_t c, uv32_t **array);
size_t uv32_new_split_e(uv32_t view, uc32_t c, uv32_t **array, bool *error);
size_t uv32_split(uv32_t view, uc32_t c, uv32_t *array, size_t array_len);

size_t uv32_new_csplit_uz32(uv32_t view, const uc32_t *cstr, ucv32_t **array);
size_t uv32_new_csplit_uz32_e(uv32_t view, const uc32_t *cstr, ucv32_t **array, bool *error);
size_t uv32_csplit_uz32(uv32_t view, const uc32_t *cstr, ucv32_t *array, size_t array_len);
size_t uv32_new_split_uz32(uv32_t view, const uc32_t *cstr, uv32_t **array);
size_t uv32_new_split_uz32_e(uv32_t view, const uc32_t *cstr, uv32_t **array, bool *error);
size_t uv32_split_uz32(uv32_t view, const uc32_t *cstr, uv32_t *array, size_t array_len);

size_t uv32_new_csplit_uz32_n(uv32_t view, const uc32_t *cstr, size_t n, ucv32_t **array);
size_t uv32_new_csplit_uz32_n_e(uv32_t view, const uc32_t *cstr, size_t n, ucv32_t **array, bool *error);
size_t uv32_csplit_uz32_n(uv32_t view, const uc32_t *cstr, size_t n, ucv32_t *array, size_t array_len);
size_t uv32_new_split_uz32_n(uv32_t view, const uc32_t *cstr, size_t n, uv32_t **array);
size_t uv32_new_split_uz32_n_e(uv32_t view, const uc32_t *cstr, size_t n, uv32_t **array, bool *error);
size_t uv32_split_uz32_n(uv32_t view, const uc32_t *cstr, size_t n, uv32_t *array, size_t array_len);

size_t uv32_new_csplit_ucv32(uv32_t view, ucv32_t another, ucv32_t **array);
size_t uv32_new_csplit_ucv32_e(uv32_t view, ucv32_t another, ucv32_t **array, bool *error);
size_t uv32_csplit_ucv32(uv32_t view, ucv32_t another, ucv32_t *array, size_t array_len);
size_t uv32_new_split_ucv32(uv32_t view, ucv32_t another, uv32_t **array);
size_t uv32_new_split_ucv32_e(uv32_t view, ucv32_t another, uv32_t **array, bool *error);
size_t uv32_split_ucv32(uv32_t view, ucv32_t another, uv32_t *array, size_t array_len);

size_t uv32_new_csplit_us32(uv32_t view, const us32_t *str, ucv32_t **array);
size_t uv32_new_csplit_us32_e(uv32_t view, const us32_t *str, ucv32_t **array, bool *error);
size_t uv32_csplit_us32(uv32_t view, const us32_t *str, ucv32_t *array, size_t array_len);
size_t uv32_new_split_us32(uv32_t view, const us32_t *str, uv32_t **array);
size_t uv32_new_split_us32_e(uv32_t view, const us32_t *str, uv32_t **array, bool *error);
size_t uv32_split_us32(uv32_t view, const us32_t *str, uv32_t *array, size_t array_len);

size_t uv32_new_csplit_uv32(uv32_t view, uv32_t another, ucv32_t **array);
size_t uv32_new_csplit_uv32_e(uv32_t view, uv32_t another, ucv32_t **array, bool *error);
size_t uv32_csplit_uv32(uv32_t view, uv32_t another, ucv32_t *array, size_t array_len);
size_t uv32_new_split_uv32(uv32_t view, uv32_t another, uv32_t **array);
size_t uv32_new_split_uv32_e(uv32_t view, uv32_t another, uv32_t **array, bool *error);
size_t uv32_split_uv32(uv32_t view, uv32_t another, uv32_t *array, size_t array_len);

// Replace

size_t uv32_replace_uc32_uc32(uv32_t *view, uc32_t from, uc32_t to);
size_t uv32_replace_uc32_uc32_c(uv32_t *view, uc32_t from, uc32_t to, size_t *count);

size_t uv32_replace_uz32_uc32(uv32_t *view, const uc32_t *from, uc32_t to);
size_t uv32_replace_uz32_uc32_c(uv32_t *view, const uc32_t *from, uc32_t to, size_t *count);

size_t uv32_replace_uz32_n_uc32(uv32_t *view, const uc32_t *from, size_t from_len, uc32_t to);
size_t uv32_replace_uz32_n_uc32_c(uv32_t *view, const uc32_t *from, size_t from_len, uc32_t to, size_t *count);

size_t uv32_replace_ucv32_uc32(uv32_t *view, ucv32_t from, uc32_t to);
size_t uv32_replace_ucv32_uc32_c(uv32_t *view, ucv32_t from, uc32_t to, size_t *count);

size_t uv32_replace_us32_uc32(uv32_t *view, const us32_t *from, uc32_t to);
size_t uv32_replace_us32_uc32_c(uv32_t *view, const us32_t *from, uc32_t to, size_t *count);

size_t uv32_replace_uv32_uc32(uv32_t *view, uv32_t from, uc32_t to);
size_t uv32_replace_uv32_uc32_c(uv32_t *view, uv32_t from, uc32_t to, size_t *count);

size_t uv32_replace_uc32_uz32(uv32_t *view, uc32_t from, const uc32_t *to);
size_t uv32_replace_uc32_uz32_c(uv32_t *view, uc32_t from, const uc32_t *to, size_t *count);

size_t uv32_replace_uc32_uz32_n(uv32_t *view, uc32_t from, const uc32_t *to, size_t to_len);
size_t uv32_replace_uc32_uz32_n_c(uv32_t *view, uc32_t from, const uc32_t *to, size_t to_len, size_t *count);

size_t uv32_replace_uc32_ucv32(uv32_t *view, uc32_t from, ucv32_t to);
size_t uv32_replace_uc32_ucv32_c(uv32_t *view, uc32_t from, ucv32_t to, size_t *count);

size_t uv32_replace_uc32_us32(uv32_t *view, uc32_t from, const us32_t *to);
size_t uv32_replace_uc32_us32_c(uv32_t *view, uc32_t from, const us32_t *to, size_t *count);

size_t uv32_replace_uc32_uv32(uv32_t *view, uc32_t from, uv32_t to);
size_t uv32_replace_uc32_uv32_c(uv32_t *view, uc32_t from, uv32_t to, size_t *count);

size_t uv32_replace_uz32_uz32(uv32_t *view, const uc32_t *from, const uc32_t *to);
size_t uv32_replace_uz32_uz32_c(uv32_t *view, const uc32_t *from, const uc32_t *to, size_t *count);

size_t uv32_replace_uz32_n_uz32(uv32_t *view, const uc32_t *from, size_t from_len, const uc32_t *to);
size_t uv32_replace_uz32_n_uz32_c(uv32_t *view, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count);

size_t uv32_replace_ucv32_uz32(uv32_t *view, ucv32_t from, const uc32_t *to);
size_t uv32_replace_ucv32_uz32_c(uv32_t *view, ucv32_t from, const uc32_t *to, size_t *count);

size_t uv32_replace_us32_uz32(uv32_t *view, const us32_t *from, const uc32_t *to);
size_t uv32_replace_us32_uz32_c(uv32_t *view, const us32_t *from, const uc32_t *to, size_t *count);

size_t uv32_replace_uv32_uz32(uv32_t *view, uv32_t from, const uc32_t *to);
size_t uv32_replace_uv32_uz32_c(uv32_t *view, uv32_t from, const uc32_t *to, size_t *count);

size_t uv32_replace_uz32_uz32_n(uv32_t *view, const uc32_t *from, const uc32_t *to, size_t to_len);
size_t uv32_replace_uz32_uz32_n_c(uv32_t *view, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count);

size_t uv32_replace_uz32_n_uz32_n(uv32_t *view, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len);
size_t uv32_replace_uz32_n_uz32_n_c(uv32_t *view, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count);

size_t uv32_replace_ucv32_uz32_n(uv32_t *view, ucv32_t from, const uc32_t *to, size_t to_len);
size_t uv32_replace_ucv32_uz32_n_c(uv32_t *view, ucv32_t from, const uc32_t *to, size_t to_len, size_t *count);

size_t uv32_replace_us32_uz32_n(uv32_t *view, const us32_t *from, const uc32_t *to, size_t to_len);
size_t uv32_replace_us32_uz32_n_c(uv32_t *view, const us32_t *from, const uc32_t *to, size_t to_len, size_t *count);

size_t uv32_replace_uv32_uz32_n(uv32_t *view, uv32_t from, const uc32_t *to, size_t to_len);
size_t uv32_replace_uv32_uz32_n_c(uv32_t *view, uv32_t from, const uc32_t *to, size_t to_len, size_t *count);

size_t uv32_replace_uz32_ucv32(uv32_t *view, const uc32_t *from, ucv32_t to);
size_t uv32_replace_uz32_ucv32_c(uv32_t *view, const uc32_t *from, ucv32_t to, size_t *count);

size_t uv32_replace_uz32_n_ucv32(uv32_t *view, const uc32_t *from, size_t from_len, ucv32_t to);
size_t uv32_replace_uz32_n_ucv32_c(uv32_t *view, const uc32_t *from, size_t from_len, ucv32_t to, size_t *count);

size_t uv32_replace_ucv32_ucv32(uv32_t *view, ucv32_t from, ucv32_t to);
size_t uv32_replace_ucv32_ucv32_c(uv32_t *view, ucv32_t from, ucv32_t to, size_t *count);

size_t uv32_replace_us32_ucv32(uv32_t *view, const us32_t *from, ucv32_t to);
size_t uv32_replace_us32_ucv32_c(uv32_t *view, const us32_t *from, ucv32_t to, size_t *count);

size_t uv32_replace_uv32_ucv32(uv32_t *view, uv32_t from, ucv32_t to);
size_t uv32_replace_uv32_ucv32_c(uv32_t *view, uv32_t from, ucv32_t to, size_t *count);

size_t uv32_replace_uz32_us32(uv32_t *view, const uc32_t *from, const us32_t *to);
size_t uv32_replace_uz32_us32_c(uv32_t *view, const uc32_t *from, const us32_t *to, size_t *count);

size_t uv32_replace_uz32_n_us32(uv32_t *view, const uc32_t *from, size_t from_len, const us32_t *to);
size_t uv32_replace_uz32_n_us32_c(uv32_t *view, const uc32_t *from, size_t from_len, const us32_t *to, size_t *count);

size_t uv32_replace_ucv32_us32(uv32_t *view, ucv32_t from, const us32_t *to);
size_t uv32_replace_ucv32_us32_c(uv32_t *view, ucv32_t from, const us32_t *to, size_t *count);

size_t uv32_replace_us32_us32(uv32_t *view, const us32_t *from, const us32_t *to);
size_t uv32_replace_us32_us32_c(uv32_t *view, const us32_t *from, const us32_t *to, size_t *count);

size_t uv32_replace_uv32_us32(uv32_t *view, uv32_t from, const us32_t *to);
size_t uv32_replace_uv32_us32_c(uv32_t *view, uv32_t from, const us32_t *to, size_t *count);

size_t uv32_replace_uz32_uv32(uv32_t *view, const uc32_t *from, uv32_t to);
size_t uv32_replace_uz32_uv32_c(uv32_t *view, const uc32_t *from, uv32_t to, size_t *count);

size_t uv32_replace_uz32_n_uv32(uv32_t *view, const uc32_t *from, size_t from_len, uv32_t to);
size_t uv32_replace_uz32_n_uv32_c(uv32_t *view, const uc32_t *from, size_t from_len, uv32_t to, size_t *count);

size_t uv32_replace_ucv32_uv32(uv32_t *view, ucv32_t from, uv32_t to);
size_t uv32_replace_ucv32_uv32_c(uv32_t *view, ucv32_t from, uv32_t to, size_t *count);

size_t uv32_replace_us32_uv32(uv32_t *view, const us32_t *from, uv32_t to);
size_t uv32_replace_us32_uv32_c(uv32_t *view, const us32_t *from, uv32_t to, size_t *count);

size_t uv32_replace_uv32_uv32(uv32_t *view, uv32_t from, uv32_t to);
size_t uv32_replace_uv32_uv32_c(uv32_t *view, uv32_t from, uv32_t to, size_t *count);

// Chars

const uc32_t *uv32_cchars(uv32_t view);
uc32_t *uv32_chars(uv32_t view);
void uv32_set_chars(uv32_t *view, uc32_t *chars);

// Valid

bool uv32_valid_p(const uv32_t *view);
bool uv32_valid(uv32_t view);

#endif