#ifndef USTR_STR_H
#define USTR_STR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "type/fmt/case.h"
#include "type/fmt/int.h"
#include "type/char.h"
#include "type/cview.h"
#include "type/str.h"
#include "type/view.h"

// Expand

#define US32_EXPAND(str)  us32_chars(str),  (str)->len
#define US32_CEXPAND(str) us32_cchars(str), (str)->len

// Creation

#define us32(literal) us32_from_uz32_n(U##literal, sizeof(U""literal) / sizeof(uc32_t) - 1)

us32_t us32_mk(void);
us32_t us32_from(us32_t *str);
us32_t us32_from_e(us32_t *str, bool *error);
us32_t us32_from_us32_range(us32_t *str, size_t from, size_t len);
us32_t us32_from_us32_range_e(us32_t *str, size_t from, size_t len, bool *error);
us32_t us32_from_uv32(uv32_t view);
us32_t us32_from_uv32_e(uv32_t view, bool *error);
us32_t us32_from_uv32_range(uv32_t view, size_t from, size_t len);
us32_t us32_from_uv32_range_e(uv32_t view, size_t from, size_t len, bool *error);
us32_t us32_from_ucv32(ucv32_t view);
us32_t us32_from_ucv32_e(ucv32_t view, bool *error);
us32_t us32_from_ucv32_range(ucv32_t view, size_t from, size_t len);
us32_t us32_from_ucv32_range_e(ucv32_t view, size_t from, size_t len, bool *error);
us32_t us32_from_uz32(uc32_t *cstr);
us32_t us32_from_uz32_e(uc32_t *cstr, bool *error);
us32_t us32_from_uz32_n(uc32_t *cstr, size_t n);
us32_t us32_from_uz32_n_e(uc32_t *cstr, size_t n, bool *error);
us32_t us32_from_uc32(uc32_t c);
us32_t us32_from_uc32_e(uc32_t c, bool *error);
us32_t us32_from_uc32_n(uc32_t c, size_t n);
us32_t us32_from_uc32_n_e(uc32_t c, size_t n, bool *error);
us32_t us32_from_int(intmax_t i);
us32_t us32_from_int_e(intmax_t i, bool *error);
us32_t us32_from_int_fmt(intmax_t i, const struct uifmt *fmt);
us32_t us32_from_int_fmt_e(intmax_t i, const struct uifmt *fmt, bool *error);
us32_t us32_from_uint(uintmax_t i);
us32_t us32_from_uint_e(uintmax_t i, bool *error);
us32_t us32_from_uint_fmt(uintmax_t i, const struct uifmt *fmt);
us32_t us32_from_uint_fmt_e(uintmax_t i, const struct uifmt *fmt, bool *error);

// Free 

void us32_free(us32_t *str);

// Cross-UTF Len

size_t us32_uz16_len(const us32_t *str);
size_t us32_uz8_len(const us32_t *str);

// Append

size_t us32_append(us32_t *str, const us32_t *another);
size_t us32_append_e(us32_t *str, const us32_t *another, bool *error);
size_t us32_append_uv32(us32_t *str, uv32_t view);
size_t us32_append_uv32_e(us32_t *str, uv32_t view, bool *error);
size_t us32_append_ucv32(us32_t *str, ucv32_t view);
size_t us32_append_ucv32_e(us32_t *str, ucv32_t view, bool *error);
size_t us32_append_uc32(us32_t *str, uc32_t c);
size_t us32_append_uc32_e(us32_t *str, uc32_t c, bool *error);
size_t us32_append_uc32_n(us32_t *str, uc32_t c, size_t n);
size_t us32_append_uc32_n_e(us32_t *str, uc32_t c, size_t n, bool *error);
size_t us32_append_uz32(us32_t *str, const uc32_t *cstr);
size_t us32_append_uz32_e(us32_t *str, const uc32_t *cstr, bool *error);
size_t us32_append_uz32_n(us32_t *str, const uc32_t *cstr, size_t n);
size_t us32_append_uz32_n_e(us32_t *str, const uc32_t *cstr, size_t n, bool *error);
size_t us32_append_int(us32_t *str, intmax_t i);
size_t us32_append_int_e(us32_t *str, intmax_t i, bool *error);
size_t us32_append_int_fmt(us32_t *str, intmax_t i, const struct uifmt *fmt);
size_t us32_append_int_fmt_e(us32_t *str, intmax_t i, const struct uifmt *fmt, bool *error);
size_t us32_append_uint(us32_t *str, uintmax_t i);
size_t us32_append_uint_e(us32_t *str, uintmax_t i, bool *error);
size_t us32_append_uint_fmt(us32_t *str, uintmax_t i, const struct uifmt *fmt);
size_t us32_append_uint_fmt_e(us32_t *str, uintmax_t i, const struct uifmt *fmt, bool *error);

