#ifndef USTR_CSTR_H
#define USTR_CSTR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "type/fmt/case.h"
#include "type/fmt/float.h"
#include "type/fmt/int.h"
#include "type/char.h"
#include "type/cview.h"
#include "type/view.h"

// Creation

// - From literal

#define uz32(literal) (uc32_t *)  U##literal
#define uz16(literal) (uc16_t *)  u##literal
#define  uz8(literal)  (uc8_t *) u8##literal

// - From float

size_t uz32_from_float(uc32_t *cstr, long double f);
size_t uz32_from_float_fmt(uc32_t *cstr, long double f, const struct uffmt *fmt);

size_t uz16_from_float(uc16_t *cstr, long double f);
size_t uz16_from_float_fmt(uc16_t *cstr, long double f, const struct uffmt *fmt);

size_t uz8_from_float(uc8_t *cstr, long double f);
size_t uz8_from_float_fmt(uc8_t *cstr, long double f, const struct uffmt *fmt);

// - From int

size_t uz32_from_int(uc32_t *cstr, intmax_t i);
size_t uz32_from_int_fmt(uc32_t *cstr, intmax_t i, const struct uifmt *fmt);
size_t uz32_from_uint(uc32_t *cstr, uintmax_t i);
size_t uz32_from_uint_fmt(uc32_t *cstr, uintmax_t i, const struct uifmt *fmt);

size_t uz16_from_int(uc16_t *cstr, intmax_t i);
size_t uz16_from_int_fmt(uc16_t *cstr, intmax_t i, const struct uifmt *fmt);
size_t uz16_from_uint(uc16_t *cstr, uintmax_t i);
size_t uz16_from_uint_fmt(uc16_t *cstr, uintmax_t i, const struct uifmt *fmt);

size_t uz8_from_int(uc8_t *cstr, intmax_t i);
size_t uz8_from_int_fmt(uc8_t *cstr, intmax_t i, const struct uifmt *fmt);
size_t uz8_from_uint(uc8_t *cstr, uintmax_t i);
size_t uz8_from_uint_fmt(uc8_t *cstr, uintmax_t i, const struct uifmt *fmt);

// - From bool

size_t uz32_from_bool(uc32_t *cstr, bool b);
size_t uz32_from_case_bool(uc32_t *cstr, bool b, ucase_t c);
size_t uz32_from_upper_bool(uc32_t *cstr, bool b);
size_t uz32_from_lower_bool(uc32_t *cstr, bool b);

size_t uz16_from_bool(uc16_t *cstr, bool b);
size_t uz16_from_case_bool(uc16_t *cstr, bool b, ucase_t c);
size_t uz16_from_upper_bool(uc16_t *cstr, bool b);
size_t uz16_from_lower_bool(uc16_t *cstr, bool b);

size_t uz8_from_bool(uc8_t *cstr, bool b);
size_t uz8_from_case_bool(uc8_t *cstr, bool b, ucase_t c);
size_t uz8_from_upper_bool(uc8_t *cstr, bool b);
size_t uz8_from_lower_bool(uc8_t *cstr, bool b);

// Lead Count

size_t uz8_trail(const uc8_t *cstr);
size_t uz8_n_trail(const uc8_t *cstr, size_t n);

// Advance

size_t uz32_advance(const uc32_t *cstr, size_t n);
size_t uz16_advance(const uc16_t *cstr, size_t n);
size_t uz8_advance(const uc8_t *cstr, size_t n);

// Retreat

size_t uz32_retreat(const uc32_t *cstr, size_t n);
size_t uz16_retreat(const uc16_t *cstr, size_t n);
size_t uz8_retreat(const uc8_t *cstr, size_t n);

// Convert

// - To UTF-32

size_t uz32_from_uz8(uc32_t *to, const uc8_t *from);
size_t uz32_from_uz8_n(uc32_t *to, const uc8_t *from, size_t n);
size_t uz32_from_uz16(uc32_t *to, const uc16_t *from);
size_t uz32_from_uz16_n(uc32_t *to, const uc16_t *from, size_t n);

// - To UTF-16

size_t uz16_from_uz8(uc16_t *to, const uc8_t *from);
size_t uz16_from_uz8_n(uc16_t *to, const uc8_t *from, size_t n);
size_t uz16_from_uz32(uc16_t *to, const uc32_t *from);
size_t uz16_from_uz32_n(uc16_t *to, const uc32_t *from, size_t n);

// - To UTF-8

