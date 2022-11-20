#include "str.h"

#include <assert.h>

#include "config.h"
#include "cstr.h"
#include "cview.h"
#include "mem.h"
#include "view.h"

us32_t us32_mk(void) {
	return (us32_t) {
		.chars = NULL,
		.len   = 0,
		.cap   = 0
	};
}

us32_t us32_from(us32_t *str) {
	return us32_from_e(str, NULL);
}

us32_t us32_from_e(us32_t *str, bool *error) {
	us32_t res = us32_mk();
	us32_append_e(&res, str, error);
	return res;
}

us32_t us32_from_us32_range(us32_t *str, size_t from, size_t len) {
	return us32_from_us32_range_e(str, from, len, NULL);
}

us32_t us32_from_us32_range_e(us32_t *str, size_t from, size_t len, bool *error) {
	assert(us32_bounds(str, from) && us32_ebounds(str, from + len));
	us32_t res = us32_mk();
	us32_append_uz32_n_e(&res, str->chars + from, len, error);
	return res;
}

us32_t us32_from_uv32(uv32_t view) {
	return us32_from_uv32_e(view, NULL);
}

us32_t us32_from_uv32_e(uv32_t view, bool *error) {
	us32_t res = us32_mk();
	us32_append_uv32_e(&res, view, error);
	return res;
}

us32_t us32_from_uv32_range(uv32_t view, size_t from, size_t len) {
	return us32_from_uv32_range_e(view, from, len, NULL);
}

us32_t us32_from_uv32_range_e(uv32_t view, size_t from, size_t len, bool *error) {
	assert(uv32_bounds(view, from) && uv32_ebounds(view, from + len));
	us32_t res = us32_mk();
	us32_append_uz32_n_e(&res, view.chars + from, len, error);
	return res;
}

us32_t us32_from_ucv32(ucv32_t view) {
	return us32_from_ucv32_e(view, NULL);
}

us32_t us32_from_ucv32_e(ucv32_t view, bool *error) {
	us32_t res = us32_mk();
	us32_append_ucv32_e(&res, view, error);
	return res;
}

us32_t us32_from_ucv32_range(ucv32_t view, size_t from, size_t len) {
	return us32_from_ucv32_range_e(view, from, len, NULL);
}

us32_t us32_from_ucv32_range_e(ucv32_t view, size_t from, size_t len, bool *error) {
	assert(ucv32_bounds(view, from) && ucv32_ebounds(view, from + len));
	us32_t res = us32_mk();
	us32_append_uz32_n_e(&res, view.chars + from, len, error);
	return res;
}

us32_t us32_from_uz32(uc32_t *cstr) {
	return us32_from_uz32_e(cstr, NULL);
}

us32_t us32_from_uz32_e(uc32_t *cstr, bool *error) {
	us32_t res = us32_mk();
	us32_append_uz32_e(&res, cstr, error);
	return res;
}

us32_t us32_from_uz32_n(uc32_t *cstr, size_t n) {
    return us32_from_uz32_n_e(cstr, n, NULL);
}

us32_t us32_from_uz32_n_e(uc32_t *cstr, size_t n, bool *error) {
	us32_t res = us32_mk();
	us32_append_uz32_n_e(&res, cstr, n, error);
	return res;
}

us32_t us32_from_uc32(uc32_t c) {
	return us32_from_uc32_e(c, NULL);
}

us32_t us32_from_uc32_e(uc32_t c, bool *error) {
	us32_t res = us32_mk();
	us32_append_uc32_e(&res, c, error);
	return res;
}

us32_t us32_from_uc32_n(uc32_t c, size_t n) {
	return us32_from_uc32_n_e(c, n, NULL);
}

us32_t us32_from_uc32_n_e(uc32_t c, size_t n, bool *error) {
	us32_t res = us32_mk();
	us32_append_uc32_n_e(&res, c, n, error);
	return res;
}

