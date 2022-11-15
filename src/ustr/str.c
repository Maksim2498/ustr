#include "str.h"

#include <assert.h>

#include "cstr.h"
#include "cview.h"
#include "view.h"

us32_t us32_from(us32_t *str) {
    return (us32_t) {};
}

us32_t us32_from_e(us32_t *str, bool *error) {
    return (us32_t) {};
}

us32_t us32_from_us32_range(us32_t *str, size_t from, size_t len) {
    return (us32_t) {};
}

us32_t us32_from_us32_range_e(us32_t *str, size_t from, size_t len, bool *error) {
    return (us32_t) {};
}

us32_t us32_from_uv32(uv32_t view) {
    return (us32_t) {};
}

us32_t us32_from_uv32_e(uv32_t view, bool *error) {
    return (us32_t) {};
}

us32_t us32_from_uv32_range(uv32_t view, size_t from, size_t len) {
    return (us32_t) {};
}

us32_t us32_from_uv32_range_e(uv32_t view, size_t from, size_t len, bool *error) {
    return (us32_t) {};
}

us32_t us32_from_ucv32(ucv32_t view) {
    return (us32_t) {};
}

us32_t us32_from_ucv32_e(ucv32_t view, bool *error) {
    return (us32_t) {};
}

us32_t us32_from_ucv32_range(ucv32_t view, size_t from, size_t len) {
    return (us32_t) {};
}

us32_t us32_from_ucv32_range_e(ucv32_t view, size_t from, size_t len, bool *error) {
    return (us32_t) {};
}

us32_t us32_from_uz32(uc32_t *cstr) {
    return (us32_t) {};
}

us32_t us32_from_uz32_e(uc32_t *cstr, bool *error) {
    return (us32_t) {};
}

us32_t us32_from_uz32_n(uc32_t *cstr, size_t n) {
    return (us32_t) {};
}

us32_t us32_from_uz32_n_e(uc32_t *cstr, size_t n, bool *error) {
    return (us32_t) {};
}

us32_t us32_from_uc32(uc32_t c) {
    return (us32_t) {};
}

us32_t us32_from_uc32_e(uc32_t c, bool *error) {
    return (us32_t) {};
}

us32_t us32_from_uc32_n(uc32_t c, size_t n) {
    return (us32_t) {};
}

us32_t us32_from_uc32_n_e(uc32_t c, size_t n, bool *error) {
    return (us32_t) {};
}

void us32_free(us32_t *str) {
}

void us32_append(us32_t *str, const us32_t *another) {
}

void us32_append_e(us32_t *str, const us32_t *another, bool *error) {
}

void us32_append_uv32(us32_t *str, uv32_t view) {
}

void us32_append_uv32_e(us32_t *str, uv32_t view, bool *error) {
}

void us32_append_ucv32(us32_t *str, ucv32_t view) {
}

void us32_append_ucv32_e(us32_t *str, ucv32_t view, bool *error) {
}

void us32_append_uc32(us32_t *str, uc32_t c) {
}

void us32_append_uc32_e(us32_t *str, uc32_t c, bool *error) {
}

void us32_append_uc32_n(us32_t *str, uc32_t c, size_t n) {
}

void us32_append_uc32_ne(us32_t *str, uc32_t c, size_t n, bool *error) {
}

void us32_append_uz32(us32_t *str, const uc32_t *cstr) {
}

void us32_append_uz32_e(us32_t *str, const uc32_t *cstr, bool *error) {
}

void us32_append_uz32_n(us32_t *str, const uc32_t *cstr, size_t n) {
}

void us32_append_uz32_ne(us32_t *str, const uc32_t *cstr, size_t n, bool *error) {
}

void us32_trim(us32_t *str) {
}

void us32_trim_left(us32_t *str) {
}

void us32_trim_right(us32_t *str) {
}

uc32_t us32_uc32(const us32_t *str, size_t index) {
	return 0;
}