size_t uz8_from_uz16(uc8_t *to, const uc16_t *from);
size_t uz8_from_uz16_n(uc8_t *to, const uc16_t *from, size_t n);
size_t uz8_from_uz32(uc8_t *to, const uc32_t *from);
size_t uz8_from_uz32_n(uc8_t *to, const uc32_t *from, size_t n);

// Cross-UTF Len

size_t uz32_8_len(const uc32_t *cstr);
size_t uz32_n_8_len(const uc32_t *cstr, size_t n);
size_t uz32_16_len(const uc32_t *cstr);
size_t uz32_n_16_len(const uc32_t *cstr, size_t n);
size_t uz32_32_len(const uc32_t *cstr);
size_t uz32_n_32_len(const uc32_t *cstr, size_t n);

size_t uz16_8_len(const uc16_t *cstr);
size_t uz16_n_8_len(const uc16_t *cstr, size_t n);
size_t uz16_16_len(const uc16_t *cstr);
size_t uz16_n_16_len(const uc16_t *cstr, size_t n);
size_t uz16_32_len(const uc16_t *cstr);
size_t uz16_n_32_len(const uc16_t *cstr, size_t n);

size_t uz8_8_len(const uc8_t *cstr);
size_t uz8_n_8_len(const uc8_t *cstr, size_t n);
size_t uz8_16_len(const uc8_t *cstr);
size_t uz8_n_16_len(const uc8_t *cstr, size_t n);
size_t uz8_32_len(const uc8_t *cstr);
size_t uz8_n_32_len(const uc8_t *cstr, size_t n);

// Len

size_t uz32_len(const uc32_t *cstr);
size_t uz16_len(const uc16_t *cstr);
size_t uz8_len(const uc8_t *cstr);

// Cmp

int uz32_cmp(const uc32_t *lhs, const uc32_t *rhs);
int uz32_n_cmp(const uc32_t *lhs, size_t n, const uc32_t *rhs);
int uz32_cmp_n(const uc32_t *lhs, const uc32_t *rhs, size_t n);
int uz32_n_cmp_n(const uc32_t *lhs, size_t lhs_len, const uc32_t *rhs, size_t rhs_len);

int uz16_cmp(const uc16_t *lhs, const uc16_t *rhs);
int uz16_n_cmp(const uc16_t *lhs, size_t n, const uc16_t *rhs);
int uz16_cmp_n(const uc16_t *lhs, const uc16_t *rhs, size_t n);
int uz16_n_cmp_n(const uc16_t *lhs, size_t lhs_len, const uc16_t *rhs, size_t rhs_len);

int uz8_cmp(const uc8_t *lhs, const uc8_t *rhs);
int uz8_n_cmp(const uc8_t *lhs, size_t n, const uc8_t *rhs);
int uz8_cmp_n(const uc8_t *lhs, const uc8_t *rhs, size_t n);
int uz8_n_cmp_n(const uc8_t *lhs, size_t lhs_len, const uc8_t *rhs, size_t rhs_len);

// Search

// - Forward

ptrdiff_t uz32_pos(const uc32_t *cstr, const uc32_t *another);
ptrdiff_t uz32_n_pos(const uc32_t *cstr, size_t n, const uc32_t *another);
ptrdiff_t uz32_pos_n(const uc32_t *cstr, const uc32_t *another, size_t n);
ptrdiff_t uz32_n_pos_n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len);
ptrdiff_t uz32_uc32_pos(const uc32_t *cstr, uc32_t c);
ptrdiff_t uz32_n_uc32_pos(const uc32_t *cstr, size_t n, uc32_t c);

ptrdiff_t uz16_pos(const uc16_t *cstr, const uc16_t *another);
ptrdiff_t uz16_n_pos(const uc16_t *cstr, size_t n, const uc16_t *another);
ptrdiff_t uz16_pos_n(const uc16_t *cstr, const uc16_t *another, size_t n);
ptrdiff_t uz16_n_pos_n(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len);
ptrdiff_t uz16_uc32_pos(const uc16_t *cstr, uc16_t c);
ptrdiff_t uz16_n_uc32_pos(const uc16_t *cstr, size_t n, uc16_t c);

ptrdiff_t uz8_pos(const uc8_t *cstr, const uc8_t *another);
ptrdiff_t uz8_n_pos(const uc8_t *cstr, size_t n, const uc8_t *another);
ptrdiff_t uz8_pos_n(const uc8_t *cstr, const uc8_t *another, size_t n);
ptrdiff_t uz8_n_pos_n(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len);
ptrdiff_t uz8_uc8_pos(const uc8_t *cstr, uc8_t c);
ptrdiff_t uz8_n_uc8_pos(const uc8_t *cstr, size_t n, uc8_t c);