// Reverse

void us32_reverse(us32_t *str);

// Trim

size_t us32_trim(us32_t *str);
size_t us32_trim_left(us32_t *str);
size_t us32_trim_right(us32_t *str);

// Char

uc32_t us32_uc32(const us32_t *str, size_t index);
void us32_set_uc32(us32_t *str, uc32_t c, size_t index);

// Cmp

int us32_cmp(const us32_t *lhs, const us32_t *rhs);
int us32_cmp_n(const us32_t *lhs, const us32_t *rhs, size_t n);
int us32_cmp_uv32(const us32_t *lhs, uv32_t rhs);
int us32_cmp_uv32_n(const us32_t *lhs, uv32_t rhs, size_t n);
int us32_cmp_ucv32(const us32_t *lhs, ucv32_t rhs);
int us32_cmp_ucv32_n(const us32_t *lhs, ucv32_t rhs, size_t n);
int us32_cmp_uz32(const us32_t *lhs, const uc32_t *rhs);
int us32_cmp_uz32_n(const us32_t *lhs, const uc32_t *rhs, size_t n);

// Search

// - Forward

ptrdiff_t us32_pos(const us32_t *str, const us32_t *another);
ptrdiff_t us32_pos_from(const us32_t *str, const us32_t *another, size_t from);
ptrdiff_t us32_uc32_pos(const us32_t *str, uc32_t c);
ptrdiff_t us32_uc32_pos_from(const us32_t *str, uc32_t c, size_t from);
ptrdiff_t us32_uz32_pos(const us32_t *str, const uc32_t *cstr);
ptrdiff_t us32_uz32_pos_from(const us32_t *str, const uc32_t *cstr, size_t from);
ptrdiff_t us32_uz32_n_pos(const us32_t *str, const uc32_t *cstr, size_t n);
ptrdiff_t us32_uz32_n_pos_from(const us32_t *str, const uc32_t *cstr, size_t n, size_t from);
ptrdiff_t us32_uv32_pos(const us32_t *str, uv32_t view);
ptrdiff_t us32_uv32_pos_from(const us32_t *str, uv32_t view, size_t from);
ptrdiff_t us32_ucv32_pos(const us32_t *str, ucv32_t view);
ptrdiff_t us32_ucv32_pos_from(const us32_t *str, ucv32_t view, size_t from);

// - Backward

ptrdiff_t us32_pos_r(const us32_t *str, const us32_t *another);
ptrdiff_t us32_pos_from_r(const us32_t *str, const us32_t *another, size_t from);
ptrdiff_t us32_uc32_pos_r(const us32_t *str, uc32_t c);
ptrdiff_t us32_uc32_pos_from_r(const us32_t *str, uc32_t c, size_t from);
ptrdiff_t us32_uz32_pos_r(const us32_t *str, const uc32_t *cstr);
ptrdiff_t us32_uz32_pos_from_r(const us32_t *str, const uc32_t *cstr, size_t from);
ptrdiff_t us32_uz32_n_pos_r(const us32_t *str, const uc32_t *cstr, size_t n);
ptrdiff_t us32_uz32_n_pos_from_r(const us32_t *str, const uc32_t *cstr, size_t n, size_t from);
ptrdiff_t us32_uv32_pos_r(const us32_t *str, uv32_t view);
ptrdiff_t us32_uv32_pos_from_r(const us32_t *str, uv32_t view, size_t from);
ptrdiff_t us32_ucv32_pos_r(const us32_t *str, ucv32_t view);
ptrdiff_t us32_ucv32_pos_from_r(const us32_t *str, ucv32_t view, size_t from);