void us32_free(us32_t *str) {
	assert(us32_valid(str));

	ufree(str->chars);
	
	str->chars = NULL;
	str->len   = 0;
	str->cap   = 0;
}

size_t us32_append(us32_t *str, const us32_t *another) {
	return us32_append_e(str, another, NULL);
}

size_t us32_append_e(us32_t *str, const us32_t *another, bool *error) {
	assert(us32_valid(another));
	return us32_append_uz32_n_e(str, another->chars, another->len, error);
}

size_t us32_append_uv32(us32_t *str, uv32_t view) {
	return us32_append_uv32_e(str, view, NULL);
}

size_t us32_append_uv32_e(us32_t *str, uv32_t view, bool *error) {
	assert(uv32_valid(view));
	return us32_append_uz32_n_e(str, view.chars, view.len, error);
}

size_t us32_append_ucv32(us32_t *str, ucv32_t view) {
	return us32_append_ucv32_e(str, view, NULL);
}

size_t us32_append_ucv32_e(us32_t *str, ucv32_t view, bool *error) {
	assert(ucv32_valid(view));
	return us32_append_uz32_n_e(str, view.chars, view.len, error);
}

size_t us32_append_uc32(us32_t *str, uc32_t c) {
	return us32_append_uc32_e(str, c, NULL);
}

size_t us32_append_uc32_e(us32_t *str, uc32_t c, bool *error) {
	assert(us32_valid(str));

	bool inner_error = false;

	us32_raise_if_needed_e(str, &inner_error);

	if (inner_error) {
		if (error)
			*error = true;
	} else
		str->chars[str->len++] = c;
	
	return str->len;
}

size_t us32_append_uc32_n(us32_t *str, uc32_t c, size_t n) {
	return us32_append_uc32_n_e(str, c, n, NULL);
}

size_t us32_append_uc32_n_e(us32_t *str, uc32_t c, size_t n, bool *error) {
	assert(us32_valid(str));

	bool inner_error = false;

	us32_raise_to_e(str, str->cap + n, &inner_error);

	if (inner_error) {
		if (error)
			*error = true;
	} else
		while (n--)
			str->chars[str->len++] = c;

	return str->len;
}

size_t us32_append_uz32(us32_t *str, const uc32_t *cstr) {
	return us32_append_uz32_e(str, cstr, NULL);
}

size_t us32_append_uz32_e(us32_t *str, const uc32_t *cstr, bool *error) {
	return us32_append_uz32_n_e(str, cstr, uz32_len(cstr), error);
}

size_t us32_append_uz32_n(us32_t *str, const uc32_t *cstr, size_t n) {
	return us32_append_uz32_n_e(str, cstr, n, NULL);
}

size_t us32_append_uz32_n_e(us32_t *str, const uc32_t *cstr, size_t n, bool *error) {
	assert(us32_valid(str) && cstr);

	bool inner_error = false;

	us32_raise_to_e(str, str->cap + n, &inner_error);

	if (inner_error) {
		if (error)
			*error = true;
	} else
		while (n--)
			str->chars[str->len++] = *cstr++;

	return str->len;
}

void us32_reverse(us32_t *str) {
	assert(us32_valid(str));
	uz32_n_reverse(str->chars, str->len);
}

size_t us32_trim(us32_t *str) {
	assert(us32_valid(str));
	return str->len = uz32_n_trim(str->chars, str->len);
}

size_t us32_trim_left(us32_t *str) {
	assert(us32_valid(str));
	return str->len = uz32_n_trim_left(str->chars, str->len);
}

size_t us32_trim_right(us32_t *str) {
	assert(us32_valid(str));
	return str->len = uz32_n_trim_right(str->chars, str->len);
}

uc32_t us32_uc32(const us32_t *str, size_t index) {
	assert(us32_bounds(str, index));
	return str->chars[index];
}