// - Backward

ptrdiff_t uz32_pos_r(const uc32_t *cstr, const uc32_t *another, size_t from);
ptrdiff_t uz32_pos_n_r(const uc32_t *cstr, const uc32_t *another, size_t n, size_t from);
ptrdiff_t uz32_n_pos_r(const uc32_t *cstr, size_t n, const uc32_t *another, size_t from);
ptrdiff_t uz32_n_pos_n_r(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, size_t from);
ptrdiff_t uz32_uc32_pos_r(const uc32_t *cstr, uc32_t c, size_t from);
ptrdiff_t uz32_n_uc32_pos_r(const uc32_t *cstr, size_t n, uc32_t c, size_t from);

ptrdiff_t uz16_pos_r(const uc16_t *cstr, const uc16_t *another, size_t from);
ptrdiff_t uz16_pos_n_r(const uc16_t *cstr, const uc16_t *another, size_t n, size_t from);
ptrdiff_t uz16_n_pos_r(const uc16_t *cstr, size_t n, const uc16_t *another, size_t from);
ptrdiff_t uz16_n_pos_n_r(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len, size_t from);
ptrdiff_t uz16_uc16_pos_r(const uc16_t *cstr, uc16_t c, size_t from);
ptrdiff_t uz16_n_uc16_pos_r(const uc16_t *cstr, size_t n, uc16_t c, size_t from);

ptrdiff_t uz8_pos_r(const uc8_t *cstr, const uc8_t *another, size_t from);
ptrdiff_t uz8_pos_n_r(const uc8_t *cstr, const uc8_t *another, size_t n, size_t from);
ptrdiff_t uz8_n_pos_r(const uc8_t *cstr, size_t n, const uc8_t *another, size_t from);
ptrdiff_t uz8_n_pos_n_r(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len, size_t from);
ptrdiff_t uz8_uc8_pos_r(const uc8_t *cstr, uc8_t c, size_t from);
ptrdiff_t uz8_n_uc8_pos_r(const uc8_t *cstr, size_t n, uc8_t c, size_t from);

// Fill

void uz32_fill(uc32_t *cstr, uc32_t c);
void uz32_n_fill(uc32_t *cstr, size_t n, uc32_t c);
void uz32_fill_uz32(uc32_t *cstr, const uc32_t *another);
void uz32_n_fill_uz32(uc32_t *cstr, size_t n, const uc32_t *another);
void uz32_fill_uz32_n(uc32_t *cstr, const uc32_t *another, size_t n);
void uz32_n_fill_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len);

void uz16_fill(uc16_t *cstr, uc16_t c);
void uz16_n_fill(uc16_t *cstr, size_t n, uc16_t c);
void uz16_fill_uz16(uc16_t *cstr, const uc16_t *another);
void uz16_n_fill_uz16(uc16_t *cstr, size_t n, const uc16_t *another);
void uz16_fill_uz16_n(uc16_t *cstr, const uc16_t *another, size_t n);
void uz16_n_fill_uz16_n(uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len);

void uz8_fill(uc8_t *cstr, uc8_t c);
void uz8_n_fill(uc8_t *cstr, size_t n, uc8_t c);
void uz8_fill_uz8(uc8_t *cstr, const uc8_t *another);
void uz8_n_fill_uz8(uc8_t *cstr, size_t n, const uc8_t *another);
void uz8_fill_uz8_n(uc8_t *cstr, const uc8_t *another, size_t n);
void uz8_n_fill_uz8_n(uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len);

// Case Change

size_t uz8_upper_len(const uc8_t *cstr);
size_t uz8_n_upper_len(const uc8_t *cstr, size_t n);
size_t uz8_to_lower_len(const uc8_t *cstr);
size_t uz8_n_lower_len(const uc8_t *cstr, size_t n);
size_t uz8_to_case_len(const uc8_t *cstr, ucase_t ca);
size_t uz8_n_case_len(const uc8_t *cstr, size_t n, ucase_t ca);

void uz32_to_upper(uc32_t *cstr);
void uz32_n_to_upper(uc32_t *cstr, size_t n);
void uz32_to_lower(uc32_t *cstr);
void uz32_n_to_lower(uc32_t *cstr, size_t n);
void uz32_to_case(uc32_t *cstr, ucase_t ca);
void uz32_n_to_case(uc32_t *cstr, size_t n, ucase_t ca);