// Fill

void us32_fill(us32_t *str, uc32_t c);
void us32_fill_from(us32_t *str, uc32_t c, size_t from);
void us32_fill_to(us32_t *str, uc32_t c, size_t to);
void us32_fill_range(us32_t *str, uc32_t c, size_t from, size_t len);
void us32_fill_uz32(us32_t *str, const uc32_t *cstr);
void us32_fill_uz32_from(us32_t *str, const uc32_t *cstr, size_t from);
void us32_fill_uz32_to(us32_t *str, const uc32_t *cstr, size_t to);
void us32_fill_uz32_range(us32_t *str, const uc32_t *cstr, size_t from, size_t len);
void us32_fill_uz32_n(us32_t *str, const uc32_t *cstr, size_t n);
void us32_fill_uz32_n_from(us32_t *str, const uc32_t *cstr, size_t n, size_t from);
void us32_fill_uz32_n_to(us32_t *str, const uc32_t *cstr, size_t n, size_t to);
void us32_fill_uz32_n_range(us32_t *str, const uc32_t *cstr, size_t n, size_t from, size_t len);
void us32_fill_uv32(us32_t *str, uv32_t view);
void us32_fill_uv32_from(us32_t *str, uv32_t view, size_t from);
void us32_fill_uv32_to(us32_t *str, uv32_t view, size_t to);
void us32_fill_uv32_range(us32_t *str, uv32_t view, size_t from, size_t len);
void us32_fill_ucv32(us32_t *str, ucv32_t view);
void us32_fill_ucv32_from(us32_t *str, ucv32_t view, size_t from);
void us32_fill_ucv32_to(us32_t *str, ucv32_t view, size_t to);
void us32_fill_ucv32_range(us32_t *str, ucv32_t view, size_t from, size_t len);
void us32_fill_us32(us32_t *str, const us32_t *another);
void us32_fill_us32_from(us32_t *str, const us32_t *another, size_t from);
void us32_fill_us32_to(us32_t *str, const us32_t *another, size_t to);
void us32_fill_us32_range(us32_t *str, const us32_t *another, size_t from, size_t len);

// Case Change

void us32_to_case(us32_t *str, ucase_t ca);
void us32_to_upper(us32_t *str);
void us32_to_lower(us32_t *str);

// Iteration

uc32_t *us32_begin(us32_t *str);
const uc32_t *us32_cbegin(const us32_t *str);
uc32_t *us32_end(us32_t *str);
const uc32_t *us32_cend(const us32_t *str);
uc32_t *us32_at(us32_t *str, size_t index);
const uc32_t *us32_cat(const us32_t *str, size_t index);

// Len

bool us32_bounds(const us32_t *str, size_t index);
bool us32_ebounds(const us32_t *str, size_t index);
size_t us32_len(const us32_t *str);
size_t us32_add_len(us32_t *str, ptrdiff_t delta);
size_t us32_add_len_e(us32_t *str, ptrdiff_t delta, bool *error);
size_t us32_set_len(us32_t *str, size_t len);
size_t us32_set_len_e(us32_t *str, size_t len, bool *error);
bool us32_empty(const us32_t *str);
void us32_clear(us32_t *str);

// Cap

size_t us32_cap(const us32_t *str);
size_t us32_set_cap(us32_t *str, size_t cap);
size_t us32_set_cap_e(us32_t *str, size_t cap, bool *error);
size_t us32_shrink_to_fit(us32_t *str);
size_t us32_shrink_to_fit_e(us32_t *str, bool *error);
size_t us32_raise_if_needed(us32_t *str);
size_t us32_raise_if_needed_e(us32_t *str, bool *error);
size_t us32_raise(us32_t *str);
size_t us32_raise_e(us32_t *str, bool *error);
size_t us32_raise_to(us32_t *str, size_t to);
size_t us32_raise_to_e(us32_t *str, size_t to, bool *error);