void us32_set_uc32(us32_t *str, uc32_t c, size_t index) {
}

int us32_cmp(const us32_t *lhs, const us32_t *rhs) {
	return 0;
}

int us32_cmp_n(const us32_t *lhs, const us32_t *rhs, size_t n) {
	return 0;
}

int us32_cmp_uv32(const us32_t *lhs, uv32_t rhs) {
	return 0;
}

int us32_cmp_uv32_n(const us32_t *lhs, uv32_t rhs, size_t n) {
	return 0;
}

int us32_cmp_ucv32(const us32_t *lhs, ucv32_t rhs) {
	return 0;
}

int us32_cmp_ucv32_n(const us32_t *lhs, ucv32_t rhs, size_t n) {
	return 0;
}

int us32_cmp_uz32(const us32_t *lhs, const uc32_t *rhs) {
	return 0;
}

int us32_cmp_uz32_n(const us32_t *lhs, const uc32_t *rhs, size_t n) {
	return 0;
}

ptrdiff_t us32_pos(const us32_t *str, const us32_t *another) {
	return 0;
}

ptrdiff_t us32_pos_from(const us32_t *str, const us32_t *another, size_t from) {
	return 0;
}

ptrdiff_t us32_uc32_pos(const us32_t *str, uc32_t c) {
	return 0;
}

ptrdiff_t us32_uc32_pos_from(const us32_t *str, uc32_t c, size_t from) {
	return 0;
}

ptrdiff_t us32_uz32_pos(const us32_t *str, const uc32_t *cstr) {
	return 0;
}

ptrdiff_t us32_uz32_pos_from(const us32_t *str, const uc32_t *cstr, size_t from) {
	return 0;
}

ptrdiff_t us32_uz32_n_pos(const us32_t *str, const uc32_t *cstr, size_t n) {
	return 0;
}

ptrdiff_t us32_uz32_n_pos_from(const us32_t *str, const uc32_t *cstr, size_t n, size_t from) {
	return 0;
}

ptrdiff_t us32_uv32_pos(const us32_t *str, uv32_t view) {
	return 0;
}

ptrdiff_t us32_uv32_pos_from(const us32_t *str, uv32_t view, size_t from) {
	return 0;
}

ptrdiff_t us32_ucv32_pos(const us32_t *str, ucv32_t view) {
	return 0;
}

ptrdiff_t us32_ucv32_pos_from(const us32_t *str, ucv32_t view, size_t from) {
	return 0;
}

ptrdiff_t us32_pos_r(const us32_t *str, const us32_t *another) {
	return 0;
}

ptrdiff_t us32_pos_from_r(const us32_t *str, const us32_t *another, size_t from) {
	return 0;
}

ptrdiff_t us32_uc32_pos_r(const us32_t *str, uc32_t c) {
	return 0;
}

ptrdiff_t us32_uc32_pos_from_r(const us32_t *str, uc32_t c, size_t from) {
	return 0;
}

ptrdiff_t us32_uz32_pos_r(const us32_t *str, const uc32_t *cstr) {
	return 0;
}

ptrdiff_t us32_uz32_pos_from_r(const us32_t *str, const uc32_t *cstr, size_t from) {
	return 0;
}

ptrdiff_t us32_uz32_n_pos_r(const us32_t *str, const uc32_t *cstr, size_t n) {
	return 0;
}

ptrdiff_t us32_uz32_n_pos_from_r(const us32_t *str, const uc32_t *cstr, size_t n, size_t from) {
	return 0;
}

ptrdiff_t us32_uv32_pos_r(const us32_t *str, uv32_t view) {
	return 0;
}

ptrdiff_t us32_uv32_pos_from_r(const us32_t *str, uv32_t view, size_t from) {
	return 0;
}

ptrdiff_t us32_ucv32_pos_r(const us32_t *str, ucv32_t view) {
	return 0;
}

ptrdiff_t us32_ucv32_pos_from_r(const us32_t *str, ucv32_t view, size_t from) {
	return 0;
}