void uz16_to_upper(uc16_t *cstr);
void uz16_n_to_upper(uc16_t *cstr, size_t n);
void uz16_to_lower(uc16_t *cstr);
void uz16_n_to_lower(uc16_t *cstr, size_t n);
void uz16_to_case(uc16_t *cstr, ucase_t ca);
void uz16_n_to_case(uc16_t *cstr, size_t n, ucase_t ca);

void uz8_to_upper(const uc8_t *from, uc8_t *to);
void uz8_n_to_upper(const uc8_t *from, size_t n, uc8_t *to);
void uz8_to_lower(const uc8_t *from, uc8_t *to);
void uz8_n_to_lower(const uc8_t *from, size_t n, uc8_t *to);
void uz8_to_case(const uc8_t *from, uc8_t *to, ucase_t ca);
void uz8_n_to_case(const uc8_t *from, size_t n, uc8_t *to, ucase_t ca);

// Trim

size_t uz32_trim(uc32_t *cstr);
size_t uz32_n_trim(uc32_t *cstr, size_t n);
size_t uz32_trim_left(uc32_t *cstr);
size_t uz32_n_trim_left(uc32_t *cstr, size_t n);
size_t uz32_trim_right(const uc32_t *cstr);
size_t uz32_n_trim_right(const uc32_t *cstr, size_t n);

size_t uz16_trim(uc16_t *cstr);
size_t uz16_n_trim(uc16_t *cstr, size_t n);
size_t uz16_trim_left(uc16_t *cstr);
size_t uz16_n_trim_left(uc16_t *cstr, size_t n);
size_t uz16_trim_right(const uc16_t *cstr);
size_t uz16_n_trim_right(const uc16_t *cstr, size_t n);

size_t uz8_trim(uc8_t *cstr);
size_t uz8_n_trim(uc8_t *cstr, size_t n);
size_t uz8_trim_left(uc8_t *cstr);
size_t uz8_n_trim_left(uc8_t *cstr, size_t n);
size_t uz8_trim_right(const uc8_t *cstr);
size_t uz8_n_trim_right(const uc8_t *cstr, size_t n);

// Copy

void uz32_copy(uc32_t *dst, const uc32_t *src);
void uz32_copy_n(uc32_t *dst, const uc32_t *src, size_t n);
void uz32_n_copy_n(uc32_t *dst, size_t dst_len, const uc32_t *src, size_t src_len);

void uz16_copy(uc16_t *dst, const uc16_t *src);
void uz16_copy_n(uc16_t *dst, const uc16_t *src, size_t n);
void uz16_n_copy_n(uc16_t *dst, size_t dst_len, const uc16_t *src, size_t src_len);

void uz8_copy(uc8_t *dst, const uc8_t *src);
void uz8_copy_n(uc8_t *dst, const uc8_t *src, size_t n);
void uz8_n_copy_n(uc8_t *dst, size_t dst_len, const uc8_t *src, size_t src_len);

// Move

void uz32_move(uc32_t *dst, const uc32_t *src, size_t n);
void uz16_move(uc16_t *dst, const uc16_t *src, size_t n);
void uz8_move(uc8_t *dst, const uc8_t *src, size_t n);

// Reverse

void uz32_reverse(uc32_t *cstr);
void uz32_n_reverse(uc32_t *cstr, size_t n);

void uz16_reverse(uc16_t *cstr);
void uz16_n_reverse(uc16_t *cstr, size_t n);

void uz8_reverse(uc8_t *cstr);
void uz8_n_reverse(uc8_t *cstr, size_t n);

// Split

size_t uz32_new_csplit(const uc32_t *cstr, uc32_t c, ucv32_t **array);
size_t uz32_new_csplit_e(const uc32_t *cstr, uc32_t c, ucv32_t **array, bool *error);
size_t uz32_n_new_csplit(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t **array);
size_t uz32_n_new_csplit_e(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t **array, bool *error);
size_t uz32_csplit(const uc32_t *cstr, uc32_t c, ucv32_t *array, size_t array_len);
size_t uz32_n_csplit(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t *array, size_t array_len);

size_t uz32_new_split(uc32_t *cstr, uc32_t c, uv32_t **array);
size_t uz32_new_split_e(uc32_t *cstr, uc32_t c, uv32_t **array, bool *error);
size_t uz32_n_new_split(uc32_t *cstr, size_t n, uc32_t c, uv32_t **array);
size_t uz32_n_new_split_e(uc32_t *cstr, size_t n, uc32_t c, uv32_t **array, bool *error);
size_t uz32_split(uc32_t *cstr, uc32_t c, uv32_t *array, size_t array_len);
size_t uz32_n_split(uc32_t *cstr, size_t n, uc32_t c, uv32_t *array, size_t array_len);