// Split

size_t us32_new_csplit(const us32_t *str, uc32_t c, ucv32_t **array);
size_t us32_new_csplit_e(const us32_t *str, uc32_t c, ucv32_t **array, bool *error);
size_t us32_csplit(const us32_t *str, uc32_t c, ucv32_t *array, size_t array_len);
size_t us32_new_split(us32_t *str, uc32_t c, uv32_t **array);
size_t us32_new_split_e(us32_t *str, uc32_t c, uv32_t **array, bool *error);
size_t us32_split(us32_t *str, uc32_t c, uv32_t *array, size_t array_len);

size_t us32_new_csplit_uz32(const us32_t *str, const uc32_t *cstr, ucv32_t **array);
size_t us32_new_csplit_uz32_e(const us32_t *str, const uc32_t *cstr, ucv32_t **array, bool *error);
size_t us32_csplit_uz32(const us32_t *str, const uc32_t *cstr, ucv32_t *array, size_t array_len);
size_t us32_new_split_uz32(us32_t *str, const uc32_t *cstr, uv32_t **array);
size_t us32_new_split_uz32_e(us32_t *str, const uc32_t *cstr, uv32_t **array, bool *error);
size_t us32_split_uz32(us32_t *str, const uc32_t *cstr, uv32_t *array, size_t array_len);

size_t us32_new_csplit_uz32_n(const us32_t *str, const uc32_t *cstr, size_t n, ucv32_t **array);
size_t us32_new_csplit_uz32_n_e(const us32_t *str, const uc32_t *cstr, size_t n, ucv32_t **array, bool *error);
size_t us32_csplit_uz32_n(const us32_t *str, const uc32_t *cstr, size_t n, ucv32_t *array, size_t array_len);
size_t us32_new_split_uz32_n(us32_t *str, const uc32_t *cstr, size_t n, uv32_t **array);
size_t us32_new_split_uz32_n_e(us32_t *str, const uc32_t *cstr, size_t n, uv32_t **array, bool *error);
size_t us32_split_uz32_n(us32_t *str, const uc32_t *cstr, size_t n, uv32_t *array, size_t array_len);

size_t us32_new_csplit_us32(const us32_t *str, const us32_t *another, ucv32_t **array);
size_t us32_new_csplit_us32_e(const us32_t *str, const us32_t *another, ucv32_t **array, bool *error);
size_t us32_csplit_us32(const us32_t *str, const us32_t *another, ucv32_t *array, size_t array_len);
size_t us32_new_split_us32(us32_t *str, const us32_t *another, uv32_t **array);
size_t us32_new_split_us32_e(us32_t *str, const us32_t *another, uv32_t **array, bool *error);
size_t us32_split_us32(us32_t *str, const us32_t *another, uv32_t *array, size_t array_len);

size_t us32_new_csplit_uv32(const us32_t *str, uv32_t view, ucv32_t **array);
size_t us32_new_csplit_uv32_e(const us32_t *str, uv32_t view, ucv32_t **array, bool *error);
size_t us32_csplit_uv32(const us32_t *str, uv32_t view, ucv32_t *array, size_t array_len);
size_t us32_new_split_uv32(us32_t *str, uv32_t view, uv32_t **array);
size_t us32_new_split_uv32_e(us32_t *str, uv32_t view, uv32_t **array, bool *error);
size_t us32_split_uv32(us32_t *str, uv32_t view, uv32_t *array, size_t array_len);

size_t us32_new_csplit_ucv32(const us32_t *str, ucv32_t view, ucv32_t **array);
size_t us32_new_csplit_ucv32_e(const us32_t *str, ucv32_t view, ucv32_t **array, bool *error);
size_t us32_csplit_ucv32(const us32_t *str, ucv32_t view, ucv32_t *array, size_t array_len);
size_t us32_new_split_ucv32(us32_t *str, ucv32_t view, uv32_t **array);
size_t us32_new_split_ucv32_e(us32_t *str, ucv32_t view, uv32_t **array, bool *error);
size_t us32_split_ucv32(us32_t *str, ucv32_t view, uv32_t *array, size_t array_len);