void us32_set_uc32(us32_t *str, uc32_t c, size_t index) {
	assert(us32_bounds(str, index));
	str->chars[index] = c;
}

int us32_cmp(const us32_t *lhs, const us32_t *rhs) {
	assert(us32_valid(lhs) && us32_valid(rhs));
	return uz32_n_cmp_n(lhs->chars, lhs->len, rhs->chars, rhs->len);
}

int us32_cmp_n(const us32_t *lhs, const us32_t *rhs, size_t n) {
	assert(us32_ebounds(lhs, n) && us32_ebounds(rhs, n));
	return uz32_n_cmp_n(lhs->chars, n, rhs->chars, n);
}

int us32_cmp_uv32(const us32_t *lhs, uv32_t rhs) {
	assert(us32_valid(lhs) && uv32_valid(rhs));
	return uz32_n_cmp_n(lhs->chars, lhs->len, rhs.chars, rhs.len);
}

int us32_cmp_uv32_n(const us32_t *lhs, uv32_t rhs, size_t n) {
	assert(us32_ebounds(lhs, n) && uv32_ebounds(rhs, n));
	return uz32_n_cmp_n(lhs->chars, n, rhs.chars, n);
}

int us32_cmp_ucv32(const us32_t *lhs, ucv32_t rhs) {
	assert(us32_valid(lhs) && ucv32_valid(rhs));
	return uz32_n_cmp_n(lhs->chars, lhs->len, rhs.chars, rhs.len);
}

int us32_cmp_ucv32_n(const us32_t *lhs, ucv32_t rhs, size_t n) {
	assert(us32_ebounds(lhs, n) && ucv32_ebounds(rhs, n));
	return uz32_n_cmp_n(lhs->chars, n, rhs.chars, n);
}

int us32_cmp_uz32(const us32_t *lhs, const uc32_t *rhs) {
	assert(us32_valid(lhs) && rhs);
	return uz32_n_cmp(lhs->chars, lhs->len, rhs);
}

int us32_cmp_uz32_n(const us32_t *lhs, const uc32_t *rhs, size_t n) {
	assert(us32_valid(lhs) && rhs);
	return uz32_n_cmp_n(lhs->chars, lhs->len, rhs, n);
}

ptrdiff_t us32_pos(const us32_t *str, const us32_t *another) {
	assert(us32_valid(str) && us32_valid(another));
	return uz32_n_pos_n(str->chars, str->len, another->chars, another->len);
}

ptrdiff_t us32_pos_from(const us32_t *str, const us32_t *another, size_t from) {
	assert(us32_bounds(str, from) && us32_valid(another));
	return uz32_n_pos_n(str->chars + from, str->len - from, another->chars, another->len);
}

ptrdiff_t us32_uc32_pos(const us32_t *str, uc32_t c) {
	assert(us32_valid(str));
	return uz32_n_uc32_pos(str->chars, str->len, c);
}

ptrdiff_t us32_uc32_pos_from(const us32_t *str, uc32_t c, size_t from) {
	assert(us32_bounds(str, from));
	return uz32_n_uc32_pos(str->chars + from, str->len - from, c);
}

ptrdiff_t us32_uz32_pos(const us32_t *str, const uc32_t *cstr) {
	assert(us32_valid(str) && cstr);
	return uz32_n_pos(str->chars, str->len, cstr);
}

ptrdiff_t us32_uz32_pos_from(const us32_t *str, const uc32_t *cstr, size_t from) {
	assert(us32_bounds(str, from) && cstr);
	return uz32_n_pos(str->chars + from, str->len - from, cstr);
}

ptrdiff_t us32_uz32_n_pos(const us32_t *str, const uc32_t *cstr, size_t n) {
	assert(us32_valid(str) && cstr);
	return uz32_n_pos_n(str->chars, str->len, cstr, n);
}