size_t uz32_new_csplit_uz32(const uc32_t *cstr, const uc32_t *another, ucv32_t **array);
size_t uz32_new_csplit_uz32_e(const uc32_t *cstr, const uc32_t *another, ucv32_t **array, bool *error);
size_t uz32_n_new_csplit_uz32(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t **array);
size_t uz32_n_new_csplit_uz32_e(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t **array, bool *error);
size_t uz32_csplit_uz32(const uc32_t *cstr, const uc32_t *another, ucv32_t *array, size_t array_len);
size_t uz32_n_csplit_uz32(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t *array, size_t array_len);

size_t uz32_new_split_uz32(uc32_t *cstr, const uc32_t *another, uv32_t **array);
size_t uz32_new_split_uz32_e(uc32_t *cstr, const uc32_t *another, uv32_t **array, bool *error);
size_t uz32_n_new_split_uz32(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t **array);
size_t uz32_n_new_split_uz32_e(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t **array, bool *error);
size_t uz32_split_uz32(uc32_t *cstr, const uc32_t *another, uv32_t *array, size_t array_len);
size_t uz32_n_split_uz32(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t *array, size_t array_len);

size_t uz32_new_csplit_uz32_n(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t **array);
size_t uz32_new_csplit_uz32_n_e(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t **array, bool *error);
size_t uz32_n_new_csplit_uz32_n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t **array);
size_t uz32_n_new_csplit_uz32_n_e(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t **array, bool *error);
size_t uz32_csplit_uz32_n(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t *array, size_t array_len);
size_t uz32_n_csplit_uz32_n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t *array, size_t array_len);

size_t uz32_new_split_uz32_n(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t **array);
size_t uz32_new_split_uz32_n_e(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t **array, bool *error);
size_t uz32_n_new_split_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t **array);
size_t uz32_n_new_split_uz32_n_e(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t **array, bool *error);
size_t uz32_split_uz32_n(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t *array, size_t array_len);
size_t uz32_n_split_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t *array, size_t array_len);

// Replace

size_t uz32_replace_uc32_uc32(uc32_t *cstr, uc32_t from, uc32_t to);
size_t uz32_replace_uc32_uc32_c(uc32_t *cstr, uc32_t from, uc32_t to, size_t *count);
size_t uz32_n_replace_uc32_uc32(uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to);
size_t uz32_n_replace_uc32_uc32_c(uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to, size_t *count);

size_t uz32_replace_uz32_uc32(uc32_t *cstr, const uc32_t *from, uc32_t to);
size_t uz32_replace_uz32_uc32_c(uc32_t *cstr, const uc32_t *from, uc32_t to, size_t *count);
size_t uz32_n_replace_uz32_uc32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to);
size_t uz32_n_replace_uz32_uc32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to, size_t *count);

size_t uz32_replace_uz32_n_uc32(uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to);
size_t uz32_replace_uz32_n_uc32_c(uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to, size_t *count);
size_t uz32_n_replace_uz32_n_uc32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to);
size_t uz32_n_replace_uz32_n_uc32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to, size_t *count);

size_t uz32_replace_uc32_uz32(uc32_t *cstr, uc32_t from, const uc32_t *to);
size_t uz32_replace_uc32_uz32_c(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t *count);
size_t uz32_replace_uc32_uz32_len(const uc32_t *cstr, uc32_t from, const uc32_t *to);
size_t uz32_replace_uc32_uz32_len_c(const uc32_t *cstr, uc32_t from, const uc32_t *to, size_t *count);
size_t uz32_n_replace_uc32_uz32(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to);
size_t uz32_n_replace_uc32_uz32_c(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t *count);
size_t uz32_n_replace_uc32_uz32_len(const uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to);
size_t uz32_n_replace_uc32_uz32_len_c(const uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t *count);

size_t uz32_replace_uc32_uz32_n(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t to_len);
size_t uz32_replace_uc32_uz32_n_c(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t to_len, size_t *count);
size_t uz32_replace_uc32_uz32_n_len(const uc32_t *cstr, uc32_t from, size_t to_len);
size_t uz32_replace_uc32_uz32_n_len_c(const uc32_t *cstr, uc32_t from, size_t to_len, size_t *count);
size_t uz32_n_replace_uc32_uz32_n(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t to_len);
size_t uz32_n_replace_uc32_uz32_n_c(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t to_len, size_t *count);
size_t uz32_n_replace_uc32_uz32_n_len(const uc32_t *cstr, size_t cstr_len, uc32_t from, size_t to_len);
size_t uz32_n_replace_uc32_uz32_n_len_c(const uc32_t *cstr, size_t cstr_len, uc32_t from, size_t to_len, size_t *count);