// Replace

size_t us32_replace_uc32_uc32(us32_t *str, uc32_t from, uc32_t to);
size_t us32_replace_uc32_uc32_c(us32_t *str, uc32_t from, uc32_t to, size_t *count);

size_t us32_replace_uz32_uc32(us32_t *str, const uc32_t *from, uc32_t to);
size_t us32_replace_uz32_uc32_c(us32_t *str, const uc32_t *from, uc32_t to, size_t *count);

size_t us32_replace_uz32_n_uc32(us32_t *str, const uc32_t *from, size_t from_len, uc32_t to);
size_t us32_replace_uz32_n_uc32_c(us32_t *str, const uc32_t *from, size_t from_len, uc32_t to, size_t *count);

size_t us32_replace_ucv32_uc32(us32_t *str, ucv32_t from, uc32_t to);
size_t us32_replace_ucv32_uc32_c(us32_t *str, ucv32_t from, uc32_t to, size_t *count);

size_t us32_replace_us32_uc32(us32_t *str, const us32_t *from, uc32_t to);
size_t us32_replace_us32_uc32_c(us32_t *str, const us32_t *from, uc32_t to, size_t *count);

size_t us32_replace_uv32_uc32(us32_t *str, uv32_t from, uc32_t to);
size_t us32_replace_uv32_uc32_c(us32_t *str, uv32_t from, uc32_t to, size_t *count);

size_t us32_replace_uc32_uz32(us32_t *str, uc32_t from, const uc32_t *to);
size_t us32_replace_uc32_uz32_e(us32_t *str, uc32_t from, const uc32_t *to, bool *error);
size_t us32_replace_uc32_uz32_c(us32_t *str, uc32_t from, const uc32_t *to, size_t *count);
size_t us32_replace_uc32_uz32_c_e(us32_t *str, uc32_t from, const uc32_t *to, size_t *count, bool *error);

size_t us32_replace_uc32_uz32_n(us32_t *str, uc32_t from, const uc32_t *to, size_t to_len);
size_t us32_replace_uc32_uz32_n_e(us32_t *str, uc32_t from, const uc32_t *to, size_t to_len, bool *error);
size_t us32_replace_uc32_uz32_n_c(us32_t *str, uc32_t from, const uc32_t *to, size_t to_len, size_t *count);
size_t us32_replace_uc32_uz32_n_c_e(us32_t *str, uc32_t from, const uc32_t *to, size_t to_len, size_t *count, bool *error);

size_t us32_replace_uc32_ucv32(us32_t *str, uc32_t from, ucv32_t to);
size_t us32_replace_uc32_ucv32_e(us32_t *str, uc32_t from, ucv32_t to, bool *error);
size_t us32_replace_uc32_ucv32_c(us32_t *str, uc32_t from, ucv32_t to, size_t *count);
size_t us32_replace_uc32_ucv32_c_e(us32_t *str, uc32_t from, ucv32_t to, size_t *count, bool *error);

size_t us32_replace_uc32_us32(us32_t *str, uc32_t from, const us32_t *to);
size_t us32_replace_uc32_us32_e(us32_t *str, uc32_t from, const us32_t *to, bool *error);
size_t us32_replace_uc32_us32_c(us32_t *str, uc32_t from, const us32_t *to, size_t *count);
size_t us32_replace_uc32_us32_c_e(us32_t *str, uc32_t from, const us32_t *to, size_t *count, bool *error);

size_t us32_replace_uc32_uv32(us32_t *str, uc32_t from, uv32_t to);
size_t us32_replace_uc32_uv32_e(us32_t *str, uc32_t from, uv32_t to, bool *error);
size_t us32_replace_uc32_uv32_c(us32_t *str, uc32_t from, uv32_t to, size_t *count);
size_t us32_replace_uc32_uv32_c_e(us32_t *str, uc32_t from, uv32_t to, size_t *count, bool *error);