ptrdiff_t us32_uz32_n_pos_from(const us32_t *str, const uc32_t *cstr, size_t n, size_t from) {
	assert(us32_bounds(str, from) && cstr);
	return uz32_n_pos_n(str->chars + from, str->len - from, cstr, n);
}

ptrdiff_t us32_uv32_pos(const us32_t *str, uv32_t view) {
	assert(us32_valid(str) && uv32_valid(view));
	return uz32_n_pos_n(str->chars, str->len, view.chars, view.len);
}

ptrdiff_t us32_uv32_pos_from(const us32_t *str, uv32_t view, size_t from) {
	assert(us32_bounds(str, from) && uv32_valid(view));
	return uz32_n_pos_n(str->chars + from, str->len - from, view.chars, view.len);
}

ptrdiff_t us32_ucv32_pos(const us32_t *str, ucv32_t view) {
	assert(us32_valid(str) && ucv32_valid(view));
	return uz32_n_pos_n(str->chars, str->len, view.chars, view.len);
}

ptrdiff_t us32_ucv32_pos_from(const us32_t *str, ucv32_t view, size_t from) {
	assert(us32_bounds(str, from) && ucv32_valid(view));
	return uz32_n_pos_n(str->chars + from, str->len - from, view.chars, view.len);
}

ptrdiff_t us32_pos_r(const us32_t *str, const us32_t *another) {
	assert(us32_valid(str) && us32_valid(another));
	return uz32_n_pos_n_r(str->chars, str->len, another->chars, another->len, str->len - 1);
}

ptrdiff_t us32_pos_from_r(const us32_t *str, const us32_t *another, size_t from) {
	assert(us32_bounds(str, from) && us32_valid(another));
	return uz32_n_pos_n_r(str->chars, str->len, another->chars, another->len, from);
}

ptrdiff_t us32_uc32_pos_r(const us32_t *str, uc32_t c) {
	assert(us32_valid(str));
	return uz32_n_uc32_pos_r(str->chars, str->len, c, str->len - 1);
}

ptrdiff_t us32_uc32_pos_from_r(const us32_t *str, uc32_t c, size_t from) {
	assert(us32_bounds(str, from));
	return uz32_n_uc32_pos_r(str->chars, str->len, c, from);
}

ptrdiff_t us32_uz32_pos_r(const us32_t *str, const uc32_t *cstr) {
	assert(us32_valid(str) && cstr);
	return uz32_n_pos_r(str->chars, str->len, cstr, str->len - 1);
}

ptrdiff_t us32_uz32_pos_from_r(const us32_t *str, const uc32_t *cstr, size_t from) {
	assert(us32_bounds(str, from) && cstr);
	return uz32_n_pos_r(str->chars, str->len, cstr, from);
}

ptrdiff_t us32_uz32_n_pos_r(const us32_t *str, const uc32_t *cstr, size_t n) {
	assert(us32_valid(str) && cstr);
	return uz32_n_pos_n_r(str->chars, str->len, cstr, n, str->len - 1);
}

ptrdiff_t us32_uz32_n_pos_from_r(const us32_t *str, const uc32_t *cstr, size_t n, size_t from) {
	assert(us32_bounds(str, from) && cstr);
	return uz32_n_pos_n_r(str->chars, str->len, cstr, n, from);
}

ptrdiff_t us32_uv32_pos_r(const us32_t *str, uv32_t view) {
	assert(us32_valid(str) && uv32_valid(view));
	return uz32_n_pos_n_r(str->chars, str->len, view.chars, view.len, str->len - 1);
}

ptrdiff_t us32_uv32_pos_from_r(const us32_t *str, uv32_t view, size_t from) {
	assert(us32_bounds(str, from) && uv32_valid(view));
	return uz32_n_pos_n_r(str->chars, str->len, view.chars, view.len, from);
}

ptrdiff_t us32_ucv32_pos_r(const us32_t *str, ucv32_t view) {
	assert(us32_valid(str) && ucv32_valid(view));
	return uz32_n_pos_n_r(str->chars, str->len, view.chars, view.len, str->len - 1);
}