size_t uz32_replace_uz32_uz32(uc32_t *cstr, const uc32_t *from, const uc32_t *to);
size_t uz32_replace_uz32_uz32_c(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t *count);
size_t uz32_replace_uz32_uz32_len(const uc32_t *cstr, const uc32_t *from, const uc32_t *to);
size_t uz32_replace_uz32_uz32_len_c(const uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t *count);
size_t uz32_n_replace_uz32_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to);
size_t uz32_n_replace_uz32_uz32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t *count);
size_t uz32_n_replace_uz32_uz32_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to);
size_t uz32_n_replace_uz32_uz32_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t *count);

size_t uz32_replace_uz32_n_uz32(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to);
size_t uz32_replace_uz32_n_uz32_c(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count);
size_t uz32_replace_uz32_n_uz32_len(const uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to);
size_t uz32_replace_uz32_n_uz32_len_c(const uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count);
size_t uz32_n_replace_uz32_n_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to);
size_t uz32_n_replace_uz32_n_uz32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count);
size_t uz32_n_replace_uz32_n_uz32_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to);
size_t uz32_n_replace_uz32_n_uz32_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count);

size_t uz32_replace_uz32_uz32_n(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t to_len);
size_t uz32_replace_uz32_uz32_n_c(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count);
size_t uz32_replace_uz32_uz32_n_len(const uc32_t *cstr, const uc32_t *from, size_t to_len);
size_t uz32_replace_uz32_uz32_n_len_c(const uc32_t *cstr, const uc32_t *from, size_t to_len, size_t *count);
size_t uz32_n_replace_uz32_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t to_len);
size_t uz32_n_replace_uz32_uz32_n_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count);
size_t uz32_n_replace_uz32_uz32_n_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t to_len);
size_t uz32_n_replace_uz32_uz32_n_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t to_len, size_t *count);

size_t uz32_replace_uz32_n_uz32_n(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len);
size_t uz32_replace_uz32_n_uz32_n_c(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count);
size_t uz32_replace_uz32_n_uz32_n_len(const uc32_t *cstr, const uc32_t *from, size_t from_len, size_t to_len);
size_t uz32_replace_uz32_n_uz32_n_len_c(const uc32_t *cstr, const uc32_t *from, size_t from_len, size_t to_len, size_t *count);
size_t uz32_n_replace_uz32_n_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len);
size_t uz32_n_replace_uz32_n_uz32_n_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count);
size_t uz32_n_replace_uz32_n_uz32_n_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, size_t to_len);
size_t uz32_n_replace_uz32_n_uz32_n_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, size_t to_len, size_t *count);


size_t uz16_replace_uc16_uc16(uc16_t *cstr, uc16_t from, uc16_t to);
size_t uz16_replace_uc16_uc16_c(uc16_t *cstr, uc16_t from, uc16_t to, size_t *count);
size_t uz16_n_replace_uc16_uc16(uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to);
size_t uz16_n_replace_uc16_uc16_c(uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to, size_t *count);

size_t uz16_replace_uz16_uc16(uc16_t *cstr, const uc16_t *from, uc16_t to);
size_t uz16_replace_uz16_uc16_c(uc16_t *cstr, const uc16_t *from, uc16_t to, size_t *count);
size_t uz16_n_replace_uz16_uc16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to);
size_t uz16_n_replace_uz16_uc16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to, size_t *count);

size_t uz16_replace_uz16_n_uc16(uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to);
size_t uz16_replace_uz16_n_uc16_c(uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to, size_t *count);
size_t uz16_n_replace_uz16_n_uc16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to);
size_t uz16_n_replace_uz16_n_uc16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to, size_t *count);

size_t uz16_replace_uc16_uz16(uc16_t *cstr, uc16_t from, const uc16_t *to);
size_t uz16_replace_uc16_uz16_c(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t *count);
size_t uz16_replace_uc16_uz16_len(const uc16_t *cstr, uc16_t from, const uc16_t *to);
size_t uz16_replace_uc16_uz16_len_c(const uc16_t *cstr, uc16_t from, const uc16_t *to, size_t *count);
size_t uz16_n_replace_uc16_uz16(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to);
size_t uz16_n_replace_uc16_uz16_c(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t *count);
size_t uz16_n_replace_uc16_uz16_len(const uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to);
size_t uz16_n_replace_uc16_uz16_len_c(const uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t *count);