size_t us32_replace_uz32_uz32(us32_t *str, const uc32_t *from, const uc32_t *to);
size_t us32_replace_uz32_uz32_e(us32_t *str, const uc32_t *from, const uc32_t *to, bool *error);
size_t us32_replace_uz32_uz32_c(us32_t *str, const uc32_t *from, const uc32_t *to, size_t *count);
size_t us32_replace_uz32_uz32_c_e(us32_t *str, const uc32_t *from, const uc32_t *to, size_t *count, bool *error);

size_t us32_replace_uz32_n_uz32(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to);
size_t us32_replace_uz32_n_uz32_e(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, bool *error);
size_t us32_replace_uz32_n_uz32_c(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count);
size_t us32_replace_uz32_n_uz32_c_e(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count, bool *error);

size_t us32_replace_ucv32_uz32(us32_t *str, ucv32_t from, const uc32_t *to);
size_t us32_replace_ucv32_uz32_e(us32_t *str, ucv32_t from, const uc32_t *to, bool *error);
size_t us32_replace_ucv32_uz32_c(us32_t *str, ucv32_t from, const uc32_t *to, size_t *count);
size_t us32_replace_ucv32_uz32_c_e(us32_t *str, ucv32_t from, const uc32_t *to, size_t *count, bool *error);

size_t us32_replace_us32_uz32(us32_t *str, const us32_t *from, const uc32_t *to);
size_t us32_replace_us32_uz32_e(us32_t *str, const us32_t *from, const uc32_t *to, bool *error);
size_t us32_replace_us32_uz32_c(us32_t *str, const us32_t *from, const uc32_t *to, size_t *count);
size_t us32_replace_us32_uz32_c_e(us32_t *str, const us32_t *from, const uc32_t *to, size_t *count, bool *error);

size_t us32_replace_uv32_uz32(us32_t *str, uv32_t from, const uc32_t *to);
size_t us32_replace_uv32_uz32_e(us32_t *str, uv32_t from, const uc32_t *to, bool *error);
size_t us32_replace_uv32_uz32_c(us32_t *str, uv32_t from, const uc32_t *to, size_t *count);
size_t us32_replace_uv32_uz32_c_e(us32_t *str, uv32_t from, const uc32_t *to, size_t *count, bool *error);

size_t us32_replace_uz32_uz32_n(us32_t *str, const uc32_t *from, const uc32_t *to, size_t to_len);
size_t us32_replace_uz32_uz32_n_e(us32_t *str, const uc32_t *from, const uc32_t *to, size_t to_len, bool *error);
size_t us32_replace_uz32_uz32_n_c(us32_t *str, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count);
size_t us32_replace_uz32_uz32_n_c_e(us32_t *str, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count, bool *error);

size_t us32_replace_uz32_n_uz32_n(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len);
size_t us32_replace_uz32_n_uz32_n_e(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, bool *error);
size_t us32_replace_uz32_n_uz32_n_c(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count);
size_t us32_replace_uz32_n_uz32_n_c_e(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count, bool *error);

size_t us32_replace_ucv32_uz32_n(us32_t *str, ucv32_t from, const uc32_t *to, size_t to_len);
size_t us32_replace_ucv32_uz32_n_e(us32_t *str, ucv32_t from, const uc32_t *to, size_t to_len, bool *error);
size_t us32_replace_ucv32_uz32_n_c(us32_t *str, ucv32_t from, const uc32_t *to, size_t to_len, size_t *count);
size_t us32_replace_ucv32_uz32_n_c_e(us32_t *str, ucv32_t from, const uc32_t *to, size_t to_len, size_t *count, bool *error);

size_t us32_replace_us32_uz32_n(us32_t *str, const us32_t *from, const uc32_t *to, size_t to_len);
size_t us32_replace_us32_uz32_n_e(us32_t *str, const us32_t *from, const uc32_t *to, size_t to_len, bool *error);
size_t us32_replace_us32_uz32_n_c(us32_t *str, const us32_t *from, const uc32_t *to, size_t to_len, size_t *count);
size_t us32_replace_us32_uz32_n_c_e(us32_t *str, const us32_t *from, const uc32_t *to, size_t to_len, size_t *count, bool *error);

