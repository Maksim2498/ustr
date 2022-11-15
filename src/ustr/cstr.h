#ifndef USTR_CSTR_H
#define USTR_CSTR_H

#include <stddef.h>

#include "char_t.h"

// Creation

#define uz32(literal) (uc32_t *)  U##literal
#define uz16(literal) (uc16_t *)  u##literal
#define  uz8(literal)  (uc8_t *) u8##literal

// Char Len

size_t uz16_char_len(const uc16_t *cstr);
size_t uz8_char_len(const uc8_t *cstr);

// Len

size_t uz32_len(const uc32_t *cstr);
size_t uz16_len(const uc16_t *cstr);
size_t uz8_len(const uc8_t *cstr);

// Cmp

int uz32_cmp(const uc32_t *lhs, const uc32_t *rhs);
int uz32_cmp_n(const uc32_t *lhs, const uc32_t *rhs, size_t n);
int uz32_cmp_nn(const uc32_t *lhs, size_t lhs_len, const uc32_t *rhs, size_t rhs_len);

int uz16_cmp(const uc16_t *lhs, const uc16_t *rhs);
int uz16_cmp_n(const uc16_t *lhs, const uc16_t *rhs, size_t n);
int uz16_cmp_nn(const uc16_t *lhs, size_t lhs_len, const uc16_t *rhs, size_t rhs_len);

int uz8_cmp(const uc8_t *lhs, const uc8_t *rhs);
int uz8_cmp_n(const uc8_t *lhs, const uc8_t *rhs, size_t n);
int uz8_cmp_nn(const uc8_t *lhs, size_t lhs_len, const uc8_t *rhs, size_t rhs_len);

// Search

// - Forward

ptrdiff_t uz32_pos(const uc32_t *cstr, const uc32_t *another);
ptrdiff_t uz32_n_pos(const uc32_t *cstr, size_t n, const uc32_t *another);
ptrdiff_t uz32_pos_n(const uc32_t *cstr, const uc32_t *another, size_t n);
ptrdiff_t uz32_n_pos_n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len);
ptrdiff_t uz32_c32_pos(const uc32_t *cstr, uc32_t c);
ptrdiff_t uz32_n_c32_pos(const uc32_t *cstr, size_t n, uc32_t c);

ptrdiff_t uz16_pos(const uc16_t *cstr, const uc16_t *another);
ptrdiff_t uz16_n_pos(const uc16_t *cstr, size_t n, const uc16_t *another);
ptrdiff_t uz16_pos_n(const uc16_t *cstr, const uc16_t *another, size_t n);
ptrdiff_t uz16_n_pos_n(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len);
ptrdiff_t uz16_c32_pos(const uc16_t *cstr, uc16_t c);
ptrdiff_t uz16_n_c32_pos(const uc16_t *cstr, size_t n, uc16_t c);

ptrdiff_t uz8_pos(const uc8_t *cstr, const uc8_t *another);
ptrdiff_t uz8_n_pos(const uc8_t *cstr, size_t n, const uc8_t *another);
ptrdiff_t uz8_pos_n(const uc8_t *cstr, const uc8_t *another, size_t n);
ptrdiff_t uz8_n_pos_n(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len);
ptrdiff_t uz8_c8_pos(const uc8_t *cstr, uc8_t c);
ptrdiff_t uz8_n_c8_pos(const uc8_t *cstr, size_t n, uc8_t c);

// - Backward

ptrdiff_t uz32_pos_r(const uc32_t *cstr, const uc32_t *another, size_t from);
ptrdiff_t uz32_pos_n_r(const uc32_t *cstr, const uc32_t *another, size_t n, size_t from);
ptrdiff_t uz32_n_pos_r(const uc32_t *cstr, size_t n, const uc32_t *another, size_t from);
ptrdiff_t uz32_n_pos_n_r(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, size_t from);
ptrdiff_t uz32_c32_pos_r(const uc32_t *cstr, uc32_t c, size_t from);
ptrdiff_t uz32_n_c32_pos_r(const uc32_t *cstr, size_t n, uc32_t c, size_t from);

ptrdiff_t uz16_pos_r(const uc16_t *cstr, const uc16_t *another, size_t from);
ptrdiff_t uz16_pos_n_r(const uc16_t *cstr, const uc16_t *another, size_t n, size_t from);
ptrdiff_t uz16_n_pos_r(const uc16_t *cstr, size_t n, const uc16_t *another, size_t from);
ptrdiff_t uz16_n_pos_n_r(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len, size_t from);
ptrdiff_t uz16_c16_pos_r(const uc16_t *cstr, uc16_t c, size_t from);
ptrdiff_t uz16_n_c16_pos_r(const uc16_t *cstr, size_t n, uc16_t c, size_t from);

ptrdiff_t uz8_pos_r(const uc8_t *cstr, const uc8_t *another, size_t from);
ptrdiff_t uz8_pos_n_r(const uc8_t *cstr, const uc8_t *another, size_t n, size_t from);
ptrdiff_t uz8_n_pos_r(const uc8_t *cstr, size_t n, const uc8_t *another, size_t from);
ptrdiff_t uz8_n_pos_n_r(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len, size_t from);
ptrdiff_t uz8_c8_pos_r(const uc8_t *cstr, uc8_t c, size_t from);
ptrdiff_t uz8_n_c8_pos_r(const uc8_t *cstr, size_t n, uc8_t c, size_t from);

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

size_t uz16_to_upper_len(const uc16_t *cstr);
size_t uz16_to_upper_len_n(const uc16_t *cstr, size_t n);
size_t uz16_to_lower_len(const uc16_t *cstr);
size_t uz16_to_lower_len_n(const uc16_t *cstr, size_t n);

size_t uz8_to_upper_len(const uc8_t *cstr);
size_t uz8_to_upper_len_n(const uc8_t *cstr, size_t n);
size_t uz8_to_lower_len(const uc8_t *cstr);
size_t uz8_to_lower_len_n(const uc8_t *cstr, size_t n);

void uz32_to_upper(uc32_t *cstr);
void uz32_to_upper_n(uc32_t *cstr, size_t n);
void uz32_to_lower(uc32_t *cstr);
void uz32_to_lower_n(uc32_t *cstr, size_t n);

void uz16_to_upper(const uc16_t *from, uc16_t *to);
void uz16_to_upper_n(const uc16_t *from, size_t n, uc16_t *to);
void uz16_to_lower(const uc16_t *from, uc16_t *to);
void uz16_to_lower_n(const uc16_t *from, size_t n, uc16_t *to);

void uz8_to_upper(const uc8_t *from, uc8_t *to);
void uz8_to_upper_n(const uc8_t *from, size_t n, uc8_t *to);
void uz8_to_lower(const uc8_t *from, uc8_t *to);
void uz8_to_lower_n(const uc8_t *from, size_t n, uc8_t *to);

#endif