size_t uz16_replace_uc16_uz16_n(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t to_len);
size_t uz16_replace_uc16_uz16_n_c(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t to_len, size_t *count);
size_t uz16_replace_uc16_uz16_n_len(const uc16_t *cstr, uc16_t from, size_t to_len);
size_t uz16_replace_uc16_uz16_n_len_c(const uc16_t *cstr, uc16_t from, size_t to_len, size_t *count);
size_t uz16_n_replace_uc16_uz16_n(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t to_len);
size_t uz16_n_replace_uc16_uz16_n_c(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t to_len, size_t *count);
size_t uz16_n_replace_uc16_uz16_n_len(const uc16_t *cstr, size_t cstr_len, uc16_t from, size_t to_len);
size_t uz16_n_replace_uc16_uz16_n_len_c(const uc16_t *cstr, size_t cstr_len, uc16_t from, size_t to_len, size_t *count);

size_t uz16_replace_uz16_uz16(uc16_t *cstr, const uc16_t *from, const uc16_t *to);
size_t uz16_replace_uz16_uz16_c(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t *count);
size_t uz16_replace_uz16_uz16_len(const uc16_t *cstr, const uc16_t *from, const uc16_t *to);
size_t uz16_replace_uz16_uz16_len_c(const uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t *count);
size_t uz16_n_replace_uz16_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to);
size_t uz16_n_replace_uz16_uz16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t *count);
size_t uz16_n_replace_uz16_uz16_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to);
size_t uz16_n_replace_uz16_uz16_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t *count);

size_t uz16_replace_uz16_n_uz16(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to);
size_t uz16_replace_uz16_n_uz16_c(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count);
size_t uz16_replace_uz16_n_uz16_len(const uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to);
size_t uz16_replace_uz16_n_uz16_len_c(const uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count);
size_t uz16_n_replace_uz16_n_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to);
size_t uz16_n_replace_uz16_n_uz16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count);
size_t uz16_n_replace_uz16_n_uz16_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to);
size_t uz16_n_replace_uz16_n_uz16_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count);

size_t uz16_replace_uz16_uz16_n(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t to_len);
size_t uz16_replace_uz16_uz16_n_c(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t to_len, size_t *count);
size_t uz16_replace_uz16_uz16_n_len(const uc16_t *cstr, const uc16_t *from, size_t to_len);
size_t uz16_replace_uz16_uz16_n_len_c(const uc16_t *cstr, const uc16_t *from, size_t to_len, size_t *count);
size_t uz16_n_replace_uz16_uz16_n(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t to_len);
size_t uz16_n_replace_uz16_uz16_n_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t to_len, size_t *count);
size_t uz16_n_replace_uz16_uz16_n_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t to_len);
size_t uz16_n_replace_uz16_uz16_n_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t to_len, size_t *count);

size_t uz16_replace_uz16_n_uz16_n(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len);
size_t uz16_replace_uz16_n_uz16_n_c(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len, size_t *count);
size_t uz16_replace_uz16_n_uz16_n_len(const uc16_t *cstr, const uc16_t *from, size_t from_len, size_t to_len);
size_t uz16_replace_uz16_n_uz16_n_len_c(const uc16_t *cstr, const uc16_t *from, size_t from_len, size_t to_len, size_t *count);
size_t uz16_n_replace_uz16_n_uz16_n(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len);
size_t uz16_n_replace_uz16_n_uz16_n_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len, size_t *count);
size_t uz16_n_replace_uz16_n_uz16_n_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, size_t to_len);
size_t uz16_n_replace_uz16_n_uz16_n_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, size_t to_len, size_t *count);


size_t uz8_replace_uc8_uc8(uc8_t *cstr, uc8_t from, uc8_t to);
size_t uz8_replace_uc8_uc8_c(uc8_t *cstr, uc8_t from, uc8_t to, size_t *count);
size_t uz8_n_replace_uc8_uc8(uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to);
size_t uz8_n_replace_uc8_uc8_c(uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to, size_t *count);

size_t uz8_replace_uz8_uc8(uc8_t *cstr, const uc8_t *from, uc8_t to);
size_t uz8_replace_uz8_uc8_c(uc8_t *cstr, const uc8_t *from, uc8_t to, size_t *count);
size_t uz8_n_replace_uz8_uc8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to);
size_t uz8_n_replace_uz8_uc8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to, size_t *count);