ptrdiff_t us32_ucv32_pos_from_r(const us32_t *str, ucv32_t view, size_t from) {
	assert(us32_bounds(str, from) && ucv32_valid(view));
	return uz32_n_pos_n_r(str->chars, str->len, view.chars, view.len, from);
}

void us32_fill(const us32_t *str, uc32_t c) {
	assert(us32_valid(str));
	uz32_n_fill(str->chars, str->len, c);
}

void us32_fill_from(const us32_t *str, uc32_t c, size_t from) {
	assert(us32_bounds(str, from));
	uz32_n_fill(str->chars + from, str->len - from, c);
}

void us32_fill_to(const us32_t *str, uc32_t c, size_t to) {
	assert(us32_ebounds(str, to));
	uz32_n_fill(str->chars, to, c);
}

void us32_fill_range(const us32_t *str, uc32_t c, size_t from, size_t len) {
	assert(us32_bounds(str, from) && us32_ebounds(str, from + len));
	uz32_n_fill(str->chars + from, len, c);
}

void us32_fill_uz32(const us32_t *str, const uc32_t *cstr) {
	assert(us32_valid(str) && cstr);
	uz32_n_fill_uz32(str->chars, str->len, cstr);
}

void us32_fill_uz32_from(const us32_t *str, const uc32_t *cstr, size_t from) {
	assert(us32_bounds(str, from) && cstr);
	uz32_n_fill_uz32(str->chars + from, str->len - from, cstr);
}

void us32_fill_uz32_to(const us32_t *str, const uc32_t *cstr, size_t to) {
	assert(us32_valid(str) && cstr);
	uz32_n_fill_uz32(str->chars, to, cstr);
}

void us32_fill_uz32_range(const us32_t *str, const uc32_t *cstr, size_t from, size_t len) {
	assert(us32_bounds(str, from)
		&& us32_ebounds(str, from + len)
		&& cstr);

	uz32_n_fill_uz32(str->chars + from, len, cstr);
}

void us32_fill_uz32_n(const us32_t *str, const uc32_t *cstr, size_t n) {
	assert(us32_valid(str) && cstr);
	uz32_n_fill_uz32_n(str->chars, str->len, cstr, n);
}

void us32_fill_uz32_n_from(const us32_t *str, const uc32_t *cstr, size_t n, size_t from) {
	assert(us32_bounds(str, from) && cstr);
	uz32_n_fill_uz32_n(str->chars + from, str->len - from, cstr, n);
}

void us32_fill_uz32_n_to(const us32_t *str, const uc32_t *cstr, size_t n, size_t to) {
	assert(us32_ebounds(str, to) && cstr);
	uz32_n_fill_uz32_n(str->chars, to, cstr, n);
}

void us32_fill_uz32_n_range(const us32_t *str, const uc32_t *cstr, size_t n, size_t from, size_t len) {
	assert(us32_bounds(str, from)
		&& us32_ebounds(str, from + len)
		&& cstr);

	uz32_n_fill_uz32_n(str->chars + from, len, cstr, n);
}

void us32_fill_uv32(const us32_t *str, uv32_t view) {
	assert(us32_valid(str) && uv32_valid(view));
	uz32_n_fill_uz32_n(str->chars, str->len, view.chars, view.len);
}

void us32_fill_uv32_from(const us32_t *str, uv32_t view, size_t from) {
	assert(us32_bounds(str, from) && uv32_valid(view));
	uz32_n_fill_uz32_n(str->chars + from, str->len - from, view.chars, view.len);
}

void us32_fill_uv32_to(const us32_t *str, uv32_t view, size_t to) {
	assert(us32_ebounds(str, to) && uv32_valid(view));
	uz32_n_fill_uz32_n(str->chars, to, view.chars, view.len);
}