size_t us32_replace_uv32_uz32_n(us32_t *str, uv32_t from, const uc32_t *to, size_t to_len);
size_t us32_replace_uv32_uz32_n_e(us32_t *str, uv32_t from, const uc32_t *to, size_t to_len, bool *error);
size_t us32_replace_uv32_uz32_n_c(us32_t *str, uv32_t from, const uc32_t *to, size_t to_len, size_t *count);
size_t us32_replace_uv32_uz32_n_c_e(us32_t *str, uv32_t from, const uc32_t *to, size_t to_len, size_t *count, bool *error);

size_t us32_replace_uz32_ucv32(us32_t *str, const uc32_t *from, ucv32_t to);
size_t us32_replace_uz32_ucv32_e(us32_t *str, const uc32_t *from, ucv32_t to, bool *error);
size_t us32_replace_uz32_ucv32_c(us32_t *str, const uc32_t *from, ucv32_t to, size_t *count);
size_t us32_replace_uz32_ucv32_c_e(us32_t *str, const uc32_t *from, ucv32_t to, size_t *count, bool *error);

size_t us32_replace_uz32_n_ucv32(us32_t *str, const uc32_t *from, size_t from_len, ucv32_t to);
size_t us32_replace_uz32_n_ucv32_e(us32_t *str, const uc32_t *from, size_t from_len, ucv32_t to, bool *error);
size_t us32_replace_uz32_n_ucv32_c(us32_t *str, const uc32_t *from, size_t from_len, ucv32_t to, size_t *count);
size_t us32_replace_uz32_n_ucv32_c_e(us32_t *str, const uc32_t *from, size_t from_len, ucv32_t to, size_t *count, bool *error);

size_t us32_replace_ucv32_ucv32(us32_t *str, ucv32_t from, ucv32_t to);
size_t us32_replace_ucv32_ucv32_e(us32_t *str, ucv32_t from, ucv32_t to, bool *error);
size_t us32_replace_ucv32_ucv32_c(us32_t *str, ucv32_t from, ucv32_t to, size_t *count);
size_t us32_replace_ucv32_ucv32_c_e(us32_t *str, ucv32_t from, ucv32_t to, size_t *count, bool *error);

size_t us32_replace_us32_ucv32(us32_t *str, const us32_t *from, ucv32_t to);
size_t us32_replace_us32_ucv32_e(us32_t *str, const us32_t *from, ucv32_t to, bool *error);
size_t us32_replace_us32_ucv32_c(us32_t *str, const us32_t *from, ucv32_t to, size_t *count);
size_t us32_replace_us32_ucv32_c_e(us32_t *str, const us32_t *from, ucv32_t to, size_t *count, bool *error);

size_t us32_replace_uv32_ucv32(us32_t *str, uv32_t from, ucv32_t to);
size_t us32_replace_uv32_ucv32_e(us32_t *str, uv32_t from, ucv32_t to, bool *error);
size_t us32_replace_uv32_ucv32_c(us32_t *str, uv32_t from, ucv32_t to, size_t *count);
size_t us32_replace_uv32_ucv32_c_e(us32_t *str, uv32_t from, ucv32_t to, size_t *count, bool *error);

size_t us32_replace_uz32_us32(us32_t *str, const uc32_t *from, const us32_t *to);
size_t us32_replace_uz32_us32_e(us32_t *str, const uc32_t *from, const us32_t *to, bool *error);
size_t us32_replace_uz32_us32_c(us32_t *str, const uc32_t *from, const us32_t *to, size_t *count);
size_t us32_replace_uz32_us32_c_e(us32_t *str, const uc32_t *from, const us32_t *to, size_t *count, bool *error);

size_t us32_replace_uz32_n_us32(us32_t *str, const uc32_t *from, size_t from_len, const us32_t *to);
size_t us32_replace_uz32_n_us32_e(us32_t *str, const uc32_t *from, size_t from_len, const us32_t *to, bool *error);
size_t us32_replace_uz32_n_us32_c(us32_t *str, const uc32_t *from, size_t from_len, const us32_t *to, size_t *count);
size_t us32_replace_uz32_n_us32_c_e(us32_t *str, const uc32_t *from, size_t from_len, const us32_t *to, size_t *count, bool *error);