size_t uz8_replace_uz8_n_uc8(uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to);
size_t uz8_replace_uz8_n_uc8_c(uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to, size_t *count);
size_t uz8_n_replace_uz8_n_uc8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to);
size_t uz8_n_replace_uz8_n_uc8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to, size_t *count);

size_t uz8_replace_uc8_uz8(uc8_t *cstr, uc8_t from, const uc8_t *to);
size_t uz8_replace_uc8_uz8_c(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t *count);
size_t uz8_replace_uc8_uz8_len(const uc8_t *cstr, uc8_t from, const uc8_t *to);
size_t uz8_replace_uc8_uz8_len_c(const uc8_t *cstr, uc8_t from, const uc8_t *to, size_t *count);
size_t uz8_n_replace_uc8_uz8(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to);
size_t uz8_n_replace_uc8_uz8_c(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t *count);
size_t uz8_n_replace_uc8_uz8_len(const uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to);
size_t uz8_n_replace_uc8_uz8_len_c(const uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t *count);

size_t uz8_replace_uc8_uz8_n(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t to_len);
size_t uz8_replace_uc8_uz8_n_c(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t to_len, size_t *count);
size_t uz8_replace_uc8_uz8_n_len(const uc8_t *cstr, uc8_t from, size_t to_len);
size_t uz8_replace_uc8_uz8_n_len_c(const uc8_t *cstr, uc8_t from, size_t to_len, size_t *count);
size_t uz8_n_replace_uc8_uz8_n(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t to_len);
size_t uz8_n_replace_uc8_uz8_n_c(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t to_len, size_t *count);
size_t uz8_n_replace_uc8_uz8_n_len(const uc8_t *cstr, size_t cstr_len, uc8_t from, size_t to_len);
size_t uz8_n_replace_uc8_uz8_n_len_c(const uc8_t *cstr, size_t cstr_len, uc8_t from, size_t to_len, size_t *count);

size_t uz8_replace_uz8_uz8(uc8_t *cstr, const uc8_t *from, const uc8_t *to);
size_t uz8_replace_uz8_uz8_c(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t *count);
size_t uz8_replace_uz8_uz8_len(const uc8_t *cstr, const uc8_t *from, const uc8_t *to);
size_t uz8_replace_uz8_uz8_len_c(const uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t *count);
size_t uz8_n_replace_uz8_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to);
size_t uz8_n_replace_uz8_uz8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t *count);
size_t uz8_n_replace_uz8_uz8_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to);
size_t uz8_n_replace_uz8_uz8_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t *count);

size_t uz8_replace_uz8_n_uz8(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to);
size_t uz8_replace_uz8_n_uz8_c(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count);
size_t uz8_replace_uz8_n_uz8_len(const uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to);
size_t uz8_replace_uz8_n_uz8_len_c(const uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count);
size_t uz8_n_replace_uz8_n_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to);
size_t uz8_n_replace_uz8_n_uz8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count);
size_t uz8_n_replace_uz8_n_uz8_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to);
size_t uz8_n_replace_uz8_n_uz8_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count);

size_t uz8_replace_uz8_uz8_n(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t to_len);
size_t uz8_replace_uz8_uz8_n_c(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t to_len, size_t *count);
size_t uz8_replace_uz8_uz8_n_len(const uc8_t *cstr, const uc8_t *from, size_t to_len);
size_t uz8_replace_uz8_uz8_n_len_c(const uc8_t *cstr, const uc8_t *from, size_t to_len, size_t *count);
size_t uz8_n_replace_uz8_uz8_n(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t to_len);
size_t uz8_n_replace_uz8_uz8_n_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t to_len, size_t *count);
size_t uz8_n_replace_uz8_uz8_n_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t to_len);
size_t uz8_n_replace_uz8_uz8_n_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t to_len, size_t *count);

size_t uz8_replace_uz8_n_uz8_n(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len);
size_t uz8_replace_uz8_n_uz8_n_c(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len, size_t *count);
size_t uz8_replace_uz8_n_uz8_n_len(const uc8_t *cstr, const uc8_t *from, size_t from_len, size_t to_len);
size_t uz8_replace_uz8_n_uz8_n_len_c(const uc8_t *cstr, const uc8_t *from, size_t from_len, size_t to_len, size_t *count);
size_t uz8_n_replace_uz8_n_uz8_n(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len);
size_t uz8_n_replace_uz8_n_uz8_n_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len, size_t *count);
size_t uz8_n_replace_uz8_n_uz8_n_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, size_t to_len);
size_t uz8_n_replace_uz8_n_uz8_n_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, size_t to_len, size_t *count);

#endif