void us32_fill_uv32_range(const us32_t *str, uv32_t view, size_t from, size_t len) {
	assert(us32_bounds(str, from)
		&& us32_ebounds(str, from + len)
		&& uv32_valid(view));
		
	uz32_n_fill_uz32_n(str->chars + from, len, view.chars, view.len);
}

void us32_fill_ucv32(const us32_t *str, ucv32_t view) {
	assert(us32_valid(str) && ucv32_valid(view));
	uz32_n_fill_uz32_n(str->chars, str->len, view.chars, view.len);
}

void us32_fill_ucv32_from(const us32_t *str, ucv32_t view, size_t from) {
	assert(us32_bounds(str, from) && ucv32_valid(view));
	uz32_n_fill_uz32_n(str->chars + from, str->len - from, view.chars, view.len);
}

void us32_fill_ucv32_to(const us32_t *str, ucv32_t view, size_t to) {
	assert(us32_ebounds(str, to) && ucv32_valid(view));
	uz32_n_fill_uz32_n(str->chars, to, view.chars, view.len);
}

void us32_fill_ucv32_range(const us32_t *str, ucv32_t view, size_t from, size_t len) {
	assert(us32_bounds(str, from)
		&& us32_ebounds(str, from + len)
		&& ucv32_valid(view));

	uz32_n_fill_uz32_n(str->chars + from, len, view.chars, view.len);
}

void us32_fill_us32(const us32_t *str, const us32_t *another) {
	assert(us32_valid(str) && us32_valid(another));
	uz32_n_fill_uz32_n(str->chars, str->len, another->chars, another->len);
}

void us32_fill_us32_from(const us32_t *str, const us32_t *another, size_t from) {
	assert(us32_bounds(str, from) && us32_valid(another));
	uz32_n_fill_uz32_n(str->chars + from, str->len - from, another->chars, another->len);
}

void us32_fill_us32_to(const us32_t *str, const us32_t *another, size_t to) {
	assert(us32_ebounds(str, to) && us32_valid(another));
	uz32_n_fill_uz32_n(str->chars, to, another->chars, another->len);
}

void us32_fill_us32_range(const us32_t *str, const us32_t *another, size_t from, size_t len) {
	assert(us32_bounds(str, from)
		&& us32_ebounds(str, from + len)
		&& us32_valid(another));
	
	uz32_n_fill_uz32_n(str->chars + from, len, another->chars, another->len);
}

void us32_to_upper(us32_t *str) {
	assert(us32_valid(str));
	uz32_n_to_upper(str->chars, str->len);
}

void us32_to_lower(us32_t *str) {
	assert(us32_valid(str));
	uz32_n_to_lower(str->chars, str->len);
}

uc32_t *us32_begin(us32_t *str) {
	assert(us32_valid(str));
	return str->chars;
}

const uc32_t *us32_cbegin(const us32_t *str) {
	assert(us32_valid(str));
	return str->chars;
}

uc32_t *us32_end(us32_t *str) {
	assert(us32_valid(str));
	return str->chars + str->len;
}

const uc32_t *us32_cend(const us32_t *str) {
	assert(us32_valid(str));
	return str->chars + str->len;
}

uc32_t *us32_at(us32_t *str, size_t index) {
	assert(us32_ebounds(str, index));
	return str->chars + index;
}

const uc32_t *us32_cat(const us32_t *str, size_t index) {
	assert(us32_ebounds(str, index));
	return str->chars + index;
}

bool us32_bounds(const us32_t *str, size_t index) {
	assert(us32_valid(str));
	return index < str->len;
}

bool us32_ebounds(const us32_t *str, size_t index) {
	assert(us32_valid(str));
	return index <= str->len;
}

size_t us32_len(const us32_t *str) {
	assert(us32_valid(str));
	return str->len;
}

size_t us32_add_len(us32_t *str, ptrdiff_t delta) {
	return us32_add_len_e(str, delta, NULL);
}