void us32_fill(const us32_t *str, uc32_t c) {
}

void us32_fill_from(const us32_t *str, uc32_t c, size_t from) {
}

void us32_fill_from_r(const us32_t *str, uc32_t c, size_t from) {
}

void us32_fill_range(const us32_t *str, uc32_t c, size_t from, size_t len) {
}

void us32_fill_uz32(const us32_t *str, const uc32_t *cstr) {
}

void us32_fill_uz32_from(const us32_t *str, const uc32_t *cstr) {
}

void us32_fill_uz32_from_r(const us32_t *str, const uc32_t *cstr) {
}

void us32_fill_uz32_range(const us32_t *str, const uc32_t *cstr, size_t from, size_t len) {
}

void us32_fill_uz32_n(const us32_t *str, const uc32_t *cstr, size_t n) {
}

void us32_fill_uz32_n_from(const us32_t *str, const uc32_t *cstr, size_t n) {
}

void us32_fill_uz32_n_from_r(const us32_t *str, const uc32_t *cstr, size_t n) {
}

void us32_fill_uz32_n_range(const us32_t *str, const uc32_t *cstr, size_t n, size_t from, size_t len) {
}

void us32_fill_uv32(const us32_t *str, uv32_t view) {
}

void us32_fill_uv32_from(const us32_t *str, uv32_t view, size_t from) {
}

void us32_fill_uv32_from_r(const us32_t *str, uv32_t view, size_t from) {
}

void us32_fill_uv32_range(const us32_t *str, uv32_t view, size_t from, size_t len) {
}

void us32_fill_ucv32(const us32_t *str, ucv32_t view) {
}

void us32_fill_ucv32_from(const us32_t *str, ucv32_t view, size_t from) {
}

void us32_fill_ucv32_from_r(const us32_t *str, ucv32_t view, size_t from) {
}

void us32_fill_ucv32_range(const us32_t *str, ucv32_t view, size_t from, size_t len) {
}

void us32_fill_us32(const us32_t *str, const us32_t *another) {
}

void us32_fill_us32_from(const us32_t *str, const us32_t *another, size_t from) {
}

void us32_fill_us32_from_r(const us32_t *str, const us32_t *another, size_t from) {
}

void us32_fill_us32_range(const us32_t *str, const us32_t *another, size_t from, size_t len) {
}

void us32_to_upper(us32_t *str) {
}

void us32_to_lower(us32_t *str) {
}

uc32_t *us32_begin(us32_t *str) {
	return 0;
}

const uc32_t *us32_cbegin(const us32_t *str) {
	return 0;
}

uc32_t *us32_end(us32_t *str) {
	return 0;
}

const uc32_t *us32_cend(const us32_t *str) {
	return 0;
}

uc32_t *us32_at(us32_t *str, size_t index) {
	return 0;
}

const uc32_t *us32_cat(const us32_t *str, size_t index) {
	return 0;
}

bool us32_bounds(const us32_t *str, size_t index) {
	return 0;
}

size_t us32_len(const us32_t *str) {
	return 0;
}

void us32_add_len(us32_t *str, ptrdiff_t delta) {
}

void us32_add_len_e(us32_t *str, ptrdiff_t delta, bool *error) {
}

void us32_set_len(us32_t *str) {
}

void us32_set_len_e(us32_t *str, bool *error) {
}

bool us32_empty(const us32_t *str) {
	return 0;
}

size_t us32_cap(const us32_t *str) {
	return 0;
}

void us32_set_cap(us32_t *str, size_t cap) {
}

void us32_set_cap_e(us32_t *str, size_t cap, bool *error) {
}

void us32_shrink_to_fit(us32_t *str) {
}

void us32_shrink_to_fit_e(us32_t *str, bool *error) {
}

void us32_raise(us32_t *str) {
}

void us32_raise_e(us32_t *str, bool *error) {
}

bool us32_valid(const us32_t *str) {
	return 0;
}