size_t us32_replace_ucv32_us32(us32_t *str, ucv32_t from, const us32_t *to);
size_t us32_replace_ucv32_us32_e(us32_t *str, ucv32_t from, const us32_t *to, bool *error);
size_t us32_replace_ucv32_us32_c(us32_t *str, ucv32_t from, const us32_t *to, size_t *count);
size_t us32_replace_ucv32_us32_c_e(us32_t *str, ucv32_t from, const us32_t *to, size_t *count, bool *error);

size_t us32_replace_us32_us32(us32_t *str, const us32_t *from, const us32_t *to);
size_t us32_replace_us32_us32_e(us32_t *str, const us32_t *from, const us32_t *to, bool *error);
size_t us32_replace_us32_us32_c(us32_t *str, const us32_t *from, const us32_t *to, size_t *count);
size_t us32_replace_us32_us32_c_e(us32_t *str, const us32_t *from, const us32_t *to, size_t *count, bool *error);

size_t us32_replace_uv32_us32(us32_t *str, uv32_t from, const us32_t *to);
size_t us32_replace_uv32_us32_e(us32_t *str, uv32_t from, const us32_t *to, bool *error);
size_t us32_replace_uv32_us32_c(us32_t *str, uv32_t from, const us32_t *to, size_t *count);
size_t us32_replace_uv32_us32_c_e(us32_t *str, uv32_t from, const us32_t *to, size_t *count, bool *error);

size_t us32_replace_uz32_uv32(us32_t *str, const uc32_t *from, uv32_t to);
size_t us32_replace_uz32_uv32_e(us32_t *str, const uc32_t *from, uv32_t to, bool *error);
size_t us32_replace_uz32_uv32_c(us32_t *str, const uc32_t *from, uv32_t to, size_t *count);
size_t us32_replace_uz32_uv32_c_e(us32_t *str, const uc32_t *from, uv32_t to, size_t *count, bool *error);

size_t us32_replace_uz32_n_uv32(us32_t *str, const uc32_t *from, size_t from_len, uv32_t to);
size_t us32_replace_uz32_n_uv32_e(us32_t *str, const uc32_t *from, size_t from_len, uv32_t to, bool *error);
size_t us32_replace_uz32_n_uv32_c(us32_t *str, const uc32_t *from, size_t from_len, uv32_t to, size_t *count);
size_t us32_replace_uz32_n_uv32_c_e(us32_t *str, const uc32_t *from, size_t from_len, uv32_t to, size_t *count, bool *error);

size_t us32_replace_ucv32_uv32(us32_t *str, ucv32_t from, uv32_t to);
size_t us32_replace_ucv32_uv32_e(us32_t *str, ucv32_t from, uv32_t to, bool *error);
size_t us32_replace_ucv32_uv32_c(us32_t *str, ucv32_t from, uv32_t to, size_t *count);
size_t us32_replace_ucv32_uv32_c_e(us32_t *str, ucv32_t from, uv32_t to, size_t *count, bool *error);

size_t us32_replace_us32_uv32(us32_t *str, const us32_t *from, uv32_t to);
size_t us32_replace_us32_uv32_e(us32_t *str, const us32_t *from, uv32_t to, bool *error);
size_t us32_replace_us32_uv32_c(us32_t *str, const us32_t *from, uv32_t to, size_t *count);
size_t us32_replace_us32_uv32_c_e(us32_t *str, const us32_t *from, uv32_t to, size_t *count, bool *error);

size_t us32_replace_uv32_uv32(us32_t *str, uv32_t from, uv32_t to);
size_t us32_replace_uv32_uv32_e(us32_t *str, uv32_t from, uv32_t to, bool *error);
size_t us32_replace_uv32_uv32_c(us32_t *str, uv32_t from, uv32_t to, size_t *count);
size_t us32_replace_uv32_uv32_c_e(us32_t *str, uv32_t from, uv32_t to, size_t *count, bool *error);

// Chars

const uc32_t *us32_cchars(const us32_t *str);
uc32_t *us32_chars(us32_t *str);

// Valid

bool us32_valid(const us32_t *str);

#endif