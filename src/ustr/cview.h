#ifndef USTR_CVIEW_H
#define USTR_CVIEW_H

#include <stdbool.h>
#include <stddef.h>

#include "type/fmt/case.h"
#include "type/char.h"
#include "type/cview.h"
#include "type/str.h"
#include "type/view.h"

// Expand

#define UCV32_CEXPAND(view) ucv32_cchars(view), (view).len

// Creation

#define ucv32(literal)                                   \
    (ucv32_t) {                                          \
        .chars = (U##literal),                           \
        .len   = sizeof(U##literal) / sizeof(uc32_t) - 1 \
    }

ucv32_t ucv32_mk(void);
ucv32_t ucv32_from_range(ucv32_t view, size_t from, size_t len);
ucv32_t ucv32_from_ucv32_range(ucv32_t view, size_t from, size_t len);
ucv32_t ucv32_from_us32(const us32_t *str);
ucv32_t ucv32_from_us32_range(const us32_t *str, size_t from, size_t len);
ucv32_t ucv32_from_uv32(uv32_t view);
ucv32_t ucv32_from_uv32_range(uv32_t view, size_t from, size_t len);
ucv32_t ucv32_from_uz32(const uc32_t *cstr);
ucv32_t ucv32_from_uz32n(const uc32_t *cstr, size_t n);
ucv32_t ucv32_from_bool(bool b);
ucv32_t ucv32_from_case_bool(bool b, ucase_t c);
ucv32_t ucv32_from_upper_bool(bool b);
ucv32_t ucv32_from_lower_bool(bool b);

// Cross-UTF Len

size_t ucv32_len_n_from(ucv32_t view, unsigned n, size_t from);
size_t ucv32_len_32_from(ucv32_t view, size_t from);
size_t ucv32_len_16_from(ucv32_t view, size_t from);
size_t ucv32_len_8_from(ucv32_t view, size_t from);

size_t ucv32_len_n_to(ucv32_t view, unsigned n, size_t to);
size_t ucv32_len_32_to(ucv32_t view, size_t to);
size_t ucv32_len_16_to(ucv32_t view, size_t to);
size_t ucv32_len_8_to(ucv32_t view, size_t to);

size_t ucv32_len_n_range(ucv32_t view, unsigned n, size_t from, size_t len);
size_t ucv32_len_32_range(ucv32_t view, size_t from, size_t len);
size_t ucv32_len_16_range(ucv32_t view, size_t from, size_t len);
size_t ucv32_len_8_range(ucv32_t view, size_t from, size_t len);

size_t ucv32_len_n(ucv32_t view, unsigned n);
size_t ucv32_len_32(ucv32_t view);
size_t ucv32_len_16(ucv32_t view);
size_t ucv32_len_8(ucv32_t view);

// Trim

size_t ucv32_rtrim(ucv32_t *view);

// Char

uc32_t ucv32_at(ucv32_t view, size_t index);

// Cmp

int ucv32_cmp(ucv32_t lhs, ucv32_t rhs);
int ucv32_cmp_n(ucv32_t lhs, ucv32_t rhs, size_t n);
int ucv32_cmp_ucv32(ucv32_t lhs, ucv32_t rhs);
int ucv32_cmp_ucv32_n(ucv32_t lhs, ucv32_t rhs, size_t n);
int ucv32_cmp_uv32(ucv32_t lhs, uv32_t rhs);
int ucv32_cmp_uv32_n(ucv32_t lhs, uv32_t rhs, size_t n);
int ucv32_cmp_us32(ucv32_t lhs, const us32_t *rhs);
int ucv32_cmp_us32_n(ucv32_t lhs, const us32_t *rhs, size_t n);
int ucv32_cmp_uz32(ucv32_t lhs, const uc32_t *rhs);
int ucv32_cmp_uz32_n(ucv32_t lhs, const uc32_t *rhs, size_t n);
int ucv32_cmp_uz32n(ucv32_t lhs, const uc32_t *rhs, size_t n);
int ucv32_cmp_uz32n_n(ucv32_t lhs, const uc32_t *rhs, size_t rhs_len, size_t n);

// Search

// - Forward

ptrdiff_t ucv32_pos(ucv32_t view, ucv32_t another);
ptrdiff_t ucv32_pos_from(ucv32_t view, ucv32_t another, size_t from);
ptrdiff_t ucv32_pos_ucv32(ucv32_t view, ucv32_t another);
ptrdiff_t ucv32_pos_ucv32_from(ucv32_t view, ucv32_t another, size_t from);
ptrdiff_t ucv32_pos_uc32(ucv32_t view, uc32_t c);
ptrdiff_t ucv32_pos_uc32_from(ucv32_t view, uc32_t c, size_t from);
ptrdiff_t ucv32_pos_uz32(ucv32_t view, const uc32_t *cstr);
ptrdiff_t ucv32_pos_uz32_from(ucv32_t view, const uc32_t *cstr, size_t from);
ptrdiff_t ucv32_pos_uz32n(ucv32_t view, const uc32_t *cstr, size_t n);
ptrdiff_t ucv32_pos_uz32n_from(ucv32_t view, const uc32_t *cstr, size_t n, size_t from);
ptrdiff_t ucv32_pos_uv32(ucv32_t view, uv32_t another);
ptrdiff_t ucv32_pos_uv32_from(ucv32_t view, uv32_t another, size_t from);
ptrdiff_t ucv32_pos_us32(ucv32_t view, const us32_t *str);
ptrdiff_t ucv32_pos_us32_from(ucv32_t view, const us32_t *str, size_t from);

// - Backward

ptrdiff_t ucv32_rpos(ucv32_t view, ucv32_t another);
ptrdiff_t ucv32_rpos_from(ucv32_t view, ucv32_t another, size_t from);
ptrdiff_t ucv32_rpos_ucv32(ucv32_t view, ucv32_t another);
ptrdiff_t ucv32_rpos_ucv32_from(ucv32_t view, ucv32_t another, size_t from);
ptrdiff_t ucv32_rpos_uc32(ucv32_t view, uc32_t c);
ptrdiff_t ucv32_rpos_uc32_from(ucv32_t view, uc32_t c, size_t from);
ptrdiff_t ucv32_rpos_uz32(ucv32_t view, const uc32_t *cstr);
ptrdiff_t ucv32_rpos_uz32_from(ucv32_t view, const uc32_t *cstr, size_t from);
ptrdiff_t ucv32_rpos_uz32n(ucv32_t view, const uc32_t *cstr, size_t n);
ptrdiff_t ucv32_rpos_uz32n_from(ucv32_t view, const uc32_t *cstr, size_t n, size_t from);
ptrdiff_t ucv32_rpos_uv32(ucv32_t view, uv32_t another);
ptrdiff_t ucv32_rpos_uv32_from(ucv32_t view, uv32_t another, size_t from);
ptrdiff_t ucv32_rpos_us32(ucv32_t view, const us32_t *str);
ptrdiff_t ucv32_rpos_us32_from(ucv32_t view, const us32_t *str, size_t from);

// Iteration

const uc32_t *ucv32_cbegin(ucv32_t view);
const uc32_t *ucv32_cend(ucv32_t view);
const uc32_t *ucv32_coffset(ucv32_t view, size_t index);

// Len

bool ucv32_bounds(ucv32_t view, size_t index);
bool ucv32_ebounds(ucv32_t view, size_t index);
bool ucv32_bounds_range(ucv32_t view, size_t from, size_t len);
bool ucv32_ebounds_range(ucv32_t view, size_t from, size_t len);

size_t ucv32_len(ucv32_t view);
size_t ucv32_add_len(ucv32_t *view, ptrdiff_t delta);
void ucv32_set_len(ucv32_t *view, size_t len);

bool ucv32_empty(ucv32_t view);

// Split

size_t ucv32_new_csplit(ucv32_t view, ucv32_t another, ucv32_t **array);
size_t ucv32_new_csplit_e(ucv32_t view, ucv32_t another, ucv32_t **array, bool *error);
size_t ucv32_csplit(ucv32_t view, ucv32_t another, ucv32_t *array, size_t array_len);

size_t ucv32_new_csplit_uc32(ucv32_t view, uc32_t c, ucv32_t **array);
size_t ucv32_new_csplit_uc32_e(ucv32_t view, uc32_t c, ucv32_t **array, bool *error);
size_t ucv32_csplit_uc32(ucv32_t view, uc32_t c, ucv32_t *array, size_t array_len);

size_t ucv32_new_csplit_uz32(ucv32_t view, const uc32_t *cstr, ucv32_t **array);
size_t ucv32_new_csplit_uz32_e(ucv32_t view, const uc32_t *cstr, ucv32_t **array, bool *error);
size_t ucv32_csplit_uz32(ucv32_t view, const uc32_t *cstr, ucv32_t *array, size_t array_len);

size_t ucv32_new_csplit_uz32n(ucv32_t view, const uc32_t *cstr, size_t n, ucv32_t **array);
size_t ucv32_new_csplit_uz32n_e(ucv32_t view, const uc32_t *cstr, size_t n, ucv32_t **array, bool *error);
size_t ucv32_csplit_uz32_n(ucv32_t view, const uc32_t *cstr, size_t n, ucv32_t *array, size_t array_len);

size_t ucv32_new_csplit_ucv32(ucv32_t view, ucv32_t another, ucv32_t **array);
size_t ucv32_new_csplit_ucv32_e(ucv32_t view, ucv32_t another, ucv32_t **array, bool *error);
size_t ucv32_csplit_ucv32(ucv32_t view, ucv32_t another, ucv32_t *array, size_t array_len);

size_t ucv32_new_csplit_us32(ucv32_t view, const us32_t *str, ucv32_t **array);
size_t ucv32_new_csplit_us32_e(ucv32_t view, const us32_t *str, ucv32_t **array, bool *error);
size_t ucv32_csplit_us32(ucv32_t view, const us32_t *str, ucv32_t *array, size_t array_len);

size_t ucv32_new_csplit_uv32(ucv32_t view, uv32_t another, ucv32_t **array);
size_t ucv32_new_csplit_uv32_e(ucv32_t view, uv32_t another, ucv32_t **array, bool *error);
size_t ucv32_csplit_uv32(ucv32_t view, uv32_t another, ucv32_t *array, size_t array_len);

// Chars

const uc32_t *ucv32_cchars(ucv32_t view);
void ucv32_set_chars(ucv32_t *view, const uc32_t *chars);

// Valid

bool ucv32_valid_p(const ucv32_t *view);
bool ucv32_valid(ucv32_t view);

#endif