size_t us32_add_len_e(us32_t *str, ptrdiff_t delta, bool *error) {
	assert(us32_valid(str) && -(ptrdiff_t) str->len <= delta);
	return us32_set_len_e(str, (ptrdiff_t) str->len + delta, error);
}

size_t us32_set_len(us32_t *str, size_t len) {
	return us32_set_len_e(str, len, NULL);
}

size_t us32_set_len_e(us32_t *str, size_t len, bool *error) {
	assert(us32_valid(str));

	bool inner_error = false;

	if (len > str->cap) 
		us32_raise_to_e(str, len, &inner_error);

	if (inner_error) {
		if (error)
			*error = true;
	} else
		str->len = len;

	return str->len;
}

bool us32_empty(const us32_t *str) {
	assert(us32_valid(str));
	return !str->len;
}

void us32_clear(us32_t *str) {
	assert(us32_valid(str));
	str->len = 0;
}

size_t us32_cap(const us32_t *str) {
	assert(us32_valid(str));
	return str->cap;
}

size_t us32_set_cap(us32_t *str, size_t cap) {
	return us32_set_cap_e(str, cap, NULL);
}

size_t us32_set_cap_e(us32_t *str, size_t cap, bool *error) {
	assert(us32_valid(str));

	uc32_t *new_chars = urealloc(str->chars, sizeof(uc32_t) * cap);

	if (new_chars) {
		str->chars = new_chars;
		str->cap   = cap;
	
		if (cap < str->len)
			str->len = cap;
	} else if (error)
		*error = true;

	return str->cap;
}

size_t us32_shrink_to_fit(us32_t *str) {
	return us32_shrink_to_fit_e(str, NULL);
}

size_t us32_shrink_to_fit_e(us32_t *str, bool *error) {
	assert(us32_valid(str));

	uc32_t *new_chars = urealloc(str->chars, sizeof(uc32_t) * str->len);

	if (new_chars) {
		str->chars = new_chars;
		str->cap   = str->len;
	} else if (error)
		*error = true;

	return str->cap;
}

size_t us32_raise_if_needed(us32_t *str) {
	return us32_raise_if_needed_e(str, NULL);
}

size_t us32_raise_if_needed_e(us32_t *str, bool *error) {
	assert(us32_valid(str));

	if (str->cap == str->len)
		us32_raise_e(str, error);

	return str->cap;
}

size_t us32_raise(us32_t *str) {
	return us32_raise_e(str, NULL);
}

size_t us32_raise_e(us32_t *str, bool *error) {
	assert(us32_valid(str));
	
	size_t  new_cap   = str->cap ? USTR_RAISE_FACTOR * str->cap : USTR_INIT_CAP;
	uc32_t *new_chars = urealloc(str->chars, sizeof(uc32_t) * new_cap);

	if (new_chars) {
		str->chars = new_chars;
		str->cap   = new_cap;
	} else if (error)
		*error = true;

	return str->cap;
}

size_t us32_raise_to(us32_t *str, size_t to) {
	return us32_raise_to_e(str, to, NULL);
}

size_t us32_raise_to_e(us32_t *str, size_t to, bool *error) {
	assert(us32_valid(str));

	if (!to)
		return str->cap;

	size_t new_cap = str->cap ? str->cap : USTR_INIT_CAP;

	while (new_cap < to)
		new_cap *= USTR_RAISE_FACTOR;

	if (new_cap == str->cap)
		return str->cap;

	uc32_t *new_chars = urealloc(str->chars, sizeof(uc32_t) * new_cap);

	if (new_chars) {
		str->chars = new_chars;
		str->cap   = new_cap;
	} else if (error)
		*error = true;

	return str->cap;
}

bool us32_valid(const us32_t *str) {
	return str
		&& (bool) str->chars == (bool) str->cap
		&& str->len <= str->cap;
}